SOURCE_DIR=/Users/nedwill/dev/sockfuzzer/third_party/xnu
export CONFIG_DEFINES = -DINET -DMACH -DMACH_COMPAT -DMACH_FASTLINK -DNO_DIRECT_RPC -DVLAN -DSIXLOWPAN -DBOND -DIF_FAKE -DIF_HEADLESS -DAH_ALL_CRYPTO -DPF -DPFLOG -DDUMMYNET -DTRAFFIC_MGT -DMULTICAST -DICMP_BANDLIM -DIFNET_INPUT_SANITY_CHK -DMULTIPATH -DMPTCP -DSYSV_SEM -DSYSV_MSG -DSYSV_SHM -DPSYNCH -DFLOW_DIVERT -DNECP -DCONTENT_FILTER -DPACKET_MANGLER -DSIXLOWPAN -DOLD_SEMWAIT_SIGNAL -DSOCKETS -DSENDFILE -DCONFIG_FSE -DCONFIG_IMAGEBOOT -DCONFIG_MBUF_JUMBO -DCONFIG_IMAGEBOOT_CHUNKLIST -DCONFIG_WORKQUEUE -DCONFIG_WORKLOOP_DEBUG -DFIFO -DFDESC -DDEVFS -DNULLFS -DBINDFS -DFS_COMPRESSION -DCONFIG_DEV_KMEM -DQUOTA -DNAMEDSTREAMS -DCONFIG_APPLEDOUBLE -DCONFIG_VOLFS -DCONFIG_IMGSRC_ACCESS -DCONFIG_TRIGGERS -DCONFIG_EXT_RESOLVER -DCONFIG_SEARCHFS -DCONFIG_MNT_SUID -DCONFIG_MNT_ROOTSNAP -DCONFIG_ROSV_STARTUP -DCONFIG_FIRMLINKS -DCONFIG_MOUNT_VM -DCONFIG_MOUNT_PREBOOTRECOVERY -DCONFIG_DATALESS_FILES -DCONFIG_BASESYSTEMROOT -DNFSCLIENT -DNFSSERVER -DCONFIG_NFS_GSS -DCONFIG_NFS4 -DCONFIG_NETBOOT -DIPSEC -DIPSEC_ESP -DCRYPTO_SHA2 -DENCRYPTED_SWAP -DCONFIG_IMG4 -DZLIB -DIF_BRIDGE -DCONFIG_KN_HASHSIZE="64" -DCONFIG_VNODES="263168" -DCONFIG_NC_HASH="4096" -DCONFIG_VFS_NAMES="4096" -DCONFIG_MAX_CLUSTERS="8" -DCONFIG_MIN_NBUF="256" -DCONFIG_MIN_NIOBUF="128" -DCONFIG_NMBCLUSTERS="((1024 * 512) / MCLBYTES)" -DCONFIG_TCBHASHSIZE="4096" -DCONFIG_ICMP_BANDLIM="250" -DCONFIG_AIO_MAX="90" -DCONFIG_AIO_PROCESS_MAX="16" -DCONFIG_AIO_THREAD_COUNT="4" -DCONFIG_MAXVIFS="32" -DCONFIG_MFCTBLSIZ="256" -DCONFIG_MSG_BSIZE_REL="16384" -DCONFIG_MSG_BSIZE_DEV="131072" -DCONFIG_MSG_BSIZE="CONFIG_MSG_BSIZE_DEV" -DCONFIG_IPC_TABLE_ENTRIES_STEPS="256" -DCONFIG_VSPRINTF -DCONFIG_DYNAMIC_CODE_SIGNING -DCONFIG_CODE_DECRYPTION -DCONFIG_PROTECT -DCONFIG_KEYPAGE_WP -DCONFIG_MEMORYSTATUS -DCONFIG_DIRTYSTATUS_TRACKING -DCONFIG_LTABLE_STATS -DCONFIG_LTABLE_DEBUG -DCONFIG_WAITQ_STATS -DCONFIG_WAITQ_DEBUG -DCONFIG_PHYS_WRITE_ACCT -DVM_PRESSURE_EVENTS -DCONFIG_BACKGROUND_QUEUE -DCONFIG_LEDGER_INTERVAL_MAX -DCONFIG_IOSCHED -DIMPORTANCE_INHERITANCE -DIMPORTANCE_TRACE -DIMPORTANCE_DEBUG -DCONFIG_TELEMETRY -DCONFIG_PROC_UUID_POLICY -DCONFIG_COREDUMP -DCONFIG_VNGUARD -DIOKITSTATS -DIOTRACKING -DCONFIG_SLEEP -DCONFIG_MAX_THREADS="500" -DLIBKERNCPP -DCONFIG_BLOCKS -DCONFIG_KEC_FIPS -DCONFIG_KEXT_BASEMENT -DCONFIG_PERSONAS -DCONFIG_MACF -DCONFIG_MACF_SOCKET_SUBSET -DCONFIG_AUDIT -DCONFIG_ARCADE -DCONFIG_SETUID -DCONFIG_KAS_INFO -DMACH_DEBUG -DMACH_IPC_DEBUG -DMACH_VM_DEBUG -DMACH_MP_DEBUG -DCONFIG_ZCACHE -DCONFIG_ZLEAKS -DCONFIG_TASK_ZONE_INFO -DMACH_LDEBUG -DLOCK_STATS -DKPERF -DKPC -DPGO -DMACH_COUNTERS -DDEBUG -DMACH_BSD -DIOKIT -DCONFIG_THREAD_MAX="2560" -DCONFIG_TASK_MAX="1024" -DCONFIG_ZONE_MAP_MIN="120586240" -DCONFIG_ZLEAK_ALLOCATION_MAP_NUM="16384" -DCONFIG_ZLEAK_TRACE_MAP_NUM="8192" -DCONFIG_SCHED_TRADITIONAL -DCONFIG_SCHED_PROTO -DCONFIG_SCHED_GRRR -DCONFIG_SCHED_GRRR_CORE -DCONFIG_SCHED_MULTIQ -DCONFIG_SCHED_TIMESHARE_CORE -DCONFIG_SCHED_SFI -DCONFIG_GZALLOC -DMACH_KDP -DCONFIG_SERIAL_KDP -DCONFIG_KDP_INTERACTIVE_DEBUGGING -DCONFIG_TASKWATCH -DCONFIG_XNUPOST -DCONFIG_ATM -DCONFIG_COALITIONS -DCONFIG_SYSDIAGNOSE -DCONFIG_CSR -DSERIAL_CONSOLE -DVIDEO_CONSOLE -DCONFIG_REQUIRES_U32_MUNGING -DCOPYOUT_SHIM -DCONFIG_MACH_BRIDGE_SEND_TIME -DCONFIG_32BIT_TELEMETRY -DCONFIG_DELAY_IDLE_SLEEP -DCONFIG_PROC_UDATA_STORAGE -DPAL_I386 -DCONFIG_MCA -DCONFIG_VMX -DCONFIG_MTRR -DCONFIG_MACF_LAZY_VNODE_LABELS -DHYPERVISOR -DCONFIG_MACH_APPROXIMATE_TIME
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
CFLAGS+= -include meta_features.h -DDRIVER_PRIVATE		\
	-DIOKIT_KERNEL_PRIVATE -DDRIVERKIT_PRIVATE=1 -DIOMATCHDEBUG=1 -DIOALLOCDEBUG=1
