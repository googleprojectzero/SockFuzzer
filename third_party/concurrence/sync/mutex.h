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

#ifndef VIRTUAL_MUTEX_H_
#define VIRTUAL_MUTEX_H_

#include <set>

#include "absl/container/flat_hash_set.h"
#include "third_party/concurrence/scheduler/scheduler.h"
#include "sync.h"
#include "third_party/concurrence/executor/executor.h"

class SyncTracker;

class VirtualMutex : public Sync {
 public:
  explicit VirtualMutex(SyncTracker *sync_tracker);
  ~VirtualMutex() override;
  VirtualMutex(const VirtualMutex &) = delete;
  VirtualMutex(VirtualMutex &&) = delete;
  VirtualMutex &operator=(const VirtualMutex &) = delete;
  VirtualMutex &operator=(VirtualMutex &&) = delete;

  void Lock();
  bool TryLock();
  void Unlock();

  bool Held() const;
  void AssertHeld() const;

  bool IsOwned() override;
  bool IsOwnedBy(ThreadHandle handle) override;
  const absl::flat_hash_set<ThreadHandle> &owners() override;

 private:
  // owners_ is only populated when requested.
  absl::flat_hash_set<ThreadHandle> owners_;
  ThreadHandle owner_;
};

#endif /* VIRTUAL_MUTEX_H_ */
