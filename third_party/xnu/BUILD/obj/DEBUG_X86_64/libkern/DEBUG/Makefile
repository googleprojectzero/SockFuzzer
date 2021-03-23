SOURCE_DIR=/Users/nedwill/dev/sockfuzzer/third_party/xnu
export CONFIG_DEFINES = -DINET -DMACH -DMACH_COMPAT -DMACH_FASTLINK -DNO_DIRECT_RPC -DVLAN -DSIXLOWPAN -DBOND -DIF_FAKE -DIF_HEADLESS -DAH_ALL_CRYPTO -DPF -DPFLOG -DDUMMYNET -DTRAFFIC_MGT -DMULTICAST -DICMP_BANDLIM -DIFNET_INPUT_SANITY_CHK -DMULTIPATH -DMPTCP -DSYSV_SEM -DSYSV_MSG -DSYSV_SHM -DPSYNCH -DFLOW_DIVERT -DNECP -DCONTENT_FILTER -DPACKET_MANGLER -DSIXLOWPAN -DOLD_SEMWAIT_SIGNAL -DSOCKETS -DSENDFILE -DCONFIG_FSE -DCONFIG_IMAGEBOOT -DCONFIG_MBUF_JUMBO -DCONFIG_IMAGEBOOT_CHUNKLIST -DCONFIG_WORKQUEUE -DCONFIG_WORKLOOP_DEBUG -DFIFO -DFDESC -DDEVFS -DNULLFS -DBINDFS -DFS_COMPRESSION -DCONFIG_DEV_KMEM -DQUOTA -DNAMEDSTREAMS -DCONFIG_APPLEDOUBLE -DCONFIG_VOLFS -DCONFIG_IMGSRC_ACCESS -DCONFIG_TRIGGERS -DCONFIG_EXT_RESOLVER -DCONFIG_SEARCHFS -DCONFIG_MNT_SUID -DCONFIG_MNT_ROOTSNAP -DCONFIG_ROSV_STARTUP -DCONFIG_FIRMLINKS -DCONFIG_MOUNT_VM -DCONFIG_MOUNT_PREBOOTRECOVERY -DCONFIG_DATALESS_FILES -DCONFIG_BASESYSTEMROOT -DNFSCLIENT -DNFSSERVER -DCONFIG_NFS_GSS -DCONFIG_NFS4 -DCONFIG_NETBOOT -DIPSEC -DIPSEC_ESP -DCRYPTO_SHA2 -DENCRYPTED_SWAP -DCONFIG_IMG4 -DIF_BRIDGE -DCONFIG_KN_HASHSIZE="64" -DCONFIG_VNODES="263168" -DCONFIG_NC_HASH="4096" -DCONFIG_VFS_NAMES="4096" -DCONFIG_MAX_CLUSTERS="8" -DCONFIG_MIN_NBUF="256" -DCONFIG_MIN_NIOBUF="128" -DCONFIG_NMBCLUSTERS="((1024 * 512) / MCLBYTES)" -DCONFIG_TCBHASHSIZE="4096" -DCONFIG_ICMP_BANDLIM="250" -DCONFIG_AIO_MAX="90" -DCONFIG_AIO_PROCESS_MAX="16" -DCONFIG_AIO_THREAD_COUNT="4" -DCONFIG_MAXVIFS="32" -DCONFIG_MFCTBLSIZ="256" -DCONFIG_MSG_BSIZE_REL="16384" -DCONFIG_MSG_BSIZE_DEV="131072" -DCONFIG_MSG_BSIZE="CONFIG_MSG_BSIZE_DEV" -DCONFIG_IPC_TABLE_ENTRIES_STEPS="256" -DCONFIG_VSPRINTF -DCONFIG_DYNAMIC_CODE_SIGNING -DCONFIG_CODE_DECRYPTION -DCONFIG_PROTECT -DCONFIG_KEYPAGE_WP -DCONFIG_MEMORYSTATUS -DCONFIG_DIRTYSTATUS_TRACKING -DCONFIG_LTABLE_STATS -DCONFIG_LTABLE_DEBUG -DCONFIG_WAITQ_STATS -DCONFIG_WAITQ_DEBUG -DCONFIG_PHYS_WRITE_ACCT -DVM_PRESSURE_EVENTS -DCONFIG_BACKGROUND_QUEUE -DCONFIG_LEDGER_INTERVAL_MAX -DCONFIG_IOSCHED -DIMPORTANCE_INHERITANCE -DIMPORTANCE_TRACE -DIMPORTANCE_DEBUG -DCONFIG_TELEMETRY -DCONFIG_PROC_UUID_POLICY -DCONFIG_COREDUMP -DCONFIG_VNGUARD -DIOKITCPP -DIOKITSTATS -DCONFIG_SLEEP -DCONFIG_MAX_THREADS="500" -DCONFIG_BLOCKS -DCONFIG_KEC_FIPS -DCONFIG_KEXT_BASEMENT -DCONFIG_PERSONAS -DCONFIG_MACF -DCONFIG_MACF_SOCKET_SUBSET -DCONFIG_AUDIT -DCONFIG_ARCADE -DCONFIG_SETUID -DCONFIG_KAS_INFO -DMACH_ASSERT -DMACH_DEBUG -DMACH_IPC_DEBUG -DMACH_VM_DEBUG -DMACH_MP_DEBUG -DCONFIG_ZCACHE -DCONFIG_ZLEAKS -DCONFIG_TASK_ZONE_INFO -DMACH_LDEBUG -DLOCK_STATS -DKPERF -DKPC -DPGO -DMACH_COUNTERS -DDEBUG -DMACH_BSD -DIOKIT -DCONFIG_THREAD_MAX="2560" -DCONFIG_TASK_MAX="1024" -DCONFIG_ZONE_MAP_MIN="120586240" -DCONFIG_ZLEAK_ALLOCATION_MAP_NUM="16384" -DCONFIG_ZLEAK_TRACE_MAP_NUM="8192" -DCONFIG_SCHED_TRADITIONAL -DCONFIG_SCHED_PROTO -DCONFIG_SCHED_GRRR -DCONFIG_SCHED_GRRR_CORE -DCONFIG_SCHED_MULTIQ -DCONFIG_SCHED_TIMESHARE_CORE -DCONFIG_SCHED_SFI -DCONFIG_GZALLOC -DMACH_KDP -DCONFIG_SERIAL_KDP -DCONFIG_KDP_INTERACTIVE_DEBUGGING -DCONFIG_TASKWATCH -DCONFIG_XNUPOST -DCONFIG_ATM -DCONFIG_COALITIONS -DCONFIG_SYSDIAGNOSE -DCONFIG_CSR -DSERIAL_CONSOLE -DVIDEO_CONSOLE -DCONFIG_REQUIRES_U32_MUNGING -DCOPYOUT_SHIM -DCONFIG_MACH_BRIDGE_SEND_TIME -DCONFIG_32BIT_TELEMETRY -DCONFIG_DELAY_IDLE_SLEEP -DCONFIG_PROC_UDATA_STORAGE -DPAL_I386 -DCONFIG_MCA -DCONFIG_VMX -DCONFIG_MTRR -DCONFIG_MACF_LAZY_VNODE_LABELS -DHYPERVISOR -DCONFIG_MACH_APPROXIMATE_TIME
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
# CFLAGS
#
CFLAGS+= -include meta_features.h -DLIBKERN_KERNEL_PRIVATE -DOSALLOCDEBUG=1
SFLAGS+= -include meta_features.h

