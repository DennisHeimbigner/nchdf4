#############################################################################
##                      Setup for building programs                        ##
#############################################################################

include $(top_srcdir)/config/commence.am

## Setup the different includes and preprocessor #defines we need.
lib_INCLUDES = -I$(top_srcdir)/hdf/src        \
           -I$(top_srcdir)/mfhdf/libsrc       \
           -I$(top_srcdir)/mfhdf/xdr   
DEFINES = -DNDEBUG -DHDF
AM_CPPFLAGS = $(lib_INCLUDES) $(DEFINES)

#############################################################################
##                          Library to build                               ##
#############################################################################

lib_LTLIBRARIES = libmfhdf.la

## Information for building the "libmfhdf.la" library
CSOURCES = array.c cdf.c attr.c dim.c file.c hdfsds.c iarray.c error.c    \
         globdef.c mfsd.c mfdatainfo.c nssdc.c putget.c putgetg.c 	\
	 sharray.c string.c var.c xdrposix.c xdr.c xdrarray.c xdrfloat.c

CHEADERS = alloc.h error.h local_nc.h mfdatainfo.h \
	mfhdf.h mfhdfi.h mfnetcdf.h mfprivate.h types.h xdr.h netcdf.h

libmfhdf_la_SOURCES = $(CSOURCES) $(CHEADERS)
libmfhdf_la_LDFLAGS = -no-undefined
libmfhdf_la_LIBADD = $(top_builddir)/hdf/src/libdf.la

# mfdatainfo.h should be added conditionally only; should local_nc.h even be here? -BMR
include_HEADERS = local_nc.h mfhdf.h mfhdfi.h mfdatainfo.h

#############################################################################
##                          And the cleanup                                ##
#############################################################################

DISTCLEANFILES = *.new *.hdf *.cdf *.cdl This*

