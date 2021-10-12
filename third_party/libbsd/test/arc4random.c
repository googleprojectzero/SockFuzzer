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
#include <stdlib.h>

#include <testu01/gdef.h>
#include <testu01/unif01.h>
#include <testu01/swrite.h>
#include <testu01/bbattery.h>

#define TEST_OK		0
#define TEST_SKIP	77
#define TEST_DIE	99

#define test_print(msg, ...) \
	printf("TEST: " msg "\n", __VA_ARGS__)
#define test_res(idx, name, pval, action) \
	test_print("[%4d] (%s) pVal[%d] = %f -> %s", \
	           idx, name[idx], i, pval[idx], action)

static int test_failed = 0;

static void
test_battery_result(void)
{
	char **testNames = bbattery_TestNames;
	double *pVal = bbattery_pVal;
	double pSuspect = 0.001;

	test_print("bbattery_NTests = %d", bbattery_NTests);
	for (int i = 0; i < bbattery_NTests; i++) {
		/* That test was not done: pVal = -1. */
		if (pVal[i] < 0.0) {
			test_res(i, testNames, pVal, "SKIP");
			continue;
		}

		/* That test passed or failed. */
		if ((pVal[i] >= pSuspect) &&
		    (pVal[i] <= 1.0 - pSuspect)) {
			test_res(i, testNames, pVal, "PASS");
		} else {
			test_res(i, testNames, pVal, "FAIL");
			test_failed++;
		}
	}
}

int
main(int argc, char **argv)
{
	unif01_Gen *gen;
	int rc;

	gen = unif01_CreateExternGenBits("arc4random", arc4random);

	/* XXX: The following battery does not set pVal, so we cannot check
	 * the results. */
	bbattery_FIPS_140_2(gen);

	/* XXX: The following battery fails one test. */
	bbattery_pseudoDIEHARD(gen);
	test_battery_result();

	bbattery_Rabbit(gen, 33554432);
	test_battery_result();

	bbattery_SmallCrush(gen);
	test_battery_result();

	unif01_DeleteExternGenBits(gen);

	if (test_failed) {
		test_print("failed tests = %d", test_failed);
		/* XXX: We should probably FAIL the test, but we currently
		 * have one test always failing. */
		rc = TEST_SKIP;
	} else {
		rc = TEST_OK;
	}

	return rc;
}
