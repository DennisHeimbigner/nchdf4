# Create a number of executables

add_executable(hdfimport
 hdfimport.c crtSDSfloats.c gen_sds_floats.c
)

target_link_libraries(hdfimport libmfdf libhdf)


