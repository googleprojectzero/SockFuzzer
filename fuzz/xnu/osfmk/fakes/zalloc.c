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

#include "BUILD/obj/EXPORT_HDRS/osfmk/kern/zalloc.h"

#include <i386/cpu_number.h>
#include <kern/assert.h>
#include <kern/debug.h>
#include <kern/misc_protos.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <vm/vm_kern.h>
#include <vm/vm_map_store.h>

#include "osfmk/kern/kalloc.h"
#include "osfmk/kern/zalloc_internal.h"

// int printf(const char *, ...) __printflike(1, 2);

void free(void *ptr);

// We link these in from libc/asan
void *malloc(size_t size);
void *calloc(size_t nmemb, size_t size);
int posix_memalign(void **memptr, size_t alignment, size_t size);

struct zone *zinit(uintptr_t size, uintptr_t max, uintptr_t alloc,
                   const char *name) {
  struct zone *zone = (struct zone *)calloc(1, sizeof(struct zone));
  zone->z_elem_size = size;
  return zone;
}

static void zone_initialize(zone_t zone, const char *name, vm_size_t size,
                            zone_create_flags_t flags) {
  zone->z_self = zone;
  zone->z_name = name;
  zone->z_elem_size = size;
}

zone_t zone_create(const char *name, vm_size_t size,
                   zone_create_flags_t flags) {
  struct zone *zone = (struct zone *)calloc(1, sizeof(struct zone));
  zone_initialize(zone, name, size, flags);
  return zone;
}

// TODO(nedwill): validation here
void zone_change() {}

// __attribute__((malloc)) __attribute__((overloadable)) extern void *zalloc(
//     zone_or_view_t zone_or_view) {
//   if (!zone_or_view.zov_view->zv_zone &&
//       zone_or_view.zov_kt_heap->kt_flags & KT_DATA_ONLY) {
//     return calloc(1, zone_or_view.zov_kt_heap->kt_size);
//   }
//   return calloc(1, zone_or_view.zov_view->zv_zone->z_elem_size);
// }

void zone_enable_caching(zone_t zone) {}

__attribute__((always_inline)) void *xnu_zalloc(zone_t zov) {
  return zalloc_flags(zov, Z_WAITOK);
}

void xnu_zfree(zone_t zone, void *addr __unsafe_indexable) {
  (void)zone;  // Zone information is not used in this fake implementation
  free(addr);
}

__attribute__((noinline)) void zalloc_ro_mut(zone_id_t zid, void *elem,
                                             vm_offset_t offset,
                                             const void *new_data,
                                             vm_size_t new_data_size) {
  assert(zid >= ZONE_ID__FIRST_RO && zid <= ZONE_ID__LAST_RO);

  // #if ZSECURITY_CONFIG(READ_ONLY)
  //   zalloc_ro_mut_validate_src(zid, elem, (vm_offset_t)new_data,
  //   new_data_size); pmap_ro_zone_memcpy(zid, (vm_offset_t)elem, offset,
  //   (vm_offset_t)new_data,
  //                       new_data_size);
  // #else
  (void)zid;
  memcpy((void *)((uintptr_t)elem + offset), new_data, new_data_size);
  // #endif
}

void zalloc_ro_clear(zone_id_t zid, void *elem, vm_offset_t offset,
                     vm_size_t size) {
  assert(zid >= ZONE_ID__FIRST_RO && zid <= ZONE_ID__LAST_RO);
  // #if ZSECURITY_CONFIG(READ_ONLY)
  //   pmap_ro_zone_bzero(zid, (vm_offset_t)elem, offset, size);
  // #else
  (void)zid;
  bzero((void *)((uintptr_t)elem + offset), size);
  // #endif
}

#undef zalloc_ro
extern void *zalloc_ro(zone_id_t zone_id, zalloc_flags_t flags) {
  zone_t zone = &zone_array[zone_id];
  return zalloc(zone);
}

__attribute__((malloc)) extern void *zalloc_noblock(zone_t zone_or_view) {
  void *ptr = zalloc(zone_or_view);
  // Cannot fail
  if (!ptr) {
    GetHypercallInterface()->Abort();
  }
  return ptr;
}

#undef zfree_ro
extern void zfree_ro(zone_id_t zone_id, void *addr __unsafe_indexable) {
  (void)zone_id;
  free(addr);
}

int cpu_number() {
  return 0;
}

void *kalloc_canblock(size_t *psize, bool canblock, void *site) {
  return malloc(*psize);
}

static bool mb_is_ready = false;
extern unsigned char *mbutl;
extern unsigned char *embutl;
static size_t current_page = 0;

uintptr_t kmem_mb_alloc(unsigned int mbmap, int size, int physContig,
                        int *err) {
  *err = 0;

  if (!mb_is_ready) {
    // 268 MB
    *err = posix_memalign((void **)&mbutl, 4096, 4096 * 65535);
    if (*err) {
      return 0;
    }
    embutl = (unsigned char *)((uintptr_t)mbutl + (4096 * 65535));

    mb_is_ready = true;
  }

  assert(mbutl);
  int pages = size / 4096;
  uintptr_t ret = (uintptr_t)mbutl + (current_page * 4096);
  current_page += pages;

  return ret;
}

void *__MALLOC_ZONE(size_t size, int type, int flags,
                    vm_allocation_site_t *site) {
  return malloc(size);
}

void _FREE_ZONE(void *elem, size_t size, int type) {
  free(elem);
}

#undef kfree
void kfree(void *data, size_t size) {
  free(data);
}

void *realloc(void *ptr, size_t size);

void *__REALLOC(void *addr, size_t size, int type, int flags,
                vm_allocation_site_t *site) {
  void *ptr = realloc(addr, size);
  return ptr;
}

void OSFree(void *ptr, uint32_t size, void *tag) {
  free(ptr);
}

void *OSMalloc(uint32_t size, void *tag) {
  return malloc(size);
}

struct kalloc_zone_cfg {
  bool kzc_caching;
  uint32_t kzc_size;
  char kzc_name[MAX_ZONE_NAME];
};

