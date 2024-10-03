// Copyright 2024 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "third_party/concurrence/sync/rwlock.h"

#include <gtest/gtest.h>
#include <deque>
#include <set>

#include "third_party/concurrence/scheduler/mock_scheduler.h"
#include "third_party/concurrence/sync/tracker.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::ElementsAre;
using ::testing::IsEmpty;
using ::testing::StrictMock;

TEST(RwLockTest, MultipleReaders) {
  StrictMock<MockScheduler> mock_scheduler;
  SyncTracker tracker(&mock_scheduler);
  VirtualRwLock rwlock(&tracker);

  g_current_thread = 1;
  EXPECT_CALL(mock_scheduler, MakeAllRunnable(IsEmpty()));

  rwlock.LockShared();

  g_current_thread = 2;
  EXPECT_CALL(mock_scheduler, MakeAllRunnable(IsEmpty()));

  rwlock.LockShared();

  g_current_thread = 3;
  EXPECT_CALL(mock_scheduler, MakeAllRunnable(IsEmpty()));

  rwlock.LockShared();

  g_current_thread = 1;
  EXPECT_CALL(mock_scheduler, MakeAllRunnable(IsEmpty()));
  rwlock.UnlockShared();

  g_current_thread = 2;
  EXPECT_CALL(mock_scheduler, MakeAllRunnable(IsEmpty()));
  rwlock.UnlockShared();

  g_current_thread = 3;
  // Lock is released, waiters signalled
  EXPECT_CALL(mock_scheduler, MakeAllRunnable(IsEmpty())).Times(2);
  rwlock.UnlockShared();
}

TEST(RwLockTest, ReadersWaitForWriter) {
  MockScheduler mock_scheduler;
  SyncTracker tracker(&mock_scheduler);
  VirtualRwLock rwlock(&tracker);

  // Exclusive lock with thread 1
  g_current_thread = 1;
  rwlock.LockExclusive();

  // Try to shared lock with thread 2
  g_current_thread = 2;
  EXPECT_CALL(mock_scheduler, MakeAllRunnable(IsEmpty())).Times(1);
  EXPECT_CALL(mock_scheduler, MakeAllRunnable(ElementsAre(2)));

  EXPECT_CALL(mock_scheduler, Block()).WillRepeatedly([&]() {
    // Thread 1 releases
    g_current_thread = 1;
    rwlock.UnlockExclusive();
    g_current_thread = 2;
    return true;
  });

  rwlock.LockShared();

  // No one will be waiting
  EXPECT_CALL(mock_scheduler, MakeAllRunnable(IsEmpty())).Times(2);
  g_current_thread = 2;
  rwlock.UnlockShared();
}

// TEST(RwLockTest, WriterWaitsForReaders)
