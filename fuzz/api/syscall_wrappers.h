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

#ifndef SYSCALL_WRAPPERS_H_
#define SYSCALL_WRAPPERS_H_

#ifdef LIBXNU_BUILD
#include "BUILD/obj/DEBUG_X86_64/bsd/sys/sysproto.h"
#include "bsd/net/necp.h"
#include "bsd/netinet/in.h"
#include "bsd/sys/socket.h"
#else
typedef __uint64_t user64_addr_t;
typedef struct user64_sa_endpoints sa_endpoints_t;
typedef unsigned char uuid_t[16];
typedef u_int64_t user_addr_t;
typedef u_int32_t socklen_t;
typedef __uint32_t sae_associd_t;
typedef __uint32_t sae_connid_t;
typedef int64_t user_ssize_t;
typedef char* caddr_t;
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
#endif
#include <stddef.h>
#include <stdint.h>

int accept_wrapper(int s, caddr_t name, socklen_t* anamelen, int* retval);
int accept_nocancel_wrapper(int s, caddr_t name, socklen_t* anamelen,
                            int* retval);
int bind_wrapper(int s, caddr_t name, socklen_t namelen, int* retval);
int close_wrapper(int fd, int* retval);
int connect_wrapper(int s, caddr_t name, socklen_t namelen, int* retval);
int connect_nocancel_wrapper(int s, caddr_t name, socklen_t namelen,
                             int* retval);
int connectx_wrapper(int socket, const sa_endpoints_t* endpoints,
                     sae_associd_t associd, unsigned int flags,
                     const struct iovec* iov, unsigned int iovcnt, size_t* len,
                     sae_connid_t* connid, int* retval);
int disconnectx_wrapper(int s, sae_associd_t aid, sae_connid_t cid,
                        int* retval);
int getpeername_wrapper(int fdes, caddr_t asa, socklen_t* alen, int* retval);
int getsockname_wrapper(int fdes, caddr_t asa, socklen_t* alen, int* retval);
int getsockopt_wrapper(int s, int level, int name, caddr_t val,
                       socklen_t* avalsize, int* retval);
int ioctl_wrapper(int fd, u_long com, caddr_t data, int* retval);
int listen_wrapper(int s, int backlog, int* retval);
int necp_client_action_wrapper(int necp_fd, uint32_t action, uuid_t client_id,
                               size_t client_id_len, uint8_t* buffer,
                               size_t buffer_size, int* retval);
int necp_match_policy_wrapper(uint8_t* parameters, size_t parameters_size,
                              struct necp_aggregate_result* returned_result,
                              int* retval);
int necp_open_wrapper(int flags, int* retval);
int necp_session_action_wrapper(int necp_fd, uint32_t action,
                                uint8_t* in_buffer, size_t in_buffer_length,
                                uint8_t* out_buffer, size_t out_buffer_length,
                                int* retval);
int necp_session_open_wrapper(int flags, int* retval);
int peeloff_wrapper(int s, sae_associd_t aid, int* retval);
int pipe_wrapper(int* retval);
int recvfrom_wrapper(int s, void* buf, size_t len, int flags,
                     struct sockaddr* from, int* fromlenaddr, int* retval);
int recvfrom_nocancel_wrapper(int s, void* buf, size_t len, int flags,
                              struct sockaddr* from, int* fromlenaddr,
                              int* retval);
int recvmsg_wrapper(int s, struct msghdr* msg, int flags, int* retval);
int recvmsg_nocancel_wrapper(int s, struct msghdr* msg, int flags, int* retval);
int recvmsg_x_wrapper(int s, struct msghdr_x* msgp, u_int cnt, int flags,
                      user_ssize_t* retval);
int sendmsg_wrapper(int s, caddr_t msg, int flags, int* retval);
int sendmsg_nocancel_wrapper(int s, caddr_t msg, int flags, int* retval);
int sendmsg_x_wrapper(int s, struct msghdr_x* msgp, u_int cnt, int flags,
                      user_ssize_t* retval);
int sendto_wrapper(int s, caddr_t buf, size_t len, int flags, caddr_t to,
                   socklen_t tolen, int* retval);
int sendto_nocancel_wrapper(int s, caddr_t buf, size_t len, int flags,
                            caddr_t to, socklen_t tolen, int* retval);
int setsockopt_wrapper(int s, int level, int name, caddr_t val,
                       socklen_t valsize, int* retval);
int shutdown_wrapper(int s, int how, int* retval);
int socket_wrapper(int domain, int type, int protocol, int* retval);
int socket_delegate_wrapper(int domain, int type, int protocol, pid_t epid,
                            int* retval);
int socketpair_wrapper(int domain, int type, int protocol, int* rsv,
                       int* retval);

#endif  // SYSCALL_WRAPPERS_H_
