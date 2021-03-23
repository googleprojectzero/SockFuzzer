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

#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <iostream>
#include <memory>
#include <vector>

#include "net_fuzzer.pb.h"
#include "src/libfuzzer/libfuzzer_macro.h"

extern "C" {
#include "api/backend.h"
#include "api/syscall_wrappers.h"
#include "types.h"
}

/*
TODO(nedwill)

Fuzz vsock domain
*/

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
      *sai = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (uint8_t)addr};
      assert(IN6_IS_ADDR_LOOPBACK(sai));
      break;
    }
    case IN6_ADDR_REAL:
    case MAYBE_LOCALHOST: {
      *sai = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (uint8_t)addr};
      break;
    }
    case IN6_ADDR_V4COMPAT: {
      sai->s6_addr[12] = 1;
      assert(IN6_IS_ADDR_V4COMPAT(sai));
      break;
    }
    case IN6_ADDR_V4MAPPED: {
      *(uint32_t *)&sai->s6_addr[8] = 0xffff0000;
      assert(IN6_IS_ADDR_V4MAPPED(sai));
      break;
    }
    case IN6_ADDR_6TO4: {
      sai->s6_addr16[0] = ntohs(0x2002);
      assert(IN6_IS_ADDR_6TO4(sai));
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
  sai->sin6_family = (sa_family_t)AF_INET6;  // sa6.family();
  sai->sin6_port = (in_port_t)sa6.port();
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
          .sa_len = (uint8_t)(sizeof(sockaddr_generic) + sag.sa_data().size()),
          .sa_family = (uint8_t)sag.sa_family(),
      };

      dat = std::string((char *)&sag_s, (char *)&sag_s + sizeof(sag_s));
      dat += sag.sa_data();
      break;
    }
    case SockAddr::kSockaddr4: {
      struct sockaddr_in sai = {
          .sin_len = sizeof(struct sockaddr_in),
          .sin_family =
              AF_INET,  // (unsigned char)sockaddr.sockaddr4().sin_family(),
          .sin_port = (unsigned short)sockaddr.sockaddr4().sin_port(),
          .sin_addr = {(unsigned int)sockaddr.sockaddr4().sin_addr()},
          .sin_zero = {},
      };
      dat = std::string((char *)&sai, (char *)&sai + sizeof(sai));
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
  std::string dat((char *)&ip6_hdr, (char *)&ip6_hdr + sizeof(ip6_hdr));
  return dat;
}

std::string get_ip_hdr(const IpHdr &hdr, size_t expected_size) {
  struct in_addr ip_src = {.s_addr = (unsigned int)hdr.ip_src()};
  struct in_addr ip_dst = {.s_addr = (unsigned int)hdr.ip_dst()};
  struct ip ip_hdr = {
      .ip_hl = 5,    // TODO(nedwill): support options // hdr.ip_hl(),
      .ip_v = IPV4,  // hdr.ip_v(),
      .ip_tos = (u_char)hdr.ip_tos(),
      .ip_len = (u_short)__builtin_bswap16(expected_size),
      .ip_id = (u_short)hdr.ip_id(),
      .ip_off = (u_short)hdr.ip_off(),
      .ip_ttl = (u_char)hdr.ip_ttl(),
      .ip_p = (u_char)hdr.ip_p(),
      .ip_sum = 0,
      .ip_src = ip_src,
      .ip_dst = ip_dst,
  };
  std::string dat((char *)&ip_hdr, (char *)&ip_hdr + sizeof(ip_hdr));
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
      .th_sport = (unsigned short)hdr.th_sport(),
      .th_dport = (unsigned short)hdr.th_dport(),
      .th_seq = __builtin_bswap32(hdr.th_seq()),
      .th_ack = __builtin_bswap32(hdr.th_ack()),
      .th_off = hdr.th_off(),
      .th_flags = 0,
      .th_win = (unsigned short)hdr.th_win(),
      .th_sum = 0,
      .th_urp = (unsigned short)hdr.th_urp(),
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

  std::string dat((char *)&tcphdr, (char *)&tcphdr + sizeof(tcphdr));
  return dat;
}

