# Copyright 2024 Google LLC
# 
# @APPLE_OSREFERENCE_LICENSE_HEADER_START@
# 
# This file contains Original Code and/or Modifications of Original Code
# as defined in and that are subject to the Apple Public Source License
# Version 2.0 (the 'License'). You may not use this file except in
# compliance with the License. The rights granted to you under the License
# may not be used to create, or enable the creation or redistribution of,
# unlawful or unlicensed copies of an Apple operating system, or to
# circumvent, violate, or enable the circumvention or violation of, any
# terms of an Apple operating system software license agreement.
# 
# Please obtain a copy of the License at
# http://www.opensource.apple.com/apsl/ and read it before using this file.
# 
# The Original Code and all software distributed under the License are
# distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
# EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
# INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
# Please see the License for the specific language governing rights and
# limitations under the License.
# 
# @APPLE_OSREFERENCE_LICENSE_HEADER_END@

"""
Parses syscalls.master in UpstreamSyscalls and writes syscall_wrappers.h/cc

Filters the UpstreamSyscalls based on compiler flags and explicitly ignored names
"""
from tools.generate_syscall.upstream_syscall import UpstreamSyscall
from typing import List, IO
import os
import sys
import textwrap

debug_enabled = os.environ.get("GENERATE_SYSCALL_DEBUG", "0") == "1"


def parse_syscalls(file: IO[str]) -> List[UpstreamSyscall]:
    """
    Read file and return a list of UpstreamSyscalls.

    file should be in the format of xnu/bsd/kern/syscall.master.
    """
    defined_flag = None  # flag within an if block
    undefined_flag = None  # previous if flag when in an else block

    parsed_syscalls = []

    for line in file.readlines():
        line = line.strip()
        if len(line) == 0:
            # empty
            continue
        if line.startswith(";"):
            # comment
            continue
        if line.startswith("#include"):
            # no thanks
            continue
        if line.startswith("#if"):
            # entering if block
            defined_flag = line.split()[1]
            continue
        if line.startswith("#else"):
            # entering an else block
            assert defined_flag is not None
            undefined_flag = defined_flag
            defined_flag = None
            continue
        if line.startswith("#endif"):
            # exiting else block
            assert defined_flag is None  # does every if have an else?
            undefined_flag = None
            continue

        parsed = UpstreamSyscall.from_line(line, defined_flag, undefined_flag)

        parsed_syscalls.append(parsed)
    return parsed_syscalls


def filter_syscalls(
    syscalls: List[UpstreamSyscall], defined_flags: List[str], delete_names: List[str]
) -> List[UpstreamSyscall]:
    filtered = []
    for syscall in syscalls:
        if syscall.name in delete_names:
            continue
        required_flags = syscall.compiler_flags.defined
        if any(required not in defined_flags for required in required_flags):
            continue
        banned_flags = syscall.compiler_flags.undefined
        if any(banned in defined_flags for banned in banned_flags):
            continue
        filtered.append(syscall)
    return filtered


class UpstreamSyscallManager:
    """
    Syscalls sourced from syscalls.master
    """

    def __init__(self, syscalls: List[UpstreamSyscall]):
        self.syscalls = {}
        for syscall in syscalls:
            self.syscalls[syscall.name] = syscall

    @classmethod
    def from_path(cls, path, flags, delete_names):
        with open(path, "r") as syscall_master_file:
            parsed_syscalls = parse_syscalls(syscall_master_file)
        # Only print these if enabled by the user via the environment
        if debug_enabled:
            print(f"Parsed {len(parsed_syscalls)} syscalls from {path}")
            print(f"Filtering with flags: {flags}")
            print(f"Deleting syscalls: {delete_names}")

        syscalls = filter_syscalls(parsed_syscalls, flags, delete_names)
        if debug_enabled:
            print(f"After filtering: {len(syscalls)} syscalls remain")
        return cls(syscalls)

    def find(self, name):
        if name not in self.syscalls:
            if debug_enabled:
                print(f"Syscall '{name}' not found.")
                print(f"Total available syscalls: {len(self.syscalls)}")
                print("First 10 available syscalls:")
                for key in list(self.syscalls.keys())[:10]:
                    print(f"  {key}")
                print("...")
            return None
        return self.syscalls[name]

    def write_wrappers_header(self, out, header_preamble):
        preamble = """\
        // Autogenerated by generate_wrappers.py

        #ifndef SYSCALL_WRAPPERS_H_
        #define SYSCALL_WRAPPERS_H_

        #ifdef __cplusplus
        extern "C" {
        #endif
        """
        preamble += header_preamble.read()
        output = textwrap.dedent(preamble)

        for syscall in self.syscalls.values():
            output += syscall.wrapper_decl + ";\n"

        output += """
        #ifdef __cplusplus
        }
        #endif
        """

        output += "\n#endif  // SYSCALL_WRAPPERS_H_\n"
        out.write(output)

    def write_wrappers(self, out):
        preamble = """\
        // Autogenerated by generate_wrappers.py

        #include "syscall_wrappers_generated.h"

        """
        output = textwrap.dedent(preamble)

        for syscall in self.syscalls.values():
            output += syscall.wrapper_impl
        out.write(output)

    def write_defs(self, out):
        preamble = """\
        # Autogenerated by generate_wrappers.py

        # Manually override types to work with generate_callers

        """
        output = textwrap.dedent(preamble)

        for syscall in self.syscalls.values():
            output += syscall.def_entry + "\n"
        out.write(output)


if __name__ == "__main__":

    import argparse

    parser = argparse.ArgumentParser(
        description="Generate wrappers based on syscall.master"
    )
    parser.add_argument(
        "-i",
        dest="input",
        required=True,
        metavar="FILE",
        help="Path to syscalls.master.",
    )
    parser.add_argument(
        "-D",
        dest="flags",
        action="append",
        help="Define a compiler flag for filtering syscalls.",
    )
    parser.add_argument(
        "-x",
        dest="delete_names",
        action="append",
        help="Remove syscalls with the provided name.",
    )
    parser.add_argument(
        "--defs",
        dest="defs",
        metavar="FILE",
        help="Path to save syscall defintions for manual typing.",
    )
    parser.add_argument(
        "--wrappers",
        dest="wrappers",
        metavar="FILE",
        help="Path to save wrappers",
    )
    parser.add_argument(
        "--wrappers_header",
        dest="wrappers_header",
        metavar="FILE",
        help="Path to save wrappers header",
    )
    parser.add_argument(
        "--wrappers_header_preamble",
        dest="wrappers_header_preamble",
        metavar="FILE",
        help="Path to file containing preamble for wrappers_header",
    )
    args = parser.parse_args()

    upstream_syscalls = UpstreamSyscallManager.from_path(
        args.input, args.flags, args.delete_names
    )
    if upstream_syscalls is None:
        print(f"Failed to parse {args.input}")
        sys.exit(1)

    if args.wrappers_header:
        assert args.wrappers_header_preamble
        with open(args.wrappers_header_preamble) as header_preamble:
            with open(args.wrappers_header, "w") as out:
                upstream_syscalls.write_wrappers_header(out, header_preamble)

    if args.wrappers:
        with open(args.wrappers, "w") as out:
            upstream_syscalls.write_wrappers(out)

    if args.defs:
        with open(args.defs, "w") as out:
            upstream_syscalls.write_defs(out)
