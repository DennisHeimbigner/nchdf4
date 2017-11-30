
#############################################################################
##                      Subdirectories to build in                         ##
#############################################################################

ACLOCAL_AMFLAGS = -Iconf -Iconfig -I${top_srcdir}/.

include $(top_srcdir)/config/commence.am

SUBDIRS = hdf mfhdf man

EXTRA_DIST = README.txt README.md CMakeLists.txt LICENSE \
		h4config.h.cmake.in release_notes libhdf4.settings.in

DISTCLEANFILE =

# install .settings in lib directory.
settingsdir=$(libdir)
settings_DATA=libhdf4.settings

inst_Headers = ./h4config.h ./hdf/src/H4api_adpt.h ./hdf/src/hbitio.h ./hdf/src/hcomp.h ./hdf/src/hdatainfo.h ./hdf/src/hdfi.h ./hdf/src/herr.h ./hdf/src/hlimits.h ./hdf/src/hntdefs.h ./hdf/src/hproto.h ./hdf/src/htags.h ./hdf/src/mfgr.h ./hdf/src/vg.h

# The following files are in the github repository but are for author's use only
# cf cf.cmake tr.sh
