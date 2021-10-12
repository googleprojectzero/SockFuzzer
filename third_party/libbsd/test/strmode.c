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

#include <sys/stat.h>
#include <assert.h>
#include <string.h>

int
main(int argc, char **argv)
{
	char mode_str[12];

	strmode(0, mode_str);
	assert(strcmp(mode_str, "?--------- ") == 0);

	strmode(0777, mode_str);
	assert(strcmp(mode_str, "?rwxrwxrwx ") == 0);

	strmode(0777 | S_IFREG, mode_str);
	assert(strcmp(mode_str, "-rwxrwxrwx ") == 0);

	strmode(0777 | S_IFREG | S_ISUID | S_ISGID | S_ISVTX, mode_str);
	assert(strcmp(mode_str, "-rwsrwsrwt ") == 0);

	strmode(0666 | S_IFREG | S_ISUID | S_ISGID | S_ISVTX, mode_str);
	assert(strcmp(mode_str, "-rwSrwSrwT ") == 0);

	strmode(0777 | S_IFLNK, mode_str);
	assert(strcmp(mode_str, "lrwxrwxrwx ") == 0);

	strmode(0777 | S_IFCHR, mode_str);
	assert(strcmp(mode_str, "crwxrwxrwx ") == 0);

	strmode(0777 | S_IFBLK, mode_str);
	assert(strcmp(mode_str, "brwxrwxrwx ") == 0);

	strmode(0777 | S_IFDIR, mode_str);
	assert(strcmp(mode_str, "drwxrwxrwx ") == 0);

	strmode(0777 | S_IFIFO, mode_str);
	assert(strcmp(mode_str, "prwxrwxrwx ") == 0);

	strmode(0777 | S_IFSOCK, mode_str);
	assert(strcmp(mode_str, "srwxrwxrwx ") == 0);

	return 0;
}
