# safestringlib

## v1.3.0:

 - parse_format: fail on unrecognized modifier
 - strcpyfldin_s: avoid read over slen
 - strremovews_s: check lower bound
 - strcspn_s: check smax first in read
 - strcmpfld_s: do not fill indicator on equal string
 - fix wchar bound checking
 - avoid redefining RSIZE_MAX
 - cmake: BUILD_OPT_DEFAULT type should be bool
 - cmake: do not probe for C++
 - cmake: update minimal version to 3.15
 - unittests: do not crash on len > RSIZE_MAX_STR
 - align str rsize with the mem rsize
 - workflows: upgrade actions version
 - workflows: set top level read permissions
 - silence unused parameters warning in error handlers
 - safeclib/strpbrk_s.c: check string boundaries
 - add Cmake support for creating a Debian package
 - remove makefile it does not work anymore
 - requires cmake version 3.5 or higer
 - workflows: add codeql testing
 - add security policy file

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
