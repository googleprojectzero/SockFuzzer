cmake_minimum_required(VERSION 3.5.1)
project(libxnu)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Force colorful output
add_compile_options(-fcolor-diagnostics)

set(XNU_DEFINES
    -DAH_ALL_CRYPTO
    -DAPPLE
    -DBINDFS
    -DCONFIG_32BIT_TELEMETRY
    -DCONFIG_AIO_MAX=90
    -DCONFIG_AIO_PROCESS_MAX=16
    -DCONFIG_AIO_THREAD_COUNT=4
    -DCONFIG_APPLEDOUBLE
    -DCONFIG_ARCADE
    -DCONFIG_ATM
    -DCONFIG_BACKGROUND_QUEUE
    -DCONFIG_BASESYSTEMROOT
    -DCONFIG_BLOCKS
    -DCONFIG_COALITIONS
    -DCONFIG_CODE_DECRYPTION
    -DCONFIG_COREDUMP
    -DCONFIG_CSR
    -DCONFIG_DATALESS_FILES
    -DCONFIG_DELAY_IDLE_SLEEP
    -DCONFIG_DEV_KMEM
    -DCONFIG_DIRTYSTATUS_TRACKING
    -DCONFIG_DYNAMIC_CODE_SIGNING
    -DCONFIG_EXT_RESOLVER
    -DCONFIG_FIRMLINKS
    -DCONFIG_GZALLOC
    -DCONFIG_ICMP_BANDLIM=250
    -DCONFIG_IMAGEBOOT_CHUNKLIST
    -DCONFIG_IMG4
    -DCONFIG_IMGSRC_ACCESS
    -DCONFIG_IOSCHED
    -DCONFIG_IPC_TABLE_ENTRIES_STEPS=256
    -DCONFIG_KAS_INFO
    -DCONFIG_KDP_INTERACTIVE_DEBUGGING
    -DCONFIG_KEC_FIPS
    -DCONFIG_KEXT_BASEMENT
    -DCONFIG_KEYPAGE_WP
    -DCONFIG_KN_HASHSIZE=64
    -DCONFIG_LEDGER_INTERVAL_MAX
    -DCONFIG_LTABLE_DEBUG
    -DCONFIG_LTABLE_STATS
    -DCONFIG_MACF_LAZY_VNODE_LABELS
    -DCONFIG_MACH_APPROXIMATE_TIME
    -DCONFIG_MACH_BRIDGE_SEND_TIME
    -DCONFIG_MAXVIFS=32
    -DCONFIG_MAX_CLUSTERS=8
    -DCONFIG_MAX_THREADS=500
    -DCONFIG_MBUF_JUMBO
    -DCONFIG_MCA
    -DCONFIG_MEMORYSTATUS
    -DCONFIG_MFCTBLSIZ=256
    -DCONFIG_MIN_NBUF=256
    -DCONFIG_MIN_NIOBUF=128
    -DCONFIG_MNT_ROOTSNAP
    -DCONFIG_MNT_SUID
    -DCONFIG_MOUNT_PREBOOTRECOVERY
    -DCONFIG_MOUNT_VM
    -DCONFIG_MSG_BSIZE=CONFIG_MSG_BSIZE_DEV
    -DCONFIG_MSG_BSIZE_DEV=131072
    -DCONFIG_MSG_BSIZE_REL=16384
    -DCONFIG_MTRR
    -DCONFIG_NC_HASH=4096
    -DCONFIG_NETBOOT
    -DCONFIG_NFS_GSS
    -DCONFIG_NMBCLUSTERS=512
    -DCONFIG_PERSONAS
    -DCONFIG_PHYS_WRITE_ACCT
    -DCONFIG_PROC_UDATA_STORAGE
    -DCONFIG_PROC_UUID_POLICY
    -DCONFIG_PROTECT
    -DCONFIG_REQUIRES_U32_MUNGING
    -DCONFIG_ROSV_STARTUP
    -DCONFIG_SCHED_GRRR
    -DCONFIG_SCHED_GRRR_CORE
    -DCONFIG_SCHED_MULTIQ
    -DCONFIG_SCHED_PROTO
    -DCONFIG_SCHED_SFI
    -DCONFIG_SCHED_TIMESHARE_CORE
    -DCONFIG_SCHED_TRADITIONAL
    -DCONFIG_SEARCHFS
    -DCONFIG_SETUID
    -DCONFIG_SLEEP
    -DCONFIG_SYSDIAGNOSE
    -DCONFIG_TASKWATCH
    -DCONFIG_TASK_MAX=1024
    -DCONFIG_TASK_ZONE_INFO
    -DCONFIG_TCBHASHSIZE=4096
    -DCONFIG_TELEMETRY
    -DCONFIG_THREAD_MAX=2560
    -DCONFIG_VFS_NAMES=4096
    -DCONFIG_VMX
    -DCONFIG_VNGUARD
    -DCONFIG_VNODES=263168
    -DCONFIG_VOLFS
    -DCONFIG_VSPRINTF
    -DCONFIG_WAITQ_DEBUG
    -DCONFIG_WAITQ_STATS
    -DCONFIG_WORKLOOP_DEBUG
    -DCONFIG_WORKQUEUE
    -DCONFIG_XNUPOST
    -DCONFIG_ZALLOC_SEQUESTER
    -DCONFIG_ZCACHE
    -DCONFIG_ZLEAKS
    -DCONFIG_ZLEAK_ALLOCATION_MAP_NUM=16384
    -DCONFIG_ZLEAK_TRACE_MAP_NUM=8192
    -DCONFIG_ZONE_MAP_MIN=120586240
    -DCONTENT_FILTER
    -DCOPYOUT_SHIM
    -DCRYPTO_SHA2
    -DFLOW_DIVERT
    -DHYPERVISOR
    -DICMP_BANDLIM
    -DIFNET_INPUT_SANITY_CHK
    -DIMPORTANCE_TRACE
    -DIOKIT
    -DIOKITCPP
    -DIOKITSTATS
    -DIOTRACKING
    -DIPSEC
    -DIPSEC_ESP
    -DKERNEL
    -DKERNEL_PRIVATE
    -DKPC
    -DKPERF
    -DLIBKERNCPP
    -DLOCK_STATS
    -DLP64
    -DMACH
    -DMACH_BSD
    -DMACH_KERNEL
    -DMULTICAST
    -DMULTIPATH
    -DNAMEDSTREAMS
    -DNECP
    -DNO_DIRECT_RPC
    -DNULLFS
    -DOLD_SEMWAIT_SIGNAL
    -DPACKET_MANGLER
    -DPAGE_SIZE_FIXED
    -DPAL_I386
    -DPGO
    -DPLATFORM_MacOSX
    -DPRIVATE
    -DPSYNCH
    -DSERIAL_CONSOLE
    -DTRAFFIC_MGT
    -DVIDEO_CONSOLE
    -DVM_PRESSURE_EVENTS
    -DX86_64
    -DXNU_KERNEL_PRIVATE
    -DXNU_KERN_EVENT_DATA_IS_VLA
    # TODO(nedwill): remove this flag and get support for copyin_chk/copyout_chk
    # working in case source fortifications can help find more bugs.
    -D_FORTIFY_SOURCE=0
    -D__MACHO__=1
    -D__X86_64__
    -Dvolatile=__volatile
    -Dx86_64
    -URC_ENABLE_XNU_PRODUCT_INFO_FILTER
    -include
    meta_features.h
)

