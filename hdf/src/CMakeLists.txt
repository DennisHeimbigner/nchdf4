IF(CP)
add_compile_options(/C /P)
ENDIF()

# Create a library called "libdf" which includes the listed source files.

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})

SET(df_SOURCES atom.c bitvect.c cdeflate.c cnbit.c cnone.c crle.c cskphuff.c
           cszip.c df24.c dfan.c dfcomp.c dfconv.c dfgr.c dfgroup.c
           dfimcomp.c dfjpeg.c dfknat.c
           dfkswap.c dfp.c dfr8.c dfrle.c dfsd.c dfstubs.c
           dfufp2i.c dfunjpeg.c dfutil.c dynarray.c glist.c hbitio.c
           hblocks.c hbuffer.c hchunks.c hcomp.c hcompri.c hdatainfo.c
	   hdfalloc.c herr.c hextelt.c hfile.c hfiledd.c hkit.c linklist.c
	   mcache.c mfan.c mfgr.c mstdio.c tbbt.c vattr.c vconv.c vg.c
	   vgp.c vhi.c vio.c vparse.c vrw.c vsfld.c
)

#set(df_LIBS ${ZLIB_LIBRARY} ${JPEG_LIBRARY})
#if(ENABLE_SZIP)
#set(df_LIBS ${df_LIBS} ${SZIP_LIBRARY})
#endif(ENABLE_SZIP)

add_library(df OBJECT ${df_SOURCES})

#generate_export_header(df
#             BASE_NAME df
#             EXPORT_MACRO_NAME df_EXPORT
#             EXPORT_FILE_NAME df_Export.h
#             STATIC_DEFINE df_BUILT_AS_STATIC
#)
#target_link_libraries(df ${df_LIBS})
#set(CMAKE_REQUIRED_LIBRARIES ${CMAKE_REQUIRED_LIBRARIES} ${df_LIBS})
#if(MSVC)
#  SET_TARGET_PROPERTIES(df PROPERTIES
#    LINK_FLAGS_DEBUG " /NODEFAULTLIB:MSVCRT"
#    )
#else()
#  IF(BUILD_SHARED_LIBS)
#    SET_TARGET_PROPERTIES(df LINK_FLAGS -shared)
#  ENDIF()
#endif()

#IF(ENABLE_SHARED_LIBRARY_VERSION)
#  SET_TARGET_PROPERTIES(df PROPERTIES
#    VERSION ${df_LIB_VERSION}
#    SOVERSION ${df_SO_VERSION}
#    )
#ENDIF(ENABLE_SHARED_LIBRARY_VERSION)

#SET_TARGET_PROPERTIES(df PROPERTIES LIBRARY_OUTPUT_NAME "df")
#SET_TARGET_PROPERTIES(df PROPERTIES ARCHIVE_OUTPUT_NAME "df")
#SET_TARGET_PROPERTIES(df PROPERTIES RUNTIME_OUTPUT_NAME "df")
