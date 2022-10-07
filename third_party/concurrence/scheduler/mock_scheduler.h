/*
 * Copyright 2022 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "gmock/gmock.h"
#include "scheduler.h"

class MockScheduler : public Scheduler {
 public:
  MOCK_METHOD(ThreadHandle, CreateThread,
              (std::function<void()> target, bool runnable), (override));
  MOCK_METHOD(ThreadHandle, ChooseThread, (bool can_choose_existing),
              (override));

  MOCK_METHOD(void, Yield, (), (override));
  MOCK_METHOD(void, Block, (), (override));
  MOCK_METHOD(void, SwitchTo, (ThreadHandle handle), (override));

  MOCK_METHOD(bool, SetInterruptsEnabled, (bool enable), (override));
  MOCK_METHOD(bool, GetInterruptsEnabled, (), (override));

  MOCK_METHOD(void, MakeRunnable, (ThreadHandle id), (override));
  MOCK_METHOD(void, MakeNotRunnable, (ThreadHandle id), (override));
  MOCK_METHOD(void, MakeAllRunnable,
              (const absl::flat_hash_set<ThreadHandle> &runnable), (override));
  MOCK_METHOD(bool, IsRunnable, (ThreadHandle handle), (override));
  MOCK_METHOD(void, CleanupDeadThreads, (), (override));

  MOCK_METHOD(void, ThreadDestroyed, (ThreadHandle handle), (override));

  MOCK_METHOD(bool, RunUntilEmpty, (), (override));

  MOCK_METHOD(void, SetRandSeed, (uint32_t rand_seed), (override));
  MOCK_METHOD(void, SetThreadChoices, (FuzzedDataProvider * fuzzed_data),
              (override));
  MOCK_METHOD(void, SetThreadName,
              (ThreadHandle handle, const std::string &name), (override));
  MOCK_METHOD(std::string, DescribeThreadHandle, (ThreadHandle), (override));
  MOCK_METHOD(ThreadHandle, GetMainThread, (), (override));
  MOCK_METHOD(ThreadHandle, GetCurrentThreadHandle, (), (override));
  MOCK_METHOD(const std::set<ThreadHandle> &, GetLiveThreads, (), (override));
  MOCK_METHOD(size_t, NumLiveThreads, (), (override));
  MOCK_METHOD(size_t, NumRunnableThreads, (), (override));
  MOCK_METHOD(void, PrintThreadState, (ThreadHandle handle), (override));
  MOCK_METHOD(void, PrintBacktrace, (ThreadHandle handle), (override));
  MOCK_METHOD(void, HandleDeadlock, (const std::deque<ThreadHandle> &handles),
              (override));

  MOCK_METHOD(void, ResetBytesNeeded, (), (override));
  MOCK_METHOD(size_t, BytesNeeded, (), (override));
  MOCK_METHOD(size_t, RandomDataRemaining, (), (override));
};
