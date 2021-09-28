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

#include <sys/proc_internal.h>
#include <sys/filedesc.h>

#include "bsd/sys/_types/_size_t.h"
#include "bsd/sys/kpi_mbuf.h"
#include "bsd/sys/kpi_socket.h"
#include "bsd/sys/malloc.h"
#include "bsd/sys/protosw.h"
#include "bsd/sys/resourcevar.h"

extern ifnet_t lo_ifp;

void kernel_startup_bootstrap();
void inpcb_timeout(void*, void*);
void key_timehandler(void);
void frag_timeout(void);
void nd6_slowtimo(void);
void nd6_timeout(void);
void in6_tmpaddrtimer(void);
void mp_timeout(void);
void igmp_timeout(void);
void tcp_fuzzer_reset(void);
void in6_rtqtimo(void*);
void frag6_timeout();
void mld_timeout();
bool ioctl_wrapper(unsigned long com);
void ip_input(mbuf_t m);
void ip6_input(mbuf_t m);
struct mbuf* mbuf_create(const uint8_t* data, size_t size, bool is_header,
                         bool force_ext, int m_type, int pktflags);
void mcache_init(void);
void mbinit(void);
void eventhandler_init(void);
void dlil_init(void);
void socketinit(void);
void domaininit(void);
void domain_timeout(void*);
void loopattach(void);
void ether_family_init(void);
void tcp_cc_init(void);
void net_init_run(void);
errno_t necp_init(void);
void in_rtqtimo(void* targ);
void* nstat_idle_check(void* p0, void* p1);

extern int dlil_verbose;

struct proc proc0;
struct filedesc filedesc0;
struct plimit plimit0;
proc_t kernproc;
int cmask = CMASK;

__attribute__((visibility("default"))) bool init_proc(void) {
  kernproc = &proc0;
  kernproc->p_fd = &filedesc0;
  // Permitting 10 open files should be more than enough
  // without blowing up execution time. If you change this
  // number you probably want to change the fd enum in the
  // protobuf file.
  plimit0.pl_rlimit[RLIMIT_NOFILE].rlim_cur = 10;
  plimit0.pl_rlimit[RLIMIT_NOFILE].rlim_max = 10;
  kernproc->p_limit = &plimit0;
  filedesc0.fd_cmask = cmask;
  filedesc0.fd_knlistsize = -1;
  filedesc0.fd_knlist = NULL;
  filedesc0.fd_knhash = NULL;
  filedesc0.fd_knhashmask = 0;
  // Increase sb_max
  sb_max = 8192*1024 * 4;
  dlil_verbose = 0;
  return true;
}

// TODO: expose these clears to the net protobuf
__attribute__((visibility("default"))) void clear_all() {
  inpcb_timeout(NULL, NULL);
  key_timehandler();
  frag_timeout();
  nd6_slowtimo();
  nd6_timeout();
  in6_tmpaddrtimer();
  mp_timeout();
  igmp_timeout();
  tcp_fuzzer_reset();
  frag6_timeout();
  mld_timeout();

  // this adds work to the work queue
  in6_rtqtimo(NULL);
  in_rtqtimo(NULL);

  // TODO(nedwill): nd6_dad_timer
  nstat_idle_check(NULL, NULL);
  domain_timeout(NULL);
}

#define MT_DATA 1

__attribute__((visibility("default"))) struct mbuf* get_mbuf_data(
    const char* data, size_t size, int pktflags) {
  struct mbuf* mbuf_data =
      mbuf_create((const uint8_t*)data, size, true, false, MT_DATA, pktflags);

  // TODO(nedwill): consider using a non-loopback interface
  // This indicates where the packet came from.
  mbuf_pkthdr_setrcvif((mbuf_t)mbuf_data, lo_ifp);
  return mbuf_data;
}

extern unsigned long ioctls[];
extern int num_ioctls;

__attribute__((visibility("default"))) bool initialize_network() {
  kernel_startup_bootstrap();
  kernel_startup_initialize_upto(STARTUP_SUB_EARLY_BOOT);
  mcache_init();
  mbinit();
  eventhandler_init();
  dlil_init();
  socketinit();
  domaininit();
  loopattach();
  ether_family_init();
  tcp_cc_init();
  net_init_run();
  int res = necp_init();
  assert(!res);
  return true;
}

__attribute__((visibility("default"))) void ip_input_wrapper(void* m) {
  ip_input((mbuf_t)m);
}

__attribute__((visibility("default"))) void ip6_input_wrapper(void* m) {
  ip6_input((mbuf_t)m);
}
