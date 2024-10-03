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

"""
Helpers for MIG code generation
"""

load("@bazel_tools//tools/cpp:toolchain_utils.bzl", "find_cpp_toolchain")

def _preprocess_mig_defs_impl(ctx):
    cc_toolchain = find_cpp_toolchain(ctx)
    output_names = []
    for src in ctx.files.srcs:
        base_name = src.basename.replace(".defs", "")
        output_name = ctx.actions.declare_file("{}.c".format(base_name))
        output_names.append(output_name)

        cc_binary = cc_toolchain.compiler_executable

        ctx.actions.run_shell(
            inputs = [src] + ctx.files.headers + ctx.files.defs,
            outputs = [output_name],
            command = "{} -xc -E {} -DKERNEL -DKERNEL_SERVER -I third_party/xnu/osfmk > {}".format(
                cc_binary,
                src.path,
                output_name.path,
            ),
        )

    return [DefaultInfo(files = depset(output_names))]

preprocess_mig_defs = rule(
    implementation = _preprocess_mig_defs_impl,
    attrs = {
        "srcs": attr.label_list(allow_files = True),
        "headers": attr.label_list(allow_files = True),
        "defs": attr.label_list(allow_files = True),
        "_cc_toolchain": attr.label(default = Label("@bazel_tools//tools/cpp:current_cc_toolchain")),
    },
    toolchains = ["@bazel_tools//tools/cpp:toolchain_type"],
)
