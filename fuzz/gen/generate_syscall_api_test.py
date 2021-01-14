"""
Copyright 2021 Google LLC

@APPLE_OSREFERENCE_LICENSE_HEADER_START@

This file contains Original Code and/or Modifications of Original Code
as defined in and that are subject to the Apple Public Source License
Version 2.0 (the 'License'). You may not use this file except in
compliance with the License. The rights granted to you under the License
may not be used to create, or enable the creation or redistribution of,
unlawful or unlicensed copies of an Apple operating system, or to
circumvent, violate, or enable the circumvention or violation of, any
terms of an Apple operating system software license agreement.

Please obtain a copy of the License at
http://www.opensource.apple.com/apsl/ and read it before using this file.

The Original Code and all software distributed under the License are
distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
Please see the License for the specific language governing rights and
limitations under the License.

@APPLE_OSREFERENCE_LICENSE_HEADER_END@
"""

"""Tests for generate_syscall_api."""

import generate_syscall_api
import unittest
from unittest.mock import call, patch

WAIT4_LINE = (b'7\tAUE_WAIT4\tALL\t{ int wait4(int pid, user_addr_t status,'
              b' int options, user_addr_t rusage) NO_SYSCALL_STUB; } ')

# Number of tests to use for the hand-written output below
NUM_TESTS = 2

GENERATED_MESSAGE1 = """message DisableThreadsignal {
  optional int32 value = 1;
}"""

GENERATED_MESSAGE2 = """message MacExecve {
  optional string fname = 1;
  repeated string argp = 2;
  repeated string envp = 3;
  optional StructMac mac_p = 4;
}"""

# int __disable_threadsignal(int value);
GENERATED_PROTOBUF = """message GeneratedCommands {{
  oneof command {{
    DisableThreadsignal __disable_threadsignal = 1;
    MacExecve __mac_execve = 2;
  }}
}}

{}

{}""".format(GENERATED_MESSAGE1, GENERATED_MESSAGE2)

MAC_GET_PID_MESSAGE = """message MacGetPid {
  optional Pid pid = 1;
  optional StructMac mac_p = 2;
}"""

MAC_GETFSSTAT_MESSAGE = """message MacGetfsstat {
  optional bytes buf = 1;
  optional bytes mac = 2;
  optional MacGetfsstatFlags flags = 3;
}"""

AUDIT_MESSAGE = """message Audit {
  optional bytes record = 1;
}"""

GENERATED_SYSCALL_HEADER = """#ifndef SYSCALL_WRAPPERS_H_
#define SYSCALL_WRAPPERS_H_

#include <stddef.h>
#include <stdint.h>
typedef unsigned char uuid_t[16];
typedef u_int64_t user_addr_t;
typedef u_int32_t socklen_t;
typedef struct sa_endpoints {
	unsigned int		sae_srcif;	/* optional source interface */
	const struct sockaddr	*sae_srcaddr;   /* optional source address */
	socklen_t		sae_srcaddrlen; /* size of source address */
	const struct sockaddr	*sae_dstaddr;   /* destination address */
	socklen_t		sae_dstaddrlen; /* size of destination address */
} sa_endpoints_t;
typedef __uint32_t sae_associd_t;
typedef __uint32_t sae_connid_t;

int __disable_threadsignal_wrapper(int value, int* retval);
int __mac_execve_wrapper(char * fname, char ** argp, char ** envp, struct mac * mac_p, int* retval);

#endif  // SYSCALL_WRAPPERS_H_
"""

GENERATED_SYSCALL_IMPL = """#include "fuzz/syscall_wrappers.h"

__attribute__((visibility("default"))) int __disable_threadsignal_wrapper(int value, int* retval) {
  struct __disable_threadsignal_args uap = {
    .value = value,
  };
  return __disable_threadsignal(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int __mac_execve_wrapper(char * fname, char ** argp, char ** envp, struct mac * mac_p, int* retval) {
  struct __mac_execve_args uap = {
    .fname = fname,
    .argp = argp,
    .envp = envp,
    .mac_p = mac_p,
  };
  return __mac_execve(kernproc, &uap, retval);
}
"""

