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

#include "backtrace.h"

#include <array>
#include <vector>

#include "absl/debugging/stacktrace.h"
#include "absl/debugging/symbolize.h"

class StackTraceImpl {
public:
    std::vector<void*> stacktrace;
};

StackTrace::StackTrace() : impl_(new StackTraceImpl) {
    std::array<void *, 10> result{};
    std::array<int, 10> sizes{};
    int depth =
        absl::GetStackFrames(result.data(), sizes.data(), result.size(), 1);
    impl_->stacktrace = std::vector<void *>(result.data(), result.data() + depth);
}

StackTrace::~StackTrace() = default;

void StackTrace::Print() const {
  for (const void *pc : impl_->stacktrace) {
    std::array<char, 256> symbol{};
    absl::Symbolize(const_cast<void *>(pc), symbol.data(), symbol.size());
    printf("pc=%p %s\n", pc, symbol.data());
  }
}

bool StackTrace::Empty() const {
    return impl_->stacktrace.empty();
}
