/*
 * Copyright © 2013-2015, 2020 Guillem Jover <guillem@hadrons.org>
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
#include <locale.h>
#include <wchar.h>

#include "test-stream.h"

#define skip(msg) \
	do { \
		printf("skip: %s\n", (msg)); \
		return; \
	} while (0)

#define DATA_LINES 3

static const char *data_ascii[] = {
	"this represents an ascii sequence of lines to test the\n",
	"fgetln() family of functions\n",
	"last line without an ending newline",
};
static const wchar_t *data_wide[] = {
	L"this represénts an utf-8 seqüence of lînes to test the\n",
	L"«fgetln()» family of functions § but with an extremely long "
	 "line to test that the reallocation logic works fine, and that "
	 "the strings end up being equal…\n",
	L"last line ☭ without an ‽ ending newline ♥",
};

#define FILE_COUNT 32

#define LINE_COUNT 2
#define LINE_LEN 2

struct file {
	FILE *fp;
	void *line_alloc;
	const void **lines;

	const void *got_buf;
	int got_len;
};

static void
test_fgetln_single(void)
{
	FILE *fp;
	size_t len;
	int i;

	fp = pipe_feed("%s", (const void **)data_ascii, DATA_LINES);
	for (i = 0; i < DATA_LINES; i++) {
		char *str = fgetln(fp, &len);

		assert(str);
		assert(memcmp(str, data_ascii[i], len) == 0);
	}
	assert(fgetln(fp, &len) == NULL);
	pipe_close(fp);
}

static void
test_fgetln_multi(void)
{
	struct file files[FILE_COUNT];
	int i, l;

	for (i = 0; i < FILE_COUNT; i++) {
		char *str;

		str = strdup("A\n");
		str[0] += i;

		files[i].line_alloc = str;
		files[i].lines = reallocarray(NULL, LINE_COUNT, sizeof(char *));
		files[i].lines[0] = str;
		files[i].lines[1] = str;
		files[i].fp = pipe_feed("%s", files[i].lines, LINE_COUNT);
	}

	for (l = 0; l < LINE_COUNT; l++) {
		for (i = 0; i < FILE_COUNT; i++) {
			size_t len;
			char *str;

			str = fgetln(files[i].fp, &len);

			assert(str);
			assert(len == LINE_LEN);

			files[i].got_len = len;
			files[i].got_buf = str;
		}

		for (i = 0; i < FILE_COUNT; i++) {
			assert(memcmp(files[i].lines[l], files[i].got_buf,
			              files[i].got_len) == 0);
		}
	}

	for (i = 0; i < FILE_COUNT; i++) {
		free(files[i].line_alloc);
		free(files[i].lines);
		pipe_close(files[i].fp);
	}
}

static void
test_fgetwln_single(void)
{
	FILE *fp;
	size_t len;
	int i;

	fp = pipe_feed("%ls", (const void **)data_wide, DATA_LINES);
	for (i = 0; i < DATA_LINES; i++) {
		wchar_t *wstr;

		wstr = fgetwln(fp, &len);
		assert(wstr);

		assert(wmemcmp(data_wide[i], wstr, len) == 0);
	}
	assert(fgetwln(fp, &len) == NULL);
	pipe_close(fp);
}

static void
test_fgetwln_multi(void)
{
	struct file files[FILE_COUNT];
	int i, l;

	for (i = 0; i < FILE_COUNT; i++) {
		wchar_t *wstr;

		wstr = wcsdup(L"A\n");
		wstr[0] += i;

		files[i].line_alloc = wstr;
		files[i].lines = reallocarray(NULL, LINE_COUNT, sizeof(char *));
		files[i].lines[0] = wstr;
		files[i].lines[1] = wstr;
		files[i].fp = pipe_feed("%ls", files[i].lines, LINE_COUNT);
	}

	for (l = 0; l < LINE_COUNT; l++) {
		for (i = 0; i < FILE_COUNT; i++) {
			size_t len;
			wchar_t *wstr;

			wstr = fgetwln(files[i].fp, &len);

			assert(wstr);
			assert(len == LINE_LEN);

			files[i].got_len = len;
			files[i].got_buf = wstr;
		}

		for (i = 0; i < FILE_COUNT; i++) {
			assert(wmemcmp(files[i].lines[l], files[i].got_buf,
			               files[i].got_len) == 0);
		}
	}

	for (i = 0; i < FILE_COUNT; i++) {
		free(files[i].line_alloc);
		free(files[i].lines);
		pipe_close(files[i].fp);
	}
}

static void
test_fgetwln(void)
{
	if (setlocale(LC_ALL, "C.UTF-8") == NULL &&
	    setlocale(LC_ALL, "en_US.UTF-8") == NULL)
		skip("no default UTF-8 locale found");

	test_fgetwln_single();
	test_fgetwln_multi();
}

int
main(int argc, char **argv)
{
	test_fgetln_single();
	test_fgetln_multi();
	test_fgetwln();

	return 0;
}