SFLAGS+= -include meta_features.h
#-DIOKITDEBUG=-1

CFLAGS_RELEASE += -DIOASSERT=0
CFLAGS_DEVELOPMENT += -DIOASSERT=1
CFLAGS_DEBUG += -DIOASSERT=1

#
# Directories for generated files
#
COMP_SUBDIRS = \
	DriverKit

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

OBJS=OSObject.iig.cpo OSAction.iig.cpo IOService.iig.cpo \
	IOUserClient.iig.cpo IOMemoryDescriptor.iig.cpo \
	IOBufferMemoryDescriptor.iig.cpo IOMemoryMap.iig.cpo \
	IODispatchSource.iig.cpo IODispatchQueue.iig.cpo \
	IOInterruptDispatchSource.iig.cpo \
	IODataQueueDispatchSource.iig.cpo \
	IOServiceNotificationDispatchSource.iig.cpo IOUserServer.iig.cpo \
	IODMACommand.iig.cpo IOHibernateIO.cpo \
	IOHibernateRestoreKernel.o IOLib.cpo IOLocks.cpo \
	IOConditionLock.cpo IOStartIOKit.cpo IODeviceTreeSupport.cpo \
	IORegistryEntry.cpo IOService.cpo IOServicePM.cpo \
	IOPMinformee.cpo IOPMinformeeList.cpo IOPMPowerStateQueue.cpo \
	IOCatalogue.cpo IOPMPowerSource.cpo IOPMPowerSourceList.cpo \
	IOPMGR.cpo IOPolledInterface.cpo IOWorkLoop.cpo \
	IOEventSource.cpo IOInterruptEventSource.cpo IOCommandGate.cpo \
	IOCommand.cpo IOCommandPool.cpo IOCommandQueue.cpo \
	IODMAEventSource.cpo IOFilterInterruptEventSource.cpo \
	IOTimerEventSource.cpo IOBufferMemoryDescriptor.cpo \
	IODMACommand.cpo IODeviceMemory.cpo \
	IOInterleavedMemoryDescriptor.cpo IOMapper.cpo \
	IOMemoryCursor.cpo IOMemoryDescriptor.cpo \
	IOMultiMemoryDescriptor.cpo IORangeAllocator.cpo \
	IOSubMemoryDescriptor.cpo IOPlatformExpert.cpo IOPlatformIO.cpo \
	IOCPU.cpo IOPlatformActions.cpo IONVRAM.cpo IODMAController.cpo \
	IOInterruptController.cpo PassthruInterruptController.cpo \
	IOUserClient.cpo IOKitDebug.cpo IODataQueue.cpo \
	IOSharedDataQueue.cpo Tests.cpo TestIOMemoryDescriptor.cpo \
	IOStatistics.cpo IOInterruptAccounting.cpo IOReporter.cpo \
	IOSimpleReporter.cpo IOStateReporter.cpo IOHistogramReporter.cpo \
	IOReportLegend.cpo IORTC.cpo IOStringFuncs.o IOUserServer.cpo \
	KernelConfigTables.cpo IOKitBSDInit.cpo DINetBootHook.cpo \
	RootDomainUserClient.cpo IOPowerConnection.cpo \
	IOWatchDogTimer.cpo IOPerfControl.cpo IOSkywalkSupport.cpo \
	IOSyncer.cpo IOAsmSupport.o IOPMrootDomain.cpo \
	IOKeyStoreHelper.cpo 

