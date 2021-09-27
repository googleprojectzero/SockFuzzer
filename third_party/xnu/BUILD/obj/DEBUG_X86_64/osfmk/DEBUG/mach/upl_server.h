#ifndef	_upl_server_
#define	_upl_server_

/* Module upl */

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

#ifndef	upl_MSG_COUNT
#define	upl_MSG_COUNT	4
#endif	/* upl_MSG_COUNT */

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

#ifdef __BeforeMigServerHeader
__BeforeMigServerHeader
#endif /* __BeforeMigServerHeader */

#ifndef MIG_SERVER_ROUTINE
#define MIG_SERVER_ROUTINE
#endif


/* Routine upl_abort */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t upl_abort
(
	upl_t upl_object,
	integer_t abort_cond
);

/* Routine upl_abort_range */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t upl_abort_range
(
	upl_t upl_object,
	upl_offset_t offset,
	upl_size_t size,
	integer_t abort_cond,
	boolean_t *empty
);

/* Routine upl_commit */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t upl_commit
(
	upl_t upl_object,
	upl_page_info_array_t page_list,
	mach_msg_type_number_t page_listCnt
);

/* Routine upl_commit_range */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t upl_commit_range
(
	upl_t upl_object,
	upl_offset_t offset,
	upl_size_t size,
	integer_t cntrl_flags,
	upl_page_info_array_t page_list,
	mach_msg_type_number_t page_listCnt,
	boolean_t *empty
);

#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
boolean_t upl_server(
		mach_msg_header_t *InHeadP,
		mach_msg_header_t *OutHeadP);

#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
mig_routine_t upl_server_routine(
		mach_msg_header_t *InHeadP);


/* Description of this subsystem, for use in direct RPC */
extern const struct upl_subsystem {
	mig_server_routine_t	server;	/* Server routine */
	mach_msg_id_t	start;	/* Min routine number */
	mach_msg_id_t	end;	/* Max routine number + 1 */
	unsigned int	maxsize;	/* Max msg size */
	vm_address_t	reserved;	/* Reserved */
	struct routine_descriptor	/*Array of routine descriptors */
		routine[4];
} upl_subsystem;

/* typedefs for all requests */

#ifndef __Request__upl_subsystem__defined
#define __Request__upl_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		integer_t abort_cond;
	} __Request__upl_abort_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		upl_offset_t offset;
		upl_size_t size;
		integer_t abort_cond;
	} __Request__upl_abort_range_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_msg_type_number_t page_listCnt;
		upl_page_info_t page_list[256];
	} __Request__upl_commit_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		upl_offset_t offset;
		upl_size_t size;
		integer_t cntrl_flags;
		mach_msg_type_number_t page_listCnt;
		upl_page_info_t page_list[256];
	} __Request__upl_commit_range_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif
#endif /* !__Request__upl_subsystem__defined */


/* union of all requests */

#ifndef __RequestUnion__upl_subsystem__defined
#define __RequestUnion__upl_subsystem__defined
union __RequestUnion__upl_subsystem {
	__Request__upl_abort_t Request_upl_abort;
	__Request__upl_abort_range_t Request_upl_abort_range;
	__Request__upl_commit_t Request_upl_commit;
	__Request__upl_commit_range_t Request_upl_commit_range;
};
#endif /* __RequestUnion__upl_subsystem__defined */
/* typedefs for all replies */

#ifndef __Reply__upl_subsystem__defined
#define __Reply__upl_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__upl_abort_t __attribute__((unused));
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
		boolean_t empty;
	} __Reply__upl_abort_range_t __attribute__((unused));
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
	} __Reply__upl_commit_t __attribute__((unused));
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
		boolean_t empty;
	} __Reply__upl_commit_range_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif
#endif /* !__Reply__upl_subsystem__defined */


/* union of all replies */

#ifndef __ReplyUnion__upl_subsystem__defined
#define __ReplyUnion__upl_subsystem__defined
union __ReplyUnion__upl_subsystem {
	__Reply__upl_abort_t Reply_upl_abort;
	__Reply__upl_abort_range_t Reply_upl_abort_range;
	__Reply__upl_commit_t Reply_upl_commit;
	__Reply__upl_commit_range_t Reply_upl_commit_range;
};
#endif /* __ReplyUnion__upl_subsystem__defined */

#ifndef subsystem_to_name_map_upl
#define subsystem_to_name_map_upl \
    { "upl_abort", 2050 },\
    { "upl_abort_range", 2051 },\
    { "upl_commit", 2052 },\
    { "upl_commit_range", 2053 }
#endif

#ifdef __AfterMigServerHeader
__AfterMigServerHeader
#endif /* __AfterMigServerHeader */

#endif	 /* _upl_server_ */
