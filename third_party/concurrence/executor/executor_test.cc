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

#include "third_party/concurrence/executor/executor.h"

#include <memory>

#include "third_party/concurrence/executor/executor_test_template.h"
#include "third_party/concurrence/executor/stdthread/thread_executor.h"
#include "gtest/gtest.h"

bool is_verbose = false;

Executor* g_executor;

template <>
Executor* CreateExecutor<ThreadExecutor>() {
  return new ThreadExecutor;
}

typedef ::testing::Types<ThreadExecutor> BuiltinImplementations;

// To create a downstream executor, replicate this line with your types
INSTANTIATE_TYPED_TEST_SUITE_P(BuiltinExecutorTests, ExecutorTest,
                               BuiltinImplementations);
