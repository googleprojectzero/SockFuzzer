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

#include <kern/ast.h>
#include <kern/kern_types.h>
#include <kern/processor.h>
#include <kern/sched.h>
#include <kern/sched_prim.h>
#include <kern/task.h>
#include <mach/i386/boolean.h>
#include <mach/mach_types.h>
#include <stdbool.h>
#include <stdint.h>

#include "fuzz/host/hypercall/hypercall.h"

void init(void) {
  current_processor()->processor_set = &pset0;
}

void timebase_init(void) {
  GetHypercallInterface()->Abort();
}

void maintenance_continuation(void) {
  assert_wait((event_t)0x41414141, TH_UNINT);
  thread_block((void *)maintenance_continuation);
}

thread_t choose_thread(processor_t processor, int priority, ast_t reason) {
  GetHypercallInterface()->Abort();
}

/* True if scheduler supports stealing threads for this pset */
bool steal_thread_enabled(processor_set_t pset) {
  return false;
}

/*
 * Steal a thread from another processor in the pset so that it can run
 * immediately
 */
thread_t steal_thread(processor_set_t pset) {
  GetHypercallInterface()->Abort();
}

/*
 * Compute priority for a timeshare thread based on base priority.
 */
int compute_timeshare_priority(thread_t thread) {
  GetHypercallInterface()->Abort();
}

/*
 * Pick the best node for a thread to run on.
 */
pset_node_t choose_node(thread_t thread) {
  return &pset_node0;
}

processor_t choose_processor_stub(processor_set_t pset, processor_t processor,
                                  thread_t thread) {
  return master_processor;
}

/*
 * Enqueue a timeshare or fixed priority thread onto the per-processor
 * runqueue
 */
boolean_t processor_enqueue(processor_t processor, thread_t thread,
                            sched_options_t options) {
  GetHypercallInterface()->Abort();
}

/* Migrate threads away in preparation for processor shutdown */
void processor_queue_shutdown(processor_t processor) {
  GetHypercallInterface()->Abort();
}

/* Remove the specific thread from the per-processor runqueue */
boolean_t processor_queue_remove(processor_t processor, thread_t thread) {
  GetHypercallInterface()->Abort();
}

/*
 * Does the per-processor runqueue have any timeshare or fixed priority
 * threads on it? Called without pset lock held, so should
 * not assume immutability while executing.
 */
boolean_t processor_queue_empty(processor_t processor) {
  GetHypercallInterface()->Abort();
}

/*
 * Does the per-processor runqueue contain runnable threads that
 * should cause the currently-running thread to be preempted?
 */
ast_t processor_csw_check(processor_t processor) {
  return AST_NONE;
}

/*
 * Does the per-processor runqueue contain a runnable thread
 * of > or >= priority, as a preflight for choose_thread() or other
 * thread selection
 */
boolean_t processor_queue_has_priority(processor_t processor, int priority,
                                       boolean_t gte) {
  GetHypercallInterface()->Abort();
}

/* Quantum size for the specified non-realtime thread. */
uint32_t initial_quantum_size(thread_t thread) {
  // TODO(nedwill): figure out a good value here
  return 5;
}

/* Scheduler mode for a new thread */
sched_mode_t initial_thread_sched_mode(task_t parent_task) {
  return TH_MODE_FIXED;
}

/* Callback for non-realtime threads when the quantum timer fires */
void quantum_expire(thread_t thread) {
  GetHypercallInterface()->Abort();
}

/*
 * Runnable threads on per-processor runqueue. Should only
 * be used for relative comparisons of load between processors.
 */
int processor_runq_count(processor_t processor) {
  GetHypercallInterface()->Abort();
}

/* Aggregate runcount statistics for per-processor runqueue */
uint64_t processor_runq_stats_count_sum(processor_t processor) {
  GetHypercallInterface()->Abort();
}

boolean_t processor_bound_count(processor_t processor) {
  return true;
}

void thread_update_scan(sched_update_scan_context_t scan_context) {
  GetHypercallInterface()->Abort();
}

/* Returns true if this processor should avoid running this thread. */
bool thread_avoid_processor(processor_t processor, thread_t thread) {
  GetHypercallInterface()->Abort();
}

/*
 * Invoked when a processor is about to choose the idle thread
 * Used to send IPIs to a processor which would be preferred to be idle instead.
 * Called with pset lock held, returns pset lock unlocked.
 */
void processor_balance(processor_t processor, processor_set_t pset) {
  pset_unlock(pset);
}

rt_queue_t rt_runq(processor_set_t pset) {
  return &pset->rt_runq;
}

