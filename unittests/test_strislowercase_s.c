/*------------------------------------------------------------------
 * test_strislowercase_s
 *
 *
 *------------------------------------------------------------------
 */

#include "test_private.h"
#include "safe_str_lib.h"

#define LEN   ( 128 )


int test_strislowercase_s(void)
{
    bool rc;
    int errs = 0;
    uint32_t len;
    char   str[LEN];

/*--------------------------------------------------*/

    len = 5;
    rc = strislowercase_s(NULL, len);
    if (rc != false) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    len = 99999;
    rc = strislowercase_s("test", len);
    if (rc != false) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    len = 0;
    rc = strislowercase_s("test", len);
    if (rc != false) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    str[0] = '\0';
    rc = strislowercase_s(str, 5);
    if (rc != false) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy (str, "qqweqeqeqeq");
    len = 3;

    rc = strislowercase_s(str, len);
    if (rc != true) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy (str, "qqweqeqeqeq");
    len = strlen(str);

    rc = strislowercase_s(str, len);
    if (rc != true) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy (str, "qqWe go");
    len = strlen(str);

    rc = strislowercase_s(str, len);
    if (rc != false) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy (str, "1234");
    len = strlen(str);

    rc = strislowercase_s(str, len);
    if (rc != false) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    return errs;
}
