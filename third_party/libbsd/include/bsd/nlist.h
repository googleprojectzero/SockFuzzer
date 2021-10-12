/*
 * Copyright © 2009 Guillem Jover <guillem@hadrons.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef LIBBSD_NLIST_H
#define LIBBSD_NLIST_H

#ifdef LIBBSD_OVERLAY
#include <sys/cdefs.h>
#else
#include <bsd/sys/cdefs.h>
#endif

struct nlist {
	union {
		char *n_name;
		union {
			char *n_name;
			struct n_list *n_next;
			long n_strx;
		} n_un;
	};
	unsigned char n_type;
	char n_other;
	short n_desc;
	unsigned long n_value;
};

#define n_hash	n_desc		/* used internally by ld(1); XXX */

/*
 * Defines for n_type.
 */
#define N_UNDF	0x00		/* Undefined */
#define N_ABS	0x02		/* Absolute address */
#define N_TEXT	0x04		/* Text segment */
#define N_DATA	0x06		/* Data segment */
#define N_BSS	0x08		/* Bss segment */
#define N_INDR	0x0a		/* Alias definition */
#define N_SIZE	0x0c		/* Pseudo type, defines a symbol's size */
#define N_COMM	0x12		/* Common reference */
/* GNU extensions */
#define N_SETA	0x14		/* Absolute set element symbol */
#define N_SETT	0x16		/* Text set element symbol */
#define N_SETD	0x18		/* Data set element symbol */
#define N_SETB	0x1a		/* Bss set element symbol */
#define N_SETV	0x1c		/* Set vector symbol */
/* end GNU extensions */
#define N_FN	0x1e		/* File name (N_EXT on) */
#define N_WARN	0x1e		/* Warning message (N_EXT off) */

#define N_EXT	0x01		/* External (global) bit, OR'ed in */
#define N_TYPE	0x1e		/* Mask for all the type bits */
#define N_STAB	0xe0		/* Mask for debugger symbols -- stab(5) */

#define N_NAME(p)	((p)->n_un.n_name)

/*
 * Defines for n_other.  It contains the ".type" (AUX) field in the least
 * significant 4 bits, and the binding (for weak symbols) in the most
 * significant 4 bits.
 */
#define N_AUX(p)	((p)->n_other & 0xf)
#define N_BIND(p)	(((unsigned int)(p)->n_other >> 4) & 0xf)
#define N_OTHER(r, v)	(((unsigned int)(r) << 4) | ((v) & 0xf))

#define AUX_OBJECT	1	/* Data object */
#define AUX_FUNC	2	/* Function */

/*#define BIND_LOCAL	0	Not used */
/*#define BIND_GLOBAL	1	Not used */
#define BIND_WEAK	2	/* Weak binding */

#define N_FORMAT	"%08x"	/* namelist value format; XXX */

__BEGIN_DECLS
extern int nlist(const char *filename, struct nlist *list);
__END_DECLS

#endif
