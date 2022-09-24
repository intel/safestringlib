/*------------------------------------------------------------------
 * test_strcasecmp_s
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

int test_strcasecmp_s (void)
{
    errno_t rc;
    int errs = 0;

    int ind;
    int std_ind;

/*--------------------------------------------------*/

    rc = strcasecmp_s(NULL, LEN, str2, &ind);
    if (rc != ESNULLP) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    if (ind != 0) {
        printf("%s %u  Error  ind=%d rc=%d \n",
                     __FUNCTION__, __LINE__, ind, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    rc = strcasecmp_s(str1, LEN, NULL, &ind);
    if (rc != ESNULLP) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    if (ind != 0) {
        printf("%s %u  Error  ind=%d rc=%d \n",
                     __FUNCTION__, __LINE__, ind, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    rc = strcasecmp_s(str1, LEN, str2, NULL);
    if (rc != ESNULLP) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    rc = strcasecmp_s(str1, 0, str2, &ind);
    if (rc != ESZEROL) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    if (ind != 0) {
        printf("%s %u  Error  ind=%d rc=%d \n",
                     __FUNCTION__, __LINE__, ind, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    rc = strcasecmp_s(str1, RSIZE_MAX_STR+1, str2, &ind);
    if (rc != ESLEMAX) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    if (ind != 0) {
        printf("%s %u  Error  ind=%d rc=%d \n",
                     __FUNCTION__, __LINE__, ind, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    str1[0] = '\0';
    str2[0] = '\0';

    rc = strcasecmp_s(str1, LEN, str2, &ind);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    if (ind != 0) {
        printf("%s %u  Error  ind=%d rc=%d \n",
                     __FUNCTION__, __LINE__, ind, rc);
        ++errs;
    }

    std_ind = strcasecmp(str1, str2);
    if (ind != std_ind) {
        printf("%s %u  ind=%d  std_ind=%d  rc=%d \n",
                     __FUNCTION__, __LINE__,  ind, std_ind, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy (str1, "KEEP IT SIMPLE");
    strcpy (str2, "keep it simple");

    rc = strcasecmp_s(str1, 1, str2, &ind);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    if (ind != 0) {
        printf("%s %u  Error  ind=%d rc=%d \n",
                     __FUNCTION__, __LINE__, ind, rc);
        ++errs;
    }
/*--------------------------------------------------*/

    strcpy (str1, "KEEP IT SIMPLE");
    strcpy (str2, "keep it simple");

    rc = strcasecmp_s(str1, 2, str2, &ind);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    if (ind != 0) {
        printf("%s %u  Error  ind=%d rc=%d \n",
                     __FUNCTION__, __LINE__, ind, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy (str1, "KEEP IT SIMPLE");
    strcpy (str2, "keep it simple");

    rc = strcasecmp_s(str1, 4, str2, &ind);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    if (ind != 0) {
        printf("%s %u  Error  ind=%d rc=%d \n",
                     __FUNCTION__, __LINE__, ind, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy (str1, "KEEP IT SIMPLE");
    strcpy (str2, "keep it simple");

    rc = strcasecmp_s(str1, LEN, str2, &ind);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    if (ind != 0) {
        printf("%s %u  Error ind=%d  rc=%d \n",
                     __FUNCTION__, __LINE__,  ind, rc);
        ++errs;
    }

    std_ind = strcasecmp(str1, str2);
    if (ind != std_ind) {
        printf("%s %u  ind=%d  std_ind=%d  rc=%d \n",
                     __FUNCTION__, __LINE__,  ind, std_ind, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy (str1, "keep it simple");
    strcpy (str2, "keeP it simple");

    rc = strcasecmp_s(str1, LEN, str2, &ind);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    if (ind != 0) {
        printf("%s %u  Error ind=%d  rc=%d \n",
                     __FUNCTION__, __LINE__,  ind, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy (str1, "keep it simple");

    rc = strcasecmp_s(str1, LEN, str1, &ind);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    if (ind != 0) {
        printf("%s %u  Error ind=%d  rc=%d \n",
                     __FUNCTION__, __LINE__,  ind, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy (str1, "KEEP it simplified");
    strcpy (str2, "keep it simple");

    rc = strcasecmp_s(str1, LEN, str2, &ind);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    if (ind != ('I' - 'E')) {
        printf("%s %u  Error ind=%d  rc=%d \n",
                     __FUNCTION__, __LINE__,  ind, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy (str1, "KEEP 1234567890");
    strcpy (str2, "keep it simple");

    rc = strcasecmp_s(str1, LEN, str2, &ind);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    if (ind != ('1' - 'I')) {
        printf("%s %u  Error ind=%d  rc=%d  %d \n",
                     __FUNCTION__, __LINE__,  ind, rc, ('1' - 'I'));
        ++errs;
    }

/*--------------------------------------------------*/

    return errs;
}