std::string get_icmp6_hdr(const Icmp6Hdr &hdr) {
  struct icmp6_hdr icmp6_hdr = {
      .icmp6_type = (uint8_t)hdr.icmp6_type(),
      .icmp6_code = (uint8_t)hdr.icmp6_code(),
      .icmp6_cksum = 0,
  };
  icmp6_hdr.icmp6_dataun.icmp6_un_data32[0] = hdr.icmp6_dataun();

  std::string dat((char *)&icmp6_hdr, (char *)&icmp6_hdr + sizeof(icmp6_hdr));
  return dat;
}

std::string get_ip6_route_hdr(const Ip6RtHdr &hdr) {
  struct ip6_rthdr ip6_rthdr = {
      .ip6r_nxt = (uint8_t)hdr.ip6r_nxt(),
      .ip6r_len = (uint8_t)hdr.ip6r_len(),
      .ip6r_type = (uint8_t)hdr.ip6r_type(),
      .ip6r_segleft = (uint8_t)hdr.ip6r_segleft(),
  };

  std::string dat((char *)&ip6_rthdr, (char *)&ip6_rthdr + sizeof(ip6_rthdr));
  return dat;
}

std::string get_ip6_route0_hdr(const Ip6Rt0Hdr &hdr) {
  struct ip6_rthdr0 ip6_rthdr0 = {};
  ip6_rthdr0.ip6r0_nxt = hdr.ip6r0_nxt();
  ip6_rthdr0.ip6r0_len = hdr.ip6r0_len();
  ip6_rthdr0.ip6r0_type = hdr.ip6r0_type();
  ip6_rthdr0.ip6r0_segleft = hdr.ip6r0_segleft();
  ip6_rthdr0.ip6r0_reserved = hdr.ip6r0_reserved();
  *(uint32_t *)&ip6_rthdr0.ip6r0_slmap[0] = hdr.ip6r0_slmap();

  int i = 0;
  for (int in6addr : hdr.ip6r0_addr()) {
    if (i >= 23) {
      break;
    }

    get_in6_addr(&ip6_rthdr0.ip6r0_addr[i], (In6Addr)in6addr);

    i++;
  }

  std::string dat((char *)&ip6_rthdr0,
                  (char *)&ip6_rthdr0 + sizeof(ip6_rthdr0));
  return dat;
}

std::string get_ip6_frag_hdr(const Ip6FragHdr &hdr) {
  struct ip6_frag ip6_frag = {
      .ip6f_nxt = (uint8_t)hdr.ip6f_nxt(),
      .ip6f_reserved = (uint8_t)hdr.ip6f_reserved(),
      .ip6f_offlg = (uint16_t)hdr.ip6f_offlg(),
      .ip6f_ident = hdr.ip6f_ident(),
  };

  std::string dat((char *)&ip6_frag, (char *)&ip6_frag + sizeof(ip6_frag));
  return dat;
}

std::string get_ip6_ext(const Ip6Ext &hdr) {
  struct ip6_ext ip6_ext = {
      .ip6e_nxt = (uint8_t)hdr.ip6e_nxt(),
      .ip6e_len = (uint8_t)hdr.ip6e_len(),
  };

  std::string dat((char *)&ip6_ext, (char *)&ip6_ext + sizeof(ip6_ext));
  return dat;
}

std::string GetNecpClient(const NecpClientId &necp_client_id) {
  switch (necp_client_id) {
    case CLIENT_0: {
      return "0000000000000000";
    }
    case CLIENT_1: {
      return "1111111111111111";
    }
    case CLIENT_2: {
      return "2222222222222222";
    }
  }
  assert(false);
  return "";
}

