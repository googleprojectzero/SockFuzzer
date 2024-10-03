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

// Expose internal scheduler state via a C++ object for assertion checking
#include "fuzz/xnu/osfmk/api/scheduler_state.h"

#include <kern/misc_protos.h>
#include <kern/processor.h>
#include <kern/queue.h>
#include <kern/task.h>
#include <stddef.h>

#include "fuzz/host/hypercall/hypercall.h"

void print_task(task_t task) {
  printf("task %p\n", task);
}

void print_thread(thread_t thread) {
  if (!is_verbose) {
    return;
  }
  if (!thread) {
    return;
  }

  // printf("wait %d/runq %p/waitq %p/wake %d/wait result %d\n",
  // thread->wait_event, thread->runq, thread->waitq, thread->wake_active,
  // thread->wait_result);
  printf("thread %p: ", thread);
  bool printed = false;
  if (GetHypercallInterface()->ThreadIsWaiting(thread)) {
    printf("TH_WAIT");
    printed = true;
  }
  if (GetHypercallInterface()->ThreadIsSuspended(thread)) {
    if (printed) {
      printf(", ");
    }
    printf("TH_SUSP");
    printed = true;
  }
  if (GetHypercallInterface()->ThreadIsRunnable(thread)) {
    if (printed) {
      printf(", ");
    }
    printf("TH_RUN");
    printed = true;
  }
  if (GetHypercallInterface()->ThreadIsUninterruptible(thread)) {
    if (printed) {
      printf(", ");
    }
    printf("TH_UNINT");
    printed = true;
  }
  if (GetHypercallInterface()->ThreadIsTerminating(thread)) {
    if (printed) {
      printf(", ");
    }
    printf("TH_TERMINATE");
    printed = true;
  }
  if (GetHypercallInterface()->ThreadIsEnqueuedForTermination(thread)) {
    if (printed) {
      printf(", ");
    }
    printf("TH_TERMINATE2");
    printed = true;
  }
  if (GetHypercallInterface()->ThreadWantsWaitReport(thread)) {
    if (printed) {
      printf(", ");
    }
    printf("TH_WAIT_REPORT");
    printed = true;
  }
  if (GetHypercallInterface()->ThreadIsIdle(thread)) {
    if (printed) {
      printf(", ");
    }
    printf("TH_IDLE");
    printed = true;
  }
  // printf("continuation %p\n", thread->continuation);
  GetHypercallInterface()->PrintThreadState(thread);
  // TODO(nedwill): investigate why this crashes sometimes
  // HostPrintBacktrace(thread);
}

void CheckSchedulerState() {
  if (!is_verbose) {
    return;
  }
  // See kernelcore.py
  task_t task = NULL;
  printf("total tasks expected %d\n", tasks_count);
  queue_iterate(&tasks, task, task_t, tasks) {
    print_task(task);
  }

  thread_t thread = NULL;
  printf("total threads expected %d\n", threads_count);
  queue_iterate(&threads, thread, thread_t, threads) {
    print_thread(thread);
  }
}

task_t GetTask(task_t task) {
  if (!task) {
    if (queue_empty(&tasks)) {
      return NULL;
    }
    return (task_t)queue_first(&tasks);
  }
  task = (task_t)queue_next(&task->tasks);
  if (task == (task_t)&tasks) {
    return NULL;
  }
  return task;
}

thread_t GetThread(thread_t thread) {
  if (!thread) {
    if (queue_empty(&threads)) {
      return NULL;
    }
    return (thread_t)queue_first(&threads);
  }
  thread = (thread_t)queue_next(&thread->threads);
  if (thread == (thread_t)&threads) {
    return NULL;
  }
  return thread;
}

void GetThreadState(thread_t thread, thread_debug_state_t state) {
  state->waiting = GetHypercallInterface()->ThreadIsWaiting(thread);
  state->suspended = GetHypercallInterface()->ThreadIsSuspended(thread);
  state->runnable = GetHypercallInterface()->ThreadIsRunnable(thread);
  state->uninterruptible = GetHypercallInterface()->ThreadIsUninterruptible(thread);
  state->terminate = GetHypercallInterface()->ThreadIsTerminating(thread);
  state->terminate2 = GetHypercallInterface()->ThreadIsEnqueuedForTermination(thread);
  state->wait_report = GetHypercallInterface()->ThreadWantsWaitReport(thread);
  state->idle = GetHypercallInterface()->ThreadIsIdle(thread);
  state->wait_event = thread->wait_event;
  state->runq = thread->__runq.runq;
  state->waitq = &thread->waitq;
  state->wake_active = thread->wake_active;
  state->wait_result = GetHypercallInterface()->ThreadGetWaitResult(thread);
}
