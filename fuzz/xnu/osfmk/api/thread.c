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

#include "fuzz/xnu/osfmk/api/thread.h"

#include <kern/kern_types.h>
#include <kern/processor.h>
#include <kern/sched_prim.h>
#include <kern/task.h>
#include <kern/timer_call.h>
#include <mach/thread_act_server.h>

#include "fuzz/host/hypercall/hypercall.h"

void XNUThreadEnqueueTermination(thread_t thread) {
  thread_terminate_enqueue(thread);
}

void XNUThreadSchedCallNotifyBlocked(thread_t thread) {
  (*thread->sched_call)(SCHED_CALL_BLOCK, thread);
}

void XNUThreadSchedCallNotifyUnblocked(thread_t thread) {
  (*thread->sched_call)(SCHED_CALL_UNBLOCK, thread);
}

void XNUThreadCancelWaitTimer(thread_t thread) {
  if (thread->wait_timer_armed) {
    if (timer_call_cancel(thread->wait_timer)) {
      thread->wait_timer_active--;
    }
    thread->wait_timer_armed = false;
  }
}

void XNUThreadSignalWake(thread_t thread) {
  if (thread->wake_active) {
    thread->wake_active = false;
    thread_wakeup(&thread->wake_active);
  }
}

bool XNUWaitInterruptIsAbortSafe(wait_interrupt_t wait_interrupt) {
  return (wait_interrupt & TH_OPT_INTMASK) == THREAD_ABORTSAFE;
}

static bool XNUWaitInterruptIsUninterruptible(wait_interrupt_t wait_interrupt) {
  return (wait_interrupt & TH_OPT_INTMASK) == THREAD_UNINT;
}

bool XNUThreadSchedulerStateIsAbortSafely(thread_t thread) {
  return thread->sched_flags & TH_SFLAG_ABORTSAFELY;
}

wait_result_t XNUThreadMarkWaitLocked(thread_t thread,
                                      wait_interrupt_t interruptible_orig) {
  boolean_t at_safe_point = 0;
  wait_interrupt_t interruptible = interruptible_orig;

#ifndef NDEBUG
  if (GetHypercallInterface()->ThreadIsWaiting(thread) ||
      GetHypercallInterface()->ThreadIsIdle(thread) ||
      GetHypercallInterface()->ThreadIsUninterruptible(thread) ||
      GetHypercallInterface()->ThreadIsEnqueuedForTermination(thread) ||
      GetHypercallInterface()->ThreadWantsWaitReport(thread)) {
    GetHypercallInterface()->Abort();
  }
#endif

  interruptible &= TH_OPT_INTMASK;

  at_safe_point = XNUWaitInterruptIsAbortSafe(interruptible_orig);

  if (XNUWaitInterruptIsUninterruptible(interruptible_orig) ||
      !(thread->sched_flags & TH_SFLAG_ABORT) ||
      (!at_safe_point && XNUThreadSchedulerStateIsAbortSafely(thread))) {
    GetHypercallInterface()->ThreadSetWaiting(thread);
    if (!interruptible) {
      GetHypercallInterface()->ThreadSetUninterruptible(thread);
    }
    if (thread->sched_call) {
      wait_interrupt_t mask = THREAD_WAIT_NOREPORT_USER;
      if (is_kerneltask(get_threadtask(thread))) {
        mask = THREAD_WAIT_NOREPORT_KERNEL;
      }
      if ((interruptible_orig & mask) == 0) {
        GetHypercallInterface()->ThreadSetWaitReport(thread);
      }
    }
    thread->at_safe_point = at_safe_point;
    GetHypercallInterface()->ThreadSetWaitResult(thread, THREAD_WAITING);

    return THREAD_WAITING;
  }
  if (thread->sched_flags & TH_SFLAG_ABORTSAFELY) {
    thread->sched_flags &= ~TH_SFLAG_ABORTED_MASK;
  }

  GetHypercallInterface()->ThreadSetWaitResult(thread, THREAD_INTERRUPTED);
  return THREAD_INTERRUPTED;
}

void cause_ast_check(processor_t processor) {
  (void)processor;
  GetHypercallInterface()->Abort();
}

bool XNUThreadStop(thread_t thread, boolean_t until_not_runnable) {
  wait_result_t wresult = 0;

  while (GetHypercallInterface()->ThreadIsSuspended(thread)) {
    thread->wake_active = true;

    wresult = XNUAssertWait(&thread->wake_active, THREAD_ABORTSAFE);
    if (wresult == THREAD_WAITING) {
      wresult = GetHypercallInterface()->ThreadBlock(THREAD_CONTINUE_NULL);
    }
    if (wresult != THREAD_AWAKENED) {
      return false;
    }
  }

  GetHypercallInterface()->ThreadSetSuspended(thread);

  while (until_not_runnable &&
         GetHypercallInterface()->ThreadIsRunnable(thread)) {
    thread->wake_active = true;

    wresult = XNUAssertWait(&thread->wake_active, THREAD_ABORTSAFE);

    if (wresult == THREAD_WAITING) {
      wresult = GetHypercallInterface()->ThreadBlock(THREAD_CONTINUE_NULL);
    }

    if (wresult != THREAD_AWAKENED) {
      GetHypercallInterface()->ThreadUnstop(thread);
      return false;
    }
  }

  /*
	 * We return with the thread unlocked. To prevent it from
	 * transitioning to a runnable state (or from TH_RUN to
	 * being on the CPU), the caller must ensure the thread
	 * is stopped via an external means (such as an AST)
	 */

  return true;
}

wait_result_t XNUAssertWait(event_t event, wait_interrupt_t interruptible) {
  return assert_wait(event, interruptible);
}

void XNUThreadWait(thread_t thread, boolean_t until_not_runnable) {
  while (until_not_runnable &&
         GetHypercallInterface()->ThreadIsRunnable(thread)) {
    thread->wake_active = true;
    wait_result_t wresult = XNUAssertWait(&thread->wake_active, THREAD_UNINT);

    if (wresult == THREAD_WAITING) {
      GetHypercallInterface()->ThreadBlockReason(THREAD_CONTINUE_NULL, NULL);
    }
  }
}

void thread_terminate(thread_t thread);

void XNUThreadTerminate(thread_t thread) {
  thread_terminate(thread);
}

// Use XNU prefix since we generate protobuf class with ThreadAbortSafely
void XNUThreadAbort(thread_t thread) {
  thread_abort(thread);
}
