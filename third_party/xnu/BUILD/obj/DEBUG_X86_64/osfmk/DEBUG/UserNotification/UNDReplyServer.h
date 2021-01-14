#ifndef	_UNDReply_server_
#define	_UNDReply_server_

/* Module UNDReply */

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

#ifndef	UNDReply_MSG_COUNT
#define	UNDReply_MSG_COUNT	2
#endif	/* UNDReply_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mig.h>
#include <UserNotification/UNDTypes.h>

#ifdef __BeforeMigServerHeader
__BeforeMigServerHeader
#endif /* __BeforeMigServerHeader */

#ifndef MIG_SERVER_ROUTINE
#define MIG_SERVER_ROUTINE
#endif


/* SimpleRoutine UNDAlertCompletedWithResult_rpc */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t UNDAlertCompletedWithResult_rpc
(
	UNDReplyRef reply,
	int result,
	xmlData_t data,
	mach_msg_type_number_t dataCnt
);

/* SimpleRoutine UNDNotificationCreated_rpc */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
MIG_SERVER_ROUTINE
kern_return_t UNDNotificationCreated_rpc
(
	UNDReplyRef reply,
	int userLandNotificationKey
);

#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
boolean_t UNDReply_server(
		mach_msg_header_t *InHeadP,
		mach_msg_header_t *OutHeadP);

#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
mig_routine_t UNDReply_server_routine(
		mach_msg_header_t *InHeadP);


/* Description of this subsystem, for use in direct RPC */
extern const struct UNDReply_subsystem {
	mig_server_routine_t	server;	/* Server routine */
	mach_msg_id_t	start;	/* Min routine number */
	mach_msg_id_t	end;	/* Max routine number + 1 */
	unsigned int	maxsize;	/* Max msg size */
	vm_address_t	reserved;	/* Reserved */
	struct routine_descriptor	/*Array of routine descriptors */
		routine[2];
} UNDReply_subsystem;

/* typedefs for all requests */

#ifndef __Request__UNDReply_subsystem__defined
#define __Request__UNDReply_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_ool_descriptor_t data;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		int result;
		mach_msg_type_number_t dataCnt;
	} __Request__UNDAlertCompletedWithResult_rpc_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int userLandNotificationKey;
	} __Request__UNDNotificationCreated_rpc_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif
#endif /* !__Request__UNDReply_subsystem__defined */


/* union of all requests */

#ifndef __RequestUnion__UNDReply_subsystem__defined
#define __RequestUnion__UNDReply_subsystem__defined
union __RequestUnion__UNDReply_subsystem {
	__Request__UNDAlertCompletedWithResult_rpc_t Request_UNDAlertCompletedWithResult_rpc;
	__Request__UNDNotificationCreated_rpc_t Request_UNDNotificationCreated_rpc;
};
#endif /* __RequestUnion__UNDReply_subsystem__defined */
/* typedefs for all replies */

#ifndef __Reply__UNDReply_subsystem__defined
#define __Reply__UNDReply_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__UNDAlertCompletedWithResult_rpc_t __attribute__((unused));
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
	} __Reply__UNDNotificationCreated_rpc_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif
#endif /* !__Reply__UNDReply_subsystem__defined */


/* union of all replies */

#ifndef __ReplyUnion__UNDReply_subsystem__defined
#define __ReplyUnion__UNDReply_subsystem__defined
union __ReplyUnion__UNDReply_subsystem {
	__Reply__UNDAlertCompletedWithResult_rpc_t Reply_UNDAlertCompletedWithResult_rpc;
	__Reply__UNDNotificationCreated_rpc_t Reply_UNDNotificationCreated_rpc;
};
#endif /* __ReplyUnion__UNDReply_subsystem__defined */

#ifndef subsystem_to_name_map_UNDReply
#define subsystem_to_name_map_UNDReply \
    { "UNDAlertCompletedWithResult_rpc", 6200 },\
    { "UNDNotificationCreated_rpc", 6201 }
#endif

#ifdef __AfterMigServerHeader
__AfterMigServerHeader
#endif /* __AfterMigServerHeader */

#endif	 /* _UNDReply_server_ */
