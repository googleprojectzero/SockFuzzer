#ifndef	_clock_priv_server_
#define	_clock_priv_server_

/* Module clock_priv */

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

#ifndef	clock_priv_MSG_COUNT
#define	clock_priv_MSG_COUNT	2
#endif	/* clock_priv_MSG_COUNT */

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
#include <mach/mach_types.h>

#ifdef __BeforeMigServerHeader
__BeforeMigServerHeader
#endif /* __BeforeMigServerHeader */

#ifndef MIG_SERVER_ROUTINE
#define MIG_SERVER_ROUTINE
#endif


/* Routine clock_set_time */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t clock_set_time
(
	clock_ctrl_t clock_ctrl,
	mach_timespec_t new_time
);

/* Routine clock_set_attributes */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t clock_set_attributes
(
	clock_ctrl_t clock_ctrl,
	clock_flavor_t flavor,
	clock_attr_t clock_attr,
	mach_msg_type_number_t clock_attrCnt
);

#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
boolean_t clock_priv_server(
		mach_msg_header_t *InHeadP,
		mach_msg_header_t *OutHeadP);

#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
mig_routine_t clock_priv_server_routine(
		mach_msg_header_t *InHeadP);


/* Description of this subsystem, for use in direct RPC */
extern const struct clock_priv_subsystem {
	mig_server_routine_t	server;	/* Server routine */
	mach_msg_id_t	start;	/* Min routine number */
	mach_msg_id_t	end;	/* Max routine number + 1 */
	unsigned int	maxsize;	/* Max msg size */
	vm_address_t	reserved;	/* Reserved */
	struct routine_descriptor	/*Array of routine descriptors */
		routine[2];
} clock_priv_subsystem;

/* typedefs for all requests */

#ifndef __Request__clock_priv_subsystem__defined
#define __Request__clock_priv_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_timespec_t new_time;
	} __Request__clock_set_time_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		clock_flavor_t flavor;
		mach_msg_type_number_t clock_attrCnt;
		int clock_attr[1];
	} __Request__clock_set_attributes_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif
#endif /* !__Request__clock_priv_subsystem__defined */


/* union of all requests */

#ifndef __RequestUnion__clock_priv_subsystem__defined
#define __RequestUnion__clock_priv_subsystem__defined
union __RequestUnion__clock_priv_subsystem {
	__Request__clock_set_time_t Request_clock_set_time;
	__Request__clock_set_attributes_t Request_clock_set_attributes;
};
#endif /* __RequestUnion__clock_priv_subsystem__defined */
/* typedefs for all replies */

#ifndef __Reply__clock_priv_subsystem__defined
#define __Reply__clock_priv_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__clock_set_time_t __attribute__((unused));
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
	} __Reply__clock_set_attributes_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif
#endif /* !__Reply__clock_priv_subsystem__defined */


/* union of all replies */

#ifndef __ReplyUnion__clock_priv_subsystem__defined
#define __ReplyUnion__clock_priv_subsystem__defined
union __ReplyUnion__clock_priv_subsystem {
	__Reply__clock_set_time_t Reply_clock_set_time;
	__Reply__clock_set_attributes_t Reply_clock_set_attributes;
};
#endif /* __ReplyUnion__clock_priv_subsystem__defined */

#ifndef subsystem_to_name_map_clock_priv
#define subsystem_to_name_map_clock_priv \
    { "clock_set_time", 1200 },\
    { "clock_set_attributes", 1201 }
#endif

#ifdef __AfterMigServerHeader
__AfterMigServerHeader
#endif /* __AfterMigServerHeader */

#endif	 /* _clock_priv_server_ */
