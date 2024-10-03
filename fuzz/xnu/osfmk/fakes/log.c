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

#include "fuzz/host/hypercall/hypercall.h"

__attribute__((noinline, not_tail_called)) void _os_log_internal(
    void *dso, int log, uint8_t type, const char *message, ...) {
  if (!is_verbose) {
    return;
  }
  va_list args;
  va_start(args, message);
  GetHypercallInterface()->LogVaList(message, args);
  va_end(args);
}

void kprintf(const char *fmt, ...) {
  if (!is_verbose) {
    return;
  }
  va_list args;
  va_start(args, fmt);
  GetHypercallInterface()->LogVaList(fmt, args);
  va_end(args);
}

int printf_if_verbose(const char *format, ...) {
  if (!is_verbose) {
    return 0;
  }
  va_list args;
  va_start(args, format);
  GetHypercallInterface()->LogVaList(format, args);
  va_end(args);
  return 0;
}

void os_log_with_args(void *oslog, int type, const char *format, va_list args,
                      void *ret_addr) {
  GetHypercallInterface()->LogVaList(format, args);
}