# Runtime support functions don't interact well with LTO (9294679)
stack_protector.o_CFLAGS_ADD += $(CFLAGS_NOLTO_FLAG)

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

OBJS=OSAtomicOperations.o OSSpinLock.o OSDebug.cpo OSMetaClass.cpo \
	OSObject.cpo OSArray.cpo OSBoolean.cpo OSCollection.cpo \
	OSCollectionIterator.cpo OSData.cpo OSDictionary.cpo \
	OSIterator.cpo OSKext.cpo OSNumber.cpo OSOrderedSet.cpo \
	OSRuntime.cpo OSRuntimeSupport.o OSSerialize.cpo OSSet.cpo \
	OSString.cpo OSSymbol.cpo OSUnserialize.cpo OSUnserializeXML.cpo \
	OSSerializeBinary.cpo priority_queue.cpo OSKextLib.cpo mkext.o \
	OSKextVersion.o inet_aton.o inet_ntoa.o inet_ntop.o inet_pton.o \
	scanf.o uuid.o log.o object.o internal.o refcnt.o \
	kernel_mach_header.o adler32.o compress.o z_crc32.o deflate.o \
	infback.o inffast.o inflate.o inftrees.o trees.o uncompr.o \
	zutil.o register_crypto.o corecrypto_sha2.o corecrypto_sha1.o \
	corecrypto_md5.o corecrypto_des.o corecrypto_aes.o \
	corecrypto_aesxts.o corecrypto_rand.o corecrypto_rsa.o \
	corecrypto_chacha20poly1305.o interface.o stack_protector.o \
	ptrauth_utils.o runtime.cpo libclosuredata.o 