class GenerateFuzzerTest(unittest.TestCase):
  """Test syscall code generation."""

  @patch('generate_syscall_api.Argument')
  def test_syscall_from_line(self, MockArgument):
    syscall = generate_syscall_api.Syscall.from_line(WAIT4_LINE)
    self.assertEqual(syscall.name, 'wait4')
    self.assertEqual(syscall.return_type, 'int')
    self.assertEqual(len(syscall.arguments), 4)
    calls = [
        call.from_string('int pid'),
        call.from_string('user_addr_t status'),
        call.from_string('int options'),
        call.from_string('user_addr_t rusage')
    ]
    MockArgument.assert_has_calls(calls, any_order=True)

  def test_syscall_nosys_from_line(self):
    line = b'0\tAUE_NULL\tALL\t{ int nosys(void); }   { indirect syscall }'
    syscall = generate_syscall_api.Syscall.from_line(line)
    self.assertEqual(syscall.name, 'nosys')
    self.assertEqual(len(syscall.arguments), 0)

  def test_int_argument(self):
    argument = generate_syscall_api.Argument.from_string('int pid')
    self.assertEqual(argument.name, 'pid')
    self.assertEqual(argument.type, 'int')

  def test_tab_in_argument(self):
    argument = generate_syscall_api.Argument.from_string('socklen_t\t*anamelen')
    self.assertEqual(argument.name, 'anamelen')
    self.assertEqual(argument.type, 'socklen_t *')

  def test_syscall_message_name(self):
    syscall = generate_syscall_api.Syscall('__disable_threadsignal', 'void', [], [])
    self.assertEqual(syscall.message_name, 'DisableThreadsignal')

  def test_syscall_message(self):
    syscall = generate_syscall_api.Syscall(
        '__disable_threadsignal', 'void',
        [generate_syscall_api.Argument('value', 'int')],
        [generate_syscall_api.Argument('value', 'int')])
    self.assertEqual(syscall.message, GENERATED_MESSAGE1)

  def test_struct_pointer_argument(self):
    argument = generate_syscall_api.Argument.from_string('struct msghdr *msg')
    self.assertEqual(argument.name, 'msg')
    # TODO(nedwill): make type class more refined
    self.assertEqual(argument.type, 'struct msghdr *')

  def test_struct_pointer_argument_underscore(self):
    argument = generate_syscall_api.Argument.from_string('struct mac *mac_p')
    self.assertEqual(argument.name, 'mac_p')
    self.assertEqual(argument.type, 'struct mac *')

  def test_mac_get_pid_message(self):
    syscall = generate_syscall_api.Syscall.from_function(
        b'int __mac_get_pid(pid_t pid, struct mac *mac_p);')
    self.assertEqual(syscall.message, MAC_GET_PID_MESSAGE)

  def test_mac_getfsstat_message(self):
    syscall = generate_syscall_api.Syscall.from_function(
        b'int __mac_getfsstat(user_addr_t buf, int bufsize, user_addr_t mac, int macsize, int flags);'
    )
    self.assertEqual(syscall.message, MAC_GETFSSTAT_MESSAGE)

  def test_mac_audit_message(self):
    syscall = generate_syscall_api.Syscall.from_function(
        b'int audit(void *record, int length);')
    self.assertEqual(syscall.message, AUDIT_MESSAGE)

  def test_parsing_does_not_crash(self):
    # Creating syscall tracker should not crash
    generate_syscall_api.SyscallTracker()

  def test_generate_protobuf(self):
    tracker = generate_syscall_api.SyscallTracker(NUM_TESTS)
    self.assertEqual(tracker.generate_protobuf(), GENERATED_PROTOBUF)

  def test_generate_protobuf_does_not_crash(self):
    generate_syscall_api.SyscallTracker(0).generate_protobuf()

  def test_generate_syscall_header(self):
    tracker = generate_syscall_api.SyscallTracker(NUM_TESTS)
    self.assertEqual(tracker.generate_syscall_wrappers_header(),
                     GENERATED_SYSCALL_HEADER)

  def test_generate_syscall_header_does_not_crash(self):
    generate_syscall_api.SyscallTracker(0).generate_syscall_wrappers_header()

  def test_generate_syscall_impl(self):
    self.maxDiff = None
    tracker = generate_syscall_api.SyscallTracker(NUM_TESTS)
    self.assertEqual(tracker.generate_syscall_wrappers_impl(), GENERATED_SYSCALL_IMPL)

if __name__ == '__main__':
  unittest.main()
