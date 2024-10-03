/*
 * Copyright 2021 Google LLC
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

#include <i386/locks.h>
#include <kern/assert.h>
#include <kern/block_hint.h>
#include <kern/debug.h>
#include <kern/kern_types.h>
#include <kern/lock_group.h>
#include <kern/lock_rw.h>
#include <kern/lock_types.h>
#include <kern/locks.h>
#include <kern/sched_prim.h>
#include <kern/simple_lock.h>
#include <kern/startup.h>
#include <kern/thread.h>
#include <kern/ticket_lock.h>
#include <kern/timer_queue.h>
#include <kern/turnstile.h>
#include <kern/waitq.h>
#include <mach/boolean.h>
#include <mach/i386/kern_return.h>
#include <mach/kern_return.h>
#include <mach/mach_types.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/kdebug_kernel.h>

#include "fuzz/host/hypercall/hypercall.h"

static timer_coalescing_priority_params_ns_t priority_params;
timer_coalescing_priority_params_ns_t *timer_call_get_priority_params() {
  return &priority_params;
}

wait_result_t lck_spin_sleep_grp(lck_spin_t *lck,
                                 lck_sleep_action_t lck_sleep_action,
                                 event_t event, wait_interrupt_t interruptible,
                                 lck_grp_t *grp) {
  wait_result_t res = 0;

  if ((lck_sleep_action & ~LCK_SLEEP_MASK) != 0) {
    panic("Invalid lock sleep action %x\n", lck_sleep_action);
  }

  res = assert_wait(event, interruptible);
  if (res == THREAD_WAITING) {
    lck_spin_unlock(lck);
    res = thread_block(THREAD_CONTINUE_NULL);
    if (!(lck_sleep_action & LCK_SLEEP_UNLOCK)) {
      lck_spin_lock_grp(lck, grp);
    }
  } else if (lck_sleep_action & LCK_SLEEP_UNLOCK) {
    lck_spin_unlock(lck);
  }

  return res;
}

wait_result_t lck_spin_sleep(lck_spin_t *lck,
                             lck_sleep_action_t lck_sleep_action, event_t event,
                             wait_interrupt_t interruptible) {
  return lck_spin_sleep_grp(lck, lck_sleep_action, event, interruptible,
                            LCK_GRP_NULL);
}

wait_result_t lck_spin_sleep_deadline(lck_spin_t *lck,
                                      lck_sleep_action_t lck_sleep_action,
                                      event_t event,
                                      wait_interrupt_t interruptible,
                                      uint64_t deadline) {
  wait_result_t res;

  if ((lck_sleep_action & ~LCK_SLEEP_MASK) != 0) {
    panic("Invalid lock sleep action %x", lck_sleep_action);
  }

  res = assert_wait_deadline(event, interruptible, deadline);
  if (res == THREAD_WAITING) {
    lck_spin_unlock(lck);
    res = thread_block(THREAD_CONTINUE_NULL);
    if (!(lck_sleep_action & LCK_SLEEP_UNLOCK)) {
      lck_spin_lock(lck);
    }
  } else if (lck_sleep_action & LCK_SLEEP_UNLOCK) {
    lck_spin_unlock(lck);
  }

  return res;
}

static wait_result_t sleep_with_inheritor_and_turnstile(
    event_t event, thread_t inheritor, wait_interrupt_t interruptible,
    uint64_t deadline, void (^primitive_lock)(void),
    void (^primitive_unlock)(void)) {
  turnstile_type_t type = TURNSTILE_SLEEP_INHERITOR;
  wait_result_t ret;
  uint32_t index;
  struct turnstile *ts = NULL;

  /*
	 * the hash bucket spinlock is used as turnstile interlock,
	 * lock it before releasing the primitive lock
	 */
  turnstile_hash_bucket_lock((uintptr_t)event, &index, type);

  primitive_unlock();

  ts = turnstile_prepare_hash((uintptr_t)event, type);

  thread_set_pending_block_hint(current_thread(),
                                kThreadWaitSleepWithInheritor);
  /*
	 * We need TURNSTILE_DELAYED_UPDATE because we will call
	 * waitq_assert_wait64 after.
	 */
  turnstile_update_inheritor(
      ts, inheritor, (TURNSTILE_DELAYED_UPDATE | TURNSTILE_INHERITOR_THREAD));

  ret = waitq_assert_wait64(&ts->ts_waitq, CAST_EVENT64_T(event), interruptible,
                            deadline);

  turnstile_hash_bucket_unlock((uintptr_t)NULL, &index, type, 0);

  /*
	 * Update new and old inheritor chains outside the interlock;
	 */
  turnstile_update_inheritor_complete(ts, TURNSTILE_INTERLOCK_NOT_HELD);

  if (ret == THREAD_WAITING) {
    ret = thread_block(THREAD_CONTINUE_NULL);
  }

  turnstile_hash_bucket_lock((uintptr_t)NULL, &index, type);

  turnstile_complete_hash((uintptr_t)event, type);

  turnstile_hash_bucket_unlock((uintptr_t)NULL, &index, type, 0);

  turnstile_cleanup();

  primitive_lock();

  return ret;
}

