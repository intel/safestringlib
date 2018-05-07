/*
 ============================================================================
 Name        : Safe_String_Extensions.c
 Author      : David M. Wheeler
 Version     :
 Copyright   : (C) Intel Corp 2014
 Description : Safe String Test Suite
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <safe_lib.h>
#include <snprintf_s.h>

extern int test_memcmp_s();
extern int test_memcmp16_s();
extern int test_memcmp32_s();
extern int test_memcpy_s();
extern int test_memcpy16_s();
extern int test_memcpy32_s();
extern int test_memmove_s();
extern int test_memmove16_s();
extern int test_memmove32_s();
extern int test_memset_s();
extern int test_memset16_s();
extern int test_memset32_s();
extern int test_memzero_s();
extern int test_memzero16_s();
extern int test_memzero32_s();
extern int test_strcasecmp_s();
extern int test_strcasestr_s();
extern int test_strcat_s();
extern int test_strcmp_s();
extern int test_strcmpfld_s();
extern int test_strcpy_s();
extern int test_strcpyfld_s();
extern int test_strcpyfldin_s();
extern int test_strcpyfldout_s();
extern int test_strcspn_s ();
extern int test_strfirstchar_s();
extern int test_strfirstdiff_s();
extern int test_strfirstsame_s();
extern int test_strisalphanumeric_s();
extern int test_strisascii_s();
extern int test_strisdigit_s();
extern int test_strishex_s();
extern int test_strislowercase_s();
extern int test_strismixed_s();
extern int test_strispassword_s();
extern int test_strisuppercase_s();
extern int test_strlastchar_s();
extern int test_strlastdiff_s();
extern int test_strlastsame_s();
extern int test_strljustify_s();
extern int test_strncat_s ();
extern int test_strncpy_s ();
extern int test_strnlen_s ();
extern int test_strnterminate_s();
extern int test_strpbrk_s ();
extern int test_strprefix_s();
extern int test_strremovews_s();
extern int test_strspn_s ();
extern int test_strstr_s ();
extern int test_strtok_s();
extern int test_strtolowercase_s();
extern int test_strtouppercase_s();
extern int test_strzero_s();
extern int test_stpncpy_s();
extern int test_stpcpy_s();
extern int test_wcpcpy_s();
extern int test_wcscat_s();
extern int test_wcscpy_s();
extern int test_wcsncat_s();
extern int test_wcsncpy_s (void);
extern int test_wcsnlen_s (void);
extern int test_wmemcpy_s(void);
extern int test_wmemmove_s(void);
extern int test_wmemset_s(void);
extern int test_wmemcmp_s(void);

#define TEST_FUNC(f) { #f, f }

int main(void) {

	char     dest[128];
	char     src[128];
	rsize_t  dmax = 128;
	rsize_t  smax = 21;
	errno_t err;
	static const struct {
		const char * const name;
		int (*func)(void);
	} funcs[] = {
		TEST_FUNC(test_memcmp_s),
		TEST_FUNC(test_memcmp16_s),
		TEST_FUNC(test_memcmp32_s),
		TEST_FUNC(test_memcpy_s),
		TEST_FUNC(test_memcpy16_s),
		TEST_FUNC(test_memcpy32_s),
		TEST_FUNC(test_memmove_s),
		TEST_FUNC(test_memmove16_s),
		TEST_FUNC(test_memmove32_s),
		TEST_FUNC(test_memset_s),
		TEST_FUNC(test_memset16_s),
		TEST_FUNC(test_memset32_s),
		TEST_FUNC(test_memzero_s),
		TEST_FUNC(test_memzero16_s),
		TEST_FUNC(test_memzero32_s),
		TEST_FUNC(test_stpcpy_s),
		TEST_FUNC(test_stpncpy_s),
		TEST_FUNC(test_strcasecmp_s),
		TEST_FUNC(test_strcasestr_s),
		TEST_FUNC(test_strcat_s),
		TEST_FUNC(test_strcmp_s),
		TEST_FUNC(test_strcmpfld_s),
		TEST_FUNC(test_strcpy_s),
		TEST_FUNC(test_strcpyfld_s),
		TEST_FUNC(test_strcpyfldin_s),
		TEST_FUNC(test_strcpyfldout_s),
		TEST_FUNC(test_strcspn_s),
		TEST_FUNC(test_strfirstchar_s),
		TEST_FUNC(test_strfirstdiff_s),
		TEST_FUNC(test_strfirstsame_s),
		TEST_FUNC(test_strisalphanumeric_s),
		TEST_FUNC(test_strisascii_s),
		TEST_FUNC(test_strisdigit_s),
		TEST_FUNC(test_strishex_s),
		TEST_FUNC(test_strislowercase_s),
		TEST_FUNC(test_strismixed_s),
		TEST_FUNC(test_strispassword_s),
		TEST_FUNC(test_strisuppercase_s),
		TEST_FUNC(test_strlastchar_s),
		TEST_FUNC(test_strlastdiff_s),
		TEST_FUNC(test_strlastsame_s),
		TEST_FUNC(test_strljustify_s),
		TEST_FUNC(test_strncat_s),
		TEST_FUNC(test_strncpy_s),
		TEST_FUNC(test_strnlen_s),
		TEST_FUNC(test_strnterminate_s),
		TEST_FUNC(test_strpbrk_s),
		TEST_FUNC(test_strprefix_s),
		TEST_FUNC(test_strremovews_s),
		TEST_FUNC(test_strspn_s),
		TEST_FUNC(test_strstr_s),
		TEST_FUNC(test_strtok_s),
		TEST_FUNC(test_strtolowercase_s),
		TEST_FUNC(test_strtouppercase_s),
		TEST_FUNC(test_strzero_s),
		TEST_FUNC(test_wcpcpy_s),
		TEST_FUNC(test_wcscat_s),
		TEST_FUNC(test_wcscpy_s),
		TEST_FUNC(test_wcsncat_s),
		TEST_FUNC(test_wcsncpy_s),
		TEST_FUNC(test_wcsnlen_s),
		TEST_FUNC(test_wmemcpy_s),
		TEST_FUNC(test_wmemmove_s),
		TEST_FUNC(test_wmemset_s),
		TEST_FUNC(test_wmemcmp_s),
	};
	unsigned int i;
	int errs;

	puts("!!!Basic Test Suite for Safe String Operations!!!");
	puts("       ERRORS PRINT TO CONSOLE");
    puts("----------------BEGIN TEST--------------------");
	for (i = 0; i < sizeof(funcs) / sizeof(funcs[0]); ++i) {
		printf("test %d = %s\n", i, funcs[i].name);
		errs = funcs[i].func();
		if (errs) {
			printf("%d error(s) found, test halted\n", errs);
			return 1;
		}
	}

	char   str[] = "This is a char array";
	char   str2[] = "...And another one.";
	int    indicator = -1;

	strcpy_s(dest, dmax, str);
    char *ret = stpcpy_s(&dest[20], 108, str2, &err);
    if (err != EOK) {
		puts("stpcpy_s returned failure");
		++errs;
	}

    int val = 55;
    if ( (err = snprintf_s_si(src, 128, "Test sprintf_s_si() with simple format string [%s] and %d", dest, val)) < 0 ) {
    	if ( SNPRFNEGATE(ESBADFMT) == err ) {
    		puts("snprintf_s_si returned failure: Error Bad Format String.");
		++errs;
    	} else if ( SNPRFNEGATE(ESFMTTYP) == err ) {
    		puts("snprintf_s_si returned failure: Error Bad Argument Type for format string.");
		++errs;
    	} else {
    		printf("snprintf_s_si failed with unknown error: %d\n", err);
		++errs;
    	}
    } else if ((strcmp_s(src, smax, "Test sprintf_s_si() with simple format string [This is a char array...And another one.] and 55", &indicator) != EOK ) || (indicator != 0 )) {
    	puts("snprintf_s_si() failed - output was:");
    	puts(src);
    	++errs;
    }
    if (errs) {
    	printf("%d error(s) found, test halted\n", errs);
	return 1;
    }
    puts("----------------END TEST--------------------");
	return EXIT_SUCCESS;
}