LIBOBJS=

CFILES=\
	$(SOURCE_DIR)/libkern/gen/OSAtomicOperations.c \
	$(SOURCE_DIR)/libkern/gen/OSSpinLock.c \
	$(SOURCE_DIR)/libkern/c++/OSRuntimeSupport.c \
	$(SOURCE_DIR)/libkern/mkext.c \
	$(SOURCE_DIR)/libkern/OSKextVersion.c \
	$(SOURCE_DIR)/libkern/net/inet_aton.c \
	$(SOURCE_DIR)/libkern/net/inet_ntoa.c \
	$(SOURCE_DIR)/libkern/net/inet_ntop.c \
	$(SOURCE_DIR)/libkern/net/inet_pton.c \
	$(SOURCE_DIR)/libkern/stdio/scanf.c \
	$(SOURCE_DIR)/libkern/uuid/uuid.c \
	$(SOURCE_DIR)/libkern/os/log.c \
	$(SOURCE_DIR)/libkern/os/object.c \
	$(SOURCE_DIR)/libkern/os/internal.c \
	$(SOURCE_DIR)/libkern/os/refcnt.c \
	$(SOURCE_DIR)/libkern/kernel_mach_header.c \
	$(SOURCE_DIR)/libkern/zlib/adler32.c \
	$(SOURCE_DIR)/libkern/zlib/compress.c \
	$(SOURCE_DIR)/libkern/zlib/z_crc32.c \
	$(SOURCE_DIR)/libkern/zlib/deflate.c \
	$(SOURCE_DIR)/libkern/zlib/infback.c \
	$(SOURCE_DIR)/libkern/zlib/inffast.c \
	$(SOURCE_DIR)/libkern/zlib/inflate.c \
	$(SOURCE_DIR)/libkern/zlib/inftrees.c \
	$(SOURCE_DIR)/libkern/zlib/trees.c \
	$(SOURCE_DIR)/libkern/zlib/uncompr.c \
	$(SOURCE_DIR)/libkern/zlib/zutil.c \
	$(SOURCE_DIR)/libkern/crypto/register_crypto.c \
	$(SOURCE_DIR)/libkern/crypto/corecrypto_sha2.c \
	$(SOURCE_DIR)/libkern/crypto/corecrypto_sha1.c \
	$(SOURCE_DIR)/libkern/crypto/corecrypto_md5.c \
	$(SOURCE_DIR)/libkern/crypto/corecrypto_des.c \
	$(SOURCE_DIR)/libkern/crypto/corecrypto_aes.c \
	$(SOURCE_DIR)/libkern/crypto/corecrypto_aesxts.c \
	$(SOURCE_DIR)/libkern/crypto/corecrypto_rand.c \
	$(SOURCE_DIR)/libkern/crypto/corecrypto_rsa.c \
	$(SOURCE_DIR)/libkern/crypto/corecrypto_chacha20poly1305.c \
	$(SOURCE_DIR)/libkern/img4/interface.c \
	$(SOURCE_DIR)/libkern/stack_protector.c \
	$(SOURCE_DIR)/libkern/ptrauth_utils.c \
	$(SOURCE_DIR)/libkern/libclosure/libclosuredata.c 
COBJS=OSAtomicOperations.o OSSpinLock.o OSRuntimeSupport.o mkext.o \
	OSKextVersion.o inet_aton.o inet_ntoa.o inet_ntop.o inet_pton.o \
	scanf.o uuid.o log.o object.o internal.o refcnt.o \
	kernel_mach_header.o adler32.o compress.o z_crc32.o deflate.o \
	infback.o inffast.o inflate.o inftrees.o trees.o uncompr.o \
	zutil.o register_crypto.o corecrypto_sha2.o corecrypto_sha1.o \
	corecrypto_md5.o corecrypto_des.o corecrypto_aes.o \
	corecrypto_aesxts.o corecrypto_rand.o corecrypto_rsa.o \
	corecrypto_chacha20poly1305.o interface.o stack_protector.o \
	ptrauth_utils.o libclosuredata.o 

