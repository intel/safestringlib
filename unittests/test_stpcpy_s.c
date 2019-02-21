/*------------------------------------------------------------------
 * test_stpcpy_s
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
 *
 *   TEST WHEN SRC & DEST ARE THE SAME
 *   TC 5: Test for src=dest, but string too long for dmax
 *   TC 6: Test for src=dest, proper return
 *
 *   TEST WHEN DEST BUFFER < SOURCE BUFFER
 *   TC 7: Test for overlap of dest buffer into src buffer (src string too long)
 *   TC12: Test for proper longer string copy over shorter string
 *   TC13: Test for not enough space in destination (dest < src)
 *   TC15: Test for just enough space in destination
 *
 *   TEST NON-STANDARD FAILURE CONDITIONS FOR NULL DEST STRINGS
 *   TC 9: Test copy null string over destination string (dest < src)
 *   TC10: Test copy NULL string over existing string (dest > src)
 *   TC11: Test copy string over NULL string (dest < src)
 *
 *   TEST WHEN DEST BUFFER >= SOURCE BUFFER
 *   TC 8: Test src buffer runs into beginning of dest buffer (src buffer is unterminated or been destroyed by copy)
 *   TC14: Test for not enough space in destination (dest > src)
 *   TC16: Test copy short string over long string
 *
 *
 *
 *------------------------------------------------------------------
 */

#include "test_private.h"
#include "safe_str_lib.h"

#define MAX   ( 128 )
#define LEN   ( 128 )

static char   str1[LEN];
static char   str2[LEN];

