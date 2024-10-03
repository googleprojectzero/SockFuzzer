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

#include <i386/locks.h>
#include <kern/kern_types.h>
#include <kern/lock_rw.h>
#include <kern/locks.h>
#include <kern/misc_protos.h>
#include <kern/processor.h>
#include <kern/task.h>
#include <kern/task_ref.h>
#include <mach/boolean.h>
#include <mach/mach_traps.h>
#include <mach/thread_status.h>
#include <mach/vm_statistics.h>
#include <stdbool.h>

#include "fuzz/host/hypercall/hypercall.h"
#include "fuzz/xnu/osfmk/api/backend.h"
#include "fuzz/xnu/osfmk/api/thread.h"
#include "scheduler_state.h"
#include "third_party/xnu/osfmk/kern/syscall_sw.h"
#include "third_party/xnu/osfmk/vm/vm_fault.h"

struct proc;

int setjmp(void *env);

// Simplified i386_init
void osfmk_bootstrap() {
  processor_bootstrap();
  thread_t bootstrap_thread = thread_bootstrap();
  machine_set_current_thread(bootstrap_thread);
}

// struct _kernelrpc_mach_vm_allocate_trap_args {
// 	PAD_ARG_(mach_port_name_t, target);     /* 1 word */
// 	PAD_ARG_(user_addr_t, addr);            /* 1 word */
// 	PAD_ARG_(mach_vm_size_t, size);         /* 2 words */
// 	PAD_ARG_(int, flags);                   /* 1 word */
// };                                              /* Total: 5 */

kern_return_t _kernelrpc_mach_vm_allocate_trap_wrapper(mach_port_name_t target,
                                                       mach_vm_offset_t addr,
                                                       mach_vm_size_t size,
                                                       int flags) {
  struct _kernelrpc_mach_vm_allocate_trap_args args = {
      .target = target,
      .addr = addr,
      .size = size,
      .flags = flags,
  };

  int rv = _kernelrpc_mach_vm_allocate_trap(&args);
  return rv;
}

kern_return_t _kernelrpc_mach_vm_purgable_control_trap_wrapper(
    mach_port_name_t target, mach_vm_offset_t address, vm_purgable_t control,
    user_addr_t state) {
  struct _kernelrpc_mach_vm_purgable_control_trap_args args = {
      .target = target,
      .address = address,
      .control = control,
      .state = state,
  };

  int rv = _kernelrpc_mach_vm_purgable_control_trap(&args);
  return rv;
}

kern_return_t _kernelrpc_mach_vm_deallocate_trap_wrapper(
    mach_port_name_t target, mach_vm_address_t address, mach_vm_size_t size) {
  struct _kernelrpc_mach_vm_deallocate_args args = {
      .target = target,
      .address = address,
      .size = size,
  };

  int rv = _kernelrpc_mach_vm_deallocate_trap(&args);
  return rv;
}

// struct task_dyld_process_info_notify_get_trap_args {
// 	PAD_ARG_(mach_vm_address_t, names_addr);     /* 2 words */
// 	PAD_ARG_(mach_vm_address_t, names_count_addr);  /* 2 words */
// };                                               /* Total: 4 */

OS_OVERLOADABLE
extern void counter_dec_preemption_disabled(counter_t *counter) {
  (*counter)--;
}

kern_return_t task_dyld_process_info_notify_get_trap_wrapper(
    mach_vm_address_t names_addr, mach_vm_address_t names_count_addr) {
  struct task_dyld_process_info_notify_get_trap_args args = {
      .names_addr = names_addr,
      .names_count_addr = names_count_addr,
  };

  int rv = task_dyld_process_info_notify_get_trap(&args);
  return rv;
}

// struct _kernelrpc_mach_vm_protect_args {
// 	mach_port_name_t target,
// 	mach_vm_address_t address,
// 	mach_vm_size_t size,
// 	boolean_t set_maximum,
// 	vm_prot_t new_protection,
// };                                              /* Total: 7 */

