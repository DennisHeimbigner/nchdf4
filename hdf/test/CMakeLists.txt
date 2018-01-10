#-----------------------------------------------------------------------------
# Setup include Directories
#-----------------------------------------------------------------------------
INCLUDE_DIRECTORIES (
    ${HDF4_HDF_BINARY_DIR}
    ${HDF4_HDFSOURCE_DIR}
)
LINK_DIRECTORIES (
    ${HDF4_HDF_BINARY_DIR}
    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

set (testhdf_SRCS
an.c
anfile.c
bitio.c
blocks.c
chunks.c
comp.c
conv.c
extelt.c
file.c
file1.c
litend.c
macros.c
man.c
mgr.c
nbit.c
rig.c
sdmms.c
sdnmms.c
sdstr.c
slab.c
tbv.c
tattdatainfo.c
tdatainfo.c
tdfr8.c
tdupimgs.c
testhdf.c
tmgrattr.c
tmgrcomp.c
tree.c
tusejpegfuncs.c
tutils.c
tvattr.c
tvnameclass.c
tvset.c
tvsfpack.c
vers.c
tszip.c
)

if (WIN32)
  add_definitions (-DDOS_FS)
endif ()

#-- Adding test for testhdf
add_executable (testhdf ${testhdf_SRCS} $<TARGET_OBJECTS:df>)
target_link_libraries (testhdf ${HDF4_SRC_LIB_TARGET} ${LINK_LIBS})
#set_target_properties (testhdf PROPERTIES FOLDER test)
#if (BUILD_SHARED_LIBS)
#  add_executable (testhdf-shared ${testhdf_SRCS})
#  target_link_libraries (testhdf-shared ${HDF4_SRC_LIBSH_TARGET} ${LINK_SHARED_LIBS})
#  set_target_properties (testhdf-shared PROPERTIES FOLDER test)
#endif ()

#-- Adding test for buffer
if (NOT WIN32)
  add_executable (buffer ${HDF4_HDF_TEST_SOURCE_DIR}/buffer.c)
  TARGET_NAMING (buffer STATIC)
  TARGET_C_PROPERTIES (buffer STATIC " " " ")
  target_link_libraries (buffer ${HDF4_SRC_LIB_TARGET} ${LINK_LIBS})
#  set_target_properties (buffer PROPERTIES FOLDER test)
#  if (BUILD_SHARED_LIBS)
#    add_executable (buffer-shared ${HDF4_HDF_TEST_SOURCE_DIR}/buffer.c)
#    TARGET_NAMING (buffer-shared SHARED)
#    TARGET_C_PROPERTIES (buffer-shared SHARED " " " ")
#    target_link_libraries (buffer-shared ${HDF4_SRC_LIBSH_TARGET} ${LINK_SHARED_LIBS})
#    set_target_properties (buffer-shared PROPERTIES FOLDER test)
#  endif ()
endif ()

##############################################################################
##############################################################################
###           T H E   T E S T S                                            ###
##############################################################################
##############################################################################

#include (CMakeTests.cmake)

