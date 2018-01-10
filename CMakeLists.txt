cmake_minimum_required (VERSION 2.8.11)
project (nchdf4)

INCLUDE(CheckIncludeFiles)
INCLUDE(CheckTypeSize)
INCLUDE(CheckFunctionExists)
INCLUDE(TestBigEndian)
INCLUDE(GenerateExportHeader)

add_definitions (-DHAVE_CONFIG_H)

CHECK_INCLUDE_FILES(alloc.h HAVE_ALLOC_H)
CHECK_INCLUDE_FILES(conio.h HAVE_conio_H)
CHECK_INCLUDE_FILES(dlfcn.h HAVE_DLFCN_H)
CHECK_INCLUDE_FILES(fnctl.h HAVE_FCNTL_H)
CHECK_INCLUDE_FILES(inttypes.h HAVE_INTTYPES_H)
CHECK_INCLUDE_FILES(malloc.h HAVE_MALLOC_H)
CHECK_INCLUDE_FILES(math.h HAVE_MATH_H)
CHECK_INCLUDE_FILES(memory.h HAVE_MEMORY_H)
CHECK_INCLUDE_FILES(netinet/in.h HAVE_NETINET_IN_H)
CHECK_INCLUDE_FILES(stdarg.h HAVE_STDARG_H)
CHECK_INCLUDE_FILES(stdbool.h HAVE_STDBOOL_H)
CHECK_INCLUDE_FILES(stdc.h HAVE_STDC_H)
CHECK_INCLUDE_FILES(stddef.h HAVE_STDDEF_H)
CHECK_INCLUDE_FILES(stdint.h HAVE_STDINT_H)
CHECK_INCLUDE_FILES(stdlib.h HAVE_STDLIB_H)
CHECK_INCLUDE_FILES(strings.h HAVE_STRINGS_H)
CHECK_INCLUDE_FILES(string.h HAVE_STRING_H)
CHECK_INCLUDE_FILES(strings.h HAVE_STRINGS_H)
CHECK_INCLUDE_FILES(sys/file.h HAVE_SYS_FILE_H)
CHECK_INCLUDE_FILES(sys/stat.h HAVE_SYS_STAT_H)
CHECK_INCLUDE_FILES(sys/types.h HAVE_SYS_TYPES_H)
CHECK_INCLUDE_FILES(sys/wait.h HAVE_SYS_WAIT_H)
CHECK_INCLUDE_FILES(unistd.h HAVE_UNISTD_H)

CHECK_FUNCTION_EXISTS(access HAVE_ACCESS)
CHECK_FUNCTION_EXISTS(doprnt HAVE_DOPRNT)
CHECK_FUNCTION_EXISTS(fork HAVE_FORK)
CHECK_FUNCTION_EXISTS(getpid HAVE_GETPID)
CHECK_FUNCTION_EXISTS(getrusage HAVE_GETRUSAGE)
CHECK_FUNCTION_EXISTS(memmove HAVE_MEMMOVE)
CHECK_FUNCTION_EXISTS(memset HAVE_MEMSET)
CHECK_FUNCTION_EXISTS(mkstemp HAVE_MKSTEMP)
CHECK_FUNCTION_EXISTS(strcasecmp HAVE_STRCASECMP)
CHECK_FUNCTION_EXISTS(strchr HAVE_STRCHR)
CHECK_FUNCTION_EXISTS(strdup HAVE_STRDUP)
CHECK_FUNCTION_EXISTS(strerror HAVE_STRERROR)
CHECK_FUNCTION_EXISTS(strncpy HAVE_STRNCPY)
CHECK_FUNCTION_EXISTS(strndup HAVE_STRNDUP)
CHECK_FUNCTION_EXISTS(strrchr HAVE_STRRCHR)
CHECK_FUNCTION_EXISTS(strtol HAVE_STRTOL)
CHECK_FUNCTION_EXISTS(system HAVE_SYSTEM)
CHECK_FUNCTION_EXISTS(unlink HAVE_UNLINK)
CHECK_FUNCTION_EXISTS(wait HAVE_WAIT)
CHECK_FUNCTION_EXISTS(vprintf HAVE_VPRINTF)

