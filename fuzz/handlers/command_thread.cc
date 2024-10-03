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

#include "fuzz/handlers/command_thread.h"

#include "fuzz/handlers/command.h"
#include "fuzz/host/host.h"
#include "fuzz/xnu/osfmk/api/types.h"

// One syscall/mach trap calling thread
void CommandThread(void *ptr, wait_result_t wait_result) {
  // g_host->Log("In CommandThread\n");
  const auto &commands =
      *static_cast<const google::protobuf::RepeatedPtrField<Command> *>(ptr);

  // Scaffolding for transcribing testcases to C
  // uint32_t id = g_host->GetId(g_host->scheduler()->GetCurrentThreadHandle());
  // if (id == 1) {
  //   // Call syscalls here...
  //   return;
  // }
  // if (id == 2) {
  //   // Call syscalls here...
  //   return;
  // }
  // return;

  auto *command_handler = CommandHandler::GetInstance();

  for (const Command &command : commands) {
    command_handler->HandleCommand(command);
  }

  // g_host->Log("Finished in CommandThread\n");
  g_host->ThreadFinished();
  __builtin_unreachable();
}
