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
 *   TC 3: Test for last parameter, source length (slen), being larger than the maximum allowed size
 *   TC 4: Test for second parameter, dest maximum length (dmax), being sent in as zero
 *   TC 5: Test for second parameter, dest maximum length (dmax), being larger than the maximum allowed size
 *
 *   TEST WHEN DEST BUFFER < SOURCE BUFFER
 *   TC 6: Test for searching end of dest buffer runs into the src buffer (buffers overlap)
 *   TC 7: Test for dest buffer unterminated in dmax characters
 *   TC 8: Test for overlap of dest buffer into src buffer after copying from source begins
 *   TC 9: Test for proper concatenation of only slen characters from source string
 *   TC10: Test for proper concatenation of two strings
 *
 *   TEST NON-STANDARD FAILURE CONDITIONS FOR NULL DEST STRINGS
 *   TC 11: Test null string destination and size too short
 *   TC 12: Test null string destination and dmax size is one character too short
 *   TC 13: Test for proper concatenation into a NULL string of appropriate buffer size
 *   TC 14: Test concatenation of two NULL strings
 *   TC 15: Test concatenation of NULL string onto end of existing string
 *
 *   TEST WHEN DEST BUFFER >= SOURCE BUFFER
 *   TC16: Test concatenation of two strings - proper result
 *   TC17: Test for dest buffer unterminated in dmax characters
 *   TC18: Test for not enough space in dest buffer to fit src buffer characters
 *   TC19: Test src buffer runs into beginning of dest buffer (src buffer is unterminated or been destroyed by copy)
 *   TC20: Test concatenation with just enough space in the destination buffer
 *   TC21: Test for proper concatenation of only slen characters from source string
 *   TC22: Test concatenation with not enough room for final NULL in destination
 *
 *
 *------------------------------------------------------------------
 */

#include "test_private.h"
#include "safe_str_lib.h"

#define LEN   ( 128 )

static wchar_t   str1[LEN];
static wchar_t   str2[LEN];

extern rsize_t wcsnlen_s (const wchar_t *dest, rsize_t dmax);
extern errno_t wcscpy_s(wchar_t* dest, rsize_t dmax, const wchar_t* src);
extern errno_t wcsncat_s (wchar_t *dest, rsize_t dmax, const wchar_t *src, rsize_t slen);

int test_wcsncat_s (void)
{
    errno_t rc;
    int32_t  ind;
    int32_t  len1;
    int32_t  len2;
    int32_t  len3;
    unsigned int testno = 0;


    printf("\nTesting wcsncat_s:\n");
/*--------------------------------------------------*/
/* 1  Test for NULL destination check                  */
    printf("Test #%d:\n", ++testno);

    rc = wcsncat_s(NULL, LEN, str2, LEN);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

/*--------------------------------------------------*/
/* 2  Test for NULL source check                  */
    printf("Test #%d:\n", ++testno);

    rc = wcsncat_s(str1, LEN, NULL, LEN);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

/*--------------------------------------------------*/
/* 3  Test  Exceed Maximum possible size of source     */
	printf("Test #%d:\n", ++testno);

	rc = wcsncat_s(str1, LEN, str2, (RSIZE_MAX_STR+1));
	if (rc != ESLEMAX) {
		printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc);
	}
/*--------------------------------------------------*/
/* 4   Test zero maximum length of destination */
    printf("Test #%d:\n", ++testno);

    rc = wcsncat_s(str1, 0, str2, LEN);
    if (rc != ESZEROL) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

/*--------------------------------------------------*/
/* 5  Test  Exceed Maximum size of destination     */
    printf("Test #%d:\n", ++testno);

    rc = wcsncat_s(str1, (RSIZE_MAX_STR+1), str2, LEN);
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }


/*--------------------------------------------------*/
/*--------------------------------------------------*/
/* 6   Test destination buffer overlaps into the src buffer */
    printf("Test #%d:\n", ++testno);

    wcscpy_s(str1, LEN, L"aaaaaaaaaa keep it simple");

    rc = wcsncat_s(str1, LEN, &str1[11], LEN);
    if (rc != ESOVRLP) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

    if (str1[0] != '\0') {
        printf("%s %u  Expected null  \n",
                     __FUNCTION__, __LINE__);
    }

/*--------------------------------------------------*/
/* 7   Test length of destination appears unterminated */
    printf("Test #%d:\n", ++testno);

    wcscpy_s(str1, LEN, L"keep it simple");

    rc = wcsncat_s(str1, 2, &str1[20], LEN);
    if (rc != ESUNTERM) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

    if (str1[0] != '\0') {
        printf("%s %u  Expected null  \n",
                     __FUNCTION__, __LINE__);
    }

