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

extern "C" {

HyperMutex **lck_spin_alloc_init() {
  HyperMutex *mtx = GetHypercallInterface()->AllocateMutex();
  auto **ptr = new HyperMutex *;
  *ptr = mtx;
  return ptr;
}

void lck_spin_assert() {}

void lck_spin_destroy(HyperMutex **sp) {
  GetHypercallInterface()->FreeMutex(*sp);
  *sp = nullptr;
}

void lck_spin_init(HyperMutex **sp) {
  *sp = GetHypercallInterface()->AllocateMutex();
}

void lck_spin_startup_init(HyperMutex ***sp) {
  lck_spin_init(*sp);
}

int lck_spin_try_lock(HyperMutex **sp) {
  GetHypercallInterface()->Yield();
  return GetHypercallInterface()->MutexTryLock(*sp);
}

int lck_spin_try_lock_grp(HyperMutex **lock) {
  GetHypercallInterface()->Yield();
  return GetHypercallInterface()->MutexTryLock(*lock);
}

void lck_spin_lock(HyperMutex **lock) {
  GetHypercallInterface()->Yield();
  GetHypercallInterface()->MutexLock(*lock);
  // GetHypercallInterface()->ThreadPrintf("lck_spin_lock: acquired lock %p\n", *lock);
}

void lck_spin_unlock(HyperMutex **lock) {
  GetHypercallInterface()->MutexUnlock(*lock);
  // GetHypercallInterface()->ThreadPrintf("lck_spin_unlock: released lock %p\n", *lock);
  GetHypercallInterface()->Yield();
}

void lck_spin_lock_grp(HyperMutex **lock) {
  // printf("lck_spin_lock_grp: locking %p\n", lock);
  GetHypercallInterface()->Yield();
  GetHypercallInterface()->MutexLock(*lock);
}

void spinlock_timeout_NMI() {
  abort();
}

void spinlock_timeout_panic() {
  abort();
}
}
