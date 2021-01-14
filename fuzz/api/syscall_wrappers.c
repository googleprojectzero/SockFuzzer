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

#include "fuzz/api/syscall_wrappers.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-conversion"

__attribute__((visibility("default"))) int accept_wrapper(int s, caddr_t name,
                                                          socklen_t* anamelen,
                                                          int* retval) {
  struct accept_args uap = {
      .s = s,
      .name = name,
      .anamelen = anamelen,
  };
  return accept(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int accept_nocancel_wrapper(
    int s, caddr_t name, socklen_t* anamelen, int* retval) {
  struct accept_nocancel_args uap = {
      .s = s,
      .name = name,
      .anamelen = anamelen,
  };
  return accept_nocancel(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int bind_wrapper(int s, caddr_t name,
                                                        socklen_t namelen,
                                                        int* retval) {
  struct bind_args uap = {
      .s = s,
      .name = name,
      .namelen = namelen,
  };
  return bind(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int close_wrapper(int fd, int* retval) {
  struct close_args uap = {
      .fd = fd,
  };
  return sys_close(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int connect_wrapper(int s, caddr_t name,
                                                           socklen_t namelen,
                                                           int* retval) {
  struct connect_args uap = {
      .s = s,
      .name = name,
      .namelen = namelen,
  };
  return connect(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int connect_nocancel_wrapper(
    int s, caddr_t name, socklen_t namelen, int* retval) {
  struct connect_nocancel_args uap = {
      .s = s,
      .name = name,
      .namelen = namelen,
  };
  return connect_nocancel(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int connectx_wrapper(
    int socket, const sa_endpoints_t* endpoints, sae_associd_t associd,
    unsigned int flags, const struct iovec* iov, unsigned int iovcnt,
    size_t* len, sae_connid_t* connid, int* retval) {
  struct connectx_args uap = {
      .socket = socket,
      .endpoints = endpoints,
      .associd = associd,
      .flags = flags,
      .iov = iov,
      .iovcnt = iovcnt,
      .len = len,
      .connid = connid,
  };
  return connectx(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int disconnectx_wrapper(
    int s, sae_associd_t aid, sae_connid_t cid, int* retval) {
  struct disconnectx_args uap = {
      .s = s,
      .aid = aid,
      .cid = cid,
  };
  return disconnectx(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int getpeername_wrapper(int fdes,
                                                               caddr_t asa,
                                                               socklen_t* alen,
                                                               int* retval) {
  struct getpeername_args uap = {
      .fdes = fdes,
      .asa = asa,
      .alen = alen,
  };
  return getpeername(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int getsockname_wrapper(int fdes,
                                                               caddr_t asa,
                                                               socklen_t* alen,
                                                               int* retval) {
  struct getsockname_args uap = {
      .fdes = fdes,
      .asa = asa,
      .alen = alen,
  };
  return getsockname(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int getsockopt_wrapper(
    int s, int level, int name, caddr_t val, socklen_t* avalsize, int* retval) {
  struct getsockopt_args uap = {
      .s = s,
      .level = level,
      .name = name,
      .val = val,
      .avalsize = avalsize,
  };
  return getsockopt(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int ioctl_wrapper(int fd, u_long com,
                                                         caddr_t data,
                                                         int* retval) {
  struct ioctl_args uap = {
      .fd = fd,
      .com = com,
      .data = data,
  };
  return ioctl(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int listen_wrapper(int s, int backlog,
                                                          int* retval) {
  struct listen_args uap = {
      .s = s,
      .backlog = backlog,
  };
  return listen(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int necp_client_action_wrapper(
    int necp_fd, uint32_t action, uuid_t client_id, size_t client_id_len,
    uint8_t* buffer, size_t buffer_size, int* retval) {
  struct necp_client_action_args uap = {
      .necp_fd = necp_fd,
      .action = action,
      .client_id = client_id,
      .client_id_len = client_id_len,
      .buffer = buffer,
      .buffer_size = buffer_size,
  };
  return necp_client_action(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int necp_match_policy_wrapper(
    uint8_t* parameters, size_t parameters_size,
    struct necp_aggregate_result* returned_result, int* retval) {
  struct necp_match_policy_args uap = {
      .parameters = parameters,
      .parameters_size = parameters_size,
      .returned_result = returned_result,
  };
  return necp_match_policy(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int necp_open_wrapper(int flags,
                                                             int* retval) {
  struct necp_open_args uap = {
      .flags = flags,
  };
  return necp_open(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int necp_session_action_wrapper(
    int necp_fd, uint32_t action, uint8_t* in_buffer, size_t in_buffer_length,
    uint8_t* out_buffer, size_t out_buffer_length, int* retval) {
  struct necp_session_action_args uap = {
      .necp_fd = necp_fd,
      .action = action,
      .in_buffer = in_buffer,
      .in_buffer_length = in_buffer_length,
      .out_buffer = out_buffer,
      .out_buffer_length = out_buffer_length,
  };
  return necp_session_action(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int necp_session_open_wrapper(
    int flags, int* retval) {
  struct necp_session_open_args uap = {
      .flags = flags,
  };
  return necp_session_open(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int peeloff_wrapper(int s,
                                                           sae_associd_t aid,
                                                           int* retval) {
  struct peeloff_args uap = {
      .s = s,
      .aid = aid,
  };
  return peeloff(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int pipe_wrapper(int* retval) {
  struct pipe_args uap = {};
  return pipe(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int recvfrom_wrapper(
    int s, void* buf, size_t len, int flags, struct sockaddr* from,
    int* fromlenaddr, int* retval) {
  struct recvfrom_args uap = {
      .s = s,
      .buf = buf,
      .len = len,
      .flags = flags,
      .from = from,
      .fromlenaddr = fromlenaddr,
  };
  return recvfrom(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int recvfrom_nocancel_wrapper(
    int s, void* buf, size_t len, int flags, struct sockaddr* from,
    int* fromlenaddr, int* retval) {
  struct recvfrom_nocancel_args uap = {
      .s = s,
      .buf = buf,
      .len = len,
      .flags = flags,
      .from = from,
      .fromlenaddr = fromlenaddr,
  };
  return recvfrom_nocancel(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int recvmsg_wrapper(int s,
                                                           struct msghdr* msg,
                                                           int flags,
                                                           int* retval) {
  struct recvmsg_args uap = {
      .s = s,
      .msg = msg,
      .flags = flags,
  };
  return recvmsg(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int recvmsg_nocancel_wrapper(
    int s, struct msghdr* msg, int flags, int* retval) {
  struct recvmsg_nocancel_args uap = {
      .s = s,
      .msg = msg,
      .flags = flags,
  };
  return recvmsg_nocancel(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int recvmsg_x_wrapper(
    int s, struct msghdr_x* msgp, u_int cnt, int flags, user_ssize_t* retval) {
  struct recvmsg_x_args uap = {
      .s = s,
      .msgp = msgp,
      .cnt = cnt,
      .flags = flags,
  };
  return recvmsg_x(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int sendmsg_wrapper(int s, caddr_t msg,
                                                           int flags,
                                                           int* retval) {
  struct sendmsg_args uap = {
      .s = s,
      .msg = msg,
      .flags = flags,
  };
  return sendmsg(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int sendmsg_nocancel_wrapper(
    int s, caddr_t msg, int flags, int* retval) {
  struct sendmsg_nocancel_args uap = {
      .s = s,
      .msg = msg,
      .flags = flags,
  };
  return sendmsg_nocancel(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int sendmsg_x_wrapper(
    int s, struct msghdr_x* msgp, u_int cnt, int flags, user_ssize_t* retval) {
  struct sendmsg_x_args uap = {
      .s = s,
      .msgp = msgp,
      .cnt = cnt,
      .flags = flags,
  };
  return sendmsg_x(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int sendto_wrapper(int s, caddr_t buf,
                                                          size_t len, int flags,
                                                          caddr_t to,
                                                          socklen_t tolen,
                                                          int* retval) {
  struct sendto_args uap = {
      .s = s,
      .buf = buf,
      .len = len,
      .flags = flags,
      .to = to,
      .tolen = tolen,
  };
  return sendto(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int sendto_nocancel_wrapper(
    int s, caddr_t buf, size_t len, int flags, caddr_t to, socklen_t tolen,
    int* retval) {
  struct sendto_nocancel_args uap = {
      .s = s,
      .buf = buf,
      .len = len,
      .flags = flags,
      .to = to,
      .tolen = tolen,
  };
  return sendto_nocancel(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int setsockopt_wrapper(
    int s, int level, int name, caddr_t val, socklen_t valsize, int* retval) {
  struct setsockopt_args uap = {
      .s = s,
      .level = level,
      .name = name,
      .val = val,
      .valsize = valsize,
  };
  return setsockopt(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int shutdown_wrapper(int s, int how,
                                                            int* retval) {
  struct shutdown_args uap = {
      .s = s,
      .how = how,
  };
  return shutdown(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int socket_wrapper(int domain, int type,
                                                          int protocol,
                                                          int* retval) {
  struct socket_args uap = {
      .domain = domain,
      .type = type,
      .protocol = protocol,
  };
  return socket(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int socket_delegate_wrapper(
    int domain, int type, int protocol, pid_t epid, int* retval) {
  struct socket_delegate_args uap = {
      .domain = domain,
      .type = type,
      .protocol = protocol,
      .epid = epid,
  };
  return socket_delegate(kernproc, &uap, retval);
}

__attribute__((visibility("default"))) int socketpair_wrapper(
    int domain, int type, int protocol, int* rsv, int* retval) {
  struct socketpair_args uap = {
      .domain = domain,
      .type = type,
      .protocol = protocol,
      .rsv = rsv,
  };
  return socketpair(kernproc, &uap, retval);
}

#pragma clang diagnostic pop
