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

#include <i386/cpu_data.h>
#include <i386/cpu_topology.h>
#include <i386/fpu.h>
#include <i386/locks.h>
#include <i386/machine_routines.h>
#include <i386/mp.h>
#include <i386/pmCPU.h>
#include <i386/thread.h>
#include <i386/types.h>
#include <i386/vmx/vmx_cpu.h>
#include <kern/clock.h>
#include <kern/counter.h>
#include <kern/cpu_data.h>
#include <kern/debug.h>
#include <kern/kalloc.h>
#include <kern/locks.h>
#include <kern/misc_protos.h>
#include <kern/percpu.h>
#include <kern/processor.h>
#include <kern/sched_urgency.h>
#include <kern/startup.h>
#include <kern/task.h>
#include <kern/ticket_lock.h>
#include <kern/zalloc.h>
#include <libkern/copyio.h>
#include <libkern/kernel_mach_header.h>
#include <libkern/zconf.h>
#include <libkern/zlib.h>
#include <mach/clock_types.h>
#include <mach/i386/boolean.h>
#include <mach/i386/kern_return.h>
#include <mach/i386/thread_status.h>
#include <mach/i386/vm_param.h>
#include <mach/i386/vm_types.h>
#include <mach/kern_return.h>
#include <mach/kmod.h>
#include <mach/mach_types.h>
#include <mach/machine.h>
#include <mach/message.h>
#include <mach/ndr.h>
#include <mach/thread_info.h>
#include <mach/thread_status.h>
#include <mach/vm_types.h>
#include <machine/machine_routines.h>
#include <machine/task.h>
#include <os/base.h>
#include <pexpert/pexpert.h>
#include <prng/random.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <sys/_types/_uuid_t.h>
#include <sys/cdefs.h>
#include <sys/kdebug_kernel.h>
#include <uuid/uuid.h>
#include <vm/vm_kern.h>
#include <libkern/crypto/rand.h>
#include <libkern/crypto/crypto_internal.h>

#include "fuzz/host/hypercall/hypercall.h"

vm_size_t mem_size = 4000000;

uint64_t max_mem_actual = 4000000;

int IODTGetLoaderInfo(const char *key, void **infoAddr, int *infosize) {
  if (!*infosize) {
    return 0;
  }
  GetHypercallInterface()->GetFuzzedBytes(*infoAddr, *infosize);
  return 0;
}
void IORecordProgressBackbuffer() {
  GetHypercallInterface()->Abort();
}

void IOSleep() {
  GetHypercallInterface()->Yield();
}

bool IOTaskHasEntitlement() {
  return true;
}
void Idle_PTs_release() {}
uint64_t LockTimeOutTSC = 0;
uint32_t LockTimeOutUsec = 0;
void MD5Final() {
  GetHypercallInterface()->Abort();
}
void MD5Init() {
  GetHypercallInterface()->Abort();
}
void MD5Update() {
  GetHypercallInterface()->Abort();
}
uint64_t MutexSpin = 0;
void OSBacktrace() {}
void OSKextGetAllocationSiteForCaller() {
  GetHypercallInterface()->Abort();
}
void OSKextGetKmodIDForSite() {
  GetHypercallInterface()->Abort();
}
void OSKextRemoveKextBootstrap() {}
void OSKextSetReceiptQueried() {
  GetHypercallInterface()->Abort();
}
void SavePanicInfo(const char *message, void *panic_data,
                   uint64_t panic_options) {
  GetHypercallInterface()->Abort();
}
void WKdm_compress_new() {
  GetHypercallInterface()->Abort();
}
void WKdm_decompress_new() {
  GetHypercallInterface()->Abort();
}

void free(void *ptr);

void _Block_object_dispose(const void *object, const int flags) {}

unsigned int _MachineStateCount[] = {};
void _NSConcreteStackBlock() {
  GetHypercallInterface()->Abort();
}
void _disable_preemption() {
  GetHypercallInterface()->Abort();
}
void _enable_preemption() {
  GetHypercallInterface()->SetInterruptsEnabled(true);
}
kernel_mach_header_t _mh_execute_header;

void abort_panic_transfer() {
  GetHypercallInterface()->Abort();
}
void allow_data_exec() {
  GetHypercallInterface()->Abort();
}
void allow_stack_exec() {
  GetHypercallInterface()->Abort();
}
void arcade_upcall() {
  GetHypercallInterface()->Abort();
}
void bcopy_phys() {
  GetHypercallInterface()->Abort();
}
void begin_panic_transfer() {
  GetHypercallInterface()->Abort();
}

int cc_rand_generate(void *out, size_t outlen) {
  memset(out, 0, outlen);
  return 0;
}

void coalition_notification() {
  GetHypercallInterface()->Abort();
}
void commpage_populate() {}
void commpage_set_memory_pressure() {
  GetHypercallInterface()->Abort();
}
void commpage_text_populate() {}
void commpage_update_active_cpus() {
  GetHypercallInterface()->Abort();
}
void commpage_update_mach_approximate_time() {}
void consider_machine_adjust() {
  GetHypercallInterface()->Abort();
}
void consider_machine_collect() {
  GetHypercallInterface()->Abort();
}
boolean_t coprocessor_paniclog_flush = false;

int copyinmsg(const user_addr_t user_addr, char *kernel_addr,
              mach_msg_size_t nbytes) {
  return copyin(user_addr, kernel_addr, nbytes);
}

int copyout_atomic32(uint32_t u32, user_addr_t user_addr) {
  return copyout(&u32, user_addr, sizeof(u32));
}

