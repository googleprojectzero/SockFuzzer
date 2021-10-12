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

#include <assert.h>
#include <string.h>

int
main(int argc, char **argv)
{
	char buf[256];

	/* Test copy to 0-sized buffer . */
	memset(buf, 0, sizeof(buf));
	assert(strlcpy(buf, "xyz", 0) == 3);
	assert(strcmp(buf, "") == 0);

	/* Test normal copy. */
	memset(buf, 0, sizeof(buf));
	assert(strlcpy(buf, "xyz", sizeof(buf)) == 3);
	assert(strcmp(buf, "xyz") == 0);

	/* Test truncated copy. */
	memset(buf, 0, sizeof(buf));
	assert(strlcpy(buf, "abcdefabcdef", 10) == 12);
	assert(strcmp(buf, "abcdefabc") == 0);

	/* Test concat to 0-sized buffer. */
	memset(buf, 0, sizeof(buf));
	assert(strlcat(buf, "abc", 0) == 3);
	assert(strcmp(buf, "") == 0);

	/* Test concat to full buffer. */
	memset(buf, 0, sizeof(buf));
	assert(strlcat(buf, "abcde", 6) == 5);
	assert(strcmp(buf, "abcde") == 0);
	assert(strlcat(buf, "xyz", 5) == 8);
	assert(strcmp(buf, "abcde") == 0);

	/* Test normal concat. */
	memset(buf, 0, sizeof(buf));
	assert(strlcat(buf, "abc", sizeof(buf)) == 3);
	assert(strcmp(buf, "abc") == 0);
	assert(strlcat(buf, "xyz", sizeof(buf)) == 6);
	assert(strcmp(buf, "abcxyz") == 0);

	/* Test truncated concat. */
	memset(buf, 0, sizeof(buf));
	assert(strlcat(buf, "abcabc", 10) == 6);
	assert(strcmp(buf, "abcabc") == 0);
	assert(strlcat(buf, "xyzxyz", 10) == 12);
	assert(strcmp(buf, "abcabcxyz") == 0);

	/* Test truncated concat w/ truncated dst. */
	memset(buf, 0, sizeof(buf));
	assert(strlcat(buf, "abcabc", 10) == 6);
	assert(strcmp(buf, "abcabc") == 0);
	assert(strlcat(buf, "xyz", 4) == 7);
	assert(strcmp(buf, "abcabc") == 0);

	return 0;
}