CXXFILES=\
	$(SOURCE_DIR)/libkern/gen/OSDebug.cpp \
	$(SOURCE_DIR)/libkern/c++/OSMetaClass.cpp \
	$(SOURCE_DIR)/libkern/c++/OSObject.cpp \
	$(SOURCE_DIR)/libkern/c++/OSArray.cpp \
	$(SOURCE_DIR)/libkern/c++/OSBoolean.cpp \
	$(SOURCE_DIR)/libkern/c++/OSCollection.cpp \
	$(SOURCE_DIR)/libkern/c++/OSCollectionIterator.cpp \
	$(SOURCE_DIR)/libkern/c++/OSData.cpp \
	$(SOURCE_DIR)/libkern/c++/OSDictionary.cpp \
	$(SOURCE_DIR)/libkern/c++/OSIterator.cpp \
	$(SOURCE_DIR)/libkern/c++/OSKext.cpp \
	$(SOURCE_DIR)/libkern/c++/OSNumber.cpp \
	$(SOURCE_DIR)/libkern/c++/OSOrderedSet.cpp \
	$(SOURCE_DIR)/libkern/c++/OSRuntime.cpp \
	$(SOURCE_DIR)/libkern/c++/OSSerialize.cpp \
	$(SOURCE_DIR)/libkern/c++/OSSet.cpp \
	$(SOURCE_DIR)/libkern/c++/OSString.cpp \
	$(SOURCE_DIR)/libkern/c++/OSSymbol.cpp \
	$(SOURCE_DIR)/libkern/c++/OSUnserialize.cpp \
	$(SOURCE_DIR)/libkern/c++/OSUnserializeXML.cpp \
	$(SOURCE_DIR)/libkern/c++/OSSerializeBinary.cpp \
	$(SOURCE_DIR)/libkern/c++/priority_queue.cpp \
	$(SOURCE_DIR)/libkern/OSKextLib.cpp \
	$(SOURCE_DIR)/libkern/libclosure/runtime.cpp 
CXXOBJS=OSDebug.cpo OSMetaClass.cpo OSObject.cpo OSArray.cpo \
	OSBoolean.cpo OSCollection.cpo OSCollectionIterator.cpo \
	OSData.cpo OSDictionary.cpo OSIterator.cpo OSKext.cpo \
	OSNumber.cpo OSOrderedSet.cpo OSRuntime.cpo OSSerialize.cpo \
	OSSet.cpo OSString.cpo OSSymbol.cpo OSUnserialize.cpo \
	OSUnserializeXML.cpo OSSerializeBinary.cpo priority_queue.cpo \
	OSKextLib.cpo runtime.cpo 

SFILES=
SOBJS=

######################################################################
#BEGIN	Machine dependent Makefile fragment for x86_64
######################################################################
#
# XXX: CFLAGS
#
CWARNFLAGS   = $(CWARNFLAGS_STD) -Wshorten-64-to-32 -Wimplicit-int-conversion
CXXWARNFLAGS = $(CXXWARNFLAGS_STD) -Wshorten-64-to-32 -Wimplicit-int-conversion

mkext.o_CFLAGS_ADD += -Wno-shorten-64-to-32 -Wno-implicit-int-conversion
inet_ntop.o_CFLAGS_ADD += -Wno-shorten-64-to-32 -Wno-implicit-int-conversion
inet_pton.o_CFLAGS_ADD += -Wno-shorten-64-to-32 -Wno-implicit-int-conversion
log.o_CFLAGS_ADD += -Wno-shorten-64-to-32 -Wno-implicit-int-conversion
z_crc32.o_CFLAGS_ADD += -Wno-shorten-64-to-32 -Wno-implicit-int-conversion
deflate.o_CFLAGS_ADD += -Wno-shorten-64-to-32 -Wno-implicit-int-conversion
trees.o_CFLAGS_ADD += -Wno-shorten-64-to-32 -Wno-implicit-int-conversion
trees.o_CFLAGS_ADD += -Wno-shorten-64-to-32 -Wno-implicit-int-conversion
corecrypto_sha1.o_CFLAGS_ADD += -Wno-shorten-64-to-32 -Wno-implicit-int-conversion
corecrypto_md5.o_CFLAGS_ADD += -Wno-shorten-64-to-32 -Wno-implicit-int-conversion
corecrypto_aes.o_CFLAGS_ADD += -Wno-shorten-64-to-32 -Wno-implicit-int-conversion
kxld_sym.o_CFLAGS_ADD += -Wno-shorten-64-to-32 -Wno-implicit-int-conversion
OSUnserializeXML.cpo_CFLAGS_ADD += -Wno-shorten-64-to-32 -Wno-implicit-int-conversion
OSUnserialize.cpo_CFLAGS_ADD += -Wno-shorten-64-to-32 -Wno-implicit-int-conversion