LIBOBJS=

CFILES=\
	$(SOURCE_DIR)/iokit/Kernel/IOHibernateRestoreKernel.c \
	$(SOURCE_DIR)/iokit/Kernel/IOStringFuncs.c 
COBJS=IOHibernateRestoreKernel.o IOStringFuncs.o 

CXXFILES=\
	./DriverKit/OSObject.iig.cpp \
	./DriverKit/OSAction.iig.cpp \
	./DriverKit/IOService.iig.cpp \
	./DriverKit/IOUserClient.iig.cpp \
	./DriverKit/IOMemoryDescriptor.iig.cpp \
	./DriverKit/IOBufferMemoryDescriptor.iig.cpp \
	./DriverKit/IOMemoryMap.iig.cpp \
	./DriverKit/IODispatchSource.iig.cpp \
	./DriverKit/IODispatchQueue.iig.cpp \
	./DriverKit/IOInterruptDispatchSource.iig.cpp \
	./DriverKit/IODataQueueDispatchSource.iig.cpp \
	./DriverKit/IOServiceNotificationDispatchSource.iig.cpp \
	./DriverKit/IOUserServer.iig.cpp \
	./DriverKit/IODMACommand.iig.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOHibernateIO.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOLib.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOLocks.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOConditionLock.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOStartIOKit.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IODeviceTreeSupport.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IORegistryEntry.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOService.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOServicePM.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOPMinformee.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOPMinformeeList.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOPMPowerStateQueue.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOCatalogue.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOPMPowerSource.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOPMPowerSourceList.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOPMGR.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOPolledInterface.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOWorkLoop.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOEventSource.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOInterruptEventSource.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOCommandGate.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOCommand.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOCommandPool.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOCommandQueue.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IODMAEventSource.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOFilterInterruptEventSource.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOTimerEventSource.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOBufferMemoryDescriptor.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IODMACommand.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IODeviceMemory.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOInterleavedMemoryDescriptor.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOMapper.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOMemoryCursor.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOMemoryDescriptor.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOMultiMemoryDescriptor.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IORangeAllocator.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOSubMemoryDescriptor.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOPlatformExpert.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOPlatformIO.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOCPU.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOPlatformActions.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IONVRAM.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IODMAController.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOInterruptController.cpp \
	$(SOURCE_DIR)/iokit/Kernel/PassthruInterruptController.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOUserClient.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOKitDebug.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IODataQueue.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOSharedDataQueue.cpp \
	$(SOURCE_DIR)/iokit/Tests/Tests.cpp \
	$(SOURCE_DIR)/iokit/Tests/TestIOMemoryDescriptor.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOStatistics.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOInterruptAccounting.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOReporter.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOSimpleReporter.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOStateReporter.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOHistogramReporter.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOReportLegend.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IORTC.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOUserServer.cpp \
	$(SOURCE_DIR)/iokit/KernelConfigTables.cpp \
	$(SOURCE_DIR)/iokit/bsddev/IOKitBSDInit.cpp \
	$(SOURCE_DIR)/iokit/bsddev/DINetBootHook.cpp \
	$(SOURCE_DIR)/iokit/Kernel/RootDomainUserClient.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOPowerConnection.cpp \
	$(SOURCE_DIR)/iokit/Families/IOSystemManagement/IOWatchDogTimer.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOPerfControl.cpp \
	$(SOURCE_DIR)/iokit/bsddev/skywalk/IOSkywalkSupport.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOSyncer.cpp \
	$(SOURCE_DIR)/iokit/Kernel/IOPMrootDomain.cpp \
	$(SOURCE_DIR)/iokit/Kernel/i386/IOKeyStoreHelper.cpp 
