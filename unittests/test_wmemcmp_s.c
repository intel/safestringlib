/*------------------------------------------------------------------
 * test_wcsncat_s.c
 *
 * August 2014, D Wheeler
 *
 * Copyright (c) 2014 by Intel Corp
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *------------------------------------------------------------------
 *------------------------------------------------------------------
 *   TEST COVERAGE NOTES
 *
 *   The following notes describe the purpose of the test cases in
 *   order to ensure full coverage of all return paths in the code to
 *   be tested, as well as test for security concerns in the target.
 *   The test methodology is to perfrom branch-coverage testing to ensure
 *   all exit paths from the code have been tested. Additional tests are added to
 *   perform some corner case validation of certain more complex branches
 *   to verify no side-effects or missing corners are introduced in the code.
 *
 *   BASIC PARAMETER VALIDATION
 *   TC 1: Test for first parameter, destination char string, being sent in as NULL
 *   TC 2: Test for third parameter, source char string, being sent in as NULL
 *   TC 3: Test for last parameter, indicator, being sent in as NULL
 *   TC 4: Test for second parameter, dest maximum length (dmax), being sent in as zero
 *   TC 5: Test for last parameter, source maximum (smax), being sent in as zero
 *   TC 6: Test for second parameter, dest maximum length (dmax), being larger than the maximum allowed size
 *   TC 7: Test for last parameter, source length (smax), being larger than the maximum allowed size
 *
 *
 *   TC 8: Test for single character equality comparison - proper result
 *   TC 9: Test for two character equality comparison - proper result
 *   TC10: Test for long string character equality comparison  - proper result
 *   TC11: Test long string many differences - s1 < s2 at index 10
 *   TC12: Test long string many differences - s1 < s2 at index 10
 *   TC13: Test long string - single char greater than difference at index 1
 *   TC14: Test long string - single char less than difference at index 1
 *   TC15: Test long string - single char greater than difference at end of string
 *   TC16: Test long string - single char less than difference at end of string
 *
 *------------------------------------------------------------------
 */


#include "test_private.h"
#include "safe_mem_lib.h"

#define LEN   ( 128 )

extern errno_t wmemcmp_s (const wchar_t *dest, rsize_t dmax,
                          const wchar_t *src,  rsize_t smax, int *diff);

