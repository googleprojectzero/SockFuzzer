/*
 * Copyright © 2017 Guillem Jover <guillem@hadrons.org>
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

#include <sys/types.h>
#include <sys/stat.h>

#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <nlist.h>

static int data_prv_init = 50;
extern int data_pub_init;
extern int data_pub_uninit[2048];
extern int *data_pub_ptr;

int *data_pub_ptr = &data_prv_init;
int data_pub_init = 10;
int data_pub_uninit[2048];

extern int
func_pub(void);

int
func_pub(void)
{
	return 42;
}

int
main(int argc, char **argv)
{
	struct nlist nl[] = {
		{ .n_un.n_name = "main" },
		{ .n_un.n_name = "func_pub" },
		{ .n_un.n_name = "data_pub_uninit" },
		{ .n_un.n_name = "data_pub_init" },
		{ .n_un.n_name = "data_prv_init" },
		{ .n_un.n_name = NULL },
	};
	int rc;

	assert(*data_pub_ptr == 50);

	assert(nl[0].n_name == nl[0].n_un.n_name);

	rc = nlist(argv[0], nl);
	assert(rc == 0);

#if defined(__powerpc64__) && _CALL_ELF == 1
	/* On PowerPC 64-bit ELFv1, the functions are stored in
	 * the .text sections but they are accessed through a function
	 * descriptor stored in a data section, for example for PowerPC
	 * 64-bit that section is called .opd. */
	assert(nl[0].n_type == (N_DATA | N_EXT));
	assert(nl[1].n_type == (N_DATA | N_EXT));
#else
	assert(nl[0].n_type == (N_TEXT | N_EXT));
	assert(nl[1].n_type == (N_TEXT | N_EXT));
#endif
	assert(nl[2].n_type == (N_BSS | N_EXT));
	assert(nl[3].n_type == (N_DATA | N_EXT));
	assert(nl[4].n_type == (N_DATA));

	return 0;
}
