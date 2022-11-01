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
 *   TC 5: Test for last parameter, source length (slen), being sent in as zero
 *   TC 6: Test for last parameter, source length (slen), being larger than the maximum allowed size
 *
 *   TEST WHEN SRC & DEST ARE THE SAME
 *   TC 7: Test for src=dest, overlapping buffers not the same
 *
 *   TEST WHEN DEST BUFFER < SOURCE BUFFER
 *   TC 8: Test for overlap of dest buffer into src buffer
 *   TC 9: Test copy only slen characters from src into dest (src string longer than provided length)
 *   TC10: Test for copy dest < src, and copy ends after copy NULL char (slen > char string)
 *   TC11: Test for copy dest < src, but dmax too small to hold src string
 *   TC16: Test for accurate String copy over existing string (src > dest)
 *
 *   TEST WHEN DEST BUFFER >= SOURCE BUFFER
 *   TC12: Test overlapping buffers fails ( dest > src )
 *   TC13: Test copy only slen characters from src into dest (dest > src)
 *   TC14: Test for copy src < dest, and copy ends after copy NULL char (slen > char string)
 *   TC15: Test for copy src < dest, but dmax too small to hold src string
 *   TC17: Test for just enough space in destination (src < dest)
 *   TC18: Test for not enough space in destination for final NULL (dest > src)
 *
 *------------------------------------------------------------------
 */

#include "test_private.h"
#include "safe_str_lib.h"

#define MAX   ( 128*4 )
#define LEN   ( 128*4 )

static wchar_t   str1[LEN];
static wchar_t   str2[LEN];

extern errno_t wcsncpy_s(wchar_t* dest, rsize_t dmax, const wchar_t* src, rsize_t slen);

extern rsize_t wcsnlen_s(const wchar_t *dest, rsize_t dmax);
extern errno_t wmemset_s (wchar_t *dest, wchar_t value, rsize_t len);