int copyout_atomic64(uint64_t u64, user_addr_t user_addr) {
  GetHypercallInterface()->Abort();
}

int copyoutmsg(const char *kernel_addr, user_addr_t user_addr,
               mach_msg_size_t nbytes) {
  return copyout(kernel_addr, user_addr, nbytes);
}

// TODO(nedwill): no-op until we determine if these are used in a way
// that affects security
OS_OVERLOADABLE
void counter_add(counter_t *counter, uint64_t amount) {}

OS_OVERLOADABLE
void counter_inc(counter_t *counter) {}

OS_OVERLOADABLE
void counter_inc_preemption_disabled(counter_t *counter) {}

void cpu_can_exit() {
  GetHypercallInterface()->Abort();
}
void cpu_control() {
  GetHypercallInterface()->Abort();
}
void cpu_info() {
  GetHypercallInterface()->Abort();
}
void cpu_info_count() {}
void cpu_start() {
  GetHypercallInterface()->Abort();
}
vm_offset_t current_percpu_base() {
  return 0;
}
void debug_task() {
  GetHypercallInterface()->Abort();
}
void device_close() {
  GetHypercallInterface()->Abort();
}
void device_data_action() {
  GetHypercallInterface()->Abort();
}
bool disable_serial_output = false;

uint64_t early_random(void) {
  return 0;
}

void exception_raise() {}
void exception_raise_state() {
  GetHypercallInterface()->Abort();
}
void exception_raise_state_identity() {
  GetHypercallInterface()->Abort();
}
void fairplayd_arcade_request() {
  GetHypercallInterface()->Abort();
}
void fillPage() {}
void gIOHibernateMode() {
  GetHypercallInterface()->Abort();
}
void gLoadedKextSummaries() {
  GetHypercallInterface()->Abort();
}
crypto_functions_t g_crypto_funcs = NULL;


static x86_saved_state_t state;

void *get_user_regs(thread_t thread) {
  memset(&state, 0, sizeof(state));
  GetHypercallInterface()->GetFuzzedBytes(&state, sizeof(state));
  return &state;
}

void halt_all_cpus() {}
void hibernate_page_bitset() {
  GetHypercallInterface()->Abort();
}
void hibernate_page_bittst() {
  GetHypercallInterface()->Abort();
}
void hibernate_page_list_allocate() {
  GetHypercallInterface()->Abort();
}
void hibernate_page_list_setall_machine() {
  GetHypercallInterface()->Abort();
}
void hibernate_processor_setup() {
  GetHypercallInterface()->Abort();
}
void hibernate_should_abort() {
  GetHypercallInterface()->Abort();
}
void hibernate_vm_locks_are_safe() {
  GetHypercallInterface()->Abort();
}
void inuse_ptepages_count() {
  GetHypercallInterface()->Abort();
}
void io_map_spec() {
  GetHypercallInterface()->Abort();
}
void iokit_add_reference() {
  GetHypercallInterface()->Abort();
}
void iokit_port_object_description() {
  GetHypercallInterface()->Abort();
}
void iokit_remove_reference() {
  GetHypercallInterface()->Abort();
}
void iokit_task_app_suspended_changed() {
  GetHypercallInterface()->Abort();
}
void iokit_task_terminate() {}

OS_OVERLOADABLE
void counter_dec(unsigned long long **out) {}

void kasan_fakestack_drop() {}
void kasan_fakestack_gc() {}
void kasan_init_thread() {}
void kasan_late_init() {}
void kasan_notify_address() {}
void kasan_notify_address_nopoison() {
  GetHypercallInterface()->Abort();
}
void kasan_unpoison_stack() {}
void kdp_has_polled_corefile() {
  GetHypercallInterface()->Abort();
}
void kdp_polled_corefile_error() {
  GetHypercallInterface()->Abort();
}
void kdp_raise_exception() {
  GetHypercallInterface()->Abort();
}
void kdp_vtophys() {
  GetHypercallInterface()->Abort();
}
void kern_dump() {
  GetHypercallInterface()->Abort();
}
kern_return_t kernel_do_post() {
  return KERN_SUCCESS;
}
kern_return_t kernel_list_tests() {
  return KERN_SUCCESS;
}
void kernel_preempt_check() {
  GetHypercallInterface()->Abort();
}
void kheap_temp_leak_panic() {
  GetHypercallInterface()->Abort();
}
void kmod_panic_dump(vm_offset_t *addr, unsigned int dump_cnt) {
  GetHypercallInterface()->Abort();
}

uint32_t kpc_configurable_config_count() {
  return GetHypercallInterface()->GetFuzzedUint32();
}

uint32_t kpc_configurable_count() {
  return 6;
}

uint64_t kpc_configurable_max() {
  return GetHypercallInterface()->GetFuzzedUint64();
}

uint32_t kpc_fixed_config_count() {
  return GetHypercallInterface()->GetFuzzedUint32();
}

uint32_t kpc_fixed_count() {
  return GetHypercallInterface()->GetFuzzedUint32InRange(0, 2);
}

uint64_t kpc_fixed_max() {
  return GetHypercallInterface()->GetFuzzedUint64();
}

uint32_t kpc_get_all_cpus_counters() {
  return GetHypercallInterface()->GetFuzzedUint32InRange(0, 32);
}

int kpc_get_configurable_config(uint64_t *configv, uint64_t pmc_mask) {
  *configv = GetHypercallInterface()->GetFuzzedUint64();
  return 0;
}

