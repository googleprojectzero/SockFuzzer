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

// Unimplemented stub functions
// These are placeholders that will be replaced with real or fake implementations
// when the fuzzed code attempts to use them.

#include <kern/assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

int printf(const char* format, ...);

__attribute__((visibility("default"))) 
void Assert(const char* file, int line, const char* expression) {
  printf("%s: assert failed on line %d: %s\n", file, line, expression);
  __builtin_trap();
}

void IOBSDGetPlatformUUID() { assert(false); }

void IOMapperInsertPage() { assert(false); }

void IOPMCopySleepWakeUUIDKey() { assert(false); }

void IOTaskHasEntitlement() { assert(false); }

void OSMalloc_Tagalloc() { assert(false); }

void OSMalloc_Tagfree() { assert(false); }

void act_set_astbsd() { assert(false); }

void act_set_astkevent() { assert(false); }

void addupc_task() { assert(false); }

void assert_wait() { assert(false); }

void audit_arg_addr() { assert(false); }

void audit_arg_cmd() { assert(false); }

void audit_arg_ctlname() { assert(false); }

void audit_arg_fd() { assert(false); }

void audit_arg_file() { assert(false); }

void audit_arg_pid() { assert(false); }

void audit_arg_process() { assert(false); }

void audit_arg_signum() { assert(false); }

void audit_arg_value64() { assert(false); }

void audit_syscalls() { assert(false); }

void bsd_exception() { assert(false); }

void bsd_timeout() { assert(false); }

void bsdinit_task() { assert(false); }

void cc_rand_generate() { assert(false); }

void check_actforsig() { assert(false); }

void clear_thread_rwlock_boost() { assert(false); }

void clock_absolutetime_interval_to_deadline() { assert(false); }

void clock_continuoustime_interval_to_deadline() { assert(false); }

void clock_deadline_for_periodic_event() { assert(false); }

void clock_get_calendar_microtime() { assert(false); }

void clock_get_calendar_nanotime() { assert(false); }

void clock_get_uptime() { assert(false); }

void coalition_get_leader() { assert(false); }

void coalition_is_leader() { assert(false); }

void copyin_word() { assert(false); }

void copyinstr() { assert(false); }

void copypv() { assert(false); }

void copywithin() { assert(false); }

void coredump() { assert(false); }

void cs_identity_get() { assert(false); }

void current_task() { assert(false); }

void deflate() { assert(false); }

void deflateReset() { assert(false); }

void enodev() { assert(false); }

void enodev_strat() { assert(false); }

void exit_with_reason() { assert(false); }

void fs_filtops() { assert(false); }

void fsevent_filtops() { assert(false); }

void fuulong() { assert(false); }

void gPEClockFrequencyInfo() { assert(false); }

void* g_crypto_funcs = NULL;

void get_bsdtask_info() { assert(false); }

void get_bsdthreadtask_info() { assert(false); }

void get_signalact() { assert(false); }

void get_threadtask() { assert(false); }

void get_useraddr() { assert(false); }

void hashaddr() { assert(false); }

void hashbacktrace() { assert(false); }

void hostname() { assert(false); }

void hz() { assert(false); }

void inflate() { assert(false); }

void inflateReset() { assert(false); }

void initproc() { assert(false); }

void ipc_entry_name_mask() { assert(false); }

void is_kerneltask() { assert(false); }

void itimerdecr() { assert(false); }

void itimerfix() { assert(false); }

void kauth_authorize_generic() { assert(false); }

void kauth_cred_getgid() { assert(false); }

void kauth_cred_getruid() { assert(false); }

void kauth_cred_getsvuid() { assert(false); }

void kauth_getruid() { assert(false); }

void kcdata_estimate_required_buffer_size() { assert(false); }

void kcdata_get_memory_addr() { assert(false); }

void kcdata_memcpy() { assert(false); }

void kcdata_memory_static_init() { assert(false); }

void kdebug_enable() { assert(false); }

void kdp_get_interface() { assert(false); }

void kdp_is_in_zone() { assert(false); }

void kdp_set_gateway_mac() { assert(false); }

void kdp_set_ip_and_mac_addresses() { assert(false); }

