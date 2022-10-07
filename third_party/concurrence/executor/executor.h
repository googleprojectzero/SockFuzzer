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

#ifndef EXECUTOR_H_
#define EXECUTOR_H_

#include <stdint.h>
#include <functional>
#include <string>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/hash/hash.h"

// Use pointer type as we use pointers the the corresponding C++ objects
// as handles
typedef uintptr_t ThreadHandle;

// Implementations must not use 1 for child thread handles
// Thread handle 0 is disallowed because it implies null thread
const ThreadHandle MAIN_THREAD_HANDLE = 1;

extern ThreadHandle g_current_thread;

class Executor {
 public:
  virtual ~Executor();

  virtual ThreadHandle CreateThread(std::function<void()> target) = 0;
  virtual void DeleteThread(ThreadHandle handle) = 0;

  virtual void SwitchToMainThread() = 0;
  virtual void SwitchTo(ThreadHandle handle) = 0;

  virtual ThreadHandle GetCurrentThreadHandle() = 0;
  virtual ThreadHandle GetMainThreadHandle() = 0;

  virtual void SetThreadName(ThreadHandle handle, const std::string &name) = 0;
  virtual std::string DescribeThreadHandle(ThreadHandle handle) = 0;

  void SetBacktrace(ThreadHandle handle);
  void PrintBacktrace(ThreadHandle handle);
  void DeleteBacktrace(ThreadHandle handle);

  class CallbackInterface {
   public:
    virtual ~CallbackInterface() = default;
    virtual void ThreadDestroyed(ThreadHandle) = 0;
  };

  void set_callbacks(Executor::CallbackInterface *callbacks) {
    callbacks_ = callbacks;
  }

  Executor::CallbackInterface *callbacks() { return callbacks_; }

 private:
  Executor::CallbackInterface *callbacks_{};
  absl::flat_hash_map<ThreadHandle, std::vector<void *>> backtraces_;
};

#endif /* EXECUTOR_H_ */
