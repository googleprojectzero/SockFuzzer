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
// These are placeholders that will be replaced with real or fake
// implementations when the fuzzed code attempts to use them.

#include <i386/types.h>
#include <kern/assert.h>
#include <kern/clock.h>
#include <kern/debug.h>
#include <libkern/amfi/amfi.h>
#include <mach/i386/kern_return.h>
#include <mach/i386/vm_types.h>
#include <mach/kern_return.h>
#include <mach/mach_time.h>
#include <mach/machine.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/_types/_uuid_t.h>
#include <sys/errno.h>
#include <sys/msgbuf.h>
#include <sys/systm.h>
#include <sys/types.h>
#include <uuid/uuid.h>

#include "fuzz/host/hypercall/hypercall.h"
#include "libkern/crypto/rand.h"
#include "netinet/dhcp_options.h"

int printf(const char *format, ...);

struct os_log_s {
  int a;
};

struct os_log_s _os_log_default;

// uint32_t crc32(uint32_t crc, const void *buf, size_t size) {
//   assert(false);
//   return 0;
// }

uint64_t mem_actual = 0x41414141;

// Fake registry entry structure
typedef struct {
  char path[256];
  struct dhcp dhcp_response;
  struct in_addr netmask;
  struct in_addr router;
} fake_registry_entry_t;

// Global variable to hold the fake registry entry
static fake_registry_entry_t fake_registry_entry;

unsigned long simple_inet_addr(int a, int b, int c, int d) {
  struct in_addr addr = {0};
  addr.s_addr = htonl((a << 24) | (b << 16) | (c << 8) | d);
  return addr.s_addr;
}

void *IOBSDRegistryEntryForDeviceTree(char *path) {
  if (strcmp(path, "/chosen") == 0) {
    // Populate the fake registry entry with dummy data
    fake_registry_entry.dhcp_response.dp_yiaddr.s_addr =
        simple_inet_addr(192, 168, 1, 100);
    fake_registry_entry.netmask.s_addr = simple_inet_addr(255, 255, 255, 0);
    fake_registry_entry.router.s_addr = simple_inet_addr(192, 168, 1, 1);

    // Populate DHCP options
    memset(fake_registry_entry.dhcp_response.dp_options, 0,
           sizeof(fake_registry_entry.dhcp_response.dp_options));
    uint8_t *options = fake_registry_entry.dhcp_response.dp_options;

    // Magic cookie
    options[0] = 99;
    options[1] = 130;
    options[2] = 83;
    options[3] = 99;

    // Subnet mask option
    options[4] = dhcptag_subnet_mask_e;
    options[5] = 4;
    memcpy(&options[6], &fake_registry_entry.netmask.s_addr, 4);

    // Router option
    options[10] = dhcptag_router_e;
    options[11] = 4;
    memcpy(&options[12], &fake_registry_entry.router.s_addr, 4);

    // End option
    options[16] = dhcptag_end_e;

    strncpy(fake_registry_entry.path, path,
            sizeof(fake_registry_entry.path) - 1);
    return &fake_registry_entry;
  }
  return NULL;
}

void IOBSDRegistryEntryRelease(void *entry) {
  // No action needed for the fake implementation
  return;
}

const void *IOBSDRegistryEntryGetData(void *entry, char *property_name,
                                      int *packet_length) {
  fake_registry_entry_t *regEntry = (fake_registry_entry_t *)entry;

  if (strcmp(property_name, "DHCP_RESPONSE") == 0 ||
      strcmp(property_name, "BOOTP_RESPONSE") == 0) {
    *packet_length = sizeof(struct dhcp);
    return &regEntry->dhcp_response;
  }
  return NULL;
}

void IOBSDGetPlatformUUID() {
  GetHypercallInterface()->Abort();
}
void IOBSDMountChange() {}

void IOBaseSystemARVRootHashAvailable() {
  GetHypercallInterface()->Abort();
}
void IOCatalogueMatchingDriversPresent() {
  GetHypercallInterface()->Abort();
}

bool IOGetApfsPrebootUUID() {
  return false;
}

bool IOGetAssociatedApfsVolgroupUUID(char *uuid) {
  return false;
}

bool IOGetBootUUID() {
  return false;
}

bool IOGetVMMPresent() {
  return GetHypercallInterface()->GetFuzzedBool();
}

kern_return_t IOKitBSDInit() {
  return KERN_SUCCESS;
}
void IOKitInitializeTime() {}
void IOMapperInsertPage() {
  GetHypercallInterface()->Abort();
}
void IOPMCopySleepWakeUUIDKey() {
  GetHypercallInterface()->Abort();
}

void IORegistrySetOSBuildVersion(char *build_version) {}

