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

#ifndef FUZZ_HOST_LOG_H_
#define FUZZ_HOST_LOG_H_

#include <cstdarg>
#include <random>

#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"
#include "fuzz/host/hypercall/types.h"

class LoggerDetail {
 public:
  explicit LoggerDetail(std::ostream* out) : out_(out) {}
  void SetOutputStream(std::ostream* out) { out_ = out; }

  virtual ~LoggerDetail() = default;
  // Implementers must use the provided `out_` ostream to log the string.
  virtual void Log(absl::string_view string) = 0;

 protected:
  std::ostream* out_;
};

class Logger {
 public:
  explicit Logger(LoggerDetail* detail);
  virtual ~Logger();

  void Log(enum log_subsystem subsystem, absl::string_view string);

  template <typename... Args>
  void Log(enum log_subsystem subsystem,
           const absl::FormatSpec<Args...>& format, const Args&... args);

  absl::StatusOr<std::string> FormatWithPointers(const char* format,
                                                 va_list args);

  // For testing purposes
  absl::StatusOr<std::string> FormatWithPointersForTesting(const std::string& formatted);

  void EnableSubsystem(enum log_subsystem subsystem) {
    subsystems_[subsystem] = true;
  }

  void DisableSubsystem(enum log_subsystem subsystem) {
    subsystems_[subsystem] = false;
  }

  void Enable() { enabled_ = true; }

  bool Enabled() const { return enabled_; }

  void Disable() { enabled_ = false; }

 private:
  static std::string ReplacePointerPlaceholders(const char* format);
  static absl::StatusOr<std::vector<absl::StatusOr<uintptr_t>>> ExtractPointers(const std::string& formatted);
  std::string FormatExtractedPointers(const std::string& formatted, const std::vector<absl::StatusOr<uintptr_t>>& pointers);

  size_t GetRandomIndexForPointerName();
  virtual std::string GenerateNameFromPointer(const void* ptr);

  LoggerDetail* detail_;
  absl::flat_hash_map<enum log_subsystem, bool> subsystems_{};
  bool enabled_{};
  std::mt19937 pointer_names_prng_;
  absl::flat_hash_map<const void*, std::string> pointer_names_;
  absl::flat_hash_set<std::string> pointer_names_used_;
};

template <typename... Args>
void Logger::Log(enum log_subsystem subsystem,
                 const absl::FormatSpec<Args...>& format, const Args&... args) {
#ifndef NDEBUG
  if (!enabled_ || !subsystems_[subsystem]) {
    return;
  }
  Log(subsystem, absl::StrFormat(format, args...));
#endif
}

#endif /* FUZZ_HOST_LOG_H_ */