void kernel_debug_filtered() { assert(false); }

void kernel_task() { assert(false); }

void launchd_exit_reason_get_string_desc() { assert(false); }

void lck_mtx_lock_spin_always() { assert(false); }

void lck_rw_destroy() { assert(false); }

void lck_rw_lock_exclusive_to_shared() { assert(false); }

void lck_rw_lock_shared_to_exclusive() { assert(false); }

void lck_rw_sleep() { assert(false); }

void lck_spin_assert() { assert(false); }

void lck_spin_destroy() { assert(false); }

void ledger_get_task_entry_info_multiple() { assert(false); }

void ledger_info() { assert(false); }

void ledger_template_info() { assert(false); }

void mac_error_select() { assert(false); }

void mac_policy_list() { assert(false); }

void mac_policy_list_conditional_busy() { assert(false); }

void mac_policy_list_unbusy() { assert(false); }

void mac_proc_check_ledger() { assert(false); }

void mac_proc_check_signal() { assert(false); }

void mac_socket_check_received() { assert(false); }

void mac_socket_check_stat() { assert(false); }

void mac_system_enforce() { assert(false); }

void mach_absolutetime_asleep() { assert(false); }

void machport_filtops() { assert(false); }

void max_mem() { assert(false); }

void mb_map() { assert(false); }

void memorystatus_filtops() { assert(false); }

void memorystatus_kevent_init() { assert(false); }

void msleep() { assert(false); }

void msleep0() { assert(false); }

void msleep1() { assert(false); }

void nanoseconds_to_absolutetime() { assert(false); }

void nanotime() { assert(false); }

void pg_rele() { assert(false); }

void pgfind() { assert(false); }

void pgrp_iterate() { assert(false); }

void port_name_to_thread() { assert(false); }

void proc_get_effective_task_policy() { assert(false); }

void proc_getcdhash() { assert(false); }

void proc_iterate() { assert(false); }

void proc_klist_lock() { assert(false); }

void proc_klist_unlock() { assert(false); }

void proc_knote() { assert(false); }

void proc_list_lock() { assert(false); }

void proc_list_unlock() { assert(false); }

void proc_lock() { assert(false); }

void proc_log_32bit_telemetry() { assert(false); }

void proc_name_address() { assert(false); }

void proc_parentdropref() { assert(false); }

void proc_parentholdref() { assert(false); }

void proc_pgrp() { assert(false); }

void proc_self() { assert(false); }

void proc_set_thread_policy() { assert(false); }

void proc_signal() { assert(false); }

void proc_spinlock() { assert(false); }

void proc_spinunlock() { assert(false); }

void proc_unlock() { assert(false); }

void proc_uuid_policy_kernel() { assert(false); }

void proc_uuid_policy_lookup() { assert(false); }

void pthread_functions() { assert(false); }

void pthread_priority_canonicalize() { assert(false); }

void ptmx_kqops() { assert(false); }

void ptsd_kqops() { assert(false); }

void pzfind() { assert(false); }

void sane_size() { assert(false); }

void securelevel() { assert(false); }

void semaphore_timedwait_signal_trap_internal() { assert(false); }

void semaphore_timedwait_trap_internal() { assert(false); }

void semaphore_wait_signal_trap_internal() { assert(false); }

void semaphore_wait_trap_internal() { assert(false); }

void sendsig() { assert(false); }

void set_thread_rwlock_boost() { assert(false); }

void spec_filtops() { assert(false); }

void subyte() { assert(false); }

void suulong() { assert(false); }

void sysctl__debug_children() { assert(false); }

void sysctl__kern_children() { assert(false); }

void sysctl__net_children() { assert(false); }

void sysctl__net_link_generic_system_children() { assert(false); }

void sysctl__sysctl_children() { assert(false); }

void task_consume_32bit_log_flag() { assert(false); }

void task_deallocate() { assert(false); }

void task_did_exec() { assert(false); }

void task_hold() { assert(false); }

void task_is_active() { assert(false); }

void task_is_exec_copy() { assert(false); }

void task_is_halting() { assert(false); }

void task_release() { assert(false); }

void task_resume_internal() { assert(false); }

