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

#include "host.h"

#include <fuzzer/FuzzedDataProvider.h>

#include <array>
#include <cassert>
#include <csetjmp>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

#include "absl/hash/hash.h"
#include "absl/log/check.h"
#include "absl/meta/type_traits.h"
#include "absl/strings/ascii.h"
#include "absl/strings/str_format.h"
#include "fuzz/executor/coroutine_executor.h"
#include "fuzz/host/hypercall/hypercall.h"
#include "fuzz/xnu/bsd/api/backend.h"
#include "fuzz/xnu/osfmk/api/backend.h"
#include "fuzz/xnu/osfmk/api/scheduler_state.h"
#include "fuzz/xnu/osfmk/api/thread.h"
#include "fuzz/xnu/osfmk/api/types.h"
#include "third_party/concurrence/backtrace/backtrace.h"
#include "third_party/concurrence/executor/executor.h"
#include "third_party/concurrence/scheduler/fuzzed_scheduler.h"
#include "third_party/concurrence/sync/sync.h"
#include "third_party/concurrence/sync/tracker.h"

thread_t main_thread;

bool ready_for_preemption = false;
bool is_verbose = false;

Host *g_host;

enum {
  THREAD_WAITING = -1,    /* thread is waiting */
  THREAD_AWAKENED = 0,    /* normal wakeup */
  THREAD_TIMED_OUT = 1,   /* timeout expired */
  THREAD_INTERRUPTED = 2, /* aborted/interrupted */
  THREAD_RESTART = 3,     /* restart operation entirely */
  THREAD_NOT_WAITING = 10 /* thread didn't need to wait */
};

// First seven thread IDs are reserved for fuzzing/default threads
Host::Host(std::ostream *out)
    : LoggerDetail(out),
      scheduler_(
          std::make_unique<FuzzedScheduler>(new CoroutineExecutor, this)),
      sync_tracker_(std::make_unique<SyncTracker>(scheduler_.get())),
      hw_ticket_lock_manager_(this),
      logger_(this),
      next_thread_id_(7) {}

ThreadHandle Host::ThreadTToHandle(thread_t thread) {
  auto it = internal_to_handle_.find(thread);
  if (it == internal_to_handle_.end()) {
    return 0;
  }
  return it->second;
}

ThreadHandle Host::CreateThread(thread_t thread, bool runnable) {
  ThreadHandle handle = scheduler_->CreateThread(
      [&]() {
        ThreadStarted();
        __builtin_unreachable();
      },
      runnable);

#ifndef NDEBUG
  if (thread && internal_to_handle_.count(thread)) {
    (*out_) << absl::StrFormat("Already have existing thread %p\n", thread);
    abort();
  }
  if (handle_to_internal_.count(handle)) {
    abort();
  }
#endif

  internal_to_handle_[thread] = handle;
  handle_to_internal_[handle] = thread;
  return handle;
}

void Host::Yield() {
  if (!ready_for_preemption) {
    return;
  }
  if (!scheduler_->GetInterruptsEnabled()) {
    return;
  }

  // We can't yield if we're already waiting on an event
  thread_t thread = GetCurrentThreadT();
  if (IsWaiting(thread)) {
    return;
  }

  ThreadBlock();
}

void Host::SetContinuation(thread_t thread, thread_continue_t continuation,
                           void *param) {
  if (!continuation) {
    continuations_.erase(thread);
    return;
  }

  continuations_[thread] = {continuation, param};
}

void Host::CallContinuationIfPresent() {
  thread_t thread = GetCurrentThreadT();

  scheduler()->SetInterruptsEnabled(true);
  auto it = continuations_.find(thread);
  if (it == continuations_.end()) {
    // No continuation present
    return;
  }

  auto [continuation, param] = it->second;
  continuations_.erase(it);
  uintptr_t sp = GetStackPointerForContinuation();
  wait_result_t wait_result = GetWaitResult(thread);
  CallContinuationWithStack(continuation, param, wait_result, sp);
}

