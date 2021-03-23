SOURCE_DIR=/Users/nedwill/dev/sockfuzzer/third_party/xnu
export CONFIG_DEFINES = -DINET -DMACH -DMACH_COMPAT -DMACH_FASTLINK -DNO_DIRECT_RPC -DVLAN -DSIXLOWPAN -DBOND -DIF_FAKE -DIF_HEADLESS -DAH_ALL_CRYPTO -DPF -DPFLOG -DDUMMYNET -DTRAFFIC_MGT -DMULTICAST -DICMP_BANDLIM -DIFNET_INPUT_SANITY_CHK -DMULTIPATH -DMPTCP -DSYSV_SEM -DSYSV_MSG -DSYSV_SHM -DPSYNCH -DFLOW_DIVERT -DNECP -DCONTENT_FILTER -DPACKET_MANGLER -DSIXLOWPAN -DOLD_SEMWAIT_SIGNAL -DSOCKETS -DSENDFILE -DNETWORKING -DCONFIG_FSE -DCONFIG_IMAGEBOOT -DCONFIG_MBUF_JUMBO -DCONFIG_IMAGEBOOT_CHUNKLIST -DCONFIG_WORKQUEUE -DCONFIG_WORKLOOP_DEBUG -DFIFO -DFDESC -DDEVFS -DNULLFS -DBINDFS -DFS_COMPRESSION -DCONFIG_DEV_KMEM -DQUOTA -DNAMEDSTREAMS -DCONFIG_APPLEDOUBLE -DCONFIG_VOLFS -DCONFIG_IMGSRC_ACCESS -DCONFIG_TRIGGERS -DCONFIG_EXT_RESOLVER -DCONFIG_SEARCHFS -DCONFIG_MNT_SUID -DCONFIG_MNT_ROOTSNAP -DCONFIG_ROSV_STARTUP -DCONFIG_FIRMLINKS -DCONFIG_MOUNT_VM -DCONFIG_MOUNT_PREBOOTRECOVERY -DCONFIG_DATALESS_FILES -DCONFIG_BASESYSTEMROOT -DNFSCLIENT -DNFSSERVER -DCONFIG_NFS_GSS -DCONFIG_NFS4 -DCONFIG_NETBOOT -DIPSEC -DIPSEC_ESP -DCRYPTO_SHA2 -DCONFIG_IMG4 -DZLIB -DIF_BRIDGE -DCONFIG_KN_HASHSIZE="64" -DCONFIG_VNODES="263168" -DCONFIG_NC_HASH="4096" -DCONFIG_VFS_NAMES="4096" -DCONFIG_MAX_CLUSTERS="8" -DCONFIG_MIN_NBUF="256" -DCONFIG_MIN_NIOBUF="128" -DCONFIG_NMBCLUSTERS="((1024 * 512) / MCLBYTES)" -DCONFIG_TCBHASHSIZE="4096" -DCONFIG_ICMP_BANDLIM="250" -DCONFIG_AIO_MAX="90" -DCONFIG_AIO_PROCESS_MAX="16" -DCONFIG_AIO_THREAD_COUNT="4" -DCONFIG_MAXVIFS="32" -DCONFIG_MFCTBLSIZ="256" -DCONFIG_MSG_BSIZE_REL="16384" -DCONFIG_MSG_BSIZE_DEV="131072" -DCONFIG_MSG_BSIZE="CONFIG_MSG_BSIZE_DEV" -DCONFIG_IPC_TABLE_ENTRIES_STEPS="256" -DCONFIG_VSPRINTF -DCONFIG_DYNAMIC_CODE_SIGNING -DCONFIG_CODE_DECRYPTION -DCONFIG_PROTECT -DCONFIG_KEYPAGE_WP -DCONFIG_MEMORYSTATUS -DCONFIG_DIRTYSTATUS_TRACKING -DCONFIG_LTABLE_STATS -DCONFIG_LTABLE_DEBUG -DCONFIG_WAITQ_STATS -DCONFIG_WAITQ_DEBUG -DCONFIG_PHYS_WRITE_ACCT -DVM_PRESSURE_EVENTS -DCONFIG_BACKGROUND_QUEUE -DCONFIG_LEDGER_INTERVAL_MAX -DCONFIG_IOSCHED -DIMPORTANCE_TRACE -DCONFIG_TELEMETRY -DCONFIG_PROC_UUID_POLICY -DCONFIG_COREDUMP -DCONFIG_VNGUARD -DIOKITCPP -DIOKITSTATS -DIOTRACKING -DCONFIG_SLEEP -DCONFIG_MAX_THREADS="500" -DLIBKERNCPP -DCONFIG_BLOCKS -DCONFIG_KEC_FIPS -DCONFIG_KEXT_BASEMENT -DCONFIG_PERSONAS -DCONFIG_MACF -DCONFIG_MACF_SOCKET_SUBSET -DCONFIG_AUDIT -DCONFIG_ARCADE -DCONFIG_SETUID -DCONFIG_KAS_INFO -DCONFIG_ZALLOC_SEQUESTER -DCONFIG_ZCACHE -DCONFIG_ZLEAKS -DCONFIG_TASK_ZONE_INFO -DLOCK_STATS -DKPERF -DKPC -DPGO -DMACH_BSD -DIOKIT -DCONFIG_THREAD_MAX="2560" -DCONFIG_TASK_MAX="1024" -DCONFIG_ZONE_MAP_MIN="120586240" -DCONFIG_ZLEAK_ALLOCATION_MAP_NUM="16384" -DCONFIG_ZLEAK_TRACE_MAP_NUM="8192" -DCONFIG_SCHED_TRADITIONAL -DCONFIG_SCHED_PROTO -DCONFIG_SCHED_GRRR -DCONFIG_SCHED_GRRR_CORE -DCONFIG_SCHED_MULTIQ -DCONFIG_SCHED_TIMESHARE_CORE -DCONFIG_SCHED_SFI -DCONFIG_GZALLOC -DCONFIG_KDP_INTERACTIVE_DEBUGGING -DCONFIG_TASKWATCH -DCONFIG_XNUPOST -DCONFIG_ATM -DCONFIG_COALITIONS -DCONFIG_SYSDIAGNOSE -DCONFIG_CSR -DSERIAL_CONSOLE -DVIDEO_CONSOLE -DCONFIG_REQUIRES_U32_MUNGING -DCOPYOUT_SHIM -DCONFIG_MACH_BRIDGE_SEND_TIME -DCONFIG_32BIT_TELEMETRY -DCONFIG_DELAY_IDLE_SLEEP -DCONFIG_PROC_UDATA_STORAGE -DPAL_I386 -DCONFIG_MCA -DCONFIG_VMX -DCONFIG_MTRR -DCONFIG_MACF_LAZY_VNODE_LABELS -DHYPERVISOR -DCONFIG_MACH_APPROXIMATE_TIME
OSFMK_MACHINE=x86_64
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
CFLAGS+= -include meta_features.h -DMACH_KERNEL_PRIVATE -DMACH_KERNEL
SFLAGS+= -include meta_features.h

ifeq ($(KSANCOV),1)
# Don't instrument functions called by the ksancov runtime. SanitizeCoverage does
# not support blacklists, so exclude the whole file.
machine_routines.o_CFLAGS_RM = $(KSANCOV_CFLAGS)
machine_routines_common.o_CFLAGS_RM = $(KSANCOV_CFLAGS)
pcb_native.o_CFLAGS_RM = $(KSANCOV_CFLAGS)
endif

#
# XXX: INCFLAGS to include libsa prototypes
#
INCFLAGS_MAKEFILE= -I$(SOURCE)libsa

#
# Directories for mig generated files
#
COMP_SUBDIRS = \
	atm \
	default_pager \
	device \
	mach \
	UserNotification \
	gssd \
	kextd \
	lockd

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

OBJS=gssd_mach.o lockd_mach.o kextd_mach.o UNDRequest.o UNDReplyServer.o \
	KUNCUserNotifications.o kdp.o kern_stackshot.o kdp_udp.o \
	kdp_core.o processor_core.o kdp_serial.o ipc_entry.o \
	ipc_eventlink.o ipc_hash.o ipc_importance.o ipc_init.o \
	ipc_kmsg.o ipc_mqueue.o ipc_notify.o ipc_object.o ipc_port.o \
	ipc_pset.o ipc_right.o ipc_space.o ipc_table.o ipc_voucher.o \
	mach_debug.o mach_kernelrpc.o mach_msg.o mach_port.o affinity.o \
	arcade.o ast.o audit_sessionport.o backtrace.o btlog.o \
	build_config.o clock.o clock_oldops.o coalition.o counters.o \
	debug.o energy_perf.o exception.o extmod_statistics.o host.o \
	host_notify.o ipc_clock.o ipc_host.o ipc_kobject.o ipc_mig.o \
	ipc_misc.o ipc_sync.o ipc_tt.o kalloc.o \
	ktrace_background_notify.o ledger.o locks.o tlock.o ltable.o \
	mach_node.o machine.o mk_sp.o mk_timer.o mpsc_queue.o \
	page_decrypt.o printf.o priority.o processor.o restartable.o \
	sched_average.o sched_amp.o sched_amp_common.o sched_dualq.o \
	sched_prim.o sched_proto.o sched_traditional.o sched_grrr.o \
	sched_multiq.o sfi.o stack.o startup.o sync_lock.o sync_sema.o \
	syscall_emulation.o syscall_subr.o syscall_sw.o sysdiagnose.o \
	task.o task_policy.o task_swap.o test_lock.o test_mpsc_queue.o \
	thread.o thread_act.o thread_call.o thread_group.o \
	thread_policy.o timer.o timer_call.o turnstile.o ux_handler.o \
	waitq.o work_interval.o zalloc.o zcache.o gzalloc.o bsd_kern.o \
	hibernate.o remote_time.o memset_s.o copyout_shim.o suid_cred.o \
	clock_server.o clock_priv_server.o clock_reply_user.o exc_user.o \
	exc_server.o mach_eventlink_server.o host_priv_server.o \
	host_security_server.o ktrace_background_user.o \
	lock_set_server.o mach_exc_user.o mach_exc_server.o \
	mach_host_server.o mach_notify_user.o mach_port_server.o \
	mach_vm_server.o mach_voucher_server.o \
	mach_voucher_attr_control_server.o memory_entry_server.o \
	memory_object_control_server.o resource_notify_user.o \
	restartable_server.o upl_server.o audit_triggers_user.o \
	task_access_user.o corpse.o kern_cdata.o kernel_tests.o ktest.o \
	ktest_accessor.o ktest_emit.o ktest_global.o pmap_tests.o \
	ptrauth_data_tests.o bitmap_test.o test_thread_call.o \
	vfp_state_test.o telemetry_notification_user.o bank.o atm.o \
	atm_notification_user.o ipc_pthread_priority.o \
	coalition_notification_user.o sysdiagnose_notification_user.o \
	vfs_nspace_user.o fairplayd_notification_user.o \
	arcade_upcall_user.o arcade_register_server.o processor_server.o \
	processor_set_server.o task_server.o thread_act_server.o \
	vm32_map_server.o bsd_vm.o vm_compressor.o vm_compressor_pager.o \
	vm_compressor_backing_store.o vm_compressor_algorithms.o lz4.o \
	device_vm.o memory_object.o vm_debug.o vm_fault.o vm_init.o \
	vm_kern.o vm_map.o vm_map_store.o vm_map_store_ll.o \
	vm_map_store_rb.o vm_object.o vm_pageout.o vm_purgeable.o \
	vm_resident.o vm_shared_region.o vm_shared_region_pager.o \
	vm_swapfile_pager.o vm_tests.o vm_user.o vm32_user.o iokit_rpc.o \
	device_server.o device_init.o kext_alloc.o kmod.o subrs.o \
	kperf.o action.o callstack.o pet.o thread_samplers.o \
	task_samplers.o meminfo.o kptimer.o kperf_kpc.o kdebug_trigger.o \
	lazy.o kpc_thread.o kpc_common.o serial_general.o \
	serial_console.o video_scroll.o video_console.o telemetry.o \
	cc_clear.o cc_cmp_safe.o cc_abort.o ccdrbg_nisthmac.o \
	ccdigest_init.o ccdigest_update.o cchmac.o cchmac_init.o \
	cchmac_update.o cchmac_final.o ccdigest_final_64be.o \
	ccsha256_di.o ccsha256_initial_state.o ccsha256_K.o \
	ccsha256_ltc_compress.o ccsha256_ltc_di.o prng_random.o \
	entropy.o vm_apple_protect.o pmap.o pmap_x86_common.o \
	pmap_common.o pmap_pcid.o pal_routines.o pal_routines_asm.o \
	bsd_i386.o bsd_i386_native.o machdep_call.o boot_pt.o mp_desc.o \
	gdt.o start.o bcopy.o bzero.o WKdmDecompress_new.o \
	WKdmCompress_new.o WKdmData_new.o lz4_decode_x86_64.o cpu.o \
	cpuid.o cpu_threads.o cpu_topology.o i386_timer.o fpu.o \
	fp_simd.o i386_lock.o i386_init.o i386_vm_init.o io_map.o ktss.o \
	ldt.o loose_ends.o copyio.o locks_i386.o locks_i386_opt.o \
	locore.o lowmem_vectors.o cswitch.o machine_routines.o \
	machine_routines_asm.o machine_check.o machine_task.o pcb.o \
	pcb_native.o phys.o rtclock.o rtclock_native.o trap.o \
	trap_native.o user_ldt.o Diagnostics.o pmCPU.o tsc.o commpage.o \
	commpage_asm.o fifo_queues.o model_dep.o lapic.o lapic_native.o \
	mp.o mp_native.o acpi.o mtrr.o kdp_machdep.o kdp_vm.o \
	kdp_x86_common.o hibernate_i386.o hibernate_restore.o ucode.o \
	vmx_cpu.o vmx_shims.o hv_support_kext.o kpc_x86.o idt64.o \
	panic_hooks.o panic_notify.o machine_remote_time.o 