int test_stpcpy_s (void)
{
	char *ret;
    errno_t rc;
#ifdef SAFE_LIB_STR_NULL_SLACK
    uint32_t i;
#endif /*SAFE_LIB_STR_NULL_SLACK*/
    int32_t  ind;
    unsigned int testno = 0;

    printf("\nTesting stpcpy_s:\n");
/*--------------------------------------------------*/
/* 1 Test for NULL destination check                  */
    printf("Test #%d:\n", ++testno);

    ret = stpcpy_s(NULL, LEN, str2, &rc);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

    if (ret != NULL) {
    	printf("Returned pointer incorrect: %s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

/*--------------------------------------------------*/
/* 2 Test for zero length destination                 */
    printf("Test #%d:\n", ++testno);

	ret = stpcpy_s(str1, 0, str2, &rc);
	if (rc != ESZEROL) {
		printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc );
	}
	if (ret != NULL) {
		printf("Returned pointer incorrect: %s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc );
	}


/*--------------------------------------------------*/
/* 3 Test for too large destination size              */
    printf("Test #%d:\n", ++testno);

	ret = stpcpy_s(str1, (RSIZE_MAX_STR+1), str2, &rc);
	if (rc != ESLEMAX) {
		printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc );
	}
	if (ret != NULL) {
		printf("Returned pointer incorrect: %s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc );
	}

/*--------------------------------------------------*/
/* 4 Test for NULL source check                       */
    printf("Test #%d:\n", ++testno);

   strcpy(str1, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

    ret = stpcpy_s(str1, 5, NULL, &rc);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

    if (ret != NULL) {
    	printf("Returned pointer incorrect: %s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

#ifdef SAFE_LIB_STR_NULL_SLACK
    for (i=0; i<5; i++) {
        if (str1[i] != '\0') {
            printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        }
    }
#else
    if (str1[0] != '\0') {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }
#endif


/*--------------------------------------------------*/
/* 5 Test for Src is same as dest, but source too long */
    printf("Test #%d:\n", ++testno);

    strcpy(str1, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

    ret = stpcpy_s(str1, 5, str1, &rc);
    if (rc != ESNOSPC) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }


    if (ret != NULL) {
    	printf("Returned pointer incorrect: %s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }


/*--------------------------------------------------*/
/* 6 Test copy the same string onto itself            */
    printf("Test #%d:\n", ++testno);

	strcpy(str1, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

	ret = stpcpy_s(str1, LEN, str1, &rc);
	if (rc != EOK) {
		printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc );
	}

	if (ret == NULL || ret[0] != '\0' || ret != str1+strnlen_s(str1, LEN) ) {
		printf("Returned pointer incorrect: %s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc );
	}

/*--------------------------------------------------*/
/* 7  Test for string overlap, destination < src, and
 * dest overlaps onto the src string, so a copy would
 * change the src string                            */
    printf("Test #%d:\n", ++testno);

	strcpy(&str1[0], "keep it simple");

	ret = stpcpy_s(&str1[0], LEN, &str1[5], &rc);
	if (rc != ESOVRLP) {
		printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc );
	}
	if (ret != NULL) {
		printf("Returned pointer incorrect: %s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc );
	}

#ifdef SAFE_LIB_STR_NULL_SLACK
	for (i=0; i<LEN; i++) {
		if (str1[i] != '\0') {
			printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc );
		}
	}
#else
	if (str1[0] != '\0') {
		printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc );
	}
#endif


/*--------------------------------------------------*/
/* 8 Test for string overlap, destination > src, and
 * src overlaps onto the dest string, so a copy would
 * result in an infinite copy operation              */
    printf("Test #%d:\n", ++testno);

	strcpy(&str1[0], "keep it simple");

	ret = stpcpy_s(&str1[5], LEN, &str1[0], &rc);
	if (rc != ESOVRLP) {
		printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc );
	}
	if (ret != NULL) {
		printf("Returned pointer incorrect: %s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc );
	}

#ifdef SAFE_LIB_STR_NULL_SLACK
	for (i=0; i<LEN; i++) {
		if (str1[i] != '\0') {
			printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc );
		}
	}
#else
	if (str1[5] != '\0') {
		printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc );
	}
#endif






/*--------------------------------------------------*/
/*--------------------------------------------------*/
/* 9 Test copying the null string (zero length string)
 * into another existing string, and overwriting
 * it's contents                                    */
    printf("Test #%d:\n", ++testno);

    strcpy(str1, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    str2[0] = '\0';

    ret = stpcpy_s(str1, LEN/2, str2, &rc);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }
    if (ret == NULL || ret[0] != '\0' || ret != str1) {
    	printf("Returned pointer incorrect: %s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

#ifdef SAFE_LIB_STR_NULL_SLACK
    for (i=0; i<LEN/2; i++) {
        if (str1[i] != '\0') {
            printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        }
    }
#else
    if (str1[0] != '\0') {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }
#endif


/*--------------------------------------------------*/
/* 10 Test for copying NULL string over existing string */
    printf("Test #%d:\n", ++testno);

    str1[0] = '\0';
    strcpy(&str2[0], "keep it simple");

    ret = stpcpy_s(str2, LEN, str1, &rc);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }
    if (ret == NULL || ret[0] != '\0' || ret != str2) {
    	printf("Returned pointer incorrect: %s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

    if (*str2 != '\0') {
        printf("%s %u -%s-  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  str1, rc );
    }

/*--------------------------------------------------*/
/* 11 Test copying string to end of NULL string         */
    printf("Test #%d:\n", ++testno);

    str1[0] = '\0';
    strcpy(&str2[0], "keep it simple");

    ret = stpcpy_s(str1, LEN, str2, &rc);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

    /* be sure the results are the same as strcmp */
    ind = strcmp(str1, str2);
    if (ind != 0) {
        printf("%s %u -%s-  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  str1, rc );
    }

    if (ret == NULL || ret[0] != '\0' || ret != str1+strnlen_s(str1, LEN) ) {
    	printf("Returned pointer incorrect: %s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

/*--------------------------------------------------*/
/* 12 Test for accurate String copy over existing string */
    printf("Test #%d:\n", ++testno);

    strcpy(str1, "qqweqeqeqeq");
    strcpy(str2, "keep it simple");

    ret = stpcpy_s(str1, LEN, str2, &rc);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

    if (ret == NULL || ret[0] != '\0' || ret != str1+strnlen_s(str1, LEN) ) {
    	printf("Returned pointer incorrect: %s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

    /* be sure the results are the same as strcmp */
    ind = strcmp(str1, str2);
    if (ind != 0) {
        printf("%s %u -%s-  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  str1, rc );
    }

/*--------------------------------------------------*/
/* 13: Test for not enough space in destination         */
    printf("Test #%d:\n", ++testno);

    strcpy(str1, "qqweqeqeqeq");
    strcpy(str2, "keep it simple");

    ret = stpcpy_s(str1, 1, str2, &rc);
    if (rc != ESNOSPC) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }
    if (ret != NULL) {
    	printf("Returned pointer incorrect: %s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

    if (*str1 != '\0') {
        printf("%s %u -%s-  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  str1, rc );
    }

/*--------------------------------------------------*/
/* 14: Test for not enough space in destination (dest > src)        */
    printf("Test #%d:\n", ++testno);

    strcpy(str1, "qqweqeqeqeq");
    strcpy(str2, "keep it simple");

    ret = stpcpy_s(str2, 2, str1, &rc);
    if (rc != ESNOSPC) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }
    if (ret != NULL) {
    	printf("Returned pointer incorrect: %s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

    if (*str2 != '\0') {
        printf("%s %u -%s-  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  str1, rc );
    }

/*--------------------------------------------------*/
/* 15: Test for just enough space in destination        */
    printf("Test #%d:\n", ++testno);

    strcpy(str1, "qqweqeqeqeq");
    strcpy(str2, "it");

    ret = stpcpy_s(str1, 3, str2, &rc);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

    /* be sure the results are the same as strcmp */
    ind = strcmp(str1, str2);
    if (ind != 0) {
        printf("%s %u -%s-  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  str1, rc );
    }
    if (ret == NULL || ret[0] != '\0' || ret != str1+strnlen_s(str1, LEN) ) {
    	printf("Returned pointer incorrect: %s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

/*--------------------------------------------------*/
/* 16: Test copy short string over long string          */
    printf("Test #%d:\n", ++testno);

    strcpy(str2, "qq12345weqeqeqeq");
    strcpy(str1, "it");

    ret = stpcpy_s(str2, 10, str1, &rc);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }
    if (ret == NULL || ret[0] != '\0' || ret != str2+strnlen_s(str2, LEN) ) {
    	printf("Returned pointer incorrect: %s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

    /* be sure the results are the same as strcpy */
    ind = strcmp(str1, str2);
    if (ind != 0) {
        printf("%s %u -%s-  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  str1, rc );
    }


/*--------------------------------------------------*/

    return (0);
}

