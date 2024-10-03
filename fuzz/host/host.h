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

#ifndef FUZZ_HOST_HOST_H_
#define FUZZ_HOST_HOST_H_

// Host integration code

#include <fuzzer/FuzzedDataProvider.h>

#include <csetjmp>
#include <cstdint>
#include <cstdio>
#include <deque>
#include <memory>
#include <string>
#include <utility>

#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"
#include "fuzz/executor/coroutine_executor.h"
#include "fuzz/host/host_interface.h"
#include "fuzz/host/hw_ticket_lock_manager.h"
#include "fuzz/host/hypercall/hypercall.h"
#include "fuzz/host/hypercall/types.h"
#include "fuzz/host/logger.h"
#include "fuzz/xnu/osfmk/api/backend.h"
#include "fuzz/xnu/osfmk/api/types.h"
#include "third_party/concurrence/executor/executor.h"
#include "third_party/concurrence/scheduler/scheduler.h"
#include "third_party/concurrence/sync/tracker.h"

class FuzzedDataProvider;
class SyncTracker;
struct __jmp_buf_tag;

// asm
extern "C" {
uintptr_t GetStackPointer();
void CallContinuationWithStack(thread_continue_t continuation, void *parameter,
                               wait_result_t wresult, uintptr_t sp);
}

extern FuzzedDataProvider *xnu_fdp;
class Host : public Scheduler::CallbackInterface,
             public HostInterface,
             public LoggerDetail {
 public:
  explicit Host(std::ostream *out);
  ~Host() override = default;
  Host(const Host &) = delete;
  Host(Host &&) = delete;
  Host &operator=(const Host &) = delete;
  Host &operator=(Host &&) = delete;

  ThreadHandle CreateThread(thread_t thread, bool runnable);

  void Yield() override;

  // Thread state callbacks for Scheduler::CallbackInterface
  void ThreadWillBlock() override;
  void ThreadResumed() override;
  void ThreadDestroyed(ThreadHandle handle) override;
  std::string DescribeThreadHandle(ThreadHandle handle) override;
  void ReportDeadlock(const std::deque<ThreadHandle> &handles) override;
  // TODO(nwach): should these be added to callback interface?
  void ThreadStarted();
  void ThreadFinished();

  void ThreadWakeup(thread_t thread, wait_result_t wait_result);
  ThreadHandle ThreadSelect();

  bool TimeoutThread(ThreadHandle handle);

  void Wait(ThreadHandle handle);

  void EnableThreadPrintf();
  void PrintThreadPrefix();
  void Log(absl::string_view string) override;
  void ResetColors();
  // Helper for logging from C
  void ThreadPrintf(const char *format, va_list args);

  void NotifyEndOfSession();

  Scheduler *scheduler() { return scheduler_.get(); }

  SyncTracker *sync_tracker() override { return sync_tracker_.get(); }

  uint32_t GetId(ThreadHandle handle);
  void SetId(thread_t thread, uint32_t id);
  void SetThreadName(thread_t thread, const std::string &name);

  ThreadHandle ThreadTToHandle(thread_t thread);
  thread_t HandleToThreadT(ThreadHandle handle);

  void SwitchFrom(thread_t thread);
  void SwitchTo(ThreadHandle handle);

  thread_t GetCurrentThreadT() override;
  void SetCurrentThreadT(thread_t thread);

  __jmp_buf_tag *SetKernelEntryPoint();

  void SetContinuation(thread_t thread, thread_continue_t continuation,
                       void *param);
  void CallContinuationIfPresent();
  __attribute__((noreturn)) void SyscallReturn();
  void SaveStackPointerForContinuation();
  uintptr_t GetStackPointerForContinuation();

  void BlockCopyin();
  void UnblockCopyin();
  bool IsCopyioBlocked();

  void ReportBadThreadState(enum bad_state state);

  void RunUntilEmpty();

  bool IsRunnable(thread_t thread) override;
  void SetRunnable(thread_t thread);
  void SetNotRunnable(thread_t thread);

  bool IsSuspended(thread_t thread) override;
  void SetSuspended(thread_t thread);
  void SetNotSuspended(thread_t thread);

  bool IsTerminating(thread_t thread);
  void SetTerminating(thread_t thread);

  bool IsWaiting(thread_t thread) override;
  void SetWaiting(thread_t thread);
  void SetNotWaiting(thread_t thread);

  bool IsWaitReport(thread_t thread);
  void SetWaitReport(thread_t thread);
  void SetNotWaitReport(thread_t thread);

  bool IsUninterruptible(thread_t thread);
  void SetUninterruptible(thread_t thread);
  void SetNotUninterruptible(thread_t thread);

  bool IsEnqueuedForTermination(thread_t thread);
  void SetEnqueuedForTermination(thread_t thread);
  void SetNotEnqueuedForTermination(thread_t thread);

  wait_result_t GetWaitResult(thread_t thread);
  void SetWaitResult(thread_t thread, wait_result_t wait_result);

  void ThreadSetBlocked(thread_t thread);
  bool ShouldBlock(thread_t thread);
  void ThreadWait(thread_t thread, boolean_t until_not_runnable);

  wait_result_t ThreadBlock();

  bool IsHwTicketLockValid(VirtualMutex **tlock);

  HwTicketLockManager *hw_ticket_lock_manager() {
    return &hw_ticket_lock_manager_;
  }

  Logger *logger() override { return &logger_; }

 private:
  size_t GetRandomIndexForPointerName();
  std::string GenerateNameFromPointer(const void *ptr);

  std::unique_ptr<Scheduler> scheduler_;
  std::unique_ptr<SyncTracker> sync_tracker_;
  HwTicketLockManager hw_ticket_lock_manager_;
  Logger logger_;
  // TODO(nedwill): drop all these maps and create a HostThread to track ThreadHandle/thread_t/extraneous data
  absl::flat_hash_map<ThreadHandle, uint32_t> readable_ids_;
  absl::flat_hash_map<ThreadHandle, std::string> names_;
  absl::flat_hash_map<thread_t, ThreadHandle> internal_to_handle_;
  absl::flat_hash_map<ThreadHandle, thread_t> handle_to_internal_;
  absl::flat_hash_map<ThreadHandle, std::unique_ptr<__jmp_buf_tag>>
      saved_kernel_entry_contexts_;
  absl::flat_hash_map<ThreadHandle, uintptr_t>
      saved_continuation_stack_pointers_;
  absl::flat_hash_map<thread_t, std::pair<thread_continue_t, void *>>
      continuations_;
  absl::flat_hash_map<ThreadHandle, size_t> copyin_blocked_;
  uint32_t next_thread_id_;
  absl::flat_hash_set<thread_t> suspended_;
  absl::flat_hash_set<thread_t> suspended_runnable_;
  absl::flat_hash_set<thread_t> terminating_;
  absl::flat_hash_set<thread_t> waiting_;
  absl::flat_hash_set<thread_t> wait_report_;
  absl::flat_hash_set<thread_t> uninterruptible_;
  absl::flat_hash_set<thread_t> enqueued_for_termination_;
  absl::flat_hash_map<thread_t, wait_result_t> wait_results_;
};

extern Host *g_host;

void InitializeHost();

#endif /* FUZZ_HOST_HOST_H_ */
