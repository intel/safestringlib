IDIR = include
MKDIR_P = mkdir -p
CC=gcc
CFLAGS := -I${IDIR} -fstack-protector-strong -fPIE -fPIC -O2
CFLAGS += -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security
LDFLAGS=-z noexecstack -z now

ODIR=obj
OTDIR=objtest
SRCDIR=safeclib
TESTDIR=unittests

_DEPS := safe_lib_errno.h safe_lib.h safe_str_lib.h safe_types.h.in
_DEPS += safe_lib_errno.h.in safe_mem_lib.h safe_types.h

_ODEPS := mem_primitives_lib.h safeclib_private.h safe_mem_constraint.h
_ODEPS += safe_str_constraint.h

all: directories libsafestring.a safestringtest


DEPS = $(addprefix $(IDIR)/,$(_DEPS))
ODEPS = $(addprefix $(SRCDIR)/,$(_ODEPS))

_CLIB := abort_handler_s.c stpcpy_s.c strlastsame_s.c ignore_handler_s.c
_CLIB += stpncpy_s.c strljustify_s.c memcmp16_s.c strcasecmp_s.c strncat_s.c
_CLIB += memcmp32_s.c strcasestr_s.c strncpy_s.c memcmp_s.c strcat_s.c
_CLIB += strnlen_s.c memcpy16_s.c strcmpfld_s.c strnterminate_s.c memcpy32_s.c
_CLIB += strcmp_s.c strpbrk_s.c memcpy_s.c strcpyfldin_s.c strprefix_s.c
_CLIB += memmove16_s.c strcpyfldout_s.c strremovews_s.c memmove32_s.c
_CLIB += strcpyfld_s.c strspn_s.c memmove_s.c strcpy_s.c strstr_s.c
_CLIB += mem_primitives_lib.c strcspn_s.c strtok_s.c strfirstchar_s.c
_CLIB += strtolowercase_s.c memset16_s.c strfirstdiff_s.c strtouppercase_s.c
_CLIB += memset32_s.c strfirstsame_s.c strzero_s.c memset_s.c
_CLIB += strisalphanumeric_s.c  wcpcpy_s.c memzero16_s.c strisascii_s.c
_CLIB += wcscat_s.c memzero32_s.c strisdigit_s.c wcscpy_s.c memzero_s.c
_CLIB += strishex_s.c wcsncat_s.c strislowercase_s.c wcsncpy_s.c
_CLIB += safe_mem_constraint.c strismixedcase_s.c wcsnlen_s.c
_CLIB += strispassword_s.c wmemcmp_s.c safe_str_constraint.c
_CLIB += strisuppercase_s.c wmemcpy_s.c strlastchar_s.c wmemmove_s.c
_CLIB += snprintf_support.c strlastdiff_s.c wmemset_s.c

_TLIST = $(addprefix $(ODIR)/,$(_CLIB))
OBJ = $(patsubst %.c,%.o,$(_TLIST))
CLIB =$(addprefix $(SRCDIR)/,$(_CLIB))



$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS) $(ODEPS)
	$(CC) $(LDFLAGS) -c -o $@ $< $(CFLAGS)

libsafestring.a: $(OBJ)
	ar rcs $@ $^

_TESTFUNCS := Safe_String_UnitTestMain.c test_strcmp_s.c test_strnlen_s.c
_TESTFUNCS += test_memcmp16_s.c test_strcpyfldin_s.c test_strnterminate_s.c
_TESTFUNCS += test_memcmp32_s.c test_strcpyfldout_s.c test_strpbrk_s.c
_TESTFUNCS += test_memcmp_s.c test_strcpyfld_s.c test_strprefix_s.c
_TESTFUNCS += test_memcpy16_s.c test_strcpy_s.c test_strremovews_s.c
_TESTFUNCS += test_memcpy32_s.c test_strcspn_s.c test_strspn_s.c
_TESTFUNCS += test_memcpy_s.c test_strfirstchar_s.c test_strstr_s.c
_TESTFUNCS += test_memmove16_s.c test_strfirstdiff_s.c test_strtok_s.c
_TESTFUNCS += test_memmove32_s.c test_strfirstsame_s.c test_strtolowercase_s.c
_TESTFUNCS += test_memmove_s.c test_strisalphanumeric_s.c
_TESTFUNCS += test_strtouppercase_s.c test_memset16_s.c test_strisascii_s.c
_TESTFUNCS += test_strzero_s.c test_memset32_s.c test_strisdigit_s.c
_TESTFUNCS += test_wcpcpy_s.c test_memset_s.c test_strishex_s.c test_wcscat_s.c
_TESTFUNCS += test_memzero16_s.c test_strislowercase_s.c  test_wcscpy_s.c
_TESTFUNCS += test_memzero32_s.c test_strismixed_s.c test_wcsncat_s.c
_TESTFUNCS += test_memzero_s.c test_strispassword_s.c test_wcsncpy_s.c
_TESTFUNCS += test_strisuppercase_s.c test_wcsnlen_s.c test_stpcpy_s.c
_TESTFUNCS += test_strlastchar_s.c test_wmemcmp_s.c test_stpncpy_s.c
_TESTFUNCS += test_strlastdiff_s.c test_wmemcpy_s.c test_strcasecmp_s.c
_TESTFUNCS += test_strlastsame_s.c test_wmemmove_s.c test_strcasestr_s.c
_TESTFUNCS += test_strljustify_s.c test_wmemset_s.c test_strcat_s.c
_TESTFUNCS += test_strncat_s.c test_strcmpfld_s.c test_strncpy_s.c

_TLIST2 = $(addprefix $(OTDIR)/,$(_TESTFUNCS))
TOBJ = $(patsubst %.c,%.o,$(_TLIST2))
TCLIB =$(addprefix $(TESTDIR)/,$(_TESTFUNCS))


$(OTDIR)/%.o: $(TESTDIR)/%.c $(TESTDIR)/test_private.h
	$(CC) -c -o $@ $< $(CFLAGS)


safestringtest: directories libsafestring.a $(TOBJ)
	$(CC) $(LDFLAGS) -o $@ $(TOBJ) libsafestring.a


.PHONY: directories

directories: ${ODIR} ${OTDIR}

${ODIR}:
	${MKDIR_P} ${ODIR}

${OTDIR}:
	${MKDIR_P} ${OTDIR}

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ $(OTDIR)/*.o
	rm -f libsafestring.a
	rm -f safestringtest
