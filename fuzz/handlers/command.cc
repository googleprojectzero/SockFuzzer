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

#include "fuzz/handlers/command.h"

#include <algorithm>
#include <cassert>
#include <csetjmp>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#include "absl/strings/str_format.h"
#include "fuzz/common/utility.h"
#include "fuzz/handlers/bsd_types.h"
#include "fuzz/handlers/mach_message.h"
#include "fuzz/handlers/mig_types.h"
#include "fuzz/host/host.h"
#include "fuzz/host/hypercall/hypercall.h"
#include "fuzz/proto/bsd.pb.h"
#include "fuzz/proto/bsd_types.pb.h"
#include "fuzz/proto/common.pb.h"
#include "fuzz/proto/mach_traps.pb.h"
#include "fuzz/proto/session.pb.h"
#include "fuzz/xnu/bsd/api/backend.h"
#include "fuzz/xnu/bsd/api/ioctl.h"
#include "fuzz/xnu/osfmk/api/backend.h"
#include "fuzz/xnu/osfmk/api/types.h"
#include "third_party/bootstrap_cmds/include/mach/message.h"
#include "tools/generate_syscall/call_bsd_syscall.h"
#include "tools/generate_syscall/syscall_wrappers_generated.h"

struct __jmp_buf_tag;

vm_prot_t GetProtection(const ::google::protobuf::RepeatedField<int> &prot) {
  vm_prot_t result = 0;
  for (const auto &flag : prot) {
    result |= flag;
  }
  return result;
}

// "bsd/sys/kern_control.h"
struct sockaddr_ctl {
  u_char sc_len;        /* depends on size of bundle ID string */
  u_char sc_family;     /* AF_SYSTEM */
  u_int16_t ss_sysaddr; /* AF_SYS_KERNCONTROL */
  u_int32_t sc_id;      /* Controller unique identifier  */
  u_int32_t sc_unit;    /* Developer private unit number */
  u_int32_t sc_reserved[5];
};

struct user_nfsd_args {
  int sock; /* Socket to serve */
  user_addr_t name
      __attribute((aligned(8))); /* Client addr for connection based sockets */
  int namelen;                   /* Length of name */
};

// TODO(nedwill): move this function to XNU side since the values don't match
// Linux. To update this list use third_party/xnu/bsd/sys/errno.h
std::string ErrorToString(int error) {
  switch (error) {
    case 0: {
      return "SUCCESS";
    }
    case 102: {
      return "EOPNOTSUPP";
    }
    case 52: {
      return "ENETRESET";
    }
    case 22: {
      return "EINVAL";
    }
    case 13: {
      return "EACCES";
    }
    case 41: {
      return "EPROTOTYPE";
    }
    case 9: {
      return "EBADF";
    }
    case 17: {
      return "EEXIST";
    }
    default: {
      g_host->Log(absl::StrFormat("Unknown error code %d\n", error));
      GetHypercallInterface()->Abort();
    }
  }
}

