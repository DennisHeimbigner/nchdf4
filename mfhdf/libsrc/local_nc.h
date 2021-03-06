/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright 1993, University Corporation for Atmospheric Research           *
 * See netcdf/COPYRIGHT file for copying and redistribution conditions.      *
 *                                                                           *
 * Copyright by The HDF Group.                                               *
 * Copyright by the Board of Trustees of the University of Illinois.         *
 * All rights reserved.                                                      *
 *                                                                           *
 * This file is part of HDF.  The full HDF copyright notice, including       *
 * terms governing use, modification, and redistribution, is contained in    *
 * the COPYING file, which can be found at the root of the source code       *
 * distribution tree, or in https://support.hdfgroup.org/ftp/HDF/releases/.  *
 * If you do not have access to either file, you may request a copy from     *
 * help@hdfgroup.org.                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* $Id$ */
#ifndef _LOCAL_NC_
#define _LOCAL_NC_

#include "h4config.h"
#include "H4api_adpt.h"

/*
 *    netcdf library 'private' data structures, objects and interfaces
 */

#ifdef HAVE_STDDEF_H
#include    <stddef.h> /* size_t */
#endif
#include    <stdio.h> /* FILENAME_MAX */

#include "netcdf.h"

#ifndef FILENAME_MAX
#define FILENAME_MAX  255
#endif

#ifdef HAVE_TYPES_H
#include      "types.h"  /* "types.h" */
#endif
#include      "xdr.h"    /* "xdr.h" */

#include "H4api_adpt.h"

/* ptr argument type in internal functions */
#define Void    char

#ifndef WORDS_BIGENDIAN
#define SWAP 1
#endif

/*
** Include HDF stuff
*/

#include "hdf.h"
#include "vg.h"
#include "hfile.h"
#include "mfhdfi.h"

#define ATTR_TAG  DFTAG_VH
#define DIM_TAG   DFTAG_VG
#define VAR_TAG   DFTAG_VG
#define DATA_TAG  DFTAG_SD
#define BOGUS_TAG ((uint16) 721)

#if 0
#define ATTRIBUTE         "Attr0.0"
#define VARIABLE          "Var0.0"
#define DIMENSION         "Dim0.0"
#define UDIMENSION        "UDim0.0"
#define DIM_VALS          "DimVal0.0"
#define DIM_VALS01        "DimVal0.1"
#define CDF               "CDF0.0"
/* DATA is defined in DTM. Change DATA to DATA0 *
#define DATA              "Data0.0"
*/
#define DATA0             "Data0.0"
#define ATTR_FIELD_NAME   "VALUES"
#endif

#define DIMVAL_VERSION00  0  /* <dimsize> fake values */
#define DIMVAL_VERSION01  1  /* 1 elt with value of <dimsize>  */
#define BLOCK_MULT  64    /* multiplier for bytes in linked blocks */
#define MAX_BLOCK_SIZE  65536    /* maximum size of block in linked blocks */
#define BLOCK_COUNT 128   /* size of linked block pointer objects  */


/* from cdflib.h CDF 2.3 */
#ifndef MAX_VXR_ENTRIES
#define MAX_VXR_ENTRIES                 10
#endif /* MAX_VXR_ENTRIES */

/* VIX record for CDF variable data storage */
typedef struct vix_t_def {
    int32              nEntries;                    /* number of entries in this vix */
    int32              nUsed;                       /* number of entries containing valid data */
    int32              firstRec[MAX_VXR_ENTRIES];   /* number of first records */
    int32              lastRec[MAX_VXR_ENTRIES];    /* number of last records */
    int32              offset[MAX_VXR_ENTRIES];     /* file offset of records */
    struct vix_t_def * next;                        /* next one in line */
} vix_t;

/* like, a discriminated union in the sense of xdr */
typedef struct {
    nc_type type ;        /* the discriminant */
    size_t len ;        /* the total length originally allocated */
    size_t szof ;        /* sizeof each value */
    unsigned count ;    /* length of the array */
    Void *values ;        /* the actual data */
} NC_array ;

/* Counted string for names and such */
/*

  count is the actual size of the buffer for the string
  len is the length of the string in the buffer

  count != len when a string is resized to something smaller

*/
#define NC_compare_string(s1,s2) ((s1)->hash!=(s2)->hash ? 1 : HDstrcmp((s1)->values,(s2)->values))

typedef struct {
    unsigned count ;
    unsigned len ;
    uint32 hash;        /* [non-perfect] hash value for faster comparisons */
    char *values ;
} NC_string ;

