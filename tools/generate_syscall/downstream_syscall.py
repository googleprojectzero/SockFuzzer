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

import re
import textwrap
from typing import List
from sockfuzzer.tools.generate_syscall.downstream_field import Field
from sockfuzzer.tools.generate_syscall.downstream_syscall_parser import parse_syscall


class DownstreamSyscall:
    name: str
    fields: List[Field]

    def __init__(self, name, fields):
        self.name = name
        self.fields = fields

    @classmethod
    def from_line(cls, line):
        name, fields = parse_syscall(line)
        return cls(name, fields)

    def field_by_name(self, name):
        for field in self.fields:
            if field.name == name:
                return field
        raise KeyError("Field not found:", name)

    @property
    def capitalized_name(self):
        words = self.name.replace("_", " ").split()
        return "".join(word.capitalize() for word in words)

    @property
    def wrapper_name(self):
        return self.name + "_wrapper"

    @property
    def proto_message_name(self):
        return self.capitalized_name + "Message"

    @property
    def proto_message_body(self):
        body = ""
        i = 1
        for field in self.fields:
            entry = field.as_proto_message_type(self)
            if len(entry) == 0:
                continue
            body += f"{entry} {field.name} = {i};\n"
            i += 1
        return body

    @property
    def proto_message(self):
        message = "message " + self.proto_message_name + " {\n"
        message += textwrap.indent(self.proto_message_body, "  ")
        message += "}\n"
        return message

    @property
    def proto_syscall_field(self):
        return self.proto_message_name + " " + self.name

    @property
    def caller_case(self):
        return "case BsdSyscall::k" + self.capitalized_name + ": {\n"

    @property
    def caller_args(self):
        args = []
        for field in self.fields:
            cast = ""
            if field.cast is not None:
                cast = f"({field.cast})"
            args.append(cast + field.as_caller_arg(self))
        return ", ".join(args)

    @property
    def caller_call(self):
        return self.wrapper_name + "(" + self.caller_args + ");\n"

    @property
    def caller_case_block(self):
        out = "auto args = syscall." + self.name + "();\n"

        for field in reversed(self.fields):
            if not field.has_dependency():
                out += field.as_caller_setup(self)

        for field in reversed(self.fields):
            if field.has_dependency():
                out += field.as_caller_setup(self)

        out += self.caller_call
        for field in self.fields:
            out += field.as_caller_cleanup(self)
        out += "break;\n"
        return out

    @property
    def calling_code(self):
        out = self.caller_case
        out += textwrap.indent(self.caller_case_block, "  ")
        out += "}\n"
        return out
