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

def _generic_transition_impl(settings, attrs):
    return {
        "//command_line_option:copt": settings["//command_line_option:copt"] + attrs.copts,
        "//command_line_option:linkopt": settings["//command_line_option:linkopt"] + attrs.linkopts,
        "//command_line_option:compilation_mode": attrs.compilation_mode,
        "//command_line_option:platform_suffix": attrs.platform_suffix,
    }

generic_transition = transition(
    implementation = _generic_transition_impl,
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

def _generic_cc_binary_impl(ctx):
    cc_binary_target = ctx.attr.cc_binary_target[0]
    output_binary = ctx.actions.declare_file(ctx.label.name)
    ctx.actions.run_shell(
        inputs = cc_binary_target.files.to_list(),
        outputs = [output_binary],
        command = "cp $1 $2",
        arguments = [cc_binary_target.files.to_list()[0].path, output_binary.path],
    )
    return [DefaultInfo(files = depset([output_binary]))]

generic_cc_binary = rule(
    implementation = _generic_cc_binary_impl,
    attrs = {
        "cc_binary_target": attr.label(cfg = generic_transition, executable = True, allow_single_file = True),
        "copts": attr.string_list(default = ['-fsanitize=address']),
        "linkopts": attr.string_list(default = ['-fsanitize=address']),
        "compilation_mode": attr.string(default = "dbg"),
        "platform_suffix": attr.string(default = "asan"),
        "_allowlist_function_transition": attr.label(
            default = "@bazel_tools//tools/allowlists/function_transition_allowlist"
        ),
    },
)
