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

#include "mutex.h"

#include <gtest/gtest.h>
#include <set>

#include "third_party/concurrence/scheduler/mock_scheduler.h"
#include "third_party/concurrence/sync/tracker.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::ElementsAre;
using ::testing::IsEmpty;

bool is_verbose = false;

TEST(MutexTest, LockUnlock) {
  MockScheduler mock_scheduler;
  SyncTracker tracker(&mock_scheduler);
  VirtualMutex mutex(&tracker);

  // Thread 1 acquires
  g_current_thread = 1;
  mutex.Lock();

  // Prepare thread 2 to block
  EXPECT_CALL(mock_scheduler, Block()).WillOnce([&]() {
    // Prepare MakeAllRunnable call from scheduler
    EXPECT_CALL(mock_scheduler, MakeAllRunnable(ElementsAre(2)));
    // Thread 1 releases while thread 2 is blocked
    g_current_thread = 1;
    mutex.Unlock();
    g_current_thread = 2;
    return true;
  });

  // Thread 2 blocks, triggering thread 1 unlock callback
  g_current_thread = 2;
  mutex.Lock();

  // When thread 2 unlocks there should be no waiters
  EXPECT_CALL(mock_scheduler, MakeAllRunnable(IsEmpty()));

  g_current_thread = 2;
  // Thread 2 releases
  mutex.Unlock();
}