uint32_t kpc_get_configurable_counters() {
  return GetHypercallInterface()->GetFuzzedUint32();
}

int kpc_get_fixed_config(uint64_t *a) {
  *a = GetHypercallInterface()->GetFuzzedUint64();
  return 0;
}

int kpc_get_fixed_counters() {
  return 32;
}

void kpc_get_rawpmu_config() {
  GetHypercallInterface()->Abort();
}

boolean_t kpc_is_running_configurable() {
  return GetHypercallInterface()->GetFuzzedBool();
}

boolean_t kpc_is_running_fixed() {
  return GetHypercallInterface()->GetFuzzedBool();
}

uint32_t kpc_rawpmu_config_count() {
  return GetHypercallInterface()->GetFuzzedUint32();
}

void kpc_set_config_arch() {
  GetHypercallInterface()->Abort();
}

int kpc_set_period_arch(struct kpc_config_remote *mp_config) {
  return 0;
}

void kpc_set_running_arch() {}

void kperf_debug_level() {
  GetHypercallInterface()->Abort();
}
void kperf_init() {}
void kperf_init_early() {}
void kperf_kdebug_active() {
  GetHypercallInterface()->Abort();
}
void kperf_kdebug_handler() {
  GetHypercallInterface()->Abort();
}
void kperf_kpc_thread_ast() {
  GetHypercallInterface()->Abort();
}
void kperf_lazy_cpu_action() {
  GetHypercallInterface()->Abort();
}
void kperf_lazy_make_runnable() {}
void kperf_lazy_off_cpu() {}
void kperf_on_cpu_active() {
  GetHypercallInterface()->Abort();
}
void kperf_on_cpu_internal() {}
void kperf_sample() {
  GetHypercallInterface()->Abort();
}
void kperf_status() {
  GetHypercallInterface()->Abort();
}

void kptimer_running_setup() {
  GetHypercallInterface()->Abort();
}
void ktest_assertion_check() {
  GetHypercallInterface()->Abort();
}
// const char *T_SYM(current_file);
// const char *T_SYM(current_func);
// unsigned int T_SYM(current_line);
// void T_SYM(log)(const char *msg, ...) {
//   GetHypercallInterface()->Abort();
// }
// void T_SYM(set_current_expr)(const char *expr_fmt, ...) {
//   GetHypercallInterface()->Abort();
// }
// void T_SYM(set_current_msg)(const char *msg, ...) {
//   GetHypercallInterface()->Abort();
// }
// void T_SYM(set_current_var)(const char *name, const char *value_fmt, ...) {
//   GetHypercallInterface()->Abort();
// }
// T_SYM(temp) T_SYM(temp1), T_SYM(temp2), T_SYM(temp3);
// void ktest_testcase() { GetHypercallInterface()->Abort(); }
void kvtophys() {
  GetHypercallInterface()->Abort();
}

void kdp_init() {}
void log_putc() {
  GetHypercallInterface()->Abort();
}
uint32_t low_eintstack[1];
void lz4_decode_asm() {
  GetHypercallInterface()->Abort();
}
void mach_exception_raise() {
  GetHypercallInterface()->Abort();
}
void mach_exception_raise_state() {
  GetHypercallInterface()->Abort();
}
void mach_exception_raise_state_identity() {
  GetHypercallInterface()->Abort();
}
void machine_callstack() {
  GetHypercallInterface()->Abort();
}
processor_t machine_choose_processor(processor_set_t pset,
                                     processor_t processor) {
  GetHypercallInterface()->Abort();
}
int machine_csv(cpuvn_e cve) {
  return 0;
}
void machine_idle() {
  GetHypercallInterface()->Abort();
}
void machine_init() {
  clock_config();
}

void machine_load_context(thread_t thread) {
  GetHypercallInterface()->Abort();
}

void machine_lockdown() {}
void machine_max_runnable_latency() {
  GetHypercallInterface()->Abort();
}
void machine_signal_idle() {
  GetHypercallInterface()->Abort();
}
void machine_signal_idle_deferred() {
  GetHypercallInterface()->Abort();
}
vm_offset_t machine_stack_detach(thread_t thread) {
  GetHypercallInterface()->Abort();
}
void machine_stack_handoff(thread_t old, thread_t new) {}
void machine_switch_perfcontrol_context() {}
void machine_switch_perfcontrol_state_update() {}
kern_return_t machine_task_get_state(task_t task, int flavor,
                                     thread_state_t state,
                                     mach_msg_type_number_t *state_count) {
  return KERN_SUCCESS;
}
void machine_task_init(task_t new_task, task_t parent_task,
                       boolean_t memory_inherit) {}
kern_return_t machine_task_set_state(task_t task, int flavor,
                                     thread_state_t state,
                                     mach_msg_type_number_t state_count) {
  return KERN_SUCCESS;
}
void machine_task_terminate(task_t task) {}
void machine_tecs(thread_t thr) {
  GetHypercallInterface()->Abort();
}
boolean_t machine_timeout_suspended() {
  GetHypercallInterface()->Abort();
}
void machine_trace_thread() {
  GetHypercallInterface()->Abort();
}
void machine_trace_thread64() {
  GetHypercallInterface()->Abort();
}
void machine_track_platform_idle() {
  GetHypercallInterface()->Abort();
}
void machine_work_interval_notify() {
  GetHypercallInterface()->Abort();
}
uint64_t max_mem = 0;
void memset_word() {
  GetHypercallInterface()->Abort();
}
void ml_affinity_to_pset() {
  GetHypercallInterface()->Abort();
}
boolean_t ml_at_interrupt_context() {
  GetHypercallInterface()->Abort();
}
void ml_cpu_begin_state_transition(int cpu_id) {
  GetHypercallInterface()->Abort();
}
void ml_cpu_end_state_transition(int cpu_id) {
  GetHypercallInterface()->Abort();
}

