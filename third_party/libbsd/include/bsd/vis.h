/*	$NetBSD: vis.h,v 1.25 2017/04/23 01:57:36 christos Exp $	*/

/*-
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)vis.h	8.1 (Berkeley) 6/2/93
 */

#ifndef LIBBSD_VIS_H
#define LIBBSD_VIS_H

#include <sys/types.h>

/*
 * to select alternate encoding format
 */
#define	VIS_OCTAL	0x0001	/* use octal \ddd format */
#define	VIS_CSTYLE	0x0002	/* use \[nrft0..] where appropriate */

/*
 * to alter set of characters encoded (default is to encode all
 * non-graphic except space, tab, and newline).
 */
#define	VIS_SP		0x0004	/* also encode space */
#define	VIS_TAB		0x0008	/* also encode tab */
#define	VIS_NL		0x0010	/* also encode newline */
#define	VIS_WHITE	(VIS_SP | VIS_TAB | VIS_NL)
#define	VIS_SAFE	0x0020	/* only encode "unsafe" characters */
#define	VIS_DQ		0x8000	/* also encode double quotes */

/*
 * other
 */
#define	VIS_NOSLASH	0x0040	/* inhibit printing '\' */
#define	VIS_HTTP1808	0x0080	/* http-style escape % hex hex */
#define	VIS_HTTPSTYLE	0x0080	/* http-style escape % hex hex */
#define	VIS_MIMESTYLE	0x0100	/* mime-style escape = HEX HEX */
#define	VIS_HTTP1866	0x0200	/* http-style &#num; or &string; */
#define	VIS_NOESCAPE	0x0400	/* don't decode `\' */
#define	_VIS_END	0x0800	/* for unvis */
#define	VIS_GLOB	0x1000	/* encode glob(3) magic characters */
#define	VIS_SHELL	0x2000	/* encode shell special characters [not glob] */
#define	VIS_META	(VIS_WHITE | VIS_GLOB | VIS_SHELL)
#define	VIS_NOLOCALE	0x4000	/* encode using the C locale */

/*
 * unvis return codes
 */
#define	UNVIS_VALID	 1	/* character valid */
#define	UNVIS_VALIDPUSH	 2	/* character valid, push back passed char */
#define	UNVIS_NOCHAR	 3	/* valid sequence, no character produced */
#define	UNVIS_SYNBAD	-1	/* unrecognized escape sequence */
#define	UNVIS_ERROR	-2	/* decoder in unknown state (unrecoverable) */

/*
 * unvis flags
 */
#define	UNVIS_END	_VIS_END	/* no more characters */

#ifdef LIBBSD_OVERLAY
#include <sys/cdefs.h>
#else
#include <bsd/sys/cdefs.h>
#endif

/*
 * NetBSD added an strnvis and unfortunately made it incompatible with the
 * existing one in OpenBSD and Freedesktop's libbsd (the former having existed
 * for over ten years). Despite this incompatibility being reported during
 * development (see http://gnats.netbsd.org/44977) they still shipped it.
 * Even more unfortunately FreeBSD and later MacOS picked up this incompatible
 * implementation.
 *
 * Provide both implementations and default for now on the historical one to
 * avoid breakage, we will switch to the NetBSD one in libbsd 0.10.0 or so.
 * Define LIBBSD_NETBSD_VIS to switch to the NetBSD one now.
 * Define LIBBSD_OPENBSD_VIS to keep using the OpenBSD one.
 */
#if defined(LIBBSD_OPENBSD_VIS)
#undef LIBBSD_NETBSD_VIS
#elif !defined(LIBBSD_NETBSD_VIS)
#warning "NetBSD added incompatible strnvis() and strnunvis(), please see <bsd/vis.h> for more detils."
#endif

__BEGIN_DECLS
char	*vis(char *, int, int, int);
char	*nvis(char *, size_t, int, int, int);

char	*svis(char *, int, int, int, const char *);
char	*snvis(char *, size_t, int, int, int, const char *);

int	strvis(char *, const char *, int);
int	stravis(char **, const char *, int);
#ifdef LIBBSD_NETBSD_VIS
/* NetBSD prototype. */
int	LIBBSD_REDIRECT(strnvis, (char *, size_t, const char *, int),
                        strnvis_netbsd);
#else
/* OpenBSD prototype (current default). */
int	strnvis(char *, const char *, size_t, int);
#endif

int	strsvis(char *, const char *, int, const char *);
int	strsnvis(char *, size_t, const char *, int, const char *);

int	strvisx(char *, const char *, size_t, int);
int	strnvisx(char *, size_t, const char *, size_t, int);
int	strenvisx(char *, size_t, const char *, size_t, int, int *);

int	strsvisx(char *, const char *, size_t, int, const char *);
int	strsnvisx(char *, size_t, const char *, size_t, int, const char *);
int	strsenvisx(char *, size_t, const char *, size_t , int, const char *,
    int *);

int	strunvis(char *, const char *);
#ifdef LIBBSD_NETBSD_VIS
/* NetBSD prototype. */
int	LIBBSD_REDIRECT(strnunvis, (char *, size_t, const char *),
                        strnunvis_netbsd);
#else
/* OpenBSD prototype (current default). */
ssize_t	strnunvis(char *, const char *, size_t);
#endif

int	strunvisx(char *, const char *, int);
int	strnunvisx(char *, size_t, const char *, int);

int	unvis(char *, int, int *, int);
__END_DECLS

#endif /* !LIBBSD_VIS_H */
