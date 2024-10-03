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

// Trivial implementations belong here. More substantial faked
// subsystems should live in their own file.

#include <kern/assert.h>
#include <libkern/libkern.h>
#include <mach/vm_types.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <sys/_types/_uuid_t.h>

#include "bsd/sys/malloc.h"
#include "bsd/uuid/uuid.h"

#include "fuzz/host/hypercall/hypercall.h"

bool PE_parse_boot_argn(const char *arg_string, void *arg_ptr, int max_arg) {
  if (!strcmp(arg_string, "ifa_debug")) {
    *(bool *)arg_ptr = false;
    return true;
  }

  if (!strcmp(arg_string, "inaddr_nhash")) {
    *(uint32_t *)arg_ptr = 0;
    return true;
  }

  if (!strcmp(arg_string, "mcache_flags")) {
    *(uint32_t *)arg_ptr = 0;
    return true;
  }

  if (!strcmp(arg_string, "mbuf_debug")) {
    *(uint32_t *)arg_ptr = 0;
    return true;
  }

  if (!strcmp(arg_string, "mleak_sample_factor")) {
    *(uint32_t *)arg_ptr = 0;
    return true;
  }

  // assert(false);
  return false;
}

void *os_log_create() {
  return (void *)1;
}

void uuid_clear(uuid_t uu) {
  memset(uu, 0, sizeof(uuid_t));
}

int uuid_is_null(const uuid_t uu) {
  return !memcmp(uu, UUID_NULL, sizeof(uuid_t));
}

int uuid_compare(const uuid_t uu1, const uuid_t uu2) {
  return memcmp(uu1, uu2, sizeof(uuid_t));
}

// TODO(nedwill): this shouldn't return the same value
// within the same fuzz session (use a counter and reset)
void uuid_generate_random(uuid_t out) {
  if (GetHypercallInterface()->GetFuzzedBool()) {
    memcpy(out, "0000000000000000", 16);
    return;
  }
  if (GetHypercallInterface()->GetFuzzedBool()) {
    memcpy(out, "1111111111111111", 16);
    return;
  }
  memcpy(out, "2222222222222222", 16);
}

void uuid_copy(uuid_t dst, const uuid_t src) {
  memcpy(dst, src, sizeof(uuid_t));
}

void uuid_unparse_upper(const uuid_t uu, uuid_string_t out) {
  snprintf(out, sizeof(uuid_string_t),
           "%c%c%c%c-"
           "%c%c-"
           "%c%c-"
           "%c%c-"
           "%c%c%c%c%c%c",
           uu[0], uu[1], uu[2], uu[3], uu[4], uu[5], uu[6], uu[7], uu[8], uu[9],
           uu[10], uu[11], uu[12], uu[13], uu[14], uu[15]);
}

void uuid_unparse(const uuid_t uu, uuid_string_t out) {
  uuid_unparse_upper(uu, out);
}

// unsigned long RandomULong() {
//   // returning 0 here would be a failure
//   return 1;
// }

void *malloc(size_t size);
void free(void *ptr);

void *__MALLOC(size_t size, int type, int flags, vm_allocation_site_t *site) {
  void *addr = NULL;
  assert(type < M_LAST);

  if (size == 0) {
    return NULL;
  }

  addr = malloc(size);
  if (!addr) {
    return NULL;
  }

  if (flags & M_ZERO) {
    bzero(addr, size);
  }

  return (addr);
}

void read_frandom(void *buffer, unsigned int numBytes) {
  GetHypercallInterface()->GetFuzzedBytes(buffer, numBytes);
}

void read_random(void *buffer, unsigned int numBytes) {
  GetHypercallInterface()->GetFuzzedBytes(buffer, numBytes);
}

void ovbcopy(const char *from, char *to, size_t nbytes) {
  memmove(to, from, nbytes);
}
