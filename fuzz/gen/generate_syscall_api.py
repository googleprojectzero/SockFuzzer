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

"""Generate structured fuzzer code from syscall master list

This file autogenerates code to call syscalls to let us get us
much initial fuzz coverage as possible. It is designed to work
with hand-written syscall descriptions as well.

TODO(nedwill): support other syscall types such as mach traps

Goals:
1) generate protobuf file with a message containing all syscalls
2) generate syscall wrapper code to expose from libxnu
3) generate c code to call wrappers given autogen syscall message

First, we will simply print this output to the terminal for manual
use. Later, we can make this integration automatic, even making it
work with cmake/ninja.
"""

ALLOWLIST = frozenset([
    'socket',
    'close',
    'listen',
    'accept',
    'connect',
    'bind',
    'connectx',
    'disconnectx',
    'ioctl',
    'ioctl_data',
    'setsockopt',
    'getsockopt',
    'necp_match_policy',
    'necp_open',
    'necp_client_action',
    'necp_session_open',
    'necp_session_action',
    'recvmsg',
    'sendmsg',
    'recvfrom',
    'getpeername',
    'getsockname',
    'sendto',
    'shutdown',
    'socketpair',
    'recvmsg_nocancel',
    'sendmsg_nocancel',
    'recvfrom_nocancel',
    'accept_nocancel',
    'connect_nocancel',
    'sendto_nocancel',
    # TODO(nedwill): need to build vm_unix.c for this
    # 'pid_shutdown_sockets',
    'peeloff',
    'socket_delegate',
    'recvmsg_x',
    'sendmsg_x',
    'pipe',
    'shutdown',
])

import string


class ProtobufType:
  pass


class BufferProtobufType(ProtobufType):

  def __init__(self, name):
    self.name = name
    self.type = 'bytes'

  def __str__(self):
    return 'bytes'


class ProtobufField:

  def __init__(self, type_):
    self.type = type_

  @property
  def used(self):
    return True


class Optional(ProtobufField):

  @property
  def field_type(self):
    return 'optional'


class Repeated(ProtobufField):

  @property
  def field_type(self):
    return 'repeated'


class Result(ProtobufField):

  @property
  def used(self):
    return False


