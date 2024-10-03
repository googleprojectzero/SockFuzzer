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

#include "hw_ticket_lock_manager.h"

#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "absl/strings/string_view.h"
#include "fuzz/host/logger.h"
#include "fuzz/host/mock_host.h"
#include "third_party/concurrence/executor/executor.h"
#include "third_party/concurrence/scheduler/mock_scheduler.h"
#include "third_party/concurrence/sync/tracker.h"
#include "gmock/gmock.h"

using ::testing::ElementsAre;
using ::testing::Return;

bool is_verbose = false;

class FakeLoggerDetail : public LoggerDetail {
 public:
  FakeLoggerDetail() : LoggerDetail(nullptr) {}

  void Log(absl::string_view str) override {}
};

class HwTicketLockManagerTest : public ::testing::Test {
 protected:
  HwTicketLockManagerTest()
      : manager(&host), tracker(&scheduler), logger(&detail) {}

  void SetUp() override {
    EXPECT_CALL(host, logger()).WillRepeatedly(Return(&logger));
    EXPECT_CALL(host, sync_tracker()).WillRepeatedly(Return(&tracker));
  }

  MockHost host;
  MockScheduler scheduler;
  HwTicketLockManager manager;

  SyncTracker tracker;
  FakeLoggerDetail detail;
  Logger logger;
};

TEST_F(HwTicketLockManagerTest, Invalidate) {
  VirtualMutex* lock = nullptr;
  manager.Allocate(&lock);

  EXPECT_TRUE(manager.IsValid(&lock));

  manager.Invalidate(&lock);
  EXPECT_FALSE(manager.IsValid(&lock));

  manager.Destroy(&lock, true);
  EXPECT_FALSE(manager.IsValid(&lock));
}

TEST_F(HwTicketLockManagerTest, LockValid) {
  VirtualMutex* lock = nullptr;
  manager.Allocate(&lock);

  // Acquire lock on thread 1
  g_current_thread = 1;
  EXPECT_EQ(manager.Lock(&lock, false, 0, nullptr), HW_LOCK_ACQUIRED);
  EXPECT_TRUE(manager.Held(&lock));

  EXPECT_CALL(scheduler, Block()).WillOnce([&]() {
    // Prepare MakeAllRunnable call from scheduler
    EXPECT_CALL(scheduler, MakeAllRunnable(ElementsAre(2)));
    // Thread 1 releases while thread 2 is blocked
    g_current_thread = 1;
    manager.Unlock(&lock);
    g_current_thread = 2;
    return true;
  });

  g_current_thread = 2;
  EXPECT_EQ(manager.Lock(&lock, false, 0, nullptr), HW_LOCK_ACQUIRED);

  EXPECT_TRUE(manager.Held(&lock));
}

TEST_F(HwTicketLockManagerTest, LockInvalid) {
  VirtualMutex* lock = nullptr;
  manager.Allocate(&lock);

  // Acquire lock on thread 1
  g_current_thread = 1;
  hw_lock_status_t status = manager.Lock(&lock, false, 0, nullptr);
  EXPECT_EQ(status, HW_LOCK_ACQUIRED);
  EXPECT_TRUE(manager.Held(&lock));

  EXPECT_CALL(scheduler, Block()).WillOnce([&]() {
    // Prepare MakeAllRunnable call from scheduler
    EXPECT_CALL(scheduler, MakeAllRunnable(ElementsAre(2)));
    // Thread 1 releases while thread 2 is blocked
    g_current_thread = 1;
    EXPECT_TRUE(manager.IsValid(&lock));
    manager.Invalidate(&lock);
    EXPECT_FALSE(manager.IsValid(&lock));
    manager.Unlock(&lock);
    EXPECT_CALL(scheduler, MakeAllRunnable(ElementsAre()));
    g_current_thread = 2;
    return true;
  });

  EXPECT_TRUE(manager.IsValid(&lock));

  g_current_thread = 2;
  EXPECT_EQ(manager.Lock(&lock, false, 0, nullptr), HW_LOCK_INVALID);
  EXPECT_FALSE(manager.IsValid(&lock));
  EXPECT_FALSE(manager.Held(&lock));
}
