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

#include <kern/mpqueue.h>
#include <kern/timer_call.h>
#include <kern/timer_queue.h>
#include <mach/i386/boolean.h>
#include <stdint.h>

#include "fuzz/host/hypercall/hypercall.h"

static mpqueue_head_t timer_queue;

void cpu_init() {
  timer_call_queue_init(&timer_queue);
}

mpqueue_head_t *timer_queue_assign(uint64_t deadline) {
  return &timer_queue;
}

void timer_call_cpu(int cpu, void (*fn)(void *), void *arg) {
  GetHypercallInterface()->Abort();
}

void timer_queue_cancel(mpqueue_head_t *queue, uint64_t deadline,
                        uint64_t new_deadline) {}

mpqueue_head_t *timer_queue_cpu(int cpu) {
  GetHypercallInterface()->Abort();
}

boolean_t timer_resort_threshold(uint64_t skew) {
  GetHypercallInterface()->Abort();
}

void timer_call_nosync_cpu(int cpu, void (*fn)(void *), void *arg) {}

void timer_resync_deadlines() {}

void ml_timer_evaluate() {}

boolean_t ml_timer_forced_evaluation() {
  GetHypercallInterface()->Abort();
}