set(BSD_DEFINES
    -DBSD_BUILD
    -DBSD_KERNEL_PRIVATE
    -DCONFIG_SERIAL_KDP
    -DDEBUG
    -DDRIVER_PRIVATE
    -DENCRYPTED_SWAP
    -DHIBERNATION
    -DKERNEL_BUILD
    -DLP64_DEBUG=0
    -DMACH_KDP
    -DMACH_MP_DEBUG
    -DTARGET_OS_IPHONE=0
    -DTARGET_OS_OSX=1
    -DXNU_TARGET_OS_OSX=1
    -D_KERNEL_BUILD
    -D__APPLE__
)

set(OSFMK_DEFINES
    -DBOND
    -DCONFIG_AUDIT
    -DCONFIG_FSE
    -DCONFIG_IMAGEBOOT
    -DCONFIG_MACF
    -DCONFIG_MACF_SOCKET_SUBSET
    -DCONFIG_NFS4
    -DCONFIG_TRIGGERS
    -DDEVFS
    -DDUMMYNET
    -DFDESC
    -DFIFO
    -DFS_COMPRESSION
    -DIF_BRIDGE
    -DIF_FAKE
    -DIF_HEADLESS
    -DINET
    -DKERNEL_BASE_OFFSET=0x100000
    -DMACH_COMPAT
    -DMACH_FASTLINK
    -DMACH_KERNEL_PRIVATE
    -DMPTCP
    -DNETWORKING
    -DNFSCLIENT
    -DNFSSERVER
    -DPF
    -DPFLOG
    -DQUOTA
    -DSENDFILE
    -DSIXLOWPAN
    -DSOCKETS
    -DSYSV_MSG
    -DSYSV_SEM
    -DSYSV_SHM
    -DVLAN
    -DXNU_TARGET_OS_OSX
    -DZLIB
)

