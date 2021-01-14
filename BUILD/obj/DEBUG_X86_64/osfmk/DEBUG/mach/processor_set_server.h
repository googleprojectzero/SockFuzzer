#ifndef	_processor_set_server_
#define	_processor_set_server_

/* Module processor_set */

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

#ifndef	processor_set_MSG_COUNT
#define	processor_set_MSG_COUNT	11
#endif	/* processor_set_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mig.h>
#include <ipc/ipc_voucher.h>
#include <kern/ipc_kobject.h>
#include <kern/ipc_tt.h>
#include <kern/ipc_host.h>
#include <kern/ipc_sync.h>
#include <kern/ledger.h>
#include <kern/processor.h>
#include <kern/sync_lock.h>
#include <kern/sync_sema.h>
#include <ipc/ipc_eventlink.h>
#include <vm/memory_object.h>
#include <vm/vm_map.h>
#include <kern/arcade.h>
#include <kern/ipc_mig.h>
#include <kern/suid_cred.h>
#include <mach/mig.h>
#include <mach/mach_types.h>

#ifdef __BeforeMigServerHeader
__BeforeMigServerHeader
#endif /* __BeforeMigServerHeader */

#ifndef MIG_SERVER_ROUTINE
#define MIG_SERVER_ROUTINE
#endif


/* Routine processor_set_statistics */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t processor_set_statistics
(
	processor_set_name_t pset,
	processor_set_flavor_t flavor,
	processor_set_info_t info_out,
	mach_msg_type_number_t *info_outCnt
);

/* Routine processor_set_destroy */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t processor_set_destroy
(
	processor_set_t set
);

/* Routine processor_set_max_priority */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t processor_set_max_priority
(
	processor_set_t processor_set,
	int max_priority,
	boolean_t change_threads
);

/* Routine processor_set_policy_enable */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t processor_set_policy_enable
(
	processor_set_t processor_set,
	int policy
);

/* Routine processor_set_policy_disable */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t processor_set_policy_disable
(
	processor_set_t processor_set,
	int policy,
	boolean_t change_threads
);

/* Routine processor_set_tasks */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t processor_set_tasks
(
	processor_set_t processor_set,
	task_array_t *task_list,
	mach_msg_type_number_t *task_listCnt
);

/* Routine processor_set_threads */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t processor_set_threads
(
	processor_set_t processor_set,
	thread_act_array_t *thread_list,
	mach_msg_type_number_t *thread_listCnt
);

/* Routine processor_set_policy_control */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t processor_set_policy_control
(
	processor_set_t pset,
	processor_set_flavor_t flavor,
	processor_set_info_t policy_info,
	mach_msg_type_number_t policy_infoCnt,
	boolean_t change
);

/* Routine processor_set_stack_usage */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t processor_set_stack_usage
(
	processor_set_t pset,
	unsigned *ltotal,
	vm_size_t *space,
	vm_size_t *resident,
	vm_size_t *maxusage,
	vm_offset_t *maxstack
);

/* Routine processor_set_info */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t processor_set_info
(
	processor_set_name_t set_name,
	int flavor,
	host_t *host,
	processor_set_info_t info_out,
	mach_msg_type_number_t *info_outCnt
);

/* Routine processor_set_tasks_with_flavor */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t processor_set_tasks_with_flavor
(
	processor_set_t processor_set,
	mach_task_flavor_t flavor,
	task_array_t *task_list,
	mach_msg_type_number_t *task_listCnt
);

#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
boolean_t processor_set_server(
		mach_msg_header_t *InHeadP,
		mach_msg_header_t *OutHeadP);

#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
mig_routine_t processor_set_server_routine(
		mach_msg_header_t *InHeadP);


/* Description of this subsystem, for use in direct RPC */
extern const struct processor_set_subsystem {
	mig_server_routine_t	server;	/* Server routine */
	mach_msg_id_t	start;	/* Min routine number */
	mach_msg_id_t	end;	/* Max routine number + 1 */
	unsigned int	maxsize;	/* Max msg size */
	vm_address_t	reserved;	/* Reserved */
	struct routine_descriptor	/*Array of routine descriptors */
		routine[11];
} processor_set_subsystem;

/* typedefs for all requests */

#ifndef __Request__processor_set_subsystem__defined
#define __Request__processor_set_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		processor_set_flavor_t flavor;
		mach_msg_type_number_t info_outCnt;
	} __Request__processor_set_statistics_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__processor_set_destroy_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int max_priority;
		boolean_t change_threads;
	} __Request__processor_set_max_priority_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int policy;
	} __Request__processor_set_policy_enable_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int policy;
		boolean_t change_threads;
	} __Request__processor_set_policy_disable_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__processor_set_tasks_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__processor_set_threads_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		processor_set_flavor_t flavor;
		mach_msg_type_number_t policy_infoCnt;
		integer_t policy_info[5];
		boolean_t change;
	} __Request__processor_set_policy_control_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__processor_set_stack_usage_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int flavor;
		mach_msg_type_number_t info_outCnt;
	} __Request__processor_set_info_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_task_flavor_t flavor;
	} __Request__processor_set_tasks_with_flavor_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif
