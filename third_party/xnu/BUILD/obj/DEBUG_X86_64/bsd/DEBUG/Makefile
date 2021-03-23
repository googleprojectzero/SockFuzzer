SOURCE_DIR=/Users/nedwill/dev/sockfuzzer/third_party/xnu
export CONFIG_DEFINES = -DMACH -DNO_DIRECT_RPC -DAH_ALL_CRYPTO -DTRAFFIC_MGT -DMULTICAST -DICMP_BANDLIM -DIFNET_INPUT_SANITY_CHK -DPSYNCH -DFLOW_DIVERT -DNECP -DCONTENT_FILTER -DPACKET_MANGLER -DOLD_SEMWAIT_SIGNAL -DCONFIG_MBUF_JUMBO -DCONFIG_IMAGEBOOT_CHUNKLIST -DCONFIG_WORKQUEUE -DCONFIG_WORKLOOP_DEBUG -DNULLFS -DBINDFS -DCONFIG_DEV_KMEM -DNAMEDSTREAMS -DCONFIG_APPLEDOUBLE -DCONFIG_VOLFS -DCONFIG_IMGSRC_ACCESS -DCONFIG_EXT_RESOLVER -DCONFIG_SEARCHFS -DCONFIG_MNT_SUID -DCONFIG_MNT_ROOTSNAP -DCONFIG_ROSV_STARTUP -DCONFIG_FIRMLINKS -DCONFIG_MOUNT_VM -DCONFIG_MOUNT_PREBOOTRECOVERY -DCONFIG_DATALESS_FILES -DCONFIG_BASESYSTEMROOT -DCONFIG_NFS_GSS -DCONFIG_NETBOOT -DIPSEC -DIPSEC_ESP -DCRYPTO_SHA2 -DENCRYPTED_SWAP -DCONFIG_IMG4 -DCONFIG_KN_HASHSIZE="64" -DCONFIG_VNODES="263168" -DCONFIG_NC_HASH="4096" -DCONFIG_VFS_NAMES="4096" -DCONFIG_MAX_CLUSTERS="8" -DCONFIG_MIN_NBUF="256" -DCONFIG_MIN_NIOBUF="128" -DCONFIG_NMBCLUSTERS="((1024 * 512) / MCLBYTES)" -DCONFIG_TCBHASHSIZE="4096" -DCONFIG_ICMP_BANDLIM="250" -DCONFIG_AIO_MAX="90" -DCONFIG_AIO_PROCESS_MAX="16" -DCONFIG_AIO_THREAD_COUNT="4" -DCONFIG_MAXVIFS="32" -DCONFIG_MFCTBLSIZ="256" -DCONFIG_MSG_BSIZE_REL="16384" -DCONFIG_MSG_BSIZE_DEV="131072" -DCONFIG_MSG_BSIZE="CONFIG_MSG_BSIZE_DEV" -DCONFIG_IPC_TABLE_ENTRIES_STEPS="256" -DCONFIG_VSPRINTF -DCONFIG_DYNAMIC_CODE_SIGNING -DCONFIG_CODE_DECRYPTION -DCONFIG_PROTECT -DCONFIG_KEYPAGE_WP -DCONFIG_MEMORYSTATUS -DCONFIG_DIRTYSTATUS_TRACKING -DCONFIG_LTABLE_STATS -DCONFIG_LTABLE_DEBUG -DCONFIG_WAITQ_STATS -DCONFIG_WAITQ_DEBUG -DCONFIG_PHYS_WRITE_ACCT -DVM_PRESSURE_EVENTS -DCONFIG_BACKGROUND_QUEUE -DCONFIG_LEDGER_INTERVAL_MAX -DCONFIG_IOSCHED -DIMPORTANCE_TRACE -DCONFIG_TELEMETRY -DCONFIG_PROC_UUID_POLICY -DCONFIG_COREDUMP -DCONFIG_VNGUARD -DHIBERNATION -DIOKITCPP -DIOKITSTATS -DIOTRACKING -DCONFIG_SLEEP -DCONFIG_MAX_THREADS="500" -DLIBKERNCPP -DCONFIG_BLOCKS -DCONFIG_KEC_FIPS -DCONFIG_KEXT_BASEMENT -DCONFIG_PERSONAS -DCONFIG_ARCADE -DCONFIG_SETUID -DCONFIG_KAS_INFO -DMACH_MP_DEBUG -DCONFIG_ZCACHE -DCONFIG_ZLEAKS -DCONFIG_TASK_ZONE_INFO -DLOCK_STATS -DKPERF -DKPC -DPGO -DDEBUG -DMACH_BSD -DIOKIT -DCONFIG_THREAD_MAX="2560" -DCONFIG_TASK_MAX="1024" -DCONFIG_ZONE_MAP_MIN="120586240" -DCONFIG_ZLEAK_ALLOCATION_MAP_NUM="16384" -DCONFIG_ZLEAK_TRACE_MAP_NUM="8192" -DCONFIG_SCHED_TRADITIONAL -DCONFIG_SCHED_PROTO -DCONFIG_SCHED_GRRR -DCONFIG_SCHED_GRRR_CORE -DCONFIG_SCHED_MULTIQ -DCONFIG_SCHED_TIMESHARE_CORE -DCONFIG_SCHED_SFI -DCONFIG_GZALLOC -DMACH_KDP -DCONFIG_SERIAL_KDP -DCONFIG_KDP_INTERACTIVE_DEBUGGING -DCONFIG_TASKWATCH -DCONFIG_XNUPOST -DCONFIG_ATM -DCONFIG_COALITIONS -DCONFIG_SYSDIAGNOSE -DCONFIG_CSR -DSERIAL_CONSOLE -DVIDEO_CONSOLE -DCONFIG_REQUIRES_U32_MUNGING -DCOPYOUT_SHIM -DCONFIG_MACH_BRIDGE_SEND_TIME -DCONFIG_32BIT_TELEMETRY -DCONFIG_DELAY_IDLE_SLEEP -DCONFIG_PROC_UDATA_STORAGE -DPAL_I386 -DCONFIG_MCA -DCONFIG_VMX -DCONFIG_MTRR -DCONFIG_MACF_LAZY_VNODE_LABELS -DHYPERVISOR -DCONFIG_MACH_APPROXIMATE_TIME
OSFMK_MACHINE=x86_64
#
# Copyright (c) 2000-2020 Apple Inc. All rights reserved.
#
# @APPLE_LICENSE_HEADER_START@
#
# The contents of this file constitute Original Code as defined in and
# are subject to the Apple Public Source License Version 1.1 (the
# "License").  You may not use this file except in compliance with the
# License.  Please obtain a copy of the License at
# http://www.apple.com/publicsource and read it before using this file.
#
# This Original Code and all software distributed under the License are
# distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
# EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
# INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
# License for the specific language governing rights and limitations
# under the License.
#
# @APPLE_LICENSE_HEADER_END@
#

#
# Mach Operating System
# Copyright (c) 1986 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement specifies
# the terms and conditions for use and redistribution.
#

export MakeInc_cmd=${SRCROOT}/makedefs/MakeInc.cmd
export MakeInc_def=${SRCROOT}/makedefs/MakeInc.def
export MakeInc_rule=${SRCROOT}/makedefs/MakeInc.rule
export MakeInc_dir=${SRCROOT}/makedefs/MakeInc.dir

include $(MakeInc_cmd)
include $(MakeInc_def)

#
# XXX: CFLAGS
#
CFLAGS+= -include meta_features.h -DDRIVER_PRIVATE \
	-D_KERNEL_BUILD -DKERNEL_BUILD -DMACH_KERNEL -DBSD_BUILD \
	-DBSD_KERNEL_PRIVATE -DLP64_DEBUG=0 \
        -Warray-bounds-pointer-arithmetic
SFLAGS+= -include meta_features.h

#
# Directories for mig generated files
#
COMP_SUBDIRS =

#
#  Make sure we don't remove this by accident if interrupted at the wrong
#  time.
#
.PRECIOUS: Makefile

#
#  Theses macros are filled in by the config program depending on the
#  current configuration.  The MACHDEP macro is replaced by the
#  contents of the machine dependent makefile template and the others
#  are replaced by the corresponding symbol definitions for the
#  configuration.
#

OBJS=nfs4_subs.o nfs4_vnops.o krpc_subr.o nfs_bio.o nfs_boot.o nfs_gss.o \
	nfs_lock.o nfs_node.o nfs_serv.o nfs_socket.o nfs_srvcache.o \
	nfs_subs.o nfs_syscalls.o nfs_vfsops.o nfs_vnops.o nfs_upcall.o \
	gss_krb5_mech.o ccrypto.o netboot.o dtrace.o lockprof.o \
	lockstat.o dtrace_ptss.o dtrace_subr.o dtrace_glue.o \
	dtrace_xoroshiro128_plus.o blist.o fbt.o fbt_blacklist.o sdt.o \
	sdt_subr.o systrace.o profile_prvd.o fasttrap.o systrace_args.o \
	randomdev.o memdev.o mem.o munge.o unix_startup.o vn.o shadow.o \
	crc16.o crc32.o random.o scanc.o strsep.o bcd.o memchr.o \
	url_encode.o vfs_attrlist.o vfs_bio.o vfs_cache.o vfs_cluster.o \
	vfs_conf.o vfs_fslog.o vfs_init.o vfs_lookup.o vfs_quota.o \
	vfs_subr.o vfs_syscalls.o vfs_support.o vfs_utfconv.o \
	vfs_unicode.o vfs_vnops.o vfs_xattr.o vnode_if.o kpi_vfs.o \
	vfs_fsevents.o vfs_cprotect.o doc_tombstone.o \
	vfs_disk_conditioner.o dead_vnops.o devfs_fdesc_support.o \
	fifo_vnops.o spec_vnops.o devfs_tree.o devfs_vnops.o \
	devfs_vfsops.o decmpfs.o net_stubs.o bpf.o bpf_filter.o \
	if_bridge.o if.o init.o dlil.o ether_if_module.o \
	ether_inet_pr_module.o ether_inet6_pr_module.o if_loop.o \
	if_mib.o if_vlan.o if_fake.o if_headless.o if_6lowpan.o \
	multicast_list.o if_bond.o devtimer.o ndrv.o radix.o raw_cb.o \
	raw_usrreq.o route.o rtsock.o netsrc.o ntstat.o net_perf.o \
	if_gif.o if_stf.o if_ports_used.o if_low_power_mode.o \
	kpi_interface.o kpi_protocol.o kpi_interfacefilter.o \
	net_str_id.o if_utun.o if_ipsec.o necp.o necp_client.o \
	network_agent.o if_pflog.o nat464_utils.o pf.o pf_if.o \
	pf_ioctl.o pf_norm.o pf_osfp.o pf_pbuf.o pf_ruleset.o pf_table.o \
	iptap.o pktap.o if_llreach.o flowhash.o flowadv.o \
	content_filter.o content_filter_crypto.o packet_mangler.o \
	if_llatbl.o nwk_wq.o restricted_in_port.o classq.o classq_sfb.o \
	classq_subr.o classq_util.o classq_fq_codel.o pktsched.o \
	pktsched_fq_codel.o pktsched_netem.o cpu_in_cksum_gen.o \
	in_cksum.o igmp.o in.o dhcp_options.o in_arp.o in_mcast.o \
	in_pcb.o in_pcblist.o in_proto.o in_rmx.o in_stat.o in_tclass.o \
	ip_dummynet.o ip_icmp.o ip_id.o ip_input.o ip_output.o raw_ip.o \
	tcp_cache.o tcp_input.o tcp_output.o tcp_sack.o tcp_subr.o \
	tcp_timer.o tcp_usrreq.o tcp_cc.o tcp_newreno.o tcp_cubic.o \
	cbrtf.o tcp_ledbat.o tcp_log.o udp_usrreq.o in_gif.o ip_ecn.o \
	ip_encap.o kpi_ipfilter.o flow_divert.o mp_proto.o mp_pcb.o \
	mptcp.o mptcp_subr.o mptcp_usrreq.o mptcp_opt.o mptcp_timer.o \
	ah_core.o ah_input.o ah_output.o esp_core.o esp_input.o \
	esp_output.o esp_rijndael.o esp_chachapoly.o ipsec.o dest6.o \
	frag6.o icmp6.o in6.o in6_cga.o in6_cksum.o in6_gif.o \
	ip6_forward.o in6_ifattach.o ip6_input.o ip6_output.o in6_src.o \
	in6_mcast.o in6_pcb.o in6_proto.o in6_rmx.o mld6.o nd6.o \
	nd6_nbr.o nd6_prproxy.o nd6_rtr.o nd6_rti.o nd6_send.o raw_ip6.o \
	route6.o scope6.o udp6_output.o udp6_usrreq.o ip6_id.o \
	sixxlowpan.o frame802154.o linkaddr.o key.o key_debug.o \
	keysock.o keydb.o multi_layer_pkt_log.o entropy_sysctl.o audit.o \
	audit_arg.o audit_bsd.o audit_bsm.o audit_bsm_errno.o \
	audit_bsm_fcntl.o audit_bsm_domain.o audit_bsm_klib.o \
	audit_bsm_socket_type.o audit_bsm_token.o audit_kevents.o \
	audit_mac.o audit_pipe.o audit_session.o audit_syscalls.o \
	audit_worker.o pthread_shims.o pthread_priority.o \
	pthread_workqueue.o bsd_init.o init_sysent.o kdebug.o \
	kern_acct.o kern_aio.o kern_authorization.o kern_backtrace.o \
	kern_clock.o kern_core.o kern_credential.o kern_cs.o kern_csr.o \
	kern_symfile.o kern_descrip.o kern_guarded.o kern_event.o \
	kern_control.o kern_exec.o kern_exit.o kern_ktrace.o \
	kern_lockf.o kern_fork.o kern_asl.o kern_malloc.o kern_mman.o \
	kern_persona.o kern_physio.o kern_priv.o kern_proc.o kern_prot.o \
	kern_resource.o kern_shutdown.o kern_sig.o kern_subr.o \
	kern_synch.o kern_sysctl.o kern_newsysctl.o kern_memorystatus.o \
	kern_memorystatus_freeze.o kern_memorystatus_notify.o kern_mib.o \
	kpi_mbuf.o kern_sfi.o kern_time.o kern_xxx.o mach_process.o \
	mcache.o stackshot.o subr_log.o subr_prf.o subr_sbuf.o \
	subr_xxx.o sys_eventlink.o sys_generic.o sys_pipe.o sys_socket.o \
	sys_domain.o sys_coalition.o sys_persona.o sys_ulock.o \
	sys_work_interval.o syscalls.o tty.o tty_compat.o tty_conf.o \
	tty_dev.o tty_ptmx.o tty_pty.o tty_subr.o tty_tty.o ubc_subr.o \
	uipc_domain.o uipc_mbuf.o uipc_mbuf2.o uipc_proto.o \
	uipc_socket.o uipc_socket2.o uipc_syscalls.o uipc_usrreq.o \
	vsock_domain.o sysv_ipc.o sysv_shm.o sysv_sem.o sysv_msg.o \
	mach_fat.o mach_loader.o posix_sem.o posix_shm.o qsort.o \
	kpi_socket.o kpi_socketfilter.o proc_info.o process_policy.o \
	kern_overrides.o socket_info.o subr_eventhandler.o sys_reason.o \
	vnode_pager.o vm_unix.o dp_backing_file.o \
	vm_compressor_backing_file.o kern_ntptime.o ux_exception.o \
	param.o ioconf.o imageboot.o chunklist.o kperfbsd.o kern_kpc.o \
	proc_uuid_policy.o profile_runtime.o profile_runtime_data.o \
	null_subr.o null_vfsops.o null_vnops.o bind_subr.o bind_vfsops.o \
	bind_vnops.o bsd_tests.o copyio_tests.o pmap_test_sysctl.o \
	ptrauth_data_tests_sysctl.o skywalk_stubs.o conf.o cons.o km.o \
	kern_machdep.o stubs.o systemcalls.o sysctl.o unix_signal.o \
	dtrace_isa.o dtrace_subr_x86.o fbt_x86.o sdt_x86.o \
	fasttrap_isa.o instr_size.o dis_tables.o policy_check.o \
	bsd_stubs.o 

LIBOBJS=qsort.o 

