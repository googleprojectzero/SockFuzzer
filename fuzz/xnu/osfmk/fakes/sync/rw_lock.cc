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

#include <cstdlib>

#include "fuzz/host/hypercall/hypercall.h"

struct lck_rw_t;

extern "C" {

HyperRwLock **lck_rw_alloc_init() {
  HyperRwLock *mtx = GetHypercallInterface()->AllocateRwLock();
  auto **ptr = new HyperRwLock *;
  *ptr = mtx;
  return ptr;
}

void lck_rw_destroy(HyperRwLock **sp) {
  GetHypercallInterface()->FreeRwLock(*sp);
  *sp = nullptr;
}

void lck_rw_free() {
  abort();
}

void lck_rw_init(HyperRwLock **sp) {
  *sp = GetHypercallInterface()->AllocateRwLock();
}

void lck_rw_lock_exclusive_to_shared(HyperRwLock **sp) {
  GetHypercallInterface()->RwLockExclusiveToShared(*sp);
}

int lck_rw_lock_shared_to_exclusive(HyperRwLock **sp) {
  return GetHypercallInterface()->RwLockSharedToExclusive(*sp);
}

#define THREAD_WAITING -1     /* thread is waiting */
#define THREAD_AWAKENED 0     /* normal wakeup */
#define THREAD_TIMED_OUT 1    /* timeout expired */
#define THREAD_INTERRUPTED 2  /* aborted/interrupted */
#define THREAD_RESTART 3      /* restart operation entirely */
#define THREAD_NOT_WAITING 10 /* thread didn't need to wait */

#define LCK_SLEEP_DEFAULT \
  0x00 /* Release the lock while waiting for the event, then reclaim */
/* RW locks are returned in the same mode */
#define LCK_SLEEP_UNLOCK 0x01 /* Release the lock and return unheld */
#define LCK_SLEEP_SHARED 0x02 /* Reclaim the lock in shared mode (RW only) */
#define LCK_SLEEP_EXCLUSIVE \
  0x04                      /* Reclaim the lock in exclusive mode (RW only) */
#define LCK_SLEEP_SPIN 0x08 /* Reclaim the lock in spin mode (mutex only) */
#define LCK_SLEEP_PROMOTED_PRI 0x10 /* Sleep at a promoted priority */
#define LCK_SLEEP_SPIN_ALWAYS \
  0x20 /* Reclaim the lock in spin-always mode (mutex only) */

#define LCK_SLEEP_MASK 0x3f /* Valid actions */

typedef int lck_sleep_action_t;
typedef int wait_result_t;

void lck_rw_startup_init(HyperRwLock ***sp) {
  lck_rw_init(*sp);
}
int lck_rw_try_lock_exclusive(HyperRwLock **sp) {
  GetHypercallInterface()->Yield();
  return GetHypercallInterface()->RwLockTryLockExclusive(*sp);
}
int lck_rw_try_lock_shared(HyperRwLock **sp) {
  GetHypercallInterface()->Yield();
  return GetHypercallInterface()->RwLockTryLockShared(*sp);
}
void lck_rw_unlock() {
  abort();
}
void lck_rw_unlock_exclusive(HyperRwLock **sp) {
  GetHypercallInterface()->RwLockUnlockExclusive(*sp);
  GetHypercallInterface()->Yield();
}
void lck_rw_unlock_shared(HyperRwLock **sp) {
  GetHypercallInterface()->RwLockUnlockShared(*sp);
  GetHypercallInterface()->Yield();
}
void lck_rw_clear_promotion() {
  abort();
}

int lck_rw_lock_exclusive_check_contended(HyperRwLock **sp) {
  GetHypercallInterface()->Yield();
  GetHypercallInterface()->RwLockLockExclusive(*sp);
  return GetHypercallInterface()->GetFuzzedBool();
}

int lck_rw_lock_yield_shared(HyperRwLock **sp, bool force_yield) {
  // TODO(nedwill): sometimes return false
  GetHypercallInterface()->RwLockUnlockShared(*sp);
  GetHypercallInterface()->Yield();
  GetHypercallInterface()->RwLockLockShared(*sp);
  return true;
}

enum lck_rw_yield_t {
  LCK_RW_YIELD_WRITERS_ONLY,
  LCK_RW_YIELD_ANY_WAITER,
  LCK_RW_YIELD_ALWAYS,
};

int lck_rw_lock_yield_exclusive(HyperRwLock **sp, lck_rw_yield_t mode) {
  // TODO(nedwill): sometimes return false, handle modes
  GetHypercallInterface()->RwLockUnlockExclusive(*sp);
  GetHypercallInterface()->Yield();
  GetHypercallInterface()->RwLockLockExclusive(*sp);
  return true;
}

void lck_rw_assert(lck_rw_t *lck, unsigned int type) {
  // TODO(nedwill): track the state of the lock and implement the assertions
}

void lck_rw_lock_shared(HyperRwLock **lock) {
  GetHypercallInterface()->Yield();
  GetHypercallInterface()->RwLockLockShared(*lock);
}

#define LCK_RW_TYPE_SHARED 0x01
#define LCK_RW_TYPE_EXCLUSIVE 0x02

unsigned int lck_rw_done(HyperRwLock **lock) {
  unsigned int lock_type =
      GetHypercallInterface()->RwLockIsShared(*lock) ? LCK_RW_TYPE_SHARED : LCK_RW_TYPE_EXCLUSIVE;
  GetHypercallInterface()->RwLockUnlock(*lock);
  GetHypercallInterface()->Yield();
  return lock_type;
}

void lck_rw_lock_exclusive(HyperRwLock **lock) {
  // GetHypercallInterface()->ThreadPrintf("lck_rw_lock_exclusive: %p\n", lock);
  GetHypercallInterface()->Yield();
  GetHypercallInterface()->RwLockLockExclusive(*lock);
}

void lck_rw_lock(HyperRwLock **sp, unsigned int lck_type) {
  if (lck_type == LCK_RW_TYPE_SHARED) {
    lck_rw_lock_shared(sp);
  } else if (lck_type == LCK_RW_TYPE_EXCLUSIVE) {
    lck_rw_lock_exclusive(sp);
  } else {
    abort();
  }
}
}
