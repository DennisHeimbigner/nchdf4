#############################################################################
##                      Setup for building programs                        ##
#############################################################################

include $(top_srcdir)/config/commence.am

## Setup the different includes and preprocessor #defines we need.
hdfimport_INCLUDES=-I$(top_srcdir)/hdf/src        \
         -I$(top_srcdir)/mfhdf/libsrc   \
         -I$(top_builddir)/mfhdf/libsrc
DEFINES=-DNDEBUG -DHDF
AM_CPPFLAGS=$(hdfimport_INCLUDES) $(DEFINES)

## Add hdfimport specific linker flags here
hdfimport_LDFLAGS = $(LT_STATIC_EXEC) $(AM_LDFLAGS)

#############################################################################
##                      Libraries to link against                          ##
#############################################################################

LDADD = $(LIBMFHDF) $(LIBHDF) @LIBS@

#############################################################################
##                          Programs to build                              ##
#############################################################################

bin_PROGRAMS = hdfimport
#gen_sds_floats crtSDSfloats

hdfimport_SOURCES = hdfimport.c
hdfimport_LDADD = $(LIBMFHDF) $(LIBHDF) @LIBS@
hdfimport_DEPENDENCIES = $(LIBMFHDF) $(LIBHDF)

#############################################################################
check_PROGRAMS = hdfimporttest

hdfimporttest_SOURCES = hdfimporttest.c
hdfimporttest_LDADD = $(LIBMFHDF) $(LIBHDF) @LIBS@
hdfimporttest_DEPENDENCIES = $(LIBMFHDF) $(LIBHDF)

TESTS = testutil.sh

EXTRA_DIST = testutil.sh.in

EXTRA_DIST += SDSfloat2.hdf \
	SDSfloat3.hdf \
	hdfimport-w.out2 \
	hdfimport.input1 \
	hdfimport.out1 \
	hdfimport.out2 \
	hdfimport.out3

#############################################################################

#include $(top_srcdir)/config/conclude.am