/*--------------------------------------------------*/
/* 8   Test overlap of destination buffer into source after copying begins */
	printf("Test #%d:\n", ++testno);

	wcscpy_s(str1, LEN, L"keep it simple");
	wcscpy_s(&str1[20], LEN, L"aaaaaaaaaaaaaaaaaaaa");

	rc = wcsncat_s(str1, 30, &str1[20], LEN);
	if (rc != ESOVRLP) {
		printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc);
	}

	if (str1[0] != '\0') {
		printf("%s %u  Expected null  \n",
					 __FUNCTION__, __LINE__);
	}

/*--------------------------------------------------*/
/* 9   Test proper concatenated of at most slen characters */
    printf("Test #%d:\n", ++testno);

    wcscpy_s(&str1[0], LEN, L"aaaaaaaaaa");
    wcscpy_s(&str2[0], LEN, L"keep it simple");

    len1 = wcsnlen_s(str1, LEN);
    len2 = 10;

    rc = wcsncat_s(str1, 50, str2, len2);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

    len3 = wcsnlen_s(str1, LEN);
    if (len3 != (len1+len2)) {
        printf("%s %u lengths wrong: %u  %u  %u \n",
                     __FUNCTION__, __LINE__, len1, len2, len3);
    }

    rc = memcmp_s(str1, LEN, L"aaaaaaaaaakeep it si", (len3+1)*sizeof(wchar_t), &ind );
    if (ind != 0) {
        printf("%s %u   Error -%ls- \n",
                     __FUNCTION__, __LINE__,  str1);
    }

/*--------------------------------------------------*/
/* 10   Test Verify proper size of concatenated strings & value of concatenated string */
	printf("Test #%d:\n", ++testno);

	wcscpy_s(&str1[0], LEN, L"aaaaaaaaaa");
	wcscpy_s(&str2[0], LEN, L"keep it simple");

	len1 = wcsnlen_s(str1, LEN);
	len2 = wcsnlen_s(str2, LEN);

	rc = wcsncat_s(str1, 50, str2, LEN);
	if (rc != EOK) {
		printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc);
	}

	len3 = wcsnlen_s(str1, LEN);
	if (len3 != (len1+len2)) {
		printf("%s %u lengths wrong: %u  %u  %u \n",
					 __FUNCTION__, __LINE__, len1, len2, len3);
	}

    rc = memcmp_s(str1, LEN, L"aaaaaaaaaakeep it simple", (len3+1)*sizeof(wchar_t), &ind );
    if (ind != 0) {
        printf("%s %u   Error -%ls- \n",
                     __FUNCTION__, __LINE__,  str1);
    }

/*--------------------------------------------------*/
/*--------------------------------------------------*/
/* 11   Test NULL string is destination  - too short */
    printf("Test #%d:\n", ++testno);

    str1[0] = '\0';
    wcscpy_s(str2, LEN, L"keep it simple");

    rc = wcsncat_s(str1, 1, str2, LEN);
    if (rc != ESNOSPC) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

    if (str1[0] != '\0') {
        printf("%s %u  Expected null  \n",
                     __FUNCTION__, __LINE__);
    }

/*--------------------------------------------------*/
/* 12   Test NULL string is destination  - too short */
    printf("Test #%d:\n", ++testno);

    str1[0] = '\0';
    wcscpy_s(str2, LEN, L"keep it simple");

    rc = wcsncat_s(str1, 14, str2, LEN);
    if (rc != ESNOSPC) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

    if (str1[0] != '\0') {
        printf("%s %u  Expected null  \n",
                     __FUNCTION__, __LINE__);
    }

/*--------------------------------------------------*/
/* 13   Test NULL string is destination  - proper result */
    printf("Test #%d:\n", ++testno);

    str1[0] = '\0';
    wcscpy_s(str2, LEN, L"keep it simple");

    rc = wcsncat_s(str1, 20, str2, LEN);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

    rc = memcmp_s(str1, LEN, str2, wcsnlen_s(str2, LEN)*sizeof(wchar_t), &ind );
    if (ind != 0) {
        printf("%s %u   Error -%ls- \n",
                     __FUNCTION__, __LINE__,  str1);
    }

/*--------------------------------------------------*/
/*--------------------------------------------------*/
/* 14   Test concat two NULL strings */
    printf("Test #%d:\n", ++testno);

    str1[0] = '\0';
    str2[0] = '\0';

    rc = wcsncat_s(str1, LEN, str2, LEN);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

    if (str1[0] != '\0') {
        printf("%s %u  Expected null  \n",
                     __FUNCTION__, __LINE__);
    }

