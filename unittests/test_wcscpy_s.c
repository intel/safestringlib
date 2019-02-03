/*------------------------------------------------------------------
 * test_wcscpy_s
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
 *   TC12: Test for proper copy of short string over long string
 *   TC13: Test for not enough space in destination  (dest < src)
 *   TC16: Test copy short string over long string
 *
 *   TEST NON-STANDARD FAILURE CONDITIONS FOR NULL DEST STRINGS
 *   TC 9: Test copy null string over destination string
 *   TC10: Test copy NULL string over existing string (dest > src)
 *   TC11: Test copy string over NULL string (dest < src)
 *
 *   TEST WHEN DEST BUFFER >= SOURCE BUFFER
 *   TC 8: Test src buffer runs into beginning of dest buffer (src buffer is unterminated or been destroyed by copy)
 *   TC14: Test for not enough space in destination  (src < dest)
 *   TC15: Test copy of string - just enough space in dest
 *   TC17: Test copy with not enough room for final NULL in destination
 *
 *
 *------------------------------------------------------------------
 */

#include "test_private.h"
#include "safe_str_lib.h"

#define MAX   ( 128*4 )
#define LEN   ( 128*4 )

static wchar_t   str1[LEN];
static wchar_t   str2[LEN];

extern errno_t wcscpy_s(wchar_t* dest, rsize_t dmax, const wchar_t* src);


int test_wcscpy_s (void)
{
    errno_t rc;
#ifdef SAFE_LIB_STR_NULL_SLACK
    uint32_t i;
#endif /*SAFE_LIB_STR_NULL_SLACK*/
    int32_t  ind;
    rsize_t sz;
    rsize_t sz_orig;
    unsigned int testno = 0;


    printf("\nTesting wcscpy_s:\n");
/*--------------------------------------------------*/
/* 1  Test for NULL destination check                  */
printf("Test #%d:\n", ++testno);

    rc = wcscpy_s(NULL, LEN, str2);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

/*--------------------------------------------------*/
/* 2  Test for zero length destination                 */
    printf("Test #%d:\n", ++testno);

	rc = wcscpy_s(str1, 0, str2);
	if (rc != ESZEROL) {
		printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc );
	}

/*--------------------------------------------------*/
/* 3  Test for too large destination size              */
	printf("Test #%d:\n", ++testno);

	rc = wcscpy_s(str1, (RSIZE_MAX_STR+1), str2);
	if (rc != ESLEMAX) {
		printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc );
	}

/*--------------------------------------------------*/
/* 4  Test for NULL source check                       */
	printf("Test #%d:\n", ++testno);

   wmemcpy_s(str1, LEN, L"aaaaa", 5);

    rc = wcscpy_s(str1, 5, NULL);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

#ifdef SAFE_LIB_STR_NULL_SLACK
    for (i=0; i<5; i++) {
        if (str1[i] != L'\0') {
            printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        }
    }
#else
    if (str1[0] != L'\0') {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }
#endif


/*--------------------------------------------------*/
/* 5  Test for Src is same as dest, but source too long */
    printf("Test #%d:\n", ++testno);

    wmemcpy_s(str1, LEN, L"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 42);

    rc = wcscpy_s(str1, 5, str1);
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

/*--------------------------------------------------*/
/* 6  Test copy the same string onto itself            */
    printf("Test #%d:\n", ++testno);

    wmemcpy_s(str1, LEN, L"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 42);

	rc = wcscpy_s(str1, LEN, str1);
	if (rc != EOK) {
		printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc );
	}

/*--------------------------------------------------*/
/*--------------------------------------------------*/
/* 7  Test for string overlap, destination < src, and
 * dest overlaps onto the src string, so a copy would
 * change the src string                            */
	printf("Test #%d:\n", ++testno);

	wmemcpy_s(str1, LEN, L"keep it simple--keep it simple--keep it simple", 47);

	rc = wcscpy_s(&str1[0], LEN, &str1[5]);
	if (rc != ESOVRLP) {
		printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc );
	}

#ifdef SAFE_LIB_STR_NULL_SLACK
	for (i=0; i<LEN; i++) {
		if (str1[i] != L'\0') {
			printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc );
		}
	}
#else
	if (str1[0] != L'\0') {
		printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc );
	}
#endif


/*--------------------------------------------------*/
/* 8  Test for string overlap, src < dest, and
 * src overlaps onto the dest string, so a copy would
 * result in an infinite copy operation              */
	printf("Test #%d:\n", ++testno);

	wmemcpy_s(str1, LEN, L"keep it simple--keep it simple--keep it simple", 47);
	sz = wcsnlen_s(str1, LEN);

	rc = wcscpy_s(&str1[8], LEN, &str1[0]);
	if (rc != ESOVRLP) {
		printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc );
	}

#ifdef SAFE_LIB_STR_NULL_SLACK
	for (i=0; i<LEN; i++) {
		if (str1[i] != L'\0') {
			printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc );
		}
	}
#else
	if (str1[8] != L'\0') {
		printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc );
	}
#endif

