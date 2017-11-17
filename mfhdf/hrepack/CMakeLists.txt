# Create a number of executables

add_executable(hrepack
  hrepack.c hrepack_an.c hrepack_gr.c
  hrepack_list.c hrepack_lsttable.c hrepack_main.c
  hrepack_opttable.c hrepack_parse.c
  hrepack_sds.c hrepack_utils.c
  hrepack_vg.c hrepack_vs.c hrepack_dim.c
)

target_link_libraries(hrepack libmfdf libhdf)

