/*------------------------------------------------------------------
 * test_strcat_s
 *
 *
 *------------------------------------------------------------------
 */

#include "test_private.h"
#include "safe_str_lib.h"

#define LEN   ( 128 )

static char   str1[LEN];
static char   str2[LEN];

int test_strcat_s (void)
{
    errno_t rc;
    int errs = 0;
    int32_t  ind;
    int32_t  len1;
    int32_t  len2;
    int32_t  len3;

/*--------------------------------------------------*/

    rc = strcat_s(NULL, LEN, str2);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

/*--------------------------------------------------*/

    rc = strcat_s(str1, LEN, NULL);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

/*--------------------------------------------------*/

    rc = strcat_s(str1, 0, str2);
    if (rc != ESZEROL) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

/*--------------------------------------------------*/

    rc = strcat_s(str1, (RSIZE_MAX_STR+1), str2);
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

/*--------------------------------------------------*/
/*--------------------------------------------------*/

    strcpy(str1, "aaaaaaaaaa");
    strcpy(str2, "keep it simple");

    rc = strcat_s(str1, 1, str2);
    if (rc != ESUNTERM) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

    if (str1[0] != '\0') {
        printf("%s %u  Expected null  \n",
               __FUNCTION__, __LINE__);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy(str1, "aaaaaaaaaa");
    strcpy(str2, "keep it simple");

    rc = strcat_s(str1, 2, str2);
    if (rc != ESUNTERM) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

    if (str1[0] != '\0') {
        printf("%s %u  Expected null  \n",
               __FUNCTION__, __LINE__);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy(&str1[0], "aaaaaaaaaa");
    strcpy(&str2[0], "keep it simple");

    len1 = strlen(str1);
    len2 = strlen(str2);

    rc = strcat_s(str1, 50, str2);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

    len3 = strlen(str1);
    if (len3 != (len1+len2)) {
        printf("%s %u lengths wrong: %u  %u  %u \n",
               __FUNCTION__, __LINE__, len1, len2, len3);
        ++errs;
    }

/*--------------------------------------------------*/
/*--------------------------------------------------*/

    str1[0] = '\0';
    strcpy(str2, "keep it simple");

    rc = strcat_s(str1, 1, str2);
    if (rc != ESNOSPC) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

    if (str1[0] != '\0') {
        printf("%s %u  Expected null  \n",
               __FUNCTION__, __LINE__);
        ++errs;
    }

/*--------------------------------------------------*/

    str1[0] = '\0';
    strcpy(str2, "keep it simple");

    rc = strcat_s(str1, 2, str2);
    if (rc != ESNOSPC) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

    if (str1[0] != '\0') {
        printf("%s %u  Expected null  \n",
               __FUNCTION__, __LINE__);
        ++errs;
    }

/*--------------------------------------------------*/

    str1[0] = '\0';
    strcpy(str2, "keep it simple");

    rc = strcat_s(str1, 20, str2);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

    ind = strcmp(str1, str2 );
    if (ind != 0) {
        printf("%s %u   Error -%s- \n",
               __FUNCTION__, __LINE__,  str1);
        ++errs;
    }

/*--------------------------------------------------*/
/*--------------------------------------------------*/

    str1[0] = '\0';
    str2[0] = '\0';

    rc = strcat_s(str1, LEN, str2);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

    if (str1[0] != '\0') {
        printf("%s %u  Expected null  \n",
               __FUNCTION__, __LINE__);
        ++errs;
    }

/*--------------------------------------------------*/

    str1[0] = '\0';
    strcpy(str2, "keep it simple");

    rc = strcat_s(str1, LEN, str2);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

    ind = strcmp(str1, str2);
    if (ind != 0) {
        printf("%s %u   Error -%s- \n",
               __FUNCTION__, __LINE__,  str1);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy(str1, "qqweqq");
    strcpy(str2, "keep it simple");

    rc = strcat_s(str1, LEN, str2);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

    ind = strcmp(str1, "qqweqqkeep it simple");
    if (ind != 0) {
        printf("%s %u   Error -%s- \n",
               __FUNCTION__, __LINE__,  str1);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy(str1, "1234");
    strcpy(str2, "keep it simple");

    rc = strcat_s(str1, 12, str2);
    if (rc != ESNOSPC) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy(str1, "1234");
    strcpy(str2, "keep it simple");

    rc = strcat_s(str1, 52, str2);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

    ind = strcmp(str1, "1234keep it simple");
    if (ind != 0) {
        printf("%s %u   Error -%s- \n",
               __FUNCTION__, __LINE__,  str1);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy(str1, "12345678901234567890");

    rc = strcat_s(str1, 8, &str1[7]);
    if (rc != ESOVRLP) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

    if (str1[0] != '\0') {
        printf("%s %u  Expected null  \n",
               __FUNCTION__, __LINE__);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy(str1, "123456789");

    rc = strcat_s(str1, 9, &str1[8]);
    if (rc != ESOVRLP) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

    if (str1[0] != '\0') {
        printf("%s %u  Expected null  \n",
               __FUNCTION__, __LINE__);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy(str2, "123");
    strcpy(str1, "keep it simple");

    rc = strcat_s(str2, 31, &str1[0]);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

    ind = strcmp(str2, "123keep it simple");
    if (ind != 0) {
        printf("%s %u   Error -%s- \n",
               __FUNCTION__, __LINE__,  str1);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy(str2, "1234");
    strcpy(str1, "56789");

    rc = strcat_s(str2, 10, str1);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

    ind = strcmp(str2, "123456789");
    if (ind != 0) {
        printf("%s %u   Error -%s- \n",
               __FUNCTION__, __LINE__,  str1);
        ++errs;
    }

/*--------------------------------------------------*/

    return errs;
}


