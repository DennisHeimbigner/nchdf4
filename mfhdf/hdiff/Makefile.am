#############################################################################
##                      Setup for building programs                        ##
#############################################################################

include $(top_srcdir)/config/commence.am

## Setup the different includes and preprocessor #defines we need.
hdiff_INCLUDES=-I$(top_srcdir)/hdf/src        \
         -I$(top_srcdir)/mfhdf/libsrc   \
         -I$(top_builddir)/mfhdf/libsrc
DEFINES=-DNDEBUG -DHDF
AM_CPPFLAGS=$(hdiff_INCLUDES) $(DEFINES)

## Add hdiff specific linker flags here
hdiff_LDFLAGS = $(LT_STATIC_EXEC) $(AM_LDFLAGS)

#############################################################################
##                          Programs to build                              ##
#############################################################################

bin_PROGRAMS = hdiff

## Information for building the "hdiff" program
hdiff_SOURCES = hdiff.c hdiff_array.c hdiff_gr.c hdiff_list.c hdiff_main.c  \
                hdiff_mattbl.c hdiff_gattr.c hdiff_misc.c hdiff_sds.c       \
                hdiff_table.c hdiff_vs.c hdiff_dim.c                        \
		hdiff.h hdiff_dim.h hdiff_list.h hdiff_mattbl.h hdiff_table.h
hdiff_LDADD = $(LIBMFHDF) $(LIBHDF) -lm
hdiff_DEPENDENCIES = $(LIBMFHDF) $(LIBHDF)

#############################################################################

TESTS = testhdiff.sh

EXTRA_DIST = testfiles testhdiff.sh.in XGetopt.c XGetopt.h

#############################################################################
##                          And the cleanup                                ##
#############################################################################

CLEANFILES = hdifftst1.hdf hdifftst2.hdf hdifftst3.hdf hdifftst4.hdf hdifftst5.hdf hdifftst6.hdf hdifftst7.hdf

DISTCLEANFILES = testhdiff.sh

#include $(top_srcdir)/config/conclude.am
