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

#ifdef LIBXNU_BUILD

// clang-format off
#include <stddef.h>
#include <stdint.h>

#include <security/mac.h>
#include <sys/sysproto.h>
// clang-format on

#include "bsd/net/necp.h"
#include "bsd/netinet/in.h"
#include "bsd/netinet/in_tclass.h"
#include "bsd/sys/_types/_sigset_t.h"
#include "bsd/sys/guarded.h"
#include "bsd/sys/kernel_types.h"
#include "bsd/sys/msg.h"
#include "bsd/sys/persona.h"
#include "bsd/sys/poll.h"
#include "bsd/sys/select.h"
#include "bsd/sys/shm.h"
#include "bsd/sys/signal.h"
#include "bsd/sys/socket.h"
#include "bsd/sys/spawn_internal.h"
#include "bsd/sys/timex.h"
#include "bsd/sys/types.h"
#else
// TODO(nedwill): is it valid to have this section?
#include <stdint.h>
#include <sys/types.h>

typedef __uint64_t user64_addr_t;
typedef struct user64_sa_endpoints sa_endpoints_t;
typedef unsigned char uuid_t[16];
typedef u_int64_t user_addr_t;
typedef u_int32_t socklen_t;
typedef __uint32_t sae_associd_t;
typedef __uint32_t sae_connid_t;
typedef int64_t user_ssize_t;
typedef char *caddr_t;
struct user64_sa_endpoints {
  unsigned int sae_srcif;    /* optional source interface */
  user64_addr_t sae_srcaddr; /* optional source address */
  socklen_t sae_srcaddrlen;  /* size of source address */
  user64_addr_t sae_dstaddr; /* destination address */
  socklen_t sae_dstaddrlen;  /* size of destination address */
};
struct user64_msghdr {
  user64_addr_t msg_name;    /* optional address */
  socklen_t msg_namelen;     /* size of address */
  user64_addr_t msg_iov;     /* scatter/gather array */
  int msg_iovlen;            /* # elements in msg_iov */
  user64_addr_t msg_control; /* ancillary data, see below */
  socklen_t msg_controllen;  /* ancillary data buffer len */
  int msg_flags;             /* flags on received message */
};
typedef uint32_t mach_port_name_t;
typedef u_int64_t user_size_t;
typedef __uint64_t guardid_t;

typedef uid_t au_id_t;
typedef pid_t au_asid_t;
#define NFS_MAX_FH_SIZE 128
struct fhandle {
  unsigned int fh_len;                    /* length of file handle */
  unsigned char fh_data[NFS_MAX_FH_SIZE]; /* file handle value */
};
typedef struct fhandle fhandle_t;

union sigval {
  /* Members as suggested by Annex C of POSIX 1003.1b. */
  int sival_int;
  void *sival_ptr;
};

typedef struct __siginfo {
  int si_signo;           /* signal number */
  int si_errno;           /* errno association */
  int si_code;            /* signal code */
  pid_t si_pid;           /* sending process */
  uid_t si_uid;           /* sender's ruid */
  int si_status;          /* exit value */
  void *si_addr;          /* faulting instruction */
  union sigval si_value;  /* signal value */
  long si_band;           /* band event for SIGPOLL */
  unsigned long __pad[7]; /* Reserved for Future Use */
} siginfo_t;

#define GRAFTDMG_SECURE_BOOT_CRYPTEX_ARGS_VERSION 1
#define MAX_GRAFT_ARGS_SIZE 512

/* Flag values for secure_boot_cryptex_args.sbc_flags */
#define SBC_PRESERVE_MOUNT              0x0001  /* Preserve underlying mount until shutdown */
#define SBC_ALTERNATE_SHARED_REGION     0x0002  /* Binaries within should use alternate shared region */
#define SBC_SYSTEM_CONTENT              0x0004  /* Cryptex contains system content */
#define SBC_PANIC_ON_AUTHFAIL           0x0008  /* On failure to authenticate, panic */
#define SBC_STRICT_AUTH                 0x0010  /* Strict authentication mode */
#define SBC_PRESERVE_GRAFT              0x0020  /* Preserve graft itself until unmount */

typedef struct secure_boot_cryptex_args {
	u_int32_t sbc_version;
	u_int32_t sbc_4cc;
	int sbc_authentic_manifest_fd;
	int sbc_user_manifest_fd;
	int sbc_payload_fd;
	u_int64_t sbc_flags;
} __attribute__((aligned(4), packed))  secure_boot_cryptex_args_t;

typedef union graft_args {
	u_int8_t max_size[MAX_GRAFT_ARGS_SIZE];
	secure_boot_cryptex_args_t sbc_args;
} graftdmg_args_un;
#endif /* LIBXNU_BUILD */

// TODO(nedwill): these names are incompatible with the host so we should generate
// alternative names as manually done here for now.
typedef int fuzz_sem_t;
struct fuzz_timezone {
  int tz_minuteswest; /* minutes west of Greenwich */
  int tz_dsttime;     /* type of dst correction */
};
typedef enum { FUZZ_P_ALL, FUZZ_P_PID, FUZZ_P_PGID } fuzz_idtype_t;
