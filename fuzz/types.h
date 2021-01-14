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

#define IPV6_VERSION 0x60
#define PKTF_LOOP 0x2000

struct necp_tlv_header {
  u_int8_t type;
  u_int32_t length;
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

#ifndef __APPLE__
__uint32_t ntohl(__uint32_t _data) { return __builtin_bswap32(_data); }

__uint16_t ntohs(__uint16_t _data) { return __builtin_bswap16(_data); }
#endif  // __APPLE__

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
  u_int64_t ia6t_expire;
  u_int64_t ia6t_preferred;
  u_int32_t ia6t_vltime;
  u_int32_t ia6t_pltime;
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
      u_int32_t ip6_un1_flow; /* 20 bits of flow-ID */
      u_int16_t ip6_un1_plen; /* payload length */
      u_int8_t ip6_un1_nxt;   /* next header */
      u_int8_t ip6_un1_hlim;  /* hop limit */
    } ip6_un1;
    u_int8_t ip6_un2_vfc; /* 4 bits version, top 4 bits class */
  } ip6_ctlun;
  struct in6_addr ip6_src; /* source address */
  struct in6_addr ip6_dst; /* destination address */
} __attribute__((__packed__));

struct ip {
  u_int ip_hl : 4,               /* header length */
      ip_v : 4;                  /* version */
  u_char ip_tos;                 /* type of service */
  u_short ip_len;                /* total length */
  u_short ip_id;                 /* identification */
  u_short ip_off;                /* fragment offset field */
  u_char ip_ttl;                 /* time to live */
  u_char ip_p;                   /* protocol */
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
  u_int8_t icmp6_type;   /* type field */
  u_int8_t icmp6_code;   /* code field */
  u_int16_t icmp6_cksum; /* checksum field */
  union {
    u_int32_t icmp6_un_data32[1]; /* type-specific field */
    u_int16_t icmp6_un_data16[2]; /* type-specific field */
    u_int8_t icmp6_un_data8[4];   /* type-specific field */
  } icmp6_dataun;
} __attribute__((__packed__));

struct ip6_rthdr {
  u_int8_t ip6r_nxt;     /* next header */
  u_int8_t ip6r_len;     /* length in units of 8 octets */
  u_int8_t ip6r_type;    /* routing type */
  u_int8_t ip6r_segleft; /* segments left */
                         /* followed by routing type specific data */
} __attribute__((__packed__));

struct ip6_rthdr0 {
  u_int8_t ip6r0_nxt;             /* next header */
  u_int8_t ip6r0_len;             /* length in units of 8 octets */
  u_int8_t ip6r0_type;            /* always zero */
  u_int8_t ip6r0_segleft;         /* segments left */
  u_int8_t ip6r0_reserved;        /* reserved field */
  u_int8_t ip6r0_slmap[3];        /* strict/loose bit map */
  struct in6_addr ip6r0_addr[23]; /* up to 23 addresses */
} __attribute__((__packed__));

struct ip6_frag {
  u_int8_t ip6f_nxt;      /* next header */
  u_int8_t ip6f_reserved; /* reserved field */
  u_int16_t ip6f_offlg;   /* offset, reserved, and flag */
  u_int32_t ip6f_ident;   /* identification */
} __attribute__((__packed__));

struct ip6_ext {
  u_int8_t ip6e_nxt;
  u_int8_t ip6e_len;
} __attribute__((__packed__));

#endif /* FUZZ_TYPES_H_ */