CFILES=\
	$(SOURCE_DIR)/bsd/nfs/nfs4_subs.c \
	$(SOURCE_DIR)/bsd/nfs/nfs4_vnops.c \
	$(SOURCE_DIR)/bsd/nfs/krpc_subr.c \
	$(SOURCE_DIR)/bsd/nfs/nfs_bio.c \
	$(SOURCE_DIR)/bsd/nfs/nfs_boot.c \
	$(SOURCE_DIR)/bsd/nfs/nfs_gss.c \
	$(SOURCE_DIR)/bsd/nfs/nfs_lock.c \
	$(SOURCE_DIR)/bsd/nfs/nfs_node.c \
	$(SOURCE_DIR)/bsd/nfs/nfs_serv.c \
	$(SOURCE_DIR)/bsd/nfs/nfs_socket.c \
	$(SOURCE_DIR)/bsd/nfs/nfs_srvcache.c \
	$(SOURCE_DIR)/bsd/nfs/nfs_subs.c \
	$(SOURCE_DIR)/bsd/nfs/nfs_syscalls.c \
	$(SOURCE_DIR)/bsd/nfs/nfs_vfsops.c \
	$(SOURCE_DIR)/bsd/nfs/nfs_vnops.c \
	$(SOURCE_DIR)/bsd/nfs/nfs_upcall.c \
	$(SOURCE_DIR)/bsd/nfs/gss/gss_krb5_mech.c \
	$(SOURCE_DIR)/bsd/nfs/gss/ccrypto.c \
	$(SOURCE_DIR)/bsd/kern/netboot.c \
	$(SOURCE_DIR)/bsd/dev/dtrace/dtrace.c \
	$(SOURCE_DIR)/bsd/dev/dtrace/lockprof.c \
	$(SOURCE_DIR)/bsd/dev/dtrace/lockstat.c \
	$(SOURCE_DIR)/bsd/dev/dtrace/dtrace_ptss.c \
	$(SOURCE_DIR)/bsd/dev/dtrace/dtrace_subr.c \
	$(SOURCE_DIR)/bsd/dev/dtrace/dtrace_glue.c \
	$(SOURCE_DIR)/bsd/dev/dtrace/dtrace_xoroshiro128_plus.c \
	$(SOURCE_DIR)/bsd/dev/dtrace/blist.c \
	$(SOURCE_DIR)/bsd/dev/dtrace/fbt.c \
	$(SOURCE_DIR)/bsd/dev/dtrace/fbt_blacklist.c \
	$(SOURCE_DIR)/bsd/dev/dtrace/sdt.c \
	$(SOURCE_DIR)/bsd/dev/dtrace/sdt_subr.c \
	$(SOURCE_DIR)/bsd/dev/dtrace/systrace.c \
	$(SOURCE_DIR)/bsd/dev/dtrace/profile_prvd.c \
	$(SOURCE_DIR)/bsd/dev/dtrace/fasttrap.c \
	./systrace_args.c \
	$(SOURCE_DIR)/bsd/dev/random/randomdev.c \
	$(SOURCE_DIR)/bsd/dev/memdev.c \
	$(SOURCE_DIR)/bsd/dev/mem.c \
	$(SOURCE_DIR)/bsd/dev/munge.c \
	$(SOURCE_DIR)/bsd/dev/unix_startup.c \
	$(SOURCE_DIR)/bsd/dev/vn/vn.c \
	$(SOURCE_DIR)/bsd/dev/vn/shadow.c \
	$(SOURCE_DIR)/bsd/libkern/crc16.c \
	$(SOURCE_DIR)/bsd/libkern/crc32.c \
	$(SOURCE_DIR)/bsd/libkern/random.c \
	$(SOURCE_DIR)/bsd/libkern/scanc.c \
	$(SOURCE_DIR)/bsd/libkern/strsep.c \
	$(SOURCE_DIR)/bsd/libkern/bcd.c \
	$(SOURCE_DIR)/bsd/libkern/memchr.c \
	$(SOURCE_DIR)/bsd/libkern/url_encode.c \
	$(SOURCE_DIR)/bsd/vfs/vfs_attrlist.c \
	$(SOURCE_DIR)/bsd/vfs/vfs_bio.c \
	$(SOURCE_DIR)/bsd/vfs/vfs_cache.c \
	$(SOURCE_DIR)/bsd/vfs/vfs_cluster.c \
	$(SOURCE_DIR)/bsd/vfs/vfs_conf.c \
	$(SOURCE_DIR)/bsd/vfs/vfs_fslog.c \
	$(SOURCE_DIR)/bsd/vfs/vfs_init.c \
	$(SOURCE_DIR)/bsd/vfs/vfs_lookup.c \
	$(SOURCE_DIR)/bsd/vfs/vfs_quota.c \
	$(SOURCE_DIR)/bsd/vfs/vfs_subr.c \
	$(SOURCE_DIR)/bsd/vfs/vfs_syscalls.c \
	$(SOURCE_DIR)/bsd/vfs/vfs_support.c \
	$(SOURCE_DIR)/bsd/vfs/vfs_utfconv.c \
	$(SOURCE_DIR)/bsd/vfs/vfs_unicode.c \
	$(SOURCE_DIR)/bsd/vfs/vfs_vnops.c \
	$(SOURCE_DIR)/bsd/vfs/vfs_xattr.c \
	$(SOURCE_DIR)/bsd/vfs/vnode_if.c \
	$(SOURCE_DIR)/bsd/vfs/kpi_vfs.c \
	$(SOURCE_DIR)/bsd/vfs/vfs_fsevents.c \
	$(SOURCE_DIR)/bsd/vfs/vfs_cprotect.c \
	$(SOURCE_DIR)/bsd/vfs/doc_tombstone.c \
	$(SOURCE_DIR)/bsd/vfs/vfs_disk_conditioner.c \
	$(SOURCE_DIR)/bsd/miscfs/deadfs/dead_vnops.c \
	$(SOURCE_DIR)/bsd/miscfs/devfs/devfs_fdesc_support.c \
	$(SOURCE_DIR)/bsd/miscfs/fifofs/fifo_vnops.c \
	$(SOURCE_DIR)/bsd/miscfs/specfs/spec_vnops.c \
	$(SOURCE_DIR)/bsd/miscfs/devfs/devfs_tree.c \
	$(SOURCE_DIR)/bsd/miscfs/devfs/devfs_vnops.c \
	$(SOURCE_DIR)/bsd/miscfs/devfs/devfs_vfsops.c \
	$(SOURCE_DIR)/bsd/kern/decmpfs.c \
	$(SOURCE_DIR)/bsd/net/net_stubs.c \
	$(SOURCE_DIR)/bsd/net/bpf.c \
	$(SOURCE_DIR)/bsd/net/bpf_filter.c \
	$(SOURCE_DIR)/bsd/net/if_bridge.c \
	$(SOURCE_DIR)/bsd/net/if.c \
	$(SOURCE_DIR)/bsd/net/init.c \
	$(SOURCE_DIR)/bsd/net/dlil.c \
	$(SOURCE_DIR)/bsd/net/ether_if_module.c \
	$(SOURCE_DIR)/bsd/net/ether_inet_pr_module.c \
	$(SOURCE_DIR)/bsd/net/ether_inet6_pr_module.c \
	$(SOURCE_DIR)/bsd/net/if_loop.c \
	$(SOURCE_DIR)/bsd/net/if_mib.c \
	$(SOURCE_DIR)/bsd/net/if_vlan.c \
	$(SOURCE_DIR)/bsd/net/if_fake.c \
	$(SOURCE_DIR)/bsd/net/if_headless.c \
	$(SOURCE_DIR)/bsd/net/if_6lowpan.c \
	$(SOURCE_DIR)/bsd/net/multicast_list.c \
	$(SOURCE_DIR)/bsd/net/if_bond.c \
	$(SOURCE_DIR)/bsd/net/devtimer.c \
	$(SOURCE_DIR)/bsd/net/ndrv.c \
	$(SOURCE_DIR)/bsd/net/radix.c \
	$(SOURCE_DIR)/bsd/net/raw_cb.c \
	$(SOURCE_DIR)/bsd/net/raw_usrreq.c \
	$(SOURCE_DIR)/bsd/net/route.c \
	$(SOURCE_DIR)/bsd/net/rtsock.c \
	$(SOURCE_DIR)/bsd/net/netsrc.c \
	$(SOURCE_DIR)/bsd/net/ntstat.c \
	$(SOURCE_DIR)/bsd/net/net_perf.c \
	$(SOURCE_DIR)/bsd/net/if_gif.c \
	$(SOURCE_DIR)/bsd/net/if_stf.c \
	$(SOURCE_DIR)/bsd/net/if_ports_used.c \
	$(SOURCE_DIR)/bsd/net/if_low_power_mode.c \
	$(SOURCE_DIR)/bsd/net/kpi_interface.c \
	$(SOURCE_DIR)/bsd/net/kpi_protocol.c \
	$(SOURCE_DIR)/bsd/net/kpi_interfacefilter.c \
	$(SOURCE_DIR)/bsd/net/net_str_id.c \
	$(SOURCE_DIR)/bsd/net/if_utun.c \
	$(SOURCE_DIR)/bsd/net/if_ipsec.c \
	$(SOURCE_DIR)/bsd/net/necp.c \
	$(SOURCE_DIR)/bsd/net/necp_client.c \
	$(SOURCE_DIR)/bsd/net/network_agent.c \
	$(SOURCE_DIR)/bsd/net/if_pflog.c \
	$(SOURCE_DIR)/bsd/net/nat464_utils.c \
	$(SOURCE_DIR)/bsd/net/pf.c \
	$(SOURCE_DIR)/bsd/net/pf_if.c \
	$(SOURCE_DIR)/bsd/net/pf_ioctl.c \
	$(SOURCE_DIR)/bsd/net/pf_norm.c \
	$(SOURCE_DIR)/bsd/net/pf_osfp.c \
	$(SOURCE_DIR)/bsd/net/pf_pbuf.c \
	$(SOURCE_DIR)/bsd/net/pf_ruleset.c \
	$(SOURCE_DIR)/bsd/net/pf_table.c \
	$(SOURCE_DIR)/bsd/net/iptap.c \
	$(SOURCE_DIR)/bsd/net/pktap.c \
	$(SOURCE_DIR)/bsd/net/if_llreach.c \
	$(SOURCE_DIR)/bsd/net/flowhash.c \
	$(SOURCE_DIR)/bsd/net/flowadv.c \
	$(SOURCE_DIR)/bsd/net/content_filter.c \
	$(SOURCE_DIR)/bsd/net/content_filter_crypto.c \
	$(SOURCE_DIR)/bsd/net/packet_mangler.c \
	$(SOURCE_DIR)/bsd/net/if_llatbl.c \
	$(SOURCE_DIR)/bsd/net/nwk_wq.c \
	$(SOURCE_DIR)/bsd/net/restricted_in_port.c \
	$(SOURCE_DIR)/bsd/net/classq/classq.c \
	$(SOURCE_DIR)/bsd/net/classq/classq_sfb.c \
	$(SOURCE_DIR)/bsd/net/classq/classq_subr.c \
	$(SOURCE_DIR)/bsd/net/classq/classq_util.c \
	$(SOURCE_DIR)/bsd/net/classq/classq_fq_codel.c \
	$(SOURCE_DIR)/bsd/net/pktsched/pktsched.c \
	$(SOURCE_DIR)/bsd/net/pktsched/pktsched_fq_codel.c \
	$(SOURCE_DIR)/bsd/net/pktsched/pktsched_netem.c \
	$(SOURCE_DIR)/bsd/netinet/cpu_in_cksum_gen.c \
	$(SOURCE_DIR)/bsd/netinet/in_cksum.c \
	$(SOURCE_DIR)/bsd/netinet/igmp.c \
	$(SOURCE_DIR)/bsd/netinet/in.c \
	$(SOURCE_DIR)/bsd/netinet/dhcp_options.c \
	$(SOURCE_DIR)/bsd/netinet/in_arp.c \
	$(SOURCE_DIR)/bsd/netinet/in_mcast.c \
	$(SOURCE_DIR)/bsd/netinet/in_pcb.c \
	$(SOURCE_DIR)/bsd/netinet/in_pcblist.c \
	$(SOURCE_DIR)/bsd/netinet/in_proto.c \
	$(SOURCE_DIR)/bsd/netinet/in_rmx.c \
	$(SOURCE_DIR)/bsd/netinet/in_stat.c \
	$(SOURCE_DIR)/bsd/netinet/in_tclass.c \
	$(SOURCE_DIR)/bsd/netinet/ip_dummynet.c \
	$(SOURCE_DIR)/bsd/netinet/ip_icmp.c \
	$(SOURCE_DIR)/bsd/netinet/ip_id.c \
	$(SOURCE_DIR)/bsd/netinet/ip_input.c \
	$(SOURCE_DIR)/bsd/netinet/ip_output.c \
	$(SOURCE_DIR)/bsd/netinet/raw_ip.c \
	$(SOURCE_DIR)/bsd/netinet/tcp_cache.c \
	$(SOURCE_DIR)/bsd/netinet/tcp_input.c \
	$(SOURCE_DIR)/bsd/netinet/tcp_output.c \
	$(SOURCE_DIR)/bsd/netinet/tcp_sack.c \
	$(SOURCE_DIR)/bsd/netinet/tcp_subr.c \
	$(SOURCE_DIR)/bsd/netinet/tcp_timer.c \
	$(SOURCE_DIR)/bsd/netinet/tcp_usrreq.c \
	$(SOURCE_DIR)/bsd/netinet/tcp_cc.c \
	$(SOURCE_DIR)/bsd/netinet/tcp_newreno.c \
	$(SOURCE_DIR)/bsd/netinet/tcp_cubic.c \
	$(SOURCE_DIR)/bsd/netinet/cbrtf.c \
	$(SOURCE_DIR)/bsd/netinet/tcp_ledbat.c \
	$(SOURCE_DIR)/bsd/netinet/tcp_log.c \
	$(SOURCE_DIR)/bsd/netinet/udp_usrreq.c \
	$(SOURCE_DIR)/bsd/netinet/in_gif.c \
	$(SOURCE_DIR)/bsd/netinet/ip_ecn.c \
	$(SOURCE_DIR)/bsd/netinet/ip_encap.c \
	$(SOURCE_DIR)/bsd/netinet/kpi_ipfilter.c \
	$(SOURCE_DIR)/bsd/netinet/flow_divert.c \
	$(SOURCE_DIR)/bsd/netinet/mp_proto.c \
	$(SOURCE_DIR)/bsd/netinet/mp_pcb.c \
	$(SOURCE_DIR)/bsd/netinet/mptcp.c \
	$(SOURCE_DIR)/bsd/netinet/mptcp_subr.c \
	$(SOURCE_DIR)/bsd/netinet/mptcp_usrreq.c \
	$(SOURCE_DIR)/bsd/netinet/mptcp_opt.c \
	$(SOURCE_DIR)/bsd/netinet/mptcp_timer.c \
	$(SOURCE_DIR)/bsd/netinet6/ah_core.c \
	$(SOURCE_DIR)/bsd/netinet6/ah_input.c \
	$(SOURCE_DIR)/bsd/netinet6/ah_output.c \
	$(SOURCE_DIR)/bsd/netinet6/esp_core.c \
	$(SOURCE_DIR)/bsd/netinet6/esp_input.c \
	$(SOURCE_DIR)/bsd/netinet6/esp_output.c \
	$(SOURCE_DIR)/bsd/netinet6/esp_rijndael.c \
	$(SOURCE_DIR)/bsd/netinet6/esp_chachapoly.c \
	$(SOURCE_DIR)/bsd/netinet6/ipsec.c \
	$(SOURCE_DIR)/bsd/netinet6/dest6.c \
	$(SOURCE_DIR)/bsd/netinet6/frag6.c \
	$(SOURCE_DIR)/bsd/netinet6/icmp6.c \
	$(SOURCE_DIR)/bsd/netinet6/in6.c \
	$(SOURCE_DIR)/bsd/netinet6/in6_cga.c \
	$(SOURCE_DIR)/bsd/netinet6/in6_cksum.c \
	$(SOURCE_DIR)/bsd/netinet6/in6_gif.c \
	$(SOURCE_DIR)/bsd/netinet6/ip6_forward.c \
	$(SOURCE_DIR)/bsd/netinet6/in6_ifattach.c \
	$(SOURCE_DIR)/bsd/netinet6/ip6_input.c \
	$(SOURCE_DIR)/bsd/netinet6/ip6_output.c \
	$(SOURCE_DIR)/bsd/netinet6/in6_src.c \
	$(SOURCE_DIR)/bsd/netinet6/in6_mcast.c \
	$(SOURCE_DIR)/bsd/netinet6/in6_pcb.c \
	$(SOURCE_DIR)/bsd/netinet6/in6_proto.c \
	$(SOURCE_DIR)/bsd/netinet6/in6_rmx.c \
	$(SOURCE_DIR)/bsd/netinet6/mld6.c \
	$(SOURCE_DIR)/bsd/netinet6/nd6.c \
	$(SOURCE_DIR)/bsd/netinet6/nd6_nbr.c \
	$(SOURCE_DIR)/bsd/netinet6/nd6_prproxy.c \
	$(SOURCE_DIR)/bsd/netinet6/nd6_rtr.c \
	$(SOURCE_DIR)/bsd/netinet6/nd6_rti.c \
	$(SOURCE_DIR)/bsd/netinet6/nd6_send.c \
	$(SOURCE_DIR)/bsd/netinet6/raw_ip6.c \
	$(SOURCE_DIR)/bsd/netinet6/route6.c \
	$(SOURCE_DIR)/bsd/netinet6/scope6.c \
	$(SOURCE_DIR)/bsd/netinet6/udp6_output.c \
	$(SOURCE_DIR)/bsd/netinet6/udp6_usrreq.c \
	$(SOURCE_DIR)/bsd/netinet6/ip6_id.c \
	$(SOURCE_DIR)/bsd/net/sixxlowpan.c \
	$(SOURCE_DIR)/bsd/net/frame802154.c \
	$(SOURCE_DIR)/bsd/net/linkaddr.c \
	$(SOURCE_DIR)/bsd/netkey/key.c \
	$(SOURCE_DIR)/bsd/netkey/key_debug.c \
	$(SOURCE_DIR)/bsd/netkey/keysock.c \
	$(SOURCE_DIR)/bsd/netkey/keydb.c \
	$(SOURCE_DIR)/bsd/net/multi_layer_pkt_log.c \
	$(SOURCE_DIR)/bsd/crypto/entropy/entropy_sysctl.c \
	$(SOURCE_DIR)/bsd/security/audit/audit.c \
	$(SOURCE_DIR)/bsd/security/audit/audit_arg.c \
	$(SOURCE_DIR)/bsd/security/audit/audit_bsd.c \
	$(SOURCE_DIR)/bsd/security/audit/audit_bsm.c \
	$(SOURCE_DIR)/bsd/security/audit/audit_bsm_errno.c \
	$(SOURCE_DIR)/bsd/security/audit/audit_bsm_fcntl.c \
	$(SOURCE_DIR)/bsd/security/audit/audit_bsm_domain.c \
	$(SOURCE_DIR)/bsd/security/audit/audit_bsm_klib.c \
	$(SOURCE_DIR)/bsd/security/audit/audit_bsm_socket_type.c \
	$(SOURCE_DIR)/bsd/security/audit/audit_bsm_token.c \
	./audit_kevents.c \
	$(SOURCE_DIR)/bsd/security/audit/audit_mac.c \
	$(SOURCE_DIR)/bsd/security/audit/audit_pipe.c \
	$(SOURCE_DIR)/bsd/security/audit/audit_session.c \
	$(SOURCE_DIR)/bsd/security/audit/audit_syscalls.c \
	$(SOURCE_DIR)/bsd/security/audit/audit_worker.c \
	$(SOURCE_DIR)/bsd/pthread/pthread_shims.c \
	$(SOURCE_DIR)/bsd/pthread/pthread_priority.c \
	$(SOURCE_DIR)/bsd/pthread/pthread_workqueue.c \
	$(SOURCE_DIR)/bsd/kern/bsd_init.c \
	./init_sysent.c \
	$(SOURCE_DIR)/bsd/kern/kdebug.c \
	$(SOURCE_DIR)/bsd/kern/kern_acct.c \
	$(SOURCE_DIR)/bsd/kern/kern_aio.c \
	$(SOURCE_DIR)/bsd/kern/kern_authorization.c \
	$(SOURCE_DIR)/bsd/kern/kern_backtrace.c \
	$(SOURCE_DIR)/bsd/kern/kern_clock.c \
	$(SOURCE_DIR)/bsd/kern/kern_core.c \
	$(SOURCE_DIR)/bsd/kern/kern_credential.c \
	$(SOURCE_DIR)/bsd/kern/kern_cs.c \
	$(SOURCE_DIR)/bsd/kern/kern_csr.c \
	$(SOURCE_DIR)/bsd/kern/kern_symfile.c \
	$(SOURCE_DIR)/bsd/kern/kern_descrip.c \
	$(SOURCE_DIR)/bsd/kern/kern_guarded.c \
	$(SOURCE_DIR)/bsd/kern/kern_event.c \
	$(SOURCE_DIR)/bsd/kern/kern_control.c \
	$(SOURCE_DIR)/bsd/kern/kern_exec.c \
	$(SOURCE_DIR)/bsd/kern/kern_exit.c \
	$(SOURCE_DIR)/bsd/kern/kern_ktrace.c \
	$(SOURCE_DIR)/bsd/kern/kern_lockf.c \
	$(SOURCE_DIR)/bsd/kern/kern_fork.c \
	$(SOURCE_DIR)/bsd/kern/kern_asl.c \
	$(SOURCE_DIR)/bsd/kern/kern_malloc.c \
	$(SOURCE_DIR)/bsd/kern/kern_mman.c \
	$(SOURCE_DIR)/bsd/kern/kern_persona.c \
	$(SOURCE_DIR)/bsd/kern/kern_physio.c \
	$(SOURCE_DIR)/bsd/kern/kern_priv.c \
	$(SOURCE_DIR)/bsd/kern/kern_proc.c \
	$(SOURCE_DIR)/bsd/kern/kern_prot.c \
	$(SOURCE_DIR)/bsd/kern/kern_resource.c \
	$(SOURCE_DIR)/bsd/kern/kern_shutdown.c \
	$(SOURCE_DIR)/bsd/kern/kern_sig.c \
	$(SOURCE_DIR)/bsd/kern/kern_subr.c \
	$(SOURCE_DIR)/bsd/kern/kern_synch.c \
	$(SOURCE_DIR)/bsd/kern/kern_sysctl.c \
	$(SOURCE_DIR)/bsd/kern/kern_newsysctl.c \
	$(SOURCE_DIR)/bsd/kern/kern_memorystatus.c \
	$(SOURCE_DIR)/bsd/kern/kern_memorystatus_freeze.c \
	$(SOURCE_DIR)/bsd/kern/kern_memorystatus_notify.c \
	$(SOURCE_DIR)/bsd/kern/kern_mib.c \
	$(SOURCE_DIR)/bsd/kern/kpi_mbuf.c \
	$(SOURCE_DIR)/bsd/kern/kern_sfi.c \
	$(SOURCE_DIR)/bsd/kern/kern_time.c \
	$(SOURCE_DIR)/bsd/kern/kern_xxx.c \
	$(SOURCE_DIR)/bsd/kern/mach_process.c \
	$(SOURCE_DIR)/bsd/kern/mcache.c \
	$(SOURCE_DIR)/bsd/kern/stackshot.c \
	$(SOURCE_DIR)/bsd/kern/subr_log.c \
	$(SOURCE_DIR)/bsd/kern/subr_prf.c \
	$(SOURCE_DIR)/bsd/kern/subr_sbuf.c \
	$(SOURCE_DIR)/bsd/kern/subr_xxx.c \
	$(SOURCE_DIR)/bsd/kern/sys_eventlink.c \
	$(SOURCE_DIR)/bsd/kern/sys_generic.c \
	$(SOURCE_DIR)/bsd/kern/sys_pipe.c \
	$(SOURCE_DIR)/bsd/kern/sys_socket.c \
	$(SOURCE_DIR)/bsd/kern/sys_domain.c \
	$(SOURCE_DIR)/bsd/kern/sys_coalition.c \
	$(SOURCE_DIR)/bsd/kern/sys_persona.c \
	$(SOURCE_DIR)/bsd/kern/sys_ulock.c \
	$(SOURCE_DIR)/bsd/kern/sys_work_interval.c \
	./syscalls.c \
	$(SOURCE_DIR)/bsd/kern/tty.c \
	$(SOURCE_DIR)/bsd/kern/tty_compat.c \
	$(SOURCE_DIR)/bsd/kern/tty_conf.c \
	$(SOURCE_DIR)/bsd/kern/tty_dev.c \
	$(SOURCE_DIR)/bsd/kern/tty_ptmx.c \
	$(SOURCE_DIR)/bsd/kern/tty_pty.c \
	$(SOURCE_DIR)/bsd/kern/tty_subr.c \
	$(SOURCE_DIR)/bsd/kern/tty_tty.c \
	$(SOURCE_DIR)/bsd/kern/ubc_subr.c \
	$(SOURCE_DIR)/bsd/kern/uipc_domain.c \
	$(SOURCE_DIR)/bsd/kern/uipc_mbuf.c \
	$(SOURCE_DIR)/bsd/kern/uipc_mbuf2.c \
	$(SOURCE_DIR)/bsd/kern/uipc_proto.c \
	$(SOURCE_DIR)/bsd/kern/uipc_socket.c \
	$(SOURCE_DIR)/bsd/kern/uipc_socket2.c \
	$(SOURCE_DIR)/bsd/kern/uipc_syscalls.c \
	$(SOURCE_DIR)/bsd/kern/uipc_usrreq.c \
	$(SOURCE_DIR)/bsd/kern/vsock_domain.c \
	$(SOURCE_DIR)/bsd/kern/sysv_ipc.c \
	$(SOURCE_DIR)/bsd/kern/sysv_shm.c \
	$(SOURCE_DIR)/bsd/kern/sysv_sem.c \
	$(SOURCE_DIR)/bsd/kern/sysv_msg.c \
	$(SOURCE_DIR)/bsd/kern/mach_fat.c \
	$(SOURCE_DIR)/bsd/kern/mach_loader.c \
	$(SOURCE_DIR)/bsd/kern/posix_sem.c \
	$(SOURCE_DIR)/bsd/kern/posix_shm.c \
	$(SOURCE_DIR)/bsd/kern/qsort.c \
	$(SOURCE_DIR)/bsd/kern/kpi_socket.c \
	$(SOURCE_DIR)/bsd/kern/kpi_socketfilter.c \
	$(SOURCE_DIR)/bsd/kern/proc_info.c \
	$(SOURCE_DIR)/bsd/kern/process_policy.c \
	$(SOURCE_DIR)/bsd/kern/kern_overrides.c \
	$(SOURCE_DIR)/bsd/kern/socket_info.c \
	$(SOURCE_DIR)/bsd/kern/subr_eventhandler.c \
	$(SOURCE_DIR)/bsd/kern/sys_reason.c \
	$(SOURCE_DIR)/bsd/vm/vnode_pager.c \
	$(SOURCE_DIR)/bsd/vm/vm_unix.c \
	$(SOURCE_DIR)/bsd/vm/dp_backing_file.c \
	$(SOURCE_DIR)/bsd/vm/vm_compressor_backing_file.c \
	$(SOURCE_DIR)/bsd/kern/kern_ntptime.c \
	$(SOURCE_DIR)/bsd/uxkern/ux_exception.c \
	$(SOURCE_DIR)/bsd/conf/param.c \
	./ioconf.c \
	$(SOURCE_DIR)/bsd/kern/imageboot.c \
	$(SOURCE_DIR)/bsd/kern/chunklist.c \
	$(SOURCE_DIR)/osfmk/kperf/kperfbsd.c \
	$(SOURCE_DIR)/bsd/kern/kern_kpc.c \
	$(SOURCE_DIR)/bsd/kern/proc_uuid_policy.c \
	$(SOURCE_DIR)/bsd/pgo/profile_runtime.c \
	$(SOURCE_DIR)/bsd/pgo/profile_runtime_data.c \
	$(SOURCE_DIR)/bsd/miscfs/nullfs/null_subr.c \
	$(SOURCE_DIR)/bsd/miscfs/nullfs/null_vfsops.c \
	$(SOURCE_DIR)/bsd/miscfs/nullfs/null_vnops.c \
	$(SOURCE_DIR)/bsd/miscfs/bindfs/bind_subr.c \
	$(SOURCE_DIR)/bsd/miscfs/bindfs/bind_vfsops.c \
	$(SOURCE_DIR)/bsd/miscfs/bindfs/bind_vnops.c \
	$(SOURCE_DIR)/bsd/tests/bsd_tests.c \
	$(SOURCE_DIR)/bsd/tests/copyio_tests.c \
	$(SOURCE_DIR)/bsd/tests/pmap_test_sysctl.c \
	$(SOURCE_DIR)/bsd/tests/ptrauth_data_tests_sysctl.c \
	$(SOURCE_DIR)/bsd/net/skywalk_stubs.c \
	$(SOURCE_DIR)/bsd/dev/i386/conf.c \
	$(SOURCE_DIR)/bsd/dev/i386/cons.c \
	$(SOURCE_DIR)/bsd/dev/i386/km.c \
	$(SOURCE_DIR)/bsd/dev/i386/kern_machdep.c \
	$(SOURCE_DIR)/bsd/dev/i386/stubs.c \
	$(SOURCE_DIR)/bsd/dev/i386/systemcalls.c \
	$(SOURCE_DIR)/bsd/dev/i386/sysctl.c \
	$(SOURCE_DIR)/bsd/dev/i386/unix_signal.c \
	$(SOURCE_DIR)/bsd/dev/i386/dtrace_isa.c \
	$(SOURCE_DIR)/bsd/dev/i386/dtrace_subr_x86.c \
	$(SOURCE_DIR)/bsd/dev/i386/fbt_x86.c \
	$(SOURCE_DIR)/bsd/dev/i386/sdt_x86.c \
	$(SOURCE_DIR)/bsd/dev/i386/fasttrap_isa.c \
	$(SOURCE_DIR)/bsd/dev/i386/instr_size.c \
	$(SOURCE_DIR)/bsd/dev/i386/dis_tables.c \
	$(SOURCE_DIR)/bsd/kern/policy_check.c \
	$(SOURCE_DIR)/bsd/kern/bsd_stubs.c 
