/*
 * IDENTIFICATION:
 * stub generated Mon Mar 22 18:02:44 2021
 * with a MiG generated by bootstrap_cmds-117
 * OPTIONS: 
 *	KernelServer
 */

/* Module upl */

#define	__MIG_check__Request__upl_subsystem__ 1

#include "upl_server.h"

#ifndef	mig_internal
#define	mig_internal	static __inline__
#endif	/* mig_internal */

#ifndef	mig_external
#define mig_external
#endif	/* mig_external */

#if	!defined(__MigTypeCheck) && defined(TypeCheck)
#define	__MigTypeCheck		TypeCheck	/* Legacy setting */
#endif	/* !defined(__MigTypeCheck) */

#if	!defined(__MigKernelSpecificCode) && defined(_MIG_KERNEL_SPECIFIC_CODE_)
#define	__MigKernelSpecificCode	_MIG_KERNEL_SPECIFIC_CODE_	/* Legacy setting */
#endif	/* !defined(__MigKernelSpecificCode) */

#ifndef	LimitCheck
#define	LimitCheck 0
#endif	/* LimitCheck */

#ifndef	min
#define	min(a,b)  ( ((a) < (b))? (a): (b) )
#endif	/* min */

#if !defined(_WALIGN_)
#define _WALIGN_(x) (((x) + 3) & ~3)
#endif /* !defined(_WALIGN_) */

#if !defined(_WALIGNSZ_)
#define _WALIGNSZ_(x) _WALIGN_(sizeof(x))
#endif /* !defined(_WALIGNSZ_) */

#ifndef	UseStaticTemplates
#define	UseStaticTemplates	0
#endif	/* UseStaticTemplates */

#ifndef MIG_SERVER_ROUTINE
#define MIG_SERVER_ROUTINE
#endif

#ifndef	__DeclareRcvRpc
#define	__DeclareRcvRpc(_NUM_, _NAME_)
#endif	/* __DeclareRcvRpc */

#ifndef	__BeforeRcvRpc
#define	__BeforeRcvRpc(_NUM_, _NAME_)
#endif	/* __BeforeRcvRpc */

#ifndef	__AfterRcvRpc
#define	__AfterRcvRpc(_NUM_, _NAME_)
#endif	/* __AfterRcvRpc */

#ifndef	__DeclareRcvSimple
#define	__DeclareRcvSimple(_NUM_, _NAME_)
#endif	/* __DeclareRcvSimple */

#ifndef	__BeforeRcvSimple
#define	__BeforeRcvSimple(_NUM_, _NAME_)
#endif	/* __BeforeRcvSimple */

#ifndef	__AfterRcvSimple
#define	__AfterRcvSimple(_NUM_, _NAME_)
#endif	/* __AfterRcvSimple */

#define novalue void

#if	__MigKernelSpecificCode
#define msgh_request_port	msgh_remote_port
#define MACH_MSGH_BITS_REQUEST(bits)	MACH_MSGH_BITS_REMOTE(bits)
#define msgh_reply_port		msgh_local_port
#define MACH_MSGH_BITS_REPLY(bits)	MACH_MSGH_BITS_LOCAL(bits)
#else
#define msgh_request_port	msgh_local_port
#define MACH_MSGH_BITS_REQUEST(bits)	MACH_MSGH_BITS_LOCAL(bits)
#define msgh_reply_port		msgh_remote_port
#define MACH_MSGH_BITS_REPLY(bits)	MACH_MSGH_BITS_REMOTE(bits)
#endif /* __MigKernelSpecificCode */

#define MIG_RETURN_ERROR(X, code)	{\
				((mig_reply_error_t *)X)->RetCode = code;\
				((mig_reply_error_t *)X)->NDR = NDR_record;\
				return;\
				}

/* Forward Declarations */


mig_internal novalue _Xupl_abort
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xupl_abort_range
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xupl_commit
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);

mig_internal novalue _Xupl_commit_range
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP);


#if ( __MigTypeCheck )
#if __MIG_check__Request__upl_subsystem__
#if !defined(__MIG_check__Request__upl_abort_t__defined)
#define __MIG_check__Request__upl_abort_t__defined