void ml_cpu_get_info(ml_cpu_info_t *info) {
  info->cache_line_size = 64;
}

void ml_delay_on_yield() {
  GetHypercallInterface()->Abort();
}
uint64_t ml_energy_stat(thread_t thread) {
  GetHypercallInterface()->Abort();
}
uint64_t ml_get_booter_memory_size(void) {
  return 0;
}
boolean_t ml_get_interrupts_enabled() {
  return GetHypercallInterface()->GetInterruptsEnabled();
}
int ml_get_max_affinity_sets() {
  return 0;
}
void ml_get_power_state(boolean_t *a, boolean_t *b) {
  *a = GetHypercallInterface()->GetFuzzedBool();
  *b = GetHypercallInterface()->GetFuzzedBool();
}
uint64_t ml_get_timebase(void) {
  return 0;
}

size_t ml_get_vm_reserved_regions(bool vm_is64bit,
                                  struct vm_reserved_region **regions) {
  *regions = NULL;
  return 0;
}

uint64_t ml_gpu_stat(thread_t thread) {
  return 0;
}
void ml_gpu_stat_update(uint64_t gpu_ns_delta) {
  GetHypercallInterface()->Abort();
}

vm_size_t ml_nofault_copy(vm_offset_t virtsrc, vm_offset_t virtdst,
                          vm_size_t size) {
  GetHypercallInterface()->Abort();
}

void ml_panic_trap_to_debugger(const char *panic_format_str,
                               va_list *panic_args, unsigned int reason,
                               void *ctx, uint64_t panic_options_mask,
                               unsigned long panic_caller) {
  GetHypercallInterface()->LogVaList(panic_format_str, *panic_args);
  GetHypercallInterface()->Abort();
}

boolean_t ml_set_interrupts_enabled(boolean_t enable) {
  // Yield before disabling
  if (!enable) {
    GetHypercallInterface()->Yield();
  }
  bool result = GetHypercallInterface()->SetInterruptsEnabled(enable);
  // Yield after reenabling
  if (enable) {
    GetHypercallInterface()->Yield();
  }
  return result;
}

vm_offset_t ml_static_ptovirt(vm_offset_t offset) {
  GetHypercallInterface()->Abort();
}

boolean_t ml_validate_nofault(vm_offset_t virtsrc, vm_size_t size) {
  GetHypercallInterface()->Abort();
}
uint32_t ml_wait_max_cpus() {
  return 4;
}
void mp_interrupt_watchdog() {
  GetHypercallInterface()->Abort();
}
void mp_kdp_enter(boolean_t proceed_on_failure) {
  GetHypercallInterface()->Abort();
}
void mp_kdp_exit() {
  GetHypercallInterface()->Abort();
}
void mp_rendezvous_lock() {
  GetHypercallInterface()->Abort();
}
void mp_rendezvous_unlock() {
  GetHypercallInterface()->Abort();
}
void msgbufp() {
  GetHypercallInterface()->Abort();
}
void nanoseconds_to_absolutetime(uint64_t nanoseconds, uint64_t *result) {
  *result = nanoseconds;
}
void nanotime_to_absolutetime(clock_sec_t secs, clock_nsec_t nanosecs,
                              uint64_t *result) {
  *result = ((uint64_t)secs * NSEC_PER_SEC) + nanosecs;
}
void no_shared_cr3() {
  GetHypercallInterface()->Abort();
}

void pal_hib_rebuild_pmap_structs() {
  GetHypercallInterface()->Abort();
}
void pal_hib_teardown_pmap_structs() {
  GetHypercallInterface()->Abort();
}
bool panic_include_zprint = false;
void panic_include_ztrace() {
  GetHypercallInterface()->Abort();
}
mach_memory_info_t *panic_kext_memory_info;
vm_size_t panic_kext_memory_size;
void panic_print_symbol_name(vm_address_t search) {
  GetHypercallInterface()->Abort();
}
uintptr_t panic_stackshot_buf = 0;
size_t panic_stackshot_buf_len = 0;
void paniclog_flush() {
  GetHypercallInterface()->Abort();
}
void pcid_for_pmap_cpu_tuple() {
  GetHypercallInterface()->Abort();
}
struct percpu_base percpu_base = {.start = 0, .end = 0, .size = 0};

void physmap_base() {
  GetHypercallInterface()->Abort();
}
void physmap_max() {
  GetHypercallInterface()->Abort();
}
void plctrace_disable() {
  GetHypercallInterface()->Abort();
}
void plctrace_enabled() {
  GetHypercallInterface()->Abort();
}
void pmCPUHalt(uint32_t reason) {
  GetHypercallInterface()->Abort();
}
void pmSafeMode(x86_lcpu_t *lcpu, uint32_t flags) {
  GetHypercallInterface()->Abort();
}
bool pmap_supported_feature(pmap_t pmap, pmap_feature_flags_t feat) {
  return true;
}
void mapping_set_mod(ppnum_t pn) {
  GetHypercallInterface()->Abort();
}
void pmap_adjust_unnest_parameters() {
  GetHypercallInterface()->Abort();
}
void pmap_advise_pagezero_range() {}
void pmap_asserts_enabled() {
  GetHypercallInterface()->Abort();
}
void pmap_asserts_traced() {
  GetHypercallInterface()->Abort();
}
void pmap_cache_attributes() {
  GetHypercallInterface()->Abort();
}
void pmap_change_wiring() {}
void pmap_clear_modify() {}
void pmap_clear_reference() {}
void pmap_clear_refmod() {}
void pmap_clear_refmod_options() {}
void pmap_clear_refmod_range_options() {}

