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

#ifndef FUZZ_HANDLERS_COMMAND_H_
#define FUZZ_HANDLERS_COMMAND_H_

#include <cstdint>
#include <vector>

#include "fuzz/host/host.h"
#include "fuzz/proto/session.pb.h"

class CommandHandler {
 public:
  explicit CommandHandler(Host *host);
  ~CommandHandler() = default;

  void HandleCommand(const Command &command);

  static CommandHandler *GetInstance();

  // Per-message implementations
  int HandleMachMsg2(const MachMsg2Trap &trap) const;
  int HandleMachPortAllocate(const MachPortAllocateTrap &trap, mach_port_name_t* name) const;
  int HandleMachPortDeallocate(const MachPortDeallocateTrap &trap) const;
  int HandleTaskSelfTrap() const;

 private:
  std::vector<uint32_t> cids_;
  Host *host_;
};

#endif  // FUZZ_HANDLERS_COMMAND_H_
