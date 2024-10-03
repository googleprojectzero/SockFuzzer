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

#include <stdint.h>
#include <stdlib.h>

#include "fuzz/host/hypercall/hypercall.h"

extern "C" {

typedef void* lck_grp_t;

// TODO(nedwill): ensure ticket-based fairness is used
void lck_ticket_assert_owned(HyperTicketLock** tlock) {
  if (!GetHypercallInterface()->TicketLockHeld(tlock)) {
    abort();
  }
}

void lck_ticket_init(HyperTicketLock** tlock) {
  GetHypercallInterface()->TicketLockAllocate(tlock);
}

void lck_ticket_destroy(HyperTicketLock** tlock) {
  GetHypercallInterface()->TicketLockDestroy(tlock, false);
  *tlock = nullptr;
}

void lck_ticket_lock(HyperTicketLock** tlock) {
  GetHypercallInterface()->Yield();
  GetHypercallInterface()->TicketLockLock(tlock, false, -1, nullptr);
}

void lck_ticket_unlock(HyperTicketLock** tlock) {
  // GetHypercallInterface()->ThreadPrintf("lck_ticket_unlock: unlocking %p\n", sp);
  GetHypercallInterface()->TicketLockUnlock(tlock);
  GetHypercallInterface()->Yield();
}

void hw_lck_ticket_destroy(HyperTicketLock** tlock, lck_grp_t* grp) {
  GetHypercallInterface()->TicketLockDestroy(tlock, true);
}

bool hw_lck_ticket_held(HyperTicketLock** tlock) {
  return GetHypercallInterface()->TicketLockHeld(tlock);
}

void hw_lck_ticket_init(HyperTicketLock** tlock) {
  GetHypercallInterface()->TicketLockAllocate(tlock);
}

void hw_lck_ticket_init_locked(HyperTicketLock** tlock) {
  hw_lck_ticket_init(tlock);
  GetHypercallInterface()->TicketLockLock(tlock, false, -1, nullptr);
}

void hw_lck_ticket_invalidate(HyperTicketLock** tlock) {
  GetHypercallInterface()->TicketLockInvalidate(tlock);
}

int hw_lck_ticket_lock_allow_invalid(HyperTicketLock** tlock,
                                                  uint64_t timeout,
                                                  void* handler,
                                                  lck_grp_t* grp) {
  // TODO(nedwill): figure out when we can return contended
  int const result =
      GetHypercallInterface()->TicketLockLock(tlock, true, timeout, handler);
  GetHypercallInterface()->Yield();
  return result;
}

int hw_lck_ticket_lock_to(HyperTicketLock** tlock, uint64_t timeout,
                                       void* handler, lck_grp_t* grp) {
  // TODO(nedwill): figure out when we can return contended
  int const result =
      GetHypercallInterface()->TicketLockLock(tlock, false, timeout, handler);
  GetHypercallInterface()->Yield();
  return result;
}

bool hw_lck_ticket_lock_try(HyperTicketLock** tlock, lck_grp_t* grp) {
  GetHypercallInterface()->Yield();
  return GetHypercallInterface()->TicketLockTryLock(tlock);
}

void hw_lck_ticket_unlock(HyperTicketLock** tlock) {
  GetHypercallInterface()->TicketLockUnlock(tlock);
  GetHypercallInterface()->Yield();
}

void erase_all_test_mtx_stats() {
  abort();
}
void get_test_mtx_stats_string() {
  abort();
}
void lck_mtx_test_init() {
  abort();
}
void lck_mtx_test_mtx_contended() {
  abort();
}
void lck_mtx_test_mtx_contended_loop_time() {
  abort();
}
void lck_mtx_test_mtx_uncontended() {
  abort();
}
void lck_mtx_test_mtx_uncontended_loop_time() {
  abort();
}
void mpsc_test_pingpong() {
  abort();
}
}
