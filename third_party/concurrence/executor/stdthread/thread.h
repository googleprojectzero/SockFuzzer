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

#ifndef COOPERATIVE_THREAD_H_
#define COOPERATIVE_THREAD_H_

#include <sys/types.h>
#include <functional>
#include <memory>
#include <string>
#include <thread>

#include "absl/base/thread_annotations.h"

class ThreadExecutor;

namespace absl {
class Mutex;
}  // namespace absl

class ABSL_LOCKABLE CooperativeThread {
 public:
  CooperativeThread(ThreadExecutor *thread_executor,
                    std::function<void()> target);
  ~CooperativeThread();

  // From another thread, begin running this one
  void Start();

  // In this thread, wait to be signalled
  void Wait() ABSL_ASSERT_EXCLUSIVE_LOCK(*execution_mutex_);

  // Inform this thread is ready to run from another thread
  void Signal();

  void ExitThread() ABSL_UNLOCK_FUNCTION(*execution_mutex_);

  void SetName(const std::string &name);

  std::thread::id internal_id();
  pid_t tid() const { return tid_; }

 private:
  ThreadExecutor *thread_executor_;
  absl::Mutex *execution_mutex_;
  bool running_ = false;
  bool joinable_ = false;
  bool terminate_ ABSL_GUARDED_BY(*execution_mutex_) = false;
  std::function<void()> target_;
  std::unique_ptr<std::thread> thread_;
  // The number shown in GDB is [tid_]
  pid_t tid_;
};

#endif
