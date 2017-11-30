#############################################################################
##                      Setup for building programs                        ##
#############################################################################

include $(top_srcdir)/config/commence.am

## Setup the different includes and preprocessor #defines we need.
test_INCLUDES=-I$(top_srcdir)/hdf/src        \
         -I$(top_srcdir)/mfhdf/libsrc	\
	 -I$(top_builddir)/mfhdf/libsrc
DEFINES=-DNDEBUG -DHDF
AM_CPPFLAGS=$(test_INCLUDES) $(DEFINES)

#############################################################################
##                              Testing                                    ##
#############################################################################

#TEST_PROG = cdftest hdfnctest hdftest
#TEST_SCRIPT = testmfhdf.sh
#check_SCRIPTS = testmfhdf.sh
check_PROGRAMS = cdftest hdfnctest hdftest
TESTS = testmfhdf.sh cdftest hdfnctest hdftest

cdftest_SOURCES = cdftest.c
cdftest_LDADD = $(LIBMFHDF) $(LIBHDF) @LIBS@ $(XDRLIB)

hdfnctest_SOURCES = hdfnctest.c tutils.c tncvargetfill.c tunlim.c tncunlim.c
hdfnctest_LDADD = $(LIBMFHDF) $(LIBHDF) @LIBS@ $(XDRLIB)

hdftest_SOURCES = hdftest.c tutils.c tchunk.c tcomp.c tcoordvar.c	\
		  tdim.c temptySDSs.c tattributes.c texternal.c tfile.c	\
		  tmixed_apis.c trank0.c tsd.c tsdsprops.c	\
		  tszip.c tattdatainfo.c tdatainfo.c tdatasizes.c \
		  hdftest.h

hdftest_LDADD = $(LIBMFHDF) $(LIBHDF) @LIBS@ $(XDRLIB)

EXTRA_DIST = testmfhdf.sh.in cdftest.mak

EXTRA_DIST += sds_szipped.dat smallslice.0000.nc test1.nc testout.sav

#############################################################################
##                          And the cleanup                                ##
#############################################################################

CLEANFILES = ExternalSDSexisting multidimvar.nc onedimmultivars.nc onedimonevar.nc \
		*.new *.hdf *.cdf SD_externals SD_external_file* This*

DISTCLEANFILES = testmfhdf.sh

#include $(top_srcdir)/config/conclude.am