# TODO(nedwill): we should be detecting optional/repeated automatically
# from the number of indirections
TYPE_MAPPING = {
    'int':
        Optional('int32'),
    'char *':
        Optional('string'),
    'char **':
        Repeated('string'),
    'const char *':
        Optional('string'),
    'struct mac *':
        Optional('StructMac'),
    'pid_t':
        Optional('Pid'),
    'uint32_t':
        Optional('uint32'),
    'uint64_t':
        Optional('uint64'),
    'socklen_t *':
        Result('socklen_t'),
    'size_t':
        Optional('uint64_t'),
    'uid_t':
        Optional('Uid'),
    'struct timeval *':
        Optional('StructTimeval'),
    'const struct timespec *':
        Optional('StructTimespec'),
    'struct itimerval *':
        Optional('StructItimer'),
    'mach_port_name_t':
        Optional('MachPort'),
    'au_asid_t':
        Optional('AuditSessionID'),
    'const guardid_t *':
        Optional('Guardid'),
    'u_int':
        Optional('uint32'),
    'int *':
        Optional('int32'),
    'gid_t':
        Optional('Group'),
    'gid_t *':
        Optional('Group'),
    'uint64_t *':
        Optional('uint64'),
    'const sa_endpoints_t *':
        Optional('Endpoints'),
    'sae_associd_t':
        Optional('SaeAssocID'),
    'unsigned int':
        Optional('uint32'),
    'const struct iovec *':
        Optional('IOV'),
    'struct iovec *':
        Optional('IOV'),
    'size_t *':
        Optional('uint64'),
    'sae_connid_t *':
        Optional('SaeConnID'),
    'sae_connid_t':
        Optional('SaeConnID'),
    'u_long':
        Optional('uint64'),
    'long':
        Optional('int64'),
    'struct attrlist *':
        Optional('Attrlist'),
    'const struct fhandle *':
        Optional('StructFhandle'),
    'fhandle_t *':
        Optional('StructFhandle'),
    'struct statfs *':
        Optional('StructStatfs'),
    'struct statfs64 *':
        Optional('StructStatfs64'),
    'au_id_t *':
        Optional('AuId'),
    'long *':
        Optional('int64'),
    'off_t':
        Optional('int64'),
    'off_t *':
        Optional('int64'),
    'u_long *':
        Optional('uint64'),
    'id_t':
        Optional('Id'),
    'struct rlimit *':
        Optional('StructRlimit'),
    'struct rusage *':
        Optional('StructRusage'),
    'uid_t *':
        Optional('Uid'),
    'struct timezone *':
        Optional('StructTimezone'),
    'const struct kevent *':
        Optional('StructKevent'),
    'struct kevent *':
        Optional('StructKevent'),
    'const struct kevent64_s *':
        Optional('StructKevent64'),
    'struct kevent64_s *':
        Optional('StructKevent64'),
    'const struct kevent_qos_s *':
        Optional('StructKeventQos'),
    'struct kevent_qos_s *':
        Optional('StructKeventQos'),
    'struct eventreq *':
        Optional('StructEventreq'),
    'struct msqid_ds *':
        Optional('StructMsqidDs'),
    'key_t':
        Optional('Key'),
    'uuid_t':
        Optional('Uuid'),
    'struct necp_aggregate_result *':
        Optional('StructNecpAggregateResult'),
    'struct net_qos_param *':
        Optional('StructNetQosParam'),
    'struct timex *':
        Optional('StructTimex'),
    'struct ntptimeval *':
        Optional('StructNtptimeval'),
    'struct kpersona_info *':
        Optional('StructKpersonaInfo'),
    'struct pollfd *':
        Optional('StructPollfd'),
    'pid_t':
        Optional('Pid'),
    'pid_t *':
        Optional('Pid'),
    'const struct _posix_spawn_args_desc *':
        Optional('StructPosixSpawnArgsDesc'),
    'u_int32_t':
        Optional('uint32'),
    'u_int32_t *':
        Optional('uint32'),
    'const struct sigset_t *':
        Optional('StructSigset'),
    'int64_t':
        Optional('int64'),
    'struct sockaddr *':
        Optional('StructSockaddr'),
    'struct msghdr *':
        Optional('StructMsghdr'),
    'struct msghdr_x *':
        Optional('StructMsghdrx'),
    'struct fssearchblock *':
        Optional('StructFssearchBlock'),
    'uint32_t *':
        Optional('uint32_t'),
    'struct searchstate *':
        Optional('StructSearchstate'),
    'sem_t *':
        Optional('Semaphore'),
    'semun_t *':
        Optional('SemaphoreUn'),
    'semun_t':
        Optional('SemaphoreUn'),
    'struct sembuf *':
        Optional('StructSembuf'),
    'struct sf_hdtr *':
        Optional('StructSfHdtr'),
    'const struct shared_file_mapping_np *':
        Optional('StructSharedFileMappingNp'),
    'uint64_t*':
        Optional('uint64'),
    'struct shmid_ds *':
        Optional('StructShmidDs'),
    'struct __sigaction *':
        Optional('StructSigaction1'),
    'struct sigaction *':
        Optional('StructSigaction2'),
    'struct sigaltstack *':
        Optional('StructSigaltstack'),
    'struct sigvec *':
        Optional('StructSigvec'),
    'struct ucontext *':
        Optional('StructUcontext'),
    'sigset_t':
        Optional('Sigset'),
    'user_addr_t *':
        Optional('bytes'),
    'user_size_t':
        Optional('uint64'),
    'idtype_t':
        Optional('Idtype'),
    'siginfo_t *':
        Optional('Siginfo'),
    'const struct shared_file_np *':
        Optional('SharedFileNp'),
    'const struct shared_file_mapping_slide_np *':
        Optional('SharedFileMappingSlideNp'),
    'mach_port_name_t *':
        Optional('MachPortName'),

    # TODO(nedwill): for these cases we probably want to implement
    # manually or at least send the (void*)1 pointer to let copyin
    # read from the fuzzed input stream
    'caddr_t':
        Optional('bytes'),
    'user_addr_t':
        Optional('bytes'),
    'unsigned char *':
        Optional('bytes'),
    'void *':
        Optional('bytes'),
    'int32_t':
        Optional('int32'),
}


class Argument:

  def __init__(self, name, type_):
    self.name = name
    self.type = type_

  @property
  def protobuf_type(self):
    return TYPE_MAPPING[self.type]

  @staticmethod
  def _decode_string(raw):
    raw = raw.rstrip().replace('\t', ' ')
    # Find name
    for idx in range(len(raw) - 1, 0, -1):
      if raw[idx] not in (string.ascii_letters + string.digits + '_'):
        break

    type_, name = raw[:idx + 1], raw[idx + 1:]
    return type_, name

  @classmethod
  def from_string(cls, raw):
    type_, name = cls._decode_string(raw)
    return cls(name.strip(), type_.strip())

  def to_string(self):
    return '{} {}'.format(self.type, self.name)