uint64_t pmap_commpage_size_min(pmap_t pmap) {
  return 0x1000;
}

void pmap_copy_page() {}
void pmap_copy_part_page() {}
void pmap_cs_allow_invalid() {
  GetHypercallInterface()->Abort();
}
void pmap_disable_NX() {}
void pmap_disconnect() {}
void pmap_disconnect_options() {}
void pmap_dump_page_tables() {
  GetHypercallInterface()->Abort();
}
kern_return_t pmap_enter() {
  return 0;
}
void pmap_flush() {}
void pmap_flush_context_init() {}
bool pmap_get_jit_entitled() {
  return GetHypercallInterface()->GetFuzzedBool();
}
void pmap_get_refmod() {
  GetHypercallInterface()->Abort();
}
bool pmap_get_vm_map_cs_enforced() {
  return GetHypercallInterface()->GetFuzzedBool();
}
bool pmap_has_prot_policy() {
  return false;
}
void pmap_hi_pages_done() {}
bool pmap_is_modified() {
  return GetHypercallInterface()->GetFuzzedBool();
}
bool pmap_is_referenced() {
  return GetHypercallInterface()->GetFuzzedBool();
}
void pmap_ledger_alloc() {
  GetHypercallInterface()->Abort();
}
void pmap_ledger_alloc_init() {
  GetHypercallInterface()->Abort();
}
void pmap_ledger_free() {
  GetHypercallInterface()->Abort();
}
void pmap_list_resident_pages() {}
void pmap_lock_phys_page() {}
kern_return_t pmap_map_block_addr() {
  return KERN_SUCCESS;
}
void pmap_map_compressor_page() {
  GetHypercallInterface()->Abort();
}
kern_return_t pmap_nest() {
  return KERN_SUCCESS;
}
void pmap_nesting_size_max() {
  GetHypercallInterface()->Abort();
}
void pmap_page_protect() {
  GetHypercallInterface()->Abort();
}
void pmap_page_protect_options() {}
void pmap_pageable() {}
void pmap_pcid_activate() {
  GetHypercallInterface()->Abort();
}
void pmap_pcid_ncpus() {
  GetHypercallInterface()->Abort();
}
void pmap_pre_expand() {}
void pmap_protect_options() {}
kern_return_t pmap_query_page_info() {
  return KERN_FAILURE;
}
void pmap_query_resident() {
  GetHypercallInterface()->Abort();
}
void pmap_remove() {}
void pmap_require() {}
void pmap_set_cache_attributes() {}
void pmap_set_jit_entitled() {}
void pmap_set_noencrypt() {
  GetHypercallInterface()->Abort();
}
void pmap_set_process() {}
void pmap_set_vm_map_cs_enforced() {}
void pmap_shared_region_size_min() {
  GetHypercallInterface()->Abort();
}
void pmap_sync_page_attributes_phys() {
  GetHypercallInterface()->Abort();
}
void pmap_sync_page_data_phys() {
  GetHypercallInterface()->Abort();
}
void pmap_test_text_corruption() {
  GetHypercallInterface()->Abort();
}
void pmap_trim() {
  GetHypercallInterface()->Abort();
}
void pmap_unlock_phys_page() {}
void pmap_unmap_compressor_page() {
  GetHypercallInterface()->Abort();
}
void pmap_unnest() {
  GetHypercallInterface()->Abort();
}

kern_return_t pmap_unnest_options() {
  return KERN_SUCCESS;
}

unsigned int random_bool_gen_bits(struct bool_gen *bg, unsigned int *buffer,
                                  unsigned int count, unsigned int numbits) {
  GetHypercallInterface()->Abort();
}
void random_bool_init(struct bool_gen *bg) {}
unsigned int real_ncpus = 1;
uint64_t sane_size = 256 * MB;
void secure_memset() {
  GetHypercallInterface()->Abort();
}
void send_cpu_usage_violation() {
  GetHypercallInterface()->Abort();
}
void send_cpu_wakes_violation() {
  GetHypercallInterface()->Abort();
}
void send_disk_writes_violation() {
  GetHypercallInterface()->Abort();
}
void send_ktrace_background_available() {
  GetHypercallInterface()->Abort();
}
void send_sysdiagnose_notification_with_audit_token() {
  GetHypercallInterface()->Abort();
}
void serial_console_enabled() {
  GetHypercallInterface()->Abort();
}
void serial_getc() {
  GetHypercallInterface()->Abort();
}
void serial_putc() {
  GetHypercallInterface()->Abort();
}
void slave_machine_init(void *machine_param) {
  GetHypercallInterface()->Abort();
}
cpu_type_t slot_type(int slot_num) {
  return 0;
}

cpu_subtype_t slot_subtype(int slot_num) {
  return 0;
}
cpu_subtype_t cpu_subtype(void) {
  GetHypercallInterface()->Abort();
}

