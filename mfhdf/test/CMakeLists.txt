cmake_minimum_required (VERSION 3.2.2)
project (HDF4_MFHDF_TEST)

#INCLUDE_DIRECTORIES (${HDF4_HDFSOURCE_DIR})
#INCLUDE_DIRECTORIES (${HDF4_MFHDFSOURCE_DIR})

add_definitions (-DHDF)

if (WIN32)
  add_definitions (-DDOS_FS)
endif ()

set (hdftest_SRCS hdftest.c tchunk.c tcomp.c tcoordvar.c
	tdim.c temptySDSs.c tattributes.c tfile.c
	tmixed_apis.c tnetcdf.c trank0.c tsd.c
	tsdsprops.c tszip.c tattdatainfo.c tdatainfo.c
	tdatasizes.c texternal.c tutils.c
)

#-- Adding test for hdftest
add_executable (hdftest ${hdftest_SRCS})
#TARGET_NAMING (hdftest STATIC)
#TARGET_C_PROPERTIES (hdftest STATIC " " " ")
target_link_libraries (hdftest ${LIBMFHDF} ${LINK_LIBS})

#set_target_properties (hdftest PROPERTIES FOLDER test)
#if (BUILD_SHARED_LIBS)
#  add_executable (hdftest-shared ${hdftest_SRCS})
#  TARGET_NAMING (hdftest-shared SHARED)
#  TARGET_C_PROPERTIES (hdftest-shared SHARED " " " ")
#  if (HDF4_BUILD_XDR_LIB)
#    target_link_libraries (hdftest-shared ${HDF4_MF_LIBSH_TARGET} ${HDF4_SRC_LIBSH_TARGET} ${HDF4_MF_XDR_LIBSH_TARGET} ${LINK_SHARED_LIBS})
#  else ()
#    target_link_libraries (hdftest-shared ${HDF4_MF_LIBSH_TARGET} ${HDF4_SRC_LIBSH_TARGET} ${LINK_SHARED_LIBS})
#  endif ()
#  set_target_properties (hdftest-shared PROPERTIES FOLDER test)
#endif ()
#

#-- Adding test for cdftest
add_executable (cdftest cdftest.c)
#TARGET_NAMING (cdftest STATIC)
#TARGET_C_PROPERTIES (cdftest STATIC " " " ")
target_link_libraries(cdftest ${LIBMFHDF} ${LINK_LIBS})

#set_target_properties (cdftest PROPERTIES FOLDER test)
#if (BUILD_SHARED_LIBS)
#  add_executable (cdftest-shared ${HDF4_MFHDF_TEST_SOURCE_DIR}/cdftest.c)
#  TARGET_NAMING (cdftest-shared SHARED)
#  TARGET_C_PROPERTIES (cdftest-shared SHARED " " " ")
#  if (HDF4_BUILD_XDR_LIB)
#    target_link_libraries (cdftest-shared ${HDF4_MF_LIBSH_TARGET} ${HDF4_SRC_LIBSH_TARGET} ${HDF4_MF_XDR_LIBSH_TARGET} ${LINK_SHARED_LIBS})
#  else ()
#    target_link_libraries (cdftest-shared ${HDF4_MF_LIBSH_TARGET} ${HDF4_SRC_LIBSH_TARGET} ${LINK_SHARED_LIBS})
#  endif ()
#  set_target_properties (cdftest-shared PROPERTIES FOLDER test)
#endif ()
#
#-- Adding test for hdfnctest
set (hdfnctest_SRCS hdfnctest.c tunlim.c tncunlim.c tncvargetfill.c)

add_executable (hdfnctest ${hdfnctest_SRCS})
#TARGET_NAMING (hdfnctest STATIC)
#TARGET_C_PROPERTIES (hdfnctest STATIC " " " ")
target_link_libraries (hdfnctest ${LIBMFHDF} ${LINK_LIBS})

#set_target_properties (hdfnctest PROPERTIES FOLDER test)
#if (BUILD_SHARED_LIBS)
#  add_executable (hdfnctest-shared ${hdfnctest_SRCS})
#  TARGET_NAMING (hdfnctest-shared SHARED)
#  TARGET_C_PROPERTIES (hdfnctest-shared SHARED " " " ")
#  if (HDF4_BUILD_XDR_LIB)
#    target_link_libraries (hdfnctest-shared ${HDF4_MF_LIBSH_TARGET} ${HDF4_SRC_LIBSH_TARGET} ${HDF4_MF_XDR_LIBSH_TARGET} ${LINK_SHARED_LIBS})
#  else ()
#    target_link_libraries (hdfnctest-shared ${HDF4_MF_LIBSH_TARGET} ${HDF4_SRC_LIBSH_TARGET} ${LINK_SHARED_LIBS})
#  endif ()
#  set_target_properties (hdfnctest-shared PROPERTIES FOLDER test)
#endif ()
#
#include (CMakeTests.cmake)
#
