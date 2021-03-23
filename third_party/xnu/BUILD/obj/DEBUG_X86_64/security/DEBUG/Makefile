SOURCE_DIR=/Users/nedwill/dev/sockfuzzer/third_party/xnu
export CONFIG_DEFINES = -DINET -DMACH -DMACH_COMPAT -DMACH_FASTLINK -DNO_DIRECT_RPC -DVLAN -DSIXLOWPAN -DBOND -DIF_FAKE -DIF_HEADLESS -DAH_ALL_CRYPTO -DPF -DPFLOG -DDUMMYNET -DTRAFFIC_MGT -DMULTICAST -DICMP_BANDLIM -DIFNET_INPUT_SANITY_CHK -DMULTIPATH -DMPTCP -DSYSV_SEM -DSYSV_MSG -DSYSV_SHM -DPSYNCH -DFLOW_DIVERT -DNECP -DCONTENT_FILTER -DPACKET_MANGLER -DSIXLOWPAN -DOLD_SEMWAIT_SIGNAL -DSOCKETS -DSENDFILE -DNETWORKING -DCONFIG_IMAGEBOOT -DCONFIG_MBUF_JUMBO -DCONFIG_IMAGEBOOT_CHUNKLIST -DCONFIG_WORKQUEUE -DCONFIG_WORKLOOP_DEBUG -DFIFO -DFDESC -DDEVFS -DNULLFS -DBINDFS -DFS_COMPRESSION -DCONFIG_DEV_KMEM -DQUOTA -DNAMEDSTREAMS -DCONFIG_APPLEDOUBLE -DCONFIG_VOLFS -DCONFIG_IMGSRC_ACCESS -DCONFIG_TRIGGERS -DCONFIG_EXT_RESOLVER -DCONFIG_SEARCHFS -DCONFIG_MNT_SUID -DCONFIG_MNT_ROOTSNAP -DCONFIG_ROSV_STARTUP -DCONFIG_FIRMLINKS -DCONFIG_MOUNT_VM -DCONFIG_MOUNT_PREBOOTRECOVERY -DCONFIG_DATALESS_FILES -DCONFIG_BASESYSTEMROOT -DNFSCLIENT -DNFSSERVER -DCONFIG_NFS_GSS -DCONFIG_NFS4 -DCONFIG_NETBOOT -DIPSEC -DIPSEC_ESP -DCRYPTO -DCRYPTO_SHA2 -DENCRYPTED_SWAP -DCONFIG_IMG4 -DZLIB -DIF_BRIDGE -DCONFIG_KN_HASHSIZE="64" -DCONFIG_VNODES="263168" -DCONFIG_NC_HASH="4096" -DCONFIG_VFS_NAMES="4096" -DCONFIG_MAX_CLUSTERS="8" -DCONFIG_MIN_NBUF="256" -DCONFIG_MIN_NIOBUF="128" -DCONFIG_NMBCLUSTERS="((1024 * 512) / MCLBYTES)" -DCONFIG_TCBHASHSIZE="4096" -DCONFIG_ICMP_BANDLIM="250" -DCONFIG_AIO_MAX="90" -DCONFIG_AIO_PROCESS_MAX="16" -DCONFIG_AIO_THREAD_COUNT="4" -DCONFIG_MAXVIFS="32" -DCONFIG_MFCTBLSIZ="256" -DCONFIG_MSG_BSIZE_REL="16384" -DCONFIG_MSG_BSIZE_DEV="131072" -DCONFIG_MSG_BSIZE="CONFIG_MSG_BSIZE_DEV" -DCONFIG_IPC_TABLE_ENTRIES_STEPS="256" -DCONFIG_VSPRINTF -DCONFIG_DYNAMIC_CODE_SIGNING -DCONFIG_CODE_DECRYPTION -DCONFIG_PROTECT -DCONFIG_KEYPAGE_WP -DCONFIG_MEMORYSTATUS -DCONFIG_DIRTYSTATUS_TRACKING -DCONFIG_LTABLE_STATS -DCONFIG_LTABLE_DEBUG -DCONFIG_WAITQ_STATS -DCONFIG_WAITQ_DEBUG -DCONFIG_PHYS_WRITE_ACCT -DVM_PRESSURE_EVENTS -DCONFIG_BACKGROUND_QUEUE -DCONFIG_LEDGER_INTERVAL_MAX -DCONFIG_IOSCHED -DIMPORTANCE_INHERITANCE -DIMPORTANCE_TRACE -DIMPORTANCE_DEBUG -DCONFIG_TELEMETRY -DCONFIG_PROC_UUID_POLICY -DCONFIG_COREDUMP -DCONFIG_VNGUARD -DHIBERNATION -DIOKITCPP -DIOKITSTATS -DIOTRACKING -DCONFIG_SLEEP -DCONFIG_MAX_THREADS="500" -DLIBKERNCPP -DCONFIG_BLOCKS -DCONFIG_KEC_FIPS -DCONFIG_KEXT_BASEMENT -DCONFIG_PERSONAS -DCONFIG_AUDIT -DCONFIG_ARCADE -DCONFIG_SETUID -DCONFIG_KAS_INFO -DCONFIG_ZALLOC_SEQUESTER -DMACH_ASSERT -DMACH_DEBUG -DMACH_IPC_DEBUG -DMACH_VM_DEBUG -DMACH_MP_DEBUG -DCONFIG_ZCACHE -DCONFIG_ZLEAKS -DCONFIG_TASK_ZONE_INFO -DMACH_LDEBUG -DCONFIG_DTRACE -DLOCK_STATS -DKPERF -DKPC -DPGO -DMACH_COUNTERS -DDEBUG -DMACH_BSD -DIOKIT -DCONFIG_THREAD_MAX="2560" -DCONFIG_TASK_MAX="1024" -DCONFIG_ZONE_MAP_MIN="120586240" -DCONFIG_ZLEAK_ALLOCATION_MAP_NUM="16384" -DCONFIG_ZLEAK_TRACE_MAP_NUM="8192" -DCONFIG_SCHED_TRADITIONAL -DCONFIG_SCHED_PROTO -DCONFIG_SCHED_GRRR -DCONFIG_SCHED_GRRR_CORE -DCONFIG_SCHED_MULTIQ -DCONFIG_SCHED_TIMESHARE_CORE -DCONFIG_SCHED_SFI -DCONFIG_GZALLOC -DMACH_KDP -DCONFIG_SERIAL_KDP -DCONFIG_KDP_INTERACTIVE_DEBUGGING -DCONFIG_TASKWATCH -DCONFIG_XNUPOST -DCONFIG_ATM -DCONFIG_COALITIONS -DCONFIG_SYSDIAGNOSE -DCONFIG_CSR -DSERIAL_CONSOLE -DVIDEO_CONSOLE -DCONFIG_REQUIRES_U32_MUNGING -DCOPYOUT_SHIM -DCONFIG_MACH_BRIDGE_SEND_TIME -DCONFIG_32BIT_TELEMETRY -DCONFIG_DELAY_IDLE_SLEEP -DCONFIG_PROC_UDATA_STORAGE -DPAL_I386 -DCONFIG_MCA -DCONFIG_VMX -DCONFIG_MTRR -DCONFIG_MACF_LAZY_VNODE_LABELS -DHYPERVISOR -DCONFIG_MACH_APPROXIMATE_TIME
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
CFLAGS+= -include meta_features.h -DBSD_KERNEL_PRIVATE
SFLAGS+= -include meta_features.h