CFILES=\
	./gssd/gssd_mach.c \
	./lockd/lockd_mach.c \
	./kextd/kextd_mach.c \
	./UserNotification/UNDRequest.c \
	./UserNotification/UNDReplyServer.c \
	$(SOURCE_DIR)/osfmk/UserNotification/KUNCUserNotifications.c \
	$(SOURCE_DIR)/osfmk/kdp/kdp.c \
	$(SOURCE_DIR)/osfmk/kern/kern_stackshot.c \
	$(SOURCE_DIR)/osfmk/kdp/kdp_udp.c \
	$(SOURCE_DIR)/osfmk/kdp/kdp_core.c \
	$(SOURCE_DIR)/osfmk/kdp/processor_core.c \
	$(SOURCE_DIR)/osfmk/kdp/kdp_serial.c \
	$(SOURCE_DIR)/osfmk/ipc/ipc_entry.c \
	$(SOURCE_DIR)/osfmk/ipc/ipc_eventlink.c \
	$(SOURCE_DIR)/osfmk/ipc/ipc_hash.c \
	$(SOURCE_DIR)/osfmk/ipc/ipc_importance.c \
	$(SOURCE_DIR)/osfmk/ipc/ipc_init.c \
	$(SOURCE_DIR)/osfmk/ipc/ipc_kmsg.c \
	$(SOURCE_DIR)/osfmk/ipc/ipc_mqueue.c \
	$(SOURCE_DIR)/osfmk/ipc/ipc_notify.c \
	$(SOURCE_DIR)/osfmk/ipc/ipc_object.c \
	$(SOURCE_DIR)/osfmk/ipc/ipc_port.c \
	$(SOURCE_DIR)/osfmk/ipc/ipc_pset.c \
	$(SOURCE_DIR)/osfmk/ipc/ipc_right.c \
	$(SOURCE_DIR)/osfmk/ipc/ipc_space.c \
	$(SOURCE_DIR)/osfmk/ipc/ipc_table.c \
	$(SOURCE_DIR)/osfmk/ipc/ipc_voucher.c \
	$(SOURCE_DIR)/osfmk/ipc/mach_debug.c \
	$(SOURCE_DIR)/osfmk/ipc/mach_kernelrpc.c \
	$(SOURCE_DIR)/osfmk/ipc/mach_msg.c \
	$(SOURCE_DIR)/osfmk/ipc/mach_port.c \
	$(SOURCE_DIR)/osfmk/kern/affinity.c \
	$(SOURCE_DIR)/osfmk/kern/arcade.c \
	$(SOURCE_DIR)/osfmk/kern/ast.c \
	$(SOURCE_DIR)/osfmk/kern/audit_sessionport.c \
	$(SOURCE_DIR)/osfmk/kern/backtrace.c \
	$(SOURCE_DIR)/osfmk/kern/btlog.c \
	$(SOURCE_DIR)/osfmk/kern/build_config.c \
	$(SOURCE_DIR)/osfmk/kern/clock.c \
	$(SOURCE_DIR)/osfmk/kern/clock_oldops.c \
	$(SOURCE_DIR)/osfmk/kern/coalition.c \
	$(SOURCE_DIR)/osfmk/kern/counters.c \
	$(SOURCE_DIR)/osfmk/kern/debug.c \
	$(SOURCE_DIR)/osfmk/kern/energy_perf.c \
	$(SOURCE_DIR)/osfmk/kern/exception.c \
	$(SOURCE_DIR)/osfmk/kern/extmod_statistics.c \
	$(SOURCE_DIR)/osfmk/kern/host.c \
	$(SOURCE_DIR)/osfmk/kern/host_notify.c \
	$(SOURCE_DIR)/osfmk/kern/ipc_clock.c \
	$(SOURCE_DIR)/osfmk/kern/ipc_host.c \
	$(SOURCE_DIR)/osfmk/kern/ipc_kobject.c \
	$(SOURCE_DIR)/osfmk/kern/ipc_mig.c \
	$(SOURCE_DIR)/osfmk/kern/ipc_misc.c \
	$(SOURCE_DIR)/osfmk/kern/ipc_sync.c \
	$(SOURCE_DIR)/osfmk/kern/ipc_tt.c \
	$(SOURCE_DIR)/osfmk/kern/kalloc.c \
	$(SOURCE_DIR)/osfmk/kern/ktrace_background_notify.c \
	$(SOURCE_DIR)/osfmk/kern/ledger.c \
	$(SOURCE_DIR)/osfmk/kern/locks.c \
	$(SOURCE_DIR)/osfmk/kern/tlock.c \
	$(SOURCE_DIR)/osfmk/kern/ltable.c \
	$(SOURCE_DIR)/osfmk/kern/mach_node.c \
	$(SOURCE_DIR)/osfmk/kern/machine.c \
	$(SOURCE_DIR)/osfmk/kern/mk_sp.c \
	$(SOURCE_DIR)/osfmk/kern/mk_timer.c \
	$(SOURCE_DIR)/osfmk/kern/mpsc_queue.c \
	$(SOURCE_DIR)/osfmk/kern/page_decrypt.c \
	$(SOURCE_DIR)/osfmk/kern/printf.c \
	$(SOURCE_DIR)/osfmk/kern/priority.c \
	$(SOURCE_DIR)/osfmk/kern/processor.c \
	$(SOURCE_DIR)/osfmk/kern/restartable.c \
	$(SOURCE_DIR)/osfmk/kern/sched_average.c \
	$(SOURCE_DIR)/osfmk/kern/sched_amp.c \
	$(SOURCE_DIR)/osfmk/kern/sched_amp_common.c \
	$(SOURCE_DIR)/osfmk/kern/sched_dualq.c \
	$(SOURCE_DIR)/osfmk/kern/sched_prim.c \
	$(SOURCE_DIR)/osfmk/kern/sched_proto.c \
	$(SOURCE_DIR)/osfmk/kern/sched_traditional.c \
	$(SOURCE_DIR)/osfmk/kern/sched_grrr.c \
	$(SOURCE_DIR)/osfmk/kern/sched_multiq.c \
	$(SOURCE_DIR)/osfmk/kern/sfi.c \
	$(SOURCE_DIR)/osfmk/kern/stack.c \
	$(SOURCE_DIR)/osfmk/kern/startup.c \
	$(SOURCE_DIR)/osfmk/kern/sync_lock.c \
	$(SOURCE_DIR)/osfmk/kern/sync_sema.c \
	$(SOURCE_DIR)/osfmk/kern/syscall_emulation.c \
	$(SOURCE_DIR)/osfmk/kern/syscall_subr.c \
	$(SOURCE_DIR)/osfmk/kern/syscall_sw.c \
	$(SOURCE_DIR)/osfmk/kern/sysdiagnose.c \
	$(SOURCE_DIR)/osfmk/kern/task.c \
	$(SOURCE_DIR)/osfmk/kern/task_policy.c \
	$(SOURCE_DIR)/osfmk/kern/task_swap.c \
	$(SOURCE_DIR)/osfmk/kern/test_lock.c \
	$(SOURCE_DIR)/osfmk/kern/test_mpsc_queue.c \
	$(SOURCE_DIR)/osfmk/kern/thread.c \
	$(SOURCE_DIR)/osfmk/kern/thread_act.c \
	$(SOURCE_DIR)/osfmk/kern/thread_call.c \
	$(SOURCE_DIR)/osfmk/kern/thread_group.c \
	$(SOURCE_DIR)/osfmk/kern/thread_policy.c \
	$(SOURCE_DIR)/osfmk/kern/timer.c \
	$(SOURCE_DIR)/osfmk/kern/timer_call.c \
	$(SOURCE_DIR)/osfmk/kern/turnstile.c \
	$(SOURCE_DIR)/osfmk/kern/ux_handler.c \
	$(SOURCE_DIR)/osfmk/kern/waitq.c \
	$(SOURCE_DIR)/osfmk/kern/work_interval.c \
	$(SOURCE_DIR)/osfmk/kern/zalloc.c \
	$(SOURCE_DIR)/osfmk/kern/zcache.c \
	$(SOURCE_DIR)/osfmk/kern/gzalloc.c \
	$(SOURCE_DIR)/osfmk/kern/bsd_kern.c \
	$(SOURCE_DIR)/osfmk/kern/hibernate.c \
	$(SOURCE_DIR)/osfmk/kern/remote_time.c \
	$(SOURCE_DIR)/osfmk/kern/memset_s.c \
	$(SOURCE_DIR)/osfmk/kern/copyout_shim.c \
	$(SOURCE_DIR)/osfmk/kern/suid_cred.c \
	./mach/clock_server.c \
	./mach/clock_priv_server.c \
	./mach/clock_reply_user.c \
	./mach/exc_user.c \
	./mach/exc_server.c \
	./mach/mach_eventlink_server.c \
	./mach/host_priv_server.c \
	./mach/host_security_server.c \
	./mach/ktrace_background_user.c \
	./mach/lock_set_server.c \
	./mach/mach_exc_user.c \
	./mach/mach_exc_server.c \
	./mach/mach_host_server.c \
	./mach/mach_notify_user.c \
	./mach/mach_port_server.c \
	./mach/mach_vm_server.c \
	./mach/mach_voucher_server.c \
	./mach/mach_voucher_attr_control_server.c \
	./mach/memory_entry_server.c \
	./mach/memory_object_control_server.c \
	./mach/resource_notify_user.c \
	./mach/restartable_server.c \
	./mach/upl_server.c \
	./mach/audit_triggers_user.c \
	./mach/task_access_user.c \
	$(SOURCE_DIR)/osfmk/corpses/corpse.c \
	$(SOURCE_DIR)/osfmk/kern/kern_cdata.c \
	$(SOURCE_DIR)/osfmk/tests/kernel_tests.c \
	$(SOURCE_DIR)/osfmk/tests/ktest.c \
	$(SOURCE_DIR)/osfmk/tests/ktest_accessor.c \
	$(SOURCE_DIR)/osfmk/tests/ktest_emit.c \
	$(SOURCE_DIR)/osfmk/tests/ktest_global.c \
	$(SOURCE_DIR)/osfmk/tests/pmap_tests.c \
	$(SOURCE_DIR)/osfmk/tests/ptrauth_data_tests.c \
	$(SOURCE_DIR)/osfmk/tests/bitmap_test.c \
	$(SOURCE_DIR)/osfmk/tests/test_thread_call.c \
	$(SOURCE_DIR)/osfmk/tests/vfp_state_test.c \
	./mach/telemetry_notification_user.c \
	$(SOURCE_DIR)/osfmk/bank/bank.c \
	$(SOURCE_DIR)/osfmk/atm/atm.c \
	./atm/atm_notification_user.c \
	$(SOURCE_DIR)/osfmk/voucher/ipc_pthread_priority.c \
	./mach/coalition_notification_user.c \
	./mach/sysdiagnose_notification_user.c \
	./mach/vfs_nspace_user.c \
	./mach/fairplayd_notification_user.c \
	./mach/arcade_upcall_user.c \
	./mach/arcade_register_server.c \
	./mach/processor_server.c \
	./mach/processor_set_server.c \
	./mach/task_server.c \
	./mach/thread_act_server.c \
	./mach/vm32_map_server.c \
	$(SOURCE_DIR)/osfmk/vm/bsd_vm.c \
	$(SOURCE_DIR)/osfmk/vm/vm_compressor.c \
	$(SOURCE_DIR)/osfmk/vm/vm_compressor_pager.c \
	$(SOURCE_DIR)/osfmk/vm/vm_compressor_backing_store.c \
	$(SOURCE_DIR)/osfmk/vm/vm_compressor_algorithms.c \
	$(SOURCE_DIR)/osfmk/vm/lz4.c \
	$(SOURCE_DIR)/osfmk/vm/device_vm.c \
	$(SOURCE_DIR)/osfmk/vm/memory_object.c \
	$(SOURCE_DIR)/osfmk/vm/vm_debug.c \
	$(SOURCE_DIR)/osfmk/vm/vm_fault.c \
	$(SOURCE_DIR)/osfmk/vm/vm_init.c \
	$(SOURCE_DIR)/osfmk/vm/vm_kern.c \
	$(SOURCE_DIR)/osfmk/vm/vm_map.c \
	$(SOURCE_DIR)/osfmk/vm/vm_map_store.c \
	$(SOURCE_DIR)/osfmk/vm/vm_map_store_ll.c \
	$(SOURCE_DIR)/osfmk/vm/vm_map_store_rb.c \
	$(SOURCE_DIR)/osfmk/vm/vm_object.c \
	$(SOURCE_DIR)/osfmk/vm/vm_pageout.c \
	$(SOURCE_DIR)/osfmk/vm/vm_purgeable.c \
	$(SOURCE_DIR)/osfmk/vm/vm_resident.c \
	$(SOURCE_DIR)/osfmk/vm/vm_shared_region.c \
	$(SOURCE_DIR)/osfmk/vm/vm_shared_region_pager.c \
	$(SOURCE_DIR)/osfmk/vm/vm_swapfile_pager.c \
	$(SOURCE_DIR)/osfmk/vm/vm_tests.c \
	$(SOURCE_DIR)/osfmk/vm/vm_user.c \
	$(SOURCE_DIR)/osfmk/vm/vm32_user.c \
	$(SOURCE_DIR)/osfmk/device/iokit_rpc.c \
	./device/device_server.c \
	$(SOURCE_DIR)/osfmk/device/device_init.c \
	$(SOURCE_DIR)/osfmk/kern/kext_alloc.c \
	$(SOURCE_DIR)/osfmk/kern/kmod.c \
	$(SOURCE_DIR)/osfmk/device/subrs.c \
	$(SOURCE_DIR)/osfmk/kperf/kperf.c \
	$(SOURCE_DIR)/osfmk/kperf/action.c \
	$(SOURCE_DIR)/osfmk/kperf/callstack.c \
	$(SOURCE_DIR)/osfmk/kperf/pet.c \
	$(SOURCE_DIR)/osfmk/kperf/thread_samplers.c \
	$(SOURCE_DIR)/osfmk/kperf/task_samplers.c \
	$(SOURCE_DIR)/osfmk/kperf/meminfo.c \
	$(SOURCE_DIR)/osfmk/kperf/kptimer.c \
	$(SOURCE_DIR)/osfmk/kperf/kperf_kpc.c \
	$(SOURCE_DIR)/osfmk/kperf/kdebug_trigger.c \
	$(SOURCE_DIR)/osfmk/kperf/lazy.c \
	$(SOURCE_DIR)/osfmk/kern/kpc_thread.c \
	$(SOURCE_DIR)/osfmk/kern/kpc_common.c \
	$(SOURCE_DIR)/osfmk/console/serial_general.c \
	$(SOURCE_DIR)/osfmk/console/serial_console.c \
	$(SOURCE_DIR)/osfmk/console/video_scroll.c \
	$(SOURCE_DIR)/osfmk/console/video_console.c \
	$(SOURCE_DIR)/osfmk/kern/telemetry.c \
	$(SOURCE_DIR)/osfmk/corecrypto/cc_clear.c \
	$(SOURCE_DIR)/osfmk/corecrypto/cc_cmp_safe.c \
	$(SOURCE_DIR)/osfmk/corecrypto/cc_abort.c \
	$(SOURCE_DIR)/osfmk/corecrypto/ccdrbg_nisthmac.c \
	$(SOURCE_DIR)/osfmk/corecrypto/ccdigest_init.c \
	$(SOURCE_DIR)/osfmk/corecrypto/ccdigest_update.c \
	$(SOURCE_DIR)/osfmk/corecrypto/cchmac.c \
	$(SOURCE_DIR)/osfmk/corecrypto/cchmac_init.c \
	$(SOURCE_DIR)/osfmk/corecrypto/cchmac_update.c \
	$(SOURCE_DIR)/osfmk/corecrypto/cchmac_final.c \
	$(SOURCE_DIR)/osfmk/corecrypto/ccdigest_final_64be.c \
	$(SOURCE_DIR)/osfmk/corecrypto/ccsha256_di.c \
	$(SOURCE_DIR)/osfmk/corecrypto/ccsha256_initial_state.c \
	$(SOURCE_DIR)/osfmk/corecrypto/ccsha256_K.c \
	$(SOURCE_DIR)/osfmk/corecrypto/ccsha256_ltc_compress.c \
	$(SOURCE_DIR)/osfmk/corecrypto/ccsha256_ltc_di.c \
	$(SOURCE_DIR)/osfmk/prng/prng_random.c \
	$(SOURCE_DIR)/osfmk/prng/entropy.c \
	$(SOURCE_DIR)/osfmk/vm/vm_apple_protect.c \
	$(SOURCE_DIR)/osfmk/x86_64/pmap.c \
	$(SOURCE_DIR)/osfmk/i386/pmap_x86_common.c \
	$(SOURCE_DIR)/osfmk/i386/pmap_common.c \
	$(SOURCE_DIR)/osfmk/x86_64/pmap_pcid.c \
	$(SOURCE_DIR)/osfmk/i386/pal_routines.c \
	$(SOURCE_DIR)/osfmk/i386/bsd_i386.c \
	$(SOURCE_DIR)/osfmk/i386/bsd_i386_native.c \
	$(SOURCE_DIR)/osfmk/i386/machdep_call.c \
	$(SOURCE_DIR)/osfmk/x86_64/boot_pt.c \
	$(SOURCE_DIR)/osfmk/i386/mp_desc.c \
	$(SOURCE_DIR)/osfmk/i386/gdt.c \
	$(SOURCE_DIR)/osfmk/i386/cpu.c \
	$(SOURCE_DIR)/osfmk/i386/cpuid.c \
	$(SOURCE_DIR)/osfmk/i386/cpu_threads.c \
	$(SOURCE_DIR)/osfmk/i386/cpu_topology.c \
	$(SOURCE_DIR)/osfmk/i386/i386_timer.c \
	$(SOURCE_DIR)/osfmk/i386/fpu.c \
	$(SOURCE_DIR)/osfmk/i386/i386_init.c \
	$(SOURCE_DIR)/osfmk/i386/i386_vm_init.c \
	$(SOURCE_DIR)/osfmk/i386/io_map.c \
	$(SOURCE_DIR)/osfmk/i386/ktss.c \
	$(SOURCE_DIR)/osfmk/i386/ldt.c \
	$(SOURCE_DIR)/osfmk/x86_64/loose_ends.c \
	$(SOURCE_DIR)/osfmk/x86_64/copyio.c \
	$(SOURCE_DIR)/osfmk/i386/locks_i386.c \
	$(SOURCE_DIR)/osfmk/i386/locks_i386_opt.c \
	$(SOURCE_DIR)/osfmk/x86_64/lowmem_vectors.c \
	$(SOURCE_DIR)/osfmk/i386/machine_routines.c \
	$(SOURCE_DIR)/osfmk/i386/machine_check.c \
	$(SOURCE_DIR)/osfmk/i386/machine_task.c \
	$(SOURCE_DIR)/osfmk/i386/pcb.c \
	$(SOURCE_DIR)/osfmk/i386/pcb_native.c \
	$(SOURCE_DIR)/osfmk/i386/phys.c \
	$(SOURCE_DIR)/osfmk/i386/rtclock.c \
	$(SOURCE_DIR)/osfmk/i386/rtclock_native.c \
	$(SOURCE_DIR)/osfmk/i386/trap.c \
	$(SOURCE_DIR)/osfmk/i386/trap_native.c \
	$(SOURCE_DIR)/osfmk/i386/user_ldt.c \
	$(SOURCE_DIR)/osfmk/i386/Diagnostics.c \
	$(SOURCE_DIR)/osfmk/i386/pmCPU.c \
	$(SOURCE_DIR)/osfmk/i386/tsc.c \
	$(SOURCE_DIR)/osfmk/i386/commpage/commpage.c \
	$(SOURCE_DIR)/osfmk/i386/AT386/model_dep.c \
	$(SOURCE_DIR)/osfmk/i386/lapic.c \
	$(SOURCE_DIR)/osfmk/i386/lapic_native.c \
	$(SOURCE_DIR)/osfmk/i386/mp.c \
	$(SOURCE_DIR)/osfmk/i386/mp_native.c \
	$(SOURCE_DIR)/osfmk/i386/acpi.c \
	$(SOURCE_DIR)/osfmk/i386/mtrr.c \
	$(SOURCE_DIR)/osfmk/kdp/ml/x86_64/kdp_machdep.c \
	$(SOURCE_DIR)/osfmk/kdp/ml/x86_64/kdp_vm.c \
	$(SOURCE_DIR)/osfmk/kdp/ml/i386/kdp_x86_common.c \
	$(SOURCE_DIR)/osfmk/i386/hibernate_i386.c \
	$(SOURCE_DIR)/osfmk/i386/hibernate_restore.c \
	$(SOURCE_DIR)/osfmk/i386/ucode.c \
	$(SOURCE_DIR)/osfmk/i386/vmx/vmx_cpu.c \
	$(SOURCE_DIR)/osfmk/i386/vmx/vmx_shims.c \
	$(SOURCE_DIR)/osfmk/kern/hv_support_kext.c \
	$(SOURCE_DIR)/osfmk/x86_64/kpc_x86.c \
	$(SOURCE_DIR)/osfmk/i386/panic_hooks.c \
	$(SOURCE_DIR)/osfmk/i386/panic_notify.c \
	$(SOURCE_DIR)/osfmk/x86_64/machine_remote_time.c 