void IOSecureBSDRoot() {
  GetHypercallInterface()->Abort();
}
void IOServicePublishResource() {}

boolean_t IOServiceWaitForMatchingResource(const char *property,
                                           uint64_t timeout) {
  return true;
}

void IOSetRecoveryBoot() {
  GetHypercallInterface()->Abort();
}
void IOSystemShutdownNotification() {}
void IOVnodeHasEntitlement() {
  GetHypercallInterface()->Abort();
}
void OSKextGetUUIDForName() {
  GetHypercallInterface()->Abort();
}
void OSKextResetAfterUserspaceReboot() {
  GetHypercallInterface()->Abort();
}
void PE_imgsrc_mount_supported() {
  GetHypercallInterface()->Abort();
}
void SHA1Final() {
  GetHypercallInterface()->Abort();
}
void SHA1Init() {
  GetHypercallInterface()->Abort();
}
void SHA1Update() {
  GetHypercallInterface()->Abort();
}
void SecureDTGetProperty() {
  GetHypercallInterface()->Abort();
}

int SecureDTLookupEntry() {
  return -1;
}

void _os_log_internal_driverKit() {
  GetHypercallInterface()->Abort();
}
void act_thread_catt() {
  GetHypercallInterface()->Abort();
}
void *act_thread_csave() {
  return NULL;
}
void aes_decrypt_aad_gcm() {
  GetHypercallInterface()->Abort();
}
void aes_decrypt_cbc() {
  GetHypercallInterface()->Abort();
}
void aes_decrypt_finalize_gcm() {
  GetHypercallInterface()->Abort();
}
void aes_decrypt_gcm() {
  GetHypercallInterface()->Abort();
}
void aes_decrypt_get_ctx_size_gcm() {
  GetHypercallInterface()->Abort();
}
void aes_decrypt_key() {
  GetHypercallInterface()->Abort();
}
void aes_decrypt_key_gcm() {
  GetHypercallInterface()->Abort();
}
void aes_decrypt_set_iv_gcm() {
  GetHypercallInterface()->Abort();
}
void aes_encrypt_aad_gcm() {
  GetHypercallInterface()->Abort();
}
void aes_encrypt_cbc() {
  GetHypercallInterface()->Abort();
}
void aes_encrypt_finalize_gcm() {
  GetHypercallInterface()->Abort();
}
void aes_encrypt_gcm() {
  GetHypercallInterface()->Abort();
}
void aes_encrypt_get_ctx_size_gcm() {
  GetHypercallInterface()->Abort();
}
void aes_encrypt_inc_iv_gcm() {
  GetHypercallInterface()->Abort();
}
void aes_encrypt_key() {
  GetHypercallInterface()->Abort();
}
void aes_encrypt_key128() {
  GetHypercallInterface()->Abort();
}
void aes_encrypt_key_with_iv_gcm() {
  GetHypercallInterface()->Abort();
}
void aes_encrypt_reset_gcm() {
  GetHypercallInterface()->Abort();
}

struct msgbuf *aslbufp;

void audit_analytics() {
  GetHypercallInterface()->Abort();
}
void audit_triggers() {
  GetHypercallInterface()->Abort();
}
void bootsessionuuid_string() {
  GetHypercallInterface()->Abort();
}
int bsd_do_post() {
  return 0;
}
int bsd_list_tests() {
  return 0;
}
void bzero_phys() {
  GetHypercallInterface()->Abort();
}
void bzero_phys_nc() {
  GetHypercallInterface()->Abort();
}
void check_task_access_with_flavor() {
  GetHypercallInterface()->Abort();
}
void commpage_update_dyld_flags() {
  GetHypercallInterface()->Abort();
}
void commpage_update_kdebug_state() {
  GetHypercallInterface()->Abort();
}
int copyin_atomic32_wait_if_equals(const user_addr_t user_addr, uint32_t u32) {
  GetHypercallInterface()->Abort();
}
void copypv() {
  GetHypercallInterface()->Abort();
}
void copysize_limit_panic() {
  GetHypercallInterface()->Abort();
}

void coredumpok() {
  GetHypercallInterface()->Abort();
}
cpu_type_t cpu_type() {
  return CPU_TYPE_I386;
}

uint32_t cpuid_cpufamily(void) {
  return CPU_TYPE_I386;
}

void cpuid_extfeatures() {
  GetHypercallInterface()->Abort();
}

void *cpuid_info() {
  return NULL;
}

// Dummy implementation of di_root_image
int di_root_image(const char *root_path, char *rootdevice, int max_length,
                  dev_t *dev) {
  // Don't update rootdev as we already initialized it properly in our fake `IOFindBSDRoot`
  *dev = rootdev;

  strncpy(rootdevice, "dummy_root_device", max_length - 1);
  rootdevice[max_length - 1] = '\0';

  return 0;
}

