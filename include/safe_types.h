/*------------------------------------------------------------------
 * safe_types.h - C99 std types & defs or Linux kernel equivalents
 *
 * March 2007, Bo Berry
 * Modified 2012, Jonathan Toppins <jtoppins@users.sourceforge.net>
 *
 * Copyright (c) 2007-2013 by Cisco Systems, Inc
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

#ifndef __SAFE_TYPES_H__
#define __SAFE_TYPES_H__

#ifdef __KERNEL__
/* linux kernel environment */

#include <linux/stddef.h>
#include <linux/types.h>
#include <linux/errno.h>

/* errno_t isn't defined in the kernel */
typedef int errno_t;

#else

#include <stdio.h>

/* For systems without sys/types.h, prefer to get size_t from stdlib.h */
/* some armcc environments don't have a sys/types.h in the environment */
#ifdef _USE_STDLIB
#include <stdlib.h>
#include <ctype.h>
#else
#include <sys/types.h>
#endif

#include <inttypes.h>
#include <stdint.h>
#include <errno.h>

typedef int errno_t;

#include <stdbool.h>

#endif /* __KERNEL__ */
#endif /* __SAFE_TYPES_H__ */
