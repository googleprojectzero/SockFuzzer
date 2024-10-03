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
#include <stdbool.h>
#include <string.h>
#include <sys/_types/_u_int32_t.h>
#include <sys/_types/_u_int64_t.h>
#include <sys/cdefs.h>

#include <sys/param.h>

#include <sys/mbuf.h>
#include <sys/mcache.h>

#include "fuzz/host/hypercall/hypercall.h"

struct timeval;

void *calloc(size_t nmemb, size_t size);
void *malloc(size_t size);
void free(void *ptr);

int printf(const char *, ...) __printflike(1, 2);

int assfail(const char *a, const char *f, int l) {
  printf("assertion failed: %s, file: %s, line: %d", a, f, l);
  GetHypercallInterface()->Abort();
}

typedef enum {
  MC_MBUF = 0,   /* Regular mbuf */
  MC_CL,         /* Cluster */
  MC_BIGCL,      /* Large (4KB) cluster */
  MC_16KCL,      /* Jumbo (16KB) cluster */
  MC_MBUF_CL,    /* mbuf + cluster */
  MC_MBUF_BIGCL, /* mbuf + large (4KB) cluster */
  MC_MBUF_16KCL  /* mbuf + jumbo (16KB) cluster */
} mbuf_class_t;

void *mcache_alloc(mcache_t *cp, int wait) {
  mcache_obj_t *buf;

  mcache_alloc_ext(cp, &buf, 1, wait);
  return buf;
}

extern unsigned int mbuf_cslab_alloc(void *, mcache_obj_t ***, unsigned int,
                                     int);

#define MBUF_INIT_PKTHDR(m)        \
  {                                \
    (m)->m_pkthdr.rcvif = NULL;    \
    (m)->m_pkthdr.pkt_hdr = NULL;  \
    (m)->m_pkthdr.len = 0;         \
    (m)->m_pkthdr.csum_flags = 0;  \
    (m)->m_pkthdr.csum_data = 0;   \
    (m)->m_pkthdr.vlan_tag = 0;    \
    (m)->m_pkthdr.comp_gencnt = 0; \
    m_classifier_init(m, 0);       \
    m_tag_init(m, 1);              \
    m_scratch_init(m);             \
  }

#define MBUF_INIT(m, pkthdr, type)       \
  {                                      \
    (m)->m_next = (m)->m_nextpkt = NULL; \
    (m)->m_len = 0;                      \
    (m)->m_type = type;                  \
    if ((pkthdr) == 0) {                 \
      (m)->m_data = (uintptr_t)(m)->m_dat;          \
      (m)->m_flags = 0;                  \
    } else {                             \
      (m)->m_data = (uintptr_t)(m)->m_pktdat;       \
      (m)->m_flags = M_PKTHDR;           \
      MBUF_INIT_PKTHDR(m);               \
    }                                    \
  }

void *aligned_alloc(size_t alignment, size_t size);

unsigned int mcache_alloc_ext(mcache_t *cp, mcache_obj_t **list,
                              unsigned int num, int wait) {
  bool is_composite = ((int)cp->mc_private == MC_MBUF_CL ||
                       (int)cp->mc_private == MC_MBUF_BIGCL ||
                       (int)cp->mc_private == MC_MBUF_16KCL);
  if (cp->mc_slab_alloc && is_composite) {
    return cp->mc_slab_alloc(cp->mc_private, &list, num, wait);
  }

  mcache_obj_t *obj = NULL;
  mcache_obj_t *next = NULL;
  for (unsigned int i = 0; i < num; i++) {
    // printf("mcache_alloc_ext with bufsize %d\n", cp->mc_bufsize);
    if (cp->mc_bufsize == 256) {
      obj = aligned_alloc(cp->mc_bufsize, cp->mc_bufsize);
    } else {
      obj = malloc(cp->mc_bufsize);
    }
    if ((int)cp->mc_private == MC_MBUF) {
      MBUF_INIT((struct mbuf *)obj, 0, MT_FREE);
    }
    obj->obj_next = next;
    next = obj;
  }

  *list = obj;
  return num;
}

mcache_t *mcache_audit_cache;
void mcache_audit_free_verify(mcache_audit_t *a1, void *a2, size_t a3,
                              size_t a4) {
  GetHypercallInterface()->Abort();
}
void mcache_audit_free_verify_set(mcache_audit_t *a1, void *a2, size_t a3,
                                  size_t a4) {
  GetHypercallInterface()->Abort();
}
boolean_t mcache_bkt_isempty(mcache_t *cp) {
  return true;
}
void mcache_buffer_log(mcache_audit_t *a1, void *a2, mcache_t *a3,
                       struct timeval *a4) {
  GetHypercallInterface()->Abort();
}

mcache_t *mcache_create(const char *name, size_t bufsize, size_t align,
                        u_int32_t flags, int wait __unused) {
  mcache_t *cache = calloc(1, sizeof(mcache_t));
  strncpy(cache->mc_name, name, sizeof(cache->mc_name));
  cache->mc_bufsize = bufsize;
  cache->mc_slab_alloc = NULL;
  cache->mc_slab_free = NULL;
  cache->mc_slab_audit = NULL;
  cache->mc_private = cache;
  return cache;
}

mcache_t *mcache_create_ext(const char *name, size_t bufsize,
                            mcache_allocfn_t allocfn, mcache_freefn_t freefn,
                            mcache_auditfn_t auditfn, mcache_logfn_t logfn,
                            mcache_notifyfn_t notifyfn, void *arg,
                            u_int32_t flags, int wait __unused) {
  mcache_t *cache = calloc(1, sizeof(mcache_t));
  strncpy(cache->mc_name, name, sizeof(cache->mc_name));
  cache->mc_bufsize = bufsize;
  cache->mc_slab_alloc = allocfn;
  cache->mc_slab_free = freefn;
  cache->mc_slab_audit = auditfn;
  cache->mc_private = arg;
  return cache;
}

char *mcache_dump_mca(char buf[DUMP_MCA_BUF_SIZE], mcache_audit_t *audit) {
  GetHypercallInterface()->Abort();
}

void mcache_free(mcache_t *cp, void *buf) {
  ((mcache_obj_t *)buf)->obj_next = NULL;
  mcache_free_ext(cp, (mcache_obj_t *)buf);
}
void mcache_free_ext(mcache_t *cp, mcache_obj_t *list) {
  bool is_mbuf = ((int)cp->mc_private == MC_MBUF_CL ||
                  (int)cp->mc_private == MC_MBUF_BIGCL ||
                  (int)cp->mc_private == MC_MBUF_16KCL);
  if (cp->mc_slab_free && is_mbuf) {
    cp->mc_slab_free(cp->mc_private, list, true);
    return;
  }
  mcache_obj_t *tmp = NULL;
  while (list) {
    tmp = list->obj_next;
    free(list);
    list = tmp;
  }
}

unsigned int mcache_getflags(void) {
  return 0;
}
void mcache_init() {}
boolean_t mcache_purge_cache(mcache_t *cp, boolean_t async) {
  GetHypercallInterface()->Abort();
}
void mcache_reap() {
  GetHypercallInterface()->Abort();
}
void mcache_reap_now(mcache_t *a1, boolean_t a2) {
  GetHypercallInterface()->Abort();
}
void mcache_set_pattern(u_int64_t a1, void *a2, size_t a3) {
  GetHypercallInterface()->Abort();
}
void mcache_waiter_dec(mcache_t *a1) {
  GetHypercallInterface()->Abort();
}
void mcache_waiter_inc(mcache_t *a1) {
  GetHypercallInterface()->Abort();
}