#define KZC_ENTRY(SIZE, caching) \
  { .kzc_caching = (caching), .kzc_size = (SIZE), .kzc_name = "kalloc." #SIZE }

static SECURITY_READ_ONLY_LATE(struct kalloc_zone_cfg) k_zone_cfg[] = {
#if !defined(XNU_TARGET_OS_OSX)

#if KALLOC_MINSIZE == 16 && KALLOC_LOG2_MINALIGN == 4
    /* Zone config for embedded 64-bit platforms */
    KZC_ENTRY(16, true),    KZC_ENTRY(32, true),     KZC_ENTRY(48, true),
    KZC_ENTRY(64, true),    KZC_ENTRY(80, true),     KZC_ENTRY(96, true),
    KZC_ENTRY(128, true),   KZC_ENTRY(160, true),    KZC_ENTRY(192, true),
    KZC_ENTRY(224, true),   KZC_ENTRY(256, true),    KZC_ENTRY(288, true),
    KZC_ENTRY(368, true),   KZC_ENTRY(400, true),    KZC_ENTRY(512, true),
    KZC_ENTRY(576, false),  KZC_ENTRY(768, false),   KZC_ENTRY(1024, true),
    KZC_ENTRY(1152, false), KZC_ENTRY(1280, false),  KZC_ENTRY(1664, false),
    KZC_ENTRY(2048, false), KZC_ENTRY(4096, false),  KZC_ENTRY(6144, false),
    KZC_ENTRY(8192, false), KZC_ENTRY(16384, false), KZC_ENTRY(32768, false),

#elif KALLOC_MINSIZE == 8 && KALLOC_LOG2_MINALIGN == 3
    /* Zone config for embedded 32-bit platforms */
    KZC_ENTRY(8, true),      KZC_ENTRY(16, true),     KZC_ENTRY(24, true),
    KZC_ENTRY(32, true),     KZC_ENTRY(40, true),     KZC_ENTRY(48, true),
    KZC_ENTRY(64, true),     KZC_ENTRY(72, true),     KZC_ENTRY(88, true),
    KZC_ENTRY(112, true),    KZC_ENTRY(128, true),    KZC_ENTRY(192, true),
    KZC_ENTRY(256, true),    KZC_ENTRY(288, true),    KZC_ENTRY(384, true),
    KZC_ENTRY(440, true),    KZC_ENTRY(512, true),    KZC_ENTRY(576, false),
    KZC_ENTRY(768, false),   KZC_ENTRY(1024, true),   KZC_ENTRY(1152, false),
    KZC_ENTRY(1280, false),  KZC_ENTRY(1536, false),  KZC_ENTRY(2048, false),
    KZC_ENTRY(2128, false),  KZC_ENTRY(3072, false),  KZC_ENTRY(4096, false),
    KZC_ENTRY(6144, false),  KZC_ENTRY(8192, false),
/* To limit internal fragmentation, only add the following zones if the
 * page size is greater than 4K.
 * Note that we use ARM_PGBYTES here (instead of one of the VM macros)
 * since it's guaranteed to be a compile time constant.
 */
#if ARM_PGBYTES > 4096
    KZC_ENTRY(16384, false), KZC_ENTRY(32768, false),
#endif /* ARM_PGBYTES > 4096 */

#else
#error missing or invalid zone size parameters for kalloc
#endif

#else /* !defined(XNU_TARGET_OS_OSX) */

    /* Zone config for macOS 64-bit platforms */
    KZC_ENTRY(16, true),     KZC_ENTRY(32, true),    KZC_ENTRY(48, true),
    KZC_ENTRY(64, true),     KZC_ENTRY(80, true),    KZC_ENTRY(96, true),
    KZC_ENTRY(128, true),    KZC_ENTRY(160, true),   KZC_ENTRY(192, true),
    KZC_ENTRY(224, true),    KZC_ENTRY(256, true),   KZC_ENTRY(288, true),
    KZC_ENTRY(368, true),    KZC_ENTRY(400, true),   KZC_ENTRY(512, true),
    KZC_ENTRY(576, true),    KZC_ENTRY(768, true),   KZC_ENTRY(1024, true),
    KZC_ENTRY(1152, false),  KZC_ENTRY(1280, false), KZC_ENTRY(1664, false),
    KZC_ENTRY(2048, true),   KZC_ENTRY(4096, true),  KZC_ENTRY(6144, false),
    KZC_ENTRY(8192, true),
#if __x86_64__
    KZC_ENTRY(12288, false),
#endif /* __x86_64__ */
    KZC_ENTRY(16384, false),
#if __arm64__
    KZC_ENTRY(32768, false),
#endif
#endif /* !defined(XNU_TARGET_OS_OSX) */
};

static SECURITY_READ_ONLY_LATE(struct kalloc_zone_cfg) k_zone_cfg_data[] = {
    KZC_ENTRY(16, true),     KZC_ENTRY(32, true),     KZC_ENTRY(48, true),
    KZC_ENTRY(64, true),     KZC_ENTRY(96, true),     KZC_ENTRY(128, true),
    KZC_ENTRY(160, true),    KZC_ENTRY(192, true),    KZC_ENTRY(256, true),
    KZC_ENTRY(368, true),    KZC_ENTRY(512, true),    KZC_ENTRY(768, false),
    KZC_ENTRY(1024, true),   KZC_ENTRY(1152, false),  KZC_ENTRY(1664, false),
    KZC_ENTRY(2048, false),  KZC_ENTRY(4096, false),  KZC_ENTRY(6144, false),
    KZC_ENTRY(8192, false),  KZC_ENTRY(16384, false),
#if __arm64__
    KZC_ENTRY(32768, false),
#endif
};
#undef KZC_ENTRY

#define MAX_K_ZONE(kzc) (uint32_t)(sizeof(kzc) / sizeof(kzc[0]))

static SECURITY_READ_ONLY_LATE(zone_t) k_zone_default[MAX_K_ZONE(k_zone_cfg)];
static SECURITY_READ_ONLY_LATE(zone_t) k_zone_data[MAX_K_ZONE(k_zone_cfg_data)];
static SECURITY_READ_ONLY_LATE(zone_t) k_zone_kext[MAX_K_ZONE(k_zone_cfg)];

// static SECURITY_READ_ONLY_LATE(struct kheap_zones) kalloc_zones_default = {
//     .cfg = k_zone_cfg,
//     .heap_id = KHEAP_ID_DEFAULT,
//     .k_zone = k_zone_default,
//     .max_k_zone = MAX_K_ZONE(k_zone_cfg)};
// SECURITY_READ_ONLY_LATE(struct kalloc_heap)
// KHEAP_DEFAULT[1] = {{
//     .kh_zones = &kalloc_zones_default,
//     .kh_name = "default.",
//     .kh_heap_id = KHEAP_ID_DEFAULT,
// }};

// static SECURITY_READ_ONLY_LATE(struct kheap_zones) kalloc_zones_data = {
//     .cfg = k_zone_cfg_data,
//     .heap_id = KHEAP_ID_DATA_BUFFERS,
//     .k_zone = k_zone_data,
//     .max_k_zone = MAX_K_ZONE(k_zone_cfg_data)};
// SECURITY_READ_ONLY_LATE(struct kalloc_heap)
// KHEAP_DATA_BUFFERS[1] = {{
//     .kh_zones = &kalloc_zones_data,
//     .kh_name = "data.",
//     .kh_heap_id = KHEAP_ID_DATA_BUFFERS,
// }};

// SECURITY_READ_ONLY_LATE(struct kalloc_heap) ZV_NAMEI[1] = {
// 	{
// 		.kh_zones    = &kalloc_zones_data,
// 		.kh_name     = "vfs.namei.",
// 		.kh_heap_id  = KHEAP_ID_DATA_BUFFERS,
// 	}
// };

// TODO(nedwill): figure out why this isn't working
// we are returning size 0 here when calling malloc on this.
// it might be a failure to initialize kalloc's KHEAP_ID_DATA_BUFFERS properly
ZONE_VIEW_DEFINE(ZV_NAMEI, "vfs.namei", KHEAP_ID_DATA_BUFFERS, 4096);

static SECURITY_READ_ONLY_LATE(vm_map_t) kernel_data_map;
static SECURITY_READ_ONLY_LATE(vm_map_t) kalloc_large_map;
static SECURITY_READ_ONLY_LATE(vm_map_t) kalloc_large_data_map;

// __startup_data size_t      kheap_zsize[KHEAP_NUM_ZONES];

// __startup_func static void kalloc_zone_init(const char *kheap_name,
//                                             zone_kheap_id_t kheap_id,
//                                             zone_id_t *kheap_zstart,
//                                             zone_create_flags_t zc_flags) {
//   printf("kheap_name: %s, kheap_id: %u\n", kheap_name, kheap_id);
//   zc_flags |= (ZC_KASAN_NOREDZONE | ZC_KASAN_NOQUARANTINE | ZC_PGZ_USE_GUARDS);

//   for (uint32_t i = 0; i < KHEAP_NUM_ZONES; i++) {
//     uint32_t size = (uint32_t)kheap_zsize[i];
//     char buf[MAX_ZONE_NAME], *z_name;
//     int len;

//     len = scnprintf(buf, MAX_ZONE_NAME, "%s.%u", kheap_name, size);
//     z_name = zalloc_permanent(len + 1, ZALIGN_NONE);
//     strlcpy(z_name, buf, len + 1);

//     (void)zone_create_ext(z_name, size, zc_flags, ZONE_ID_ANY, ^(zone_t z) {
//       printf("Inside extra_setup: z: %p, zone_index: %u\n", z, zone_index(z));
// #if __arm64e__
//       uint32_t scale = kalloc_log2down(size / 32);

//       if (size == 32 << scale) {
//         z->z_array_size_class = scale;
//       } else {
//         z->z_array_size_class = scale | 0x10;
//       }
// #endif
//       zone_security_array[zone_index(z)].z_kheap_id = (uint16_t)kheap_id;
//       if (i == 0) {
//         *kheap_zstart = zone_index(z);
//       }
//     });
//   }
// }

// __startup_func static void kalloc_heap_init(struct kalloc_heap *kheap) {
//   kalloc_zone_init("kalloc", kheap->kh_heap_id, &kheap->kh_zstart, ZC_NONE);
//   /*
// 	 * Count all the "raw" views for zones in the heap.
// 	 */
//   zone_view_count += KHEAP_NUM_ZONES;
// }

// SECURITY_READ_ONLY_LATE(struct kalloc_heap) KHEAP_DEFAULT[1] = {
// 	{
// 		.kh_name     = "default.",
// 		.kh_heap_id  = KHEAP_ID_DEFAULT,
// 		.kh_tag      = VM_KERN_MEMORY_KALLOC
// 	}
// };

// SECURITY_READ_ONLY_LATE(struct kalloc_heap) KHEAP_DATA_BUFFERS[1] = {
// 	{
// 		.kh_name     = "data.",
// 		.kh_heap_id  = KHEAP_ID_DATA_BUFFERS,
// 		.kh_tag      = VM_KERN_MEMORY_KALLOC_DATA,
// 	}
// };

// vm_size_t kalloc_next_good_size(
// 	vm_size_t               size,
// 	uint32_t                period) {
//   GetHypercallInterface()->Abort();
// }

// struct kalloc_result __kalloc_array_decode(
// 	vm_address_t            array) {
//   GetHypercallInterface()->Abort();
// }

// __startup_func static void kalloc_zsize_compute(void) {
//   size_t step = KHEAP_STEP_START;
//   uint32_t start = 0;
//   /*
// 	 * Manually initialize extra initial zones
// 	 */
//   kheap_zsize[start] = 16;
//   kheap_zsize[start + 1] = KHEAP_START_SIZE;

//   /*
// 	 * Compute sizes for remaining zones
// 	 */
//   for (uint32_t i = 0; i < KHEAP_NUM_STEPS; i++) {
//     uint32_t step_idx = (i * 2) + KHEAP_EXTRA_ZONES;
//     kheap_zsize[step_idx] = kheap_zsize[step_idx - 1] + step;
//     kheap_zsize[step_idx + 1] = kheap_zsize[step_idx] + step;
//     step *= 2;
//   }
// }

// __startup_func static void kalloc_init(void) {
//   static_assert(KHEAP_MAX_SIZE >= KALLOC_SAFE_ALLOC_SIZE);
//   kalloc_zsize_compute();

//   /* Initialize kalloc default heap */
//   kalloc_heap_init(KHEAP_DEFAULT);

// #if ZSECURITY_CONFIG(SUBMAP_USER_DATA)
//   /* Initialize kalloc data buffers heap */
//   kalloc_heap_init(KHEAP_DATA_BUFFERS);
// #else
//   *KHEAP_DATA_BUFFERS = *KHEAP_DEFAULT;
// #endif
// }
// STARTUP(ZALLOC, STARTUP_RANK_THIRD, kalloc_init);

// #undef kheap_free
// extern void kheap_free(kalloc_heap_t heap, void *data, vm_size_t size) {
//   free(data);
// }

__startup_func void zone_create_startup(struct zone_create_startup_spec *spec) {
  zone_t z;

  z = zone_create_ext(spec->z_name, spec->z_size, spec->z_flags, spec->z_zid,
                      spec->z_setup);
  if (spec->z_var) {
    *spec->z_var = z;
  }
}

_Atomic uint32_t bt_init_flag = 0;

// #undef kalloc_ext
// struct kalloc_result kalloc_ext(void *kheap_or_kt_view, vm_size_t req_size,
//                                 zalloc_flags_t flags, void *site) {
//   if (req_size > (vm_size_t)65535 * 2) {
//     return (struct kalloc_result){.addr = NULL, .size = 0};
//   }
//   void *addr = malloc(req_size);
//   if (flags & Z_ZERO) {
//     bzero(addr, req_size);
//   }
//   return (struct kalloc_result){.addr = addr, .size = req_size};
// }

#undef zalloc_flags
void *zalloc_flags(zone_t zone, zalloc_flags_t flags) {
  zone_t self = zone->z_self;
  zone_stats_t zstats = zone->z_stats;

  assert(self != NULL);
  // Add any other necessary assertions

  return zalloc_ext(self, zstats, flags).addr;
}

#undef kheap_free_addr
void kheap_free_addr(kalloc_heap_t heap, void *addr) {
  free(addr);
}

#undef zalloc_permanent
void *zalloc_permanent(vm_size_t size, vm_offset_t mask) {
  return calloc(1, size);
}

static zone_t zone_init_defaults(zone_id_t zid) {
  zone_t z = &zone_array[zid];

  // No need to set z_wired_max and collectable as they are
  // not used in the fake implementation.

  // We don't need locks for libc malloc/free, so remove the
  // hw_lck_ticket_init calls.

  // zone_depot_init is not necessary for libc malloc/free.

  return z;
}

static zone_id_t num_zones_in_use;
zone_id_t _Atomic num_zones;

static zone_t zone_create_find(const char *name, vm_size_t size,
                               zone_create_flags_t flags,
                               zone_id_t *zid_inout) {
  zone_id_t nzones, zid = *zid_inout;
  zone_t z;

  nzones = (zone_id_t)os_atomic_load(&num_zones, relaxed);
  assert(num_zones_in_use <= nzones && nzones < MAX_ZONES);

  if (__improbable(nzones < ZONE_ID__FIRST_DYNAMIC)) {
    /*
		 * The first time around, make sure the reserved zone IDs
		 * have an initialized lock as zone_index_foreach() will
		 * enumerate them.
		 */
    while (nzones < ZONE_ID__FIRST_DYNAMIC) {
      zone_init_defaults(nzones++);
    }

    os_atomic_store(&num_zones, nzones, release);
  }

  if (zid != ZONE_ID_ANY) {
    if (zid >= ZONE_ID__FIRST_DYNAMIC) {
      panic("zone_create: invalid desired zone ID %d for %s", zid, name);
    }
    if (flags & ZC_DESTRUCTIBLE) {
      panic("zone_create: ID %d (%s) must be permanent", zid, name);
    }
    if (zone_array[zid].z_self) {
      panic("zone_create: creating zone ID %d (%s) twice", zid, name);
    }
    z = &zone_array[zid];
  } else {
    zid = nzones++;
    z = zone_init_defaults(zid);

    /*
		 * The release barrier pairs with the acquire in
		 * zone_index_foreach() and makes sure that enumeration loops
		 * always see an initialized zone lock.
		 */
    os_atomic_store(&num_zones, nzones, release);
  }

out:
  num_zones_in_use++;

  *zid_inout = zid;
  return z;
}

#define ZONE_MAX_ALLOC_SIZE (32 * 1024)
#define ZONE_MIN_ELEM_SIZE sizeof(uint64_t)
#define ZONE_ALIGN_SIZE ZONE_MIN_ELEM_SIZE

static vm_size_t zone_elem_adjust_size(const char *name __unused,
                                       vm_size_t elem_size,
                                       zone_create_flags_t flags __unused,
                                       uint32_t *redzone __unused) {
  vm_size_t size;
  /*
	 * Adjust element size for minimum size and pointer alignment
	 */
  size = (elem_size + ZONE_ALIGN_SIZE - 1) & -ZONE_ALIGN_SIZE;
  if (size < ZONE_MIN_ELEM_SIZE) {
    size = ZONE_MIN_ELEM_SIZE;
  }

  // #if KASAN_ZALLOC
  // 	/*
  // 	 * Expand the zone allocation size to include the redzones.
  // 	 *
  // 	 * For page-multiple zones add a full guard page because they
  // 	 * likely require alignment.
  // 	 */
  // 	uint32_t redzone_tmp;
  // 	if (flags & (ZC_KASAN_NOREDZONE | ZC_PERCPU)) {
  // 		redzone_tmp = 0;
  // 	} else if ((size & PAGE_MASK) == 0) {
  // 		if (size != PAGE_SIZE && (flags & ZC_ALIGNMENT_REQUIRED)) {
  // 			panic("zone_create: zone %s can't provide more than PAGE_SIZE"
  // 			    "alignment", name);
  // 		}
  // 		redzone_tmp = PAGE_SIZE;
  // 	} else if (flags & ZC_ALIGNMENT_REQUIRED) {
  // 		redzone_tmp = 0;
  // 	} else {
  // 		redzone_tmp = KASAN_GUARD_SIZE;
  // 	}
  // 	size += redzone_tmp * 2;
  // 	if (redzone) {
  // 		*redzone = redzone_tmp;
  // 	}
  // #endif
  return size;
}

static vm_size_t zone_get_min_alloc_granule(vm_size_t elem_size,
                                            zone_create_flags_t flags) {
  vm_size_t alloc_granule = PAGE_SIZE;
  if (flags & ZC_PERCPU) {
    alloc_granule = PAGE_SIZE * zpercpu_count();
    if (PAGE_SIZE % elem_size > 256) {
      panic("zone_create: per-cpu zone has too much fragmentation");
    }
  } else if (flags & ZC_READONLY) {
    alloc_granule = PAGE_SIZE;
  } else if ((elem_size & PAGE_MASK) == 0) {
    /* zero fragmentation by definition */
    alloc_granule = elem_size;
  } else if (alloc_granule % elem_size == 0) {
    /* zero fragmentation by definition */
  } else {
    vm_size_t frag = (alloc_granule % elem_size) * 100 / alloc_granule;
    vm_size_t alloc_tmp = PAGE_SIZE;
    vm_size_t max_chunk_size = ZONE_MAX_ALLOC_SIZE;

#if __arm64__
    /*
		 * Increase chunk size to 48K for sizes larger than 4K on 16k
		 * machines, so as to reduce internal fragementation for kalloc
		 * zones with sizes 12K and 24K.
		 */
    if (elem_size > 4 * 1024 && PAGE_SIZE == 16 * 1024) {
      max_chunk_size = 48 * 1024;
    }
#endif
    while ((alloc_tmp += PAGE_SIZE) <= max_chunk_size) {
      vm_size_t frag_tmp = (alloc_tmp % elem_size) * 100 / alloc_tmp;
      if (frag_tmp < frag) {
        frag = frag_tmp;
        alloc_granule = alloc_tmp;
      }
    }
  }
  return alloc_granule;
}

static inline bool zone_has_index(zone_t z, zone_id_t zid) {
  return zone_array + zid == z;
}

__startup_data static struct zone_stats zone_stats_startup[MAX_ZONES];

zone_t zone_create_ext(const char *name, vm_size_t size,
                       zone_create_flags_t flags, zone_id_t zid,
                       void (^extra_setup)(zone_t)) {
  vm_size_t alloc;
  uint32_t redzone;
  zone_t z;
  zone_security_flags_t *zsflags;

  if (size > ZONE_MAX_ALLOC_SIZE) {
    panic("zone_create: element size too large: %zd", (size_t)size);
  }

  if (size < 2 * sizeof(vm_size_t)) {
    /* Elements are too small for kasan. */
    flags |= ZC_KASAN_NOQUARANTINE | ZC_KASAN_NOREDZONE;
  }

  size = zone_elem_adjust_size(name, size, flags, &redzone);
  /*
   * Allocate the zone slot, return early if we found an older match.
   */
  z = zone_create_find(name, size, flags, &zid);
  if (__improbable(z->z_self)) {
    /* We found a zone to reuse */
    return z;
  }

  /*
   * Initialize the zone properly.
   */

  /*
   * If the kernel is post lockdown, copy the zone name passed in.
   * Else simply maintain a pointer to the name string as it can only
   * be a core XNU zone (no unloadable kext exists before lockdown).
   */
  if (startup_phase >= STARTUP_SUB_LOCKDOWN) {
    size_t nsz = MIN(strlen(name) + 1, MACH_ZONE_NAME_MAX_LEN);
    char *buf = zalloc_permanent(nsz, ZALIGN_NONE);
    strlcpy(buf, name, nsz);
    z->z_name = buf;
  } else {
    z->z_name = name;
  }
  if (__probable(zone_array[ZONE_ID_PERCPU_PERMANENT].z_self)) {
    z->z_stats = zalloc_percpu_permanent_type(struct zone_stats);
  } else {
    /*
     * zone_init() hasn't run yet, use the storage provided by
     * zone_stats_startup(), and zone_init() will replace it
     * with the final value once the PERCPU zone exists.
     */
    z->z_stats = __zpcpu_mangle_for_boot(&zone_stats_startup[zone_index(z)]);
  }

  alloc = zone_get_min_alloc_granule(size, flags);

  z->z_elem_size = (uint16_t)size;
  z->z_chunk_pages = (uint16_t)atop(alloc);
  z->z_quo_magic = Z_MAGIC_QUO(size);
  z->z_align_magic = Z_MAGIC_ALIGNED(size);
  if (flags & ZC_PERCPU) {
    z->z_chunk_elems = (uint16_t)(PAGE_SIZE / z->z_elem_size);
    z->z_elem_offs = (uint16_t)(PAGE_SIZE % z->z_elem_size);
  } else {
    z->z_chunk_elems = (uint16_t)(alloc / z->z_elem_size);
    z->z_elem_offs = (uint16_t)(alloc % z->z_elem_size);
  }

  /*
   * Handle KPI flags
   */
  zsflags = &zone_security_array[zid];

  /* Initialize zone_security_array entry */
  memset(zsflags, 0, sizeof(*zsflags));

  /* ZC_CACHING applied after all configuration is done */
  if (flags & ZC_NOCACHING) {
    z->z_nocaching = true;
  }

  /*
   * Then if there's extra tuning, do it
   */
  if (extra_setup) {
    extra_setup(z);
  }
  z->z_self = z;
  return z;
}

__startup_func static void zone_security_array_init(void) {
  struct zone_security_flags default_config = {
      .z_kheap_id = KHEAP_ID_NONE,
      .z_noencrypt = false,
      .z_submap_idx = Z_SUBMAP_IDX_GENERAL_0,
      .z_kalloc_type = false,
  };
  // if (ZSECURITY_OPTIONS_SEQUESTER & zsecurity_options) {
  // 	default_config.z_va_sequester = true;
  // }
  for (zone_id_t i = 0; i < MAX_ZONES; i++) {
    zone_security_array[i] = default_config;
  }
}

#define MAX_ZONES 690
struct zone zone_array[MAX_ZONES];
SECURITY_READ_ONLY_LATE(zone_security_flags_t) zone_security_array[MAX_ZONES];

void zone_bootstrap() {}
void zone_cram_foreign(zone_t zone, vm_offset_t newmem, vm_size_t size) {}
vm_size_t zone_element_info(void *addr, vm_tag_t *ptag) {
  GetHypercallInterface()->Abort();
}
void zone_fill_initially(zone_t zone, vm_size_t nelems) {}
extern vm_offset_t zone_foreign_mem_init(vm_size_t size,
                                         bool allow_meta_steal) {
  return 0;
}
// TODO(nedwill): implement GC
void zone_gc(zone_gc_level_t level) {}

vm_size_t zone_get_foreign_alloc_size(const char *name __unused,
                                      vm_size_t elem_size,
                                      zone_create_flags_t flags,
                                      uint16_t min_pages) {
  return 0;
}

const char *zone_heap_name(zone_t zone) {
  GetHypercallInterface()->Abort();
}
void zone_id_require(zone_id_t zone_id, vm_size_t elem_size, void *addr) {}
void zone_id_require_allow_foreign(zone_id_t zone_id, vm_size_t elem_size,
                                   void *addr) {}
uint32_t zone_index_from_tag_index(uint32_t tag_zone_index,
                                   vm_size_t *elem_size) {
  GetHypercallInterface()->Abort();
}

// TODO(nedwill): return true sometimes
bool zone_map_nearing_exhaustion(void) {
  return false;
}
bool zone_maps_owned(vm_address_t addr, vm_size_t size) {
  return false;
}

void zone_map_sizes(vm_map_size_t *psize, vm_map_size_t *pfree,
                    vm_map_size_t *plargest_free) {
  GetHypercallInterface()->Abort();
}
const char *zone_name(zone_t zone) {
  GetHypercallInterface()->Abort();
}
// Creates a thread to replenish the zone
void zone_replenish_configure() {}
void zone_require(zone_t zone, void *addr) {}
void zone_require_ro(zone_id_t zone_id, vm_size_t elem_size, void *addr) {}
void zone_set_exhaustible(zone_t zone, vm_size_t max_elements,
                          bool exhausts_by_design) {}
void zone_set_submap_idx() {}
uint32_t zone_view_count = 0;

ZONE_DEFINE_TYPE(percpu_u64_zone, "percpu.64", uint64_t,
                 ZC_PERCPU | ZC_ALIGNMENT_REQUIRED | ZC_KASAN_NOREDZONE);

void zone_raise_reserve(union zone_or_view zov, uint16_t min_elements) {
  zone_t zone = zov.zov_zone;

  if (zone < zone_array || zone > &zone_array[MAX_ZONES]) {
    zone = zov.zov_view->zv_zone;
  } else {
    zone = zov.zov_zone;
  }

  printf("[zone_raise_reserve]: zov.zov_zone: %p, zov.zov_view: %p, zone: %p\n",
         zov.zov_zone, zov.zov_view, zone);

  os_atomic_max(&zone->z_elems_rsv, min_elements, relaxed);
}

void zone_id_require_aligned(zone_id_t zone_id, void *addr) {}

// static zone_t kalloc_zone_for_size_with_flags(zone_id_t zid, vm_size_t size,
//                                               zalloc_flags_t flags) {
//   vm_size_t max_size = KHEAP_MAX_SIZE;
//   bool forcopyin = flags & Z_MAY_COPYINMAP;

//   if (forcopyin) {
// #if __x86_64__
//     /*
// 		 * On Intel, the OSData() ABI used to allocate
// 		 * from the kernel map starting at PAGE_SIZE.
// 		 *
// 		 * If only vm_map_copyin() or a wrapper is used,
// 		 * then everything will work fine because vm_map_copy_t
// 		 * will perform an actual copy if the data is smaller
// 		 * than msg_ool_size_small (== KHEAP_MAX_SIZE).
// 		 *
// 		 * However, if anyone is trying to call mach_vm_remap(),
// 		 * then bad things (TM) happen.
// 		 *
// 		 * Avoid this by preserving the ABI and moving
// 		 * to kalloc_large() earlier.
// 		 *
// 		 * Any recent code really ought to use IOMemoryDescriptor
// 		 * for this purpose however.
// 		 */
//     max_size = PAGE_SIZE - 1;
// #endif
//   }

//   if (size <= max_size) {
//     uint32_t idx;

//     if (size <= KHEAP_START_SIZE) {
//       zid += (size > 16);
//     } else {
//       /*
// 			 * . log2down(size - 1) is log2up(size) - 1
// 			 * . (size - 1) >> (log2down(size - 1) - 1) is either 0x2 or 0x3
// 			 */
//       size -= 1;
//       idx = kalloc_log2down((uint32_t)size);
//       zid += KHEAP_EXTRA_ZONES + 2 * (idx - KHEAP_START_IDX) +
//              ((uint32_t)size >> (idx - 1)) - 2;
//       // Print intermediate variables and final zid value
//       printf("size: %u, idx: %u, zid: %u\n", size, idx, zid);
//     }
//     if (zid > MAX_ZONES) {
//       printf("kalloc_zone_for_size(%lu) => %u (out of bounds)\n", size, zid);
//       GetHypercallInterface()->Abort();
//     }
//     // Print the calculated zone index and resulting zone pointer
//     printf("Calculated zid: %u\n", zid);
//     zone_t result_zone = zone_array + zid;
//     printf("Returning zone pointer: %p\n", (void *)result_zone);
//     return result_zone;
//   }

//   // Print when returning ZONE_NULL
//   printf("Returning ZONE_NULL\n");
//   return ZONE_NULL;
// }

bool panic_include_kalloc_types = false;

// zone_t kalloc_zone_for_size(zone_id_t zid, size_t size) {
//   return kalloc_zone_for_size_with_flags(zid, size, Z_WAITOK);
// }

void zfree_ext(zone_t zone, zone_stats_t zstats, void *addr,
               uint64_t combined_size) {
  GetHypercallInterface()->Abort();
}

vm_size_t zone_element_size(void *elem, zone_t *z, bool clear_oob,
                            vm_offset_t *oob_offs) {
  return 0;
}

zone_t kalloc_type_src_zone = ZONE_NULL;

struct kalloc_result zalloc_ext(zone_t zone, zone_stats_t zstats,
                                zalloc_flags_t flags) {
  struct kalloc_result result;
  vm_size_t size = zone->z_elem_size;

  // Check for explicit zero-init request or if the zone is configured for clean memory
  // ZC_ZFREE_CLEARMEM doesn't seem to be published so we have to stay on the safe side
  // and use zero-initialized memory for all zones. We should revisit this if we find
  // a way to determine if a zone is configured for clean memory or not or they publish
  // their internal code properly.
  result.addr = calloc(1, size);
  
  result.size = size;

  return result;
}

SECURITY_READ_ONLY_LATE(zone_cache_ops_t) zcache_ops[ZONE_ID__FIRST_DYNAMIC];

__startup_func void zone_view_startup_init(
    struct zone_view_startup_spec *spec) {
  struct kalloc_heap *heap = NULL;
  zone_view_t zv = spec->zv_view;
  zone_t z;
  zone_security_flags_t zsflags;
  printf("Initializing zone view %s\n", zv->zv_name);

  switch (spec->zv_heapid) {
    case KHEAP_ID_DATA_BUFFERS:
      heap = KHEAP_DATA_BUFFERS;
      break;
    default:
      heap = NULL;
  }

  if (heap) {
    z = kalloc_zone_for_size(heap->kh_zstart, spec->zv_size);
    printf("Initializing zone for heap %s with size %zu\n",
           spec->zv_view->zv_name, spec->zv_size);
    if (spec->zv_size > zone_elem_inner_size(z)) {
      GetHypercallInterface()->Abort();
    }
    printf("Returned zone %p has size %u\n", z, z->z_elem_size);
  } else {
    z = *spec->zv_zone;
    // if (z->z_elem_size == 0) {
    //     z->z_elem_size = spec->zv_size;
    // }
    printf("Initializing zone %s with size %zu\n", spec->zv_view->zv_name,
           spec->zv_size);
    if (spec->zv_size > zone_elem_inner_size(z)) {
      GetHypercallInterface()->Abort();
    }
    printf("Returned zone %p has size %u\n", z, z->z_elem_size);
  }

  assert(z);
  if (!z) {
    panic("%s: failed to find zone for zone view %s", __func__, zv->zv_name);
  }

  zv->zv_zone = z;
  zv->zv_stats = zalloc_percpu_permanent_type(struct zone_stats);
  zv->zv_next = z->z_views;  // Link to existing views
  zsflags = zone_security_config(z);

  if (z->z_views == NULL && zsflags.z_kheap_id == KHEAP_ID_NONE) {
    zone_view_count += 2;
  } else {
    zone_view_count += 1;
  }

  z->z_views = zv;
}

void zalloc_first_proc_made() {}

#undef zalloc_percpu
void *zalloc_percpu(zone_or_view_t zov, zalloc_flags_t flags) {
  return zalloc(zov.zov_view->zv_zone);
}

void zfree_percpu(zone_or_view_t zone_or_view, void *addr) {
  free(addr);
}

void *zalloc_percpu_permanent(vm_size_t size, vm_offset_t align_mask) {
  return calloc(1, size);
}

#define INDEX_ZDLUT(size) (((size) + KALLOC_MINALIGN - 1) / KALLOC_MINALIGN)
#define MAX_SIZE_ZDLUT ((KALLOC_DLUT_SIZE - 1) * KALLOC_MINALIGN)

// bool kalloc_owned_map(vm_map_t map) {
//   return map && (map == kalloc_large_map || map == kalloc_large_data_map ||
//                  map == kernel_data_map);
// }

// #undef krealloc_ext
// struct kalloc_result krealloc_ext(void *kheap_or_kt_view, void *addr,
//                                   vm_size_t old_size, vm_size_t new_size,
//                                   zalloc_flags_t flags, void *site) {
//   vm_size_t old_bucket_size, new_bucket_size, min_size;
//   vm_size_t adj_new_size, adj_old_size;
//   struct kalloc_result kr;

//   if (new_size == 0) {
//     free(addr);
//     return (struct kalloc_result){};
//   }

//   if (addr == NULL) {
//     return kalloc_ext(kheap_or_kt_view, new_size, flags, site);
//   }

//   adj_old_size = old_size;
//   adj_new_size = new_size;

//   kr.addr = calloc(1, new_size);
//   kr.size = new_size;
//   return kr;
// }

void *zalloc_permanent_tag(vm_size_t size, vm_offset_t mask, vm_tag_t tag) {
  return calloc(1, size);
}

#undef zcache_alloc_n
zstack_t zcache_alloc_n(zone_id_t zone_id, uint32_t count, zalloc_flags_t flags, zone_cache_ops_t ops) {
    zstack_t stack = {0};
    zone_t zone = zone_by_id(zone_id);
    
    if (zone == NULL) {
        return stack;
    }

    for (uint32_t i = 0; i < count; i++) {
        void *elem = NULL;
        if (ops->zc_op_alloc) {
            elem = ops->zc_op_alloc(zone_id, flags);
        } else {
            // Fallback to using calloc if no alloc operation is provided
            elem = calloc(1, zone->z_elem_size);
        }

        if (elem == NULL) {
            // Free previously allocated elements
            while (!zstack_empty(stack)) {
                void *to_free = zstack_pop(&stack);
                if (ops->zc_op_free) {
                    ops->zc_op_free(zone_id, to_free);
                } else {
                    free(to_free);
                }
            }
            return stack;
        }

        if (ops->zc_op_mark_valid) {
            ops->zc_op_mark_valid(zone_id, elem);
        }

        zstack_push(&stack, elem);
    }

    return stack;
}

#undef zcache_free_n
void zcache_free_n(zone_id_t zone_id, zstack_t stack, zone_cache_ops_t ops) {
    while (!zstack_empty(stack)) {
        void *elem = zstack_pop(&stack);
        if (ops->zc_op_mark_invalid) {
            ops->zc_op_mark_invalid(zone_id, elem);
        }
        if (ops->zc_op_free) {
            ops->zc_op_free(zone_id, elem);
        } else {
            free(elem);
        }
    }
}

void *__unsafe_indexable zcache_mark_valid(zone_t zone,
                                           void *elem __unsafe_indexable) {
  return elem;
}

void zstack_push(zstack_t *stack, void *elem) {
    vm_offset_t *new_elements = realloc((void *)stack->z_head, (stack->z_count + 1) * sizeof(vm_offset_t));
    if (new_elements) {
        new_elements[stack->z_count] = (vm_offset_t)elem;
        stack->z_head = (vm_offset_t)new_elements;
        stack->z_count++;
    }
    // If realloc fails, we simply don't add the new element, preserving the existing stack
}

void *zstack_pop(zstack_t *stack) {
    if (zstack_empty(*stack)) {
        return NULL;
    }
    
    vm_offset_t *elements = (vm_offset_t *)stack->z_head;
    void *elem = (void *)elements[--stack->z_count];
    
    if (stack->z_count == 0) {
        free(elements);
        stack->z_head = 0;
    }
    
    return elem;
}

zstack_t zalloc_n(zone_id_t zone_id, uint32_t count, zalloc_flags_t flags) {
    zstack_t stack = {0};
    zone_t zone = zone_by_id(zone_id);
    
    if (zone == NULL) {
        return stack;
    }

    size_t elem_size = zone->z_elem_size;
    
    for (uint32_t i = 0; i < count; i++) {
        void *elem = NULL;
        
        // Simulate allocation based on flags
        if (flags & Z_NOFAIL) {
            elem = calloc(1, elem_size);  // Always succeed
        } else {
            // Simulate occasional allocation failure
            if (GetHypercallInterface()->GetFuzzedUint32InRange(0, 9) == 0) {  // 90% success rate
                elem = calloc(1, elem_size);
            }
        }
        
        if (elem == NULL) {
            // Stop allocation if we couldn't allocate an element
            break;
        }
        
        zstack_push(&stack, elem);
    }

    return stack;
}

#undef zfree_nozero_n
void zfree_nozero_n(zone_id_t zone_id, zstack_t stack) {
    void *elem = NULL;
    
    while ((elem = zstack_pop(&stack)) != NULL) {
        // In a real implementation, you might want to add the element back to the zone
        // For now, we'll just free it
        free(elem);
    }
    
    // The stack array itself is freed in zstack_pop when the last element is removed
}

void *__unsafe_indexable zcache_mark_invalid(zone_t zone,
                                             void *elem __unsafe_indexable) {
  return elem;
}

void kfree_type_impl_internal(kalloc_type_view_t kt_view,
                              void *ptr __unsafe_indexable) {
  (void)kt_view;  // Unused parameter since we don't manage memory ourselves
  free(ptr);
}

// void kfree_ext(void *kheap_or_kt_view, void *addr __unsafe_indexable,
//                vm_size_t size) {
//   free(addr);
// }

// void kfree_addr_ext(kalloc_heap_t kheap, void *addr __unsafe_indexable) {
//   free(addr);
// }

zone_id_t zone_id_for_element(void *addr, vm_size_t esize) {
  GetHypercallInterface()->Abort();
}

vm_map_size_t zone_map_size;

__startup_func void zone_cram_early(zone_t zone, vm_offset_t newmem,
                                    vm_size_t size) {}

vm_size_t zone_get_early_alloc_size(const char *name __unused,
                                    vm_size_t elem_size,
                                    zone_create_flags_t flags,
                                    vm_size_t min_elems) {
  return 0;
}

__startup_func vm_offset_t zone_early_mem_init(vm_size_t size) {
  return 0;
}

__attribute__((noinline)) uint64_t zalloc_ro_mut_atomic(zone_id_t zid,
                                                        void *elem,
                                                        vm_offset_t offset,
                                                        zro_atomic_op_t op,
                                                        uint64_t value) {
  assert(zid >= ZONE_ID__FIRST_RO && zid <= ZONE_ID__LAST_RO);

  (void)zid;
  return __zalloc_ro_mut_atomic((vm_offset_t)elem + offset, op, value);
}

#undef zalloc_id
__attribute__((always_inline)) void *zalloc_id(zone_id_t zid,
                                               zalloc_flags_t flags) {
  return zalloc_flags(&zone_array[zid], flags);
}

#undef zfree_id
void zfree_id(zone_id_t zone_id, void *addr __unsafe_indexable) {
  free(addr);
}

void zone_set_sig_eq(zone_t zone, zone_id_t sig_eq) {
  zone_security_array[zone_index(zone)].z_sig_eq = sig_eq;
}

zone_id_t zone_get_sig_eq(zone_t zone) {
  return zone_security_array[zone_index(zone)].z_sig_eq;
}

zone_t zone_by_id(size_t zid) {
  if (zid == ZONE_ID_ANY) {
    return NULL;
  }

  if (zid >= MAX_ZONES) {
    panic("zone_by_id: invalid zone id %d", zid);
  }

  zone_t z = &zone_array[zid];

  if (z->z_self != z) {
    return NULL;
  }

  return z;
}

#undef zfree_nozero
void zfree_nozero(zone_id_t zone_id, void *elem __unsafe_indexable) {
  (void)zone_id;  // Zone information is not used in this fake implementation.
  free(elem);
}
