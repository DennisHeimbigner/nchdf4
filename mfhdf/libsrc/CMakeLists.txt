
if(CP)
add_compile_options(/C /P)
endif()

SET(mfhdf_SOURCES 
         array.c cdf.c attr.c dim.c file.c hdfsds.c iarray.c error.c
         globdef.c mfsd.c mfdatainfo.c nssdc.c putget.c putgetg.c
	 sharray.c string.c var.c xdrposix.c xdr.c xdrarray.c xdrfloat.c
)

add_library(mfhdf ${mfhdf_SOURCES}  $<TARGET_OBJECTS:df>)

generate_export_header(mfhdf
             BASE_NAME mfhdf
             EXPORT_MACRO_NAME mfhdf_EXPORT
             EXPORT_FILE_NAME mfhdf_Export.h
             STATIC_DEFINE mfhdf_BUILT_AS_STATIC
)
target_link_libraries(mfhdf ${LINK_LIBS})

if(MSVC)
  SET_TARGET_PROPERTIES(mfhdf PROPERTIES
    LINK_FLAGS_DEBUG " /NODEFAULTLIB:MSVCRT"
    )
else()
  IF(BUILD_SHARED_LIBS)
    SET_TARGET_PROPERTIES(mfhdf LINK_FLAGS -shared)
  ENDIF()
endif()
