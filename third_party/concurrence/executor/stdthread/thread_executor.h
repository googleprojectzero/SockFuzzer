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

#ifndef THREAD_EXECUTOR_H_
#define THREAD_EXECUTOR_H_

#include <functional>
#include <memory>
#include <string>

#include "absl/container/flat_hash_map.h"
#include "absl/synchronization/mutex.h"
#include "third_party/concurrence/executor/executor.h"
#include "thread.h"

class CooperativeThread;

class ThreadExecutor : public Executor {
 public:
  ThreadExecutor();
  ~ThreadExecutor() override;
  ThreadExecutor(const ThreadExecutor &) = delete;
  ThreadExecutor(ThreadExecutor &&) = delete;
  ThreadExecutor &operator=(const ThreadExecutor &) = delete;
  ThreadExecutor &operator=(ThreadExecutor &&) = delete;

  ThreadHandle CreateThread(std::function<void()> target) override;
  void DeleteThread(ThreadHandle handle) override;
  void SwitchToMainThread() override;
  void SwitchTo(ThreadHandle handle) override;

  ThreadHandle GetCurrentThreadHandle() override;
  ThreadHandle GetMainThreadHandle() override;

  void SetThreadName(ThreadHandle handle, const std::string &name) override;
  std::string DescribeThreadHandle(ThreadHandle handle) override;

  void NotifyDestroyed(ThreadHandle handle);

  absl::Mutex *mutex() { return &executor_mutex_; }

 private:
  ThreadHandle GetThreadHandle(CooperativeThread *thread);
  void AcquireLock();
  void ReleaseLock();

  // Token that must be held for any thread including scheduler to be runnable
  absl::Mutex executor_mutex_;
  bool main_thread_running_ = true;

  absl::flat_hash_map<ThreadHandle, std::unique_ptr<CooperativeThread>>
      threads_;
};

#endif /* THREAD_EXECUTOR_H_ */