extern "C" {

static FuzzedDataProvider *fdp = nullptr;

// These are callbacks to let the C-based backend access the fuzzed input
// stream.
void get_fuzzed_bytes(void *addr, size_t bytes) {
  // If we didn't initialize the fdp just clear the bytes.
  if (!fdp) {
    memset(addr, 0, bytes);
    return;
  }
  memset(addr, 0, bytes);
  std::vector<uint8_t> dat = fdp->ConsumeBytes<uint8_t>(bytes);
  memcpy(addr, dat.data(), dat.size());
}

bool get_fuzzed_bool(void) {
  // If we didn't initialize the fdp just return false.
  if (!fdp) {
    return false;
  }
  return fdp->ConsumeBool();
}

int get_fuzzed_int32(int low, int high) {
  return fdp->ConsumeIntegralInRange<int>(low, high);
}

unsigned int get_fuzzed_uint32(unsigned int low, unsigned int high) {
  return fdp->ConsumeIntegralInRange<unsigned int>(low, high);
}

unsigned int get_remaining_bytes() { return fdp->remaining_bytes(); }

static bool ready = false;

bool initialize_network(void);

extern unsigned long ioctls[];
extern int num_ioctls;
extern const unsigned long siocaifaddr_in6_64;
extern const unsigned long siocsifflags;

// Enable this when copyout should work.
extern bool real_copyout;

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
  }
}

// NECP client wrappers
// TODO(nedwill): move these to their own file
void necp_client_add(int fd, NecpClientId client_id, unsigned char *data,
                     size_t size) {
  std::string client_id_s = GetNecpClient(client_id);
  int retval = 0;
  necp_client_action_wrapper(fd, NECP_CLIENT_ACTION_ADD,
                             // parameters
                             (unsigned char *)client_id_s.data(),
                             client_id_s.size(), data, size, &retval);
}

// TODO(nedwill): support flow_ifnet_stats
void necp_client_remove(int fd, NecpClientId client_id) {
  std::string client_id_s = GetNecpClient(client_id);
  int retval = 0;
  necp_client_action_wrapper(fd, NECP_CLIENT_ACTION_REMOVE,
                             (unsigned char *)client_id_s.data(),
                             client_id_s.size(), nullptr, 0, &retval);
}

void necp_client_copy_parameters(int fd, NecpClientId client_id,
                                 uint32_t copyout_size) {
  std::string client_id_s = GetNecpClient(client_id);
  copyout_size %= 4096;
  std::unique_ptr<uint8_t[]> copyout_buffer(new uint8_t[copyout_size]);
  int retval = 0;
  necp_client_action_wrapper(fd, NECP_CLIENT_ACTION_COPY_PARAMETERS,
                             (unsigned char *)client_id_s.data(),
                             client_id_s.size(), copyout_buffer.get(),
                             copyout_size, &retval);
}

void necp_client_agent(
    int fd, NecpClientId client_id,
    const ::google::protobuf::RepeatedPtrField<::NecpTlv> &necp_tlv) {
  std::string client_id_s = GetNecpClient(client_id);
  std::string parameters;
  for (const NecpTlv &tlv : necp_tlv) {
    // std::string dat((char *)&icmp6_hdr, (char *)&icmp6_hdr +
    // sizeof(icmp6_hdr));
    struct necp_tlv_header header = {
        .type = (uint8_t)tlv.necp_type(),
        .length = (uint32_t)tlv.data().size(),
    };
    std::string tlv_s((char *)&header, (char *)&header + sizeof(header));
    tlv_s += tlv.data();
    parameters += tlv_s;
  }
  int retval = 0;
  necp_client_action_wrapper(fd, NECP_CLIENT_ACTION_AGENT,
                             (unsigned char *)client_id_s.data(),
                             client_id_s.size(), (uint8_t *)parameters.data(),
                             parameters.size(), &retval);
}