int test_wmemcmp_s()
{
    errno_t rc;
    uint32_t len;
    int32_t  ind;
    uint32_t i;

    wchar_t  mem1[LEN];
    wchar_t  mem2[LEN];
    unsigned int testno = 0;


    printf("\nTesting wmemcmp_s:\n");
/*--------------------------------------------------*/
/* 1: Test for first parameter, destination char string, being sent in as NULL */

    printf("Test #%d:\n", ++testno);
    rc = wmemcmp_s(NULL, LEN, mem2, LEN, &ind);
    if (rc != ESNULLP) {
        printf("%s %u  Ind=%d  Error rc=%u \n",
                     __FUNCTION__, __LINE__, ind, rc );
    }

/*--------------------------------------------------*/
/* 2: Test for third parameter, source char string, being sent in as NULL */

    printf("Test #%d:\n", ++testno);
    rc = wmemcmp_s(mem1, LEN, NULL, LEN, &ind);
    if (rc != ESNULLP) {
        printf("%s %u  Ind=%d  Error rc=%u \n",
                     __FUNCTION__, __LINE__, ind, rc );
    }

/*--------------------------------------------------*/
/* 3: Test for last parameter, indicator, being sent in as NULL */

    printf("Test #%d:\n", ++testno);
    rc = wmemcmp_s(mem1, LEN, mem2, LEN, NULL);
    if (rc != ESNULLP) {
        printf("%s %u  Ind=%d  Error rc=%u \n",
                     __FUNCTION__, __LINE__, ind, rc );
    }

/*--------------------------------------------------*/
/* 4: Test for second parameter, dest maximum length (dmax), being sent in as zero */

    printf("Test #%d:\n", ++testno);
    rc = wmemcmp_s(mem1, 0, mem2, LEN, &ind);
    if (rc != ESZEROL) {
        printf("%s %u  Ind=%d  Error rc=%u \n",
                     __FUNCTION__, __LINE__, ind, rc );
    }

/*--------------------------------------------------*/
/* 5: Test for last parameter, source maximum (smax), being sent in as zero */

    printf("Test #%d:\n", ++testno);
    rc = wmemcmp_s(mem1, LEN, mem2, 0, &ind);
    if (rc != ESZEROL) {
        printf("%s %u  Ind=%d  Error rc=%u \n",
                     __FUNCTION__, __LINE__, ind, rc );
    }

/*--------------------------------------------------*/
/* 6: Test for second parameter, dest maximum length (dmax), being larger than the maximum allowed size */

    printf("Test #%d:\n", ++testno);
    rc = wmemcmp_s(mem1, RSIZE_MAX_MEM+1, mem2, LEN, &ind);
    if (rc != ESLEMAX) {
        printf("%s %u  Ind=%d  Error rc=%u \n",
                     __FUNCTION__, __LINE__, ind, rc );
    }

/*--------------------------------------------------*/
/* 7: Test for last parameter, source length (smax), being larger than the maximum allowed size */

    printf("Test #%d:\n", ++testno);
    rc = wmemcmp_s(mem1, LEN, mem2, RSIZE_MAX_MEM+1, &ind);
    if (rc != ESLEMAX) {
        printf("%s %u  Ind=%d  Error rc=%u \n",
                     __FUNCTION__, __LINE__, ind, rc );
    }

/*--------------------------------------------------*/
/* 8: Test for single character equality comparison    */

    printf("Test #%d:\n", ++testno);
    for (i=0; i<LEN; i++) { mem1[i] = i; }
    for (i=0; i<LEN; i++) { mem2[i] = i; }

    len = 1;
    rc = wmemcmp_s(mem1, len, mem2, len, &ind);
    if (rc != EOK) {
        printf("%s %u  Ind=%d  Error rc=%u \n",
                     __FUNCTION__, __LINE__, ind, rc );
    }

    if (ind != 0) {
        printf("%s %u  Ind=%d  rc=%u \n",
                     __FUNCTION__, __LINE__,  ind, rc );
    }

    ind = memcmp(mem1, mem2, len*4);
    if (ind != 0) {
        printf("%s %u  Ind=%d  rc=%u \n",
                     __FUNCTION__, __LINE__,  ind, rc );
    }

/*--------------------------------------------------*/
/* 9: Test for two character equality comparison  */

    printf("Test #%d:\n", ++testno);
    for (i=0; i<LEN; i++) { mem1[i] = i; }
    for (i=0; i<LEN; i++) { mem2[i] = i; }

    len = 2;
    rc = wmemcmp_s(mem1, len, mem2, len, &ind);
    if (rc != EOK) {
        printf("%s %u  Ind=%d  Error rc=%u \n",
                     __FUNCTION__, __LINE__, ind, rc );
    }

    if (ind != 0) {
        printf("%s %u  Ind=%d  rc=%u \n",
                     __FUNCTION__, __LINE__,  ind, rc );
    }

    ind = memcmp(mem1, mem2, len*4);
    if (ind != 0) {
        printf("%s %u  Ind=%d  rc=%u \n",
                     __FUNCTION__, __LINE__,  ind, rc );
    }

/*--------------------------------------------------*/
/* 10: Test for long string character equality comparison   */

    printf("Test #%d:\n", ++testno);
    for (i=0; i<LEN; i++) { mem1[i] = i; }
    for (i=0; i<LEN; i++) { mem2[i] = i; }

    rc = wmemcmp_s(mem1, LEN, mem2, LEN, &ind);
    if (rc != EOK) {
        printf("%s %u  Ind=%d  Error rc=%u \n",
                     __FUNCTION__, __LINE__, ind, rc );
    }

    if (ind != 0) {
        printf("%s %u  Ind=%d  rc=%u \n",
                     __FUNCTION__, __LINE__,  ind, rc );
    }

    ind = memcmp(mem1, mem2, LEN*4);
    if (ind != 0) {
        printf("%s %u  Ind=%d  rc=%u \n",
                     __FUNCTION__, __LINE__,  ind, rc );
    }

/*--------------------------------------------------*/
/* 11: Test short string - s1 > s2 at index 10  */

    printf("Test #%d:\n", ++testno);
    for (i=0; i<LEN; i++) { mem1[i] = i; }
    for (i=0; i<LEN; i++) { mem2[i] = i; }

    for (i=10; i<LEN-10; i++) { mem2[i] = 5; }

    rc = wmemcmp_s(mem1, LEN, mem2, LEN, &ind);
    if (rc != EOK) {
        printf("%s %u  Ind=%d  Error rc=%u \n",
                     __FUNCTION__, __LINE__, ind, rc );
    }

    if (ind <= 0) {
        printf("%s %u  Ind=%d  rc=%u \n",
                     __FUNCTION__, __LINE__,  ind, rc );
    }


/*--------------------------------------------------*/
/* 12: Test short string - s1 < s2 at index 10  */

	printf("Test #%d:\n", ++testno);
	for (i=0; i<LEN; i++) { mem1[i] = i; }
	for (i=0; i<LEN; i++) { mem2[i] = i; }

	for (i=10; i<LEN-10; i++) { mem2[i] = 5; }

	rc = wmemcmp_s(mem2, LEN, mem1, LEN, &ind);
	if (rc != EOK) {
		printf("%s %u  Ind=%d  Error rc=%u \n",
					 __FUNCTION__, __LINE__, ind, rc );
	}

	if (ind >= 0) {
		printf("%s %u  Ind=%d  rc=%u \n",
					 __FUNCTION__, __LINE__,  ind, rc );
	}

/*--------------------------------------------------*/
/* 13: Test long string - single char greater than difference at index 1  */

	printf("Test #%d:\n", ++testno);
	for (i=0; i<LEN; i++) { mem1[i] = i; }
	for (i=0; i<LEN; i++) { mem2[i] = i; }

	mem2[1] += 1;

	rc = wmemcmp_s(mem1, LEN, mem2, LEN, &ind);
	if (rc != EOK) {
		printf("%s %u  Ind=%d  Error rc=%u \n",
					 __FUNCTION__, __LINE__, ind, rc );
	}

	if (ind >= 0) {
		printf("%s %u  Ind=%d  rc=%u \n",
					 __FUNCTION__, __LINE__,  ind, rc );
	}

/*--------------------------------------------------*/
/* 14: Test long string - single char less than difference at index 1  */

	printf("Test #%d:\n", ++testno);
	for (i=0; i<LEN; i++) { mem1[i] = i; }
	for (i=0; i<LEN; i++) { mem2[i] = i; }

	mem2[1] -= 1;

	rc = wmemcmp_s(mem1, LEN, mem2, LEN, &ind);
	if (rc != EOK) {
		printf("%s %u  Ind=%d  Error rc=%u \n",
					 __FUNCTION__, __LINE__, ind, rc );
	}

	if (ind <= 0) {
		printf("%s %u  Ind=%d  rc=%u \n",
					 __FUNCTION__, __LINE__,  ind, rc );
	}

/*--------------------------------------------------*/
/* 15: Test long string - single char greater than difference at end of string  */

	printf("Test #%d:\n", ++testno);
	for (i=0; i<LEN; i++) { mem1[i] = i; }
	for (i=0; i<LEN; i++) { mem2[i] = i; }

	mem2[LEN-1] += 1;

	rc = wmemcmp_s(mem1, LEN, mem2, LEN, &ind);
	if (rc != EOK) {
		printf("%s %u  Ind=%d  Error rc=%u \n",
					 __FUNCTION__, __LINE__, ind, rc );
	}

	if (ind >= 0) {
		printf("%s %u  Ind=%d  rc=%u \n",
					 __FUNCTION__, __LINE__,  ind, rc );
	}

/*--------------------------------------------------*/
/* 16: Test long string - single char less than difference at end of string  */

	printf("Test #%d:\n", ++testno);
	for (i=0; i<LEN; i++) { mem1[i] = i; }
	for (i=0; i<LEN; i++) { mem2[i] = i; }

	mem2[LEN-1] -= 1;

	rc = wmemcmp_s(mem1, LEN, mem2, LEN, &ind);
	if (rc != EOK) {
		printf("%s %u  Ind=%d  Error rc=%u \n",
					 __FUNCTION__, __LINE__, ind, rc );
	}

	if (ind <= 0) {
		printf("%s %u  Ind=%d  rc=%u \n",
					 __FUNCTION__, __LINE__,  ind, rc );
	}

/*--------------------------------------------------*/
/*--------------------------------------------------*/

    return (0);
}