CXXOBJS=OSObject.iig.cpo OSAction.iig.cpo IOService.iig.cpo \
	IOUserClient.iig.cpo IOMemoryDescriptor.iig.cpo \
	IOBufferMemoryDescriptor.iig.cpo IOMemoryMap.iig.cpo \
	IODispatchSource.iig.cpo IODispatchQueue.iig.cpo \
	IOInterruptDispatchSource.iig.cpo \
	IODataQueueDispatchSource.iig.cpo \
	IOServiceNotificationDispatchSource.iig.cpo IOUserServer.iig.cpo \
	IODMACommand.iig.cpo IOHibernateIO.cpo IOLib.cpo IOLocks.cpo \
	IOConditionLock.cpo IOStartIOKit.cpo IODeviceTreeSupport.cpo \
	IORegistryEntry.cpo IOService.cpo IOServicePM.cpo \
	IOPMinformee.cpo IOPMinformeeList.cpo IOPMPowerStateQueue.cpo \
	IOCatalogue.cpo IOPMPowerSource.cpo IOPMPowerSourceList.cpo \
	IOPMGR.cpo IOPolledInterface.cpo IOWorkLoop.cpo \
	IOEventSource.cpo IOInterruptEventSource.cpo IOCommandGate.cpo \
	IOCommand.cpo IOCommandPool.cpo IOCommandQueue.cpo \
	IODMAEventSource.cpo IOFilterInterruptEventSource.cpo \
	IOTimerEventSource.cpo IOBufferMemoryDescriptor.cpo \
	IODMACommand.cpo IODeviceMemory.cpo \
	IOInterleavedMemoryDescriptor.cpo IOMapper.cpo \
	IOMemoryCursor.cpo IOMemoryDescriptor.cpo \
	IOMultiMemoryDescriptor.cpo IORangeAllocator.cpo \
	IOSubMemoryDescriptor.cpo IOPlatformExpert.cpo IOPlatformIO.cpo \
	IOCPU.cpo IOPlatformActions.cpo IONVRAM.cpo IODMAController.cpo \
	IOInterruptController.cpo PassthruInterruptController.cpo \
	IOUserClient.cpo IOKitDebug.cpo IODataQueue.cpo \
	IOSharedDataQueue.cpo Tests.cpo TestIOMemoryDescriptor.cpo \
	IOStatistics.cpo IOInterruptAccounting.cpo IOReporter.cpo \
	IOSimpleReporter.cpo IOStateReporter.cpo IOHistogramReporter.cpo \
	IOReportLegend.cpo IORTC.cpo IOUserServer.cpo \
	KernelConfigTables.cpo IOKitBSDInit.cpo DINetBootHook.cpo \
	RootDomainUserClient.cpo IOPowerConnection.cpo \
	IOWatchDogTimer.cpo IOPerfControl.cpo IOSkywalkSupport.cpo \
	IOSyncer.cpo IOPMrootDomain.cpo IOKeyStoreHelper.cpo 

SFILES=\
	$(SOURCE_DIR)/iokit/Kernel/x86_64/IOAsmSupport.s 
SOBJS=IOAsmSupport.o 

######################################################################
#BEGIN  Machine dependent Makefile fragment for x86_64
######################################################################
#
# XXX: CFLAGS
#
CWARNFLAGS   = $(CWARNFLAGS_STD) -Wno-unused-parameter  -Wshorten-64-to-32 -Wimplicit-int-conversion
CXXWARNFLAGS = $(CXXWARNFLAGS_STD) -Wno-unused-parameter -Wno-cast-qual -Wno-shadow  -Wshorten-64-to-32 -Wimplicit-int-conversion

# Files that must go in the __HIB segment:
UNCONFIGURED_HIB_FILES=	\
			IOHibernateRestoreKernel.o

HIB_FILES=$(filter $(UNCONFIGURED_HIB_FILES),$(OBJS))

# Unconfigured __HIB files must be Mach-O for "setsegname"
IOHibernateRestoreKernel.o_CFLAGS_ADD += -fno-stack-protector -fno-stack-check $(CFLAGS_NOLTO_FLAG)

######################################################################
#END    Machine dependent Makefile fragment for x86_64
######################################################################