######################################################################
#END	Machine dependent Makefile fragment for x86_64
######################################################################

#
# Machine-independent per-file flags
#

#
# Diagnostic opt-outs.  We need to make this list empty.
#
# DO NOT ADD MORE HERE.
#
# -Wno-cast-align
OSKext.cpo_CXXWARNFLAGS_ADD += -Wno-cast-align
OSKextLib.cpo_CXXWARNFLAGS_ADD += -Wno-cast-align
OSMetaClass.cpo_CXXWARNFLAGS_ADD += -Wno-cast-align
OSUnserialize.cpo_CXXWARNFLAGS_ADD += -Wno-cast-align
corecrypto_md5.o_CFLAGS_ADD += -Wno-cast-align
corecrypto_sha1.o_CFLAGS_ADD += -Wno-cast-align
# -Wno-cast-qual
OSKext.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
compress.o_CFLAGS_ADD += -Wno-cast-qual
deflate.o_CFLAGS_ADD += -Wno-cast-qual
runtime.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
trees.o_CFLAGS_ADD += -Wno-cast-qual
uncompr.o_CFLAGS_ADD += -Wno-cast-qual
# -Wno-implicit-int-conversion
OSUnserialize.cpo_CXXWARNFLAGS_ADD += -Wno-implicit-int-conversion
OSUnserializeXML.cpo_CXXWARNFLAGS_ADD += -Wno-implicit-int-conversion
kxld_sym.o_CFLAGS_ADD += -Wno-implicit-int-conversion
log.o_CFLAGS_ADD += -Wno-implicit-int-conversion
scanf.o_CFLAGS_ADD += -Wno-implicit-int-conversion
# -Wno-missing-prototypes
OSRuntime.cpo_CXXWARNFLAGS_ADD += -Wno-missing-prototypes
# -Wno-shorten-64-to-32
OSKext.cpo_CXXWARNFLAGS_ADD += -Wno-shorten-64-to-32
OSUnserialize.cpo_CXXWARNFLAGS_ADD += -Wno-shorten-64-to-32
OSUnserializeXML.cpo_CXXWARNFLAGS_ADD += -Wno-shorten-64-to-32
log.o_CFLAGS_ADD += -Wno-shorten-64-to-32
scanf.o_CFLAGS_ADD += -Wno-shorten-64-to-32
# -Wno-sign-conversion
OSCollection.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
OSData.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
OSDebug.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
OSKext.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
OSKextVersion.o_CFLAGS_ADD += -Wno-sign-conversion
OSMetaClass.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
OSNumber.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
OSObject.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
OSRuntime.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
OSSerializeBinary.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
OSSet.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
OSString.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
OSUnserialize.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
OSUnserializeXML.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
adler32.o_CFLAGS_ADD += -Wno-sign-conversion
corecrypto_aes.o_CFLAGS_ADD += -Wno-sign-conversion
corecrypto_aesxts.o_CFLAGS_ADD += -Wno-sign-conversion
deflate.o_CFLAGS_ADD += -Wno-sign-conversion
inet_aton.o_CFLAGS_ADD += -Wno-sign-conversion
infback.o_CFLAGS_ADD += -Wno-sign-conversion
inflate.o_CFLAGS_ADD += -Wno-sign-conversion
kxld_array.o_CFLAGS_ADD += -Wno-sign-conversion
kxld_copyright.o_CFLAGS_ADD += -Wno-sign-conversion
kxld_dict.o_CFLAGS_ADD += -Wno-sign-conversion
kxld_object.o_CFLAGS_ADD += -Wno-sign-conversion
kxld_reloc.o_CFLAGS_ADD += -Wno-sign-conversion
kxld_sym.o_CFLAGS_ADD += -Wno-sign-conversion
kxld_symtab.o_CFLAGS_ADD += -Wno-sign-conversion
kxld_util.o_CFLAGS_ADD += -Wno-sign-conversion
log.o_CFLAGS_ADD += -Wno-sign-conversion
refcnt.o_CFLAGS_ADD += -Wno-sign-conversion
scanf.o_CFLAGS_ADD += -Wno-sign-conversion
trees.o_CFLAGS_ADD += -Wno-sign-conversion
uuid.o_CFLAGS_ADD += -Wno-sign-conversion
# -Wno-unreachable-code
OSUnserialize.cpo_CXXWARNFLAGS_ADD += -Wno-unreachable-code
OSUnserializeXML.cpo_CXXWARNFLAGS_ADD += -Wno-unreachable-code
OSUnserialize.cpo_CXXWARNFLAGS_ADD += -Wno-unreachable-code-break
OSUnserializeXML.cpo_CXXWARNFLAGS_ADD += -Wno-unreachable-code-break
# -Wno-zero-as-null-pointer-constant
OSUnserialize.cpo_CXXWARNFLAGS_ADD += -Wno-zero-as-null-pointer-constant
OSUnserializeXML.cpo_CXXWARNFLAGS_ADD += -Wno-zero-as-null-pointer-constant

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
	$(_v)for hib_file in ${HIB_FILES}; \
	do	\
		$(SEG_HACK) -n __HIB -o $${hib_file}__ $${hib_file} || exit 1; \
		mv $${hib_file}__ $${hib_file} || exit 1; \
	done
	@$(LOG_LDFILELIST) "$(COMPONENT)"
	$(_v)for obj in ${OBJS}; do	\
		 $(ECHO) $(TARGET)/$(CURRENT_KERNEL_CONFIG)/$${obj}; \
	done > $(COMPONENT).filelist

