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

// Trivial implementations belong here. More substantial faked
// subsystems should live in their own file.

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <kern/assert.h>
#include <libkern/libkern.h>

#include "bsd/net/nwk_wq.h"
#include "bsd/sys/_types/_timeval.h"
#include "bsd/sys/kernel_types.h"
#include "bsd/sys/malloc.h"
#include "bsd/sys/resource.h"
#include "bsd/uuid/uuid.h"

extern void get_fuzzed_bytes(void* addr, size_t bytes);
extern bool get_fuzzed_bool(void);

int snprintf(char*, size_t, const char*, ...) __printflike(3, 4);

int maxfilesperproc = 10;

bool PE_parse_boot_argn(const char* arg_string, void* arg_ptr, int max_arg) {
  if (!strcmp(arg_string, "ifa_debug")) {
    *(int*)arg_ptr = 0;
    return true;
  }

  if (!strcmp(arg_string, "inaddr_nhash")) {
    *(uint32_t*)arg_ptr = 0;
    return true;
  }

  if (!strcmp(arg_string, "mcache_flags")) {
    *(uint32_t*)arg_ptr = 0;
    return true;
  }

  if (!strcmp(arg_string, "mbuf_debug")) {
    *(uint32_t*)arg_ptr = 0;
    return true;
  }

  if (!strcmp(arg_string, "mleak_sample_factor")) {
    *(uint32_t*)arg_ptr = 0;
    return true;
  }

  // Just return 0 by default.
  memset(arg_ptr, 0, max_arg);

  // assert(false);
  return false;
}

void* os_log_create() { return (void*)1; }

void pflog_packet() {}

// TODO(nedwill): return a real vfs context
void* vfs_context_current() { return NULL; }

int csproc_get_platform_binary(void* p) { return 0; }

void uuid_clear(uuid_t uu) { memset(uu, 0, sizeof(uuid_t)); }

int uuid_is_null(const uuid_t uu) {
  return !memcmp(uu, UUID_NULL, sizeof(uuid_t));
}

int uuid_compare(const uuid_t uu1, const uuid_t uu2) {
  return memcmp(uu1, uu2, sizeof(uuid_t));
}

// TODO(nedwill): this shouldn't return the same value
// within the same fuzz session (use a counter and reset)
void uuid_generate_random(uuid_t out) {
  if (get_fuzzed_bool()) {
    memcpy(out, "0000000000000000", 16);
    return;
  }
  if (get_fuzzed_bool()) {
    memcpy(out, "1111111111111111", 16);
    return;
  }
  memcpy(out, "2222222222222222", 16);
}

void uuid_copy(uuid_t dst, const uuid_t src) {
  memcpy(dst, src, sizeof(uuid_t));
}

void uuid_unparse_upper(const uuid_t uu, uuid_string_t out) {
  snprintf(out, sizeof(uuid_string_t),
           "%c%c%c%c-"
           "%c%c-"
           "%c%c-"
           "%c%c-"
           "%c%c%c%c%c%c",
           uu[0], uu[1], uu[2], uu[3], uu[4], uu[5], uu[6], uu[7], uu[8], uu[9],
           uu[10], uu[11], uu[12], uu[13], uu[14], uu[15]);
}

void uuid_unparse(const uuid_t uu, uuid_string_t out) {
  uuid_unparse_upper(uu, out);
}

extern void* kernproc;

void* vfs_context_proc() { return kernproc; }

// TODO(Ned): better timekeeping here
uint64_t mach_continuous_time(void) { return 0; }

void lck_mtx_assert() {}

void lck_mtx_init() {}

void lck_mtx_lock() {}

void lck_spin_init() {}

// fake these so they aren't null but still invalid
void* lck_grp_attr_alloc_init() { return (void*)1; }

void* lck_grp_alloc_init() { return (void*)1; }

void* lck_rw_alloc_init() { return (void*)1; }

void* lck_mtx_alloc_init() { return (void*)1; }

void* lck_spin_alloc_init() { return (void*)1; }