#
# Diagnostic opt-outs.  We need to make this list empty.
#
# DO NOT ADD MORE HERE.
#
# -Wno-cast-align
IODataQueue.cpo_CXXWARNFLAGS_ADD += -Wno-cast-align
IOHibernateIO.cpo_CXXWARNFLAGS_ADD += -Wno-cast-align
IOHibernateRestoreKernel.o_CFLAGS_ADD += -Wno-cast-align
IONVRAM.cpo_CXXWARNFLAGS_ADD += -Wno-cast-align
IOSharedDataQueue.cpo_CXXWARNFLAGS_ADD += -Wno-cast-align
IOUserClient.cpo_CXXWARNFLAGS_ADD += -Wno-cast-align
# -Wno-cast-qual
DINetBootHook.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
IOCatalogue.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
IODMAController.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
IODataQueue.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
IODeviceTreeSupport.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
IOHibernateIO.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
IOInterruptController.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
IOKitBSDInit.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
IOKitDebug.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
IOLib.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
IOLocks.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
IOMapper.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
IOMemoryDescriptor.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
IONVRAM.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
IOPMrootDomain.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
IOPlatformExpert.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
IOPolledInterface.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
IORegistryEntry.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
IOService.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
IOServicePM.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
IOSharedDataQueue.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
IOSimpleReporter.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
IOSkywalkSupport.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
IOStateReporter.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
IOUserClient.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
IOUserServer.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
RootDomainUserClient.cpo_CXXWARNFLAGS_ADD += -Wno-cast-qual
# -Wno-missing-prototypes
IOKitBSDInit.cpo_CXXWARNFLAGS_ADD += -Wno-missing-prototypes
IOKitDebug.cpo_CXXWARNFLAGS_ADD += -Wno-missing-prototypes
IOPMrootDomain.cpo_CXXWARNFLAGS_ADD += -Wno-missing-prototypes
IOUserClient.cpo_CXXWARNFLAGS_ADD += -Wno-missing-prototypes
# -Wno-shadow
IOHibernateIO.cpo_CXXWARNFLAGS_ADD += -Wno-shadow
IOKitDebug.cpo_CXXWARNFLAGS_ADD += -Wno-shadow
IOMemoryDescriptor.cpo_CXXWARNFLAGS_ADD += -Wno-shadow
IOMultiMemoryDescriptor.cpo_CXXWARNFLAGS_ADD += -Wno-shadow
IOPMrootDomain.cpo_CXXWARNFLAGS_ADD += -Wno-shadow
IOPolledInterface.cpo_CXXWARNFLAGS_ADD += -Wno-shadow
IOService.cpo_CXXWARNFLAGS_ADD += -Wno-shadow
IOServicePM.cpo_CXXWARNFLAGS_ADD += -Wno-shadow
IOSharedDataQueue.cpo_CXXWARNFLAGS_ADD += -Wno-shadow
IOTimerEventSource.cpo_CXXWARNFLAGS_ADD += -Wno-shadow
IOUserServer.cpo_CXXWARNFLAGS_ADD += -Wno-shadow
TestIOMemoryDescriptor.cpo_CXXWARNFLAGS_ADD += -Wno-shadow
Tests.cpo_CXXWARNFLAGS_ADD += -Wno-shadow
# -Wno-shadow-field-in-constructor
IOUserServer.cpo_CXXWARNFLAGS_ADD += -Wno-shadow-field-in-constructor
# -Wno-sign-conversion
DINetBootHook.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOBufferMemoryDescriptor.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOCPU.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOCatalogue.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOCommandQueue.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IODMACommand.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IODMAEventSource.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IODeviceTreeSupport.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOFilterInterruptEventSource.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOHibernateIO.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOHibernateRestoreKernel.o_CFLAGS_ADD += -Wno-sign-conversion
IOHistogramReporter.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOInterleavedMemoryDescriptor.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOInterruptAccounting.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOInterruptController.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOInterruptEventSource.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOKitBSDInit.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOKitDebug.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOLib.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOMemoryDescriptor.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOMultiMemoryDescriptor.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IONVRAM.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOPMPowerSource.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOPMrootDomain.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOPlatformActions.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOPlatformExpert.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOPolledInterface.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IORTC.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IORegistryEntry.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOService.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOServicePM.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOSkywalkSupport.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOStartIOKit.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOStatistics.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOStringFuncs.o_CFLAGS_ADD += -Wno-sign-conversion
IOTimerEventSource.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOUserClient.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOUserServer.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
IOWorkLoop.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
RootDomainUserClient.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
TestIOMemoryDescriptor.cpo_CXXWARNFLAGS_ADD += -Wno-sign-conversion
# -Wno-unused-parameter
IOBufferMemoryDescriptor.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IOCatalogue.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IOCommandGate.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IODMACommand.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IODeviceTreeSupport.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IOFilterInterruptEventSource.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IOHibernateIO.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IOHibernateRestoreKernel.o_CFLAGS_ADD += -Wno-unused-parameter
IOInterruptController.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IOInterruptEventSource.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IOKitBSDInit.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IOKitDebug.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IOLib.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IOLocks.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IOMemoryDescriptor.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IOMultiMemoryDescriptor.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IONVRAM.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IOPMrootDomain.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IOPerfControl.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IOPlatformExpert.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IOPolledInterface.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IORTC.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IORegistryEntry.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IOReporter.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IOService.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IOServicePM.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IOSkywalkSupport.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IOStateReporter.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IOUserClient.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IOUserServer.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IOWatchDogTimer.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IOWorkLoop.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
PassthruInterruptController.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
RootDomainUserClient.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
TestIOMemoryDescriptor.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
Tests.cpo_CXXWARNFLAGS_ADD += -Wno-unused-parameter
IODMACommand.iig.cpo_CXXWARNFLAGS_ADD += -Wno-duplicate-decl-specifier

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

-include OSObject.iig.cpd
OSObject.iig.cpo: DriverKit/OSObject.iig.cpp
	${P_RULE_0}
	${P_RULE_1A}DriverKit/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}DriverKit/${P_RULE_4B})
-include OSAction.iig.cpd
OSAction.iig.cpo: DriverKit/OSAction.iig.cpp
	${P_RULE_0}
	${P_RULE_1A}DriverKit/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}DriverKit/${P_RULE_4B})
-include IOService.iig.cpd
IOService.iig.cpo: DriverKit/IOService.iig.cpp
	${P_RULE_0}
	${P_RULE_1A}DriverKit/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}DriverKit/${P_RULE_4B})
