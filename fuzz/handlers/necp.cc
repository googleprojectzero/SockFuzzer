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

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

#include "bsd_types.h"
#include "fuzz/proto/bsd.pb.h"
#include "fuzz/proto/bsd_enums.pb.h"
#include "fuzz/proto/bsd_types.pb.h"

typedef unsigned char uuid_t[16];

// Manually copied from syscall_wrappers.h as we can't mix XNU symbols with
// host symbols.
extern "C" int necp_client_action_wrapper(int necp_fd, uint32_t action,
                                          uuid_t client_id,
                                          size_t client_id_len, uint8_t *buffer,
                                          size_t buffer_size, int *retval);

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
