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

#include "fuzz/host/logger.h"

#include <cstdio>
#include <vector>

#include "absl/strings/str_replace.h"
#include "absl/strings/str_split.h"
#include "absl/strings/numbers.h"
#include "fuzz/host/words/adjectives.h"
#include "fuzz/host/words/nouns.h"

Logger::Logger(LoggerDetail* detail)
    : detail_(detail),
      pointer_names_prng_(1234) {}

Logger::~Logger() = default;

void Logger::Log(enum log_subsystem subsystem, absl::string_view string) {
  if (subsystem == TICKET_LOCK) {
    return;
  }
#ifndef NDEBUG
  detail_->Log(string);
#else
  (void)detail_;
#endif
}

std::string Logger::ReplacePointerPlaceholders(const char* format) {
  return absl::StrReplaceAll(format, {{"%p", "[ptr:%p]"}});
}

absl::StatusOr<std::vector<absl::StatusOr<uintptr_t>>> Logger::ExtractPointers(const std::string& formatted) {
  std::vector<absl::StatusOr<uintptr_t>> pointers;
  std::vector<std::string> tokens = absl::StrSplit(formatted, absl::ByString("[ptr:"));

  for (size_t i = 1; i < tokens.size(); ++i) {
    std::vector<std::string> parts = absl::StrSplit(tokens[i], absl::MaxSplits(']', 1));
    if (parts.size() != 2) {
      return absl::InvalidArgumentError(absl::StrFormat("Invalid pointer token: %s", tokens[i]));
    }

    if (parts[0] == "(nil)") {
      pointers.push_back(0);
    } else {
      try {
        unsigned long long value;
        if (absl::StartsWith(parts[0], "0x") || absl::StartsWith(parts[0], "0X")) {
          value = std::stoull(parts[0], nullptr, 16);
        } else {
          value = std::stoull(parts[0], nullptr, 10);
        }
        
        if (value <= std::numeric_limits<uintptr_t>::max()) {
          pointers.push_back(static_cast<uintptr_t>(value));
        } else {
          return absl::InvalidArgumentError(absl::StrFormat("Pointer value out of range: %s", parts[0]));
        }
      } catch (const std::exception& e) {
        return absl::InvalidArgumentError(absl::StrFormat("Invalid pointer value: %s (%s)", parts[0], e.what()));
      }
    }
  }

  return pointers;
}

std::string Logger::FormatExtractedPointers(const std::string& formatted, const std::vector<absl::StatusOr<uintptr_t>>& pointers) {
  std::string result;
  std::vector<std::string> tokens = absl::StrSplit(formatted, absl::ByString("[ptr:"));
  result = tokens[0];

  for (size_t i = 0; i < pointers.size(); ++i) {
    std::vector<std::string> parts = absl::StrSplit(tokens[i + 1], absl::MaxSplits(']', 1));
    if (pointers[i].ok()) {
      uintptr_t value = pointers[i].value();
      if (value == 0) {
        result += "(nil)" + parts[1];
      } else {
        result += absl::StrFormat("%#lx (%s)%s", static_cast<unsigned long>(value), 
                                  GenerateNameFromPointer(reinterpret_cast<const void*>(value)), 
                                  parts[1]);
      }
    } else {
      result += "[ptr:" + tokens[i + 1];
    }
  }

  return result;
}

absl::StatusOr<std::string> Logger::FormatWithPointers(const char* format, va_list args) {
  // Replace all occurrences of %p with [ptr:%p] in the format string
  std::string modified_format = ReplacePointerPlaceholders(format);

  // Use vsnprintf to format the string with the provided arguments
  std::vector<char> buffer(1024);  // Start with a 1KB buffer
  va_list args_copy;
  va_copy(args_copy, args);
  int result = vsnprintf(buffer.data(), buffer.size(), modified_format.c_str(), args_copy);
  va_end(args_copy);

  if (result < 0) {
    return absl::InvalidArgumentError("Error in vsnprintf");
  }

  if (static_cast<size_t>(result) >= buffer.size()) {
    // If the initial buffer was too small, resize it and try again
    buffer.resize(result + 1);
    va_copy(args_copy, args);
    result = vsnprintf(buffer.data(), buffer.size(), modified_format.c_str(), args_copy);
    va_end(args_copy);

    if (result < 0 || static_cast<size_t>(result) >= buffer.size()) {
      return absl::InvalidArgumentError("Error in vsnprintf after resize");
    }
  }

  // Now that we have the formatted string, we can use FormatWithPointersForTesting
  return FormatWithPointersForTesting(std::string(buffer.data(), result));
}

absl::StatusOr<std::string> Logger::FormatWithPointersForTesting(const std::string& formatted) {
  auto extracted_pointers = ExtractPointers(formatted);
  if (!extracted_pointers.ok()) {
    return extracted_pointers.status();
  }

  return FormatExtractedPointers(formatted, *extracted_pointers);
}

size_t Logger::GetRandomIndexForPointerName() {
  const size_t num_names = adjectives.size() * nouns.size();
  std::uniform_int_distribution<> distribution(0, num_names - 1);
  return distribution(pointer_names_prng_);
}

std::string Logger::GenerateNameFromPointer(const void* ptr) {
  auto iter = pointer_names_.find(ptr);
  if (iter != pointer_names_.end()) {
    return iter->second;
  }

  while (true) {
    size_t index = GetRandomIndexForPointerName();
    std::string name = absl::StrFormat(
        "%s_%s", adjectives[index % adjectives.size()],
        absl::AsciiStrToLower(
            nouns[(index / adjectives.size()) % nouns.size()]));

    if (pointer_names_used_.contains(name)) {
      continue;
    }
    pointer_names_used_.insert(name);
    pointer_names_[ptr] = name;
    return name;
  }
}