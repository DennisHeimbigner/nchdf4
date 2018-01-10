# -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.62)
AC_INIT([nchdf4], 4.2.13, support-netcdf@unidata.ucar.edu)

AC_CANONICAL_HOST
AC_CANONICAL_TARGET
AC_CONFIG_MACRO_DIR([conf])
AC_CONFIG_HEADER([h4config.h])

AM_INIT_AUTOMAKE([foreign subdir-objects])

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
# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([alloc.h arpa/inet.h conio.h dlfcn.h fcntl.h \
getopt.h inttypes.h malloc.h math.h memory.h netinet/in.h \
stdarg.h stdbool.h stdc.h stddef.h stdint.h \
stdlib.h string.h strings.h sys/stat.h sys/time.h sys/types.h \
sys/wait.h unistd.h])

##################################################
# Checks for library functions.
AC_CHECK_FUNCS([access doprnt fork getpid getrusage \
memmove memset mkstemp strcasecmp strchr \
strdup strerror strncpy strndup strrchr \
strtol system unlink wait])
AC_FUNC_VPRINTF
##################################################
# Checks for typedefs, structures, and compiler characteristics. AC_C_CONST
AC_HEADER_STDBOOL
AC_TYPE_LONG_LONG_INT
AC_TYPE_SIZE_T
AC_TYPE_OFF_T
AC_CHECK_TYPES([ssize_t, ptrdiff_t, uchar])
AC_C_CHAR_UNSIGNED
AC_CHECK_SIZEOF(int)
AC_CHECK_SIZEOF(long)
AC_CHECK_SIZEOF(size_t)
AC_CHECK_SIZEOF(off_t)
AC_CHECK_SIZEOF(void*)
AC_CHECK_TYPES([boolean])
AC_CHECK_TYPES([bool_t])
AC_CHECK_TYPES([enum_t])

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

AC_CHECK_LIB([jpeg], [jpeg_set_quality], [], [AC_MSG_ERROR([Can't find or link to the jpeg library. See config.log for errors.])])

AC_CHECK_HEADERS(netcdf.h, [HAVE_NETCDF=1],[HAVE_NETCDF=0])
if test "x$HAVE_NETCDF" = x0 ; then
  AC_MSG_ERROR([Cannot locate netcdf.h; Please add it to CPPFLAGS])
fi

# Make use of szip a configuration option
AC_MSG_CHECKING([whether to enable szip])
AC_ARG_ENABLE([szip],
              [AS_HELP_STRING([--enable-szip],
                              [Enable szipe support])])
test "x$enable_szip" = xyes || enable_szip=no
AC_MSG_RESULT([$enable_szip])
if test "x$enable_szip" = xyes; then
   AC_DEFINE(HAVE_LIBSZ, 1, [set this only when szip is enabled])
   # There are way too many aliases needed
   AC_DEFINE(USE_COMP_SZIP, 1, [alias for HAVE_LIBSZ])
   AC_SUBST(USE_COMP_SZIP, yes)
   # Assume encoder is always there
   AC_DEFINE(SZIP_HAS_ENCODER, yes, [alias for HAVE_LIBSZ])
fi

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
AC_DEFINE([NO_SYS_XDR_INC],[1],[Never use system xdr.h])

##################################################
# Process the Makefile.am (and other) files

# Following are the shell scripts
SCRIPTS="hdf/util/h4redeploy hdf/util/h4cc hdf/util/testutil.sh mfhdf/dumper/testhdp.sh \
          mfhdf/hdfimport/testutil.sh mfhdf/hdiff/testhdiff.sh mfhdf/hrepack/hrepack.sh  \
	  mfhdf/hrepack/hrepack_all.sh mfhdf/test/testmfhdf.sh"

AC_CONFIG_FILES([Makefile
libhdf4.settings
hdf/Makefile
hdf/src/Makefile
hdf/util/Makefile
hdf/test/Makefile
man/Makefile
mfhdf/Makefile
mfhdf/libsrc/Makefile
mfhdf/dumper/Makefile
mfhdf/hdfimport/Makefile
mfhdf/hdiff/Makefile
mfhdf/hrepack/Makefile
mfhdf/test/Makefile
netcdf.h
${SCRIPTS}])

AC_OUTPUT

# Make all shell scripts executable 
chmod a+x ${SCRIPTS}

# Display settings
cat libhdf4.settings