namespace {

absl::flat_hash_map<MachMsgReturnT, std::string> mach_message_return_strings = {
	{MachMsgReturnT::MACH_MSG_SUCCESS, "MACH_MSG_SUCCESS"},
	{MachMsgReturnT::MACH_MSG_MASK, "MACH_MSG_MASK"},
	{MachMsgReturnT::MACH_MSG_IPC_SPACE, "MACH_MSG_IPC_SPACE"},
	{MachMsgReturnT::MACH_MSG_VM_SPACE, "MACH_MSG_VM_SPACE"},
	{MachMsgReturnT::MACH_MSG_IPC_KERNEL, "MACH_MSG_IPC_KERNEL"},
	{MachMsgReturnT::MACH_MSG_VM_KERNEL, "MACH_MSG_VM_KERNEL"},
	{MachMsgReturnT::MACH_SEND_IN_PROGRESS, "MACH_SEND_IN_PROGRESS"},
	{MachMsgReturnT::MACH_SEND_INVALID_DATA, "MACH_SEND_INVALID_DATA"},
	{MachMsgReturnT::MACH_SEND_INVALID_DEST, "MACH_SEND_INVALID_DEST"},
	{MachMsgReturnT::MACH_SEND_TIMED_OUT, "MACH_SEND_TIMED_OUT"},
	{MachMsgReturnT::MACH_SEND_INVALID_VOUCHER, "MACH_SEND_INVALID_VOUCHER"},
	{MachMsgReturnT::MACH_SEND_INTERRUPTED, "MACH_SEND_INTERRUPTED"},
	{MachMsgReturnT::MACH_SEND_MSG_TOO_SMALL, "MACH_SEND_MSG_TOO_SMALL"},
	{MachMsgReturnT::MACH_SEND_INVALID_REPLY, "MACH_SEND_INVALID_REPLY"},
	{MachMsgReturnT::MACH_SEND_INVALID_RIGHT, "MACH_SEND_INVALID_RIGHT"},
	{MachMsgReturnT::MACH_SEND_INVALID_NOTIFY, "MACH_SEND_INVALID_NOTIFY"},
	{MachMsgReturnT::MACH_SEND_INVALID_MEMORY, "MACH_SEND_INVALID_MEMORY"},
	{MachMsgReturnT::MACH_SEND_NO_BUFFER, "MACH_SEND_NO_BUFFER"},
	{MachMsgReturnT::MACH_SEND_TOO_LARGE, "MACH_SEND_TOO_LARGE"},
	{MachMsgReturnT::MACH_SEND_INVALID_TYPE, "MACH_SEND_INVALID_TYPE"},
	{MachMsgReturnT::MACH_SEND_INVALID_HEADER, "MACH_SEND_INVALID_HEADER"},
	{MachMsgReturnT::MACH_SEND_INVALID_TRAILER, "MACH_SEND_INVALID_TRAILER"},
	{MachMsgReturnT::MACH_SEND_INVALID_CONTEXT, "MACH_SEND_INVALID_CONTEXT"},
	{MachMsgReturnT::MACH_SEND_INVALID_OPTIONS, "MACH_SEND_INVALID_OPTIONS"},
	{MachMsgReturnT::MACH_SEND_INVALID_RT_OOL_SIZE, "MACH_SEND_INVALID_RT_OOL_SIZE"},
	{MachMsgReturnT::MACH_SEND_NO_GRANT_DEST, "MACH_SEND_NO_GRANT_DEST"},
	{MachMsgReturnT::MACH_SEND_MSG_FILTERED, "MACH_SEND_MSG_FILTERED"},
	{MachMsgReturnT::MACH_SEND_AUX_TOO_SMALL, "MACH_SEND_AUX_TOO_SMALL"},
	{MachMsgReturnT::MACH_SEND_AUX_TOO_LARGE, "MACH_SEND_AUX_TOO_LARGE"},
	{MachMsgReturnT::MACH_RCV_IN_PROGRESS, "MACH_RCV_IN_PROGRESS"},
	{MachMsgReturnT::MACH_RCV_INVALID_NAME, "MACH_RCV_INVALID_NAME"},
	{MachMsgReturnT::MACH_RCV_TIMED_OUT, "MACH_RCV_TIMED_OUT"},
	{MachMsgReturnT::MACH_RCV_TOO_LARGE, "MACH_RCV_TOO_LARGE"},
	{MachMsgReturnT::MACH_RCV_INTERRUPTED, "MACH_RCV_INTERRUPTED"},
	{MachMsgReturnT::MACH_RCV_PORT_CHANGED, "MACH_RCV_PORT_CHANGED"},
	{MachMsgReturnT::MACH_RCV_INVALID_NOTIFY, "MACH_RCV_INVALID_NOTIFY"},
	{MachMsgReturnT::MACH_RCV_INVALID_DATA, "MACH_RCV_INVALID_DATA"},
	{MachMsgReturnT::MACH_RCV_PORT_DIED, "MACH_RCV_PORT_DIED"},
	{MachMsgReturnT::MACH_RCV_IN_SET, "MACH_RCV_IN_SET"},
	{MachMsgReturnT::MACH_RCV_HEADER_ERROR, "MACH_RCV_HEADER_ERROR"},
	{MachMsgReturnT::MACH_RCV_BODY_ERROR, "MACH_RCV_BODY_ERROR"},
	{MachMsgReturnT::MACH_RCV_INVALID_TYPE, "MACH_RCV_INVALID_TYPE"},
	{MachMsgReturnT::MACH_RCV_SCATTER_SMALL, "MACH_RCV_SCATTER_SMALL"},
	{MachMsgReturnT::MACH_RCV_INVALID_TRAILER, "MACH_RCV_INVALID_TRAILER"},
	{MachMsgReturnT::MACH_RCV_IN_PROGRESS_TIMED, "MACH_RCV_IN_PROGRESS_TIMED"},
	{MachMsgReturnT::MACH_RCV_INVALID_REPLY, "MACH_RCV_INVALID_REPLY"},
	{MachMsgReturnT::MACH_RCV_INVALID_ARGUMENTS, "MACH_RCV_INVALID_ARGUMENTS"},
};

std::string MachMessageReturnValueToString(mach_msg_return_t rv) {
  auto it = mach_message_return_strings.find(static_cast<MachMsgReturnT>(rv));
  if (it != mach_message_return_strings.end()) {
    return it->second;
  }
  return absl::StrFormat("MachMessageReturnValueToString: Unknown Mach message return value: 0x%x", rv);
}

}