void di_root_image_ext() {
  GetHypercallInterface()->Abort();
}
void di_root_ramfile_buf() {
  GetHypercallInterface()->Abort();
}
void early_boot() {
  GetHypercallInterface()->Abort();
}
void find_code_signature() {
  GetHypercallInterface()->Abort();
}

// From loose_ends.c
int fls(unsigned int mask) {
  if (mask == 0) {
    return 0;
  }

  return (sizeof(mask) << 3) - __builtin_clz(mask);
}

void gPEClockFrequencyInfo() {
  GetHypercallInterface()->Abort();
}
void get_largest_zone_info() {}
void get_zone_map_size() {}
void halt_log_enter() {}
void hashaddr() {
  GetHypercallInterface()->Abort();
}
void hashbacktrace() {
  GetHypercallInterface()->Abort();
}
void high_MutexSpin() {
  GetHypercallInterface()->Abort();
}

// Dummy implementation of kdp_get_interface
void *kdp_get_interface() {
  // Return a non-null pointer to simulate a valid interface
  static int dummy_interface;
  return &dummy_interface;
}

// Dummy implementation of kdp_set_ip_and_mac_addresses
void kdp_set_ip_and_mac_addresses(struct in_addr *ip_addr, void *mac_addr) {
  // No action needed for the fake implementation
}

// Dummy implementation of kdp_set_gateway_mac
void kdp_set_gateway_mac(void *mac_addr) {
  // No action needed for the fake implementation
}

void kpc_arch_init() {}

uint32_t kpc_get_classes() {
  return 0;
}

int kpc_get_pmu_version() {
  return GetHypercallInterface()->GetFuzzedUint32();
}

void kpc_set_sw_inc() {}
void kperf_disable_sampling() {
  GetHypercallInterface()->Abort();
}
void kperf_reset() {
  GetHypercallInterface()->Abort();
}
void lockd_request() {
  GetHypercallInterface()->Abort();
}
void lockd_shutdown() {
  GetHypercallInterface()->Abort();
}

int log_dmesg(user_addr_t buffer, uint32_t buffersize, int32_t *retval) {
  return 0;
}

void log_putc_locked(struct msgbuf *a, char b) {
  GetHypercallInterface()->Abort();
}

void log_setsize() {
  GetHypercallInterface()->Abort();
}
void logwakeup() {
  GetHypercallInterface()->Abort();
}
void low_MutexSpin() {
  GetHypercallInterface()->Abort();
}
uint64_t mach_bridge_remote_time() {
  return 0;
}
void mach_bridge_timer_enable() {
  GetHypercallInterface()->Abort();
}
void mach_gss_accept_sec_context() {
  GetHypercallInterface()->Abort();
}
void mach_gss_init_sec_context_v3() {
  GetHypercallInterface()->Abort();
}
void mach_gss_log_error() {
  GetHypercallInterface()->Abort();
}
void mach_gss_lookup() {
  GetHypercallInterface()->Abort();
}

kern_return_t machine_thread_function_pointers_convert_from_user(
    thread_t thread, user_addr_t *fptrs, uint32_t count) {
  return KERN_SUCCESS;
}

void machine_thread_on_core() {
  GetHypercallInterface()->Abort();
}
void max_ncpus() {
  GetHypercallInterface()->Abort();
}
void ml_cpu_cache_sharing() {
  GetHypercallInterface()->Abort();
}
void ml_cpu_cache_size() {
  GetHypercallInterface()->Abort();
}
void rsa_make_pub() {
  GetHypercallInterface()->Abort();
}
void rsa_verify_pkcs1v15() {
  GetHypercallInterface()->Abort();
}
// void __muloti4() {
//   GetHypercallInterface()->Abort();
// }
void _get_cpu_capabilities() {}
void nx_enabled() {
  GetHypercallInterface()->Abort();
}
void oslog_setsize() {
  GetHypercallInterface()->Abort();
}

void osobject_release(void *object) {
  GetHypercallInterface()->Abort();
}

void osobject_retain(void *object) {
  GetHypercallInterface()->Abort();
}

char osversion[256] = "SockFuzzer OS";

void panic_dump_mem() {
  GetHypercallInterface()->Abort();
}
void panic_hook() {}
void panic_phys_range_before() {
  GetHypercallInterface()->Abort();
}
void panic_unhook() {}
void registerSleepWakeInterest() {
  GetHypercallInterface()->Abort();
}
void send_nspace_resolve_cancel() {
  GetHypercallInterface()->Abort();
}

void send_nspace_resolve_path() {
  GetHypercallInterface()->Abort();
}