-include IOUserClient.iig.cpd
IOUserClient.iig.cpo: DriverKit/IOUserClient.iig.cpp
	${P_RULE_0}
	${P_RULE_1A}DriverKit/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}DriverKit/${P_RULE_4B})
-include IOMemoryDescriptor.iig.cpd
IOMemoryDescriptor.iig.cpo: DriverKit/IOMemoryDescriptor.iig.cpp
	${P_RULE_0}
	${P_RULE_1A}DriverKit/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}DriverKit/${P_RULE_4B})
-include IOBufferMemoryDescriptor.iig.cpd
IOBufferMemoryDescriptor.iig.cpo: DriverKit/IOBufferMemoryDescriptor.iig.cpp
	${P_RULE_0}
	${P_RULE_1A}DriverKit/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}DriverKit/${P_RULE_4B})
-include IOMemoryMap.iig.cpd
IOMemoryMap.iig.cpo: DriverKit/IOMemoryMap.iig.cpp
	${P_RULE_0}
	${P_RULE_1A}DriverKit/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}DriverKit/${P_RULE_4B})
-include IODispatchSource.iig.cpd
IODispatchSource.iig.cpo: DriverKit/IODispatchSource.iig.cpp
	${P_RULE_0}
	${P_RULE_1A}DriverKit/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}DriverKit/${P_RULE_4B})
-include IODispatchQueue.iig.cpd
IODispatchQueue.iig.cpo: DriverKit/IODispatchQueue.iig.cpp
	${P_RULE_0}
	${P_RULE_1A}DriverKit/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}DriverKit/${P_RULE_4B})
-include IOInterruptDispatchSource.iig.cpd
IOInterruptDispatchSource.iig.cpo: DriverKit/IOInterruptDispatchSource.iig.cpp
	${P_RULE_0}
	${P_RULE_1A}DriverKit/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}DriverKit/${P_RULE_4B})
-include IODataQueueDispatchSource.iig.cpd
IODataQueueDispatchSource.iig.cpo: DriverKit/IODataQueueDispatchSource.iig.cpp
	${P_RULE_0}
	${P_RULE_1A}DriverKit/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}DriverKit/${P_RULE_4B})
-include IOServiceNotificationDispatchSource.iig.cpd
IOServiceNotificationDispatchSource.iig.cpo: DriverKit/IOServiceNotificationDispatchSource.iig.cpp
	${P_RULE_0}
	${P_RULE_1A}DriverKit/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}DriverKit/${P_RULE_4B})
-include IOUserServer.iig.cpd
IOUserServer.iig.cpo: DriverKit/IOUserServer.iig.cpp
	${P_RULE_0}
	${P_RULE_1A}DriverKit/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}DriverKit/${P_RULE_4B})
-include IODMACommand.iig.cpd
IODMACommand.iig.cpo: DriverKit/IODMACommand.iig.cpp
	${P_RULE_0}
	${P_RULE_1A}DriverKit/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}DriverKit/${P_RULE_4B})
