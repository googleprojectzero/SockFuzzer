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

from tools.generate_syscall.upstream_syscall_manager import (
    parse_syscalls,
    filter_syscalls,
)
import unittest
from io import StringIO

SYSCALL_WAIT4 = """
#include dummy

; comment

7	AUE_WAIT4	ALL	{ int wait4(int pid, user_addr_t status, int options, user_addr_t rusage) NO_SYSCALL_STUB; }

; command

"""

WAIT4_IMPL = """\
int wait4_wrapper(int pid, user_addr_t status, int options, user_addr_t rusage, int *retval) {
  struct wait4_args args = {
    .pid = pid,
    .status = status,
    .options = options,
    .rusage = rusage,
  };
  return wait4(current_proc(), &args, retval);
}
"""

SYSCALLS_WITH_DEFS = """
#if COMPILE_FOO
20	AUE_NULL	ALL	{ int foo(int rval) NO_SYSCALL_STUB; }
#else
20	AUE_NULL	ALL	{ int bar(int rval) NO_SYSCALL_STUB; }
#endif
"""

SYSCALLS = """
30	AUE_NULL	ALL	{ int foo(int rval) NO_SYSCALL_STUB; }
31	AUE_NULL	ALL	{ int bar(user_addr_t fd, int rval); }
"""

SYSCALL_COLLISION = """
40	AUE_NULL	ALL	{ int collision(void *collision) NO_SYSCALL_STUB; }
"""

COLLISION_IMPL = """\
int collision_wrapper(void *collision_arg, int *retval) {
  struct collision_args args = {
    .collision = (user_addr_t) collision_arg,
  };
  return collision(current_proc(), &args, retval);
}
"""

SYSCALL_PTR_TYPES = """
50	AUE_NULL	ALL	{ weird_return_t weird(void *ptr, weird_type **val) NO_SYSCALL_STUB; }
"""

SYSCALL_VOID = """
60	AUE_NULL	ALL	{ void boring(void); }
"""


def parse(string):
    return parse_syscalls(StringIO(string))


class ParserTest(unittest.TestCase):
    def test_parses_wait4_correctly(self):
        parsed = parse(SYSCALL_WAIT4)
        self.assertEqual(len(parsed), 1)
        wait4 = parsed[0]
        self.assertEqual(wait4.number, 7)
        self.assertEqual(wait4.name, "wait4")
        self.assertEqual(wait4.return_type, "int")
        self.assertEqual(len(wait4.args), 4)

        self.assertEqual(wait4.args[0].type_, "int")
        self.assertEqual(wait4.args[0].name, "pid")

        self.assertEqual(wait4.args[1].type_, "user_addr_t")
        self.assertEqual(wait4.args[1].name, "status")

        self.assertEqual(wait4.args[2].type_, "int")
        self.assertEqual(wait4.args[2].name, "options")

        self.assertEqual(wait4.args[3].type_, "user_addr_t")
        self.assertEqual(wait4.args[3].name, "rusage")

    def test_avoids_name_collision(self):
        parsed = parse(SYSCALL_COLLISION)[0]

        self.assertNotEqual(parsed.name, parsed.args[0].name)

    def test_ptr_types(self):
        parsed = parse(SYSCALL_PTR_TYPES)
        args = parsed[0].args

        self.assertEqual(args[0].type_, "void *")
        self.assertEqual(args[0].name, "ptr")

        self.assertEqual(args[1].type_, "weird_type **")
        self.assertEqual(args[1].name, "val")

    def test_void_args(self):
        parsed = parse(SYSCALL_VOID)

        self.assertEqual(len(parsed[0].args), 0)


class FilterTest(unittest.TestCase):
    def test_filter_by_defs(self):
        parsed = parse(SYSCALLS_WITH_DEFS)
        self.assertEqual(len(parsed), 2)

        filtered = filter_syscalls(parsed, ["COMPILE_FOO"], [])
        self.assertEqual(len(filtered), 1)
        self.assertEqual(filtered[0].name, "foo")

        filtered = filter_syscalls(parsed, [], [])
        self.assertEqual(len(filtered), 1)
        self.assertEqual(filtered[0].name, "bar")

    def test_filter_delete(self):
        parsed = parse(SYSCALLS)
        self.assertEqual(len(parsed), 2)

        filtered = filter_syscalls(parsed, [], ["foo"])
        self.assertEqual(len(filtered), 1)
        self.assertEqual(filtered[0].name, "bar")


class CodegenTest(unittest.TestCase):
    def test_adds_retval(self):
        parsed = parse(SYSCALL_WAIT4)[0]
        self.assertTrue("int *retval" in parsed.wrapper_decl)

    def test_retval_respects_type(self):
        parsed = parse(SYSCALL_PTR_TYPES)[0]
        self.assertTrue("weird_return_t *retval" in parsed.wrapper_decl)

    def test_wrapper_decl(self):
        parsed = parse(SYSCALL_COLLISION)[0]
        self.assertEqual(
            parsed.wrapper_decl,
            "int collision_wrapper(void *collision_arg, int *retval)",
        )

    def test_wrapper_impl(self):
        parsed = parse(SYSCALL_COLLISION)[0]
        self.assertEqual(parsed.wrapper_impl, COLLISION_IMPL)

    def test_wait4_impl(self):
        parsed = parse(SYSCALL_WAIT4)[0]
        self.assertEqual(parsed.wrapper_impl, WAIT4_IMPL)

    def test_def_entry(self):
        parsed = parse(SYSCALL_COLLISION)[0]
        self.assertEqual(
            parsed.def_entry, "collision(void *collision_arg, int *retval)"
        )


if __name__ == "__main__":
    unittest.main()
