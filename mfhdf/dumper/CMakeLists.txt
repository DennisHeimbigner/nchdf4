# Create a number of executables

set(hdp_SOURCE
    hdp.c hdp_dump.c hdp_gr.c hdp_list.c hdp_rig.c hdp_sds.c hdp_util.c hdp_vd.c hdp_vg.c show.c
)

add_executable(hdp ${hdp_SOURCE})

target_link_libraries(hdp ${LIBMFHDF} ${LINK_LIBS})




