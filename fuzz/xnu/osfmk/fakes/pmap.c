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

#include <i386/machine_routines.h>
#include <i386/pmap.h>
#include <mach/kern_return.h>
#include <vm/pmap.h>

struct pmap kernel_pmap_store;
const pmap_t kernel_pmap = &kernel_pmap_store;

void pmap_remove_options(pmap_t pmap, vm_map_address_t start,
                         vm_map_address_t end, int options) {}

void pmap_init() {}

void pmap_assert_free() {}

boolean_t pmap_is_noencrypt(ppnum_t page) {
  return false;
}

bool pmap_verify_free(ppnum_t pn) {
  return true;
}

kern_return_t pmap_enter_options(pmap_t pmap, vm_map_offset_t v, ppnum_t pn,
                                 vm_prot_t prot, vm_prot_t fault_type,
                                 unsigned int flags, boolean_t wired,
                                 unsigned int options, void *arg,
                                 pmap_mapping_type_t mapping_type) {
  return KERN_SUCCESS;
}

kern_return_t pmap_enter_options_addr(pmap_t pmap, vm_map_offset_t v,
                                      pmap_paddr_t pa, vm_prot_t prot,
                                      vm_prot_t fault_type, unsigned int flags,
                                      boolean_t wired, unsigned int options,
                                      void *arg,
                                      pmap_mapping_type_t mapping_type) {
  return KERN_SUCCESS;
}

boolean_t pmap_is_empty(pmap_t pmap, vm_map_offset_t start,
                        vm_map_offset_t end) {
  return true;
}

void pmap_reference(pmap_t pmap) {}

void mapping_free_prime() {}

// TODO(nedwill); reset pmap?
static int next_page = 0;

void *calloc(size_t nmemb, size_t size);
void free(void *ptr);

pmap_t pmap_create_options(/* Create a pmap_t. */
                           ledger_t ledger, vm_map_size_t size,
                           unsigned int flags) {
  return calloc(1, sizeof(struct pmap));
}

void pmap_destroy(pmap_t pmap) {
  free(pmap);
}

// 256 MiB
const ppnum_t NUM_PAGES = 65536;

boolean_t pmap_next_page(ppnum_t *pn) {
  *pn = next_page++;
  // TODO(nedwill): fuzz pmap
  return *pn <= NUM_PAGES;
}

kern_return_t pmap_next_page_large(ppnum_t *pn) {
  *pn = next_page++;
  // TODO(nedwill): fuzz pmap
  return *pn <= NUM_PAGES;
}

boolean_t pmap_next_page_hi(ppnum_t *pnum, boolean_t might_free) {
  *pnum = next_page++;
  return true;
}
boolean_t pmap_valid_page(ppnum_t pn) {
  // TODO(nedwill): fuzz
  return true;
}

static vm_offset_t start_pmap;

int posix_memalign(void **memptr, size_t alignment, size_t size);

void pmap_virtual_space(vm_offset_t *virtual_start, vm_offset_t *virtual_end) {
  void *ptr;
  int ret = posix_memalign(&ptr, 0x1000, 0x1000 * NUM_PAGES);
  if (ret) {
    GetHypercallInterface()->Abort();
  }
  start_pmap = (vm_offset_t)ptr;
  *virtual_start = start_pmap;
  *virtual_end = start_pmap + (0x1000 * NUM_PAGES);
}

uint_t pmap_free_pages() {
  return NUM_PAGES;
}

void pmap_zero_page(ppnum_t pn) {}
void(pmap_zero_part_page)(ppnum_t pn, vm_offset_t offset, vm_size_t len) {}

kern_return_t pmap_pre_expand_large(pmap_t pmap, vm_map_offset_t vaddr) {
  return KERN_SUCCESS;
}

void mapping_adjust() {}

ppnum_t IOMapperIOVMAlloc(unsigned pages) {
  return 0;
}

void ml_static_mfree(vm_offset_t addr, vm_size_t size) {}

vm_size_t pmap_query_pagesize(pmap_t map, vm_map_offset_t vaddr) {
  return I386_PGBYTES;
}

void pmap_protect(pmap_t pmap, vm_map_address_t s, vm_map_address_t e,
                  vm_prot_t prot) {}

uint64_t pmap_release_pages_fast() {
  return 0;
}
void pmap_clear_noencrypt(ppnum_t pn) {}

// TODO(nedwill): actually simulate physical page mappings
ppnum_t pmap_find_phys(pmap_t map, addr64_t va) {
  return 0;
}