int CommandHandler::HandleMachMsg2(const MachMsg2Trap &trap) const {
  std::vector<uint8_t> message;
  mach_vm_address_t data = 0;
  if (trap.has_data()) {
    message = GetMachMsg(trap.data());
    data = reinterpret_cast<mach_vm_address_t>(message.data());
  }

  // Start out with upper-most bit set for msg2
  uint64_t options = 0x80000000ULL << 32;
  for (const auto &option : trap.options()) {
    options |= option;
  }
  for (const auto &option : trap.options_upper_bits()) {
    options |= (static_cast<uint64_t>(option) << 32);
  }

  uint64_t send_size = message.size();
  uint64_t msgh_bits =
      MACH_MSGH_BITS_SET(trap.data().header().msgh_bits().remote(),
                         trap.data().header().msgh_bits().local(),
                         trap.data().header().msgh_bits().voucher(), 0);

  uint64_t msgh_bits_and_send_size = (send_size << 32) | msgh_bits;

  mach_port_name_t remote_port = GetMachPortName(trap.msgh_remote_port());
  mach_port_name_t local_port = GetMachPortName(trap.msgh_local_port());
  auto msgh_remote_and_local_port =
      (static_cast<uint64_t>(remote_port) & 0xFFFFFFFF) |
      (static_cast<uint64_t>(local_port) << 32);

  mach_port_name_t voucher_port = GetMachPortName(trap.msgh_voucher_port());
  uint32_t msgh_id = trap.msgh_id();
  auto msgh_voucher_and_id =
      (static_cast<uint64_t>(voucher_port) & 0xFFFFFFFF) |
      (static_cast<uint64_t>(msgh_id) << 32);

  auto desc_count_and_rcv_name =
      (static_cast<uint64_t>(trap.desc_count()) & 0xFFFFFFFF) |
      (static_cast<uint64_t>(GetMachPortName(trap.rcv_name())) << 32);

  auto rcv_size_and_priority =
      (static_cast<uint64_t>(trap.rcv_size()) & 0xFFFFFFFF) |
      (static_cast<uint64_t>(trap.priority()) << 32);

  auto timeout = trap.timeout();

  host_->Log("mach_msg2_trap()\n");
  mach_msg_return_t err = mach_msg2_trap_wrapper(
      data, options, msgh_bits_and_send_size, msgh_remote_and_local_port,
      msgh_voucher_and_id, desc_count_and_rcv_name, rcv_size_and_priority,
      timeout);
  host_->Log(absl::StrFormat("mach_msg2_trap return %s\n", MachMessageReturnValueToString(err)));
  return err;
}

int CommandHandler::HandleMachPortAllocate(const MachPortAllocateTrap &trap, mach_port_name_t* name) const {
  host_->Log("mach_port_allocate_trap()\n");
  mach_msg_return_t err = _kernelrpc_mach_port_allocate_trap_wrapper(
      GetMachPortName(trap.target()), trap.right(), reinterpret_cast<user_addr_t>(name));
  host_->Log(absl::StrFormat("mach_port_allocate_trap return: %s\n", MachMessageReturnValueToString(err)));
  return err;
}

int CommandHandler::HandleMachPortDeallocate(
    const MachPortDeallocateTrap &trap) const {
  host_->Log("mach_port_deallocate_trap()\n");
  mach_msg_return_t err = _kernelrpc_mach_port_deallocate_trap_wrapper(
      GetMachPortName(trap.target()), GetMachPortName(trap.name()));
  host_->Log(absl::StrFormat("mach_port_deallocate_trap return 0x%x\n", err));
  return err;
}

