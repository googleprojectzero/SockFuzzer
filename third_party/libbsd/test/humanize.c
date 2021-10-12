/*
 * Copyright © 2013 Guillem Jover <guillem@hadrons.org>
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

#include <assert.h>
#include <errno.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
	uint64_t uval;
	int64_t val;

	assert(expand_number("512", &uval) == 0);
	assert(uval == 512);

	assert(expand_number("512b", &uval) == 0);
	assert(uval == 512);

	assert(expand_number("10k", &uval) == 0);
	assert(uval == 10240);

	assert(expand_number("20M", &uval) == 0);
	assert(uval == 20971520);

	assert(dehumanize_number("512", &val) == 0);
	assert(val == 512);

	assert(dehumanize_number("512b", &val) == 0);
	assert(val == 512);

	assert(dehumanize_number("10k", &val) == 0);
	assert(val == 10240);

	assert(dehumanize_number("20M", &val) == 0);
	assert(val == 20971520);

	assert(dehumanize_number("-3G", &val) == 0);
	assert(val == -3221225472LL);

	assert(dehumanize_number("9223372036854775807", &val) == 0);
	assert(val == INT64_MAX);

	assert(dehumanize_number("9223372036854775808", &val) == -1);
	assert(errno == ERANGE);

	assert(dehumanize_number("-9223372036854775808", &val) == 0);
	assert(val == INT64_MIN);

	assert(dehumanize_number("-9223372036854775809", &val) == -1);
	assert(errno == ERANGE);

	return 0;
}
