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

#include "fuzz/host/host.h"

#include <gtest/gtest.h>
#include <mach/message.h>

#include <vector>

#include "fuzz/handlers/mach_message.h"
#include "fuzz/host/hypercall/hypercall.h"
#include "fuzz/proto/mach_message.pb.h"
#include "fuzz/xnu/bsd/api/backend.h"
#include "fuzz/xnu/osfmk/api/backend.h"
#include "fuzz/xnu/osfmk/api/scheduler_state.h"
#include "fuzz/xnu/test/backend.h"

extern int nprocs;
extern "C" int fork_wrapper(int *retval);

class Environment : public ::testing::Environment {
 public:
  ~Environment() override = default;

  // Override this to define how to set up the environment.
  void SetUp() override {
    is_verbose = true;
    InitializeHost();
    g_host->scheduler()->SetThreadChoices(nullptr);
  }
};

testing::Environment *const env =
    testing::AddGlobalTestEnvironment(new Environment);

bool ThreadIsWaiting(thread_t thread) {
  struct thread_debug_state state = {};
  GetThreadState(thread, &state);
  return state.waiting;
}

bool ThreadIsRunnable(thread_t thread) {
  struct thread_debug_state state = {};
  GetThreadState(thread, &state);
  return state.runnable;
}

bool ThreadIsInterruptible(thread_t thread) {
  struct thread_debug_state state = {};
  GetThreadState(thread, &state);
  return !state.uninterruptible;
}

uint64_t ThreadWaitEvent(thread_t thread) {
  struct thread_debug_state state = {};
  GetThreadState(thread, &state);
  return state.wait_event;
}

bool ThreadIsTerminated(thread_t thread) {
  struct thread_debug_state state = {};
  GetThreadState(thread, &state);
  return state.terminate;
}

bool ThreadIsTerminated2(thread_t thread) {
  struct thread_debug_state state = {};
  GetThreadState(thread, &state);
  return state.terminate2;
}

void Waitq1(Waitq *waitq, wait_result_t /* unused */) {
  waitq->AssertWait64(1, wait_interrupt::interruptible, 0);
  GetHypercallInterface()->ThreadBlock(nullptr);
  g_host->ThreadFinished();
}

void Waitq2(Waitq *waitq, wait_result_t /*unused*/) {
  waitq->AssertWait64(1, wait_interrupt::interruptible, 0);
  GetHypercallInterface()->ThreadBlock(nullptr);
  g_host->ThreadFinished();
}

