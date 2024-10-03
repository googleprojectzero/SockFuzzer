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

#include <i386/types.h>
#include <kern/startup.h>
#include <mach/mach_types.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/kernel_types.h>
#include <sys/proc.h>
#include <sys/proc_internal.h>
#include <sys/queue.h>
#include <sys/signal.h>
#include <sys/vm.h>
#include <sys/wait.h>

#include "fuzz/host/hypercall/hypercall.h"
#include "fuzz/xnu/bsd/api/backend.h"
#include "third_party/xnu/BUILD/obj/EXPORT_HDRS/bsd/sys/sysproto.h"
#include "third_party/xnu/BUILD/obj/EXPORT_HDRS/osfmk/kern/timer_call.h"
#include "third_party/xnu/bsd/sys/kpi_mbuf.h"
#include "third_party/xnu/bsd/sys/sysent.h"

extern ifnet_t lo_ifp;

// TODO(nedwill): include all of these via headers
void cpu_init();
void kernel_bootstrap_thread(void);
void osfmk_bootstrap();

void *calloc(size_t nmemb, size_t size);
void free(void *ptr);

struct mbuf *mbuf_create(const uint8_t *data, size_t size, bool is_header,
                         bool force_ext, int m_type, int pktflags);
void ip_input(mbuf_t m);
void ip6_input(mbuf_t m);

const int MT_DATA = 1;

struct mbuf *get_mbuf_data(const char *data, size_t size, int pktflags) {
  struct mbuf *mbuf_data =
      mbuf_create((const uint8_t *)data, size, true, false, MT_DATA, pktflags);

  if (!mbuf_data) {
    return NULL;
  }

  // TODO(nedwill): consider using a non-loopback interface
  // This indicates where the packet came from.
  mbuf_pkthdr_setrcvif((mbuf_t)mbuf_data, lo_ifp);
  return mbuf_data;
}

bool initialize_kernel() {
  kernel_startup_bootstrap();
  timer_call_init();
  cpu_init();
  osfmk_bootstrap();
  kernel_bootstrap();
  return true;
}

void ip_input_wrapper(void *m) {
  ip_input((mbuf_t)m);
}

void ip6_input_wrapper(void *m) {
  ip6_input((mbuf_t)m);
}

// typedef struct task* task_t;

task_t get_init_task() {
  return proc_task(initproc);
}

int printf(const char *format, ...);
void proc_exit(proc_t p);

void KillAllNonInitProcs() {
  proc_list_lock();
  proc_t p = NULL;
  pid_t *pids = calloc(nprocs, sizeof(pid_t));
  size_t n = 0;
  ALLPROC_FOREACH(p) {
    if (p == kernproc || p == initproc) {
      continue;
    }
    pid_t pid = p->p_pid;
    pids[n++] = pid;
  }
  proc_list_unlock();

  for (int i = 0; i < n; i++) {
    int rv = 0;
    struct kill_args args = {
        .pid = pids[i],
        .signum = SIGKILL,
        .posix = 0,
    };
    kill(current_proc(), &args, &rv);
    GetHypercallInterface()->ThreadPrintf(
        "KillAllNonInitProcs: SIGKILL called on %d\n", pids[i]);
  }
  free(pids);

  // We now check that the pids were actually killed.
  // Uninterruptible threads cannot be killed, and kill() doesn't report an error.
  // We want to avoid unkillable procs building up and slowing down the fuzzer.
  proc_list_lock();
  n = 0;
  ALLPROC_FOREACH(p) {
    if (p == kernproc || p == initproc) {
      continue;
    }
    n++;
  }
  proc_list_unlock();
  if (n > 0) {
    GetHypercallInterface()->ThreadPrintf(
        "Failed to kill %d procs in KillAllNonInitProcs\n", n);
    // panic();
  }
}

enum {
  // TODO(nedwill): fix nosys signal handling
  NOSYS_SYSNO = 0,
  // TODO(nedwill): can't call exit more than once on same thread
  EXIT_SYSNO = 1,
  // TODO(nedwill): causes infinite loop killing non-init procs
  FORK_SYSNO = 2,
  // Banned until we support exit.
  PTRACE_SYSNO = 26,
  // TODO(nedwill): causes panic when reaping children
  POSIX_SPAWN_SYSNO = 244,
  // TODO(nedwill): crashes with null derefs
  SEMSYS_SYSNO = 251,
  SEMGET_SYSNO = 255,
  // TODO(nedwill): crashes due to bad signal number
  LIO_LISTIO_SYSNO = 320,
  // TODO(nedwill): crashes due to interactions with invalid waitqs
  PSELECT_SYSNO = 394,
};

extern const char *syscallnames[];

void XNUDoRandomSyscall(unsigned int number, void *data, size_t size) {
  number %= nsysent;
  switch (number) {
    case FORK_SYSNO:
    case PTRACE_SYSNO:
    case NOSYS_SYSNO:
    case POSIX_SPAWN_SYSNO:
    case EXIT_SYSNO:
    case LIO_LISTIO_SYSNO:
    case PSELECT_SYSNO:
    case SEMSYS_SYSNO:
    case SEMGET_SYSNO:
      return;
    default:
      break;
  }
  const struct sysent *entry = &sysent[number];
  size_t argument_size = (size_t)(entry->sy_narg * 8);
  void *arguments = calloc(1, argument_size);
  if (!arguments) {
    return;
  }
  if (size > argument_size) {
    size = argument_size;
  }
  memcpy(arguments, data, size);
  user_ssize_t retval = 0;
  GetHypercallInterface()->BlockCopyin();
  proc_t proc = current_proc();
  GetHypercallInterface()->ThreadPrintf(
      "[SYSCALL] (XNUDoRandomSyscall): %s (%d)\n", syscallnames[number],
      number);
  entry->sy_call(proc, arguments, &retval);
  GetHypercallInterface()->ThreadPrintf(
      "[/SYSCALL] (XNUDoRandomSyscall): %s returned %d\n", syscallnames[number],
      retval);
  GetHypercallInterface()->UnblockCopyin();
  free(arguments);
}

void *XNUCurrentProc() {
  return current_proc();
}

bool XNUReapInitChildren() {
  int retval = 0;
  struct wait4_args uap = {
      .pid = -1,
      .status = 0,
      .options = WNOHANG,
      .rusage = 0,
  };
  while (!LIST_EMPTY(&zombproc)) {
    int rv = wait4(initproc, &uap, &retval);
    if (!retval) {
      // panic("Failed to reap child");
      return false;
    }
  }
  return false;
}