int CommandHandler::HandleTaskSelfTrap() const {
  const int rv = task_self_trap_wrapper();
  host_->Log(absl::StrFormat("task_self_trap_wrapper() -> %d\n", rv));
  return rv;
}

void CommandHandler::HandleCommand(const Command &command) {
  // host_->Log("Saving CommandThread entrypoint\n");
  __jmp_buf_tag *jmp_buf = host_->SetKernelEntryPoint();
  if (setjmp(jmp_buf)) {
    // host_->Log("syscall_return to CommandThread\n");
    return;
  }

  int retval = 0;
  switch (command.command_case()) {
    case Command::kMachVmAllocateTrap: {
      _kernelrpc_mach_vm_allocate_trap_wrapper(
          GetMachPortName(command.mach_vm_allocate_trap().target()), 1,
          command.mach_vm_allocate_trap().size(),
          command.mach_vm_allocate_trap().flags());
      break;
    }
    case Command::kMachVmPurgableControl: {
      _kernelrpc_mach_vm_purgable_control_trap_wrapper(
          GetMachPortName(command.mach_vm_purgable_control().target()),
          command.mach_vm_purgable_control().address(),
          command.mach_vm_purgable_control().control(), 1);
      break;
    }
    case Command::kMachVmDeallocateTrap: {
      _kernelrpc_mach_vm_deallocate_trap_wrapper(
          GetMachPortName(command.mach_vm_deallocate_trap().target()),
          command.mach_vm_deallocate_trap().address(),
          command.mach_vm_deallocate_trap().size());
      break;
    }
    case Command::kTaskDyldProcessInfoNotifyGet: {
      task_dyld_process_info_notify_get_trap_wrapper(
          // command.task_dyld_process_info_notify_get().names_addr(),
          // command.task_dyld_process_info_notify_get().names_count_addr()
          1, 1);
      break;
    }
    case Command::kMachVmProtectTrap: {
      _kernelrpc_mach_vm_protect_trap_wrapper(
          GetMachPortName(command.mach_vm_protect_trap().target()),
          command.mach_vm_protect_trap().address(),
          command.mach_vm_protect_trap().size(),
          static_cast<boolean_t>(command.mach_vm_protect_trap().set_maximum()),
          GetProtection(command.mach_vm_protect_trap().new_protection()));
      break;
    }
    case Command::kMachVmMapTrap: {
      _kernelrpc_mach_vm_map_trap_wrapper(
          GetMachPortName(command.mach_vm_map_trap().target()),
          // command.mach_vm_map_trap().addr(),
          1, command.mach_vm_map_trap().size(),
          command.mach_vm_map_trap().mask(), command.mach_vm_map_trap().flags(),
          GetProtection(command.mach_vm_map_trap().cur_protection()));
      break;
    }
    case Command::kMachPortAllocate: {
      mach_port_name_t name = 0;
      HandleMachPortAllocate(command.mach_port_allocate(), &name);
      break;
    }
    case Command::kMachPortDeallocate: {
      HandleMachPortDeallocate(command.mach_port_deallocate());
      break;
    }
    case Command::kMachPortModRefs: {
      _kernelrpc_mach_port_mod_refs_trap_wrapper(
          GetMachPortName(command.mach_port_mod_refs().target()),
          GetMachPortName(command.mach_port_mod_refs().name()),
          command.mach_port_mod_refs().right(),
          command.mach_port_mod_refs().delta());
      break;
    }
    case Command::kMachPortMoveMember: {
      _kernelrpc_mach_port_move_member_trap_wrapper(
          GetMachPortName(command.mach_port_move_member().target()),
          GetMachPortName(command.mach_port_move_member().member()),
          GetMachPortName(command.mach_port_move_member().after()));
      break;
    }
    case Command::kMachPortInsertRight: {
      const int ret = _kernelrpc_mach_port_insert_right_trap_wrapper(
          GetMachPortName(command.mach_port_insert_right().target()),
          GetMachPortName(command.mach_port_insert_right().name()),
          GetMachPortName(command.mach_port_insert_right().poly()),
          command.mach_port_insert_right().polypoly());
      host_->Log(absl::StrFormat(
          "mach_port_insert_right_trap_wrapper() -> %d\n", ret));
      break;
    }
    case Command::kMachPortInsertMember: {
      _kernelrpc_mach_port_insert_member_trap_wrapper(
          GetMachPortName(command.mach_port_insert_member().target()),
          GetMachPortName(command.mach_port_insert_member().name()),
          GetMachPortName(command.mach_port_insert_member().pset()));
      break;
    }
    case Command::kMachPortExtractMember: {
      _kernelrpc_mach_port_extract_member_trap_wrapper(
          GetMachPortName(command.mach_port_extract_member().target()),
          GetMachPortName(command.mach_port_extract_member().name()),
          GetMachPortName(command.mach_port_extract_member().pset()));
      break;
    }
    case Command::kMachPortConstruct: {
      uint64_t name = 0;

      const MachPortOptions &options_proto =
          command.mach_port_construct().options();

      uint32_t flags = 0;
      for (const auto &flag : options_proto.flags()) {
        flags |= flag;
      }

      mach_port_options_t options = {
          .flags = flags,
          .mpl =
              {
                  .mpl_qlimit = options_proto.limits().limit(),
              },
          .work_interval_port =
              GetMachPortName(options_proto.work_interval_port()),
      };
      int rv = task_self_trap_wrapper();
      host_->Log(absl::StrFormat("task_self_trap_wrapper() -> %d\n", rv));
      rv = _kernelrpc_mach_port_construct_trap_wrapper(
          GetMachPortName(command.mach_port_construct().target()),
          reinterpret_cast<user_addr_t>(&options),
          command.mach_port_construct().context(),
          reinterpret_cast<uintptr_t>(&name));
      if (rv == 0) {
        host_->Log(
            absl::StrFormat("mach_port_construct: got name %lu\n", name));
      } else {
        host_->Log(
            absl::StrFormat("mach_port_construct: failed with %d\n", rv));
      }
      break;
    }
    case Command::kMachPortDestruct: {
      host_->Log("mach_port_destruct()\n");
      _kernelrpc_mach_port_destruct_trap_wrapper(
          GetMachPortName(command.mach_port_destruct().target()),
          GetMachPortName(command.mach_port_destruct().name()),
          command.mach_port_destruct().srdelta(),
          command.mach_port_destruct().guard());
      break;
    }
    case Command::kMachReplyPort: {
      const int rv = mach_reply_port_wrapper();
      host_->Log(absl::StrFormat("mach_reply_port_wrapper() -> %d\n", rv));
      break;
    }
    case Command::kMachPortRequestNotificationTrap: {
      mach_port_name_t previous = 0;
      _kernelrpc_mach_port_request_notification_trap_wrapper(
          /*task=*/task_self_trap_wrapper(),
          // GetMachPortName(command.mach_port_request_notification_trap().target()),
          GetMachPortName(command.mach_port_request_notification_trap().name()),
          command.mach_port_request_notification_trap().msgid(),
          command.mach_port_request_notification_trap().sync(),
          GetMachPortName(
              command.mach_port_request_notification_trap().notify()),
          GetMachMsgTypeName(
              command.mach_port_request_notification_trap().notify_poly()),
          &previous);
      break;
    }
    case Command::kThreadSelf: {
      host_->Log("thread_self()\n");
      const int rv = thread_self_trap_wrapper();
      host_->Log(absl::StrFormat("thread_self_trap_wrapper() -> %d\n", rv));
      break;
    }
    case Command::kTaskSelf: {
      HandleTaskSelfTrap();
      break;
    }
    case Command::kHostSelf: {
      host_->Log("host_self()\n");
      const int rv = host_self_trap_wrapper();
      host_->Log(absl::StrFormat("host_self_trap_wrapper() -> %d\n", rv));
      break;
    }
    case Command::kMachMsg: {
      break;
      user_addr_t addr = 1;
      std::vector<uint8_t> message;
      if (command.mach_msg().has_msg()) {
        message = GetMachMsg(command.mach_msg().msg());
        addr = reinterpret_cast<user_addr_t>(message.data());
      }
      host_->Log("mach_msg()\n");
      int options = 0;
      for (const auto &option : command.mach_msg().options()) {
        options |= option;
      }
      mach_msg_trap_wrapper(
          addr, options, message.size(), command.mach_msg().rcv_size(),
          GetMachPortName(command.mach_msg().rcv_name()),
          command.mach_msg().timeout(), command.mach_msg().priority(),
          command.mach_msg().rcv_msg());
      break;
    }
    case Command::kMachMsgOverwrite: {
      user_addr_t addr = 1;
      std::vector<uint8_t> message;
      if (command.mach_msg_overwrite().has_msg()) {
        message = GetMachMsg(command.mach_msg_overwrite().msg());
        addr = reinterpret_cast<user_addr_t>(message.data());
      }
      host_->Log("mach_msg_overwrite()\n");
      int options = 0;
      for (const auto &option : command.mach_msg_overwrite().options()) {
        options |= option;
      }
      const int err = mach_msg_overwrite_trap_wrapper(
          addr, options, message.size(),
          command.mach_msg_overwrite().rcv_size(),
          GetMachPortName(command.mach_msg_overwrite().rcv_name()),
          command.mach_msg_overwrite().timeout(),
          command.mach_msg_overwrite().priority(),
          command.mach_msg_overwrite().rcv_msg());
      host_->Log(absl::StrFormat("mach_msg return 0x%x\n", err));
      break;
    }
    case Command::kMachMsg2Trap: {
      HandleMachMsg2(command.mach_msg2_trap());
      break;
    }
    case Command::kHostCreateMachVoucherTrap: {
      std::string recipes = command.host_create_mach_voucher_trap().recipes();
      host_create_mach_voucher_trap_wrapper(
          GetMachPortName(command.host_create_mach_voucher_trap().host()),
          reinterpret_cast<mach_voucher_attr_raw_recipe_array_t>(
              recipes.data()),
          static_cast<int>(recipes.size()), 1
          // command.host_create_mach_voucher_trap().voucher(),
      );
      break;
    }
    case Command::kMachVoucherExtractAttrRecipeTrap: {
      size_t recipe_size =
          command.mach_voucher_extract_attr_recipe_trap().recipe().size();
      mach_voucher_extract_attr_recipe_trap_wrapper(
          GetMachPortName(
              command.mach_voucher_extract_attr_recipe_trap().voucher_name()),
          command.mach_voucher_extract_attr_recipe_trap().key(),
          (uint8_t *)command.mach_voucher_extract_attr_recipe_trap()
              .recipe()
              .data(),
          reinterpret_cast<uintptr_t>(&recipe_size));
      break;
    }
    case Command::kThreadGetSpecialReplyPort: {
      thread_get_special_reply_port_wrapper();
      break;
    }
    case Command::kMkTimerCreateTrap: {
      mk_timer_create_trap_wrapper();
      break;
    }
    case Command::kMkTimerDestroyTrap: {
      host_->Log("mk_timer_destroy_trap()\n");
      mk_timer_destroy_trap_wrapper(
          GetMachPortName(command.mk_timer_destroy_trap().name()));
      break;
    }
    case Command::kMkTimerCancelTrap: {
      mk_timer_cancel_trap_wrapper(
          GetMachPortName(command.mk_timer_cancel_trap().name()), 0);
      break;
    }
    case Command::kMkTimerArmTrap: {
      mk_timer_arm_trap_wrapper(
          GetMachPortName(command.mk_timer_arm_trap().name()),
          command.mk_timer_arm_trap().expire_time());
      break;
    }
    case Command::kMkTimerArmLeewayTrap: {
      mk_timer_arm_leeway_trap_wrapper(
          GetMachPortName(command.mk_timer_arm_leeway_trap().name()),
          command.mk_timer_arm_leeway_trap().mk_timer_flags(),
          command.mk_timer_arm_leeway_trap().expire_time(),
          command.mk_timer_arm_leeway_trap().mk_leeway());
      break;
    }
    // TODO(nedwill): fuzz all random syscalls but filter better modelled ones
    case Command::kArbBsdSyscall: {
      XNUDoRandomSyscall(command.arb_bsd_syscall().number(),
                         (void *)command.arb_bsd_syscall().arguments().data(),
                         command.arb_bsd_syscall().arguments().size());
      break;
    }
    case Command::kArbMachTrap: {
      DoRandomMachTrap(command.arb_mach_trap().number(),
                       (void *)command.arb_mach_trap().arguments().data(),
                       command.arb_mach_trap().arguments().size());
      break;
    }
    case Command::kIoctl: {
      // TODO(nedwill): pick these values more efficiently
      // XXX: these mutate global state
      const uint32_t fd = command.ioctl().fd();
      const uint32_t com = ioctls[command.ioctl().ioctl_idx() - 1];
      GetHypercallInterface()->BlockCopyin();
      ioctl_wrapper(fd, com, /*data=*/(caddr_t)1, nullptr);
      GetHypercallInterface()->UnblockCopyin();
      break;
    }
    case Command::kIpInput: {
      DoIpInput(command.ip_input());
      break;
    }
    case Command::kIoctlReal: {
      host_->Log("ioctl_real()\n");
      switch (command.ioctl_real().ioctl_case()) {
        case IoctlReal::kSiocaifaddrIn664: {
          const In6_AliasReq_64 &req =
              command.ioctl_real().siocaifaddr_in6_64();
          struct in6_aliasreq_64 alias = {};
          memcpy(&alias.ifra_name[0], req.ifra_name().data(),
                 std::min(req.ifra_name().size(), sizeof(alias.ifra_name)));
          get_sockaddr6(&alias.ifra_addr, req.ifra_addr());
          get_sockaddr6(&alias.ifra_dstaddr, req.ifra_dstaddr());
          get_sockaddr6(&alias.ifra_prefixmask, req.ifra_prefixmask());
          for (const int flag : req.ifra_flags()) {
            // make mutations that dupe a flag more useful by xoring
            alias.ifra_flags ^= flag;
          }
          get_in6_addrlifetime_64(&alias.ifra_lifetime, req.ifra_lifetime());
          ioctl_wrapper(command.ioctl_real().fd(), siocaifaddr_in6_64,
                        reinterpret_cast<caddr_t>(&alias), nullptr);
          break;
        }
        case IoctlReal::kSiocsifflags: {
          struct ifreq ifreq = {};
          for (const int flag : command.ioctl_real().siocsifflags().flags()) {
            ifreq.ifr_flags |= flag;
          }
          // TODO(nedwill): fuzz non-loopback options here
          get_ifr_name(&ifreq.ifr_name[0], LO0);
          ioctl_wrapper(command.ioctl_real().fd(), siocsifflags,
                        reinterpret_cast<caddr_t>(&ifreq), nullptr);
          break;
        }
        case IoctlReal::IOCTL_NOT_SET: {
          break;
        }
      }
    }
    case Command::kConnectx: {
      host_->Log("connectx()\n");
      const bool has_srcaddr = command.connectx().endpoints().has_sae_srcaddr();

      std::string srcaddr_s;
      if (has_srcaddr) {
        srcaddr_s = get_sockaddr(command.connectx().endpoints().sae_srcaddr());
      }

      std::string dstaddr_s =
          get_sockaddr(command.connectx().endpoints().sae_dstaddr());

      auto srcaddr = reinterpret_cast<user64_addr_t>(srcaddr_s.data());
      const uint32_t srcsize = srcaddr_s.size();
      if (!has_srcaddr) {
        srcaddr = 0;
        assert(!srcsize);
      }

      auto dstaddr = reinterpret_cast<user64_addr_t>(dstaddr_s.data());
      const uint32_t dstsize = dstaddr_s.size();

      // We ignore failure here since it's ok to try to send things regardless
      uint32_t connectx_flags = 0;
      for (const int flag : command.connectx().flags()) {
        connectx_flags |= flag;
      }
      uint32_t cid = 0;

      const struct user64_sa_endpoints endpoints = {
          .sae_srcif = static_cast<unsigned int>(
              command.connectx().endpoints().sae_srcif()),
          .sae_srcaddr = srcaddr,
          .sae_srcaddrlen = srcsize,
          .sae_dstaddr = dstaddr,
          .sae_dstaddrlen = dstsize};

      // TODO(nedwill): is this a return value?
      size_t len = 0;
      // TODO(nedwill): add IOV mocking
      connectx_wrapper(command.connectx().socket(), &endpoints,
                       command.connectx().associd(), connectx_flags, nullptr, 0,
                       &len, &cid, nullptr);
      cids_.push_back(cid);
      break;
    }
    case Command::kDisconnectx: {
      host_->Log("disconnectx()\n");
      uint32_t cid = 0;
      if (!cids_.empty()) {
        cid = cids_[command.disconnectx().cid() % cids_.size()];
      } else {
        cid = command.disconnectx().cid();
      }
      disconnectx_wrapper(command.disconnectx().fd(),
                          command.disconnectx().associd(), cid, nullptr);
      break;
    }
    case Command::kNecpClientAction: {
      DoNecpClientAction(command.necp_client_action());
      break;
    }
    case Command::kNecpSessionAction: {
      const size_t out_buffer_size =
          command.necp_session_action().out_buffer_size() % 4096;
      std::string buffer = command.necp_session_action().in_buffer();
      std::vector<uint8_t> out_buffer(out_buffer_size);
      necp_session_action_wrapper(
          command.necp_session_action().necp_fd(),
          command.necp_session_action().action(),
          reinterpret_cast<uint8_t *>(buffer.data()),
          command.necp_session_action().in_buffer().size(), out_buffer.data(),
          out_buffer_size, &retval);
      break;
    }
    case Command::kMigRoutineMachMsg: {
      std::vector<uint8_t> message = GetMigRoutineMsg(
          command.mig_routine_mach_msg().routine(),
          command.mig_routine_mach_msg().remote_type(),
          GetMachPortName(command.mig_routine_mach_msg().remote_port()),
          command.mig_routine_mach_msg().local_type(),
          GetMachPortName(command.mig_routine_mach_msg().local_port()),
          command.mig_routine_mach_msg().voucher_type(),
          GetMachPortName(command.mig_routine_mach_msg().voucher_port()));
      host_->Log("mig_routine_mach_msg()\n");
      host_->Log(absl::StrFormat("Got message: %s\n", DumpVector(message)));
      int options = 0;
      for (const auto &option : command.mig_routine_mach_msg().options()) {
        options |= option;
      }
      host_->Log(absl::StrFormat(
          "Got options: 0x%x, size 0x%x, rcv_size 0x%x, rcv_name 0x%x, "
          "timeout 0x%x, priority 0x%x, rcv_msg 0x%x\n",
          options, message.size(), command.mig_routine_mach_msg().rcv_size(),
          GetMachPortName(command.mig_routine_mach_msg().rcv_name()),
          command.mig_routine_mach_msg().timeout(),
          command.mig_routine_mach_msg().priority(),
          command.mig_routine_mach_msg().rcv_msg()));
      int ret = mach_msg_trap_wrapper(
          reinterpret_cast<user_addr_t>(message.data()), options,
          message.size(), command.mig_routine_mach_msg().rcv_size(),
          GetMachPortName(command.mig_routine_mach_msg().rcv_name()),
          command.mig_routine_mach_msg().timeout(),
          command.mig_routine_mach_msg().priority(),
          command.mig_routine_mach_msg().rcv_msg());
      host_->Log(absl::StrFormat("mig_routine_mach_msg() -> %d\n", ret));
      break;
    }
    case Command::kKevent: {
      std::vector<struct kevent> changes;
      for (const auto &c : command.kevent().changelist()) {
        int flags = 0;
        for (const auto &flag : c.flags()) {
          flags |= flag;
        }
        changes.emplace_back(c.ident(), c.filter(), flags, c.fflags(),
                             reinterpret_cast<intptr_t>(c.data()),
                             reinterpret_cast<void *>(c.udata()));
      }

      std::vector<struct kevent> events;
      for (const auto &e : command.kevent().eventlist()) {
        int flags = 0;
        for (const auto &flag : e.flags()) {
          flags |= flag;
        }
        events.emplace_back(e.ident(), e.filter(), flags, e.fflags(),
                            reinterpret_cast<intptr_t>(e.data()),
                            reinterpret_cast<void *>(e.udata()));
      }

      kevent_wrapper(command.kevent().kq(), changes.data(), changes.size(),
                     events.data(), events.size(), nullptr, &retval);
      break;
    }
    case Command::kProcessorException: {
      switch (command.processor_exception().exception_case()) {
        case ProcessorException::kVmFault: {
          const VmFaultException &vm_fault =
              command.processor_exception().vm_fault();
          DoVmFault(vm_fault.addr(), vm_fault.type());
          break;
        }
        case ProcessorException::EXCEPTION_NOT_SET: {
          break;
        }
      }
      break;
    }
    case Command::kSyscall: {
      CallBsdSyscall(command.syscall());
      break;
    }
    case Command::COMMAND_NOT_SET: {
      break;
    }
  }
  // Don't yield if we didn't do any call since we could have importantly
  // yielded on the last iteration
  if (command.command_case() != Command::COMMAND_NOT_SET) {
    host_->Yield();
  }
}

CommandHandler *CommandHandler::GetInstance() {
  static auto *instance = new CommandHandler(g_host);
  return instance;
}

CommandHandler::CommandHandler(Host *host) : host_(host) {}
