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

#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>

#include <string>

#include "absl/strings/str_join.h"
#include "bsd_types.h"
#include "fuzz/proto/bsd.pb.h"
#include "fuzz/proto/bsd_enums.pb.h"
#include "fuzz/proto/bsd_types.pb.h"
#include "fuzz/host/host.h"
#include "fuzz/xnu/bsd/api/backend.h"

#ifndef __APPLE__
__uint32_t ntohl(__uint32_t _data) {
  return __builtin_bswap32(_data);
}

__uint16_t ntohs(__uint16_t _data) {
  return __builtin_bswap16(_data);
}
#endif  // __APPLE__

// TODO(nedwill): support multiple addresses of each type below,
// not just one of each type
void get_in6_addr(struct in6_addr *sai, enum In6Addr addr) {
  memset(sai, 0, sizeof(*sai));
  switch (addr) {
    case IN6_ADDR_SELF: {
      sai->__u6_addr.__u6_addr32[0] = 16810238;
      sai->__u6_addr.__u6_addr32[0] = 0;
      sai->__u6_addr.__u6_addr32[0] = 0;
      sai->__u6_addr.__u6_addr32[0] = 16777216;
      // assert(IN6_IS_ADDR_SELF(sai));
      break;
    }
    case IN6_ADDR_LINK_LOCAL: {
      sai->s6_addr[0] = 0xfe;
      sai->s6_addr[1] = 0x80;
      // TODO(nedwill): set other fields?
      assert(IN6_IS_ADDR_LINKLOCAL(sai));
      break;
    }
    case IN6_ADDR_LOOPBACK: {
      *sai = {{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                static_cast<uint8_t>(addr)}}};
      assert(IN6_IS_ADDR_LOOPBACK(sai));
      break;
    }
    case IN6_ADDR_REAL:
    case MAYBE_LOCALHOST: {
      *sai = {{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                static_cast<uint8_t>(addr)}}};
      break;
    }
    case IN6_ADDR_V4COMPAT: {
      sai->s6_addr[12] = 1;
      assert(IN6_IS_ADDR_V4COMPAT(sai));
      break;
    }
    case IN6_ADDR_V4MAPPED: {
      *reinterpret_cast<uint32_t *>(&sai->s6_addr[8]) = 0xffff0000;
      assert(IN6_IS_ADDR_V4MAPPED(sai));
      break;
    }
    case IN6_ADDR_6TO4: {
      // sai->s6_addr16[0] = ntohs(0x2002);
      // assert(IN6_IS_ADDR_6TO4(sai));
      break;
    }
    case IN6_ADDR_LINKLOCAL: {
      sai->s6_addr[0] = 0xfe;
      sai->s6_addr[1] = 0x80;
      assert(IN6_IS_ADDR_LINKLOCAL(sai));
      break;
    }
    case IN6_ADDR_SITELOCAL: {
      sai->s6_addr[0] = 0xfe;
      sai->s6_addr[1] = 0xc0;
      assert(IN6_IS_ADDR_SITELOCAL(sai));
      break;
    }
    case IN6_ADDR_MULTICAST: {
      sai->s6_addr[0] = 0xff;
      assert(IN6_IS_ADDR_MULTICAST(sai));
      break;
    }
    case IN6_ADDR_UNIQUE_LOCAL: {
      sai->s6_addr[0] = 0xfc;
      assert(IN6_IS_ADDR_UNIQUE_LOCAL(sai));
      break;
    }
    case IN6_ADDR_MC_NODELOCAL: {
      sai->s6_addr[0] = 0xff;
      sai->s6_addr[1] = __IPV6_ADDR_SCOPE_NODELOCAL;
      assert(IN6_IS_ADDR_MC_NODELOCAL(sai));
      break;
    }
    case IN6_ADDR_MC_INTFACELOCAL: {
      sai->s6_addr[0] = 0xff;
      sai->s6_addr[1] = __IPV6_ADDR_SCOPE_INTFACELOCAL;
      assert(IN6_IS_ADDR_MC_INTFACELOCAL(sai));
      break;
    }
    case IN6_ADDR_MC_LINKLOCAL: {
      sai->s6_addr[0] = 0xff;
      sai->s6_addr[1] = __IPV6_ADDR_SCOPE_LINKLOCAL;
      assert(IN6_IS_ADDR_MC_LINKLOCAL(sai));
      break;
    }
    case IN6_ADDR_MC_SITELOCAL: {
      sai->s6_addr[0] = 0xff;
      sai->s6_addr[1] = __IPV6_ADDR_SCOPE_SITELOCAL;
      assert(IN6_IS_ADDR_MC_SITELOCAL(sai));
      break;
    }
    case IN6_ADDR_MC_ORGLOCAL: {
      sai->s6_addr[0] = 0xff;
      sai->s6_addr[1] = __IPV6_ADDR_SCOPE_ORGLOCAL;
      assert(IN6_IS_ADDR_MC_ORGLOCAL(sai));
      break;
    }
    case IN6_ADDR_MC_GLOBAL: {
      sai->s6_addr[0] = 0xff;
      sai->s6_addr[1] = __IPV6_ADDR_SCOPE_GLOBAL;
      assert(IN6_IS_ADDR_MC_GLOBAL(sai));
      break;
    }
    case IN6_ADDR_UNSPECIFIED:
    case IN6_ADDR_ANY: {
      assert(IN6_IS_ADDR_UNSPECIFIED(sai));
      break;
    }
    case IN6_ADDR_LOCAL_ADDRESS: {
      // Discovered this address dynamically
      // fe80:0001:0000:0000:a8aa:aaaa:aaaa:aaaa
      sai->s6_addr16[0] = 0xfe80;
      sai->s6_addr16[1] = 0x0001;
      sai->s6_addr16[4] = 0xa8aa;
      sai->s6_addr16[5] = 0xaaaa;
      sai->s6_addr16[6] = 0xaaaa;
      sai->s6_addr16[7] = 0xaaaa;
    }
      // *sai = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (uint8_t)addr};
  }
}

