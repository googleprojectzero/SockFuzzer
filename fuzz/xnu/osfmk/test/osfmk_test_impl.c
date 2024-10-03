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

#include "fuzz/xnu/osfmk/test/osfmk_test_impl.h"

#include <kern/kalloc.h>
#include <mach/mach_types.h>

#include "fuzz/host/hypercall/hypercall.h"
#include "fuzz/xnu/common/test_utils.h"

void test_kalloc_type_impl(TestResult* result) {
  // Test kalloc_type(int, Z_WAITOK)
  int* allocated = kalloc_type(int, Z_WAITOK);
  XNU_ASSERT(result, allocated != NULL, "kalloc_type returned NULL");

  if (allocated != NULL) {
    // Perform some operations with the allocated memory
    *allocated = 42;
    XNU_ASSERT(result, *allocated == 42,
               "Unexpected value in allocated memory");

    // Free the allocated memory
    kfree_type(int, allocated);
  }

  if (is_verbose) {
    printf("test_kalloc_type_impl completed with %d assertions, %d failures\n",
           result->num_assertions, result->num_failures);
  }
}