$(COMPONENT).libfilelist: $(LIBOBJS)
	@$(LOG_LDFILELIST) "lib$(COMPONENT)"
	$(_v)for obj in ${LIBOBJS}; do	\
		 $(ECHO) $(TARGET)/$(CURRENT_KERNEL_CONFIG)/$${obj}; \
	done > $(COMPONENT).libfilelist

ifeq ($(RC_ProjectName),xnu_libraries)
do_all: $(COMPONENT).libfilelist
else
do_all: $(COMPONENT).filelist
endif

do_build_all:: do_all

-include OSAtomicOperations.d
OSAtomicOperations.o: $(SOURCE_DIR)/libkern/gen/OSAtomicOperations.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/gen/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/gen/${C_RULE_4B})
-include OSSpinLock.d
OSSpinLock.o: $(SOURCE_DIR)/libkern/gen/OSSpinLock.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/gen/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/gen/${C_RULE_4B})
-include OSDebug.cpd
OSDebug.cpo: $(SOURCE_DIR)/libkern/gen/OSDebug.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/libkern/gen/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/libkern/gen/${P_RULE_4B})
-include OSMetaClass.cpd
OSMetaClass.cpo: $(SOURCE_DIR)/libkern/c++/OSMetaClass.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/libkern/c++/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/libkern/c++/${P_RULE_4B})
-include OSObject.cpd
OSObject.cpo: $(SOURCE_DIR)/libkern/c++/OSObject.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/libkern/c++/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/libkern/c++/${P_RULE_4B})
-include OSArray.cpd
OSArray.cpo: $(SOURCE_DIR)/libkern/c++/OSArray.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/libkern/c++/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/libkern/c++/${P_RULE_4B})
-include OSBoolean.cpd
OSBoolean.cpo: $(SOURCE_DIR)/libkern/c++/OSBoolean.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/libkern/c++/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/libkern/c++/${P_RULE_4B})
-include OSCollection.cpd
OSCollection.cpo: $(SOURCE_DIR)/libkern/c++/OSCollection.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/libkern/c++/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/libkern/c++/${P_RULE_4B})
-include OSCollectionIterator.cpd
OSCollectionIterator.cpo: $(SOURCE_DIR)/libkern/c++/OSCollectionIterator.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/libkern/c++/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/libkern/c++/${P_RULE_4B})
-include OSData.cpd
OSData.cpo: $(SOURCE_DIR)/libkern/c++/OSData.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/libkern/c++/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/libkern/c++/${P_RULE_4B})
-include OSDictionary.cpd
OSDictionary.cpo: $(SOURCE_DIR)/libkern/c++/OSDictionary.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/libkern/c++/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/libkern/c++/${P_RULE_4B})
-include OSIterator.cpd
OSIterator.cpo: $(SOURCE_DIR)/libkern/c++/OSIterator.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/libkern/c++/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/libkern/c++/${P_RULE_4B})
-include OSKext.cpd
OSKext.cpo: $(SOURCE_DIR)/libkern/c++/OSKext.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/libkern/c++/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/libkern/c++/${P_RULE_4B})
-include OSNumber.cpd
OSNumber.cpo: $(SOURCE_DIR)/libkern/c++/OSNumber.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/libkern/c++/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/libkern/c++/${P_RULE_4B})
-include OSOrderedSet.cpd
OSOrderedSet.cpo: $(SOURCE_DIR)/libkern/c++/OSOrderedSet.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/libkern/c++/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/libkern/c++/${P_RULE_4B})
-include OSRuntime.cpd
OSRuntime.cpo: $(SOURCE_DIR)/libkern/c++/OSRuntime.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/libkern/c++/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/libkern/c++/${P_RULE_4B})
-include OSRuntimeSupport.d
OSRuntimeSupport.o: $(SOURCE_DIR)/libkern/c++/OSRuntimeSupport.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/c++/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/c++/${C_RULE_4B})
-include OSSerialize.cpd
OSSerialize.cpo: $(SOURCE_DIR)/libkern/c++/OSSerialize.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/libkern/c++/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/libkern/c++/${P_RULE_4B})
-include OSSet.cpd
OSSet.cpo: $(SOURCE_DIR)/libkern/c++/OSSet.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/libkern/c++/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/libkern/c++/${P_RULE_4B})
-include OSString.cpd
OSString.cpo: $(SOURCE_DIR)/libkern/c++/OSString.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/libkern/c++/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/libkern/c++/${P_RULE_4B})
-include OSSymbol.cpd
OSSymbol.cpo: $(SOURCE_DIR)/libkern/c++/OSSymbol.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/libkern/c++/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/libkern/c++/${P_RULE_4B})
-include OSUnserialize.cpd
OSUnserialize.cpo: $(SOURCE_DIR)/libkern/c++/OSUnserialize.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/libkern/c++/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/libkern/c++/${P_RULE_4B})
-include OSUnserializeXML.cpd
OSUnserializeXML.cpo: $(SOURCE_DIR)/libkern/c++/OSUnserializeXML.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/libkern/c++/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/libkern/c++/${P_RULE_4B})
-include OSSerializeBinary.cpd
OSSerializeBinary.cpo: $(SOURCE_DIR)/libkern/c++/OSSerializeBinary.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/libkern/c++/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/libkern/c++/${P_RULE_4B})
-include priority_queue.cpd
priority_queue.cpo: $(SOURCE_DIR)/libkern/c++/priority_queue.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/libkern/c++/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/libkern/c++/${P_RULE_4B})
-include OSKextLib.cpd
OSKextLib.cpo: $(SOURCE_DIR)/libkern/OSKextLib.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/libkern/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/libkern/${P_RULE_4B})
-include mkext.d
mkext.o: $(SOURCE_DIR)/libkern/mkext.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/${C_RULE_4B})
-include OSKextVersion.d
OSKextVersion.o: $(SOURCE_DIR)/libkern/OSKextVersion.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/${C_RULE_4B})
-include inet_aton.d
inet_aton.o: $(SOURCE_DIR)/libkern/net/inet_aton.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/net/${C_RULE_4B})
-include inet_ntoa.d
inet_ntoa.o: $(SOURCE_DIR)/libkern/net/inet_ntoa.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/net/${C_RULE_4B})
-include inet_ntop.d
inet_ntop.o: $(SOURCE_DIR)/libkern/net/inet_ntop.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/net/${C_RULE_4B})
-include inet_pton.d
inet_pton.o: $(SOURCE_DIR)/libkern/net/inet_pton.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/net/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/net/${C_RULE_4B})
-include scanf.d
scanf.o: $(SOURCE_DIR)/libkern/stdio/scanf.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/stdio/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/stdio/${C_RULE_4B})
-include uuid.d
uuid.o: $(SOURCE_DIR)/libkern/uuid/uuid.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/uuid/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/uuid/${C_RULE_4B})
-include log.d
log.o: $(SOURCE_DIR)/libkern/os/log.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/os/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/os/${C_RULE_4B})
-include object.d
object.o: $(SOURCE_DIR)/libkern/os/object.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/os/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/os/${C_RULE_4B})
-include internal.d
internal.o: $(SOURCE_DIR)/libkern/os/internal.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/os/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/os/${C_RULE_4B})
-include refcnt.d
refcnt.o: $(SOURCE_DIR)/libkern/os/refcnt.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/os/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/os/${C_RULE_4B})
-include kernel_mach_header.d
kernel_mach_header.o: $(SOURCE_DIR)/libkern/kernel_mach_header.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/${C_RULE_4B})
-include adler32.d
adler32.o: $(SOURCE_DIR)/libkern/zlib/adler32.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/zlib/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/zlib/${C_RULE_4B})
-include compress.d
compress.o: $(SOURCE_DIR)/libkern/zlib/compress.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/zlib/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/zlib/${C_RULE_4B})
-include z_crc32.d
z_crc32.o: $(SOURCE_DIR)/libkern/zlib/z_crc32.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/zlib/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/zlib/${C_RULE_4B})
-include deflate.d
deflate.o: $(SOURCE_DIR)/libkern/zlib/deflate.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/zlib/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/zlib/${C_RULE_4B})
-include infback.d
infback.o: $(SOURCE_DIR)/libkern/zlib/infback.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/zlib/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/zlib/${C_RULE_4B})
-include inffast.d
inffast.o: $(SOURCE_DIR)/libkern/zlib/inffast.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/zlib/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/zlib/${C_RULE_4B})
-include inflate.d
inflate.o: $(SOURCE_DIR)/libkern/zlib/inflate.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/zlib/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/zlib/${C_RULE_4B})
-include inftrees.d
inftrees.o: $(SOURCE_DIR)/libkern/zlib/inftrees.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/zlib/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/zlib/${C_RULE_4B})
-include trees.d
trees.o: $(SOURCE_DIR)/libkern/zlib/trees.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/zlib/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/zlib/${C_RULE_4B})
-include uncompr.d
uncompr.o: $(SOURCE_DIR)/libkern/zlib/uncompr.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/zlib/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/zlib/${C_RULE_4B})
-include zutil.d
zutil.o: $(SOURCE_DIR)/libkern/zlib/zutil.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/zlib/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/zlib/${C_RULE_4B})
-include register_crypto.d
register_crypto.o: $(SOURCE_DIR)/libkern/crypto/register_crypto.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/crypto/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/crypto/${C_RULE_4B})
-include corecrypto_sha2.d
corecrypto_sha2.o: $(SOURCE_DIR)/libkern/crypto/corecrypto_sha2.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/crypto/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/crypto/${C_RULE_4B})
-include corecrypto_sha1.d
corecrypto_sha1.o: $(SOURCE_DIR)/libkern/crypto/corecrypto_sha1.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/crypto/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/crypto/${C_RULE_4B})
-include corecrypto_md5.d
corecrypto_md5.o: $(SOURCE_DIR)/libkern/crypto/corecrypto_md5.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/crypto/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/crypto/${C_RULE_4B})
-include corecrypto_des.d
corecrypto_des.o: $(SOURCE_DIR)/libkern/crypto/corecrypto_des.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/crypto/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/crypto/${C_RULE_4B})
-include corecrypto_aes.d
corecrypto_aes.o: $(SOURCE_DIR)/libkern/crypto/corecrypto_aes.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/crypto/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/crypto/${C_RULE_4B})
-include corecrypto_aesxts.d
corecrypto_aesxts.o: $(SOURCE_DIR)/libkern/crypto/corecrypto_aesxts.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/crypto/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/crypto/${C_RULE_4B})
-include corecrypto_rand.d
corecrypto_rand.o: $(SOURCE_DIR)/libkern/crypto/corecrypto_rand.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/crypto/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/crypto/${C_RULE_4B})
-include corecrypto_rsa.d
corecrypto_rsa.o: $(SOURCE_DIR)/libkern/crypto/corecrypto_rsa.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/crypto/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/crypto/${C_RULE_4B})
-include corecrypto_chacha20poly1305.d
corecrypto_chacha20poly1305.o: $(SOURCE_DIR)/libkern/crypto/corecrypto_chacha20poly1305.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/crypto/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/crypto/${C_RULE_4B})
-include interface.d
interface.o: $(SOURCE_DIR)/libkern/img4/interface.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/img4/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/img4/${C_RULE_4B})
-include stack_protector.d
stack_protector.o: $(SOURCE_DIR)/libkern/stack_protector.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/${C_RULE_4B})
-include ptrauth_utils.d
ptrauth_utils.o: $(SOURCE_DIR)/libkern/ptrauth_utils.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/${C_RULE_4B})
-include runtime.cpd
runtime.cpo: $(SOURCE_DIR)/libkern/libclosure/runtime.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/libkern/libclosure/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/libkern/libclosure/${P_RULE_4B})
-include libclosuredata.d
libclosuredata.o: $(SOURCE_DIR)/libkern/libclosure/libclosuredata.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/libkern/libclosure/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/libkern/libclosure/${C_RULE_4B})

include $(MakeInc_rule)
include $(MakeInc_dir)
