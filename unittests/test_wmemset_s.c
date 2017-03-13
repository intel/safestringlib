/*------------------------------------------------------------------
 * test_wmemset_s
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
 *   TC 2: Test for third parameter, dest maximum length (dmax), being sent in as zero
 *   TC 3: Test for third parameter, dest maximum length (dmax), being larger than the maximum allowed size
 *
 *   TC 4: Test setting a single character
 *   TC 5: Test setting two characters
 *   TC 6: Test setting multiple characters (12)
 *   TC 7: Test setting multiple characters (31)
 *   TC 8: Test setting multiple characters (133)
 *
 *
 *------------------------------------------------------------------
 */


#include "test_private.h"
#include "safe_mem_lib.h"

#define LEN   ( 256 )

static wchar_t mem1[LEN];

extern errno_t wmemset_s (wchar_t *dest, wchar_t value, rsize_t len);

int test_wmemset_s (void)
{
    errno_t rc;
    uint32_t len;
    uint32_t i;
    unsigned int testno = 0;
    wchar_t value;

    printf("\nTesting wmemset_s:\n");
/*--------------------------------------------------*/
/* 1: Test for first parameter, destination char string, being sent in as NULL */
    printf("Test #%d:\n", ++testno);

    value = 34;

    rc = wmemset_s(NULL, value, LEN);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__, rc);
    }

/*--------------------------------------------------*/
/* 2: Test for third parameter, dest maximum length (dmax), being sent in as zero */
    printf("Test #%d:\n", ++testno);
    value = 34;

    rc = wmemset_s(mem1, value, 0);
    if (rc != ESZEROL) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__, rc);
    }

/*--------------------------------------------------*/
/* 3: Test for second parameter, dest maximum length (dmax), being larger than the maximum allowed size */
    printf("Test #%d:\n", ++testno);

    value = 34;

    rc = wmemset_s(mem1, value, (RSIZE_MAX_MEM+1));
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__, rc);
    }

/*--------------------------------------------------*/
/* 4: Test setting a single character */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN; i++) { mem1[i] = 99; }

    len = 1;
    value = 34;

    rc = wmemset_s(mem1, value, len);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if ( mem1[0] != value ) {
        printf("%d - m1[0]=%d \n",
             __LINE__, mem1[0]);
    }
    for (i=1; i<LEN; i++) {
        if (mem1[i] != 99) {
            printf("%d - %d m1=%d \n",
                 __LINE__, i, mem1[i]);
        }
    }

/*--------------------------------------------------*/
/* 5: Test setting two characters */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN; i++) { mem1[i] = 99; }

    len = 2;
    value = 34;

    rc = wmemset_s(mem1, value, len);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if ( mem1[0] != value || mem1[1] != value ) {
        printf("%d - m1[0]=%d m1[1]=%d \n",
             __LINE__, mem1[0], mem1[1]);
    }
    for (i=2; i<LEN; i++) {
        if (mem1[i] != 99) {
            printf("%d - %d m1=%d \n",
                 __LINE__, i, mem1[i]);
        }
    }


/*--------------------------------------------------*/
/* 6: Test setting multiple characters */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN; i++) { mem1[i] = 99; }

    len = 12;
    value = 34;

    rc = wmemset_s(mem1, value, len);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__, rc);
    }

    for (i=0; i<len; i++) {
        if (mem1[i] != value) {
            printf("%d - %d m1=%d \n",
                 __LINE__, i, mem1[i]);
        }
    }
    for (i=len; i<LEN; i++) {
        if (mem1[i] != 99) {
            printf("%d - %d m1=%d \n",
                 __LINE__, i, mem1[i]);
        }
    }

/*--------------------------------------------------*/
/* 7: Test setting multiple characters */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN; i++) { mem1[i] = 99; }

    len = 31;
    value = 3;

    rc = wmemset_s(mem1, value, len);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__, rc);
    }

    for (i=0; i<len; i++) {
        if (mem1[i] != value) {
            printf("%d - %d m1=%d \n",
                 __LINE__, i, mem1[i]);
        }
    }

/*--------------------------------------------------*/
/* 8: Test setting multiple characters */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN; i++) { mem1[i] = 99; }

    len = 133;
    value = L'A';

    rc = wmemset_s(mem1, value, len);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__, rc);
    }

    for (i=0; i<len; i++) {
        if (mem1[i] != value) {
            printf("%d - %d m1=%d \n",
                 __LINE__, i, mem1[i]);
        }
    }

/*--------------------------------------------------*/
/*--------------------------------------------------*/

    return (0);
}