void lck_mtx_lock_spin() {}

void lck_mtx_convert_spin() {}

void lck_mtx_free() {}

void lck_rw_init() {}

void lck_mtx_unlock() {}

// TODO: handle timer scheduling
void timeout() { assert(false); }

void microtime(struct timeval* tvp) { memset(&tvp, 0, sizeof(tvp)); }

void microuptime(struct timeval* tvp) { memset(&tvp, 0, sizeof(tvp)); }

int mac_socket_check_accepted() { return 0; }

int mac_socket_check_setsockopt() { return 0; }

int mac_socket_check_bind() { return 0; }

int mac_file_check_ioctl() { return 0; }

int deflateInit2_() { return 1; }
int inflateInit2_() { return 1; }

bool kauth_cred_issuser() { return true; }

unsigned long RandomULong() {
  // returning 0 here would be a failure
  return 1;
}

// TODO: threading
int kernel_thread_start() { return 0; }

// TODO: can reach these
void cdevsw_add() {}

void devfs_make_node() {}

bool lck_mtx_try_lock() { return true; }

void kprintf() { return; }

void thread_deallocate() {}

// we are root
int proc_suser() { return 0; }

void _os_log_internal() {}

void hw_atomic_add() {}

void hw_atomic_sub() {}

void lck_mtx_destroy() {}

int mac_socket_check_ioctl() { return 0; }

bool proc_is64bit() { return true; }

int priv_check_cred() { return 0; }

bool lck_rw_try_lock_exclusive() { return true; }

void* malloc(size_t size);
void free(void* ptr);

// TODO(nedwill): fix this hack
__attribute__((visibility("default"))) bool real_copyout = true;

int copyout(const void* kaddr, user_addr_t udaddr, size_t len) {
  // randomly fail
  if (get_fuzzed_bool()) {
    return 1;
  }

  if (!udaddr || udaddr == 1 || !real_copyout) {
    void* buf = malloc(len);
    memcpy(buf, kaddr, len);
    free(buf);
    return 0;
  }

  memcpy((void*)udaddr, kaddr, len);
  return 0;
}

void* __MALLOC(size_t size, int type, int flags, vm_allocation_site_t* site) {
  void* addr = NULL;
  assert(type < M_LAST);

  if (size == 0) {
    return NULL;
  }

  addr = malloc(size);
  if (!addr) {
    return NULL;
  }

  if (flags & M_ZERO) {
    bzero(addr, size);
  }

  return (addr);
}

void read_frandom(void* buffer, unsigned int numBytes) {
  get_fuzzed_bytes(buffer, numBytes);
}

void read_random(void* buffer, unsigned int numBytes) {
  get_fuzzed_bytes(buffer, numBytes);
}

int ml_get_max_cpus(void) { return 1; }

void clock_interval_to_deadline(uint32_t interval, uint32_t scale_factor,
                                uint64_t* result) {
  *result = 0;
}

void clock_interval_to_absolutetime_interval(uint32_t interval,
                                             uint32_t scale_factor,
                                             uint64_t* result) {
  *result = 0;
}

void* thread_call_allocate_with_options() { return (void*)1; }

bool thread_call_enter_delayed_with_leeway() { return true; }

void lck_rw_assert() {}

uint32_t IOMapperIOVMAlloc() { return 0; }

int proc_uniqueid() { return 0; }

uint64_t mach_absolute_time() { return 0; }

int proc_pid() { return 0; }

void proc_getexecutableuuid(void* p, unsigned char* uuidbuf,
                            unsigned long size) {
  memset(uuidbuf, 0, size);
}

void proc_pidoriginatoruuid(void* buffer, size_t size) {
  memset(buffer, 0, size);
}

void* kauth_cred_proc_ref() { return (void*)1; }

void* kauth_cred_get() { return (void*)1; }

void* proc_ucred() { return (void*)1; }

int suser(void* arg1, void* arg2) {
  (void)arg1;
  (void)arg2;
  return 0;
}

