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

#ifndef HOST_INTERFACE_H_
#define HOST_INTERFACE_H_

#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"
#include "fuzz/host/hypercall/types.h"
#include "fuzz/host/logger.h"
#include "third_party/concurrence/sync/tracker.h"

extern "C" {
#include "fuzz/xnu/osfmk/api/types.h"
}

class HostInterface {
 public:
  virtual ~HostInterface() = default;

  virtual Logger *logger() = 0;
  virtual SyncTracker *sync_tracker() = 0;

  virtual void Yield() = 0;
  virtual bool IsRunnable(thread_t thread) = 0;
  virtual bool IsSuspended(thread_t thread) = 0;
  virtual bool IsWaiting(thread_t thread) = 0;
  virtual thread_t GetCurrentThreadT() = 0;
};

#endif /* HOST_INTERFACE_H_ */
