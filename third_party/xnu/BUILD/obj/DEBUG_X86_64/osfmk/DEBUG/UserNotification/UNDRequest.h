#ifndef	_UNDRequest_user_
#define	_UNDRequest_user_

/* Module UNDRequest */

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

#ifndef	UNDRequest_MSG_COUNT
#define	UNDRequest_MSG_COUNT	8
#endif	/* UNDRequest_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mig.h>
#include <UserNotification/UNDTypes.h>

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */

#include <sys/cdefs.h>
__BEGIN_DECLS


/* SimpleRoutine UNDExecute_rpc */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t UNDExecute_rpc
(
	UNDServerRef server,
	UNDPath executionPath,
	int uid,
	int gid
);

/* SimpleRoutine UNDDisplayNoticeFromBundle_rpc */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t UNDDisplayNoticeFromBundle_rpc
(
	UNDServerRef server,
	mach_port_t reply,
	UNDPath bundlePath,
	UNDPath fileName,
	UNDPath fileExtension,
	UNDKey messageKey
);

/* SimpleRoutine UNDDisplayAlertFromBundle_rpc */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t UNDDisplayAlertFromBundle_rpc
(
	UNDServerRef server,
	mach_port_t reply,
	UNDPath bundlePath,
	UNDKey fileName,
	UNDKey fileExtension,
	UNDKey messageKey
);

/* SimpleRoutine UNDDisplayCustomFromBundle_rpc */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t UNDDisplayCustomFromBundle_rpc
(
	UNDServerRef server,
	mach_port_t reply,
	UNDPath bundlePath,
	UNDKey fileName,
	UNDKey fileExtension,
	UNDKey messageKey,
	UNDPath tokenKey
);

/* SimpleRoutine UNDCancelNotification_rpc */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t UNDCancelNotification_rpc
(
	UNDServerRef server,
	int userLandNotificationKey
);

/* SimpleRoutine UNDDisplayNoticeSimple_rpc */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t UNDDisplayNoticeSimple_rpc
(
	UNDServerRef server,
	int rpctimeout,
	unsigned flags,
	UNDLabel iconPath,
	UNDLabel soundPath,
	UNDLabel localizationPath,
	UNDLabel header,
	UNDMessage message,
	UNDLabel defaultButtonTitle
);

