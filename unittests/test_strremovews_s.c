/*------------------------------------------------------------------
 * test_strremovews_s
 *
 *
 *------------------------------------------------------------------
 */

#include "test_private.h"
#include "safe_str_lib.h"

#define LEN   ( 128 )


int test_strremovews_s(void)
{
    errno_t rc;
    int errs = 0;
    int ind;

    uint32_t len;
    char   str[LEN];

/*--------------------------------------------------*/

    len = 5;
    rc = strremovews_s(NULL, len);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    len = 0;
    rc = strremovews_s("test", len);
    if (rc != ESZEROL) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    len = 99999;
    rc = strremovews_s("test", len);
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    strzero_s(str, LEN);
    strcpy (str, "ABCDEFGHIJK");
    len = 1;
    rc = strremovews_s(str, len);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

    if (str[0] != '\0') {
        printf("%s %u   Error -%s- \n",
                     __FUNCTION__, __LINE__,  str);
        ++errs;
    }

/*--------------------------------------------------*/

    strzero_s(str, LEN);
    strcpy (str, "ABCDEFGHIJK");
    len = 2;

    rc = strremovews_s(str, len);
    if (rc != ESUNTERM) {
        printf("%s %u   Error rc=%u --%s--\n",
                     __FUNCTION__, __LINE__,  rc, str );
        ++errs;
    }

/*--------------------------------------------------*/

    strzero_s(str, LEN);
    strcpy (str, "      ABCDEFGHIJK");
    len = 3;

    rc = strremovews_s(str, len);
    if (rc != ESUNTERM) {
        printf("%s %u   Error rc=%u --%s--\n",
                     __FUNCTION__, __LINE__,  rc, str );
        ++errs;
    }

    if (str[0] != '\0') {
        printf("%s %u   Error rc=%u --%s--\n",
                     __FUNCTION__, __LINE__,  rc, str );
        ++errs;
    }

/*--------------------------------------------------*/

    strzero_s(str, LEN);
    strcpy (str, "      ABCDEFGHIJK");
    len = 9;

    rc = strremovews_s(str, len);
    if (rc != ESUNTERM) {
        printf("%s %u   Error rc=%u --%s--\n",
                     __FUNCTION__, __LINE__,  rc, str );
        ++errs;
    }

/*--------------------------------------------------*/

    strzero_s(str, LEN);
    strcpy (str, "A");
    len = 1;

    /* a one char string will be emptied - str[0]=='\0' */
    rc = strremovews_s(str, len);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

    if (str[0] != '\0') {
        printf("%s %u   Error -%s- \n",
                     __FUNCTION__, __LINE__,  str);
        ++errs;
    }

/*--------------------------------------------------*/

    strzero_s(str, LEN);
    strcpy (str, "ABC");
    len = 8;

    rc = strremovews_s(str, len);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

    if (str[0] != 'A') {
        printf("%s %u   Error -%s- \n",
                     __FUNCTION__, __LINE__,  str);
        ++errs;
    }

/*--------------------------------------------------*/

    strzero_s(str, LEN);
    strcpy(str, "   B");
    len = strlen(str);

    rc = strremovews_s(str, len);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

    if (str[0] != 'B') {
        printf("%s %u   Error -%s- \n",
                     __FUNCTION__, __LINE__,  str);
        ++errs;
    }

/*--------------------------------------------------*/

    strzero_s(str, LEN);
    strcpy(str, "  C       ");
    len = strlen(str);

    rc = strremovews_s(str, len);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

    ind = strcmp(str, "C");
    if (ind != 0) {
        printf("%s %u   Error -%s- \n",
                     __FUNCTION__, __LINE__,  str);
        ++errs;
    }

/*--------------------------------------------------*/

    strzero_s(str, LEN);
    strcpy(str, "   NowISTHETimE 1 2   ");
    len = strlen(str);

    rc = strremovews_s(str, len);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

    ind = strcmp(str, "NowISTHETimE 1 2");
    if (ind != 0) {
        printf("%s %u   Error -%s- \n",
                     __FUNCTION__, __LINE__,  str);
        ++errs;
    }

/*--------------------------------------------------*/

    strzero_s(str, LEN);
    strcpy (str, "  q q21ego");
    len = strlen(str);

    rc = strremovews_s(str, len);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

    ind = strcmp(str, "q q21ego");
    if (ind != 0) {
        printf("%s %u   Error -%s- \n",
                     __FUNCTION__, __LINE__,  str);
        ++errs;
    }

/*--------------------------------------------------*/

    strzero_s(str, LEN);
    strcpy (str, "  1 2 3 4   ");
    len = strlen(str);

    rc = strremovews_s(str, len);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

    ind = strcmp(str, "1 2 3 4");
    if (ind != 0) {
        printf("%s %u   Error -%s- \n",
                     __FUNCTION__, __LINE__,  str);
        ++errs;
    }

/*--------------------------------------------------*/

    return errs;
}
