cmake_minimum_required(VERSION 3.1)
project(safestring)

option(BUILD_UNITTESTS "Build also project unit-tests" OFF)

set(SOURCES
    safeclib/abort_handler_s.c
    safeclib/ignore_handler_s.c
    safeclib/memcmp16_s.c
    safeclib/memcmp32_s.c
    safeclib/memcmp_s.c
    safeclib/memcpy16_s.c
    safeclib/memcpy32_s.c
    safeclib/memcpy_s.c
    safeclib/memmove16_s.c
    safeclib/memmove32_s.c
    safeclib/memmove_s.c
    safeclib/mem_primitives_lib.c
    safeclib/memset16_s.c
    safeclib/memset32_s.c
    safeclib/memset_s.c
    safeclib/memzero16_s.c
    safeclib/memzero32_s.c
    safeclib/memzero_s.c
    safeclib/safe_mem_constraint.c
    safeclib/safe_str_constraint.c
    safeclib/snprintf_support.c
    safeclib/stpcpy_s.c
    safeclib/stpncpy_s.c
    safeclib/strcasecmp_s.c
    safeclib/strcasestr_s.c
    safeclib/strcat_s.c
    safeclib/strcmpfld_s.c
    safeclib/strcmp_s.c
    safeclib/strcpyfldin_s.c
    safeclib/strcpyfldout_s.c
    safeclib/strcpyfld_s.c
    safeclib/strcpy_s.c
    safeclib/strcspn_s.c
    safeclib/strfirstchar_s.c
    safeclib/strfirstdiff_s.c
    safeclib/strfirstsame_s.c
    safeclib/strisalphanumeric_s.c
    safeclib/strisascii_s.c
    safeclib/strisdigit_s.c
    safeclib/strishex_s.c
    safeclib/strislowercase_s.c
    safeclib/strismixedcase_s.c
    safeclib/strispassword_s.c
    safeclib/strisuppercase_s.c
    safeclib/strlastchar_s.c
    safeclib/strlastdiff_s.c
    safeclib/strlastsame_s.c
    safeclib/strljustify_s.c
    safeclib/strncat_s.c
    safeclib/strncpy_s.c
    safeclib/strnlen_s.c
    safeclib/strnterminate_s.c
    safeclib/strpbrk_s.c
    safeclib/strprefix_s.c
    safeclib/strremovews_s.c
    safeclib/strspn_s.c
    safeclib/strstr_s.c
    safeclib/strtok_s.c
    safeclib/strtolowercase_s.c
    safeclib/strtouppercase_s.c
    safeclib/strzero_s.c
    safeclib/wcpcpy_s.c
    safeclib/wcscat_s.c
    safeclib/wcscpy_s.c
    safeclib/wcsncat_s.c
    safeclib/wcsncpy_s.c
    safeclib/wcsnlen_s.c
    safeclib/wmemcmp_s.c
    safeclib/wmemcpy_s.c
    safeclib/wmemmove_s.c
    safeclib/wmemset_s.c)

include_directories(include)

add_library(${PROJECT_NAME}_objlib OBJECT ${SOURCES})
set_target_properties(${PROJECT_NAME}_objlib
                      PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_compile_definitions(${PROJECT_NAME}_objlib PRIVATE -DSTDC_HEADERS)

target_compile_options(${PROJECT_NAME}_objlib
                       PRIVATE -Wno-unknown-pragmas -Wno-unused-parameter)
if(CMAKE_COMPILER_IS_GNUCC AND CMAKE_C_COMPILER_VERSION VERSION_GREATER 7)
  target_compile_options(${PROJECT_NAME}_objlib
                         PRIVATE -Wno-implicit-fallthrough)
endif()
target_compile_options(${PROJECT_NAME}_objlib
                       PRIVATE -Wall -Wextra -Wsign-compare -Wformat-security)
target_compile_options(${PROJECT_NAME}_objlib
                       PRIVATE  -Wstack-protector -Winit-self)
target_compile_options(${PROJECT_NAME}_objlib
                       PRIVATE -D_FORTIFY_SOURCE=2 -O2)
target_compile_options(${PROJECT_NAME}_objlib
                       PRIVATE -fstack-protector-all)
target_compile_options(${PROJECT_NAME}_objlib
                       PRIVATE --param ssp-buffer-size=4 -ftrapv)
target_compile_options(${PROJECT_NAME}_objlib PRIVATE -fPIE -fPIC)

if(CMAKE_COMPILER_IS_GNUCC AND CMAKE_C_COMPILER_VERSION VERSION_GREATER 6)
    target_compile_options(${PROJECT_NAME}_objlib PRIVATE -mmitigate-rop)
endif()
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -z noexecstack -z relro -z now")

option(BUILD_ERROR_ON_WARNING "Fail compilation on warning" OFF)

if(BUILD_ERROR_ON_WARNING)
    target_compile_options(${PROJECT_NAME}_objlib PRIVATE -Werror)
endif()

target_compile_options(${PROJECT_NAME}_objlib PRIVATE $<$<CONFIG:RELEASE>:-s>)

add_library(${PROJECT_NAME}_shared SHARED $<TARGET_OBJECTS:${PROJECT_NAME}_objlib>)
add_library(${PROJECT_NAME}_static STATIC $<TARGET_OBJECTS:${PROJECT_NAME}_objlib>)
target_include_directories(${PROJECT_NAME}_shared PUBLIC include)
target_include_directories(${PROJECT_NAME}_static PUBLIC include)

if(BUILD_UNITTESTS)
  add_subdirectory(unittests)
endif()
