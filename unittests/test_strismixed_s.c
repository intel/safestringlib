/*  SPDX-License-Identifier: MIT */
/*
*  Copyright (c) 2014 by Intel Corp
/*------------------------------------------------------------------
 * test_strismixed_s
 *
 *
 *------------------------------------------------------------------
 */

#include "test_private.h"
#include "safe_str_lib.h"

#define LEN   ( 128 )


int test_strismixed_s(void)
{
    bool rc;
    rsize_t len;
    char str[LEN];
    unsigned int testno = 0;


    printf("\nTesting strisdigit_s:\n");

/*--------------------------------------------------*/

/* 1: Test for first parameter, char string, being sent in as NULL */
    printf("Test #%d:\n", ++testno);

    len = 5;
    rc = strismixedcase_s(NULL, len);
    if (rc != false) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

/*--------------------------------------------------*/

    printf("Test #%d:\n", ++testno);

    len = 0;
    rc = strismixedcase_s("test", len);
    if (rc != false) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

/*--------------------------------------------------*/

    printf("Test #%d:\n", ++testno);

    len = RSIZE_MAX_STR+1;
    rc = strismixedcase_s("test", len);
    if (rc != false) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

/*--------------------------------------------------*/

    printf("Test #%d:\n", ++testno);

    len = 9;
    rc = strismixedcase_s("", len);
    if (rc != false) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

/*--------------------------------------------------*/

    printf("Test #%d:\n", ++testno);

    strcpy(str, "AaBbCcDdEeFf");
    len = 5;

    rc = strismixedcase_s(str, len);
    if (rc != true) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

/*--------------------------------------------------*/

    printf("Test #%d:\n", ++testno);

    strcpy(str, "N");
    len = strlen(str);

    rc = strismixedcase_s(str, len);
    if (rc != true) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

/*--------------------------------------------------*/

    printf("Test #%d:\n", ++testno);

    strcpy(str, "NowISTHETimE");
    len = strlen(str);

    rc = strismixedcase_s(str, len);
    if (rc != true) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

/*--------------------------------------------------*/

    printf("Test #%d:\n", ++testno);

    strcpy(str, "qq21ego");
    len = strlen(str);

    rc = strismixedcase_s(str, len);
    if (rc != false) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

/*--------------------------------------------------*/

    printf("Test #%d:\n", ++testno);

    strcpy(str, "1234");
    len = strlen(str);

    rc = strismixedcase_s(str, len);
    if (rc != false) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

/*--------------------------------------------------*/

    return (0);
}
