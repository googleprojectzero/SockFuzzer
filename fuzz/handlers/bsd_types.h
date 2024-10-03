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

#ifndef FUZZ_TYPES_H_
#define FUZZ_TYPES_H_

#include <sys/types.h>

#include <cstdint>

#include "fuzz/proto/bsd.pb.h"
#include "fuzz/proto/bsd_types.pb.h"

#define IPV6_VERSION 0x60
#define PKTF_LOOP 0x2000

typedef char *caddr_t;

struct necp_tlv_header {
  uint8_t type;
  uint32_t length;
} __attribute__((__packed__));

struct sockaddr_generic {
  uint8_t sa_len;
  uint8_t sa_family;
};

typedef __uint8_t sa_family_t;
struct sockaddr {
  __uint8_t sa_len;
  sa_family_t sa_family;
  char sa_data[14];
};

typedef uint32_t in_addr_t;
typedef uint8_t sa_family_t;
typedef uint16_t in_port_t;

struct in_addr {
  in_addr_t s_addr;
};

struct sockaddr_in {
  __uint8_t sin_len;
  sa_family_t sin_family;
  in_port_t sin_port;
  struct in_addr sin_addr;
  char sin_zero[8];
};

typedef struct in6_addr {
  union {
    __uint8_t __u6_addr8[16];
    __uint16_t __u6_addr16[8];
    __uint32_t __u6_addr32[4];
  } __u6_addr;
} in6_addr_t;

struct sockaddr_in6 {
  uint8_t sin6_len;
  sa_family_t sin6_family;
  in_port_t sin6_port;
  uint32_t sin6_flowinfo;
  struct in6_addr sin6_addr;
  uint32_t sin6_scope_id;
};

#define s6_addr __u6_addr.__u6_addr8
#define s6_addr8 __u6_addr.__u6_addr8
#define s6_addr16 __u6_addr.__u6_addr16
#define s6_addr32 __u6_addr.__u6_addr32

/*
 * Unspecified
 */
#define IN6_IS_ADDR_UNSPECIFIED(a)                                 \
  ((*(const __uint32_t *)(const void *)(&(a)->s6_addr[0]) == 0) && \
   (*(const __uint32_t *)(const void *)(&(a)->s6_addr[4]) == 0) && \
   (*(const __uint32_t *)(const void *)(&(a)->s6_addr[8]) == 0) && \
   (*(const __uint32_t *)(const void *)(&(a)->s6_addr[12]) == 0))

/*
 * Loopback
 */
#define IN6_IS_ADDR_LOOPBACK(a)                                    \
  ((*(const __uint32_t *)(const void *)(&(a)->s6_addr[0]) == 0) && \
   (*(const __uint32_t *)(const void *)(&(a)->s6_addr[4]) == 0) && \
   (*(const __uint32_t *)(const void *)(&(a)->s6_addr[8]) == 0) && \
   (*(const __uint32_t *)(const void *)(&(a)->s6_addr[12]) == ntohl(1)))

/*
 * IPv4 compatible
 */
#define IN6_IS_ADDR_V4COMPAT(a)                                     \
  ((*(const __uint32_t *)(const void *)(&(a)->s6_addr[0]) == 0) &&  \
   (*(const __uint32_t *)(const void *)(&(a)->s6_addr[4]) == 0) &&  \
   (*(const __uint32_t *)(const void *)(&(a)->s6_addr[8]) == 0) &&  \
   (*(const __uint32_t *)(const void *)(&(a)->s6_addr[12]) != 0) && \
   (*(const __uint32_t *)(const void *)(&(a)->s6_addr[12]) != ntohl(1)))

/*
 * Mapped
 */
#define IN6_IS_ADDR_V4MAPPED(a)                                    \
  ((*(const __uint32_t *)(const void *)(&(a)->s6_addr[0]) == 0) && \
   (*(const __uint32_t *)(const void *)(&(a)->s6_addr[4]) == 0) && \
   (*(const __uint32_t *)(const void *)(&(a)->s6_addr[8]) ==       \
    ntohl(0x0000ffff)))

/*
 * 6to4
 */
#define IN6_IS_ADDR_6TO4(x) (ntohs((x)->s6_addr16[0]) == 0x2002)

/*
 * KAME Scope Values
 */

