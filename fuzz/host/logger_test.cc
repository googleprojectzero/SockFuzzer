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

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "fuzz/host/logger.h"

class MockLogger : public Logger {
public:
  explicit MockLogger(LoggerDetail* detail) : Logger(detail) {}
  MOCK_METHOD(std::string, GenerateNameFromPointer, (const void* ptr), (override));
};

class MockLoggerDetail : public LoggerDetail {
public:
  explicit MockLoggerDetail(std::ostream* out) : LoggerDetail(out) {}
  MOCK_METHOD(void, Log, (absl::string_view string), (override));
};

TEST(LoggerTest, ExtractPointers) {
  MockLoggerDetail detail(nullptr);
  MockLogger logger(&detail);

  auto result = logger.FormatWithPointersForTesting("test [ptr:0x1] [ptr:(nil)] [ptr:0xFFFFFFFF]");
  ASSERT_TRUE(result.ok());
  EXPECT_THAT(*result, testing::HasSubstr("0x1"));
  EXPECT_THAT(*result, testing::HasSubstr("(nil)"));
  EXPECT_THAT(*result, testing::HasSubstr("0xffffffff"));

  result = logger.FormatWithPointersForTesting("invalid [ptr:not_a_pointer]");
  ASSERT_FALSE(result.ok());
}

TEST(LoggerTest, FormatExtractedPointers) {
  MockLoggerDetail detail(nullptr);
  MockLogger logger(&detail);
  EXPECT_CALL(logger, GenerateNameFromPointer(reinterpret_cast<const void*>(1)))
      .WillOnce(testing::Return("one"));
  EXPECT_CALL(logger, GenerateNameFromPointer(reinterpret_cast<const void*>(0xFFFFFFFF)))
      .WillOnce(testing::Return("max"));

  auto result = logger.FormatWithPointersForTesting("test [ptr:0x1] middle [ptr:(nil)] end [ptr:0xFFFFFFFF]");
  ASSERT_TRUE(result.ok());
  EXPECT_EQ(*result, "test 0x1 (one) middle (nil) end 0xffffffff (max)");
}

TEST(LoggerTest, FormatWithPointersIntegration) {
  MockLoggerDetail detail(nullptr);
  MockLogger logger(&detail);
  EXPECT_CALL(logger, GenerateNameFromPointer(testing::_))
      .WillOnce(testing::Return("mock_name"));

  auto result = logger.FormatWithPointersForTesting("test [ptr:0x1234] middle [ptr:(nil)]");
  ASSERT_TRUE(result.ok());
  EXPECT_EQ(*result, "test 0x1234 (mock_name) middle (nil)");
}