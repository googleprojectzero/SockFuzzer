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

#include "fuzzed_scheduler.h"

#include "fuzzed_scheduler_test_template.h"
#include "gtest/gtest.h"

#include "executor/stdthread/thread_executor.h"

Scheduler* g_scheduler;

template <>
Scheduler* CreateScheduler<ThreadExecutor>() {
  return new FuzzedScheduler(new ThreadExecutor, new EmptySchedulerCallbacks);
}

typedef ::testing::Types<ThreadExecutor> BuiltinImplementations;

// To create a downstream executor, replicate this line with your types
INSTANTIATE_TYPED_TEST_SUITE_P(BuiltinSchedulerTest, SchedulerTest,
                               BuiltinImplementations);
