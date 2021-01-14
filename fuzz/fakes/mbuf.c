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

#include "bsd/machine/param.h"
#include "bsd/sys/mbuf.h"

// We link these in from libc/asan
void* malloc(size_t size);
void* calloc(size_t nmemb, size_t size);
void free(void* ptr);
int posix_memalign(void** memptr, size_t alignment, size_t size);

typedef struct {
  size_t bufsize;
  // Must we always return clusters?
  bool cluster_cache;
} mcache_t;

mcache_t* mcache_create(const char* name, size_t bufsize, size_t align,
                        u_int32_t flags, int wait) {
  mcache_t* cache = (mcache_t*)malloc(sizeof(mcache_t));
  cache->bufsize = bufsize;
  cache->cluster_cache = false;
  return cache;
}

// type doesn't match but we just need the address
void mbuf_cslab_alloc(void);

mcache_t* mcache_create_ext(const char* name, size_t bufsize, void* allocfn,
                            void* freefn, void* auditfn, void* logfn,
                            void* notifyfn, void* arg, u_int32_t flags,
                            int wait) {
  mcache_t* cache = (mcache_t*)malloc(sizeof(mcache_t));
  cache->bufsize = bufsize;
  cache->cluster_cache = allocfn == mbuf_cslab_alloc;
  return cache;
}

void assfail() { assert(false); }

struct mbuf* mbuf_create(const uint8_t* data, size_t size, bool is_header,
                         bool force_ext, int mtype, int pktflags) {
  struct mbuf* m = NULL;
  assert(sizeof(struct mbuf) == MSIZE);
  if (posix_memalign((void**)&m, MSIZE, sizeof(struct mbuf))) {
    return NULL;
  }
  memset((void*)m, 0, sizeof(struct mbuf));
  m->m_type = mtype;
  // TODO: use fuzzed data to create all kinds of mbuf chains
  size_t max_size = MBIGCLBYTES;
  if (njcl > 0) {
    max_size = njclbytes;
  }
  if (size >= max_size) {
    size = max_size - 1;
  }

  if (force_ext || size > sizeof(m->M_dat.MH.MH_dat.MH_databuf)) {
    m->m_flags = M_EXT;
    m->m_data = m->m_ext.ext_buf = (caddr_t)calloc(1, size);
    m->m_ext.ext_size = size;

    struct ext_ref* rfa = (struct ext_ref*)calloc(1, sizeof(struct ext_ref));
    rfa->refcnt = 1;
    rfa->minref = 1;
    int EXTF_COMPOSITE = 0x1;
    rfa->flags = EXTF_COMPOSITE;
    m->m_ext.ext_refflags = (struct ext_ref*)rfa;
  } else {
    m->m_flags = M_PKTHDR;
    m->m_data = m->m_pktdat;
  }

  if (data) memcpy(m->m_data, data, size);
  m->m_len = size;
  if (is_header) {
    m->m_flags |= M_PKTHDR;
    m->m_pkthdr.len = m->m_len;
    m->m_pkthdr.redzone = ((u_int32_t)(uintptr_t)m);
    m->m_pkthdr.pkt_flags = pktflags;
  }

  assert(m->m_len <= ((njcl > 0) ? njclbytes : MBIGCLBYTES));

  return m;
}

void* mcache_alloc(mcache_t* cp, int flags) {
  if (cp->cluster_cache) {
    return mbuf_create(NULL, cp->bufsize, false, cp->cluster_cache, MT_FREE, 0);
  }

  void* m = NULL;
  if (posix_memalign((void**)&m, MSIZE, cp->bufsize)) {
    return NULL;
  }
  return m;
}

uint16_t m_decref(struct mbuf* m) {
  struct ext_ref* rfa = m->m_ext.ext_refflags;
  if (rfa) {
    rfa->refcnt--;
    return rfa->refcnt;
  }
  return 0;
}

struct mbuf* m_free(struct mbuf* m) {
  if ((m->m_flags & M_EXT)) {
    uint16_t refcnt = m_decref(m);
    if (!refcnt) {
      free(m->m_ext.ext_buf);
      free(m->m_ext.ext_refflags);
    }
  }
  struct mbuf* ret = m->m_next;
  free(m);
  return ret;
}

void mcache_free(mcache_t* cp, void* buf) {
  if (cp->cluster_cache) {
    m_free((struct mbuf*)buf);
  } else {
    free(buf);
  }
}

void mcache_init() {
  // Nothing to do for mocked case.
}

void mcache_reap_now() { assert(false); }

int mcache_alloc_ext(mcache_t* cp, void** list, unsigned int num, int wait) {
  struct mbuf* m = (struct mbuf*)calloc(1, sizeof(struct mbuf));
  m->m_hdr.mh_next = NULL;
  m->m_hdr.mh_nextpkt = NULL;
  m->m_type = MT_FREE;
  m->m_flags = M_EXT;
  m->m_hdr.mh_data = (caddr_t)calloc(1, num * cp->bufsize);
  m->m_hdr.mh_len = num * cp->bufsize;
  *list = m;
  return 1;
}

void mcache_audit_cache() { assert(false); }

void mcache_audit_free_verify() { assert(false); }

void mcache_audit_free_verify_set() { assert(false); }

void mcache_bkt_isempty() { assert(false); }

void mcache_buffer_log() { assert(false); }

unsigned int mcache_cache_line_size() {
  return 64;
}

void mcache_dump_mca() { assert(false); }

void mcache_free_ext() { assert(false); }

unsigned int mcache_getflags() { return 0; }

void mcache_purge_cache() { assert(false); }

void mcache_reap() { assert(false); }

void mcache_set_pattern() { assert(false); }

void mcache_waiter_dec() { assert(false); }

void mcache_waiter_inc() { assert(false); }