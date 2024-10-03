/*
 * Copyright 2024 Google LLC
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>

// Must come after system includes
#include <cmocka.h>

#include "fuzz/host/hypercall/hypercall.h"
#include "fuzz/xnu/osfmk/test/osfmk_test_impl.h"

static void test_kalloc_type(void **state) {
  (void)state;  // Unused parameter
  TestResult result = {0};
  test_kalloc_type_impl(&result);

  // Use cmocka assertions to report the test results
  assert_int_equal(result.num_failures, 0);

  // If there were failures, print them and fail the test
  if (result.num_failures > 0) {
    for (int i = 0; i < result.num_failures; i++) {
      print_error("%s\n", result.failure_messages[i]);
    }
    fail();
  }
}

static int global_setup(void **state) {
  (void)state;  // Unused parameter
  is_verbose = true;
  GetHypercallInterface()->Initialize();
  return 0;
}

static int global_teardown(void **state) {
    (void)state;  // Unused parameter
    // Add any necessary cleanup here if possible in the future
    return 0;
}

int main(void) {
    static const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_kalloc_type),
        // Add more tests here as needed
    };

    return cmocka_run_group_tests(tests, global_setup, global_teardown);
}