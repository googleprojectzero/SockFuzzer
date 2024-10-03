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

#ifndef FUZZ_HOST_HYPERCALL_HYPERCALL_H_
#define FUZZ_HOST_HYPERCALL_HYPERCALL_H_

// Host interface exposed to kernel code (libxnu.so)

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef LIBXNU_BUILD
#include <kern/kern_types.h>
#include <kern/thread.h>
#include <mach/i386/boolean.h>
#include <mach/mach_types.h>
#ifdef MACH_KERNEL_PRIVATE
#include <kern/ticket_lock.h>
#endif /* MACH_KERNEL_PRIVATE */
#else
#include "fuzz/xnu/osfmk/api/types.h"
#include "fuzz/xnu/osfmk/api/backend.h"

struct HyperMutex;
struct HyperRwLock;
struct HyperTicketLock;
#endif

extern thread_t main_thread;

extern bool kernel_booted;
extern bool ready_for_preemption;
extern bool is_verbose;

#ifdef __cplusplus
extern "C" {
#endif

#include "fuzz/host/hypercall/types.h"

// This is the "hypercall" interface to the concurrence scheduler from
// XNU. We want this to be as small as possible.

struct HypercallInterface {
  void (*Initialize)(void);
  __attribute__((noreturn)) void (*Abort)(void);
  void (*Yield)(void);
  void (*Block)(void);
  bool (*SetInterruptsEnabled)(bool enabled);
  void (*ThreadPrintf)(const char *format, ...);
  void (*Log)(enum log_subsystem subsystem, const char *format, ...);
  void (*LogVaList)(const char *format, va_list args);
  void (*ReportBadThreadState)(enum bad_state state);
  void (*BlockCopyin)(void);
  void (*UnblockCopyin)(void);
  size_t (*RandomDataRemaining)(void);
  size_t (*BytesNeeded)(void);
  __attribute__((noreturn)) void (*SyscallReturn)();
  bool (*IsCopyioBlocked)(void);
  bool (*GetInterruptsEnabled)();
  void (*GetFuzzedBytes)(void *addr, size_t bytes);
  bool (*GetFuzzedBool)(void);
  uint32_t (*GetFuzzedUint32)();
  uint32_t (*GetFuzzedUint32InRange)(uint32_t low, uint32_t high);
  uint64_t (*GetFuzzedUint64)();
  uint64_t (*GetFuzzedUint64InRange)(uint64_t low, uint64_t high);
  unsigned int (*GetRemainingFuzzedBytes)(void);
  void (*FreeVirtualMutex)(void *mutex);
  void *(*CurrentProc)();
  bool (*IsHwTicketLockValid)(void *lck);

  kern_return_t (*ThreadGo)(thread_t thread, wait_result_t wresult);
  wait_result_t (*ThreadMarkWaitLocked)(thread_t thread,
                                        wait_interrupt_t interruptible_orig);
  void (*ThreadSetTerminating)(thread_t thread);
  bool (*ThreadIsTerminating)(thread_t thread);
  bool (*ThreadIsEnqueuedForTermination)(thread_t thread);
  boolean_t (*ThreadStop)(thread_t thread, boolean_t until_not_runnable);
  void (*ThreadUnstop)(thread_t thread);
  void (*ThreadClearUninterruptibleWait)(thread_t thread);
  void (*ThreadWait)(thread_t thread, boolean_t until_not_runnable);
  bool (*ThreadIsRunnable)(thread_t thread);
  void (*ThreadSetRunnable)(thread_t thread);
  void (*ThreadSetNotRunnable)(thread_t thread);
  void (*ThreadSetUninterruptibleWait)(thread_t thread);
  bool (*ThreadIsIdle)(thread_t thread);
  bool (*ThreadIsWaiting)(thread_t thread);
  bool (*ThreadIsUninterruptible)(thread_t thread);
  bool (*ThreadIsSuspended)(thread_t thread);
  bool (*ThreadWantsWaitReport)(thread_t thread);
  bool (*ThreadShouldBlock)(thread_t thread);
  void (*ThreadSignalWake)(thread_t thread);
  void (*ThreadClearWait)(thread_t thread, wait_result_t result);
  void (*ThreadSetWaitResult)(thread_t thread, wait_result_t result);
  void (*ThreadCancelWaitTimer)(thread_t thread);
  void (*ThreadSchedCallNotifyUnblocked)(thread_t thread);
  void (*ThreadSetNotSuspended)(thread_t thread);
  void (*ThreadSetSuspended)(thread_t thread);
  void (*ThreadSetWaitReport)(thread_t thread);
  void (*ThreadSetNotWaitReport)(thread_t thread);
  void (*ThreadSetUninterruptible)(thread_t thread);
  void (*ThreadSetNotUninterruptible)(thread_t thread);
  wait_result_t (*ThreadGetWaitResult)(thread_t thread);

  // Continuations
  wait_result_t (*ThreadBlock)(thread_continue_t continuation);
  wait_result_t (*ThreadBlockReason)(thread_continue_t continuation,
                                     void *parameter);
  void (*ThreadSetContinuation)(thread_t thread, thread_continue_t continuation,
                                void *parameter);
  void (*ThreadClearContinuation)(thread_t thread);
  void (*ThreadAbort)(thread_t thread);
  void (*ThreadFinished)();
  void (*ThreadSetWaiting)(thread_t thread);
  void (*ThreadSetNotWaiting)(thread_t thread);

  void (*CreateThread)(thread_t thread, bool runnable);
  thread_t (*GetCurrentThreadT)(void);
  void (*SetCurrentThreadT)(thread_t thread);
  void (*PrintBacktrace)(thread_t thread);
  void (*PrintThreadState)(thread_t thread);
  void (*NotifyDestroyed)(thread_t thread);

  struct HyperMutex *(*AllocateMutex)(void);
  void (*FreeMutex)(struct HyperMutex *mutex);
  void (*AssertMutexHeld)(struct HyperMutex *mutex);
  void (*MutexLock)(struct HyperMutex *sp);
  bool (*MutexTryLock)(struct HyperMutex *sp);
  void (*MutexUnlock)(struct HyperMutex *sp);
  bool (*MutexIsOwned)(struct HyperMutex *sp);

  void (*TicketLockAllocate)(struct HyperTicketLock **tlock);
  void (*TicketLockDestroy)(struct HyperTicketLock **tlock, bool sync);
  int (*TicketLockLock)(struct HyperTicketLock **htlock, bool allow_invalid,
                        uint64_t timeout, void *handler);
  bool (*TicketLockTryLock)(struct HyperTicketLock **tlock);
  void (*TicketLockUnlock)(struct HyperTicketLock **tlock);
  void (*TicketLockInvalidate)(struct HyperTicketLock **tlock);
  bool (*TicketLockHeld)(struct HyperTicketLock **tlock);

  struct HyperRwLock *(*AllocateRwLock)(void);
  void (*FreeRwLock)(struct HyperRwLock *rwlock);
  void (*RwLockExclusiveToShared)(struct HyperRwLock *rwlock);
  bool (*RwLockSharedToExclusive)(struct HyperRwLock *rwlock);
  void (*RwLockLockExclusive)(struct HyperRwLock *rwlock);
  bool (*RwLockTryLockExclusive)(struct HyperRwLock *rwlock);
  void (*RwLockLockShared)(struct HyperRwLock *rwlock);
  bool (*RwLockTryLockShared)(struct HyperRwLock *rwlock);
  void (*RwLockUnlockExclusive)(struct HyperRwLock *rwlock);
  void (*RwLockUnlockShared)(struct HyperRwLock *rwlock);
  void (*RwLockUnlock)(struct HyperRwLock *rwlock);
  bool (*RwLockIsShared)(struct HyperRwLock *rwlock);
} __attribute__((aligned(128)));

struct HypercallInterface* GetHypercallInterface(void);

#ifdef __cplusplus
}
#endif

#endif /* FUZZ_HOST_HYPERCALL_HYPERCALL_H_ */
