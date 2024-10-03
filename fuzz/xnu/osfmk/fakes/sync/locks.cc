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

#include <cstdint>
#include <cstdlib>

#include "fuzz/host/hypercall/hypercall.h"

struct lck_grp_t;

// VirtualLckPtr class definition
class VirtualLckPtr {
 public:
  VirtualLckPtr(void* initial_value) : protected_value(initial_value) {
    mutex = GetHypercallInterface()->AllocateMutex(); 
  }

  ~VirtualLckPtr() { 
    GetHypercallInterface()->FreeMutex(mutex); 
  }

  void* GetValue() { return protected_value; }
  void SetValue(void* value) { protected_value = value; }

  void LockExclusive() { GetHypercallInterface()->MutexLock(mutex); }
  void UnlockExclusive() { GetHypercallInterface()->MutexUnlock(mutex); }

  bool IsLocked() { return GetHypercallInterface()->MutexIsOwned(mutex); }
  
  // TODO(nedwill): this is quite wasteful to yield so often when we may not be "runnable"
  // yet due to the value not matching. We should add a mechanism similar to abseil's mutex
  // that lets you wait for a condition to be true and the outstanding conditions are evaluated
  // every time the scheduler wants to wake up an eligible mutex (IIUC that's how it works).
  void WaitForValue(void* value) {
    while (GetValue() != value) {
      UnlockExclusive(); 
      GetHypercallInterface()->Yield();
      LockExclusive(); 
    }
  }

 private:
  HyperMutex* mutex;
  void* protected_value;
};

// Define the hw_lck_ptr_t structure 
struct hw_lck_ptr_t {
  VirtualLckPtr* virtual_lck_ptr; 
};

extern "C" {

// General Lock Handling Functions
void hw_lock_init(HyperMutex **sp) {
  *sp = GetHypercallInterface()->AllocateMutex();
}

unsigned int hw_lock_try(HyperMutex **sp, lck_grp_t *grp) {
  GetHypercallInterface()->Yield();
  return GetHypercallInterface()->MutexTryLock(*sp);
}

void hw_lock_unlock(HyperMutex **sp) {
  GetHypercallInterface()->MutexUnlock(*sp);
  GetHypercallInterface()->Yield();
}

void hw_lock_held(HyperMutex **sp) {
  GetHypercallInterface()->Yield();
  GetHypercallInterface()->AssertMutexHeld(*sp);
}

void hw_lock_to_init(HyperMutex **sp) {
  *sp = GetHypercallInterface()->AllocateMutex();
}

int hw_lock_to(HyperMutex **sp) {
  GetHypercallInterface()->Yield();
  return GetHypercallInterface()->MutexTryLock(*sp);
}

// hw_lck_ptr_t Handling Functions
void hw_lck_ptr_init(hw_lck_ptr_t *lck, void *val, lck_grp_t *grp) {
  lck->virtual_lck_ptr = new VirtualLckPtr(val);
}

void hw_lck_ptr_destroy(hw_lck_ptr_t *lck, lck_grp_t *grp) {
  delete lck->virtual_lck_ptr;
  lck->virtual_lck_ptr = nullptr;
}

void *hw_lck_ptr_value(hw_lck_ptr_t *lck) {
  if (!lck->virtual_lck_ptr) {
    GetHypercallInterface()->Abort();
  }
  return lck->virtual_lck_ptr->GetValue();
}

void *hw_lck_ptr_lock(hw_lck_ptr_t *lck, lck_grp_t *grp) {
  if (!lck->virtual_lck_ptr) {
    GetHypercallInterface()->Abort();
  }
  lck->virtual_lck_ptr->LockExclusive();
  return lck->virtual_lck_ptr->GetValue();
}

// Use hw_lck_ptr_lock for both lock and lock_nopreempt 
void *hw_lck_ptr_lock_nopreempt(hw_lck_ptr_t *lck, lck_grp_t *grp) {
  return hw_lck_ptr_lock(lck, grp); 
}

void hw_lck_ptr_unlock(hw_lck_ptr_t *lck, void *val, lck_grp_t *grp) {
  if (!lck->virtual_lck_ptr) {
    GetHypercallInterface()->Abort();
  }
  lck->virtual_lck_ptr->SetValue(val);
  lck->virtual_lck_ptr->UnlockExclusive();
}

// Use hw_lck_ptr_unlock for both unlock and unlock_nopreempt
void hw_lck_ptr_unlock_nopreempt(hw_lck_ptr_t *lck, void *val, lck_grp_t *grp) {
  hw_lck_ptr_unlock(lck, val, grp);
}

bool hw_lck_ptr_held(hw_lck_ptr_t *lck) {
  if (!lck->virtual_lck_ptr) {
    GetHypercallInterface()->Abort();
  }
  return lck->virtual_lck_ptr->IsLocked();
}

void hw_lck_ptr_wait_for_value(hw_lck_ptr_t *lck, void *val, lck_grp_t *grp) {
  if (!lck->virtual_lck_ptr) {
    GetHypercallInterface()->Abort();
  }
  lck->virtual_lck_ptr->WaitForValue(val);
}

void hw_lck_ptr_wait_for_value_contended(hw_lck_ptr_t *lck, void *val,
                                         lck_grp_t *grp) {
  hw_lck_ptr_wait_for_value(lck, val, grp);
}

void *hw_lck_ptr_lock_fastpath(hw_lck_ptr_t *lck, lck_grp_t *grp) {
  return hw_lck_ptr_lock(lck, grp); // No optimization needed in this context
}

void *hw_lck_ptr_lock_slow(hw_lck_ptr_t *lck, hw_lck_ptr_t tmp,
                           lck_grp_t *grp) {
  return hw_lck_ptr_lock(lck, grp); // Same as fast path in this context
}

// Simple Lock Functions
void usimple_lock(HyperMutex **sp) {
  GetHypercallInterface()->Yield();
  GetHypercallInterface()->MutexLock(*sp);
}

int usimple_lock_try(HyperMutex **sp) {
  GetHypercallInterface()->Yield();
  return GetHypercallInterface()->MutexTryLock(*sp);
}

void usimple_unlock(HyperMutex **sp) {
  GetHypercallInterface()->MutexUnlock(*sp);
  GetHypercallInterface()->Yield();
}

void usimple_lock_init(HyperMutex **sp) {
  *sp = GetHypercallInterface()->AllocateMutex();
}

void usimple_lock_startup_init(HyperMutex ***sp) {
  usimple_lock_init(*sp);
}

// Miscellaneous Functions
void hw_lock_byte_init() {
  abort();
}

void mutex_pause(uint32_t collisions) {
  GetHypercallInterface()->Yield();
}

void host_lockgroup_info() {}

void hw_wait_while_equals() {
  abort();
}

void kdp_lck_mtx_find_owner() {
  abort();
}

void kdp_lck_mtx_lock_spin_is_acquired() {
  abort();
}

void kdp_lck_rw_lock_is_acquired_exclusive() {
  abort();
}

void kdp_lck_spin_is_acquired() {
  abort();
}

void kdp_rwlck_find_owner() {
  abort();
}

void kdp_sleep_with_inheritor_find_owner() {
  abort();
}
}
