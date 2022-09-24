/*------------------------------------------------------------------
 * test_strncpy_s
 *
 *
 *------------------------------------------------------------------
 */

#include "test_private.h"
#include "safe_str_lib.h"

#define MAX   ( 128 )
#define LEN   ( 128 )

static char   str1[LEN];
static char   str2[LEN];
static char   dest[LEN];

int test_strncpy_s (void)
{
    errno_t rc;
    int errs = 0;
    rsize_t nlen;
    int32_t ind;

/*--------------------------------------------------*/

    nlen = 5;
    rc = strncpy_s(NULL, LEN, str2, nlen);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy(str1, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

    nlen = 5;
    rc = strncpy_s(str1, 5, NULL, nlen);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

        if (str1[0] != '\0') {
            printf("%s %u   Error rc=%u \n",
                   __FUNCTION__, __LINE__,  rc );
            ++errs;
        }

/*--------------------------------------------------*/

    nlen = 5;
    rc = strncpy_s(str1, 0, str2, nlen);
    if (rc != ESZEROL) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    rc = strncpy_s(str1, (RSIZE_MAX_STR+1), str2, nlen);
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/
/*--------------------------------------------------*/

    strcpy(str1, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    str2[0] = '\0';

    rc = strncpy_s(str1, 5, str2, 0);
    if (rc != ESZEROL) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

        if (str1[0] != '\0') {
            printf("%s %u   Error rc=%u \n",
                   __FUNCTION__, __LINE__,  rc );
            ++errs;
        }

/*--------------------------------------------------*/

#if 1
   strcpy(str1, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
   strcpy(str2, "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");

    rc = strncpy_s(str1, 5, str2, (RSIZE_MAX_STR+1));
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }
#endif

/*--------------------------------------------------*/

    strcpy(str1, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    str2[0] = '\0';
    nlen = 5;

    rc = strncpy_s(&str1[0], LEN/2, &str2[0], nlen);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

        if (str1[0] != '\0') {
            printf("%s %u   Error rc=%u \n",
                   __FUNCTION__, __LINE__,  rc );
            ++errs;
        }

/*--------------------------------------------------*/

    strcpy(str1, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    nlen = 5;

    /* test overlap */
    rc = strncpy_s(str1, LEN, str1, nlen);
    if (rc != ESOVRLP) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

        if (str1[0] != '\0') {
            printf("%s %u   Error rc=%u \n",
                   __FUNCTION__, __LINE__,  rc );
            ++errs;
        }

/*--------------------------------------------------*/

    strcpy(str1, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    nlen = 18;

    rc = strncpy_s(&str1[0], LEN, &str1[5], nlen);
    if (rc != ESOVRLP) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

        if (str1[0] != '\0') {
            printf("%s %u   Error rc=%u \n",
                   __FUNCTION__, __LINE__,  rc );
            ++errs;
        }

/*--------------------------------------------------*/

    strcpy(str1, "keep it simple");
    str2[0] = '\0';

    nlen = 10;
    rc = strncpy_s(str1, LEN, str2, nlen);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

        if (str1[0] != '\0') {
            printf("%s %u   Error rc=%u \n",
                   __FUNCTION__, __LINE__,  rc );
            ++errs;
        }

/*--------------------------------------------------*/

    str1[0] = '\0';
    strcpy(str2, "keep it simple");

    nlen = 20;
    rc = strncpy_s(str1, LEN, str2, nlen);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

    /* be sure the results are the same as strcmp */
    ind = strcmp(str1, str2);
    if (ind != 0) {
        printf("%s %u -%s-  Error rc=%u \n",
               __FUNCTION__, __LINE__,  str1, rc );
        ++errs;
    }


/*--------------------------------------------------*/

    strcpy(str1, "qqweqeqeqeq");
    strcpy(str2, "keep it simple");

    nlen = 32;
    rc = strncpy_s(str1, LEN, str2, nlen);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

    /* be sure the results are the same as strcmp */
    ind = strcmp(str1, str2);
    if (ind != 0) {
        printf("%s %u -%s-  Error rc=%u \n",
               __FUNCTION__, __LINE__,  str1, rc );
        ++errs;
    }

/*--------------------------------------------------*/
/*--------------------------------------------------*/

    strcpy(str1, "qqweqeqeqeq");
    strcpy(str2, "keep it simple");

    rc = strncpy_s(str1, 1, str2, nlen);
    if (rc != ESNOSPC) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

    if (*str1 != '\0') {
        printf("%s %u -%s-  Error rc=%u \n",
               __FUNCTION__, __LINE__,  str1, rc );
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy(str1, "qqweqeqeqeq");
    strcpy(str2, "keep it simple");

    rc = strncpy_s(str1, 2, str2, nlen);
    if (rc != ESNOSPC) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

    if (*str1 != '\0') {
        printf("%s %u -%s-  Error rc=%u \n",
               __FUNCTION__, __LINE__,  str1, rc );
        ++errs;
    }

/*--------------------------------------------------*/
/* TR example */

    strcpy(dest, "                            ");
    strcpy(str1, "hello");

    rc = strncpy_s(dest, 6, str1, 100);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

    /* be sure the results are the same as strcmp */
    ind = strcmp(dest, str1);
    if (ind != 0) {
        printf("%s %u -%s-  Error rc=%u \n",
               __FUNCTION__, __LINE__,  str1, rc );
        ++errs;
    }

/*--------------------------------------------------*/
/* TR example */

    strcpy(dest, "                            ");
    strcpy(str2, "goodbye");

    rc = strncpy_s(dest, 5, str2, 7);
    if (rc != ESNOSPC) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/
/* TR example */

    strcpy(dest, "                            ");
    strcpy(str2, "goodbye");

    rc = strncpy_s(dest, 5, str2, 4);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

    /* be sure the results are the same as strcmp */
    ind = strcmp(dest, "good");
    if (ind != 0) {
        printf("%s %u -%s-  Error rc=%u \n",
               __FUNCTION__, __LINE__,  str1, rc );
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy(dest, "                            ");
    strcpy(str2, "good");

    /*   strnlen("good") < 5   */
    rc = strncpy_s(dest, 5, str2, 8);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

    /* be sure the results are the same as strcmp */
    ind = strcmp(dest, "good");
    if (ind != 0) {
        printf("%s %u -%s-  Error rc=%u \n",
               __FUNCTION__, __LINE__,  str1, rc );
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy(str1, "qq12345weqeqeqeq");
    strcpy(str2, "it");

    nlen = 10;
    rc = strncpy_s(str1, 10, str2, nlen);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

    /* be sure the results are the same as strcmp */
    ind = strcmp(str1, str2);
    if (ind != 0) {
        printf("%s %u -%s-  Error rc=%u \n",
               __FUNCTION__, __LINE__,  str1, rc );
        ++errs;
    }

/*--------------------------------------------------*/

    return errs;
}