COBJS=nfs4_subs.o nfs4_vnops.o krpc_subr.o nfs_bio.o nfs_boot.o \
	nfs_gss.o nfs_lock.o nfs_node.o nfs_serv.o nfs_socket.o \
	nfs_srvcache.o nfs_subs.o nfs_syscalls.o nfs_vfsops.o \
	nfs_vnops.o nfs_upcall.o gss_krb5_mech.o ccrypto.o netboot.o \
	dtrace.o lockprof.o lockstat.o dtrace_ptss.o dtrace_subr.o \
	dtrace_glue.o dtrace_xoroshiro128_plus.o blist.o fbt.o \
	fbt_blacklist.o sdt.o sdt_subr.o systrace.o profile_prvd.o \
	fasttrap.o systrace_args.o randomdev.o memdev.o mem.o munge.o \
	unix_startup.o vn.o shadow.o crc16.o crc32.o random.o scanc.o \
	strsep.o bcd.o memchr.o url_encode.o vfs_attrlist.o vfs_bio.o \
	vfs_cache.o vfs_cluster.o vfs_conf.o vfs_fslog.o vfs_init.o \
	vfs_lookup.o vfs_quota.o vfs_subr.o vfs_syscalls.o vfs_support.o \
	vfs_utfconv.o vfs_unicode.o vfs_vnops.o vfs_xattr.o vnode_if.o \
	kpi_vfs.o vfs_fsevents.o vfs_cprotect.o doc_tombstone.o \
	vfs_disk_conditioner.o dead_vnops.o devfs_fdesc_support.o \
	fifo_vnops.o spec_vnops.o devfs_tree.o devfs_vnops.o \
	devfs_vfsops.o decmpfs.o net_stubs.o bpf.o bpf_filter.o \
	if_bridge.o if.o init.o dlil.o ether_if_module.o \
	ether_inet_pr_module.o ether_inet6_pr_module.o if_loop.o \
	if_mib.o if_vlan.o if_fake.o if_headless.o if_6lowpan.o \
	multicast_list.o if_bond.o devtimer.o ndrv.o radix.o raw_cb.o \
	raw_usrreq.o route.o rtsock.o netsrc.o ntstat.o net_perf.o \
	if_gif.o if_stf.o if_ports_used.o if_low_power_mode.o \
	kpi_interface.o kpi_protocol.o kpi_interfacefilter.o \
	net_str_id.o if_utun.o if_ipsec.o necp.o necp_client.o \
	network_agent.o if_pflog.o nat464_utils.o pf.o pf_if.o \
	pf_ioctl.o pf_norm.o pf_osfp.o pf_pbuf.o pf_ruleset.o pf_table.o \
	iptap.o pktap.o if_llreach.o flowhash.o flowadv.o \
	content_filter.o content_filter_crypto.o packet_mangler.o \
	if_llatbl.o nwk_wq.o restricted_in_port.o classq.o classq_sfb.o \
	classq_subr.o classq_util.o classq_fq_codel.o pktsched.o \
	pktsched_fq_codel.o pktsched_netem.o cpu_in_cksum_gen.o \
	in_cksum.o igmp.o in.o dhcp_options.o in_arp.o in_mcast.o \
	in_pcb.o in_pcblist.o in_proto.o in_rmx.o in_stat.o in_tclass.o \
	ip_dummynet.o ip_icmp.o ip_id.o ip_input.o ip_output.o raw_ip.o \
	tcp_cache.o tcp_input.o tcp_output.o tcp_sack.o tcp_subr.o \
	tcp_timer.o tcp_usrreq.o tcp_cc.o tcp_newreno.o tcp_cubic.o \
	cbrtf.o tcp_ledbat.o tcp_log.o udp_usrreq.o in_gif.o ip_ecn.o \
	ip_encap.o kpi_ipfilter.o flow_divert.o mp_proto.o mp_pcb.o \
	mptcp.o mptcp_subr.o mptcp_usrreq.o mptcp_opt.o mptcp_timer.o \
	ah_core.o ah_input.o ah_output.o esp_core.o esp_input.o \
	esp_output.o esp_rijndael.o esp_chachapoly.o ipsec.o dest6.o \
	frag6.o icmp6.o in6.o in6_cga.o in6_cksum.o in6_gif.o \
	ip6_forward.o in6_ifattach.o ip6_input.o ip6_output.o in6_src.o \
	in6_mcast.o in6_pcb.o in6_proto.o in6_rmx.o mld6.o nd6.o \
	nd6_nbr.o nd6_prproxy.o nd6_rtr.o nd6_rti.o nd6_send.o raw_ip6.o \
	route6.o scope6.o udp6_output.o udp6_usrreq.o ip6_id.o \
	sixxlowpan.o frame802154.o linkaddr.o key.o key_debug.o \
	keysock.o keydb.o multi_layer_pkt_log.o entropy_sysctl.o audit.o \
	audit_arg.o audit_bsd.o audit_bsm.o audit_bsm_errno.o \
	audit_bsm_fcntl.o audit_bsm_domain.o audit_bsm_klib.o \
	audit_bsm_socket_type.o audit_bsm_token.o audit_kevents.o \
	audit_mac.o audit_pipe.o audit_session.o audit_syscalls.o \
	audit_worker.o pthread_shims.o pthread_priority.o \
	pthread_workqueue.o bsd_init.o init_sysent.o kdebug.o \
	kern_acct.o kern_aio.o kern_authorization.o kern_backtrace.o \
	kern_clock.o kern_core.o kern_credential.o kern_cs.o kern_csr.o \
	kern_symfile.o kern_descrip.o kern_guarded.o kern_event.o \
	kern_control.o kern_exec.o kern_exit.o kern_ktrace.o \
	kern_lockf.o kern_fork.o kern_asl.o kern_malloc.o kern_mman.o \
	kern_persona.o kern_physio.o kern_priv.o kern_proc.o kern_prot.o \
	kern_resource.o kern_shutdown.o kern_sig.o kern_subr.o \
	kern_synch.o kern_sysctl.o kern_newsysctl.o kern_memorystatus.o \
	kern_memorystatus_freeze.o kern_memorystatus_notify.o kern_mib.o \
	kpi_mbuf.o kern_sfi.o kern_time.o kern_xxx.o mach_process.o \
	mcache.o stackshot.o subr_log.o subr_prf.o subr_sbuf.o \
	subr_xxx.o sys_eventlink.o sys_generic.o sys_pipe.o sys_socket.o \
	sys_domain.o sys_coalition.o sys_persona.o sys_ulock.o \
	sys_work_interval.o syscalls.o tty.o tty_compat.o tty_conf.o \
	tty_dev.o tty_ptmx.o tty_pty.o tty_subr.o tty_tty.o ubc_subr.o \
	uipc_domain.o uipc_mbuf.o uipc_mbuf2.o uipc_proto.o \
	uipc_socket.o uipc_socket2.o uipc_syscalls.o uipc_usrreq.o \
	vsock_domain.o sysv_ipc.o sysv_shm.o sysv_sem.o sysv_msg.o \
	mach_fat.o mach_loader.o posix_sem.o posix_shm.o qsort.o \
	kpi_socket.o kpi_socketfilter.o proc_info.o process_policy.o \
	kern_overrides.o socket_info.o subr_eventhandler.o sys_reason.o \
	vnode_pager.o vm_unix.o dp_backing_file.o \
	vm_compressor_backing_file.o kern_ntptime.o ux_exception.o \
	param.o ioconf.o imageboot.o chunklist.o kperfbsd.o kern_kpc.o \
	proc_uuid_policy.o profile_runtime.o profile_runtime_data.o \
	null_subr.o null_vfsops.o null_vnops.o bind_subr.o bind_vfsops.o \
	bind_vnops.o bsd_tests.o copyio_tests.o pmap_test_sysctl.o \
	ptrauth_data_tests_sysctl.o skywalk_stubs.o conf.o cons.o km.o \
	kern_machdep.o stubs.o systemcalls.o sysctl.o unix_signal.o \
	dtrace_isa.o dtrace_subr_x86.o fbt_x86.o sdt_x86.o \
	fasttrap_isa.o instr_size.o dis_tables.o policy_check.o \
	bsd_stubs.o 

CXXFILES=
CXXOBJS=

SFILES=
SOBJS=

######################################################################
#BEGIN  Machine dependent Makefile fragment for x86_64
######################################################################

# Inline assembly doesn't interact well with LTO
fbt_x86.o_CFLAGS_ADD += $(CFLAGS_NOLTO_FLAG)
# Taking the address of labels doesn't work with LTO (9524055)
dtrace.o_CFLAGS_ADD += $(CFLAGS_NOLTO_FLAG)

