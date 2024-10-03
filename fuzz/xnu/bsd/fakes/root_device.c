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

#include "fuzz/host/hypercall/hypercall.h"
#include <net/if.h>
#include <sys/buf.h>
#include <sys/conf.h>
#include <sys/kern_control.h>
#include <sys/systm.h>
#include <sys/tty.h>
#include <sys/types.h>
#include <sys/uio.h>

#define DEVMAXNAMESIZE 32
extern unsigned char rootdevice[DEVMAXNAMESIZE];

static int fuzzed_open(dev_t dev, int flags, int devtype, struct proc *p) {
    return 0;
}

static int fuzzed_close(dev_t dev, int flags, int devtype, struct proc *p) {
    return 0;
}

static void fuzzed_strategy(struct buf *bp) {
    buf_biodone(bp);
}

static int fuzzed_ioctl(dev_t dev, u_long cmd, caddr_t data, int fflag, struct proc *p) {
    return 0;
}

static int fuzzed_psize(dev_t dev) {
    return 0;
}

static int fuzzed_read(dev_t dev, struct uio *uio, int ioflag) {
    return 0;
}

static int fuzzed_write(dev_t dev, struct uio *uio, int ioflag) {
    return 0;
}

static const struct bdevsw fuzzed_bdevsw = {
    .d_open     = fuzzed_open,
    .d_close    = fuzzed_close,
    .d_strategy = fuzzed_strategy,
    .d_ioctl    = fuzzed_ioctl,
    .d_dump     = eno_dump,
    .d_psize    = fuzzed_psize,
    .d_type     = D_DISK,
};

static const struct cdevsw fuzzed_cdevsw = {
    .d_open       = fuzzed_open,
    .d_close      = fuzzed_close,
    .d_read       = fuzzed_read,
    .d_write      = fuzzed_write,
    .d_ioctl      = fuzzed_ioctl,
    .d_stop       = eno_stop,
    .d_reset      = eno_reset,
    .d_ttys       = NULL,
    .d_select     = eno_select,
    .d_mmap       = eno_mmap,
    .d_strategy   = eno_strat,
    .d_reserved_1 = eno_getc,
    .d_reserved_2 = eno_putc,
    .d_type       = D_DISK,
};

static struct ifnet *fuzzed_ifp = NULL;

static errno_t fuzzed_output(ifnet_t interface, mbuf_t m) {
    // Handle packet output (for now just free the mbuf)
    m_freem(m);
    return 0;
}

static errno_t fuzzed_demux(ifnet_t interface, mbuf_t m, char *header, protocol_family_t *protocol_family) {
    // Handle packet demux (for now just return an error)
    return EOPNOTSUPP;
}

static errno_t fuzzed_add_proto(ifnet_t interface, protocol_family_t protocol_family, const struct ifnet_demux_desc *demux_list, u_int32_t demux_count) {
    // Handle adding protocol (for now just return success)
    return 0;
}

static errno_t fuzzed_del_proto(ifnet_t interface, protocol_family_t protocol_family) {
    // Handle deleting protocol (for now just return success)
    return 0;
}

static errno_t fuzzed_check_multi(ifnet_t interface, const struct sockaddr *multicast) {
    // Handle multicast checking (for now just return success)
    return 0;
}

static errno_t fuzzed_ifnet_ioctl(ifnet_t interface, u_long cmd, void *data) {
    struct ifreq *ifr = (struct ifreq *)data;
    switch (cmd) {
        case SIOCSIFFLAGS:
            // Handle setting interface flags here
            ifnet_set_flags(interface, IFF_UP | IFF_RUNNING, IFF_UP | IFF_RUNNING);
            return 0;
        default:
            return EOPNOTSUPP;
    }
}

static void fuzzed_initialize(void) {
    struct ifnet_init_params params;

    bzero(&params, sizeof(params));
    params.name = "fuzzed";
    params.unit = 0;
    params.family = IFNET_FAMILY_ETHERNET;
    params.type = IFT_ETHER;
    params.output = fuzzed_output;
    params.demux = fuzzed_demux;
    params.add_proto = fuzzed_add_proto;
    params.del_proto = fuzzed_del_proto;
    params.check_multi = fuzzed_check_multi;
    params.ioctl = fuzzed_ifnet_ioctl;
    params.broadcast_addr = NULL;  // Set to a valid broadcast address if needed
    params.broadcast_len = 0;      // Set to the correct length if needed

    if (ifnet_allocate(&params, &fuzzed_ifp) != 0) {
        printf("Failed to allocate ifnet structure for fuzzed0\n");
        return;
    }

    // Set additional parameters
    ifnet_set_flags(fuzzed_ifp, IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST, 0);
    ifnet_set_baudrate(fuzzed_ifp, 0); // Set to the appropriate baudrate if known

    if (ifnet_attach(fuzzed_ifp, NULL) != 0) {
        printf("Failed to attach fuzzed0 interface\n");
        ifnet_release(fuzzed_ifp);
        fuzzed_ifp = NULL;
    } else {
        printf("Successfully initialized and attached fuzzed0 interface\n");
    }
}

kern_return_t IOFindBSDRoot() {
    // Initialize fuzzed interface
    fuzzed_initialize();

    // Add the fuzzed block device using bdevsw_add
    int fuzzed_bmajor = bdevsw_add(-1, &fuzzed_bdevsw);
    if (fuzzed_bmajor < 0) {
        GetHypercallInterface()->ThreadPrintf("IOFindBSDRoot: bdevsw_add() returned %d\n", fuzzed_bmajor);
        return KERN_FAILURE;
    }

    // Add the fuzzed character device using cdevsw_add
    int fuzzed_cmajor = cdevsw_add_with_bdev(-1, &fuzzed_cdevsw, fuzzed_bmajor);
    if (fuzzed_cmajor < 0) {
        GetHypercallInterface()->ThreadPrintf("IOFindBSDRoot: cdevsw_add() returned %d\n", fuzzed_cmajor);
        return KERN_FAILURE;
    }

    // Set rootdevice and rootdev to the created fuzzed device
    int minor_number = 0;
    int err = snprintf((char*)rootdevice, sizeof(rootdevice), "fuzzed%d", minor_number);
    if (err < 0 || (size_t)err >= sizeof(rootdevice)) {
        GetHypercallInterface()->ThreadPrintf("IOFindBSDRoot: snprintf() failed\n");
        return KERN_FAILURE;
    }
    rootdev = makedev(fuzzed_bmajor, minor_number);

    // Set flags, for example, 0 for a non-network device
    u_int32_t flags = 0;

    return KERN_SUCCESS;
}
