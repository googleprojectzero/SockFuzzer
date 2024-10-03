/*
 * Copyright 2024 Google LLC
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

#ifndef CONCURRENCE_SCHEDULER_FUZZED_SCHEDULER_TEST_TEMPLATE_H_
#define CONCURRENCE_SCHEDULER_FUZZED_SCHEDULER_TEST_TEMPLATE_H_

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "third_party/concurrence/scheduler/fuzzed_scheduler.h"

extern Scheduler *g_scheduler;

class EmptySchedulerCallbacks : public Scheduler::CallbackInterface {
  void ThreadWillBlock() override {}
  void ThreadResumed() override {}
  void ThreadDestroyed(ThreadHandle handle) override {}
  std::string DescribeThreadHandle(ThreadHandle handle) override { return {}; }
  void ReportDeadlock(const std::deque<ThreadHandle> &handles) override {}
};

template <class T>
Scheduler *CreateScheduler();

template <class T>
class SchedulerTest : public testing::Test {
 protected:
  // The ctor calls the factory function to create a prime table
  // implemented by T.
  SchedulerTest() : scheduler_(CreateScheduler<T>()) {}

  ~SchedulerTest() override { delete scheduler_; }

  Scheduler *const scheduler_;
};

TYPED_TEST_SUITE_P(SchedulerTest);

inline void yield() {
  g_scheduler->Yield();
}

inline void Store123(std::vector<int> *results) {
  yield();
  results->push_back(1);
  yield();
  results->push_back(2);
  yield();
  results->push_back(3);
}

inline void Store456(std::vector<int> *results) {
  yield();
  results->push_back(4);
  yield();
  results->push_back(5);
  yield();
  results->push_back(6);
}

TYPED_TEST_P(SchedulerTest, TwoThreads) {
  g_scheduler = this->scheduler_;

  std::vector<int> results;

  this->scheduler_->CreateThread([&results]() { Store123(&results); }, true);
  this->scheduler_->CreateThread([&results]() { Store456(&results); }, true);

  this->scheduler_->RunUntilEmpty();
  EXPECT_THAT(results, ::testing::SizeIs(6));
}

TYPED_TEST_P(SchedulerTest, TwoThreadsAlternating) {
  std::vector<uint8_t> data = {0, 0, 0, 0, 0, 0, 0, 0};
  FuzzedDataProvider fdp(data.data(), data.size());
  this->scheduler_->SetThreadChoices(&fdp);
  g_scheduler = this->scheduler_;
  std::vector<int> results;
  this->scheduler_->CreateThread([&results]() { Store123(&results); }, true);
  this->scheduler_->CreateThread([&results]() { Store456(&results); }, true);

  this->scheduler_->RunUntilEmpty();
  EXPECT_THAT(results, ::testing::ElementsAre(1, 4, 2, 5, 3, 6));
}

inline void CreateSubThreads(std::vector<int> *results) {
  g_scheduler->CreateThread([results]() { Store123(results); }, true);
  g_scheduler->CreateThread([results]() { Store456(results); }, true);
}

// Nested thread creation
TYPED_TEST_P(SchedulerTest, NestedThreadCreation) {
  g_scheduler = this->scheduler_;
  std::vector<int> results;
  this->scheduler_->CreateThread([&results]() { CreateSubThreads(&results); },
                                 true);
  this->scheduler_->RunUntilEmpty();
  EXPECT_THAT(results, ::testing::SizeIs(6));
}

// Test "yielding" doesn't crash when called from the main thread
TYPED_TEST_P(SchedulerTest, YieldNop) {
  g_scheduler = this->scheduler_;
  yield();
}

REGISTER_TYPED_TEST_SUITE_P(SchedulerTest, TwoThreads, TwoThreadsAlternating,
                            NestedThreadCreation, YieldNop);

#endif /* CONCURRENCE_SCHEDULER_FUZZED_SCHEDULER_TEST_TEMPLATE_H_ */