void task_suspend_internal() { assert(false); }

void task_vtimer_clear() { assert(false); }

void task_vtimer_set() { assert(false); }

void task_vtimer_update() { assert(false); }

void task_wait() { assert(false); }

void telemetry_timer_event() { assert(false); }

void thread_add_ipc_override() { assert(false); }

void thread_add_sync_ipc_override() { assert(false); }

void thread_block() { assert(false); }

void thread_block_parameter() { assert(false); }

void thread_call_cancel() { assert(false); }

void thread_call_cancel_wait() { assert(false); }

void thread_call_enter() { assert(false); }

void thread_call_free() { assert(false); }

void thread_call_func_cancel() { assert(false); }

void thread_call_func_delayed() { assert(false); }

void thread_call_isactive() { assert(false); }

void thread_drop_ipc_override() { assert(false); }

void thread_drop_sync_ipc_override() { assert(false); }

void thread_ends_owning_workloop() { assert(false); }

void thread_get_ipc_override() { assert(false); }

void thread_get_tag() { assert(false); }

void thread_handoff() { assert(false); }

void thread_owned_workloops_count() { assert(false); }

void thread_qos_from_pthread_priority() { assert(false); }

void thread_reference() { assert(false); }

void thread_rettokern_addr() { assert(false); }

void thread_set_pending_block_hint() { assert(false); }

void thread_set_thread_name() { assert(false); }

void thread_set_voucher_name() { assert(false); }

void thread_should_abort() { assert(false); }

void thread_should_halt() { assert(false); }

void thread_starts_owning_workloop() { assert(false); }

void thread_tid() { assert(false); }

void thread_update_ipc_override() { assert(false); }

void thread_wakeup_thread() { assert(false); }

void tick() { assert(false); }

void timeout_with_leeway() { assert(false); }

void timespec_is_valid() { assert(false); }

void tsleep() { assert(false); }

void tsleep0() { assert(false); }

void tsleep1() { assert(false); }

void tstoabstime() { assert(false); }

void tty_filtops() { assert(false); }

void tty_pgrp() { assert(false); }

void tvtoabstime() { assert(false); }

void unix_syscall_return() { assert(false); }

void untimeout() { assert(false); }

void vaddlog() { assert(false); }

void vfs_context_create() { assert(false); }

void vfs_context_rele() { assert(false); }

void vm_kernel_addrperm() { assert(false); }

void vm_kernel_slid_base() { assert(false); }

void vm_kernel_slid_top() { assert(false); }

void vm_kernel_slide() { assert(false); }

void vn_stat() { assert(false); }

void vnode_filtops() { assert(false); }

void vnode_isfifo() { assert(false); }

void waitq_assert_wait64() { assert(false); }

void waitq_assert_wait64_leeway() { assert(false); }

void waitq_clear_prepost() { assert(false); }

void waitq_deinit() { assert(false); }

void waitq_get_prepost_id() { assert(false); }

void waitq_init() { assert(false); }

void waitq_is_valid() { assert(false); }

void waitq_link() { assert(false); }

void waitq_link_release() { assert(false); }

void waitq_link_reserve() { assert(false); }

void waitq_set_alloc() { assert(false); }

void waitq_set_clear_preposts() { assert(false); }

void waitq_set_deinit() { assert(false); }

void waitq_set_init() { assert(false); }

void waitq_set_is_valid() { assert(false); }

void waitq_set_unlink_all() { assert(false); }

void waitq_unlink() { assert(false); }

void waitq_unlink_by_prepost_id() { assert(false); }

void waitq_wakeup64_all() { assert(false); }

void waitq_wakeup64_one() { assert(false); }

void wqset_id() { assert(false); }

void wqset_waitq() { assert(false); }

void zalloc_canblock() { assert(false); }

void zfill() { assert(false); }

void kernel_pmap() { assert(false); }

void kmem_free() { assert(false); }

void cru2x() { assert(false); }

void mac_vnode_check_create() { assert(false); }

void mac_vnode_check_uipc_bind() { assert(false); }

void mac_vnode_check_uipc_connect() { assert(false); }

void namei() { assert(false); }