/*
 * Name: lck_spin_sleep_with_inheritor
 *
 * Description: deschedule the current thread and wait on the waitq associated with event to be woken up.
 *              While waiting, the sched priority of the waiting thread will contribute to the push of the event that will
 *              be directed to the inheritor specified.
 *              An interruptible mode and deadline can be specified to return earlier from the wait.
 *
 * Args:
 *   Arg1: lck_spin_t lock used to protect the sleep. The lock will be dropped while sleeping and reaquired before returning according to the sleep action specified.
 *   Arg2: sleep action. LCK_SLEEP_DEFAULT, LCK_SLEEP_UNLOCK.
 *   Arg3: event to wait on.
 *   Arg4: thread to propagate the event push to.
 *   Arg5: interruptible flag for wait.
 *   Arg6: deadline for wait.
 *
 * Conditions: Lock must be held. Returns with the lock held according to the sleep action specified.
 *             Lock will be dropped while waiting.
 *             The inheritor specified cannot return to user space or exit until another inheritor is specified for the event or a
 *             wakeup for the event is called.
 *
 * Returns: result of the wait.
 */
wait_result_t lck_spin_sleep_with_inheritor(lck_spin_t *lock,
                                            lck_sleep_action_t lck_sleep_action,
                                            event_t event, thread_t inheritor,
                                            wait_interrupt_t interruptible,
                                            uint64_t deadline) {
  if (lck_sleep_action & LCK_SLEEP_UNLOCK) {
    return sleep_with_inheritor_and_turnstile(event, inheritor, interruptible,
                                              deadline,
                                              ^{
                                              },
                                              ^{
                                                lck_spin_unlock(lock);
                                              });
  } else {
    return sleep_with_inheritor_and_turnstile(
        event, inheritor, interruptible, deadline,
        ^{
          lck_spin_lock(lock);
        },
        ^{
          lck_spin_unlock(lock);
        });
  }
}

wait_result_t lck_ticket_sleep_with_inheritor(
    lck_ticket_t *lock, lck_grp_t *grp, lck_sleep_action_t lck_sleep_action,
    event_t event, thread_t inheritor, wait_interrupt_t interruptible,
    uint64_t deadline) {
  if (lck_sleep_action & LCK_SLEEP_UNLOCK) {
    return sleep_with_inheritor_and_turnstile(event, inheritor, interruptible,
                                              deadline,
                                              ^{
                                              },
                                              ^{
                                                lck_ticket_unlock(lock);
                                              });
  } else {
    return sleep_with_inheritor_and_turnstile(
        event, inheritor, interruptible, deadline,
        ^{
          lck_ticket_lock(lock, grp);
        },
        ^{
          lck_ticket_unlock(lock);
        });
  }
}

