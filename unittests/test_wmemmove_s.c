/*------------------------------------------------------------------
 * test_wmemmove_s
 *
 * September 2014, D Wheeler
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
 *   TC 2: Test for second parameter, dest maximum length (dmax), being sent in as zero
 *   TC 3: Test for second parameter, dest maximum length (dmax), being larger than the maximum allowed size
 *   TC 4: Test for third parameter, source char string, being sent in as NULL
 *   TC 5: Test for last parameter, source length (smax), being sent in as zero
 *   TC 6: Test for last parameter, source length (smax), being larger than the maximum allowed size
 *   TC 7: Test for destination overlaps into source buffer
 *   TC 8: Test for source overlaps into dest buffer
 *
 *   TC 9: Test for just enough room for dest buffer before source & proper copying
 *   TC10: Test source length is too large for destination buffer length by only one
 *   TC11: Test destination buffer is too short for source buffer
 *   TC12: Test proper copy without going over
 *   TC13: Test copying when src buffer overlaps end of destination buffer
 *   TC14: Test copying when src buffer overlaps beginning of destination buffer
 *   TC15: Test moving pointer onto itself
 *   TC16: Test short move between buffers
 *   TC17: Test offset buffer one byte for move between buffers
 *   TC18: Test offset buffer two bytes for move between buffers
 *
 *
 *------------------------------------------------------------------
 */


#include "test_private.h"
#include "safe_mem_lib.h"

#define LEN   ( 256*4 )

static wchar_t  mem1[LEN+2];
static wchar_t  mem2[LEN+2];

extern errno_t wmemmove_s(wchar_t* dest, rsize_t dmax, const wchar_t* src, rsize_t smax);
extern errno_t wmemmove_s(wchar_t* dest, rsize_t dmax, const wchar_t* src, size_t smax);

int test_wmemmove_s (void)
{
    errno_t rc;
    uint32_t i;
    rsize_t len;
    unsigned int testno = 0;


    printf("\nTesting wmemmove_s:\n");
/*--------------------------------------------------*/
/* 1  Test for NULL destination check                  */
    printf("Test #%d:\n", ++testno);

    rc = wmemmove_s(NULL, LEN, mem2, LEN);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

/*--------------------------------------------------*/
/* 2  Test for zero length destination                 */

    printf("Test #%d:\n", ++testno);

    rc = wmemmove_s(mem1, 0, mem2, LEN);
    if (rc != ESZEROL) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

/*--------------------------------------------------*/
/* 3  Test for too large destination size              */
    printf("Test #%d:\n", ++testno);

    rc = wmemmove_s(mem1, RSIZE_MAX_MEM+1, mem2, LEN);
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

/*--------------------------------------------------*/
/* 4  Test for NULL source check                  */
    printf("Test #%d:\n", ++testno);

    rc = wmemmove_s(mem1, LEN, NULL, LEN);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

/*--------------------------------------------------*/
/* 5  Test for zero length source                 */
    printf("Test #%d:\n", ++testno);

    rc = wmemmove_s(mem1, 10, mem2, 0);
    if (rc != ESZEROL) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

/*--------------------------------------------------*/
/* 6  Test for too large source size              */
    printf("Test #%d:\n", ++testno);

    rc = wmemmove_s(mem1, LEN, mem2, RSIZE_MAX_MEM+1);
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

/*--------------------------------------------------*/
/* 7 Test for destination overlaps into source buffer */
    printf("Test #%d:\n", ++testno);

    rc = wmemmove_s(mem1, LEN, &mem1[20], 21);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

/*--------------------------------------------------*/
/* 8 Test for source overlaps into dest buffer */
	printf("Test #%d:\n", ++testno);

	rc = wmemmove_s(&mem1[25], LEN, mem1, 26);
	if (rc != EOK) {
		printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc);
	}