kern_return_t _kernelrpc_mach_vm_protect_trap_wrapper(
    mach_port_name_t target, mach_vm_address_t address, mach_vm_size_t size,
    boolean_t set_maximum, vm_prot_t new_protection) {
  struct _kernelrpc_mach_vm_protect_args args = {
      .target = target,
      .address = address,
      .size = size,
      .set_maximum = set_maximum,
      .new_protection = new_protection,
  };

  int rv = _kernelrpc_mach_vm_protect_trap(&args);
  return rv;
}

// struct _kernelrpc_mach_vm_map_trap_args {
// 	mach_port_name_t target,
// 	user_addr_t addr,
// 	mach_vm_size_t size,
// 	mach_vm_offset_t mask,
// 	int flags,
//   vm_prot_t cur_protection,
// };

kern_return_t _kernelrpc_mach_vm_map_trap_wrapper(
    mach_port_name_t target, user_addr_t addr, mach_vm_size_t size,
    mach_vm_offset_t mask, int flags, vm_prot_t cur_protection) {
  struct _kernelrpc_mach_vm_map_trap_args args = {
      .target = target,
      .addr = addr,
      .size = size,
      .mask = mask,
      .flags = flags,
      .cur_protection = cur_protection,
  };

  int rv = _kernelrpc_mach_vm_map_trap(&args);
  return rv;
}

kern_return_t _kernelrpc_mach_port_allocate_trap_wrapper(
    mach_port_name_t target, mach_port_right_t right, user_addr_t name) {
  struct _kernelrpc_mach_port_allocate_args args = {
      .target = target, .right = right, .name = name};

  int rv = _kernelrpc_mach_port_allocate_trap(&args);
  return rv;
}

kern_return_t _kernelrpc_mach_port_deallocate_trap_wrapper(
    mach_port_name_t target, mach_port_name_t name) {
  struct _kernelrpc_mach_port_deallocate_args args = {.target = target,
                                                      .name = name};

  int rv = _kernelrpc_mach_port_deallocate_trap(&args);
  return rv;
}

kern_return_t _kernelrpc_mach_port_mod_refs_trap_wrapper(
    mach_port_name_t target, mach_port_name_t name, mach_port_right_t right,
    mach_port_delta_t delta) {
  struct _kernelrpc_mach_port_mod_refs_args args = {
      .target = target, .name = name, .right = right, .delta = delta};

  int rv = _kernelrpc_mach_port_mod_refs_trap(&args);
  return rv;
}

kern_return_t _kernelrpc_mach_port_move_member_trap_wrapper(
    mach_port_name_t target, mach_port_name_t member, mach_port_name_t after) {
  struct _kernelrpc_mach_port_move_member_args args = {
      .target = target, .member = member, .after = after};

  int rv = _kernelrpc_mach_port_move_member_trap(&args);
  return rv;
}

kern_return_t _kernelrpc_mach_port_insert_right_trap_wrapper(
    mach_port_name_t target, mach_port_name_t name, mach_port_name_t poly,
    mach_msg_type_name_t polyPoly) {
  struct _kernelrpc_mach_port_insert_right_args args = {
      .target = target, .name = name, .poly = poly, .polyPoly = polyPoly};

  int rv = _kernelrpc_mach_port_insert_right_trap(&args);
  return rv;
}

kern_return_t _kernelrpc_mach_port_insert_member_trap_wrapper(
    mach_port_name_t target, mach_port_name_t name, mach_port_name_t pset) {
  struct _kernelrpc_mach_port_insert_member_args args = {
      .target = target, .name = name, .pset = pset};

  int rv = _kernelrpc_mach_port_insert_member_trap(&args);
  return rv;
}

kern_return_t _kernelrpc_mach_port_extract_member_trap_wrapper(
    mach_port_name_t target, mach_port_name_t name, mach_port_name_t pset) {
  struct _kernelrpc_mach_port_extract_member_args args = {
      .target = target, .name = name, .pset = pset};

  int rv = _kernelrpc_mach_port_extract_member_trap(&args);
  return rv;
}

kern_return_t _kernelrpc_mach_port_construct_trap_wrapper(
    mach_port_name_t target, user_addr_t options, uint64_t context,
    user_addr_t name) {
  struct _kernelrpc_mach_port_construct_args args = {
      .target = target, .options = options, .context = context, .name = name};

  int rv = _kernelrpc_mach_port_construct_trap(&args);
  return rv;
}