__attribute__((noreturn)) void Host::SyscallReturn() {
  auto it = saved_kernel_entry_contexts_.find(g_current_thread);
  if (it == saved_kernel_entry_contexts_.end()) {
    abort();
  }
  __jmp_buf_tag *kernel_entry_context = it->second.get();
  longjmp(kernel_entry_context, 1);
}

uint32_t Host::GetId(ThreadHandle handle) {
  auto it = readable_ids_.find(handle);
  if (it == readable_ids_.end()) {
    uint32_t id = next_thread_id_++;
    readable_ids_[handle] = id;
    return id;
  }

  return it->second;
}

void Host::SetId(thread_t thread, uint32_t id) {
  ThreadHandle handle = ThreadTToHandle(thread);
  readable_ids_[handle] = id;
  auto it = names_.find(handle);
  if (it == names_.end()) {
    names_[handle] = absl::StrFormat("user%d", id);
  }
}

void Host::SetThreadName(thread_t thread, const std::string &name) {
  ThreadHandle handle = ThreadTToHandle(thread);
  thread_set_thread_name(thread, name.c_str());
  scheduler_->SetThreadName(handle, name);
  names_[handle] = name;
}

static std::array<char, 4096> thread_info;
std::string HostGetThreadInfo(thread_t thread) {
  if (!thread) {
    return "";
  }
  XNUGetThreadInfo(thread, thread_info.data(), thread_info.size());
  return thread_info.data();
}

// \033
const std::string reset_colors_and_text_effects = "\u001b[0m";
const std::string default_colors = "\u001b[39m";
const std::string bright_red = "\u001b[91m";
const std::string bright_green = "\u001b[92m";
const std::string bright_yellow = "\u001b[93m";
const std::string bright_blue = "\u001b[94m";
const std::string bright_magenta = "\u001b[95m";
const std::string bright_cyan = "\u001b[96m";
const std::string bright_white = "\u001b[97m";

const std::vector<std::string> color_sequences = {
    bright_magenta, bright_green, bright_red,   bright_blue,
    bright_yellow,  bright_cyan,  bright_white,
};

void Host::PrintThreadPrefix() {
  uint32_t id = GetId(g_current_thread);

  (*out_) << absl::StrFormat(
      "%s[%s]: ", color_sequences[(id - 1) % color_sequences.size()],
      DescribeThreadHandle(g_current_thread));
}

void Host::ResetColors() {
  (*out_) << reset_colors_and_text_effects;
  (*out_).flush();
}

void Host::ThreadPrintf(const char *format, va_list args) {
#ifndef NDEBUG
  if (!logger_.Enabled()) {
    return;
  }

  auto result = logger_.FormatWithPointers(format, args);
  if (!result.ok()) {
    logger_.Log(ANY_SUBSYSTEM, result.status().message());
  }
  const std::string &formatted = result.value();

  logger_.Log(ANY_SUBSYSTEM, formatted);

  if (formatted.empty() || formatted.back() != '\n') {
    logger_.Log(ANY_SUBSYSTEM, "\n");
  }
#endif
}

void Host::Log(absl::string_view string) {
#ifndef NDEBUG
  if (!logger_.Enabled()) {
    return;
  }
  PrintThreadPrefix();
  (*out_) << string;
  ResetColors();
#endif
}

void Host::ThreadDestroyed(ThreadHandle handle) {
  thread_t thread = HandleToThreadT(handle);

  internal_to_handle_.erase(thread);
  handle_to_internal_.erase(handle);
  saved_kernel_entry_contexts_.erase(handle);
  saved_continuation_stack_pointers_.erase(handle);
  continuations_.erase(thread);
  copyin_blocked_.erase(handle);
  suspended_.erase(thread);
  terminating_.erase(thread);
  waiting_.erase(thread);
  wait_report_.erase(thread);
  uninterruptible_.erase(thread);
  enqueued_for_termination_.erase(thread);
  wait_results_.erase(thread);
}

