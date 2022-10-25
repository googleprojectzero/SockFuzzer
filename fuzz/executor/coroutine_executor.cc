// Copyright 2022 Google LLC
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

// #define _GNU_SOURCE
#include "fuzz/executor/coroutine_executor.h"

#include <functional>
#include <string>
#include <utility>

#include "absl/meta/type_traits.h"

#if __has_feature(address_sanitizer)
#include <sanitizer/common_interface_defs.h>
#endif

const int KERNEL_STACK_SIZE = 4096 * 16;

#include "third_party/libco/libco.h"
#include <stdint.h>
#include <stdlib.h>
#include <sys/mman.h>

static CoroutineExecutor *g_coroutine_executor;

static void ThreadStart() {
  g_coroutine_executor->CallPendingFunctionThenSwap();
}

CoroutineExecutor::CoroutineExecutor() : main_thread_(co_active()) {
  g_current_thread = reinterpret_cast<ThreadHandle>(co_active());
  g_coroutine_executor = this;
}

CoroutineExecutor::~CoroutineExecutor() { g_coroutine_executor = nullptr; }

ThreadHandle CoroutineExecutor::CreateThread(std::function<void()> target) {
  void *mapping =
      mmap(nullptr, 0x1000 + KERNEL_STACK_SIZE, PROT_READ | PROT_WRITE,
           MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (mapping == MAP_FAILED) {
    abort();
  }
  if (mprotect(mapping, 0x1000, PROT_NONE)) {
    abort();
  }
  cothread_t thread = co_derive(static_cast<uint8_t *>(mapping) + 0x1000,
                                KERNEL_STACK_SIZE, ThreadStart);
  pending_functions_[thread] = std::move(target);
  return reinterpret_cast<ThreadHandle>(thread);
}

void CoroutineExecutor::CallPendingFunctionThenSwap() {
#if __has_feature(address_sanitizer)
  __sanitizer_finish_switch_fiber(nullptr, nullptr, nullptr);
#endif
  cothread_t active = co_active();
  g_current_thread = reinterpret_cast<ThreadHandle>(active);
  if (active == main_thread_) {
    abort();
  }

  auto it = pending_functions_.find(active);
  if (it == pending_functions_.end()) {
    abort();
  }

  auto pending_function = std::move(it->second);
  pending_functions_.erase(it);

  pending_function();

  // TODO(nedwill): only notify destroyed once the thread actually gets
  // destroyed explicitly
  callbacks()->ThreadDestroyed(reinterpret_cast<ThreadHandle>(active));
  SwitchToMainThread();
}

void CoroutineExecutor::DeleteThread(ThreadHandle handle) {
  // co_delete(cothread);
  DeleteBacktrace(handle);
  munmap(reinterpret_cast<uint8_t *>(handle - 0x1000),
         KERNEL_STACK_SIZE + 0x1000);
}

void CoroutineExecutor::SwitchToMainThread() {
  SwitchTo(reinterpret_cast<ThreadHandle>(main_thread_));
}

void CoroutineExecutor::SwitchTo(ThreadHandle handle) {
  auto *cothread = reinterpret_cast<cothread_t>(handle);

  if (co_active() == cothread) {
    // Already on requested thread
    return;
  }

#if __has_feature(address_sanitizer)
  // TODO(nedwill): track first argument to support stack use after return
  // detection
  __sanitizer_start_switch_fiber(nullptr, cothread, KERNEL_STACK_SIZE);
#endif
  co_switch(cothread);
  g_current_thread = reinterpret_cast<ThreadHandle>(co_active());
#if __has_feature(address_sanitizer)
  __sanitizer_finish_switch_fiber(nullptr, nullptr, nullptr);
#endif
}

ThreadHandle CoroutineExecutor::GetCurrentThreadHandle() {
  // For performance, prefer to access g_current_thread directly.
  // This global is set in SwitchTo.
  return g_current_thread;
}

ThreadHandle CoroutineExecutor::GetMainThreadHandle() {
  return reinterpret_cast<ThreadHandle>(main_thread_);
}

// TODO(nedwill): support naming fibers
void CoroutineExecutor::SetThreadName(ThreadHandle handle,
                                      const std::string &name) {}

std::string CoroutineExecutor::DescribeThreadHandle(ThreadHandle handle) {
  return {};
}
