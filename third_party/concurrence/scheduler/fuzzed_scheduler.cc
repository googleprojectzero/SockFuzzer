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

#include "fuzzed_scheduler.h"

#include <fuzzer/FuzzedDataProvider.h>
#include <iostream>
#include <memory>
#include <algorithm>
#include <cstdlib>

#include "absl/strings/str_format.h"
#include "third_party/concurrence/executor/executor.h"
#include "third_party/concurrence/scheduler/scheduler.h"

FuzzedScheduler::FuzzedScheduler(
    Executor *executor, Scheduler::CallbackInterface *callback_interface)
    : executor_(executor),
      callbacks_(callback_interface),
      thread_choices_(nullptr),
      interrupts_enabled_(true),
      bytes_needed_(0) {
  SetRandSeed(0);
  executor_->set_callbacks(this);
}

// TODO(nedwill): consider using lock state as part of fuzzer feedback
// Is it typical to run the same code path with different locks? Perhaps
// the state of locks in other threads is important.

ThreadHandle FuzzedScheduler::CreateThread(std::function<void()> target,
                                           bool runnable) {
  ThreadHandle handle = executor_->CreateThread(target);
  // printf("Created thread 0x%zx\n", handle);
  live_set_.insert(handle);
  if (runnable) {
    MakeRunnable(handle);
  }
  return handle;
}

ThreadHandle FuzzedScheduler::GetMainThread() {
  return executor_->GetMainThreadHandle();
}

void FuzzedScheduler::ThreadDestroyed(ThreadHandle handle) {
  live_set_.erase(handle);
  pending_deletion_.insert(handle);
  callbacks_->ThreadDestroyed(handle);
}

void FuzzedScheduler::HandleDeadlock(const std::deque<ThreadHandle> &handles) {
  callbacks_->ReportDeadlock(handles);
}

std::string FuzzedScheduler::DescribeThreadHandle(ThreadHandle handle) {
  std::string host_description = callbacks_->DescribeThreadHandle(handle);

  std::string executor_description = executor_->DescribeThreadHandle(handle);
  if (executor_description.empty()) {
    return host_description;
  }

  return absl::StrFormat("%s/%s", host_description, executor_description);
}

void FuzzedScheduler::SetThreadName(ThreadHandle handle,
                                    const std::string &name) {
  executor_->SetThreadName(handle, name);
}

void FuzzedScheduler::Yield() {
  // Called from child thread

  // Yielding in main thread is a nop
  if (g_current_thread == executor_->GetMainThreadHandle()) {
    // printf("FuzzedScheduler::Yield: in main thread\n");
    return;
  }

  // don't yield if interrupts are enabled
  if (!interrupts_enabled_) {
    // printf("FuzzedScheduler::Yield: interrupts disabled\n");
    return;
  }

  // Don't yield if we will immediately schedule this thread again
  if (runnable_.empty()) {
    // printf("FuzzedScheduler::Yield: nothing available to run\n");
    return;
  }

  MakeRunnable(g_current_thread);
  Block();
}

void FuzzedScheduler::Block() {
  // printf("FuzzedScheduler::Block: blocking in thread %p\n", (void*)handle);
  if (g_current_thread == executor_->GetMainThreadHandle()) {
    std::cout
        << "FuzzedScheduler::Block: blocking main thread is not allowed\n";
    abort();
  }
  // printf("Block removing runnable 0x%lx\n", handle);
  // runnable_set_.erase(handle);
  ThreadHandle main_handle = executor_->GetMainThreadHandle();
  callbacks_->ThreadWillBlock();
  SwitchTo(main_handle);
}

ThreadHandle FuzzedScheduler::GetRandomRunnableHandle(
    bool can_choose_existing) {
  // for speed, default to removing from the end of the runnables_ vector
  size_t idx = runnable_.size() - 1;
  if (idx == 0) {
    // there is only one runnable handle.
    ThreadHandle tid = runnable_.at(0);
    runnable_.erase(runnable_.begin());
    return tid;
  }

  if (thread_choices_) {
    size_t upper_bound = idx;
    if (can_choose_existing) {
      upper_bound++;
    }
    if (thread_choices_->remaining_bytes()) {
      idx = thread_choices_->ConsumeIntegralInRange<size_t>(0, upper_bound);
    } else {
      idx = (static_cast<unsigned int>(std::rand())) % (upper_bound + 1);
    }
    bytes_needed_++;
    if (can_choose_existing && idx >= runnable_.size()) {
      MakeNotRunnable(g_current_thread);
      return g_current_thread;
    }
  }
  ThreadHandle tid = runnable_.at(idx);
  runnable_.erase(runnable_.begin() + idx);
  return tid;
}

