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

#include "fuzz/handlers/mig_types.h"

#include <cstring>
#include <mach/message.h>

#include <algorithm>
#include <string>

#include "fuzz/handlers/mach_message.h"
#include "fuzz/handlers/mig_generated.h"
#include "fuzz/proto/mig_types.pb.h"
#include "fuzz/xnu/osfmk/api/backend.h"

class MigRoutine;

/*
 * MIG supported protocols for Network Data Representation
 */
#define NDR_PROTOCOL_2_0 0

/*
 * NDR 2.0 format flag type definition and values.
 */
#define NDR_INT_BIG_ENDIAN 0
#define NDR_INT_LITTLE_ENDIAN 1
#define NDR_FLOAT_IEEE 0
#define NDR_FLOAT_VAX 1
#define NDR_FLOAT_CRAY 2
#define NDR_FLOAT_IBM 3
#define NDR_CHAR_ASCII 0
#define NDR_CHAR_EBCDIC 1

// mach_port_t GetTaskPort(const TaskPort &port) {
//   // TODO(nedwill): support other tasks
//   return task_self_trap_wrapper();
// }

#define VM_PROT_READ ((vm_prot_t)0x01)    /* read permission */
#define VM_PROT_WRITE ((vm_prot_t)0x02)   /* write permission */
#define VM_PROT_EXECUTE ((vm_prot_t)0x04) /* execute permission */

vm_prot_t GetVmProt(const VmProt &prot) {
  vm_prot_t result = 0;
  if (prot.read()) {
    result |= VM_PROT_READ;
  }
  if (prot.write()) {
    result |= VM_PROT_WRITE;
  }
  if (prot.execute()) {
    result |= VM_PROT_EXECUTE;
  }
  return result;
}

#define VM_SYNC_ASYNCHRONOUS ((vm_sync_t)0x01)
#define VM_SYNC_SYNCHRONOUS ((vm_sync_t)0x02)
#define VM_SYNC_INVALIDATE ((vm_sync_t)0x04)
#define VM_SYNC_KILLPAGES ((vm_sync_t)0x08)
#define VM_SYNC_DEACTIVATE ((vm_sync_t)0x10)
#define VM_SYNC_CONTIGUOUS ((vm_sync_t)0x20)
#define VM_SYNC_REUSABLEPAGES ((vm_sync_t)0x40)

vm_sync_t GetVmSync(const VmSync &sync) {
  vm_sync_t result = 0;

  if (sync.asynchronous()) {
    result |= VM_SYNC_ASYNCHRONOUS;
  }
  if (sync.synchronous()) {
    result |= VM_SYNC_SYNCHRONOUS;
  }
  if (sync.invalidate()) {
    result |= VM_SYNC_INVALIDATE;
  }
  if (sync.killpages()) {
    result |= VM_SYNC_KILLPAGES;
  }
  if (sync.deactivate()) {
    result |= VM_SYNC_DEACTIVATE;
  }
  if (sync.contiguous()) {
    result |= VM_SYNC_CONTIGUOUS;
  }
  if (sync.reusablepages()) {
    result |= VM_SYNC_REUSABLEPAGES;
  }

  return result;
}

vm_behavior_t GetVmBehavior(const VmBehavior &behavior) {
  return behavior;
}

std::vector<uint8_t> GetMigRoutineMsg(const MigRoutine &routine,
                                      mach_msg_type_name_t remote_type,
                                      mach_port_name_t remote_port,
                                      mach_msg_type_name_t local_type,
                                      mach_port_name_t local_port,
                                      mach_msg_type_name_t voucher_type,
                                      mach_port_name_t voucher_port) {
  mach_msg_id_t msgh_id = 0;
  std::vector<std::vector<uint8_t>> descriptors;
  std::vector<uint8_t> data =
      GetMigRoutineMsgData(routine, &msgh_id, &descriptors);
  if (!msgh_id) {
    return {};
  }
  return GetMachMsgStruct(remote_type, remote_port, local_type, local_port,
                          voucher_type, voucher_port, msgh_id, data,
                          descriptors);
}

mach_port_qos_t GetMachPortQos(const MachPortQos &qos) {
  mach_port_qos_t result = {
      .name = qos.name(),
      .prealloc = qos.prealloc(),
      .len = static_cast<natural_t>(qos.len()),
  };
  return result;
}

mach_timespec_t GetMachTimespec(const MachTimespec &timespec) {
  mach_timespec_t result = {
      .tv_sec = static_cast<unsigned int>(timespec.a1()),
      .tv_nsec = static_cast<clock_res_t>(timespec.a2()),
  };
  return result;
}

mach_zone_name_t GetMachZoneName(const MachZoneName &zone_name) {
  mach_zone_name_t result;
  size_t size = zone_name.mzn_name().size();
  if (size > sizeof(result.mzn_name)) {
    size = sizeof(result.mzn_name);
  }
  memcpy(result.mzn_name, zone_name.mzn_name().data(), size);
  return result;
}

dyld_kernel_image_info GetDyldKernelImageInfo(const DyldKernelImageInfo &info) {
  dyld_kernel_image_info result = {};
  size_t size = info.uuid().size();
  if (size > sizeof(result.uuid)) {
    size = sizeof(result.uuid);
  }
  memcpy(&result.uuid, info.uuid().data(), size);
  result.fsobjid.fid_objno = info.fs_obj_id().fid_objno();
  result.fsobjid.fid_generation = info.fs_obj_id().fid_generation();
  result.fsid[0] = info.fsid().id1();
  result.fsid[1] = info.fsid().id2();
  result.load_addr = info.load_addr();
  return result;
}

audit_token_t GetAuditToken(const AuditToken &info) {
  audit_token_t audit_token = {};
  size_t size = info.val().size();
  if (size > sizeof(audit_token)) {
    size = sizeof(audit_token);
  }

  memcpy(&audit_token.val[0], info.val().data(), size);

  return audit_token;
}

security_token_t GetSecurityToken(const SecurityToken &token) {
  security_token_t security_token = {static_cast<unsigned int>(token.token1()),
                                     static_cast<unsigned int>(token.token2())};
  return security_token;
}


// extern NDR_record_t NDR_record;
// NDR_record_t NDR_record = {
//     0, /* mig_reserved */
//     0, /* mig_reserved */
//     0, /* mig_reserved */
//     NDR_PROTOCOL_2_0,
//     NDR_INT_LITTLE_ENDIAN,
//     NDR_CHAR_ASCII,
//     NDR_FLOAT_IEEE,
//     0,
// };