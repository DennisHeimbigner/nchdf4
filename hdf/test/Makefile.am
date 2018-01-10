#############################################################################
##                      Setup for building programs                        ##
#############################################################################

include $(top_srcdir)/config/commence.am

## Setup the different includes and preprocessor #defines we need.
AM_CPPFLAGS=-I$(top_srcdir)/hdf/src

#############################################################################
##                          Programs to build                              ##
#############################################################################

EXTRA_DIST = test_files

#TEST_PROG = testhdf buffer
TESTS = testhdf buffer
check_PROGRAMS = testhdf buffer

testhdf_SOURCES = an.c anfile.c bitio.c blocks.c chunks.c comp.c   \
                  conv.c extelt.c file.c file1.c litend.c macros.c man.c    \
                  mgr.c nbit.c rig.c sdmms.c sdnmms.c sdstr.c slab.c tbv.c  \
                  tattdatainfo.c tdatainfo.c tdfr8.c tdupimgs.c testhdf.c   \
		  tmgrattr.c tmgrcomp.c tree.c tusejpegfuncs.c      \
		  tutils.c tvattr.c tvnameclass.c tvset.c tvsfpack.c vers.c \
		  tdatainfo.h tproto.h tszip.c tutils.h

testhdf_LDADD = $(LIBHDF)
testhdf_DEPENDENCIES = testdir $(LIBHDF) 

buffer_SOURCES = buffer.c
buffer_LDADD = $(LIBHDF)
buffer_DEPENDENCIES = $(LIBHDF)

testdir:
	-mkdir testdir

#############################################################################
##                          And the cleanup                                ##
#############################################################################

CLEANFILES = testdir/t5.hdf Tables_External_File

# Automake's distclean won't remove directories, so we can add an additional
# hook target which will do so during 'make distclean'.
distclean-local:
	-rm -rf testdir

#include $(top_srcdir)/config/conclude.am
