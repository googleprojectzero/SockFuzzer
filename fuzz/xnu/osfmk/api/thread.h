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

#ifndef FUZZ_XNU_OSFMK_API_THREAD_H_
#define FUZZ_XNU_OSFMK_API_THREAD_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef LIBXNU_BUILD
#include <kern/kern_types.h>
#include <kern/thread.h>
#include <mach/i386/boolean.h>
#include <mach/mach_types.h>
#include <stdbool.h>
#include <stddef.h>
#else
#include "types.h"
#endif

// Continuations
void XNUThreadSetContinuation(thread_t thread, thread_continue_t function,
                              void *parameter);

// Wait timer
void XNUThreadCancelWaitTimer(thread_t thread);

// Blocked
void XNUThreadSchedCallNotifyBlocked(thread_t thread);
void XNUThreadSchedCallNotifyUnblocked(thread_t thread);
void XNUThreadSignalWake(thread_t thread);

wait_result_t XNUThreadMarkWaitLocked(thread_t thread,
                                      wait_interrupt_t interruptible_orig);
bool XNUThreadStop(thread_t thread, boolean_t until_not_runnable);
void XNUThreadWait(thread_t thread, boolean_t until_not_runnable);

wait_result_t XNUAssertWait(event_t event, wait_interrupt_t interruptible);

void XNUThreadStart();
void XNUThreadTerminate(thread_t thread);
void XNUThreadEnqueueTermination(thread_t thread);
void XNUThreadAbort(thread_t thread);
void XNUThreadGetThreadName(thread_t th, char *name);
void XNUGetThreadInfo(thread_t thread, char *data, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* FUZZ_XNU_OSFMK_API_THREAD_H_ */