void startup_serial_num_procs() {
  GetHypercallInterface()->Abort();
}
void test_oslog_handleOSLogCtl() {
  GetHypercallInterface()->Abort();
}
user_addr_t thread_adjuserstack(thread_t thread, int adjust) {
  return 0;
}
kern_return_t thread_entrypoint(__unused thread_t thread, int flavor,
                                thread_state_t tstate,
                                __unused unsigned int count,
                                mach_vm_offset_t *entry_point) {
  *entry_point = CAST_USER_ADDR_T(VM_MIN_ADDRESS);
  return KERN_SUCCESS;
}
void thread_set_child() {}
void thread_set_parent() {
  GetHypercallInterface()->Abort();
}

void thread_setentrypoint(thread_t thread, mach_vm_offset_t entry) {
  GetHypercallInterface()->Abort();
}

kern_return_t thread_setsinglestep(thread_t thread, int on) {
  GetHypercallInterface()->Abort();
}

void thread_setuserstack(thread_t thread, mach_vm_offset_t user_stack) {
  GetHypercallInterface()->Abort();
}
kern_return_t thread_userstack(__unused thread_t thread, int flavor,
                               thread_state_t tstate, unsigned int count,
                               mach_vm_offset_t *user_stack, int *customstack,
                               __unused boolean_t is64bit) {
  *user_stack = GetHypercallInterface()->GetFuzzedUint64();
  if (customstack) {
    *customstack = GetHypercallInterface()->GetFuzzedBool();
  }
  return KERN_SUCCESS;
}
kern_return_t thread_userstackdefault(mach_vm_offset_t *default_user_stack,
                                      boolean_t is64bit __unused) {
  *default_user_stack = GetHypercallInterface()->GetFuzzedUint64();
  return KERN_SUCCESS;
}
void tsc_at_boot() {
  GetHypercallInterface()->Abort();
}
void tsc_rebase_abs_time() {
  GetHypercallInterface()->Abort();
}
void uuid_generate(uuid_t out) {
  GetHypercallInterface()->Abort();
}
int uuid_parse(const uuid_string_t in, uuid_t uu) {
  GetHypercallInterface()->Abort();
}
void xnupost_export_testdata() {
  GetHypercallInterface()->Abort();
}
void xnupost_get_estimated_testdata_size() {
  GetHypercallInterface()->Abort();
}
void xnupost_reset_all_tests() {
  GetHypercallInterface()->Abort();
}
void zdestroy(zone_t zone) {
  GetHypercallInterface()->Abort();
}
void zone_gc_drain() {
  GetHypercallInterface()->Abort();
}

void OSReportWithBacktrace() {
  GetHypercallInterface()->Abort();
}
void _Block_object_assign() {
  GetHypercallInterface()->Abort();
}
void _NSConcreteGlobalBlock() {
  GetHypercallInterface()->Abort();
}
void compute_pmap_gc_throttle() {
  GetHypercallInterface()->Abort();
}
void compute_zone_working_set_size() {
  GetHypercallInterface()->Abort();
}
void driverkit_checkin_timed_out() {
  GetHypercallInterface()->Abort();
}
void iokit_user_client_trap() {}
void kperf_timer_expire() {
  GetHypercallInterface()->Abort();
}
void mp_slave_stack() {
  GetHypercallInterface()->Abort();
}
void osbuild_config() {
  GetHypercallInterface()->Abort();
}
void oslog_msgbuf_dropped_charcount() {
  GetHypercallInterface()->Abort();
}
void oslog_msgbuf_dropped_msgcount() {
  GetHypercallInterface()->Abort();
}
void oslog_msgbuf_msgcount() {
  GetHypercallInterface()->Abort();
}
void osrelease() {
  GetHypercallInterface()->Abort();
}
void ostype() {
  GetHypercallInterface()->Abort();
}
kern_return_t thread_set_wq_state32(thread_t thread, thread_state_t tstate) {
  GetHypercallInterface()->Abort();
}
kern_return_t thread_set_wq_state64(thread_t thread, thread_state_t tstate) {
  GetHypercallInterface()->Abort();
}
void gEnforceQuiesceSafety() {
  GetHypercallInterface()->Abort();
}
void iotrace_generators() {
  GetHypercallInterface()->Abort();
}
void iotrace_next() {
  GetHypercallInterface()->Abort();
}
void iotrace_ring() {
  GetHypercallInterface()->Abort();
}
void reportphyreadosbt() {
  GetHypercallInterface()->Abort();
}
void reportphywriteosbt() {
  GetHypercallInterface()->Abort();
}
void tracephyreaddelayabs() {
  GetHypercallInterface()->Abort();
}
void tracephywritedelayabs() {
  GetHypercallInterface()->Abort();
}