#endif /* !__Request__processor_set_subsystem__defined */


/* union of all requests */

#ifndef __RequestUnion__processor_set_subsystem__defined
#define __RequestUnion__processor_set_subsystem__defined
union __RequestUnion__processor_set_subsystem {
	__Request__processor_set_statistics_t Request_processor_set_statistics;
	__Request__processor_set_destroy_t Request_processor_set_destroy;
	__Request__processor_set_max_priority_t Request_processor_set_max_priority;
	__Request__processor_set_policy_enable_t Request_processor_set_policy_enable;
	__Request__processor_set_policy_disable_t Request_processor_set_policy_disable;
	__Request__processor_set_tasks_t Request_processor_set_tasks;
	__Request__processor_set_threads_t Request_processor_set_threads;
	__Request__processor_set_policy_control_t Request_processor_set_policy_control;
	__Request__processor_set_stack_usage_t Request_processor_set_stack_usage;
	__Request__processor_set_info_t Request_processor_set_info;
	__Request__processor_set_tasks_with_flavor_t Request_processor_set_tasks_with_flavor;
};
#endif /* __RequestUnion__processor_set_subsystem__defined */
/* typedefs for all replies */

#ifndef __Reply__processor_set_subsystem__defined
#define __Reply__processor_set_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
		mach_msg_type_number_t info_outCnt;
		integer_t info_out[5];
	} __Reply__processor_set_statistics_t __attribute__((unused));
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
	} __Reply__processor_set_destroy_t __attribute__((unused));
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
	} __Reply__processor_set_max_priority_t __attribute__((unused));
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
	} __Reply__processor_set_policy_enable_t __attribute__((unused));
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
	} __Reply__processor_set_policy_disable_t __attribute__((unused));
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
		mach_msg_ool_ports_descriptor_t task_list;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t task_listCnt;
	} __Reply__processor_set_tasks_t __attribute__((unused));
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
		mach_msg_ool_ports_descriptor_t thread_list;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t thread_listCnt;
	} __Reply__processor_set_threads_t __attribute__((unused));
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
	} __Reply__processor_set_policy_control_t __attribute__((unused));
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
		unsigned ltotal;
		vm_size_t space;
		vm_size_t resident;
		vm_size_t maxusage;
		vm_offset_t maxstack;
	} __Reply__processor_set_stack_usage_t __attribute__((unused));
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
		mach_msg_port_descriptor_t host;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t info_outCnt;
		integer_t info_out[5];
	} __Reply__processor_set_info_t __attribute__((unused));
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
		mach_msg_ool_ports_descriptor_t task_list;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t task_listCnt;
	} __Reply__processor_set_tasks_with_flavor_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif
#endif /* !__Reply__processor_set_subsystem__defined */


/* union of all replies */

#ifndef __ReplyUnion__processor_set_subsystem__defined
#define __ReplyUnion__processor_set_subsystem__defined
union __ReplyUnion__processor_set_subsystem {
	__Reply__processor_set_statistics_t Reply_processor_set_statistics;
	__Reply__processor_set_destroy_t Reply_processor_set_destroy;
	__Reply__processor_set_max_priority_t Reply_processor_set_max_priority;
	__Reply__processor_set_policy_enable_t Reply_processor_set_policy_enable;
	__Reply__processor_set_policy_disable_t Reply_processor_set_policy_disable;
	__Reply__processor_set_tasks_t Reply_processor_set_tasks;
	__Reply__processor_set_threads_t Reply_processor_set_threads;
	__Reply__processor_set_policy_control_t Reply_processor_set_policy_control;
	__Reply__processor_set_stack_usage_t Reply_processor_set_stack_usage;
	__Reply__processor_set_info_t Reply_processor_set_info;
	__Reply__processor_set_tasks_with_flavor_t Reply_processor_set_tasks_with_flavor;
};
#endif /* __ReplyUnion__processor_set_subsystem__defined */

#ifndef subsystem_to_name_map_processor_set
#define subsystem_to_name_map_processor_set \
    { "processor_set_statistics", 4000 },\
    { "processor_set_destroy", 4001 },\
    { "processor_set_max_priority", 4002 },\
    { "processor_set_policy_enable", 4003 },\
    { "processor_set_policy_disable", 4004 },\
    { "processor_set_tasks", 4005 },\
    { "processor_set_threads", 4006 },\
    { "processor_set_policy_control", 4007 },\
    { "processor_set_stack_usage", 4008 },\
    { "processor_set_info", 4009 },\
    { "processor_set_tasks_with_flavor", 4010 }
#endif

#ifdef __AfterMigServerHeader
__AfterMigServerHeader
#endif /* __AfterMigServerHeader */

#endif	 /* _processor_set_server_ */
