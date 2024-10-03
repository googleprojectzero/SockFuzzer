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

#include "fuzz/host/hypercall/hypercall.h"

#include <kern/assert.h>
#include <kern/ast.h>
#include <kern/misc_protos.h>
#include <kern/sched_prim.h>
#include <kern/task.h>
// #include <kern/thread_kernel_state.h>
#include <kern/ticket_lock.h>
#include <kern/timer_call.h>
#include <mach/i386/kern_return.h>
#include <mach/i386/vm_types.h>
#include <mach/kern_return.h>
#include <mach/message.h>
#include <mach/thread_info.h>
#include <mach/thread_status.h>
#include <stddef.h>

#include "fuzz/host/hypercall/hypercall.h"

extern void *initproc;

void free(void *ptr);
void *calloc(size_t nmemb, size_t size);

void machine_stack_attach(thread_t thread, vm_offset_t stack) {
  assert(stack);
  thread->kernel_stack = stack;
  thread_initialize_kernel_state(thread);
}

void machine_thread_init() {}

void XNUGetThreadInfo(thread_t thread, char *data, size_t size) {
  char name[MAXTHREADNAMESIZE] = {};
  thread_get_thread_name(thread, name);
  (void)snprintf(data, size, "%s", name);
}

void machine_thread_create(thread_t thread, task_t task, bool first_thread) {
  GetHypercallInterface()->CreateThread(thread, false);
}

kern_return_t machine_thread_dup(thread_t self, thread_t target,
                                 boolean_t is_corpse) {
  // GetHypercallInterface()->CreateThread(target, (void*)self->continuation, self->parameter,
  // false); It should already be created. We don't have anything else to copy.
  return KERN_SUCCESS;
}

bool ThreadLocked(thread_t thread) {
  // nedwill: assumes hw_lck and ulock are just VirtualMutex under the hood
  return hw_lck_ticket_held((hw_lck_ticket_t *)&thread->sched_lock);
}

kern_return_t machine_thread_state_convert_from_user(
    thread_t thread, thread_flavor_t flavor, thread_state_t tstate,
    mach_msg_type_number_t count, thread_state_t old_tstate,
    mach_msg_type_number_t old_count, thread_set_status_flags_t tssf_flags) {
  // No conversion from userspace representation on this platform
  return KERN_SUCCESS;
}

ast_t cpu_pending_ast;
ast_t *ast_pending() {
  return &cpu_pending_ast;
}

void call_continuation(thread_continue_t continuation, void *parameter,
                       wait_result_t wresult, boolean_t enable_interrupts) {
  GetHypercallInterface()->Abort();
}

thread_t machine_switch_context(thread_t old, thread_continue_t continuation,
                                thread_t new) {
  GetHypercallInterface()->Abort();
}

void machine_thread_destroy(thread_t thread) {
  // We implement simple locks OOL so we need to free them here
  GetHypercallInterface()->FreeVirtualMutex(&thread->sched_lock);
  GetHypercallInterface()->FreeVirtualMutex(&thread->wake_lock);
  GetHypercallInterface()->FreeVirtualMutex(&thread->depress_timer->tc_lock);
  GetHypercallInterface()->FreeVirtualMutex(&thread->wait_timer->tc_lock);

  // TODO(nwach): shouldn't the executor call this?
  GetHypercallInterface()->NotifyDestroyed(thread);
}

// TODO(nedwill): figure out a smarter way to deal with this
__attribute__((noreturn)) void thread_bootstrap_return() {
  GetHypercallInterface()->ThreadPrintf("thread_bootstrap_return thread\n");
  // Keep init (launchd) alive permanently
  if (get_bsdtask_info(current_task()) == initproc) {
    while (true) {
      GetHypercallInterface()->Block();
    }
  }

  // TODO(nedwill): pull syscalls from main loop here
  GetHypercallInterface()->ThreadFinished();
  __builtin_unreachable();
}
