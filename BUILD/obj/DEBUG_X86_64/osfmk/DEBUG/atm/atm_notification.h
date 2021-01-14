#ifndef	_atm_notification_user_
#define	_atm_notification_user_

/* Module atm_notification */

#include <string.h>
#include <mach/ndr.h>
#include <mach/boolean.h>
#include <mach/kern_return.h>
#include <mach/notify.h>
#include <mach/mach_types.h>
#include <mach/message.h>
#include <mach/mig_errors.h>
#include <mach/port.h>
	
/* BEGIN MIG_STRNCPY_ZEROFILL CODE */

#if defined(__has_include)
#if __has_include(<mach/mig_strncpy_zerofill_support.h>)
#ifndef USING_MIG_STRNCPY_ZEROFILL
#define USING_MIG_STRNCPY_ZEROFILL
#endif
#ifndef __MIG_STRNCPY_ZEROFILL_FORWARD_TYPE_DECLS__
#define __MIG_STRNCPY_ZEROFILL_FORWARD_TYPE_DECLS__
#ifdef __cplusplus
extern "C" {
#endif
	extern int mig_strncpy_zerofill(char *dest, const char *src, int len) __attribute__((weak_import));
#ifdef __cplusplus
}
#endif
#endif /* __MIG_STRNCPY_ZEROFILL_FORWARD_TYPE_DECLS__ */
#endif /* __has_include(<mach/mig_strncpy_zerofill_support.h>) */
#endif /* __has_include */
	
/* END MIG_STRNCPY_ZEROFILL CODE */

#if	(__MigKernelSpecificCode) || (_MIG_KERNEL_SPECIFIC_CODE_)
#include <kern/ipc_mig.h>
#endif /* __MigKernelSpecificCode */

#ifdef AUTOTEST
#ifndef FUNCTION_PTR_T
#define FUNCTION_PTR_T
typedef void (*function_ptr_t)(mach_port_t, char *, mach_msg_type_number_t);
typedef struct {
        char            *name;
        function_ptr_t  function;
} function_table_entry;
typedef function_table_entry   *function_table_t;
#endif /* FUNCTION_PTR_T */
#endif /* AUTOTEST */

#ifndef	atm_notification_MSG_COUNT
#define	atm_notification_MSG_COUNT	2
#endif	/* atm_notification_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mig.h>
#include <mach/mig.h>
#include <mach/mach_types.h>
#include <atm/atm_types.h>

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */

#include <sys/cdefs.h>
__BEGIN_DECLS


/* SimpleRoutine atm_collect_trace_info */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t atm_collect_trace_info
(
	mach_port_t atm_port,
	atm_aid_t activity_trace_id,
	mach_atm_subaid_t sub_activity_id,
	uint32_t flags,
	atm_memory_descriptor_array_t memory_buffers,
	mach_msg_type_number_t memory_buffersCnt,
	atm_memory_size_array_t buffer_sizes,
	mach_msg_type_number_t buffer_sizesCnt
);

/* SimpleRoutine atm_inspect_process_buffer */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t atm_inspect_process_buffer
(
	mach_port_t atm_port,
	uint32_t proc_pid,
	uint64_t proc_uniqueid,
	uint64_t buffer_size,
	mach_port_t trace_buffer
);

__END_DECLS

/********************** Caution **************************/
/* The following data types should be used to calculate  */
/* maximum message sizes only. The actual message may be */
/* smaller, and the position of the arguments within the */
/* message layout may vary from what is presented here.  */
/* For example, if any of the arguments are variable-    */
/* sized, and less than the maximum is sent, the data    */
/* will be packed tight in the actual message to reduce  */
/* the presence of holes.                                */
/********************** Caution **************************/

/* typedefs for all requests */

#ifndef __Request__atm_notification_subsystem__defined
#define __Request__atm_notification_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t memory_buffers[512];
		/* end of the kernel processed data */
		NDR_record_t NDR;
		atm_aid_t activity_trace_id;
		mach_atm_subaid_t sub_activity_id;
		uint32_t flags;
		mach_msg_type_number_t memory_buffersCnt;
		mach_msg_type_number_t buffer_sizesCnt;
		uint64_t buffer_sizes[512];
	} __Request__atm_collect_trace_info_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_port_descriptor_t trace_buffer;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		uint32_t proc_pid;
		uint64_t proc_uniqueid;
		uint64_t buffer_size;
	} __Request__atm_inspect_process_buffer_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif
#endif /* !__Request__atm_notification_subsystem__defined */

/* union of all requests */

#ifndef __RequestUnion__atm_notification_subsystem__defined
#define __RequestUnion__atm_notification_subsystem__defined
union __RequestUnion__atm_notification_subsystem {
	__Request__atm_collect_trace_info_t Request_atm_collect_trace_info;
	__Request__atm_inspect_process_buffer_t Request_atm_inspect_process_buffer;
};
#endif /* !__RequestUnion__atm_notification_subsystem__defined */
/* typedefs for all replies */

#ifndef __Reply__atm_notification_subsystem__defined
#define __Reply__atm_notification_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__atm_collect_trace_info_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__atm_inspect_process_buffer_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif
#endif /* !__Reply__atm_notification_subsystem__defined */

/* union of all replies */

#ifndef __ReplyUnion__atm_notification_subsystem__defined
#define __ReplyUnion__atm_notification_subsystem__defined
union __ReplyUnion__atm_notification_subsystem {
	__Reply__atm_collect_trace_info_t Reply_atm_collect_trace_info;
	__Reply__atm_inspect_process_buffer_t Reply_atm_inspect_process_buffer;
};
#endif /* !__RequestUnion__atm_notification_subsystem__defined */

#ifndef subsystem_to_name_map_atm_notification
#define subsystem_to_name_map_atm_notification \
    { "atm_collect_trace_info", 11500 },\
    { "atm_inspect_process_buffer", 11501 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _atm_notification_user_ */
