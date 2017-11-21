# Create a library called "libdf" which includes the listed source files.

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})

SET(df_SOURCES 
    atom.c bitvect.c cdeflate.c cnbit.c cnone.c crle.c cskphuff.c
    cszip.c df24.c dfan.c dfcomp.c dfconv.c dfgr.c dfgroup.c
    dfimcomp.c dfjpeg.c dfknat.c
    dfkswap.c dfp.c dfr8.c dfrle.c dfsd.c dfstubs.c
    dfufp2i.c dfunjpeg.c dfutil.c dynarray.c glist.c hbitio.c
    hblocks.c hbuffer.c hchunks.c hcomp.c hcompri.c hdatainfo.c
    hdfalloc.c herr.c hextelt.c hfile.c hfiledd.c hkit.c linklist.c
    mcache.c mfan.c mfgr.c mstdio.c tbbt.c vattr.c vconv.c vg.c
    vgp.c vhi.c vio.c vparse.c vrw.c vsfld.c
)

add_library(df ${df_SOURCES})

target_link_libraries(df ${ZLIB_LIBRARY})
target_link_libraries(df ${JPEG_LIBRARY})