xstate_t current_xstate() {
  return 0;
}
uint32_t get_eflags_exportmask() {
  GetHypercallInterface()->Abort();
}
void ml_fp_setvalid(boolean_t valid) {}
void write_random() {
  GetHypercallInterface()->Abort();
}

void cpu_signal_handler(void) {
  GetHypercallInterface()->Abort();
}
void handle_pending_TLB_flushes(void) {
  GetHypercallInterface()->Abort();
}
void NMIPI_panic(cpumask_t cpus, NMI_reason_t reason) {
  GetHypercallInterface()->Abort();
}
void hw_lock_byte_lock(volatile uint8_t *lock_byte) {
  *lock_byte = 1;
}
void hw_lock_byte_unlock(volatile uint8_t *lock_byte) {
  *lock_byte = 0;
}

cpu_threadtype_t slot_threadtype(int slot_num) {
  return 0;
}
void telemetry_notification() {
  GetHypercallInterface()->Abort();
}
void thread_tell_urgency(thread_urgency_t urgency, uint64_t rt_period,
                         uint64_t rt_deadline, uint64_t sched_latency,
                         thread_t nthread) {}
void top_ztrace() {
  GetHypercallInterface()->Abort();
}
void trace_backtrace() {
  GetHypercallInterface()->Abort();
}
void track_this_zone() {
  GetHypercallInterface()->Abort();
}
void trust_cache_init() {}
void uext_server() {
  GetHypercallInterface()->Abort();
}
void version() {
  GetHypercallInterface()->Abort();
}
void version_major() {
  GetHypercallInterface()->Abort();
}
void version_minor() {
  GetHypercallInterface()->Abort();
}
vm_offset_t vm_hib_base = 0;

vm_offset_t vm_kernel_builtinkmod_text = 0;
vm_offset_t vm_kernel_builtinkmod_text_end = 0;
vm_offset_t vm_kernel_slid_base = 0;
vm_offset_t vm_kernel_slid_top = 0;
vm_offset_t vm_kernel_slide = 0;
vm_offset_t vm_kernel_stext = 0;
vm_offset_t vm_kernel_top = 0;

boolean_t vmx_hv_support() {
  return false;
}
void xts_decrypt() {
  GetHypercallInterface()->Abort();
}
void xts_encrypt() {
  GetHypercallInterface()->Abort();
}
void xts_start() {
  GetHypercallInterface()->Abort();
}
uLong zlib_deflate_memory_size(int wbits, int memlevel) {
  GetHypercallInterface()->Abort();
}

// TODO(nedwill): try increasing this to simulate multi-core
// and make additional calls to __smr_init
unsigned zpercpu_count(void) {
  return 1;
}

void default_pager_memory_object_create() {
  GetHypercallInterface()->Abort();
}
void do_mach_notify_dead_name() {
  GetHypercallInterface()->Abort();
}
void do_mach_notify_no_senders() {
  GetHypercallInterface()->Abort();
}
void do_mach_notify_port_deleted() {
  GetHypercallInterface()->Abort();
}
void do_mach_notify_port_destroyed() {
  GetHypercallInterface()->Abort();
}
void do_mach_notify_send_once() {
  GetHypercallInterface()->Abort();
}
kern_return_t host_get_UNDServer() {
  return KERN_FAILURE;
}
kern_return_t host_set_UNDServer() {
  return KERN_FAILURE;
}
kern_return_t kext_request() {
  return KERN_FAILURE;
}
kern_return_t mach_memory_info() {
  return KERN_FAILURE;
}
void mach_vm_region_info() {
  GetHypercallInterface()->Abort();
}
void mach_vm_region_info_64() {
  GetHypercallInterface()->Abort();
}
void mach_zone_force_gc() {}
kern_return_t mach_zone_get_btlog_records() {
  return KERN_FAILURE;
}
void mach_zone_get_zlog_zones() {}
kern_return_t mach_zone_info() {
  return KERN_FAILURE;
}
kern_return_t mach_zone_info_for_largest_zone() {
  return KERN_FAILURE;
}
kern_return_t mach_zone_info_for_zone() {
  return KERN_FAILURE;
}
kern_return_t task_zone_info() {
  return KERN_FAILURE;
}
void vm_mapped_pages_info() {
  GetHypercallInterface()->Abort();
}

void commpage_update_atm_diagnostic_config(uint32_t diagnostic_config) {}

void cpu_exit_wait() {
  GetHypercallInterface()->Abort();
}
void cpu_sleep() {
  GetHypercallInterface()->Abort();
}
void hibernate_vm_lock() {
  GetHypercallInterface()->Abort();
}
void hibernate_vm_unlock() {
  GetHypercallInterface()->Abort();
}
void init_ast_check() {}

bool ml_cpu_can_exit(int cpu_id, processor_reason_t reason) {
  GetHypercallInterface()->Abort();
}

void ml_cpu_down() {
  GetHypercallInterface()->Abort();
}
void ml_cpu_up() {
  GetHypercallInterface()->Abort();
}
void panic_notify() {
  GetHypercallInterface()->Abort();
}
void phyreadpanic() {
  GetHypercallInterface()->Abort();
}
void phywritepanic() {
  GetHypercallInterface()->Abort();
}
uintptr_t pmap_verify_noncacheable(uintptr_t vaddr) {
  GetHypercallInterface()->Abort();
}
void reportphyreaddelayabs() {
  GetHypercallInterface()->Abort();
}
void reportphywritedelayabs() {
  GetHypercallInterface()->Abort();
}

