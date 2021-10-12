/*
 * Copyright © 2012 Guillem Jover <guillem@hadrons.org>
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

#include <sys/endian.h>

#include <assert.h>
#include <string.h>

int
main(int argc, char *argv[])
{
	unsigned char decstream[] = {
		0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
	};
	unsigned char encstream[sizeof(decstream)];

	assert(be16dec(decstream) == 0x0011);
	assert(le16dec(decstream) == 0x1100);

	assert(be32dec(decstream) == 0x00112233);
	assert(le32dec(decstream) == 0x33221100);

	assert(be64dec(decstream) == 0x0011223344556677);
	assert(le64dec(decstream) == 0x7766554433221100);

	memset(encstream, 0, sizeof(encstream));
	be16enc(encstream, 0x1100);
	assert(memcmp(encstream, decstream, sizeof(uint16_t)));
	le16enc(encstream, 0x0011);
	assert(memcmp(encstream, decstream, sizeof(uint16_t)));

	memset(encstream, 0, sizeof(encstream));
	be32enc(encstream, 0x33221100);
	assert(memcmp(encstream, decstream, sizeof(uint32_t)));
	le32enc(encstream, 0x00112233);
	assert(memcmp(encstream, decstream, sizeof(uint32_t)));

	memset(encstream, 0, sizeof(encstream));
	be64enc(encstream, 0x7766554433221100);
	assert(memcmp(encstream, decstream, sizeof(uint64_t)));
	le64enc(encstream, 0x0011223344556677);
	assert(memcmp(encstream, decstream, sizeof(uint64_t)));

	return 0;
}
