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

#include "fuzz/xnu/common/test_utils.h"

#include <stdio.h>

#include "fuzz/host/hypercall/hypercall.h"

void xnu_assert_helper(TestResult* result, bool condition, const char* file,
                       int line, const char* message) {
  result->num_assertions++;
  if (!condition) {
    if (result->num_failures < MAX_ASSERTION_FAILURES) {
      int ret = snprintf(result->failure_messages[result->num_failures],
                         sizeof(result->failure_messages[result->num_failures]),
                         "%s:%d: %s", file, line, message);

      if (ret < 0) {
        // Handle snprintf error
        if (is_verbose) {
          printf("Error formatting assertion message\n");
        }
      } else if ((size_t)ret >=
                 sizeof(result->failure_messages[result->num_failures])) {
        // Handle truncation
        if (is_verbose) {
          printf("Assertion message truncated: %s:%d: %s\n", file, line,
                 message);
        }
      }

      result->num_failures++;
    } else if (result->num_failures == MAX_ASSERTION_FAILURES) {
      // Log that we've hit the maximum number of recorded failures
      if (is_verbose) {
        printf(
            "Maximum number of assertion failures reached. Further failures "
            "will not be recorded.\n");
      }
      result->num_failures++;
    }

    if (is_verbose) {
      printf("Assertion failed at %s:%d: %s\n", file, line, message);
    }
  }
}
