## Makefile.am
## Run automake to generate a Makefile.in from this file.
#
# XDR Library Makefile(.in)
#

include $(top_srcdir)/config/commence.am

## Setup the different includes and preprocessor #defines we need.
AM_CPPFLAGS=-I$(top_srcdir)/hdf/src

# XDR Library
noinst_LTLIBRARIES = libxdr.la
libxdr_la_SOURCES = xdr.c xdrfloat.c xdrarray.c
# duplicate of what is in libsrc? xdrstdio.c 
include_HEADERS = xdr.h types.h

#include $(top_srcdir)/config/conclude.am