kern_return_t machine_thread_get_state(thread_t thread, thread_flavor_t flavor,
                                       thread_state_t state,
                                       mach_msg_type_number_t *count) {
  GetHypercallInterface()->GetFuzzedBytes(state, *count * sizeof(*state));
  return KERN_SUCCESS;
}
void machine_thread_going_off_core() {}
void machine_thread_going_on_core() {}
kern_return_t machine_thread_inherit_taskwide(thread_t thread,
                                              task_t parent_task) {
  return KERN_SUCCESS;
}
mach_vm_address_t machine_thread_pc(thread_t thread) {
  GetHypercallInterface()->Abort();
}
void machine_thread_reset_pc(thread_t thread, mach_vm_address_t pc) {
  GetHypercallInterface()->Abort();
}

extern void machine_thread_set_insn_copy_optout(thread_t thr) {}

kern_return_t machine_thread_set_state(thread_t thread, thread_flavor_t flavor,
                                       thread_state_t state,
                                       mach_msg_type_number_t count) {
  return KERN_SUCCESS;
}
kern_return_t machine_thread_set_tsd_base(thread_t thread,
                                          mach_vm_offset_t tsd_base) {
  GetHypercallInterface()->Abort();
}
kern_return_t machine_thread_state_convert_to_user(
    thread_t thread, thread_flavor_t flavor, thread_state_t tstate,
    mach_msg_type_number_t *count, thread_set_status_flags_t tssf_flags) {
  return KERN_SUCCESS;
}
void machine_thread_state_initialize(thread_t thread) {
  GetHypercallInterface()->Abort();
}
void machine_thread_switch_addrmode(thread_t thread) {
  // machine_thread_create(thread, task, false);
}
void machine_thread_template_init(thread_t thr_template) {}
bool IOCurrentTaskHasEntitlement() {
  return true;
}
void IOPMRootDomainGetWillShutdown() {
  GetHypercallInterface()->Abort();
}
void IOSetImageBoot() {
  GetHypercallInterface()->Abort();
}
void OSKextGetRefGrpForCaller() {
  GetHypercallInterface()->Abort();
}

void _storage_lock() {
  GetHypercallInterface()->Abort();
}
void _storage_unlock() {
  GetHypercallInterface()->Abort();
}
void aes_encrypt_key_gcm() {
  GetHypercallInterface()->Abort();
}
void aes_encrypt_set_iv_gcm() {
  GetHypercallInterface()->Abort();
}

const char *core_analytics_ca_bool_cpp_stringified = "TODO";

void core_analytics_send_event_lazy() {
  // TODO(nedwill): implement coreanalytics
}

void *core_analytics_family_match() {
  return NULL;
}

void create_buffers() {
  GetHypercallInterface()->Abort();
}
void create_buffers_triage() {}
void delete_buffers() {
  GetHypercallInterface()->Abort();
}
void disable_wrap() {
  GetHypercallInterface()->Abort();
}
void host_security_create_task_token() {
  GetHypercallInterface()->Abort();
}
void host_security_set_task_token() {
  GetHypercallInterface()->Abort();
}
void hvg_hcall_set_coredump_data() {
  GetHypercallInterface()->Abort();
}
void is_iokit_subsystem() {
  GetHypercallInterface()->Abort();
}
void kdbg_cpu_count() {
  GetHypercallInterface()->Abort();
}
void kdbg_debug() {
  GetHypercallInterface()->Abort();
}
void kdebug_lck_grp() {
  GetHypercallInterface()->Abort();
}
void kdebug_lck_init() {}
uint64_t kdebug_timestamp() {
  GetHypercallInterface()->Abort();
}
vm_map_t kernel_data_map_get() {
  GetHypercallInterface()->Abort();
}
void kernel_debug_read() {
  GetHypercallInterface()->Abort();
}
void kernel_debug_write() {
  GetHypercallInterface()->Abort();
}
void kernel_triage_extract(uint64_t thread_id, void *buf, uint32_t bufsz) {
  GetHypercallInterface()->Abort();
}
void kernel_triage_record(uint64_t thread_id, uint64_t debugid,
                          uintptr_t arg1) {}
lck_spinlock_to_info_t lck_spinlock_timeout_hit(void *lck, uintptr_t owner) {
  GetHypercallInterface()->Abort();
}
void log_queue_cnt_dropped_nomem() {
  GetHypercallInterface()->Abort();
}
void log_queue_cnt_dropped_off() {
  GetHypercallInterface()->Abort();
}
void log_queue_cnt_mem_allocated() {
  GetHypercallInterface()->Abort();
}
void log_queue_cnt_mem_failed() {
  GetHypercallInterface()->Abort();
}
void log_queue_cnt_mem_released() {
  GetHypercallInterface()->Abort();
}
void log_queue_cnt_queued() {
  GetHypercallInterface()->Abort();
}
void log_queue_cnt_received() {
  GetHypercallInterface()->Abort();
}
void log_queue_cnt_rejected_fh() {
  GetHypercallInterface()->Abort();
}
void log_queue_cnt_sent() {
  GetHypercallInterface()->Abort();
}
void mach_exception_raise_identity_protected() {
  GetHypercallInterface()->Abort();
}
void mach_test_sync_upcall() {}
void ml_cpu_get_info_type(ml_cpu_info_t *ml_cpu_info,
                          cluster_type_t cluster_type) {}