######################################################################
#END    Machine dependent Makefile fragment for x86_64
######################################################################

tcp_cubic.o_CFLAGS_ADD += -Wno-error=implicit-int-float-conversion

#
# Diagnostic opt-outs.  We need to make this list empty.
#
# DO NOT ADD MORE HERE.
#
# -Wno-address-of-packed-member
ah_core.o_CFLAGS_ADD += -Wno-address-of-packed-member
ah_input.o_CFLAGS_ADD += -Wno-address-of-packed-member
dlil.o_CFLAGS_ADD += -Wno-address-of-packed-member
esp_input.o_CFLAGS_ADD += -Wno-address-of-packed-member
esp_output.o_CFLAGS_ADD += -Wno-address-of-packed-member
frag6.o_CFLAGS_ADD += -Wno-address-of-packed-member
icmp6.o_CFLAGS_ADD += -Wno-address-of-packed-member
if_stf.o_CFLAGS_ADD += -Wno-address-of-packed-member
in6_cksum.o_CFLAGS_ADD += -Wno-address-of-packed-member
in6_gif.o_CFLAGS_ADD += -Wno-address-of-packed-member
ip6_forward.o_CFLAGS_ADD += -Wno-address-of-packed-member
ip6_input.o_CFLAGS_ADD += -Wno-address-of-packed-member
ip6_output.o_CFLAGS_ADD += -Wno-address-of-packed-member
ipsec.o_CFLAGS_ADD += -Wno-address-of-packed-member
iptap.o_CFLAGS_ADD += -Wno-address-of-packed-member
mld6.o_CFLAGS_ADD += -Wno-address-of-packed-member
mptcp_opt.o_CFLAGS_ADD += -Wno-address-of-packed-member
nd6.o_CFLAGS_ADD += -Wno-address-of-packed-member
nd6_nbr.o_CFLAGS_ADD += -Wno-address-of-packed-member
nd6_prproxy.o_CFLAGS_ADD += -Wno-address-of-packed-member
nd6_rtr.o_CFLAGS_ADD += -Wno-address-of-packed-member
necp.o_CFLAGS_ADD += -Wno-address-of-packed-member
packet_mangler.o_CFLAGS_ADD += -Wno-address-of-packed-member
pf_norm.o_CFLAGS_ADD += -Wno-address-of-packed-member
pktap.o_CFLAGS_ADD += -Wno-address-of-packed-member
raw_ip6.o_CFLAGS_ADD += -Wno-address-of-packed-member
sixxlowpan.o_CFLAGS_ADD += -Wno-address-of-packed-member
tcp_input.o_CFLAGS_ADD += -Wno-address-of-packed-member
tcp_subr.o_CFLAGS_ADD += -Wno-address-of-packed-member
udp6_output.o_CFLAGS_ADD += -Wno-address-of-packed-member
udp6_usrreq.o_CFLAGS_ADD += -Wno-address-of-packed-member
udp_usrreq.o_CFLAGS_ADD += -Wno-address-of-packed-member
# -Wno-cast-align
audit_bsm_token.o_CFLAGS_ADD += -Wno-cast-align
audit_pipe.o_CFLAGS_ADD += -Wno-cast-align
audit_session.o_CFLAGS_ADD += -Wno-cast-align
bind_vnops.o_CFLAGS_ADD += -Wno-cast-align
dtrace.o_CFLAGS_ADD += -Wno-cast-align
fasttrap.o_CFLAGS_ADD += -Wno-cast-align
fasttrap_isa.o_CFLAGS_ADD += -Wno-cast-align
fbt.o_CFLAGS_ADD += -Wno-cast-align
fbt_arm.o_CFLAGS_ADD += -Wno-cast-align
fbt_x86.o_CFLAGS_ADD += -Wno-cast-align
if_bond.o_CFLAGS_ADD += -Wno-cast-align
ip_dummynet.o_CFLAGS_ADD += -Wno-cast-align
kern_credential.o_CFLAGS_ADD += -Wno-cast-align
kern_descrip.o_CFLAGS_ADD += -Wno-cast-align
kern_event.o_CFLAGS_ADD += -Wno-cast-align
kern_exec.o_CFLAGS_ADD += -Wno-cast-align
kern_guarded.o_CFLAGS_ADD += -Wno-cast-align
kern_lockf.o_CFLAGS_ADD += -Wno-cast-align
kern_subr.o_CFLAGS_ADD += -Wno-cast-align
km.o_CFLAGS_ADD += -Wno-cast-align
mach_loader.o_CFLAGS_ADD += -Wno-cast-align
memdev.o_CFLAGS_ADD += -Wno-cast-align
munge.o_CFLAGS_ADD += -Wno-cast-align
nfs4_subs.o_CFLAGS_ADD += -Wno-cast-align
nfs4_vnops.o_CFLAGS_ADD += -Wno-cast-align
nfs_boot.o_CFLAGS_ADD += -Wno-cast-align
nfs_gss.o_CFLAGS_ADD += -Wno-cast-align
nfs_serv.o_CFLAGS_ADD += -Wno-cast-align
nfs_socket.o_CFLAGS_ADD += -Wno-cast-align
nfs_srvcache.o_CFLAGS_ADD += -Wno-cast-align
nfs_subs.o_CFLAGS_ADD += -Wno-cast-align
nfs_syscalls.o_CFLAGS_ADD += -Wno-cast-align
nfs_vfsops.o_CFLAGS_ADD += -Wno-cast-align
nfs_vnops.o_CFLAGS_ADD += -Wno-cast-align
proc_info.o_CFLAGS_ADD += -Wno-cast-align
qsort.o_CFLAGS_ADD += -Wno-cast-align
sdt.o_CFLAGS_ADD += -Wno-cast-align
sdt_arm.o_CFLAGS_ADD += -Wno-cast-align
shadow.o_CFLAGS_ADD += -Wno-cast-align
spec_vnops.o_CFLAGS_ADD += -Wno-cast-align
subr_log.o_CFLAGS_ADD += -Wno-cast-align
sys_generic.o_CFLAGS_ADD += -Wno-cast-align
sys_pipe.o_CFLAGS_ADD += -Wno-cast-align
systemcalls.o_CFLAGS_ADD += -Wno-cast-align
systrace.o_CFLAGS_ADD += -Wno-cast-align
tty.o_CFLAGS_ADD += -Wno-cast-align
tty_compat.o_CFLAGS_ADD += -Wno-cast-align
tty_dev.o_CFLAGS_ADD += -Wno-cast-align
ubc_subr.o_CFLAGS_ADD += -Wno-cast-align
uipc_mbuf.o_CFLAGS_ADD += -Wno-cast-align
uipc_usrreq.o_CFLAGS_ADD += -Wno-cast-align
vfs_attrlist.o_CFLAGS_ADD += -Wno-cast-align
vfs_fsevents.o_CFLAGS_ADD += -Wno-cast-align
vfs_syscalls.o_CFLAGS_ADD += -Wno-cast-align
vfs_utfconv.o_CFLAGS_ADD += -Wno-cast-align
vfs_vnops.o_CFLAGS_ADD += -Wno-cast-align
vfs_xattr.o_CFLAGS_ADD += -Wno-cast-align
vn.o_CFLAGS_ADD += -Wno-cast-align
# -Wno-cast-qual
dis_tables.o_CFLAGS_ADD += -Wno-cast-qual
# -Wno-format
dlil.o_CFLAGS_ADD += -Wno-format
in_rmx.o_CFLAGS_ADD += -Wno-format
in6_rmx.o_CFLAGS_ADD += -Wno-format
route.o_CFLAGS_ADD += -Wno-format
# -Wno-format-extra-args
dlil.o_CFLAGS_ADD += -Wno-format-extra-args
kpi_interface.o_CFLAGS_ADD += -Wno-format-extra-args
in_rmx.o_CFLAGS_ADD += -Wno-format-extra-args
in6_rmx.o_CFLAGS_ADD += -Wno-format-extra-args
route.o_CFLAGS_ADD += -Wno-format-extra-args
# -Wno-format-invalid-specifier
dlil.o_CFLAGS_ADD += -Wno-format-invalid-specifier
in_rmx.o_CFLAGS_ADD += -Wno-format-invalid-specifier
in6_rmx.o_CFLAGS_ADD += -Wno-format-invalid-specifier
kpi_interface.o_CFLAGS_ADD += -Wno-format-invalid-specifier
route.o_CFLAGS_ADD += -Wno-format-invalid-specifier
# -Wno-implicit-int-conversion
audit.o_CFLAGS_ADD += -Wno-implicit-int-conversion
audit_bsm.o_CFLAGS_ADD += -Wno-implicit-int-conversion
audit_bsm_errno.o_CFLAGS_ADD += -Wno-implicit-int-conversion
audit_bsm_token.o_CFLAGS_ADD += -Wno-implicit-int-conversion
audit_worker.o_CFLAGS_ADD += -Wno-implicit-int-conversion
bpf.o_CFLAGS_ADD += -Wno-implicit-int-conversion
content_filter.o_CFLAGS_ADD += -Wno-implicit-int-conversion
devfs_fdesc_support.o_CFLAGS_ADD += -Wno-implicit-int-conversion
devfs_vnops.o_CFLAGS_ADD += -Wno-implicit-int-conversion
dis_tables.o_CFLAGS_ADD += -Wno-implicit-int-conversion
dtrace.o_CFLAGS_ADD += -Wno-implicit-int-conversion
fasttrap.o_CFLAGS_ADD += -Wno-implicit-int-conversion
fasttrap_isa.o_CFLAGS_ADD += -Wno-implicit-int-conversion
fbt_arm.o_CFLAGS_ADD += -Wno-implicit-int-conversion
flow_agg.o_CFLAGS_ADD += -Wno-implicit-int-conversion
flowadv.o_CFLAGS_ADD += -Wno-implicit-int-conversion
gss_krb5_mech.o_CFLAGS_ADD += -Wno-implicit-int-conversion
if.o_CFLAGS_ADD += -Wno-implicit-int-conversion
if_bond.o_CFLAGS_ADD += -Wno-implicit-int-conversion
if_bridge.o_CFLAGS_ADD += -Wno-implicit-int-conversion
if_fake.o_CFLAGS_ADD += -Wno-implicit-int-conversion
if_ipsec.o_CFLAGS_ADD += -Wno-implicit-int-conversion
if_stf.o_CFLAGS_ADD += -Wno-implicit-int-conversion
if_utun.o_CFLAGS_ADD += -Wno-implicit-int-conversion
if_vlan.o_CFLAGS_ADD += -Wno-implicit-int-conversion
in6.o_CFLAGS_ADD += -Wno-implicit-int-conversion
in6_gif.o_CFLAGS_ADD += -Wno-implicit-int-conversion
in6_pcb.o_CFLAGS_ADD += -Wno-implicit-int-conversion
in_gif.o_CFLAGS_ADD += -Wno-implicit-int-conversion
ip_input.o_CFLAGS_ADD += -Wno-implicit-int-conversion
km.o_CFLAGS_ADD += -Wno-implicit-int-conversion
kpi_mbuf.o_CFLAGS_ADD += -Wno-implicit-int-conversion
necp.o_CFLAGS_ADD += -Wno-implicit-int-conversion
network_agent.o_CFLAGS_ADD += -Wno-implicit-int-conversion
nfs4_vnops.o_CFLAGS_ADD += -Wno-implicit-int-conversion
nfs_boot.o_CFLAGS_ADD += -Wno-implicit-int-conversion
nfs_gss.o_CFLAGS_ADD += -Wno-implicit-int-conversion
nfs_node.o_CFLAGS_ADD += -Wno-implicit-int-conversion
nfs_socket.o_CFLAGS_ADD += -Wno-implicit-int-conversion
nfs_subs.o_CFLAGS_ADD += -Wno-implicit-int-conversion
nfs_syscalls.o_CFLAGS_ADD += -Wno-implicit-int-conversion
nfs_vfsops.o_CFLAGS_ADD += -Wno-implicit-int-conversion
nfs_vnops.o_CFLAGS_ADD += -Wno-implicit-int-conversion
ntstat.o_CFLAGS_ADD += -Wno-implicit-int-conversion
null_vnops.o_CFLAGS_ADD += -Wno-implicit-int-conversion
pf.o_CFLAGS_ADD += -Wno-implicit-int-conversion
pf_norm.o_CFLAGS_ADD += -Wno-implicit-int-conversion
radix.o_CFLAGS_ADD += -Wno-implicit-int-conversion
route.o_CFLAGS_ADD += -Wno-implicit-int-conversion
shadow.o_CFLAGS_ADD += -Wno-implicit-int-conversion
skpc.o_CFLAGS_ADD += -Wno-implicit-int-conversion
spec_vnops.o_CFLAGS_ADD += -Wno-implicit-int-conversion
systemcalls.o_CFLAGS_ADD += -Wno-implicit-int-conversion
systrace.o_CFLAGS_ADD += -Wno-implicit-int-conversion
sysv_msg.o_CFLAGS_ADD += -Wno-implicit-int-conversion
sysv_sem.o_CFLAGS_ADD += -Wno-implicit-int-conversion
tcp_input.o_CFLAGS_ADD += -Wno-implicit-int-conversion
uipc_mbuf.o_CFLAGS_ADD += -Wno-implicit-int-conversion
uipc_socket.o_CFLAGS_ADD += -Wno-implicit-int-conversion
vfs_quota.o_CFLAGS_ADD += -Wno-implicit-int-conversion
vsock_domain.o_CFLAGS_ADD += -Wno-implicit-int-conversion
# -Wno-shorten-64-to-32
audit_bsm.o_CFLAGS_ADD += -Wno-shorten-64-to-32
audit_bsm_token.o_CFLAGS_ADD += -Wno-shorten-64-to-32
audit_pipe.o_CFLAGS_ADD += -Wno-shorten-64-to-32
audit_session.o_CFLAGS_ADD += -Wno-shorten-64-to-32
audit_syscalls.o_CFLAGS_ADD += -Wno-shorten-64-to-32
audit_worker.o_CFLAGS_ADD += -Wno-shorten-64-to-32
bind_vnops.o_CFLAGS_ADD += -Wno-shorten-64-to-32
bpf.o_CFLAGS_ADD += -Wno-shorten-64-to-32
devfs_fdesc_support.o_CFLAGS_ADD += -Wno-shorten-64-to-32
devfs_tree.o_CFLAGS_ADD += -Wno-shorten-64-to-32
devfs_vnops.o_CFLAGS_ADD += -Wno-shorten-64-to-32
devtimer.o_CFLAGS_ADD += -Wno-shorten-64-to-32
dis_tables.o_CFLAGS_ADD += -Wno-shorten-64-to-32
doc_tombstone.o_CFLAGS_ADD += -Wno-shorten-64-to-32
dtrace.o_CFLAGS_ADD += -Wno-shorten-64-to-32
dtrace_ptss.o_CFLAGS_ADD += -Wno-shorten-64-to-32
esp_chachapoly.o_CFLAGS_ADD += -Wno-shorten-64-to-32
fasttrap.o_CFLAGS_ADD += -Wno-shorten-64-to-32
fasttrap_isa.o_CFLAGS_ADD += -Wno-shorten-64-to-32
gss_krb5_mech.o_CFLAGS_ADD += -Wno-shorten-64-to-32
if.o_CFLAGS_ADD += -Wno-shorten-64-to-32
if_bond.o_CFLAGS_ADD += -Wno-shorten-64-to-32
if_bridge.o_CFLAGS_ADD += -Wno-shorten-64-to-32
if_fake.o_CFLAGS_ADD += -Wno-shorten-64-to-32
if_gif.o_CFLAGS_ADD += -Wno-shorten-64-to-32
if_ipsec.o_CFLAGS_ADD += -Wno-shorten-64-to-32
if_stf.o_CFLAGS_ADD += -Wno-shorten-64-to-32
if_utun.o_CFLAGS_ADD += -Wno-shorten-64-to-32
if_vlan.o_CFLAGS_ADD += -Wno-shorten-64-to-32
in6.o_CFLAGS_ADD += -Wno-shorten-64-to-32
in6_rmx.o_CFLAGS_ADD += -Wno-shorten-64-to-32
in_rmx.o_CFLAGS_ADD += -Wno-shorten-64-to-32
ip_dummynet.o_CFLAGS_ADD += -Wno-shorten-64-to-32
ip_input.o_CFLAGS_ADD += -Wno-shorten-64-to-32
iptap.o_CFLAGS_ADD += -Wno-shorten-64-to-32
kern_fork.o_CFLAGS_ADD += -Wno-shorten-64-to-32
kern_malloc.o_CFLAGS_ADD += -Wno-shorten-64-to-32
kern_overrides.o_CFLAGS_ADD += -Wno-shorten-64-to-32

