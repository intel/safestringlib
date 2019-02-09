#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>


extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);

int main(int argc, char**argv) {

	for (int i =1; i < argc; i++) {
		std::ifstream in(argv[i]);
		in.seekg(0, in.end);
		size_t length = in.tellg();
		in.seekg (0, in.beg);

		std::vector<char> bytes(length);

		in.read(bytes.data(), bytes.size());
		assert(in);
		LLVMFuzzerTestOneInput(reinterpret_cast<const uint8_t *>(bytes.data()), bytes.size());	
	}
	return 0;
}