#
# INCFLAGS to include security prototypes
#
INCFLAGS_MAKEFILE= -I$(SOURCE)/..

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

OBJS=mac_audit.o mac_base.o mac_data.o mac_label.o mac_process.o \
	mac_vfs.o mac_vfs_subr.o mac_system.o mac_sysv_sem.o \
	mac_sysv_shm.o mac_sysv_msg.o mac_posix_sem.o mac_posix_shm.o \
	mac_socket.o mac_pipe.o mac_iokit.o mac_file.o mac_priv.o \
	mac_pty.o mac_kext.o mac_mach.o 

CFILES=\
	$(SOURCE_DIR)/security/mac_audit.c \
	$(SOURCE_DIR)/security/mac_base.c \
	$(SOURCE_DIR)/security/mac_data.c \
	$(SOURCE_DIR)/security/mac_label.c \
	$(SOURCE_DIR)/security/mac_process.c \
	$(SOURCE_DIR)/security/mac_vfs.c \
	$(SOURCE_DIR)/security/mac_vfs_subr.c \
	$(SOURCE_DIR)/security/mac_system.c \
	$(SOURCE_DIR)/security/mac_sysv_sem.c \
	$(SOURCE_DIR)/security/mac_sysv_shm.c \
	$(SOURCE_DIR)/security/mac_sysv_msg.c \
	$(SOURCE_DIR)/security/mac_posix_sem.c \
	$(SOURCE_DIR)/security/mac_posix_shm.c \
	$(SOURCE_DIR)/security/mac_socket.c \
	$(SOURCE_DIR)/security/mac_pipe.c \
	$(SOURCE_DIR)/security/mac_iokit.c \
	$(SOURCE_DIR)/security/mac_file.c \
	$(SOURCE_DIR)/security/mac_priv.c \
	$(SOURCE_DIR)/security/mac_pty.c \
	$(SOURCE_DIR)/security/mac_kext.c \
	$(SOURCE_DIR)/security/mac_mach.c 
COBJS=mac_audit.o mac_base.o mac_data.o mac_label.o mac_process.o \
	mac_vfs.o mac_vfs_subr.o mac_system.o mac_sysv_sem.o \
	mac_sysv_shm.o mac_sysv_msg.o mac_posix_sem.o mac_posix_shm.o \
	mac_socket.o mac_pipe.o mac_iokit.o mac_file.o mac_priv.o \
	mac_pty.o mac_kext.o mac_mach.o 