kpi_mbuf.o_CFLAGS_ADD += -Wno-shorten-64-to-32
krpc_subr.o_CFLAGS_ADD += -Wno-shorten-64-to-32
lockprof.o_CFLAGS_ADD += -Wno-shorten-64-to-32
mem.o_CFLAGS_ADD += -Wno-shorten-64-to-32
memdev.o_CFLAGS_ADD += -Wno-shorten-64-to-32
nd6_rtr.o_CFLAGS_ADD += -Wno-shorten-64-to-32
necp.o_CFLAGS_ADD += -Wno-shorten-64-to-32
necp_client.o_CFLAGS_ADD += -Wno-shorten-64-to-32
network_agent.o_CFLAGS_ADD += -Wno-shorten-64-to-32
nfs4_subs.o_CFLAGS_ADD += -Wno-shorten-64-to-32
nfs4_vnops.o_CFLAGS_ADD += -Wno-shorten-64-to-32
nfs_bio.o_CFLAGS_ADD += -Wno-shorten-64-to-32
nfs_boot.o_CFLAGS_ADD += -Wno-shorten-64-to-32
nfs_gss.o_CFLAGS_ADD += -Wno-shorten-64-to-32
nfs_lock.o_CFLAGS_ADD += -Wno-shorten-64-to-32
nfs_node.o_CFLAGS_ADD += -Wno-shorten-64-to-32
nfs_serv.o_CFLAGS_ADD += -Wno-shorten-64-to-32
nfs_socket.o_CFLAGS_ADD += -Wno-shorten-64-to-32
nfs_subs.o_CFLAGS_ADD += -Wno-shorten-64-to-32
nfs_syscalls.o_CFLAGS_ADD += -Wno-shorten-64-to-32
nfs_vfsops.o_CFLAGS_ADD += -Wno-shorten-64-to-32
nfs_vnops.o_CFLAGS_ADD += -Wno-shorten-64-to-32
ntstat.o_CFLAGS_ADD += -Wno-shorten-64-to-32
null_vnops.o_CFLAGS_ADD += -Wno-shorten-64-to-32
pf.o_CFLAGS_ADD += -Wno-shorten-64-to-32
pf_norm.o_CFLAGS_ADD += -Wno-shorten-64-to-32
pf_pbuf.o_CFLAGS_ADD += -Wno-shorten-64-to-32
profile_prvd.o_CFLAGS_ADD += -Wno-shorten-64-to-32
profile_runtime.o_CFLAGS_ADD += -Wno-shorten-64-to-32
radix.o_CFLAGS_ADD += -Wno-shorten-64-to-32
route.o_CFLAGS_ADD += -Wno-shorten-64-to-32
sdt.o_CFLAGS_ADD += -Wno-shorten-64-to-32
shadow.o_CFLAGS_ADD += -Wno-shorten-64-to-32
skpc.o_CFLAGS_ADD += -Wno-shorten-64-to-32
spec_vnops.o_CFLAGS_ADD += -Wno-shorten-64-to-32
stubs.o_CFLAGS_ADD += -Wno-shorten-64-to-32
systemcalls.o_CFLAGS_ADD += -Wno-shorten-64-to-32
sysv_msg.o_CFLAGS_ADD += -Wno-shorten-64-to-32
sysv_sem.o_CFLAGS_ADD += -Wno-shorten-64-to-32
sysv_shm.o_CFLAGS_ADD += -Wno-shorten-64-to-32
tcp_input.o_CFLAGS_ADD += -Wno-shorten-64-to-32
uipc_mbuf.o_CFLAGS_ADD += -Wno-shorten-64-to-32
uipc_socket.o_CFLAGS_ADD += -Wno-shorten-64-to-32
unix_signal.o_CFLAGS_ADD += -Wno-shorten-64-to-32
ux_exception.o_CFLAGS_ADD += -Wno-shorten-64-to-32
vfs_cluster.o_CFLAGS_ADD += -Wno-shorten-64-to-32
vfs_quota.o_CFLAGS_ADD += -Wno-shorten-64-to-32
vfs_subr.o_CFLAGS_ADD += -Wno-shorten-64-to-32
vfs_support.o_CFLAGS_ADD += -Wno-shorten-64-to-32
vn.o_CFLAGS_ADD += -Wno-shorten-64-to-32
xcpm.o_CFLAGS_ADD += -Wno-shorten-64-to-32
# -Wno-sign-compare
dest6.o_CFLAGS_ADD += -Wno-sign-compare
dhcp_options.o_CFLAGS_ADD += -Wno-sign-compare
esp_chachapoly.o_CFLAGS_ADD += -Wno-sign-compare
frag6.o_CFLAGS_ADD += -Wno-sign-compare
in6.o_CFLAGS_ADD += -Wno-sign-compare
in6_cksum.o_CFLAGS_ADD += -Wno-sign-compare
in6_proto.o_CFLAGS_ADD += -Wno-sign-compare
ip_dummynet.o_CFLAGS_ADD += -Wno-sign-compare
ip_input.o_CFLAGS_ADD += -Wno-sign-compare
radix.o_CFLAGS_ADD += -Wno-sign-compare
route.o_CFLAGS_ADD += -Wno-sign-compare
route6.o_CFLAGS_ADD += -Wno-sign-compare
scope6.o_CFLAGS_ADD += -Wno-sign-compare
tcp_input.o_CFLAGS_ADD += -Wno-sign-compare
uipc_mbuf.o_CFLAGS_ADD += -Wno-sign-compare
uipc_socket.o_CFLAGS_ADD += -Wno-sign-compare
# -Wno-sign-conversion
audit.o_CFLAGS_ADD += -Wno-sign-conversion
audit_arg.o_CFLAGS_ADD += -Wno-sign-conversion
audit_bsd.o_CFLAGS_ADD += -Wno-sign-conversion
audit_bsm.o_CFLAGS_ADD += -Wno-sign-conversion
audit_bsm_klib.o_CFLAGS_ADD += -Wno-sign-conversion
audit_bsm_token.o_CFLAGS_ADD += -Wno-sign-conversion
audit_mac.o_CFLAGS_ADD += -Wno-sign-conversion
audit_pipe.o_CFLAGS_ADD += -Wno-sign-conversion
audit_session.o_CFLAGS_ADD += -Wno-sign-conversion
audit_syscalls.o_CFLAGS_ADD += -Wno-sign-conversion
audit_worker.o_CFLAGS_ADD += -Wno-sign-conversion
bind_vfsops.o_CFLAGS_ADD += -Wno-sign-conversion
bind_vnops.o_CFLAGS_ADD += -Wno-sign-conversion
blist.o_CFLAGS_ADD += -Wno-sign-conversion
bpf.o_CFLAGS_ADD += -Wno-sign-conversion
bsd_init.o_CFLAGS_ADD += -Wno-sign-conversion
bsd_stubs.o_CFLAGS_ADD += -Wno-sign-conversion
cbrtf.o_CFLAGS_ADD += -Wno-sign-conversion
chunklist.o_CFLAGS_ADD += -Wno-sign-conversion
content_filter.o_CFLAGS_ADD += -Wno-sign-conversion
cpu_in_cksum_gen.o_CFLAGS_ADD += -Wno-sign-conversion
cuckoo_hashtable_test.o_CFLAGS_ADD += -Wno-sign-conversion
decmpfs.o_CFLAGS_ADD += -Wno-sign-conversion
dest6.o_CFLAGS_ADD += -Wno-sign-conversion
devfs_fdesc_support.o_CFLAGS_ADD += -Wno-sign-conversion
devfs_tree.o_CFLAGS_ADD += -Wno-sign-conversion
devfs_vfsops.o_CFLAGS_ADD += -Wno-sign-conversion
devfs_vnops.o_CFLAGS_ADD += -Wno-sign-conversion
devtimer.o_CFLAGS_ADD += -Wno-sign-conversion
dhcp_options.o_CFLAGS_ADD += -Wno-sign-conversion
dis_tables.o_CFLAGS_ADD += -Wno-sign-conversion
disassembler.o_CFLAGS_ADD += -Wno-sign-conversion
doc_tombstone.o_CFLAGS_ADD += -Wno-sign-conversion
dtrace.o_CFLAGS_ADD += -Wno-sign-conversion
dtrace_glue.o_CFLAGS_ADD += -Wno-sign-conversion
dtrace_isa.o_CFLAGS_ADD += -Wno-sign-conversion
dtrace_ptss.o_CFLAGS_ADD += -Wno-sign-conversion
dtrace_subr.o_CFLAGS_ADD += -Wno-sign-conversion
dtrace_subr_arm.o_CFLAGS_ADD += -Wno-sign-conversion
ether_if_module.o_CFLAGS_ADD += -Wno-sign-conversion
ether_inet6_pr_module.o_CFLAGS_ADD += -Wno-sign-conversion
ether_inet_pr_module.o_CFLAGS_ADD += -Wno-sign-conversion
fasttrap.o_CFLAGS_ADD += -Wno-sign-conversion
fasttrap_isa.o_CFLAGS_ADD += -Wno-sign-conversion
fbt.o_CFLAGS_ADD += -Wno-sign-conversion
fbt_arm.o_CFLAGS_ADD += -Wno-sign-conversion
fbt_x86.o_CFLAGS_ADD += -Wno-sign-conversion
fifo_vnops.o_CFLAGS_ADD += -Wno-sign-conversion
flowhash.o_CFLAGS_ADD += -Wno-sign-conversion
frag6.o_CFLAGS_ADD += -Wno-sign-conversion
gss_krb5_mech.o_CFLAGS_ADD += -Wno-sign-conversion
if.o_CFLAGS_ADD += -Wno-sign-conversion
if_bond.o_CFLAGS_ADD += -Wno-sign-conversion
if_bridge.o_CFLAGS_ADD += -Wno-sign-conversion
if_fake.o_CFLAGS_ADD += -Wno-sign-conversion
if_gif.o_CFLAGS_ADD += -Wno-sign-conversion
if_ipsec.o_CFLAGS_ADD += -Wno-sign-conversion
if_llatbl.o_CFLAGS_ADD += -Wno-sign-conversion
if_loop.o_CFLAGS_ADD += -Wno-sign-conversion
if_low_power_mode.o_CFLAGS_ADD += -Wno-sign-conversion
if_pflog.o_CFLAGS_ADD += -Wno-sign-conversion
if_stf.o_CFLAGS_ADD += -Wno-sign-conversion
if_utun.o_CFLAGS_ADD += -Wno-sign-conversion
if_vlan.o_CFLAGS_ADD += -Wno-sign-conversion
imageboot.o_CFLAGS_ADD += -Wno-sign-conversion
in6.o_CFLAGS_ADD += -Wno-sign-conversion
in6_cga.o_CFLAGS_ADD += -Wno-sign-conversion
in6_cksum.o_CFLAGS_ADD += -Wno-sign-conversion
in6_gif.o_CFLAGS_ADD += -Wno-sign-conversion
in6_pcb.o_CFLAGS_ADD += -Wno-sign-conversion
in6_proto.o_CFLAGS_ADD += -Wno-sign-conversion
in6_rmx.o_CFLAGS_ADD += -Wno-sign-conversion
in_gif.o_CFLAGS_ADD += -Wno-sign-conversion
in_rmx.o_CFLAGS_ADD += -Wno-sign-conversion
instr_size.o_CFLAGS_ADD += -Wno-sign-conversion
ip6_forward.o_CFLAGS_ADD += -Wno-sign-conversion
ip6_id.o_CFLAGS_ADD += -Wno-sign-conversion
ip_dummynet.o_CFLAGS_ADD += -Wno-sign-conversion
ip_input.o_CFLAGS_ADD += -Wno-sign-conversion
iptap.o_CFLAGS_ADD += -Wno-sign-conversion
kern_acct.o_CFLAGS_ADD += -Wno-sign-conversion
kern_authorization.o_CFLAGS_ADD += -Wno-sign-conversion
kern_clock.o_CFLAGS_ADD += -Wno-sign-conversion
kern_control.o_CFLAGS_ADD += -Wno-sign-conversion
kern_core.o_CFLAGS_ADD += -Wno-sign-conversion
kern_credential.o_CFLAGS_ADD += -Wno-sign-conversion
kern_cs.o_CFLAGS_ADD += -Wno-sign-conversion
kern_descrip.o_CFLAGS_ADD += -Wno-sign-conversion
kern_event.o_CFLAGS_ADD += -Wno-sign-conversion
kern_exit.o_CFLAGS_ADD += -Wno-sign-conversion
kern_fork.o_CFLAGS_ADD += -Wno-sign-conversion
kern_guarded.o_CFLAGS_ADD += -Wno-sign-conversion
kern_kpc.o_CFLAGS_ADD += -Wno-sign-conversion
kern_lockf.o_CFLAGS_ADD += -Wno-sign-conversion
kern_malloc.o_CFLAGS_ADD += -Wno-sign-conversion
kern_memorystatus.o_CFLAGS_ADD += -Wno-sign-conversion
kern_memorystatus_freeze.o_CFLAGS_ADD += -Wno-sign-conversion
kern_memorystatus_notify.o_CFLAGS_ADD += -Wno-sign-conversion
kern_mib.o_CFLAGS_ADD += -Wno-sign-conversion
kern_mman.o_CFLAGS_ADD += -Wno-sign-conversion
kern_ntptime.o_CFLAGS_ADD += -Wno-sign-conversion
kern_overrides.o_CFLAGS_ADD += -Wno-sign-conversion
kern_persona.o_CFLAGS_ADD += -Wno-sign-conversion
kern_physio.o_CFLAGS_ADD += -Wno-sign-conversion
kern_proc.o_CFLAGS_ADD += -Wno-sign-conversion
kern_prot.o_CFLAGS_ADD += -Wno-sign-conversion
kern_resource.o_CFLAGS_ADD += -Wno-sign-conversion
kern_shutdown.o_CFLAGS_ADD += -Wno-sign-conversion
kern_sig.o_CFLAGS_ADD += -Wno-sign-conversion
kern_subr.o_CFLAGS_ADD += -Wno-sign-conversion
kern_symfile.o_CFLAGS_ADD += -Wno-sign-conversion
kern_synch.o_CFLAGS_ADD += -Wno-sign-conversion
kern_time.o_CFLAGS_ADD += -Wno-sign-conversion
km.o_CFLAGS_ADD += -Wno-sign-conversion
kpi_mbuf.o_CFLAGS_ADD += -Wno-sign-conversion
kpi_protocol.o_CFLAGS_ADD += -Wno-sign-conversion
kpi_socketfilter.o_CFLAGS_ADD += -Wno-sign-conversion
kpi_vfs.o_CFLAGS_ADD += -Wno-sign-conversion
krpc_subr.o_CFLAGS_ADD += -Wno-sign-conversion
lockprof.o_CFLAGS_ADD += -Wno-sign-conversion
mach_loader.o_CFLAGS_ADD += -Wno-sign-conversion
mach_process.o_CFLAGS_ADD += -Wno-sign-conversion
mem.o_CFLAGS_ADD += -Wno-sign-conversion
memdev.o_CFLAGS_ADD += -Wno-sign-conversion
monotonic.o_CFLAGS_ADD += -Wno-sign-conversion
munge.o_CFLAGS_ADD += -Wno-sign-conversion
nd6_prproxy.o_CFLAGS_ADD += -Wno-sign-conversion
nd6_send.o_CFLAGS_ADD += -Wno-sign-conversion
necp.o_CFLAGS_ADD += -Wno-sign-conversion
necp_client.o_CFLAGS_ADD += -Wno-sign-conversion
netboot.o_CFLAGS_ADD += -Wno-sign-conversion
network_agent.o_CFLAGS_ADD += -Wno-sign-conversion
nfs4_subs.o_CFLAGS_ADD += -Wno-sign-conversion
nfs4_vnops.o_CFLAGS_ADD += -Wno-sign-conversion
nfs_bio.o_CFLAGS_ADD += -Wno-sign-conversion
nfs_boot.o_CFLAGS_ADD += -Wno-sign-conversion
nfs_gss.o_CFLAGS_ADD += -Wno-sign-conversion
nfs_lock.o_CFLAGS_ADD += -Wno-sign-conversion
nfs_node.o_CFLAGS_ADD += -Wno-sign-conversion
nfs_serv.o_CFLAGS_ADD += -Wno-sign-conversion
nfs_socket.o_CFLAGS_ADD += -Wno-sign-conversion
nfs_subs.o_CFLAGS_ADD += -Wno-sign-conversion
nfs_syscalls.o_CFLAGS_ADD += -Wno-sign-conversion
nfs_upcall.o_CFLAGS_ADD += -Wno-sign-conversion
nfs_vfsops.o_CFLAGS_ADD += -Wno-sign-conversion
nfs_vnops.o_CFLAGS_ADD += -Wno-sign-conversion
ntstat.o_CFLAGS_ADD += -Wno-sign-conversion
null_vfsops.o_CFLAGS_ADD += -Wno-sign-conversion
null_vnops.o_CFLAGS_ADD += -Wno-sign-conversion
packet_mangler.o_CFLAGS_ADD += -Wno-sign-conversion
pf.o_CFLAGS_ADD += -Wno-sign-conversion
pf_norm.o_CFLAGS_ADD += -Wno-sign-conversion
pf_pbuf.o_CFLAGS_ADD += -Wno-sign-conversion
pf_table.o_CFLAGS_ADD += -Wno-sign-conversion
posix_sem.o_CFLAGS_ADD += -Wno-sign-conversion
posix_shm.o_CFLAGS_ADD += -Wno-sign-conversion
process_policy.o_CFLAGS_ADD += -Wno-sign-conversion
profile_prvd.o_CFLAGS_ADD += -Wno-sign-conversion
profile_runtime.o_CFLAGS_ADD += -Wno-sign-conversion
radix.o_CFLAGS_ADD += -Wno-sign-conversion
randomdev.o_CFLAGS_ADD += -Wno-sign-conversion
route.o_CFLAGS_ADD += -Wno-sign-conversion
route6.o_CFLAGS_ADD += -Wno-sign-conversion
routefs_ops.o_CFLAGS_ADD += -Wno-sign-conversion
scope6.o_CFLAGS_ADD += -Wno-sign-conversion
sdt.o_CFLAGS_ADD += -Wno-sign-conversion
sdt_arm.o_CFLAGS_ADD += -Wno-sign-conversion
sdt_x86.o_CFLAGS_ADD += -Wno-sign-conversion
shadow.o_CFLAGS_ADD += -Wno-sign-conversion
sixxlowpan.o_CFLAGS_ADD += -Wno-sign-conversion
spec_vnops.o_CFLAGS_ADD += -Wno-sign-conversion
subr_log.o_CFLAGS_ADD += -Wno-sign-conversion
subr_prf.o_CFLAGS_ADD += -Wno-sign-conversion
sys_coalition.o_CFLAGS_ADD += -Wno-sign-conversion
sys_generic.o_CFLAGS_ADD += -Wno-sign-conversion
sys_pipe.o_CFLAGS_ADD += -Wno-sign-conversion
sys_reason.o_CFLAGS_ADD += -Wno-sign-conversion
sys_ulock.o_CFLAGS_ADD += -Wno-sign-conversion
systemcalls.o_CFLAGS_ADD += -Wno-sign-conversion
systrace.o_CFLAGS_ADD += -Wno-sign-conversion
sysv_msg.o_CFLAGS_ADD += -Wno-sign-conversion
sysv_sem.o_CFLAGS_ADD += -Wno-sign-conversion
sysv_shm.o_CFLAGS_ADD += -Wno-sign-conversion
tcp_cc.o_CFLAGS_ADD += -Wno-sign-conversion
tcp_cubic.o_CFLAGS_ADD += -Wno-sign-conversion
tcp_input.o_CFLAGS_ADD += -Wno-sign-conversion
ubc_subr.o_CFLAGS_ADD += -Wno-sign-conversion
uipc_mbuf.o_CFLAGS_ADD += -Wno-sign-conversion
uipc_socket.o_CFLAGS_ADD += -Wno-sign-conversion
unix_signal.o_CFLAGS_ADD += -Wno-sign-conversion
unix_startup.o_CFLAGS_ADD += -Wno-sign-conversion
ux_exception.o_CFLAGS_ADD += -Wno-sign-conversion
vfs_attrlist.o_CFLAGS_ADD += -Wno-sign-conversion
vfs_bio.o_CFLAGS_ADD += -Wno-sign-conversion
vfs_cache.o_CFLAGS_ADD += -Wno-sign-conversion
vfs_cluster.o_CFLAGS_ADD += -Wno-sign-conversion
vfs_cprotect.o_CFLAGS_ADD += -Wno-sign-conversion
vfs_disk_conditioner.o_CFLAGS_ADD += -Wno-sign-conversion
vfs_fsevents.o_CFLAGS_ADD += -Wno-sign-conversion
vfs_fslog.o_CFLAGS_ADD += -Wno-sign-conversion
vfs_init.o_CFLAGS_ADD += -Wno-sign-conversion
vfs_lookup.o_CFLAGS_ADD += -Wno-sign-conversion
vfs_quota.o_CFLAGS_ADD += -Wno-sign-conversion
vfs_subr.o_CFLAGS_ADD += -Wno-sign-conversion
vfs_syscalls.o_CFLAGS_ADD += -Wno-sign-conversion
vfs_utfconv.o_CFLAGS_ADD += -Wno-sign-conversion
vfs_vnops.o_CFLAGS_ADD += -Wno-sign-conversion
vfs_xattr.o_CFLAGS_ADD += -Wno-sign-conversion
vm_compressor_backing_file.o_CFLAGS_ADD += -Wno-sign-conversion
vm_unix.o_CFLAGS_ADD += -Wno-sign-conversion
vn.o_CFLAGS_ADD += -Wno-sign-conversion
vnode_pager.o_CFLAGS_ADD += -Wno-sign-conversion

