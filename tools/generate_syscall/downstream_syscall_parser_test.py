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

import unittest
from sockfuzzer.tools.generate_syscall.downstream_syscall_parser import (
    tokenize,
    parse,
    Type,
    Token,
    TypeArg,
    Argument,
    SyscallDef,
    parse_basic_type,
    parse_value,
    parse_type_arg,
    parse_type,
    BasicType,
)
from sockfuzzer.tools.generate_syscall.downstream_field import (
    Declared,
    FIELD_CLASSES,
    Ptr,
    UInt64,
    Enum
)


class TestParser(unittest.TestCase):
    def test_tokenize(self):
        input_str = "syscall_name(Ptr[ref=Declared[Int32]] arg1, UInt64 arg2)"
        expected_tokens = [
            Token("identifier", "syscall_name"),
            Token("(", "("),
            Token("basic_type", "Ptr"),
            Token("[", "["),
            Token("identifier", "ref"),
            Token("=", "="),
            Token("basic_type", "Declared"),
            Token("[", "["),
            Token("basic_type", "Int32"),
            Token("]", "]"),
            Token("]", "]"),
            Token("identifier", "arg1"),
            Token(",", ","),
            Token("basic_type", "UInt64"),
            Token("identifier", "arg2"),
            Token(")", ")"),
        ]
        self.assertEqual(tokenize(input_str), expected_tokens)

    def test_parse_basic_type(self):
        tokens = [Token("basic_type", "Ptr")]
        basic_type = parse_basic_type(tokens)
        self.assertEqual(basic_type.name, "Ptr")

    def test_parse_type_arg(self):
        tokens = [
            Token("identifier", "ref"),
            Token("=", "="),
            Token("basic_type", "Declared"),
            Token("[", "["),
            Token("identifier", "c_type"),
            Token("=", "="),
            Token("basic_type", "Int32"),
            Token("]", "]"),
        ]
        type_arg = parse_type_arg(tokens)
        self.assertEqual(type_arg.attr_identifier, "ref")
        ref_value = type_arg.value
        self.assertIsInstance(ref_value, Type)
        assert isinstance(ref_value, Type)

    def test_parse_type_arg_string(self):
        input = 'c_type="struct msghdr"'
        tokens = tokenize(input)
        type_arg = parse_type_arg(tokens)
        self.assertEqual(type_arg.attr_identifier, "c_type")
        self.assertEqual(type_arg.value, "struct msghdr")

    def test_parse_type_missing_ref(self):
        # Ptr[Declared[Int32]]
        tokens = [
            Token("basic_type", "Ptr"),
            Token("[", "["),
            Token("basic_type", "Declared"),
            Token("[", "["),
            Token("basic_type", "Int32"),
            Token("]", "]"),
            Token("]", "]"),
        ]
        try:
            type_arg = parse_type_arg(tokens)
        except ValueError as e:
            self.assertEqual(
                str(e),
                "Expected identifier but found 'Ptr' of type 'basic_type' while parsing 'Ptr[Declared[Int32]]'"
            )
        else:
            self.fail("Expected ValueError")

    def test_basic_type(self):
        tokens = [Token("basic_type", "UInt32")]
        result = parse_value(tokens)
        self.assertEqual(str(result), "UInt32")

    def test_quoted_string(self):
        tokens = [
            Token('"', '"'),
            Token("identifier", "hello"),
            Token("identifier", "world"),
            Token('"', '"'),
        ]
        result = parse_value(tokens)
        self.assertEqual(result, "helloworld")

    def test_unquoted_string(self):
        tokens = [Token("identifier", "unquoted_string")]
        result = parse_value(tokens)
        self.assertEqual(result, "unquoted_string")

    def test_integer(self):
        tokens = [Token("identifier", "42")]
        result = parse_value(tokens)
        self.assertEqual(result, 42)

    def test_unterminated_string(self):
        tokens = [Token('"', '"'),
            Token("identifier", "unterminated"),
            Token("identifier", "string"),
        ]
        with self.assertRaises(ValueError):
            parse_value(tokens)

    def test_uint64_cast(self):
        # UInt64[cast=caddr_t]
        tokens = [
            Token("basic_type", "UInt64"),
            Token("[", "["),
            Token("identifier", "cast"),
            Token("=", "="),
            Token("identifier", "caddr_t"),
            Token("]", "]"),
        ]
        type = parse_type(tokens)
        field = type.as_field("field_name")
        self.assertEqual(field.name, "field_name")
        assert isinstance(field, UInt64)
        self.assertEqual(field.c_type, "unsigned long")
        self.assertEqual(field.cast, "caddr_t")

    def test_enum_invalid(self):
        """
        Using c_type is not valid for Enum. Make sure we raise a ValueError.
        """
        # Enum[c_type=MadviseFlags]
        tokens = [
            Token("basic_type", "Enum"),
            Token("[", "["),
            Token("identifier", "c_type"),
            Token("=", "="),
            Token("identifier", "MadviseFlags"),
            Token("]", "]"),
        ]
        type = parse_type(tokens)
        self.assertRaises(ValueError, type.as_field)

    def test_enum(self):
        # Enum[proto_type=MadviseFlags]
        tokens = [
            Token("basic_type", "Enum"),
            Token("[", "["),
            Token("identifier", "proto_type"),
            Token("=", "="),
            Token("identifier", "MadviseFlags"),
            Token("]", "]"),
        ]
        type = parse_type(tokens)
        field = type.as_field("madvise")
        self.assertEqual(field.name, "madvise")
        assert isinstance(field, Enum)
        self.assertEqual(field.c_type, "int")
        self.assertIsNone(field.cast)
        self.assertEqual(field.proto_type, "MadviseFlags")

    def test_parse(self):
        input_str = "syscall_name(Ptr[ref=Declared[c_type=Int32]] arg1, UInt64 arg2)"
        expected_syscall_def = SyscallDef(
            "syscall_name",
            [
                Argument(
                    Type(
                        BasicType("Ptr"),
                        [
                            TypeArg(
                                "ref",
                                Type(
                                    BasicType("Declared"),
                                    [TypeArg("c_type", Type(BasicType("Int32"), []))],
                                ),
                            ),
                        ],
                    ),
                    "arg1",
                ),
                Argument(Type(BasicType("UInt64"), []), "arg2"),
            ],
        )
        self.assertEqual(parse(input_str), expected_syscall_def)

    def test_as_field_basic(self):
        arg = Argument(Type(BasicType("UInt64"), []), "arg2")
        field = arg.as_field()

        # Check field properties
        self.assertEqual(field.name, "arg2")
        self.assertIs(type(field), FIELD_CLASSES["UInt64"])
        self.assertEqual(field.proto_type, "uint64")
        self.assertEqual(field.c_type, "unsigned long")
        self.assertIsNone(field.max_value)

    def test_as_field_nested(self):
        # Ptr[field=Declared[c_type=int]]
        arg = Argument(
            Type(
                BasicType("Ptr"),
                [
                    TypeArg(
                        "field", Type(BasicType("Declared"), [TypeArg("c_type", "int")])
                    )
                ],
            ),
            "arg1",
        )
        field = arg.as_field()

        # Check field properties
        self.assertEqual(field.name, "arg1")
        self.assertIs(type(field), Ptr)
        self.assertIsNotNone(field.field)

        # Check nested field properties
        nested_field = field.field
        self.assertIsInstance(nested_field, Declared)
        assert isinstance(nested_field, Declared)
        print(nested_field)
        self.assertEqual(nested_field.c_type, "int")

    def test_retval_name(self):
        # Retval retval
        # arg = Argument(Type(BasicType("Retval"), []), "retval")
        tokens = [
            Token("basic_type", "Retval"),
            Token("identifier", "retval"),
        ]

        parse_type_arg


if __name__ == "__main__":
    unittest.main()
