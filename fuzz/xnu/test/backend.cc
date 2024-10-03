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

// Links against internal libxnu to make testing easier

#include "fuzz/xnu/test/backend.h"

#include <mach/vm_statistics.h>

#include <kern/kalloc.h>
#include <kern/kern_types.h>
#include <kern/waitq.h>
#include <mach/i386/kern_return.h>

class Waitq::WaitqImpl {
 public:
  explicit WaitqImpl(sync_policy policy) {
    waitq_.wq_q = &waitq_data_;
    waitq_init(waitq_, WQT_QUEUE, static_cast<int>(policy));
  }
  ~WaitqImpl() { waitq_deinit(waitq_); }
  WaitqImpl(const WaitqImpl &) = delete;
  WaitqImpl &operator=(const WaitqImpl &) = delete;
  WaitqImpl(WaitqImpl &&) = delete;
  WaitqImpl &operator=(WaitqImpl &&) = delete;

  wait_result AssertWait64(event64_t wait_event, wait_interrupt interruptible,
                           uint64_t deadline) {
    wait_result_t result = waitq_assert_wait64(
        waitq_, wait_event, static_cast<wait_interrupt_t>(interruptible),
        deadline);
    return static_cast<wait_result>(result);
  }

  wait_result AssertWait64Leeway(event64_t wait_event,
                                 wait_interrupt interruptible,
                                 wait_timeout_urgency urgency,
                                 uint64_t deadline, uint64_t leeway) {
    wait_result_t result = waitq_assert_wait64_leeway(
        waitq_, wait_event, static_cast<wait_interrupt_t>(interruptible),
        static_cast<wait_timeout_urgency_t>(urgency), deadline, leeway);
    return static_cast<wait_result>(result);
  }

  kern_return Wakeup64One(event64_t wake_event, wait_result result,
                          waitq_wakeup_flags_t flags) {
    kern_return_t ret = waitq_wakeup64_one(
        waitq_, wake_event, static_cast<wait_result_t>(result), flags);
    return static_cast<kern_return>(ret);
  }

 private:
  struct waitq waitq_data_ {};
  waitq_t waitq_{};
};

Waitq::Waitq(sync_policy policy) : impl_(new WaitqImpl(policy)) {}

Waitq::~Waitq() {
  delete impl_;
}

// assert intent to wait on <waitq,event64> pair
wait_result Waitq::AssertWait64(event64_t wait_event,
                                wait_interrupt interruptible,
                                uint64_t deadline) {
  return impl_->AssertWait64(wait_event, interruptible, deadline);
}

wait_result Waitq::AssertWait64Leeway(event64_t wait_event,
                                      wait_interrupt interruptible,
                                      wait_timeout_urgency urgency,
                                      uint64_t deadline, uint64_t leeway) {
  return impl_->AssertWait64Leeway(wait_event, interruptible, urgency, deadline,
                                   leeway);
}

kern_return Waitq::Wakeup64One(event64_t wake_event, wait_result result,
                               wakeup_flags flags) {
  return impl_->Wakeup64One(wake_event, result, static_cast<waitq_wakeup_flags_t>(flags));
}

// kern_return_t Waitq::Wakeup64All(event64_t wake_event, wait_result_t result,
//                                    int priority) {
//   return waitq_wakeup64_all(&waitq_, wake_event, result, priority);
// }

// /* wakeup a specified thread iff it's waiting on <waitq,event64> pair */
// extern kern_return_t waitq_wakeup64_thread(struct waitq *waitq,
//     event64_t wake_event,
//     thread_t thread,
//     wait_result_t result);

// /* return a reference to the thread that was woken up */
// extern thread_t waitq_wakeup64_identify(struct waitq *waitq,
//     event64_t       wake_event,
//     wait_result_t   result,
//     int             priority);
// thread_t Waitq::Wakeup64Identify(event64_t wake_event, wait_result_t result,
//                                    int priority) {
//   return waitq_wakeup64_identify(&waitq_, wake_event, result, priority);
// }

// void Waitq::Lock() { waitq_lock(&waitq_); }

// void Waitq::Unlock() { waitq_unlock(&waitq_); }

void* KHeap::alloc(size_t size, int flags) {
  return kheap_alloc(KHEAP_DEFAULT, size, static_cast<zalloc_flags_t>(flags | Z_ZERO));
}

void KHeap::free_addr(void* ptr) {
  kheap_free_addr(KHEAP_DEFAULT, ptr);
}
