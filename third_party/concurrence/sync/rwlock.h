/*
 * Copyright 2024 Google LLC
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

#ifndef VIRTUAL_RWLOCK_H_
#define VIRTUAL_RWLOCK_H_

#include <cstddef>
#include <unordered_map>
#include <unordered_set>

#include "third_party/concurrence/scheduler/scheduler.h"
#include "absl/container/flat_hash_set.h"
#include "third_party/concurrence/executor/executor.h"
#include "third_party/concurrence/sync/mutex.h"
#include "third_party/concurrence/sync/sync.h"

class SyncTracker;

class VirtualRwLock : public Sync {
 public:
  explicit VirtualRwLock(SyncTracker *sync_tracker);
  ~VirtualRwLock() override;
  VirtualRwLock(const VirtualRwLock &) = delete;
  VirtualRwLock(VirtualRwLock &&) = delete;
  VirtualRwLock &operator=(const VirtualRwLock &) = delete;
  VirtualRwLock &operator=(VirtualRwLock &&) = delete;

  bool TryLockExclusive();
  void LockExclusive();
  void UnlockExclusive();

  bool TryLockShared();
  void LockShared();
  void UnlockShared();

  void Unlock();

  bool IsShared();
  void ExclusiveToShared();
  bool SharedToExclusive();

  bool IsOwned() override;
  bool IsOwnedBy(ThreadHandle handle) override;
  const absl::flat_hash_set<ThreadHandle> &owners() override {
    return owners_;
  };

  void AddOwner();
  void RemoveOwner();

 private:
  absl::flat_hash_set<ThreadHandle> owners_;
  // Used to lock access to owners (readers)
  VirtualMutex mutex_;
};

#endif /* VIRTUAL_RWLOCK_H_ */
