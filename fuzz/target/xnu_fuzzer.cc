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

#include <fuzzer/FuzzedDataProvider.h>
#include <google/protobuf/text_format.h>

#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "absl/debugging/symbolize.h"
#include "absl/flags/flag.h"
#include "absl/flags/marshalling.h"
#include "absl/flags/parse.h"
#include "absl/flags/usage.h"
#include "absl/log/initialize.h"
#include "absl/log/log.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"
#include "fuzz/common/utility.h"
#include "fuzz/handlers/session.h"
#include "fuzz/host/host.h"
#include "third_party/libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.h"

namespace absl::flags_internal {
enum class ArgvListAction;
enum class OnUndefinedFlag;
enum class UsageFlagsAction;
}  // namespace absl::flags_internal
namespace google::protobuf {
class Message;
}  // namespace google::protobuf

#ifdef LIMIT_CALLGRIND_SCOPE
#include <valgrind/callgrind.h>
#endif

extern "C" {

using proc_t = struct proc *;
using task_t = struct task *;

using boolean_t = int;
using ast_t = int;
}

extern int nprocs;

static std::string ProtobufToString(const google::protobuf::Message &message) {
  std::string result;
  google::protobuf::TextFormat::Printer printer;
  printer.SetHideUnknownFields(true);
  printer.PrintToString(message, &result);
  return result;
}

// This should be a plaintext Session protobuf. The commands will be kept constant
// as the scheduler and xnu data are fuzzed.
struct SingleTestcaseSession {
  explicit SingleTestcaseSession(std::optional<std::string> path)
      : path(std::move(path)) {}

  std::optional<std::string> path;
  Session session;
} __attribute__((packed)) __attribute__((aligned(128)));

std::string AbslUnparseFlag(const SingleTestcaseSession &testcase) {
  return absl::UnparseFlag(testcase.path);
}

bool AbslParseFlag(absl::string_view text, SingleTestcaseSession *testcase,
                   std::string *error) {
  // Check if path is provided
  // std::optional<std::string> path_option;
  if (!absl::ParseFlag(text, &testcase->path, error)) {
    return false;
  }
  if (!testcase->path.has_value()) {
    return true;
  }
  const std::string &path = testcase->path.value();

  // Read testcase data
  absl::StatusOr<std::vector<uint8_t>> testcase_bytes_or = ReadFile(path);
  if (!testcase_bytes_or.ok()) {
    *error = testcase_bytes_or.status().message();
    return false;
  }
  const auto &testcase_bytes = testcase_bytes_or.value();

  // Attempt to parse protobuf data
  constexpr bool binary = true;
  if (protobuf_mutator::libfuzzer::LoadProtoInput(
          !binary, testcase_bytes.data(), testcase_bytes.size(),
          &testcase->session)) {
    return true;
  }

  // See if a binary input was provided by accident
  // If so, print out a text version
  if (protobuf_mutator::libfuzzer::LoadProtoInput(binary, testcase_bytes.data(),
                                                  testcase_bytes.size(),
                                                  &testcase->session)) {
    *error = absl::StrFormat("Binary input provided for %s", path);
    std::string session_as_text = ProtobufToString(testcase->session);
    std::cerr << session_as_text;
  } else {
    *error = absl::StrFormat("Failed to parse protobuf input %s", path);
  }

  return false;
}

ABSL_FLAG(SingleTestcaseSession, testcase, SingleTestcaseSession(std::nullopt),
          "Fuzz only data_provider and scheduler fields for a given testcase");
ABSL_FLAG(std::optional<std::string>, write_text_protobuf, std::nullopt,
          "Write text protobuf to provided path from the testcase specified "
          "with --testcase.");
ABSL_FLAG(bool, verbose, false, "Enable verbose testcase output");

std::vector<char *> new_argv;
std::vector<std::unique_ptr<char[]>> flag_names_storage;

extern "C" int LLVMFuzzerInitialize(int *argc, char ***argv) {
  absl::SetProgramUsageMessage("use --helpfull to see options");

  std::vector<char *> positional_args;
  std::vector<absl::UnrecognizedFlag> unrecognized_flags;
  absl::ParseAbseilFlagsOnly(*argc, *argv, positional_args, unrecognized_flags);

  absl::InitializeSymbolizer(**argv);
  is_verbose = absl::GetFlag(FLAGS_verbose);
  absl::InitializeLog();
  InitializeHost();
#ifdef NDEBUG
  if (is_verbose) {
    LOG(FATAL) << "--verbose flag not supported with optimized builds";
  }
#endif

  new_argv.reserve(positional_args.size() + unrecognized_flags.size());

  int new_argc = 0;
  for (char *positional_arg : positional_args) {
    new_argv[new_argc++] = positional_arg;
  }

  for (const absl::UnrecognizedFlag &unrecognized_flag : unrecognized_flags) {
    std::string flag_name_with_dashes =
        absl::StrFormat("--%s", unrecognized_flag.flag_name);
    auto flag_name_with_dashes_storage =
        std::make_unique<char[]>(flag_name_with_dashes.size() + 1);
    memcpy(flag_name_with_dashes_storage.get(), flag_name_with_dashes.data(),
           flag_name_with_dashes.size() + 1);

    new_argv[new_argc++] = flag_name_with_dashes_storage.get();
    flag_names_storage.push_back(std::move(flag_name_with_dashes_storage));
  }

  *argv = new_argv.data();
  *argc = new_argc;

  return 0;
}

DEFINE_BINARY_PROTO_FUZZER(const Session &input_session) {
  const Session *session = &input_session;

#ifdef LIMIT_CALLGRIND_SCOPE
  CALLGRIND_START_INSTRUMENTATION;
  CALLGRIND_TOGGLE_COLLECT;
#endif

  // TODO(nedwill): these flag checks are costly and should not be compiled
  // in for large-scale fuzzing builds. We only want them when doing minimization
  // and PoC creation. We should have a separate build flag for that.
  auto testcase = absl::GetFlag(FLAGS_testcase);
  if (testcase.path.has_value()) {
    // Use XNU data provider and scheduler data with existing session.
    testcase.session.set_xnu_data_provider(input_session.xnu_data_provider());
    testcase.session.mutable_schedule()->set_rand_seed(
        input_session.schedule().rand_seed());
    testcase.session.mutable_schedule()->set_thread_choices(
        input_session.schedule().thread_choices());
    session = &testcase.session;
  }

  // TODO(nedwill): minimization only
  auto write_text_protobuf = absl::GetFlag(FLAGS_write_text_protobuf);
  if (write_text_protobuf.has_value()) {
    std::string path = write_text_protobuf.value();
    std::ofstream out(path);
    if (!out.is_open()) {
      std::cout << "Failed to open file for --write_text_protobuf: " << path
                << std::endl;
      return;
    }

    std::string text_output;
    if (!google::protobuf::TextFormat::PrintToString(*session, &text_output)) {
      std::cout << "Failed to convert protobuf to text format for "
                   "--write_text_protobuf"
                << std::endl;
      return;
    }

    out << text_output;
    if (!out) {
      std::cout << "Failed to write text protobuf to file: " << path
                << std::endl;
      return;
    }

    std::cout << "Successfully wrote text protobuf to: " << path << std::endl;
  }

  if (is_verbose) {
    std::cout << ProtobufToString(*session);
  }

  HandleSession(session);
}
