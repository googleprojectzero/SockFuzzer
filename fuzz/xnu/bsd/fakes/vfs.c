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

#include <i386/types.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/_types/_caddr_t.h>
#include <sys/_types/_s_ifmt.h>
#include <sys/_types/_u_int.h>
#include <sys/cdefs.h>
#include <sys/errno.h>
#include <sys/mount.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/vnode.h>
#include <sys/vnode_if.h>
#include <sys/vnode_internal.h>

#include "fuzz/host/hypercall/hypercall.h"

struct mount;

void abort();

#define VOPFUNC int (*)(void *)
int (**fuzzed_vnodeop_p)(void *);

int fuzzed_mount(struct mount *mp, vnode_t devvp, user_addr_t data,
                 vfs_context_t context) {
  return 0;
}

int fuzzed_start(struct mount *mp, int flags, vfs_context_t context) {
  return 0;
}

int fuzzed_unmount(struct mount *mp, int mntflags, vfs_context_t context) {
  return 0;
}

int fuzzed_root(struct mount *mp, struct vnode **vpp, vfs_context_t context) {
  if (!vpp) {
    return EINVAL;
  }
  struct vnode_fsparam vnfs_param = {
      .vnfs_mp = mp,
      // TODO(nedwill): fuzz this with VDIR, VBLK, etc.
      .vnfs_str = "fuzzed_vnfs",
      .vnfs_vtype = VREG,
      .vnfs_dvp = NULL,
      .vnfs_fsnode = (void *)1,
      .vnfs_vops = fuzzed_vnodeop_p,
      .vnfs_markroot = true,
      .vnfs_marksystem = false,
      .vnfs_rdev = 0,
      // TODO(nedwill): can't fuzz during boot stage
      .vnfs_filesize =
          1024,  // GetHypercallInterface()->GetFuzzedUint32InRange(0, 1024),
                 // TODO(nedwill)
      .vnfs_cnp = NULL,
      .vnfs_flags = VNFS_CANTCACHE | VNFS_NOCACHE};

  return vnode_create(VNCREATE_FLAVOR, VCREATESIZE, &vnfs_param, vpp);
}

int fuzzed_quotactl(struct mount *mp, int cmds, uid_t uid, caddr_t arg,
                    vfs_context_t context) {
  // TODO(nedwill): support this
  return 0;
}

int fuzzed_getattr(struct mount *mp, struct vfs_attr *attr,
                   vfs_context_t context) {
  // GetHypercallInterface()->GetFuzzedBytes((uint8_t*)attr, sizeof(struct vfs_attr));
  return 0;
}

int fuzzed_sync(struct mount *mp, int waitfor, vfs_context_t context) {
  return 0;
}

int fuzzed_vget(struct mount *mp, ino64_t ino, struct vnode **vpp,
                vfs_context_t context) {
  abort();
  return 0;
}
int fuzzed_fhtovp(struct mount *mp, int fhlen, unsigned char *fhp,
                  struct vnode **vpp, vfs_context_t context) {
  abort();
  return 0;
}
int fuzzed_vptofh(struct vnode *vp, int *fhlen, unsigned char *fhp,
                  vfs_context_t context) {
  abort();
  return 0;
}
int fuzzed_init(struct vfsconf *conf) {
  return 0;
}
int fuzzed_sysctl(int *a1, u_int a2, user_addr_t a3, size_t *a4, user_addr_t a5,
                  size_t a6, vfs_context_t context) {
  return 0;
}
int fuzzed_setattr(struct mount *mp, struct vfs_attr *a2,
                   vfs_context_t context) {
  abort();
  return 0;
}
int fuzzed_ioctl(struct mount *mp, u_long command, caddr_t data, int flags,
                 vfs_context_t context) {
  return 0;
}
int fuzzed_vget_snapdir(struct mount *mp, struct vnode **vpp,
                        vfs_context_t context) {
  return 1;
}

int fuzzed_mountroot(mount_t mp, vnode_t rvp, __unused vfs_context_t ctx) {
  return 0;
}

