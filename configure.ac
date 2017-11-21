# -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.62)
AC_INIT([hdf4], 4.2.13, support-netcdf@unidata.ucar.edu)

AC_CANONICAL_HOST
AC_CANONICAL_TARGET
AC_CONFIG_MACRO_DIR([conf])
AC_CONFIG_HEADER([h4config.h])

AM_INIT_AUTOMAKE([foreign dist-tarZ subdir-objects])

#
# ======================================================================
## Libtool initialization
## ======================================================================
LT_INIT()

##
# Prefer an empty CFLAGS variable instead of the default -g -O2.
# See:
#   * http://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/html_node/C-Compiler.html#C-Compiler
##
: ${CFLAGS=""}

# User definable options
# None currently

# Checks for programs.
AC_PROG_CXX
AC_PROG_LIBTOOL
AC_PROG_MAKE_SET
AC_PROG_INSTALL

##################################################
# CPU Checks

AC_C_BIGENDIAN

##################################################
# Checks for library functions.
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([memset memmove strcasecmp strchr strrchr strdup strerror strtol access unlink mkstemp getpid strndup strncpy])
AC_CHECK_FUNCS([fork getrusage system wait])

##################################################
# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([malloc.h memory.h stddef.h stdlib.h string.h strings.h unistd.h stdarg.h])
AC_CHECK_HEADERS([fcntl.h stdc.h math.h alloc.h])
AC_CHECK_HEADERS([netinet/in.h])
AC_CHECK_HEADERS([winsock.h])
AC_CHECK_HEADERS([conio.h])
AC_CHECK_HEADERS([sys/stat.h sys/types.h])

##################################################
# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_HEADER_STDBOOL
AC_TYPE_LONG_LONG_INT
AC_TYPE_SIZE_T
AC_TYPE_OFF_T
AC_CHECK_TYPES([ssize_t, ptrdiff_t, uchar])
AC_C_CHAR_UNSIGNED
AC_C_BIGENDIAN
AC_CHECK_SIZEOF(int)
AC_CHECK_SIZEOF(long)
AC_CHECK_SIZEOF(size_t)
AC_CHECK_SIZEOF(off_t)
AC_CHECK_SIZEOF(void*)
AC_CHECK_TYPES([boolean])

AC_MSG_CHECKING([sizeof(long) > sizeof(int)])
if test $SIZEOF_LONG -gt $SIZEOF_INT ; then
AC_MSG_RESULT([yes])
AC_DEFINE([BIG_LONGS],1,[Define if sizeof(long) > sizeof(int)])
else
AC_MSG_RESULT([no])
fi


# What is fmpool and MPset/MPget?

##################################################
# Checks for external dependencies

AC_SEARCH_LIBS([deflate], [zlibwapi zlibstat zlib zlib1 z], [], [
     AC_MSG_ERROR([Can't find or link to the z library. See config.log for errors.])])

AC_SEARCH_LIBS([SZ_BufftoBuffCompress], [szlib], [HAVE_LIBSZ=yes], [HAVE_LIBSZ=1])

AC_CHECK_LIB([jpeg], [jpeg_set_quality], [], [AC_MSG_ERROR([Can't find or link to the jpeg library. See config.log for errors.])])

AC_CHECK_HEADERS(netcdf.h, [HAVE_NETCDF=1],[HAVE_NETCDF=0])
if test "x$HAVE_NETCDF" = x0 ; then
  AC_MSG_ERROR([Cannot locate netcdf.h; Please add it to CPPFLAGS])
fi

AM_CONDITIONAL(HAVE_LIBSZ, [test xHAVE_LIBSZ = x1])

##################################################

AM_CONDITIONAL(BUILD_SHARED, [test xenable_shared = xyes])

##################################################
# Settings Info
## HDF4 version from the first line of the README.txt file.
H4_VERSION="`cut -d' ' -f3 $srcdir/README.txt | head -1`"
AC_SUBST([H4_VERSION])

## Configuration date
AC_SUBST([CONFIG_DATE]) CONFIG_DATE="`date`"

AC_SUBST([UNAME_INFO]) UNAME_INFO=`uname -a`
AC_SUBST([CC_VERSION]) CC_VERSION=`$CC --version | sed -e 1p -ed`

AC_SUBST([enable_shared])
AC_SUBST([enable_static])

AC_SUBST([LDFLAGS])

##################################################
# Always Define

AC_DEFINE([HDF],[1],[Define if building HDF4 (always true)])

##################################################
# Process the Makefile.am (and other) files
AC_CONFIG_FILES([Makefile
hdf/Makefile
hdf/src/Makefile
hdf/util/Makefile
hdf/util/h4redeploy
hdf/util/h4cc
hdf/test/Makefile
libhdf4.settings
man/Makefile
mfhdf/Makefile
mfhdf/libsrc/Makefile
mfhdf/dumper/Makefile
mfhdf/hdfimport/Makefile
mfhdf/hdiff/Makefile
mfhdf/hrepack/Makefile
mfhdf/xdr/Makefile
mfhdf/hrepack/hrepack.sh
mfhdf/hrepack/hrepack_all.sh
mfhdf/test/Makefile
mfhdf/test/testmfhdf.sh
])

AC_OUTPUT

# Display settings
cat libhdf4.settings
