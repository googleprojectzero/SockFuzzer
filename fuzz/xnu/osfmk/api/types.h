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

#ifndef OSFMK_API_TYPES_H_
#define OSFMK_API_TYPES_H_

#include <stddef.h>
#include <stdint.h>

#define MACH_MSG_OPTION_NONE 0x00000000

#define MACH_SEND_MSG 0x00000001
#define MACH_RCV_MSG 0x00000002

#define MACH_RCV_LARGE 0x00000004 /* report large message sizes */
#define MACH_RCV_LARGE_IDENTITY \
  0x00000008 /* identify source of large messages */

#define MACH_SEND_TIMEOUT 0x00000010   /* timeout value applies to send */
#define MACH_SEND_OVERRIDE 0x00000020  /* priority override for send */
#define MACH_SEND_INTERRUPT 0x00000040 /* don't restart interrupted sends */
#define MACH_SEND_NOTIFY 0x00000080    /* arm send-possible notify */
#define MACH_SEND_ALWAYS 0x00010000    /* ignore qlimits - kernel only */
#define MACH_SEND_FILTER_NONFATAL \
  0x00010000 /* rejection by message filter should return failure - user only */
#define MACH_SEND_TRAILER 0x00020000      /* sender-provided trailer */
#define MACH_SEND_NOIMPORTANCE 0x00040000 /* msg won't carry importance */
#define MACH_SEND_NODENAP MACH_SEND_NOIMPORTANCE
#define MACH_SEND_IMPORTANCE \
  0x00080000 /* msg carries importance - kernel only */
#define MACH_SEND_SYNC_OVERRIDE \
  0x00100000 /* msg should do sync IPC override (on legacy kernels) */
#define MACH_SEND_PROPAGATE_QOS \
  0x00200000 /* IPC should propagate the caller's QoS */
#define MACH_SEND_SYNC_USE_THRPRI MACH_SEND_PROPAGATE_QOS /* obsolete name */
#define MACH_SEND_KERNEL \
  0x00400000 /* full send from kernel space - kernel only */
#define MACH_SEND_SYNC_BOOTSTRAP_CHECKIN \
  0x00800000 /* special reply port should boost thread doing sync bootstrap checkin */

#define MACH_RCV_TIMEOUT 0x00000100   /* timeout value applies to receive */
#define MACH_RCV_NOTIFY 0x00000000    /* legacy name (value was: 0x00000200) */
#define MACH_RCV_INTERRUPT 0x00000400 /* don't restart interrupted receive */
#define MACH_RCV_VOUCHER 0x00000800   /* willing to receive voucher port */
#define MACH_RCV_OVERWRITE 0x00000000 /* scatter receive (deprecated) */
#define MACH_RCV_GUARDED_DESC \
  0x00001000                          /* Can receive new guarded descriptor */
#define MACH_RCV_SYNC_WAIT 0x00004000 /* sync waiter waiting for rcv */
#define MACH_RCV_SYNC_PEEK 0x00008000 /* sync waiter waiting to peek */

#define MACH_MSG_STRICT_REPLY \
  0x00000200 /* Enforce specific properties about the reply port, and
	                                         * the context in which a thread replies to a message.
	                                         * This flag must be passed on both the SEND and RCV */

typedef uint32_t mach_port_name_t;
typedef uintptr_t mach_vm_offset_t;
typedef size_t mach_vm_size_t;
typedef int vm_purgable_t;
typedef uint64_t user_addr_t;
typedef uint64_t mach_vm_address_t;
typedef uint32_t mach_vm_range_flavor_t;
// type mach_vm_range_recipes_raw_t = array[*:1024] of uint8_t;
typedef uint8_t mach_vm_range_recipes_raw_t[1024];
typedef int kern_return_t;
typedef int boolean_t;
typedef int vm_prot_t;
typedef unsigned int natural_t;
typedef natural_t mach_msg_size_t;
typedef natural_t mach_msg_size_t;
typedef unsigned int mach_msg_priority_t;
typedef natural_t mach_msg_timeout_t;
typedef natural_t mach_port_right_t;
typedef int mach_port_delta_t;
typedef int integer_t;
typedef integer_t mach_msg_option_t;
typedef kern_return_t mach_msg_return_t;

