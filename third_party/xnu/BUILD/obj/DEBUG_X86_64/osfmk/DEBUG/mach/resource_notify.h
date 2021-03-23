#ifndef	_resource_notify_user_
#define	_resource_notify_user_

/* Module resource_notify */

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

#ifndef	resource_notify_MSG_COUNT
#define	resource_notify_MSG_COUNT	3
#endif	/* resource_notify_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mig.h>
#include <mach/mig.h>
#include <mach/mach_types.h>
#include <mach/mach_types.h>
#include <mach/resource_monitors.h>
#include <mach/clock_types.h>

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */

#include <sys/cdefs.h>
__BEGIN_DECLS


/* SimpleRoutine cpu_usage_violation */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t send_cpu_usage_violation
(
	mach_port_t receiver,
	proc_name_t procname,
	int pid,
	posix_path_t killed_proc_path,
	mach_timespec_t timestamp,
	int64_t observed_cpu_nsecs,
	int64_t observation_nsecs,
	int64_t cpu_nsecs_allowed,
	int64_t limit_window_nsecs,
	resource_notify_flags_t flags
);

/* SimpleRoutine cpu_wakes_violation */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t send_cpu_wakes_violation
(
	mach_port_t receiver,
	proc_name_t procname,
	int pid,
	posix_path_t killed_proc_path,
	mach_timespec_t timestamp,
	int64_t observed_cpu_wakes,
	int64_t observation_nsecs,
	int64_t cpu_wakes_allowed,
	int64_t limit_window_nsecs,
	resource_notify_flags_t flags
);

/* SimpleRoutine disk_writes_violation */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t send_disk_writes_violation
(
	mach_port_t receiver,
	proc_name_t procname,
	int pid,
	posix_path_t killed_proc_path,
	mach_timespec_t timestamp,
	int64_t observed_bytes_dirtied,
	int64_t observation_nsecs,
	int64_t bytes_dirtied_allowed,
	int64_t limit_window_nsecs,
	resource_notify_flags_t flags
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

#ifndef __Request__resource_notify_subsystem__defined
#define __Request__resource_notify_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		proc_name_t procname;
		char procnamePad[3];
		int pid;
		posix_path_t killed_proc_path;
		mach_timespec_t timestamp;
		int64_t observed_cpu_nsecs;
		int64_t observation_nsecs;
		int64_t cpu_nsecs_allowed;
		int64_t limit_window_nsecs;
		resource_notify_flags_t flags;
	} __Request__cpu_usage_violation_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		proc_name_t procname;
		char procnamePad[3];
		int pid;
		posix_path_t killed_proc_path;
		mach_timespec_t timestamp;
		int64_t observed_cpu_wakes;
		int64_t observation_nsecs;
		int64_t cpu_wakes_allowed;
		int64_t limit_window_nsecs;
		resource_notify_flags_t flags;
	} __Request__cpu_wakes_violation_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		proc_name_t procname;
		char procnamePad[3];
		int pid;
		posix_path_t killed_proc_path;
		mach_timespec_t timestamp;
		int64_t observed_bytes_dirtied;
		int64_t observation_nsecs;
		int64_t bytes_dirtied_allowed;
		int64_t limit_window_nsecs;
		resource_notify_flags_t flags;
	} __Request__disk_writes_violation_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif
#endif /* !__Request__resource_notify_subsystem__defined */

/* union of all requests */

#ifndef __RequestUnion__send_resource_notify_subsystem__defined
#define __RequestUnion__send_resource_notify_subsystem__defined
union __RequestUnion__send_resource_notify_subsystem {
	__Request__cpu_usage_violation_t Request_send_cpu_usage_violation;
	__Request__cpu_wakes_violation_t Request_send_cpu_wakes_violation;
	__Request__disk_writes_violation_t Request_send_disk_writes_violation;
};
#endif /* !__RequestUnion__send_resource_notify_subsystem__defined */
/* typedefs for all replies */

#ifndef __Reply__resource_notify_subsystem__defined
#define __Reply__resource_notify_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__cpu_usage_violation_t __attribute__((unused));
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
	} __Reply__cpu_wakes_violation_t __attribute__((unused));
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
	} __Reply__disk_writes_violation_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif
#endif /* !__Reply__resource_notify_subsystem__defined */

/* union of all replies */

#ifndef __ReplyUnion__send_resource_notify_subsystem__defined
#define __ReplyUnion__send_resource_notify_subsystem__defined
union __ReplyUnion__send_resource_notify_subsystem {
	__Reply__cpu_usage_violation_t Reply_send_cpu_usage_violation;
	__Reply__cpu_wakes_violation_t Reply_send_cpu_wakes_violation;
	__Reply__disk_writes_violation_t Reply_send_disk_writes_violation;
};
#endif /* !__RequestUnion__send_resource_notify_subsystem__defined */

#ifndef subsystem_to_name_map_resource_notify
#define subsystem_to_name_map_resource_notify \
    { "cpu_usage_violation", 827800 },\
    { "cpu_wakes_violation", 827801 },\
    { "disk_writes_violation", 827802 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _resource_notify_user_ */
