/*
 * Copyright 2022 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CONCURRENCE_SYNC_H_
#define CONCURRENCE_SYNC_H_

#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"

#include "executor/executor.h"

class Scheduler;
class SyncTracker;

class Sync {
 public:
  explicit Sync(SyncTracker *sync_tracker);
  virtual ~Sync();

  void AddWaiter();
  void ClearAndUnblockWaiters();

  Scheduler *scheduler() { return scheduler_; }

  const std::vector<void *> &construction_backtrace() {
    return construction_backtrace_;
  }

  virtual bool IsOwned() = 0;
  virtual bool IsOwnedBy(ThreadHandle handle) = 0;
  // Some sync primitives have multiple owners
  virtual const absl::flat_hash_set<ThreadHandle> &owners() = 0;

  const absl::flat_hash_set<ThreadHandle> &waiters() { return waiters_; }

  absl::flat_hash_map<ThreadHandle, std::vector<void *>> &owner_backtraces() {
    return owner_backtraces_;
  }

  void HandleNestedWait();
  void HandleBlockedMainThread();

 protected:
  // Logs stacktraces and checks for deadlocks and nested locking
  bool enable_debug_checks_;

 private:
  void DetectDeadlock();

  SyncTracker *sync_tracker_;
  // Scheduler can be referenced through SyncTracker, but we maintain a direct
  // reference for a slight performance boost.
  Scheduler *scheduler_;

  absl::flat_hash_set<ThreadHandle> waiters_;
  std::vector<void *> construction_backtrace_;
  absl::flat_hash_map<ThreadHandle, std::vector<void *>> owner_backtraces_;
};

#endif