enum MachMsgReturnT {
  MACH_MSG_SUCCESS = 0x00000000,
  MACH_MSG_MASK = 0x00003e00,
  MACH_MSG_IPC_SPACE = 0x00002000,
  MACH_MSG_VM_SPACE = 0x00001000,
  MACH_MSG_IPC_KERNEL = 0x00000800,
  MACH_MSG_VM_KERNEL = 0x00000400,
  MACH_SEND_IN_PROGRESS = 0x10000001,
  MACH_SEND_INVALID_DATA = 0x10000002,
  MACH_SEND_INVALID_DEST = 0x10000003,
  MACH_SEND_TIMED_OUT = 0x10000004,
  MACH_SEND_INVALID_VOUCHER = 0x10000005,
  MACH_SEND_INTERRUPTED = 0x10000007,
  MACH_SEND_MSG_TOO_SMALL = 0x10000008,
  MACH_SEND_INVALID_REPLY = 0x10000009,
  MACH_SEND_INVALID_RIGHT = 0x1000000a,
  MACH_SEND_INVALID_NOTIFY = 0x1000000b,
  MACH_SEND_INVALID_MEMORY = 0x1000000c,
  MACH_SEND_NO_BUFFER = 0x1000000d,
  MACH_SEND_TOO_LARGE = 0x1000000e,
  MACH_SEND_INVALID_TYPE = 0x1000000f,
  MACH_SEND_INVALID_HEADER = 0x10000010,
  MACH_SEND_INVALID_TRAILER = 0x10000011,
  MACH_SEND_INVALID_CONTEXT = 0x10000012,
  MACH_SEND_INVALID_OPTIONS = 0x10000013,
  MACH_SEND_INVALID_RT_OOL_SIZE = 0x10000015,
  MACH_SEND_NO_GRANT_DEST = 0x10000016,
  MACH_SEND_MSG_FILTERED = 0x10000017,
  MACH_SEND_AUX_TOO_SMALL = 0x10000018,
  MACH_SEND_AUX_TOO_LARGE = 0x10000019,
  MACH_RCV_IN_PROGRESS = 0x10004001,
  MACH_RCV_INVALID_NAME = 0x10004002,
  MACH_RCV_TIMED_OUT = 0x10004003,
  MACH_RCV_TOO_LARGE = 0x10004004,
  MACH_RCV_INTERRUPTED = 0x10004005,
  MACH_RCV_PORT_CHANGED = 0x10004006,
  MACH_RCV_INVALID_NOTIFY = 0x10004007,
  MACH_RCV_INVALID_DATA = 0x10004008,
  MACH_RCV_PORT_DIED = 0x10004009,
  MACH_RCV_IN_SET = 0x1000400a,
  MACH_RCV_HEADER_ERROR = 0x1000400b,
  MACH_RCV_BODY_ERROR = 0x1000400c,
  MACH_RCV_INVALID_TYPE = 0x1000400d,
  MACH_RCV_SCATTER_SMALL = 0x1000400e,
  MACH_RCV_INVALID_TRAILER = 0x1000400f,
  MACH_RCV_IN_PROGRESS_TIMED = 0x10004011,
  MACH_RCV_INVALID_REPLY = 0x10004012,
  MACH_RCV_INVALID_ARGUMENTS = 0x10004013,
};

typedef uint64_t mach_msg_option64_t;

// typedef enum : uint64_t {
// 	MACH64_MSG_OPTION_NONE                 = 0x0ull,
// 	/* share lower 32 bits with mach_msg_option_t */
// 	MACH64_SEND_MSG                        = MACH_SEND_MSG,
// 	MACH64_RCV_MSG                         = MACH_RCV_MSG,

// 	MACH64_RCV_LARGE                       = MACH_RCV_LARGE,
// 	MACH64_RCV_LARGE_IDENTITY              = MACH_RCV_LARGE_IDENTITY,

