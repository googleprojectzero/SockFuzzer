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

#include "fuzz/host/hw_ticket_lock_manager.h"

#include <stdlib.h>

#include "fuzz/host/host_interface.h"
#include "fuzz/host/hypercall/types.h"
#include "fuzz/host/logger.h"
#include "third_party/concurrence/sync/mutex.h"
#include "third_party/concurrence/sync/tracker.h"

void HwTicketLockManager::Allocate(VirtualMutex** lock) {
  *lock = host_->sync_tracker()->AllocateMutex();
  host_->logger()->Log(TICKET_LOCK, "Allocate -> %p\n", lock);
  live_locks_.insert(lock);
}

void HwTicketLockManager::Invalidate(VirtualMutex** lock) {
  host_->logger()->Log(TICKET_LOCK, "Invalidate %p\n", lock);
  live_locks_.erase(lock);
  invalidated_locks_.insert(lock);
}

void HwTicketLockManager::Destroy(VirtualMutex** lock, bool sync) {
  host_->logger()->Log(TICKET_LOCK, "Destroy %p, %d\n", *lock, sync);
  live_locks_.erase(lock);

  // Wakeup any waiters in the invalid case so we don't UaF
  if (sync && invalidated_locks_.count(lock)) {
    WakeupWaiters(lock);
    if (!(*lock)->waiters().empty()) {
      abort();
    }
  }

  invalidated_locks_.erase(lock);
  host_->sync_tracker()->FreeMutex(*lock);
}

void HwTicketLockManager::WakeupWaiters(VirtualMutex** lock) {
  host_->logger()->Log(TICKET_LOCK, "WakeupWaiters %p\n", lock);
  if ((*lock)->waiters().empty()) {
    host_->logger()->Log(TICKET_LOCK, "no waiters for %p, returning\n", lock);
    return;
  }

  host_->logger()->Log(TICKET_LOCK, "Unlocking %p\n", lock);
  if ((*lock)->Held()) {
    (*lock)->Unlock();
  }
  while (!(*lock)->waiters().empty()) {
    host_->logger()->Log(TICKET_LOCK, "Has waiters, yielding %p\n", lock);
    host_->Yield();
  }
}

bool HwTicketLockManager::IsValid(VirtualMutex** lock) {
  return live_locks_.count(lock);
}

hw_lock_status_t HwTicketLockManager::Lock(VirtualMutex** lock,
                                           bool allow_invalid, uint64_t timeout,
                                           void* handler) {
  host_->logger()->Log(TICKET_LOCK, "Lock %p %d\n", lock, allow_invalid);
  bool const is_invalid = invalidated_locks_.count(lock);
  if (is_invalid) {
    host_->logger()->Log(TICKET_LOCK, "is_invalid case\n");
    if (allow_invalid) {
      return HW_LOCK_INVALID;
    }
    return HW_LOCK_ACQUIRED;
  }

  if (!live_locks_.count(lock)) {
    host_->logger()->Log(TICKET_LOCK, "not live, returning invalid\n");
    return HW_LOCK_INVALID;
  }

  // TODO(nedwill): flip a coin here and return HW_LOCK_CONTENDED

  host_->logger()->Log(TICKET_LOCK, "locking %p\n", *lock);
  (*lock)->Lock();

  if (invalidated_locks_.count(lock)) {
    host_->logger()->Log(TICKET_LOCK, "now invalid, unlocking\n");
    (*lock)->Unlock();
    return HW_LOCK_INVALID;
  }

  host_->logger()->Log(TICKET_LOCK, "acquired!\n");
  return HW_LOCK_ACQUIRED;
}

bool HwTicketLockManager::TryLock(VirtualMutex** lock) {
  host_->logger()->Log(TICKET_LOCK, "TryLock %p\n", lock);
  if (!live_locks_.count(lock)) {
    return false;
  }

  return (*lock)->TryLock();
}

void HwTicketLockManager::Unlock(VirtualMutex** lock) {
  host_->logger()->Log(TICKET_LOCK, "Unlock %p\n", lock);
  if (!live_locks_.count(lock) && !invalidated_locks_.count(lock)) {
    return;
  }

  if (!(*lock)->Held()) {
    return;
  }

  (*lock)->Unlock();
  host_->logger()->Log(
      TICKET_LOCK,
      "unlocking ticket lock, before yield runnable %d suspended %d "
      "waiting %d\n",
      host_->IsRunnable(host_->GetCurrentThreadT()),
      host_->IsSuspended(host_->GetCurrentThreadT()),
      host_->IsWaiting(host_->GetCurrentThreadT()));
}

bool HwTicketLockManager::Held(VirtualMutex** lock) {
  if (!live_locks_.count(lock)) {
    return false;
  }

  if (invalidated_locks_.count(lock)) {
    abort();
  }

  return (*lock)->Held();
}
