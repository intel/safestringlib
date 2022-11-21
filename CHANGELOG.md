# safestringlib

## v1.2.0:
 - unittests: add test counter to strisdigit_s and strismixed_s.c
 - fix out of bounds check in stris_xxx functions
 - unittests: test_wcscpy_s.c don't count string terminator
 - unittest: test_wmemcpy_s: set correct destination length
 - safec: fix heap-buffer-overflow
 - unittest: don't use tabs
 - safeclib: don't use tabs
 - remove Debug folder
 - unittests: use SPDX identifier in the files
 - lib: use SPDX identifier in the files
 - unittests: cast pointer to intptr_t instead to int
 - unittests: use correct casting in wmemmove_s
 - workflows: add cmake test
 - unittests: strcasestr requires _GNU_SOURCE
 - cmake: BUILD_OPT_DEFAULT type should be bool