struct vfsops fuzzed_vfsops = {
    .vfs_mount = fuzzed_mount,
    .vfs_start = fuzzed_start,
    .vfs_unmount = fuzzed_unmount,
    .vfs_root = fuzzed_root,
    .vfs_quotactl = fuzzed_quotactl,
    .vfs_getattr = fuzzed_getattr,
    .vfs_sync = fuzzed_sync,
    .vfs_vget = fuzzed_vget,
    .vfs_fhtovp = fuzzed_fhtovp,
    .vfs_vptofh = fuzzed_vptofh,
    .vfs_init = fuzzed_init,
    .vfs_sysctl = fuzzed_sysctl,
    .vfs_setattr = fuzzed_setattr,
    .vfs_ioctl = fuzzed_ioctl,
    .vfs_vget_snapdir = fuzzed_vget_snapdir,
};

int unsupported_function(void *ptr) {
  abort();
  return ENOTSUP;
}

int nop_function(void *ptr) {
  return ENOTSUP;
}

int fuzzed_pagein(struct vnop_pagein_args *args) {
  // TODO(nedwill): fill in data here?
  return GetHypercallInterface()->GetFuzzedBool();
}

int fuzzed_vnop_getattr(struct vnop_getattr_args *args) {
  // TODO(nedwill): fuzz with grammar
  // GetHypercallInterface()->GetFuzzedBytes((uint8_t *)args->a_vap, sizeof(*args->a_vap));
  // TODO(nedwill): let the fuzzer discover these flags
  args->a_vap->va_supported = 0xFFFFFFFFFFFFFFFF;
  args->a_vap->va_type = VREG;
  args->a_vap->va_mode = S_IXUSR | S_IXGRP | S_IXOTH;
  args->a_vap->va_acl = NULL;
  // printf("setting vap->va_data_size (%p, %d)\n", args->a_vap, 1024);
  args->a_vap->va_data_size =
      1024;  // GetHypercallInterface()->GetFuzzedUint32InRange(0, 1024);
  return 0;
}

int fuzzed_pathconf(struct vnop_pathconf_args *ap) {
  *ap->a_retval =
      GetHypercallInterface()->GetFuzzedUint32InRange(0, UINT32_MAX);
  return 0;
}

int fuzzed_open(struct vnop_open_args *args) {
  return 0;
}

int fuzzed_close(struct vnop_close_args *args) {
  return 0;
}

int fuzzed_mmap_check(struct vnop_mmap_check_args *args) {
  return 0;
}

int fuzzed_fsync(struct vnop_fsync_args *args) {
  return 0;
}

void *malloc(size_t size);

int fuzzed_read(struct vnop_read_args *args) {
  uint32_t length =
      1024;  // GetHypercallInterface()->GetFuzzedUint32InRange(0, 1024);
  uint8_t *buffer = malloc(length);
  if (!buffer) {
    length = 0;
  }
  GetHypercallInterface()->GetFuzzedBytes(buffer, length);
  GetHypercallInterface()->BlockCopyin();
  uiomove((char *)buffer, length, args->a_uio);
  GetHypercallInterface()->UnblockCopyin();
  return 0;
}

errno_t fuzzed_vnop_inactive(struct vnop_inactive_args *ap) {
  vnode_t vp = ap->a_vp;
  vfs_context_t ctx = ap->a_context;

  // Check if the vnode is already marked for recycle
  if (vnode_isrecycled(vp)) {
    printf("Vnode %p is already marked for recycle\n", vp);
    return 0;
  }

  vnode_recycle(vp);

  return 0;
}

errno_t
fuzzed_vnop_reclaim(struct vnop_reclaim_args *ap)
{
    vnode_t vp = ap->a_vp;
    vfs_context_t ctx = ap->a_context;

    vp->v_mount = NULL;
    vp->v_op = NULL;

    return 0;
}