wait_result_t lck_rw_sleep(lck_rw_t *lck, lck_sleep_action_t lck_sleep_action,
                           event_t event, wait_interrupt_t interruptible) {
  wait_result_t res = 0;
  lck_rw_type_t lck_rw_type = 0;
  thread_pri_floor_t token;

  if ((lck_sleep_action & ~LCK_SLEEP_MASK) != 0) {
    panic("Invalid lock sleep action %x", lck_sleep_action);
  }

  if (lck_sleep_action & LCK_SLEEP_PROMOTED_PRI) {
    /*
     * Although we are dropping the RW lock, the intent in most cases
     * is that this thread remains as an observer, since it may hold
     * some secondary resource, but must yield to avoid deadlock. In
     * this situation, make sure that the thread is boosted to the
     * ceiling while blocked, so that it can re-acquire the
     * RW lock at that priority.
     */
    token = thread_priority_floor_start();
  }

  res = assert_wait(event, interruptible);
  if (res == THREAD_WAITING) {
    lck_rw_type = lck_rw_done(lck);
    res = thread_block(THREAD_CONTINUE_NULL);
    if (!(lck_sleep_action & LCK_SLEEP_UNLOCK)) {
      if (!(lck_sleep_action & (LCK_SLEEP_SHARED | LCK_SLEEP_EXCLUSIVE))) {
        lck_rw_lock(lck, lck_rw_type);
      } else if (lck_sleep_action & LCK_SLEEP_EXCLUSIVE) {
        lck_rw_lock_exclusive(lck);
      } else {
        lck_rw_lock_shared(lck);
      }
    }
  } else if (lck_sleep_action & LCK_SLEEP_UNLOCK) {
    (void)lck_rw_done(lck);
  }

  if (lck_sleep_action & LCK_SLEEP_PROMOTED_PRI) {
    thread_priority_floor_end(&token);
  }

  return res;
}

wait_result_t lck_mtx_sleep(lck_mtx_t *lck, lck_sleep_action_t lck_sleep_action,
                            event_t event, wait_interrupt_t interruptible) {
  wait_result_t res = 0;
  thread_pri_floor_t token;

  KERNEL_DEBUG(
      MACHDBG_CODE(DBG_MACH_LOCKS, LCK_MTX_SLEEP_CODE) | DBG_FUNC_START,
      VM_KERNEL_UNSLIDE_OR_PERM(lck), (int)lck_sleep_action,
      VM_KERNEL_UNSLIDE_OR_PERM(event), (int)interruptible, 0);

  if ((lck_sleep_action & ~LCK_SLEEP_MASK) != 0) {
    panic("Invalid lock sleep action %x", lck_sleep_action);
  }

  if (lck_sleep_action & LCK_SLEEP_PROMOTED_PRI) {
    /*
     * We get a priority floor
     * during the time that this thread is asleep, so that when it
     * is re-awakened (and not yet contending on the mutex), it is
     * runnable at a reasonably high priority.
     */
    token = thread_priority_floor_start();
  }

  res = assert_wait(event, interruptible);
  if (res == THREAD_WAITING) {
    lck_mtx_unlock(lck);
    res = thread_block(THREAD_CONTINUE_NULL);
    if (!(lck_sleep_action & LCK_SLEEP_UNLOCK)) {
      if ((lck_sleep_action & LCK_SLEEP_SPIN)) {
        lck_mtx_lock_spin(lck);
      } else if ((lck_sleep_action & LCK_SLEEP_SPIN_ALWAYS)) {
        lck_mtx_lock_spin_always(lck);
      } else {
        lck_mtx_lock(lck);
      }
    }
  } else if (lck_sleep_action & LCK_SLEEP_UNLOCK) {
    lck_mtx_unlock(lck);
  }

  if (lck_sleep_action & LCK_SLEEP_PROMOTED_PRI) {
    thread_priority_floor_end(&token);
  }

  KERNEL_DEBUG(MACHDBG_CODE(DBG_MACH_LOCKS, LCK_MTX_SLEEP_CODE) | DBG_FUNC_END,
               (int)res, 0, 0, 0, 0);

  return res;
}