void get_sockaddr6(struct sockaddr_in6 *sai, const SockAddr6 &sa6) {
  sai->sin6_len = sizeof(struct sockaddr_in6);
  sai->sin6_family = static_cast<sa_family_t>(AF_INET6);  // sa6.family();
  sai->sin6_port = static_cast<in_port_t>(sa6.port());
  sai->sin6_flowinfo = sa6.flow_info();
  get_in6_addr(&sai->sin6_addr, sa6.sin6_addr());
  sai->sin6_scope_id = sa6.sin6_scope_id();
}

std::string get_sockaddr(const SockAddr &sockaddr) {
  std::string dat;
  switch (sockaddr.sockaddr_case()) {
    case SockAddr::kSockaddrGeneric: {
      const SockAddrGeneric &sag = sockaddr.sockaddr_generic();
      // data size + sizeof(sa_len) + sizeof(sa_family)
      struct sockaddr_generic sag_s = {
          .sa_len = static_cast<uint8_t>(sizeof(sockaddr_generic) +
                                         sag.sa_data().size()),
          .sa_family = static_cast<uint8_t>(sag.sa_family()),
      };

      dat = std::string(reinterpret_cast<char *>(&sag_s),
                        reinterpret_cast<char *>(&sag_s) + sizeof(sag_s));
      dat += sag.sa_data();
      break;
    }
    case SockAddr::kSockaddr4: {
      struct sockaddr_in sai = {
          .sin_len = sizeof(struct sockaddr_in),
          .sin_family =
              AF_INET,  // (unsigned char)sockaddr.sockaddr4().sin_family(),
          .sin_port =
              static_cast<unsigned short>(sockaddr.sockaddr4().sin_port()),
          .sin_addr = {static_cast<unsigned int>(
              sockaddr.sockaddr4().sin_addr())},
          .sin_zero = {},
      };
      dat = std::string(reinterpret_cast<char *>(&sai),
                        reinterpret_cast<char *>(&sai) + sizeof(sai));
      break;
    }
    case SockAddr::kSockaddr6: {
      struct sockaddr_in6 sai = {};
      get_sockaddr6(&sai, sockaddr.sockaddr6());
      dat = std::string((char *)&sai, (char *)&sai + sizeof(sai));
      break;
    }
    // case SockAddr::kRawBytes: {
    //   dat = sockaddr.raw_bytes();
    //   break;
    // }
    case SockAddr::SOCKADDR_NOT_SET: {
      break;
    }
  }
  if (is_verbose) {
    g_host->Log("get_sockaddr: returning dat\n");
    // TODO(nedwill): have this whole function return std::string<uint8_t>
    std::vector<std::uint8_t> dat_vec;
    for (const uint8_t ch : dat) {
      dat_vec.push_back(ch);
    }
    std::string result;
    g_host->Log(absl::StrCat("{", absl::StrJoin(dat_vec, ", "), "}\n"));
  }
  return dat;
}

