LIB_FUZZING_ENGINE ?= standalone_fuzz_target_runner.o

CXXFLAGS += -std=c++11

clean:
	rm -fv *.a *.o *_fuzzer *_seed_corpus.zip crash-* *.zip

all: fuzz_strisascii

fuzz_strisascii: fuzz_strisascii_s.cpp standalone_fuzz_target_runner.o
	$(CXX) $(CXXFLAGS) $< libsafestring.a ${LIB_FUZZING_ENGINE} -o $@

standalone_fuzz_target_runner.o: standalone_fuzz_target_runner.cpp
