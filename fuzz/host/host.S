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

.globl GetStackPointer
.text
.type GetStackPointer,@function
GetStackPointer:
	movq	%rsp, %rax
	ret

.globl CallContinuationWithStack
.text
.type CallContinuationWithStack,@function
CallContinuationWithStack:
    movq    %rdi, %r12       /* continuation */
    movq    %rsi, %r13       /* continuation param */
    movq    %rdx, %r14       /* wait result */
    movq    %rcx, %rsp       /* set the stack */

    xorq    %rbp, %rbp       /* zero frame pointer */

    movq    %r12, %rcx       /* continuation */
    movq    %r13, %rdi       /* continuation param */
    movq    %r14, %rsi       /* wait result */

    call    *%rcx            /* call continuation */

    call    GetHostThreadFinished
    call    *%rax            /* Call ThreadFinished */

    int3                     /* This should now be unreachable */
