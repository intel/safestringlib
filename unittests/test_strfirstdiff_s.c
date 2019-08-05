/*------------------------------------------------------------------
 * test_strfirstdiff_s
 *
 *
 *------------------------------------------------------------------
 */

#include "test_private.h"
#include "safe_str_lib.h"

#define LEN   ( 128 )
#define SHORT_LEN  ( 5 )


int test_strfirstdiff_s()
{
    errno_t rc;
    rsize_t ind;

    char   str1[LEN];
    char   str2[LEN];

/*--------------------------------------------------*/

    rc = strfirstdiff_s(NULL, LEN, str2, &ind);
    if (rc != ESNULLP) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if (ind != 0) {
        printf("%s %u  Error  ind=%zu rc=%d \n",
                     __FUNCTION__, __LINE__, ind, rc);
    }

/*--------------------------------------------------*/

    rc = strfirstdiff_s(str1, LEN, NULL, &ind);
    if (rc != ESNULLP) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if (ind != 0) {
        printf("%s %u  Error  ind=%zu rc=%d \n",
                     __FUNCTION__, __LINE__, ind, rc);
    }

/*--------------------------------------------------*/

    rc = strfirstdiff_s(str1, LEN, str2, NULL);
    if (rc != ESNULLP) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

/*--------------------------------------------------*/

    rc = strfirstdiff_s(str1, 0, str2, &ind);
    if (rc != ESZEROL) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if (ind != 0) {
        printf("%s %u  Error  ind=%zu rc=%d \n",
                     __FUNCTION__, __LINE__, ind, rc);
    }

/*--------------------------------------------------*/

    rc = strfirstdiff_s(str1, RSIZE_MAX_STR+1, str2, &ind);
    if (rc != ESLEMAX) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if (ind != 0) {
        printf("%s %u  Error  ind=%zu rc=%d \n",
                     __FUNCTION__, __LINE__, ind, rc);
    }

/*--------------------------------------------------*/

    str1[0] = '\0';
    str2[0] = '\0';

    rc = strfirstdiff_s(str1, LEN, str2, &ind);
    if (rc != ESNODIFF) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if (ind != 0) {
        printf("%s %u  Error  ind=%zu rc=%d \n",
                     __FUNCTION__, __LINE__, ind, rc);
    }

/*--------------------------------------------------*/

    strcpy (str1, "Keep it simple");
    strcpy (str2, "keep it simple");

    rc = strfirstdiff_s(str1, LEN, str2, &ind);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if (ind != 0) {
        printf("%s %u  Error ind=%zu  rc=%d \n",
                     __FUNCTION__, __LINE__,  ind, rc);
    }

/*--------------------------------------------------*/

    strcpy (str1, "kEeP it simple");
    strcpy (str2, "keep it simple");

    rc = strfirstdiff_s(str1, LEN, str2, &ind);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if (ind != 1) {
        printf("%s %u  Error ind=%zu  rc=%d \n",
                     __FUNCTION__, __LINE__,  ind, rc);
    }

/*--------------------------------------------------*/

    strcpy (str1, "keep it simple");
    strcpy (str2, "keEp IT simple");

    rc = strfirstdiff_s(str1, LEN, str2, &ind);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if (ind != 2) {
        printf("%s %u  Error ind=%zu  rc=%d \n",
                     __FUNCTION__, __LINE__,  ind, rc);
    }

/*--------------------------------------------------*/

    strcpy (str1, "keep it simple");

    rc = strfirstdiff_s(str1, LEN, str1, &ind);
    if (rc != ESNODIFF) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if (ind != 0) {
        printf("%s %u  Error ind=%zu  rc=%d \n",
                     __FUNCTION__, __LINE__,  ind, rc);
    }

/*--------------------------------------------------*/

    strcpy (str1, "keep it simple");
    strcpy (str2, "keep it simple");

    rc = strfirstdiff_s(str1, 1, str2, &ind);
    if (rc != ESNODIFF) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if (ind != 0) {
        printf("%s %u  Error ind=%zu  rc=%d \n",
                     __FUNCTION__, __LINE__,  ind, rc);
    }

/*--------------------------------------------------*/

    strcpy (str1, "keep it simplE");
    strcpy (str2, "keep it simple");

    rc = strfirstdiff_s(str1, 13, str2, &ind);
    if (rc != ESNODIFF) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if (ind != 0) {
        printf("%s %u  Error ind=%zu  rc=%d \n",
                     __FUNCTION__, __LINE__,  ind, rc);
    }

/*--------------------------------------------------*/

    strcpy (str1, "keep it simplE");
    strcpy (str2, "keep it simple");

    rc = strfirstdiff_s(str1, 14, str2, &ind);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if (ind != 13) {
        printf("%s %u  Error ind=%zu  rc=%d \n",
                     __FUNCTION__, __LINE__,  ind, rc);
    }

/*--------------------------------------------------*/

    strcpy (str1, "keep it simplE");
    strcpy (str2, "keep it simple");

    rc = strfirstdiff_s(str1, 55, str2, &ind);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if (ind != 13) {
        printf("%s %u  Error ind=%zu  rc=%d \n",
                     __FUNCTION__, __LINE__,  ind, rc);
    }

/*--------------------------------------------------*/

    return (0);
}
