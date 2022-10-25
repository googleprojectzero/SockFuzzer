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

#include "rwlock.h"

#include <stdlib.h>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/hash/hash.h"
#include "absl/log/log.h"

#include "scheduler/scheduler.h"

class SyncTracker;

void GetBacktrace(std::vector<void *> &stack);

VirtualRwLock::VirtualRwLock(SyncTracker *sync_tracker)
    : Sync(sync_tracker), mutex_(sync_tracker) {}
VirtualRwLock::~VirtualRwLock() = default;

bool VirtualRwLock::TryLockExclusive() {
  if (!owners_.empty()) {
    return false;
  }
  if (mutex_.TryLock()) {
    return true;
  }
  return false;
}

bool VirtualRwLock::TryLockShared() {
  if (!mutex_.TryLock()) {
    return false;
  }

  AddOwner();

  mutex_.Unlock();

  return true;
}

void VirtualRwLock::LockExclusive() {
  while (true) {
    while (!owners_.empty()) {
      AddWaiter();
      scheduler()->Block();
    }

    // mutex_.Lock can block and we might lose the race after someone else
    // took it added a reader
    mutex_.Lock();
    if (owners_.empty()) {
      return;
    }
    mutex_.Unlock();
  }
}

void VirtualRwLock::UnlockExclusive() {
  if (!mutex_.Held()) {
    abort();
  }
  if (!owners_.empty()) {
    abort();
  }
  mutex_.Unlock();
}

void VirtualRwLock::LockShared() {
  mutex_.Lock();
  AddOwner();
  mutex_.Unlock();
}

void VirtualRwLock::UnlockShared() {
  mutex_.Lock();
  RemoveOwner();
  mutex_.Unlock();
}

void VirtualRwLock::ExclusiveToShared() {
  mutex_.AssertHeld();
  if (!owners_.empty()) {
    abort();
  }

  AddOwner();
  mutex_.Unlock();
}

void VirtualRwLock::Unlock() {
  if (!IsShared()) {
    UnlockExclusive();
  } else {
    UnlockShared();
  }
}

bool VirtualRwLock::IsShared() {
  return !owners_.empty();
}

bool VirtualRwLock::SharedToExclusive() {
  RemoveOwner();
  // TODO(nedwill): testing non-trylock version for now
  return TryLockExclusive();
}

void VirtualRwLock::AddOwner() {
  if (IsOwnedBy(g_current_thread)) {
    LOG(ERROR) << "VirtualRwLock is already owned by current thread!\n";
    abort();
  }
  owners_.insert(g_current_thread);
  if (enable_debug_checks_) {
    GetBacktrace(owner_backtraces()[g_current_thread]);
  }
}

void VirtualRwLock::RemoveOwner() {
  size_t erased = owners_.erase(g_current_thread);
  if (!erased) {
    abort();
  }
  if (enable_debug_checks_) {
    owner_backtraces().erase(g_current_thread);
  }
  if (owners_.empty()) {
    ClearAndUnblockWaiters();
  }
}

bool VirtualRwLock::IsOwned() {
  return !owners_.empty();
}

bool VirtualRwLock::IsOwnedBy(ThreadHandle handle) {
  return owners_.count(handle);
}