set(SAN_DEFINES
    -DKASAN_OFFSET=0
    -DKASAN_SCALE=0
)

set(XNU_WARNING_FLAGS
    -Wno-address-of-packed-member -Wno-unguarded-availability-new
    -Wno-pointer-to-int-cast -Wno-format -Wunused-result -Werror
)

set(XNU_C_FLAGS
    -nostdinc
    -fno-builtin
    -fno-common
    -fsigned-bitfields
    -g
    -fblocks
    -O1
    -ftrivial-auto-var-init=pattern
    ${XNU_WARNING_FLAGS}
    ${XNU_DEFINES}
)

set(LIBFUZZER_SOURCES
    third_party/fuzzer/FuzzerCrossOver.cpp
    third_party/fuzzer/FuzzerDataFlowTrace.cpp
    third_party/fuzzer/FuzzerDriver.cpp
    third_party/fuzzer/FuzzerExtFunctionsDlsym.cpp
    third_party/fuzzer/FuzzerExtFunctionsWeak.cpp
    third_party/fuzzer/FuzzerExtFunctionsWindows.cpp
    third_party/fuzzer/FuzzerExtraCounters.cpp
    third_party/fuzzer/FuzzerFork.cpp
    third_party/fuzzer/FuzzerIO.cpp
    third_party/fuzzer/FuzzerIOPosix.cpp
    third_party/fuzzer/FuzzerIOWindows.cpp
    third_party/fuzzer/FuzzerLoop.cpp
    third_party/fuzzer/FuzzerMain.cpp
    third_party/fuzzer/FuzzerMerge.cpp
    third_party/fuzzer/FuzzerMutate.cpp
    third_party/fuzzer/FuzzerSHA1.cpp
    third_party/fuzzer/FuzzerTracePC.cpp
    third_party/fuzzer/FuzzerUtil.cpp
    third_party/fuzzer/FuzzerUtilDarwin.cpp
    third_party/fuzzer/FuzzerUtilFuchsia.cpp
    third_party/fuzzer/FuzzerUtilLinux.cpp
    third_party/fuzzer/FuzzerUtilPosix.cpp
    third_party/fuzzer/FuzzerUtilWindows.cpp
)

set(LIBFUZZER_HEADERS
    third_party/fuzzer/FuzzerBuiltins.h
    third_party/fuzzer/FuzzerBuiltinsMsvc.h
    third_party/fuzzer/FuzzerCommand.h
    third_party/fuzzer/FuzzerCorpus.h
    third_party/fuzzer/FuzzerDataFlowTrace.h
    third_party/fuzzer/FuzzerDefs.h
    third_party/fuzzer/FuzzerDictionary.h
    third_party/fuzzer/FuzzerExtFunctions.h
    third_party/fuzzer/FuzzerFork.h
    third_party/fuzzer/FuzzerInterface.h
    third_party/fuzzer/FuzzerInternal.h
    third_party/fuzzer/FuzzerIO.h
    third_party/fuzzer/FuzzerMerge.h
    third_party/fuzzer/FuzzerMutate.h
    third_party/fuzzer/FuzzerOptions.h
    third_party/fuzzer/FuzzerRandom.h
    third_party/fuzzer/FuzzerSHA1.h
    third_party/fuzzer/FuzzerTracePC.h
    third_party/fuzzer/FuzzerUtil.h
    third_party/fuzzer/FuzzerValueBitMap.h
)

