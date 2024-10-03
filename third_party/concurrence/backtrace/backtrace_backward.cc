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
#include "third_party/backward-cpp/backward.hpp"

class StackTraceImpl {
public:
    backward::StackTrace stacktrace;
};

StackTrace::StackTrace() : impl_(new StackTraceImpl) {
    impl_->stacktrace.load_here(32);
}

StackTrace::~StackTrace() = default;

void StackTrace::Print() const {
    backward::Printer printer;
    printer.color_mode = backward::ColorMode::type::always;
    printer.print(impl_->stacktrace);
}

bool StackTrace::Empty() const {
    return impl_->stacktrace.size() == 0;
}
