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

#include <i386/types.h>
#include <kern/misc_protos.h>
#include <libkern/copyio.h>
#include <mach/i386/vm_types.h>
#include <stdint.h>
#include <string.h>

#include "fuzz/host/hypercall/hypercall.h"

void *malloc(size_t size);
void free(void *ptr);

int mincore(void *addr, size_t length, unsigned char *vec);

#undef copyin
int __attribute__((warn_unused_result))
copyin(const user_addr_t uaddr, void *kaddr, size_t len) {
  // Address 1 means use fuzzed bytes, otherwise use real bytes.
  // NOTE: this does not support nested useraddr.
  // TODO(nedwill): disable for now when we have random syscalls
  // TODO(nedwill): just disable copyin for unsupport syscalls from the
  // fuzz target instead of checking every time
  // bool mapped = HostIsMapped(uaddr, len);

  if (!GetHypercallInterface()->IsCopyioBlocked() && uaddr != 1) {
    // GetHypercallInterface()->ThreadPrintf("copyin doing real copy from %p\n", uaddr);
    memcpy(kaddr, (void *)uaddr, len);
    return 0;
  }

  if (!GetHypercallInterface()->GetRemainingFuzzedBytes() || GetHypercallInterface()->GetFuzzedBool()) {
    return -1;
  }

  GetHypercallInterface()->GetFuzzedBytes(kaddr, len);
  return 0;
}

int copyinstr(const user_addr_t user_addr, char *kernel_addr, vm_size_t max,
              vm_size_t *actual) {
  // TODO(nedwill): disable for now when we have random syscalls
  // if (user_addr != 1) {
  //   strncpy(kernel_addr, (void *)user_addr, max);
  //   return 0;
  // }

  if (!GetHypercallInterface()->GetRemainingFuzzedBytes() || GetHypercallInterface()->GetFuzzedBool()) {
    return -1;
  }

  GetHypercallInterface()->GetFuzzedBytes(kernel_addr, max);
  if (max) {
    kernel_addr[max - 1] = 0;
  }
  return 0;
}

#undef copyout
int copyout(const void *kaddr, user_addr_t udaddr, size_t len) {
  if (GetHypercallInterface()->GetFuzzedBool()) {
    return 1;
  }

  if (!udaddr || udaddr == 1 || GetHypercallInterface()->IsCopyioBlocked()) {
    void *buf = malloc(len);
    memcpy(buf, kaddr, len);
    free(buf);
    return 0;
  }

  memcpy((void *)udaddr, kaddr, len);
  return 0;
}

int copyin_atomic32(const user_addr_t user_addr, uint32_t *kernel_addr) {
  return copyin(user_addr, kernel_addr, sizeof(uint32_t));
}

int copyin_atomic64(const user_addr_t user_addr, uint64_t *kernel_addr) {
  return copyin(user_addr, kernel_addr, sizeof(uint64_t));
}