void lck_rw_set_promotion_locked() {
  GetHypercallInterface()->Abort();
}
bool kperf_is_sampling(void) {
  return false;
}
vm_offset_t other_percpu_base(int cpu) {
  return 0;
}
void sysctl_get_bound_cpuid() {
  GetHypercallInterface()->Abort();
}
void sysctl_task_get_no_smt() {
  GetHypercallInterface()->Abort();
}
void sysctl_task_set_no_smt() {
  GetHypercallInterface()->Abort();
}
void sysctl_thread_bind_cpuid() {
  GetHypercallInterface()->Abort();
}

void OSKextResetPgoCounters() {
  GetHypercallInterface()->Abort();
}
kern_return_t OSKextGrabPgoData() {
  return KERN_FAILURE;
}
void OSKextResetPgoCountersLock() {}
void OSKextResetPgoCountersUnlock() {}

void pid_hibernate() {}
int debug_syscall_reject() {
  return ENOTSUP;
}

void logclose() {
  GetHypercallInterface()->Abort();
}
void logread() {
  GetHypercallInterface()->Abort();
}
void logioctl() {
  GetHypercallInterface()->Abort();
}
void logselect() {
  GetHypercallInterface()->Abort();
}
void logopen() {
  GetHypercallInterface()->Abort();
}
void _kmem_alloc_pageable() {
  GetHypercallInterface()->Abort();
}

const img4_interface_t *img4if = NULL;

const amfi_t *amfi = NULL;

void _kmem_alloc() {
  GetHypercallInterface()->Abort();
}
void _vm_fault() {
  GetHypercallInterface()->Abort();
}
void bt_params_get_latest() {
  GetHypercallInterface()->Abort();
}
kern_return_t kdp_core_handle_new_encryption_key(
    IOCoreFileAccessCallback access_data, void *access_context,
    void *recipient_context) {
  GetHypercallInterface()->Abort();
}
kern_return_t IOProvideCoreFileAccess(IOCoreFileAccessRecipient recipient,
                                      void *recipient_context) {
  return KERN_SUCCESS;
}
void _vm_kernel_addrhash() {
  GetHypercallInterface()->Abort();
}
void io_compression_stats() {
  GetHypercallInterface()->Abort();
}

void _kmem_alloc_kobject() {
  GetHypercallInterface()->Abort();
}
void clock_timebase_info(mach_timebase_info_data_t *info) {
  info->denom = 1;
  info->numer = 1;
}
void vnode_iocs_record_and_free() {
  GetHypercallInterface()->Abort();
}
void clock_alarm_reply() {
  GetHypercallInterface()->Abort();
}
void machine_signal_idle_cancel() {
  GetHypercallInterface()->Abort();
}
void send_port_space_violation() {
  GetHypercallInterface()->Abort();
}
void send_file_descriptors_violation() {
  GetHypercallInterface()->Abort();
}

void iokit_client_died() {
  GetHypercallInterface()->Abort();
}
void iokit_port_for_object() {
  GetHypercallInterface()->Abort();
}
void pmap_map_block() {
  GetHypercallInterface()->Abort();
}
void pmap_memory_region_count() {
  GetHypercallInterface()->Abort();
}
void pmap_memory_regions() {
  GetHypercallInterface()->Abort();
}
int PE_init_socd_client() {
  return 0;
}
void PE_write_socd_client_buffer() {
  GetHypercallInterface()->Abort();
}
void ml_get_timebase_entropy() {
  GetHypercallInterface()->Abort();
}

void sdt_probetab() {
  GetHypercallInterface()->Abort();
}
void sdt_probetab_mask() {
  GetHypercallInterface()->Abort();
}
void dtrace_probe() {
  GetHypercallInterface()->Abort();
}
void dtrace_invop_callsite_pre() {
  GetHypercallInterface()->Abort();
}
void dtrace_invop_callsite_post() {
  GetHypercallInterface()->Abort();
}
void cpu_core() {
  GetHypercallInterface()->Abort();
}
void cpu_list() {
  GetHypercallInterface()->Abort();
}

uint64_t cpuid_features() {
  return 0;
}

char *cpuid_get_feature_names(uint64_t features, char *buf, unsigned buf_len) {
  memset(buf, 0, buf_len);
  return NULL;
}

