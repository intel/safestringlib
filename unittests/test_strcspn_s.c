/*------------------------------------------------------------------
 * test_strcspn_s
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

int test_strcspn_s (void)
{
    errno_t rc;
    rsize_t count;
    int std_count;
    unsigned int testno = 0;



/*--------------------------------------------------*/
/* 1  Test for NULL destination check                  */
printf("Test #%d: NULL Scan String Check\n", ++testno);

    rc = strcspn_s(NULL, LEN, str2, LEN, &count);
    if (rc != ESNULLP) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if (count != 0) {
        printf("%s %u  Error  count=%zu rc=%d \n",
                     __FUNCTION__, __LINE__, count, rc);
    }

/*--------------------------------------------------*/
/* 2  Test for NULL source check                       */
    printf("Test #%d: NULL Exclusion String Check: \n", ++testno);

    rc = strcspn_s(str1, LEN, NULL, LEN, &count);
    if (rc != ESNULLP) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if (count != 0) {
        printf("%s %u  Error  count=%zu rc=%d \n",
                     __FUNCTION__, __LINE__, count, rc);
    }

/*--------------------------------------------------*/
/* 3  Test for NULL Count ouput check                       */
    printf("Test #%d: NULL Count parameter Check: \n", ++testno);

    rc = strcspn_s(str1, LEN, str2, LEN, NULL);
    if (rc != ESNULLP) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

/*--------------------------------------------------*/
/* 4  Test for zero length destination                 */
    printf("Test #%d:Zero Length Scan String Check\n", ++testno);

    rc = strcspn_s(str1, 0, str2, LEN, &count);
    if (rc != ESZEROL) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if (count != 0) {
        printf("%s %u  Error  count=%zu rc=%d \n",
                     __FUNCTION__, __LINE__, count, rc);
    }

/*--------------------------------------------------*/
/* 5  Test for zero length source                 */
    printf("Test #%d:Zero Length Exclusion String Check\n", ++testno);

    rc = strcspn_s(str1, LEN, str2, 0, &count);
    if (rc != ESZEROL) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if (count != 0) {
        printf("%s %u  Error  count=%zu rc=%d \n",
                     __FUNCTION__, __LINE__, count, rc);
    }

/*--------------------------------------------------*/
/* 6  Test for too large length destination                 */
    printf("Test #%d:Exceed Max Length Scan String Check\n", ++testno);

    rc = strcspn_s(str1, RSIZE_MAX_STR+1, str2, LEN, &count);
    if (rc != ESLEMAX) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if (count != 0) {
        printf("%s %u  Error  count=%zu rc=%d \n",
                     __FUNCTION__, __LINE__, count, rc);
    }

/*--------------------------------------------------*/
/* 7  Test for too large length destination                 */
    printf("Test #%d:Exceed Max Length Exclusion String Check\n", ++testno);

    rc = strcspn_s(str1, RSIZE_MAX_STR, str2, RSIZE_MAX_STR+1, &count);
    if (rc != ESLEMAX) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if (count != 0) {
        printf("%s %u  Error  count=%zu rc=%d \n",
                     __FUNCTION__, __LINE__, count, rc);
    }

/*--------------------------------------------------*/
/* 8  Test for                  */
    printf("Test #%d:\n", ++testno);

    str1[0] = '\0';
    str2[0] = '\0';

    rc = strcspn_s(str1, LEN, str2, LEN, &count);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if (count != 0) {
        printf("%s %u  Error  count=%zu rc=%d \n",
                     __FUNCTION__, __LINE__, count, rc);
    }

    std_count = strcspn(str1, str2);
    if (count != std_count) {
        printf("%s %u  count=%zu  std_count=%d  rc=%d \n",
                     __FUNCTION__, __LINE__,  count, std_count, rc);
    }

/*--------------------------------------------------*/
/* 9  Test for                  */
    printf("Test #%d:\n", ++testno);


    strcpy (str1, "keep it simple");
    strcpy (str2, "KEEP");

    rc = strcspn_s(str1, 1, str2, LEN, &count);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if (count != 1) {
        printf("%s %u  Error  count=%zu rc=%d \n",
                     __FUNCTION__, __LINE__, count, rc);
    }

/*--------------------------------------------------*/
/* 10  Test for                  */
    printf("Test #%d:\n", ++testno);


    strcpy (str1, "keep it simple");
    strcpy (str2, "KEEP");

    rc = strcspn_s(str1, 2, str2, LEN, &count);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if (count != 2) {
        printf("%s %u  Error  count=%zu rc=%d \n",
                     __FUNCTION__, __LINE__, count, rc);
    }

/*--------------------------------------------------*/
/* 11  Test for                  */
    printf("Test #%d:\n", ++testno);


    strcpy (str1, "keep it simple");
    strcpy (str2, "KEEP");

    rc = strcspn_s(str1, 3, str2, LEN, &count);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if (count != 3) {
        printf("%s %u  Error  count=%zu rc=%d \n",
                     __FUNCTION__, __LINE__, count, rc);
    }


/*--------------------------------------------------*/
/* 12  Test for                  */
    printf("Test #%d:\n", ++testno);


    strcpy (str1, "keep it simple");
    strcpy (str2, "KEEP");

    rc = strcspn_s(str1, 6, str2, LEN, &count);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if (count != 6) {
        printf("%s %u  Error  count=%zu rc=%d \n",
                     __FUNCTION__, __LINE__, count, rc);
    }

/*--------------------------------------------------*/
/* 13  Test for                  */
    printf("Test #%d:\n", ++testno);


    strcpy (str1, "keep it simple");
    strcpy (str2, "ABCDEF");

    rc = strcspn_s(str1, 6, str2, 2, &count);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    if (count != 6) {
        printf("%s %u  count=%zu  std_count=%d  rc=%d \n",
                     __FUNCTION__, __LINE__,  count, std_count, rc);
    }

/*--------------------------------------------------*/
/* 14  Test for                  */
    printf("Test #%d:\n", ++testno);


    strcpy (str1, "keep it simple");
    strcpy (str2, "keep");

    rc = strcspn_s(str1, LEN, str2, LEN, &count);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    std_count = strcspn(str1, str2);
    if (count != std_count) {
        printf("%s %u  count=%zu  std_count=%d  rc=%d \n",
                     __FUNCTION__, __LINE__,  count, std_count, rc);
    }

/*--------------------------------------------------*/
/* 15  Test for                  */
    printf("Test #%d:\n", ++testno);


    strcpy (str1, "keep it simple");
    strcpy (str2, "notincluded");

    rc = strcspn_s(str1, LEN, str2, LEN, &count);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    std_count = strcspn(str1, str2);
    if (count != std_count) {
        printf("%s %u  count=%zu  std_count=%d  rc=%d \n",
                     __FUNCTION__, __LINE__,  count, std_count, rc);
    }

/*--------------------------------------------------*/
/* 16  Test for                  */
    printf("Test #%d:\n", ++testno);


    strcpy (str1, "keep it simple");
    strcpy (str2, "1234567890");

    rc = strcspn_s(str1, LEN, str2, LEN, &count);
    if (rc != EOK) {
        printf("%s %u  Error rc=%d \n",
                     __FUNCTION__, __LINE__, rc);
    }

    std_count = strcspn(str1, str2);
    if (count != std_count) {
        printf("%s %u  count=%zu  std_count=%d  rc=%d \n",
                     __FUNCTION__, __LINE__,  count, std_count, rc);
    }

/*--------------------------------------------------*/

    return (0);
}

