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

#ifndef SYNC_TRACKER_H_
#define SYNC_TRACKER_H_

#include <deque>
#include <memory>

#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"

#include "executor/executor.h"

class Scheduler;
class Sync;
class VirtualMutex;
class VirtualRwLock;

class SyncTracker {
 public:
  explicit SyncTracker(Scheduler *scheduler);
  ~SyncTracker();

  VirtualMutex *AllocateMutex();
  void FreeMutex(VirtualMutex *mutex);

  VirtualRwLock *AllocateRwLock();
  void FreeRwLock(VirtualRwLock *rwlock);

  // Assistance routines to help debug blocked threads
  absl::flat_hash_set<Sync *> Owned(ThreadHandle handle);
  Sync *GetObjectWithWaiter(ThreadHandle handle);

  bool FindDependencyPath(ThreadHandle source, ThreadHandle destination,
                          std::deque<ThreadHandle> &path);

  Scheduler *scheduler() { return scheduler_; };

  void BeginSession();
  void ReportSession();
  void FreeSession();

 private:
  Scheduler *scheduler_;
  absl::flat_hash_map<Sync *, std::unique_ptr<Sync>> all_primitives_;
#ifdef NDEBUG
  absl::flat_hash_set<Sync *> session_tracked_primitives_;
#endif
};

#endif
