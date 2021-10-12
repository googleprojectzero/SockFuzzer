/*-
 * Copyright (c) 2001 FreeBSD Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * These routines are for converting time_t to fixed-bit representations
 * for use in protocols or storage.  When converting time to a larger
 * representation of time_t these routines are expected to assume temporal
 * locality and use the 50-year rule to properly set the msb bits.  XXX
 *
 */

#include <sys/cdefs.h>
#include <sys/types.h>
#include <timeconv.h>

/*
 * Convert a 32 bit representation of time_t into time_t.  XXX needs to
 * implement the 50-year rule to handle post-2038 conversions.
 */
time_t
_time32_to_time(int32_t t32)
{
    return((time_t)t32);
}

/*
 * Convert time_t to a 32 bit representation.  If time_t is 64 bits we can
 * simply chop it down.   The resulting 32 bit representation can be
 * converted back to a temporally local 64 bit time_t using time32_to_time.
 */
int32_t
_time_to_time32(time_t t)
{
    return((int32_t)t);
}

/*
 * Convert a 64 bit representation of time_t into time_t.  If time_t is
 * represented as 32 bits we can simply chop it and not support times
 * past 2038.
 */
time_t
_time64_to_time(int64_t t64)
{
    return((time_t)t64);
}

/*
 * Convert time_t to a 64 bit representation.  If time_t is represented
 * as 32 bits we simply sign-extend and do not support times past 2038.
 */
int64_t
_time_to_time64(time_t t)
{
    return((int64_t)t);
}

/*
 * Convert to/from 'long'.  Depending on the sizeof(long) this may or
 * may not require using the 50-year rule.
 */
long
_time_to_long(time_t t)
{
    if (sizeof(long) == sizeof(int64_t))
	return(_time_to_time64(t));
    return((long)t);
}

time_t
_long_to_time(long tlong)
{
    if (sizeof(long) == sizeof(int32_t))
	return(_time32_to_time(tlong));
    return((time_t)tlong);
}

/*
 * Convert to/from 'int'.  Depending on the sizeof(int) this may or
 * may not require using the 50-year rule.
 */
int
_time_to_int(time_t t)
{
    if (sizeof(int) == sizeof(int64_t))
	return(_time_to_time64(t));
    return((int)t);
}

time_t
_int_to_time(int tint)
{
    if (sizeof(int) == sizeof(int32_t))
	return(_time32_to_time(tint));
    return((time_t)tint);
}
