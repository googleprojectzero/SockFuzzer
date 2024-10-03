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

#ifndef OSFMK_BACKEND_H_
#define OSFMK_BACKEND_H_

#ifndef LIBXNU_BUILD
#ifdef __cplusplus
#include <cstddef>
#include <cstdint>
#else
#include <stddef.h>
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"
void thread_set_thread_name(thread_t th, const char* name);
void thread_deallocate(thread_t thread);
void ast_taken_user();

#else
#include <i386/types.h>
#include <kern/thread.h>
#include <mach/i386/boolean.h>
#include <mach/i386/kern_return.h>
#include <mach/i386/vm_types.h>
#include <mach/mach_traps.h>
#include <mach/mach_types.h>
#include <mach/mach_voucher_types.h>
#include <mach/message.h>
#include <mach/port.h>
#include <mach/vm_prot.h>
#include <mach/vm_purgable.h>
#include <stddef.h>
#include <stdint.h>
#endif

kern_return_t _kernelrpc_mach_vm_allocate_trap_wrapper(mach_port_name_t target,
                                                       mach_vm_offset_t addr,
                                                       mach_vm_size_t size,
                                                       int flags);
kern_return_t _kernelrpc_mach_vm_purgable_control_trap_wrapper(
    mach_port_name_t target, mach_vm_offset_t address, vm_purgable_t control,
    user_addr_t state);
kern_return_t _kernelrpc_mach_vm_deallocate_trap_wrapper(
    mach_port_name_t target, mach_vm_address_t address, mach_vm_size_t size);
kern_return_t task_dyld_process_info_notify_get_trap_wrapper(
    mach_vm_address_t names_addr, mach_vm_address_t names_count_addr);
kern_return_t _kernelrpc_mach_vm_protect_trap_wrapper(mach_port_name_t target,
                                                      mach_vm_address_t address,
                                                      mach_vm_size_t size,
                                                      boolean_t set_maximum,
                                                      vm_prot_t new_protection);
kern_return_t _kernelrpc_mach_vm_map_trap_wrapper(
    mach_port_name_t target, user_addr_t addr, mach_vm_size_t size,
    mach_vm_offset_t mask, int flags, vm_prot_t cur_protection);
kern_return_t _kernelrpc_mach_port_allocate_trap_wrapper(
    mach_port_name_t target, mach_port_right_t right, user_addr_t name);
kern_return_t _kernelrpc_mach_port_deallocate_trap_wrapper(
    mach_port_name_t target, mach_port_name_t name);
kern_return_t _kernelrpc_mach_port_mod_refs_trap_wrapper(
    mach_port_name_t target, mach_port_name_t name, mach_port_right_t right,
    mach_port_delta_t delta);
kern_return_t _kernelrpc_mach_port_move_member_trap_wrapper(
    mach_port_name_t target, mach_port_name_t member, mach_port_name_t after);
kern_return_t _kernelrpc_mach_port_insert_right_trap_wrapper(
    mach_port_name_t target, mach_port_name_t name, mach_port_name_t poly,
    mach_msg_type_name_t polyPoly);
kern_return_t _kernelrpc_mach_port_insert_member_trap_wrapper(
    mach_port_name_t target, mach_port_name_t name, mach_port_name_t pset);
kern_return_t _kernelrpc_mach_port_extract_member_trap_wrapper(
    mach_port_name_t target, mach_port_name_t name, mach_port_name_t pset);
kern_return_t _kernelrpc_mach_port_construct_trap_wrapper(
    mach_port_name_t target, user_addr_t options, uint64_t context,
    user_addr_t name);
kern_return_t _kernelrpc_mach_port_destruct_trap_wrapper(
    mach_port_name_t target, mach_port_name_t name, mach_port_delta_t srdelta,
    uint64_t guard);
kern_return_t _kernelrpc_mach_port_request_notification_trap_wrapper(
    mach_port_name_t task, mach_port_name_t name, mach_msg_id_t msgid,
    mach_port_mscount_t sync, mach_port_name_t notify,
    mach_msg_type_name_t notifyPoly, mach_port_name_t* previous);
kern_return_t mach_reply_port_wrapper();
kern_return_t thread_self_trap_wrapper();
kern_return_t task_self_trap_wrapper();
kern_return_t host_self_trap_wrapper();
kern_return_t mach_msg_trap_wrapper(user_addr_t msg, mach_msg_option_t option,
                                    mach_msg_size_t send_size,
                                    mach_msg_size_t rcv_size,
                                    mach_port_name_t rcv_name,
                                    mach_msg_timeout_t timeout,
                                    mach_msg_priority_t priority,
                                    user_addr_t rcv_msg);
mach_msg_return_t mach_msg2_trap_wrapper(mach_vm_address_t data, 
                                         mach_msg_option64_t options, 
                                         uint64_t msgh_bits_and_send_size,
                                         uint64_t msgh_remote_and_local_port,
                                         uint64_t msgh_voucher_and_id,
                                         uint64_t desc_count_and_rcv_name,
                                         uint64_t rcv_size_and_priority,
                                         uint64_t timeout);
kern_return_t mach_msg_overwrite_trap_wrapper(
    user_addr_t msg, mach_msg_option_t option, mach_msg_size_t send_size,
    mach_msg_size_t rcv_size, mach_port_name_t rcv_name,
    mach_msg_timeout_t timeout, mach_msg_priority_t priority,
    user_addr_t rcv_msg);
kern_return_t host_create_mach_voucher_trap_wrapper(
    mach_port_name_t host, mach_voucher_attr_raw_recipe_array_t recipes,
    int recipes_size, user_addr_t voucher);
kern_return_t mach_voucher_extract_attr_recipe_trap_wrapper(
    mach_port_name_t voucher_name, mach_voucher_attr_key_t key,
    mach_voucher_attr_raw_recipe_t recipe, user_addr_t recipe_size);
kern_return_t thread_get_special_reply_port_wrapper();
kern_return_t mk_timer_create_trap_wrapper();
kern_return_t mk_timer_destroy_trap_wrapper(mach_port_name_t name);
kern_return_t mk_timer_arm_trap_wrapper(mach_port_name_t name,
                                        uint64_t expire_time);
kern_return_t mk_timer_cancel_trap_wrapper(mach_port_name_t name,
                                           uint64_t result_time);
kern_return_t mk_timer_arm_leeway_trap_wrapper(mach_port_name_t name,
                                               uint64_t mk_timer_flags,
                                               uint64_t expire_time,
                                               uint64_t mk_leeway);

void DoRandomMachTrap(unsigned int number, void* data, size_t size);

thread_t CloneTaskFromInit();
task_t GetTaskFromThread(thread_t thread);

void DoVmFault(uint64_t address, int type);

#ifdef __cplusplus
}
#endif

#endif /* OFSMK_BACKEND_H_ */
