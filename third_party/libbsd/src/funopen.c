/*
 * Copyright © 2011, 2013, 2017, 2020 Guillem Jover
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
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef HAVE_FOPENCOOKIE
struct funopen_cookie {
	void *orig_cookie;

	int (*readfn)(void *cookie, char *buf, int size);
	int (*writefn)(void *cookie, const char *buf, int size);
	off_t (*seekfn)(void *cookie, off_t offset, int whence);
	int (*closefn)(void *cookie);
};

static ssize_t
funopen_read(void *cookie, char *buf, size_t size)
{
	struct funopen_cookie *cookiewrap = cookie;

	if (cookiewrap->readfn == NULL) {
		errno = EBADF;
		return -1;
	}

	return cookiewrap->readfn(cookiewrap->orig_cookie, buf, size);
}

static ssize_t
funopen_write(void *cookie, const char *buf, size_t size)
{
	struct funopen_cookie *cookiewrap = cookie;

	if (cookiewrap->writefn == NULL)
		return EOF;

	return cookiewrap->writefn(cookiewrap->orig_cookie, buf, size);
}

static int
funopen_seek(void *cookie, off64_t *offset, int whence)
{
	struct funopen_cookie *cookiewrap = cookie;
	off_t soff = *offset;

	if (cookiewrap->seekfn == NULL) {
		errno = ESPIPE;
		return -1;
	}

	soff = cookiewrap->seekfn(cookiewrap->orig_cookie, soff, whence);
	*offset = soff;

	return *offset;
}

static int
funopen_close(void *cookie)
{
	struct funopen_cookie *cookiewrap = cookie;
	int rc;

	if (cookiewrap->closefn)
		rc = cookiewrap->closefn(cookiewrap->orig_cookie);
	else
		rc = 0;

	free(cookiewrap);

	return rc;
}

FILE *
funopen(const void *cookie,
        int (*readfn)(void *cookie, char *buf, int size),
        int (*writefn)(void *cookie, const char *buf, int size),
        off_t (*seekfn)(void *cookie, off_t offset, int whence),
        int (*closefn)(void *cookie))
{
	struct funopen_cookie *cookiewrap;
	cookie_io_functions_t funcswrap = {
		.read = funopen_read,
		.write = funopen_write,
		.seek = funopen_seek,
		.close = funopen_close,
	};
	const char *mode;

	if (readfn) {
		if (writefn == NULL)
			mode = "r";
		else
			mode = "r+";
	} else if (writefn) {
		mode = "w";
	} else {
		errno = EINVAL;
		return NULL;
	}

	cookiewrap = malloc(sizeof(*cookiewrap));
	if (cookiewrap == NULL)
		return NULL;

	cookiewrap->orig_cookie = (void *)cookie;
	cookiewrap->readfn = readfn;
	cookiewrap->writefn = writefn;
	cookiewrap->seekfn = seekfn;
	cookiewrap->closefn = closefn;

	return fopencookie(cookiewrap, mode, funcswrap);
}
#elif defined(__MUSL__)
/*
 * This is unimplementable on musl based systems, and upstream has stated
 * they will not add the needed support to implement it. Just ignore this
 * interface there, as it has never been provided anyway.
 */
#else
#error "Function funopen() needs to be ported or disabled."
#endif