kern_return_t _kernelrpc_mach_port_destruct_trap_wrapper(
    mach_port_name_t target, mach_port_name_t name, mach_port_delta_t srdelta,
    uint64_t guard) {
  struct _kernelrpc_mach_port_destruct_args args = {
      .target = target, .name = name, .srdelta = srdelta, .guard = guard};

  int rv = _kernelrpc_mach_port_destruct_trap(&args);
  return rv;
}

kern_return_t mach_reply_port_wrapper() {
  struct mach_reply_port_args args = {};

  int rv = mach_reply_port(&args);
  return rv;
}

kern_return_t thread_self_trap_wrapper() {
  struct thread_self_trap_args args = {};

  int rv = thread_self_trap(&args);
  return rv;
}

kern_return_t task_self_trap_wrapper() {
  struct task_self_trap_args args = {};

  int rv = task_self_trap(&args);
  return rv;
}

kern_return_t host_self_trap_wrapper() {
  struct host_self_trap_args args = {};

  int rv = host_self_trap(&args);
  return rv;
}

kern_return_t mach_msg_trap_wrapper(user_addr_t msg, mach_msg_option_t option,
                                    mach_msg_size_t send_size,
                                    mach_msg_size_t rcv_size,
                                    mach_port_name_t rcv_name,
                                    mach_msg_timeout_t timeout,
                                    mach_msg_priority_t priority,
                                    user_addr_t rcv_msg) {
  struct mach_msg_overwrite_trap_args args = {.msg = msg,
                                              .option = option,
                                              .send_size = send_size,
                                              .rcv_size = rcv_size,
                                              .rcv_name = rcv_name,
                                              .timeout = timeout,
                                              .priority = priority,
                                              .rcv_msg = rcv_msg};

  int rv = mach_msg_trap(&args);
  return rv;
}

mach_msg_return_t mach_msg2_trap_wrapper(
    mach_vm_address_t data, mach_msg_option64_t options,
    uint64_t msgh_bits_and_send_size, uint64_t msgh_remote_and_local_port,
    uint64_t msgh_voucher_and_id, uint64_t desc_count_and_rcv_name,
    uint64_t rcv_size_and_priority, uint64_t timeout) {
  struct mach_msg2_trap_args args = {
      .data = data,
      .options = options,
      .msgh_bits_and_send_size = msgh_bits_and_send_size,
      .msgh_remote_and_local_port = msgh_remote_and_local_port,
      .msgh_voucher_and_id = msgh_voucher_and_id,
      .desc_count_and_rcv_name = desc_count_and_rcv_name,
      .rcv_size_and_priority = rcv_size_and_priority,
      .timeout = timeout};

  mach_msg_return_t rv = mach_msg2_trap(&args);
  return rv;
}

kern_return_t mach_msg_overwrite_trap_wrapper(
    user_addr_t msg, mach_msg_option_t option, mach_msg_size_t send_size,
    mach_msg_size_t rcv_size, mach_port_name_t rcv_name,
    mach_msg_timeout_t timeout, mach_msg_priority_t priority,
    user_addr_t rcv_msg) {
  struct mach_msg_overwrite_trap_args args = {.msg = msg,
                                              .option = option,
                                              .send_size = send_size,
                                              .rcv_size = rcv_size,
                                              .rcv_name = rcv_name,
                                              .timeout = timeout,
                                              .priority = priority,
                                              .rcv_msg = rcv_msg};

  int rv = mach_msg_overwrite_trap(&args);
  return rv;
}

kern_return_t host_create_mach_voucher_trap_wrapper(
    mach_port_name_t host, mach_voucher_attr_raw_recipe_array_t recipes,
    int recipes_size, user_addr_t voucher) {
  struct host_create_mach_voucher_args args = {
      .host = host,
      .recipes = recipes,
      .recipes_size = recipes_size,
      .voucher = voucher,
  };

  int rv = host_create_mach_voucher_trap(&args);
  return rv;
}

