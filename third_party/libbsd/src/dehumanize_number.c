/*
 * Copyright © 2012-2013 Guillem Jover <guillem@hadrons.org>
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

#include <errno.h>
#include <ctype.h>
#include <libutil.h>
#include <stdint.h>
#include <stdlib.h>

int
dehumanize_number(const char *buf, int64_t *num)
{
	uint64_t rval, rmax;
	int sign = +1;
	int rc;

	/* The current expand_number() implementation uses bit shifts, so
	 * we cannot pass negative numbers, preserve the sign and apply it
	 * later. */
	while (isspace(*buf))
		buf++;
	if (*buf == '-') {
		sign = -1;
		buf++;
	}

	rc = expand_number(buf, &rval);
	if (rc < 0)
		return rc;

	/* The sign has been stripped, so rval has the absolute value.
	 * Error out, regardless of the sign, if rval is greater than
	 * abs(INT64_MIN) (== INT64_MAX + 1), or if the sign is positive
	 * and the value has overflown by one (INT64_MAX + 1). */
	rmax = INT64_MAX + 1ULL;
	if (rval > rmax || (rval == rmax && sign == +1)) {
		errno = ERANGE;
		return -1;
	}
	*num = rval * sign;

	return 0;
}