void FuzzedScheduler::CleanupDeadThreads() {
  for (const ThreadHandle &handle : pending_deletion_) {
    executor_->DeleteThread(handle);
  }
  pending_deletion_.clear();
}

void FuzzedScheduler::SwitchTo(ThreadHandle handle) {
  if (executor_->GetMainThreadHandle() != handle &&
      !live_set_.contains(handle)) {
    return;
  }

  executor_->SwitchTo(handle);
  callbacks_->ThreadResumed();
}

bool FuzzedScheduler::RunUntilEmpty() {
  // ASSERT in scheduler thread

  if (runnable_.empty()) {
    return false;
  }

  while (!runnable_.empty()) {
    ThreadHandle handle = GetRandomRunnableHandle(false);
    SwitchTo(handle);
  }

  CleanupDeadThreads();
  return true;
}

void FuzzedScheduler::MakeRunnable(ThreadHandle handle) {
  if (handle == executor_->GetMainThreadHandle()) {
    // Main thread is always runnable
    return;
  }

  if (IsRunnable(handle)) {
    // TODO(nwach): seems like this is called twice for every XNU thread...
    return;
  }

#ifndef NDEBUG
  if (!handle) {
    std::cout << "missing handle\n";
    abort();
  }

  if (pending_deletion_.contains(handle)) {
    std::cout << "pending deletion\n";
    abort();
  }
#endif

  runnable_.push_back(handle);
}

void FuzzedScheduler::MakeNotRunnable(ThreadHandle handle) {
  if (handle == executor_->GetMainThreadHandle()) {
    // Main thread is always runnable
    abort();
  }

  auto it = std::find(runnable_.begin(), runnable_.end(), handle);
  if (it == runnable_.end()) {
    // Thread is already not runnable
    // TODO(nwach): how can this happen?
    return;
  }

  runnable_.erase(it);
}

void FuzzedScheduler::MakeAllRunnable(
    const std::vector<ThreadHandle> &runnable) {
  for (const ThreadHandle &handle : runnable) {
    MakeRunnable(handle);
  }
}

bool FuzzedScheduler::IsRunnable(ThreadHandle handle) {
  return std::find(runnable_.begin(), runnable_.end(), handle) !=
         runnable_.end();
}

void FuzzedScheduler::SetRandSeed(uint32_t rand_seed) {
  std::srand(rand_seed);
}

void FuzzedScheduler::SetThreadChoices(FuzzedDataProvider *thread_choices) {
  thread_choices_ = thread_choices;
}

ThreadHandle FuzzedScheduler::GetCurrentThreadHandle() {
  return g_current_thread;
}

bool FuzzedScheduler::SetInterruptsEnabled(bool enabled) {
  bool original_state = interrupts_enabled_;
  interrupts_enabled_ = enabled;
  return original_state;
}

bool FuzzedScheduler::GetInterruptsEnabled() {
  return interrupts_enabled_;
}

size_t FuzzedScheduler::NumLiveThreads() {
  return live_set_.size();
}

size_t FuzzedScheduler::NumRunnableThreads() {
  return runnable_.size();
}

ThreadHandle FuzzedScheduler::ChooseThread(bool can_choose_existing) {
  while (!runnable_.empty()) {
    ThreadHandle handle = GetRandomRunnableHandle(can_choose_existing);
    // Ownership of runnable state goes back to the scheduler
    if (can_choose_existing && handle == g_current_thread) {
      return handle;
    }
    if (pending_deletion_.contains(handle) || !live_set_.contains(handle)) {
      continue;
    }
    return handle;
  }

  if (can_choose_existing) {
    return g_current_thread;
  }

  return 0;
}

void FuzzedScheduler::PrintThreadState(ThreadHandle handle) {
  std::cout << "; ";
  bool printed = false;
  if (IsRunnable(handle)) {
    std::cout << "RUNNABLE";
    printed = true;
  }
  if (live_set_.contains(handle)) {
    if (printed) {
      std::cout << ", ";
    }
    std::cout << "ALIVE";
    printed = true;
  }
  if (pending_deletion_.contains(handle)) {
    if (printed) {
      std::cout << ", ";
    }
    std::cout << "PENDING DELETION";
    printed = true;
  }
  if (printed) {
    std::cout << "\n";
  }
}

void FuzzedScheduler::PrintBacktrace(ThreadHandle handle) {
  executor_->PrintBacktrace(handle);
}

void FuzzedScheduler::ResetBytesNeeded() {
  bytes_needed_ = 0;
}

size_t FuzzedScheduler::BytesNeeded() {
  return bytes_needed_;
}

size_t FuzzedScheduler::RandomDataRemaining() {
  if (!thread_choices_) {
    return 0;
  }
  return thread_choices_->remaining_bytes();
}