/*--------------------------------------------------*/
/* 9 Test for just enough room for dest buffer before source & proper copying */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<10; i++) { mem1[i] = 33; }
    mem1[10] = 40;
    for (i=11; i<LEN; i++) { mem1[i] = 44; }

    rc = wmemmove_s(mem1, 10, &mem1[10], 10);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    } else {

    	if ( mem1[0] != 40 && mem1[10] != 40) {
            printf("%d - %d m1[0]=%d  m1[10]=%d should be 40  \n",
                 __LINE__, i, mem1[0], mem1[10]);
    	}
		for (i=1; i<10; i++) {
			if (mem1[i] != 44) {
				printf("%d - %d m1=%d  should be 44  \n",
					 __LINE__, i, mem1[i]);
			}
		}
    }

/*--------------------------------------------------*/
/* 10  Test source length is too large for destination buffer length  */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN+1; i++) { mem1[i] = 33; }
    for (i=0; i<LEN; i++) { mem2[i] = 44; }

    len = LEN;
    rc = wmemmove_s(mem1, len, mem2, (len+1) );
    if (rc == EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);

    } else {

		for (i=0; i<len; i++) {
			if (mem1[i] != 0) {
				printf("%d - %d m1=%d  m2=%d  \n",
					 __LINE__, i, mem1[i], mem2[i]);
			}
		}

		if (mem1[i] != 33) {
			printf("%d - %lu m1=%d  m2=%d  \n",
					 __LINE__, len, mem1[len], mem2[len]);
		}

    }

/*--------------------------------------------------*/
/* 11  Test destination buffer is too short for source buffer  */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN+2; i++) { mem1[i] = 33; }
    for (i=0; i<LEN; i++) { mem2[i] = 44; }

    len = LEN/2;
    rc = wmemmove_s(mem1, len, mem2, LEN);
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);

    } else {

		for (i=0; i<len; i++) {
			if (mem1[i] != 0) {
				printf("%d - %d m1=%d  m2=%d  \n",
					 __LINE__, i, mem1[i], mem2[i]);
			}
		}

		if (mem1[len] != 33) {
				printf("%d - %lu m1=%d  m2=%d  \n",
					 __LINE__, len, mem1[len], mem2[len]);
		}
    }

/*--------------------------------------------------*/
/* 12 Test proper copy without going over  */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN+2; i++) { mem1[i] = 33; }
    for (i=0; i<LEN; i++) { mem2[i] = 44; }

    len = LEN;
    rc = wmemmove_s(mem1, len, mem2, len);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);

    } else {

		/* verify mem1 was copied */
		for (i=0; i<len; i++) {
			if (mem1[i] != mem2[i]) {
				printf("%d - %d m1=%d <> m2=%d  \n",
					 __LINE__, i, mem1[i], mem2[i]);
			}
		}

		if (mem1[len] != 33 && mem1[len+1] != 33) {
				printf("%d - %lu m1[len]=%d  m1[len+1]=%d  \n",
					 __LINE__, len, mem1[len], mem1[len+1]);
		}

    }

/*--------------------------------------------------*/
/* 13 Test copying when src buffer overlaps end of destination buffer  */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<10; i++) { mem1[i] = 33; }
    for (i=10; i<LEN; i++) { mem1[i] = 44; }

    len = LEN-10;
    rc = wmemmove_s(mem1, len, &mem1[10], len);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__, rc);
    } else {

		/* verify mem1 was copied properly */
		for (i=0; i<len; i++) {
			if (mem1[i] != 44) {
				printf("%d - %d m1=%d  m2=%d  \n",
					 __LINE__, i, mem1[i], mem2[i]);
			}
		}

    }