int test_wcsncpy_s (void)
{
    errno_t rc;
#ifdef SAFE_LIB_STR_NULL_SLACK
    uint32_t i;
#endif /*SAFE_LIB_STR_NULL_SLACK*/
    int32_t  ind;
    rsize_t sz;
    rsize_t sz_orig;
    unsigned int testno = 0;


    printf("\nTesting wcsncpy_s:\n");
/*--------------------------------------------------*/
/* 1  Test for NULL destination check                  */
printf("Test #%d:\n", ++testno);

    rc = wcsncpy_s(NULL, LEN, str2, LEN);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

/*--------------------------------------------------*/
/* 2  Test for zero length destination                 */
    printf("Test #%d:\n", ++testno);

    rc = wcsncpy_s(str1, 0, str2, LEN);
    if (rc != ESZEROL) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

/*--------------------------------------------------*/
/* 3  Test for too large destination size              */
    printf("Test #%d:\n", ++testno);

    rc = wcsncpy_s(str1, (RSIZE_MAX_STR+1), str2, LEN);
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

/*--------------------------------------------------*/
/* 4  Test for NULL source check                       */
    printf("Test #%d:\n", ++testno);

   wmemcpy_s(str1, LEN, L"aaaaa", 5);

    rc = wcsncpy_s(str1, 5, NULL, LEN);
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
/* 5  Test for zero length source                 */
    printf("Test #%d:\n", ++testno);

    rc = wcsncpy_s(str1, LEN, str2, 0);
    if (rc != ESZEROL) {
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
/* 6  Test for too large source size              */
    printf("Test #%d:\n", ++testno);

    rc = wcsncpy_s(str1, LEN, str2, (RSIZE_MAX_STR+1));
    if (rc != ESLEMAX) {
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
/* 7  Test for Src is same as dest, overlapping buffers not allowed */
    printf("Test #%d:\n", ++testno);

    wmemcpy_s(str1, LEN, L"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 40);

    rc = wcsncpy_s(str1, 5, str1, LEN);
    if (rc != ESOVRLP) {
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
/* 8  Test overlapping buffers fails            */
    printf("Test #%d:\n", ++testno);

    wmemcpy_s(str1, LEN, L"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 40);

    rc = wcsncpy_s(str1, LEN, &str1[5], 30);
    if (rc != ESOVRLP) {
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
/*--------------------------------------------------*/
/* 9 Test copy only slen characters from src into dest                            */
    printf("Test #%d:\n", ++testno);

    wmemcpy_s(str2, LEN, L"keep it simple--keep it simple--keep it simple", 47);
    wmemset_s(str1, L'\0', 20);

    rc = wcsncpy_s(str1, LEN, str2, 10);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

    if (str1[9] == L'\0' && str2[10] != L'\0') {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

    rc = memcmp_s(str1, LEN, str2, (10)*sizeof(wchar_t), &ind );
    if (ind != 0) {
        printf("%s %u   Error -%ls- <> -%ls-\n",
                     __FUNCTION__, __LINE__,  str1, str2);
    }


/*--------------------------------------------------*/
/* 10  Test for copy src > dest, and copy ends after copy NULL char (slen > char string)  */
    printf("Test #%d:\n", ++testno);

    wmemset_s(str1, L'\0', 20);
    wmemcpy_s(str2, LEN, L"keep it simple--keep it simple--keep it simple", 47);
    sz = wcsnlen_s(str2, LEN);

    rc = wcsncpy_s(str1, LEN, str2, LEN);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

    if (str1[sz] != L'\0') {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

    rc = memcmp_s(str1, LEN, str2, (sz+1)*sizeof(wchar_t), &ind );
    if (ind != 0) {
        printf("%s %u   Error -%ls- <> -%ls-\n",
                     __FUNCTION__, __LINE__,  str1, str2);
    }

/*--------------------------------------------------*/
/*--------------------------------------------------*/
/* 11 Test for copy src > dest, but dmax too small to hold src string                                    */
    printf("Test #%d:\n", ++testno);

    wmemset_s(str1, L'\0', 20);
    wmemcpy_s(str2, LEN, L"keep it simple--keep it simple--keep it simple", 47);
    sz = wcsnlen_s(str2, LEN);

    rc = wcsncpy_s(str1, (sz-5), str2, LEN);
    if (rc != ESNOSPC) {
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
/* 12  Test overlapping buffers fails (dest > src )   */
    printf("Test #%d:\n", ++testno);

    wmemcpy_s(str1, LEN, L"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 40);

    rc = wcsncpy_s(&str1[5], LEN, str1, 30);
    if (rc != ESOVRLP) {
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
    if (str1[5] != L'\0') {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }
#endif

/*--------------------------------------------------*/
/*--------------------------------------------------*/
/* 13 Test copy only slen characters from src into dest    */
    printf("Test #%d:\n", ++testno);

    wmemcpy_s(str1, LEN, L"keep it simple--keep it simple--keep it simple", 47);
    wmemset_s(str2, L'\0', 20);

    rc = wcsncpy_s(str2, LEN, str1, 17);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

    if (str2[16] == L'\0' && str2[17] != L'\0') {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

    rc = memcmp_s(str1, LEN, str2, (17)*sizeof(wchar_t), &ind );
    if (ind != 0) {
        printf("%s %u   Error -%ls- <> -%ls-\n",
                     __FUNCTION__, __LINE__,  str1, str2);
    }


/*--------------------------------------------------*/
/* 14  Test for copy src < dest, and copy ends after copy NULL char (slen > char string)  */
    printf("Test #%d:\n", ++testno);

    wmemset_s(str2, L'\0', 20);
    wmemcpy_s(str1, LEN, L"keep it simple--keep it simple--keep it simple", 47);
    sz = wcsnlen_s(str1, LEN);

    rc = wcsncpy_s(str2, LEN, str1, LEN);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

    if (str1[sz] != L'\0') {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

    rc = memcmp_s(str2, LEN, str1, (sz+1)*sizeof(wchar_t), &ind );
    if (ind != 0) {
        printf("%s %u   Error -%ls- <> -%ls-\n",
                     __FUNCTION__, __LINE__,  str2, str1);
    }

/*--------------------------------------------------*/
/*--------------------------------------------------*/
/* 15: Test for copy src < dest, but dmax too small to hold src string   */
    printf("Test #%d:\n", ++testno);

    wmemset_s(str2, L'\0', 20);
    wmemcpy_s(str1, LEN, L"keep it simple--keep it simple--keep it simple", 47);
    sz = wcsnlen_s(str1, LEN);

    rc = wcsncpy_s(str2, (sz-5), str1, LEN);
    if (rc != ESNOSPC) {
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
    if (str2[0] != L'\0') {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }
#endif


/*--------------------------------------------------*/
/* 16: Test for accurate String copy over existing string */
    printf("Test #%d:\n", ++testno);

    wmemset_s(str1, L'x', 20);
    wmemcpy_s(str2, LEN, L"keep it simple", 15);
    sz_orig = wcsnlen_s(str2, LEN);

    rc = wcsncpy_s(str1, LEN, str2, LEN);
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
/* 17: Test for just enough space in destination        */
    printf("Test #%d:\n", ++testno);


    wmemcpy_s(str1, LEN, L"it", 3);
    wmemcpy_s(str2, LEN, L"qqweqeqeqeq", 12);

    rc = wcsncpy_s(str2, 3, str1, LEN);
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
/* 18: Test for not enough space in destination for final NULL */
    printf("Test #%d:\n", ++testno);

    wmemcpy_s(str1, LEN, L"it", 3);
    wmemcpy_s(str2, LEN, L"qqweqeqeqeq", 12);

    sz = wcsnlen_s(str2, LEN);

    rc = wcsncpy_s(str2, 2, str1, LEN);
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

