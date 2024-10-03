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

from dataclasses import dataclass
from typing import List
import re
import textwrap


@dataclass
class ParsedArgument:
    type_: str
    raw_name: str
    syscall_name: str

    @property
    def name(self):
        if self.raw_name in [self.syscall_name, "new", "class"]:
            return self.raw_name + "_arg"
        return self.raw_name

    def as_decl_argument(self):
        type_ = self.type_
        if type_ == "sem_t *":
            type_ = "fuzz_sem_t *"
        if type_ == "idtype_t":
            type_ = "fuzz_idtype_t"
        if type_ == "semun_t":
            type_ = "user_addr_t"
        if type_ == "const struct sigset_t *":
            type_ = "u_int32_t *"
        if type_ == "struct timezone *":
            type_ = "struct fuzz_timezone *"
        if type_.endswith("*"):
            arg = type_ + self.name
        else:
            arg = type_ + " " + self.name
        return arg

    def as_struct_field_assignment(self):
        cast = ""
        suffix = ""
        if self.type_ in (
            "caddr_t",
            "idtype_t",
            "semun_t",
            "uuid_t",
        ) or self.type_.endswith("*"):
            cast = "(user_addr_t) "
        return f".{self.raw_name} = {cast}{self.name}{suffix},"


@dataclass
class CompilerFlags:
    # These probably don't need to be lists
    defined: List[str]
    undefined: List[str]


@dataclass
class UpstreamSyscall:
    number: int
    name: str
    args: List[ParsedArgument]
    return_type: str
    call: str
    comment: str
    compiler_flags: CompilerFlags

    @classmethod
    def from_line(cls, line, defined_flag, undefined_flag):
        # We are thus parsing a syscall. Example:
        # 33 AUE_ACCESS ALL { int access(user_addr_t path, int flags); }
        # It has approximately the following form:
        # [number] [?] [?] [raw] [comment]
        # where [raw] = { [return_type] [name]([args...]); }
        line = line.replace("\t", " ")
        number = int(line.split()[0])
        call = line[line.index("{") : line.index("}") + 1]
        match = re.match(r"\{\s*(\w+)\s*(\w+)\s*\((.*)\).*", call)
        if match is None:
            raise ValueError(f"Failed to parse {call}")
        return_type, name, args_raw = match.groups()
        args = []
        if args_raw != "void":
            for arg in args_raw.split(","):
                arg = arg.strip()
                arg_name_start = max(arg.rfind(" "), arg.rfind("*")) + 1
                assert arg_name_start > 0
                arg_type, arg_name = arg[:arg_name_start], arg[arg_name_start:]
                args.append(ParsedArgument(arg_type.strip(), arg_name.strip(), name))
        comment = line[line.index("}") + 1 :].strip()
        compiler_flags = CompilerFlags(
            [defined_flag] if defined_flag is not None else [],
            [undefined_flag] if undefined_flag is not None else [],
        )
        return cls(number, name, args, return_type, call, comment, compiler_flags)

    @property
    def wrapper_name(self):
        return self.name + "_wrapper"

    @property
    def all_args(self):
        if self.name == "exit":
            ret_arg = ParsedArgument("int *", "retval", self.name)
        else:
            ret_arg = ParsedArgument(self.return_type + " *", "retval", self.name)
        return self.args + [ret_arg]

    @property
    def wrapper_decl(self):
        args = ", ".join(arg.as_decl_argument() for arg in self.all_args)
        return f"int {self.wrapper_name}({args})"

    @property
    def wrapper_struct_name(self):
        if self.name.startswith("sys_"):
            return self.name[4:] + "_args"
        return self.name + "_args"

    @property
    def wrapper_struct(self):
        struct = "struct " + self.wrapper_struct_name + " args = {\n"
        for arg in self.args:
            if arg.name == "retval":
                continue
            struct += "  " + arg.as_struct_field_assignment() + "\n"
        struct += "};\n"
        return struct

    @property
    def wrapper_real_call(self):
        retval_cast = ""
        if self.name.startswith("psynch") and self.name not in (
            "psynch_rw_downgrade",
            "psynch_cvclrprepost",
        ):
            retval_cast = "(unsigned int *) "
        if self.name == "audit_session_self":
            retval_cast = "(unsigned int *) "
        return self.name + "(current_proc(), &args, " + retval_cast + "retval)"

    @property
    def wrapper_call_and_return(self):
        if self.return_type == "void":
            return f"{self.wrapper_real_call};\nreturn 0;\n"
        return f"return {self.wrapper_real_call};\n"

    @property
    def wrapper_body(self):
        return self.wrapper_struct + self.wrapper_call_and_return

    @property
    def wrapper_impl(self):
        wrapper = self.wrapper_decl + " {\n"
        wrapper += textwrap.indent(self.wrapper_body, "  ")
        wrapper += "}\n"
        return wrapper

    @property
    def def_entry(self):
        args = ", ".join(arg.as_decl_argument() for arg in self.all_args)
        return f"{self.name}({args})"