class BufferArgument(Argument):

  def __init__(self, arg1, arg2):
    self.arg1 = arg1
    self.arg2 = arg2

  @property
  def protobuf_type(self):
    return Optional(BufferProtobufType(self.arg1.name))

  @property
  def name(self):
    return self.arg1.name


class FlagsArgument(Argument):

  def __init__(self, syscall_message_name, argument_name):
    self.syscall_message_name = syscall_message_name
    self.name = argument_name

  @property
  def protobuf_type(self):
    return Optional(self.syscall_message_name + 'Flags')


def arguments_form_buffer(argument, next_argument):
  if next_argument.name == argument.name + 'size':
    return True
  if next_argument.name == argument.name + '_size':
    return True
  if next_argument.name == argument.name + 'len':
    return True
  if next_argument.name in ('length', 'bufferSize', 'nbyte'):
    return True
  if next_argument.name == 'bufferSize':
    return True
  if (argument.name, next_argument.name) in (
      ('buffer', 'bufsize'),
      ('useraddr', 'usersize'),
      ('buffer', 'size'),
      ('value', 'size'),
      # TODO(nedwill): for kdebug_typefilter we're really receiving size bytes,
      # not sending [addr, addr+size)
      ('addr', 'size'),
      ('addr', 'len'),
      ('in_buffer', 'in_buffer_length'),
      # TODO(nedwill): used to store results not send bytes
      ('out_buffer', 'out_buffer_length'),
  ):
    return True
  return False


class Syscall:

  def __init__(self, name, return_type, original_arguments, arguments):
    self.name = name
    self.return_type = return_type
    self.original_arguments = original_arguments
    self.arguments = arguments

  @staticmethod
  def _get_message_name(name):
    return ''.join([e.capitalize() for e in name.split('_') if e])

  @property
  def message_name(self):
    return self._get_message_name(self.name)

  @property
  def message(self):
    output = 'message {} {{\n'.format(self.message_name)
    for i, argument in enumerate(self.arguments):
      if not argument.protobuf_type.used:
        continue
      output += '  {} {} {} = {};\n'.format(argument.protobuf_type.field_type,
                                            argument.protobuf_type.type,
                                            argument.name, i + 1)
    output += '}'
    return output

  @property
  def wrapper_prototype(self):
    args = self.original_arguments + [
        Argument('retval', self.return_type + '*')
    ]
    output = 'int {}({})'.format(self.name + '_wrapper',
                                    ', '.join(arg.to_string() for arg in args))
    return output

  @property
  def wrapper_impl(self):
    output = ''
    output += '__attribute__((visibility("default"))) {} {{\n'.format(self.wrapper_prototype)
    output += '  struct {}_args uap = {{\n'.format(self.name)
    for arg in self.original_arguments:
      output += '    .{} = {},\n'.format(arg.name, arg.name)
    output += '  };\n'
    output += '  return {}(kernproc, &uap, retval);\n'.format(self.name)
    output += '}\n'
    return output

  @property
  def wrapper_real(self):
    output = ''
    output += '__attribute__((visibility("default"))) {} {{\n'.format(self.wrapper_prototype)
    args = []
    for arg in self.original_arguments:
      args.append(arg.name)
    output += '  return {}({});\n'.format(self.name, ', '.join(args))
    output += '}\n'
    return output

  @classmethod
  def from_function(cls, function):
    return_type = function.split(b' ')[0].decode()
    name = function.split(b'(')[0].split(b' ')[1].decode()
    argument_substring = function.split(b'(')[1].split(b')')[0]

    original_arguments = []
    arguments = []

    if argument_substring != b'void':
      args = [arg.strip().decode() for arg in argument_substring.split(b',')]
      idx = 0
      while idx < len(args):
        argument = Argument.from_string(args[idx])
        original_arguments.append(argument)

        # Check for buffer case
        if idx + 1 < len(args):
          next_argument = Argument.from_string(args[idx + 1])
          # TODO(nedwill): this is definitely not the only case for this
          if arguments_form_buffer(argument, next_argument):
            original_arguments.append(next_argument)
            argument = BufferArgument(argument, next_argument)
            idx += 1

        # Check for flags case
        elif argument.name == 'flags':
          # TODO(nedwill): assert argument.type.is_integer
          assert argument.type in ('int', 'short', 'uint32_t', 'unsigned int',
                                   'uint64_t', 'u_int')
          argument = FlagsArgument(cls._get_message_name(name), argument.name)

        # TODO(nedwill): remove this hack once we find all void* usage
        elif (name, argument.name) in (('fmount', 'data'),
                                       ('iopolicysys', 'arg'), ('kevent_id',
                                                                'data_out')):
          argument.type = 'user_addr_t'

        arguments.append(argument)
        idx += 1

    return cls(name, return_type, original_arguments, arguments)

  @classmethod
  def from_line(cls, line):
    if b'\t' not in line:
      return None
    if b'{' not in line:
      return None
    if b'}' not in line:
      return None
    function = line.split(b'}')[0].split(b'{')[1].strip()
    return cls.from_function(function)