/*--------------------------------------------------*/
/*--------------------------------------------------*/
/* 9  Test copying the null string (zero length string)
 * into another existing string, and overwriting
 * it's contents                                    */
	printf("Test #%d:\n", ++testno);

    wmemcpy_s(str1, LEN, L"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 41);
    str2[0] = L'\0';

    rc = wcscpy_s(str1, LEN/2, str2);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

#ifdef SAFE_LIB_STR_NULL_SLACK
    for (i=0; i<LEN/2; i++) {
        if (str1[i] != L'\0') {
            printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        }
    }
#else
    if (str1[0] != L'\0') {
        printf("%s %u   Error - string should be NULL rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }
#endif


/*--------------------------------------------------*/
/* 10  Test for copying string over NULL string */
    printf("Test #%d:\n", ++testno);

	wmemcpy_s(str1, LEN, L"keep it simple--keep it simple--keep it simple", 47);
	sz = wcsnlen_s(str1, LEN);
    memset_s(str2, '\0', 30);

    rc = wcscpy_s(str2, LEN, str1);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

    rc = memcmp_s(str2, LEN, str1, (sz+1)*sizeof(wchar_t), &ind );
    if (ind != 0) {
        printf("%s %u   Error -%ls- <> -%ls-\n",
                     __FUNCTION__, __LINE__,  str2, str1);
    }


/*--------------------------------------------------*/
/* 11  Test copying string over the NULL string         */
    printf("Test #%d:\n", ++testno);

    memset_s(str1, '\0', 50);
	wmemcpy_s(str2, LEN, L"keep it simple--keep it simple--keep it simple", 47);
	sz = wcsnlen_s(str2, LEN);

    rc = wcscpy_s(str1, LEN, str2);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

    rc = memcmp_s(str1, LEN, str2, (sz)*sizeof(wchar_t), &ind );
    if (ind != 0) {
        printf("%s %u -%ls- <> -%ls-  (smax=%lu) Error rc=%u \n",
                     __FUNCTION__, __LINE__,  str1, str2, sz, rc );
    }

/*--------------------------------------------------*/
/* 12  Test for accurate subString copy over existing string */
    printf("Test #%d:\n", ++testno);

    wmemset_s(str1, L'x', 20);
	wmemcpy_s(str2, LEN, L"keep it simple", 15);
	sz_orig = wcsnlen_s(str2, LEN);

    rc = wcscpy_s(str1, LEN, str2);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

    sz = wcsnlen_s(str1, LEN);
    if (sz != sz_orig && sz == 14) {
            printf("%s %u (sz=%lu <> 5) Error rc=%u \n",
                         __FUNCTION__, __LINE__,  sz, rc );
    }
    rc = memcmp_s(str1, LEN, str2, (sz)*sizeof(wchar_t), &ind );
    if (ind != 0) {
        printf("%s %u -%ls- <> -%ls-  (size=%lu) Error rc=%u \n",
                     __FUNCTION__, __LINE__,  str1, str2, sz, rc );
    }


/*--------------------------------------------------*/
/* 13 Test for not enough space in destination  (dest < src)  */
	printf("Test #%d:\n", ++testno);


    wmemset_s(str1, L'x', 20);
	wmemcpy_s(str2, LEN, L"keep it simple", 15);

    rc = wcscpy_s(str1, 14, str2);
    if (rc != ESNOSPC) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

    if (*str1 != L'\0') {
        printf("%s %u -%ls-  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  str1, rc );
    }

/*--------------------------------------------------*/
/* 14 Test for not enough space in destination (src < dest) */
    printf("Test #%d:\n", ++testno);

    wmemset_s(str1, L'x', 20);
	wmemcpy_s(str2, LEN, L"keep it simple", 15);

    rc = wcscpy_s(str2, 6, str1);
    if (rc != ESNOSPC) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

    if (*str2 != L'\0') {
        printf("%s %u -%ls-  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  str1, rc );
    }

/*--------------------------------------------------*/
/* 15 Test for just enough space in destination        */
    printf("Test #%d:\n", ++testno);


    wmemcpy_s(str1, LEN, L"it", 3);
	wmemcpy_s(str2, LEN, L"qqweqeqeqeq", 12);

    rc = wcscpy_s(str2, 3, str1);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

    rc = memcmp_s(str1, LEN, str2, (3)*sizeof(wchar_t), &ind );
    if (ind != 0) {
        printf("%s %u -%ls-  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  str1, rc );
    }

/*--------------------------------------------------*/
/* 16 Test copy short string over long string          */
    printf("Test #%d:\n", ++testno);

	wmemcpy_s(str1, LEN, L"qq12345weqeqeqeq", 17);
    wmemcpy_s(str2, LEN, L"it", 3);
	sz_orig = wcsnlen_s(str2, LEN);


    rc = wcscpy_s(str1, 10, str2);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

    rc = memcmp_s(str1, LEN, str2, (3)*sizeof(wchar_t), &ind );
    if (ind != 0) {
        printf("%s %u -%ls-  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  str1, rc );
    }


/*--------------------------------------------------*/
/* 17 Test for not enough space in destination for final NULL */
	printf("Test #%d:\n", ++testno);

    wmemcpy_s(str1, LEN, L"it", 3);
	wmemcpy_s(str2, LEN, L"qqweqeqeqeq", 12);

	sz = wcsnlen_s(str2, LEN);

	rc = wcscpy_s(str2, 2, str1);
	if (rc != ESNOSPC) {
		printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc );
	}

    if (*str2 != L'\0') {
        printf("%s %u -%ls-  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  str1, rc );
    }
/*--------------------------------------------------*/

    return (0);
}