void cpuid_get_leaf7_feature_names() {
  GetHypercallInterface()->Abort();
}
void cpuid_get_leaf7_extfeature_names() {
  GetHypercallInterface()->Abort();
}
void cpuid_get_extfeature_names() {
  GetHypercallInterface()->Abort();
}
void flex_ratio() {
  GetHypercallInterface()->Abort();
}
void flex_ratio_min() {
  GetHypercallInterface()->Abort();
}
void flex_ratio_max() {
  GetHypercallInterface()->Abort();
}
void ucode_interface() {
  GetHypercallInterface()->Abort();
}
void panic_restart_timeout() {
  GetHypercallInterface()->Abort();
}
void interrupt_populate_latency_stats() {
  GetHypercallInterface()->Abort();
}
void interrupt_reset_latency_stats() {
  GetHypercallInterface()->Abort();
}
void NMI_count() {
  GetHypercallInterface()->Abort();
}
void NMI_cpus() {
  GetHypercallInterface()->Abort();
}
bool cpuid_vmm_present() {
  return false;
}
void cpuid_vmm_get_applepv_features() {
  GetHypercallInterface()->Abort();
}
void hvg_hcall_trigger_dump() {
  GetHypercallInterface()->Abort();
}
void pv_hashed_kern_low_water_mark() {
  GetHypercallInterface()->Abort();
}
void tscFreq() {
  GetHypercallInterface()->Abort();
}
void deep_idle_rebase() {
  GetHypercallInterface()->Abort();
}
void pal_rtc_nanotime_info() {
  GetHypercallInterface()->Abort();
}
void is_x2apic() {
  GetHypercallInterface()->Abort();
}

uint32_t interrupt_timer_coalescing_enabled;

void idle_entry_timer_processing_hdeadline_threshold() {
  GetHypercallInterface()->Abort();
}

uint32_t ml_timer_eager_evaluations = 0;

void ml_timer_eager_evaluation_max() {
  GetHypercallInterface()->Abort();
}
void x86_isr_fp_simd_use() {
  GetHypercallInterface()->Abort();
}
void ml_cpu_power_disable(__unused int cpu_id) {}
void ml_cpu_power_enable(__unused int cpu_id) {}

int sys_debug_syscall_reject_config() {
  return 0;
}

void hvg_hcall_get_mabs_offset() {
  GetHypercallInterface()->Abort();
}

void hvg_hcall_get_bootsessionuuid() {
  GetHypercallInterface()->Abort();
}

void wake_nkdbufs() {
  GetHypercallInterface()->Abort();
}

void trace_wrap() {
  GetHypercallInterface()->Abort();
}

void IOCurrentTaskGetEntitlement() {
  GetHypercallInterface()->Abort();
}

void IOVnodeGetEntitlement() {
  GetHypercallInterface()->Abort();
}

void kern_register_userspace_coredump() {
  GetHypercallInterface()->Abort();
}

kern_return_t machine_task_process_signature() {
  return KERN_SUCCESS;
}

void ktriage_extract() {
  GetHypercallInterface()->Abort();
}

void IOUserServerRecordExitReason() {
  GetHypercallInterface()->Abort();
}

void ml_get_cluster_type_name() {
  GetHypercallInterface()->Abort();
}

void IOParseWorkloadConfig() {
  GetHypercallInterface()->Abort();
}

void reset_debug_syscall_rejection_mode() {
  GetHypercallInterface()->Abort();
}

void IOCurrentTaskHasStringEntitlement() {
  GetHypercallInterface()->Abort();
}

void enable_dklog_serial_output() {
  GetHypercallInterface()->Abort();
}

void record_system_event_no_varargs() {}

void os_memcmp_mask_16B() {
  GetHypercallInterface()->Abort();
}

void os_memcmp_mask_32B() {
  GetHypercallInterface()->Abort();
}

void ktriage_record() {
  // GetHypercallInterface()->Abort();
}

void send_vfs_resolve_dir_with_audit_token() {
  GetHypercallInterface()->Abort();
}

void send_vfs_resolve_file_with_audit_token() {
  GetHypercallInterface()->Abort();
}

void ml_io_map_unmappable() {
  GetHypercallInterface()->Abort();
}

void current_space_size() {
  GetHypercallInterface()->Abort();
}

void write_trace_on_panic() {
  GetHypercallInterface()->Abort();
}

void kdp_polled_corefile_mode() {
  GetHypercallInterface()->Abort();
}

void mach_exception_raise_backtrace() {
  GetHypercallInterface()->Abort();
}

wait_result_t cond_sleep_with_inheritor64_mask(cond_swi_var_t cond,
                                               cond_swi_var64_s expected_cond,
                                               uint64_t check_mask,
                                               wait_interrupt_t interruptible,
                                               uint64_t deadline) {
  GetHypercallInterface()->Abort();
}

kern_return_t cond_wakeup_all_with_inheritor(cond_swi_var_t cond,
                                             wait_result_t result) {
  GetHypercallInterface()->Abort();
}

void kdp_memcpy() {
  GetHypercallInterface()->Abort();
}

void kdp_strlcpy() {
  GetHypercallInterface()->Abort();
}

void kdp_generic_copyin() {
  GetHypercallInterface()->Abort();
}

