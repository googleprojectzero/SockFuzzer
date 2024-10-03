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

#include "fuzz/handlers/session.h"

#include "fuzz/host/host.h"
#include "fuzz/handlers/command_thread.h"
#include "fuzz/xnu/bsd/api/backend.h"

void HandleSession(const Session *session) {
  g_host->sync_tracker()->BeginSession();
  g_host->scheduler()->SetInterruptsEnabled(true);

  ready_for_preemption = false;
  // CheckSchedulerState();

  // size_t num_threads = g_host->scheduler->NumLiveThreads();

  thread_t thread1 = CloneTaskFromInit();
  task_t task = GetTaskFromThread(thread1);
  if (!thread1) {
    abort();
    return;
  }

  GetHypercallInterface()->ThreadSetContinuation(thread1, CommandThread,
                            (void *)&session->commands1());
  g_host->SetId(thread1, 1);

  thread_t thread2 = CreateWaitingThread(task);  // CloneTaskFromInit();
  if (!thread2) {
    abort();
    return;
  }

  GetHypercallInterface()->ThreadSetContinuation(thread2, CommandThread,
                            (void *)&session->commands2());
  g_host->SetId(thread2, 2);

  // TODO(nedwill): figure out how to share send rights to task ports
  thread_t thread3 = CloneTaskFromInit();
  task_t task2 = GetTaskFromThread(thread3);
  if (thread3 == nullptr) {
    abort();
    return;
  }

  GetHypercallInterface()->ThreadSetContinuation(thread3, CommandThread,
                            (void *)&session->commands3());
  g_host->SetId(thread3, 3);

  // Now that we've setup the threads with continuations they are ready to run.
  ClearTaskWait(task);
  ClearTaskWait(task2);

  FuzzedDataProvider xnu_dp(
      reinterpret_cast<const uint8_t *>(session->xnu_data_provider().data()),
      session->xnu_data_provider().size());
  xnu_fdp = &xnu_dp;

  g_host->scheduler()->SetRandSeed(session->schedule().rand_seed());
  FuzzedDataProvider thread_choices_dp(
      reinterpret_cast<const uint8_t *>(
          session->schedule().thread_choices().data()),
      session->schedule().thread_choices().size());
  g_host->scheduler()->SetThreadChoices(&thread_choices_dp);
  ready_for_preemption = true;

  g_host->RunUntilEmpty();

  // TODO(nedwill): generically abort and deallocate non-system threads
  // TODO(nedwill): run these from another thread as they can get stuck
  GetHypercallInterface()->ThreadAbort(thread1);
  g_host->RunUntilEmpty();
  GetHypercallInterface()->ThreadAbort(thread2);
  g_host->RunUntilEmpty();
  GetHypercallInterface()->ThreadAbort(thread3);
  g_host->RunUntilEmpty();

  thread_deallocate(thread1);
  thread_deallocate(thread2);
  thread_deallocate(thread3);
  g_host->RunUntilEmpty();

  g_host->Log("Killing all non init procs\n");
  g_host->scheduler()->SetInterruptsEnabled(false);
  KillAllNonInitProcs();
  // Multiple calls might be needed if first call reparented ptraced children
  while (XNUReapInitChildren()) {
  }

  g_host->RunUntilEmpty();
  xnu_fdp = nullptr;

  g_host->NotifyEndOfSession();
  // TODO(nwach): Freeing everything causes sporadic crashes. Some must be
  // meant to stick around in the kernel.
  // g_adapter->sync_tracker()->FreeTracked();

  // CheckSchedulerState();

#ifdef LIMIT_CALLGRIND_SCOPE
  CALLGRIND_TOGGLE_COLLECT;
  CALLGRIND_STOP_INSTRUMENTATION;
#endif
}
