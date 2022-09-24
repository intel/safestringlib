/*------------------------------------------------------------------
 * test_wwmemcpy_s
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
 *
 *
 *
 *------------------------------------------------------------------
 */


#include "test_private.h"
#include "safe_mem_lib.h"

#define LEN   ( 256*4 )

static wchar_t  mem1[LEN+2];
static wchar_t  mem2[LEN+2];

extern errno_t wmemcpy_s(wchar_t* dest, rsize_t dmax, const wchar_t* src, rsize_t smax);

int test_wmemcpy_s (void)
{
    errno_t rc;
    int errs = 0;
    uint32_t i;
    rsize_t len;
    unsigned int testno = 0;


    printf("\nTesting wmemcpy_s:\n");
/*--------------------------------------------------*/
/* 1  Test for NULL destination check                  */
    printf("Test #%d:\n", ++testno);

    rc = wmemcpy_s(NULL, LEN, mem2, LEN);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

/*--------------------------------------------------*/
/* 2  Test for zero length destination                 */

    printf("Test #%d:\n", ++testno);

    rc = wmemcpy_s(mem1, 0, mem2, LEN);
    if (rc != ESZEROL) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

/*--------------------------------------------------*/
/* 3  Test for too large destination size              */
    printf("Test #%d:\n", ++testno);

    rc = wmemcpy_s(mem1, RSIZE_MAX_MEM+1, mem2, LEN);
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

/*--------------------------------------------------*/
/* 4  Test for NULL source check                  */
    printf("Test #%d:\n", ++testno);

    rc = wmemcpy_s(mem1, LEN, NULL, LEN);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

/*--------------------------------------------------*/
/* 5  Test for zero length source                 */
    printf("Test #%d:\n", ++testno);

    rc = wmemcpy_s(mem1, 10, mem2, 0);
    if (rc != ESZEROL) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

/*--------------------------------------------------*/
/* 6  Test for too large source size              */
    printf("Test #%d:\n", ++testno);

    rc = wmemcpy_s(mem1, LEN, mem2, RSIZE_MAX_MEM+1);
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

/*--------------------------------------------------*/
/* 7 Test for destination overlaps into source buffer */
    printf("Test #%d:\n", ++testno);

    rc = wmemcpy_s(mem1, LEN, &mem1[20], 21);
    if (rc != ESOVRLP) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

/*--------------------------------------------------*/
/* 8 Test for source overlaps into dest buffer */
	printf("Test #%d:\n", ++testno);

	rc = wmemcpy_s(&mem1[25], LEN, mem1, 26);
	if (rc != ESOVRLP) {
		printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc);
	    ++errs;
	}


/*--------------------------------------------------*/
/* 9 Test for just enough room for dest buffer before source & proper copying */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<10; i++) { mem1[i] = 33; }
    mem1[10] = 40;
    for (i=11; i<LEN; i++) { mem1[i] = 44; }

    rc = wmemcpy_s(mem1, 10, &mem1[10], 10);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
        ++errs;
    } else {

    	if ( mem1[0] != 40 && mem1[10] != 40) {
            printf("%d - %d m1[0]=%d  m1[10]=%d should be 40  \n",
                 __LINE__, i, mem1[0], mem1[10]);
	    ++errs;
    	}
		for (i=1; i<10; i++) {
			if (mem1[i] != 44) {
				printf("%d - %d m1=%d  should be 44  \n",
					 __LINE__, i, mem1[i]);
			    ++errs;
			}
		}
    }

/*--------------------------------------------------*/
/* 10    */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN+1; i++) { mem1[i] = 33; }
    for (i=0; i<LEN; i++) { mem2[i] = 44; }

    len = LEN;
    rc = wmemcpy_s(mem1, len, mem2, (len+1) );
    if (rc == EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
        ++errs;
    } else {

    for (i=0; i<len; i++) {
        if (mem1[i] != 0) {
            printf("%d - %d m1=%d  m2=%d  \n",
                 __LINE__, i, mem1[i], mem2[i]);
            ++errs;
        }
    }

    if (mem1[i] != 33) {
        printf("%d - %lu m1=%d  m2=%d  \n",
                 __LINE__, len, mem1[len], mem2[len]);
        ++errs;
    }

    }

/*--------------------------------------------------*/
/* 11    */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN+2; i++) { mem1[i] = 33; }
    for (i=0; i<LEN; i++) { mem2[i] = 44; }

    len = LEN/2;
    rc = wmemcpy_s(mem1, len, mem2, LEN);
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
        ++errs;
    } else {

    for (i=0; i<len; i++) {
        if (mem1[i] != 0) {
            printf("%d - %d m1=%d  m2=%d  \n",
                 __LINE__, i, mem1[i], mem2[i]);
            ++errs;
        }
    }

    if (mem1[len] != 33) {
            printf("%d - %lu m1=%d  m2=%d  \n",
                 __LINE__, len, mem1[len], mem2[len]);
            ++errs;
    }
    }

