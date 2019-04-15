#include "safe_lib.h"

int FuzzerInitialize(int *argc, char ***argv)
{
    return 1;
}

int FuzzerTestOneInput(const uint8_t *buf, size_t len) {
	const char *input = reinterpret_cast<const char *>(buf);
	strisascii_s(input, (rsize_t)len); //ignore return for now.
	return 0;
}

