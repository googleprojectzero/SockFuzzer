#ifndef	_task_restartable_server_
#define	_task_restartable_server_

/* Module task_restartable */

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

#ifndef	task_restartable_MSG_COUNT
#define	task_restartable_MSG_COUNT	2
#endif	/* task_restartable_MSG_COUNT */

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
#include <kern/task_ident.h>
#include <mach/mig.h>
#include <mach/mach_types.h>
#include <mach_debug/mach_debug_types.h>
#include <kern/restartable.h>

#ifdef __BeforeMigServerHeader
__BeforeMigServerHeader
#endif /* __BeforeMigServerHeader */

#ifndef MIG_SERVER_ROUTINE
#define MIG_SERVER_ROUTINE
#endif


/* Routine task_restartable_ranges_register */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t task_restartable_ranges_register
(
	task_t target_task,
	task_restartable_range_array_t ranges,
	mach_msg_type_number_t rangesCnt
);

/* Routine task_restartable_ranges_synchronize */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t task_restartable_ranges_synchronize
(
	task_t target_task
);

#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
boolean_t task_restartable_server(
		mach_msg_header_t *InHeadP,
		mach_msg_header_t *OutHeadP);

#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
mig_routine_t task_restartable_server_routine(
		mach_msg_header_t *InHeadP);


/* Description of this subsystem, for use in direct RPC */
extern const struct task_restartable_subsystem {
	mig_server_routine_t	server;	/* Server routine */
	mach_msg_id_t	start;	/* Min routine number */
	mach_msg_id_t	end;	/* Max routine number + 1 */
	unsigned int	maxsize;	/* Max msg size */
	vm_address_t	reserved;	/* Reserved */
	struct routine_descriptor	/*Array of routine descriptors */
		routine[2];
} task_restartable_subsystem;

/* typedefs for all requests */

#ifndef __Request__task_restartable_subsystem__defined
#define __Request__task_restartable_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_msg_type_number_t rangesCnt;
		task_restartable_range_t ranges[64];
	} __Request__task_restartable_ranges_register_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__task_restartable_ranges_synchronize_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif
#endif /* !__Request__task_restartable_subsystem__defined */


/* union of all requests */

#ifndef __RequestUnion__task_restartable_subsystem__defined
#define __RequestUnion__task_restartable_subsystem__defined
union __RequestUnion__task_restartable_subsystem {
	__Request__task_restartable_ranges_register_t Request_task_restartable_ranges_register;
	__Request__task_restartable_ranges_synchronize_t Request_task_restartable_ranges_synchronize;
};
#endif /* __RequestUnion__task_restartable_subsystem__defined */
/* typedefs for all replies */

#ifndef __Reply__task_restartable_subsystem__defined
#define __Reply__task_restartable_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__task_restartable_ranges_register_t __attribute__((unused));
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
	} __Reply__task_restartable_ranges_synchronize_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif
#endif /* !__Reply__task_restartable_subsystem__defined */


/* union of all replies */

#ifndef __ReplyUnion__task_restartable_subsystem__defined
#define __ReplyUnion__task_restartable_subsystem__defined
union __ReplyUnion__task_restartable_subsystem {
	__Reply__task_restartable_ranges_register_t Reply_task_restartable_ranges_register;
	__Reply__task_restartable_ranges_synchronize_t Reply_task_restartable_ranges_synchronize;
};
#endif /* __ReplyUnion__task_restartable_subsystem__defined */

#ifndef subsystem_to_name_map_task_restartable
#define subsystem_to_name_map_task_restartable \
    { "task_restartable_ranges_register", 8000 },\
    { "task_restartable_ranges_synchronize", 8001 }
#endif

#ifdef __AfterMigServerHeader
__AfterMigServerHeader
#endif /* __AfterMigServerHeader */

#endif	 /* _task_restartable_server_ */
