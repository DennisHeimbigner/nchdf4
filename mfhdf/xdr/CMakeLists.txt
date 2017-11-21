SET(xdr_SOURCES 
    xdr.c xdrfloat.c xdrstdio.c xdrarray.c
)

add_library(xdr OBJECT ${xdr_SOURCES})