COBJS=gssd_mach.o lockd_mach.o kextd_mach.o UNDRequest.o \
	UNDReplyServer.o KUNCUserNotifications.o kdp.o kern_stackshot.o \
	kdp_udp.o kdp_core.o processor_core.o kdp_serial.o ipc_entry.o \
	ipc_eventlink.o ipc_hash.o ipc_importance.o ipc_init.o \
	ipc_kmsg.o ipc_mqueue.o ipc_notify.o ipc_object.o ipc_port.o \
	ipc_pset.o ipc_right.o ipc_space.o ipc_table.o ipc_voucher.o \
	mach_debug.o mach_kernelrpc.o mach_msg.o mach_port.o affinity.o \
	arcade.o ast.o audit_sessionport.o backtrace.o btlog.o \
	build_config.o clock.o clock_oldops.o coalition.o counters.o \
	debug.o energy_perf.o exception.o extmod_statistics.o host.o \
	host_notify.o ipc_clock.o ipc_host.o ipc_kobject.o ipc_mig.o \
	ipc_misc.o ipc_sync.o ipc_tt.o kalloc.o \
	ktrace_background_notify.o ledger.o locks.o tlock.o ltable.o \
	mach_node.o machine.o mk_sp.o mk_timer.o mpsc_queue.o \
	page_decrypt.o printf.o priority.o processor.o restartable.o \
	sched_average.o sched_amp.o sched_amp_common.o sched_dualq.o \
	sched_prim.o sched_proto.o sched_traditional.o sched_grrr.o \
	sched_multiq.o sfi.o stack.o startup.o sync_lock.o sync_sema.o \
	syscall_emulation.o syscall_subr.o syscall_sw.o sysdiagnose.o \
	task.o task_policy.o task_swap.o test_lock.o test_mpsc_queue.o \
	thread.o thread_act.o thread_call.o thread_group.o \
	thread_policy.o timer.o timer_call.o turnstile.o ux_handler.o \
	waitq.o work_interval.o zalloc.o zcache.o gzalloc.o bsd_kern.o \
	hibernate.o remote_time.o memset_s.o copyout_shim.o suid_cred.o \
	clock_server.o clock_priv_server.o clock_reply_user.o exc_user.o \
	exc_server.o mach_eventlink_server.o host_priv_server.o \
	host_security_server.o ktrace_background_user.o \
	lock_set_server.o mach_exc_user.o mach_exc_server.o \
	mach_host_server.o mach_notify_user.o mach_port_server.o \
	mach_vm_server.o mach_voucher_server.o \
	mach_voucher_attr_control_server.o memory_entry_server.o \
	memory_object_control_server.o resource_notify_user.o \
	restartable_server.o upl_server.o audit_triggers_user.o \
	task_access_user.o corpse.o kern_cdata.o kernel_tests.o ktest.o \
	ktest_accessor.o ktest_emit.o ktest_global.o pmap_tests.o \
	ptrauth_data_tests.o bitmap_test.o test_thread_call.o \
	vfp_state_test.o telemetry_notification_user.o bank.o atm.o \
	atm_notification_user.o ipc_pthread_priority.o \
	coalition_notification_user.o sysdiagnose_notification_user.o \
	vfs_nspace_user.o fairplayd_notification_user.o \
	arcade_upcall_user.o arcade_register_server.o processor_server.o \
	processor_set_server.o task_server.o thread_act_server.o \
	vm32_map_server.o bsd_vm.o vm_compressor.o vm_compressor_pager.o \
	vm_compressor_backing_store.o vm_compressor_algorithms.o lz4.o \
	device_vm.o memory_object.o vm_debug.o vm_fault.o vm_init.o \
	vm_kern.o vm_map.o vm_map_store.o vm_map_store_ll.o \
	vm_map_store_rb.o vm_object.o vm_pageout.o vm_purgeable.o \
	vm_resident.o vm_shared_region.o vm_shared_region_pager.o \
	vm_swapfile_pager.o vm_tests.o vm_user.o vm32_user.o iokit_rpc.o \
	device_server.o device_init.o kext_alloc.o kmod.o subrs.o \
	kperf.o action.o callstack.o pet.o thread_samplers.o \
	task_samplers.o meminfo.o kptimer.o kperf_kpc.o kdebug_trigger.o \
	lazy.o kpc_thread.o kpc_common.o serial_general.o \
	serial_console.o video_scroll.o video_console.o telemetry.o \
	cc_clear.o cc_cmp_safe.o cc_abort.o ccdrbg_nisthmac.o \
	ccdigest_init.o ccdigest_update.o cchmac.o cchmac_init.o \
	cchmac_update.o cchmac_final.o ccdigest_final_64be.o \
	ccsha256_di.o ccsha256_initial_state.o ccsha256_K.o \
	ccsha256_ltc_compress.o ccsha256_ltc_di.o prng_random.o \
	entropy.o vm_apple_protect.o pmap.o pmap_x86_common.o \
	pmap_common.o pmap_pcid.o pal_routines.o bsd_i386.o \
	bsd_i386_native.o machdep_call.o boot_pt.o mp_desc.o gdt.o cpu.o \
	cpuid.o cpu_threads.o cpu_topology.o i386_timer.o fpu.o \
	i386_init.o i386_vm_init.o io_map.o ktss.o ldt.o loose_ends.o \
	copyio.o locks_i386.o locks_i386_opt.o lowmem_vectors.o \
	machine_routines.o machine_check.o machine_task.o pcb.o \
	pcb_native.o phys.o rtclock.o rtclock_native.o trap.o \
	trap_native.o user_ldt.o Diagnostics.o pmCPU.o tsc.o commpage.o \
	model_dep.o lapic.o lapic_native.o mp.o mp_native.o acpi.o \
	mtrr.o kdp_machdep.o kdp_vm.o kdp_x86_common.o hibernate_i386.o \
	hibernate_restore.o ucode.o vmx_cpu.o vmx_shims.o \
	hv_support_kext.o kpc_x86.o panic_hooks.o panic_notify.o \
	machine_remote_time.o 

CXXFILES=
CXXOBJS=