wait_result_t lck_mtx_sleep_deadline(lck_mtx_t *lck,
                                     lck_sleep_action_t lck_sleep_action,
                                     event_t event,
                                     wait_interrupt_t interruptible,
                                     uint64_t deadline) {
  wait_result_t res = 0;
  thread_pri_floor_t token;

  KERNEL_DEBUG(MACHDBG_CODE(DBG_MACH_LOCKS, LCK_MTX_SLEEP_DEADLINE_CODE) |
                   DBG_FUNC_START,
               VM_KERNEL_UNSLIDE_OR_PERM(lck), (int)lck_sleep_action,
               VM_KERNEL_UNSLIDE_OR_PERM(event), (int)interruptible, 0);

  if ((lck_sleep_action & ~LCK_SLEEP_MASK) != 0) {
    panic("Invalid lock sleep action %x", lck_sleep_action);
  }

  if (lck_sleep_action & LCK_SLEEP_PROMOTED_PRI) {
    /*
     * See lck_mtx_sleep().
     */
    token = thread_priority_floor_start();
  }

  res = assert_wait_deadline(event, interruptible, deadline);
  if (res == THREAD_WAITING) {
    lck_mtx_unlock(lck);
    res = thread_block(THREAD_CONTINUE_NULL);
    if (!(lck_sleep_action & LCK_SLEEP_UNLOCK)) {
      if ((lck_sleep_action & LCK_SLEEP_SPIN)) {
        lck_mtx_lock_spin(lck);
      } else {
        lck_mtx_lock(lck);
      }
    }
  } else if (lck_sleep_action & LCK_SLEEP_UNLOCK) {
    lck_mtx_unlock(lck);
  }

  if (lck_sleep_action & LCK_SLEEP_PROMOTED_PRI) {
    thread_priority_floor_end(&token);
  }

  KERNEL_DEBUG(
      MACHDBG_CODE(DBG_MACH_LOCKS, LCK_MTX_SLEEP_DEADLINE_CODE) | DBG_FUNC_END,
      (int)res, 0, 0, 0, 0);

  return res;
}

TUNABLE(uint32_t, LcksOpts, "lcks", 0);

uint64_t hw_wait_while_equals64(uint64_t *address, uint64_t current) {
  GetHypercallInterface()->Abort();
}

bool lck_ticket_lock_try(lck_ticket_t *tlock, lck_grp_t *grp) {
  GetHypercallInterface()->Abort();
}

#undef hw_lck_ticket_reserve
bool hw_lck_ticket_reserve(hw_lck_ticket_t *tlock,
                           uint32_t *ticket LCK_GRP_ARG(lck_grp_t *grp)) {
  // TODO(nedwill): only permit invalid locks in the allow_invalid case
  bool got_lock = hw_lck_ticket_lock_try(tlock, NULL);
  if (got_lock) {
    return true;
  }

  *ticket = 0;
  return false;
}

// #undef hw_lck_ticket_wait
hw_lock_status_t hw_lck_ticket_wait(hw_lck_ticket_t *tlock, uint32_t ticket,
                                    hw_spin_policy_t policy, lck_grp_t *grp) {
  return hw_lck_ticket_lock_to(tlock, 0, NULL);
}

#undef hw_lck_ticket_reserve_allow_invalid
hw_lock_status_t hw_lck_ticket_reserve_allow_invalid(
    hw_lck_ticket_t *tlock, uint32_t *ticket LCK_GRP_ARG(lck_grp_t *grp)) {
  return hw_lck_ticket_reserve(tlock, ticket);
}

