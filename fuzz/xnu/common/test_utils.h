/*
 * Copyright 2024 Google LLC
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

#ifndef FUZZ_XNU_COMMON_TEST_UTILS_H_
#define FUZZ_XNU_COMMON_TEST_UTILS_H_

#include <stdbool.h>

#define MAX_ASSERTION_FAILURES 10

typedef struct {
  int num_assertions;
  int num_failures;
  char failure_messages[MAX_ASSERTION_FAILURES][256];
} __attribute__((aligned(128))) TestResult;

void xnu_assert_helper(TestResult* result, bool condition, const char* file,
                       int line, const char* message);

#define XNU_ASSERT(result, condition, message) \
  xnu_assert_helper(result, condition, __FILE__, __LINE__, message)

#endif  // FUZZ_XNU_COMMON_TEST_UTILS_H_