/*--------------------------------------------------*/
/* 15   Test concat NULL string to existing string  - proper result */
    printf("Test #%d:\n", ++testno);

    str1[0] = '\0';
    wcscpy_s(str2, LEN, L"keep it simple");

    rc = wcsncat_s(str2, LEN, str1, LEN);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

    rc = memcmp_s(str2, LEN, L"keep it simple", (15)*sizeof(wchar_t), &ind );
    if (ind != 0) {
        printf("%s %u   Error -%ls- \n",
                     __FUNCTION__, __LINE__,  str1);
    }

/*--------------------------------------------------*/
/* 16   Test concat two strings  - proper result */
    printf("Test #%d:\n", ++testno);

    wcscpy_s(str2, LEN, L"qqweqq");
    wcscpy_s(str1, LEN, L"keep it simple");

    rc = wcsncat_s(str2, LEN, str1, LEN);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

    rc = memcmp_s(str2, LEN, L"qqweqqkeep it simple", (20)*sizeof(wchar_t), &ind );
    if (ind != 0) {
        printf("%s %u   Error -%ls- \n",
                     __FUNCTION__, __LINE__,  str1);
    }

/*--------------------------------------------------*/
/* 17   Test concat two strings  - dest appears unterminated */
    printf("Test #%d:\n", ++testno);

    wcscpy_s(str1, LEN, L"1234");
    wcscpy_s(str2, LEN, L"keep it simple");

    rc = wcsncat_s(str2, 12, str1, LEN);
    if (rc != ESUNTERM) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

    if (str2[0] != '\0') {
        printf("%s %u  Expected null  \n",
                     __FUNCTION__, __LINE__);
    }

/*--------------------------------------------------*/
/* 18   Test concat two strings  - not enough space in dest */
	printf("Test #%d:\n", ++testno);

	wcscpy_s(str1, LEN, L"1234");
	wcscpy_s(str2, LEN, L"keep it simple");

	rc = wcsncat_s(str2, 16, str1, LEN);
	if (rc != ESNOSPC) {
		printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc);
	}

    if (str2[0] != '\0') {
        printf("%s %u  Expected null  \n",
                     __FUNCTION__, __LINE__);
    }

/*--------------------------------------------------*/
/* 19   Test overlapping destination string into the beginning of the src */
	printf("Test #%d:\n", ++testno);

	wcscpy_s(str1, LEN, L"12345678901234567890");

	rc = wcsncat_s(&str1[7], LEN, str1, LEN);
	if (rc != ESOVRLP) {
		printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc);
	}

	if (str1[7] != '\0') {
		printf("%s %u  Expected null  \n",
					 __FUNCTION__, __LINE__);
	}

/*--------------------------------------------------*/
/* 20   Test concat two strings  - just enough space in the destination */
    printf("Test #%d:\n", ++testno);

    wcscpy_s(str1, LEN, L"1234");
    wcscpy_s(str2, LEN, L"keep it simple");

    rc = wcsncat_s(str2, 19, str1, LEN);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

    rc = memcmp_s(str2, LEN, L"keep it simple1234", (19)*sizeof(wchar_t), &ind );
    if (ind != 0) {
        printf("%s %u   Error -%ls- \n",
                     __FUNCTION__, __LINE__,  str1);
    }

/*--------------------------------------------------*/
/* 21   Test copy at most slen characters from src string  */
    printf("Test #%d:\n", ++testno);

    wcscpy_s(str2, LEN, L"123456789");
    wcscpy_s(str1, LEN, L"keep it simple");

    rc = wcsncat_s(str2, LEN, str1, 7);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

    rc = memcmp_s(str2, LEN, L"123456789keep it", (17)*sizeof(wchar_t), &ind );
    if (ind != 0) {
        printf("%s %u   Error -%ls- \n",
                     __FUNCTION__, __LINE__,  str1);
    }

/*--------------------------------------------------*/
/* 22   Test normal string concat - no enough room for NULL */
	printf("Test #%d:\n", ++testno);

	wcscpy_s(str2, LEN, L"1234");
	wcscpy_s(str1, LEN, L"56789");

	rc = wcsncat_s(str2, 9, str1, LEN);
	if (rc != ESNOSPC) {
		printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc);
	}

    if (str2[0] != L'\0') {
        printf("%s %u  Expected null  \n",
                     __FUNCTION__, __LINE__);
    }


/*--------------------------------------------------*/

    return (0);
}


