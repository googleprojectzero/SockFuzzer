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

#include "gtest/gtest.h"

// TODO(nedwill): kern_return_t from kern_return.h
#define KERN_SUCCESS 0

class Environment : public ::testing::Environment {
 public:
  ~Environment() override = default;

  // Override this to define how to set up the environment.
  void SetUp() override {
    is_verbose = true;
    InitializeHost();
    g_host->scheduler()->SetThreadChoices(nullptr);
  }
};

testing::Environment *const env =
    testing::AddGlobalTestEnvironment(new Environment);

MachPortAllocateTrap GetMachPortAllocateTrap(PortNumberMach target_port_number, MachPortRight right) {
  MachPortAllocateTrap trap;
  auto* target_port_name = new MachPortName();
  auto* target_port = new MachPort();
  target_port->set_port(target_port_number);
  target_port_name->set_allocated_port(target_port);
  trap.set_allocated_target(target_port_name);
  trap.set_right(right);
  return trap;
}

MachMsg* GetMachMsg() {
  // Set up the message header
  auto* header = new MachMsgHeader();

  // Create and set msgh_bits
  auto* bits = new MachMsgHeaderBits();
  bits->set_remote(MachMsgTypeName::FUZZED_MACH_MSG_TYPE_COPY_SEND);
  bits->set_local(MachMsgTypeName::FUZZED_MACH_MSG_TYPE_MAKE_SEND);
  header->set_allocated_msgh_bits(bits);

  // Create and set msgh_remote_port
  auto* remote_port = new MachPort();
  remote_port->set_port(PortNumberMach::CASE_0);
  header->set_allocated_msgh_remote_port(remote_port);

  // Create and set msgh_local_port
  auto* local_port = new MachPort();
  local_port->set_port(PortNumberMach::CASE_0);
  header->set_allocated_msgh_local_port(local_port);

  // Create and set msgh_voucher_port
  auto* voucher_port = new MachPortName();
  auto* voucher = new MachPort();
  voucher->set_port(PortNumberMach::CASE_0);
  voucher_port->set_allocated_port(voucher);
  header->set_allocated_msgh_voucher_port(voucher_port);

  // Set msgh_id
  header->set_msgh_id(123);

  auto* msg = new MachMsg();
  msg->set_allocated_header(header);

  // Create and set body
  auto* descriptor = new MachMsgDescriptor();

  // Choose one descriptor type to set. Here we choose MachMsgPortDescriptor as an example.
  auto* port_descriptor = new MachMsgPortDescriptor();
  auto* port = new MachPort();
  port->set_port(PortNumberMach::CASE_0);
  port_descriptor->set_allocated_name(port);
  port_descriptor->set_disposition(MachMsgTypeName::FUZZED_MACH_MSG_TYPE_COPY_SEND);

  descriptor->set_allocated_port(port_descriptor);
  msg->add_body()->CopyFrom(*descriptor);

  // Set data
  msg->set_data("test");

  return msg;
}

MachMsg2Trap GetMachMsg2Trap() {
  MachMsg2Trap trap;
  trap.add_options(FUZZED_MACH64_SEND_MSG);
  trap.add_options_upper_bits(FUZZED_MACH64_SEND_KOBJECT_CALL);
  // TODO(nedwill): finish implementing this
  return trap;
}

// constexpr unsigned int MACH_SEND_MSG_TOO_SMALL = 0x10000008;

TEST(CommandHandlerTest, TestMachMsg2) {
  CommandHandler handler(g_host);

  mach_port_name_t task_port_name = handler.HandleTaskSelfTrap();

  MachPortAllocateTrap allocate_trap = GetMachPortAllocateTrap(static_cast<PortNumberMach>(task_port_name), FUZZED_MACH_PORT_RIGHT_RECEIVE);
  mach_port_name_t port_name = 0;
  EXPECT_EQ(handler.HandleMachPortAllocate(allocate_trap, &port_name), KERN_SUCCESS);

  MachMsg2Trap msg2_trap = GetMachMsg2Trap();

  // TODO(nedwill): finish test case for successful message case
  EXPECT_EQ(handler.HandleMachMsg2(msg2_trap), MACH_SEND_MSG_TOO_SMALL);

  MachPortDeallocateTrap deallocate_trap;

  auto* target_port_name = new MachPortName();
  auto* target_port = new MachPort();
  target_port->set_port(static_cast<PortNumberMach>(task_port_name));
  target_port_name->set_allocated_port(target_port);
  deallocate_trap.set_allocated_target(target_port_name);

  EXPECT_EQ(handler.HandleMachPortDeallocate(deallocate_trap), KERN_SUCCESS);
}
