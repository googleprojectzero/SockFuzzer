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

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <fuzzer/FuzzedDataProvider.h>

#include <deque>
#include <set>
#include <unordered_set>

#include "absl/container/flat_hash_set.h"
#include "executor/executor.h"

class Scheduler : public Executor::CallbackInterface {
 public:
  ~Scheduler() override = default;

  // External scheduler support
  // TODO(nedwill): remove these
  virtual ThreadHandle CreateThread(std::function<void()> target,
                                    bool runnable) = 0;
  virtual ThreadHandle ChooseThread(bool can_choose_existing) = 0;

  // Yielding/blocking
  virtual void Yield() = 0;
  virtual void Block() = 0;
  virtual void SwitchTo(ThreadHandle handle) = 0;

  // Scheduler state
  virtual bool SetInterruptsEnabled(bool enable) = 0;
  virtual bool GetInterruptsEnabled() = 0;

  // Thread state
  virtual void MakeRunnable(ThreadHandle id) = 0;
  virtual void MakeNotRunnable(ThreadHandle id) = 0;
  virtual void MakeAllRunnable(
      const absl::flat_hash_set<ThreadHandle> &runnable) = 0;
  virtual bool IsRunnable(ThreadHandle handle) = 0;
  virtual void CleanupDeadThreads() = 0;

  // Executor callbacks
  void ThreadDestroyed(ThreadHandle handle) override = 0;

  // Task processing
  virtual bool RunUntilEmpty() = 0;

  // Util
  virtual void SetRandSeed(uint32_t rand_seed) = 0;
  virtual void SetThreadChoices(FuzzedDataProvider *thread_choices) = 0;
  virtual ThreadHandle GetMainThread() = 0;
  virtual ThreadHandle GetCurrentThreadHandle() = 0;
  virtual const std::set<ThreadHandle> &GetLiveThreads() = 0;
  virtual size_t NumLiveThreads() = 0;
  virtual size_t NumRunnableThreads() = 0;
  virtual void PrintThreadState(ThreadHandle handle) = 0;
  virtual void PrintBacktrace(ThreadHandle handle) = 0;
  virtual void HandleDeadlock(const std::deque<ThreadHandle> &handles) = 0;
  virtual void SetThreadName(ThreadHandle handle, const std::string &name) = 0;
  virtual std::string DescribeThreadHandle(ThreadHandle) = 0;

  // Benchmarking
  virtual void ResetBytesNeeded() = 0;
  virtual size_t BytesNeeded() = 0;
  virtual size_t RandomDataRemaining() = 0;

  class CallbackInterface {
   public:
    virtual ~CallbackInterface() = default;
    virtual void ThreadWillBlock() = 0;
    virtual void ThreadResumed() = 0;
    virtual void ThreadDestroyed(ThreadHandle) = 0;
    virtual std::string DescribeThreadHandle(ThreadHandle) = 0;
    virtual void ReportDeadlock(const std::deque<ThreadHandle> &handles) = 0;
  };
};

#endif /* SCHEDULER_H_ */
