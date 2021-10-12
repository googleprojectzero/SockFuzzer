/*
 * Copyright © 2021 Guillem Jover <guillem@hadrons.org>
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

#include <stddef.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <md5.h>
#include "local-link.h"

static void (*libmd_MD5Init)(MD5_CTX *);
static void (*libmd_MD5Update)(MD5_CTX *, const uint8_t *, size_t);
static void (*libmd_MD5Pad)(MD5_CTX *);
static void (*libmd_MD5Final)(uint8_t [MD5_DIGEST_LENGTH], MD5_CTX *);
static void (*libmd_MD5Transform)(uint32_t [4], const uint8_t [MD5_BLOCK_LENGTH]);
static char *(*libmd_MD5End)(MD5_CTX *, char *);
static char *(*libmd_MD5File)(const char *, char *);
static char *(*libmd_MD5FileChunk)(const char *, char *, off_t, off_t);
static char *(*libmd_MD5Data)(const uint8_t *, size_t, char *);

static void *
libmd_loader(const char *symbol)
{
	void *func;

	func = dlsym(RTLD_NEXT, symbol);
	if (func == NULL) {
		fprintf(stderr,
		        "libbsd: cannot find wrapped symbol %s in libc or libmd\n",
		        symbol);
		abort();
	}

	return func;
}

#define libmd_wrapper(symbol) \
	if (libmd_ ## symbol == NULL) \
		libmd_ ## symbol = libmd_loader(#symbol)

void
MD5Init(MD5_CTX *context)
{
	libmd_wrapper(MD5Init);
	libmd_MD5Init(context);
}
libbsd_link_warning(MD5Init,
                    "This function is a deprecated wrapper, use libmd instead.");

void
MD5Update(MD5_CTX *context, const uint8_t *data, size_t len)
{
	libmd_wrapper(MD5Update);
	libmd_MD5Update(context, data, len);
}
libbsd_link_warning(MD5Update,
                    "This function is a deprecated wrapper, use libmd instead.");

void
MD5Pad(MD5_CTX *context)
{
	libmd_wrapper(MD5Pad);
	libmd_MD5Pad(context);
}
libbsd_link_warning(MD5Pad,
                    "This function is a deprecated wrapper, use libmd instead.");

void
MD5Final(uint8_t digest[MD5_DIGEST_LENGTH], MD5_CTX *context)
{
	libmd_wrapper(MD5Final);
	libmd_MD5Final(digest, context);
}
libbsd_link_warning(MD5Final,
                    "This function is a deprecated wrapper, use libmd instead.");

void
MD5Transform(uint32_t state[4], const uint8_t block[MD5_BLOCK_LENGTH])
{
	libmd_wrapper(MD5Transform);
	libmd_MD5Transform(state, block);
}
libbsd_link_warning(MD5Transform,
                    "This function is a deprecated wrapper, use libmd instead.");

char *
MD5End(MD5_CTX *context, char *buf)
{
	libmd_wrapper(MD5End);
	return libmd_MD5End(context, buf);
}
libbsd_link_warning(MD5End,
                    "This function is a deprecated wrapper, use libmd instead.");

char *
MD5File(const char *filename, char *buf)
{
	libmd_wrapper(MD5File);
	return MD5File(filename, buf);
}
libbsd_link_warning(MD5File,
                    "This function is a deprecated wrapper, use libmd instead.");

char *
MD5FileChunk(const char *filename, char *buf, off_t offset, off_t length)
{
	libmd_wrapper(MD5FileChunk);
	return libmd_MD5FileChunk(filename, buf, offset, length);
}
libbsd_link_warning(MD5FileChunk,
                    "This function is a deprecated wrapper, use libmd instead.");

char *
MD5Data(const uint8_t *data, size_t len, char *buf)
{
	libmd_wrapper(MD5Data);
	return libmd_MD5Data(data, len, buf);
}
libbsd_link_warning(MD5Data,
                    "This function is a deprecated wrapper, use libmd instead.");