CXXFILES=
CXXOBJS=

SFILES=
SOBJS=

######################################################################
#BEGIN	Machine dependent Makefile fragment for x86_64
######################################################################

######################################################################
#END	Machine dependent Makefile fragment for x86_64
######################################################################

#
# Diagnostic opt-outs.  We need to make this list empty.
#
# DO NOT ADD MORE HERE.
#
# -Wno-cast-align
mac_base.o_CFLAGS_ADD += -Wno-cast-align
# -Wno-shorten-64-to-32
mac_audit.o_CFLAGS_ADD += -Wno-shorten-64-to-32
mac_base.o_CFLAGS_ADD += -Wno-shorten-64-to-32
mac_process.o_CFLAGS_ADD += -Wno-shorten-64-to-32
# -Wno-sign-conversion
mac_base.o_CFLAGS_ADD += -Wno-sign-conversion
mac_mach.o_CFLAGS_ADD += -Wno-sign-conversion
mac_vfs.o_CFLAGS_ADD += -Wno-sign-conversion
mac_vfs_subr.o_CFLAGS_ADD += -Wno-sign-conversion

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
	@$(LOG_LDFILELIST) "$(COMPONENT)"
	$(_v)for obj in ${OBJS}; do	\
		 $(ECHO) $(TARGET)/$(CURRENT_KERNEL_CONFIG)/$${obj}; \
	done > $(COMPONENT).filelist

do_all: $(COMPONENT).filelist

do_build_all:: do_all

-include mac_audit.d
mac_audit.o: $(SOURCE_DIR)/security/mac_audit.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/security/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/security/${C_RULE_4B})
-include mac_base.d
mac_base.o: $(SOURCE_DIR)/security/mac_base.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/security/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/security/${C_RULE_4B})
-include mac_data.d
mac_data.o: $(SOURCE_DIR)/security/mac_data.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/security/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/security/${C_RULE_4B})
-include mac_label.d
mac_label.o: $(SOURCE_DIR)/security/mac_label.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/security/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/security/${C_RULE_4B})
-include mac_process.d
mac_process.o: $(SOURCE_DIR)/security/mac_process.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/security/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/security/${C_RULE_4B})
-include mac_vfs.d
mac_vfs.o: $(SOURCE_DIR)/security/mac_vfs.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/security/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/security/${C_RULE_4B})
-include mac_vfs_subr.d
mac_vfs_subr.o: $(SOURCE_DIR)/security/mac_vfs_subr.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/security/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/security/${C_RULE_4B})
-include mac_system.d
mac_system.o: $(SOURCE_DIR)/security/mac_system.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/security/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/security/${C_RULE_4B})
-include mac_sysv_sem.d
mac_sysv_sem.o: $(SOURCE_DIR)/security/mac_sysv_sem.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/security/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/security/${C_RULE_4B})
-include mac_sysv_shm.d
mac_sysv_shm.o: $(SOURCE_DIR)/security/mac_sysv_shm.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/security/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/security/${C_RULE_4B})
-include mac_sysv_msg.d
mac_sysv_msg.o: $(SOURCE_DIR)/security/mac_sysv_msg.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/security/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/security/${C_RULE_4B})
-include mac_posix_sem.d
mac_posix_sem.o: $(SOURCE_DIR)/security/mac_posix_sem.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/security/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/security/${C_RULE_4B})
-include mac_posix_shm.d
mac_posix_shm.o: $(SOURCE_DIR)/security/mac_posix_shm.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/security/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/security/${C_RULE_4B})
-include mac_socket.d
mac_socket.o: $(SOURCE_DIR)/security/mac_socket.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/security/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/security/${C_RULE_4B})
-include mac_pipe.d
mac_pipe.o: $(SOURCE_DIR)/security/mac_pipe.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/security/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/security/${C_RULE_4B})
-include mac_iokit.d
mac_iokit.o: $(SOURCE_DIR)/security/mac_iokit.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/security/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/security/${C_RULE_4B})
-include mac_file.d
mac_file.o: $(SOURCE_DIR)/security/mac_file.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/security/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/security/${C_RULE_4B})
-include mac_priv.d
mac_priv.o: $(SOURCE_DIR)/security/mac_priv.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/security/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/security/${C_RULE_4B})
-include mac_pty.d
mac_pty.o: $(SOURCE_DIR)/security/mac_pty.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/security/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/security/${C_RULE_4B})
-include mac_kext.d
mac_kext.o: $(SOURCE_DIR)/security/mac_kext.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/security/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/security/${C_RULE_4B})
-include mac_mach.d
mac_mach.o: $(SOURCE_DIR)/security/mac_mach.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/security/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/security/${C_RULE_4B})

include $(MakeInc_rule)
include $(MakeInc_dir)