SFILES=\
	$(SOURCE_DIR)/osfmk/x86_64/pal_routines_asm.s \
	$(SOURCE_DIR)/osfmk/x86_64/start.s \
	$(SOURCE_DIR)/osfmk/x86_64/bcopy.s \
	$(SOURCE_DIR)/osfmk/x86_64/bzero.s \
	$(SOURCE_DIR)/osfmk/x86_64/WKdmDecompress_new.s \
	$(SOURCE_DIR)/osfmk/x86_64/WKdmCompress_new.s \
	$(SOURCE_DIR)/osfmk/x86_64/WKdmData_new.s \
	$(SOURCE_DIR)/osfmk/x86_64/lz4_decode_x86_64.s \
	$(SOURCE_DIR)/osfmk/i386/fp_simd.s \
	$(SOURCE_DIR)/osfmk/i386/i386_lock.s \
	$(SOURCE_DIR)/osfmk/x86_64/locore.s \
	$(SOURCE_DIR)/osfmk/x86_64/cswitch.s \
	$(SOURCE_DIR)/osfmk/x86_64/machine_routines_asm.s \
	$(SOURCE_DIR)/osfmk/i386/commpage/commpage_asm.s \
	$(SOURCE_DIR)/osfmk/i386/commpage/fifo_queues.s \
	$(SOURCE_DIR)/osfmk/x86_64/idt64.s 
SOBJS=pal_routines_asm.o start.o bcopy.o bzero.o WKdmDecompress_new.o \
	WKdmCompress_new.o WKdmData_new.o lz4_decode_x86_64.o fp_simd.o \
	i386_lock.o locore.o cswitch.o machine_routines_asm.o \
	commpage_asm.o fifo_queues.o idt64.o 

######################################################################
#BEGIN	Machine dependent Makefile fragment for x86_64
######################################################################

CWARNFLAGS = $(CWARNFLAGS_STD) -Wno-atomic-implicit-seq-cst

# Files that must go in the __HIB segment:
UNCONFIGURED_HIB_FILES=					\
           WKdmDecompress_new.o         \
           WKdmData_new.o               \
           hibernate_restore.o          \
           bcopy.o			\
           bzero.o

HIB_FILES=$(filter $(UNCONFIGURED_HIB_FILES),$(OBJS))

# Unconfigured __HIB files must be Mach-O for "setsegname"
WKdmDecompress_new.o_CFLAGS_ADD += -fno-stack-protector -fno-stack-check $(CFLAGS_NOLTO_FLAG)
WKdmData_new.o_CFLAGS_ADD += -fno-stack-protector -fno-stack-check $(CFLAGS_NOLTO_FLAG)
hibernate_restore.o_CFLAGS_ADD += -fno-stack-protector -fno-stack-check $(CFLAGS_NOLTO_FLAG)
bcopy.o_CFLAGS_ADD += -fno-stack-protector -fno-stack-check $(CFLAGS_NOLTO_FLAG)
bzero.o_CFLAGS_ADD += -fno-stack-protector -fno-stack-check $(CFLAGS_NOLTO_FLAG)
fp_simd.o_SFLAGS_ADD += -mavx512f

# To appear at the beginning of the __HIB segment, emit
# as Mach-O so that the linker can enforce symbol order
boot_pt.o_CFLAGS_ADD += $(CFLAGS_NOLTO_FLAG)

# fast path lock C leaf functions must be built without stack frames
locks_i386_opt.o_CFLAGS_ADD += -momit-leaf-frame-pointer -O2

######################################################################
#END	Machine dependent Makefile fragment for x86_64
######################################################################