#
# Machine-independent per-file flags
#

#
# This rule insures that the subr_prof.c does NOT get compiled with
# profiling. It implements mcount() and profiling it leads to recursion.
#

subr_prof.o_CFLAGS_RM = -pg

# Rebuild if per-file overrides change
${OBJS}: $(firstword $(MAKEFILE_LIST))

# Rebuild if global compile flags change
$(COBJS): .CFLAGS
.CFLAGS: ALWAYS
	$(_v)$(REPLACECONTENTS) $@ $(KCC) $(CFLAGS) $(INCFLAGS)
$(CXXOBJS): .CXXFLAGS
.CXXFLAGS: ALWAYS
	$(_v)$(REPLACECONTENTS) $@ $(KC++) $(CXXFLAGS) $(INCFLAGS)
$(SOBJS): .SFLAGS
.SFLAGS: ALWAYS
	$(_v)$(REPLACECONTENTS) $@ $(S_KCC) $(SFLAGS) $(INCFLAGS)

$(COMPONENT).filelist: $(OBJS)
	@$(LOG_LDFILELIST) $(COMPONENT)
	$(_v)for obj in ${OBJS}; do	\
		 $(ECHO) $(TARGET)/$(CURRENT_KERNEL_CONFIG)/$${obj}; \
	done > $(COMPONENT).filelist

$(COMPONENT).libfilelist: $(LIBOBJS)
	@$(LOG_LDFILELIST) "lib$(COMPONENT)"
	$(_v)for obj in ${LIBOBJS}; do	\
		 $(ECHO) $(TARGET)/$(CURRENT_KERNEL_CONFIG)/$${obj}; \
	done > $(COMPONENT).libfilelist

MAKESYSCALLS = $(SRCROOT)/bsd/kern/makesyscalls.sh

init_sysent.c: $(TARGET)/bsd.syscalls.master
	@$(LOG_GENERATE) "$@$(Color0) from $(ColorF)$(<F)$(Color0)"
	$(_v)$(MAKESYSCALLS) $< table > /dev/null

syscalls.c: $(TARGET)/bsd.syscalls.master
	@$(LOG_GENERATE) "$@$(Color0) from $(ColorF)$(<F)$(Color0)"
	$(_v)$(MAKESYSCALLS) $< names > /dev/null

audit_kevents.c: $(TARGET)/bsd.syscalls.master
	@$(LOG_GENERATE) "$@$(Color0) from $(ColorF)$(<F)$(Color0)"
	$(_v)$(MAKESYSCALLS) $< audit > /dev/null

systrace_args.c: $(TARGET)/bsd.syscalls.master
	@$(LOG_GENERATE) "$@$(Color0) from $(ColorF)$(<F)$(Color0)"
	$(_v)$(MAKESYSCALLS) $< systrace > /dev/null

ifeq ($(RC_ProjectName),xnu_libraries)
do_all: $(COMPONENT).libfilelist
else
do_all: $(COMPONENT).filelist
endif

do_build_all:: do_all

-include nfs4_subs.d
nfs4_subs.o: $(SOURCE_DIR)/bsd/nfs/nfs4_subs.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_4B})
-include nfs4_vnops.d
nfs4_vnops.o: $(SOURCE_DIR)/bsd/nfs/nfs4_vnops.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_4B})
-include krpc_subr.d
krpc_subr.o: $(SOURCE_DIR)/bsd/nfs/krpc_subr.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_4B})
-include nfs_bio.d
nfs_bio.o: $(SOURCE_DIR)/bsd/nfs/nfs_bio.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_4B})
-include nfs_boot.d
nfs_boot.o: $(SOURCE_DIR)/bsd/nfs/nfs_boot.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_4B})
-include nfs_gss.d
nfs_gss.o: $(SOURCE_DIR)/bsd/nfs/nfs_gss.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_4B})
-include nfs_lock.d
nfs_lock.o: $(SOURCE_DIR)/bsd/nfs/nfs_lock.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_4B})
-include nfs_node.d
nfs_node.o: $(SOURCE_DIR)/bsd/nfs/nfs_node.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_4B})
-include nfs_serv.d
nfs_serv.o: $(SOURCE_DIR)/bsd/nfs/nfs_serv.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_4B})
-include nfs_socket.d
nfs_socket.o: $(SOURCE_DIR)/bsd/nfs/nfs_socket.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_4B})
-include nfs_srvcache.d
nfs_srvcache.o: $(SOURCE_DIR)/bsd/nfs/nfs_srvcache.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_4B})
-include nfs_subs.d
nfs_subs.o: $(SOURCE_DIR)/bsd/nfs/nfs_subs.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_4B})
-include nfs_syscalls.d
nfs_syscalls.o: $(SOURCE_DIR)/bsd/nfs/nfs_syscalls.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_4B})
-include nfs_vfsops.d
nfs_vfsops.o: $(SOURCE_DIR)/bsd/nfs/nfs_vfsops.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_4B})
-include nfs_vnops.d
nfs_vnops.o: $(SOURCE_DIR)/bsd/nfs/nfs_vnops.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_4B})
-include nfs_upcall.d
nfs_upcall.o: $(SOURCE_DIR)/bsd/nfs/nfs_upcall.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/nfs/${C_RULE_4B})
-include gss_krb5_mech.d
gss_krb5_mech.o: $(SOURCE_DIR)/bsd/nfs/gss/gss_krb5_mech.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/nfs/gss/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/nfs/gss/${C_RULE_4B})
-include ccrypto.d
ccrypto.o: $(SOURCE_DIR)/bsd/nfs/gss/ccrypto.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/nfs/gss/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/nfs/gss/${C_RULE_4B})
-include netboot.d
netboot.o: $(SOURCE_DIR)/bsd/kern/netboot.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include dtrace.d
dtrace.o: $(SOURCE_DIR)/bsd/dev/dtrace/dtrace.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_4B})
-include lockprof.d
lockprof.o: $(SOURCE_DIR)/bsd/dev/dtrace/lockprof.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_4B})
-include lockstat.d
lockstat.o: $(SOURCE_DIR)/bsd/dev/dtrace/lockstat.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_4B})
-include dtrace_ptss.d
dtrace_ptss.o: $(SOURCE_DIR)/bsd/dev/dtrace/dtrace_ptss.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_4B})
-include dtrace_subr.d
dtrace_subr.o: $(SOURCE_DIR)/bsd/dev/dtrace/dtrace_subr.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_4B})
-include dtrace_glue.d
dtrace_glue.o: $(SOURCE_DIR)/bsd/dev/dtrace/dtrace_glue.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_4B})
-include dtrace_xoroshiro128_plus.d
dtrace_xoroshiro128_plus.o: $(SOURCE_DIR)/bsd/dev/dtrace/dtrace_xoroshiro128_plus.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_4B})
-include blist.d
blist.o: $(SOURCE_DIR)/bsd/dev/dtrace/blist.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_4B})
-include fbt.d
fbt.o: $(SOURCE_DIR)/bsd/dev/dtrace/fbt.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_4B})
-include fbt_blacklist.d
fbt_blacklist.o: $(SOURCE_DIR)/bsd/dev/dtrace/fbt_blacklist.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_4B})
-include sdt.d
sdt.o: $(SOURCE_DIR)/bsd/dev/dtrace/sdt.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_4B})
-include sdt_subr.d
sdt_subr.o: $(SOURCE_DIR)/bsd/dev/dtrace/sdt_subr.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_4B})
-include systrace.d
systrace.o: $(SOURCE_DIR)/bsd/dev/dtrace/systrace.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_4B})
-include profile_prvd.d
profile_prvd.o: $(SOURCE_DIR)/bsd/dev/dtrace/profile_prvd.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_4B})
-include fasttrap.d
fasttrap.o: $(SOURCE_DIR)/bsd/dev/dtrace/fasttrap.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/dtrace/${C_RULE_4B})
-include systrace_args.d
systrace_args.o: systrace_args.c
	${C_RULE_0}
	${C_RULE_1A}${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}${C_RULE_4B})
