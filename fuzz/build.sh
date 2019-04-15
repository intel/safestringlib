#!/bin/bash

CXX=clang++

CCFLAGS="-g -O0 -fprofile-instr-generate -fcoverage-mapping -fsanitize=fuzzer,address"
CXXFLAGS="-g -O0 -fprofile-instr-generate -fcoverage-mapping -fsanitize=fuzzer,address"

fuzzerFiles=$(find $PWD/ -name '*.cpp')

for F in $fuzzerFiles; do
    fuzzerName=$(basename $F .cpp)
    echo "Building fuzzer $fuzzerName"
    $CXX -v $CXXFLAGS -I../include \
        -o $fuzzerName $F driver.c ../libsafestring.a
done

