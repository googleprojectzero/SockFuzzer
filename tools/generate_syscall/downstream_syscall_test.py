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

from sockfuzzer.tools.generate_syscall.downstream_syscall import DownstreamSyscall
from sockfuzzer.tools.generate_syscall.downstream_field import Nullptr, Literal, EmptyBuffer, Flags, EmptyArray
import unittest


class ParserTest(unittest.TestCase):
    def test_parses_simple(self):
        syscall = DownstreamSyscall.from_line("syscall(Nullptr retval)")
        self.assertEqual(syscall.name, "syscall")
        self.assertEqual(len(syscall.fields), 1)
        self.assertEqual(syscall.fields[0].name, "retval")
        self.assertIsInstance(syscall.fields[0], Nullptr)

    def test_parses_arg(self):
        syscall = DownstreamSyscall.from_line("bla(Literal[value=1] val)")
        # Use plain assert to inform type system
        assert isinstance(syscall.fields[0], Literal)
        self.assertEqual(syscall.fields[0].value, 1)

    def test_parses_kwarg(self):
        syscall = DownstreamSyscall.from_line("bla(Literal[value=1] val)")
        assert isinstance(syscall.fields[0], Literal)
        self.assertEqual(syscall.fields[0].value, 1)

    def test_parses_kwargs(self):
        syscall = DownstreamSyscall.from_line(
            "bla(EmptyArray[c_type=\"unsigned long\", fixed_size=2] val)"
        )
        assert isinstance(syscall.fields[0], EmptyArray)
        self.assertEqual(syscall.fields[0].c_type, "unsigned long")
        self.assertEqual(syscall.fields[0].fixed_size, 2)

    def test_parses_args_and_kwargs(self):
        syscall = DownstreamSyscall.from_line(
            "bla(Flags[proto_type=EnumName, c_type=\"unsigned long\"] val)"
        )
        assert isinstance(syscall.fields[0], Flags)
        self.assertEqual(syscall.fields[0].c_type, "unsigned long")
        self.assertEqual(syscall.fields[0].proto_type, "EnumName")

    def test_parses_cast(self):
        syscall = DownstreamSyscall.from_line("dummy(Literal[cast=my_cast_t, value=0] val)")
        self.assertEqual(len(syscall.fields), 1)
        assert syscall.fields[0].cast is not None
        self.assertEqual(syscall.fields[0].cast.strip(), "my_cast_t")

    def test_buffer_with_size(self):
        syscall = DownstreamSyscall.from_line(
            "read(EmptyBuffer[size_given_by=size] buf, UInt32 size)"
        )
        self.assertEqual(len(syscall.fields), 2)
        assert isinstance(syscall.fields[0], EmptyBuffer)
        self.assertEqual(syscall.fields[0].size_given_by, "size")
        self.assertEqual(syscall.fields[1].name, "size")
        self.assertEqual(syscall.fields[1], syscall.field_by_name("size"))


SIMPLE_SYSCALL_DEF = "simple(UInt64 bla)"
SIMPLE_CALLER_CALL = "simple_wrapper(bla);"
SIMPLE_CALLING_CODE = """\
case BsdSyscall::kSimple: {
  auto args = syscall.simple();
  unsigned long bla = args.bla();
  simple_wrapper(bla);
  break;
}
"""
SIMPLE_PROTO = """\
message SimpleMessage {
  required uint64 bla = 1;
}
"""

MINCORE_SYSCALL_DEF = "mincore(UInt64 addr, CappedSize len, EmptyBuffer[size_given_by=len] vec, Retval retval)"
MINCORE_CALLER_CALL = "mincore_wrapper(addr, len, vec.data(), &(retval));"
MINCORE_CALLING_CODE = """\
case BsdSyscall::kMincore: {
  auto args = syscall.mincore();
  int retval;
  unsigned long len = (args.len() % 4096);
  unsigned long addr = args.addr();
  std::vector<char> vec(len);
  mincore_wrapper(addr, len, vec.data(), &(retval));
  break;
}
"""
MINCORE_PROTO = """\
message MincoreMessage {
  required uint64 addr = 1;
  required uint64 len = 2;
}
"""


class CodegenTest(unittest.TestCase):
    # These tests are simple, just making sure *something* is generated.
    # The real test of codegen and syscalls.defs is whether the actual
    # generated code compiles.
    def test_codegen_call_simple(self):
        syscall = DownstreamSyscall.from_line(SIMPLE_SYSCALL_DEF)
        self.assertEqual(syscall.caller_call.strip(), SIMPLE_CALLER_CALL)

    def test_codegen_caller_case_simple(self):
        syscall = DownstreamSyscall.from_line(SIMPLE_SYSCALL_DEF)
        self.assertEqual(syscall.calling_code, SIMPLE_CALLING_CODE)

    def test_codegen_proto_simple(self):
        syscall = DownstreamSyscall.from_line(SIMPLE_SYSCALL_DEF)
        self.assertEqual(syscall.proto_message, SIMPLE_PROTO)

    def test_codegen_call_mincore(self):
        syscall = DownstreamSyscall.from_line(MINCORE_SYSCALL_DEF)
        self.assertEqual(syscall.caller_call.strip(), MINCORE_CALLER_CALL)

    def test_codegen_caller_case_mincore(self):
        syscall = DownstreamSyscall.from_line(MINCORE_SYSCALL_DEF)
        self.assertEqual(syscall.calling_code, MINCORE_CALLING_CODE)

    def test_codegen_proto_mincore(self):
        syscall = DownstreamSyscall.from_line(MINCORE_SYSCALL_DEF)
        self.assertEqual(syscall.proto_message, MINCORE_PROTO)


if __name__ == "__main__":
    unittest.main()