// 	MACH64_SEND_TIMEOUT                    = MACH_SEND_TIMEOUT,
// 	MACH64_SEND_OVERRIDE                   = MACH_SEND_OVERRIDE,
// 	MACH64_SEND_INTERRUPT                  = MACH_SEND_INTERRUPT,
// 	MACH64_SEND_NOTIFY                     = MACH_SEND_NOTIFY,
// #if KERNEL
// 	MACH64_SEND_ALWAYS                     = MACH_SEND_ALWAYS,
// 	MACH64_SEND_IMPORTANCE                 = MACH_SEND_IMPORTANCE,
// 	MACH64_SEND_KERNEL                     = MACH_SEND_KERNEL,
// #endif
// 	MACH64_SEND_FILTER_NONFATAL            = MACH_SEND_FILTER_NONFATAL,
// 	MACH64_SEND_TRAILER                    = MACH_SEND_TRAILER,
// 	MACH64_SEND_NOIMPORTANCE               = MACH_SEND_NOIMPORTANCE,
// 	MACH64_SEND_NODENAP                    = MACH_SEND_NODENAP,
// 	MACH64_SEND_SYNC_OVERRIDE              = MACH_SEND_SYNC_OVERRIDE,
// 	MACH64_SEND_PROPAGATE_QOS              = MACH_SEND_PROPAGATE_QOS,

// 	MACH64_SEND_SYNC_BOOTSTRAP_CHECKIN     = MACH_SEND_SYNC_BOOTSTRAP_CHECKIN,

// 	MACH64_RCV_TIMEOUT                     = MACH_RCV_TIMEOUT,

// 	MACH64_RCV_INTERRUPT                   = MACH_RCV_INTERRUPT,
// 	MACH64_RCV_VOUCHER                     = MACH_RCV_VOUCHER,

// 	MACH64_RCV_GUARDED_DESC                = MACH_RCV_GUARDED_DESC,
// 	MACH64_RCV_SYNC_WAIT                   = MACH_RCV_SYNC_WAIT,
// 	MACH64_RCV_SYNC_PEEK                   = MACH_RCV_SYNC_PEEK,

// 	MACH64_MSG_STRICT_REPLY                = MACH_MSG_STRICT_REPLY,
// 	/* following options are 64 only */

// 	/* Send and receive message as vectors */
// 	MACH64_MSG_VECTOR                      = 0x0000000100000000ull,
// 	/* The message is a kobject call */
// 	MACH64_SEND_KOBJECT_CALL               = 0x0000000200000000ull,
// 	/* The message is sent to a message queue */
// 	MACH64_SEND_MQ_CALL                    = 0x0000000400000000ull,
// 	/* This message destination is unknown. Used by old simulators only. */
// 	MACH64_SEND_ANY                        = 0x0000000800000000ull,

// #ifdef XNU_KERNEL_PRIVATE
// 	/*
// 	 * If kmsg has auxiliary data, append it immediate after the message
// 	 * and trailer.
// 	 *
// 	 * Must be used in conjunction with MACH64_MSG_VECTOR
// 	 */
// 	MACH64_RCV_LINEAR_VECTOR               = 0x1000000000000000ull,
// 	/* Receive into highest addr of buffer */
// 	MACH64_RCV_STACK                       = 0x2000000000000000ull,
// 	/*
// 	 * This internal-only flag is intended for use by a single thread per-port/set!
// 	 * If more than one thread attempts to MACH64_PEEK_MSG on a port or set, one of
// 	 * the threads may miss messages (in fact, it may never wake up).
// 	 */
// 	MACH64_PEEK_MSG                        = 0x4000000000000000ull,
// 	/*
// 	 * This is a mach_msg2() send/receive operation.
// 	 */
// 	MACH64_MACH_MSG2                       = 0x8000000000000000ull
// #endif
// } mach_msg_option64_t;

typedef unsigned int mach_msg_type_name_t;
typedef uint8_t *mach_voucher_attr_raw_recipe_array_t;
typedef uint8_t *mach_voucher_attr_raw_recipe_t;
typedef uint32_t mach_voucher_attr_key_t;
typedef uint32_t mach_voucher_attr_command_t;
typedef struct thread *thread_t;
typedef int vm_machine_attribute_t;
typedef int vm_machine_attribute_val_t;
typedef int vm_region_flavor_t;
typedef int vm_page_info_flavor_t;
typedef struct task *task_t;
typedef int ast_t;
typedef void *event_t;
typedef int wait_interrupt_t;
typedef integer_t mach_msg_id_t;
typedef natural_t mach_port_mscount_t; /* make-send count */

typedef int wait_result_t;
typedef void (*thread_continue_t)(void *, wait_result_t);
thread_t CreateWaitingThread(task_t task);
void ClearTaskWait(task_t task);

#endif /* OSFMK_API_TYPES_H_ */
