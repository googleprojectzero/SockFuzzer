// Copyright 2024 Google LLC
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

#include "thread_executor.h"

#include <utility>

#include "absl/log/check.h"
#include "absl/strings/str_format.h"
#include "third_party/concurrence/executor/executor.h"
#include "absl/hash/hash.h"
#include "third_party/concurrence/executor/stdthread/thread.h"

ThreadExecutor::ThreadExecutor() {
  g_current_thread = MAIN_THREAD_HANDLE;
  executor_mutex_.Lock();
}

ThreadExecutor::~ThreadExecutor() = default;

ThreadHandle ThreadExecutor::CreateThread(std::function<void()> target) {
  std::unique_ptr<CooperativeThread> thread(
      new CooperativeThread(this, target));

  auto handle = reinterpret_cast<ThreadHandle>(thread.get());
  threads_[handle] = std::move(thread);
  return handle;
}

ThreadHandle ThreadExecutor::GetThreadHandle(CooperativeThread *thread) {
  auto handle = reinterpret_cast<ThreadHandle>(thread);
  auto it = threads_.find(handle);
  if (it == threads_.end()) {
    return MAIN_THREAD_HANDLE;
  }

  return handle;
}

void ThreadExecutor::NotifyDestroyed(ThreadHandle handle) {
  DCHECK(callbacks());
  callbacks()->ThreadDestroyed(handle);
  SwitchToMainThread();
}

void ThreadExecutor::DeleteThread(ThreadHandle handle) {
  DeleteBacktrace(handle);
  threads_.erase(handle);
}

void ThreadExecutor::SwitchToMainThread() {
  SwitchTo(MAIN_THREAD_HANDLE);
}

void ThreadExecutor::SwitchTo(ThreadHandle handle) {
  auto current_handle = GetCurrentThreadHandle();
  if (handle == current_handle) {
    // Already on requested thread
    return;
  }

  // Resume target
  g_current_thread = handle;
  if (handle == MAIN_THREAD_HANDLE) {
    CHECK(!main_thread_running_);
    main_thread_running_ = true;
  } else {
    auto *thread = reinterpret_cast<CooperativeThread *>(handle);
    thread->Signal();
  }

  // Pause current thread
  if (current_handle == MAIN_THREAD_HANDLE) {
    main_thread_running_ = false;
    executor_mutex_.Await(absl::Condition(&main_thread_running_));
  } else {
    auto *current_thread =
        reinterpret_cast<CooperativeThread *>(current_handle);
    current_thread->Wait();
  }
}

ThreadHandle ThreadExecutor::GetCurrentThreadHandle() {
  // For performance, prefer to access g_current_thread directly.
  return g_current_thread;
}

ThreadHandle ThreadExecutor::GetMainThreadHandle() {
  return MAIN_THREAD_HANDLE;
}

std::string ThreadExecutor::DescribeThreadHandle(ThreadHandle handle) {
  if (handle == MAIN_THREAD_HANDLE) {
    return "main_thread";
  }
  auto *thread = reinterpret_cast<CooperativeThread *>(handle);
  return absl::StrFormat("tid%d", thread->tid());
}

void ThreadExecutor::SetThreadName(ThreadHandle handle,
                                   const std::string &name) {
  auto *thread = reinterpret_cast<CooperativeThread *>(handle);
  thread->SetName(name);
}
