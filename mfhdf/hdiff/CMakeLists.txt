# Create a number of executables

add_executable(hdiff
  hdiff.c hdiff_array.c hdiff_gr.c hdiff_list.c hdiff_main.c
  hdiff_mattbl.c hdiff_gattr.c hdiff_misc.c hdiff_sds.c
  hdiff_table.c hdiff_vs.c hdiff_dim.c
)

target_link_libraries(hdiff libmfdf libhdf libm)

