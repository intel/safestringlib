/*------------------------------------------------------------------
 * test_private.h - Internal test routines & library references
 *
 * 2012, Jonathan Toppins <jtoppins@users.sourceforge.net>
 *
 * Copyright (c) 2012, 2013 by Cisco Systems, Inc
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *------------------------------------------------------------------
 */

#ifndef __TEST_PRIVATE_H__
#define __TEST_PRIVATE_H__

#ifdef __KERNEL__

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/ctype.h>

#include <linux/string.h>
#define printf(...) printk(KERN_INFO __VA_ARGS__)

#else

#define _GNU_SOURCE 1 /* needed to define strcasestr */
#include <stdio.h>
#include <string.h>

#endif

#ifdef DEBUG
#  ifdef __KERNEL__
#    define debug_printf(...)  printk(KERN_DEBUG __VA_ARGS__)
#  else
#    define debug_printf printf
#  endif
#else
#define debug_printf(...)
#endif

int test_memcmp_s(void);
int test_memcmp16_s(void);
int test_memcmp32_s(void);
int test_memcpy_s(void);
int test_memcpy16_s(void);
int test_memcpy32_s(void);
int test_memmove_s(void);
int test_memmove16_s(void);
int test_memmove32_s(void);
int test_memset_s(void);
int test_memset16_s(void);
int test_memset32_s(void);
int test_memzero_s(void);
int test_memzero16_s(void);
int test_memzero32_s(void);
int test_strcasecmp_s(void);
int test_strcasestr_s(void);
int test_strcat_s(void);
int test_strcmp_s(void);
int test_strcmpfld_s(void);
int test_strcpy_s(void);
int test_strcpyfld_s(void);
int test_strcpyfldin_s(void);
int test_strcpyfldout_s(void);
int test_strcspn_s(void);
int test_strfirstchar_s(void);
int test_strfirstdiff_s(void);
int test_strfirstsame_s(void);
int test_strisalphanumeric_s(void);
int test_strisascii_s(void);
int test_strisdigit_s(void);
int test_strishex_s(void);
int test_strislowercase_s(void);
int test_strismixed_s(void);
int test_strispassword_s(void);
int test_strisuppercase_s(void);
int test_strlastchar_s(void);
int test_strlastdiff_s(void);
int test_strlastsame_s(void);
int test_strljustify_s(void);
int test_strncat_s(void);
int test_strncpy_s(void);
int test_strnlen_s(void);
int test_strnterminate_s(void);
int test_strpbrk_s(void);
int test_strprefix_s(void);
int test_strremovews_s(void);
int test_strspn_s(void);
int test_strstr_s(void);
int test_strtok_s(void);
int test_strtolowercase_s(void);
int test_strtouppercase_s(void);
int test_strzero_s(void);
int test_stpncpy_s(void);
int test_stpcpy_s(void);
int test_wcpcpy_s(void);
int test_wcscat_s(void);
int test_wcscpy_s(void);
int test_wcsncat_s(void);
int test_wcsncpy_s(void);
int test_wcsnlen_s(void);
int test_wmemcpy_s(void);
int test_wmemmove_s(void);
int test_wmemset_s(void);
int test_wmemcmp_s(void);

#endif /* __TEST_PRIVATE_H__ */
