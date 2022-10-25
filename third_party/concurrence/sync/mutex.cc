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

#include "mutex.h"

#include <stdlib.h>

#include "backtrace/backtrace.h"
#include "executor/executor.h"
#include "absl/container/flat_hash_map.h"
#include "absl/hash/hash.h"
#include "scheduler/scheduler.h"
#include "sync/sync.h"

VirtualMutex::VirtualMutex(SyncTracker *sync_tracker)
    : Sync(sync_tracker), owner_(0) {}

VirtualMutex::~VirtualMutex() = default;

void VirtualMutex::Lock() {
  while (owner_) {
    AddWaiter();
    scheduler()->Block();
  }

  owner_ = g_current_thread;

  if (enable_debug_checks_) {
    GetBacktrace(owner_backtraces()[owner_]);
  }
}

bool VirtualMutex::TryLock() {
  // Trying to locking something we already hold
  if (Held()) {
    HandleNestedWait();
  }
  if (owner_) {
    return false;
  }

  owner_ = g_current_thread;

  if (enable_debug_checks_) {
    GetBacktrace(owner_backtraces()[owner_]);
  }

  return true;
}

void VirtualMutex::Unlock() {
  AssertHeld();
  if (enable_debug_checks_) {
    owner_backtraces().erase(owner_);
  }
  owner_ = 0;
  ClearAndUnblockWaiters();
}

bool VirtualMutex::Held() {
  return owner_ == g_current_thread;
}

void VirtualMutex::AssertHeld() {
  if (!Held()) {
    abort();
  }
}

bool VirtualMutex::IsOwned() {
  return owner_ != 0;
}

bool VirtualMutex::IsOwnedBy(ThreadHandle handle) {
  return owner_ == handle;
}

const absl::flat_hash_set<ThreadHandle> &VirtualMutex::owners() {
  if (owner_) {
    owners_ = {owner_};
  } else {
    owners_ = {};
  }
  return owners_;
}
