/*------------------------------------------------------------------
 * test_strpbrk_s
 *
 *
 *------------------------------------------------------------------
 */

#include "test_private.h"
#include "safe_str_lib.h"

#define LEN   ( 128 )
#define SHORT_LEN  ( 5 )

static char   str1[LEN];
static char   str2[LEN];

int test_strpbrk_s (void)
{
    errno_t rc;
    int errs = 0;
    char *first;
    char *std_first;

/*--------------------------------------------------*/

    rc = strpbrk_s(str1, LEN, str2, LEN, NULL);
    if (rc != ESNULLP) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    rc = strpbrk_s(NULL, LEN, str2, LEN, &first);
    if (rc != ESNULLP) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    if (first) {
        printf("%s %u  Error  first=%p  rc=%d \n",
                     __FUNCTION__, __LINE__, first, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    rc = strpbrk_s(str1, LEN, NULL, LEN, &first);
    if (rc != ESNULLP) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    if (first) {
        printf("%s %u  Error  first=%p  rc=%d \n",
                     __FUNCTION__, __LINE__, first, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    rc = strpbrk_s(str1, LEN, str2, LEN, NULL);
    if (rc != ESNULLP) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    rc = strpbrk_s(str1, 0, str2, LEN, &first);
    if (rc != ESZEROL) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    if (first) {
        printf("%s %u  Error  first=%p  rc=%d \n",
                     __FUNCTION__, __LINE__, first, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    rc = strpbrk_s(str1, RSIZE_MAX_STR+1, str2, LEN, &first);
    if (rc != ESLEMAX) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    if (first) {
        printf("%s %u  Error  first=%p  rc=%d \n",
                     __FUNCTION__, __LINE__, first, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    rc = strpbrk_s(str1, RSIZE_MAX_STR, str2, RSIZE_MAX_STR+1, &first);
    if (rc != ESLEMAX) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    if (first) {
        printf("%s %u  Error  first=%p  rc=%d \n",
                     __FUNCTION__, __LINE__, first, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    str1[0] = '\0';
    str2[0] = '\0';

    /* not to be found */
    rc = strpbrk_s(str1, LEN, str2, LEN, &first);
    if (rc != ESNOTFND) {
        printf("%s %u  Error  first=%p  rc=%d \n",
                     __FUNCTION__, __LINE__, first, rc);
        ++errs;
    }

    if (first) {
        printf("%s %u  Error  first=%p  rc=%d \n",
                     __FUNCTION__, __LINE__, first, rc);
        ++errs;
    }

    std_first = strpbrk(str1, str2);
    if (first != std_first) {
        printf("%s %u  first=%p  std_first=%p  rc=%d \n",
                     __FUNCTION__, __LINE__,  first, std_first, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy (str1, "keep it simple");
    strcpy (str2, "1234");

    rc = strpbrk_s(str1, 2, str2, LEN, &first);
    if (rc != ESNOTFND) {
        printf("%s %u  Error  first=%p  rc=%d \n",
                     __FUNCTION__, __LINE__, first, rc);
        ++errs;
    }

    std_first = strpbrk(str1, str2);
    if (first != std_first) {
        printf("%s %u  first=%p  std_first=%p  rc=%d \n",
                     __FUNCTION__, __LINE__,  first, std_first, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy (str1, "keep it simple");
    strcpy (str2, "ke");

    rc = strpbrk_s(str1, 2, str2, LEN, &first);
    if (rc != EOK) {
        printf("%s %u  Error  first=%p  rc=%d \n",
                     __FUNCTION__, __LINE__, first, rc);
        ++errs;
    }

    std_first = strpbrk(str1, str2);
    if (first != std_first) {
        printf("%s %u  first=%p  std_first=%p  rc=%d \n",
                     __FUNCTION__, __LINE__,  first, std_first, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy (str1, "keep it simplez");
    strcpy (str2, "z");

    rc = strpbrk_s(str1, LEN, str2, LEN, &first);
    if (rc != EOK) {
        printf("%s %u  Error  first=%p  rc=%d \n",
                     __FUNCTION__, __LINE__, first, rc);
        ++errs;
    }

    std_first = strpbrk(str1, str2);
    if (first != std_first) {
        printf("%s %u  first=%p  std_first=%p  rc=%d \n",
                     __FUNCTION__, __LINE__,  first, std_first, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy (str1, "keep it simple");
    strcpy (str2, "123456");

    rc = strpbrk_s(str1, LEN, str2, 2, &first);
    if (rc != ESNOTFND) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    if (first != 0) {
        printf("%s %u  Error  first=%p  rc=%d \n",
                     __FUNCTION__, __LINE__, first, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy (str1, "keep it simple");
    strcpy (str2, "");

    rc = strpbrk_s(str1, LEN, str2, 1, &first);
    if (rc != ESNOTFND) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    if (first != 0) {
        printf("%s %u  Error  first=%p  rc=%d \n",
                     __FUNCTION__, __LINE__, first, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy (str1, "keep it simple");
    strcpy (str2, "k");

    rc = strpbrk_s(str1, LEN, str2, 1, &first);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    std_first = strpbrk(str1, str2);
    if (first != std_first) {
        printf("%s %u  first=%p  std_first=%p  rc=%d \n",
                     __FUNCTION__, __LINE__,  first, std_first, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy (str1, "keep it simple");
    strcpy (str2, "ke");

    rc = strpbrk_s(str1, LEN, str2, 2, &first);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    std_first = strpbrk(str1, str2);
    if (first != std_first) {
        printf("%s %u  first=%p  std_first=%p  rc=%d \n",
                     __FUNCTION__, __LINE__,  first, std_first, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy (str1, "keep it simple");
    strcpy (str2, "hip");

    rc = strpbrk_s(str1, LEN, str2, LEN, &first);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    std_first = strpbrk(str1, str2);
    if (first != std_first) {
        printf("%s %u  first=%p  std_first=%p  rc=%d \n",
                     __FUNCTION__, __LINE__,  first, std_first, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy (str1, "keep it simply");
    strcpy (str2, "123y");

    rc = strpbrk_s(str1, LEN, str2, LEN, &first);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    std_first = strpbrk(str1, str2);
    if (first != std_first) {
        printf("%s %u  first=%p  std_first=%p  rc=%d \n",
                     __FUNCTION__, __LINE__,  first, std_first, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    return errs;
}
