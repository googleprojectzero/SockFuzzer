/*
 * Copyright 2024 Google LLC
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */

#include "fuzz/handlers/mach_message.h"

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "absl/strings/str_format.h"
#include "fuzz/host/host.h"
#include "fuzz/proto/common.pb.h"
#include "fuzz/proto/mach_message.pb.h"

struct mach_msg_base_t {
  mach_msg_header_t header;
  mach_msg_body_t body;
} __attribute__((aligned(32)));

mach_port_t GetMachPort(const MachPort &port) {
  return (port.port() == PortNumberMach::CASE_NEGATIVE) ? 0xFFFFFFFFU
                                                        : port.port();
}

// TODO(nedwill): figure out how this is different from mach_port_t
mach_port_name_t GetMachPortName(const MachPortName &name) {
  return GetMachPort(name.port());
}

mach_msg_type_name_t GetMachMsgTypeName(const MachMsgTypeName &type_name) {
  return type_name;
}

std::vector<uint8_t> GetMachMsgPortDescriptor(
    const MachMsgPortDescriptor &port_descriptor) {
  mach_msg_port_descriptor_t result = {
      .name = GetMachPort(port_descriptor.name()),
      .disposition = GetMachMsgTypeName(port_descriptor.disposition()),
      .type = MACH_MSG_PORT_DESCRIPTOR};

  return {reinterpret_cast<uint8_t *>(&result),
          reinterpret_cast<uint8_t *>(&result) + sizeof(result)};
}

mach_msg_copy_options_t GetMachMsgCopyOptions(
    const MachMsgCopyOptions &copy_options) {
  return copy_options;
}

std::vector<uint8_t> GetMachMsgOolDescriptor(
    const MachMsgOolDescriptor &ool_descriptor) {
  mach_msg_ool_descriptor_t result = {
      // TODO(nedwill): get OOL data from the message itself
      .address = (void *)1,
      .deallocate = ool_descriptor.deallocate(),
      .copy = GetMachMsgCopyOptions(ool_descriptor.copy()),
      .type = MACH_MSG_OOL_DESCRIPTOR,
      .size = ool_descriptor.size()};

  return {reinterpret_cast<uint8_t *>(&result),
          reinterpret_cast<uint8_t *>(&result) + sizeof(result)};
}

std::vector<uint8_t> GetMachMsgOolDescriptorVolatile(
    const MachMsgOolDescriptor &ool_descriptor) {
  mach_msg_ool_descriptor_t result = {
      .address = (void *)1,
      .deallocate = ool_descriptor.deallocate(),
      .copy = GetMachMsgCopyOptions(ool_descriptor.copy()),
      .type = MACH_MSG_OOL_VOLATILE_DESCRIPTOR,
      .size = ool_descriptor.size()};

  return {reinterpret_cast<uint8_t *>(&result),
          reinterpret_cast<uint8_t *>(&result) + sizeof(result)};
}

std::vector<uint8_t> GetMachMsgOolPortsDescriptor(
    const MachMsgOolPortsDescriptor &ool_ports) {
  mach_msg_ool_ports_descriptor_t result = {
      // TODO(nedwill): pass ownership of names back up to caller so we can
      // actually
      // specify them in our test case
      .address = (void *)1,  // ool_ports.names.data(),
      .deallocate = ool_ports.deallocate(),
      .copy = GetMachMsgCopyOptions(ool_ports.copy()),
      .disposition = GetMachMsgTypeName(ool_ports.disposition()),
      .type = MACH_MSG_OOL_PORTS_DESCRIPTOR,
      .count = static_cast<mach_msg_size_t>(ool_ports.names().size()),
  };

  return {reinterpret_cast<uint8_t *>(&result),
          reinterpret_cast<uint8_t *>(&result) + sizeof(result)};
}

std::vector<uint8_t> GetMachMsgGuardedPortDescriptor(
    const MachMsgGuardedPortDescriptor &guarded_port) {
  mach_msg_guarded_port_descriptor_t result = {
      .context = static_cast<user_addr_t>(guarded_port.context()),
      .flags = static_cast<mach_msg_guard_flags_t>(guarded_port.flags()),
      .disposition = GetMachMsgTypeName(guarded_port.disposition()),
      .type = MACH_MSG_GUARDED_PORT_DESCRIPTOR,
      .name = GetMachPortName(guarded_port.name())};

  return {reinterpret_cast<uint8_t *>(&result),
          reinterpret_cast<uint8_t *>(&result) + sizeof(result)};
}

