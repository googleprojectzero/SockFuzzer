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

#include <sys/wait.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>

#include "test-stream.h"

FILE *
pipe_feed(const char *fmt, const void **buf, int buf_nmemb)
{
	FILE *fp;
	int rc;
	int pipefd[2];
	pid_t pid;

	rc = pipe(pipefd);
	assert(rc >= 0);

	pid = fork();
	assert(pid >= 0);

	if (pid == 0) {
		int line;

		/* Child writes data to pipe. */
		rc = close(pipefd[0]);
		assert(rc >= 0);

		fp = fdopen(pipefd[1], "w");
		assert(fp);

		for (line = 0; line < buf_nmemb; line++) {
			rc = fprintf(fp, fmt, buf[line]);
			assert(rc >= 0);
		}

		rc = fclose(fp);
		assert(rc >= 0);

		_exit(0);
	} else {
		/* Parent gets a FILE and reads from it. */
		rc = close(pipefd[1]);
		assert(rc >= 0);

		fp = fdopen(pipefd[0], "r");
		assert(fp);

		return fp;
	}
}

void
pipe_close(FILE *fp)
{
	fclose(fp);
	wait(NULL);
}
