/*------------------------------------------------------------------
 * test_memmove32_s
 *
 *
 *=
 *------------------------------------------------------------------
 */

#include "test_private.h"
#include "safe_mem_lib.h"

#define LEN   ( 1024 )

int test_memmove32_s(void)
{
    errno_t rc;
    int errs = 0;
    uint32_t i;
    uint32_t len;

    uint32_t  mem1[LEN];
    uint32_t  mem2[LEN];

/*--------------------------------------------------*/

    rc = memmove32_s(NULL, LEN, mem2, LEN);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

/*--------------------------------------------------*/

    rc = memmove32_s(mem1, 0, mem2, LEN);
    if (rc != ESZEROL) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

/*--------------------------------------------------*/

    rc = memmove32_s(mem1, RSIZE_MAX_MEM16+1, mem2, LEN);
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

/*--------------------------------------------------*/

    rc = memmove32_s(mem1, LEN, NULL, LEN);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

/*--------------------------------------------------*/

    rc = memmove32_s(mem1, 10, mem2, 0);
    if (rc != ESZEROL) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

/*--------------------------------------------------*/

    rc = memmove32_s(mem1, LEN, mem2, RSIZE_MAX_MEM16+1);
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

/*--------------------------------------------------*/

    for (i=0; i<LEN; i++) { mem1[i] = 33; }
    for (i=0; i<LEN; i++) { mem2[i] = 44; }

    /* a valid move */
    len = LEN;
    rc = memmove32_s(mem1, len, mem2, len);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

    for (i=0; i<len; i++) {
        if (mem1[i] != mem2[i]) {
            printf("%d m1=%d  m2=%d  \n",
                 i, mem1[i], mem2[i]);
            ++errs;
        }
    }

/*--------------------------------------------------*/

/*--------------------------------------------------*/

    for (i=0; i<LEN; i++) { mem1[i] = 33; }
    for (i=0; i<LEN; i++) { mem2[i] = 44; }

    /* length error */
    len = LEN/2;
    rc = memmove32_s(mem1, len, mem2, LEN);
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

    /* verify mem1 was zeroed */
    for (i=0; i<len; i++) {
        if (mem1[i] != 0) {
            printf("%d - %d m1=%d \n",
                 __LINE__, i, mem1[i]);
            ++errs;
        }
    }

/*--------------------------------------------------*/

    for (i=0; i<LEN; i++) { mem1[i] = 33; }
    for (i=0; i<LEN; i++) { mem2[i] = 44; }

    /* invalid length - zero dest */
    len = LEN;
    rc = memmove32_s(mem1, len, mem2, 0);
    if (rc != ESZEROL) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

    /* verify mem1 was zeroed */
    for (i=0; i<len; i++) {
        if (mem1[i] != 0) {
            printf("%d - %d m1=%d \n",
                 __LINE__, i, mem1[i]);
            ++errs;
        }
    }

/*--------------------------------------------------*/

/*--------------------------------------------------*/

    for (i=0; i<LEN; i++) { mem1[i] = 33; }
    for (i=0; i<LEN; i++) { mem2[i] = 44; }

    /* invalid length - zero dest */
    len = LEN;
    rc = memmove32_s(mem1, len, mem2, RSIZE_MAX_MEM+1);
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    /* verify mem1 was zeroed */
    for (i=0; i<len; i++) {
        if (mem1[i] != 0) {
            printf("%d - %d m1=%d \n",
                 __LINE__, i, mem1[i]);
            ++errs;
        }
    }

/*--------------------------------------------------*/

    for (i=0; i<LEN; i++) { mem1[i] = 33; }
    for (i=0; i<LEN; i++) { mem2[i] = 44; }

    /* same ptr - no move */
    rc = memmove32_s(mem1, LEN, mem1, LEN);
    if (rc != EOK) {
        printf("%s %u  Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

/*--------------------------------------------------*/

    for (i=0; i<LEN; i++) { mem1[i] = 25; }
    for (i=10; i<LEN-10; i++) { mem1[i] = 35; }

    /* overlap move */
    len = 20;
    rc = memmove32_s(&mem1[0], len, &mem1[10], len);
    if (rc != EOK) {
        printf("%s %u  Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

    for (i=0; i<len; i++) {
        if (mem1[i] != 35) {
            printf("%d - %d m1=%d \n",
                 __LINE__, i, mem1[i]);
            ++errs;
        }
    }

/*--------------------------------------------------*/

    for (i=0; i<LEN; i++) { mem1[i] = 25; }
    for (i=10; i<LEN-10; i++) { mem1[i] = 35; }

    /* overlap move */
    len = 20;
    rc = memmove32_s(&mem1[10], len, &mem1[0], len);
    if (rc != EOK) {
        printf("%s %u  Error rc=%u \n",
               __FUNCTION__, __LINE__,  rc);
        ++errs;
    }

    for (i=0; i<10; i++) {
        if (mem1[i] != 25) {
            printf("%d - %d m1=%d \n",
                 __LINE__, i, mem1[i]);
            ++errs;
        }
    }

/*--------------------------------------------------*/
/*--------------------------------------------------*/

    return errs;
}
