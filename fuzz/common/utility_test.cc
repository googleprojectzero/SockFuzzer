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

#include "fuzz/common/utility.h"

#include <gtest/gtest.h>

TEST(VectorDumpTest, BasicTest) {
  std::vector<uint8_t> v = {1, 2, 3, 4, 5};
  EXPECT_EQ("{1, 2, 3, 4, 5}", DumpVector(v));
}

TEST(VectorDumpTest, EmptyTest) {
  std::vector<uint8_t> v;
  EXPECT_EQ("{}", DumpVector(v));
}

TEST(VectorDumpTest, LargeTest) {
  std::vector<uint8_t> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ("{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}", DumpVector(v));
}