#define __IPV6_ADDR_SCOPE_NODELOCAL 0x01
#define __IPV6_ADDR_SCOPE_INTFACELOCAL 0x01
#define __IPV6_ADDR_SCOPE_LINKLOCAL 0x02
#define __IPV6_ADDR_SCOPE_SITELOCAL 0x05
#define __IPV6_ADDR_SCOPE_ORGLOCAL 0x08
#define __IPV6_ADDR_SCOPE_GLOBAL 0x0e

/*
 * Unicast Scope
 * Note that we must check topmost 10 bits only, not 16 bits (see RFC2373).
 */
#define IN6_IS_ADDR_LINKLOCAL(a) \
  (((a)->s6_addr[0] == 0xfe) && (((a)->s6_addr[1] & 0xc0) == 0x80))
#define IN6_IS_ADDR_SITELOCAL(a) \
  (((a)->s6_addr[0] == 0xfe) && (((a)->s6_addr[1] & 0xc0) == 0xc0))

/*
 * Multicast
 */
#define IN6_IS_ADDR_MULTICAST(a) ((a)->s6_addr[0] == 0xff)

/*
 * Unique Local IPv6 Unicast Addresses (per RFC 4193)
 */
#define IN6_IS_ADDR_UNIQUE_LOCAL(a) \
  (((a)->s6_addr[0] == 0xfc) || ((a)->s6_addr[0] == 0xfd))

#define __IPV6_ADDR_MC_SCOPE(a) ((a)->s6_addr[1] & 0x0f)

/*
 * Multicast Scope
 */
#define IN6_IS_ADDR_MC_NODELOCAL(a) \
  (IN6_IS_ADDR_MULTICAST(a) &&      \
   (__IPV6_ADDR_MC_SCOPE(a) == __IPV6_ADDR_SCOPE_NODELOCAL))
#define IN6_IS_ADDR_MC_LINKLOCAL(a) \
  (IN6_IS_ADDR_MULTICAST(a) &&      \
   (__IPV6_ADDR_MC_SCOPE(a) == __IPV6_ADDR_SCOPE_LINKLOCAL))
#define IN6_IS_ADDR_MC_SITELOCAL(a) \
  (IN6_IS_ADDR_MULTICAST(a) &&      \
   (__IPV6_ADDR_MC_SCOPE(a) == __IPV6_ADDR_SCOPE_SITELOCAL))
#define IN6_IS_ADDR_MC_ORGLOCAL(a) \
  (IN6_IS_ADDR_MULTICAST(a) &&     \
   (__IPV6_ADDR_MC_SCOPE(a) == __IPV6_ADDR_SCOPE_ORGLOCAL))
#define IN6_IS_ADDR_MC_GLOBAL(a) \
  (IN6_IS_ADDR_MULTICAST(a) &&   \
   (__IPV6_ADDR_MC_SCOPE(a) == __IPV6_ADDR_SCOPE_GLOBAL))

#define IN6_IS_ADDR_MC_INTFACELOCAL(a) \
  (IN6_IS_ADDR_MULTICAST(a) &&         \
   (__IPV6_ADDR_MC_SCOPE(a) == __IPV6_ADDR_SCOPE_INTFACELOCAL))

struct in6_addrlifetime_64 {
  uint64_t ia6t_expire;
  uint64_t ia6t_preferred;
  uint32_t ia6t_vltime;
  uint32_t ia6t_pltime;
};

#define IFNAMSIZ 16
struct in6_aliasreq_64 {
  char ifra_name[IFNAMSIZ];
  struct sockaddr_in6 ifra_addr;
  struct sockaddr_in6 ifra_dstaddr;
  struct sockaddr_in6 ifra_prefixmask;
  int ifra_flags;
  struct in6_addrlifetime_64 ifra_lifetime;
};

struct ifreq {
#ifndef IFNAMSIZ
#define IFNAMSIZ IF_NAMESIZE
#endif
  char ifr_name[IFNAMSIZ]; /* if name, e.g. "en0" */
  union {
    struct sockaddr ifru_addr;
    struct sockaddr ifru_dstaddr;
    struct sockaddr ifru_broadaddr;
    short ifru_flags;
    int ifru_metric;
    int ifru_mtu;
    int ifru_phys;
    int ifru_media;
    int ifru_intval;
    caddr_t ifru_data;
  } ifr_ifru;
#define ifr_flags ifr_ifru.ifru_flags /* flags */
};

