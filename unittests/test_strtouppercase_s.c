/*------------------------------------------------------------------
 * test_strtouppercase_s
 *
 *
 *------------------------------------------------------------------
 */

#include "test_private.h"
#include "safe_str_lib.h"

#define LEN   ( 128 )


int test_strtouppercase_s(void)
{
    errno_t rc;
    int errs = 0;
    rsize_t len;
    char str[LEN];

/*--------------------------------------------------*/

    len = 5;
	//printf("debug - 01\n");
    rc = strtouppercase_s(NULL, len);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    len = 0;
	//printf("debug - 02\n");
    rc = strtouppercase_s("test", len);
    if (rc != ESZEROL) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    /* empty string */
    len = 5;
	//printf("debug - 03\n");
    rc = strtouppercase_s("", len);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

/* FIXME: known bug: this test causes a bus error if the string max size is
   not restricted via RSIZE_MAX_STR */
    len = 99999;
	//printf("debug - 04\n");
    rc = strtouppercase_s("test", len);
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy (str, "n");
    len = strlen(str);

	//printf("debug - 05\n");
    rc = strtouppercase_s(str, len);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }
	//printf("debug - 06\n");

    if (strcmp(str, "N") ) {
        printf("%s %u   Error -%s- \n",
                     __FUNCTION__, __LINE__,  str);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy (str, "N");
    len = strlen(str);

	//printf("debug - 07\n");
    rc = strtouppercase_s(str, len);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

	//printf("debug - 08\n");
    if (strcmp(str, "N") ) {
        printf("%s %u   Error -%s- \n",
                     __FUNCTION__, __LINE__,  str);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy (str, "nowisthetime");
    len = strlen(str);

	//printf("debug - 09\n");
    rc = strtouppercase_s(str, len);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

	//printf("debug - 10\n");
    if (strcmp(str, "NOWISTHETIME") ) {
        printf("%s %u   Error -%s- \n",
                     __FUNCTION__, __LINE__,  str);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy (str, "qqeRo");
    len = strlen(str);

	//printf("debug - 11\n");
    rc = strtouppercase_s(str, len);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

	//printf("debug - 12\n");
    if (strcmp(str, "QQERO") ) {
        printf("%s %u   Error -%s- \n",
                     __FUNCTION__, __LINE__,  str);
        ++errs;
    }

/*--------------------------------------------------*/

    strcpy (str, "1234");
    len = strlen(str);

	//printf("debug - 13\n");
    rc = strtouppercase_s(str, 22);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        ++errs;
    }

/*--------------------------------------------------*/

    return errs;
}