void Host::NotifyEndOfSession() {
  sync_tracker_->ReportSession();
}

void Host::EnableThreadPrintf() {
  logger_.Enable();
}

thread_t Host::HandleToThreadT(ThreadHandle handle) {
  auto it = handle_to_internal_.find(handle);
  if (it == handle_to_internal_.end()) {
    return nullptr;
    abort();
  }
  return it->second;
}

thread_t Host::GetCurrentThreadT() {
  return HandleToThreadT(g_current_thread);
}

void Host::SetCurrentThreadT(thread_t thread) {
  internal_to_handle_[thread] = g_current_thread;
  handle_to_internal_[g_current_thread] = thread;
}

__jmp_buf_tag *Host::SetKernelEntryPoint() {
  // syscall_return means returning to the "userspace" stack.
  // We save the current stack (below the userspace stack) so
  // any continuations won't overwrite it.
  SaveStackPointerForContinuation();

  saved_kernel_entry_contexts_[g_current_thread] =
      std::make_unique<__jmp_buf_tag>();
  __jmp_buf_tag *jmp_buf = saved_kernel_entry_contexts_[g_current_thread].get();
  assert(jmp_buf);

  // The setjmp man page says:
  // "If the function which called setjmp() returns before longjmp() is
  // called, the behavior is undefined.  Some kind of subtle or unsubtle
  // chaos is sure to result."
  // But it should be okay in this case as we are careful to not use any
  // stack variables and immediately return.
  return jmp_buf;
}

void Host::ThreadFinished() {
  // Thread is going away
  // logger_.Log(THREAD, "Host::ThreadFinished before terminate\n");
  XNUThreadTerminate(GetCurrentThreadT());
  // logger_.Log(THREAD, "Host::ThreadFinished after terminate\n");
  ast_taken_user();
}

void Host::SaveStackPointerForContinuation() {
  // Weird hack but fetching this deeper in the call stack is fairly safe
  // then we can continue to use it across continuations
  uintptr_t sp = GetStackPointer() & ~0xFF;
  saved_continuation_stack_pointers_[g_current_thread] = sp;
}

uintptr_t Host::GetStackPointerForContinuation() {
  // Subsequent continuations should reuse the same stack
  auto it = saved_continuation_stack_pointers_.find(g_current_thread);
  if (it != saved_continuation_stack_pointers_.end()) {
    return it->second;
  }

  SaveStackPointerForContinuation();
  return saved_continuation_stack_pointers_[g_current_thread];
}

void Host::BlockCopyin() {
  copyin_blocked_[g_current_thread]++;
}

void Host::UnblockCopyin() {
  copyin_blocked_[g_current_thread]--;
}

bool Host::IsCopyioBlocked() {
  return copyin_blocked_[g_current_thread] > 0;
}

std::string Host::DescribeThreadHandle(ThreadHandle handle) {
  auto it = names_.find(handle);
  if (it != names_.end()) {
    return absl::StrFormat("%s", it->second);
  }
  return absl::StrFormat("kernel%d", GetId(handle));
}

// TODO(nedwill): move some of this logic to the scheduler.
// We only need to support the non-concurrence thread state externally.
void Host::ReportDeadlock(const std::deque<ThreadHandle> &handles) {
  for (ThreadHandle handle : handles) {
    thread_t thread = HandleToThreadT(handle);
    auto state = std::make_unique<struct thread_debug_state>();
    GetThreadState(thread, state.get());

    Sync *sync = sync_tracker_->GetObjectWithWaiter(handle);
    if (!sync) {
      continue;
    }
    (*out_) << absl::StrFormat(
        "Thread 0x%lx (runnable %d waiting %d waitq %p) is blocked on sync "
        "primitive %p\n",
        handle, state->runnable, state->waiting, state->waitq, sync);
    scheduler_->PrintBacktrace(handle);
    for (const auto &it : sync->owner_backtraces()) {
      (*out_) << "\nThe primitive was locked here:\n";
      it.second->Print();
    }
    (*out_) << "\nThe primitive was constructed here:\n";
    sync->construction_stacktrace()->Print();
  }
  abort();
}