/* Routine UNDDisplayAlertSimple_rpc */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t UNDDisplayAlertSimple_rpc
(
	UNDServerRef server,
	int rpctimeout,
	unsigned flags,
	UNDLabel iconPath,
	UNDLabel soundPath,
	UNDLabel localizationPath,
	UNDLabel header,
	UNDMessage message,
	UNDLabel defaultButtonTitle,
	UNDLabel alternateButtonTitle,
	UNDLabel otherButtonTitle,
	unsigned *response
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

#ifndef __Request__UNDRequest_subsystem__defined
#define __Request__UNDRequest_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_msg_type_number_t executionPathOffset; /* MiG doesn't use it */
		mach_msg_type_number_t executionPathCnt;
		char executionPath[1024];
		int uid;
		int gid;
	} __Request__UNDExecute_rpc_t __attribute__((unused));
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
		mach_msg_port_descriptor_t reply;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t bundlePathOffset; /* MiG doesn't use it */
		mach_msg_type_number_t bundlePathCnt;
		char bundlePath[1024];
		mach_msg_type_number_t fileNameOffset; /* MiG doesn't use it */
		mach_msg_type_number_t fileNameCnt;
		char fileName[1024];
		mach_msg_type_number_t fileExtensionOffset; /* MiG doesn't use it */
		mach_msg_type_number_t fileExtensionCnt;
		char fileExtension[1024];
		mach_msg_type_number_t messageKeyOffset; /* MiG doesn't use it */
		mach_msg_type_number_t messageKeyCnt;
		char messageKey[128];
	} __Request__UNDDisplayNoticeFromBundle_rpc_t __attribute__((unused));
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
		mach_msg_port_descriptor_t reply;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t bundlePathOffset; /* MiG doesn't use it */
		mach_msg_type_number_t bundlePathCnt;
		char bundlePath[1024];
		mach_msg_type_number_t fileNameOffset; /* MiG doesn't use it */
		mach_msg_type_number_t fileNameCnt;
		char fileName[128];
		mach_msg_type_number_t fileExtensionOffset; /* MiG doesn't use it */
		mach_msg_type_number_t fileExtensionCnt;
		char fileExtension[128];
		mach_msg_type_number_t messageKeyOffset; /* MiG doesn't use it */
		mach_msg_type_number_t messageKeyCnt;
		char messageKey[128];
	} __Request__UNDDisplayAlertFromBundle_rpc_t __attribute__((unused));
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
		mach_msg_port_descriptor_t reply;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t bundlePathOffset; /* MiG doesn't use it */
		mach_msg_type_number_t bundlePathCnt;
		char bundlePath[1024];
		mach_msg_type_number_t fileNameOffset; /* MiG doesn't use it */
		mach_msg_type_number_t fileNameCnt;
		char fileName[128];
		mach_msg_type_number_t fileExtensionOffset; /* MiG doesn't use it */
		mach_msg_type_number_t fileExtensionCnt;
		char fileExtension[128];
		mach_msg_type_number_t messageKeyOffset; /* MiG doesn't use it */
		mach_msg_type_number_t messageKeyCnt;
		char messageKey[128];
		mach_msg_type_number_t tokenKeyOffset; /* MiG doesn't use it */
		mach_msg_type_number_t tokenKeyCnt;
		char tokenKey[1024];
	} __Request__UNDDisplayCustomFromBundle_rpc_t __attribute__((unused));
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
	} __Request__UNDCancelNotification_rpc_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int rpctimeout;
		unsigned flags;
		mach_msg_type_number_t iconPathOffset; /* MiG doesn't use it */
		mach_msg_type_number_t iconPathCnt;
		char iconPath[128];
		mach_msg_type_number_t soundPathOffset; /* MiG doesn't use it */
		mach_msg_type_number_t soundPathCnt;
		char soundPath[128];
		mach_msg_type_number_t localizationPathOffset; /* MiG doesn't use it */
		mach_msg_type_number_t localizationPathCnt;
		char localizationPath[128];
		mach_msg_type_number_t headerOffset; /* MiG doesn't use it */
		mach_msg_type_number_t headerCnt;
		char header[128];
		mach_msg_type_number_t messageOffset; /* MiG doesn't use it */
		mach_msg_type_number_t messageCnt;
		char message[1024];
		mach_msg_type_number_t defaultButtonTitleOffset; /* MiG doesn't use it */
		mach_msg_type_number_t defaultButtonTitleCnt;
		char defaultButtonTitle[128];
	} __Request__UNDDisplayNoticeSimple_rpc_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int rpctimeout;
		unsigned flags;
		mach_msg_type_number_t iconPathOffset; /* MiG doesn't use it */
		mach_msg_type_number_t iconPathCnt;
		char iconPath[128];
		mach_msg_type_number_t soundPathOffset; /* MiG doesn't use it */
		mach_msg_type_number_t soundPathCnt;
		char soundPath[128];
		mach_msg_type_number_t localizationPathOffset; /* MiG doesn't use it */
		mach_msg_type_number_t localizationPathCnt;
		char localizationPath[128];
		mach_msg_type_number_t headerOffset; /* MiG doesn't use it */
		mach_msg_type_number_t headerCnt;
		char header[128];
		mach_msg_type_number_t messageOffset; /* MiG doesn't use it */
		mach_msg_type_number_t messageCnt;
		char message[1024];
		mach_msg_type_number_t defaultButtonTitleOffset; /* MiG doesn't use it */
		mach_msg_type_number_t defaultButtonTitleCnt;
		char defaultButtonTitle[128];
		mach_msg_type_number_t alternateButtonTitleOffset; /* MiG doesn't use it */
		mach_msg_type_number_t alternateButtonTitleCnt;
		char alternateButtonTitle[128];
		mach_msg_type_number_t otherButtonTitleOffset; /* MiG doesn't use it */
		mach_msg_type_number_t otherButtonTitleCnt;
		char otherButtonTitle[128];
	} __Request__UNDDisplayAlertSimple_rpc_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif
