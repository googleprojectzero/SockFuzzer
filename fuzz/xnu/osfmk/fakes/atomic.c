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

#include "fuzz/xnu/osfmk/fakes/atomic.h"

#include "fuzz/host/hypercall/hypercall.h"

uint64_t atomic_load_explicit_wrapper_32(uint32_t *ptr, memory_order order) {
  uint64_t value = *ptr;
  GetHypercallInterface()->Yield();
  return value;
}

uint64_t atomic_load_explicit_wrapper_64(uint64_t *ptr, memory_order order) {
  uint64_t value = *ptr;
  GetHypercallInterface()->Yield();
  return value;
}

int atomic_compare_exchange_weak_explicit_wrapper_32(uint32_t *p,
                                                     uint32_t *expected,
                                                     uint32_t desired,
                                                     memory_order success,
                                                     memory_order failure) {
  GetHypercallInterface()->Yield();

  if (*p == *expected) {
    *p = desired;
    return 1;
  }

  *expected = *p;
  return 0;
                                                     }

int atomic_compare_exchange_weak_explicit_wrapper_64(uint64_t *p,
                                                     uint64_t *expected,
                                                     uint64_t desired,
                                                     memory_order success,
                                                     memory_order failure) {
  GetHypercallInterface()->Yield();

  if (*p == *expected) {
    *p = desired;
    return 1;
  }

  *expected = *p;
  return 0;
}

void atomic_store_explicit_wrapper_32(uint32_t *ptr, uint32_t value, memory_order order) {
  *ptr = value;
  GetHypercallInterface()->Yield();
}

void atomic_store_explicit_wrapper_64(uint64_t *ptr, void* value, memory_order order) {
  *ptr = (uint64_t)value;  // Cast pointer to integer
  GetHypercallInterface()->Yield();
}
