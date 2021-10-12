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
#include <string.h>
#include <stdio.h>

#define ARRAY_SIZE 100
#define TEST_SIZE 50

struct test_cookie {
	char array[ARRAY_SIZE];
	int index;
};

static int
test_readfn(void *cookie, char *buf, int size)
{
	struct test_cookie *tc = cookie;
	int left_size = sizeof(tc->array) - tc->index;

	if (left_size < 0)
		size = 0;
	else if (left_size < size)
		size = left_size;

	if (size > 0) {
		memcpy(buf, tc->array + tc->index, size);
		tc->index += size;
	}

	return size;
}

static int
test_writefn(void *cookie, const char *buf, int size)
{
	struct test_cookie *tc = cookie;
	int left_size = sizeof(tc->array) - tc->index;

	if (left_size < 0)
		size = 0;
	else if (left_size < size)
		size = left_size;

	if (size > 0) {
		memcpy(tc->array + tc->index, buf, size);
		tc->index += size;
	}

	return size;
}

static off_t
test_seekfn(void *cookie, off_t offset, int whence)
{
	struct test_cookie *tc = cookie;

	switch (whence) {
	case SEEK_SET:
		tc->index = offset;
		break;
	case SEEK_CUR:
		tc->index += offset;
		break;
	case SEEK_END:
		tc->index = sizeof(tc->array) + offset;
		break;
	}

	return tc->index;
}

static int
test_closefn(void *cookie)
{
	struct test_cookie *tc = cookie;

	memset(tc->array, 0x7f, sizeof(tc->array));

	return 0;
}

int
main(int argc, char **argv)
{
	struct test_cookie tc;
	char data[ARRAY_SIZE];
	FILE *fp;
	size_t i;

	/* Test invalid hooks. */
	fp = funopen(&tc, NULL, NULL, NULL, NULL);
	assert(fp == NULL);
	assert(errno == EINVAL);

	/* Test read-only file. */
	tc.index = 0;
	for (i = 0; i < sizeof(tc.array); i++)
		tc.array[i] = i;

	fp = fropen(&tc, test_readfn);
	assert(fp);

	assert(fread(data, 1, TEST_SIZE, fp) == TEST_SIZE);
	assert(memcmp(tc.array, data, TEST_SIZE) == 0);

	assert(fwrite(data, 1, TEST_SIZE, fp) == 0);

	assert(fclose(fp) == 0);

	/* Test write-only file. */
	memset(&tc, 0, sizeof(tc));

	fp = fwopen(&tc, test_writefn);
	assert(fp);

	setvbuf(fp, NULL, _IONBF, 0);

	assert(fwrite(data, 1, TEST_SIZE, fp) == TEST_SIZE);
	assert(memcmp(tc.array, data, TEST_SIZE) == 0);

	assert(fread(data, 1, TEST_SIZE, fp) == 0);

	assert(fclose(fp) == 0);

	/* Test seekable file. */
	memset(&tc, 0, sizeof(tc));

	fp = funopen(&tc, test_readfn, test_writefn, test_seekfn, NULL);
	assert(fp);

	setvbuf(fp, NULL, _IONBF, 0);

	assert(fwrite(data, 1, TEST_SIZE, fp) == TEST_SIZE);
	assert(fseek(fp, 0L, SEEK_SET) == 0);
	assert(fwrite(data, 1, ARRAY_SIZE, fp) == ARRAY_SIZE);
	assert(memcmp(tc.array, data, ARRAY_SIZE) == 0);

	assert(fread(data, 1, TEST_SIZE, fp) == 0);

	assert(fclose(fp) == 0);

	/* Test close hook. */
	memset(&tc, 0, sizeof(tc));

	fp = funopen(&tc, test_readfn, test_writefn, NULL, test_closefn);
	assert(fclose(fp) == 0);

	for (i = 0; i < sizeof(tc.array); i++)
		assert(tc.array[i] == 0x7f);

	return 0;
}
