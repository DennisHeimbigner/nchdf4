# Create a number of executables

if(${CP})
add_compile_options(/C /P)
endif()

add_executable(hdfimport hdfimport.c)
add_executable(hdfimporttest hdfimporttest.c)
#build_bin_test(hdfimporttest)

target_link_libraries(hdfimport ${LIBMFHDF} ${LINK_LIBS})
target_link_libraries(hdfimporttest ${LIBMFHDF} ${LINK_LIBS})

add_sh_test(hdfimport testutil)



