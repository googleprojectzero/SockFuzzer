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

#include <mach/i386/boolean.h>
#include <pexpert/i386/boot.h>
#include <pexpert/pexpert.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "fuzz/host/hypercall/hypercall.h"

void PEGetCoprocessorVersion() {
  GetHypercallInterface()->Abort();
}

void PEHaltRestartInternal() {
  GetHypercallInterface()->Abort();
}

void PEInitiatePanic() {
  GetHypercallInterface()->Abort();
}

char *PE_boot_args() {
  return "boot_args";
}

void PE_display_icon(unsigned int flags, const char *name) {}

void PEHaltRestart() {}

boolean_t PE_get_default(const char *property_name, void *property_ptr,
                         unsigned int max_property) {
  // TODO(nedwill): fuzz this
  memset(property_ptr, 0, max_property);
  return false;
  // return true;
}

void *PE_get_kc_header(kc_kind_t type) {
  GetHypercallInterface()->Abort();
}

bool PE_get_primary_kc_format(kc_format_t *type) {
  *type = KCFormatStatic;
  return true;
}

uint32_t PE_i_can_has_debugger(uint32_t *debug_flags) {
  if (debug_flags) {
    *debug_flags = 1;
  }
  return 1;
}

void PE_init_iokit() {}

void PE_init_panicheader() {
  GetHypercallInterface()->Abort();
}

void (*PE_kputc)(char c) = NULL;

void PE_lockdown_iokit() {}

void PE_panic_hook(const char *str) {
  GetHypercallInterface()->Abort();
}

boolean_t PE_parse_boot_arg_str(const char *arg_string, char *arg_ptr,
                                int size) {
  bzero(arg_ptr, size);
  return true;
}

static boot_args args;

PE_state_t PE_state = {.bootArgs = &args};

int PE_stub_poll_input(unsigned int options, char *c) {
  GetHypercallInterface()->Abort();
}

void PE_update_panicheader_nestedpanic() {
  GetHypercallInterface()->Abort();
}
