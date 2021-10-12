/*
 * Copyright © 2010 Guillem Jover <guillem@hadrons.org>
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

#include <sys/cdefs.h>

#include <sys/param.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <errno.h>
#include <unistd.h>

#if defined(SO_PEERCRED)
/* Linux and OpenBSD */
int
getpeereid(int s, uid_t *euid, gid_t *egid)
{
/* XXX: This should be autodetected at build time instead. */
#if defined(__linux__)
	struct ucred cred;
#elif defined(__OpenBSD__)
	struct sockpeercred cred;
#endif
	socklen_t credlen = sizeof(cred);
	int ret;

	ret = getsockopt(s, SOL_SOCKET, SO_PEERCRED, &cred, &credlen);
	if (ret != 0)
		return ret;

	*euid = cred.uid;
	*egid = cred.gid;

	return 0;
}
#elif defined(LOCAL_PEERCRED)
/* FreeBSD */
#include <sys/ucred.h>

int
getpeereid(int s, uid_t *euid, gid_t *egid)
{
	struct xucred cred;
	socklen_t credlen = sizeof(cred);
	int ret;

	ret = getsockopt(s, 0, LOCAL_PEERCRED, &cred, &credlen);
	if (ret != 0)
		return ret;
	if (cred.cr_version != XUCRED_VERSION)
		return EINVAL;

	*euid = cred.cr_uid;
	*egid = cred.cr_gid;

	return 0;
}
#elif defined(LOCAL_PEEREID)
/* NetBSD */
int
getpeereid(int s, uid_t *euid, gid_t *egid)
{
	struct unpcbid cred;
	socklen_t credlen = sizeof(cred);
	int ret;

	ret = getsockopt(s, 0, LOCAL_PEEREID, &cred, &credlen);
	if (ret != 0)
		return ret;

	*euid = cred.unp_euid;
	*egid = cred.unp_egid;

	return 0;
}
#elif defined(__sun)
/* Solaris */
#include <alloca.h>
#include <ucred.h>

int
getpeereid(int s, uid_t *euid, gid_t *egid)
{
	ucred_t *cred = alloca(ucred_size());
	int ret;

	ret = getpeerucred(s, &cred);
	if (ret != 0)
		return ret;

	*euid = ucred_geteuid(cred);
	if (*euid < 0)
		return -1;
	*egid = ucred_getegid(cred);
	if (*egid < 0)
		return -1;

	return 0;
}
#else
#warning "This platform needs an implementation of getpeereid()"
int
getpeereid(int s, uid_t *euid, gid_t *egid)
{
	*euid = geteuid();
	*egid = getegid();

	return 0;
}
#endif
