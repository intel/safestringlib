/*------------------------------------------------------------------
 * test_strisalphanumeric_s.c
 *
 *
 *------------------------------------------------------------------
 */


#include "test_private.h"
#include "safe_str_lib.h"

#define LEN   ( 128 )


int test_strisalphanumeric_s(void)
{
    bool rc;
    int errs = 0;

    uint32_t len;
    char   str[LEN];

/*--------------------------------------------------*/

    len = 5;
    rc = strisalphanumeric_s(NULL, len);
    if (rc != false) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    len = 0;
    rc = strisalphanumeric_s("test", len);
    if (rc != false) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    /* exceeds max */
    len = 99999;
    rc = strisalphanumeric_s("test", len);
    if (rc != false) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    /* empty string */
    rc = strisalphanumeric_s("", LEN);
    if (rc != false) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy(str, "123456789");
    len = 4;

    rc = strisalphanumeric_s(str, len);
    if (rc != true) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy(str, "N");

    rc = strisalphanumeric_s(str, 1);
    if (rc != true) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy(str, "N");
    len = strlen(str);

    rc = strisalphanumeric_s(str, len);
    if (rc != true) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy(str, "NowISTHETimE4us");
    len = strlen(str);

    rc = strisalphanumeric_s(str, len);
    if (rc != true) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy(str, "qq21ego");
    len = strlen(str);

    rc = strisalphanumeric_s(str, len);
    if (rc != true) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy(str, "1234");
    str[2] = 132;          /* special char */
    len = strlen(str);

    /* special char embedded */
    rc = strisalphanumeric_s(str, len);
    if (rc != false) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy(str, "!@#$%^&*(){}[]:;\"'?/.>,<");
    len = strlen(str);

    rc = strisalphanumeric_s(str, len);
    if (rc != false) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    return errs;
}