/*--------------------------------------------------*/
/* 12   */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN+2; i++) { mem1[i] = 33; }
    for (i=0; i<LEN; i++) { mem2[i] = 44; }

    len = LEN;
    rc = wmemcpy_s(mem1, len, mem2, 0);
    if (rc != ESZEROL) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
        ++errs;
    } else {

    /* verify mem1 was zeroed */
    for (i=0; i<len; i++) {
        if (mem1[i] != 0) {
            printf("%d - %d m1=%d  m2=%d  \n",
                 __LINE__, i, mem1[i], mem2[i]);
            ++errs;
        }
    }

    if (mem1[len] != 33) {
            printf("%d - %lu m1=%d  m2=%d  \n",
                 __LINE__, len, mem1[len], mem2[len]);
            ++errs;
    }

    }

/*--------------------------------------------------*/
/* 13   */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN; i++) { mem1[i] = 33; }
    for (i=0; i<LEN; i++) { mem2[i] = 44; }

    len = LEN;
    rc = wmemcpy_s(mem1, len, mem2, RSIZE_MAX_MEM+1);
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    } else {

		/* verify mem1 was zeroed */
		for (i=0; i<len; i++) {
			if (mem1[i] != 0) {
				printf("%d - %d m1=%d  m2=%d  \n",
					 __LINE__, i, mem1[i], mem2[i]);
				++errs;
			}
		}

		if (mem1[len] == 0) {
				printf("%d - %d m1=%d  m2=%d  \n",
					 __LINE__, i, mem1[i], mem2[i]);
				++errs;
		}

    }

/*--------------------------------------------------*/
/* 14   */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN; i++) { mem1[i] = 55; }

    /* same ptr - no move */
    rc = wmemcpy_s(mem1, LEN, mem1, LEN);
    if (rc != EOK) {
        printf("%s %u  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

/*--------------------------------------------------*/
/* 15   */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN; i++) { mem1[i] = 55; }
    for (i=0; i<LEN; i++) { mem2[i] = 65; }

    /* overlap */
    len = 100;
    rc = wmemcpy_s(&mem1[0], len, &mem1[10], len);
    if (rc != ESOVRLP) {
        printf("%s %u  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
        ++errs;
    } else {

    for (i=0; i<len; i++) {
        if (mem1[i] != 0) {
            printf("%d - %d m1=%d  m2=%d  \n",
                 __LINE__, i, mem1[i], mem2[i]);
            ++errs;
        }
    }

    if (mem1[len] == 0) {
            printf("%d - %d m1=%d  m2=%d  \n",
                 __LINE__, i, mem1[i], mem2[i]);
            ++errs;
    }

    }

/*--------------------------------------------------*/
/* 16  */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN; i++) { mem1[i] = 55; }
    for (i=0; i<LEN; i++) { mem2[i] = 65; }

    /* overlap */
    len = 100;
    rc = wmemcpy_s(&mem1[10], len, &mem1[0], len);
    if (rc != ESOVRLP) {
        printf("%s %u  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
        ++errs;
    } else {

		for (i=10; i<len+10; i++) {
			if (mem1[i] != 0) {
				printf("%d - %d m1=%d  m2=%d  \n",
					 __LINE__, i, mem1[i], mem2[i]);
				++errs;
			}
		}

    }

/*--------------------------------------------------*/
/* 17   */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN; i++) { mem1[i] = 35; }
    for (i=0; i<LEN; i++) { mem2[i] = 55; }

    len = 5;
    rc = wmemcpy_s(mem1, len, mem2, len);
    if (rc != EOK) {
        printf("%s %u  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
        ++errs;
    } else {

    for (i=0; i<len; i++) {
        if (mem1[i] != 55) {
            printf("%d - %d m1=%d\n",
                 __LINE__, i, mem1[i]);
            ++errs;
        }
    }

    }

/*--------------------------------------------------*/
/* 18   */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN; i++) { mem1[i] = 35; }
    for (i=0; i<LEN; i++) { mem2[i] = 55; }

    rc = wmemcpy_s(mem1, LEN, mem2, LEN/2);
    if (rc != EOK) {
        printf("%s %u  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
        ++errs;
    } else {

    for (i=0; i<LEN/2; i++) {
        if (mem1[i] != 55) {
            printf("%d - %d m1=%d  m2=%d  \n",
                 __LINE__, i, mem1[i], mem2[i]);
            ++errs;
        }
    }
    }

/*--------------------------------------------------*/
/*--------------------------------------------------*/

    return errs;
}