void kdp_find_phys() {
  GetHypercallInterface()->Abort();
}

void kdp_generic_copyin_word() {
  GetHypercallInterface()->Abort();
}

void kdp_generic_copyin_string() {
  GetHypercallInterface()->Abort();
}

void kdp_vm_map_get_page_size() {
  GetHypercallInterface()->Abort();
}

void ml_cpu_down_update_counts() {
  GetHypercallInterface()->Abort();
}

void gEnforcePlatformActionSafety() {
  GetHypercallInterface()->Abort();
}

// TODO(nedwill)
void kern_unregister_userspace_coredump() {}

void machine_thread_process_signature() {}

bool crypto_init = false;

bool hvg_is_hcall_available() {
  return false;
}

void kdebug_startup() {}

bool os_log_disabled(void) {
  return false;
}

void dtrace_init() {}

void helper_init() {}

void lockstat_init() {}

void lockprof_init() {}

void sdt_init() {}

void systrace_init() {}

void fbt_init() {}

void profile_init() {}

void oslogopen() {
  GetHypercallInterface()->Abort();
}

void oslogclose() {
  GetHypercallInterface()->Abort();
}

void oslogioctl() {
  GetHypercallInterface()->Abort();
}

void oslogselect() {
  GetHypercallInterface()->Abort();
}

void pmap_query_page_info_retries() {
  GetHypercallInterface()->Abort();
}

void grab_pgo_data() {}

void do_pgo_reset_counters() {
  GetHypercallInterface()->Abort();
}

void hw_spin_should_keep_spinning() {
  GetHypercallInterface()->Abort();
}

EVENT_DEFINE(ZONE_EXHAUSTED);

void hw_lck_ticket_lock() {
  GetHypercallInterface()->Abort();
}

void zone_get_stats(zone_t zone, struct zone_basic_stats *stats) {
  GetHypercallInterface()->Abort();
}

void lck_ticket_unlock_nopreempt(lck_ticket_t *tlock) {
  GetHypercallInterface()->Abort();
}

void zone_drain(zone_t zone) {
  GetHypercallInterface()->Abort();
}

void hw_lck_ticket_unlock_nopreempt() {
  GetHypercallInterface()->Abort();
}

void hw_spin_compute_timeout() {
  GetHypercallInterface()->Abort();
}

void percpu_slot_lck_mcs() {
  GetHypercallInterface()->Abort();
}

void lck_ticket_lock_nopreempt(lck_ticket_t *tlock, lck_grp_t *grp) {
  GetHypercallInterface()->Abort();
}

void zcache_drain(zone_id_t zone_id) {
  GetHypercallInterface()->Abort();
}

void _zc_mag_size() {
  GetHypercallInterface()->Abort();
}

void hw_lck_ticket_lock_nopreempt() {
  GetHypercallInterface()->Abort();
}

void zone_enable_smr(zone_t zone, struct smr *smr, zone_smr_free_cb_t free_cb) {
  /*
   * Scalable Memory Reclamation (SMR) is not supported in the sockfuzzer environment.
   *
   * SMR allows for efficient memory reclamation in multi-threaded
   * environments by using sequence numbers to track freed elements and
   * allowing them to be reused without explicit synchronization.
   *
   * We need to revisit SMR support in the future, especially with regards
   * to security and safety. Some potential risks include:
   *
   * - Sequence number management: If sequence numbers are not managed
   *   correctly, it could lead to freed elements being reused prematurely,
   *   resulting in use-after-free vulnerabilities.
   * - ABA problem: The ABA problem could occur if a sequence number wraps
   *   around before a freed element is reused. This could lead to a thread
   *   mistakenly believing that an element is safe to reuse when it is not.
   * - Memory ordering: Ensuring correct memory ordering is crucial for
   *   SMR to function correctly. Without proper memory barriers, threads
   *   could observe stale sequence numbers or freed elements.
   */
}

#undef zfree_id_smr
void zfree_id_smr(zone_id_t zone_id, void *addr __unsafe_indexable) {
  GetHypercallInterface()->Abort();
}

#undef zfree_smr
void zfree_smr(zone_t zone, void *elem __unsafe_indexable) {
  GetHypercallInterface()->Abort();
}

boolean_t PEReadNVRAMBooleanProperty(const char *symbol, boolean_t *value) {
  *value = GetHypercallInterface()->GetFuzzedBool();
  return true;
}

void lck_rw_lock_count_dec() {
  GetHypercallInterface()->Abort();
}

void _bcopy() {
  GetHypercallInterface()->Abort();
}

char *__null_terminated strnstr(const char *__null_terminated s,
                                const char *__null_terminated find,
                                size_t slen) {
  GetHypercallInterface()->Abort();
}

