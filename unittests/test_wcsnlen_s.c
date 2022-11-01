/*  SPDX-License-Identifier: MIT */
/*
 *  Copyright (c) 2014-2022 by Intel Corp
 */

/*------------------------------------------------------------------
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
 *
 *
 *
 *------------------------------------------------------------------
 */

#include "test_private.h"
#include "safe_str_lib.h"

#define MAX   ( 128*4 )
#define LEN   ( 128*4 )

static wchar_t   str1[LEN];

extern rsize_t wcsnlen_s(const wchar_t *dest, rsize_t dmax);
extern errno_t wmemset_s(wchar_t *dest, wchar_t value, rsize_t len);

int test_wcsnlen_s (void)
{
    errno_t rc;
    unsigned int testno = 0;


    printf("\nTesting wcsnlen_s:\n");
/*--------------------------------------------------*/
/* 1  Test for NULL destination check                  */
printf("Test #%d:\n", ++testno);

    rc = wcsnlen_s(NULL, LEN);
    if (rc != 0) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

/*--------------------------------------------------*/
/* 2  Test for too large maximum size              */
    printf("Test #%d:\n", ++testno);

    rc = wcsnlen_s(str1, (RSIZE_MAX_STR+1));
    if (rc != 0) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

/*--------------------------------------------------*/
/* 3  Test for length is equal to maximum */
    printf("Test #%d:\n", ++testno);

    wmemcpy_s(str1, LEN, L"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 40);

    rc = wcsnlen_s(str1, 40);
    if (rc != 40) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
    }

/*--------------------------------------------------*/
/* 4  Test for return length is equal to dmax */
    printf("Test #%d:\n", ++testno);

    wmemcpy_s(str1, LEN, L"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 40);

    rc = wcsnlen_s(str1, 20);
    if (rc != 20) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
    }

/*--------------------------------------------------*/
/* 5  Test for zero length string            */
    printf("Test #%d:\n", ++testno);

    wmemset_s(str1, L'\0', 42);

    rc = wcsnlen_s(str1, LEN);
    if (rc != 0) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
    }


/*--------------------------------------------------*/
/* 6  Test for single character string         */
    printf("Test #%d:\n", ++testno);

    memset_s(str1, '\0', 50);
    str1[0] = L'A';

    rc = wcsnlen_s(str1, LEN);
    if (rc != 1) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
    }

/*--------------------------------------------------*/
/* 7  Test for two char string */
    printf("Test #%d:\n", ++testno);

    wmemcpy_s(str1, LEN, L"12", 3);

    rc = wcsnlen_s(str1, LEN);
    if (rc != 2) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
    }


    return (0);
}

