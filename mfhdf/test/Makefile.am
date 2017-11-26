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
		  tszip.c tattdatainfo.c tdatainfo.c tdatasizes.c
hdftest_LDADD = $(LIBMFHDF) $(LIBHDF) @LIBS@ $(XDRLIB)

EXTRA_DIST = testmfhdf.sh.in

EXTRA_DIST += \
    ExternalSDSexisting SDSlongname.hdf SD_external_file SD_external_file \
    Unlim_dim.hdf Unlim_inloop.hdf attdatainfo.hdf b150.hdf \
    bug376.hdf cdfout.new chknbit.hdf chktst.hdf \
    comptst1.hdf comptst2.hdf comptst3.hdf comptst4.hdf \
    comptst5.hdf comptst6.hdf comptst7.hdf datainfo_chk.hdf \
    datainfo_chkcmp.hdf datainfo_cmp.hdf datainfo_extend.hdf datainfo_nodata.hdf \
    datainfo_simple.hdf datasizes.hdf dim.hdf emptySDSs.hdf \
    exttst.hdf hdffile.hdf idtypes.hdf multidimmixed.hdf \
    multidimvar.nc nbit.hdf onedimmultivars.hdf onedimmultivars.nc \
    onedimonevar.nc scaletst.hdf sds1_dim1_samename.hdf sds2_dim1_samename.hdf \
    sds_compressed.hdf tattributes.hdf tdfanndg.hdf tdfansdg.hdf \
    tdfsdatts.hdf test.cdf test1.hdf test2.hdf \
    test_arguments.hdf testmfhdf.sh tvdatasvgroups_SD.hdf vars_samename.hdf

#############################################################################
##                          And the cleanup                                ##
#############################################################################

CHECK_CLEANFILES += *.new *.hdf *.cdf SD_externals

DISTCLEANFILES =

#include $(top_srcdir)/config/conclude.am
