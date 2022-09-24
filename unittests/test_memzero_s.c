/*------------------------------------------------------------------
 * test_memzero_s
 *
 *
 *=
 *------------------------------------------------------------------
 */

#include "test_private.h"
#include "safe_mem_lib.h"

#define LEN   ( 512 )

int test_memzero_s(void)
{
    errno_t rc;
    int errs = 0;
    uint32_t i;
    uint32_t len;

    uint8_t mem1[LEN];

/*--------------------------------------------------*/

    rc = memzero_s(NULL, LEN);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    rc = memzero_s(mem1, 0);
    if (rc != ESZEROL) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    rc = memzero_s(mem1, RSIZE_MAX_MEM+1);
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    for (i=0; i<LEN; i++) { mem1[i] = 33; }

    len = 1;
    rc = memzero_s(mem1, len);
    if (rc != EOK) {
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

    len = 2;
    rc = memzero_s(mem1, len);
    if (rc != EOK) {
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

    len = 3;
    rc = memzero_s(mem1, len);
    if (rc != EOK) {
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

    len = LEN;
    rc = memzero_s(mem1, len);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    /* verify mem1 was zeroed */
    for (i=0; i<len; i++) {
        if (mem1[i] != 0) {
            printf("%d - %d m1=%d \n",
                 __LINE__, i, mem1[i] );
            ++errs;
        }
    }

/*--------------------------------------------------*/
/*--------------------------------------------------*/

    return errs;
}