void Host::ReportBadThreadState(enum bad_state state) {
  switch (state) {
    case RUNNING_AFTER_CONTINUATION: {
      Log("Thread is resuming after continuation\n");
      abort();
      break;
    }
  }
}

void Host::RunUntilEmpty() {
  // TODO(nedwill): alternate scheduler implementations
  while (ThreadHandle handle = scheduler_->ChooseThread(false)) {
    SwitchTo(handle);
  }
  scheduler_->CleanupDeadThreads();
}

void Host::ThreadSetBlocked(thread_t thread) {
  if (!IsEnqueuedForTermination(thread) && IsTerminating(thread)) {
    SetEnqueuedForTermination(thread);
    XNUThreadEnqueueTermination(thread);
  }

  SetNotRunnable(thread);

  if (IsWaitReport(thread)) {
    XNUThreadSchedCallNotifyBlocked(thread);
  }
}

void Host::SwitchFrom(thread_t thread) {
  bool is_waiting = IsWaiting(thread);
  if (is_waiting) {
    ThreadSetBlocked(thread);
  } else {
    SetRunnable(thread);
  }

  GetHypercallInterface()->ThreadSignalWake(thread);
}

void Host::ThreadWillBlock() {
  thread_t self = GetCurrentThreadT();
  SetWaiting(self);
  SetUninterruptible(self);
}

void Host::ThreadStarted() {
  ThreadResumed();
}

void Host::ThreadResumed() {
  thread_t self = GetCurrentThreadT();
  GetHypercallInterface()->ThreadClearWait(self, THREAD_AWAKENED);
  CallContinuationIfPresent();
}

void Host::SwitchTo(ThreadHandle handle) {
  thread_t current_thread = HandleToThreadT(g_current_thread);

  if (handle == g_current_thread) {
    CallContinuationIfPresent();
    return;
  }

  SwitchFrom(current_thread);
  scheduler_->SwitchTo(handle);
}

void Host::ThreadWakeup(thread_t thread, wait_result_t wait_result) {
  GetHypercallInterface()->ThreadCancelWaitTimer(thread);

  bool wants_report = IsWaitReport(thread);
  GetHypercallInterface()->ThreadClearWait(thread, wait_result);

  if (IsRunnable(thread) && !ShouldBlock(thread)) {
    return;
  }

  SetRunnable(thread);
  ThreadHandle handle = ThreadTToHandle(thread);
  scheduler_->MakeRunnable(handle);

  if (wants_report) {
    GetHypercallInterface()->ThreadSchedCallNotifyUnblocked(thread);
  }
}

ThreadHandle Host::ThreadSelect() {
  thread_t self = GetCurrentThreadT();
  bool still_running = scheduler_->IsRunnable(g_current_thread) &&
                       !ShouldBlock(self) && !IsSuspended(self);

  ThreadHandle new_thread = scheduler_->ChooseThread(still_running);
  if (new_thread) {
    return new_thread;
  }

#ifndef NDEBUG
  if (IsWaiting(main_thread)) {
    Log("No runnable threads including main_thread\n");
    abort();
  }
#endif

  return scheduler_->GetMainThread();
}

bool Host::IsRunnable(thread_t thread) {
  return scheduler_->IsRunnable(ThreadTToHandle(thread));
}

void Host::SetRunnable(thread_t thread) {
  scheduler_->MakeRunnable(ThreadTToHandle(thread));
}

void Host::SetNotRunnable(thread_t thread) {
  scheduler_->MakeNotRunnable(ThreadTToHandle(thread));
}

bool Host::IsSuspended(thread_t thread) {
  return suspended_.count(thread) != 0;
}