#
# Diagnostic opt-outs.  We need to make this list empty.
#
# DO NOT ADD MORE HERE.
#
vm_tests.o_CFLAGS_ADD += -O0 -g
# -Wno-atomic-implicit-seq-cst
mp.o_CFLAGS_ADD += -Wno-atomic-implicit-seq-cst
pmCPU.o_CFLAGS_ADD += -Wno-atomic-implicit-seq-cst
pmap_pcid.o_CFLAGS_ADD += -Wno-atomic-implicit-seq-cst
xcpm_dvfs.o_CFLAGS_ADD += -Wno-atomic-implicit-seq-cst
xcpm_fi.o_CFLAGS_ADD += -Wno-atomic-implicit-seq-cst
xcpm_idle.o_CFLAGS_ADD += -Wno-atomic-implicit-seq-cst
# -Wno-cast-align
bsd_i386.o_CFLAGS_ADD += -Wno-cast-align
ccdigest_final_64be.o_CFLAGS_ADD += -Wno-cast-align
ccdigest_init.o_CFLAGS_ADD += -Wno-cast-align
ccdigest_update.o_CFLAGS_ADD += -Wno-cast-align
cchmac_final.o_CFLAGS_ADD += -Wno-cast-align
cchmac_init.o_CFLAGS_ADD += -Wno-cast-align
commpage.o_CFLAGS_ADD += -Wno-cast-align
cpu_threads.o_CFLAGS_ADD += -Wno-cast-align
host.o_CFLAGS_ADD += -Wno-cast-align
kdp_machdep.o_CFLAGS_ADD += -Wno-cast-align
kdp_udp.o_CFLAGS_ADD += -Wno-cast-align
kdp_x86_common.o_CFLAGS_ADD += -Wno-cast-align
locks_i386.o_CFLAGS_ADD += -Wno-cast-align
machine_task.o_CFLAGS_ADD += -Wno-cast-align
model_dep.o_CFLAGS_ADD += -Wno-cast-align
mp_desc.o_CFLAGS_ADD += -Wno-cast-align
pcb.o_CFLAGS_ADD += -Wno-cast-align
pcb_native.o_CFLAGS_ADD += -Wno-cast-align
processor.o_CFLAGS_ADD += -Wno-cast-align
status.o_CFLAGS_ADD += -Wno-cast-align
task.o_CFLAGS_ADD += -Wno-cast-align
task_policy.o_CFLAGS_ADD += -Wno-cast-align
video_console.o_CFLAGS_ADD += -Wno-cast-align
# -Wno-implicit-int-conversion
acpi.o_CFLAGS_ADD += -Wno-implicit-int-conversion
commpage.o_CFLAGS_ADD += -Wno-implicit-int-conversion
cpu.o_CFLAGS_ADD += -Wno-implicit-int-conversion
cpu_threads.o_CFLAGS_ADD += -Wno-implicit-int-conversion
kdebug_trigger.o_CFLAGS_ADD += -Wno-implicit-int-conversion
kern_stackshot.o_CFLAGS_ADD += -Wno-implicit-int-conversion
lapic_native.o_CFLAGS_ADD += -Wno-implicit-int-conversion
loose_ends.o_CFLAGS_ADD += -Wno-implicit-int-conversion
lz4.o_CFLAGS_ADD += -Wno-implicit-int-conversion
model_dep.o_CFLAGS_ADD += -Wno-implicit-int-conversion
mp.o_CFLAGS_ADD += -Wno-implicit-int-conversion
mp_desc.o_CFLAGS_ADD += -Wno-implicit-int-conversion
pcb.o_CFLAGS_ADD += -Wno-implicit-int-conversion
pcb_native.o_CFLAGS_ADD += -Wno-implicit-int-conversion
pmap_pcid.o_CFLAGS_ADD += -Wno-implicit-int-conversion
pmap_x86_common.o_CFLAGS_ADD += -Wno-implicit-int-conversion
sched_clutch.o_CFLAGS_ADD += -Wno-implicit-int-conversion
thread_group.o_CFLAGS_ADD += -Wno-implicit-int-conversion
trap.o_CFLAGS_ADD += -Wno-implicit-int-conversion
uat.o_CFLAGS_ADD += -Wno-implicit-int-conversion
video_console.o_CFLAGS_ADD += -Wno-implicit-int-conversion
xcpm_dvfs.o_CFLAGS_ADD += -Wno-implicit-int-conversion
xcpm_ioctl.o_CFLAGS_ADD += -Wno-implicit-int-conversion
zalloc.o_CFLAGS_ADD += -Wno-implicit-int-conversion
# -Wno-shorten-64-to-32
arm_vm_init.o_CFLAGS_ADD += -Wno-shorten-64-to-32
backtrace.o_CFLAGS_ADD += -Wno-shorten-64-to-32
btlog.o_CFLAGS_ADD += -Wno-shorten-64-to-32
caches.o_CFLAGS_ADD += -Wno-shorten-64-to-32
callstack.o_CFLAGS_ADD += -Wno-shorten-64-to-32
clock.o_CFLAGS_ADD += -Wno-shorten-64-to-32
clock_oldops.o_CFLAGS_ADD += -Wno-shorten-64-to-32
iokit_rpc.o_CFLAGS_ADD += -Wno-shorten-64-to-32
ipc_kmsg.o_CFLAGS_ADD += -Wno-shorten-64-to-32
ipc_pset.o_CFLAGS_ADD += -Wno-shorten-64-to-32
ipc_right.o_CFLAGS_ADD += -Wno-shorten-64-to-32
kdp_core.o_CFLAGS_ADD += -Wno-shorten-64-to-32
kdp_vm.o_CFLAGS_ADD += -Wno-shorten-64-to-32
kern_cdata.o_CFLAGS_ADD += -Wno-shorten-64-to-32
kern_stackshot.o_CFLAGS_ADD += -Wno-shorten-64-to-32
loose_ends.o_CFLAGS_ADD += -Wno-shorten-64-to-32
mach_msg.o_CFLAGS_ADD += -Wno-shorten-64-to-32
machine_routines.o_CFLAGS_ADD += -Wno-shorten-64-to-32
mk_timer.o_CFLAGS_ADD += -Wno-shorten-64-to-32
model_dep.o_CFLAGS_ADD += -Wno-shorten-64-to-32
pcb.o_CFLAGS_ADD += -Wno-shorten-64-to-32
pmap.o_CFLAGS_ADD += -Wno-shorten-64-to-32
processor_core.o_CFLAGS_ADD += -Wno-shorten-64-to-32
rtclock.o_CFLAGS_ADD += -Wno-shorten-64-to-32
status.o_CFLAGS_ADD += -Wno-shorten-64-to-32
telemetry.o_CFLAGS_ADD += -Wno-shorten-64-to-32
vm_init.o_CFLAGS_ADD += -Wno-shorten-64-to-32
vm_kern.o_CFLAGS_ADD += -Wno-shorten-64-to-32
vm_object.o_CFLAGS_ADD += -Wno-shorten-64-to-32
vm_shared_region_pager.o_CFLAGS_ADD += -Wno-shorten-64-to-32
vm_swapfile_pager.o_CFLAGS_ADD += -Wno-shorten-64-to-32
vm_user.o_CFLAGS_ADD += -Wno-shorten-64-to-32
zalloc.o_CFLAGS_ADD += -Wno-shorten-64-to-32
# -Wno-sign-conversion
Diagnostics.o_CFLAGS_ADD += -Wno-sign-conversion
acpi.o_CFLAGS_ADD += -Wno-sign-conversion
action.o_CFLAGS_ADD += -Wno-sign-conversion
affinity.o_CFLAGS_ADD += -Wno-sign-conversion
alternate_debugger.o_CFLAGS_ADD += -Wno-sign-conversion
arcade.o_CFLAGS_ADD += -Wno-sign-conversion
arm_init.o_CFLAGS_ADD += -Wno-sign-conversion
arm_timer.o_CFLAGS_ADD += -Wno-sign-conversion
arm_vm_init.o_CFLAGS_ADD += -Wno-sign-conversion
ast.o_CFLAGS_ADD += -Wno-sign-conversion
backtrace.o_CFLAGS_ADD += -Wno-sign-conversion
bank.o_CFLAGS_ADD += -Wno-sign-conversion
bitmap_test.o_CFLAGS_ADD += -Wno-sign-conversion
bsd_arm64.o_CFLAGS_ADD += -Wno-sign-conversion
bsd_i386.o_CFLAGS_ADD += -Wno-sign-conversion
bsd_i386_native.o_CFLAGS_ADD += -Wno-sign-conversion
bsd_kern.o_CFLAGS_ADD += -Wno-sign-conversion
bsd_vm.o_CFLAGS_ADD += -Wno-sign-conversion
btlog.o_CFLAGS_ADD += -Wno-sign-conversion
caches.o_CFLAGS_ADD += -Wno-sign-conversion
callstack.o_CFLAGS_ADD += -Wno-sign-conversion
ccdrbg_nisthmac.o_CFLAGS_ADD += -Wno-sign-conversion
cchmac.o_CFLAGS_ADD += -Wno-sign-conversion
cchmac_final.o_CFLAGS_ADD += -Wno-sign-conversion
cchmac_init.o_CFLAGS_ADD += -Wno-sign-conversion
clock.o_CFLAGS_ADD += -Wno-sign-conversion
clock_oldops.o_CFLAGS_ADD += -Wno-sign-conversion
coalition.o_CFLAGS_ADD += -Wno-sign-conversion
commpage.o_CFLAGS_ADD += -Wno-sign-conversion
copyio.o_CFLAGS_ADD += -Wno-sign-conversion
corpse.o_CFLAGS_ADD += -Wno-sign-conversion
cpu.o_CFLAGS_ADD += -Wno-sign-conversion
cpu_common.o_CFLAGS_ADD += -Wno-sign-conversion
cpu_quiesce.o_CFLAGS_ADD += -Wno-sign-conversion
cpu_threads.o_CFLAGS_ADD += -Wno-sign-conversion
cpu_topology.o_CFLAGS_ADD += -Wno-sign-conversion
cpuid.o_CFLAGS_ADD += -Wno-sign-conversion
dbgwrap.o_CFLAGS_ADD += -Wno-sign-conversion
debug.o_CFLAGS_ADD += -Wno-sign-conversion
ecc_logging.o_CFLAGS_ADD += -Wno-sign-conversion
entropy.o_CFLAGS_ADD += -Wno-sign-conversion
exception.o_CFLAGS_ADD += -Wno-sign-conversion
fpu.o_CFLAGS_ADD += -Wno-sign-conversion
gzalloc.o_CFLAGS_ADD += -Wno-sign-conversion
host.o_CFLAGS_ADD += -Wno-sign-conversion
host_notify.o_CFLAGS_ADD += -Wno-sign-conversion
hv.o_CFLAGS_ADD += -Wno-sign-conversion
i386_init.o_CFLAGS_ADD += -Wno-sign-conversion
i386_timer.o_CFLAGS_ADD += -Wno-sign-conversion
i386_vm_init.o_CFLAGS_ADD += -Wno-sign-conversion
iokit_rpc.o_CFLAGS_ADD += -Wno-sign-conversion
ipc_eventlink.o_CFLAGS_ADD += -Wno-sign-conversion
ipc_host.o_CFLAGS_ADD += -Wno-sign-conversion
ipc_importance.o_CFLAGS_ADD += -Wno-sign-conversion
ipc_init.o_CFLAGS_ADD += -Wno-sign-conversion
ipc_kmsg.o_CFLAGS_ADD += -Wno-sign-conversion
ipc_kobject.o_CFLAGS_ADD += -Wno-sign-conversion
ipc_mqueue.o_CFLAGS_ADD += -Wno-sign-conversion
ipc_object.o_CFLAGS_ADD += -Wno-sign-conversion
ipc_port.o_CFLAGS_ADD += -Wno-sign-conversion
ipc_pset.o_CFLAGS_ADD += -Wno-sign-conversion
ipc_right.o_CFLAGS_ADD += -Wno-sign-conversion
ipc_space.o_CFLAGS_ADD += -Wno-sign-conversion
ipc_tt.o_CFLAGS_ADD += -Wno-sign-conversion
ipc_voucher.o_CFLAGS_ADD += -Wno-sign-conversion
kalloc.o_CFLAGS_ADD += -Wno-sign-conversion
kdp.o_CFLAGS_ADD += -Wno-sign-conversion
kdp_core.o_CFLAGS_ADD += -Wno-sign-conversion
kdp_machdep.o_CFLAGS_ADD += -Wno-sign-conversion
kdp_serial.o_CFLAGS_ADD += -Wno-sign-conversion
kdp_vm.o_CFLAGS_ADD += -Wno-sign-conversion
kern_monotonic.o_CFLAGS_ADD += -Wno-sign-conversion
kern_stackshot.o_CFLAGS_ADD += -Wno-sign-conversion
kernel_tests.o_CFLAGS_ADD += -Wno-sign-conversion
kext_alloc.o_CFLAGS_ADD += -Wno-sign-conversion
kpc.o_CFLAGS_ADD += -Wno-sign-conversion
kpc_arm.o_CFLAGS_ADD += -Wno-sign-conversion
kpc_common.o_CFLAGS_ADD += -Wno-sign-conversion
kpc_x86.o_CFLAGS_ADD += -Wno-sign-conversion
kperf.o_CFLAGS_ADD += -Wno-sign-conversion
kperf_kpc.o_CFLAGS_ADD += -Wno-sign-conversion
kperf_mp.o_CFLAGS_ADD += -Wno-sign-conversion
kperf_timer.o_CFLAGS_ADD += -Wno-sign-conversion
kperfbsd.o_CFLAGS_ADD += -Wno-sign-conversion
ktest_emit.o_CFLAGS_ADD += -Wno-sign-conversion
lapic_native.o_CFLAGS_ADD += -Wno-sign-conversion
lazy.o_CFLAGS_ADD += -Wno-sign-conversion
ledger.o_CFLAGS_ADD += -Wno-sign-conversion
locks.o_CFLAGS_ADD += -Wno-sign-conversion
locks_arm.o_CFLAGS_ADD += -Wno-sign-conversion
locks_i386.o_CFLAGS_ADD += -Wno-sign-conversion
locks_i386_opt.o_CFLAGS_ADD += -Wno-sign-conversion
loose_ends.o_CFLAGS_ADD += -Wno-sign-conversion
lowmem_vectors.o_CFLAGS_ADD += -Wno-sign-conversion
ltable.o_CFLAGS_ADD += -Wno-sign-conversion
lz4.o_CFLAGS_ADD += -Wno-sign-conversion
mach_debug.o_CFLAGS_ADD += -Wno-sign-conversion
mach_kernelrpc.o_CFLAGS_ADD += -Wno-sign-conversion
mach_port.o_CFLAGS_ADD += -Wno-sign-conversion
machdep_call.o_CFLAGS_ADD += -Wno-sign-conversion
machine.o_CFLAGS_ADD += -Wno-sign-conversion
machine_check.o_CFLAGS_ADD += -Wno-sign-conversion
machine_remote_time.o_CFLAGS_ADD += -Wno-sign-conversion
machine_routines.o_CFLAGS_ADD += -Wno-sign-conversion
machine_routines_common.o_CFLAGS_ADD += -Wno-sign-conversion
machine_task.o_CFLAGS_ADD += -Wno-sign-conversion
meminfo.o_CFLAGS_ADD += -Wno-sign-conversion
memory_object.o_CFLAGS_ADD += -Wno-sign-conversion
mk_sp.o_CFLAGS_ADD += -Wno-sign-conversion
mk_timer.o_CFLAGS_ADD += -Wno-sign-conversion
model_dep.o_CFLAGS_ADD += -Wno-sign-conversion
monotonic_arm64.o_CFLAGS_ADD += -Wno-sign-conversion
monotonic_x86_64.o_CFLAGS_ADD += -Wno-sign-conversion
mp.o_CFLAGS_ADD += -Wno-sign-conversion
mp_desc.o_CFLAGS_ADD += -Wno-sign-conversion
mp_native.o_CFLAGS_ADD += -Wno-sign-conversion
mpsc_queue.o_CFLAGS_ADD += -Wno-sign-conversion
mtrr.o_CFLAGS_ADD += -Wno-sign-conversion
pal_routines.o_CFLAGS_ADD += -Wno-sign-conversion
pcb.o_CFLAGS_ADD += -Wno-sign-conversion
pcb_native.o_CFLAGS_ADD += -Wno-sign-conversion
pet.o_CFLAGS_ADD += -Wno-sign-conversion
platform_tests.o_CFLAGS_ADD += -Wno-sign-conversion
pmCPU.o_CFLAGS_ADD += -Wno-sign-conversion
pmap.o_CFLAGS_ADD += -Wno-sign-conversion
pmap_common.o_CFLAGS_ADD += -Wno-sign-conversion
pmap_pcid.o_CFLAGS_ADD += -Wno-sign-conversion
pmap_tests.o_CFLAGS_ADD += -Wno-sign-conversion
pmap_x86_common.o_CFLAGS_ADD += -Wno-sign-conversion
printf.o_CFLAGS_ADD += -Wno-sign-conversion
priority.o_CFLAGS_ADD += -Wno-sign-conversion
prng_random.o_CFLAGS_ADD += -Wno-sign-conversion
processor.o_CFLAGS_ADD += -Wno-sign-conversion
remote_time.o_CFLAGS_ADD += -Wno-sign-conversion
rtclock.o_CFLAGS_ADD += -Wno-sign-conversion
sart.o_CFLAGS_ADD += -Wno-sign-conversion
sched_amp.o_CFLAGS_ADD += -Wno-sign-conversion
sched_amp_common.o_CFLAGS_ADD += -Wno-sign-conversion
sched_average.o_CFLAGS_ADD += -Wno-sign-conversion
sched_clutch.o_CFLAGS_ADD += -Wno-sign-conversion
sched_dualq.o_CFLAGS_ADD += -Wno-sign-conversion
sched_multiq.o_CFLAGS_ADD += -Wno-sign-conversion
sched_prim.o_CFLAGS_ADD += -Wno-sign-conversion
sched_traditional.o_CFLAGS_ADD += -Wno-sign-conversion
serial_console.o_CFLAGS_ADD += -Wno-sign-conversion
serial_general.o_CFLAGS_ADD += -Wno-sign-conversion
sfi.o_CFLAGS_ADD += -Wno-sign-conversion
shart.o_CFLAGS_ADD += -Wno-sign-conversion
sleh.o_CFLAGS_ADD += -Wno-sign-conversion
stack.o_CFLAGS_ADD += -Wno-sign-conversion
startup.o_CFLAGS_ADD += -Wno-sign-conversion
status.o_CFLAGS_ADD += -Wno-sign-conversion
status_shared.o_CFLAGS_ADD += -Wno-sign-conversion
subrs.o_CFLAGS_ADD += -Wno-sign-conversion
sync_sema.o_CFLAGS_ADD += -Wno-sign-conversion
syscall_subr.o_CFLAGS_ADD += -Wno-sign-conversion
t8020dart.o_CFLAGS_ADD += -Wno-sign-conversion
task.o_CFLAGS_ADD += -Wno-sign-conversion
task_policy.o_CFLAGS_ADD += -Wno-sign-conversion
telemetry.o_CFLAGS_ADD += -Wno-sign-conversion
test_lock.o_CFLAGS_ADD += -Wno-sign-conversion
test_thread_call.o_CFLAGS_ADD += -Wno-sign-conversion
thread_call.o_CFLAGS_ADD += -Wno-sign-conversion
thread_group.o_CFLAGS_ADD += -Wno-sign-conversion
thread_policy.o_CFLAGS_ADD += -Wno-sign-conversion
timer_call.o_CFLAGS_ADD += -Wno-sign-conversion
trap.o_CFLAGS_ADD += -Wno-sign-conversion
trustcache.o_CFLAGS_ADD += -Wno-sign-conversion
turnstile.o_CFLAGS_ADD += -Wno-sign-conversion
uat.o_CFLAGS_ADD += -Wno-sign-conversion
ucode.o_CFLAGS_ADD += -Wno-sign-conversion
ux_handler.o_CFLAGS_ADD += -Wno-sign-conversion
vfp_state_test.o_CFLAGS_ADD += -Wno-sign-conversion
video_console.o_CFLAGS_ADD += -Wno-sign-conversion
video_scroll.o_CFLAGS_ADD += -Wno-sign-conversion
vm32_user.o_CFLAGS_ADD += -Wno-sign-conversion
vm_compressor.o_CFLAGS_ADD += -Wno-sign-conversion
vm_compressor_algorithms.o_CFLAGS_ADD += -Wno-sign-conversion
vm_compressor_backing_store.o_CFLAGS_ADD += -Wno-sign-conversion
vm_compressor_pager.o_CFLAGS_ADD += -Wno-sign-conversion
vm_fault.o_CFLAGS_ADD += -Wno-sign-conversion
vm_fourk_pager.o_CFLAGS_ADD += -Wno-sign-conversion
vm_kern.o_CFLAGS_ADD += -Wno-sign-conversion
vm_map.o_CFLAGS_ADD += -Wno-sign-conversion
vm_map_store_ll.o_CFLAGS_ADD += -Wno-sign-conversion
vm_map_store_rb.o_CFLAGS_ADD += -Wno-sign-conversion
vm_object.o_CFLAGS_ADD += -Wno-sign-conversion
vm_pageout.o_CFLAGS_ADD += -Wno-sign-conversion
vm_phantom_cache.o_CFLAGS_ADD += -Wno-sign-conversion
vm_purgeable.o_CFLAGS_ADD += -Wno-sign-conversion
vm_resident.o_CFLAGS_ADD += -Wno-sign-conversion
vm_shared_region.o_CFLAGS_ADD += -Wno-sign-conversion
vm_user.o_CFLAGS_ADD += -Wno-sign-conversion
vmx_cpu.o_CFLAGS_ADD += -Wno-sign-conversion
waitq.o_CFLAGS_ADD += -Wno-sign-conversion
work_interval.o_CFLAGS_ADD += -Wno-sign-conversion
xcpm_dvfs.o_CFLAGS_ADD += -Wno-sign-conversion
xcpm_fi.o_CFLAGS_ADD += -Wno-sign-conversion
xcpm_idle.o_CFLAGS_ADD += -Wno-sign-conversion
xcpm_ioctl.o_CFLAGS_ADD += -Wno-sign-conversion
zalloc.o_CFLAGS_ADD += -Wno-sign-conversion
zcache.o_CFLAGS_ADD += -Wno-sign-conversion

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
	$(_v)for hib_file in ${HIB_FILES};		\
	do	\
                $(SEG_HACK) -n __HIB -o $${hib_file}__ $${hib_file} || exit 1; \
                mv $${hib_file}__ $${hib_file} || exit 1; \
	done
	@$(LOG_LDFILELIST) "$(COMPONENT)"
	$(_v)for obj in ${OBJS}; do	\
		 $(ECHO) $(TARGET)/$(CURRENT_KERNEL_CONFIG)/$${obj}; \
	done > $(COMPONENT).filelist

do_all: $(COMPONENT).filelist

do_build_all:: do_all

# genassym.o actually is an assembly file,
# we name it genassym.o to help with the automatic
# dependency generation

GENASSYM_LOCATION = $(CURRENT_ARCH_CONFIG_LC)

ifeq ($(CURRENT_ARCH_CONFIG_LC),x86_64)
GENASSYM_LOCATION = i386
else ifeq ($(CURRENT_ARCH_CONFIG_LC),x86_64h)
GENASSYM_LOCATION = i386
endif

-include genassym.d
genassym.o: .CFLAGS $(firstword $(MAKEFILE_LIST))
genassym.o: $(SOURCE_DIR)/$(COMPONENT)/$(GENASSYM_LOCATION)/genassym.c
	@$(LOG_GENASSYM) "$<"
	$(_v)${GENASSYM_KCC} ${CFLAGS} ${CFLAGS_NOLTO_FLAG} -fno-integrated-as -MD -S -o ${@} ${INCFLAGS} $<

assym.s: genassym.o
	$(_v)sed -e '/^[[:space:]]*DEFINITION__define__/!d;{N;s/\n//;}' -e 's/^[[:space:]]*DEFINITION__define__\([^:]*\):.*ascii.*\"[\$$]*\([-0-9\#]*\)\".*$$/#define \1 \2/' -e 'p'  -e 's/#//2' -e 's/^[[:space:]]*#define \([A-Za-z0-9_]*\)[[:space:]]*[\$$#]*\([-0-9]*\).*$$/#define \1_NUM \2/' genassym.o > $@