int ml_early_cpu_max_number() {
  return 1;
}
unsigned int ml_get_cpu_number_type(cluster_type_t cluster_type __unused,
                                    bool logical, bool available) {
  GetHypercallInterface()->Abort();
}
unsigned int ml_get_cpu_types(void) {
  return GetHypercallInterface()->GetFuzzedUint32InRange(0, 0xFFFFFFFFU);
}
void pmap_cs_fork_prepare() {}
bool pmap_in_ppl() {
  return false;
}
void pmap_ledger_verify_size() {
  GetHypercallInterface()->Abort();
}
void ptrauth_utils_auth_blob_generic() {
  GetHypercallInterface()->Abort();
}
void ptrauth_utils_sign_blob_generic() {
  GetHypercallInterface()->Abort();
}
void read_lbr() {
  GetHypercallInterface()->Abort();
}
uint64_t report_phy_read_delay = 0;
uint32_t report_phy_read_osbt = 0;
uint64_t report_phy_write_delay = 0;
uint32_t report_phy_write_osbt = 0;
void send_vfs_resolve_dir() {
  GetHypercallInterface()->Abort();
}
void send_vfs_resolve_file() {
  GetHypercallInterface()->Abort();
}
void serial_putc_options() {
  GetHypercallInterface()->Abort();
}
uint64_t trace_phy_read_delay = 0;
uint64_t trace_phy_write_delay = 0;
void uuid_unparse_lower(const uuid_t uu, uuid_string_t out) {
  GetHypercallInterface()->Abort();
}

__abortlike void zone_invalid_panic(zone_t zone) {
  panic("zone %p isn't in the zone_array", zone);
}

void zone_ro_elem_size() {
  GetHypercallInterface()->Abort();
}
void zone_userspace_reboot_checks(void) {
  GetHypercallInterface()->Abort();
}

void workq_schedule_delayed_thread_creation() {
  GetHypercallInterface()->Abort();
}
void bsdthread_get_max_parallelism() {
  GetHypercallInterface()->Abort();
}
void _wq_thactive_move() {
  GetHypercallInterface()->Abort();
}
void _wq_thactive_refresh_best_constrained_req_qos() {
  GetHypercallInterface()->Abort();
}
void workq_lock_try() {
  GetHypercallInterface()->Abort();
}
void _wq_thactive() {
  GetHypercallInterface()->Abort();
}
void workq_lock_is_acquired_kdp() {
  GetHypercallInterface()->Abort();
}
void _wq_thactive_inc() {
  GetHypercallInterface()->Abort();
}
void workq_unpark_continue() {
  GetHypercallInterface()->Abort();
}
void _wq_thactive_dec() {
  GetHypercallInterface()->Abort();
}
void __atomic_fetch_add_16() {
  GetHypercallInterface()->Abort();
}
void __atomic_fetch_sub_16() {
  GetHypercallInterface()->Abort();
}
bool kdp_lck_ticket_is_acquired(lck_ticket_t *lck) {
  GetHypercallInterface()->Abort();
}

kern_return_t machine_thread_siguctx_pointer_convert_to_user(
    __unused thread_t thread, __unused user_addr_t *uctxp) {
  // No conversion to userspace representation on this platform
  return KERN_SUCCESS;
}

vm_offset_t panic_fault_address = 0;

int hv_support_available = 0;

int hv_disable = 0;

void kdebug_storage_lock() {
  GetHypercallInterface()->Abort();
}
void kdebug_storage_unlock() {
  GetHypercallInterface()->Abort();
}
void mac_audit_data_zone() {
  GetHypercallInterface()->Abort();
}
void IOSKArenaCreate() {
  GetHypercallInterface()->Abort();
}
void IOSKArenaDestroy() {
  GetHypercallInterface()->Abort();
}
void IOSKMapperCreate() {
  GetHypercallInterface()->Abort();
}
void IOSKMapperGetAddress() {
  GetHypercallInterface()->Abort();
}
void IOSKMapperDestroy() {
  GetHypercallInterface()->Abort();
}
void IOSKMapperRedirect() {
  GetHypercallInterface()->Abort();
}
int flsll(unsigned long long mask) {
  if (mask == 0) {
    return 0;
  }

  return (sizeof(mask) << 3) - __builtin_clzll(mask);
}
void *IOSKRegionCreate() {
  return (void *)1;
}
void IOSKRegionDestroy() {
  GetHypercallInterface()->Abort();
}

void *IOSKMemoryBufferCreate() {
  return (void *)1;
}

int IOSKMemoryReclaim() {
  return 0;
}

int IOSKMemoryWire() {
  return 0;
}

int IOSKRegionSetBuffer() {
  return 0;
}

bool IOSKBufferIsWired() {
  return true;
}

void IOSKRegionClearBufferDebug() {
  GetHypercallInterface()->Abort();
}
void IOSKMemoryUnwire() {
  GetHypercallInterface()->Abort();
}
void IOSKMemoryDiscard() {
  GetHypercallInterface()->Abort();
}
void IOSKMemoryDestroy() {
  GetHypercallInterface()->Abort();
}
void os_memcmp_mask_64B() {
  GetHypercallInterface()->Abort();
}
void os_memcmp_mask_80B() {
  GetHypercallInterface()->Abort();
}
void os_memcmp_mask_48B() {
  GetHypercallInterface()->Abort();
}
void os_cpu_copy_in_cksum() {
  GetHypercallInterface()->Abort();
}
void OSKernelStackRemaining() {
  GetHypercallInterface()->Abort();
}
void hv_support_init() {}

uint32_t hw_wait_while_equals32(uint32_t *address, uint32_t current) {
  GetHypercallInterface()->Abort();
}
