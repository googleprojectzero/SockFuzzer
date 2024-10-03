// Copyright 2024 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "third_party/concurrence/sync/tracker.h"

#include <algorithm>
#include <cstdlib>
#include <utility>

#include "third_party/concurrence/backtrace/backtrace.h"
#include "third_party/concurrence/sync/mutex.h"
#include "third_party/concurrence/sync/rwlock.h"
#include "third_party/concurrence/sync/sync.h"

class Scheduler;

extern bool is_verbose;

SyncTracker::SyncTracker(Scheduler *scheduler) : scheduler_(scheduler) {}
SyncTracker::~SyncTracker() = default;

VirtualMutex *SyncTracker::AllocateMutex() {
  auto mutex = std::make_unique<VirtualMutex>(this);
  VirtualMutex *ptr = mutex.get();
  all_primitives_[ptr] = std::move(mutex);
#ifndef NDEBUG
  session_tracked_primitives_.insert(ptr);
#endif
  return ptr;
}

void SyncTracker::FreeMutex(VirtualMutex *mutex) {
  all_primitives_.erase(mutex);
#ifndef NDEBUG
  session_tracked_primitives_.erase(mutex);
#endif
}

VirtualRwLock *SyncTracker::AllocateRwLock() {
  auto rwlock = std::make_unique<VirtualRwLock>(this);
  VirtualRwLock *ptr = rwlock.get();
  all_primitives_[ptr] = std::move(rwlock);
#ifndef NDEBUG
  session_tracked_primitives_.insert(ptr);
#endif
  return ptr;
}

void SyncTracker::FreeRwLock(VirtualRwLock *rwlock) {
  all_primitives_.erase(rwlock);
#ifndef NDEBUG
  session_tracked_primitives_.erase(rwlock);
#endif
}

// Assistance routines to help debug blocked threads
absl::flat_hash_set<Sync *> SyncTracker::Owned(ThreadHandle handle) {
  absl::flat_hash_set<Sync *> owned;
  for (const auto &it : all_primitives_) {
    Sync *sync = it.first;
    if (sync->IsOwnedBy(handle)) {
      owned.insert(sync);
    }
  }
  return owned;
}

Sync *SyncTracker::GetObjectWithWaiter(ThreadHandle handle) {
  for (const auto &it : all_primitives_) {
    Sync *sync = it.first;
    if (std::find(sync->waiters().begin(), sync->waiters().end(), handle) != sync->waiters().end()) {
      if (sync->IsOwnedBy(handle)) {
        abort();
      }
      return sync;
    }
  }
  return nullptr;
}

bool SyncTracker::FindDependencyPath(ThreadHandle source,
                                     ThreadHandle destination,
                                     std::deque<ThreadHandle> &path) {
  if (source == destination) {
    if (!path.empty()) {
      abort();
    }
    path.push_front(destination);
    return true;
  }

  Sync *wanted = GetObjectWithWaiter(source);
  // Not waiting on an object
  if (!wanted) {
    return false;
  }

  for (ThreadHandle neighbor : wanted->owners()) {
    if (FindDependencyPath(neighbor, destination, path)) {
      path.push_front(source);
      return true;
    }
  }

  return false;
}

void SyncTracker::BeginSession() {
#ifndef NDEBUG
  session_tracked_primitives_.clear();
#endif
}

void SyncTracker::ReportSession() {
#ifndef NDEBUG
  if (!is_verbose || session_tracked_primitives_.empty()) {
    return;
  }
  // TODO(nedwill): investigate if it makes sense to keep some allocated
  return;
  printf(
      "SyncTracker Report: there are %lu sync primitives that were never "
      "freed.\n",
      session_tracked_primitives_.size());

  for (auto *sync : session_tracked_primitives_) {
    printf("Sync primitive was never freed. Created here:\n");
    sync->construction_stacktrace()->Print();
  }
#endif
}

void SyncTracker::FreeSession() {
#ifndef NDEBUG
  for (auto *sync : session_tracked_primitives_) {
    all_primitives_.erase(sync);
  }
  session_tracked_primitives_.clear();
#endif
}