${SOBJS}: assym.s

-include gssd_mach.d
gssd_mach.o: gssd/gssd_mach.c
	${C_RULE_0}
	${C_RULE_1A}gssd/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}gssd/${C_RULE_4B})
-include lockd_mach.d
lockd_mach.o: lockd/lockd_mach.c
	${C_RULE_0}
	${C_RULE_1A}lockd/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}lockd/${C_RULE_4B})
-include kextd_mach.d
kextd_mach.o: kextd/kextd_mach.c
	${C_RULE_0}
	${C_RULE_1A}kextd/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}kextd/${C_RULE_4B})
-include UNDRequest.d
UNDRequest.o: UserNotification/UNDRequest.c
	${C_RULE_0}
	${C_RULE_1A}UserNotification/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}UserNotification/${C_RULE_4B})
-include UNDReplyServer.d
UNDReplyServer.o: UserNotification/UNDReplyServer.c
	${C_RULE_0}
	${C_RULE_1A}UserNotification/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}UserNotification/${C_RULE_4B})
-include KUNCUserNotifications.d
KUNCUserNotifications.o: $(SOURCE_DIR)/osfmk/UserNotification/KUNCUserNotifications.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/UserNotification/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/UserNotification/${C_RULE_4B})
-include kdp.d
kdp.o: $(SOURCE_DIR)/osfmk/kdp/kdp.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kdp/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kdp/${C_RULE_4B})
-include kern_stackshot.d
kern_stackshot.o: $(SOURCE_DIR)/osfmk/kern/kern_stackshot.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include kdp_udp.d
kdp_udp.o: $(SOURCE_DIR)/osfmk/kdp/kdp_udp.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kdp/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kdp/${C_RULE_4B})
-include kdp_core.d
kdp_core.o: $(SOURCE_DIR)/osfmk/kdp/kdp_core.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kdp/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kdp/${C_RULE_4B})
-include processor_core.d
processor_core.o: $(SOURCE_DIR)/osfmk/kdp/processor_core.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kdp/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kdp/${C_RULE_4B})
-include kdp_serial.d
kdp_serial.o: $(SOURCE_DIR)/osfmk/kdp/kdp_serial.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kdp/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kdp/${C_RULE_4B})
-include ipc_entry.d
ipc_entry.o: $(SOURCE_DIR)/osfmk/ipc/ipc_entry.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_4B})
-include ipc_eventlink.d
ipc_eventlink.o: $(SOURCE_DIR)/osfmk/ipc/ipc_eventlink.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_4B})
-include ipc_hash.d
ipc_hash.o: $(SOURCE_DIR)/osfmk/ipc/ipc_hash.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_4B})
-include ipc_importance.d
ipc_importance.o: $(SOURCE_DIR)/osfmk/ipc/ipc_importance.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_4B})
-include ipc_init.d
ipc_init.o: $(SOURCE_DIR)/osfmk/ipc/ipc_init.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_4B})
-include ipc_kmsg.d
ipc_kmsg.o: $(SOURCE_DIR)/osfmk/ipc/ipc_kmsg.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_4B})
-include ipc_mqueue.d
ipc_mqueue.o: $(SOURCE_DIR)/osfmk/ipc/ipc_mqueue.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_4B})
-include ipc_notify.d
ipc_notify.o: $(SOURCE_DIR)/osfmk/ipc/ipc_notify.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_4B})
-include ipc_object.d
ipc_object.o: $(SOURCE_DIR)/osfmk/ipc/ipc_object.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_4B})
-include ipc_port.d
ipc_port.o: $(SOURCE_DIR)/osfmk/ipc/ipc_port.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_4B})
-include ipc_pset.d
ipc_pset.o: $(SOURCE_DIR)/osfmk/ipc/ipc_pset.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_4B})
-include ipc_right.d
ipc_right.o: $(SOURCE_DIR)/osfmk/ipc/ipc_right.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_4B})
-include ipc_space.d
ipc_space.o: $(SOURCE_DIR)/osfmk/ipc/ipc_space.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_4B})
-include ipc_table.d
ipc_table.o: $(SOURCE_DIR)/osfmk/ipc/ipc_table.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_4B})
-include ipc_voucher.d
ipc_voucher.o: $(SOURCE_DIR)/osfmk/ipc/ipc_voucher.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_4B})
-include mach_debug.d
mach_debug.o: $(SOURCE_DIR)/osfmk/ipc/mach_debug.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_4B})
-include mach_kernelrpc.d
mach_kernelrpc.o: $(SOURCE_DIR)/osfmk/ipc/mach_kernelrpc.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_4B})
-include mach_msg.d
mach_msg.o: $(SOURCE_DIR)/osfmk/ipc/mach_msg.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_4B})
-include mach_port.d
mach_port.o: $(SOURCE_DIR)/osfmk/ipc/mach_port.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/ipc/${C_RULE_4B})
-include affinity.d
affinity.o: $(SOURCE_DIR)/osfmk/kern/affinity.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include arcade.d
arcade.o: $(SOURCE_DIR)/osfmk/kern/arcade.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include ast.d
ast.o: $(SOURCE_DIR)/osfmk/kern/ast.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include audit_sessionport.d
audit_sessionport.o: $(SOURCE_DIR)/osfmk/kern/audit_sessionport.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include backtrace.d
backtrace.o: $(SOURCE_DIR)/osfmk/kern/backtrace.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include btlog.d
btlog.o: $(SOURCE_DIR)/osfmk/kern/btlog.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include build_config.d
build_config.o: $(SOURCE_DIR)/osfmk/kern/build_config.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include clock.d
clock.o: $(SOURCE_DIR)/osfmk/kern/clock.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include clock_oldops.d
clock_oldops.o: $(SOURCE_DIR)/osfmk/kern/clock_oldops.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include coalition.d
coalition.o: $(SOURCE_DIR)/osfmk/kern/coalition.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include counters.d
counters.o: $(SOURCE_DIR)/osfmk/kern/counters.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include debug.d
debug.o: $(SOURCE_DIR)/osfmk/kern/debug.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include energy_perf.d
energy_perf.o: $(SOURCE_DIR)/osfmk/kern/energy_perf.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include exception.d
exception.o: $(SOURCE_DIR)/osfmk/kern/exception.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include extmod_statistics.d
extmod_statistics.o: $(SOURCE_DIR)/osfmk/kern/extmod_statistics.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include host.d
host.o: $(SOURCE_DIR)/osfmk/kern/host.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include host_notify.d
host_notify.o: $(SOURCE_DIR)/osfmk/kern/host_notify.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include ipc_clock.d
ipc_clock.o: $(SOURCE_DIR)/osfmk/kern/ipc_clock.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include ipc_host.d
ipc_host.o: $(SOURCE_DIR)/osfmk/kern/ipc_host.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include ipc_kobject.d
ipc_kobject.o: $(SOURCE_DIR)/osfmk/kern/ipc_kobject.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include ipc_mig.d
ipc_mig.o: $(SOURCE_DIR)/osfmk/kern/ipc_mig.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include ipc_misc.d
ipc_misc.o: $(SOURCE_DIR)/osfmk/kern/ipc_misc.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include ipc_sync.d
ipc_sync.o: $(SOURCE_DIR)/osfmk/kern/ipc_sync.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include ipc_tt.d
ipc_tt.o: $(SOURCE_DIR)/osfmk/kern/ipc_tt.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include kalloc.d
kalloc.o: $(SOURCE_DIR)/osfmk/kern/kalloc.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include ktrace_background_notify.d
ktrace_background_notify.o: $(SOURCE_DIR)/osfmk/kern/ktrace_background_notify.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include ledger.d
ledger.o: $(SOURCE_DIR)/osfmk/kern/ledger.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include locks.d
locks.o: $(SOURCE_DIR)/osfmk/kern/locks.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include tlock.d
tlock.o: $(SOURCE_DIR)/osfmk/kern/tlock.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include ltable.d
ltable.o: $(SOURCE_DIR)/osfmk/kern/ltable.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include mach_node.d
mach_node.o: $(SOURCE_DIR)/osfmk/kern/mach_node.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include machine.d
machine.o: $(SOURCE_DIR)/osfmk/kern/machine.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include mk_sp.d
mk_sp.o: $(SOURCE_DIR)/osfmk/kern/mk_sp.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include mk_timer.d
mk_timer.o: $(SOURCE_DIR)/osfmk/kern/mk_timer.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include mpsc_queue.d
mpsc_queue.o: $(SOURCE_DIR)/osfmk/kern/mpsc_queue.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include page_decrypt.d
page_decrypt.o: $(SOURCE_DIR)/osfmk/kern/page_decrypt.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include printf.d
printf.o: $(SOURCE_DIR)/osfmk/kern/printf.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include priority.d
priority.o: $(SOURCE_DIR)/osfmk/kern/priority.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include processor.d
processor.o: $(SOURCE_DIR)/osfmk/kern/processor.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include restartable.d
restartable.o: $(SOURCE_DIR)/osfmk/kern/restartable.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include sched_average.d
sched_average.o: $(SOURCE_DIR)/osfmk/kern/sched_average.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include sched_amp.d
sched_amp.o: $(SOURCE_DIR)/osfmk/kern/sched_amp.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include sched_amp_common.d
sched_amp_common.o: $(SOURCE_DIR)/osfmk/kern/sched_amp_common.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include sched_dualq.d
sched_dualq.o: $(SOURCE_DIR)/osfmk/kern/sched_dualq.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include sched_prim.d
sched_prim.o: $(SOURCE_DIR)/osfmk/kern/sched_prim.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include sched_proto.d
sched_proto.o: $(SOURCE_DIR)/osfmk/kern/sched_proto.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include sched_traditional.d
sched_traditional.o: $(SOURCE_DIR)/osfmk/kern/sched_traditional.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include sched_grrr.d
sched_grrr.o: $(SOURCE_DIR)/osfmk/kern/sched_grrr.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include sched_multiq.d
sched_multiq.o: $(SOURCE_DIR)/osfmk/kern/sched_multiq.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include sfi.d
sfi.o: $(SOURCE_DIR)/osfmk/kern/sfi.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include stack.d
stack.o: $(SOURCE_DIR)/osfmk/kern/stack.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include startup.d
startup.o: $(SOURCE_DIR)/osfmk/kern/startup.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include sync_lock.d
sync_lock.o: $(SOURCE_DIR)/osfmk/kern/sync_lock.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include sync_sema.d
sync_sema.o: $(SOURCE_DIR)/osfmk/kern/sync_sema.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include syscall_emulation.d
syscall_emulation.o: $(SOURCE_DIR)/osfmk/kern/syscall_emulation.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include syscall_subr.d
syscall_subr.o: $(SOURCE_DIR)/osfmk/kern/syscall_subr.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include syscall_sw.d
syscall_sw.o: $(SOURCE_DIR)/osfmk/kern/syscall_sw.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include sysdiagnose.d
sysdiagnose.o: $(SOURCE_DIR)/osfmk/kern/sysdiagnose.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include task.d
task.o: $(SOURCE_DIR)/osfmk/kern/task.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include task_policy.d
task_policy.o: $(SOURCE_DIR)/osfmk/kern/task_policy.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include task_swap.d
task_swap.o: $(SOURCE_DIR)/osfmk/kern/task_swap.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include test_lock.d
test_lock.o: $(SOURCE_DIR)/osfmk/kern/test_lock.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include test_mpsc_queue.d
test_mpsc_queue.o: $(SOURCE_DIR)/osfmk/kern/test_mpsc_queue.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include thread.d
thread.o: $(SOURCE_DIR)/osfmk/kern/thread.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include thread_act.d
thread_act.o: $(SOURCE_DIR)/osfmk/kern/thread_act.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include thread_call.d
thread_call.o: $(SOURCE_DIR)/osfmk/kern/thread_call.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include thread_group.d
thread_group.o: $(SOURCE_DIR)/osfmk/kern/thread_group.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include thread_policy.d
thread_policy.o: $(SOURCE_DIR)/osfmk/kern/thread_policy.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include timer.d
timer.o: $(SOURCE_DIR)/osfmk/kern/timer.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include timer_call.d
timer_call.o: $(SOURCE_DIR)/osfmk/kern/timer_call.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include turnstile.d
turnstile.o: $(SOURCE_DIR)/osfmk/kern/turnstile.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include ux_handler.d
ux_handler.o: $(SOURCE_DIR)/osfmk/kern/ux_handler.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include waitq.d
waitq.o: $(SOURCE_DIR)/osfmk/kern/waitq.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include work_interval.d
work_interval.o: $(SOURCE_DIR)/osfmk/kern/work_interval.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include zalloc.d
zalloc.o: $(SOURCE_DIR)/osfmk/kern/zalloc.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include zcache.d
zcache.o: $(SOURCE_DIR)/osfmk/kern/zcache.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include gzalloc.d
gzalloc.o: $(SOURCE_DIR)/osfmk/kern/gzalloc.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include bsd_kern.d
bsd_kern.o: $(SOURCE_DIR)/osfmk/kern/bsd_kern.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include hibernate.d
hibernate.o: $(SOURCE_DIR)/osfmk/kern/hibernate.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include remote_time.d
remote_time.o: $(SOURCE_DIR)/osfmk/kern/remote_time.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include memset_s.d
memset_s.o: $(SOURCE_DIR)/osfmk/kern/memset_s.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include copyout_shim.d
copyout_shim.o: $(SOURCE_DIR)/osfmk/kern/copyout_shim.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include suid_cred.d
suid_cred.o: $(SOURCE_DIR)/osfmk/kern/suid_cred.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include clock_server.d
clock_server.o: mach/clock_server.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include clock_priv_server.d
clock_priv_server.o: mach/clock_priv_server.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include clock_reply_user.d
clock_reply_user.o: mach/clock_reply_user.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include exc_user.d
exc_user.o: mach/exc_user.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include exc_server.d
exc_server.o: mach/exc_server.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include mach_eventlink_server.d
mach_eventlink_server.o: mach/mach_eventlink_server.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include host_priv_server.d
host_priv_server.o: mach/host_priv_server.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include host_security_server.d
host_security_server.o: mach/host_security_server.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include ktrace_background_user.d
ktrace_background_user.o: mach/ktrace_background_user.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include lock_set_server.d
lock_set_server.o: mach/lock_set_server.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include mach_exc_user.d
mach_exc_user.o: mach/mach_exc_user.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include mach_exc_server.d
mach_exc_server.o: mach/mach_exc_server.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include mach_host_server.d
mach_host_server.o: mach/mach_host_server.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include mach_notify_user.d
mach_notify_user.o: mach/mach_notify_user.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include mach_port_server.d
mach_port_server.o: mach/mach_port_server.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include mach_vm_server.d
mach_vm_server.o: mach/mach_vm_server.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include mach_voucher_server.d
mach_voucher_server.o: mach/mach_voucher_server.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include mach_voucher_attr_control_server.d
mach_voucher_attr_control_server.o: mach/mach_voucher_attr_control_server.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include memory_entry_server.d
memory_entry_server.o: mach/memory_entry_server.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include memory_object_control_server.d
memory_object_control_server.o: mach/memory_object_control_server.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include resource_notify_user.d
resource_notify_user.o: mach/resource_notify_user.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include restartable_server.d
restartable_server.o: mach/restartable_server.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include upl_server.d
upl_server.o: mach/upl_server.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include audit_triggers_user.d
audit_triggers_user.o: mach/audit_triggers_user.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include task_access_user.d
task_access_user.o: mach/task_access_user.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include corpse.d
corpse.o: $(SOURCE_DIR)/osfmk/corpses/corpse.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/corpses/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/corpses/${C_RULE_4B})
-include kern_cdata.d
kern_cdata.o: $(SOURCE_DIR)/osfmk/kern/kern_cdata.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include kernel_tests.d
kernel_tests.o: $(SOURCE_DIR)/osfmk/tests/kernel_tests.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/tests/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/tests/${C_RULE_4B})
-include ktest.d
ktest.o: $(SOURCE_DIR)/osfmk/tests/ktest.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/tests/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/tests/${C_RULE_4B})
-include ktest_accessor.d
ktest_accessor.o: $(SOURCE_DIR)/osfmk/tests/ktest_accessor.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/tests/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/tests/${C_RULE_4B})
-include ktest_emit.d
ktest_emit.o: $(SOURCE_DIR)/osfmk/tests/ktest_emit.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/tests/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/tests/${C_RULE_4B})
-include ktest_global.d
ktest_global.o: $(SOURCE_DIR)/osfmk/tests/ktest_global.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/tests/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/tests/${C_RULE_4B})
-include pmap_tests.d
pmap_tests.o: $(SOURCE_DIR)/osfmk/tests/pmap_tests.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/tests/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/tests/${C_RULE_4B})
-include ptrauth_data_tests.d
ptrauth_data_tests.o: $(SOURCE_DIR)/osfmk/tests/ptrauth_data_tests.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/tests/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/tests/${C_RULE_4B})
-include bitmap_test.d
bitmap_test.o: $(SOURCE_DIR)/osfmk/tests/bitmap_test.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/tests/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/tests/${C_RULE_4B})
-include test_thread_call.d
test_thread_call.o: $(SOURCE_DIR)/osfmk/tests/test_thread_call.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/tests/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/tests/${C_RULE_4B})
-include vfp_state_test.d
vfp_state_test.o: $(SOURCE_DIR)/osfmk/tests/vfp_state_test.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/tests/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/tests/${C_RULE_4B})
-include telemetry_notification_user.d
telemetry_notification_user.o: mach/telemetry_notification_user.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include bank.d
bank.o: $(SOURCE_DIR)/osfmk/bank/bank.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/bank/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/bank/${C_RULE_4B})
-include atm.d
atm.o: $(SOURCE_DIR)/osfmk/atm/atm.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/atm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/atm/${C_RULE_4B})
-include atm_notification_user.d
atm_notification_user.o: atm/atm_notification_user.c
	${C_RULE_0}
	${C_RULE_1A}atm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}atm/${C_RULE_4B})