std::string get_ip6_hdr(const Ip6Hdr &hdr, uint16_t expected_size) {
  struct ip6_hdr ip6_hdr;
  memset(&ip6_hdr, 0, sizeof(ip6_hdr));
  get_in6_addr(&ip6_hdr.ip6_src, hdr.ip6_src());
  get_in6_addr(&ip6_hdr.ip6_dst, hdr.ip6_src());
  ip6_hdr.ip6_ctlun.ip6_un2_vfc = IPV6_VERSION;
  // How TF does flow work?
  // ip6_hdr.ip6_ctlun.ip6_un1.ip6_un1_flow = hdr.ip6_hdrctl().ip6_un1_flow();
  ip6_hdr.ip6_ctlun.ip6_un1.ip6_un1_plen =
      __builtin_bswap16(expected_size);  // hdr.ip6_hdrctl().ip6_un1_plen();
  ip6_hdr.ip6_ctlun.ip6_un1.ip6_un1_nxt = hdr.ip6_hdrctl().ip6_un1_nxt();
  ip6_hdr.ip6_ctlun.ip6_un1.ip6_un1_hlim = hdr.ip6_hdrctl().ip6_un1_hlim();
  std::string dat(reinterpret_cast<char *>(&ip6_hdr),
                  reinterpret_cast<char *>(&ip6_hdr) + sizeof(ip6_hdr));
  return dat;
}

std::string get_ip_hdr(const IpHdr &hdr, size_t expected_size) {
  struct in_addr ip_src = {.s_addr = static_cast<unsigned int>(hdr.ip_src())};
  struct in_addr ip_dst = {.s_addr = static_cast<unsigned int>(hdr.ip_dst())};
  struct ip ip_hdr = {
      .ip_hl = 5,    // TODO(nedwill): support options // hdr.ip_hl(),
      .ip_v = IPV4,  // hdr.ip_v(),
      .ip_tos = static_cast<u_char>(hdr.ip_tos()),
      .ip_len = static_cast<u_short>(__builtin_bswap16(expected_size)),
      .ip_id = static_cast<u_short>(hdr.ip_id()),
      .ip_off = static_cast<u_short>(hdr.ip_off()),
      .ip_ttl = static_cast<u_char>(hdr.ip_ttl()),
      .ip_p = static_cast<u_char>(hdr.ip_p()),
      .ip_sum = 0,
      .ip_src = ip_src,
      .ip_dst = ip_dst,
  };
  std::string dat(reinterpret_cast<char *>(&ip_hdr),
                  reinterpret_cast<char *>(&ip_hdr) + sizeof(ip_hdr));
  return dat;
}

// message TcpHdr {
//   required Port th_sport = 1;
//   required Port th_dport = 2;
//   required uint32 th_seq = 3;
//   required uint32 th_ack = 4;
//   required uint32 th_off = 5;
//   repeated TcpFlag th_flags = 6;
//   required uint32 th_win = 7;
//   required uint32 th_sum = 8;
//   required uint32 th_urp = 9;
// }

std::string get_tcp_hdr(const TcpHdr &hdr) {
  struct tcphdr tcphdr = {
      .th_sport = static_cast<unsigned short>(hdr.th_sport()),
      .th_dport = static_cast<unsigned short>(hdr.th_dport()),
      .th_seq = __builtin_bswap32(hdr.th_seq()),
      .th_ack = __builtin_bswap32(hdr.th_ack()),
      .th_off = hdr.th_off(),
      .th_flags = 0,
      .th_win = static_cast<unsigned short>(hdr.th_win()),
      .th_sum = 0,
      .th_urp = static_cast<unsigned short>(hdr.th_urp()),
  };

  for (const int flag : hdr.th_flags()) {
    tcphdr.th_flags ^= flag;
  }

  // Prefer pure syn
  if (hdr.is_pure_syn()) {
    tcphdr.th_flags &= ~(TH_RST | TH_ACK);
    tcphdr.th_flags |= TH_SYN;
  } else if (hdr.is_pure_ack()) {
    tcphdr.th_flags &= ~(TH_RST | TH_SYN);
    tcphdr.th_flags |= TH_ACK;
  }

  std::string dat(reinterpret_cast<char *>(&tcphdr),
                  reinterpret_cast<char *>(&tcphdr) + sizeof(tcphdr));
  return dat;
}

