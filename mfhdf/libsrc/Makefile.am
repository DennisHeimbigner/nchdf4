#############################################################################
##                      Setup for building programs                        ##
#############################################################################

include $(top_srcdir)/config/commence.am

## Setup the different includes and preprocessor #defines we need.
lib_INCLUDES = -I$(top_srcdir)/hdf/src        \
           -I$(top_srcdir)/mfhdf/libsrc   
DEFINES = -DNDEBUG -DHDF
AM_CPPFLAGS = $(lib_INCLUDES) $(DEFINES)

#############################################################################
##                          Library to build                               ##
#############################################################################

lib_LTLIBRARIES = libmfhdf.la

## Information for building the "libmfhdf.la" library
CSOURCES = array.c cdf.c attr.c dim.c file.c hdfsds.c iarray.c error.c    \
         globdef.c mfsd.c mfdatainfo.c nssdc.c putget.c putgetg.c 	\
	 sharray.c string.c var.c xdrposix.c
# cdf.c

libmfhdf_la_SOURCES = $(CSOURCES)

libmfhdf_la_LIBADD = $(top_builddir)/mfhdf/xdr/libxdr.la \
			$(top_builddir)/hdf/src/libdf.la
libmfhdf_la_LDFLAGS = -no-undefined

# mfdatainfo.h should be added conditionally only; should local_nc.h even be here? -BMR
include_HEADERS = local_nc.h mfhdf.h mfhdfi.h mfdatainfo.h

#############################################################################
##                          And the cleanup                                ##
#############################################################################

DISTCLEANFILES = *.new *.hdf *.cdf *.cdl This*
