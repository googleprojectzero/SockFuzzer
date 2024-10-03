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

#ifndef SCHEDULER_IMPL_H_
#define SCHEDULER_IMPL_H_

#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <deque>
#include <list>
#include <memory>
#include <mutex>
#include <set>
#include <unordered_map>
#include <functional>
#include <string>
#include <vector>

#include "third_party/concurrence/executor/executor.h"
#include "scheduler.h"
#include "absl/container/flat_hash_set.h"

class FuzzedDataProvider;

class FuzzedScheduler : public Scheduler {
 public:
  FuzzedScheduler(Executor *executor,
                  Scheduler::CallbackInterface *callback_interface);
  ~FuzzedScheduler() override = default;
  FuzzedScheduler(const FuzzedScheduler &) = delete;
  FuzzedScheduler &operator=(const FuzzedScheduler &) = delete;
  FuzzedScheduler(const FuzzedScheduler &&) = delete;
  FuzzedScheduler &operator=(FuzzedScheduler &&) = delete;

  // External scheduler support
  ThreadHandle CreateThread(std::function<void()> target,
                            bool runnable) override;
  ThreadHandle ChooseThread(bool can_choose_existing) override;
  ThreadHandle GetRandomRunnableHandle(bool can_choose_existing);

  // Yielding/blocking
  void Yield() override;
  void Block() override;
  void SwitchTo(ThreadHandle handle) override;

  // Scheduler state
  bool SetInterruptsEnabled(bool enable) override;
  bool GetInterruptsEnabled() override;

  // Thread state
  void MakeRunnable(ThreadHandle handle) override;
  void MakeNotRunnable(ThreadHandle handle) override;
  void MakeAllRunnable(
      const std::vector<ThreadHandle> &runnables) override;
  bool IsRunnable(ThreadHandle handle) override;
  void CleanupDeadThreads() override;

  // Executor callbacks
  void ThreadDestroyed(ThreadHandle handle) override;

  // Task processing
  bool RunUntilEmpty() override;

  // Util
  void SetRandSeed(uint32_t rand_seed) override;
  void SetThreadChoices(FuzzedDataProvider* thread_choices) override;
  ThreadHandle GetMainThread() override;
  ThreadHandle GetCurrentThreadHandle() override;
  const std::set<ThreadHandle> &GetLiveThreads() override { return live_set_; }
  size_t NumLiveThreads() override;
  size_t NumRunnableThreads() override;
  std::string DescribeThreadHandle(ThreadHandle handle) override;
  void SetThreadName(ThreadHandle handle, const std::string &name) override;
  void PrintThreadState(ThreadHandle handle) override;
  void PrintBacktrace(ThreadHandle handle) override;
  void HandleDeadlock(const std::deque<ThreadHandle> &handles) override;

  // Benchmarking
  void ResetBytesNeeded() override;
  size_t BytesNeeded() override;
  size_t RandomDataRemaining() override;

 private:
  std::unique_ptr<Executor> executor_;

  Scheduler::CallbackInterface *callbacks_;

  FuzzedDataProvider *thread_choices_;

  // Track all runnable threads so we don't double-enqueue
  std::vector<ThreadHandle> runnable_;
  // Set of threads that are not deleted or pending deletion
  std::set<ThreadHandle> live_set_;
  std::set<ThreadHandle> pending_deletion_;
  bool interrupts_enabled_;
  size_t bytes_needed_;
};

#endif /* SCHEDULER_IMPL_H_ */