kern_return_t mach_voucher_extract_attr_recipe_trap_wrapper(
    mach_port_name_t voucher_name, mach_voucher_attr_key_t key,
    mach_voucher_attr_raw_recipe_t recipe, user_addr_t recipe_size) {
  struct mach_voucher_extract_attr_recipe_args args = {
      .voucher_name = voucher_name,
      .key = key,
      .recipe = recipe,
      .recipe_size = recipe_size,
  };

  int rv = mach_voucher_extract_attr_recipe_trap(&args);
  return rv;
}

kern_return_t _kernelrpc_mach_port_request_notification_trap_wrapper(
    mach_port_name_t task, mach_port_name_t name, mach_msg_id_t msgid,
    mach_port_mscount_t sync, mach_port_name_t notify,
    mach_msg_type_name_t notifyPoly, mach_port_name_t *previous) {
  struct _kernelrpc_mach_port_request_notification_args args = {
      .target = task,
      .name = name,
      .msgid = msgid,
      .sync = sync,
      .notify = notify,
      .notifyPoly = notifyPoly,
      .previous = (user_addr_t)previous};

  int rv = _kernelrpc_mach_port_request_notification_trap(&args);
  return rv;
}

kern_return_t thread_create_running(task_t task, int flavor,
                                    thread_state_t new_state,
                                    mach_msg_type_number_t new_state_count,
                                    thread_t *new_thread);

void *get_init_task();

// kern_return_t
// thread_create_running(
// 	task_t         task,
// 	int                     flavor,
// 	thread_state_t          new_state,
// 	mach_msg_type_number_t  new_state_count,
// 	thread_t                                *new_thread)
thread_t CreateKernelThread() {
  thread_t thread = NULL;
  // kern_return_t ret =
  kernel_thread_create(/* continuation */ NULL,
                       /* parameter */ NULL, /* priority */ 0, &thread);
  thread->t_task = kernel_task;
  return thread;
}

// __attribute__((visibility("default")))
// thread_t CreateInitThread() {
//   thread_t thread = NULL;
//   task_t init_task = get_init_task();
//   if (thread_create_running(init_task, 0, 0, 0, &thread)) {
//     return NULL;
//   }
//   return thread;
// }

void XNUThreadGetThreadName(thread_t th, char *name) {
  thread_get_thread_name(th, name);
}

thread_t CreateWaitingThread(task_t task) {
  thread_t thread = NULL;

  if (main_thread_create_waiting(task, (thread_continue_t)task_wait_to_return,
                                 task_get_return_wait_event(task), &thread)) {
    return NULL;
  }
  // if (thread_create_running(task, 0, 0, 0, &thread)) {
  //   return NULL;
  // }
  return thread;
}

task_t GetTaskFromThread(thread_t thread) {
  return thread->t_task;
}

typedef struct proc *proc_t;

void proc_signalend(struct proc *, int locked);
void proc_transend(proc_t p, int locked);

thread_t cloneproc(task_t, coalition_t *, proc_t, int, int);
thread_t CloneTask(task_t task) {
  // TODO(nedwill): consider using posix_spawn syscall instead
  thread_t thread =
      cloneproc(TASK_NULL, NULL, get_bsdtask_info(task), FALSE, FALSE);
  proc_signalend(get_bsdtask_info(thread->t_task), 0);
  proc_transend(get_bsdtask_info(thread->t_task), 0);
  // TODO(nedwill): consider supporting this
  // act_set_astbsd(thread);
  return thread;
}

void ClearTaskWait(task_t task) {
  task_clear_return_wait(task, TCRW_CLEAR_ALL_WAIT);
  // We can now safely drop the extra reference we got when cloning
  task_deallocate(task);
}

thread_t CloneTaskFromInit() {
  return CloneTask(get_init_task());
}

proc_t GetProcFromTask(task_t task) {
  return get_bsdtask_info(task);
}

kern_return_t thread_get_special_reply_port_wrapper() {
  struct thread_get_special_reply_port_args args = {};

  int rv = thread_get_special_reply_port(&args);
  return rv;
}

kern_return_t mk_timer_create_trap_wrapper() {
  struct mk_timer_create_trap_args args = {};

  int rv = mk_timer_create_trap(&args);
  return rv;
}