/* Counted array of ints for assoc list */
typedef struct {
    unsigned count ;
    int *values ;
} NC_iarray ;

/* NC dimension stucture */
typedef struct {
    NC_string *name ;
    long size ;
    int32 dim00_compat;   /* compatible with Dim0.0 */
    int32 vgid;   /* id of the Vgroup representing this dimension */
    int32 count;  /* Number of pointers to this dimension */
} NC_dim ;

/* NC attribute */
typedef struct {
    NC_string    *name ;
    NC_array    *data ;
    int32           HDFtype; /* it should be in NC_array *data. However, */
                             /* NC.dims and NC.vars are NC_array too. */
} NC_attr ;

typedef struct {
    char path[FILENAME_MAX + 1] ;
    unsigned flags ;
    XDR *xdrs ;
    long begin_rec ; /* (off_t) postion of the first 'record' */
    unsigned long recsize ; /* length of 'record' */
    int redefid ;
    /* below gets xdr'd */
    unsigned long numrecs ; /* number of 'records' allocated */
    NC_array *dims ;
    NC_array *attrs ;
    NC_array *vars ;
    int32 hdf_file;
    int file_type;
    int32 vgid;
    int hdf_mode; /* mode we are attached for */
    hdf_file_t cdf_fp; /* file pointer used for CDF files */
} NC ;

/* NC variable: description and data */
typedef struct {
    NC_string *name ;    /* name->values shows data set's name */
    NC_iarray *assoc ;    /* user definition */
    unsigned long *shape ;    /* compiled info (Each holds a dimension size. -BMR) */
    unsigned long *dsizes ;    /* compiled info (Each element holds the amount of space
            needed to hold values in that dimension, e.g., first dimension
            size is 10, value type is int32=4, then dsizes[0]=4*10=40. -BMR) */
    NC_array *attrs;    /* list of attribute structures */
    nc_type type ;        /* the discriminant */
    unsigned long len ;    /* the total length originally allocated */
    size_t szof ;        /* sizeof each value */
    long begin ;        /* seek index, often an off_t */
    NC *cdf;    /* handle of the file where this var belongs to  */
    int32 vgid;    /* id of the variable's Vgroup */
    uint16 data_ref;/* ref of the variable's data storage (if exists), default 0 */
    uint16 data_tag;/* tag of the variable's data storage (if exists), default DATA_TAG */
    uint16 ndg_ref; /* ref of ndg for this dataset */
    hdf_vartype_t var_type; /* type of this variable, default UNKNOWN
            IS_SDSVAR == this var is an SDS variable
            IS_CRDVAR == this var is a coordinate variable
            UNKNOWN == because the var was created prior to this distinction.
    This is to distinguish b/w a one-dim data set and a coord var of the same name.
    It's less riskier than using a flag and change the file format, I think. -BMR */
    intn   data_offset; /* non-traditional data may not begin at 0 */
    int32  block_size;  /* size of the blocks for unlimited dim. datasets, default -1 */
    int numrecs;    /* number of records this has been filled up to, for unlimited dim */
    int32 aid;    /* aid for DFTAG_SD data */
    int32 HDFtype;    /* type of this variable as HDF thinks */
    int32 HDFsize;    /* size of this variable as HDF thinks */
    /* These next two flags control when space in the file is allocated
        for a new dataset.  They are used (currently) in SDwritedata() and
        hdf_get_vp_aid() to allocate the full length of a new fixed-size dataset
        which is not writing fill values, instead of letting them get created
        as an "appendable" dataset and probably get converted into a linked-
        block special element when they don't need to be one */
    int32   created;    /* BOOLEAN == is newly created */
    int32   set_length; /* BOOLEAN == needs length set */
    int32   is_ragged;  /* BOOLEAN == is a ragged array */
    int32 * rag_list;   /* size of ragged array lines */
    int32   rag_fill;   /* last line in rag_list to be set */
    vix_t * vixHead;    /* list of VXR records for CDF data storage */
} NC_var ;

#define IS_RECVAR(vp) \
    ((vp)->shape != NULL ? (*(vp)->shape == NC_UNLIMITED) : 0 )

#define HDF_FILE     1
#define CDF_FILE     2

HDFLIBAPI const char *cdf_routine_name ; /* defined in lerror.c */

#define MAGICOFFSET  0    /* Offset where format version number is written */

/* Format version number for CDF file */
/* Written twice at the beginning of pre-2.6 CDF file */
#define CDFMAGIC    0x0000FFFF

