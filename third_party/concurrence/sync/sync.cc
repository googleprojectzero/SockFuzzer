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

#include "sync.h"

#include <deque>
#include <iostream>
#include <cstdlib>
#include <string>

#include "absl/hash/hash.h"
#include "absl/log/check.h"
#include "absl/meta/type_traits.h"
#include "absl/strings/str_format.h"
#include "third_party/concurrence/backtrace/backtrace.h"
#include "third_party/concurrence/scheduler/scheduler.h"
#include "tracker.h"

extern bool is_verbose;

Sync::Sync(SyncTracker *sync_tracker)
    : sync_tracker_(sync_tracker), scheduler_(sync_tracker->scheduler()) {
  if (is_verbose) {
    construction_stacktrace_ = std::make_unique<StackTrace>();
  }
}

Sync::~Sync() = default;

void Sync::AddWaiter() {
  if (IsOwnedBy(g_current_thread)) {
    HandleNestedWait();
  }
  // Remove our existing wait if we already are waiting to avoid duplication
  // TODO(nedwill): add a unit test for this case
  RemoveWaiter();
  waiters_.push_back(g_current_thread);
  if (is_verbose) {
    DetectDeadlock();
  }
}

void Sync::RemoveWaiter() {
  auto it = std::find(waiters_.begin(), waiters_.end(), g_current_thread);
  if (it == waiters_.end()) {
    return;
  }
  waiters_.erase(it);
}

void Sync::WakeupWaiters() {
  scheduler_->MakeAllRunnable(waiters_);
  // waiters_.clear();
}

// The current thread is now a waiter for this sync object. Check for deadlocks.
void Sync::DetectDeadlock() {
  ThreadHandle handle = g_current_thread;
  if (handle == scheduler_->GetMainThread()) {
    HandleBlockedMainThread();
  }
  std::deque<ThreadHandle> path;
  for (ThreadHandle owner : owners()) {
    // If any owner has a dependency chain leading back to us we have a
    // deadlock.
    if (sync_tracker_->FindDependencyPath(owner, handle, path)) {
      scheduler_->HandleDeadlock(path);
    }
  }
}

void Sync::HandleNestedWait() {
  if (is_verbose) {
    auto stacktrace = std::make_unique<StackTrace>();

    const auto& original_stacktrace = owner_backtraces_[g_current_thread];

    std::cout << absl::StrFormat("Nested wait for sync primitive %p\n", this);
    std::cout << "\nOriginal ownership acquired:\n";
    original_stacktrace->Print();
    std::cout << "\nTried to wait again on the same object here:\n";
    stacktrace->Print();
  }
  abort();
}

void Sync::HandleBlockedMainThread() {
  std::cout << absl::StrFormat(
      "\nMain thread %s blocked\n",
      scheduler_->DescribeThreadHandle(g_current_thread));
  auto stacktrace = std::make_unique<StackTrace>();
  stacktrace->Print();
  Sync *current = this;
  while (current && !current->owners().empty()) {
    // Only consider first owner since we only need one example dependency path
    ThreadHandle owner = *current->owners().begin();
    Sync *blocking_object = sync_tracker_->GetObjectWithWaiter(owner);
    std::cout << absl::StrFormat(
        "\nBlocked by thread %s (IsRunnable %d) on object %p\n",
        scheduler_->DescribeThreadHandle(owner), scheduler_->IsRunnable(owner),
        blocking_object);
    scheduler_->PrintBacktrace(owner);
    std::cout << "\nBacktrace where ownership was acquired\n";
    auto it = owner_backtraces_.find(owner);
    if (it != owner_backtraces_.end()) {
      it->second->Print();
    }
    current = blocking_object;
  }
  abort();
}