-include randomdev.d
randomdev.o: $(SOURCE_DIR)/bsd/dev/random/randomdev.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/random/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/random/${C_RULE_4B})
-include memdev.d
memdev.o: $(SOURCE_DIR)/bsd/dev/memdev.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/${C_RULE_4B})
-include mem.d
mem.o: $(SOURCE_DIR)/bsd/dev/mem.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/${C_RULE_4B})
-include munge.d
munge.o: $(SOURCE_DIR)/bsd/dev/munge.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/${C_RULE_4B})
-include unix_startup.d
unix_startup.o: $(SOURCE_DIR)/bsd/dev/unix_startup.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/${C_RULE_4B})
-include vn.d
vn.o: $(SOURCE_DIR)/bsd/dev/vn/vn.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/vn/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/vn/${C_RULE_4B})
-include shadow.d
shadow.o: $(SOURCE_DIR)/bsd/dev/vn/shadow.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/vn/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/vn/${C_RULE_4B})
-include crc16.d
crc16.o: $(SOURCE_DIR)/bsd/libkern/crc16.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/libkern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/libkern/${C_RULE_4B})
-include crc32.d
crc32.o: $(SOURCE_DIR)/bsd/libkern/crc32.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/libkern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/libkern/${C_RULE_4B})
-include random.d
random.o: $(SOURCE_DIR)/bsd/libkern/random.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/libkern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/libkern/${C_RULE_4B})
-include scanc.d
scanc.o: $(SOURCE_DIR)/bsd/libkern/scanc.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/libkern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/libkern/${C_RULE_4B})
-include strsep.d
strsep.o: $(SOURCE_DIR)/bsd/libkern/strsep.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/libkern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/libkern/${C_RULE_4B})
-include bcd.d
bcd.o: $(SOURCE_DIR)/bsd/libkern/bcd.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/libkern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/libkern/${C_RULE_4B})
-include memchr.d
memchr.o: $(SOURCE_DIR)/bsd/libkern/memchr.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/libkern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/libkern/${C_RULE_4B})
-include url_encode.d
url_encode.o: $(SOURCE_DIR)/bsd/libkern/url_encode.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/libkern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/libkern/${C_RULE_4B})
-include vfs_attrlist.d
vfs_attrlist.o: $(SOURCE_DIR)/bsd/vfs/vfs_attrlist.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_4B})
-include vfs_bio.d
vfs_bio.o: $(SOURCE_DIR)/bsd/vfs/vfs_bio.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_4B})
-include vfs_cache.d
vfs_cache.o: $(SOURCE_DIR)/bsd/vfs/vfs_cache.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_4B})
-include vfs_cluster.d
vfs_cluster.o: $(SOURCE_DIR)/bsd/vfs/vfs_cluster.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_4B})
-include vfs_conf.d
vfs_conf.o: $(SOURCE_DIR)/bsd/vfs/vfs_conf.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_4B})
-include vfs_fslog.d
vfs_fslog.o: $(SOURCE_DIR)/bsd/vfs/vfs_fslog.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_4B})
-include vfs_init.d
vfs_init.o: $(SOURCE_DIR)/bsd/vfs/vfs_init.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_4B})
-include vfs_lookup.d
vfs_lookup.o: $(SOURCE_DIR)/bsd/vfs/vfs_lookup.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_4B})
-include vfs_quota.d
vfs_quota.o: $(SOURCE_DIR)/bsd/vfs/vfs_quota.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_4B})
-include vfs_subr.d
vfs_subr.o: $(SOURCE_DIR)/bsd/vfs/vfs_subr.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_4B})
-include vfs_syscalls.d
vfs_syscalls.o: $(SOURCE_DIR)/bsd/vfs/vfs_syscalls.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_4B})
-include vfs_support.d
vfs_support.o: $(SOURCE_DIR)/bsd/vfs/vfs_support.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_4B})
-include vfs_utfconv.d
vfs_utfconv.o: $(SOURCE_DIR)/bsd/vfs/vfs_utfconv.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_4B})
-include vfs_unicode.d
vfs_unicode.o: $(SOURCE_DIR)/bsd/vfs/vfs_unicode.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_4B})
-include vfs_vnops.d
vfs_vnops.o: $(SOURCE_DIR)/bsd/vfs/vfs_vnops.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_4B})
-include vfs_xattr.d
vfs_xattr.o: $(SOURCE_DIR)/bsd/vfs/vfs_xattr.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_4B})
-include vnode_if.d
vnode_if.o: $(SOURCE_DIR)/bsd/vfs/vnode_if.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_4B})
-include kpi_vfs.d
kpi_vfs.o: $(SOURCE_DIR)/bsd/vfs/kpi_vfs.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_4B})
-include vfs_fsevents.d
vfs_fsevents.o: $(SOURCE_DIR)/bsd/vfs/vfs_fsevents.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_4B})
-include vfs_cprotect.d
vfs_cprotect.o: $(SOURCE_DIR)/bsd/vfs/vfs_cprotect.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_4B})
-include doc_tombstone.d
doc_tombstone.o: $(SOURCE_DIR)/bsd/vfs/doc_tombstone.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_4B})
-include vfs_disk_conditioner.d
vfs_disk_conditioner.o: $(SOURCE_DIR)/bsd/vfs/vfs_disk_conditioner.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/vfs/${C_RULE_4B})
-include dead_vnops.d
dead_vnops.o: $(SOURCE_DIR)/bsd/miscfs/deadfs/dead_vnops.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/miscfs/deadfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/miscfs/deadfs/${C_RULE_4B})
-include devfs_fdesc_support.d
devfs_fdesc_support.o: $(SOURCE_DIR)/bsd/miscfs/devfs/devfs_fdesc_support.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/miscfs/devfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/miscfs/devfs/${C_RULE_4B})
-include fifo_vnops.d
fifo_vnops.o: $(SOURCE_DIR)/bsd/miscfs/fifofs/fifo_vnops.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/miscfs/fifofs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/miscfs/fifofs/${C_RULE_4B})
-include spec_vnops.d
spec_vnops.o: $(SOURCE_DIR)/bsd/miscfs/specfs/spec_vnops.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/miscfs/specfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/miscfs/specfs/${C_RULE_4B})
-include devfs_tree.d
devfs_tree.o: $(SOURCE_DIR)/bsd/miscfs/devfs/devfs_tree.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/miscfs/devfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/miscfs/devfs/${C_RULE_4B})
-include devfs_vnops.d
devfs_vnops.o: $(SOURCE_DIR)/bsd/miscfs/devfs/devfs_vnops.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/miscfs/devfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/miscfs/devfs/${C_RULE_4B})
-include devfs_vfsops.d
devfs_vfsops.o: $(SOURCE_DIR)/bsd/miscfs/devfs/devfs_vfsops.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/miscfs/devfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/miscfs/devfs/${C_RULE_4B})
-include decmpfs.d
decmpfs.o: $(SOURCE_DIR)/bsd/kern/decmpfs.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include net_stubs.d
net_stubs.o: $(SOURCE_DIR)/bsd/net/net_stubs.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include bpf.d
bpf.o: $(SOURCE_DIR)/bsd/net/bpf.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include bpf_filter.d
bpf_filter.o: $(SOURCE_DIR)/bsd/net/bpf_filter.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include if_bridge.d
if_bridge.o: $(SOURCE_DIR)/bsd/net/if_bridge.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include if.d
if.o: $(SOURCE_DIR)/bsd/net/if.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include init.d
init.o: $(SOURCE_DIR)/bsd/net/init.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include dlil.d
dlil.o: $(SOURCE_DIR)/bsd/net/dlil.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include ether_if_module.d
ether_if_module.o: $(SOURCE_DIR)/bsd/net/ether_if_module.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include ether_inet_pr_module.d
ether_inet_pr_module.o: $(SOURCE_DIR)/bsd/net/ether_inet_pr_module.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include ether_inet6_pr_module.d
ether_inet6_pr_module.o: $(SOURCE_DIR)/bsd/net/ether_inet6_pr_module.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include if_loop.d
if_loop.o: $(SOURCE_DIR)/bsd/net/if_loop.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include if_mib.d
if_mib.o: $(SOURCE_DIR)/bsd/net/if_mib.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include if_vlan.d
if_vlan.o: $(SOURCE_DIR)/bsd/net/if_vlan.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include if_fake.d
if_fake.o: $(SOURCE_DIR)/bsd/net/if_fake.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include if_headless.d
if_headless.o: $(SOURCE_DIR)/bsd/net/if_headless.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include if_6lowpan.d
if_6lowpan.o: $(SOURCE_DIR)/bsd/net/if_6lowpan.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include multicast_list.d
multicast_list.o: $(SOURCE_DIR)/bsd/net/multicast_list.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include if_bond.d
if_bond.o: $(SOURCE_DIR)/bsd/net/if_bond.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include devtimer.d
devtimer.o: $(SOURCE_DIR)/bsd/net/devtimer.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include ndrv.d
ndrv.o: $(SOURCE_DIR)/bsd/net/ndrv.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include radix.d
radix.o: $(SOURCE_DIR)/bsd/net/radix.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include raw_cb.d
raw_cb.o: $(SOURCE_DIR)/bsd/net/raw_cb.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include raw_usrreq.d
raw_usrreq.o: $(SOURCE_DIR)/bsd/net/raw_usrreq.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include route.d
route.o: $(SOURCE_DIR)/bsd/net/route.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include rtsock.d
rtsock.o: $(SOURCE_DIR)/bsd/net/rtsock.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include netsrc.d
netsrc.o: $(SOURCE_DIR)/bsd/net/netsrc.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include ntstat.d
ntstat.o: $(SOURCE_DIR)/bsd/net/ntstat.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include net_perf.d
net_perf.o: $(SOURCE_DIR)/bsd/net/net_perf.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include if_gif.d
if_gif.o: $(SOURCE_DIR)/bsd/net/if_gif.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include if_stf.d
if_stf.o: $(SOURCE_DIR)/bsd/net/if_stf.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include if_ports_used.d
if_ports_used.o: $(SOURCE_DIR)/bsd/net/if_ports_used.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include if_low_power_mode.d
if_low_power_mode.o: $(SOURCE_DIR)/bsd/net/if_low_power_mode.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include kpi_interface.d
kpi_interface.o: $(SOURCE_DIR)/bsd/net/kpi_interface.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include kpi_protocol.d
kpi_protocol.o: $(SOURCE_DIR)/bsd/net/kpi_protocol.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include kpi_interfacefilter.d
kpi_interfacefilter.o: $(SOURCE_DIR)/bsd/net/kpi_interfacefilter.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include net_str_id.d
net_str_id.o: $(SOURCE_DIR)/bsd/net/net_str_id.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include if_utun.d
if_utun.o: $(SOURCE_DIR)/bsd/net/if_utun.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include if_ipsec.d
if_ipsec.o: $(SOURCE_DIR)/bsd/net/if_ipsec.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include necp.d
necp.o: $(SOURCE_DIR)/bsd/net/necp.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include necp_client.d
necp_client.o: $(SOURCE_DIR)/bsd/net/necp_client.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include network_agent.d
network_agent.o: $(SOURCE_DIR)/bsd/net/network_agent.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include if_pflog.d
if_pflog.o: $(SOURCE_DIR)/bsd/net/if_pflog.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include nat464_utils.d
nat464_utils.o: $(SOURCE_DIR)/bsd/net/nat464_utils.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include pf.d
pf.o: $(SOURCE_DIR)/bsd/net/pf.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include pf_if.d
pf_if.o: $(SOURCE_DIR)/bsd/net/pf_if.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include pf_ioctl.d
pf_ioctl.o: $(SOURCE_DIR)/bsd/net/pf_ioctl.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include pf_norm.d
pf_norm.o: $(SOURCE_DIR)/bsd/net/pf_norm.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include pf_osfp.d
pf_osfp.o: $(SOURCE_DIR)/bsd/net/pf_osfp.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include pf_pbuf.d
pf_pbuf.o: $(SOURCE_DIR)/bsd/net/pf_pbuf.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include pf_ruleset.d
pf_ruleset.o: $(SOURCE_DIR)/bsd/net/pf_ruleset.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include pf_table.d
pf_table.o: $(SOURCE_DIR)/bsd/net/pf_table.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include iptap.d
iptap.o: $(SOURCE_DIR)/bsd/net/iptap.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include pktap.d
pktap.o: $(SOURCE_DIR)/bsd/net/pktap.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include if_llreach.d
if_llreach.o: $(SOURCE_DIR)/bsd/net/if_llreach.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include flowhash.d
flowhash.o: $(SOURCE_DIR)/bsd/net/flowhash.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include flowadv.d
flowadv.o: $(SOURCE_DIR)/bsd/net/flowadv.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include content_filter.d
content_filter.o: $(SOURCE_DIR)/bsd/net/content_filter.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include content_filter_crypto.d
content_filter_crypto.o: $(SOURCE_DIR)/bsd/net/content_filter_crypto.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include packet_mangler.d
packet_mangler.o: $(SOURCE_DIR)/bsd/net/packet_mangler.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include if_llatbl.d
if_llatbl.o: $(SOURCE_DIR)/bsd/net/if_llatbl.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include nwk_wq.d
nwk_wq.o: $(SOURCE_DIR)/bsd/net/nwk_wq.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include restricted_in_port.d
restricted_in_port.o: $(SOURCE_DIR)/bsd/net/restricted_in_port.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include classq.d
classq.o: $(SOURCE_DIR)/bsd/net/classq/classq.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/classq/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/classq/${C_RULE_4B})
-include classq_sfb.d
classq_sfb.o: $(SOURCE_DIR)/bsd/net/classq/classq_sfb.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/classq/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/classq/${C_RULE_4B})
-include classq_subr.d
classq_subr.o: $(SOURCE_DIR)/bsd/net/classq/classq_subr.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/classq/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/classq/${C_RULE_4B})
-include classq_util.d
classq_util.o: $(SOURCE_DIR)/bsd/net/classq/classq_util.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/classq/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/classq/${C_RULE_4B})
-include classq_fq_codel.d
classq_fq_codel.o: $(SOURCE_DIR)/bsd/net/classq/classq_fq_codel.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/classq/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/classq/${C_RULE_4B})
-include pktsched.d
pktsched.o: $(SOURCE_DIR)/bsd/net/pktsched/pktsched.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/pktsched/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/pktsched/${C_RULE_4B})
-include pktsched_fq_codel.d
pktsched_fq_codel.o: $(SOURCE_DIR)/bsd/net/pktsched/pktsched_fq_codel.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/pktsched/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/pktsched/${C_RULE_4B})
-include pktsched_netem.d
pktsched_netem.o: $(SOURCE_DIR)/bsd/net/pktsched/pktsched_netem.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/pktsched/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/pktsched/${C_RULE_4B})
-include cpu_in_cksum_gen.d
cpu_in_cksum_gen.o: $(SOURCE_DIR)/bsd/netinet/cpu_in_cksum_gen.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include in_cksum.d
in_cksum.o: $(SOURCE_DIR)/bsd/netinet/in_cksum.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include igmp.d
igmp.o: $(SOURCE_DIR)/bsd/netinet/igmp.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include in.d
in.o: $(SOURCE_DIR)/bsd/netinet/in.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include dhcp_options.d
dhcp_options.o: $(SOURCE_DIR)/bsd/netinet/dhcp_options.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include in_arp.d
in_arp.o: $(SOURCE_DIR)/bsd/netinet/in_arp.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include in_mcast.d
in_mcast.o: $(SOURCE_DIR)/bsd/netinet/in_mcast.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include in_pcb.d
in_pcb.o: $(SOURCE_DIR)/bsd/netinet/in_pcb.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include in_pcblist.d
in_pcblist.o: $(SOURCE_DIR)/bsd/netinet/in_pcblist.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include in_proto.d
in_proto.o: $(SOURCE_DIR)/bsd/netinet/in_proto.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include in_rmx.d
in_rmx.o: $(SOURCE_DIR)/bsd/netinet/in_rmx.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include in_stat.d
in_stat.o: $(SOURCE_DIR)/bsd/netinet/in_stat.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include in_tclass.d
in_tclass.o: $(SOURCE_DIR)/bsd/netinet/in_tclass.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include ip_dummynet.d
ip_dummynet.o: $(SOURCE_DIR)/bsd/netinet/ip_dummynet.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include ip_icmp.d
ip_icmp.o: $(SOURCE_DIR)/bsd/netinet/ip_icmp.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include ip_id.d
ip_id.o: $(SOURCE_DIR)/bsd/netinet/ip_id.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include ip_input.d
ip_input.o: $(SOURCE_DIR)/bsd/netinet/ip_input.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include ip_output.d
ip_output.o: $(SOURCE_DIR)/bsd/netinet/ip_output.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include raw_ip.d
raw_ip.o: $(SOURCE_DIR)/bsd/netinet/raw_ip.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include tcp_cache.d
tcp_cache.o: $(SOURCE_DIR)/bsd/netinet/tcp_cache.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include tcp_input.d
tcp_input.o: $(SOURCE_DIR)/bsd/netinet/tcp_input.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include tcp_output.d
tcp_output.o: $(SOURCE_DIR)/bsd/netinet/tcp_output.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include tcp_sack.d
tcp_sack.o: $(SOURCE_DIR)/bsd/netinet/tcp_sack.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include tcp_subr.d
tcp_subr.o: $(SOURCE_DIR)/bsd/netinet/tcp_subr.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include tcp_timer.d
tcp_timer.o: $(SOURCE_DIR)/bsd/netinet/tcp_timer.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include tcp_usrreq.d
tcp_usrreq.o: $(SOURCE_DIR)/bsd/netinet/tcp_usrreq.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include tcp_cc.d
tcp_cc.o: $(SOURCE_DIR)/bsd/netinet/tcp_cc.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include tcp_newreno.d
tcp_newreno.o: $(SOURCE_DIR)/bsd/netinet/tcp_newreno.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include tcp_cubic.d
tcp_cubic.o: $(SOURCE_DIR)/bsd/netinet/tcp_cubic.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include cbrtf.d
cbrtf.o: $(SOURCE_DIR)/bsd/netinet/cbrtf.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include tcp_ledbat.d
tcp_ledbat.o: $(SOURCE_DIR)/bsd/netinet/tcp_ledbat.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include tcp_log.d
tcp_log.o: $(SOURCE_DIR)/bsd/netinet/tcp_log.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include udp_usrreq.d
udp_usrreq.o: $(SOURCE_DIR)/bsd/netinet/udp_usrreq.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include in_gif.d
in_gif.o: $(SOURCE_DIR)/bsd/netinet/in_gif.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include ip_ecn.d
ip_ecn.o: $(SOURCE_DIR)/bsd/netinet/ip_ecn.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include ip_encap.d
ip_encap.o: $(SOURCE_DIR)/bsd/netinet/ip_encap.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include kpi_ipfilter.d
kpi_ipfilter.o: $(SOURCE_DIR)/bsd/netinet/kpi_ipfilter.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include flow_divert.d
flow_divert.o: $(SOURCE_DIR)/bsd/netinet/flow_divert.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include mp_proto.d
mp_proto.o: $(SOURCE_DIR)/bsd/netinet/mp_proto.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include mp_pcb.d
mp_pcb.o: $(SOURCE_DIR)/bsd/netinet/mp_pcb.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include mptcp.d
mptcp.o: $(SOURCE_DIR)/bsd/netinet/mptcp.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include mptcp_subr.d
mptcp_subr.o: $(SOURCE_DIR)/bsd/netinet/mptcp_subr.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include mptcp_usrreq.d
mptcp_usrreq.o: $(SOURCE_DIR)/bsd/netinet/mptcp_usrreq.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include mptcp_opt.d
mptcp_opt.o: $(SOURCE_DIR)/bsd/netinet/mptcp_opt.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include mptcp_timer.d
mptcp_timer.o: $(SOURCE_DIR)/bsd/netinet/mptcp_timer.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet/${C_RULE_4B})
-include ah_core.d
ah_core.o: $(SOURCE_DIR)/bsd/netinet6/ah_core.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include ah_input.d
ah_input.o: $(SOURCE_DIR)/bsd/netinet6/ah_input.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include ah_output.d
ah_output.o: $(SOURCE_DIR)/bsd/netinet6/ah_output.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include esp_core.d
esp_core.o: $(SOURCE_DIR)/bsd/netinet6/esp_core.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include esp_input.d
esp_input.o: $(SOURCE_DIR)/bsd/netinet6/esp_input.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include esp_output.d
esp_output.o: $(SOURCE_DIR)/bsd/netinet6/esp_output.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include esp_rijndael.d
esp_rijndael.o: $(SOURCE_DIR)/bsd/netinet6/esp_rijndael.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include esp_chachapoly.d
esp_chachapoly.o: $(SOURCE_DIR)/bsd/netinet6/esp_chachapoly.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include ipsec.d
ipsec.o: $(SOURCE_DIR)/bsd/netinet6/ipsec.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include dest6.d
dest6.o: $(SOURCE_DIR)/bsd/netinet6/dest6.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include frag6.d
frag6.o: $(SOURCE_DIR)/bsd/netinet6/frag6.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include icmp6.d
icmp6.o: $(SOURCE_DIR)/bsd/netinet6/icmp6.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include in6.d
in6.o: $(SOURCE_DIR)/bsd/netinet6/in6.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include in6_cga.d
in6_cga.o: $(SOURCE_DIR)/bsd/netinet6/in6_cga.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include in6_cksum.d
in6_cksum.o: $(SOURCE_DIR)/bsd/netinet6/in6_cksum.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include in6_gif.d
in6_gif.o: $(SOURCE_DIR)/bsd/netinet6/in6_gif.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include ip6_forward.d
ip6_forward.o: $(SOURCE_DIR)/bsd/netinet6/ip6_forward.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include in6_ifattach.d
in6_ifattach.o: $(SOURCE_DIR)/bsd/netinet6/in6_ifattach.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include ip6_input.d
ip6_input.o: $(SOURCE_DIR)/bsd/netinet6/ip6_input.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include ip6_output.d
ip6_output.o: $(SOURCE_DIR)/bsd/netinet6/ip6_output.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include in6_src.d
in6_src.o: $(SOURCE_DIR)/bsd/netinet6/in6_src.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include in6_mcast.d
in6_mcast.o: $(SOURCE_DIR)/bsd/netinet6/in6_mcast.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include in6_pcb.d
in6_pcb.o: $(SOURCE_DIR)/bsd/netinet6/in6_pcb.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include in6_proto.d
in6_proto.o: $(SOURCE_DIR)/bsd/netinet6/in6_proto.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include in6_rmx.d
in6_rmx.o: $(SOURCE_DIR)/bsd/netinet6/in6_rmx.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include mld6.d
mld6.o: $(SOURCE_DIR)/bsd/netinet6/mld6.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include nd6.d
nd6.o: $(SOURCE_DIR)/bsd/netinet6/nd6.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include nd6_nbr.d
nd6_nbr.o: $(SOURCE_DIR)/bsd/netinet6/nd6_nbr.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include nd6_prproxy.d
nd6_prproxy.o: $(SOURCE_DIR)/bsd/netinet6/nd6_prproxy.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include nd6_rtr.d
nd6_rtr.o: $(SOURCE_DIR)/bsd/netinet6/nd6_rtr.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include nd6_rti.d
nd6_rti.o: $(SOURCE_DIR)/bsd/netinet6/nd6_rti.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include nd6_send.d
nd6_send.o: $(SOURCE_DIR)/bsd/netinet6/nd6_send.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include raw_ip6.d
raw_ip6.o: $(SOURCE_DIR)/bsd/netinet6/raw_ip6.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include route6.d
route6.o: $(SOURCE_DIR)/bsd/netinet6/route6.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include scope6.d
scope6.o: $(SOURCE_DIR)/bsd/netinet6/scope6.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include udp6_output.d
udp6_output.o: $(SOURCE_DIR)/bsd/netinet6/udp6_output.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include udp6_usrreq.d
udp6_usrreq.o: $(SOURCE_DIR)/bsd/netinet6/udp6_usrreq.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include ip6_id.d
ip6_id.o: $(SOURCE_DIR)/bsd/netinet6/ip6_id.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netinet6/${C_RULE_4B})
-include sixxlowpan.d
sixxlowpan.o: $(SOURCE_DIR)/bsd/net/sixxlowpan.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include frame802154.d
frame802154.o: $(SOURCE_DIR)/bsd/net/frame802154.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include linkaddr.d
linkaddr.o: $(SOURCE_DIR)/bsd/net/linkaddr.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include key.d
key.o: $(SOURCE_DIR)/bsd/netkey/key.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netkey/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netkey/${C_RULE_4B})
-include key_debug.d
key_debug.o: $(SOURCE_DIR)/bsd/netkey/key_debug.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netkey/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netkey/${C_RULE_4B})
-include keysock.d
keysock.o: $(SOURCE_DIR)/bsd/netkey/keysock.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netkey/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netkey/${C_RULE_4B})
-include keydb.d
keydb.o: $(SOURCE_DIR)/bsd/netkey/keydb.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/netkey/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/netkey/${C_RULE_4B})
-include multi_layer_pkt_log.d
multi_layer_pkt_log.o: $(SOURCE_DIR)/bsd/net/multi_layer_pkt_log.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include entropy_sysctl.d
entropy_sysctl.o: $(SOURCE_DIR)/bsd/crypto/entropy/entropy_sysctl.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/crypto/entropy/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/crypto/entropy/${C_RULE_4B})
-include audit.d
audit.o: $(SOURCE_DIR)/bsd/security/audit/audit.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_4B})
-include audit_arg.d
audit_arg.o: $(SOURCE_DIR)/bsd/security/audit/audit_arg.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_4B})
-include audit_bsd.d
audit_bsd.o: $(SOURCE_DIR)/bsd/security/audit/audit_bsd.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_4B})
-include audit_bsm.d
audit_bsm.o: $(SOURCE_DIR)/bsd/security/audit/audit_bsm.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_4B})
-include audit_bsm_errno.d
audit_bsm_errno.o: $(SOURCE_DIR)/bsd/security/audit/audit_bsm_errno.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_4B})
-include audit_bsm_fcntl.d
audit_bsm_fcntl.o: $(SOURCE_DIR)/bsd/security/audit/audit_bsm_fcntl.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_4B})
-include audit_bsm_domain.d
audit_bsm_domain.o: $(SOURCE_DIR)/bsd/security/audit/audit_bsm_domain.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_4B})
-include audit_bsm_klib.d
audit_bsm_klib.o: $(SOURCE_DIR)/bsd/security/audit/audit_bsm_klib.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_4B})
-include audit_bsm_socket_type.d
audit_bsm_socket_type.o: $(SOURCE_DIR)/bsd/security/audit/audit_bsm_socket_type.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_4B})
-include audit_bsm_token.d
audit_bsm_token.o: $(SOURCE_DIR)/bsd/security/audit/audit_bsm_token.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_4B})
-include audit_kevents.d
audit_kevents.o: audit_kevents.c
	${C_RULE_0}
	${C_RULE_1A}${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}${C_RULE_4B})
