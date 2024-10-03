# Copyright 2024 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

def _asan_dbg_transition_impl(settings, _attrs):
    return {
        "//command_line_option:copt": settings["//command_line_option:copt"] + ['-fsanitize=address'],
        "//command_line_option:linkopt": settings["//command_line_option:linkopt"] + ['-fsanitize=address'],
        "//command_line_option:compilation_mode": "dbg",
        "//command_line_option:platform_suffix": "asan",
    }

asan_dbg_transition = transition(
    implementation = _asan_dbg_transition_impl,
    inputs = [
        "//command_line_option:copt",
        "//command_line_option:linkopt",
        "//command_line_option:compilation_mode",
    ],
    outputs = [
        "//command_line_option:copt",
        "//command_line_option:linkopt",
        "//command_line_option:compilation_mode",
        "//command_line_option:platform_suffix",
    ],
)

def _asan_cc_binary_impl(ctx):
    cc_binary_target = ctx.attr.cc_binary_target[0]
    return [DefaultInfo(files = cc_binary_target.default_runfiles.files)]

asan_cc_binary = rule(
    implementation = _asan_cc_binary_impl,
    attrs = {
        "cc_binary_target": attr.label(cfg = asan_dbg_transition, executable = True, allow_single_file = True),
        "_allowlist_function_transition": attr.label(
            default = "@bazel_tools//tools/allowlists/function_transition_allowlist"
        ),
    },
)