/*--------------------------------------------------*/
/* 14 Test copying when src buffer overlaps beginning of destination buffer  */
	printf("Test #%d:\n", ++testno);

	for (i=0; i<LEN+2; i++) { mem1[i] = i; }

	len = LEN-10;
	rc = wmemmove_s(&mem1[10], len, mem1, len);
	if (rc != EOK) {
		printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__, rc);
	} else {

		/* verify mem1 was copied properly */
		for (i=0; i<10; i++) {
			if (mem1[i] != i) {
				printf("%d - %d m1=%d  m2=%d  \n",
					 __LINE__, i, mem1[i], mem2[i]);
			}
		}
		for (i=10; i<LEN; i++) {
			if (mem1[i] != i-10) {
				printf("%d - %d m1=%d  should=%d  \n",
					 __LINE__, i, mem1[i], i-10);
			}
		}

		if ( mem1[LEN] != LEN && mem1[LEN+1] != LEN+1) {
			printf("%d - %d m1[LEN]=%d  mem1[LEN+1]=%d should be 1024 & 1025  \n",
				 __LINE__, i, mem1[LEN], mem1[LEN+1]);
		}

	}

/*--------------------------------------------------*/
/* 15 Test moving pointer onto itself  */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN; i++) { mem1[i] = 55; }

    /* same ptr - no move */
    rc = wmemmove_s(mem1, LEN, mem1, LEN);
    if (rc != EOK) {
        printf("%s %u  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }


/*--------------------------------------------------*/
/* 16  Test short move between buffers */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN; i++) { mem1[i] = 35; }
    for (i=0; i<LEN; i++) { mem2[i] = 55; }

    len = 5;
    rc = wmemmove_s(mem1, len, mem2, len);
    if (rc != EOK) {
        printf("%s %u  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    } else {

		for (i=0; i<len; i++) {
			if (mem1[i] != 55) {
				printf("%d - %d m1=%d\n",
					 __LINE__, i, mem1[i]);
			}
		}

    }

/*--------------------------------------------------*/
/* 17  Test long move between buffers */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN; i++) { mem1[i] = 35; }
    for (i=0; i<LEN; i++) { mem2[i] = 55; }

    rc = wmemmove_s(mem1, LEN, mem2, LEN/2);
    if (rc != EOK) {
        printf("%s %u  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    } else {

		for (i=0; i<LEN/2; i++) {
			if (mem1[i] != 55) {
				printf("%d - %d m1=%d  m2=%d  \n",
					 __LINE__, i, mem1[i], mem2[i]);
			}
		}
    }


/*--------------------------------------------------*/
/* 17  Test offset buffer one byte for move between buffers */
	printf("Test #%d:\n", ++testno);

	for (i=0; i<LEN; i++) { mem1[i] = 35; }
	for (i=0; i<LEN; i++) { mem2[i] = 55; }

	rc = wmemmove_s((wchar_t)(((char *)mem1)+1), LEN, mem2, 10);
	if (rc != EOK) {
		printf("%s %u  Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc);
	} else {

		if ( mem1[0] != 0x00003723 ) {
			printf("%d - %d first char memory incorrect m1=%04x  \n",
				 __LINE__, i, mem1[i]);
		}
		for (i=1; i<10; i++) {
			if (mem1[i] != 0x00003700) {
				printf("%d - %d m1=%04x  \n",
					 __LINE__, i, mem1[i]);
			}
		}
	}


/*--------------------------------------------------*/
/* 18  Test offset buffer two byte for move between buffers */
	printf("Test #%d:\n", ++testno);

	for (i=0; i<LEN; i++) { mem1[i] = 35; }
	for (i=0; i<LEN; i++) { mem2[i] = 55; }

	rc = wmemmove_s((wchar_t)(((char *)mem1)+2), LEN, mem2, 10);
	if (rc != EOK) {
		printf("%s %u  Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc);
	} else {

		if ( mem1[0] != 0x00370023 ) {
			printf("%d - %d first char memory incorrect m1=%04x  \n",
				 __LINE__, i, mem1[i]);
		}
		for (i=1; i<10; i++) {
			if (mem1[i] != 0x00370000) {
				printf("%d - %d m1=%04x  \n",
					 __LINE__, i, mem1[i]);
			}
		}
	}

/*--------------------------------------------------*/
/*--------------------------------------------------*/

    return (0);
}

