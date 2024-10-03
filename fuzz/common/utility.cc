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

#include <cstdarg>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>

#include "absl/status/statusor.h"
#include "absl/strings/str_format.h"

absl::StatusOr<std::vector<uint8_t>> ReadFile(const std::string& filename) {
  if (!std::filesystem::exists(filename)) {
    return absl::NotFoundError("File does not exist: " + filename);
  }
  std::ifstream input_fstream(filename, std::ios::binary);
  return std::vector<uint8_t>(std::istreambuf_iterator<char>(input_fstream),
                              std::istreambuf_iterator<char>());
}

std::string DumpVector(const std::vector<uint8_t>& data) {
  std::stringstream out;
  out << "{";
  for (auto it = data.begin(); it != data.end(); ++it) {
    if (it != data.begin()) {
      out << ", ";
    }
    out << std::to_string(*it);
  }
  out << "}";
  return out.str();
}