-include audit_mac.d
audit_mac.o: $(SOURCE_DIR)/bsd/security/audit/audit_mac.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_4B})
-include audit_pipe.d
audit_pipe.o: $(SOURCE_DIR)/bsd/security/audit/audit_pipe.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_4B})
-include audit_session.d
audit_session.o: $(SOURCE_DIR)/bsd/security/audit/audit_session.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_4B})
-include audit_syscalls.d
audit_syscalls.o: $(SOURCE_DIR)/bsd/security/audit/audit_syscalls.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_4B})
-include audit_worker.d
audit_worker.o: $(SOURCE_DIR)/bsd/security/audit/audit_worker.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/security/audit/${C_RULE_4B})
-include pthread_shims.d
pthread_shims.o: $(SOURCE_DIR)/bsd/pthread/pthread_shims.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/pthread/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/pthread/${C_RULE_4B})
-include pthread_priority.d
pthread_priority.o: $(SOURCE_DIR)/bsd/pthread/pthread_priority.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/pthread/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/pthread/${C_RULE_4B})
-include pthread_workqueue.d
pthread_workqueue.o: $(SOURCE_DIR)/bsd/pthread/pthread_workqueue.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/pthread/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/pthread/${C_RULE_4B})
-include bsd_init.d
bsd_init.o: $(SOURCE_DIR)/bsd/kern/bsd_init.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include init_sysent.d
init_sysent.o: init_sysent.c
	${C_RULE_0}
	${C_RULE_1A}${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}${C_RULE_4B})
-include kdebug.d
kdebug.o: $(SOURCE_DIR)/bsd/kern/kdebug.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_acct.d
kern_acct.o: $(SOURCE_DIR)/bsd/kern/kern_acct.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_aio.d
kern_aio.o: $(SOURCE_DIR)/bsd/kern/kern_aio.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_authorization.d
kern_authorization.o: $(SOURCE_DIR)/bsd/kern/kern_authorization.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_backtrace.d
kern_backtrace.o: $(SOURCE_DIR)/bsd/kern/kern_backtrace.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_clock.d
kern_clock.o: $(SOURCE_DIR)/bsd/kern/kern_clock.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_core.d
kern_core.o: $(SOURCE_DIR)/bsd/kern/kern_core.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_credential.d
kern_credential.o: $(SOURCE_DIR)/bsd/kern/kern_credential.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_cs.d
kern_cs.o: $(SOURCE_DIR)/bsd/kern/kern_cs.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_csr.d
kern_csr.o: $(SOURCE_DIR)/bsd/kern/kern_csr.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_symfile.d
kern_symfile.o: $(SOURCE_DIR)/bsd/kern/kern_symfile.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_descrip.d
kern_descrip.o: $(SOURCE_DIR)/bsd/kern/kern_descrip.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_guarded.d
kern_guarded.o: $(SOURCE_DIR)/bsd/kern/kern_guarded.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_event.d
kern_event.o: $(SOURCE_DIR)/bsd/kern/kern_event.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_control.d
kern_control.o: $(SOURCE_DIR)/bsd/kern/kern_control.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_exec.d
kern_exec.o: $(SOURCE_DIR)/bsd/kern/kern_exec.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_exit.d
kern_exit.o: $(SOURCE_DIR)/bsd/kern/kern_exit.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_ktrace.d
kern_ktrace.o: $(SOURCE_DIR)/bsd/kern/kern_ktrace.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_lockf.d
kern_lockf.o: $(SOURCE_DIR)/bsd/kern/kern_lockf.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_fork.d
kern_fork.o: $(SOURCE_DIR)/bsd/kern/kern_fork.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_asl.d
kern_asl.o: $(SOURCE_DIR)/bsd/kern/kern_asl.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_malloc.d
kern_malloc.o: $(SOURCE_DIR)/bsd/kern/kern_malloc.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_mman.d
kern_mman.o: $(SOURCE_DIR)/bsd/kern/kern_mman.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_persona.d
kern_persona.o: $(SOURCE_DIR)/bsd/kern/kern_persona.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_physio.d
kern_physio.o: $(SOURCE_DIR)/bsd/kern/kern_physio.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_priv.d
kern_priv.o: $(SOURCE_DIR)/bsd/kern/kern_priv.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_proc.d
kern_proc.o: $(SOURCE_DIR)/bsd/kern/kern_proc.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_prot.d
kern_prot.o: $(SOURCE_DIR)/bsd/kern/kern_prot.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_resource.d
kern_resource.o: $(SOURCE_DIR)/bsd/kern/kern_resource.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_shutdown.d
kern_shutdown.o: $(SOURCE_DIR)/bsd/kern/kern_shutdown.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_sig.d
kern_sig.o: $(SOURCE_DIR)/bsd/kern/kern_sig.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_subr.d
kern_subr.o: $(SOURCE_DIR)/bsd/kern/kern_subr.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_synch.d
kern_synch.o: $(SOURCE_DIR)/bsd/kern/kern_synch.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_sysctl.d
kern_sysctl.o: $(SOURCE_DIR)/bsd/kern/kern_sysctl.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_newsysctl.d
kern_newsysctl.o: $(SOURCE_DIR)/bsd/kern/kern_newsysctl.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_memorystatus.d
kern_memorystatus.o: $(SOURCE_DIR)/bsd/kern/kern_memorystatus.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_memorystatus_freeze.d
kern_memorystatus_freeze.o: $(SOURCE_DIR)/bsd/kern/kern_memorystatus_freeze.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_memorystatus_notify.d
kern_memorystatus_notify.o: $(SOURCE_DIR)/bsd/kern/kern_memorystatus_notify.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_mib.d
kern_mib.o: $(SOURCE_DIR)/bsd/kern/kern_mib.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kpi_mbuf.d
kpi_mbuf.o: $(SOURCE_DIR)/bsd/kern/kpi_mbuf.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_sfi.d
kern_sfi.o: $(SOURCE_DIR)/bsd/kern/kern_sfi.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_time.d
kern_time.o: $(SOURCE_DIR)/bsd/kern/kern_time.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_xxx.d
kern_xxx.o: $(SOURCE_DIR)/bsd/kern/kern_xxx.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include mach_process.d
mach_process.o: $(SOURCE_DIR)/bsd/kern/mach_process.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include mcache.d
mcache.o: $(SOURCE_DIR)/bsd/kern/mcache.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include stackshot.d
stackshot.o: $(SOURCE_DIR)/bsd/kern/stackshot.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include subr_log.d
subr_log.o: $(SOURCE_DIR)/bsd/kern/subr_log.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include subr_prf.d
subr_prf.o: $(SOURCE_DIR)/bsd/kern/subr_prf.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include subr_sbuf.d
subr_sbuf.o: $(SOURCE_DIR)/bsd/kern/subr_sbuf.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include subr_xxx.d
subr_xxx.o: $(SOURCE_DIR)/bsd/kern/subr_xxx.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include sys_eventlink.d
sys_eventlink.o: $(SOURCE_DIR)/bsd/kern/sys_eventlink.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include sys_generic.d
sys_generic.o: $(SOURCE_DIR)/bsd/kern/sys_generic.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include sys_pipe.d
sys_pipe.o: $(SOURCE_DIR)/bsd/kern/sys_pipe.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include sys_socket.d
sys_socket.o: $(SOURCE_DIR)/bsd/kern/sys_socket.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include sys_domain.d
sys_domain.o: $(SOURCE_DIR)/bsd/kern/sys_domain.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include sys_coalition.d
sys_coalition.o: $(SOURCE_DIR)/bsd/kern/sys_coalition.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include sys_persona.d
sys_persona.o: $(SOURCE_DIR)/bsd/kern/sys_persona.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include sys_ulock.d
sys_ulock.o: $(SOURCE_DIR)/bsd/kern/sys_ulock.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include sys_work_interval.d
sys_work_interval.o: $(SOURCE_DIR)/bsd/kern/sys_work_interval.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include syscalls.d
syscalls.o: syscalls.c
	${C_RULE_0}
	${C_RULE_1A}${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}${C_RULE_4B})
-include tty.d
tty.o: $(SOURCE_DIR)/bsd/kern/tty.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include tty_compat.d
tty_compat.o: $(SOURCE_DIR)/bsd/kern/tty_compat.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include tty_conf.d
tty_conf.o: $(SOURCE_DIR)/bsd/kern/tty_conf.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include tty_dev.d
tty_dev.o: $(SOURCE_DIR)/bsd/kern/tty_dev.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include tty_ptmx.d
tty_ptmx.o: $(SOURCE_DIR)/bsd/kern/tty_ptmx.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include tty_pty.d
tty_pty.o: $(SOURCE_DIR)/bsd/kern/tty_pty.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include tty_subr.d
tty_subr.o: $(SOURCE_DIR)/bsd/kern/tty_subr.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include tty_tty.d
tty_tty.o: $(SOURCE_DIR)/bsd/kern/tty_tty.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include ubc_subr.d
ubc_subr.o: $(SOURCE_DIR)/bsd/kern/ubc_subr.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include uipc_domain.d
uipc_domain.o: $(SOURCE_DIR)/bsd/kern/uipc_domain.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include uipc_mbuf.d
uipc_mbuf.o: $(SOURCE_DIR)/bsd/kern/uipc_mbuf.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include uipc_mbuf2.d
uipc_mbuf2.o: $(SOURCE_DIR)/bsd/kern/uipc_mbuf2.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include uipc_proto.d
uipc_proto.o: $(SOURCE_DIR)/bsd/kern/uipc_proto.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include uipc_socket.d
uipc_socket.o: $(SOURCE_DIR)/bsd/kern/uipc_socket.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include uipc_socket2.d
uipc_socket2.o: $(SOURCE_DIR)/bsd/kern/uipc_socket2.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include uipc_syscalls.d
uipc_syscalls.o: $(SOURCE_DIR)/bsd/kern/uipc_syscalls.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include uipc_usrreq.d
uipc_usrreq.o: $(SOURCE_DIR)/bsd/kern/uipc_usrreq.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include vsock_domain.d
vsock_domain.o: $(SOURCE_DIR)/bsd/kern/vsock_domain.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include sysv_ipc.d
sysv_ipc.o: $(SOURCE_DIR)/bsd/kern/sysv_ipc.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include sysv_shm.d
sysv_shm.o: $(SOURCE_DIR)/bsd/kern/sysv_shm.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include sysv_sem.d
sysv_sem.o: $(SOURCE_DIR)/bsd/kern/sysv_sem.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include sysv_msg.d
sysv_msg.o: $(SOURCE_DIR)/bsd/kern/sysv_msg.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include mach_fat.d
mach_fat.o: $(SOURCE_DIR)/bsd/kern/mach_fat.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include mach_loader.d
mach_loader.o: $(SOURCE_DIR)/bsd/kern/mach_loader.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include posix_sem.d
posix_sem.o: $(SOURCE_DIR)/bsd/kern/posix_sem.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include posix_shm.d
posix_shm.o: $(SOURCE_DIR)/bsd/kern/posix_shm.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include qsort.d
qsort.o: $(SOURCE_DIR)/bsd/kern/qsort.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kpi_socket.d
kpi_socket.o: $(SOURCE_DIR)/bsd/kern/kpi_socket.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kpi_socketfilter.d
kpi_socketfilter.o: $(SOURCE_DIR)/bsd/kern/kpi_socketfilter.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include proc_info.d
proc_info.o: $(SOURCE_DIR)/bsd/kern/proc_info.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include process_policy.d
process_policy.o: $(SOURCE_DIR)/bsd/kern/process_policy.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kern_overrides.d
kern_overrides.o: $(SOURCE_DIR)/bsd/kern/kern_overrides.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include socket_info.d
socket_info.o: $(SOURCE_DIR)/bsd/kern/socket_info.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include subr_eventhandler.d
subr_eventhandler.o: $(SOURCE_DIR)/bsd/kern/subr_eventhandler.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include sys_reason.d
sys_reason.o: $(SOURCE_DIR)/bsd/kern/sys_reason.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include vnode_pager.d
vnode_pager.o: $(SOURCE_DIR)/bsd/vm/vnode_pager.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/vm/${C_RULE_4B})
-include vm_unix.d
vm_unix.o: $(SOURCE_DIR)/bsd/vm/vm_unix.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/vm/${C_RULE_4B})
-include dp_backing_file.d
dp_backing_file.o: $(SOURCE_DIR)/bsd/vm/dp_backing_file.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/vm/${C_RULE_4B})
-include vm_compressor_backing_file.d
vm_compressor_backing_file.o: $(SOURCE_DIR)/bsd/vm/vm_compressor_backing_file.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/vm/${C_RULE_4B})
-include kern_ntptime.d
kern_ntptime.o: $(SOURCE_DIR)/bsd/kern/kern_ntptime.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include ux_exception.d
ux_exception.o: $(SOURCE_DIR)/bsd/uxkern/ux_exception.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/uxkern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/uxkern/${C_RULE_4B})
-include param.d
param.o: $(SOURCE_DIR)/bsd/conf/param.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/conf/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/conf/${C_RULE_4B})
-include ioconf.d
ioconf.o: ioconf.c
	${C_RULE_0}
	${C_RULE_1A}${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}${C_RULE_4B})
-include imageboot.d
imageboot.o: $(SOURCE_DIR)/bsd/kern/imageboot.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include chunklist.d
chunklist.o: $(SOURCE_DIR)/bsd/kern/chunklist.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include kperfbsd.d
kperfbsd.o: $(SOURCE_DIR)/osfmk/kperf/kperfbsd.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kperf/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kperf/${C_RULE_4B})
-include kern_kpc.d
kern_kpc.o: $(SOURCE_DIR)/bsd/kern/kern_kpc.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include proc_uuid_policy.d
proc_uuid_policy.o: $(SOURCE_DIR)/bsd/kern/proc_uuid_policy.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include profile_runtime.d
profile_runtime.o: $(SOURCE_DIR)/bsd/pgo/profile_runtime.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/pgo/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/pgo/${C_RULE_4B})
-include profile_runtime_data.d
profile_runtime_data.o: $(SOURCE_DIR)/bsd/pgo/profile_runtime_data.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/pgo/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/pgo/${C_RULE_4B})
-include null_subr.d
null_subr.o: $(SOURCE_DIR)/bsd/miscfs/nullfs/null_subr.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/miscfs/nullfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/miscfs/nullfs/${C_RULE_4B})
-include null_vfsops.d
null_vfsops.o: $(SOURCE_DIR)/bsd/miscfs/nullfs/null_vfsops.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/miscfs/nullfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/miscfs/nullfs/${C_RULE_4B})
-include null_vnops.d
null_vnops.o: $(SOURCE_DIR)/bsd/miscfs/nullfs/null_vnops.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/miscfs/nullfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/miscfs/nullfs/${C_RULE_4B})
-include bind_subr.d
bind_subr.o: $(SOURCE_DIR)/bsd/miscfs/bindfs/bind_subr.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/miscfs/bindfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/miscfs/bindfs/${C_RULE_4B})
-include bind_vfsops.d
bind_vfsops.o: $(SOURCE_DIR)/bsd/miscfs/bindfs/bind_vfsops.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/miscfs/bindfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/miscfs/bindfs/${C_RULE_4B})
-include bind_vnops.d
bind_vnops.o: $(SOURCE_DIR)/bsd/miscfs/bindfs/bind_vnops.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/miscfs/bindfs/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/miscfs/bindfs/${C_RULE_4B})
-include bsd_tests.d
bsd_tests.o: $(SOURCE_DIR)/bsd/tests/bsd_tests.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/tests/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/tests/${C_RULE_4B})
-include copyio_tests.d
copyio_tests.o: $(SOURCE_DIR)/bsd/tests/copyio_tests.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/tests/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/tests/${C_RULE_4B})
-include pmap_test_sysctl.d
pmap_test_sysctl.o: $(SOURCE_DIR)/bsd/tests/pmap_test_sysctl.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/tests/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/tests/${C_RULE_4B})
-include ptrauth_data_tests_sysctl.d
ptrauth_data_tests_sysctl.o: $(SOURCE_DIR)/bsd/tests/ptrauth_data_tests_sysctl.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/tests/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/tests/${C_RULE_4B})
-include skywalk_stubs.d
skywalk_stubs.o: $(SOURCE_DIR)/bsd/net/skywalk_stubs.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/net/${C_RULE_4B})
-include conf.d
conf.o: $(SOURCE_DIR)/bsd/dev/i386/conf.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_4B})
-include cons.d
cons.o: $(SOURCE_DIR)/bsd/dev/i386/cons.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_4B})
-include km.d
km.o: $(SOURCE_DIR)/bsd/dev/i386/km.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_4B})
-include kern_machdep.d
kern_machdep.o: $(SOURCE_DIR)/bsd/dev/i386/kern_machdep.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_4B})
-include stubs.d
stubs.o: $(SOURCE_DIR)/bsd/dev/i386/stubs.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_4B})
-include systemcalls.d
systemcalls.o: $(SOURCE_DIR)/bsd/dev/i386/systemcalls.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_4B})
-include sysctl.d
sysctl.o: $(SOURCE_DIR)/bsd/dev/i386/sysctl.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_4B})
-include unix_signal.d
unix_signal.o: $(SOURCE_DIR)/bsd/dev/i386/unix_signal.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_4B})
-include dtrace_isa.d
dtrace_isa.o: $(SOURCE_DIR)/bsd/dev/i386/dtrace_isa.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_4B})
-include dtrace_subr_x86.d
dtrace_subr_x86.o: $(SOURCE_DIR)/bsd/dev/i386/dtrace_subr_x86.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_4B})
-include fbt_x86.d
fbt_x86.o: $(SOURCE_DIR)/bsd/dev/i386/fbt_x86.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_4B})
-include sdt_x86.d
sdt_x86.o: $(SOURCE_DIR)/bsd/dev/i386/sdt_x86.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_4B})
-include fasttrap_isa.d
fasttrap_isa.o: $(SOURCE_DIR)/bsd/dev/i386/fasttrap_isa.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_4B})
-include instr_size.d
instr_size.o: $(SOURCE_DIR)/bsd/dev/i386/instr_size.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_4B})
-include dis_tables.d
dis_tables.o: $(SOURCE_DIR)/bsd/dev/i386/dis_tables.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/dev/i386/${C_RULE_4B})
-include policy_check.d
policy_check.o: $(SOURCE_DIR)/bsd/kern/policy_check.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})
-include bsd_stubs.d
bsd_stubs.o: $(SOURCE_DIR)/bsd/kern/bsd_stubs.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/bsd/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/bsd/kern/${C_RULE_4B})

include $(MakeInc_rule)
include $(MakeInc_dir)
