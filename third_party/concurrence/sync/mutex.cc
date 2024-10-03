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

#include "mutex.h"

#include <stdlib.h>

#include "third_party/concurrence/backtrace/backtrace.h"
#include "third_party/concurrence/executor/executor.h"
#include "absl/container/flat_hash_map.h"
#include "absl/hash/hash.h"
#include "third_party/concurrence/scheduler/scheduler.h"
#include "third_party/concurrence/sync/sync.h"

extern bool is_verbose;

VirtualMutex::VirtualMutex(SyncTracker *sync_tracker)
    : Sync(sync_tracker), owner_(0) {}

VirtualMutex::~VirtualMutex() = default;

void VirtualMutex::Lock() {
  while (owner_) {
    AddWaiter();
    // printf("VirtualMutex::Lock: blocking; have owner at &owner_ %p for this %p\n", &owner_, this);
    // printf("VirtualMutex::Lock: waiters size now %zu for this %p\n", waiters().size(), this);
    scheduler()->Block();
    // printf("VirtualMutex::Lock: woke up, going to check &owner_ %p for this %p\n", &owner_, this);
  }
  RemoveWaiter();

  // printf("VirtualMutex::Lock(%p) setting handle %lx\n", this, handle);
  owner_ = g_current_thread;

  if (is_verbose) {
    owner_backtraces()[owner_] = std::make_unique<StackTrace>();
  }
}

bool VirtualMutex::TryLock() {
  // Trying to locking something we already hold
  if (Held()) {
    HandleNestedWait();
  }
  if (owner_) {
    // printf("VirtualMutex::TryLock(%p) failed to acquire the lock\n", this);
    return false;
  }

  owner_ = g_current_thread;

  if (is_verbose) {
    owner_backtraces()[owner_] = std::make_unique<StackTrace>();
  }

  return true;
}

void VirtualMutex::Unlock() {
  AssertHeld();
  if (is_verbose) {
    owner_backtraces().erase(owner_);
  }
  owner_ = 0;
  WakeupWaiters();
}

bool VirtualMutex::Held() const {
  return owner_ == g_current_thread;
}

void VirtualMutex::AssertHeld() const {
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
