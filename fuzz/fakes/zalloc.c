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

#include <kern/assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "osfmk/kern/kalloc.h"
#include "osfmk/kern/zalloc_internal.h"
#include "osfmk/mach/i386/kern_return.h"
#include "BUILD/obj/EXPORT_HDRS/osfmk/kern/zalloc.h"

int printf(const char*, ...) __printflike(1, 2);

void free(void *ptr);

// We link these in from libc/asan
void* malloc(size_t size);
void* calloc(size_t nmemb, size_t size);
void free(void* ptr);
int posix_memalign(void** memptr, size_t alignment, size_t size);

struct zone* zinit(uintptr_t size, uintptr_t max, uintptr_t alloc,
                   const char* name) {
  struct zone* zone = (struct zone*)calloc(1, sizeof(struct zone));
  zone->z_elem_size = size;
  return zone;
}

zone_t zone_create(
	const char             *name,
	vm_size_t               size,
	zone_create_flags_t     flags)
{
  struct zone* zone = (struct zone*)calloc(1, sizeof(struct zone));
  zone->z_elem_size = size;
  return zone;
}

// TODO: validation here
void zone_change() { return; }

void* zalloc(struct zone* zone) {
  assert(zone != NULL);
  return calloc(1, zone->z_elem_size);
}

void* zalloc_noblock(struct zone* zone) { return zalloc(zone); }

extern void     zfree(
	zone_or_view_t  zone_or_view,
	void            *elem) {
  (void)zone_or_view;
  free(elem);
}

int cpu_number() { return 0; }

void* kalloc_canblock(size_t* psize, bool canblock, void* site) {
  return malloc(*psize);
}

static bool mb_is_ready = false;
extern unsigned char* mbutl;
extern unsigned char* embutl;
static size_t current_page = 0;

uintptr_t kmem_mb_alloc(unsigned int mbmap, int size, int physContig,
                        int* err) {
  *err = 0;

  if (!mb_is_ready) {
    // 268 MB
    *err = posix_memalign((void**)&mbutl, 4096, 4096 * 65535);
    if (*err) {
      return 0;
    }
    embutl = (unsigned char*)((uintptr_t)mbutl + (4096 * 65535));

    mb_is_ready = true;
  }

  assert(mbutl);
  int pages = size / 4096;
  uintptr_t ret = (uintptr_t)mbutl + (current_page * 4096);
  current_page += pages;

  return ret;
}

// TODO: actually simulate physical page mappings
unsigned int pmap_find_phys(int pmap, uintptr_t va) { return 0; }

void* __MALLOC_ZONE(size_t size, int type, int flags,
                    vm_allocation_site_t* site) {
  return malloc(size);
}

void _FREE_ZONE(void* elem, size_t size, int type) { free(elem); }

#undef kfree
void kfree(void* data, size_t size) { free(data); }

void* realloc(void* ptr, size_t size);

void* __REALLOC(void* addr, size_t size, int type, int flags,
                vm_allocation_site_t* site) {
  void* ptr = realloc(addr, size);
  return ptr;
}

void OSFree(void* ptr, uint32_t size, void* tag) { free(ptr); }

void* OSMalloc(uint32_t size, void* tag) {
  return malloc(size);
}

SECURITY_READ_ONLY_LATE(struct kalloc_heap) KHEAP_DATA_BUFFERS[1] = {
	{
		.kh_zones    = NULL,
		.kh_name     = "data.",
		.kh_heap_id  = KHEAP_ID_DATA_BUFFERS,
	}
};

SECURITY_READ_ONLY_LATE(struct kalloc_heap) KHEAP_DEFAULT[1] = {
	{
		.kh_zones    = NULL,
		.kh_name     = "default.",
		.kh_heap_id  = KHEAP_ID_DEFAULT,
	}
};

KALLOC_HEAP_DEFINE(KHEAP_TEMP, "temp allocations", KHEAP_ID_DEFAULT);

ZONE_VIEW_DEFINE(ZV_NAMEI, "vfs.namei", KHEAP_ID_DATA_BUFFERS, 1024);

void abort() {
  __builtin_trap();
}

#undef kheap_free
extern void
kheap_free(
	kalloc_heap_t heap,
	void         *data,
	vm_size_t     size) {
  free(data);
}

__startup_func
void
zone_create_startup(struct zone_create_startup_spec *spec)
{
	*spec->z_var = zone_create(spec->z_name, spec->z_size,
	    spec->z_flags);
}

_Atomic uint32_t bt_init_flag = 0;

struct kalloc_result
kalloc_ext(
	kalloc_heap_t         kheap,
	vm_size_t             req_size,
	zalloc_flags_t        flags,
	vm_allocation_site_t  *site) {
  void *addr = malloc(req_size);
  if (flags & Z_ZERO) {
    bzero(addr, req_size);
  }
  return (struct kalloc_result){ .addr = addr, .size = req_size };
}

void *zalloc_flags(union zone_or_view zov, zalloc_flags_t flags) {
  return zalloc(zov.zov_zone);
}

#undef kheap_free_addr
void kheap_free_addr(
	kalloc_heap_t         heap,
	void                 *addr) {
  free(addr);
}

void *zalloc_permanent(vm_size_t size, vm_offset_t mask) {
  return malloc(size);
}