class SyscallTracker:

  def __init__(self, prefix=0, use_allowlist=False):
    """If prefix is non-0, only first 0 of sorted"""
    with open('bsd/kern/syscalls.master', 'rb') as fd:
      data = fd.read()
    syscalls = {}
    for line in data.splitlines():
      try:
        syscall = Syscall.from_line(line)
      except:
        print('failed to decode', line)
        raise
      if syscall is None:
        continue
      # We intentionally ignore duplicate syscalls (e.g. nosys)
      if syscall.name in syscalls:
        continue
      if use_allowlist and syscall.name not in ALLOWLIST:
        continue
      syscalls[syscall.name] = syscall
    self.syscalls = list(
        sorted(syscalls.values(), key=lambda syscall: syscall.name))
    if prefix:
      self.syscalls = self.syscalls[:prefix]

  def generate_protobuf(self):
    output = 'message GeneratedCommands {\n'
    output += '  oneof command {\n'
    for i, syscall in enumerate(self.syscalls):
      output += '    {} {} = {};\n'.format(syscall.message_name, syscall.name,
                                           i + 1)
    output += '  }\n'
    output += '}\n\n'

    syscall_output = []
    for syscall in self.syscalls:
      try:
        syscall_output.append(syscall.message)
      except:
        print('bug in message generation for', syscall.name)
        raise
    output += '\n\n'.join(syscall_output)

    return output

  def generate_syscall_wrappers_header(self):
    output = '#ifndef SYSCALL_WRAPPERS_H_\n'
    output += '#define SYSCALL_WRAPPERS_H_\n\n'
    output += '#include <stddef.h>\n'
    output += '#include <stdint.h>\n'
    output += 'typedef unsigned char uuid_t[16];\n'
    output += """typedef u_int64_t user_addr_t;
typedef u_int32_t socklen_t;
typedef struct sa_endpoints {
	unsigned int		sae_srcif;	/* optional source interface */
	const struct sockaddr	*sae_srcaddr;   /* optional source address */
	socklen_t		sae_srcaddrlen; /* size of source address */
	const struct sockaddr	*sae_dstaddr;   /* destination address */
	socklen_t		sae_dstaddrlen; /* size of destination address */
} sa_endpoints_t;
typedef __uint32_t sae_associd_t;
typedef __uint32_t sae_connid_t;\n"""
    output += '\n'

    for syscall in self.syscalls:
      output += syscall.wrapper_prototype + ';\n'

    output += '\n#endif  // SYSCALL_WRAPPERS_H_\n'
    return output

  def generate_syscall_wrappers_impl(self):
    output = '#include "fuzz/api/syscall_wrappers.h"\n\n'
    syscall_impls = []
    for syscall in self.syscalls:
      syscall_impls.append(syscall.wrapper_impl)
    output += '\n'.join(syscall_impls)
    return output

  def generate_syscall_wrappers_real(self):
    output = '#include "fuzz/api/syscall_wrappers.h"\n\n'
    syscall_impls = []
    for syscall in self.syscalls:
      syscall_impls.append(syscall.wrapper_real)
    output += '\n'.join(syscall_impls)
    return output

  def generate_calling_code(self):
    raise Unimplemented


if __name__ == '__main__':
  tracker = SyscallTracker(use_allowlist=True)
  print(tracker.generate_protobuf())
  print(tracker.generate_syscall_wrappers_header())
  print(tracker.generate_syscall_wrappers_impl())
  print(tracker.generate_syscall_wrappers_real())
