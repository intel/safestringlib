#include <stdint.h>
#include <stdlib.h>
#include "fuzzer.h"

#ifndef NO_FUZZ_LIBFUZZER

extern "C" int LLVMFuzzerInitialize(int *argc, char ***argv)
{
    return FuzzerInitialize(argc, argv);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *buf, size_t len)
{
    return FuzzerTestOneInput(buf, len);
}

#elif !defined(NO_FUZZ_AFL)

#define BUF_SIZE 65536

int main(int argc, char** argv)
{
    FuzzerInitialize(&argc, &argv);

    while (__AFL_LOOP(10000)) {
        uint8_t *buf = malloc(BUF_SIZE);
        size_t size = read(0, buf, BUF_SIZE);

        FuzzerTestOneInput(buf, size);
        free(buf);
    }

    FuzzerCleanup();
    return 0;
}

#else

#error "Unsupported fuzzer"

#endif

