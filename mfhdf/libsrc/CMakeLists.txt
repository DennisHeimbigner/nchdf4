SET(mfhdf_SOURCES 
array.c attr.c cdf.c dim.c file.c hdfsds.c iarray.c error.c
globdef.c mfsd.c mfdatainfo.c nssdc.c putget.c putgetg.c
sharray.c string.c var.c xdrposix.c
)

add_library(mfhdf ${mfhdf_SOURCES} $<TARGET_OBJECTS:xdr>)

target_link_libraries(mfhdf df)

