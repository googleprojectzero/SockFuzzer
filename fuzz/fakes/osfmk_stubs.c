/*
 * Copyright 2021 Google LLC
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

#include <kern/assert.h>
#include <kern/counter.h>
#include <kern/locks.h>
#include <vm/vm_kern.h>
#include <stdbool.h>

void kheap_startup_init() {
  assert(false);
}

void zone_view_startup_init() {
  assert(false);
}

void lck_attr_startup_init(struct lck_attr_startup_spec *sp) { assert(false); }

lck_attr_t* lck_attr_alloc_init() { return (void*)1; }

void lck_attr_free() {}

void lck_attr_setdebug() {}

OS_OVERLOADABLE
uint64_t counter_load(struct generic_counter_t *counter) {
  assert(false);
}

int32_t sysctl_get_bound_cpuid(void) {
  assert(false);
}

kern_return_t sysctl_thread_bind_cpuid(int32_t cpuid) {
  assert(false);
}

kern_return_t
kernel_memory_allocate(
	vm_map_t        map,
	vm_offset_t     *addrp,
	vm_size_t       size,
	vm_offset_t     mask,
	kma_flags_t     flags,
	vm_tag_t        tag) {
  assert(false);
}

void lck_mtx_startup_init(struct lck_mtx_startup_spec *spec) {
  assert(false);
}