/* Format version number for HDF file */
#define HDFXMAGIC   0x0e031301   /* ^N^C^S^A */

/* Format version number for link file */
#define NCLINKMAGIC 0x43444c01   /*  C D L 1 */

/* #endif */ /* HDF */

#ifdef __cplusplus
extern "C" {
#endif

#if 0
/* If using the real netCDF library and API (when --disable-netcdf configure flag is used)
   need to mangle the HDF versions of netCDF API function names
   to not conflict w/ oriinal netCDF ones */
#define nc_serror        HNAME(nc_serror)
#define NCadvise         HNAME(NCadvise)
#define NC_computeshapes HNAME(NC_computeshapes)
#define NC_xtypelen      HNAME(NC_xtypelen)
#define NC_xlen_array    HNAME(NC_xlen_array)
#define NC_xlen_attr     HNAME(NC_xlen_attr)
#define NC_xlen_cdf      HNAME(NC_xlen_cdf)
#define NC_xlen_dim      HNAME(NC_xlen_dim)
#define NC_xlen_iarray   HNAME(NC_xlen_iarray)
#define NC_xlen_string   HNAME(NC_xlen_string)
#define NC_xlen_var      HNAME(NC_xlen_var)
#define NCmemset         HNAME(NCmemset)
#define NC_arrayfill     HNAME(NC_arrayfill)
#define NC_copy_arrayvals HNAME(NC_copy_arrayvals)
#define NC_free_array    HNAME(NC_free_array)
#define NC_free_attr     HNAME(NC_free_attr)
#define NC_free_cdf      HNAME(NC_free_cdf)
#define NC_free_dim      HNAME(NC_free_dim)
#define NC_free_iarray   HNAME(NC_free_iarray)
#define NC_free_string   HNAME(NC_free_string)
#define NC_free_var      HNAME(NC_free_var)
#define NC_incr_array    HNAME(NC_incr_array)
#define NC_dimid         HNAME(NC_dimid)
#define NCcktype         HNAME(NCcktype)
#define NC_indefine      HNAME(NC_indefine)
#define xdr_cdf          HNAME(xdr_cdf)
#define xdr_numrecs      HNAME(xdr_numrecs)
#define xdr_shorts       HNAME(xdr_shorts)
#define xdr_NC_array     HNAME(xdr_NC_array)
#define xdr_NC_attr      HNAME(xdr_NC_attr)
#define xdr_NC_dim       HNAME(xdr_NC_dim)
#define xdr_NC_fill      HNAME(xdr_NC_fill)
#define xdr_NC_iarray    HNAME(xdr_NC_iarray)
#define xdr_NC_string    HNAME(xdr_NC_string)
#define xdr_NC_var       HNAME(xdr_NC_var)
#define NC_typelen       HNAME(NC_typelen)
#define NC_check_id      HNAME(NC_check_id)
#define NC_dup_cdf       HNAME(NC_dup_cdf)
#define NC_new_cdf       HNAME(NC_new_cdf)
#define NC_new_array     HNAME(NC_new_array)
#define NC_re_array      HNAME(NC_re_array)
#define NC_new_attr      HNAME(NC_new_attr)
#define NC_findattr      HNAME(NC_findattr)
#define NC_new_dim       HNAME(NC_new_dim)
#define NC_new_iarray    HNAME(NC_new_iarray)
#define NC_new_string    HNAME(NC_new_string)
#define NC_re_string     HNAME(NC_re_string)
#define NC_hlookupvar    HNAME(NC_hlookupvar)
#define NC_new_var       HNAME(NC_new_var)
#define NCvario          HNAME(NCvario)
#define NCcoordck        HNAME(NCcoordck)
#define xdr_NCvshort     HNAME(xdr_NCvshort)
#define NC_dcpy          HNAME(NC_dcpy)
#define NCxdrfile_sync   HNAME(NCxdrfile_sync)
#define NCxdrfile_create HNAME(NCxdrfile_create)
#define NCgenio          HNAME(NCgenio)      /* from putgetg.c */
#define NC_var_shape     HNAME(NC_var_shape) /* from var.c */
#endif /*0*/

HDFLIBAPI void        nc_serror(const char *fmt,...) ;
HDFLIBAPI void        NCadvise            (
    int err,
    const char *fmt,
    ...
) ;

HDFLIBAPI int        NC_computeshapes    (
    NC        *handle
);
HDFLIBAPI int        NC_xtypelen        (
    nc_type    type
);
HDFLIBAPI int        NC_xlen_array        (
    NC_array    *array
);
HDFLIBAPI int        NC_xlen_attr        (
    NC_attr    **app
);
HDFLIBAPI int        NC_xlen_cdf        (
    NC        *cdf
);
HDFLIBAPI int        NC_xlen_dim        (
    NC_dim    **dpp
);
HDFLIBAPI int        NC_xlen_iarray    (
    NC_iarray    *iarray
);
HDFLIBAPI int        NC_xlen_string    (
    NC_string    *cdfstr
);
HDFLIBAPI int        NC_xlen_var        (
    NC_var    **vpp
);

HDFLIBAPI char       *NCmemset        (
    char    *s,
    int        c,
    int        n
);

HDFLIBAPI void       NC_arrayfill        (
    void    *lo,
    size_t    len,
    nc_type    type
);
HDFLIBAPI void       NC_copy_arrayvals    (
    char    *target,
    NC_array    *array
);
HDFLIBAPI int       NC_free_array        (
    NC_array    *array
);
HDFLIBAPI int       NC_free_attr        (
    NC_attr    *attr
);
HDFLIBAPI int       NC_free_cdf        (
    NC        *handle
);
HDFLIBAPI int       NC_free_dim        (
    NC_dim    *dim
);
HDFLIBAPI int       NC_free_iarray    (
    NC_iarray    *iarray
);
HDFLIBAPI int       NC_free_string    (
    NC_string    *cdfstr
);
HDFLIBAPI int       NC_free_var        (
    NC_var    *var
);

HDFLIBAPI Void      *NC_incr_array        (
    NC_array    *array,
    Void    *tail
);

HDFLIBAPI int       NC_dimid               (
    NC          *handle,
    char        *name
);
HDFLIBAPI bool_t     NCcktype        (
    nc_type    datatype
);
HDFLIBAPI bool_t     NC_indefine        (
    int        cdfid,
    bool_t    iserr
);
HDFLIBAPI bool_t     xdr_cdf        (
    XDR        *xdrs,
    NC        **handlep
);
HDFLIBAPI bool_t     xdr_numrecs        (
    XDR        *xdrs,
    NC        *handle
);
HDFLIBAPI bool_t     xdr_shorts        (
    XDR        *xdrs,
    short    *sp,
    u_int    cnt
);
HDFLIBAPI bool_t     xdr_NC_array        (
    XDR        *xdrs,
    NC_array    **app
);
HDFLIBAPI bool_t     xdr_NC_attr        (
    XDR        *xdrs,
    NC_attr    **app
);
HDFLIBAPI bool_t     xdr_NC_dim        (
    XDR        *xdrs,
    NC_dim    **dpp
);
HDFLIBAPI bool_t     xdr_NC_fill        (
    XDR        *xdrs,
    NC_var    *vp
);
HDFLIBAPI bool_t     xdr_NC_iarray        (
    XDR        *xdrs,
    NC_iarray    **ipp
);
HDFLIBAPI bool_t     xdr_NC_string        (
    XDR        *xdrs,
    NC_string    **spp
);
HDFLIBAPI bool_t     xdr_NC_var        (
    XDR        *xdrs,
    NC_var    **vpp
);

HDFLIBAPI size_t     NC_typelen        (
    nc_type    type
);

HDFLIBAPI NC        *NC_check_id        (
    int        cdfid
);
HDFLIBAPI NC        *NC_dup_cdf        (
    const char *name,
    int     mode,
    NC        *old
);
HDFLIBAPI NC        *NC_new_cdf        (
    const char *name,
    int        mode
);
HDFLIBAPI NC_array  *NC_new_array        (
    nc_type    type,
    unsigned    count,
    const void    *values
);
HDFLIBAPI NC_array  *NC_re_array        (
    NC_array    *old,
    nc_type    type,
    unsigned    count,
    const void    *values
);
HDFLIBAPI NC_attr  *NC_new_attr        (
    const char *name,
    nc_type type,
    unsigned count ,
    const void *values
);
HDFLIBAPI NC_attr  **NC_findattr        (
    NC_array    **ap,
    const char    *name
);
HDFLIBAPI NC_dim    *NC_new_dim        (
    const char    *name,
    long    size
);
HDFLIBAPI NC_iarray *NC_new_iarray        (
    unsigned    count,
    const int        values[]
);
HDFLIBAPI NC_string *NC_new_string        (
    unsigned    count,
    const char    *str
);
HDFLIBAPI NC_string *NC_re_string        (
    NC_string    *old,
    unsigned    count,
    const char    *str
);
HDFLIBAPI NC_var    *NC_hlookupvar        (
    NC        *handle,
    int        varid
);
HDFLIBAPI NC_var    *NC_new_var        (
    const char    *name,
    nc_type    type,
    int        ndims,
    const int        *dims
);
HDFLIBAPI int    NCvario            (
    NC *handle,
    int varid,
    const long *start,
    const long *edges,
    void *values
);
HDFLIBAPI bool_t    NCcoordck    (
    NC *handle,
    NC_var *vp,
    const long *coords
);
HDFLIBAPI bool_t xdr_NCvshort    (
        XDR *xdrs,
        unsigned which,
        short *values
);
HDFLIBAPI bool_t    NC_dcpy            (
    XDR *target,
    XDR *source,
    long nbytes
);
HDFLIBAPI int NCxdrfile_sync
    (XDR *xdrs);

HDFLIBAPI int NCxdrfile_create
    (XDR *xdrs,const char *path,int ncmode);

/* this routine is found in 'xdrposix.c' */
HDFLIBAPI void hdf_xdrfile_create
    ( XDR *xdrs, int ncop);

HDFLIBAPI intn hdf_fill_array
    (Void  * storage,int32 len,Void  * value,int32 type);

HDFLIBAPI intn hdf_get_data
    (NC *handle,NC_var *vp);

HDFLIBAPI int32 hdf_get_vp_aid
    (NC *handle, NC_var *vp);

HDFLIBAPI int hdf_map_type
    (nc_type );

HDFLIBAPI nc_type hdf_unmap_type
    (int );

HDFLIBAPI intn hdf_get_ref
    (NC *,int );

HDFLIBAPI intn hdf_create_dim_vdata
    (XDR *,NC *,NC_dim *);

HDFLIBAPI intn hdf_create_compat_dim_vdata
    (XDR *xdrs, NC *handle, NC_dim *dim, int32 dimval_ver);

HDFLIBAPI intn hdf_write_attr
    (XDR *,NC *,NC_attr **);

HDFLIBAPI int32 hdf_write_dim
    (XDR *,NC *,NC_dim **,int32);

HDFLIBAPI int32 hdf_write_var
    (XDR *,NC *,NC_var **);

HDFLIBAPI intn hdf_write_xdr_cdf
    (XDR *,NC **);

HDFLIBAPI intn hdf_conv_scales
    (NC **);

HDFLIBAPI intn hdf_read_dims
    (XDR *,NC *,int32 );

HDFLIBAPI NC_array *hdf_read_attrs
    (XDR *,NC *,int32 );

HDFLIBAPI intn hdf_read_vars
    (XDR *,NC *,int32 );

HDFLIBAPI intn hdf_read_xdr_cdf
    (XDR *,NC **);

HDFLIBAPI intn hdf_xdr_cdf
    (XDR *,NC **);

HDFLIBAPI intn hdf_vg_clobber
    (NC *,int );

HDFLIBAPI intn hdf_cdf_clobber
    (NC *);

HDFLIBAPI intn hdf_close
    (NC *);

HDFLIBAPI intn hdf_read_sds_dims
    (NC *);

HDFLIBAPI intn hdf_read_sds_cdf
    (XDR *,NC **);

HDFLIBAPI intn SDPfreebuf (void);

HDFLIBAPI intn NCgenio
    (NC *handle, int varid, const long *start, const long *count,
        const long *stride, const long *imap, void *values);

HDFLIBAPI intn NC_var_shape
    (NC_var *var,NC_array *dims);

HDFLIBAPI intn NC_reset_maxopenfiles
    (intn req_max);

HDFLIBAPI intn NC_get_maxopenfiles
    ();

HDFLIBAPI intn NC_get_systemlimit
    ();

HDFLIBAPI int NC_get_numopencdfs
    ();

/* CDF stuff. don't need anymore? -GV */
HDFLIBAPI nc_type cdf_unmap_type
    (int type);

HDFLIBAPI bool_t nssdc_read_cdf
    (XDR *xdrs, NC **handlep);

HDFLIBAPI bool_t nssdc_write_cdf
   (XDR *xdrs, NC **handlep);

HDFLIBAPI bool_t nssdc_xdr_cdf
    (XDR *xdrs, NC **handlep);

HDFLIBAPI intn HDiscdf
    (const char *filename);

#ifdef __cplusplus
}
#endif

#endif /* _LOCAL_NC_ */
