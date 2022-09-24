/*------------------------------------------------------------------
 * test_strcpyfldout_s
 *
 *
 *------------------------------------------------------------------
 */

#include "test_private.h"
#include "safe_str_lib.h"

#define MAX   ( 128 )
#define LEN   ( 128 )

int test_strcpyfldout_s(void)
{
    errno_t rc;
    int errs = 0;
    uint32_t i;
    rsize_t len;
    rsize_t slen;

    char   str1[LEN];
    char   str2[LEN];


/*--------------------------------------------------*/

    slen = sizeof(str2);
    rc = strcpyfldout_s(NULL, LEN, str2, slen);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    len = 5;
    rc = strcpyfldout_s(str1, len, NULL, len);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

    for (i=0; i<len; i++) {
        if (str1[i] != '\0') {
            printf("%s %u   Error rc=%u \n",
                   __FUNCTION__, __LINE__,  rc );
            ++errs;
        }
    }

/*--------------------------------------------------*/

    rc = strcpyfldout_s(str1, 0, str2, LEN);
    if (rc != ESZEROL) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    rc = strcpyfldout_s(str1, (RSIZE_MAX_STR+1), str2, LEN);
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    len = 5;
    slen = 0;
    rc = strcpyfldout_s(str1, len, str2, slen);
    if (rc != ESZEROL) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    len = 5;
    slen = 6;
    rc = strcpyfldout_s(str1, len, str2, slen);
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/
/*--------------------------------------------------*/

    strcpy(str1, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    strcpy(str2, "01234567890123456789");

    len = 1;
    slen = 1;
    rc = strcpyfldout_s(str1, len, str2, slen);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

    /* str1 becomes null */
    for (i=0; i<len; i++) {
        if (str1[i] != '\0') {
            printf("%s %u  diff s1[%d]=%d  s2[%d]=%d  rc=%u \n",
                   __FUNCTION__, __LINE__, i, str1[i], i, str2[i], rc);
            ++errs;
        }
    }

/*--------------------------------------------------*/

    strcpy(str1, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    strcpy(str2, "01234567890123456789");

    len = 2;
    slen = 2;
    rc = strcpyfldout_s(str1, len, str2, slen);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

    for (i=0; i<len-1; i++) {
        if (str1[i] != str2[i]) {
            printf("%s %u  diff s1[%d]=%d  s2[%d]=%d  rc=%u \n",
                   __FUNCTION__, __LINE__, i, str1[i], i, str2[i], rc);
            ++errs;
        }
    }

/*--------------------------------------------------*/

    strcpy(str1, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    strcpy(str2, "01234567890123456789");

    len = 3;
    slen = 3;
    rc = strcpyfldout_s(str1, len, str2, slen);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

    for (i=0; i<len-1; i++) {
        if (str1[i] != str2[i]) {
            printf("%s %u  diff s1[%d]=%d  s2[%d]=%d  rc=%u \n",
                   __FUNCTION__, __LINE__, i, str1[i], i, str2[i], rc);
            ++errs;
        }
    }


/*--------------------------------------------------*/

    strcpy(str1, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

    /* same string in dest and src */
    len = LEN;
    rc = strcpyfldout_s(str1, len, str1, len);
    if (rc != ESOVRLP) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

    for (i=0; i<len; i++) {
        if (str1[i] != '\0') {
            printf("%s %u  diff s1[%d]=%d  s2[%d]=%d  rc=%u \n",
                   __FUNCTION__, __LINE__, i, str1[i], i, str2[i], rc);
            ++errs;
        }
    }

/*--------------------------------------------------*/

    strcpy(str1, "keep it simple for best results");
    len = strlen(str1);

    /* overlap */
    rc = strcpyfldout_s(&str1[0], len, &str1[5], len);
    if (rc != ESOVRLP) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

    for (i=0; i<len; i++) {
        if (str1[i] != '\0') {
            printf("%s %u  diff s1[%d]=%d  s2[%d]=%d  rc=%u \n",
                   __FUNCTION__, __LINE__, i, str1[i], i, str2[i], rc);
            ++errs;
        }
    }

/*--------------------------------------------------*/

    strcpy(str1, "keep it simple for best results ");
    len = 20;

    /* overlap */
    rc = strcpyfldout_s(&str1[10], len, &str1[0], len);
    if (rc != ESOVRLP) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

    for (i=10; i<len; i++) {
        if (str1[i] != '\0') {
            printf("%s %u  diff s1[%d]=%d  s2[%d]=%d  rc=%u \n",
                   __FUNCTION__, __LINE__, i, str1[i], i, str2[i], rc);
            ++errs;
        }
    }

/*--------------------------------------------------*/

    strcpy(str1, "keep it simple");
    len = strlen(str1);

    strcpy(str2, "aaaaaaaaaaaaaa");
    slen = strlen(str2);

    rc = strcpyfldout_s(str1, len, str2, slen);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

    for (i=0; i<len-1; i++) {
        if (str1[i] != str2[i]) {
            printf("%s %u  diff s1[%d]=%d  s2[%d]=%d  rc=%u \n",
                   __FUNCTION__, __LINE__, i, str1[i], i, str2[i], rc);
            ++errs;
        }
    }

/*--------------------------------------------------*/

    strcpy(str1, "always keep it simple");
    len = strlen(str1);

    strcpy(str2, "keep it simple");
    slen = strlen(str2);

    rc = strcpyfldout_s(str1, len, str2, slen);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

    for (i=0; i<slen; i++) {
        if (str1[i] != str2[i]) {
            printf("%s %u  diff s1[%d]=%d  s2[%d]=%d  rc=%u \n",
                   __FUNCTION__, __LINE__, i, str1[i], i, str2[i], rc);
            ++errs;
        }
    }

/*--------------------------------------------------*/

    return errs;
}