void nameidone() { assert(false); }

void vfs_context_ucred() { assert(false); }

void vn_create() { assert(false); }

void vnode_authorize() { assert(false); }

void vnode_put() { assert(false); }

void vnode_ref() { assert(false); }

void vnode_rele() { assert(false); }

void audit_arg_sockaddr() { assert(false); }

void audit_arg_socket() { assert(false); }

void audit_arg_value32() { assert(false); }

void vfs_context_cwd() { assert(false); }

void vnode_isreg() { assert(false); }

void vnode_size() { assert(false); }

void aes_decrypt_aad_gcm() { assert(false); }

void aes_decrypt_cbc() { assert(false); }

void aes_decrypt_finalize_gcm() { assert(false); }

void aes_decrypt_gcm() { assert(false); }

void aes_decrypt_get_ctx_size_gcm() { assert(false); }

void aes_decrypt_key() { assert(false); }

void aes_decrypt_key_gcm() { assert(false); }

void aes_decrypt_set_iv_gcm() { assert(false); }

void aes_encrypt_aad_gcm() { assert(false); }

void aes_encrypt_cbc() { assert(false); }

void aes_encrypt_finalize_gcm() { assert(false); }

void aes_encrypt_gcm() { assert(false); }

void aes_encrypt_get_ctx_size_gcm() { assert(false); }

void aes_encrypt_inc_iv_gcm() { assert(false); }

void aes_encrypt_key() { assert(false); }

void aes_encrypt_key_with_iv_gcm() { assert(false); }

void aes_encrypt_reset_gcm() { assert(false); }

void clock_get_system_microtime() { assert(false); }

void thread_call_enter1_delayed() { assert(false); }

void panic() { assert(false); }

struct os_log_s {
  int a;
};

struct os_log_s _os_log_default;

uint32_t net_flowhash_mh3_x86_32(const void* key, uint32_t len,
                                 const uint32_t seed) {
  assert(false);
  return 1;
}

void cc_clear() { assert(false); }

void cc_cmp_safe() { assert(false); }

void getsectdatafromheader() { assert(false); }

void _mh_execute_header() { assert(false); }

void net_flowhash() { assert(false); }

void os_cpu_in_cksum() { assert(false); }

void os_cpu_in_cksum_mbuf() { assert(false); }

void proc_name() { assert(false); }

void thread_terminate() { assert(false); }

void uuid_generate() { assert(false); }

void uuid_parse() { assert(false); }

void _pthread_priority_normalize() { assert(false); }

void workq_kern_threadreq_modify() { assert(false); }

void nat464_translate_proto() { assert(false); }

void turnstile_cleanup() { assert(false); }

void thread_wakeup_prim() { assert(false); }

void waitq_wakeup64_thread() { assert(false); }

void turnstile_prepare() { assert(false); }

void assert_wait_deadline() { assert(false); }

void nat464_synthesize_ipv4() { assert(false); }

void clat_debug() { assert(false); }

void workq_kern_threadreq_redrive() { assert(false); }

void zdestroy() { assert(false); }

void turnstile_update_inheritor() { assert(false); }

void thread_handoff_parameter() { assert(false); }

void in6_clat46_eventhdlr_callback() { assert(false); }

void turnstile_update_inheritor_complete() { assert(false); }

void nat464_insert_frag46() { assert(false); }

void nat464_synthesize_ipv6() { assert(false); }

void turnstile_complete() { assert(false); }

void nat464_translate_64() { assert(false); }

void waitq_set_should_lazy_init_link() { assert(false); }

void workq_is_exiting() { assert(false); }

void sysctl_helper_waitq_set_nelem() { assert(false); }

void turnstile_alloc() { assert(false); }

void workq_kern_threadreq_update_inheritor() { assert(false); }

void thread_handoff_deallocate() { assert(false); }

void workq_kern_threadreq_unlock() { assert(false); }

void telemetry_pmi_setup() { assert(false); }

void nat464_translate_46() { assert(false); }

void waitq_set_lazy_init_link() { assert(false); }

void workq_thread_set_max_qos() { assert(false); }

void workq_kern_threadreq_lock() { assert(false); }

