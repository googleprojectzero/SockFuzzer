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

#ifndef FUZZ_HOST_HW_TICKET_LOCK_MANAGER_H_
#define FUZZ_HOST_HW_TICKET_LOCK_MANAGER_H_

#include <stdint.h>

#include <memory>
#include <unordered_set>

#include "absl/container/flat_hash_set.h"
#include "host_interface.h"
#include "third_party/concurrence/sync/mutex.h"

class HostInterface;
class VirtualMutex;

enum hw_lock_status_t {
  HW_LOCK_INVALID = -1,
  HW_LOCK_CONTENDED = 0,
  HW_LOCK_ACQUIRED = 1,
};

class HwTicketLockManager {
 public:
  explicit HwTicketLockManager(HostInterface* host) : host_(host) {}
  ~HwTicketLockManager() = default;

  void Allocate(VirtualMutex** lock);
  void Invalidate(VirtualMutex** lock);
  void Destroy(VirtualMutex** lock, bool sync);
  void WakeupWaiters(VirtualMutex** lock);

  bool IsValid(VirtualMutex** lock);

  hw_lock_status_t Lock(VirtualMutex** lock, bool allow_invalid,
                        uint64_t timeout, void* handler);
  bool TryLock(VirtualMutex** lock);
  void Unlock(VirtualMutex** lock);

  bool Held(VirtualMutex** lock);

 private:
  HostInterface* host_;
  absl::flat_hash_set<VirtualMutex**> live_locks_;
  absl::flat_hash_set<VirtualMutex**> invalidated_locks_;
};

#endif /* FUZZ_HOST_HW_TICKET_LOCK_MANAGER_H_ */
