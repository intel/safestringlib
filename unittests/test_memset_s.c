/*------------------------------------------------------------------
 * test_memset_s
 *
 *
 *------------------------------------------------------------------
 */

#include "test_private.h"
#include "safe_mem_lib.h"

#define LEN   ( 256 )

static uint8_t mem1[LEN];

int test_memset_s (void)
{
    errno_t rc;
    int errs = 0;
    uint32_t len;
    uint32_t i;

    uint8_t value;

/*--------------------------------------------------*/

    value = 34;

    rc = memset_s(NULL, LEN, value);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    value = 34;

    rc = memset_s(mem1, 0, value);
    if (rc != ESZEROL) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__, rc);
        ++errs;
    }

/*--------------------------------------------------*/

    for (i=0; i<LEN; i++) { mem1[i] = 99; }

    len = 1;
    value = 34;

    rc = memset_s(mem1, len, value);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    for (i=0; i<len; i++) {
        if (mem1[i] != value) {
            printf("%d - %d m1=%d \n",
                 __LINE__, i, mem1[i]);
            ++errs;
        }
    }

/*--------------------------------------------------*/

    for (i=0; i<LEN; i++) { mem1[i] = 99; }

    len = 2;
    value = 34;

    rc = memset_s(mem1, len, value);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    for (i=0; i<len; i++) {
        if (mem1[i] != value) {
            printf("%d - %d m1=%d \n",
                 __LINE__, i, mem1[i]);
            ++errs;
        }
    }

/*--------------------------------------------------*/

    for (i=0; i<LEN; i++) { mem1[i] = 99; }

    len = 12;
    value = 34;

    rc = memset_s(mem1, len, value);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    for (i=0; i<len; i++) {
        if (mem1[i] != value) {
            printf("%d - %d m1=%d \n",
                 __LINE__, i, mem1[i]);
            ++errs;
        }
    }

/*--------------------------------------------------*/

    for (i=0; i<LEN; i++) { mem1[i] = 99; }

    len = 31;
    value = 34;

    rc = memset_s(mem1, len, value);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    for (i=0; i<len; i++) {
        if (mem1[i] != value) {
            printf("%d - %d m1=%d \n",
                 __LINE__, i, mem1[i]);
            ++errs;
        }
    }

/*--------------------------------------------------*/

    for (i=0; i<LEN; i++) { mem1[i] = 99; }

    len = 133;
    value = 34;

    rc = memset_s(mem1, len, value);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
               __FUNCTION__, __LINE__, rc);
        ++errs;
    }

    for (i=0; i<len; i++) {
        if (mem1[i] != value) {
            printf("%d - %d m1=%d \n",
                 __LINE__, i, mem1[i]);
            ++errs;
        }
    }

/*--------------------------------------------------*/
/*--------------------------------------------------*/

    return errs;
}