-include ipc_pthread_priority.d
ipc_pthread_priority.o: $(SOURCE_DIR)/osfmk/voucher/ipc_pthread_priority.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/voucher/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/voucher/${C_RULE_4B})
-include coalition_notification_user.d
coalition_notification_user.o: mach/coalition_notification_user.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include sysdiagnose_notification_user.d
sysdiagnose_notification_user.o: mach/sysdiagnose_notification_user.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include vfs_nspace_user.d
vfs_nspace_user.o: mach/vfs_nspace_user.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include fairplayd_notification_user.d
fairplayd_notification_user.o: mach/fairplayd_notification_user.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include arcade_upcall_user.d
arcade_upcall_user.o: mach/arcade_upcall_user.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include arcade_register_server.d
arcade_register_server.o: mach/arcade_register_server.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include processor_server.d
processor_server.o: mach/processor_server.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include processor_set_server.d
processor_set_server.o: mach/processor_set_server.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include task_server.d
task_server.o: mach/task_server.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include thread_act_server.d
thread_act_server.o: mach/thread_act_server.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include vm32_map_server.d
vm32_map_server.o: mach/vm32_map_server.c
	${C_RULE_0}
	${C_RULE_1A}mach/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}mach/${C_RULE_4B})
-include bsd_vm.d
bsd_vm.o: $(SOURCE_DIR)/osfmk/vm/bsd_vm.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include vm_compressor.d
vm_compressor.o: $(SOURCE_DIR)/osfmk/vm/vm_compressor.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include vm_compressor_pager.d
vm_compressor_pager.o: $(SOURCE_DIR)/osfmk/vm/vm_compressor_pager.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include vm_compressor_backing_store.d
vm_compressor_backing_store.o: $(SOURCE_DIR)/osfmk/vm/vm_compressor_backing_store.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include vm_compressor_algorithms.d
vm_compressor_algorithms.o: $(SOURCE_DIR)/osfmk/vm/vm_compressor_algorithms.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include lz4.d
lz4.o: $(SOURCE_DIR)/osfmk/vm/lz4.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include device_vm.d
device_vm.o: $(SOURCE_DIR)/osfmk/vm/device_vm.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include memory_object.d
memory_object.o: $(SOURCE_DIR)/osfmk/vm/memory_object.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include vm_debug.d
vm_debug.o: $(SOURCE_DIR)/osfmk/vm/vm_debug.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include vm_fault.d
vm_fault.o: $(SOURCE_DIR)/osfmk/vm/vm_fault.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include vm_init.d
vm_init.o: $(SOURCE_DIR)/osfmk/vm/vm_init.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include vm_kern.d
vm_kern.o: $(SOURCE_DIR)/osfmk/vm/vm_kern.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include vm_map.d
vm_map.o: $(SOURCE_DIR)/osfmk/vm/vm_map.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include vm_map_store.d
vm_map_store.o: $(SOURCE_DIR)/osfmk/vm/vm_map_store.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include vm_map_store_ll.d
vm_map_store_ll.o: $(SOURCE_DIR)/osfmk/vm/vm_map_store_ll.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include vm_map_store_rb.d
vm_map_store_rb.o: $(SOURCE_DIR)/osfmk/vm/vm_map_store_rb.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include vm_object.d
vm_object.o: $(SOURCE_DIR)/osfmk/vm/vm_object.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include vm_pageout.d
vm_pageout.o: $(SOURCE_DIR)/osfmk/vm/vm_pageout.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include vm_purgeable.d
vm_purgeable.o: $(SOURCE_DIR)/osfmk/vm/vm_purgeable.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include vm_resident.d
vm_resident.o: $(SOURCE_DIR)/osfmk/vm/vm_resident.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include vm_shared_region.d
vm_shared_region.o: $(SOURCE_DIR)/osfmk/vm/vm_shared_region.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include vm_shared_region_pager.d
vm_shared_region_pager.o: $(SOURCE_DIR)/osfmk/vm/vm_shared_region_pager.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include vm_swapfile_pager.d
vm_swapfile_pager.o: $(SOURCE_DIR)/osfmk/vm/vm_swapfile_pager.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include vm_tests.d
vm_tests.o: $(SOURCE_DIR)/osfmk/vm/vm_tests.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include vm_user.d
vm_user.o: $(SOURCE_DIR)/osfmk/vm/vm_user.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include vm32_user.d
vm32_user.o: $(SOURCE_DIR)/osfmk/vm/vm32_user.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include iokit_rpc.d
iokit_rpc.o: $(SOURCE_DIR)/osfmk/device/iokit_rpc.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/device/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/device/${C_RULE_4B})
-include device_server.d
device_server.o: device/device_server.c
	${C_RULE_0}
	${C_RULE_1A}device/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}device/${C_RULE_4B})
-include device_init.d
device_init.o: $(SOURCE_DIR)/osfmk/device/device_init.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/device/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/device/${C_RULE_4B})
-include kext_alloc.d
kext_alloc.o: $(SOURCE_DIR)/osfmk/kern/kext_alloc.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include kmod.d
kmod.o: $(SOURCE_DIR)/osfmk/kern/kmod.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include subrs.d
subrs.o: $(SOURCE_DIR)/osfmk/device/subrs.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/device/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/device/${C_RULE_4B})
-include kperf.d
kperf.o: $(SOURCE_DIR)/osfmk/kperf/kperf.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kperf/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kperf/${C_RULE_4B})
-include action.d
action.o: $(SOURCE_DIR)/osfmk/kperf/action.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kperf/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kperf/${C_RULE_4B})
-include callstack.d
callstack.o: $(SOURCE_DIR)/osfmk/kperf/callstack.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kperf/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kperf/${C_RULE_4B})
-include pet.d
pet.o: $(SOURCE_DIR)/osfmk/kperf/pet.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kperf/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kperf/${C_RULE_4B})
-include thread_samplers.d
thread_samplers.o: $(SOURCE_DIR)/osfmk/kperf/thread_samplers.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kperf/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kperf/${C_RULE_4B})
-include task_samplers.d
task_samplers.o: $(SOURCE_DIR)/osfmk/kperf/task_samplers.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kperf/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kperf/${C_RULE_4B})
-include meminfo.d
meminfo.o: $(SOURCE_DIR)/osfmk/kperf/meminfo.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kperf/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kperf/${C_RULE_4B})
-include kptimer.d
kptimer.o: $(SOURCE_DIR)/osfmk/kperf/kptimer.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kperf/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kperf/${C_RULE_4B})
-include kperf_kpc.d
kperf_kpc.o: $(SOURCE_DIR)/osfmk/kperf/kperf_kpc.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kperf/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kperf/${C_RULE_4B})
-include kdebug_trigger.d
kdebug_trigger.o: $(SOURCE_DIR)/osfmk/kperf/kdebug_trigger.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kperf/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kperf/${C_RULE_4B})
-include lazy.d
lazy.o: $(SOURCE_DIR)/osfmk/kperf/lazy.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kperf/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kperf/${C_RULE_4B})
-include kpc_thread.d
kpc_thread.o: $(SOURCE_DIR)/osfmk/kern/kpc_thread.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include kpc_common.d
kpc_common.o: $(SOURCE_DIR)/osfmk/kern/kpc_common.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include serial_general.d
serial_general.o: $(SOURCE_DIR)/osfmk/console/serial_general.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/console/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/console/${C_RULE_4B})
-include serial_console.d
serial_console.o: $(SOURCE_DIR)/osfmk/console/serial_console.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/console/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/console/${C_RULE_4B})
-include video_scroll.d
video_scroll.o: $(SOURCE_DIR)/osfmk/console/video_scroll.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/console/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/console/${C_RULE_4B})
-include video_console.d
video_console.o: $(SOURCE_DIR)/osfmk/console/video_console.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/console/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/console/${C_RULE_4B})
-include telemetry.d
telemetry.o: $(SOURCE_DIR)/osfmk/kern/telemetry.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include cc_clear.d
cc_clear.o: $(SOURCE_DIR)/osfmk/corecrypto/cc_clear.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_4B})
-include cc_cmp_safe.d
cc_cmp_safe.o: $(SOURCE_DIR)/osfmk/corecrypto/cc_cmp_safe.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_4B})
-include cc_abort.d
cc_abort.o: $(SOURCE_DIR)/osfmk/corecrypto/cc_abort.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_4B})
-include ccdrbg_nisthmac.d
ccdrbg_nisthmac.o: $(SOURCE_DIR)/osfmk/corecrypto/ccdrbg_nisthmac.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_4B})
-include ccdigest_init.d
ccdigest_init.o: $(SOURCE_DIR)/osfmk/corecrypto/ccdigest_init.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_4B})
-include ccdigest_update.d
ccdigest_update.o: $(SOURCE_DIR)/osfmk/corecrypto/ccdigest_update.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_4B})
-include cchmac.d
cchmac.o: $(SOURCE_DIR)/osfmk/corecrypto/cchmac.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_4B})
-include cchmac_init.d
cchmac_init.o: $(SOURCE_DIR)/osfmk/corecrypto/cchmac_init.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_4B})
-include cchmac_update.d
cchmac_update.o: $(SOURCE_DIR)/osfmk/corecrypto/cchmac_update.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_4B})
-include cchmac_final.d
cchmac_final.o: $(SOURCE_DIR)/osfmk/corecrypto/cchmac_final.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_4B})
-include ccdigest_final_64be.d
ccdigest_final_64be.o: $(SOURCE_DIR)/osfmk/corecrypto/ccdigest_final_64be.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_4B})
-include ccsha256_di.d
ccsha256_di.o: $(SOURCE_DIR)/osfmk/corecrypto/ccsha256_di.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_4B})
-include ccsha256_initial_state.d
ccsha256_initial_state.o: $(SOURCE_DIR)/osfmk/corecrypto/ccsha256_initial_state.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_4B})
-include ccsha256_K.d
ccsha256_K.o: $(SOURCE_DIR)/osfmk/corecrypto/ccsha256_K.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_4B})
-include ccsha256_ltc_compress.d
ccsha256_ltc_compress.o: $(SOURCE_DIR)/osfmk/corecrypto/ccsha256_ltc_compress.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_4B})
-include ccsha256_ltc_di.d
ccsha256_ltc_di.o: $(SOURCE_DIR)/osfmk/corecrypto/ccsha256_ltc_di.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/corecrypto/${C_RULE_4B})
-include prng_random.d
prng_random.o: $(SOURCE_DIR)/osfmk/prng/prng_random.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/prng/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/prng/${C_RULE_4B})
-include entropy.d
entropy.o: $(SOURCE_DIR)/osfmk/prng/entropy.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/prng/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/prng/${C_RULE_4B})
-include vm_apple_protect.d
vm_apple_protect.o: $(SOURCE_DIR)/osfmk/vm/vm_apple_protect.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/vm/${C_RULE_4B})
-include pmap.d
pmap.o: $(SOURCE_DIR)/osfmk/x86_64/pmap.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/x86_64/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/x86_64/${C_RULE_4B})
-include pmap_x86_common.d
pmap_x86_common.o: $(SOURCE_DIR)/osfmk/i386/pmap_x86_common.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include pmap_common.d
pmap_common.o: $(SOURCE_DIR)/osfmk/i386/pmap_common.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include pmap_pcid.d
pmap_pcid.o: $(SOURCE_DIR)/osfmk/x86_64/pmap_pcid.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/x86_64/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/x86_64/${C_RULE_4B})
-include pal_routines.d
pal_routines.o: $(SOURCE_DIR)/osfmk/i386/pal_routines.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include pal_routines_asm.d
pal_routines_asm.o: $(SOURCE_DIR)/osfmk/x86_64/pal_routines_asm.s
	${S_RULE_0}
	${S_RULE_1A}$(SOURCE_DIR)/osfmk/x86_64/${S_RULE_1B}
	${S_RULE_2}
