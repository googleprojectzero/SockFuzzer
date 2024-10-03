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

#ifndef MACH_TYPES_H_
#define MACH_TYPES_H_

extern "C" {
#include <mach/message.h>
}

#include <cstdint>
#include <vector>

#include "fuzz/proto/mach_message.pb.h"
#include "fuzz/xnu/osfmk/api/backend.h"
#include "fuzz/xnu/osfmk/api/types.h"
#include "third_party/bootstrap_cmds/mig_generated.pb.h"

class MachMsg;
class MachMsgDescriptor;
class MachMsgOolDescriptor;
class MachMsgOolPortsDescriptor;
class MachMsgPortDescriptor;
class MachPort;
class MachPortName;
enum MachMsgTypeName : int;

std::vector<uint8_t> GetMachMsgDescriptor(const MachMsgDescriptor &descriptor);
mach_msg_type_name_t GetMachMsgTypeName(const MachMsgTypeName &type_name);
mach_port_t GetMachPort(const MachPort &port);
mach_port_name_t GetMachPortName(const MachPortName &name);
std::vector<uint8_t> GetMachMsg(const MachMsg &msg);
std::vector<uint8_t> GetMachMsgPortDescriptor(
    const MachMsgPortDescriptor &port_descriptor);
std::vector<uint8_t> GetMachMsgOolDescriptor(
    const MachMsgOolDescriptor &ool_descriptor);
std::vector<uint8_t> GetMachMsgOolPortsDescriptor(
    const MachMsgOolPortsDescriptor &ool_ports);
std::vector<uint8_t> GetMachMsgStruct(
    mach_msg_type_name_t remote_type, mach_port_t remote_port,
    mach_msg_type_name_t local_type, mach_port_t local_port,
    mach_msg_type_name_t voucher_type, mach_port_t voucher_port,
    mach_msg_id_t msgh_id, std::vector<uint8_t> inline_data,
    const std::vector<std::vector<uint8_t>> &descriptors);

int HandleMachMsg2(const MachMsg2Trap &trap);

#endif
