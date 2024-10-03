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

#ifndef OSFMK_TEST_BACKEND_H_
#define OSFMK_TEST_BACKEND_H_

#include <stddef.h>
#include <stdint.h>

enum class sync_policy {
  fifo = 0x0,
  lifo = 0x2,
  disable_irq = 0x8,
};

enum class wait_result {
  waiting = -1,
  awakened = 0,
  timed_out = 1,
  interrupted = 2,
  restart = 3,
  not_waiting = 10,
};

typedef unsigned long long uint64;

typedef uint64 event64_t;
const event64_t no_event = 0;

enum class wait_interrupt : uint32_t {
  uninterruptible = 0x00000000,
  interruptible = 0x00000001,
  abortsafe = 0x00000002,
  noreport_kernel = 0x80000000,
  noreport_user = 0x40000000,
  noreport = (noreport_kernel | noreport_user),
};

enum class wait_timeout_urgency {
  sys_normal = 0x00,
  sys_critical = 0x01,
  sys_background = 0x02,
  user_mask = 0x10,
  user_normal = 0x10,
  user_critical = 0x11,
  user_background = 0x12,
  mask = 0x13,
  leeway = 0x20,
  first_avail = 0x40,
  ratelimited = 0x80
};

enum class kern_return {
  success = 0,
  invalid_address = 1,
  protection_failure = 2,
  no_space = 3,
  invalid_argument = 4,
  failure = 5,
  resource_shortage = 6,
  not_receiver = 7,
  no_access = 8,
  memory_failure = 9,
  memory_error = 10,
  already_in_set = 11,
  not_in_set = 12,
  name_exists = 13,
  aborted = 14,
  invalid_name = 15,
  invalid_task = 16,
  invalid_right = 17,
  invalid_value = 18,
  urefs_overflow = 19,
  invalid_capability = 20,
  right_exists = 21,
  invalid_host = 22,
  memory_present = 23,
  memory_data_moved = 24,
  memory_restart_copy = 25,
  invalid_processor_set = 26,
  policy_limit = 27,
  invalid_policy = 28,
  invalid_object = 29,
  already_waiting = 30,
  default_set = 31,
  exception_protected = 32,
  invalid_ledger = 33,
  invalid_memory_control = 34,
  invalid_security = 35,
  not_depressed = 36,
  terminated = 37,
  lock_set_destroyed = 38,
  lock_unstable = 39,
  lock_owned = 40,
  lock_owned_self = 41,
  semaphore_destroyed = 42,
  rpc_server_terminated = 43,
  rpc_terminate_orphan = 44,
  rpc_continue_orphan = 45,
  not_supported = 46,
  node_down = 47,
  not_waiting = 48,
  operation_timed_out = 49,
  codesign_error = 50,
  policy_static = 51,
  insufficient_buffer_size = 52,
  denied = 53,
  missing_kc = 54,
  invalid_kc = 55,
  not_found = 56,
};

enum class wakeup_flags {
	WAITQ_WAKEUP_DEFAULT    = 0x0000,
	WAITQ_UPDATE_INHERITOR  = 0x0001,
	WAITQ_PROMOTE_PRIORITY  = 0x0002,
	WAITQ_UNLOCK            = 0x0004,
	WAITQ_KEEP_LOCKED       = 0x0000,
	WAITQ_HANDOFF           = 0x0008,
};

class Waitq {
 public:
  explicit Waitq(sync_policy policy);
  ~Waitq();
  Waitq(const Waitq &) = delete;
  Waitq &operator=(const Waitq &) = delete;
  Waitq(Waitq &&) = delete;
  Waitq &operator=(Waitq &&) = delete;

  wait_result AssertWait64(event64_t wait_event, wait_interrupt interruptible,
                           uint64 deadline);

  wait_result AssertWait64Leeway(event64_t wait_event,
                                 wait_interrupt interruptible,
                                 wait_timeout_urgency urgency, uint64 deadline,
                                 uint64 leeway);

  kern_return Wakeup64One(event64_t wake_event, wait_result result,
                          wakeup_flags flags);

 private:
  class WaitqImpl;

  WaitqImpl* impl_;
};

class KHeap {
public:
  KHeap() = default;
  ~KHeap() = default;

  void* alloc(size_t size, int flags);

  void free_addr(void* ptr);
};

#endif /* OSFMK_TEST_BACKEND_H_ */
