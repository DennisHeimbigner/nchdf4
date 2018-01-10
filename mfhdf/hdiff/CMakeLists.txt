# Create a number of executables

set(HDIFFSRC hdiff.c hdiff_array.c hdiff_gr.c hdiff_list.c hdiff_main.c
  hdiff_mattbl.c hdiff_gattr.c hdiff_misc.c hdiff_sds.c
  hdiff_table.c hdiff_vs.c hdiff_dim.c)

if(USE_XGETOPT)
set(HDIFFSRC ${HDIFFSRC} XGetopt.c)
endif()

add_executable(hdiff ${HDIFFSRC})

target_link_libraries(hdiff ${LIBMFHDF} ${LINK_LIBS})