kern_return_t mk_timer_destroy_trap_wrapper(mach_port_name_t name) {
  struct mk_timer_destroy_trap_args args = {.name = name};

  int rv = mk_timer_destroy_trap(&args);
  return rv;
}

kern_return_t mk_timer_arm_trap_wrapper(mach_port_name_t name,
                                        uint64_t expire_time) {
  struct mk_timer_arm_trap_args args = {.name = name,
                                        .expire_time = expire_time};

  int rv = mk_timer_arm_trap(&args);
  return rv;
}

kern_return_t mk_timer_cancel_trap_wrapper(mach_port_name_t name,
                                           uint64_t result_time) {
  struct mk_timer_cancel_trap_args args = {.name = name,
                                           .result_time = result_time};

  int rv = mk_timer_cancel_trap(&args);
  return rv;
}

kern_return_t mk_timer_arm_leeway_trap_wrapper(mach_port_name_t name,
                                               uint64_t mk_timer_flags,
                                               uint64_t expire_time,
                                               uint64_t mk_leeway) {
  struct mk_timer_arm_leeway_trap_args args = {.name = name,
                                               .mk_timer_flags = mk_timer_flags,
                                               .expire_time = expire_time,
                                               .mk_leeway = mk_leeway};

  int rv = mk_timer_arm_leeway_trap(&args);
  return rv;
}

void *calloc(size_t a, size_t b);
void free(void *ptr);

void DoRandomMachTrap(unsigned int number, void *data, size_t size) {
  number %= mach_trap_count;
  const mach_trap_t *entry = &mach_trap_table[number];
  size_t argument_size = entry->mach_trap_arg_count * 8;
  void *arguments = calloc(1, argument_size);
  if (!arguments) {
    return;
  }
  if (size > argument_size) {
    size = argument_size;
  }
  int retval;
  GetHypercallInterface()->BlockCopyin();
  entry->mach_trap_function(arguments);
  GetHypercallInterface()->UnblockCopyin();
  free(arguments);
}

// TODO(nedwill): move the following section into concurrence test
lck_mtx_t test_mtx;
lck_rw_t test_rw;

bool sync_initialized = false;

enum LOCK_TEST {
  YIELD = 0,
  MUTEX = 1,
  READ_WRITE_SHARED = 2,
  READ_WRITE_EXCLUSIVE = 3,
  MUTEX2 = 4,
  READ_WRITE_SHARED2 = 5,
  READ_WRITE_EXCLUSIVE2 = 6,
};

size_t current_index = 0;
bool failed = false;
// If 0, entire array is checked.
size_t num_expected = 10;
int expected_order[] = {4, 0, 2, 2, 1, 4, 3, 4, 3, 0, 4, 0, 2, 2, 1,
                        3, 0, 3, 2, 0, 1, 3, 1, 2, 0, 1, 4, 2, 3};

// These functions are called by the concurrence_test_fuzzer
void HostTestInit() {
  if (!sync_initialized) {
    lck_mtx_init(&test_mtx, NULL, NULL);
    lck_rw_init(&test_rw, NULL, NULL);
  }
  current_index = 0;
  failed = false;
}

bool check_state(int id) {
  // Check if another thread has already failed
  GetHypercallInterface()->ThreadPrintf(
      "checking id %d for current index %d, failed %d\n", id, current_index,
      failed);
  if (failed) {
    return false;
  }
  if (current_index >= sizeof(expected_order) / sizeof(int)) {
    GetHypercallInterface()->ThreadPrintf("check_state: succeeded\n");
    return true;
  }
  printf("current_index %d\n", current_index);
  int expected_id = expected_order[current_index++];
  // Note we just incremented so this is the last check
  GetHypercallInterface()->ThreadPrintf("id %d, expected_id %d\n", id,
                                        expected_id);
  if (id != expected_id) {
    if (current_index >= num_expected) {
      GetHypercallInterface()->ThreadPrintf(
          "almost succeeded at index %d with id %d but required %d\n",
          current_index - 1, id, expected_id);
      CheckSchedulerState();
      if (GetHypercallInterface()->RandomDataRemaining()) {
        // GetHypercallInterface()->Abort();
      }
      // GetHypercallInterface()->Abort();
    }
    GetHypercallInterface()->ThreadPrintf("check_state: failed 2\n");
    failed = true;
    return false;
  }
  if (!num_expected) {
    num_expected = sizeof(expected_order) / sizeof(int);
  }
  if (current_index >= num_expected) {
    // Found the bug interleaving!
    GetHypercallInterface()->Abort();
  }

  return true;
}

