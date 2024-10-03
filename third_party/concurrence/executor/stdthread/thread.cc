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

#include "thread.h"

#include <pthread.h>
#include <unistd.h>
#include <utility>

#include "absl/log/check.h"
#include "absl/synchronization/mutex.h"
#include "third_party/concurrence/executor/executor.h"
#include "thread_executor.h"

void CooperativeThread::Start() {
  tid_ = gettid();
  // wait to be scheduled
  execution_mutex_->LockWhen(absl::Condition(&running_));

  target_();

  ExitThread();
}

// Execution mutex held by this thread
void CooperativeThread::ExitThread() {
  execution_mutex_->AssertHeld();
  thread_executor_->NotifyDestroyed(reinterpret_cast<ThreadHandle>(this));
  joinable_ = true;
  execution_mutex_->Unlock();
  pthread_exit(nullptr);
}

void CooperativeThread::Wait() {
  execution_mutex_->AssertHeld();
  running_ = false;
  execution_mutex_->Await(absl::Condition(&running_));
  if (terminate_) {
    ExitThread();
  }
}

void CooperativeThread::Signal() {
  CHECK_NE(gettid(), tid_);
  running_ = true;
}

std::thread::id CooperativeThread::internal_id() {
  return thread_->get_id();
}

CooperativeThread::CooperativeThread(ThreadExecutor* thread_executor,
                                     std::function<void()> target)
    : thread_executor_(thread_executor),
      execution_mutex_(thread_executor->mutex()),
      target_(std::move(target)),
      tid_(-1) {
  thread_ = std::make_unique<std::thread>([this] { Start(); });
}

CooperativeThread::~CooperativeThread() {
  // Threads are destroyed from the main thread so shouldn't destroy themselves.
  CHECK_NE(gettid(), tid_);

  if (!joinable_) {
    // Notify thread must terminate then wake it up so it can pthread_exit
    terminate_ = true;
    Signal();
    execution_mutex_->Await(absl::Condition(&joinable_));
  }

  thread_->join();
}

void CooperativeThread::SetName(const std::string& name) {
  pthread_t handle = thread_->native_handle();
  pthread_setname_np(handle, name.c_str());
}
