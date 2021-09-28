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

#include <kern/assert.h>
#include <kern/btlog.h>
#include <kern/counter.h>
#include <kern/locks.h>
#include <stdbool.h>
#include <vm/vm_kern.h>

void kheap_startup_init() {}

void zone_view_startup_init() {}

void lck_attr_startup_init(struct lck_attr_startup_spec *sp) {}

void lck_grp_startup_init() {}

lck_attr_t *lck_attr_alloc_init() { return (void *)1; }

void lck_mtx_assert() {}

void lck_mtx_init() {}

void lck_mtx_lock() {}

void lck_spin_init() {}

void lck_rw_startup_init(struct lck_rw_startup_spec *spec) {}

// fake these so they aren't null but still invalid
lck_grp_attr_t  *lck_grp_attr_alloc_init(
void) {
  return (void*)1;
}

lck_grp_t       *lck_grp_alloc_init(
	const char*             grp_name,
	lck_grp_attr_t  *attr) {
    return (void*)1;
  }

lck_rw_t         *lck_rw_alloc_init(
	lck_grp_t               *grp,
	lck_attr_t              *attr) { return (void*)1; }

lck_mtx_t        *lck_mtx_alloc_init(
	lck_grp_t               *grp,
	lck_attr_t              *attr) { return (void*)1; }

lck_spin_t      *lck_spin_alloc_init(
	lck_grp_t               *grp,
	lck_attr_t              *attr) { return (void*)1; }

void lck_mtx_lock_spin() {}

void lck_mtx_convert_spin() {}

void lck_mtx_free() {}

void lck_rw_init() {}

void lck_mtx_unlock() {}

void lck_attr_free() {}

void lck_attr_setdebug() {}

OS_OVERLOADABLE
uint64_t counter_load(unsigned long long **counter) { assert(false); }

int32_t sysctl_get_bound_cpuid(void) { assert(false); }

kern_return_t sysctl_thread_bind_cpuid(int32_t cpuid) { assert(false); }

kern_return_t kernel_memory_allocate(vm_map_t map, vm_offset_t *addrp,
                                     vm_size_t size, vm_offset_t mask,
                                     kma_flags_t flags, vm_tag_t tag) {
  assert(false);
}

void lck_mtx_startup_init(struct lck_mtx_startup_spec *spec) {}

void
btlog_add_entry(btlog_t *btlog,
    void *element,
    uint8_t operation,
    void *bt[],
    size_t btcount)
{}

void
btlog_remove_entries_for_element(btlog_t *btlog,
    void *element) {}

btlog_t *
btlog_create(size_t numrecords,
    size_t record_btdepth,
    boolean_t caller_will_remove_entries_for_element) {
      assert(false);
    }

void machine_init(void) { assert(false); }

void device_service_create(void) { assert(false); }

void bsd_init(void) { assert(false); }

void slave_machine_init(__unused void *param) { assert(false); }

void phys_carveout_init() { assert(false); }
void hv_support_init() { assert(false); }
void vm_mem_bootstrap() { assert(false); }
void kdp_init() { assert(false); }
void workq_init() { assert(false); }
void machine_lockdown() { assert(false); }
void thread_max() { assert(false); }
void kperf_init_early() { assert(false); }
void thread_daemon_init() { assert(false); }
void mac_policy_initmach() { assert(false); }
void vm_kernel_reserved_entry_init() { assert(false); }
void kdebug_free_early_buf() { assert(false); }
void turnstiles_init() { assert(false); }
void vm_commpage_text_init() { assert(false); }
void machine_load_context() { assert(false); }
void ipc_pthread_priority_init() { assert(false); }
void PE_i_can_has_debugger() { assert(false); }
void sfi_init() { assert(false); }
void dtrace_early_init() { assert(false); }
void sched_startup() { assert(false); }
void ml_get_interrupts_enabled() { assert(false); }
void kernel_list_tests() { assert(false); }
void thread_machine_init_template() { assert(false); }
void task_max() { assert(false); }
void thread_get_perfcontrol_class() { assert(false); }
void ml_set_interrupts_enabled() { assert(false); }
void processor_up() { assert(false); }
void exception_init() { assert(false); }
void vm_set_restrictions() { assert(false); }
void thread_init() { assert(false); }
void console_init() { assert(false); }
void idle_thread_create() { assert(false); }
void PE_init_iokit() { assert(false); }
void mac_policy_init() { assert(false); }
void bsd_scale_setup() { assert(false); }
void mapping_adjust() { assert(false); }
void trust_cache_init() { assert(false); }

vm_size_t mem_size = 4000000;

void version_minor() { assert(false); }
void restartable_init() { assert(false); }
void clock_init() { assert(false); }
void kpc_init() { assert(false); }
void vnguard_policy_init() { assert(false); }
void coalitions_init() { assert(false); }
void PE_lockdown_iokit() { assert(false); }
void work_interval_subsystem_init() { assert(false); }
void kernel_do_post() { assert(false); }
void stack_alloc_try() { assert(false); }
void vm_commpage_init() { assert(false); }
void serial_keyboard_init() { assert(false); }
void stackshot_init() { assert(false); }
void task_threadmax() { assert(false); }
void version() { assert(false); }
void mach_init_activity_id() { assert(false); }
void current_processor() { assert(false); }
void telemetry_init() { assert(false); }
void vm_pageout() { assert(false); }
void sdt_early_init() { assert(false); }
void task_init() { assert(false); }
void vm_page_init_local_q() { assert(false); }
void bootprofile_init() { assert(false); }

struct machine_info machine_info;
uint64_t max_mem_actual = 4000000;

void thread_bind() { assert(false); }
void spinlock_timeout_panic() { assert(false); }
void sched_dualq_dispatch() { assert(false); }
void processor_state_update_explicit() { assert(false); }
void mapping_free_prime() { assert(false); }
void PE_parse_boot_arg_str() { assert(false); }
void timer_start() { assert(false); }
void atm_init() { assert(false); }
void version_major() { assert(false); }
void waitq_bootstrap() { assert(false); }
void sched_init() { assert(false); }
void kperf_init() { assert(false); }
void kernel_thread_create() { assert(false); }
void machine_set_current_thread() { assert(false); }
void idle_thread() { assert(false); }
void kasan_late_init() { assert(false); }
void thread_call_initialize() { assert(false); }
void clock_service_create() { assert(false); }
void ipc_thread_call_init() { assert(false); }
void corpses_init() { assert(false); }
void OSKextRemoveKextBootstrap() { assert(false); }
void bank_init() { assert(false); }
void kdebug_init() { assert(false); }
void vm_free_delayed_pages() { assert(false); }
void initialize_screen() { assert(false); }
void serverperfmode() { assert(false); }
void host_statistics_init() { assert(false); }

boolean_t doprnt_hide_pointers = true;
