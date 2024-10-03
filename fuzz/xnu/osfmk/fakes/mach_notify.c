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

#include <ipc/ipc_port.h>
#include <mach/i386/kern_return.h>
#include <mach/kern_return.h>
#include <mach/mach_notify.h>
#include <mach/port.h>

// Nothing locked. Consumes a ref/soright for port.
// Consumes a ref for right.
kern_return_t mach_notify_port_destroyed(mach_port_t notify,
                                         mach_port_t rights) {
  notify->ip_sorights--;
  ip_release(notify);
  ip_release(rights);
  return KERN_SUCCESS;
}

kern_return_t mach_notify_send_once(mach_port_t notify) {
  notify->ip_sorights--;
  ip_release(notify);
  return KERN_SUCCESS;
}

kern_return_t mach_notify_port_deleted(mach_port_t notify,
                                       mach_port_name_t name) {
  (void)name;
  notify->ip_sorights--;
  ip_release(notify);
  return KERN_SUCCESS;
}

kern_return_t mach_notify_send_possible(mach_port_t notify,
                                        mach_port_name_t name) {
  (void)name;
  notify->ip_sorights--;
  ip_release(notify);
  return KERN_SUCCESS;
}

kern_return_t mach_notify_no_senders(mach_port_t notify,
                                     mach_port_mscount_t mscount) {
  (void)mscount;
  notify->ip_sorights--;
  ip_release(notify);
  return KERN_SUCCESS;
}

kern_return_t mach_notify_dead_name(mach_port_t notify, mach_port_name_t name) {
  (void)name;
  notify->ip_sorights--;
  ip_release(notify);
  return KERN_SUCCESS;
}