-include IOHibernateIO.cpd
IOHibernateIO.cpo: $(SOURCE_DIR)/iokit/Kernel/IOHibernateIO.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOHibernateRestoreKernel.d
IOHibernateRestoreKernel.o: $(SOURCE_DIR)/iokit/Kernel/IOHibernateRestoreKernel.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${C_RULE_4B})
-include IOLib.cpd
IOLib.cpo: $(SOURCE_DIR)/iokit/Kernel/IOLib.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOLocks.cpd
IOLocks.cpo: $(SOURCE_DIR)/iokit/Kernel/IOLocks.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOConditionLock.cpd
IOConditionLock.cpo: $(SOURCE_DIR)/iokit/Kernel/IOConditionLock.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOStartIOKit.cpd
IOStartIOKit.cpo: $(SOURCE_DIR)/iokit/Kernel/IOStartIOKit.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IODeviceTreeSupport.cpd
IODeviceTreeSupport.cpo: $(SOURCE_DIR)/iokit/Kernel/IODeviceTreeSupport.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IORegistryEntry.cpd
IORegistryEntry.cpo: $(SOURCE_DIR)/iokit/Kernel/IORegistryEntry.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOService.cpd
IOService.cpo: $(SOURCE_DIR)/iokit/Kernel/IOService.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOServicePM.cpd
IOServicePM.cpo: $(SOURCE_DIR)/iokit/Kernel/IOServicePM.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOPMinformee.cpd
IOPMinformee.cpo: $(SOURCE_DIR)/iokit/Kernel/IOPMinformee.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOPMinformeeList.cpd
IOPMinformeeList.cpo: $(SOURCE_DIR)/iokit/Kernel/IOPMinformeeList.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOPMPowerStateQueue.cpd
IOPMPowerStateQueue.cpo: $(SOURCE_DIR)/iokit/Kernel/IOPMPowerStateQueue.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOCatalogue.cpd
IOCatalogue.cpo: $(SOURCE_DIR)/iokit/Kernel/IOCatalogue.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOPMPowerSource.cpd
IOPMPowerSource.cpo: $(SOURCE_DIR)/iokit/Kernel/IOPMPowerSource.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOPMPowerSourceList.cpd
IOPMPowerSourceList.cpo: $(SOURCE_DIR)/iokit/Kernel/IOPMPowerSourceList.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOPMGR.cpd
IOPMGR.cpo: $(SOURCE_DIR)/iokit/Kernel/IOPMGR.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOPolledInterface.cpd
IOPolledInterface.cpo: $(SOURCE_DIR)/iokit/Kernel/IOPolledInterface.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOWorkLoop.cpd
IOWorkLoop.cpo: $(SOURCE_DIR)/iokit/Kernel/IOWorkLoop.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOEventSource.cpd
IOEventSource.cpo: $(SOURCE_DIR)/iokit/Kernel/IOEventSource.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOInterruptEventSource.cpd
IOInterruptEventSource.cpo: $(SOURCE_DIR)/iokit/Kernel/IOInterruptEventSource.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOCommandGate.cpd
IOCommandGate.cpo: $(SOURCE_DIR)/iokit/Kernel/IOCommandGate.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOCommand.cpd
IOCommand.cpo: $(SOURCE_DIR)/iokit/Kernel/IOCommand.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOCommandPool.cpd
IOCommandPool.cpo: $(SOURCE_DIR)/iokit/Kernel/IOCommandPool.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOCommandQueue.cpd
IOCommandQueue.cpo: $(SOURCE_DIR)/iokit/Kernel/IOCommandQueue.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IODMAEventSource.cpd
IODMAEventSource.cpo: $(SOURCE_DIR)/iokit/Kernel/IODMAEventSource.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOFilterInterruptEventSource.cpd
IOFilterInterruptEventSource.cpo: $(SOURCE_DIR)/iokit/Kernel/IOFilterInterruptEventSource.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOTimerEventSource.cpd
IOTimerEventSource.cpo: $(SOURCE_DIR)/iokit/Kernel/IOTimerEventSource.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOBufferMemoryDescriptor.cpd
IOBufferMemoryDescriptor.cpo: $(SOURCE_DIR)/iokit/Kernel/IOBufferMemoryDescriptor.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IODMACommand.cpd
IODMACommand.cpo: $(SOURCE_DIR)/iokit/Kernel/IODMACommand.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IODeviceMemory.cpd
IODeviceMemory.cpo: $(SOURCE_DIR)/iokit/Kernel/IODeviceMemory.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOInterleavedMemoryDescriptor.cpd
IOInterleavedMemoryDescriptor.cpo: $(SOURCE_DIR)/iokit/Kernel/IOInterleavedMemoryDescriptor.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOMapper.cpd
IOMapper.cpo: $(SOURCE_DIR)/iokit/Kernel/IOMapper.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOMemoryCursor.cpd
IOMemoryCursor.cpo: $(SOURCE_DIR)/iokit/Kernel/IOMemoryCursor.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOMemoryDescriptor.cpd
IOMemoryDescriptor.cpo: $(SOURCE_DIR)/iokit/Kernel/IOMemoryDescriptor.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOMultiMemoryDescriptor.cpd
IOMultiMemoryDescriptor.cpo: $(SOURCE_DIR)/iokit/Kernel/IOMultiMemoryDescriptor.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IORangeAllocator.cpd
IORangeAllocator.cpo: $(SOURCE_DIR)/iokit/Kernel/IORangeAllocator.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOSubMemoryDescriptor.cpd
IOSubMemoryDescriptor.cpo: $(SOURCE_DIR)/iokit/Kernel/IOSubMemoryDescriptor.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOPlatformExpert.cpd
IOPlatformExpert.cpo: $(SOURCE_DIR)/iokit/Kernel/IOPlatformExpert.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOPlatformIO.cpd
IOPlatformIO.cpo: $(SOURCE_DIR)/iokit/Kernel/IOPlatformIO.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOCPU.cpd
IOCPU.cpo: $(SOURCE_DIR)/iokit/Kernel/IOCPU.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOPlatformActions.cpd
IOPlatformActions.cpo: $(SOURCE_DIR)/iokit/Kernel/IOPlatformActions.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IONVRAM.cpd
IONVRAM.cpo: $(SOURCE_DIR)/iokit/Kernel/IONVRAM.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IODMAController.cpd
IODMAController.cpo: $(SOURCE_DIR)/iokit/Kernel/IODMAController.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOInterruptController.cpd
IOInterruptController.cpo: $(SOURCE_DIR)/iokit/Kernel/IOInterruptController.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include PassthruInterruptController.cpd
PassthruInterruptController.cpo: $(SOURCE_DIR)/iokit/Kernel/PassthruInterruptController.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOUserClient.cpd
IOUserClient.cpo: $(SOURCE_DIR)/iokit/Kernel/IOUserClient.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOKitDebug.cpd
IOKitDebug.cpo: $(SOURCE_DIR)/iokit/Kernel/IOKitDebug.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IODataQueue.cpd
IODataQueue.cpo: $(SOURCE_DIR)/iokit/Kernel/IODataQueue.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOSharedDataQueue.cpd
IOSharedDataQueue.cpo: $(SOURCE_DIR)/iokit/Kernel/IOSharedDataQueue.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include Tests.cpd
Tests.cpo: $(SOURCE_DIR)/iokit/Tests/Tests.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Tests/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Tests/${P_RULE_4B})
-include TestIOMemoryDescriptor.cpd
TestIOMemoryDescriptor.cpo: $(SOURCE_DIR)/iokit/Tests/TestIOMemoryDescriptor.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Tests/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Tests/${P_RULE_4B})
-include IOStatistics.cpd
IOStatistics.cpo: $(SOURCE_DIR)/iokit/Kernel/IOStatistics.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOInterruptAccounting.cpd
IOInterruptAccounting.cpo: $(SOURCE_DIR)/iokit/Kernel/IOInterruptAccounting.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOReporter.cpd
IOReporter.cpo: $(SOURCE_DIR)/iokit/Kernel/IOReporter.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOSimpleReporter.cpd
IOSimpleReporter.cpo: $(SOURCE_DIR)/iokit/Kernel/IOSimpleReporter.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOStateReporter.cpd
IOStateReporter.cpo: $(SOURCE_DIR)/iokit/Kernel/IOStateReporter.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOHistogramReporter.cpd
IOHistogramReporter.cpo: $(SOURCE_DIR)/iokit/Kernel/IOHistogramReporter.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOReportLegend.cpd
IOReportLegend.cpo: $(SOURCE_DIR)/iokit/Kernel/IOReportLegend.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IORTC.cpd
IORTC.cpo: $(SOURCE_DIR)/iokit/Kernel/IORTC.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOStringFuncs.d
IOStringFuncs.o: $(SOURCE_DIR)/iokit/Kernel/IOStringFuncs.c
	${C_RULE_0}
	${C_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${C_RULE_1B}
	${C_RULE_2}
	${C_RULE_3}
	$(if ${C_RULE_4A},${C_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${C_RULE_4B})
-include IOUserServer.cpd
IOUserServer.cpo: $(SOURCE_DIR)/iokit/Kernel/IOUserServer.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include KernelConfigTables.cpd
KernelConfigTables.cpo: $(SOURCE_DIR)/iokit/KernelConfigTables.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/${P_RULE_4B})
-include IOKitBSDInit.cpd
IOKitBSDInit.cpo: $(SOURCE_DIR)/iokit/bsddev/IOKitBSDInit.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/bsddev/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/bsddev/${P_RULE_4B})
-include DINetBootHook.cpd
DINetBootHook.cpo: $(SOURCE_DIR)/iokit/bsddev/DINetBootHook.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/bsddev/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/bsddev/${P_RULE_4B})
-include RootDomainUserClient.cpd
RootDomainUserClient.cpo: $(SOURCE_DIR)/iokit/Kernel/RootDomainUserClient.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOPowerConnection.cpd
IOPowerConnection.cpo: $(SOURCE_DIR)/iokit/Kernel/IOPowerConnection.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOWatchDogTimer.cpd
IOWatchDogTimer.cpo: $(SOURCE_DIR)/iokit/Families/IOSystemManagement/IOWatchDogTimer.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Families/IOSystemManagement/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Families/IOSystemManagement/${P_RULE_4B})
-include IOPerfControl.cpd
IOPerfControl.cpo: $(SOURCE_DIR)/iokit/Kernel/IOPerfControl.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOSkywalkSupport.cpd
IOSkywalkSupport.cpo: $(SOURCE_DIR)/iokit/bsddev/skywalk/IOSkywalkSupport.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/bsddev/skywalk/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/bsddev/skywalk/${P_RULE_4B})
-include IOSyncer.cpd
IOSyncer.cpo: $(SOURCE_DIR)/iokit/Kernel/IOSyncer.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOAsmSupport.d
IOAsmSupport.o: $(SOURCE_DIR)/iokit/Kernel/x86_64/IOAsmSupport.s
	${S_RULE_0}
	${S_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/x86_64/${S_RULE_1B}
	${S_RULE_2}
-include IOPMrootDomain.cpd
IOPMrootDomain.cpo: $(SOURCE_DIR)/iokit/Kernel/IOPMrootDomain.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/${P_RULE_4B})
-include IOKeyStoreHelper.cpd
IOKeyStoreHelper.cpo: $(SOURCE_DIR)/iokit/Kernel/i386/IOKeyStoreHelper.cpp
	${P_RULE_0}
	${P_RULE_1A}$(SOURCE_DIR)/iokit/Kernel/i386/${P_RULE_1B}
	${P_RULE_2}
	${P_RULE_3}
	$(if ${P_RULE_4A},${P_RULE_4A}$(SOURCE_DIR)/iokit/Kernel/i386/${P_RULE_4B})

include $(MakeInc_rule)
include $(MakeInc_dir)