std::vector<uint8_t> GetMachMsgDescriptor(const MachMsgDescriptor &descriptor) {
  switch (descriptor.descriptor_case()) {
    case MachMsgDescriptor::kPort: {
      return GetMachMsgPortDescriptor(descriptor.port());
    }
    case MachMsgDescriptor::kOutOfLine: {
      return GetMachMsgOolDescriptor(descriptor.out_of_line());
    }
    case MachMsgDescriptor::kOolPorts: {
      return GetMachMsgOolPortsDescriptor(descriptor.ool_ports());
    }
    case MachMsgDescriptor::kGuardedPort: {
      return GetMachMsgGuardedPortDescriptor(descriptor.guarded_port());
    }
    case MachMsgDescriptor::kOutOfLineVolatile: {
      return GetMachMsgOolDescriptorVolatile(descriptor.out_of_line_volatile());
    }
    case MachMsgDescriptor::DESCRIPTOR_NOT_SET: {
      return {};
    }
  }
  return {};
}

std::vector<uint8_t> GetMachMsgStruct(
    mach_msg_type_name_t remote_type, mach_port_t remote_port,
    mach_msg_type_name_t local_type, mach_port_t local_port,
    mach_msg_type_name_t voucher_type, mach_port_t voucher_port,
    mach_msg_id_t msgh_id, std::vector<uint8_t> inline_data,
    const std::vector<std::vector<uint8_t>> &descriptors) {
  unsigned int other = 0;
  size_t size = sizeof(mach_msg_header_t);
  // printf("sizeof header %lu\n", size);

  if (!descriptors.empty()) {
    // TODO(nedwill): consider fuzzing more options
    other = MACH_MSGH_BITS_COMPLEX;
    size += sizeof(mach_msg_body_t);
    for (const auto &descriptor : descriptors) {
      size += descriptor.size();
    }
  }
  // printf("base size %zu\n", size);

  mach_msg_header_t message_header = {
      .msgh_bits =
          MACH_MSGH_BITS_SET(remote_type, local_type, voucher_type, other),
      .msgh_remote_port = remote_port,
      .msgh_local_port = local_port,
      .msgh_voucher_port = voucher_port,
      .msgh_id = msgh_id};

  // printf("inline data size %zu\n", inline_data.size());
  size += inline_data.size();

  // Finally ready to update the size in the header
  message_header.msgh_size = size;

  auto result = std::vector<uint8_t>(size);

  size_t i = 0;
  memcpy(result.data(), &message_header, sizeof(message_header));
  i += sizeof(message_header);
  if (!descriptors.empty()) {
    mach_msg_body_t body = {
        .msgh_descriptor_count =
            static_cast<mach_msg_size_t>(descriptors.size())};
    memcpy(result.data() + i, reinterpret_cast<uint8_t *>(&body), sizeof(body));
    i += sizeof(body);
  }
  for (const auto &descriptor : descriptors) {
    memcpy(result.data() + i, descriptor.data(), descriptor.size());
    i += descriptor.size();
  }
  memcpy(result.data() + i, inline_data.data(), inline_data.size());
  i += inline_data.size();
  if (i != size) {
    abort();
  }
  return result;
}

std::vector<uint8_t> GetMachMsg(const MachMsg &msg) {
  if (!msg.has_header()) {
    return {msg.data().begin(), msg.data().end()};
  }

  const MachMsgHeader &header = msg.header();
  const MachMsgHeaderBits &bits = header.msgh_bits();

  std::vector<std::vector<std::uint8_t>> descriptors;
  for (const auto &descriptor : msg.body()) {
    if (descriptor.descriptor_case() == MachMsgDescriptor::DESCRIPTOR_NOT_SET) {
      continue;
    }
    descriptors.push_back(GetMachMsgDescriptor(descriptor));
  }

  return GetMachMsgStruct(
      GetMachMsgTypeName(bits.remote()), GetMachPort(header.msgh_remote_port()),
      GetMachMsgTypeName(bits.local()), GetMachPort(header.msgh_local_port()),
      GetMachMsgTypeName(bits.voucher()),
      GetMachPortName(header.msgh_voucher_port()), header.msgh_id(),
      {msg.data().begin(), msg.data().end()}, descriptors);
}