void Host::SetSuspended(thread_t thread) {
  suspended_.insert(thread);
  if (IsRunnable(thread)) {
    suspended_runnable_.insert(thread);
    SetNotRunnable(thread);
  }
}

void Host::SetNotSuspended(thread_t thread) {
  suspended_.erase(thread);
  if (suspended_runnable_.contains(thread)) {
    suspended_runnable_.erase(thread);
    SetRunnable(thread);
  }
}

bool Host::IsTerminating(thread_t thread) {
  return terminating_.contains(thread);
}

void Host::SetTerminating(thread_t thread) {
  terminating_.insert(thread);
}

bool Host::IsWaiting(thread_t thread) {
  return waiting_.contains(thread);
}

void Host::SetWaiting(thread_t thread) {
  waiting_.insert(thread);
}

void Host::SetNotWaiting(thread_t thread) {
  waiting_.erase(thread);
}

bool Host::IsWaitReport(thread_t thread) {
  return wait_report_.contains(thread);
}

void Host::SetWaitReport(thread_t thread) {
  wait_report_.insert(thread);
}

void Host::SetNotWaitReport(thread_t thread) {
  wait_report_.erase(thread);
}

bool Host::IsUninterruptible(thread_t thread) {
  return uninterruptible_.contains(thread);
}

void Host::SetUninterruptible(thread_t thread) {
  uninterruptible_.insert(thread);
}

void Host::SetNotUninterruptible(thread_t thread) {
  uninterruptible_.erase(thread);
}

bool Host::IsEnqueuedForTermination(thread_t thread) {
  return enqueued_for_termination_.contains(thread);
}

void Host::SetEnqueuedForTermination(thread_t thread) {
  enqueued_for_termination_.insert(thread);
}

void Host::SetNotEnqueuedForTermination(thread_t thread) {
  enqueued_for_termination_.erase(thread);
}

wait_result_t Host::GetWaitResult(thread_t thread) {
  auto it = wait_results_.find(thread);
  if (it == wait_results_.end()) {
    return THREAD_WAITING;
  }
  return it->second;
}

void Host::SetWaitResult(thread_t thread, wait_result_t wait_result) {
  wait_results_[thread] = wait_result;
}

bool Host::ShouldBlock(thread_t thread) {
  return IsTerminating(thread) || IsWaiting(thread) || IsSuspended(thread);
}

wait_result_t Host::ThreadBlock() {
  thread_t self = GetCurrentThreadT();

  ThreadHandle handle = ThreadSelect();
  SwitchTo(handle);

#ifndef NDEBUG
  if (IsWaiting(self)) {
    CheckSchedulerState();
    Log("resumed a thread without clearing the waitq\n");
    abort();
  }
#endif

  return GetWaitResult(self);
}

bool Host::IsHwTicketLockValid(VirtualMutex **tlock) {
  return hw_ticket_lock_manager_.IsValid(tlock);
}

void HandleSignal(int signal) {
  auto stacktrace = std::make_unique<StackTrace>();
  stacktrace->Print();
  _Exit(1);
}

void InitializeHost() {
#if !__has_feature(address_sanitizer)
  // Install signal handler
  if (signal(SIGABRT, HandleSignal) == SIG_ERR) {
    perror("signal");
    abort();
  }
  if (signal(SIGSEGV, HandleSignal) == SIG_ERR) {
    perror("signal");
    abort();
  }
#endif

  g_host = new Host(&std::cout);
  if (is_verbose) {
    g_host->EnableThreadPrintf();
  }

  // Temporarily set empty data provider during init
  FuzzedDataProvider init_dp(nullptr, 0);
  xnu_fdp = &init_dp;
  g_host->scheduler()->SetThreadChoices(&init_dp);
  g_host->scheduler()->SetRandSeed(0);
  g_host->scheduler()->SetInterruptsEnabled(false);

  initialize_kernel();

  CHECK_EQ(main_thread, g_host->GetCurrentThreadT());
  g_host->RunUntilEmpty();
  xnu_fdp = nullptr;
}