std::string get_icmp6_hdr(const Icmp6Hdr &hdr) {
  struct icmp6_hdr icmp6_hdr = {
      .icmp6_type = static_cast<uint8_t>(hdr.icmp6_type()),
      .icmp6_code = static_cast<uint8_t>(hdr.icmp6_code()),
      .icmp6_cksum = 0,
  };
  icmp6_hdr.icmp6_dataun.icmp6_un_data32[0] = hdr.icmp6_dataun();

  std::string dat(reinterpret_cast<char *>(&icmp6_hdr),
                  reinterpret_cast<char *>(&icmp6_hdr) + sizeof(icmp6_hdr));
  return dat;
}

std::string get_ip6_route_hdr(const Ip6RtHdr &hdr) {
  struct ip6_rthdr ip6_rthdr = {
      .ip6r_nxt = static_cast<uint8_t>(hdr.ip6r_nxt()),
      .ip6r_len = static_cast<uint8_t>(hdr.ip6r_len()),
      .ip6r_type = static_cast<uint8_t>(hdr.ip6r_type()),
      .ip6r_segleft = static_cast<uint8_t>(hdr.ip6r_segleft()),
  };

  std::string dat(reinterpret_cast<char *>(&ip6_rthdr),
                  reinterpret_cast<char *>(&ip6_rthdr) + sizeof(ip6_rthdr));
  return dat;
}

std::string get_ip6_route0_hdr(const Ip6Rt0Hdr &hdr) {
  struct ip6_rthdr0 ip6_rthdr0 = {};
  ip6_rthdr0.ip6r0_nxt = hdr.ip6r0_nxt();
  ip6_rthdr0.ip6r0_len = hdr.ip6r0_len();
  ip6_rthdr0.ip6r0_type = hdr.ip6r0_type();
  ip6_rthdr0.ip6r0_segleft = hdr.ip6r0_segleft();
  ip6_rthdr0.ip6r0_reserved = hdr.ip6r0_reserved();
  *reinterpret_cast<uint32_t *>(&ip6_rthdr0.ip6r0_slmap[0]) = hdr.ip6r0_slmap();

  int i = 0;
  for (int in6addr : hdr.ip6r0_addr()) {
    if (i >= 23) {
      break;
    }

    get_in6_addr(&ip6_rthdr0.ip6r0_addr[i], static_cast<In6Addr>(in6addr));

    i++;
  }

  std::string dat(reinterpret_cast<char *>(&ip6_rthdr0),
                  reinterpret_cast<char *>(&ip6_rthdr0) + sizeof(ip6_rthdr0));
  return dat;
}

std::string get_ip6_frag_hdr(const Ip6FragHdr &hdr) {
  struct ip6_frag ip6_frag = {
      .ip6f_nxt = static_cast<uint8_t>(hdr.ip6f_nxt()),
      .ip6f_reserved = static_cast<uint8_t>(hdr.ip6f_reserved()),
      .ip6f_offlg = static_cast<uint16_t>(hdr.ip6f_offlg()),
      .ip6f_ident = hdr.ip6f_ident(),
  };

  std::string dat(reinterpret_cast<char *>(&ip6_frag),
                  reinterpret_cast<char *>(&ip6_frag) + sizeof(ip6_frag));
  return dat;
}

std::string get_ip6_ext(const Ip6Ext &hdr) {
  struct ip6_ext ip6_ext = {
      .ip6e_nxt = static_cast<uint8_t>(hdr.ip6e_nxt()),
      .ip6e_len = static_cast<uint8_t>(hdr.ip6e_len()),
  };

  std::string dat(reinterpret_cast<char *>(&ip6_ext),
                  reinterpret_cast<char *>(&ip6_ext) + sizeof(ip6_ext));
  return dat;
}

void get_in6_addrlifetime_64(struct in6_addrlifetime_64 *sai,
                             const In6AddrLifetime_64 &msg) {
  sai->ia6t_expire = msg.ia6t_expire();
  sai->ia6t_preferred = msg.ia6t_preferred();
  sai->ia6t_vltime = msg.ia6t_vltime();
  sai->ia6t_pltime = msg.ia6t_pltime();
}

