#############################################################################
##                          Library to build                               ##
#############################################################################

include $(top_srcdir)/config/commence.am

lib_LTLIBRARIES = libdf.la

CSOURCES = atom.c bitvect.c cdeflate.c cnbit.c cnone.c crle.c cskphuff.c    \
           cszip.c df24.c dfan.c dfcomp.c dfconv.c dfgr.c dfgroup.c         \
           dfimcomp.c dfjpeg.c dfknat.c       \
           dfkswap.c dfp.c dfr8.c dfrle.c dfsd.c dfstubs.c         \
           dfufp2i.c dfunjpeg.c dfutil.c dynarray.c glist.c hbitio.c        \
           hblocks.c hbuffer.c hchunks.c hcomp.c hcompri.c hdatainfo.c      \
	   hdfalloc.c herr.c hextelt.c hfile.c hfiledd.c hkit.c linklist.c  \
	   mcache.c mfan.c mfgr.c mstdio.c tbbt.c vattr.c vconv.c vg.c	    \
	   vgp.c vhi.c vio.c vparse.c vrw.c vsfld.c

CHEADERS = atom.h bitvect.h cdeflate.h cnbit.h cnone.h cskphuff.h crle.h    \
           cszip.h df.h dfan.h dfi.h dfgr.h dfrig.h dfsd.h dfstubs.h        \
           dfufp2i.h dynarray.h H4api_adpt.h hbitio.h hchunks.h hcomp.h       \
           hcompi.h hconv.h hdf.h hdfi.h herr.h hfile.h hkit.h hlimits.h    \
           hproto.h hntdefs.h htags.h linklist.h mfan.h mfgr.h mstdio.h     \
           tbbt.h vattr.h vg.h hdatainfo.h

libdf_la_SOURCES = $(CSOURCES)
libdf_la_LDFLAGS = -no-undefined
include_HEADERS = $(CHEADERS)