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

#ifndef COROUTINE_EXECUTOR_H_
#define COROUTINE_EXECUTOR_H_

#include <functional>
#include <string>

#include "absl/container/flat_hash_map.h"
#include "executor/executor.h"
#include "third_party/libco/libco.h"

class CoroutineExecutor : public Executor {
 public:
  explicit CoroutineExecutor();
  ~CoroutineExecutor() override;

  ThreadHandle CreateThread(std::function<void()> target) override;
  void DeleteThread(ThreadHandle handle) override;

  void SwitchToMainThread() override;
  void SwitchTo(ThreadHandle handle) override;

  ThreadHandle GetCurrentThreadHandle() override;
  ThreadHandle GetMainThreadHandle() override;

  void SetThreadName(ThreadHandle handle, const std::string &name) override;

  std::string DescribeThreadHandle(ThreadHandle handle) override;

  void CallPendingFunctionThenSwap();

 private:
  cothread_t main_thread_;

  // Map from cothread_t to target functions
  absl::flat_hash_map<cothread_t, std::function<void()>> pending_functions_;
};

#endif /* COROUTINE_EXECUTOR_H_ */
