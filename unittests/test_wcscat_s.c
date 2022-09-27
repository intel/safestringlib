/*  SPDX-License-Identifier: MIT */
/*
 *  Copyright (c) 2014 by Intel Corp
 */

#include "test_private.h"
#include "safe_str_lib.h"

#define LEN   ( 128 )

static wchar_t   str1[LEN];
static wchar_t   str2[LEN];

extern rsize_t wcsnlen_s(const wchar_t *dest, rsize_t dmax);
extern errno_t wcscpy_s(wchar_t* dest, rsize_t dmax, const wchar_t* src);
extern errno_t wcscat_s(wchar_t* dest, rsize_t dmax, const wchar_t* src);

int test_wcscat_s (void)
{
    errno_t rc;
    int32_t  ind;
    int32_t  len1;
    int32_t  len2;
    int32_t  len3;
    unsigned int testno = 0;


    printf("\nTesting wcscat_s:\n");
/*--------------------------------------------------*/
/* 1  Test for NULL destination check                  */
    printf("Test #%d:\n", ++testno);

    rc = wcscat_s(NULL, LEN, str2);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

/*--------------------------------------------------*/
/* 2  Test for NULL source check                  */
    printf("Test #%d:\n", ++testno);

    rc = wcscat_s(str1, LEN, NULL);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

/*--------------------------------------------------*/
/* 3   Test zero maximum length of destination */
    printf("Test #%d:\n", ++testno);

    rc = wcscat_s(str1, 0, str2);
    if (rc != ESZEROL) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

/*--------------------------------------------------*/
/* 4  Test  Exceed Maximum size of destination     */
    printf("Test #%d:\n", ++testno);

    rc = wcscat_s(str1, (RSIZE_MAX_STR+1), str2);
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

/*--------------------------------------------------*/
/*--------------------------------------------------*/
/* 5   Test overlapping destination string into the beginning of the src */
    printf("Test #%d:\n", ++testno);

    wcscpy_s(str1, LEN, L"12345678901234567890");

    rc = wcscat_s(str1, 8, &str1[7]);
    if (rc != ESOVRLP) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

    if (str1[0] != L'\0') {
        printf("%s %u  Expected null  \n",
                     __FUNCTION__, __LINE__);
    }

/*--------------------------------------------------*/
/* 6   Test too small size - destination appears unterminated */
    printf("Test #%d:\n", ++testno);

    wcscpy_s(str1, LEN, L"aaaaaaaaaa");
    wcscpy_s(str2, LEN, L"keep it simple");

    rc = wcscat_s(str1, 1, str2);
    if (rc != ESUNTERM) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

    if (str1[0] != L'\0') {
        printf("%s %u  Expected null  \n",
                     __FUNCTION__, __LINE__);
    }

/*--------------------------------------------------*/
/* 7   Test length of destination appears unterminated */
    printf("Test #%d:\n", ++testno);

    wcscpy_s(str1, LEN, L"aaaaaaaaaa");
    wcscpy_s(str2, LEN, L"keep it simple");

    rc = wcscat_s(str1, 10, str2);
    if (rc != ESUNTERM) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

    if (str1[0] != L'\0') {
        printf("%s %u  Expected null  \n",
                     __FUNCTION__, __LINE__);
    }

/*--------------------------------------------------*/
/* 8   Test overlap of destination buffer into source after copying begins */
    printf("Test #%d:\n", ++testno);

    wcscpy_s(str1, LEN, L"keep it simple");
    wcscpy_s(&str1[20], LEN, L"aaaaaaaaaaaaaaaaaaaa");

    rc = wcscat_s(str1, 30, &str1[20]);
    if (rc != ESOVRLP) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

    if (str1[0] != L'\0') {
        printf("%s %u  Expected null  \n",
                     __FUNCTION__, __LINE__);
    }

/*--------------------------------------------------*/
/* 9   Test Verify proper size of concatenated strings */
    printf("Test #%d:\n", ++testno);

    wcscpy_s(&str1[0], LEN, L"aaaaaaaaaa");
    wcscpy_s(&str2[0], LEN, L"keep it simple");

    len1 = wcsnlen_s(str1, LEN);
    len2 = wcsnlen_s(str2, LEN);

    rc = wcscat_s(str1, 50, str2);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

    len3 = wcsnlen_s(str1, LEN);
    if (len3 != (len1+len2)) {
        printf("%s %u lengths wrong: %u  %u  %u \n",
                     __FUNCTION__, __LINE__, len1, len2, len3);
    }

/*--------------------------------------------------*/
/*--------------------------------------------------*/
/* 10   Test NULL string is destination  - too short */
    printf("Test #%d:\n", ++testno);

    str1[0] = '\0';
    wcscpy_s(str2, LEN, L"keep it simple");

    rc = wcscat_s(str1, 1, str2);
    if (rc != ESNOSPC) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

    if (str1[0] != L'\0') {
        printf("%s %u  Expected null  \n",
                     __FUNCTION__, __LINE__);
    }

/*--------------------------------------------------*/
/* 11   Test NULL string is destination  - too short */
    printf("Test #%d:\n", ++testno);

    str1[0] = '\0';
    wcscpy_s(str2, LEN, L"keep it simple");

    rc = wcscat_s(str1, 11, str2);
    if (rc != ESNOSPC) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

    if (str1[0] != L'\0') {
        printf("%s %u  Expected null  \n",
                     __FUNCTION__, __LINE__);
    }

/*--------------------------------------------------*/
/* 12   Test NULL string is destination  - proper result */
    printf("Test #%d:\n", ++testno);

    str1[0] = '\0';
    wcscpy_s(str2, LEN, L"keep it simple");

    rc = wcscat_s(str1, 20, str2);
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
/* 13   Test concat two NULL strings */
    printf("Test #%d:\n", ++testno);

    str1[0] = '\0';
    str2[0] = '\0';

    rc = wcscat_s(str1, LEN, str2);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

    if (str1[0] != L'\0') {
        printf("%s %u  Expected null  \n",
                     __FUNCTION__, __LINE__);
    }

/*--------------------------------------------------*/
/* 14   Test concat NULL string to existing string  - proper result */
    printf("Test #%d:\n", ++testno);

    str1[0] = '\0';
    wcscpy_s(str2, LEN, L"keep it simple");

    rc = wcscat_s(str2, LEN, str1);
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
/* 15   Test concat two strings  - proper result */
    printf("Test #%d:\n", ++testno);

    wcscpy_s(str1, LEN, L"qqweqq");
    wcscpy_s(str2, LEN, L"keep it simple");

    rc = wcscat_s(str1, LEN, str2);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

    rc = memcmp_s(str1, LEN, L"qqweqqkeep it simple", (20)*sizeof(wchar_t), &ind );
    if (ind != 0) {
        printf("%s %u   Error -%ls- \n",
                     __FUNCTION__, __LINE__,  str1);
    }

/*--------------------------------------------------*/
/* 16   Test concat two strings  - not enough space in dest */
    printf("Test #%d:\n", ++testno);

    wcscpy_s(str1, LEN, L"1234");
    wcscpy_s(str2, LEN, L"keep it simple");

    rc = wcscat_s(str2, 16, str1);
    if (rc != ESNOSPC) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

/*--------------------------------------------------*/
/* 17   Test concat two strings  - just enough space in the destination */
    printf("Test #%d:\n", ++testno);

    wcscpy_s(str1, LEN, L"1234");
    wcscpy_s(str2, LEN, L"keep it simple");

    rc = wcscat_s(str2, 19, str1);
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
/* 18   Test source overlaps into the dest string after copying begins */
    printf("Test #%d:\n", ++testno);

    wcscpy_s(str1, LEN, L"123456789123456789");
    wcscpy_s(&str1[13], LEN, L"ABCDEFGHIJKLMNOP123456789");

    rc = wcscat_s(&str1[13], LEN, str1);
    if (rc != ESOVRLP) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

    if (str1[13] != L'\0') {
        printf("%s %u  Expected null  \n",
                     __FUNCTION__, __LINE__);
    }

/*--------------------------------------------------*/
/* 19   Test normal string concat  */
    printf("Test #%d:\n", ++testno);

    wcscpy_s(str2, LEN, L"123");
    wcscpy_s(str1, LEN, L"keep it simple");

    rc = wcscat_s(str2, 31, &str1[0]);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

    rc = memcmp_s(str2, LEN, L"123keep it simple", (17)*sizeof(wchar_t), &ind );
    if (ind != 0) {
        printf("%s %u   Error -%ls- \n",
                     __FUNCTION__, __LINE__,  str1);
    }

/*--------------------------------------------------*/
/* 20   Test normal string concat - just enough room */
    printf("Test #%d:\n", ++testno);

    wcscpy_s(str2, LEN, L"1234");
    wcscpy_s(str1, LEN, L"56789");

    rc = wcscat_s(str2, 10, str1);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

    rc = memcmp_s(str2, LEN, L"123456789", (9)*sizeof(wchar_t), &ind );

    if (ind != 0) {
        printf("%s %u   Error -%ls- \n",
                     __FUNCTION__, __LINE__,  str1);
    }

/*--------------------------------------------------*/
/* 21   Test normal string concat - not enough room for NULL */
    printf("Test #%d:\n", ++testno);

    wcscpy_s(str2, LEN, L"1234");
    wcscpy_s(str1, LEN, L"56789");

    rc = wcscat_s(str2, 9, str1);
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