CHECK_TYPE_SIZE("ptrdiff_t" SIZE_PTRDIFF_T)
CHECK_TYPE_SIZE("off_t" SIZE_OFF_T)
CHECK_TYPE_SIZE("ssize_t" SIZE_SSIZE_T)
CHECK_TYPE_SIZE("uchar" SIZE_UCHAR)
CHECK_TYPE_SIZE("unsigned long long int" SIZE_UNSIGNED_LONG_LONG_INT)
CHECK_TYPE_SIZE("_bool" SIZE__BOOL)
CHECK_TYPE_SIZE("void*" SIZE_VOIDP)
CHECK_TYPE_SIZE("bool_t" SIZE_BOOL_T)
CHECK_TYPE_SIZE("enum_t" SIZE_ENUM_T)
IF(SIZEOF_PTRDIFF_T)
  SET(HAVE_PTRDIFF_T TRUE)
ENDIF(SIZEOF_PTRDIFF_T)
IF(SIZEOF_OFF_T)
  SET(HAVE_OFF_T TRUE)
ENDIF(SIZEOF_OFF_T)
IF(SIZEOF_SSIZE_T)
  SET(HAVE_SSIZE_T TRUE)
ENDIF(SIZEOF_SSIZE_T)
IF(SIZEOF_UCHAR)
  SET(HAVE_UCHAR TRUE)
ENDIF(SIZEOF_UCHAR)
IF(SIZEOF__BOOL)
  SET(HAVE__BOOL TRUE)
ENDIF(SIZEOF__BOOL)
IF(SIZEOF_BOOL_T)
  SET(HAVE_BOOL_T TRUE)
ENDIF(SIZEOF_BOOL_T)
IF(SIZEOF_ENUM_T)
  SET(HAVE_ENUM_T TRUE)
ENDIF(SIZEOF_ENUM_T)

# A check to see if the system is big endian
TEST_BIG_ENDIAN(BIGENDIAN)
IF(${BIGENDIAN})
  SET(WORDS_BIGENDIAN "1")
  add_definitions (-DBIG_LONGS -DSWAP)
ENDIF(${BIGENDIAN})

# Check to see if |long| > |int|
if($(SIZE_INT) LESS $(SIZE_LONG))
SET(BIG_LONGS "1")
endif()

# Checks for external dependencies

# Check for zlib
FIND_PACKAGE(ZLIB)
IF(NOT ZLIB_LIBRARY)
    MESSAGE(FATAL_ERROR "Cannot find zlib.")
ENDIF()
INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIRS})

# Check for jpeg
FIND_PACKAGE(JPEG)
IF(NOT JPEG_LIBRARY)
    MESSAGE(FATAL_ERROR "Cannot find jpeg.")
ENDIF()
INCLUDE_DIRECTORIES(${JPEG_INCLUDE_DIRS})

# Check for szip
OPTION(ENABLE_SZIP "Enable szip support" OFF)
if(ENABLE_SZIP)
FIND_PACKAGE(SZIP)
IF(NOT SZIP_LIBRARY)
    MESSAGE(FATAL_ERROR "szip enabled, but cannot find libsz.")
ENDIF()
INCLUDE_DIRECTORIES(${SZIP_INCLUDE_DIRS})
endif(ENABLE_SZIP)

IF(MSVC)
  SET(USE_XGETOPT ON CACHE BOOL "")
ENDIF()

##
# Default building shared libraries.
# BUILD_SHARED_LIBS is provided by/used by
# CMake directly.
##
OPTION(BUILD_SHARED_LIBS "Configure nchdf4 as a shared library." ON)
IF(BUILD_SHARED_LIBS)
  SET(CMAKE_POSITION_INDEPENDENT_CODE ON)
ENDIF()

OPTION(NC_FIND_SHARED_LIBS "Find dynamically-built versions of dependent libraries" ${BUILD_SHARED_LIBS})

OPTION(ENABLE_DLL "Build a Windows DLL." ${BUILD_SHARED_LIBS})

if(MSVC)
set(H4_BUILT_AS_DYNAMIC_LIB ON)
set(SHARED_EXPORTS ON)
if(ENABLE_DLL)
  set(BUILD_DLL ON CACHE BOOL "")
endif()
endif()

##
# We've had a request to allow for non-versioned shared libraries.
# This seems reasonable enough to accomodate.  See
# https://github.com/Unidata/netcdf-c/issues/228 for more info.
##
OPTION(ENABLE_SHARED_LIBRARY_VERSION "Encode the library SO version in the file name of the generated library file." ON)

# Suppress CRT Warnings.
# Only necessary for Windows
IF(MSVC)
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
ENDIF()

INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/hdf/src)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/mfhdf/libsrc)

set(LINK_LIBS ${ZLIB_LIBRARY} ${JPEG_LIBRARY})
if(ENABLE_SZIP)
set(LINKG_LIBS ${LINK_LIBS} ${SZIP_LIBRARY})
endif(ENABLE_SZIP)

