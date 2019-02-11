#include "safe_lib.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

	const char *input = reinterpret_cast<const char *>(data);
	strisascii_s(input, (rsize_t)size); //ignore return for now.
	return 0;
}

