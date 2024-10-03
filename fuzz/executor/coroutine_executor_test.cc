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

#include "fuzz/executor/coroutine_executor.h"

#include <memory>

#include "gtest/gtest.h"
#include "third_party/concurrence/executor/executor_test_template.h"
#include "third_party/concurrence/scheduler/fuzzed_scheduler.h"
#include "third_party/concurrence/scheduler/fuzzed_scheduler_test_template.h"

class Scheduler;

bool is_verbose = false;

Executor* g_executor;

Scheduler* g_scheduler;

template <>
Executor* CreateExecutor<CoroutineExecutor>() {
  return new CoroutineExecutor;
}

typedef ::testing::Types<CoroutineExecutor> ExecutorImplementation;

// To create a downstream executor, replicate this line with your types
INSTANTIATE_TYPED_TEST_SUITE_P(CoroutineExecutorTests, ExecutorTest,
                               ExecutorImplementation);

template <>
Scheduler* CreateScheduler<CoroutineExecutor>() {
  return new FuzzedScheduler(new CoroutineExecutor,
                             new EmptySchedulerCallbacks);
}

typedef ::testing::Types<CoroutineExecutor> SchedulerImplementation;

// To create a downstream executor, replicate this line with your types
INSTANTIATE_TYPED_TEST_SUITE_P(CoroutineSchedulerTest, SchedulerTest,
                               SchedulerImplementation);
