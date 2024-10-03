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

#ifndef SCHEDULER_STATE_H_
#define SCHEDULER_STATE_H_

#include <stdbool.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

#ifdef LIBXNU_BUILD
#include <kern/thread.h>
#include <mach/mach_types.h>
#else
#include "types.h"
#endif

struct thread_debug_state {
  bool waiting;
  bool suspended;
  bool runnable;
  bool uninterruptible;
  bool terminate;
  bool terminate2;
  bool wait_report;
  bool idle;
  uint64_t wait_event;
  void *runq;
  void *waitq;
  bool wake_active;
  int wait_result;
};

typedef struct thread_debug_state *thread_debug_state_t;

void GetThreadState(thread_t thread, thread_debug_state_t state);

void CheckSchedulerState();

#ifdef __cplusplus
}
#endif

#endif