struct ip6_hdr {
  union {
    struct ip6_hdrctl {
      uint32_t ip6_un1_flow; /* 20 bits of flow-ID */
      uint16_t ip6_un1_plen; /* payload length */
      uint8_t ip6_un1_nxt;   /* next header */
      uint8_t ip6_un1_hlim;  /* hop limit */
    } ip6_un1;
    uint8_t ip6_un2_vfc; /* 4 bits version, top 4 bits class */
  } ip6_ctlun;
  struct in6_addr ip6_src; /* source address */
  struct in6_addr ip6_dst; /* destination address */
} __attribute__((__packed__));

struct ip {
  u_int ip_hl : 4,               /* header length */
      ip_v : 4;                  /* version */
  uint8_t ip_tos;                /* type of service */
  u_short ip_len;                /* total length */
  u_short ip_id;                 /* identification */
  u_short ip_off;                /* fragment offset field */
  uint8_t ip_ttl;                /* time to live */
  uint8_t ip_p;                  /* protocol */
  u_short ip_sum;                /* checksum */
  struct in_addr ip_src, ip_dst; /* source and dest address */
};

typedef __uint32_t tcp_seq;

struct tcphdr {
  unsigned short th_sport; /* source port */
  unsigned short th_dport; /* destination port */
  tcp_seq th_seq;          /* sequence number */
  tcp_seq th_ack;          /* acknowledgement number */
  unsigned int th_x2 : 4,  /* (unused) */
      th_off : 4;          /* data offset */
  unsigned char th_flags;

  unsigned short th_win; /* window */
  unsigned short th_sum; /* checksum */
  unsigned short th_urp; /* urgent pointer */
};

struct icmp6_hdr {
  uint8_t icmp6_type;   /* type field */
  uint8_t icmp6_code;   /* code field */
  uint16_t icmp6_cksum; /* checksum field */
  union {
    uint32_t icmp6_un_data32[1]; /* type-specific field */
    uint16_t icmp6_un_data16[2]; /* type-specific field */
    uint8_t icmp6_un_data8[4];   /* type-specific field */
  } icmp6_dataun;
} __attribute__((__packed__));

struct ip6_rthdr {
  uint8_t ip6r_nxt;     /* next header */
  uint8_t ip6r_len;     /* length in units of 8 octets */
  uint8_t ip6r_type;    /* routing type */
  uint8_t ip6r_segleft; /* segments left */
                        /* followed by routing type specific data */
} __attribute__((__packed__));

struct ip6_rthdr0 {
  uint8_t ip6r0_nxt;              /* next header */
  uint8_t ip6r0_len;              /* length in units of 8 octets */
  uint8_t ip6r0_type;             /* always zero */
  uint8_t ip6r0_segleft;          /* segments left */
  uint8_t ip6r0_reserved;         /* reserved field */
  uint8_t ip6r0_slmap[3];         /* strict/loose bit map */
  struct in6_addr ip6r0_addr[23]; /* up to 23 addresses */
} __attribute__((__packed__));

struct ip6_frag {
  uint8_t ip6f_nxt;      /* next header */
  uint8_t ip6f_reserved; /* reserved field */
  uint16_t ip6f_offlg;   /* offset, reserved, and flag */
  uint32_t ip6f_ident;   /* identification */
} __attribute__((__packed__));

struct ip6_ext {
  uint8_t ip6e_nxt;
  uint8_t ip6e_len;
} __attribute__((__packed__));

typedef uint64_t user_addr_t;

struct kevent {
  uintptr_t ident; /* identifier for this event */
  int16_t filter;  /* filter for event */
  uint16_t flags;  /* general flags */
  uint32_t fflags; /* filter-specific flags */
  intptr_t data;   /* filter-specific data */
  void *udata;     /* opaque user data identifier */

  kevent(uintptr_t ident, int16_t filter, uint16_t flags, uint32_t fflags,
         intptr_t data, void *udata)
      : ident(ident),
        filter(filter),
        flags(flags),
        fflags(fflags),
        data(data),
        udata(udata) {}
};

struct msghdr {
  void *msg_name;             /* [XSI] optional address */
  __socklen_t msg_namelen;    /* [XSI] size of address */
  struct iovec *msg_iov;      /* [XSI] scatter/gather array */
  int msg_iovlen;             /* [XSI] # elements in msg_iov */
  void *msg_control;          /* [XSI] ancillary data, see below */
  __socklen_t msg_controllen; /* [XSI] ancillary data buffer len */
  int msg_flags;              /* [XSI] flags on received message */
};

