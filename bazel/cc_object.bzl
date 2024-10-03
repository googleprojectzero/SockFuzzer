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

# cmd = "ld.lld -r -o $@ $(SRCS)",
# cmd = "objcopy --localize-hidden $< $@",

load("@bazel_tools//tools/cpp:toolchain_utils.bzl", "find_cpp_toolchain")

def _cc_object_impl(ctx):
    cc_toolchain = find_cpp_toolchain(ctx)
    prelinked_object = ctx.actions.declare_file("{}_prelinked".format(ctx.label.name))
    final_object = ctx.actions.declare_file(ctx.label.name)
    redefine_syms_file = ctx.file.redefine_syms

    if not redefine_syms_file:
        fail("Attribute redefine_syms is required and must be a single file")

    link_args = ctx.actions.args()

    # TODO(nedwill): Consider simply redefining syms in the relevant
    # dependent objects and forwarding them without actually prelinking
    # all of them. This change could speed up compile times and improve link
    # time optimization.
    link_args.add("-r")
    link_args.add("-o", prelinked_object)

    # Add deps
    linker_input_paths = []
    for dep in ctx.attr.deps:
        for linker_input in dep[CcInfo].linking_context.linker_inputs.to_list():
            for library in linker_input.libraries:
                linker_input_paths.extend(library.pic_objects)
    link_args.add_all(linker_input_paths)

    ctx.actions.run(
        mnemonic = "PartialLink",
        executable = cc_toolchain.ld_executable,
        arguments = [link_args],
        inputs = depset(
            direct = linker_input_paths,
            transitive = [
                cc_toolchain.all_files,
            ],
        ),
        outputs = [prelinked_object],
    )

    redefine_syms_args = ctx.actions.args()
    redefine_syms_args.add("--redefine-syms")
    redefine_syms_args.add(redefine_syms_file)
    redefine_syms_args.add(prelinked_object)
    redefine_syms_args.add(final_object)
    ctx.actions.run(
        mnemonic = "RedefineSymbols",
        executable = cc_toolchain.objcopy_executable,
        arguments = [redefine_syms_args],
        inputs = [prelinked_object, redefine_syms_file],
        outputs = [final_object],
    )

    return [DefaultInfo(files = depset([final_object]))]

cc_object = rule(
    implementation = _cc_object_impl,
    attrs = {
        "deps": attr.label_list(providers = [CcInfo]),
        "redefine_syms": attr.label(allow_single_file = True),
        "_cc_toolchain": attr.label(default = Label("@bazel_tools//tools/cpp:current_cc_toolchain")),
    },
    incompatible_use_toolchain_transition = True,
    fragments = ["cpp"],
    toolchains = ["@bazel_tools//tools/cpp:toolchain_type"],
)
