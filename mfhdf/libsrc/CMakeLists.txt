SET(libmfhdf_SOURCES 
array.c attr.c cdf.c dim.c file.c hdfsds.c iarray.c error.c
globdef.c mfsd.c mfdatainfo.c nssdc.c putget.c putgetg.c
sharray.c string.c var.c xdrposix.c
)

add_library(libmfhdf ${libmfhdf_SOURCES} $<TARGET_OBJECTS:libxdr>)

target_link_libraries(libmfhdf libdf)