void nat464_cksum_fixup() { assert(false); }

void turnstile_deallocate() { assert(false); }

void in6_clat46_event_enqueue_nwk_wq_entry() { assert(false); }

void workq_kern_threadreq_initiate() { assert(false); }

void turnstile_reference() { assert(false); }

void _pthread_priority_combine() { assert(false); }

void cchmac_final() { assert(false); }

void thread_update_kevent_override() { assert(false); }

void thread_add_kevent_override() { assert(false); }

void _disable_preemption() { assert(false); }

void lck_spin_sleep_with_inheritor() { assert(false); }

void ccsha256_di() { assert(false); }

void copysize_limit_panic() { assert(false); }

void sysctl_load_devicetree_entries() { assert(false); }

void mpsc_test_pingpong() { assert(false); }

void sysctl_task_get_no_smt() { assert(false); }

void hostname_lock() { assert(false); }

void cchmac_update() { assert(false); }

void _os_log_internal_driverKit() { assert(false); }

void machine_tecs() { assert(false); }

void machine_csv() { assert(false); }

void act_clear_astkevent() { assert(false); }

void cchmac_init() { assert(false); }

void thread_drop_servicer_override() { assert(false); }

void thread_update_servicer_override() { assert(false); }

void wakeup_one_with_inheritor() { assert(false); }

void sysctl__machdep_children() { assert(false); }

void thread_unfreeze_base_pri() { assert(false); }

void turnstile_deallocate_safe() { assert(false); }

void task_exc_guard_default() { assert(false); }

void sysctl_task_set_no_smt() { assert(false); }

void current_uthread() { assert(false); }

void filt_wldetach_sync_ipc() { assert(false); }

void _enable_preemption() { assert(false); }

void restricted_port_bitmap() { assert(false); }

void cfil_crypto_sign_data() { assert(false); }

void thread_set_no_smt() { assert(false); }

void net_mpklog_enabled() { assert(false); }

void cfil_crypto_init_client() { assert(false); }

void task_info() { assert(false); }

void thread_get_no_smt() { assert(false); }

void task_get_coalition() { assert(false); }

void atm_get_diagnostic_config() { assert(false); }

void cfil_crypto_cleanup_state() { assert(false); }

void copyin_atomic64() { assert(false); }

void thread_drop_kevent_override() { assert(false); }

void filt_wlattach_sync_ipc() { assert(false); }

void thread_deallocate_safe() { assert(false); }

void vm_kernel_addrhash() { assert(false); }

void _vm_kernel_addrhash_XNU_INTERNAL() { assert(false); }

void thread_add_servicer_override() { assert(false); }

void net_mpklog_type() { assert(false); }

void mach_bridge_remote_time() { assert(false); }

void vn_getpath_ext() { assert(false); }

void wakeup_all_with_inheritor() { assert(false); }

void registerSleepWakeInterest() { assert(false); }

void absolutetime_to_microtime() { assert(false); }

void thread_abort() {
  assert(false);
}

void strnstr() {
  assert(false);
}

void thread_abort_safely() {
  assert(false);
}

uint32_t crc32(uint32_t crc, const void *buf, size_t size) {
  assert(false);
  return 0;
}

void cs_get_cdhash() {
  assert(false);
}

void cs_hash_type() {
  assert(false);
}

void cs_valid() {
  assert(false);
}

void kernel_startup_tunable_init() {
  assert(false);
}

void mac_file_notify_close() {
  assert(false);
}

void mach_bridge_timer_enable() {
  assert(false);
}

void machine_thread_function_pointers_convert_from_user() {
  assert(false);
}

uint64_t mem_actual = 0x41414141;

void proc_min_sdk() {
  assert(false);
}

void proc_platform() {
  assert(false);
}

void proc_sdk() {
  assert(false);
}

const char *sysctl_debug_get_preoslog(size_t *size) {
  assert(false);
  return NULL;
}

void task_get_filter_msg_flag() {
  assert(false);
}

void task_set_filter_msg_flag() {
  assert(false);
}

void thread_zone() {
  assert(false);
}

void zalloc_permanent() {
  assert(false);
}

void zone_require() {
  assert(false);
}
