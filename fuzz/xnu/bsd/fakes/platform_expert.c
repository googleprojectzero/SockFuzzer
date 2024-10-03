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

#include <IOKit/IOPlatformExpert.h>
#include <mach/i386/boolean.h>
#include <stdbool.h>
#include <string.h>

static char fuzzer_model_name[] = "fuzzer_model";
static char fuzzer_machine_name[] = "fuzzer_machine";
static char fuzzer_target_name[] = "fuzzer_target_name";
static char fuzzer_product_name[] = "fuzzer_product_name";

boolean_t PEGetModelName(char* name, int maxLength) {
  strlcpy(name, fuzzer_model_name, maxLength);
  return true;
}

// third_party/xnu/BUILD/obj/EXPORT_HDRS/iokit/IOKit/IOPlatformExpert.h
boolean_t PEGetMachineName(char* name, int maxLength) {
  strlcpy(name, fuzzer_machine_name, maxLength);
  return true;
}

int PEGetPlatformEpoch() {
  return -1;
}

int PEGetTargetName(char* name, int maxLength) {
  strlcpy(name, fuzzer_target_name, maxLength);
  return true;
}

boolean_t PEGetProductName(char* name, int maxLength) {
  strlcpy(name, fuzzer_product_name, maxLength);
  return true;
}