##################################################
##
# Shell script Macro
##
# Determine if 'bash' is on the system.
##

FIND_PROGRAM(HAVE_BASH NAMES bash)
IF(HAVE_BASH)
  MESSAGE(STATUS "Found bash: ${HAVE_BASH}")
ELSE()
  MESSAGE(STATUS "Bash shell not found; disabling shell script tests.")
ENDIF()

MACRO(add_sh_test prefix F)
  IF(HAVE_BASH)
    ADD_TEST(${prefix}_${F} bash "-c" "export srcdir=${CMAKE_CURRENT_SOURCE_DIR};export TOPSRCDIR=${CMAKE_SOURCE_DIR};${CMAKE_CURRENT_BINARY_DIR}/${F}.sh")
  ENDIF()
ENDMACRO()

# Build a binary used by a script, but don't make a test out of it.
MACRO(build_bin_test F)
  ADD_EXECUTABLE(${F} ${F}.c)
  TARGET_LINK_LIBRARIES(${F} hdf mfhdf ${ALL_TLL_LIBS})
  IF(MSVC)
    SET_TARGET_PROPERTIES(${F}
      PROPERTIES LINK_FLAGS_DEBUG " /NODEFAULTLIB:MSVCRT"
      )
    SET_TARGET_PROPERTIES(${F} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
      ${CMAKE_CURRENT_BINARY_DIR})
    SET_TARGET_PROPERTIES(${F} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG
      ${CMAKE_CURRENT_BINARY_DIR})
    SET_TARGET_PROPERTIES(${F} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE
      ${CMAKE_CURRENT_BINARY_DIR})
  ENDIF()
ENDMACRO()

##################################################
# Create h4config.h file.

configure_file("${nchdf4_SOURCE_DIR}/h4config.h.cmake.in"
  "${nchdf4_BINARY_DIR}/h4config.h")

ADD_DEFINITIONS(-DHAVE_CONFIG_H)

option(CP "build with /C/P" OFF)

add_subdirectory(hdf)
#add_subdirectory(mfhdf)
#add_subdirectory(man)

##################################################
# Installation

set(inst_Headers ./h4config.h ./hdf/src/H4api_adpt.h ./hdf/src/hbitio.h ./hdf/src/hcomp.h ./hdf/src/hdatainfo.h ./hdf/src/hdfi.h ./hdf/src/herr.h ./hdf/src/hlimits.h ./hdf/src/hntdefs.h ./hdf/src/hproto.h ./hdf/src/htags.h ./hdf/src/mfgr.h ./hdf/src/vg.h ./hdf/src/hdf.h ./mfhdf/libsrc/mfhdf.h)

#install(TARGETS ${inst_Headers}
#	PUBLIC_HEADER
#	DESTINATION include
#	PERMISSIONS OWNER_READ|GROUP_READ|WORLD|READ	
#	CONFIGURATIONS Release
#	)
#
#install(TARGETS ${inst_Binaries}
#	DESTINATION bin
#	PERMISSIONS OWNER_READ|GROUP_READ|WORLD|READ	
#	CONFIGURATIONS Release
#	)
#
#if(MSVC)
#install(TARGETS ./mfhdf/libsrc/mfdf
#	DESTINATION bin
#	PERMISSIONS OWNER_READ|GROUP_READ|WORLD_READ|OWNER_EXEC|GROUP_EXEC|WORLD_EXEC	
#	CONFIGURATIONS Release
#	)
#else()
#install(TARGETS ./mfhdf/libsrc/mfdf
#	DESTINATION lib
#	PERMISSIONS OWNER_READ|GROUP_READ|WORLD_READ|OWNER_EXEC|GROUP_EXEC|WORLD_EXEC	
#	CONFIGURATIONS Release
#	)
#endif()
#install(EXPORT)

#install(TARGETS targets... [EXPORT <export-name>]
#	DESTINATION include
#        [[ARCHIVE|LIBRARY|RUNTIME|FRAMEWORK|BUNDLE|PRIVATE_HEADER|PUBLIC_HEADER|RESOURCE]
#         [DESTINATION <dir>]
#         [INCLUDES DESTINATION [<dir> ...]]
#         [PERMISSIONS permissions...]
#         [CONFIGURATIONS [Debug|Release|...]]
#         [COMPONENT <component>]
#         [OPTIONAL] [NAMELINK_ONLY|NAMELINK_SKIP]
#        ] [...])

##################################################
# CPack inclusion must come last.
INCLUDE(CPack)