-include bsd_i386.d
bsd_i386.o: $(SOURCE_DIR)/osfmk/i386/bsd_i386.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include bsd_i386_native.d
bsd_i386_native.o: $(SOURCE_DIR)/osfmk/i386/bsd_i386_native.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include machdep_call.d
machdep_call.o: $(SOURCE_DIR)/osfmk/i386/machdep_call.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include boot_pt.d
boot_pt.o: $(SOURCE_DIR)/osfmk/x86_64/boot_pt.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/x86_64/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/x86_64/${C_RULE_4B})
-include mp_desc.d
mp_desc.o: $(SOURCE_DIR)/osfmk/i386/mp_desc.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include gdt.d
gdt.o: $(SOURCE_DIR)/osfmk/i386/gdt.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include start.d
start.o: $(SOURCE_DIR)/osfmk/x86_64/start.s
	${S_RULE_0}
	${S_RULE_1A}$(SOURCE_DIR)/osfmk/x86_64/${S_RULE_1B}
	${S_RULE_2}
-include bcopy.d
bcopy.o: $(SOURCE_DIR)/osfmk/x86_64/bcopy.s
	${S_RULE_0}
	${S_RULE_1A}$(SOURCE_DIR)/osfmk/x86_64/${S_RULE_1B}
	${S_RULE_2}
-include bzero.d
bzero.o: $(SOURCE_DIR)/osfmk/x86_64/bzero.s
	${S_RULE_0}
	${S_RULE_1A}$(SOURCE_DIR)/osfmk/x86_64/${S_RULE_1B}
	${S_RULE_2}
-include WKdmDecompress_new.d
WKdmDecompress_new.o: $(SOURCE_DIR)/osfmk/x86_64/WKdmDecompress_new.s
	${S_RULE_0}
	${S_RULE_1A}$(SOURCE_DIR)/osfmk/x86_64/${S_RULE_1B}
	${S_RULE_2}
-include WKdmCompress_new.d
WKdmCompress_new.o: $(SOURCE_DIR)/osfmk/x86_64/WKdmCompress_new.s
	${S_RULE_0}
	${S_RULE_1A}$(SOURCE_DIR)/osfmk/x86_64/${S_RULE_1B}
	${S_RULE_2}
-include WKdmData_new.d
WKdmData_new.o: $(SOURCE_DIR)/osfmk/x86_64/WKdmData_new.s
	${S_RULE_0}
	${S_RULE_1A}$(SOURCE_DIR)/osfmk/x86_64/${S_RULE_1B}
	${S_RULE_2}
-include lz4_decode_x86_64.d
lz4_decode_x86_64.o: $(SOURCE_DIR)/osfmk/x86_64/lz4_decode_x86_64.s
	${S_RULE_0}
	${S_RULE_1A}$(SOURCE_DIR)/osfmk/x86_64/${S_RULE_1B}
	${S_RULE_2}
-include cpu.d
cpu.o: $(SOURCE_DIR)/osfmk/i386/cpu.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include cpuid.d
cpuid.o: $(SOURCE_DIR)/osfmk/i386/cpuid.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include cpu_threads.d
cpu_threads.o: $(SOURCE_DIR)/osfmk/i386/cpu_threads.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include cpu_topology.d
cpu_topology.o: $(SOURCE_DIR)/osfmk/i386/cpu_topology.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include i386_timer.d
i386_timer.o: $(SOURCE_DIR)/osfmk/i386/i386_timer.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include fpu.d
fpu.o: $(SOURCE_DIR)/osfmk/i386/fpu.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include fp_simd.d
fp_simd.o: $(SOURCE_DIR)/osfmk/i386/fp_simd.s
	${S_RULE_0}
	${S_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${S_RULE_1B}
	${S_RULE_2}
-include i386_lock.d
i386_lock.o: $(SOURCE_DIR)/osfmk/i386/i386_lock.s
	${S_RULE_0}
	${S_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${S_RULE_1B}
	${S_RULE_2}
-include i386_init.d
i386_init.o: $(SOURCE_DIR)/osfmk/i386/i386_init.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include i386_vm_init.d
i386_vm_init.o: $(SOURCE_DIR)/osfmk/i386/i386_vm_init.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include io_map.d
io_map.o: $(SOURCE_DIR)/osfmk/i386/io_map.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include ktss.d
ktss.o: $(SOURCE_DIR)/osfmk/i386/ktss.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include ldt.d
ldt.o: $(SOURCE_DIR)/osfmk/i386/ldt.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include loose_ends.d
loose_ends.o: $(SOURCE_DIR)/osfmk/x86_64/loose_ends.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/x86_64/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/x86_64/${C_RULE_4B})
-include copyio.d
copyio.o: $(SOURCE_DIR)/osfmk/x86_64/copyio.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/x86_64/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/x86_64/${C_RULE_4B})
-include locks_i386.d
locks_i386.o: $(SOURCE_DIR)/osfmk/i386/locks_i386.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include locks_i386_opt.d
locks_i386_opt.o: $(SOURCE_DIR)/osfmk/i386/locks_i386_opt.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include locore.d
locore.o: $(SOURCE_DIR)/osfmk/x86_64/locore.s
	${S_RULE_0}
	${S_RULE_1A}$(SOURCE_DIR)/osfmk/x86_64/${S_RULE_1B}
	${S_RULE_2}
-include lowmem_vectors.d
lowmem_vectors.o: $(SOURCE_DIR)/osfmk/x86_64/lowmem_vectors.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/x86_64/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/x86_64/${C_RULE_4B})
-include cswitch.d
cswitch.o: $(SOURCE_DIR)/osfmk/x86_64/cswitch.s
	${S_RULE_0}
	${S_RULE_1A}$(SOURCE_DIR)/osfmk/x86_64/${S_RULE_1B}
	${S_RULE_2}
-include machine_routines.d
machine_routines.o: $(SOURCE_DIR)/osfmk/i386/machine_routines.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include machine_routines_asm.d
machine_routines_asm.o: $(SOURCE_DIR)/osfmk/x86_64/machine_routines_asm.s
	${S_RULE_0}
	${S_RULE_1A}$(SOURCE_DIR)/osfmk/x86_64/${S_RULE_1B}
	${S_RULE_2}
-include machine_check.d
machine_check.o: $(SOURCE_DIR)/osfmk/i386/machine_check.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include machine_task.d
machine_task.o: $(SOURCE_DIR)/osfmk/i386/machine_task.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include pcb.d
pcb.o: $(SOURCE_DIR)/osfmk/i386/pcb.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include pcb_native.d
pcb_native.o: $(SOURCE_DIR)/osfmk/i386/pcb_native.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include phys.d
phys.o: $(SOURCE_DIR)/osfmk/i386/phys.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include rtclock.d
rtclock.o: $(SOURCE_DIR)/osfmk/i386/rtclock.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include rtclock_native.d
rtclock_native.o: $(SOURCE_DIR)/osfmk/i386/rtclock_native.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include trap.d
trap.o: $(SOURCE_DIR)/osfmk/i386/trap.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include trap_native.d
trap_native.o: $(SOURCE_DIR)/osfmk/i386/trap_native.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include user_ldt.d
user_ldt.o: $(SOURCE_DIR)/osfmk/i386/user_ldt.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include Diagnostics.d
Diagnostics.o: $(SOURCE_DIR)/osfmk/i386/Diagnostics.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include pmCPU.d
pmCPU.o: $(SOURCE_DIR)/osfmk/i386/pmCPU.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include tsc.d
tsc.o: $(SOURCE_DIR)/osfmk/i386/tsc.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include commpage.d
commpage.o: $(SOURCE_DIR)/osfmk/i386/commpage/commpage.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/commpage/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/commpage/${C_RULE_4B})
-include commpage_asm.d
commpage_asm.o: $(SOURCE_DIR)/osfmk/i386/commpage/commpage_asm.s
	${S_RULE_0}
	${S_RULE_1A}$(SOURCE_DIR)/osfmk/i386/commpage/${S_RULE_1B}
	${S_RULE_2}
-include fifo_queues.d
fifo_queues.o: $(SOURCE_DIR)/osfmk/i386/commpage/fifo_queues.s
	${S_RULE_0}
	${S_RULE_1A}$(SOURCE_DIR)/osfmk/i386/commpage/${S_RULE_1B}
	${S_RULE_2}
-include model_dep.d
model_dep.o: $(SOURCE_DIR)/osfmk/i386/AT386/model_dep.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/AT386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/AT386/${C_RULE_4B})
-include lapic.d
lapic.o: $(SOURCE_DIR)/osfmk/i386/lapic.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include lapic_native.d
lapic_native.o: $(SOURCE_DIR)/osfmk/i386/lapic_native.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include mp.d
mp.o: $(SOURCE_DIR)/osfmk/i386/mp.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include mp_native.d
mp_native.o: $(SOURCE_DIR)/osfmk/i386/mp_native.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include acpi.d
acpi.o: $(SOURCE_DIR)/osfmk/i386/acpi.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include mtrr.d
mtrr.o: $(SOURCE_DIR)/osfmk/i386/mtrr.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include kdp_machdep.d
kdp_machdep.o: $(SOURCE_DIR)/osfmk/kdp/ml/x86_64/kdp_machdep.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kdp/ml/x86_64/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kdp/ml/x86_64/${C_RULE_4B})
-include kdp_vm.d
kdp_vm.o: $(SOURCE_DIR)/osfmk/kdp/ml/x86_64/kdp_vm.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kdp/ml/x86_64/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kdp/ml/x86_64/${C_RULE_4B})
-include kdp_x86_common.d
kdp_x86_common.o: $(SOURCE_DIR)/osfmk/kdp/ml/i386/kdp_x86_common.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kdp/ml/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kdp/ml/i386/${C_RULE_4B})
-include hibernate_i386.d
hibernate_i386.o: $(SOURCE_DIR)/osfmk/i386/hibernate_i386.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include hibernate_restore.d
hibernate_restore.o: $(SOURCE_DIR)/osfmk/i386/hibernate_restore.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include ucode.d
ucode.o: $(SOURCE_DIR)/osfmk/i386/ucode.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include vmx_cpu.d
vmx_cpu.o: $(SOURCE_DIR)/osfmk/i386/vmx/vmx_cpu.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/vmx/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/vmx/${C_RULE_4B})
-include vmx_shims.d
vmx_shims.o: $(SOURCE_DIR)/osfmk/i386/vmx/vmx_shims.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/vmx/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/vmx/${C_RULE_4B})
-include hv_support_kext.d
hv_support_kext.o: $(SOURCE_DIR)/osfmk/kern/hv_support_kext.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/kern/${C_RULE_4B})
-include kpc_x86.d
kpc_x86.o: $(SOURCE_DIR)/osfmk/x86_64/kpc_x86.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/x86_64/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/x86_64/${C_RULE_4B})
-include idt64.d
idt64.o: $(SOURCE_DIR)/osfmk/x86_64/idt64.s
	${S_RULE_0}
	${S_RULE_1A}$(SOURCE_DIR)/osfmk/x86_64/${S_RULE_1B}
	${S_RULE_2}
-include panic_hooks.d
panic_hooks.o: $(SOURCE_DIR)/osfmk/i386/panic_hooks.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include panic_notify.d
panic_notify.o: $(SOURCE_DIR)/osfmk/i386/panic_notify.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/i386/${C_RULE_4B})
-include machine_remote_time.d
machine_remote_time.o: $(SOURCE_DIR)/osfmk/x86_64/machine_remote_time.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/osfmk/x86_64/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/osfmk/x86_64/${C_RULE_4B})

include $(MakeInc_rule)
include $(MakeInc_dir)