mig_internal kern_return_t __MIG_check__Request__upl_abort_t(__attribute__((__unused__)) __Request__upl_abort_t *In0P)
{

	typedef __Request__upl_abort_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__upl_abort_t__defined) */
#endif /* __MIG_check__Request__upl_subsystem__ */
#endif /* ( __MigTypeCheck ) */


/* Routine upl_abort */
mig_internal novalue _Xupl_abort
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		integer_t abort_cond;
		mach_msg_trailer_t trailer;
	} Request __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif
	typedef __Request__upl_abort_t __Request;
	typedef __Reply__upl_abort_t Reply __attribute__((unused));

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__upl_abort_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__upl_abort_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	upl_t upl_object;

	__DeclareRcvRpc(2050, "upl_abort")
	__BeforeRcvRpc(2050, "upl_abort")

#if	defined(__MIG_check__Request__upl_abort_t__defined)
	check_result = __MIG_check__Request__upl_abort_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__upl_abort_t__defined) */

	upl_object = convert_port_to_upl(In0P->Head.msgh_request_port);

	OutP->RetCode = upl_abort(upl_object, In0P->abort_cond);
	upl_deallocate(upl_object);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(2050, "upl_abort")
}

#if ( __MigTypeCheck )
#if __MIG_check__Request__upl_subsystem__
#if !defined(__MIG_check__Request__upl_abort_range_t__defined)
#define __MIG_check__Request__upl_abort_range_t__defined

mig_internal kern_return_t __MIG_check__Request__upl_abort_range_t(__attribute__((__unused__)) __Request__upl_abort_range_t *In0P)
{

	typedef __Request__upl_abort_range_t __Request;
#if	__MigTypeCheck
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (In0P->Head.msgh_size != (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__upl_abort_range_t__defined) */
#endif /* __MIG_check__Request__upl_subsystem__ */
#endif /* ( __MigTypeCheck ) */


/* Routine upl_abort_range */
mig_internal novalue _Xupl_abort_range
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		upl_offset_t offset;
		upl_size_t size;
		integer_t abort_cond;
		mach_msg_trailer_t trailer;
	} Request __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif
	typedef __Request__upl_abort_range_t __Request;
	typedef __Reply__upl_abort_range_t Reply __attribute__((unused));

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__upl_abort_range_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__upl_abort_range_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	upl_t upl_object;

	__DeclareRcvRpc(2051, "upl_abort_range")
	__BeforeRcvRpc(2051, "upl_abort_range")

#if	defined(__MIG_check__Request__upl_abort_range_t__defined)
	check_result = __MIG_check__Request__upl_abort_range_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__upl_abort_range_t__defined) */

	upl_object = convert_port_to_upl(In0P->Head.msgh_request_port);

	OutP->RetCode = upl_abort_range(upl_object, In0P->offset, In0P->size, In0P->abort_cond, &OutP->empty);
	upl_deallocate(upl_object);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(2051, "upl_abort_range")
}

#if ( __MigTypeCheck )
#if __MIG_check__Request__upl_subsystem__
#if !defined(__MIG_check__Request__upl_commit_t__defined)
#define __MIG_check__Request__upl_commit_t__defined

