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

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <sys/param.h>

#include <sys/mbuf.h>

struct mbuf *mbuf_create(const uint8_t *data, size_t size, bool is_header,
                         bool force_ext, int mtype, int pktflags) {
  struct mbuf *m;
  if (is_header) {
    m = m_gethdr(M_DONTWAIT, mtype);
  } else {
    m = m_get(M_DONTWAIT, mtype);
  }
  if (!m) {
    return m;
  }

  if (size > m->m_len) {
    size = m->m_len;
  }

  /* populate a new mbuf containing the vlan ethernet header */
  m->m_len = size;
  memcpy((void*)m->m_data, data, size);
  return m;
}
