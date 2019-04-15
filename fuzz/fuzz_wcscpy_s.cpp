#include "safe_lib.h"
#include <string>

#define MAX   ( 128*4 )
#define LEN   ( 128*4 )

static wchar_t   str1[LEN];
static wchar_t   str2[LEN];


int FuzzerInitialize(int *argc, char ***argv)
{
    return 1;
}

int FuzzerTestOneInput(const uint8_t *buf, size_t len) {
     errno_t rc;

    std::wstring wstr(reinterpret_cast<const wchar_t*>(buf), len/sizeof(wchar_t));
    rc = wcscpy_s(str1, LEN, wstr.c_str());

    return rc;
    return (0);
} 

