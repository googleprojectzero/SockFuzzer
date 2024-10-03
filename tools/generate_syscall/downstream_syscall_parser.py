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

from __future__ import annotations
import re
from typing import List, Tuple, Union
from sockfuzzer.tools.generate_syscall.downstream_field import FIELD_CLASSES, Field

# <syscall_def> ::= <identifier> ( <arg_list> )
# <arg_list> ::= <arg> | <arg> , <arg_list>
# <arg> ::= <type> <identifier>
# <type> ::= <basic_type> | <basic_type> [ <type_args> ]
# <basic_type> ::= any key in FIELD_CLASSES
# <type_args> ::= <type_arg> | <type_arg> , <type_args>
# <type_arg> ::= <attr_identifier> = <value>
# <value> ::= <type> | <integer_literal> | " <string_literal> "


class BasicType:
    def __init__(self, name: str):
        self.name = name

    def __eq__(self, other):
        return self.name == other.name

    def __repr__(self):
        return f"BasicType({self.name!r})"

    def __str__(self):
        return self.name


class TypeArg:
    def __init__(self, attr_identifier: str, value: str | int | Type):
        self.attr_identifier = attr_identifier
        self.value = value

    def __eq__(self, other):
        return (
            self.attr_identifier == other.attr_identifier and self.value == other.value
        )

    def __repr__(self):
        return f"TypeArg({self.attr_identifier!r}, {self.value!r})"

    def __str__(self):
        return f"{self.attr_identifier}={self.value}"


class Type:
    def __init__(self, basic_type: BasicType, type_args: List[TypeArg]):
        self.basic_type = basic_type
        self.type_args = type_args

    def __eq__(self, other):
        return self.basic_type == other.basic_type and self.type_args == other.type_args

    def __repr__(self):
        return f"Type({self.basic_type!r}, {self.type_args!r})"

    def __str__(self):
        type_args_str = (
            f"[{', '.join(str(arg) for arg in self.type_args)}]"
            if self.type_args
            else ""
        )
        return f"{self.basic_type}{type_args_str}"

    def as_field(self, name=None) -> Field:
        field_cls = FIELD_CLASSES[self.basic_type.name]
        kwargs = {}
        for type_arg in self.type_args:
            if isinstance(type_arg.value, Type):
                kwargs[type_arg.attr_identifier] = type_arg.value.as_field(name)
            else:
                kwargs[type_arg.attr_identifier] = type_arg.value
        kwargs["name"] = name
        return field_cls(**kwargs)

class Argument:
    def __init__(self, type: Type, identifier: str):
        self.type = type
        self.identifier = identifier

    def __str__(self):
        type_args_str = (
            f"[{', '.join(str(arg) for arg in self.type.type_args)}]"
            if self.type.type_args
            else ""
        )
        return f"{self.type.basic_type}{type_args_str} {self.identifier}"

    def __repr__(self):
        return f"Argument({self.type!r}, {self.identifier!r})"

    def __eq__(self, other):
        return self.type == other.type and self.identifier == other.identifier

    def as_field(self) -> Field:
        return self.type.as_field(self.identifier)


class SyscallDef:
    def __init__(self, name: str, arg_list: List[Argument]):
        self.name = name
        self.arg_list = arg_list

    def __str__(self):
        arg_list_str = ", ".join(str(arg) for arg in self.arg_list)
        return f"{self.name}({arg_list_str})"

    def __repr__(self):
        return f"SyscallDef({self.name!r}, {self.arg_list!r})"

    def __eq__(self, other):
        return self.name == other.name and self.arg_list == other.arg_list


class Token:
    def __init__(self, token_type: str, token_value: str):
        self.token_type = token_type
        self.token_value = token_value

    def __str__(self):
        return f"{self.token_type}({self.token_value})"

    def __repr__(self):
        return f"Token({self.token_type!r}, {self.token_value!r})"

    def __eq__(self, other):
        return (
            self.token_type == other.token_type
            and self.token_value == other.token_value
        )


def tokenize(input_str: str) -> List[Token]:
    # match words, parentheses, brackets, commas, and equal signs
    # also match double-quoted strings
    tokens = re.findall(r'\w+|[()[\],=]|"[^"]*"', input_str)
    token_list = []

    for token in tokens:
        if token in FIELD_CLASSES:
            token_list.append(Token("basic_type", token))
        elif token in ["(", ")", "[", "]", ",", "="]:
            token_list.append(Token(token, token))
        elif token.startswith('"') and token.endswith('"'):
            token_list.append(Token("string_literal", token[1:-1]))
        else:
            token_list.append(Token("identifier", token))

    return token_list


def parse_type(tokens: List[Token]) -> Type:
    basic_type = parse_basic_type(tokens)
    type_args = parse_type_args(tokens)

    return Type(basic_type, type_args)


def parse_basic_type(tokens: List[Token]) -> BasicType:
    return BasicType(tokens.pop(0).token_value)


def parse_type_args(tokens: List[Token]) -> List[TypeArg]:
    type_args = []

    if tokens and tokens[0].token_type == "[":
        tokens.pop(0)  # Remove '['
        while tokens and tokens[0].token_type != "]":
            type_args.append(parse_type_arg(tokens))
            if tokens and tokens[0].token_type == ",":
                tokens.pop(0)  # Remove ','
        if tokens and tokens[0].token_type == "]":
            tokens.pop(0)  # Remove ']'

    return type_args


def parse_value(tokens: List[Token]) -> Union[Type, str, int]:
    if tokens[0].token_type == "basic_type":
        return parse_type(tokens)

    if tokens[0].token_type == '"':
        accumulator = []
        tokens.pop(0)
        while tokens and tokens[0].token_type != '"':
            accumulator.append(tokens.pop(0).token_value)
        if tokens:
            tokens.pop(0)  # Remove ending '"'
        else:
            raise ValueError("Unterminated string")
        return ''.join(accumulator)

    value = tokens.pop(0).token_value
    try:
        return int(value)
    except ValueError:
        return value


def parse_type_arg(tokens: List[Token]) -> TypeArg:
    if tokens[0].token_type != "identifier":
        remaining = ''.join(token.token_value for token in tokens)
        raise ValueError(
            f"Expected identifier but found '{tokens[0].token_value}' of type '{tokens[0].token_type}' while parsing '{remaining}'"
        )
    if tokens[1].token_type != "=":
        remaining = ''.join(token.token_value for token in tokens)
        raise ValueError(
            f"Expected '=' following '{tokens[0].token_value}' while parsing '{remaining}'"
        )

    attr_identifier = tokens.pop(0).token_value
    tokens.pop(0)  # Remove '='
    value = parse_value(tokens)
    return TypeArg(attr_identifier, value)


# Updated parse function
def parse(input_str: str) -> SyscallDef:
    tokens = tokenize(input_str)
    syscall_name = tokens.pop(0).token_value
    tokens.pop(0)  # Remove '('

    arg_list = []
    while tokens and tokens[0].token_type != ")":
        type = parse_type(tokens)
        arg_name = tokens.pop(0).token_value
        arg_list.append(Argument(type, arg_name))

        if tokens and tokens[0].token_type == ",":
            tokens.pop(0)  # Remove ','

    if tokens and tokens[0].token_type == ")":
        tokens.pop(0)  # Remove ')'

    return SyscallDef(syscall_name, arg_list)


def parse_syscall(line: str) -> Tuple[str, List[Field]]:
    syscall_def = parse(line)
    fields = [arg.as_field() for arg in syscall_def.arg_list]
    return syscall_def.name, fields