mig_internal kern_return_t __MIG_check__Request__upl_commit_t(__attribute__((__unused__)) __Request__upl_commit_t *In0P)
{

	typedef __Request__upl_commit_t __Request;
#if	__MigTypeCheck
	unsigned int msgh_size;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	msgh_size = In0P->Head.msgh_size;
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (msgh_size < (mach_msg_size_t)(sizeof(__Request) - 2048)) ||  (msgh_size > (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if defined(__NDR_convert__int_rep__Request__upl_commit_t__page_listCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep)
		__NDR_convert__int_rep__Request__upl_commit_t__page_listCnt(&In0P->page_listCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__upl_commit_t__page_listCnt__defined */
#if	__MigTypeCheck
	if ( In0P->page_listCnt > 512 )
		return MIG_BAD_ARGUMENTS;
	if (((msgh_size - (mach_msg_size_t)(sizeof(__Request) - 2048)) / 8 < In0P->page_listCnt) ||
	    (msgh_size != (mach_msg_size_t)(sizeof(__Request) - 2048) + (8 * In0P->page_listCnt)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__upl_commit_t__defined) */
#endif /* __MIG_check__Request__upl_subsystem__ */
#endif /* ( __MigTypeCheck ) */


/* Routine upl_commit */
mig_internal novalue _Xupl_commit
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

#ifdef  __MigPackStructs
#pragma pack(push, 4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_msg_type_number_t page_listCnt;
		upl_page_info_t page_list[256];
		mach_msg_trailer_t trailer;
	} Request __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif
	typedef __Request__upl_commit_t __Request;
	typedef __Reply__upl_commit_t Reply __attribute__((unused));

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__upl_commit_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__upl_commit_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	upl_t upl_object;

	__DeclareRcvRpc(2052, "upl_commit")
	__BeforeRcvRpc(2052, "upl_commit")

#if	defined(__MIG_check__Request__upl_commit_t__defined)
	check_result = __MIG_check__Request__upl_commit_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__upl_commit_t__defined) */

	upl_object = convert_port_to_upl(In0P->Head.msgh_request_port);

	OutP->RetCode = upl_commit(upl_object, In0P->page_list, In0P->page_listCnt);
	upl_deallocate(upl_object);
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	__AfterRcvRpc(2052, "upl_commit")
}

#if ( __MigTypeCheck )
#if __MIG_check__Request__upl_subsystem__
#if !defined(__MIG_check__Request__upl_commit_range_t__defined)
#define __MIG_check__Request__upl_commit_range_t__defined

mig_internal kern_return_t __MIG_check__Request__upl_commit_range_t(__attribute__((__unused__)) __Request__upl_commit_range_t *In0P)
{

	typedef __Request__upl_commit_range_t __Request;
#if	__MigTypeCheck
	unsigned int msgh_size;
#endif	/* __MigTypeCheck */

#if	__MigTypeCheck
	msgh_size = In0P->Head.msgh_size;
	if ((In0P->Head.msgh_bits & MACH_MSGH_BITS_COMPLEX) ||
	    (msgh_size < (mach_msg_size_t)(sizeof(__Request) - 2048)) ||  (msgh_size > (mach_msg_size_t)sizeof(__Request)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

#if defined(__NDR_convert__int_rep__Request__upl_commit_range_t__page_listCnt__defined)
	if (In0P->NDR.int_rep != NDR_record.int_rep)
		__NDR_convert__int_rep__Request__upl_commit_range_t__page_listCnt(&In0P->page_listCnt, In0P->NDR.int_rep);
#endif	/* __NDR_convert__int_rep__Request__upl_commit_range_t__page_listCnt__defined */
#if	__MigTypeCheck
	if ( In0P->page_listCnt > 512 )
		return MIG_BAD_ARGUMENTS;
	if (((msgh_size - (mach_msg_size_t)(sizeof(__Request) - 2048)) / 8 < In0P->page_listCnt) ||
	    (msgh_size != (mach_msg_size_t)(sizeof(__Request) - 2048) + (8 * In0P->page_listCnt)))
		return MIG_BAD_ARGUMENTS;
#endif	/* __MigTypeCheck */

	return MACH_MSG_SUCCESS;
}
#endif /* !defined(__MIG_check__Request__upl_commit_range_t__defined) */
#endif /* __MIG_check__Request__upl_subsystem__ */
#endif /* ( __MigTypeCheck ) */


/* Routine upl_commit_range */
mig_internal novalue _Xupl_commit_range
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{

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
		mach_msg_trailer_t trailer;
	} Request __attribute__((unused));
#ifdef  __MigPackStructs
#pragma pack(pop)
#endif
	typedef __Request__upl_commit_range_t __Request;
	typedef __Reply__upl_commit_range_t Reply __attribute__((unused));

	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	Request *In0P = (Request *) InHeadP;
	Reply *OutP = (Reply *) OutHeadP;
#ifdef	__MIG_check__Request__upl_commit_range_t__defined
	kern_return_t check_result;
#endif	/* __MIG_check__Request__upl_commit_range_t__defined */

#if	__MigKernelSpecificCode
#else
#endif /* __MigKernelSpecificCode */
	upl_t upl_object;

	__DeclareRcvRpc(2053, "upl_commit_range")
	__BeforeRcvRpc(2053, "upl_commit_range")

#if	defined(__MIG_check__Request__upl_commit_range_t__defined)
	check_result = __MIG_check__Request__upl_commit_range_t((__Request *)In0P);
	if (check_result != MACH_MSG_SUCCESS)
		{ MIG_RETURN_ERROR(OutP, check_result); }
#endif	/* defined(__MIG_check__Request__upl_commit_range_t__defined) */

	upl_object = convert_port_to_upl(In0P->Head.msgh_request_port);

	OutP->RetCode = upl_commit_range(upl_object, In0P->offset, In0P->size, In0P->cntrl_flags, In0P->page_list, In0P->page_listCnt, &OutP->empty);
	upl_deallocate(upl_object);
	if (OutP->RetCode != KERN_SUCCESS) {
		MIG_RETURN_ERROR(OutP, OutP->RetCode);
	}
#if	__MigKernelSpecificCode
#endif /* __MigKernelSpecificCode */

	OutP->NDR = NDR_record;


	OutP->Head.msgh_size = (mach_msg_size_t)(sizeof(Reply));
	__AfterRcvRpc(2053, "upl_commit_range")
}



/* Description of this subsystem, for use in direct RPC */
const struct upl_subsystem upl_subsystem = {
	upl_server_routine,
	2050,
	2054,
	(mach_msg_size_t)sizeof(union __ReplyUnion__upl_subsystem),
	(vm_address_t)0,
	{
          { (mig_impl_routine_t) 0,
          (mig_stub_routine_t) _Xupl_abort, 2, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__upl_abort_t)},
          { (mig_impl_routine_t) 0,
          (mig_stub_routine_t) _Xupl_abort_range, 5, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__upl_abort_range_t)},
          { (mig_impl_routine_t) 0,
          (mig_stub_routine_t) _Xupl_commit, 3, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__upl_commit_t)},
          { (mig_impl_routine_t) 0,
          (mig_stub_routine_t) _Xupl_commit_range, 7, 0, (routine_arg_descriptor_t)0, (mach_msg_size_t)sizeof(__Reply__upl_commit_range_t)},
	}
};