TEST(HostTest, WaitqWakeupTwoInterruptible) {
  thread_t thread1 = CloneTaskFromInit();
  task_t task = GetTaskFromThread(thread1);
  thread_t thread2 = CreateWaitingThread(task);

  Waitq waitq(sync_policy::fifo);
  GetHypercallInterface()->ThreadSetContinuation(
      thread1, reinterpret_cast<thread_continue_t>(Waitq1), &waitq);
  GetHypercallInterface()->ThreadSetContinuation(
      thread2, reinterpret_cast<thread_continue_t>(Waitq2), &waitq);

  ClearTaskWait(task);

  g_host->RunUntilEmpty();

  EXPECT_FALSE(ThreadIsRunnable(thread1));
  EXPECT_TRUE(ThreadIsWaiting(thread1));
  EXPECT_TRUE(ThreadIsInterruptible(thread1));
  EXPECT_EQ(ThreadWaitEvent(thread1), 1);

  EXPECT_FALSE(ThreadIsRunnable(thread2));
  EXPECT_TRUE(ThreadIsWaiting(thread2));
  EXPECT_TRUE(ThreadIsInterruptible(thread2));
  EXPECT_EQ(ThreadWaitEvent(thread2), 1);

  // Wake up either thread1 or thread2
  kern_return ret = waitq.Wakeup64One(1, wait_result::interrupted, wakeup_flags::WAITQ_WAKEUP_DEFAULT);
  EXPECT_EQ(ret, kern_return::success);

  // The scheduler implementation might change, so we shouldn't count on
  // a certain order. All that matters is that exactly one of the
  // threads is awake. There are only two possiblities...
  if (ThreadIsRunnable(thread1)) {
    // thread1 runnable
    EXPECT_TRUE(ThreadIsRunnable(thread1));
    EXPECT_FALSE(ThreadIsWaiting(thread1));
    EXPECT_EQ(ThreadWaitEvent(thread1), 0);

    // thread2 waiting
    EXPECT_FALSE(ThreadIsRunnable(thread2));
    EXPECT_TRUE(ThreadIsWaiting(thread2));
    EXPECT_EQ(ThreadWaitEvent(thread2), 1);
  } else {
    // thread1 waiting
    EXPECT_FALSE(ThreadIsRunnable(thread1));
    EXPECT_TRUE(ThreadIsWaiting(thread1));
    EXPECT_EQ(ThreadWaitEvent(thread1), 1);

    // thread2 runnable
    EXPECT_TRUE(ThreadIsRunnable(thread2));
    EXPECT_FALSE(ThreadIsWaiting(thread2));
    EXPECT_EQ(ThreadWaitEvent(thread2), 0);
  }

  // Wake up the other one
  ret = waitq.Wakeup64One(1, wait_result::interrupted, wakeup_flags::WAITQ_WAKEUP_DEFAULT);
  EXPECT_EQ(ret, kern_return::success);

  // Thread 1 woke up
  EXPECT_TRUE(ThreadIsRunnable(thread1));
  EXPECT_FALSE(ThreadIsWaiting(thread1));
  EXPECT_EQ(ThreadWaitEvent(thread1), 0);

  // Thread 2 woke up
  EXPECT_TRUE(ThreadIsRunnable(thread2));
  EXPECT_FALSE(ThreadIsWaiting(thread2));
  EXPECT_EQ(ThreadWaitEvent(thread2), 0);

  ret = waitq.Wakeup64One(1, wait_result::interrupted, wakeup_flags::WAITQ_WAKEUP_DEFAULT);
  EXPECT_EQ(ret, kern_return::not_waiting);

  // Threads haven't actually been run yet so haven't terminated
  EXPECT_FALSE(ThreadIsTerminated(thread1));
  EXPECT_FALSE(ThreadIsTerminated(thread2));
  EXPECT_FALSE(ThreadIsTerminated2(thread1));
  EXPECT_FALSE(ThreadIsTerminated2(thread2));

  g_host->RunUntilEmpty();

  // Threads have finished running and terminated
  EXPECT_FALSE(ThreadIsRunnable(thread1));
  EXPECT_FALSE(ThreadIsRunnable(thread2));
  EXPECT_TRUE(ThreadIsTerminated(thread1));
  EXPECT_TRUE(ThreadIsTerminated(thread2));
  EXPECT_TRUE(ThreadIsTerminated2(thread1));
  EXPECT_TRUE(ThreadIsTerminated2(thread2));

  thread_deallocate(thread1);
  thread_deallocate(thread2);
  XNUReapInitChildren();
}

void ContinuationThread(void *ptr, wait_result_t wresult) {
  ASSERT_EQ(static_cast<wait_result>(wresult), wait_result::awakened);
  *reinterpret_cast<bool *>(ptr) = true;
  g_host->ThreadFinished();
}

void StartThread(void *ptr, wait_result_t /* unused */) {
  GetHypercallInterface()->ThreadBlockReason(static_cast<thread_continue_t>(ContinuationThread),
                        ptr);
  ASSERT_TRUE(false);
}

TEST(HostTest, ThreadBlockContinuation) {
  bool continuation_executed = false;
  thread_t thread = CloneTaskFromInit();
  task_t task = GetTaskFromThread(thread);
  GetHypercallInterface()->ThreadSetContinuation(thread,
                            reinterpret_cast<thread_continue_t>(StartThread),
                            &continuation_executed);
  ClearTaskWait(task);

  g_host->RunUntilEmpty();
  EXPECT_TRUE(continuation_executed);

  thread_deallocate(thread);
  g_host->RunUntilEmpty();
  XNUReapInitChildren();
}

void YieldingThread(void * /* unused */, wait_result_t /* unused */) {
  g_host->Yield();
  g_host->ThreadFinished();
}

