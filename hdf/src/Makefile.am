#############################################################################
##                          Library to build                               ##
#############################################################################

include $(top_srcdir)/config/commence.am

CFLAGS += -Dhdf4_EXPORTS

CSOURCES = atom.c bitvect.c cdeflate.c cnbit.c cnone.c crle.c cskphuff.c    \
           cszip.c df24.c dfan.c dfcomp.c dfconv.c dfgr.c dfgroup.c         \
           dfimcomp.c dfjpeg.c dfknat.c       \
           dfkswap.c dfp.c dfr8.c dfrle.c dfsd.c dfstubs.c         \
           dfufp2i.c dfunjpeg.c dfutil.c dynarray.c glist.c hbitio.c        \
           hblocks.c hbuffer.c hchunks.c hcomp.c hcompri.c hdatainfo.c      \
	   herr.c hextelt.c hfile.c hfiledd.c hkit.c linklist.c  \
	   mcache.c mfan.c mfgr.c mstdio.c tbbt.c vattr.c vconv.c vg.c	    \
	   vgp.c vhi.c vio.c vparse.c vrw.c vsfld.c

CHEADERS = atom.h bitvect.h cdeflate.h cnbit.h cnone.h \
	crle.h cskphuff.h cszip.h df.h dfan.h \
	dfconvrt.h dfgr.h dfi.h dfrig.h dfsd.h \
	dfstubs.h dfufp2i.h dynarray.h glist.h H4api_adpt.h \
	hbitio.h hchunks.h hcomp.h hcompi.h hconv.h \
	hdatainfo.h hdf.h hdfi.h hdfinternal.h herr.h hfile.h \
	hinternal.h hkit.h hlimits.h hntdefs.h hproto.h hqueue.h \
	hshared.h htags.h linklist.h maldebug.h mcache.h mfan.h \
	mfgr.h mstdio.h patchlevel.h tbbt.h trace.h \
	vattr.h vg.h vgint.h 

libdf_la_SOURCES = $(CSOURCES) $(CHEADERS)
libdf_la_LDFLAGS = -no-undefined
libnetcdf3_la_CPPFLAGS = ${AM_CPPFLAGS}

noinst_LTLIBRARIES = libdf.la

include_HEADERS = H4api_adpt.h hbitio.h hcomp.h hdatainfo.h hdf.h hdfi.h \
		  herr.h hlimits.h hntdefs.h hproto.h htags.h mfgr.h vg.h