mig_external boolean_t upl_server
	(mach_msg_header_t *InHeadP, mach_msg_header_t *OutHeadP)
{
	/*
	 * typedef struct {
	 * 	mach_msg_header_t Head;
	 * 	NDR_record_t NDR;
	 * 	kern_return_t RetCode;
	 * } mig_reply_error_t;
	 */

	mig_routine_t routine;

	OutHeadP->msgh_bits = MACH_MSGH_BITS(MACH_MSGH_BITS_REPLY(InHeadP->msgh_bits), 0);
	OutHeadP->msgh_remote_port = InHeadP->msgh_reply_port;
	/* Minimal size: routine() will update it if different */
	OutHeadP->msgh_size = (mach_msg_size_t)sizeof(mig_reply_error_t);
	OutHeadP->msgh_local_port = MACH_PORT_NULL;
	OutHeadP->msgh_id = InHeadP->msgh_id + 100;
	OutHeadP->msgh_reserved = 0;

	if ((InHeadP->msgh_id > 2053) || (InHeadP->msgh_id < 2050) ||
	    ((routine = upl_subsystem.routine[InHeadP->msgh_id - 2050].stub_routine) == 0)) {
		((mig_reply_error_t *)OutHeadP)->NDR = NDR_record;
		((mig_reply_error_t *)OutHeadP)->RetCode = MIG_BAD_ID;
		return FALSE;
	}
	(*routine) (InHeadP, OutHeadP);
	return TRUE;
}

mig_external mig_routine_t upl_server_routine
	(mach_msg_header_t *InHeadP)
{
	int msgh_id;

	msgh_id = InHeadP->msgh_id - 2050;

	if ((msgh_id > 3) || (msgh_id < 0))
		return 0;

	return upl_subsystem.routine[msgh_id].stub_routine;
}