add_library(fuzzer STATIC ${LIBFUZZER_SOURCES} ${LIBFUZZER_HEADERS})
target_compile_options(fuzzer PRIVATE -g -std=c++11 -Werror)

set(XNU_SOURCES
    bsd/conf/param.c
    bsd/kern/kern_asl.c
    bsd/kern/kern_control.c
    bsd/kern/kern_descrip.c
    bsd/kern/kern_event.c
    bsd/kern/kern_newsysctl.c
    bsd/kern/kern_sig.c
    bsd/kern/kern_subr.c
    bsd/kern/kpi_mbuf.c
    bsd/kern/kpi_socket.c
    bsd/kern/kpi_socketfilter.c
    bsd/kern/subr_eventhandler.c
    bsd/kern/sys_domain.c
    bsd/kern/sys_generic.c
    bsd/kern/sys_pipe.c
    bsd/kern/sys_reason.c
    bsd/kern/sys_socket.c
    bsd/kern/uipc_domain.c
    bsd/kern/uipc_mbuf.c
    bsd/kern/uipc_mbuf2.c
    bsd/kern/uipc_proto.c
    bsd/kern/uipc_socket.c
    bsd/kern/uipc_socket2.c
    bsd/kern/uipc_syscalls.c
    bsd/kern/uipc_usrreq.c
    bsd/kern/vsock_domain.c
    bsd/net/bpf.c
    bsd/net/bpf_filter.c
    bsd/net/classq/classq.c
    bsd/net/classq/classq_fq_codel.c
    bsd/net/classq/classq_sfb.c
    bsd/net/classq/classq_subr.c
    bsd/net/content_filter.c
    bsd/net/devtimer.c
    bsd/net/dlil.c
    bsd/net/ether_inet6_pr_module.c
    bsd/net/ether_if_module.c
    bsd/net/ether_inet_pr_module.c
    bsd/net/flowadv.c
    bsd/net/frame802154.c
    bsd/net/if.c
    bsd/net/if_6lowpan.c
    bsd/net/if_bridge.c
    bsd/net/if_bond.c
    bsd/net/if_fake.c
    bsd/net/if_llatbl.c
    bsd/net/if_llreach.c
    bsd/net/if_loop.c
    bsd/net/if_low_power_mode.c
    bsd/net/if_headless.c
    bsd/net/if_ipsec.c
    bsd/net/if_ports_used.c
    bsd/net/if_stf.c
    bsd/net/if_vlan.c
    bsd/net/init.c
    bsd/net/kpi_interface.c
    bsd/net/kpi_interfacefilter.c
    bsd/net/kpi_protocol.c
    bsd/net/linkaddr.c
    bsd/net/multicast_list.c
    bsd/net/ndrv.c
    bsd/net/net_str_id.c
    bsd/net/pf.c
    bsd/net/pf_if.c
    bsd/net/pf_ioctl.c
    bsd/net/pf_norm.c
    bsd/net/pf_osfp.c
    bsd/net/pf_pbuf.c
    bsd/net/pf_ruleset.c
    bsd/net/pf_table.c
    bsd/net/sixxlowpan.c
    bsd/net/necp.c
    bsd/net/necp_client.c
    bsd/net/net_perf.c
    bsd/net/network_agent.c
    bsd/net/ntstat.c
    bsd/net/pktap.c
    bsd/net/pktsched/pktsched.c
    bsd/net/pktsched/pktsched_fq_codel.c
    bsd/net/pktsched/pktsched_netem.c
    bsd/net/raw_cb.c
    bsd/net/raw_usrreq.c
    bsd/net/radix.c
    bsd/net/route.c
    bsd/net/rtsock.c
    bsd/netinet/flow_divert.c
    bsd/netinet/in.c
    bsd/netinet/igmp.c
    bsd/netinet/in_arp.c
    bsd/netinet/in_cksum.c
    bsd/netinet/in_mcast.c
    bsd/netinet/in_pcb.c
    bsd/netinet/in_pcblist.c
    bsd/netinet/in_proto.c
    bsd/netinet/in_rmx.c
    bsd/netinet/in_tclass.c
    bsd/netinet/ip_dummynet.c
    bsd/netinet/ip_ecn.c
    bsd/netinet/ip_encap.c
    bsd/netinet/ip_icmp.c
    bsd/netinet/ip_id.c
    bsd/netinet/ip_input.c
    bsd/netinet/ip_output.c
    bsd/netinet/kpi_ipfilter.c
    bsd/netinet/mp_pcb.c
    bsd/netinet/mp_pcb.h
    bsd/netinet/mp_proto.c
    bsd/netinet/mptcp.c
    bsd/netinet/mptcp.h
    bsd/netinet/mptcp_opt.c
    bsd/netinet/mptcp_opt.h
    bsd/netinet/mptcp_subr.c
    bsd/netinet/mptcp_timer.c
    bsd/netinet/mptcp_timer.h
    bsd/netinet/mptcp_usrreq.c
    bsd/netinet/raw_ip.c
    bsd/netinet/tcp_cache.c
    bsd/netinet/tcp_cc.c
    bsd/netinet/tcp_cubic.c
    bsd/netinet/tcp_input.c
    bsd/netinet/tcp_ledbat.c
    bsd/netinet/tcp_log.c
    bsd/netinet/tcp_newreno.c
    bsd/netinet/tcp_output.c
    bsd/netinet/tcp_sack.c
    bsd/netinet/tcp_subr.c
    bsd/netinet/tcp_timer.c
    bsd/netinet/tcp_usrreq.c
    bsd/netinet/udp_usrreq.c
    bsd/netinet6/ah_core.c
    bsd/netinet6/ah_input.c
    bsd/netinet6/ah_output.c
    bsd/netinet6/dest6.c
    bsd/netinet6/esp_chachapoly.c
    bsd/netinet6/esp_core.c
    bsd/netinet6/esp_input.c
    bsd/netinet6/esp_output.c
    bsd/netinet6/esp_rijndael.c
    bsd/netinet6/frag6.c
    bsd/netinet6/icmp6.c
    bsd/netinet6/in6.c
    bsd/netinet6/in6_cga.c
    bsd/netinet6/in6_cksum.c
    bsd/netinet6/in6_ifattach.c
    bsd/netinet6/in6_mcast.c
    bsd/netinet6/in6_pcb.c
    bsd/netinet6/in6_proto.c
    bsd/netinet6/in6_rmx.c
    bsd/netinet6/in6_src.c
    bsd/netinet6/ipsec.c
    bsd/netinet6/ip6_forward.c
    bsd/netinet6/ip6_input.c
    bsd/netinet6/ip6_id.c
    bsd/netinet6/ip6_output.c
    bsd/netinet6/mld6.c
    bsd/netinet6/nd6.c
    bsd/netinet6/nd6_nbr.c
    bsd/netinet6/nd6_prproxy.c
    bsd/netinet6/nd6_rti.c
    bsd/netinet6/nd6_rtr.c
    bsd/netinet6/nd6_send.c
    bsd/netinet6/raw_ip6.c
    bsd/netinet6/route6.c
    bsd/netinet6/scope6.c
    bsd/netinet6/udp6_output.c
    bsd/netinet6/udp6_usrreq.c
    bsd/netkey/key.c
    bsd/netkey/keydb.c
    bsd/netkey/keysock.c
    bsd/sys/mcache.h
    libkern/crypto/corecrypto_chacha20poly1305.c
    libkern/crypto/corecrypto_des.c
    libkern/crypto/corecrypto_sha2.c
    libkern/gen/OSAtomicOperations.c
    security/mac_system.c
    fuzz/api/syscall_wrappers.c
    fuzz/api/ioctl.c
    fuzz/api/backend.c
    fuzz/fakes/stubs.c
    fuzz/fakes/thread.c
    fuzz/fakes/fake_impls.c
    fuzz/fakes/mbuf.c
)