void lck_ticket_startup_init(struct lck_ticket_startup_spec *spec) {}

static kern_return_t wakeup_with_inheritor_and_turnstile(
    event_t event, wait_result_t result, bool wake_one,
    lck_wake_action_t action, thread_t *thread_wokenup) {
  turnstile_type_t type = TURNSTILE_SLEEP_INHERITOR;
  uint32_t index;
  struct turnstile *ts = NULL;
  kern_return_t ret = KERN_NOT_WAITING;
  thread_t wokeup;

  /*
	 * the hash bucket spinlock is used as turnstile interlock
	 */
  turnstile_hash_bucket_lock((uintptr_t)event, &index, type);

  ts = turnstile_prepare_hash((uintptr_t)event, type);

  if (wake_one) {
    waitq_wakeup_flags_t flags = WAITQ_WAKEUP_DEFAULT;

    if (action == LCK_WAKE_DEFAULT) {
      flags = WAITQ_UPDATE_INHERITOR;
    } else {
      assert(action == LCK_WAKE_DO_NOT_TRANSFER_PUSH);
    }

    /*
		 * WAITQ_UPDATE_INHERITOR will call turnstile_update_inheritor
		 * if it finds a thread
		 */
    wokeup = waitq_wakeup64_identify(&ts->ts_waitq, CAST_EVENT64_T(event),
                                     result, flags);
    if (wokeup != NULL) {
      if (thread_wokenup != NULL) {
        *thread_wokenup = wokeup;
      } else {
        thread_deallocate_safe(wokeup);
      }
      ret = KERN_SUCCESS;
      if (action == LCK_WAKE_DO_NOT_TRANSFER_PUSH) {
        goto complete;
      }
    } else {
      if (thread_wokenup != NULL) {
        *thread_wokenup = NULL;
      }
      turnstile_update_inheritor(ts, TURNSTILE_INHERITOR_NULL,
                                 TURNSTILE_IMMEDIATE_UPDATE);
      ret = KERN_NOT_WAITING;
    }
  } else {
    ret = waitq_wakeup64_all(&ts->ts_waitq, CAST_EVENT64_T(event), result,
                             WAITQ_UPDATE_INHERITOR);
  }

  /*
	 * turnstile_update_inheritor_complete could be called while holding the interlock.
	 * In this case the new inheritor or is null, or is a thread that is just been woken up
	 * and have not blocked because it is racing with the same interlock used here
	 * after the wait.
	 * So there is no chain to update for the new inheritor.
	 *
	 * However unless the current thread is the old inheritor,
	 * old inheritor can be blocked and requires a chain update.
	 *
	 * The chain should be short because kernel turnstiles cannot have user turnstiles
	 * chained after them.
	 *
	 * We can anyway optimize this by asking turnstile to tell us
	 * if old inheritor needs an update and drop the lock
	 * just in that case.
	 */
  turnstile_hash_bucket_unlock((uintptr_t)NULL, &index, type, 0);

  turnstile_update_inheritor_complete(ts, TURNSTILE_INTERLOCK_NOT_HELD);

  turnstile_hash_bucket_lock((uintptr_t)NULL, &index, type);

complete:
  turnstile_complete_hash((uintptr_t)event, type);

  turnstile_hash_bucket_unlock((uintptr_t)NULL, &index, type, 0);

  turnstile_cleanup();

  return ret;
}

kern_return_t wakeup_one_with_inheritor(event_t event, wait_result_t result,
                                        lck_wake_action_t action,
                                        thread_t *thread_wokenup) {
  return wakeup_with_inheritor_and_turnstile(event, result, TRUE, action,
                                             thread_wokenup);
}

kern_return_t wakeup_all_with_inheritor(event_t event, wait_result_t result) {
  return wakeup_with_inheritor_and_turnstile(event, result, FALSE, 0, NULL);
}