void lck_rw_lock_shared() {}

void lck_rw_done() {}

bool proc_get_effective_thread_policy() {
  // TODO: more options
  return false;
}

void* current_proc() { return kernproc; }

int proc_selfpid() { return 1; }

void tvtohz() {}

int kauth_cred_getuid() {
  // UUID: root
  return get_fuzzed_bool() ? 1 : 0;
}

char* proc_best_name() { return "kernproc"; }

void* proc_find() { return kernproc; }

int mac_socket_check_create() { return 0; }

int mac_socket_check_accept() { return 0; }

void ovbcopy(const char* from, char* to, size_t nbytes) {
  memmove(to, from, nbytes);
}

int __attribute__((warn_unused_result))
copyin(const user_addr_t uaddr, void *kaddr, size_t len) {
  // Address 1 means use fuzzed bytes, otherwise use real bytes.
  // NOTE: this does not support nested useraddr.
  if (uaddr != 1) {
    memcpy(kaddr, (void*)uaddr, len);
    return 0;
  }

  if (get_fuzzed_bool()) {
    return -1;
  }

  get_fuzzed_bytes(kaddr, len);
  return 0;
}

void SHA1Final() {}

void SHA1Init() {}

void SHA1Update() {}

void* thread_call_allocate_with_priority() { return (void*)1; }

void lck_grp_attr_free() {}

void lck_grp_free() {}

void lck_rw_lock_exclusive() {}

void timevaladd() {}
void timevalsub() {}

void thread_call_enter_delayed() {}

void MD5Init() {}
void MD5Update() {}
void MD5Final(unsigned char* digest, void* ctx) {
  memset(digest, 0, 4);
}

void proc_rele() {}
void wakeup(void* chan) {}

void lck_spin_lock() {}
void lck_spin_unlock() {}
void kauth_cred_unref(void* cred) {}
void lck_rw_unlock_exclusive() {}

bool IS_64BIT_PROCESS() { return true; }

int mac_socket_check_listen() { return 0; }

void kauth_cred_ref() {}

void in_stat_set_activity_bitmap() {}

int mac_socket_check_getsockopt() { return 0; }

int mac_pipe_check_ioctl() { return 0; }

int mac_pipe_check_write() { return 0; }

int mac_pipe_check_kqfilter() { return 0; }

int mac_pipe_label_init() { return 0; }

int mac_pipe_label_destroy() { return 0; }

int mac_pipe_check_read() { return 0; }

int mac_pipe_check_stat() { return 0; }

int mac_pipe_label_associate() { return 0; }

int kauth_getuid() { return 0; }

int kauth_getgid() { return 0; }

int mac_pipe_check_select() { return 0; }

void _aio_close() {}
void unlink1() {}

int mac_socket_check_connect() { return 0; }

void ml_thread_policy() {}

void aes_encrypt_key128() {}

void OSBacktrace() {}

void lck_grp_attr_setdefault() {}

void nanouptime() {}

void wakeup_one() {}

int lck_mtx_try_lock_spin() { return 1; }

void absolutetime_to_nanoseconds(uint64_t in, uint64_t* out) { *out = 0; }

void free(void* ptr);

void nwk_wq_enqueue(struct nwk_wq_entry* nwk_item) {
  nwk_item->func(nwk_item->arg);
  free(nwk_item);
}

int ppsratecheck() { return 1; }

bool ratecheck() { return true; }

