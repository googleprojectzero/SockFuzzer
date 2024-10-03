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

#ifndef MIG_TYPES_H_
#define MIG_TYPES_H_

extern "C" {
#include "fuzz/xnu/osfmk/api/types.h"
#include "third_party/bootstrap_cmds/include/mach/message.h"
}

#include <cstdint>
#include <vector>

#include "fuzz/proto/mig_types.pb.h"
#include "fuzz/xnu/osfmk/api/backend.h"
#include "third_party/bootstrap_cmds/mig_generated.pb.h"

class AuditToken;
class DyldKernelImageInfo;
class MachPortQos;
class MachTimespec;
class MachZoneName;
class MigRoutine;
class SecurityToken;
class TaskPort;
class VmProt;
class VmSync;
enum VmBehavior : int;

typedef struct {
  unsigned char mig_vers;
  unsigned char if_vers;
  unsigned char reserved1;
  unsigned char mig_encoding;
  unsigned char int_rep;
  unsigned char char_rep;
  unsigned char float_rep;
  unsigned char reserved2;
} NDR_record_t;

extern NDR_record_t NDR_record;

// mach_port_t GetTaskPort(const TaskPort &port);
vm_prot_t GetVmProt(const VmProt &prot);
vm_sync_t GetVmSync(const VmSync &sync);
vm_behavior_t GetVmBehavior(const VmBehavior &behavior);
std::vector<uint8_t> GetMigRoutineMsg(const MigRoutine &routine,
                                      mach_msg_type_name_t remote_type,
                                      mach_port_name_t remote_port,
                                      mach_msg_type_name_t local_type,
                                      mach_port_name_t local_port,
                                      mach_msg_type_name_t voucher_type,
                                      mach_port_name_t voucher_port);
mach_port_qos_t GetMachPortQos(const MachPortQos &qos);
mach_timespec_t GetMachTimespec(const MachTimespec &timespec);
mach_zone_name_t GetMachZoneName(const MachZoneName &zone_name);
dyld_kernel_image_info GetDyldKernelImageInfo(const DyldKernelImageInfo &info);
audit_token_t GetAuditToken(const AuditToken &info);
security_token_t GetSecurityToken(const SecurityToken &token);

#endif
