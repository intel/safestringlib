/*------------------------------------------------------------------
 * test_memcmp16_s
 *
 *------------------------------------------------------------------
 */

#include "test_private.h"
#include "safe_mem_lib.h"

#define LEN   ( 128 )

int test_memcmp16_s(void)
{
    errno_t rc;
    int errs = 0;
    uint32_t len;
    int32_t  ind;
    int32_t  std_ind;
    uint32_t i;

    uint16_t  mem1[LEN];
    uint16_t  mem2[LEN];

/*--------------------------------------------------*/

    rc = memcmp16_s(NULL, LEN, mem2, LEN, &ind);
    if (rc != ESNULLP) {
        printf("%s %u  Ind=%d  Error rc=%u \n",
               __FUNCTION__, __LINE__, ind, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    rc = memcmp16_s(mem1, LEN, NULL, LEN, &ind);
    if (rc != ESNULLP) {
        printf("%s %u  Ind=%d  Error rc=%u \n",
               __FUNCTION__, __LINE__, ind, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    rc = memcmp16_s(mem1, LEN, mem2, LEN, NULL);
    if (rc != ESNULLP) {
        printf("%s %u  Ind=%d  Error rc=%u \n",
               __FUNCTION__, __LINE__, ind, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    rc = memcmp16_s(mem1, 0, mem2, LEN, &ind);
    if (rc != ESZEROL) {
        printf("%s %u  Ind=%d  Error rc=%u \n",
               __FUNCTION__, __LINE__, ind, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    rc = memcmp16_s(mem1, LEN, mem2, 0, &ind);
    if (rc != ESZEROL) {
        printf("%s %u  Ind=%d  Error rc=%u \n",
               __FUNCTION__, __LINE__, ind, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    rc = memcmp16_s(mem1, RSIZE_MAX_MEM+1, mem2, LEN, &ind);
    if (rc != ESLEMAX) {
        printf("%s %u  Ind=%d  Error rc=%u \n",
               __FUNCTION__, __LINE__, ind, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    rc = memcmp16_s(mem1, LEN, mem2, RSIZE_MAX_MEM+1, &ind);
    if (rc != ESLEMAX) {
        printf("%s %u  Ind=%d  Error rc=%u \n",
               __FUNCTION__, __LINE__, ind, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    for (i=0; i<LEN; i++) { mem1[i] = i; }
    for (i=0; i<LEN; i++) { mem2[i] = i; }

    len = 1;
    rc = memcmp16_s(mem1, len, mem2, len, &ind);
    if (rc != EOK) {
        printf("%s %u  Ind=%d  Error rc=%u \n",
               __FUNCTION__, __LINE__, ind, rc);
        ++errs;
    }

    if (ind != 0) {
        printf("%s %u  Ind=%d  rc=%u \n",
               __FUNCTION__, __LINE__,  ind, rc);
        ++errs;
    }

    std_ind = memcmp(mem1, mem2, len*2);
    if (ind != std_ind) {
        printf("%s %u  Ind=%d  rc=%u \n",
               __FUNCTION__, __LINE__,  ind, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    for (i=0; i<LEN; i++) { mem1[i] = i; }
    for (i=0; i<LEN; i++) { mem2[i] = i; }

    len = 2;
    rc = memcmp16_s(mem1, len, mem2, len, &ind);
    if (rc != EOK) {
        printf("%s %u  Ind=%d  Error rc=%u \n",
               __FUNCTION__, __LINE__, ind, rc);
        ++errs;
    }

    if (ind != 0) {
        printf("%s %u  Ind=%d  rc=%u \n",
               __FUNCTION__, __LINE__,  ind, rc);
        ++errs;
    }

    std_ind = memcmp(mem1, mem2, len*2);
    if (ind != std_ind) {
        printf("%s %u  Ind=%d  rc=%u \n",
               __FUNCTION__, __LINE__,  ind, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    for (i=0; i<LEN; i++) { mem1[i] = i; }
    for (i=0; i<LEN; i++) { mem2[i] = i; }

    rc = memcmp16_s(mem1, LEN, mem2, LEN, &ind);
    if (rc != EOK) {
        printf("%s %u  Ind=%d  Error rc=%u \n",
               __FUNCTION__, __LINE__, ind, rc);
        ++errs;
    }

    if (ind != 0) {
        printf("%s %u  Ind=%d  rc=%u \n",
               __FUNCTION__, __LINE__,  ind, rc);
        ++errs;
    }

    std_ind = memcmp(mem1, mem2, LEN*2);
    if (ind != std_ind) {
        printf("%s %u  Ind=%d  rc=%u \n",
               __FUNCTION__, __LINE__,  ind, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    for (i=0; i<LEN; i++) { mem1[i] = i; }
    for (i=0; i<LEN; i++) { mem2[i] = i; }

    for (i=10; i<LEN-10; i++) { mem2[i] = 5; }

    rc = memcmp16_s(mem1, LEN, mem2, LEN, &ind);
    if (rc != EOK) {
        printf("%s %u  Ind=%d  Error rc=%u \n",
               __FUNCTION__, __LINE__, ind, rc);
        ++errs;
    }

    if (ind == 0) {
        printf("%s %u  Ind=%d  rc=%u \n",
               __FUNCTION__, __LINE__,  ind, rc);
        ++errs;
    }

    std_ind = memcmp(mem1, mem2, LEN*2);
    if (ind != std_ind) {
        printf("%s %u  Ind=%d  rc=%u \n",
               __FUNCTION__, __LINE__,  ind, rc);
        ++errs;
    }

/*--------------------------------------------------*/
/*--------------------------------------------------*/

    return errs;
}