void DoNecpClientAction(const NecpClientAction &necp_client_action) {
  switch (necp_client_action.action_case()) {
    case NecpClientAction::kAdd: {
      necp_client_add(necp_client_action.necp_fd(),
                      necp_client_action.client_id(),
                      (unsigned char *)necp_client_action.add().buffer().data(),
                      necp_client_action.add().buffer().size());
      break;
    }
    case NecpClientAction::kRemove: {
      necp_client_remove(necp_client_action.necp_fd(),
                         necp_client_action.client_id());
      break;
    }
    case NecpClientAction::kCopyParameters: {
      necp_client_copy_parameters(
          necp_client_action.necp_fd(), necp_client_action.client_id(),
          necp_client_action.copy_parameters().copyout_size());
      break;
    }
    case NecpClientAction::kAgent: {
      necp_client_agent(necp_client_action.necp_fd(),
                        necp_client_action.client_id(),
                        necp_client_action.agent().necp_tlv());
      break;
    }
    case NecpClientAction::ACTION_NOT_SET: {
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

// TODO(nedwill): make alternative build of this function that runs the
// the testcases against the real XNU syscalls, also KCOV-enabled
DEFINE_BINARY_PROTO_FUZZER(const Session &session) {
  // std::string str;
  // google::protobuf::TextFormat::PrintToString(session, &str);
  // std::cout << str;
  if (!ready) {
    initialize_network();
    init_proc();
    ready = true;
  }

  FuzzedDataProvider dp((const uint8_t *)session.data_provider().data(),
                        session.data_provider().size());
  fdp = &dp;

  // TODO(nedwill): Make these containers own the references to their
  // objects so that we can use RAII to avoid leaks.
  std::vector<uint32_t> cids;
  std::set<int> open_fds;

  for (const Command &command : session.commands()) {
    int retval = 0;
    switch (command.command_case()) {
      case Command::kSocket: {
        int fd = 0;
        int err = socket_wrapper(command.socket().domain(),
                                 command.socket().so_type(),
                                 command.socket().protocol(), &fd);
        if (err == 0) {
          // Make sure we're tracking fds properly.
          if (open_fds.find(fd) != open_fds.end()) {
            printf("Found existing fd %d\n", fd);
            assert(false);
          }
          open_fds.insert(fd);
        }
        break;
      }
      case Command::kClose: {
        open_fds.erase(command.close().fd());
        close_wrapper(command.close().fd(), nullptr);
        break;
      }
      case Command::kSetSockOpt: {
        int s = command.set_sock_opt().fd();
        int level = command.set_sock_opt().level();
        int name = command.set_sock_opt().name();
        size_t size = command.set_sock_opt().val().size();
        std::unique_ptr<char[]> val(new char[size]);
        memcpy(val.get(), command.set_sock_opt().val().data(), size);
        setsockopt_wrapper(s, level, name, val.get(), size, nullptr);
        break;
      }
      case Command::kGetSockOpt: {
        int s = command.get_sock_opt().fd();
        int level = command.get_sock_opt().level();
        int name = command.get_sock_opt().name();
        socklen_t size = command.get_sock_opt().size();
        if (size < 0 || size > 4096) {
          break;
        }
        std::unique_ptr<char[]> val(new char[size]);
        getsockopt_wrapper(s, level, name, val.get(), &size, nullptr);
        break;
      }
      case Command::kBind: {
        std::string sockaddr_s = get_sockaddr(command.bind().sockaddr());
        bind_wrapper(command.bind().fd(), (caddr_t)sockaddr_s.data(),
                     sockaddr_s.size(), nullptr);
        break;
      }
      case Command::kIoctl: {
        // TODO: pick these values more efficiently
        // XXX: these mutate global state
        uint32_t fd = command.ioctl().fd();
        uint32_t com = ioctls[command.ioctl().ioctl_idx() - 1];
        real_copyout = false;
        ioctl_wrapper(fd, com, /*data=*/(caddr_t)1, nullptr);
        real_copyout = true;
        break;
      }
      case Command::kAccept: {
        std::string sockaddr_s = get_sockaddr(command.accept().sockaddr());
        socklen_t size = sockaddr_s.size();
        int retval = 0;
        accept_wrapper(command.accept().fd(), (caddr_t)sockaddr_s.data(), &size,
                       &retval);
        break;
      }
      case Command::kIpInput: {
        DoIpInput(command.ip_input());
        break;
      }
      case Command::kIoctlReal: {
        switch (command.ioctl_real().ioctl_case()) {
          case IoctlReal::kSiocaifaddrIn664: {
            const In6_AliasReq_64 &req =
                command.ioctl_real().siocaifaddr_in6_64();
            struct in6_aliasreq_64 alias = {};
            memcpy(alias.ifra_name, req.ifra_name().data(),
                   std::min(req.ifra_name().size(), sizeof(alias.ifra_name)));
            get_sockaddr6(&alias.ifra_addr, req.ifra_addr());
            get_sockaddr6(&alias.ifra_dstaddr, req.ifra_dstaddr());
            get_sockaddr6(&alias.ifra_prefixmask, req.ifra_prefixmask());
            for (int flag : req.ifra_flags()) {
              // make mutations that dupe a flag more useful by xoring
              alias.ifra_flags ^= flag;
            }
            get_in6_addrlifetime_64(&alias.ifra_lifetime, req.ifra_lifetime());
            ioctl_wrapper(command.ioctl_real().fd(), siocaifaddr_in6_64,
                          (caddr_t)&alias, nullptr);
          }
          case IoctlReal::kSiocsifflags: {
            struct ifreq ifreq = {};
            for (int flag : command.ioctl_real().siocsifflags().flags()) {
              ifreq.ifr_flags |= flag;
            }
            get_ifr_name(ifreq.ifr_name, LO0);
            ioctl_wrapper(command.ioctl_real().fd(), siocsifflags,
                          (caddr_t)&ifreq, nullptr);
            break;
          }
          case IoctlReal::IOCTL_NOT_SET: {
            break;
          }
        }
      }
      case Command::kConnectx: {
        bool has_srcaddr = command.connectx().endpoints().has_sae_srcaddr();

        std::string srcaddr_s;
        if (has_srcaddr) {
          srcaddr_s =
              get_sockaddr(command.connectx().endpoints().sae_srcaddr());
        }

        std::string dstaddr_s =
            get_sockaddr(command.connectx().endpoints().sae_dstaddr());

        void *srcaddr = (void *)srcaddr_s.data();
        uint32_t srcsize = srcaddr_s.size();
        if (!has_srcaddr) {
          srcaddr = nullptr;
          assert(!srcsize);
        }

        void *dstaddr = (void *)dstaddr_s.data();
        uint32_t dstsize = dstaddr_s.size();

        // We ignore failure here since it's ok to try to send things regardless
        uint32_t connectx_flags = 0;
        for (const int flag : command.connectx().flags()) {
          connectx_flags |= flag;
        }
        uint32_t cid = 0;

        struct user64_sa_endpoints endpoints = {
            .sae_srcif = static_cast<unsigned int>(command.connectx().endpoints().sae_srcif()),
            .sae_srcaddr = (user64_addr_t)srcaddr,
            .sae_srcaddrlen = srcsize,
            .sae_dstaddr = (user64_addr_t)dstaddr,
            .sae_dstaddrlen = dstsize};

        // TODO(nedwill): is this a return value?
        size_t len = 0;
        // TODO(nedwill): add IOV mocking
        connectx_wrapper(command.connectx().socket(), &endpoints,
                         command.connectx().associd(), connectx_flags, nullptr,
                         0, &len, &cid, nullptr);
        cids.push_back(cid);
        break;
      }
      case Command::kConnect: {
        std::string sockaddr_s = get_sockaddr(command.connect().sockaddr());
        connect_wrapper(command.connect().fd(), (caddr_t)sockaddr_s.data(),
                        sockaddr_s.size(), nullptr);
        break;
      }
      case Command::kListen: {
        listen_wrapper(command.listen().socket(), command.listen().backlog(),
                       nullptr);
        break;
      }
      case Command::kDisconnectx: {
        uint32_t cid = 0;
        if (!cids.empty()) {
          cid = cids[command.disconnectx().cid() % cids.size()];
        } else {
          cid = command.disconnectx().cid();
        }
        disconnectx_wrapper(command.disconnectx().fd(),
                            command.disconnectx().associd(), cid, nullptr);
        break;
      }
      case Command::kClearAll: {
        // TODO(nedwill): finer-grained calling of clear_all functions here
        clear_all();
        break;
      }
      case Command::kNecpMatchPolicy: {
        std::unique_ptr<uint8_t[]> parameters_u8(
            new uint8_t[command.necp_match_policy().parameters().size()]);
        memcpy(parameters_u8.get(),
               command.necp_match_policy().parameters().data(),
               command.necp_match_policy().parameters().size());
        // necp_match_policy_wrapper(
        //     parameters_u8.get(),
        //     command.necp_match_policy().parameters().size(),
        //     /*returned_result*/ nullptr, nullptr);
        break;
      }
      case Command::kNecpOpen: {
        // int flags = 0;
        // for (int flag : command.necp_open().flags()) {
        //   flags |= flag;
        // }
        // int fd = 0;
        // int err = necp_open_wrapper(flags, &fd);
        // if (err == 0) {
        //   if (open_fds.find(fd) != open_fds.end()) {
        //     printf("fd %d already in open sockets\n", fd);
        //     assert(false);
        //   }
        //   open_fds.insert(fd);
        // }
        break;
      }
      case Command::kNecpClientAction: {
        // DoNecpClientAction(command.necp_client_action());
        break;
      }
      case Command::kNecpSessionOpen: {
        // int flags = 0;
        // int fd = 0;
        // int err = necp_session_open_wrapper(flags, &fd);
        // if (err == 0) {
        //   if (open_fds.find(fd) != open_fds.end()) {
        //     printf("fd %d already in open sockets\n", fd);
        //     assert(false);
        //   }
        //   open_fds.insert(fd);
        // }
        break;
      }
      case Command::kNecpSessionAction: {
        size_t out_buffer_size =
            command.necp_session_action().out_buffer_size() % 4096;
        std::unique_ptr<uint8_t[]> out_buffer(new uint8_t[out_buffer_size]);
        // necp_session_action_wrapper(
        //     command.necp_session_action().necp_fd(),
        //     command.necp_session_action().action(),
        //     // TODO(nedwill): fix const cast
        //     (uint8_t *)command.necp_session_action().in_buffer().data(),
        //     command.necp_session_action().in_buffer().size(), out_buffer.get(),
        //     out_buffer_size, &retval);
        break;
      }
      case Command::kAcceptNocancel: {
        std::string sockaddr_s = get_sockaddr(command.accept_nocancel().name());
        socklen_t size = sockaddr_s.size();
        accept_nocancel_wrapper(command.accept_nocancel().s(),
                                (caddr_t)sockaddr_s.data(), &size, &retval);
        break;
      }
      case Command::kConnectNocancel: {
        std::string sockaddr_s =
            get_sockaddr(command.connect_nocancel().name());
        socklen_t size = sockaddr_s.size();
        connect_nocancel_wrapper(command.connect_nocancel().s(),
                                 (caddr_t)sockaddr_s.data(), size, &retval);
        break;
      }
      case Command::kGetpeername: {
        std::string sockaddr_s = get_sockaddr(command.getpeername().asa());
        socklen_t size = sockaddr_s.size();
        getpeername_wrapper(command.getpeername().fdes(),
                            (caddr_t)sockaddr_s.data(), &size, &retval);
        break;
      }
      case Command::kGetsockname: {
        std::string sockaddr_s = get_sockaddr(command.getsockname().asa());
        socklen_t size = sockaddr_s.size();
        getsockname_wrapper(command.getsockname().fdes(),
                            (caddr_t)sockaddr_s.data(), &size, &retval);
        break;
      }
      case Command::kPeeloff: {
        peeloff_wrapper(command.peeloff().s(), command.peeloff().aid(),
                        &retval);
        break;
      }
      case Command::kRecvfrom: {
        std::string sockaddr_s = get_sockaddr(command.recvfrom().from());
        int size = sockaddr_s.size();
        // TODO(nedwill): just specify the size of the buffer, don't store bytes
        // in the proto message just for them to be overwritten
        recvfrom_wrapper(
            command.recvfrom().s(), (caddr_t)command.recvfrom().buf().data(),
            command.recvfrom().buf().size(), command.recvfrom().flags(),
            (struct sockaddr *)sockaddr_s.data(), &size, &retval);
        break;
      }
      case Command::kRecvfromNocancel: {
        std::string sockaddr_s =
            get_sockaddr(command.recvfrom_nocancel().from());
        int size = sockaddr_s.size();
        recvfrom_nocancel_wrapper(
            command.recvfrom_nocancel().s(),
            (caddr_t)command.recvfrom_nocancel().buf().data(),
            command.recvfrom_nocancel().buf().size(),
            command.recvfrom_nocancel().flags(),
            (struct sockaddr *)sockaddr_s.data(), &size, &retval);
        break;
      }
      case Command::kRecvmsg: {
        // TODO(nedwill): fuzz this msg field
        user64_msghdr msg = {};
        recvmsg_wrapper(command.recvmsg().s(), (struct msghdr *)&msg,
                        command.recvmsg().flags(), &retval);
        break;
      }
      case Command::kSendto: {
        std::string sockaddr_s = get_sockaddr(command.sendto().to());
        socklen_t size = sockaddr_s.size();
        sendto_wrapper(command.sendto().s(),
                       (caddr_t)command.sendto().buf().data(),
                       command.sendto().buf().size(), command.sendto().flags(),
                       (caddr_t)sockaddr_s.data(), size, &retval);
        break;
      }
      case Command::kSocketpair: {
        int rsv[2] = {};
        int ret = socketpair_wrapper(
            command.socketpair().domain(), command.socketpair().type(),
            command.socketpair().protocol(), rsv, &retval);
        if (!ret) {
          if (open_fds.find(rsv[0]) != open_fds.end()) {
            assert(false);
          }
          open_fds.insert(rsv[0]);
          if (open_fds.find(rsv[1]) != open_fds.end()) {
            assert(false);
          }
          open_fds.insert(rsv[1]);
        }
        break;
      }
      case Command::kPipe: {
        int rsv[2] = {};
        int ret = pipe_wrapper(rsv);
        if (!ret) {
          if (open_fds.find(rsv[0]) != open_fds.end()) {
            assert(false);
          }
          open_fds.insert(rsv[0]);
          if (open_fds.find(rsv[1]) != open_fds.end()) {
            assert(false);
          }
          open_fds.insert(rsv[1]);
        }
        break;
      }
      case Command::kShutdown: {
        shutdown_wrapper(command.shutdown().s(), command.shutdown().how(),
                         &retval);
        break;
      }
      case Command::COMMAND_NOT_SET: {
        break;
      }
    }
  }

  for (int fd : open_fds) {
    int err = close_wrapper(fd, nullptr);
    assert(err != EBADF);
  }

  // TODO(nedwill): split up these worker threads and run them as
  // part of main loop
  clear_all();
}
}