TEST(HostTest, Yield) {
  thread_t thread = CloneTaskFromInit();
  task_t task = GetTaskFromThread(thread);
  GetHypercallInterface()->ThreadSetContinuation(
      thread, reinterpret_cast<thread_continue_t>(YieldingThread), nullptr);

  thread_t thread2 = CreateWaitingThread(task);
  GetHypercallInterface()->ThreadSetContinuation(
      thread2, reinterpret_cast<thread_continue_t>(YieldingThread), nullptr);

  thread_t thread3 = CloneTaskFromInit();
  task_t task2 = GetTaskFromThread(thread3);
  GetHypercallInterface()->ThreadSetContinuation(
      thread3, reinterpret_cast<thread_continue_t>(YieldingThread), nullptr);

  ClearTaskWait(task);
  ClearTaskWait(task2);

  g_host->RunUntilEmpty();
  thread_deallocate(thread);
  thread_deallocate(thread2);
  thread_deallocate(thread3);
  g_host->RunUntilEmpty();
  XNUReapInitChildren();
}

void ForkingThread(void * /* unused */, wait_result_t /* unused */) {
  int retval;
  fork_wrapper(&retval);
  g_host->ThreadFinished();
}

TEST(HostTest, Fork) {
  // Other tests might not reap their children
  XNUReapInitChildren();
  int original_nprocs = nprocs;
  thread_t thread = CloneTaskFromInit();
  task_t task = GetTaskFromThread(thread);
  GetHypercallInterface()->ThreadSetContinuation(
      thread, reinterpret_cast<thread_continue_t>(ForkingThread), nullptr);

  ClearTaskWait(task);
  g_host->RunUntilEmpty();
  thread_deallocate(thread);
  g_host->RunUntilEmpty();

  // Both threads should be finished and reapable.
  XNUReapInitChildren();

  ASSERT_EQ(original_nprocs, nprocs);
}

void CreateUserThreadThread(void * /* unused */, wait_result_t /* unused */) {
  mach_port_name_t port = task_self_trap_wrapper();

  // There must be a better way to represent this, but GetMachMsgStruct
  // looks complicated. This was pulled from gdb.
  const int thread_create_from_user = 3411;
  std::vector<uint8_t> msg =
      GetMachMsgStruct(FUZZED_MACH_MSG_TYPE_COPY_SEND, port, 0, 0, 0, 0,
                       thread_create_from_user, {}, {});

  mach_msg_trap_wrapper((user_addr_t)msg.data(), 1, msg.size(), 0, 0, 0, 0, 0);

  g_host->ThreadFinished();
}

TEST(HostTest, CreateUserThread) {
  GTEST_SKIP_("Known to be broken.");

  // Other tests might not reap their children
  XNUReapInitChildren();
  int original_nprocs = nprocs;
  thread_t thread = CloneTaskFromInit();
  task_t task = GetTaskFromThread(thread);
  GetHypercallInterface()->ThreadSetContinuation(
      thread, reinterpret_cast<thread_continue_t>(CreateUserThreadThread),
      nullptr);

  ClearTaskWait(task);
  g_host->RunUntilEmpty();
  thread_deallocate(thread);
  g_host->RunUntilEmpty();

  // Both threads should be finished and reapable.
  XNUReapInitChildren();

  ASSERT_EQ(original_nprocs, nprocs);
}

TEST(HostTest, NestedBlockCopyin) {
  EXPECT_FALSE(g_host->IsCopyioBlocked());

  g_host->BlockCopyin();
  EXPECT_TRUE(g_host->IsCopyioBlocked());

  g_host->BlockCopyin();
  EXPECT_TRUE(g_host->IsCopyioBlocked());

  g_host->UnblockCopyin();
  EXPECT_TRUE(g_host->IsCopyioBlocked());

  g_host->UnblockCopyin();
  EXPECT_FALSE(g_host->IsCopyioBlocked());
}

TEST(HostTest, Kheap) {
  KHeap allocator;
  for (int i = 0; i < 64000; i += 1024) {
    void *sa = allocator.alloc(i, 0);
    EXPECT_NE(sa, nullptr);
    allocator.free_addr(sa);
  }
}