void get_ifr_name(void *dest, const IfrName name) {
  switch (name) {
    case LO0: {
      memcpy(dest, "lo0", sizeof("lo0"));
      break;
    }
    case STF0: {
      memcpy(dest, "stf0", sizeof("stf0"));
      break;
    }
    case IPSEC0: {
      memcpy(dest, "ipsec0", sizeof("ipsec0"));
      break;
    }
    case UTUN0: {
      memcpy(dest, "utun0", sizeof("utun0"));
      break;
    }
  }
}

void DoTcpInput(const TcpPacket &tcp_packet) {
  std::string packet_s;

  size_t expected_size =
      sizeof(struct ip) + sizeof(struct tcphdr) + tcp_packet.data().size();
  packet_s += get_ip_hdr(tcp_packet.ip_hdr(), expected_size);
  packet_s += get_tcp_hdr(tcp_packet.tcp_hdr());
  packet_s += tcp_packet.data();
  assert(expected_size == packet_s.size());

  if (packet_s.empty()) {
    return;
  }

  // TODO(nedwill): fuzz structure of mbuf itself
  void *mbuf_data = get_mbuf_data(packet_s.data(), packet_s.size(), PKTF_LOOP);
  if (!mbuf_data) {
    return;
  }

  ip_input_wrapper(mbuf_data);
}

void DoTcp6Input(const Tcp6Packet &tcp6_packet) {
  std::string packet_s;

  // TODO(nedwill): support hop-by-hop and other options
  size_t expected_size = sizeof(struct tcphdr) + tcp6_packet.data().size();
  packet_s += get_ip6_hdr(tcp6_packet.ip6_hdr(), expected_size);
  packet_s += get_tcp_hdr(tcp6_packet.tcp_hdr());
  packet_s += tcp6_packet.data();

  if (packet_s.empty()) {
    return;
  }

  void *mbuf_data = get_mbuf_data(packet_s.data(), packet_s.size(), PKTF_LOOP);
  if (!mbuf_data) {
    return;
  }

  ip6_input_wrapper(mbuf_data);
}

void DoIp4Packet(const Ip4Packet &packet) {
  size_t expected_size = sizeof(struct ip) + packet.data().size();
  std::string packet_s = get_ip_hdr(packet.ip_hdr(), expected_size);
  packet_s += packet.data();

  void *mbuf_data = get_mbuf_data(packet_s.data(), packet_s.size(), PKTF_LOOP);
  if (!mbuf_data) {
    return;
  }

  ip_input_wrapper(mbuf_data);
}

void DoIp6Packet(const Ip6Packet &packet) {
  size_t expected_size = packet.data().size();
  std::string packet_s = get_ip6_hdr(packet.ip6_hdr(), expected_size);
  packet_s += packet.data();

  void *mbuf_data = get_mbuf_data(packet_s.data(), packet_s.size(), PKTF_LOOP);
  if (!mbuf_data) {
    return;
  }

  ip6_input_wrapper(mbuf_data);
}

void DoIpInput(const Packet &packet) {
  switch (packet.packet_case()) {
    case Packet::kTcpPacket: {
      DoTcpInput(packet.tcp_packet());
      break;
    }
    case Packet::kTcp6Packet: {
      DoTcp6Input(packet.tcp6_packet());
      break;
    }
    case Packet::kIp4Packet: {
      DoIp4Packet(packet.ip4_packet());
      break;
    }
    case Packet::kIp6Packet: {
      DoIp6Packet(packet.ip6_packet());
      break;
    }
    case Packet::kRawIp4: {
      void *mbuf_data = get_mbuf_data(packet.raw_ip4().data(),
                                      packet.raw_ip4().size(), PKTF_LOOP);
      if (!mbuf_data) {
        return;
      }

      ip_input_wrapper(mbuf_data);
      break;
    }
    case Packet::kRawIp6: {
      void *mbuf_data = get_mbuf_data(packet.raw_ip6().data(),
                                      packet.raw_ip6().size(), PKTF_LOOP);
      if (!mbuf_data) {
        return;
      }

      ip6_input_wrapper(mbuf_data);
      break;
    }
    case Packet::PACKET_NOT_SET: {
      break;
    }
  }
}
