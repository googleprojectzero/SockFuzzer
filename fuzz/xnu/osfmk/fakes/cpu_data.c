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

#include "BUILD/obj/EXPORT_HDRS/osfmk/i386/cpu_data.h"

#include <kern/processor.h>
#include <kern/task.h>
#include <mach/machine.h>

#include "fuzz/host/hypercall/hypercall.h"

static struct processor processor;

static cpu_data_t cpu_data = {.cpu_processor = &processor};

cpu_data_t *cpu_data_ptr[64] = {&cpu_data};

void machine_set_current_thread(thread_t thread) {
  GetHypercallInterface()->SetCurrentThreadT(thread);
}

extern thread_t bootstrap_thread;

#undef current_thread
// Make visible for BSD half
thread_t current_thread() {
  return GetHypercallInterface()->GetCurrentThreadT();
}

processor_t current_processor(void) {
  return cpu_data.cpu_processor;
}

cpu_threadtype_t cpu_threadtype() {
  return CPU_THREADTYPE_NONE;
}
