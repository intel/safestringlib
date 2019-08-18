# CONFIGURE.AC file for Safestring Library
# Copyright (C) 2019 David M. Wheeler All Rights Reserved
#
AC_PREREQ([2.69])
AC_INIT([safestringlib], [1.2], [https://github.com/intel/safestringlib/issues])

    echo >& AS_MESSAGE_FD
    echo '   [Autoconf Script for SafeString Library 1.2.]   ' | sed -e's/./-/g' >&AS_MESSAGE_FD
    echo '   [Autoconf Script for SafeString Library 1.2.]' >& AS_MESSAGE_FD
    echo '   [Autoconf Script for SafeString Library 1.2.]   ' | sed -e's/./-/g' >&AS_MESSAGE_FD


AC_CONFIG_SRCDIR([include/safe_types.h.in])
AC_CONFIG_HEADERS([config.h])

AC_MSG_NOTICE([Checking the compiler...])

# Checks for programs.
AC_PROG_CC
AC_PROG_MKDIR_P
AC_CHECK_TOOL([ARXX], [ar])

    echo >& AS_MESSAGE_FD
    echo '   [Checking and Setting Compiler Flags]   ' | sed -e's/./-/g' >&AS_MESSAGE_FD
    echo '   [Checking and Setting Compiler Flags]' >& AS_MESSAGE_FD
    echo '   [Checking and Setting Compiler Flags]   ' | sed -e's/./-/g' >&AS_MESSAGE_FD

dnl TEST_AND_SET_CXXFLAG(flag, [program])
dnl
dnl This attempts to compile a program with a certain compiler flag.
dnl If no program is given, then the minimal C++ program is compiled, and 
dnl this tests just the validity of the compiler flag. 
dnl
define([TEST_AND_SET_CFLAG],[
	AC_MSG_CHECKING([if compiler flag $1 works])	
	
	dnl Store the current CXXFLAGS
	save_CFLAGS="$CFLAGS"

	dnl Append the flag of interest
	CFLAGS="$CFLAGS $1"
	
	dnl Create an M4 macro, "prog", which expands to a C++ program.
	dnl This should either be a default one or the one specified.
	dnl Note that macros are not local, but there is a stack so push
	dnl the definition on to the stack to prevent clobbering a definition
	dnl that might already exist.
	m4_if([$2],[],[pushdef(prog, [int main(){}])], [pushdef(prog, [$2])])
	
	flag_test=0
	
	dnl See if the compiler runs
	AC_COMPILE_IFELSE([AC_LANG_SOURCE([prog])], [flag_test=1],[flag_test=0])
	
	dnl De-clobber the "prog" macro
	popdef([prog])

	if test $flag_test = 1
	then
		AC_MSG_RESULT(yes)
	else
		AC_MSG_RESULT(no)
		dnl The flag doesn't work, so restore the old CXXFLAGS
		CFLAGS="$save_CFLAGS"
	fi
])

# set the required Compiler flags
TEST_AND_SET_CFLAG([-Wall])
TEST_AND_SET_CFLAG([-Wextra])
TEST_AND_SET_CFLAG([-fstack-protector-strong])  
TEST_AND_SET_CFLAG([-fPIE])
TEST_AND_SET_CFLAG([-fPIC])
TEST_AND_SET_CFLAG([-O2])
TEST_AND_SET_CFLAG([-D_FORTIFY_SOURCE=2])
TEST_AND_SET_CFLAG([-Wformat])
TEST_AND_SET_CFLAG([-Wformat-security])

CFLAGS="-I\$(srcdir)/include $CFLAGS"
echo 'Set the default include directory for project into CFLAGS.' >& AS_MESSAGE_FD

if [[ -z $LDFLAGS ]]
then
	LDFLAGS="-z noexecstack -z relo -z now"
        echo 'Set the defaults for loader flags because they were empty.' >& AS_MESSAGE_FD
fi

    echo >& AS_MESSAGE_FD
    echo '   [Setting up the header files...]   ' | sed -e's/./-/g' >&AS_MESSAGE_FD
    echo '   [Setting up the header files...]' >& AS_MESSAGE_FD
    echo '   [Setting up the header files...]   ' | sed -e's/./-/g' >&AS_MESSAGE_FD


# Checks for header files.
AC_CHECK_HEADERS([limits.h memory.h stddef.h stdlib.h string.h wchar.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADERS([stdio.h])
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT32_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Check for the special include files and set -D options if not
if test $ac_cv_header_stdlib_h = "yes" 
then
    compiler_defines="$compiler_defines -D_HAVE_STDLIB_H"
    echo 'Setting _HAVE_STDLIB_H for stdlib.h' >& AS_MESSAGE_FD

    chka=0;
    AC_CHECK_HEADER(ctype.h, [chka=1], [chka=0])

    if test $chka = 1
    then
        AC_CHECK_HEADER(stddef.h, [chka=1], [chka=0])
    fi
    # Now, chka is only 1 if both both ctype.h and stddef.h are both available
    if test $chka = 1
    then
        compiler_defines="$compiler_defines -DSTDC_HEADERS"
        echo 'Setting STDC_HEADERS to use ctype.h, stdlib.h and stddef.h' >& AS_MESSAGE_FD
    fi
fi
AC_CHECK_HEADER(string.h, [chka=1], [chka=0])
if test $chka = 1
then
    compiler_defines="$compiler_defines -DHAVE_STRING_H"
    echo 'Setting HAVE_STRING_H to use string.h' >& AS_MESSAGE_FD
fi

AC_CHECK_HEADER(memory.h, [chka=1], [chka=0])
if test $chka = 1
then
    compiler_defines="$compiler_defines -DHAVE_MEMORY_H"
    echo 'Setting HAVE_MEMORY_H to use memory.h' >& AS_MESSAGE_FD
fi

AC_CHECK_HEADER(limits.h, [chka=1], [chka=0])
if test $chka = 1
then
    compiler_defines="$compiler_defines -DHAVE_LIMITS_H"
    echo 'Setting HAVE_LIMITS_H to use limits.h' >& AS_MESSAGE_FD
fi

# end check for proper include files

# Set up the safe_lib_errno.h file
AC_CHECK_HEADER([errno.h], [ AC_SUBST(INSERT_ERRNO_H, ["#include <errno.h>"])], [echo 'PROBLEM Header errno.h not found' >& AS_MESSAGE_FD ])

AC_CHECK_HEADER([sys/types.h], [ AC_SUBST(INSERT_SYS_TYPES_H, ["#include <sys/types.h>" ])], [echo 'PROBLEM Header sys/types.h not found' >& AS_MESSAGE_FD ])

AC_CHECK_HEADER([inttypes.h], [ AC_SUBST(INSERT_INTTYPES_H, ["#include <inttypes.h>"])], [echo 'PROBLEM Header inttypes.h not found' >& AS_MESSAGE_FD ])

AC_CHECK_HEADER([stdint.h], [ AC_SUBST(INSERT_STDINT_H, ["#include <stdint.h>"])], [echo 'PROBLEM Header stdint.h not found' >& AS_MESSAGE_FD ])

AC_SUBST(FALLBACK_ERRNO_T, ["typedef int errno_t;" ])

AC_CHECK_HEADER([stdbool.h], [ AC_SUBST(INSERT_BOOL_SUPPORT, ["#include <stdbool.h>"])], [echo 'PROBLEM Header stdbool.h not found' >& AS_MESSAGE_FD ])

# Update compiler flags with the defines needed to select portions of the include files
# which we just figured out from the statements above
CFLAGS="$CFLAGS $compiler_defines"

    echo >& AS_MESSAGE_FD
    echo '   [Setting Included Library Functions]   ' | sed -e's/./-/g' >&AS_MESSAGE_FD
    echo '   [Setting Included Library Functions]' >& AS_MESSAGE_FD
    echo '   [Setting Included Library Functions]   ' | sed -e's/./-/g' >&AS_MESSAGE_FD

# Query the User for selectng the functions in the library
echo 'The following commands determine which functions are included'
echo 'and thus compiled into SafeString Library. These are set by '
echo 'parameters on the .configure command line. The following parameters'
echo 'are options ot select which functions are available:'
echo 'SET_MEMCPY               include memcpy_s().'
echo 'SET_STRCPY               includes strcpy_s() and strncpy_s()'
echo 'SET_STRLEN               includes strnlen_s()'
echo 'SET_MEMFUNCS             includes memcmp_s(), memset_s() and others'
echo 'SET_MEM16                includes 16-bit memory functions'
echo 'SET_MEM32                includes 32-bit memory functions'
echo 'SET_STRFUNCS             includes strcat_s(), stpcpy_s() and others'
echo 'SET_WCHAR                includes wide character functions'
echo 'SET_STRCMP               includes strcmp_s(), strtok_s() and others'
echo 'SET_STRMANIP             includes strremove_s() and string test functions'
echo 'SET_STRFIELD             includes strcmpfld_s() and others'
    echo '   [Setting Included Library Functions]   ' | sed -e's/./-/g' >&AS_MESSAGE_FD
    echo >& AS_MESSAGE_FD

incl_funcs=["\$(_INFRA_LIB)"]
need_meminfra=0
need_stringinfra=0

# #######################################
# Check to include memcpy_s
AC_MSG_CHECKING([include memcpy_s()?])
if [[ "${SET_MEMCPY:0}" == "y" ]]
then
    incl_funcs="$incl_funcs \$(_MEMCPY_FUNC) \$(_MEM_INFRA)"
    need_meminfra=1
    AC_MSG_RESULT([YES])
else
    AC_MSG_RESULT([NO])
fi
# #######################################
# Check to include strcpy_s functions
AC_MSG_CHECKING([include strcpy_s() and strncpy_s()?])
if [[ "${SET_STRCPY:0}" == "y" ]]
then
    incl_funcs="$incl_funcs \$(_STRCPY_FUNC) \$(_STR_INFRA)"
    need_stringinfra=1
    AC_MSG_RESULT([YES])
else
    AC_MSG_RESULT([NO])
fi
# #######################################
# Check to include strnlen_s
AC_MSG_CHECKING([include strnlen_s()?])
if [[ "${SET_STRLEN:0}" == "y" ]]
then
    incl_funcs="$incl_funcs \$(_STRLEN_FUNC)"
    if test $need_stringinfra == 0
    then
    need_stringinfra=1
    incl_funcs="$incl_funcs \$(_STR_INFRA)"
    fi
    AC_MSG_RESULT([YES])
else
    AC_MSG_RESULT([NO])
fi
# #######################################
# Check to include other memcpy functions
AC_MSG_CHECKING([include five other mem bufer functions, like memcmp_s() and memset_s()?])
if [[ "${SET_MEMFUNCS:0}" == "y" ]]
then
    incl_funcs="$incl_funcs \$(_MEMCPY_LIB)"
    if test $need_meminfra == 0
    then
    need_meminfra = 1
    incl_funcs="$incl_funcs $(_MEM_INFRA)"
    fi
    AC_MSG_RESULT([YES])
else
    AC_MSG_RESULT([NO])
fi
# #######################################
# Check to include 16-bit mem buffer functions
AC_MSG_CHECKING([include five special 16-bit word-optimized mem bufer functions, like memcpy16_s() and memset16_s()?])
if [[ "${SET_MEM16:0}" == "y" ]]
then
    incl_funcs="$incl_funcs \$(_MEM16_LIB)"
    if test $need_meminfra == 0
    then
    need_meminfra = 1
    incl_funcs="$incl_funcs \$(_MEM_INFRA)"
    fi
    AC_MSG_RESULT([YES])
else
    AC_MSG_RESULT([NO])
fi
# #######################################
# Check to include 32-bit mem buffer functions
AC_MSG_CHECKING([include five special 32-bit word-optimized mem bufer functions, like memcpy32_s() and memset32_s()?])
if [[ "${SET_MEM32:0}" == "y" ]]
then
    incl_funcs="$incl_funcs \$(_MEM32_LIB)"
    if test $need_meminfra == 0
    then
    need_meminfra = 1
    incl_funcs="$incl_funcs \$(_MEM_INFRA)"
    fi
    AC_MSG_RESULT([YES])
else
    AC_MSG_RESULT([NO])
fi
# #######################################
# Check to include other string functions like stpcpy_s & strcat_s
AC_MSG_CHECKING([include five other string functions like strcat_s() and stpcpy_s()?])
if [[ "${SET_STRFUNCS:0}" == "y" ]]
then
    incl_funcs="$incl_funcs \$(_STRCPY_LIB)"
    if test $need_stringinfra == 0
    then
    need_stringinfra = 1
    incl_funcs="$incl_funcs \$(_STR_INFRA)"
    fi
    AC_MSG_RESULT([YES])
else
    AC_MSG_RESULT([NO])
fi
# #######################################
# Check to include wide-character functions
AC_MSG_CHECKING([include ten wide-character functions, like wcpcpy_s() and wmemcpy_s()?])
if [[ "${SET_WCHAR:0}" == "y" ]]
then
    incl_funcs="$incl_funcs \$(_WIDEC_LIB)"
    if test $need_meminfra == 0
    then
    need_meminfra = 1
    incl_funcs="$incl_funcs \$(_MEM_INFRA)"
    fi
    if test $need_stringinfra == 0
    then
    need_stringinfra = 1
    incl_funcs="$incl_funcs \$(_STR_INFRA)"
    fi
    AC_MSG_RESULT([YES])
else
    AC_MSG_RESULT([NO])
fi
# #######################################
# Check to include special string comparison functions like strcmp_s & strtok_s
AC_MSG_CHECKING([include eight special string comparison functions like strcmp_s() and strtok_s()?])
if [[ "${SET_STRCMP:0}" == "y" ]]
then
    incl_funcs="$incl_funcs \$(_CMPSTR_LIB)"
    if test $need_stringinfra == 0
    then
    need_stringinfra = 1
    incl_funcs="$incl_funcs \$(_STR_INFRA)"
    fi
    AC_MSG_RESULT([YES])
else
    AC_MSG_RESULT([NO])
fi
# #######################################
# Check to include special string operation functions
AC_MSG_CHECKING([include 21 special string manipulation functions like strremovews_s() and strisalphanumeric_s()?])
if [[ "${SET_STRMANIP:0}" == "y" ]]
then
    incl_funcs="$incl_funcs \$(_ADVSTR_LIB)"
    if test $need_stringinfra == 0
    then
    need_stringinfra = 1
    incl_funcs="$incl_funcs \$(_STR_INFRA)"
    fi
    AC_MSG_RESULT([YES])
else
    AC_MSG_RESULT([NO])
fi
# #######################################
# Check to include special string field operation functions
AC_MSG_CHECKING([include four special string ops for fields like strcmpfld_s() and strcpyfldout_s()?])
if [[ "${SET_STRFIELD:0}" == "y" ]]
then
    incl_funcs="$incl_funcs \$(_FIELD_LIB)"
    if test $need_stringinfra == 0
    then
    need_stringinfra = 1
    incl_funcs="$incl_funcs \$(_STR_INFRA)"
    fi
    AC_MSG_RESULT([YES])
else
    AC_MSG_RESULT([NO])
fi

    echo >& AS_MESSAGE_FD
    echo '   [The Selected SAFESTRING Function Groups in the Makefile]   ' | sed -e's/./-/g' >&AS_MESSAGE_FD
    echo '   [The Selected SAFESTRING Function Groups in the Makefile]' >& AS_MESSAGE_FD
    echo '   [The Selected SAFESTRING Function Groups in the Makefile]   ' | sed -e's/./-/g' >&AS_MESSAGE_FD
    echo $incl_funcs >& AS_MESSAGE_FD
    echo >& AS_MESSAGE_FD

    echo >& AS_MESSAGE_FD
    echo '   [The Configured CFLAGS]   ' | sed -e's/./-/g' >&AS_MESSAGE_FD
    echo '   [The Configured CFLAGS]' >& AS_MESSAGE_FD
    echo '   [The Configured CFLAGS]   ' | sed -e's/./-/g' >&AS_MESSAGE_FD
    echo $CFLAGS >& AS_MESSAGE_FD
    echo >& AS_MESSAGE_FD

    echo >& AS_MESSAGE_FD
    echo '   [The Configured Archive Tool]   ' | sed -e's/./-/g' >&AS_MESSAGE_FD
    echo '   [The Configured Archive Tool]' >& AS_MESSAGE_FD
    echo '   [The Configured Archive Tool]   ' | sed -e's/./-/g' >&AS_MESSAGE_FD
    echo $ARXX >& AS_MESSAGE_FD
    echo >& AS_MESSAGE_FD

    echo >& AS_MESSAGE_FD
    echo '   [The ERRNO_H Variable]   ' | sed -e's/./-/g' >&AS_MESSAGE_FD
    echo '   [The ERRNO_H Variable]' >& AS_MESSAGE_FD
    echo '   [The ERRNO_H Variable]   ' | sed -e's/./-/g' >&AS_MESSAGE_FD
    echo $INSERT_ERRNO_H >& AS_MESSAGE_FD
    echo >& AS_MESSAGE_FD

# Make AC_OUTPUT substitute the contents of $incl_funcs for @SELECTLIBS@
AC_SUBST(SELECTLIBS, ["$incl_funcs"])

AC_SUBST(TOPSRCDIR, ["$top_srcdir"])

AC_CONFIG_FILES([Makefile include/safe_types.h include/safe_lib_errno.h])
AC_OUTPUT