const struct vnodeopv_entry_desc fuzzed_vnodeop_entries[] = {
    {.opve_op = &vnop_default_desc, .opve_impl = (VOPFUNC)unsupported_function},
    {.opve_op = &vnop_lookup_desc, .opve_impl = (VOPFUNC)unsupported_function},
    {.opve_op = &vnop_create_desc, .opve_impl = (VOPFUNC)unsupported_function},
    {.opve_op = &vnop_open_desc, .opve_impl = (VOPFUNC)fuzzed_open},
    {.opve_op = &vnop_mknod_desc, .opve_impl = (VOPFUNC)unsupported_function},
    {.opve_op = &vnop_close_desc, .opve_impl = (VOPFUNC)fuzzed_close},
    {.opve_op = &vnop_access_desc, .opve_impl = (VOPFUNC)unsupported_function},
    {.opve_op = &vnop_getattr_desc, .opve_impl = (VOPFUNC)fuzzed_vnop_getattr},
    {.opve_op = &vnop_setattr_desc, .opve_impl = (VOPFUNC)nop_function},
    {.opve_op = &vnop_read_desc, .opve_impl = (VOPFUNC)fuzzed_read},
    {.opve_op = &vnop_write_desc, .opve_impl = (VOPFUNC)unsupported_function},
    {.opve_op = &vnop_ioctl_desc, .opve_impl = (VOPFUNC)nop_function},
    {.opve_op = &vnop_select_desc, .opve_impl = (VOPFUNC)unsupported_function},
    {.opve_op = &vnop_mmap_check_desc, .opve_impl = (VOPFUNC)fuzzed_mmap_check},
    {.opve_op = &vnop_mmap_desc, .opve_impl = (VOPFUNC)nop_function},
    {.opve_op = &vnop_fsync_desc, .opve_impl = (VOPFUNC)fuzzed_fsync},
    {.opve_op = &vnop_remove_desc, .opve_impl = (VOPFUNC)unsupported_function},
    {.opve_op = &vnop_link_desc, .opve_impl = (VOPFUNC)unsupported_function},
    {.opve_op = &vnop_rename_desc, .opve_impl = (VOPFUNC)unsupported_function},
    {.opve_op = &vnop_mkdir_desc, .opve_impl = (VOPFUNC)unsupported_function},
    {.opve_op = &vnop_rmdir_desc, .opve_impl = (VOPFUNC)unsupported_function},
    {.opve_op = &vnop_symlink_desc, .opve_impl = (VOPFUNC)unsupported_function},
    {.opve_op = &vnop_readdir_desc, .opve_impl = (VOPFUNC)unsupported_function},
    {.opve_op = &vnop_readlink_desc,
     .opve_impl = (VOPFUNC)unsupported_function},
    {.opve_op = &vnop_inactive_desc,
     .opve_impl = (VOPFUNC)fuzzed_vnop_inactive},
    {.opve_op = &vnop_reclaim_desc, .opve_impl = (VOPFUNC)fuzzed_vnop_reclaim},
    {.opve_op = &vnop_strategy_desc,
     .opve_impl = (VOPFUNC)unsupported_function},
    {.opve_op = &vnop_pathconf_desc, .opve_impl = (VOPFUNC)fuzzed_pathconf},
    {.opve_op = &vnop_advlock_desc, .opve_impl = (VOPFUNC)nop_function},
    {.opve_op = &vnop_bwrite_desc, .opve_impl = (VOPFUNC)unsupported_function},
    {.opve_op = &vnop_monitor_desc, .opve_impl = (VOPFUNC)nop_function},
    {.opve_op = &vnop_mnomap_desc, .opve_impl = (VOPFUNC)nop_function},
    {.opve_op = &vnop_select_desc, .opve_impl = (VOPFUNC)nop_function},
    {.opve_op = &vnop_pagein_desc, .opve_impl = (VOPFUNC)fuzzed_pagein},
    {.opve_op = &vnop_pageout_desc, .opve_impl = (VOPFUNC)unsupported_function},
    {.opve_op = &vnop_copyfile_desc,
     .opve_impl = (VOPFUNC)unsupported_function},
    {.opve_op = &vnop_blktooff_desc,
     .opve_impl = (VOPFUNC)unsupported_function},
    {.opve_op = &vnop_offtoblk_desc, .opve_impl = (VOPFUNC)nop_function},
    {.opve_op = &vnop_blockmap_desc,
     .opve_impl = (VOPFUNC)unsupported_function},
    {.opve_op = &vnop_getxattr_desc, .opve_impl = (VOPFUNC)nop_function},
    {.opve_op = &vnop_listxattr_desc, .opve_impl = (VOPFUNC)nop_function},
    {.opve_op = &vnop_setxattr_desc, .opve_impl = (VOPFUNC)nop_function},
    {.opve_op = &vnop_removexattr_desc, .opve_impl = (VOPFUNC)nop_function},
    {.opve_op = (struct vnodeop_desc *)NULL, .opve_impl = (VOPFUNC)NULL}};

const struct vnodeopv_desc fuzzed_vnodeop_opv_desc = {
    .opv_desc_vector_p = &fuzzed_vnodeop_p,
    .opv_desc_ops = fuzzed_vnodeop_entries};
