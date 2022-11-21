/*  SPDX-License-Identifier: MIT */
/*
*  Copyright (c) 2014-2022 Intel Corp
*/
/*------------------------------------------------------------------
 * test_strisdigit_s
 *
 *------------------------------------------------------------------
 */

#include "test_private.h"
#include "safe_str_lib.h"

#define LEN   ( 128 )


int test_strisdigit_s(void)
{
    bool rc;

    rsize_t len;
    char str[LEN];
    unsigned int testno = 0;
    unsigned int err = 0;


    printf("\nTesting strisdigit_s:\n");

/*--------------------------------------------------*/

/* 1: Test for first parameter, char string, being sent in as NULL */
    printf("Test #%d:\n", ++testno);

    len = 5;
    rc = strisdigit_s(NULL, len);
    if (rc != false) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
	err++;
    }

/*--------------------------------------------------*/

    printf("Test #%d:\n", ++testno);

    len = 0;
    rc = strisdigit_s("1234", len);
    if (rc != false) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
	err++;
    }

/*--------------------------------------------------*/

    printf("Test #%d:\n", ++testno);

    len = 99999;
    rc = strisdigit_s("1234", len);
    if (rc != false) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
	err++;
    }

/*--------------------------------------------------*/

    printf("Test #%d:\n", ++testno);

    len = 9;
    rc = strisdigit_s("", len);
    if (rc != false) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
	err++;
    }

/*--------------------------------------------------*/

    printf("Test #%d:\n", ++testno);

    strcpy(str, "123456789");
    len = 4;

    rc = strisdigit_s(str, len);
    if (rc != true) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
	err++;
    }

/*--------------------------------------------------*/

    printf("Test #%d:\n", ++testno);

    strcpy(str, "1");
    len = strlen(str);

    rc = strisdigit_s(str, len);
    if (rc != true) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
	err++;
    }

/*--------------------------------------------------*/

    printf("Test #%d:\n", ++testno);

    strcpy(str, "12");
    len = strlen(str);

    rc = strisdigit_s(str, len);
    if (rc != true) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
	err++;
    }

/*--------------------------------------------------*/

    printf("Test #%d:\n", ++testno);

    strcpy(str, "1abcd");
    len = strlen(str);

    rc = strisdigit_s(str, len);
    if (rc != false) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
    }

/*--------------------------------------------------*/

    printf("Test #%d:\n", ++testno);

    strcpy(str, "abcd");
    len = strlen(str);

    rc = strisdigit_s(str, len);
    if (rc != false) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
	err++;
    }

/*--------------------------------------------------*/

/*  Test for non terminated string */
    printf("Test #%d:\n", ++testno);

    memset(str, '6', LEN);
    len = LEN - 3;

    rc = strisdigit_s(str, len);
    if (rc != true) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
	err++;
    }

    return  (err == 0) ? 0 : 1;
}
