// Copyright 2022 Google LLC
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

#include <cstdlib>
#include <deque>

#include "absl/hash/hash.h"
#include "absl/log/log.h"
#include "absl/meta/type_traits.h"
#include "absl/strings/str_format.h"
#include "backtrace/backtrace.h"
#include "scheduler/scheduler.h"
#include "sync/tracker.h"

Sync::Sync(SyncTracker *sync_tracker)
    : sync_tracker_(sync_tracker), scheduler_(sync_tracker->scheduler()) {
  if (enable_debug_checks_) {
    GetBacktrace(construction_backtrace_);
  }
}

Sync::~Sync() = default;

void Sync::AddWaiter() {
  if (IsOwnedBy(g_current_thread)) {
    HandleNestedWait();
  }
  waiters_.insert(g_current_thread);
  if (enable_debug_checks_) {
    DetectDeadlock();
  }
}

void Sync::ClearAndUnblockWaiters() {
  scheduler_->MakeAllRunnable(waiters_);
  waiters_.clear();
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
  if (enable_debug_checks_) {
    std::vector<void *> backtrace;
    GetBacktrace(backtrace);

    std::vector<void *> original_backtrace =
        owner_backtraces_[g_current_thread];

    LOG(INFO) << absl::StrFormat("Nested wait for sync primitive %p\n", this);
    LOG(INFO) << "\nOriginal ownership acquired:\n";
    PrintBacktraceFromStack(original_backtrace);
    LOG(INFO) << "\nTried to wait again on the same object here:\n";
    PrintBacktraceFromStack(backtrace);
  }
  abort();
}

void Sync::HandleBlockedMainThread() {
  LOG(INFO) << absl::StrFormat(
      "\nMain thread %s blocked\n",
      scheduler_->DescribeThreadHandle(g_current_thread));
  std::vector<void *> backtrace;
  GetBacktrace(backtrace);
  PrintBacktraceFromStack(backtrace);
  Sync *current = this;
  while (current && !current->owners().empty()) {
    // Only consider first owner since we only need one example dependency path
    ThreadHandle owner = *current->owners().begin();
    Sync *blocking_object = sync_tracker_->GetObjectWithWaiter(owner);
    LOG(INFO) << absl::StrFormat(
        "\nBlocked by thread %s (IsRunnable %d) on object %p\n",
        scheduler_->DescribeThreadHandle(owner), scheduler_->IsRunnable(owner),
        blocking_object);
    scheduler_->PrintBacktrace(owner);
    LOG(INFO) << "\nBacktrace where ownership was acquired\n";
    auto it = owner_backtraces_.find(owner);
    if (it != owner_backtraces_.end()) {
      PrintBacktraceFromStack(it->second);
    }
    current = blocking_object;
  }
  abort();
}