set(XNU_INCLUDES
    .
    BUILD/obj/EXPORT_HDRS/bsd
    BUILD/obj/EXPORT_HDRS/osfmk
    BUILD/obj/EXPORT_HDRS/libkern
    BUILD/obj/EXPORT_HDRS/iokit
    BUILD/obj/EXPORT_HDRS/pexpert
    BUILD/obj/EXPORT_HDRS/libsa
    BUILD/obj/EXPORT_HDRS/security
    BUILD/obj/EXPORT_HDRS/san
    EXTERNAL_HEADERS
)

# If SANITIZER flag is passed, we are building for OSS-Fuzz. This means we
# already pass the build CFLAGs/LDFLAGS it wants via the environment variables.
if(DEFINED ENV{SANITIZER})
  if($ENV{SANITIZER} MATCHES "address")
    set(FUZZER_SOURCES fuzz/fakes/san.c san/kasan-memintrinsics.c)
    set(FUZZER_DEFINES -DKASAN)
  endif()
else()
  set(FUZZER_CXX_FLAGS -fsanitize=address,fuzzer-no-link)
  set(FUZZER_LD_FLAGS -fsanitize=address)
  set(FUZZER_SOURCES fuzz/fakes/san.c san/kasan-memintrinsics.c)
  set(FUZZER_DEFINES -DKASAN)
