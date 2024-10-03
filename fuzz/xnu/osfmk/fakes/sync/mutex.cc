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
HyperMutex **lck_mtx_alloc_init() {
  HyperMutex *mtx = GetHypercallInterface()->AllocateMutex();
  auto **ptr = new HyperMutex *;
  *ptr = mtx;
  return ptr;
}

// We don't differentiate between spin- and fully-acquired mutexes
void lck_mtx_convert_spin() {}
void lck_mtx_free() {
  abort();
}

// TODO(nedwill): this may need special semantics
void lck_mtx_lock_spin_always(HyperMutex **sp) {
  GetHypercallInterface()->Yield();
  GetHypercallInterface()->MutexLock(*sp);
}

void lck_mtx_sleep_with_inheritor() {
  abort();
}

int lck_mtx_try_lock(HyperMutex **sp) {
  GetHypercallInterface()->Yield();
  return GetHypercallInterface()->MutexTryLock(*sp);
}

void lck_mtx_init_ext(HyperMutex **sp) {
  *sp = GetHypercallInterface()->AllocateMutex();
}

void lck_mtx_try_lock_spin_always() {
  abort();
}

void lck_mtx_init(HyperMutex **sp) {
  *sp = GetHypercallInterface()->AllocateMutex();
}

void lck_mtx_startup_init(HyperMutex ***sp) {
  lck_mtx_init(*sp);
}

void lck_mtx_destroy(HyperMutex **sp) {
  GetHypercallInterface()->FreeMutex(*sp);
  *sp = nullptr;
}

int lck_mtx_try_lock_spin(HyperMutex **sp) {
  GetHypercallInterface()->Yield();
  return GetHypercallInterface()->MutexTryLock(*sp);
}

void lck_mtx_lock(HyperMutex **sp) {
  GetHypercallInterface()->Yield();
  GetHypercallInterface()->MutexLock(*sp);
}

void lck_mtx_unlock(HyperMutex **sp) {
  GetHypercallInterface()->MutexUnlock(*sp);
  GetHypercallInterface()->Yield();
}

void lck_mtx_yield(HyperMutex **sp) {
  GetHypercallInterface()->MutexUnlock(*sp);
  GetHypercallInterface()->Yield();
  GetHypercallInterface()->MutexLock(*sp);
}

void lck_mtx_lock_spin(HyperMutex **sp) {
  lck_mtx_lock(sp);
}

void lck_mtx_assert(HyperMutex **sp) {
  GetHypercallInterface()->Yield();
  // TODO(nedwill): debug this assertion
  // GetHypercallInterface()->MutexAssertHeld(*sp);
}
}
