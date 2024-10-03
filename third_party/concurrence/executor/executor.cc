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

#include "executor.h"

#include "third_party/concurrence/backtrace/backtrace.h"

ThreadHandle g_current_thread;

Executor::~Executor() = default;

void Executor::SetBacktrace(ThreadHandle handle) {
  backtraces_[handle] = std::make_unique<StackTrace>();
}

void Executor::PrintBacktrace(ThreadHandle handle) {
  if (!backtraces_.count(handle)) {
    return;
  }

  backtraces_[handle]->Print();
}

void Executor::DeleteBacktrace(ThreadHandle handle) {
  backtraces_.erase(handle);
}