void crypto_random_kmem_init(crypto_random_ctx_t ctx) {}

void lck_rw_lock_count_inc() {
  GetHypercallInterface()->Abort();
}

void PERemoveNVRAMProperty() {
  GetHypercallInterface()->Abort();
}

void PEWriteNVRAMBooleanProperty() {
  GetHypercallInterface()->Abort();
}

void pmap_user_va_bits() {
  GetHypercallInterface()->Abort();
}

void crypto_random_uniform(crypto_random_ctx_t ctx, uint64_t bound,
                           uint64_t *random) {
  if (bound == 0) {
    *random = 0;  // Handle the edge case where bound is 0.
    return;
  }

  // Calculate the number of bits needed to represent the bound.
  uint64_t bits = 64 - __builtin_clzll(bound - 1);

  if (bits <= 32) {
    *random = GetHypercallInterface()->GetFuzzedUint32InRange(0, bound - 1);
  } else {
    // Generate a 64-bit random value and mask off the upper bits
    // to ensure it falls within the desired range.
    *random = GetHypercallInterface()->GetFuzzedUint64() % bound;
  }
}

bool
pmap_get_tpro(
	__unused pmap_t pmap)
{
	return false;
}

void ml_addr_in_non_xnu_stack() {
  GetHypercallInterface()->Abort();
}

void pmap_set_tpro() {
  GetHypercallInterface()->Abort();
}

void ml_did_interrupt_userspace() {
  GetHypercallInterface()->Abort();
}

void iokit_kobject_retain() {
  GetHypercallInterface()->Abort();
}

void send_vfs_resolve_reparent_with_audit_token() {
  GetHypercallInterface()->Abort();
}

void ml_page_protection_type() {
  GetHypercallInterface()->Abort();
}

// The following two functions are for use in the kmem subsystem
// only. They are NOT guaranteed to provide cryptographic randomness
// and should not be used elsewhere.

// Return the size needed for a random generator to be used by
// kmem. (See the discussion below for the semantics of this
// generator.)
//
// The returned value may vary by platform, but it is guaranteed to be
// no larger than CRYPTO_RANDOM_MAX_CTX_SIZE.
size_t crypto_random_kmem_ctx_size(void) {
  return CRYPTO_RANDOM_MAX_CTX_SIZE;
}

void iokit_copy_object_for_consumed_kobject() {
  GetHypercallInterface()->Abort();
}

void lock_panic_timeout() {
  GetHypercallInterface()->Abort();
}

// TODO(nedwill): support ktriage?
void ktriage_register_subsystem_strings() {}

void xnu_strncmp() {
  GetHypercallInterface()->Abort();
}

void xnu_strncpy() {
  GetHypercallInterface()->Abort();
}

void xnu_strncasecmp() {
  GetHypercallInterface()->Abort();
}

vm_offset_t ml_static_unslide(vm_offset_t vaddr) {
  GetHypercallInterface()->Abort();
}

void telemetry_backtrace_add_kexts() {
  GetHypercallInterface()->Abort();
}
void ml_fp_save_area_prealloc() {
  GetHypercallInterface()->Abort();
}
void kpc_set_period() {
  GetHypercallInterface()->Abort();
}
void mt_microstackshot_ctr() {
  GetHypercallInterface()->Abort();
}

vm_offset_t vm_kernel_etext;

void IOTaskHasStringEntitlement() {
  GetHypercallInterface()->Abort();
}
void kperf_thread_ast_handler() {
  GetHypercallInterface()->Abort();
}
void kpc_get_actionid() {
  GetHypercallInterface()->Abort();
}
void kpc_get_counter_count() {
  GetHypercallInterface()->Abort();
}
void kpc_supported() {
  GetHypercallInterface()->Abort();
}
void mt_microstackshot_period() {
  GetHypercallInterface()->Abort();
}
void kpc_set_actionid() {
  GetHypercallInterface()->Abort();
}
void kpc_set_config_kernel() {
  GetHypercallInterface()->Abort();
}
void kpc_get_config_count() {
  GetHypercallInterface()->Abort();
}
void kpc_counterbuf_free() {
  GetHypercallInterface()->Abort();
}
void kpc_get_period() {
  GetHypercallInterface()->Abort();
}

void mt_dev_init() {}

void kpc_get_counterbuf_size() {
  GetHypercallInterface()->Abort();
}
void image4_dlxk_get() {
  GetHypercallInterface()->Abort();
}
void IOTaskGetEntitlement() {
  GetHypercallInterface()->Abort();
}
void usimple_lock_assert() {
  GetHypercallInterface()->Abort();
}
void kpc_counterbuf_alloc() {
  GetHypercallInterface()->Abort();
}
void _memmove() {
  GetHypercallInterface()->Abort();
}