#endif /* !__Request__UNDRequest_subsystem__defined */

/* union of all requests */

#ifndef __RequestUnion__UNDRequest_subsystem__defined
#define __RequestUnion__UNDRequest_subsystem__defined
union __RequestUnion__UNDRequest_subsystem {
	__Request__UNDExecute_rpc_t Request_UNDExecute_rpc;
	__Request__UNDDisplayNoticeFromBundle_rpc_t Request_UNDDisplayNoticeFromBundle_rpc;
	__Request__UNDDisplayAlertFromBundle_rpc_t Request_UNDDisplayAlertFromBundle_rpc;
	__Request__UNDDisplayCustomFromBundle_rpc_t Request_UNDDisplayCustomFromBundle_rpc;
	__Request__UNDCancelNotification_rpc_t Request_UNDCancelNotification_rpc;
	__Request__UNDDisplayNoticeSimple_rpc_t Request_UNDDisplayNoticeSimple_rpc;
	__Request__UNDDisplayAlertSimple_rpc_t Request_UNDDisplayAlertSimple_rpc;
};
#endif /* !__RequestUnion__UNDRequest_subsystem__defined */
/* typedefs for all replies */

#ifndef __Reply__UNDRequest_subsystem__defined
#define __Reply__UNDRequest_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__UNDExecute_rpc_t __attribute__((unused));
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
	} __Reply__UNDDisplayNoticeFromBundle_rpc_t __attribute__((unused));
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
	} __Reply__UNDDisplayAlertFromBundle_rpc_t __attribute__((unused));
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
	} __Reply__UNDDisplayCustomFromBundle_rpc_t __attribute__((unused));
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
	} __Reply__UNDCancelNotification_rpc_t __attribute__((unused));
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
	} __Reply__UNDDisplayNoticeSimple_rpc_t __attribute__((unused));
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
		unsigned response;
	} __Reply__UNDDisplayAlertSimple_rpc_t __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif
#endif /* !__Reply__UNDRequest_subsystem__defined */

/* union of all replies */

#ifndef __ReplyUnion__UNDRequest_subsystem__defined
#define __ReplyUnion__UNDRequest_subsystem__defined
union __ReplyUnion__UNDRequest_subsystem {
	__Reply__UNDExecute_rpc_t Reply_UNDExecute_rpc;
	__Reply__UNDDisplayNoticeFromBundle_rpc_t Reply_UNDDisplayNoticeFromBundle_rpc;
	__Reply__UNDDisplayAlertFromBundle_rpc_t Reply_UNDDisplayAlertFromBundle_rpc;
	__Reply__UNDDisplayCustomFromBundle_rpc_t Reply_UNDDisplayCustomFromBundle_rpc;
	__Reply__UNDCancelNotification_rpc_t Reply_UNDCancelNotification_rpc;
	__Reply__UNDDisplayNoticeSimple_rpc_t Reply_UNDDisplayNoticeSimple_rpc;
	__Reply__UNDDisplayAlertSimple_rpc_t Reply_UNDDisplayAlertSimple_rpc;
};
#endif /* !__RequestUnion__UNDRequest_subsystem__defined */

#ifndef subsystem_to_name_map_UNDRequest
#define subsystem_to_name_map_UNDRequest \
    { "UNDExecute_rpc", 6000 },\
    { "UNDDisplayNoticeFromBundle_rpc", 6001 },\
    { "UNDDisplayAlertFromBundle_rpc", 6002 },\
    { "UNDDisplayCustomFromBundle_rpc", 6003 },\
    { "UNDCancelNotification_rpc", 6005 },\
    { "UNDDisplayNoticeSimple_rpc", 6006 },\
    { "UNDDisplayAlertSimple_rpc", 6007 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _UNDRequest_user_ */