endif()

# These must be built separately due to header incompatabilities
set(OSFMK_SOURCES
    fuzz/fakes/zalloc.c
    fuzz/fakes/osfmk_stubs.c
    # osfmk/x86_64/loose_ends.c
)

set(BSD_INCLUDES ${XNU_INCLUDES} BUILD/obj/DEBUG_X86_64/bsd/DEBUG bsd san)

set(OSFMK_INCLUDES ${XNU_INCLUDES} BUILD/obj/DEBUG_X86_64/osfmk/DEBUG osfmk
                   osfmk/libsa
)

# We use an object library so we can include the osfmk objects which require
# different build flags into the libxnu library
add_library(osfmk OBJECT ${OSFMK_SOURCES})
target_include_directories(osfmk PRIVATE ${OSFMK_INCLUDES})
# set_target_properties(osfmk PROPERTIES C_VISIBILITY_PRESET hidden)
set_property(TARGET osfmk PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_options(
  osfmk PRIVATE ${XNU_C_FLAGS} ${OSFMK_DEFINES} ${FUZZER_DEFINES}
                ${FUZZER_CXX_FLAGS}
)

add_library(xnu SHARED ${XNU_SOURCES} ${FUZZER_SOURCES} $<TARGET_OBJECTS:osfmk>)

if(APPLE)
  # Dynamic lookups are needed for us to link correctly when we have
  # mutually dependent targets (net_fuzzer and xnu)
  target_link_options(xnu PRIVATE -undefined dynamic_lookup)
endif(APPLE)

target_include_directories(xnu PRIVATE ${BSD_INCLUDES})
set_target_properties(xnu PROPERTIES C_VISIBILITY_PRESET hidden)
target_compile_options(
  xnu PRIVATE ${XNU_C_FLAGS} ${BSD_DEFINES} ${SAN_DEFINES} -DLIBXNU_BUILD=1 ${FUZZER_DEFINES}
              ${FUZZER_CXX_FLAGS}
)

# Only build coverage builds locally on Linux.
if(NOT DEFINED ENV{SANITIZER} AND NOT APPLE)
  add_library(osfmk-cov OBJECT ${OSFMK_SOURCES})
  target_include_directories(osfmk-cov PRIVATE ${OSFMK_INCLUDES})
  # set_target_properties(osfmk-cov PROPERTIES C_VISIBILITY_PRESET hidden)
  set_property(TARGET osfmk-cov PROPERTY POSITION_INDEPENDENT_CODE ON)
  target_compile_options(
    osfmk-cov
    PRIVATE ${XNU_C_FLAGS} ${OSFMK_DEFINES} -DLIBXNU_BUILD=1
            -fprofile-instr-generate -fcoverage-mapping
  )

  add_library(xnu-cov SHARED ${XNU_SOURCES} $<TARGET_OBJECTS:osfmk-cov>)
  target_include_directories(xnu-cov PRIVATE ${BSD_INCLUDES})
  set_target_properties(xnu-cov PROPERTIES C_VISIBILITY_PRESET hidden)
  target_compile_options(
    xnu-cov
    PRIVATE ${XNU_C_FLAGS} ${BSD_DEFINES} ${SAN_DEFINES} -DLIBXNU_BUILD=1
            -fprofile-instr-generate -fcoverage-mapping
  )
endif()

find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# TODO(nedwill): Import CMakeLists.txt from libprotobuf-mutator folder
add_library(
  protobuf-mutator STATIC
  third_party/libprotobuf-mutator/src/binary_format.cc
  third_party/libprotobuf-mutator/src/mutator.cc
  third_party/libprotobuf-mutator/src/text_format.cc
  third_party/libprotobuf-mutator/src/utf8_fix.cc
  third_party/libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.cc
  third_party/libprotobuf-mutator/src/libfuzzer/libfuzzer_mutator.cc
  third_party/libprotobuf-mutator/src/mutator.h
)

target_include_directories(
  protobuf-mutator PRIVATE third_party/libprotobuf-mutator
)
target_compile_options(protobuf-mutator PRIVATE -std=c++11)

if(APPLE)
  target_link_libraries(protobuf-mutator)
else()
  target_link_libraries(protobuf-mutator protobuf)
endif(APPLE)

protobuf_generate_cpp(NET_PROTO_SRCS NET_PROTO_HDRS fuzz/net_fuzzer.proto)
add_executable(
  net_fuzzer fuzz/net_fuzzer.cc ${NET_PROTO_SRCS} ${NET_PROTO_HDRS}
)
target_include_directories(net_fuzzer PRIVATE third_party/libprotobuf-mutator)
target_compile_options(
  net_fuzzer PRIVATE -g -std=c++11 -Werror -Wno-address-of-packed-member
                     ${FUZZER_CXX_FLAGS}
)
if(APPLE)
  target_link_libraries(
    net_fuzzer ${FUZZER_LD_FLAGS} xnu fuzzer protobuf-mutator
    ${Protobuf_LIBRARIES}
  )
else()
  target_link_libraries(
    net_fuzzer
    ${FUZZER_LD_FLAGS}
    xnu
    fuzzer
    protobuf-mutator
    ${Protobuf_LIBRARIES}
    pthread
    bsd
  )
endif(APPLE)

# if(APPLE) add_executable(net_real fuzz/net_fuzzer.cc ${NET_PROTO_SRCS}
# ${NET_PROTO_HDRS}) target_include_directories(net_real PRIVATE
# libprotobuf-mutator) target_compile_options(net_real PRIVATE -g -std=c++11
# -Wno-address-of-packed-member -Werror) # Notice we don't include libxnu here
# since we use the real kernel. target_link_libraries(net_real fuzzer
# protobuf-mutator ${Protobuf_LIBRARIES}) endif(APPLE)

# Only build coverage builds locally.
if(DEFINED ENV{SANITIZER})

else()
  if(NOT APPLE)
    add_executable(
      net_cov fuzz/net_fuzzer.cc ${NET_PROTO_SRCS} ${NET_PROTO_HDRS}
    )
    target_include_directories(net_cov PRIVATE third_party/libprotobuf-mutator)
    target_compile_options(
      net_cov PRIVATE -g -std=c++11 -Werror -Wno-address-of-packed-member
                      -fprofile-instr-generate -fcoverage-mapping
    )
    target_link_libraries(
      net_cov
      xnu-cov
      fuzzer
      -fprofile-instr-generate
      -fcoverage-mapping
      protobuf-mutator
      ${Protobuf_LIBRARIES}
      bsd
      pthread
      -Wl,--exclude-libs,ALL
    )
  endif(NOT APPLE)
endif()
