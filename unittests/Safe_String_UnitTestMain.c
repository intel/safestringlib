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

int main(void) {

	char     dest[128];
	char     src[128];
	rsize_t  dmax = 128;
	rsize_t  smax = 21;
	errno_t err;

	puts("!!!Basic Test Suite for Safe String Operations!!!");
	puts("       ERRORS PRINT TO CONSOLE");
    puts("----------------BEGIN TEST--------------------");
	test_memcmp_s();
	test_memcmp16_s();
	test_memcmp32_s();
	test_memcpy_s();
	test_memcpy16_s();
	test_memcpy32_s();
	test_memmove_s();
	test_memmove16_s();
	test_memmove32_s();
	test_memset_s();
	test_memset16_s();
	test_memset32_s();
	test_memzero_s();
	test_memzero16_s();
	test_memzero32_s();


	test_stpcpy_s(); /* New - Done */
	test_stpncpy_s(); /* New - Done */

	test_strcasecmp_s();
	test_strcasestr_s();
	test_strcat_s();
	test_strcmp_s();
	test_strcmpfld_s();
	test_strcpy_s();
	test_strcpyfld_s();
	test_strcpyfldin_s();
	test_strcpyfldout_s();
	test_strcspn_s ();

	test_strfirstchar_s();
	test_strfirstdiff_s();
	test_strfirstsame_s();
	test_strisalphanumeric_s();
	test_strisascii_s();
	test_strisdigit_s();
	test_strishex_s();
	test_strislowercase_s();
	test_strismixed_s();
	test_strispassword_s();
	test_strisuppercase_s();

	test_strlastchar_s();
	test_strlastdiff_s();
	test_strlastsame_s();
	test_strljustify_s();

	test_strncat_s ();
	test_strncpy_s ();
	test_strnlen_s ();
	test_strnterminate_s();
	test_strpbrk_s ();
	test_strprefix_s();
	test_strremovews_s();
	test_strspn_s ();
	test_strstr_s ();
	test_strtok_s();
	test_strtolowercase_s();
	test_strtouppercase_s();
	test_strzero_s();

	test_wcpcpy_s(); /* New - Done */
	test_wcscat_s(); /* New - Done */
	test_wcscpy_s(); /* New - Done */
	test_wcsncat_s(); /* New - Done */
	test_wcsncpy_s(); /* New - Done */
	test_wcsnlen_s(); /* New - Done */
	test_wmemcpy_s(); /* New - Done */
	test_wmemmove_s(); /* New - Done */
	test_wmemset_s(); /* New - Done */
	test_wmemcmp_s(); /* New - Done */

	char   str[] = "This is a char array";
	char   str2[] = "...And another one.";
	int    indicator = -1;

	strcpy_s(dest, dmax, str);
    char *ret = stpcpy_s(&dest[20], 108, str2, &err);
    if (err != EOK) {
		puts("stpcpy_s returned failure");
	}

    int val = 55;
    if ( (err = snprintf_s_si(src, 128, "Test sprintf_s_si() with simple format string [%s] and %d", dest, val)) < 0 ) {
    	if ( SNPRFNEGATE(ESBADFMT) == err ) {
    		puts("snprintf_s_si returned failure: Error Bad Format String.");
    	} else if ( SNPRFNEGATE(ESFMTTYP) == err ) {
    		puts("snprintf_s_si returned failure: Error Bad Argument Type for format string.");
    	} else {
    		printf("snprintf_s_si failed with unknown error: %d\n", err);
    	}
    } else if ((strcmp_s(src, smax, "Test sprintf_s_si() with simple format string [This is a char array...And another one.] and 55", &indicator) != EOK ) || (indicator != 0 )) {
    	puts("snprintf_s_si() failed - output was:");
    	puts(src);
    }
    puts("----------------END TEST--------------------");
	return EXIT_SUCCESS;
}