typedef __uint64_t rlim_t;
struct rlimit {
  rlim_t rlim_cur; /* current (soft) limit */
  rlim_t rlim_max; /* maximum value for rlim_cur */
};

struct ipv6_prefix {
  struct in6_addr ipv6_prefix;
  uint32_t prefix_len;
};

typedef u_int32_t necp_kernel_policy_result;
typedef u_int32_t necp_kernel_policy_filter;
typedef unsigned char uuid_t[16];

typedef union {
  u_int tunnel_interface_index;
  u_int scoped_interface_index;
  u_int32_t flow_divert_control_unit;
  u_int32_t filter_control_unit;
  u_int32_t pass_flags;
  u_int32_t drop_flags;
} necp_kernel_policy_routing_result_parameter;

#define NECP_MAX_NETAGENTS 16
#define NAT64_MAX_NUM_PREFIXES 4

struct necp_aggregate_result {
  necp_kernel_policy_result routing_result;
  necp_kernel_policy_routing_result_parameter routing_result_parameter;
  necp_kernel_policy_filter filter_control_unit;
  u_int32_t flow_divert_aggregate_unit;
  necp_kernel_policy_result service_action;
  uuid_t service_uuid;
  u_int32_t service_flags;
  u_int32_t service_data;
  u_int routed_interface_index;
  u_int32_t policy_id;
  uuid_t netagents[NECP_MAX_NETAGENTS];
  u_int32_t netagent_use_flags[NECP_MAX_NETAGENTS];
  struct ipv6_prefix nat64_prefixes[NAT64_MAX_NUM_PREFIXES];
  u_int8_t mss_recommended;
};

/* union for signal handlers */
union __sigaction_u {
  void (*__sa_handler)(int);
  void (*__sa_sigaction)(int, struct __siginfo *, void *);
};

/*
 * Signal vector "template" used in sigaction call.
 */
struct sigaction {
  union __sigaction_u __sigaction_u; /* signal handler */
  sigset_t sa_mask;                  /* signal mask to apply */
  int sa_flags;                      /* see signal options below */
};

struct rusage {
  struct timeval ru_utime; /* user time used (PL) */
  struct timeval ru_stime; /* system time used (PL) */
#if __DARWIN_C_LEVEL < __DARWIN_C_FULL
  long ru_opaque[14]; /* implementation defined */
#else
  /*
	 * Informational aliases for source compatibility with programs
	 * that need more information than that provided by standards,
	 * and which do not mind being OS-dependent.
	 */
  long ru_maxrss;   /* max resident set size (PL) */
#define ru_first ru_ixrss /* internal: ruadd() range start */
  long ru_ixrss;    /* integral shared memory size (NU) */
  long ru_idrss;    /* integral unshared data (NU)  */
  long ru_isrss;    /* integral unshared stack (NU) */
  long ru_minflt;   /* page reclaims (NU) */
  long ru_majflt;   /* page faults (NU) */
  long ru_nswap;    /* swaps (NU) */
  long ru_inblock;  /* block input operations (atomic) */
  long ru_oublock;  /* block output operations (atomic) */
  long ru_msgsnd;   /* messages sent (atomic) */
  long ru_msgrcv;   /* messages received (atomic) */
  long ru_nsignals; /* signals received (atomic) */
  long ru_nvcsw;    /* voluntary context switches (atomic) */
  long ru_nivcsw;   /* involuntary " */
#define ru_last ru_nivcsw /* internal: ruadd() range end */
#endif                    /* __DARWIN_C_LEVEL >= __DARWIN_C_FULL */
};

enum {
  NFSSVC_NFSD = 0x004,
  NFSSVC_ADDSOCK = 0x008,
  NFSSVC_EXPORTSTATS = 0x010,
  NFSSVC_USERSTATS = 0x020,
  NFSSVC_USERCOUNT = 0x040,
  NFSSVC_ZEROSTATS = 0x080,
  NFSSVC_SRVSTATS = 0x100,
  NFSSVC_EXPORT = 0x200
};

void get_sockaddr6(struct sockaddr_in6 *sai, const SockAddr6 &sa6);
std::string get_sockaddr(const SockAddr &sockaddr);
void get_in6_addrlifetime_64(struct in6_addrlifetime_64 *sai,
                             const In6AddrLifetime_64 &msg);
void get_ifr_name(void *dest, const IfrName name);

void DoIpInput(const Packet &packet);
void DoNecpClientAction(const NecpClientAction &necp_client_action);

#endif /* FUZZ_TYPES_H_ */
