# Create a number of executables

add_executable(hdp
    hdp.c hdp_dump.c hdp_gr.c hdp_list.c hdp_rig.c hdp_sds.c hdp_util.c hdp_vd.c hdp_vg.c show.c
)

target_link_libraries(hdp libmfdf libhdf)