void rt_init(processor_set_t pset) {}
void rt_queue_shutdown(processor_t processor) {
  GetHypercallInterface()->Abort();
}
void rt_runq_scan(sched_update_scan_context_t scan_context) {
  GetHypercallInterface()->Abort();
}
int64_t rt_runq_count_sum(void) {
  GetHypercallInterface()->Abort();
}
thread_t rt_steal_thread(processor_set_t pset, uint64_t earliest_deadline) {
  GetHypercallInterface()->Abort();
}

void check_spill(processor_set_t pset, thread_t thread) {}
sched_ipi_type_t ipi_policy(processor_t dst, thread_t thread,
                            boolean_t dst_idle, sched_ipi_event_t event) {
  GetHypercallInterface()->Abort();
}

bool thread_should_yield(processor_t processor, thread_t thread) {
  return thread != main_thread;
}

/* Routine to update run counts */
uint32_t run_count_incr(thread_t thread) {
  return 1;
}
uint32_t run_count_decr(thread_t thread) {
  return 1;
}

/* Routine to update scheduling bucket for a thread */
void update_thread_bucket(thread_t thread) {
  thread->th_sched_bucket = TH_BUCKET_RUN;
  // TODO(nedwill): determine best value for this
  thread->pri_shift = INT8_MAX;
}

/* Routine to inform the scheduler when a new pset becomes schedulable */
void pset_made_schedulable(processor_t processor, processor_set_t pset,
                           boolean_t drop_lock) {
  GetHypercallInterface()->Abort();
}
/* Routine to inform the scheduler when all CPUs have finished initializing */
void cpu_init_completed(void) {
  GetHypercallInterface()->Abort();
}
/* Routine to check if a thread is eligible to execute on a specific pset */
bool thread_eligible_for_pset(thread_t thread, processor_set_t pset) {
  GetHypercallInterface()->Abort();
}

void pset_init_stub(processor_set_t pset) {}

void processor_init_stub(processor_t p) {}

uint32_t qos_max_parallelism_nop(int qos, uint64_t options) {
  return 0;
}

const struct sched_dispatch_table sched_dualq_dispatch = {
    .sched_name = "SockScheduler",
    .init = init,
    .timebase_init = timebase_init,
    .processor_init = processor_init_stub,
    .pset_init = pset_init_stub,
    .maintenance_continuation = maintenance_continuation,
    .choose_thread = choose_thread,
    .steal_thread_enabled = steal_thread_enabled,
    .steal_thread = steal_thread,
    .compute_timeshare_priority = compute_timeshare_priority,
    .choose_node = choose_node,
    .choose_processor = choose_processor_stub,
    .processor_enqueue = processor_enqueue,
    .processor_queue_shutdown = processor_queue_shutdown,
    .processor_queue_remove = processor_queue_remove,
    .processor_queue_empty = processor_queue_empty,
    .priority_is_urgent = priority_is_urgent,
    .processor_csw_check = processor_csw_check,
    .processor_queue_has_priority = processor_queue_has_priority,
    .initial_quantum_size = initial_quantum_size,
    .initial_thread_sched_mode = initial_thread_sched_mode,
    .can_update_priority = can_update_priority,
    .update_priority = update_priority,
    .lightweight_update_priority = lightweight_update_priority,
    .quantum_expire = quantum_expire,
    .processor_runq_count = processor_runq_count,
    .processor_runq_stats_count_sum = processor_runq_stats_count_sum,
    .processor_bound_count = processor_bound_count,
    .thread_update_scan = thread_update_scan,
    .multiple_psets_enabled = false,
    .sched_groups_enabled = false,
    .avoid_processor_enabled = false,
    .thread_avoid_processor = thread_avoid_processor,
    .processor_balance = processor_balance,
    .rt_runq = rt_runq,
    .rt_init = rt_init,
    .rt_queue_shutdown = rt_queue_shutdown,
    .rt_runq_scan = rt_runq_scan,
    .rt_runq_count_sum = rt_runq_count_sum,
    .rt_steal_thread = rt_steal_thread,
    .qos_max_parallelism = qos_max_parallelism_nop,
    .check_spill = check_spill,
    .ipi_policy = ipi_policy,
    .thread_should_yield = thread_should_yield,
    .run_count_incr = run_count_incr,
    .run_count_decr = run_count_decr,
    .update_thread_bucket = update_thread_bucket,
    .pset_made_schedulable = pset_made_schedulable,
    /* Routine to inform the scheduler when all CPUs have finished initializing
     */
    .cpu_init_completed = cpu_init_completed,
    /* Routine to check if a thread is eligible to execute on a specific pset */
    .thread_eligible_for_pset = thread_eligible_for_pset,
};