void fulong() {}
void ubc_cs_blob_deallocate() {}
void proc_thread() {}
void munge_user32_stat64() {}
int mac_file_check_lock() { return 0; }
void vnode_setsize() {}
void vnode_setnocache() {}
void kauth_authorize_fileop() {}
void VNOP_FSYNC() {}
void tablefull() {}
void vnode_recycle() {}
void ipc_object_copyin() {}
int mac_file_check_inherit() { return 0; }
void vnode_vid() {}
void munge_user32_stat() {}
void VNOP_OFFTOBLK() {}
int mac_file_check_create() { return 0; }
void fileport_port_to_fileglob() {}
void VNOP_SETATTR() {}
void vfs_devblocksize() {}
int mac_file_check_library_validation() { return 0; }
void ubc_cs_blob_add() {}
void vn_getpath() {}
void ipc_port_release_send() {}
void proc_kqhashlock_grp() {}
void vn_path_package_check() {}
void VNOP_GETATTR() {}
void ubc_cs_blob_allocate() {}
void audit_sysclose() {}
void vnode_is_openevt() {}
void audit_arg_vnpath_withref() {}
int mac_file_check_fcntl() { return 0; }
void VNOP_ALLOCATE() {}
void fg_vn_data_free() {}
void VNOP_BLKTOOFF() {}
void vnode_islnk() {}
void VNOP_IOCTL() {}
int mac_vnode_check_truncate() { return 0; }
int mac_file_check_dup() { return 0; }
void ubc_cs_blob_get() {}
void audit_arg_vnpath() {}
void get_task_ipcspace() {}
void vn_rdwr() {}
int mac_file_label_destroy() { return 0; }
void fileport_alloc() {}
void vnode_getwithref() {}
int mac_file_label_associate() { return 0; }
void sulong() {}
void proc_lck_attr() {}
int mac_vnode_check_write() { return 0; }
void ipc_port_copyout_send() {}
void kauth_filesec_free() {}
void munge_user64_stat64() {}
void munge_user64_stat() {}
void VNOP_EXCHANGE() {}
void vnode_set_openevt() {}
void vn_stat_noauth() {}
void vnode_mount() {}
void open1() {}
void kauth_authorize_fileop_has_listeners() {}
void fp_isguarded() {}
void audit_arg_fflags() {}
int mac_vnode_notify_truncate() { return 0; }
void fp_guard_exception() {}
void vnode_clear_openevt() {}
void pshm_stat() {}
void proc_knhashlock_grp() {}
void VNOP_BLOCKMAP() {}
void vnode_clearnocache() {}
void VNOP_ADVLOCK() {}
void ubc_cs_blob_revalidate() {}
void guarded_fileproc_free() {}
void audit_arg_text() {}
void vnode_isnocache() {}
void mach_port_deallocate() {}
int mac_file_label_init() { return 0; }
void vn_pathconf() {}
void audit_arg_mode() {}
long boottime_sec() { return 0; }
void mac_socket_check_receive() {}
void mac_socket_check_send() {}

// libkern/os/refcnt.c
// TODO(nedwill): implement these to catch refcount bugs
void os_ref_retain_internal() {}

os_ref_count_t os_ref_release_locked_internal(os_ref_atomic_t *at, struct os_refgrp *ref) {
  return 0;
}

os_ref_count_t os_ref_release_barrier_internal(os_ref_atomic_t *at, struct os_refgrp *ref) {
  return 0;
}

void os_ref_panic_live() {
  while (1) {
    assert(false);
  }
}

void os_ref_init_count_internal() {}

void kernel_debug() {}

void lck_rw_unlock_shared() {}
kern_return_t kmem_alloc_contig() { assert(false); }
uint32_t ipc_control_port_options;

bool current_task_can_use_restricted_in_port() { return true; }

unsigned int
ml_wait_max_cpus(void)
{
  return 1;
}

int
fls(unsigned int mask)
{
	if (mask == 0) {
		return 0;
	}

	return (sizeof(mask) << 3) - __builtin_clz(mask);
}

int scnprintf(char *buf, size_t size, const char *fmt, ...) {
  return 0;
}

rlim_t
proc_limitgetcur(proc_t p, int which, boolean_t to_lock_proc) {
  if (which == RLIMIT_NOFILE) {
    return 10;
  }
  assert(false);
}

task_t proc_task() { return TASK_NULL; }

vm_offset_t current_percpu_base(void) {
  assert(false);
  return 0;
}

int proc_pidversion(proc_t p) {
  assert(false);
  return 0;
}
