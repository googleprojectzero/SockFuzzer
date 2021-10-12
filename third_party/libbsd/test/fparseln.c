/*
 * Copyright © 2015 Guillem Jover <guillem@hadrons.org>
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test-stream.h"

#define TEST_LINES 9
static const char *data_test[] = {
	"# This is a test\n",
	"line 1\n",
	"line 2 \\\n",
	"line 3 # Comment\n",
	"line 4 \\# Not comment \\\\\\\\\n",
	"\n",
	"# And a comment \\\n",
	"line 5 \\\\\\\n",
	"line 6 w/ escape sequences \\b, \\t, \\\\t",
};

#define EXPECT_LINES 5
static size_t lineno_expect[] = { 2, 4, 5, 6, 9 };

static const char *data_parse[] = {
	"line 1",
	"line 2 line 3 ",
	"line 4 \\# Not comment \\\\\\\\",
	"",
	"line 5 \\\\line 6 w/ escape sequences \\b, \\t, \\\\t",
};
static const char *data_escape[] = {
	"line 1",
	"line 2 line 3 ",
	"line 4 # Not comment \\\\",
	"",
	"line 5 \\line 6 w/ escape sequences b, t, \\t",
};

static void
test_fparseln(const char **data_expect, int flags)
{
	FILE *fp;
	size_t i, len, lineno = 0;

	fp = pipe_feed("%s", (const void **)data_test, TEST_LINES);
	for (i = 0; i < EXPECT_LINES; i++) {
		char *str = fparseln(fp, &len, &lineno, NULL, flags);

		assert(str);
		assert(lineno == lineno_expect[i]);
		assert(strcmp(str, data_expect[i]) == 0);

		free(str);
	}
	assert(fparseln(fp, &len, NULL, NULL, 0) == NULL);
	pipe_close(fp);
}

int
main(int argc, char **argv)
{
	test_fparseln(data_parse, 0);
	test_fparseln(data_escape, FPARSELN_UNESCALL);

	return 0;
}
