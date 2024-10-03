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

#ifndef CONCURRENCE_EXECUTOR_TEST_H_
#define CONCURRENCE_EXECUTOR_TEST_H_

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "third_party/concurrence/executor/executor.h"

class EmptyExecutorCallbacks : public Executor::CallbackInterface {
  void ThreadDestroyed(ThreadHandle handle) override {}
};

template <class T>
Executor* CreateExecutor();

template <class T>
class ExecutorTest : public ::testing::Test {
 protected:
  // The ctor calls the factory function to create a prime table
  // implemented by T.
  ExecutorTest() : executor_(CreateExecutor<T>()) {
    executor_->set_callbacks(&callbacks_);
  }

  ~ExecutorTest() override { delete executor_; }

  // Note that we test an implementation via the base interface
  // instead of the actual implementation class.  This is important
  // for keeping the tests close to the real world scenario, where the
  // implementation is invoked via the base interface.  It avoids
  // got-yas where the implementation class has a method that shadows
  // a method with the same name (but slightly different argument
  // types) in the base interface, for example.
  EmptyExecutorCallbacks callbacks_;
  Executor* const executor_;
};

TYPED_TEST_SUITE_P(ExecutorTest);

// Switch round robin between threads [ main -> 1 -> 2 -> main ]
TYPED_TEST_P(ExecutorTest, SwitchTo) {
  std::vector<int> order;

  ThreadHandle thread2 = this->executor_->CreateThread([&] {
    order.push_back(2);
    this->executor_->SwitchToMainThread();
  });

  ThreadHandle thread1 = this->executor_->CreateThread([&] {
    order.push_back(1);
    this->executor_->SwitchTo(thread2);
  });

  this->executor_->SwitchTo(thread1);
  order.push_back(3);

  EXPECT_THAT(order, ::testing::ElementsAre(1, 2, 3));
}

REGISTER_TYPED_TEST_SUITE_P(ExecutorTest, SwitchTo);

#endif /* CONCURRENCE_EXECUTOR_TEST_H_ */