void *HostTestThread(void *tid) {
  int id = (int)tid;
  while (true) {
    bool passed = false;
    switch (id) {
      case YIELD: {
        size_t before = GetHypercallInterface()->BytesNeeded();
        thread_yield_internal(1);
        size_t after = GetHypercallInterface()->BytesNeeded();
        GetHypercallInterface()->ThreadPrintf("yield cost %d bytes\n",
                                              after - before);
        passed = check_state(id);
        break;
      }
      case MUTEX:
      case MUTEX2: {
        size_t before = GetHypercallInterface()->BytesNeeded();
        if (id == MUTEX2) {
          GetHypercallInterface()->ThreadPrintf("mutex2 before lock\n");
        }
        lck_mtx_lock(&test_mtx);
        if (id == MUTEX2) {
          GetHypercallInterface()->ThreadPrintf("mutex2 after lock\n");
        }
        size_t after = GetHypercallInterface()->BytesNeeded();
        GetHypercallInterface()->ThreadPrintf("mutex lock cost %d bytes\n",
                                              after - before);
        if (id == MUTEX2) {
          GetHypercallInterface()->ThreadPrintf("mutex2 before check_state\n");
        }
        passed = check_state(id);
        if (id == MUTEX2) {
          GetHypercallInterface()->ThreadPrintf("mutex2 after check_state\n");
        }
        before = GetHypercallInterface()->BytesNeeded();
        if (id == MUTEX2) {
          GetHypercallInterface()->ThreadPrintf("mutex2 before unlock\n");
        }
        lck_mtx_unlock(&test_mtx);
        if (id == MUTEX2) {
          GetHypercallInterface()->ThreadPrintf("mutex2 after unlock\n");
        }
        after = GetHypercallInterface()->BytesNeeded();
        // GetHypercallInterface()->ThreadPrintf("mutex unlock cost %d bytes\n", after-before);
        break;
      }
      case READ_WRITE_SHARED:
      case READ_WRITE_SHARED2: {
        size_t before = GetHypercallInterface()->BytesNeeded();
        lck_rw_lock_shared(&test_rw);
        size_t after = GetHypercallInterface()->BytesNeeded();
        GetHypercallInterface()->ThreadPrintf("rw shared lock cost %d bytes\n",
                                              after - before);
        passed = check_state(id);
        before = GetHypercallInterface()->BytesNeeded();
        lck_rw_unlock_shared(&test_rw);
        after = GetHypercallInterface()->BytesNeeded();
        // GetHypercallInterface()->ThreadPrintf("rw shared unlock cost %d bytes\n",
        // after-before);
        break;
      }
      case READ_WRITE_EXCLUSIVE:
      case READ_WRITE_EXCLUSIVE2: {
        size_t before = GetHypercallInterface()->BytesNeeded();
        lck_rw_lock_exclusive(&test_rw);
        size_t after = GetHypercallInterface()->BytesNeeded();
        GetHypercallInterface()->ThreadPrintf(
            "rw exclusive lock cost %d bytes\n", after - before);
        passed = check_state(id);
        before = GetHypercallInterface()->BytesNeeded();
        lck_rw_unlock_exclusive(&test_rw);
        after = GetHypercallInterface()->BytesNeeded();
        // GetHypercallInterface()->ThreadPrintf("rw exclusive unlock cost %d bytes\n",
        // after-before);
        break;
      }
      default: {
        GetHypercallInterface()->Abort();
        break;
      }
    }
    if (!passed) {
      break;
    }
  }

  return NULL;
}

void DoVmFault(uint64_t address, vm_prot_t type) {
  vm_fault(current_thread()->map, address, type,
           /* change_wiring */ FALSE, VM_KERN_MEMORY_NONE, THREAD_ABORTSAFE,
           /* caller_pmap */ NULL, /* caller_pmap_addr */ 0);
}
