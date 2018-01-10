/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
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

#ifndef HSHARED_H
#define HSHARED_H

/* This is the complement to hshared.h that will
   declare prototypes as __declspec(dllexport)
*/

#include "H4api_adpt.h"
#include "atom.h" /* For the types */
#include "hfile.h" /* For the types */
#include "df.h" /* For the types */
#include "dfufp2i.h"

/* Include types from hproto.h */

/* Usefull macros, which someday might become actual functions */
/* Wrappers for Hinquire. feb-2-92 */
#define HQueryfileid(aid, fileid)     \
  (Hinquire ((int32)   aid,  (int32*) fileid, (uint16*) NULL,\
             (uint16*) NULL, (int32*) NULL,   (int32*)  NULL,\
             (int32*)  NULL, (int16*) NULL,   (int16*)  NULL))

#define HQuerytagref(aid, tag, ref) \
  (Hinquire ((int32)   aid,  (int32*) NULL,   (uint16*) tag,\
             (uint16*) ref,  (int32*) NULL,   (int32*)  NULL,\
             (int32*)  NULL, (int16*) NULL,   (int16*)  NULL))

#define HQuerylength(aid, length)     \
  (Hinquire ((int32)    aid, (int32*) NULL, (uint16*) NULL,   \
             (uint16*) NULL, (int32*) length,   (int32*)  NULL,   \
             (int32*)  NULL, (int16*) NULL, (int16*)  NULL))

#define HQueryoffset(aid, offset)     \
  (Hinquire ((int32)    aid, (int32*) NULL, (uint16*) NULL,   \
             (uint16*) NULL, (int32*) NULL,     (int32*)  offset, \
             (int32*)  NULL, (int16*) NULL,     (int16*)  NULL))

#define HQueryposition(aid, position) \
  (Hinquire ((int32)    aid, (int32*) NULL, (uint16*) NULL,   \
             (uint16*) NULL, (int32*) NULL, (int32*)  NULL,   \
             (int32*) position, (int16*) NULL,  (int16*)  NULL))

#define HQueryaccess(aid, access)     \
  (Hinquire ((int32)    aid,    (int32*) NULL,   (uint16*) NULL,  \
             (uint16*) NULL,    (int32*) NULL,   (int32*)  NULL,  \
             (int32*)   NULL,   (int16*) access, (int16*)  NULL))

#define HQueryspecial(aid, special) \
  (Hinquire ((int32)    aid,    (int32*) NULL,  (uint16*) NULL,   \
             (uint16*) NULL,    (int32*) NULL,  (int32*)  NULL,   \
             (int32*)   NULL,   (int16*) NULL,  (int16*)  special))

/*=== HDF_CHUNK_DEF same as in mfhdf.h - moved here  ====*/

/* Bit flags used for SDsetchunk(), SDgetchunkinfo() 
   GRsetchunk() and GRgetchunkinfo(). Note that GRs do not support NBIT */
#define HDF_NONE    0x0
#define HDF_CHUNK   0x1
#define HDF_COMP    0x3
#define HDF_NBIT    0x5

/* Cache flags */
#define HDF_CACHEALL 0x1

/* Chunk Defintion, Note that GRs need only 2 dimensions for the chunk_lengths */
typedef union hdf_chunk_def_u
{
    /* Chunk Lengths only */
    int32   chunk_lengths[H4_MAX_VAR_DIMS]; /* chunk lengths along each dimension */

    struct 
    {   /* For Compression info */
        int32      chunk_lengths[H4_MAX_VAR_DIMS]; /* chunk lengths along each dimension */
        int32      comp_type;    /* Compression type */
        int32      model_type;   /* Compression model type */
        comp_info  cinfo;        /* Compression info struct */
        model_info minfo;        /* Compression model info struct */
    }comp;
        
    struct 
    { /* For NBIT, Used by SDS and not by GR */
        int32 chunk_lengths[H4_MAX_VAR_DIMS]; /* chunk lengths along each dimension */
        intn  start_bit; /* offset of the start bit in the data */
        intn  bit_len;   /* number of bits to store */
        intn  sign_ext;  /* whether to sign extend or not */
        intn  fill_one;  /* whether to fill with 1's or not (0's) */
    } nbit;

} HDF_CHUNK_DEF;

#if defined c_plusplus || defined __cplusplus
extern      "C"
{
#endif                          /* c_plusplus || __cplusplus */

/* It should be the case that hdf4_EXPORTS is true
   when this file is used
*/
#ifndef hdf4_EXPORTS
error: hshared => !hdf4_EXPORTS
#endif

#ifdef _MSV_VER
/* Make HDFPUBLIC be __declspec(dllimport) */
#undef HDFPUBLIC
#define HDFPUBLIC __declspec(dllimport)
#else
#undef HDFPUBLIC
#define HDFPUBLIC extern
#endif /*_MSC_VER*/

#ifndef hfile_EXPORTS

/*
   ** from hfile.c
 */


    HDFPUBLIC int32 Hopen
                (const char *path, intn acc_mode, int16 ndds);

    HDFPUBLIC intn Hclose
                (int32 file_id);

    HDFPUBLIC int32 Hstartread
                (int32 file_id, uint16 tag, uint16 ref);

    HDFPUBLIC intn Hnextread
                (int32 access_id, uint16 tag, uint16 ref, intn origin);

    HDFPUBLIC intn Hexist
                (int32 file_id, uint16 search_tag, uint16 search_ref);

    HDFPUBLIC intn Hinquire
                (int32 access_id, int32 * pfile_id, uint16 * ptag,
          uint16 * pref, int32 * plength, int32 * poffset,
        int32 * pposn, int16 * paccess, int16 * pspecial);

    HDFPUBLIC int32 Hstartwrite
                (int32 file_id, uint16 tag, uint16 ref, int32 length);

    HDFPUBLIC int32 Hstartaccess
                (int32 file_id, uint16 tag, uint16 ref, uint32 flags);

    HDFPUBLIC intn Hsetlength
                (int32 file_id, int32 length);

    HDFPUBLIC intn Happendable
                (int32 aid);

    HDFPUBLIC intn HPisappendable
                (int32 aid);

    HDFPUBLIC intn HPregister_term_func
                (hdf_termfunc_t term_func);

    HDFPUBLIC intn Hseek
                (int32 access_id, int32 offset, intn origin);

    HDFPUBLIC int32 Htell
                (int32 access_id);

    HDFPUBLIC int32 Hread
                (int32 access_id, int32 length, void * data);

    HDFPUBLIC int32 Hwrite
                (int32 access_id, int32 length, const void * data);

    HDFPUBLIC int32 Htrunc
                (int32 access_id, int32 trunc_len);

    HDFPUBLIC intn Hendaccess
                (int32 access_id);

    HDFPUBLIC intn HDgetc
                (int32 access_id);

    HDFPUBLIC intn HDputc
                (uint8 c, int32 access_id);

    HDFPUBLIC int32 Hgetelement
                (int32 file_id, uint16 tag, uint16 ref, uint8 * data);

    HDFPUBLIC int32 Hputelement
                (int32 file_id, uint16 tag, uint16 ref, const uint8 * data, int32 length);

    HDFPUBLIC int32 Hlength
                (int32 file_id, uint16 tag, uint16 ref);

    HDFPUBLIC int32 Hoffset
                (int32 file_id, uint16 tag, uint16 ref);

    HDFPUBLIC intn Hsync
                (int32 file_id);

    HDFPUBLIC intn Hcache
                (int32 file_id, intn cache_on);

    HDFPUBLIC intn Hgetlibversion
                (uint32 * majorv, uint32 * minorv,
                 uint32 * releasev, char * string);

    HDFPUBLIC intn Hgetfileversion
                (int32 file_id, uint32 * majorv, uint32 * minorv,
                 uint32 * release, char * string);

    HDFPUBLIC intn Hsetaccesstype(int32 access_id, uintn accesstype);

    HDFPUBLIC uint16 HDmake_special_tag
                (uint16 tag);

    HDFPUBLIC intn HDis_special_tag
                (uint16 tag);

    HDFPUBLIC uint16 HDbase_tag
                (uint16 tag);

    HDFPUBLIC int  HDerr
                (int32 file_id);

    HDFPUBLIC intn HDvalidfid
                (int32 file_id);

    HDFPUBLIC intn Hgetntinfo
                (const int32 numbertype, hdf_ntinfo_t *nt_info);

    HDFPUBLIC intn Hishdf
                (const char * filename);

    HDFPUBLIC intn Hfidinquire
                (int32 file_id, char ** fname, intn * acc_mode,
                 intn * attach);
    
    HDFPUBLIC intn Hshutdown(void);

    HDFPUBLIC void HPend(void);

    HDFPUBLIC intn HDdont_atexit(void);
#endif /*hfile_EXPORTS*/

#ifndef hfiledd_EXPORTS

/*
   ** from hfiledd.c
 */


/******************************************************************************
 NAME
     Hdupdd - Duplicate a data descriptor

 DESCRIPTION
    Duplicates a data descriptor so that the new tag/ref points to the
    same data element pointed to by the old tag/ref.  Return FAIL if
    the given tag/ref are already in use.

 RETURNS
    returns SUCCEED (0) if successful, FAIL (-1) otherwise

*******************************************************************************/
HDFPUBLIC intn Hdupdd(int32 file_id,      /* IN: File ID the tag/refs are in */
        uint16 tag,             /* IN: Tag of new tag/ref */
        uint16 ref,             /* IN: Ref of new tag/ref */
        uint16 old_tag,         /* IN: Tag of old tag/ref */
        uint16 old_ref          /* IN: Ref of old tag/ref */
);

/******************************************************************************
 NAME
     Hnumber - Determine the number of objects of a given type

 DESCRIPTION
    Determine how many objects of the given tag are in the file.
    tag may be set to DFTAG_WILDCARD to get back the total number
    of objects in the file.

    Note, a return value of zero is not a fail condition.

 RETURNS
    the number of objects of type 'tag' else FAIL

*******************************************************************************/
HDFPUBLIC int32 Hnumber(int32 file_id,    /* IN: File ID the tag/refs are in */
        uint16 tag              /* IN: Tag to count */
);

/******************************************************************************
 NAME
     Hnewref - Returns a ref that is guaranteed to be unique in the file

 DESCRIPTION
    Returns a ref number that can be used with any tag to produce a
    unique tag/ref.  Successive calls to Hnewref will generate a
    strictly increasing sequence until the highest possible ref had been
    returned, then Hnewref will return unused ref's starting from 1.

 RETURNS
    returns the ref number, 0 otherwise

*******************************************************************************/
HDFPUBLIC uint16 Hnewref(int32 file_id        /* IN: File ID the tag/refs are in */
);

/******************************************************************************
 NAME
    Htagnewref  - returns a ref that is unique in the file for a given tag

 DESCRIPTION
    Returns a ref number that can be used with any tag to produce a
    unique tag/ref.  Successive calls to Hnewref will generate a
    strictly increasing sequence until the highest possible ref had been
    returned, then Hnewref will return unused ref's starting from 1.

 RETURNS
    returns the ref number, 0 otherwise

*******************************************************************************/
HDFPUBLIC uint16 Htagnewref(int32 file_id,    /* IN: File ID the tag/refs are in */
        uint16 tag                  /* IN: Tag to search for a new ref for */
);

/******************************************************************************
 NAME
    Hfind - locate the next object of a search in an HDF file

 DESCRIPTION
    Searches for the `next' DD that fits the search tag/ref.  Wildcards
    apply.  If origin is DF_FORWARD, search from current position forwards
    in the file, otherwise DF_BACKWARD searches backward from the current
    position in the file.  If *find_tag and *find_ref are both set to
    0, this indicates the beginning of a search, and the search will
    start from the beginning of the file if the direction is DF_FORWARD
    and from the and of the file if the direction is DF_BACKWARD.

 RETURNS
    returns SUCCEED (0) if successful and FAIL (-1) otherwise

*******************************************************************************/
HDFPUBLIC intn Hfind(int32 file_id,       /* IN: file ID to search in */
        uint16 search_tag,      /* IN: the tag to search for (can be DFTAG_WILDCARD) */
        uint16 search_ref,      /* IN: ref to search for (can be DFREF_WILDCARD) */
        uint16 *find_tag,       /* IN: if (*find_tag==0) and (*find_ref==0) then start search */
                                /* OUT: tag matching the search tag */
        uint16 *find_ref,       /* IN: if (*find_tag==0) and (*find_ref==0) then start search */
                                /* OUT: ref matching the search ref */
        int32 *find_offset,     /* OUT: offset of the data element found */
        int32 *find_length,     /* OUT: length of the data element found */
        intn direction          /* IN: Direction to search in: */
                                /*  DF_FORWARD searches forward from the current location */
                                /*  DF_BACKWARD searches backward from the current location */
);


/******************************************************************************
 NAME
     HDcheck_tagref - Checks to see if tag/ref is in DD list i.e. created already

 DESCRIPTION
     Routine checks to see if tag/ref exists in the DD list i.e. has
     been created.

 RETURNS
     0-> tag/ref does not exist
     1-> tag/ref exists
    -1-> function failed

*******************************************************************************/
HDFPUBLIC intn 
HDcheck_tagref(int32  file_id, /* IN: id of file */
               uint16 tag,     /* IN: Tag to check */
               uint16 ref      /* IN: ref to check */);

/************************************************************************
NAME
   HDreuse_tagref -- reuse a data descriptor preserving tag/ref

DESCRIPTION
   Reuses the data descriptor of tag/ref in the dd list of the file.
   The tag/ref must already exist in the DD list.
   This routine is unsafe and may leave a file in a condition that is
   not usable by some routines.  Use with care. Not valid for
   special elments right now. Used for allowing the data to change
   and move somewhere else in the file for non-special elements.
   Must be carefully if apply to higher-level objects like GR's and SDS
   that are comprised of other objects. 
   Usefull when re-writing simple elements whose size changes while
   preserving the original tag/ref of the element since other elements
   might refer to this element by tag/ref e.g. in a Vgroup.

RETURNS
   returns SUCCEED (0) if successful, FAIL (-1) otherwise
************************************************************************/
HDFPUBLIC intn 
HDreuse_tagref(int32 file_id, /* IN: id of file */
               uint16 tag,    /* IN: tag of data descriptor to reuse */
               uint16 ref     /* IN: ref of data descriptor to reuse */ );

/******************************************************************************
 NAME
     Hdeldd - Delete a data descriptor

 DESCRIPTION
    Deletes a data descriptor of tag/ref from the dd list of the file.
    This routine is unsafe and may leave a file in a condition that is
    not usable by some routines.  Use with care.
    For example, if this element is contained in a Vgroup, that group
    will *NOT* get updated to reflect that this element has been deleted.

 RETURNS
    returns SUCCEED (0) if successful, FAIL (-1) otherwise

*******************************************************************************/
HDFPUBLIC intn Hdeldd(int32 file_id,      /* IN: File ID the tag/refs are in */
        uint16 tag,             /* IN: Tag of tag/ref to delete */
        uint16 ref              /* IN: Ref of tag/ref to delete */
);

#endif /*hfiledd_EXPORTS*/

#ifndef hdfalloc_EXPORTS

/*
   ** from hdfalloc.c
 */


    HDFPUBLIC void * HDmemfill
                (void * dest, const void * src, uint32 item_size, uint32 num_items);

    HDFPUBLIC char *HIstrncpy
                (char * dest, const char * source, intn len);

    HDFPUBLIC int32 HDspaceleft
                (void);

#if defined(MALLOC_CHECK)
    HDFPUBLIC void * HDmalloc
                (uint32 qty);

    HDFPUBLIC void * HDrealloc
                (void * where, uint32 qty);

    HDFPUBLIC void * HDcalloc
                (uint32 n, uint32 size);

    HDFPUBLIC void HDfree
                (void * ptr);

#endif /* defined MALLOC_CHECK */

    HDFPUBLIC char *HDstrdup
                (const char *s);

#endif /*hdfalloc_EXPORTS*/

#ifndef hkit_EXPORTS
    HDFPUBLIC const char *HDfidtoname
                (int32 fid);

    HDFPUBLIC char *HDgettagsname
                (uint16 tag);

    HDFPUBLIC intn HDgettagnum
                (const char *tag_name);

    HDFPUBLIC char *HDgetNTdesc
                (int32 nt);

    HDFPUBLIC intn HDpackFstring
                (char * src, char * dest, intn len);

    HDFPUBLIC const char *HDgettagdesc
                (uint16 tag);

    HDFPUBLIC intn HDflush
                (int32 file_id);

    HDFPUBLIC intn HDc2fstr
                (char * str, intn len);

    HDFPUBLIC char *HDf2cstring
                (_fcd fdesc, intn len);
#endif /*hkit_EXPORTS*/

#ifndef hblocks_EXPORTS

/*
   ** from hblocks.c
 */
    HDFPUBLIC int32 HLcreate
                (int32 file_id, uint16 tag, uint16 ref, int32 block_length,
                 int32 number_blocks);

    HDFPUBLIC intn HLconvert
                (int32 aid, int32 block_length, int32 number_blocks);

    HDFPUBLIC int  HDinqblockinfo
                (int32 aid, int32 *length, int32 *first_length, int32 *block_length,
                 int32 *number_blocks);

    HDFPUBLIC intn HLsetblockinfo
                (int32 aid, int32 block_size, int32 num_blocks);

    HDFPUBLIC intn HLgetblockinfo
                (int32 aid, int32* block_size, int32* num_blocks);

    HDFPUBLIC intn HLgetdatainfo
		(int32 file_id, uint8 *buf, uintn start_block,
		 uintn info_count, int32 *offsetarray, int32 *lengtharray);

#endif /*hblocks_EXPORTS*/

#ifndef hextelt_EXPORTS

/*
   ** from hextelt.c
 */
    HDFPUBLIC int32 HXcreate
                (int32 file_id, uint16 tag, uint16 ref, const char * extern_file_name,
                 int32 offset, int32 start_len);

    HDFPUBLIC intn HXsetcreatedir
                (const char *dir);

    HDFPUBLIC intn HXsetdir
                (const char *dir);
#endif /*hextelt_EXPORTS*/

#ifndef hcomp_EXPORTS

/*
   ** from hcomp.c
 */
    HDFPUBLIC int32 HCcreate
                (int32 file_id, uint16 tag, uint16 ref,
                 comp_model_t model_type, model_info * m_info,
                 comp_coder_t coder_type, comp_info * c_info);

    HDFPUBLIC intn HCPgetcompress
                (int32 file_id, uint16 data_tag, uint16 data_ref, 
		 comp_coder_t *coder_type, comp_info * c_info);

    HDFPUBLIC intn HCPgetcompinfo
                (int32 file_id, uint16 data_tag, uint16 data_ref, 
		 comp_coder_t *coder_type, comp_info * c_info);

    HDFPUBLIC intn HCPgetcomptype
                (int32 file_id, uint16 data_tag, uint16 data_ref, 
		 comp_coder_t *coder_type);

    HDFPUBLIC intn HCPgetdatasize
                (int32 file_id, uint16 data_tag, uint16 data_ref, 
		 int32* comp_size, int32* orig_size);

    HDFPUBLIC intn HCget_config_info ( comp_coder_t coder_type, uint32 *compression_config_info);

    HDFPUBLIC int32 HCPquery_encode_header(comp_model_t model_type, model_info * m_info,
             comp_coder_t coder_type, comp_info * c_info);

    HDFPUBLIC intn HCPencode_header(uint8 *p, comp_model_t model_type, model_info * m_info,
             comp_coder_t coder_type, comp_info * c_info);

    HDFPUBLIC intn HCPdecode_header(uint8 *p, comp_model_t *model_type, model_info * m_info,
             comp_coder_t *coder_type, comp_info * c_info);

#endif /*hcomp_EXPORTS*/

#ifndef cszip_EXPORTS

/*
   ** from cszip.c
 */

     HDFPUBLIC intn HCPsetup_szip_parms ( comp_info *c_info, int32 nt, int32 ncomp, int32 ndims, int32 *dims, int32 *cdims);

#endif /*cszip_EXPORTS*/

#ifndef hbuffer_EXPORTS

/*
   ** from hbuffer.c
 */
    HDFPUBLIC intn HBconvert
                (int32 aid);
#endif /*hbuffer_EXPORTS*/

#ifndef hcompri_EXPORTS

/*
   ** from hcompri.c
 */
    HDFPUBLIC int32 HRPconvert
                (int32 fid, uint16 tag, uint16 ref, int32 xdim, int32 ydim,int16 scheme, comp_info *cinfo, uintn pixel_size);

#endif /*hcompri_EXPORTS*/

#ifndef herr_EXPORTS

/*
   ** from herr.c
 */
    HDFPUBLIC const char *HEstring
                (hdf_err_code_t error_code);

    HDFPUBLIC void HEpush
                (hdf_err_code_t error_code, const char * function_name,
                 const char * file_name, intn line);

    HDFPUBLIC void HEreport
                (const char *,...);

    HDFPUBLIC void HEprint
                (FILE * stream, int32 print_level);

    HDFPUBLIC int16 HEvalue
                (int32 level);

    HDFPUBLIC void HEPclear
                (void);

 	HDFPUBLIC intn HEshutdown(void);
#endif /*herr_EXPORTS*/

#ifndef hbitio_EXPORTS

/*
   ** from hbitio.c
 */
    HDFPUBLIC int32 Hstartbitread
                (int32 file_id, uint16 tag, uint16 ref);

    HDFPUBLIC int32 Hstartbitwrite
                (int32 file_id, uint16 tag, uint16 ref, int32 length);

    HDFPUBLIC intn Hbitappendable
                (int32 bitid);

    HDFPUBLIC intn Hbitwrite
                (int32 bitid, intn count, uint32 data);

    HDFPUBLIC intn Hbitread
                (int32 bitid, intn count, uint32 *data);

    HDFPUBLIC intn Hbitseek
                (int32 bitid, int32 byte_offset, intn bit_offset);

    HDFPUBLIC intn Hgetbit
                (int32 bitid);

    HDFPUBLIC int32 Hendbitaccess
                (int32 bitfile_id, intn flushbit);

    HDFPUBLIC intn HPbitshutdown(void);
#endif /*hbitio_EXPORTS*/

#ifndef dfutil_EXPORTS

/*
 ** from dfutil.c
 */
    HDFPUBLIC uint16 DFfindnextref
                (int32 file_id, uint16 tag, uint16 lref);
#endif /*dfutil_EXPORTS*/

#ifndef dfcomp_EXPORTS
/*
   ** from dfcomp.c
 */
    HDFPUBLIC intn DFputcomp
                (int32 file_id, uint16 tag, uint16 ref, const uint8 * image,
        int32 xdim, int32 ydim, uint8 * palette, uint8 * newpal,
                 int16 scheme, comp_info * cinfo);

    HDFPUBLIC int  DFgetcomp
                (int32 file_id, uint16 tag, uint16 ref, uint8 * image,
                 int32 xdim, int32 ydim, uint16 scheme);
#endif /*dfcomp_EXPORTS*/

#ifndef dfrle_EXPORTS

/*
   ** from dfrle.c
 */
    HDFPUBLIC int32 DFCIrle
                (const void * buf, void * bufto, int32 len);

    HDFPUBLIC int32 DFCIunrle
                (uint8 * buf, uint8 *bufto, int32 outlen, int resetsave);
#endif /*dfrle_EXPORTS*/

#ifndef dfimcomp_EXPORTS

/*
   ** from dfimcomp.c
 */
    HDFPUBLIC void DFCIimcomp
                (int32 xdim, int32 ydim, const uint8 *in, uint8 out[],
                 uint8 in_pal[], uint8 out_pal[], int mode);

    HDFPUBLIC void DFCIunimcomp
                (int32 xdim, int32 ydim, uint8 in[], uint8 out[]);

#endif /*dfimcomp_EXPORTS*/

#ifndef dfjpeg_EXPORTS

/*
   ** from dfjpeg.c
 */

    HDFPUBLIC intn DFCIjpeg
                (int32 file_id, uint16 tag, uint16 ref, int32 xdim, int32 ydim,
                 const void * image, int16 scheme, comp_info * scheme_info);
#endif /*dfjpeg_EXPORTS*/

#ifndef dfunjpeg_EXPORTS

/*
   ** from dfunjpeg.c
 */

    HDFPUBLIC intn DFCIunjpeg
                (int32 file_id, uint16 tag, uint16 ref, void * image, int32 xdim,
                 int32 ydim, int16 scheme);

#endif /*dfunjpeg_EXPORTS*/

#ifndef dfgroup_EXPORTS

/*
   ** from dfgroup.c
 */
    HDFPUBLIC int32 DFdiread
                (int32 file_id, uint16 tag, uint16 ref);

    HDFPUBLIC intn DFdiget
                (int32 list, uint16 * ptag, uint16 * pref);

    HDFPUBLIC intn DFdinobj
                (int32 list);

    HDFPUBLIC int32 DFdisetup
                (int maxsize);

    HDFPUBLIC intn DFdiput
                (int32 list, uint16 tag, uint16 ref);

    HDFPUBLIC intn DFdiwrite
                (int32 file_id, int32 list, uint16 tag, uint16 ref);
                
    HDFPUBLIC void DFdifree
    			(int32 groupID);
#endif /*dfgroup_EXPORTS*/

#ifndef dfp_EXPORTS

/*
   ** from dfp.c
 */
    HDFPUBLIC intn DFPgetpal
                (const char * filename, void * palette);

    HDFPUBLIC intn DFPputpal
                (const char * filename, const void * palette, intn overwrite, const char * filemode);

    HDFPUBLIC intn DFPaddpal
                (const char * filename, const void * palette);

    HDFPUBLIC intn DFPnpals
                (const char * filename);

    HDFPUBLIC intn DFPreadref
                (const char * filename, uint16 ref);

    HDFPUBLIC intn DFPwriteref
                (const char * filename, uint16 ref);

    HDFPUBLIC intn DFPrestart
                (void);

    HDFPUBLIC uint16 DFPlastref
                (void);

#endif /*dfp_EXPORTS*/

#ifndef dfr8_EXPORTS

/*
   ** from dfr8.c
 */
    HDFPUBLIC int  DFR8setcompress
                (int32 scheme, comp_info * cinfo);

    HDFPUBLIC intn DFR8getdims
                (const char * filename, int32 * pxdim, int32 * pydim,
                 int * pispal);

    HDFPUBLIC intn DFR8getimage
                (const char * filename, uint8 * image, int32 xdim, int32 ydim,
                 uint8 * pal);

    HDFPUBLIC intn DFR8setpalette
                (uint8 * pal);

    HDFPUBLIC intn DFR8putimage
                (const char * filename, const void * image, int32 xdim, int32 ydim, uint16 compress);

    HDFPUBLIC intn DFR8addimage
                (const char * filename, const void * image, int32 xdim, int32 ydim, uint16 compress);

    HDFPUBLIC intn DFR8nimages
                (const char * filename);

    HDFPUBLIC intn DFR8readref
                (const char * filename, uint16 ref);

    HDFPUBLIC intn DFR8writeref
                (const char * filename, uint16 ref);

    HDFPUBLIC intn DFR8restart
                (void);

    HDFPUBLIC uint16 DFR8lastref
                (void);

    HDFPUBLIC intn DFR8getpalref(uint16 *pal_ref);

    HDFPUBLIC intn DFR8Pshutdown(void);

#endif /*dfr8_EXPORTS*/

#ifndef dfgr_EXPORTS

/*
   ** from dfgr.c
 */
    HDFPUBLIC intn DFGRgetlutdims
                (const char * filename, int32 * pxdim, int32 * pydim,
                 intn * pncomps, intn * pil);

    HDFPUBLIC intn DFGRreqlutil
                (intn il);

    HDFPUBLIC intn DFGRgetlut
                (const char * filename, void * lut, int32 xdim, int32 ydim);

    HDFPUBLIC intn DFGRgetimdims
                (const char * filename, int32 * pxdim, int32 * pydim,
                 intn * pncomps, intn * pil);

    HDFPUBLIC intn DFGRreqimil
                (intn il);

    HDFPUBLIC intn DFGRgetimage
                (const char * filename, void * image, int32 xdim, int32 ydim);

    HDFPUBLIC intn DFGRsetcompress
                (int32 scheme, comp_info * cinfo);

    HDFPUBLIC intn DFGRsetlutdims
                (int32 xdim, int32 ydim, intn ncomps, intn il);

    HDFPUBLIC intn DFGRsetlut
                (void * lut, int32 xdim, int32 ydim);

    HDFPUBLIC intn DFGRaddlut
                (const char * filename, void * lut, int32 xdim, int32 ydim);

    HDFPUBLIC intn DFGRsetimdims
                (int32 xdim, int32 ydim, intn ncomps, intn il);

    HDFPUBLIC intn DFGRaddimage
                (const char * filename, void * image, int32 xdim, int32 ydim);

    HDFPUBLIC intn DFGRputimage
                (const char * filename, void * image, int32 xdim, int32 ydim);

    HDFPUBLIC intn DFGRreadref
                (const char * filename, uint16 ref);

    HDFPUBLIC uint16 DFGRIlastref
                (void);

    HDFPUBLIC intn DFGRIgetdims
                (const char * filename, int32 * pxdim, int32 * pydim,
                 intn * pncomps, intn * pil, intn type);

    HDFPUBLIC intn DFGRIreqil
                (intn il, intn type);

    HDFPUBLIC intn DFGRIgetimlut
                (const char * filename, void * imlut, int32 xdim, int32 ydim, intn type,
                 intn isfortran, int *compressed, uint16 *compr_type, int *has_pal);

    HDFPUBLIC intn DFGRIsetdims
                (int32 xdim, int32 ydim, intn ncomps, intn type);

    HDFPUBLIC intn DFGRIsetil
                (intn il, intn type);

    HDFPUBLIC intn DFGRIrestart
                (void);

    HDFPUBLIC intn DFGRIaddimlut
                (const char * filename, const void * imlut, int32 xdim, int32 ydim, intn type,
                 intn isfortran, intn newfile);

    HDFPUBLIC intn DFGRPshutdown(void);

#endif /*dfgr_EXPORTS*/

#ifndef df24_EXPORTS

/*
   ** from df24.c
 */
    HDFPUBLIC intn DF24getdims
                (const char * filename, int32 * pxdim, int32 * pydim,
                 intn * pil);

    HDFPUBLIC intn DF24reqil
                (intn il);

    HDFPUBLIC intn DF24getimage
                (const char * filename, void * image, int32 xdim, int32 ydim);

    HDFPUBLIC intn DF24setdims
                (int32 xdim, int32 ydim);

    HDFPUBLIC intn DF24setil
                (intn il);

    HDFPUBLIC intn DF24setcompress
                (int32 type, comp_info * cinfo);

    HDFPUBLIC intn DF24restart
                (void);

    HDFPUBLIC intn DF24addimage
                (const char * filename, const void * image, int32 xdim, int32 ydim);

    HDFPUBLIC intn DF24putimage
                (const char * filename, const void * image, int32 xdim, int32 ydim);

    HDFPUBLIC intn DF24nimages
                (const char * filename);

    HDFPUBLIC intn DF24readref
                (const char * filename, uint16 ref);

    HDFPUBLIC uint16 DF24lastref
                (void);

#endif /*df24_EXPORTS*/

#ifndef dfan_EXPORTS

/*
   ** from dfan.c
 */

    HDFPUBLIC int32 DFANgetlablen
                (const char * filename, uint16 tag, uint16 ref);

    HDFPUBLIC intn DFANgetlabel
                (const char * filename, uint16 tag, uint16 ref, char * label,
                 int32 maxlen);

    HDFPUBLIC int32 DFANgetdesclen
                (const char * filename, uint16 tag, uint16 ref);

    HDFPUBLIC intn DFANgetdesc
                (const char * filename, uint16 tag, uint16 ref, char * desc,
                 int32 maxlen);

    HDFPUBLIC int32 DFANgetfidlen
                (int32 file_id, intn isfirst);

    HDFPUBLIC int32 DFANgetfid
                (int32 file_id, char * id, int32 maxlen, intn isfirst);

    HDFPUBLIC int32 DFANgetfdslen
                (int32 file_id, intn isfirst);

    HDFPUBLIC int32 DFANgetfds
                (int32 file_id, char * desc, int32 maxlen, intn isfirst);

    HDFPUBLIC intn DFANputlabel
                (const char * filename, uint16 tag, uint16 ref, char * label);

    HDFPUBLIC intn DFANputdesc
                (const char * filename, uint16 tag, uint16 ref, char * desc,
                 int32 desclen);

    HDFPUBLIC intn DFANaddfid
                (int32 file_id, char * id);

    HDFPUBLIC intn DFANaddfds
                (int32 file_id, char * desc, int32 desclen);

    HDFPUBLIC uint16 DFANlastref
                (void);

    HDFPUBLIC intn DFANlablist
                (const char * filename, uint16 tag, uint16 reflist[],
         char * labellist, intn listsize, intn maxlen, intn startpos);

    HDFPUBLIC intn DFANclear
                (void);

    HDFPUBLIC intn DFANIclear
                (void);

    HDFPUBLIC uint16 DFANIlocate
                (int32 file_id, int type, uint16 tag, uint16 ref);

    HDFPUBLIC int  DFANIaddentry
                (int type, uint16 annref, uint16 datatag, uint16 dataref);

    HDFPUBLIC int32 DFANIgetannlen
                (const char * filename, uint16 tag, uint16 ref, int type);

    HDFPUBLIC intn DFANIgetann
                (const char * filename, uint16 tag, uint16 ref, uint8 * ann,
                 int32 maxlen, int type, int isfortran);

    HDFPUBLIC intn DFANIputann
                (const char * filename, uint16 tag, uint16 ref, uint8 * ann,
                 int32 annlen, int type);

    HDFPUBLIC int  DFANIlablist
                (const char * filename, uint16 tag, uint16 reflist[],
            uint8 * labellist, int listsize, int maxlen, int startpos,
                 int isfortran);

    HDFPUBLIC int  DFANIaddfann
                (int32 file_id, char * ann, int32 annlen, int type);

    HDFPUBLIC int32 DFANIgetfannlen
                (int32 file_id, int type, int isfirst);

    HDFPUBLIC int32 DFANIgetfann
                (int32 file_id, char * ann, int32 maxlen, int type, int isfirst);

    HDFPUBLIC intn DFANPshutdown(void);

#endif /*dfan_EXPORTS*/

#ifndef dfsd_EXPORTS

/*
   ** from dfsd.c
 */

    HDFPUBLIC int  DFSDgetdims
                (const char * filename, intn * prank, int32 sizes[], intn maxrank);

    HDFPUBLIC int  DFSDgetdatastrs
                (char * label, char * unit, char * format, char * coordsys);

    HDFPUBLIC int  DFSDgetdimstrs
                (int dim, char * label, char * unit, char * format);

    HDFPUBLIC int  DFSDgetdatalen
                (int * llabel, int * lunit, int * lformat, int * lcoordsys);

    HDFPUBLIC int  DFSDgetdimlen
                (int dim, int * llabel, int * lunit, int * lformat);

    HDFPUBLIC int  DFSDgetdimscale
                (intn dim, int32 maxsize, void * scale);

    HDFPUBLIC int  DFSDgetrange
                (void * pmax, void * pmin);

    HDFPUBLIC int  DFSDgetdata
                (const char * filename, intn rank, int32 maxsizes[], void * data);

    HDFPUBLIC int  DFSDsetlengths
                (int maxlen_label, int maxlen_unit, int maxlen_format,
                 int maxlen_coordsys);

    HDFPUBLIC int  DFSDsetdims
                (intn rank, int32 dimsizes[]);

    HDFPUBLIC int  DFSDsetdatastrs
                (const char * label, const char * unit, const char * format, const char * coordsys);

    HDFPUBLIC int  DFSDsetdimstrs
                (int dim, const char * label, const char * unit, const char * format);

    HDFPUBLIC int  DFSDsetdimscale
                (intn dim, int32 dimsize, void * scale);

    HDFPUBLIC int  DFSDsetrange
                (void * maxi, void * mini);

    HDFPUBLIC int  DFSDputdata
                (const char * filename, intn rank, int32 dimsizes[], void * data);

    HDFPUBLIC int  DFSDadddata
                (const char * filename, intn rank, int32 dimsizes[], void * data);

    HDFPUBLIC int  DFSDrestart
                (void);

    HDFPUBLIC int32 DFSDndatasets
                (char * filename);

    HDFPUBLIC int  DFSDclear
                (void);

    HDFPUBLIC uint16 DFSDlastref
                (void);

    HDFPUBLIC int  DFSDreadref
                (char * filename, uint16 ref);

    HDFPUBLIC int  DFSDgetslice
                (const char * filename, int32 winst[], int32 windims[], void * data,
                 int32 dims[]);

    HDFPUBLIC int  DFSDstartslice
                (const char * filename);

    HDFPUBLIC int  DFSDputslice
                (int32 winend[], void * data, int32 dims[]);

    HDFPUBLIC int  DFSDendslice
                (void);

    HDFPUBLIC int  DFSDsetNT
                (int32 numbertype);

    HDFPUBLIC int  DFSDsetorder
                (int arrayorder);

    HDFPUBLIC int  DFSDgetNT
                (int32 * pnumbertype);

    HDFPUBLIC intn DFSDpre32sdg
                (char * filename, uint16 ref, intn * ispre32);

    HDFPUBLIC int  DFSDsetcal
                (float64 cal, float64 cal_err, float64 ioff,
                 float64 ioff_err, int32 cal_nt);

    HDFPUBLIC int  DFSDgetcal
                (float64 * pcal, float64 * pcal_err, float64 * pioff,
                 float64 * pioff_err, int32 * cal_nt);

    HDFPUBLIC int  DFSDwriteref
                (const char * filename, uint16 ref);

    HDFPUBLIC int  DFSDsetfillvalue
                (void * fill_value);

    HDFPUBLIC int  DFSDgetfillvalue
                (void * fill_value);

    HDFPUBLIC int  DFSDstartslab
                (const char * filename);

    HDFPUBLIC int  DFSDwriteslab
                (int32 start[], int32 stride[], int32 count[],
                 void * data);

    HDFPUBLIC int  DFSDendslab
                (void);

    HDFPUBLIC int  DFSDreadslab
                (const char *filename, int32 start[], int32 slab_size[],
             int32 stride[], void * buffer, int32 buffer_size[]);

    HDFPUBLIC intn DFSDPshutdown(void);

#endif /*dfsd_EXPORTS*/

#ifndef dfconv_EXPORTS

/*
   ** from dfconv.c
 */

    HDFPUBLIC int  DFKNTsize
                (int32 number_type);

    HDFPUBLIC int32 DFKisnativeNT
                (int32 numbertype);

    HDFPUBLIC int32 DFKislitendNT
                (int32 numbertype);

    HDFPUBLIC int8 DFKgetPNSC
                (int32 numbertype, int32 machinetype);

    HDFPUBLIC intn DFKsetNT
                (int32 ntype);

    HDFPUBLIC int32 DFKconvert
                (void * source, void * dest, int32 ntype, int32 num_elm,
                 int16 acc_mode, int32 source_stride, int32 dest_stride);

#endif /*dfconv_EXPORTS*/

#ifndef dfknat_EXPORTS

/*
   ** from dfknat.c
 */

    HDFPUBLIC intn DFKnb1b
                (void * s, void * d, uint32 num_elm, uint32 source_stride, uint32 dest_stride);

    HDFPUBLIC intn DFKnb2b
                (void * s, void * d, uint32 num_elm, uint32 source_stride, uint32 dest_stride);

    HDFPUBLIC intn DFKnb4b
                (void * s, void * d, uint32 num_elm, uint32 source_stride, uint32 dest_stride);

    HDFPUBLIC intn DFKnb8b
                (void * s, void * d, uint32 num_elm, uint32 source_stride, uint32 dest_stride);

#endif /*dfknat_EXPORTS*/

#ifndef dfkswap_EXPORTS

/*
   ** from dfkswap.c
 */

    HDFPUBLIC intn DFKsb2b
                (void * s, void * d, uint32 num_elm, uint32 source_stride, uint32 dest_stride);

    HDFPUBLIC intn DFKsb4b
                (void * s, void * d, uint32 num_elm, uint32 source_stride, uint32 dest_stride);

    HDFPUBLIC intn DFKsb8b
                (void * s, void * d, uint32 num_elm, uint32 source_stride, uint32 dest_stride);

#endif /*dfkswap_EXPORTS*/

#ifndef mfan_EXPORTS

/* Multi-file Annotation C-routines found in mfan.c */
HDFPUBLIC int32 ANstart(int32 file_id);

HDFPUBLIC intn  ANfileinfo(int32 an_id, int32 *n_file_label, int32 *n_file_desc,
                        int32 *n_obj_label, int32 *n_obj_desc);

HDFPUBLIC int32 ANend(int32 an_id);

HDFPUBLIC int32 ANcreate(int32 an_id, uint16 elem_tag, uint16 elem_ref, 
                      ann_type type);

HDFPUBLIC int32 ANcreatef(int32 an_id, ann_type type);

HDFPUBLIC int32 ANselect(int32 an_id, int32 idx, ann_type type);

HDFPUBLIC intn  ANnumann(int32 an_id, ann_type type, uint16 elem_tag, 
                      uint16 elem_ref);

HDFPUBLIC intn  ANannlist(int32 an_id, ann_type type, uint16 elem_tag, 
                       uint16 elem_ref, int32 ann_list[]);

HDFPUBLIC int32 ANannlen(int32 ann_id);

HDFPUBLIC int32 ANwriteann(int32 ann_id, const char *ann, int32 annlen);

HDFPUBLIC int32 ANreadann(int32 ann_id, char *ann, int32 maxlen);

HDFPUBLIC intn  ANendaccess(int32 ann_id);

HDFPUBLIC int32 ANget_tagref(int32 an_id, int32 idx, ann_type type,
                          uint16 *ann_tag, uint16 *ann_ref);

HDFPUBLIC int32 ANid2tagref(int32 an_id, uint16 *ann_tag, uint16 *ann_ref);

HDFPUBLIC int32 ANtagref2id(int32 an_id, uint16 ann_tag, uint16 ann_ref);

HDFPUBLIC uint16 ANatype2tag(ann_type atype);

HDFPUBLIC ann_type ANtag2atype(uint16 atag);

/* BMR: Removed because this function is meant to be private.
HDFPUBLIC intn ANdestroy(void); */ 

#endif /*mfan_EXPORTS*/

#ifndef mfgr_EXPORTS

/* Multi-file Raster C-routines found in mfgr.c */
HDFPUBLIC intn rigcompare(void * k1, void * k2, intn cmparg);

HDFPUBLIC int32 GRstart(int32 hdf_file_id);

HDFPUBLIC intn GRfileinfo(int32 grid,int32 *n_datasets,int32 *n_attrs);

HDFPUBLIC intn GRend(int32 grid);

HDFPUBLIC int32 GRcreate(int32 grid,const char *name,int32 ncomp,int32 nt,int32 il,
    int32 dimsizes[2]);

HDFPUBLIC int32 GRselect(int32 grid,int32 idx);

HDFPUBLIC int32 GRnametoindex(int32 grid,const char *name);

HDFPUBLIC intn GRgetiminfo(int32 riid,char *name,int32 *ncomp,int32 *nt,int32 *il,
    int32 dimsizes[2],int32 *n_attr);

HDFPUBLIC intn GRgetnluts(int32 riid);

HDFPUBLIC intn GRwriteimage(int32 riid,int32 start[2],int32 stride[2],
    int32 count[2],void * data);

HDFPUBLIC intn GRreadimage(int32 riid,int32 start[2],int32 stride[2],
    int32 count[2],void * data);

HDFPUBLIC intn GRendaccess(int32 riid);

HDFPUBLIC uint16 GRidtoref(int32 riid);

HDFPUBLIC int32 GRreftoindex(int32 grid,uint16 ref);

HDFPUBLIC intn GRreqlutil(int32 riid,intn il);

HDFPUBLIC intn GRreqimageil(int32 riid,intn il);

HDFPUBLIC int32 GRgetlutid(int32 riid,int32 idx);

HDFPUBLIC uint16 GRluttoref(int32 lutid);

HDFPUBLIC intn GRgetlutinfo(int32 riid,int32 *ncomp,int32 *nt,
    int32 *il,int32 *nentries);

HDFPUBLIC intn GRwritelut(int32 riid,int32 ncomps,int32 nt,
    int32 il,int32 nentries,void * data);

HDFPUBLIC intn GRreadlut(int32 lutid,void * data);

HDFPUBLIC intn GRsetexternalfile(int32 riid,const char *filename,int32 offset);

HDFPUBLIC intn GRsetaccesstype(int32 riid,uintn accesstype);

HDFPUBLIC intn GRsetcompress(int32 riid,comp_coder_t comp_type,comp_info *cinfo);

HDFPUBLIC intn GRgetcompress(int32 riid,comp_coder_t* comp_type,comp_info *cinfo);

HDFPUBLIC intn GRgetcompinfo(int32 riid,comp_coder_t* comp_type,comp_info *cinfo);

HDFPUBLIC intn GRsetattr(int32 id,const char *name,int32 attr_nt,int32 count,const void * data);

HDFPUBLIC intn GRattrinfo(int32 id,int32 idx,char *name,int32 *attr_nt,int32 *count);

HDFPUBLIC intn GRgetattr(int32 id,int32 idx,void * data);

HDFPUBLIC int32 GRfindattr(int32 id,const char *name);

HDFPUBLIC intn GRgetcomptype (int32 riid, comp_coder_t *comp_type);

HDFPUBLIC intn GRPshutdown(void);

/* This function was added for hmap project only.  Feb-25-2011 */
HDFPUBLIC intn GR2bmapped(int32 riid, intn *tobe_mapped, intn *created_byGR);

/*=== GR Chunking Routines  ====*/

/******************************************************************************
 NAME
      GRsetchunk   -- make GR a chunked GR

 DESCRIPTION
      This routine makes the GR a chunked GR according to the chunk
      definition passed in.

      The image currently cannot be special already.  i.e. NBIT,
      COMPRESSED, or EXTERNAL. This is an Error.

      The defintion of the HDF_CHUNK_DEF union with relvant fields is:

      typedef union hdf_chunk_def_u
      {
         int32   chunk_lengths[2];  Chunk lengths along each dimension

         struct 
          {   
            int32     chunk_lengths[2]; Chunk lengths along each dimension
            int32     comp_type;                   Compression type 
            comp_info cinfo;                       Compression info struct 
          }comp;

      } HDF_CHUNK_DEF

      The simplist is the 'chunk_lengths' array specifiying chunk 
      lengths for each dimension where the 'flags' argument set to 
      'HDF_CHUNK';

      COMPRESSION is set by using the 'HDF_CHUNK_DEF' structure to set the
      appropriate compression information along with the required chunk lengths
      for each dimension. The compression information is the same as 
      that set in 'SDsetcompress()'. The bit-or'd'flags' argument' is set to 
      'HDF_CHUNK | HDF_COMP'.

      See the example in pseudo-C below for further usage.

      The maximum number of Chunks in an HDF file is 65,535.

      The performance of the GRxxx interface with chunking is greatly
      affected by the users access pattern over the image and by
      the maximum number of chunks set in the chunk cache. The cache contains 
      the Least Recently Used(LRU cache replacment policy) chunks. See the
      routine GRsetchunkcache() for further info on the chunk cache and how 
      to set the maximum number of chunks in the chunk cache. A default chunk 
      cache is always created.

      The following example shows the organization of chunks for a 2D iamge.
      e.g. 4x4 image with 2x2 chunks. The array shows the layout of
           chunks in the chunk array.

            4 ---------------------                                           
              |         |         |                                                 
        Y     |  (0,1)  |  (1,1)  |                                       
        ^     |         |         |                                      
        |   2 ---------------------                                       
        |     |         |         |                                               
        |     |  (0,0)  |  (1,0)  |                                      
        |     |         |         |                                           
        |     ---------------------                                         
        |     0         2         4                                       
        ---------------> X                                                       
                                                                                
        --Without compression--:
        {                                                                    
        HDF_CHUNK_DEF chunk_def;
                                                                            
        .......                                                                    
        -- Set chunk lengths --                                                    
        chunk_def.chunk_lengths[0]= 2;                                                     
        chunk_def.chunk_lengths[1]= 2; 

        -- Set Chunking -- 
        GRsetchunk(riid, chunk_def, HDF_CHUNK);                      
         ......                                                                  
        }                                                                           

        --With compression--:
        {                                                                    
        HDF_CHUNK_DEF chunk_def;
                                                                            
        .......                
        -- Set chunk lengths first --                                                    
        chunk_def.chunk_lengths[0]= 2;                                                     
        chunk_def.chunk_lengths[1]= 2;

        -- Set compression --
        chunk_def.comp.cinfo.deflate.level = 9;
        chunk_def.comp.comp_type = COMP_CODE_DEFLATE;

        -- Set Chunking with Compression --
        GRsetchunk(riid, chunk_def, HDF_CHUNK | HDF_COMP);                      
         ......                                                                  
        }                                                                           

 RETURNS
        SUCCEED/FAIL
******************************************************************************/
HDFPUBLIC intn GRsetchunk
    (int32 riid,             /* IN: raster access id */
     HDF_CHUNK_DEF chunk_def, /* IN: chunk definition */
     int32 flags              /* IN: flags */);

/******************************************************************************
 NAME
     GRgetchunkinfo -- get Info on GR

 DESCRIPTION
     This routine gets any special information on the GR. If its chunked,
     chunked and compressed or just a regular GR. Currently it will only
     fill the array of chunk lengths for each dimension as specified in
     the 'HDF_CHUNK_DEF' union. You can pass in a NULL for 'chunk_def'
     if don't want the chunk lengths for each dimension.
     Additionaly if successfull it will return a bit-or'd value in 'flags' 
     indicating if the GR is:

     Chunked                  -> flags = HDF_CHUNK
     Chunked and compressed   -> flags = HDF_CHUNK | HDF_COMP 
     Non-chunked              -> flags = HDF_NONE
  
     e.g. 4x4 array - Pseudo-C
     {
     int32   rcdims[3];
     HDF_CHUNK_DEF rchunk_def;
     int32   cflags;
     ...
     rchunk_def.chunk_lengths = rcdims;
     GRgetchunkinfo(riid, &rchunk_def, &cflags);
     ...
     }

 RETURNS
        SUCCEED/FAIL
******************************************************************************/
HDFPUBLIC intn GRgetchunkinfo
    (int32 riid,              /* IN: Raster access id */
     HDF_CHUNK_DEF *chunk_def, /* IN/OUT: chunk definition */
     int32 *flags              /* IN/OUT: flags */);


/******************************************************************************
 NAME
     GRwritechunk  -- write the specified chunk to the GR

 DESCRIPTION
     This routine writes a whole chunk of data to the chunked GR 
     specified by chunk 'origin' for the given GR and can be used
     instead of GRwriteimage() when this information is known. This
     routine has less overhead and is much faster than using GRwriteimage().

     Origin specifies the co-ordinates of the chunk according to the chunk
     position in the overall chunk array.

     'datap' must point to a whole chunk of data.

     See GRsetchunk() for a description of the organization of chunks in an GR.

 RETURNS
        SUCCEED/FAIL
******************************************************************************/
HDFPUBLIC intn GRwritechunk
    (int32 riid,      /* IN: raster access id */
     int32 *origin,    /* IN: origin of chunk to write */
     const void *datap /* IN: buffer for data */);

/******************************************************************************
 NAME
     GRreadchunk   -- read the specified chunk to the GR

 DESCRIPTION
     This routine reads a whole chunk of data from the chunked GR
     specified by chunk 'origin' for the given GR and can be used
     instead of GRreadimage() when this information is known. This
     routine has less overhead and is much faster than using GRreadimage().

     Origin specifies the co-ordinates of the chunk according to the chunk
     position in the overall chunk array.

     'datap' must point to a whole chunk of data.

     See GRsetchunk() for a description of the organization of chunks in an GR.

 RETURNS
        SUCCEED/FAIL
******************************************************************************/
HDFPUBLIC intn GRreadchunk
    (int32 riid,      /* IN: raster access id */
     int32 *origin,    /* IN: origin of chunk to read */
     void  *datap      /* IN/OUT: buffer for data */);


/******************************************************************************
NAME
     GRsetchunkcache -- maximum number of chunks to cache 

DESCRIPTION
     Set the maximum number of chunks to cache.

     The cache contains the Least Recently Used(LRU cache replacment policy) 
     chunks. This routine allows the setting of maximum number of chunks that 
     can be cached, 'maxcache'.

     The performance of the GRxxx interface with chunking is greatly
     affected by the users access pattern over the image and by
     the maximum number of chunks set in the chunk cache. The number chunks 
     that can be set in the cache is process memory limited. It is a good 
     idea to always set the maximum number of chunks in the cache as the 
     default heuristic does not take into account the memory available for 
     the application.

     By default when the GR is promoted to a chunked element the 
     maximum number of chunks in the cache 'maxcache' is set to the number of
     chunks along the last dimension.

     The values set here affects the current object's caching behaviour.

     If the chunk cache is full and 'maxcache' is greater then the
     current 'maxcache' value, then the chunk cache is reset to the new
     'maxcache' value, else the chunk cache remains at the current
     'maxcache' value.

     If the chunk cache is not full, then the chunk cache is set to the
     new 'maxcache' value only if the new 'maxcache' value is greater than the
     current number of chunks in the cache.

     Use flags argument of 'HDF_CACHEALL' if the whole object is to be cached 
     in memory, otherwise pass in zero(0). Currently you can only
     pass in zero.

    See GRsetchunk() for a description of the organization of chunks in an GR.

RETURNS
     Returns the 'maxcache' value for the chunk cache if successful 
     and FAIL otherwise
******************************************************************************/
HDFPUBLIC intn GRsetchunkcache
    (int32 riid,     /* IN: raster access id */
     int32 maxcache,  /* IN: max number of chunks to cache */
     int32 flags      /* IN: flags = 0, HDF_CACHEALL */);

#ifndef HAVE_FMPOOL
/******************************************************************************
NAME
     Hmpset - set pagesize and maximum number of pages to cache on next open/create

DESCRIPTION
     Set the pagesize and maximum number of pages to cache on the next 
     open/create of a file. A pagesize that is a power of 2 is recommended.

     The values set here only affect the next open/creation of a file and
     do not change a particular file's paging behaviour after it has been
     opened or created. This maybe changed in a later release.

     Use flags arguement of 'MP_PAGEALL' if the whole file is to be cached 
     in memory otherwise passs in zero.

RETURNS
     Returns SUCCEED if successful and FAIL otherwise

NOTE
     This calls the real routine MPset().
     Currently 'maxcache' has to be greater than 1. Maybe use special 
     case of 0 to specify you want to turn page buffering off or use
     the flags arguement. 

******************************************************************************/
HDFPUBLIC int  Hmpset(int pagesize, /* IN: pagesize to use for next open/create */
                   int maxcache, /* IN: max number of pages to cache */
                   int flags     /* IN: flags = 0, MP_PAGEALL */);

/******************************************************************************
NAME
     Hmpget - get last pagesize and max number of pages cached for open/create

DESCRIPTION
     This gets the last pagesize and maximum number of pages cached for 
     the last open/create of a file.

RETURNS
     Returns SUCCEED.

NOTES
     This routine calls the real routine MPget().
******************************************************************************/
HDFPUBLIC int  Hmpget(int *pagesize, /*OUT: pagesize to used in last open/create */
                   int *maxcache, /*OUT: max number of pages cached in last open/create */
                   int flags      /* IN: */);

#endif /* HAVE_FMPOOL */

#endif /*mfgr_EXPORTS*/


/* Vset interface functions (used to be in vproto.h) */

/* Useful macros, which someday might become actuall functions */
/*
 * macros for VSinquire
 * all these macros should be public for users
 */
#define VSQuerycount(vs, count) \
        (VSinquire (vs, (int32 *) count, (int32*) NULL, (char*) NULL, (int32*) NULL, (char*) NULL))

#define VSQueryinterlace(vs, intr) \
        (VSinquire (vs, (int32 *) NULL, (int32*) intr, (char*) NULL, (int32*) NULL, (char*) NULL))

#define VSQueryfields(vs, flds) \
        (VSinquire (vs, (int32 *) NULL, (int32*) NULL, (char*) flds, (int32*) NULL, (char*) NULL))

#define VSQueryvsize(vs, size) \
        (VSinquire (vs, (int32 *) NULL, (int32*) NULL, (char*) NULL, (int32*) size, (char*) NULL))

#define VSQueryname(vs, name) \
        (VSinquire (vs, (int32 *) NULL, (int32*) NULL, (char*) NULL, (int32*) NULL, (char*) name))

#ifndef vattr_EXPORTS

/* 
   ** from vattr.c
 */
   HDFPUBLIC intn Vsetattr
                (int32 vgid,  const char *attrname, int32 datatype,
                 int32 count, const void * values);
   HDFPUBLIC intn Vnattrs
                (int32 vgid);
   HDFPUBLIC intn Vnattrs2
                (int32 vgid);
   HDFPUBLIC intn Vnoldattrs
                (int32 vgid);
   HDFPUBLIC intn Vfindattr
                (int32 vgid, const char *attrname);
   HDFPUBLIC intn Vattrinfo
                (int32 vgid, intn attrindex, char *name, 
                 int32 *datatype, int32 *count, int32 *size);
   HDFPUBLIC intn Vattrinfo2 /* copy of Vattrinfo for old attributes */
                (int32 vgid, intn attrindex, char *name, int32 *datatype,
		 int32 *count, int32 *size, int32 *nfields, uint16 *refnum);
   HDFPUBLIC intn Vgetattr
                (int32 vgid, intn attrindex, void * values);
   HDFPUBLIC intn Vgetattr2 /* copy of Vgetattr for old attributes */
                (int32 vgid, intn attrindex, void * values);
   HDFPUBLIC int32 Vgetversion
                (int32 vgid);
   HDFPUBLIC intn VSfindex
                 (int32 vsid, const char *fieldname, int32 *fldindex);
   HDFPUBLIC intn VSsetattr
                (int32 vsid, int32 findex, const char *attrname,
                 int32 datatype, int32 count, const void * values);
   HDFPUBLIC intn VSnattrs
                (int32 vsid);
   HDFPUBLIC intn VSfnattrs
                (int32 vsid, int32 findex);
   HDFPUBLIC intn VSfindattr
                (int32 vsid, int32 findex, const char *attrname);
   HDFPUBLIC intn VSattrinfo
                (int32 vsid, int32 findex, intn attrindex,
                 char *name, int32 *datatype, int32 *count, 
                 int32 *size);
   HDFPUBLIC intn VSgetattr
                (int32 vsid, int32 findex, intn attrindex,
                  void * values);
   HDFPUBLIC intn VSisattr
                (int32 vsid);
#endif /*vattr_EXPORTS*/

#ifndef vconv_EXPORTS

/*
   ** from vconv.c
 */
    HDFPUBLIC int32 vicheckcompat
                (HFILEID f);

    HDFPUBLIC int32 vimakecompat
                (HFILEID f);

    HDFPUBLIC int32 vcheckcompat
                (char  * fs);

    HDFPUBLIC int32 vmakecompat
                (char  * fs);

#endif /*vconv_EXPORTS*/

#ifndef vg_EXPORTS

/*
   ** from vg.c
 */
    HDFPUBLIC int32 VSelts
                (int32 vkey);

    HDFPUBLIC int32 VSgetinterlace
                (int32 vkey);

    HDFPUBLIC intn VSsetinterlace
                (int32 vkey, int32 interlace);

    HDFPUBLIC int32 VSgetfields
                (int32 vkey, char  * fields);

    HDFPUBLIC intn VSfexist
                (int32 vkey, char  * fields);

    HDFPUBLIC int32 VSsizeof
                (int32 vkey, char  * fields);

    HDFPUBLIC void VSdump
                (int32 vkey);

    HDFPUBLIC int32 VSsetname
                (int32 vkey, const char  * vsname);

    HDFPUBLIC int32 VSsetclass
                (int32 vkey, const char  * vsclass);

    HDFPUBLIC int32 VSgetname
                (int32 vkey, char  * vsname);

    HDFPUBLIC int32 VSgetclass
                (int32 vkey, char  * vsclass);

    HDFPUBLIC intn VSinquire
                (int32 vkey, int32  * nelt, int32  * interlace,
           char  * fields, int32  * eltsize, char  * vsname);

    HDFPUBLIC intn VSisinternal
                (const char  *vsclass);

    HDFPUBLIC int32 VSlone
                (HFILEID f, int32  * idarray, int32 asize);

    HDFPUBLIC int32 Vlone
                (HFILEID f, int32  * idarray, int32 asize);

    HDFPUBLIC int32 Vfind
                (HFILEID f, const char  * vgname);

    HDFPUBLIC int32 VSfind
                (HFILEID f, const char  * vsname);

    HDFPUBLIC int32 Vfindclass
                (HFILEID f, const char  * vgclass);

    HDFPUBLIC int32 VSfindclass
                (HFILEID f, const char  * vsclass);
    
    HDFPUBLIC intn VSofclass
                (int32 id, const char *vsclass, uintn start_vd,
                 uintn array_size, uint16 *refarray);

    HDFPUBLIC intn VSgetvdatas
                (int32 id, const uintn start_vd, const uintn array_size, uint16 *refarray);
    
    HDFPUBLIC intn VSsetblocksize
                (int32 vkey, int32 block_size);

    HDFPUBLIC intn VSsetnumblocks
                (int32 vkey, int32 num_blocks);

    HDFPUBLIC intn VSgetblockinfo
                (int32 vkey, int32* block_size, int32* num_blocks);

    HDFPUBLIC void Vsetzap
                (void);

#endif /*vg_EXPORTS*/

#ifndef vgp_EXPORTS

/*
   ** from vgp.c
 */
    HDFPUBLIC intn vcompare
                (void * k1, void * k2, intn cmparg);

    HDFPUBLIC intn vcompareref
                (void * k1, void * k2, intn cmparg);

    HDFPUBLIC void vdestroynode
                (void * n);

    HDFPUBLIC void vtfreekey
                (void * k);

    HDFPUBLIC intn Vinitialize
                (HFILEID f);

    HDFPUBLIC intn Vfinish
                (HFILEID f);

    HDFPUBLIC HFILEID Vopen
                (char *path, intn acc_mode, int16 ndds);

    HDFPUBLIC intn Vclose
                (HFILEID f);

    HDFPUBLIC int32 vexistvg
                (HFILEID f, uint16 vgid);

    HDFPUBLIC int32 Vattach
                (HFILEID f, int32 vgid, const char  * accesstype);

    HDFPUBLIC int32 Vdetach
                (int32 vkey);

    HDFPUBLIC int32 Vinsert
                (int32 vkey, int32 vskey);
    /* note: 2nd arg of Vinsert can also be (VGROUP *) */

    HDFPUBLIC int32 Vflocate
                (int32 vkey, char  * field);

    HDFPUBLIC intn Vinqtagref
                (int32 vkey, int32 tag, int32 ref);

    HDFPUBLIC int32 Vntagrefs
                (int32 vkey);

    HDFPUBLIC int32 Vnrefs
                (int32 vkey,int32 tag);

    HDFPUBLIC int32 Vgettagrefs
                (int32 vkey, int32  tagarray[], int32  refarray[], int32 n);

    HDFPUBLIC int32 Vgetuservgs
                (int32 id, int32 start_ref, int32 n_vgs, int32 *refarray); 

    HDFPUBLIC intn Vgettagref
                (int32 vkey, int32 which, int32  * tag, int32  * ref);

    HDFPUBLIC int32 VQueryref
                (int32 vkey);

    HDFPUBLIC int32 VQuerytag
                (int32 vkey);

    HDFPUBLIC int32 Vaddtagref
                (int32 vkey, int32 tag, int32 ref);

    HDFPUBLIC int32 Ventries
                (HFILEID f, int32 vgid);

    HDFPUBLIC int32 Vsetname
                (int32 vkey, const char  * vgname);

    HDFPUBLIC int32 Vsetclass
                (int32 vkey, const char  * vgclass);

    HDFPUBLIC intn Visvg
                (int32 vkey, int32 id);

    HDFPUBLIC intn Visvs
                (int32 vkey, int32 id);

    HDFPUBLIC int32 Vgetid
                (HFILEID f, int32 vgid);

    HDFPUBLIC int32 Vgetnext
                (int32 vkey, int32 id);

    HDFPUBLIC int32 Vgetname
                (int32 vkey, char  * vgname);

    HDFPUBLIC int32 Vgetnamelen
                (int32 vkey, uint16 * name_len);

    HDFPUBLIC int32 Vgetclassnamelen
                (int32 vkey, uint16 * classname_len);

    HDFPUBLIC int32 Vgetclass
                (int32 vkey, char  * vgclass);

    HDFPUBLIC intn Vinquire
                (int32 vkey, int32  * nentries, char  * vgname);

    HDFPUBLIC int32 Vdelete
                (int32 f, int32 ref);

    HDFPUBLIC intn Vgisinternal
		(int32 vkey);

    HDFPUBLIC intn Visinternal	/* this function is replaced by Vgisinternal */
		(const char *classname);

    HDFPUBLIC intn Vgetvgroups
		(int32 id, uintn start_vg, uintn n_vgs, uint16 *refarray);


/*******************************************************************************
NAME
   Vdeletetagref - delete tag/ref pair in Vgroup

DESCRIPTION
    Deletes the given tag/ref pair from the Vgroup.  If the given tag/ref pair 
    does not exist in the vgroup the routine will return FAIL. Users should use 
    Vinqtagref() to check if the tag/ref pair exists before deleting.

RETURNS
    Returns SUCCEED if the tag/ref pair is deleted from Vgroup and
    FAIL if unsuccessful.

*******************************************************************************/
HDFPUBLIC intn
Vdeletetagref(int32 vkey, /* IN: vgroup key */ 
              int32 tag,  /* IN: tag to delete in vgroup */
              int32 ref   /* IN: ref to delete in vgroup */);

    HDFPUBLIC intn VPshutdown(void);

#endif /*vgp_EXPORTS*/

#ifndef vparse_EXPORTS

/*
   ** from vparse.c
 */
    HDFPUBLIC int32 scanattrs
                (const char  * attrs, int32  * attrc, char  *** attrv);

#endif /*vparse_EXPORTS*/

#ifndef vhi_EXPORTS

/*
   ** from vhi.c
 */
    HDFPUBLIC int32 VHstoredata
                (HFILEID f, const char  * field, const uint8  *buf, int32 n, int32 datatype,
                 const char  * vsname, const char  * vsclass);

    HDFPUBLIC int32 VHstoredatam
                (HFILEID f, const char * field, const uint8  *buf, int32 n, int32 datatype,
                 const char  * vsname, const char  * vsclass, int32 order);

    HDFPUBLIC int32 VHmakegroup
                (HFILEID f, int32  tagarray[], int32  refarray[], int32 n,
                    const char * vgname, const char  * vgclass);

#endif /*vhi_EXPORTS*/

#ifndef vio_EXPORTS

/*
   ** from vio.c
 */

    HDFPUBLIC intn VSPhshutdown(void);

    HDFPUBLIC int32 vexistvs
                (HFILEID f, uint16 vsref);

    HDFPUBLIC void vsdestroynode
                (void * n);

    HDFPUBLIC int32 VSattach
                (HFILEID f, int32 vsref, const char  * accesstype);

    HDFPUBLIC int32 VSdetach
                (int32 vkey);

    HDFPUBLIC int32 VSQuerytag
                (int32 vkey);

    HDFPUBLIC int32 VSQueryref
                (int32 vkey);
 
    HDFPUBLIC int32 VSgetid
                (HFILEID f, int32 vsref);

    HDFPUBLIC int32 VSgetversion
                (int32 vkey);

    HDFPUBLIC int32 VSdelete
                (int32 f, int32 ref);

    HDFPUBLIC int32 VSappendable
                (int32 vkey, int32 blk);

#endif /*vio_EXPORTS*/

#ifndef vsfld_EXPORTS

/*
   ** from vsfld.c
 */

    HDFPUBLIC intn VSsetfields
                (int32 vkey, const char  * fields);

    HDFPUBLIC intn VSfdefine
                (int32 vkey, const char  * field, int32 localtype, int32 order);

    HDFPUBLIC int32 VFnfields
                (int32 vkey);

    HDFPUBLIC char *VFfieldname
                (int32 vkey, int32 idx);

    HDFPUBLIC int32 VFfieldtype
                (int32 vkey, int32 idx);

    HDFPUBLIC int32 VFfieldisize
                (int32 vkey, int32 idx);

    HDFPUBLIC int32 VFfieldesize
                (int32 vkey, int32 idx);

    HDFPUBLIC int32 VFfieldorder
                (int32 vkey, int32 idx);

    HDFPUBLIC intn VSsetexternalfile
		(int32 vkey, const char *filename, int32 offset);

    HDFPUBLIC intn VSgetexternalfile
		 (int32 vkey, uintn name_len, char *filename, int32* offset);

    HDFPUBLIC intn VSgetexternalinfo
		 (int32 vkey, uintn name_len, char *filename, int32* offset,
		 int32* length);

    HDFPUBLIC intn VSfpack
                (int32 vsid, intn packtype, const char *fields_in_buf,
                void * buf, intn bufsz, intn n_records, 
                const char *fields, void * fldbufpt[]);

#endif /*vsfld_EXPORTS*/

#ifndef vrw_EXPORTS

/*
   ** from vrw.c
 */
    HDFPUBLIC intn VSPshutdown(void);

    HDFPUBLIC int32 VSseek
                (int32 vkey, int32 eltpos);

    HDFPUBLIC int32 VSread
                (int32 vkey, uint8  buf[], int32 nelt, int32 interlace);

    HDFPUBLIC int32 VSwrite
                (int32 vkey, const uint8  buf[], int32 nelt, int32 interlace);

#endif /*vrw_EXPORTS*/

/* These are not in hproto.h */

#ifndef hchunks_EXPORTS

HDFPUBLIC int32 HMCPstread(accrec_t * access_rec);
HDFPUBLIC int32 HMCPstwrite(accrec_t * access_rec);
HDFPUBLIC int32 HMCPseek(accrec_t * access_rec,
         int32 offset,
         int origin);
HDFPUBLIC int32 HMCPchunkread(void  *cookie,
              int32 chunk_num,
              void  *datap);
HDFPUBLIC int32 HMCPread(accrec_t * access_rec,
         int32 length,
         void * datap);
HDFPUBLIC int32 HMCPchunkwrite(void  *cookie,
               int32 chunk_num,
               const void *datap);
HDFPUBLIC int32 HMCPwrite(accrec_t * access_rec,
          int32 length,
          const void * datap);
HDFPUBLIC int32 HMCPcloseAID(accrec_t *access_rec);
HDFPUBLIC intn HMCPendaccess(accrec_t * access_rec);
HDFPUBLIC int32 HMCPinfo(accrec_t *access_rec,
         sp_info_block_t *info_chunk);
HDFPUBLIC int32 HMCPinquire(accrec_t *access_rec,
            int32 *pfile_id,
            uint16 *ptag,
            uint16 *pref,
            int32 *plength,
            int32 *poffset,
            int32 *pposn,
            int16 *paccess,
            int16 *pspecial);
HDFPUBLIC int32 HMCPgetnumrecs(accrec_t* access_rec,
               int32 *num_recs);

#endif /*hchunks_EXPORTS*/

#ifndef hfile_EXPORTS
HDFPUBLIC int32 Hopen(const char *path, intn acc_mode, int16 ndds);
HDFPUBLIC intn Hclose(int32 file_id);
HDFPUBLIC intn Hexist(int32 file_id, uint16 search_tag, uint16 search_ref);
HDFPUBLIC intn Hinquire(int32 access_id, int32 *pfile_id, uint16 *ptag, uint16 *pref,
		 int32 *plength, int32 *poffset, int32 *pposn, int16 *paccess,
		 int16 *pspecial);
HDFPUBLIC intn  Hfidinquire(int32 file_id, char **fname, intn *faccess, intn *attach);
HDFPUBLIC int32 Hstartread(int32 file_id, uint16 tag, uint16 ref);
HDFPUBLIC intn Hnextread(int32 access_id, uint16 tag, uint16 ref, intn origin);
HDFPUBLIC int32 Hstartwrite(int32 file_id, uint16 tag, uint16 ref, int32 length);
HDFPUBLIC int32 Hstartaccess(int32 file_id, uint16 tag, uint16 ref, uint32 flags);
HDFPUBLIC intn Hsetlength(int32 aid, int32 length);
HDFPUBLIC intn Happendable(int32 aid);
HDFPUBLIC intn HPisappendable(int32 aid);
HDFPUBLIC intn Hseek(int32 access_id, int32 offset, intn origin);
HDFPUBLIC int32 Htell(int32 access_id);
HDFPUBLIC int32 Hread(int32 access_id, int32 length, void * data);
HDFPUBLIC int32 Hwrite(int32 access_id, int32 length, const void * data);
HDFPUBLIC intn HDgetc(int32 access_id);
HDFPUBLIC intn HDputc(uint8 c, int32 access_id);
HDFPUBLIC intn Hendaccess(int32 access_id);
HDFPUBLIC int32 Hgetelement(int32 file_id, uint16 tag, uint16 ref, uint8 *data);
HDFPUBLIC int32 Hputelement(int32 file_id, uint16 tag, uint16 ref, const uint8 *data,
 			int32 length);
HDFPUBLIC int32 Hlength(int32 file_id, uint16 tag, uint16 ref);
HDFPUBLIC int32 Hoffset(int32 file_id, uint16 tag, uint16 ref);
HDFPUBLIC intn Hishdf(const char *filename);
HDFPUBLIC int32 Htrunc(int32 aid, int32 trunc_len);
HDFPUBLIC intn Hsync(int32 file_id);
HDFPUBLIC intn Hcache(int32 file_id, intn cache_on);
HDFPUBLIC intn HDvalidfid(int32 file_id);
HDFPUBLIC int HDerr(int32 file_id);
HDFPUBLIC intn Hsetaccesstype(int32 access_id, uintn accesstype);
HDFPUBLIC intn HDdont_atexit(void);
HDFPUBLIC intn HPregister_term_func(hdf_termfunc_t term_func); 
HDFPUBLIC void HPend(void); 
HDFPUBLIC void * HIgetspinfo(accrec_t * access_rec);
HDFPUBLIC uint16 HDmake_special_tag(uint16 tag);
HDFPUBLIC intn HDis_special_tag(uint16 tag);
HDFPUBLIC uint16 HDbase_tag(uint16 tag);
HDFPUBLIC intn Hgetlibversion(uint32 *majorv, uint32 *minorv, uint32 *releasev, char *string);
HDFPUBLIC intn Hgetfileversion(int32 file_id, uint32 *majorv, uint32 *minorv,
				uint32 *release, char *string);
HDFPUBLIC intn HPisfile_in_use(const char *path); 
HDFPUBLIC intn HPcompare_filerec_path(const void * obj, const void * key); 
HDFPUBLIC intn HPcompare_accrec_tagref(const void * rec1, const void * rec2); 
HDFPUBLIC accrec_t *HIget_access_rec(void); 
HDFPUBLIC void HIrelease_accrec_node(accrec_t *acc); 
HDFPUBLIC int32 HPgetdiskblock(filerec_t * file_rec, int32 block_size, intn moveto);
HDFPUBLIC intn HPfreediskblock(filerec_t * file_rec, int32 block_off, int32 block_size);
HDFPUBLIC int32 HDget_special_info(int32 access_id, sp_info_block_t * info_block);
HDFPUBLIC int32 HDset_special_info(int32 access_id, sp_info_block_t * info_block);
HDFPUBLIC intn  Hshutdown(void);
HDFPUBLIC void Hdumpseek(void);
HDFPUBLIC intn  HP_read(filerec_t *file_rec,void * buf,int32 bytes);
HDFPUBLIC intn  HPseek(filerec_t *file_rec,int32 offset);
HDFPUBLIC intn  HP_write(filerec_t *file_rec,const void * buf,int32 bytes);
HDFPUBLIC int32 HPread_drec(int32 file_id, atom_t data_id, uint8** drec_buf);
HDFPUBLIC int32 HDcheck_empty(int32 file_id, uint16 tag, uint16 ref, intn  *emptySDS);
HDFPUBLIC intn Hgetspecinfo(int32 file_id, uint16 tag, uint16 ref, sp_info_block_t *info);
HDFPUBLIC intn Hgetntinfo(const int32 numbertype, hdf_ntinfo_t *nt_info);
HDFPUBLIC int Hmpset(int pagesize, int maxcache, int flags);
HDFPUBLIC int Hmpget(int *pagesize, int *maxcache, int flags);
#endif /*hfile_EXPORTS*/

#ifndef hextelt_EXPORTS
HDFPUBLIC int32 HXcreate(int32 file_id, uint16 tag, uint16 ref, const char *extern_file_name, int32 offset, int32 start_len);
HDFPUBLIC intn HXPsetaccesstype(accrec_t * access_rec);
HDFPUBLIC int32 HXPstread(accrec_t * rec);
HDFPUBLIC int32 HXPstwrite(accrec_t * rec);
HDFPUBLIC int32 HXPseek(accrec_t * access_rec, int32 offset, int origin);
HDFPUBLIC int32 HXPread(accrec_t * access_rec, int32 length, void * data);
HDFPUBLIC int32 HXPwrite(accrec_t * access_rec, int32 length, const void * data);
HDFPUBLIC int32 HXPinquire(accrec_t * access_rec, int32 *pfile_id, uint16 *ptag,
		            uint16 *pref, int32 *plength, int32 *poffset,            int32 *pposn, int16 *paccess, int16 *pspecial);
HDFPUBLIC intn HXPendaccess(accrec_t * access_rec);
HDFPUBLIC int32 HXPcloseAID(accrec_t * access_rec);
HDFPUBLIC int32 HXPinfo(accrec_t * access_rec, sp_info_block_t * info_block);
HDFPUBLIC int32 HXPreset(accrec_t * access_rec, sp_info_block_t * info_block);
HDFPUBLIC intn HXsetcreatedir(const char *dir);
HDFPUBLIC intn HXsetdir(const char *dir);
HDFPUBLIC intn HXPshutdown(void);
#endif /*hextelt_EXPORTS*/

#ifndef dfstubs_EXPORTS
HDFPUBLIC DF* DFopen(char *name, int acc_mode, int ndds);
HDFPUBLIC int DFclose(DF * dfile);
HDFPUBLIC int DFdescriptors(DF * dfile, DFdesc ptr[], int begin, int num);
HDFPUBLIC int DFnumber(DF * dfile, uint16 tag);
HDFPUBLIC int DFsetfind(DF * dfile, uint16 tag, uint16 ref);
HDFPUBLIC int DFfind(DF * dfile, DFdesc * ptr);
HDFPUBLIC int DFaccess(DF * dfile, uint16 tag, uint16 ref, char *acc_mode);
HDFPUBLIC int DFstart(DF * dfile, uint16 tag, uint16 ref, char *acc_mode);
HDFPUBLIC int32 DFread(DF * dfile, char *ptr, int32 len);
HDFPUBLIC int32 DFseek(DF * dfile, int32 offset);
HDFPUBLIC int32 DFwrite(DF * dfile, char *ptr, int32 len);
HDFPUBLIC int DFupdate(DF * dfile);
HDFPUBLIC int DFstat(DF * dfile, DFdata * dfinfo);
HDFPUBLIC int32 DFgetelement(DF * dfile, uint16 tag, uint16 ref, char *ptr);
HDFPUBLIC int32 DFputelement(DF * dfile, uint16 tag, uint16 ref, char *ptr, int32 len);
HDFPUBLIC int DFdup(DF * dfile, uint16 itag, uint16 iref, uint16 otag, uint16 oref);
HDFPUBLIC int DFdel(DF * dfile, uint16 tag, uint16 ref);
HDFPUBLIC uint16 DFnewref(DF * dfile);
HDFPUBLIC int DFishdf(char *filename);
HDFPUBLIC int DFerrno(void);
#endif /*dfstubs_EXPORTS*/

#ifndef dfufp2i_EXPORTS
HDFPUBLIC int DFUfptoimage(int32 hdim, int32 vdim, float32 max, float32 min,
             float32 *hscale, float32 *vscale, float32 *data, uint8 *palette,
         char *outfile, int ct_method, int32 hres, int32 vres, int compress);
HDFPUBLIC int process(Input * in, Output * out);
HDFPUBLIC int generate_scale(int32 dim, float32 *scale);
HDFPUBLIC int convert_interp(Input * in, Output * out);
HDFPUBLIC int pixrep_scaled(Input * in, Output * out);
HDFPUBLIC int compute_offsets(float32 *scale, int32 dim, int32 *offsets, int32 res);
HDFPUBLIC int pixrep_simple(Input * in, Output * out);
#endif /*dfufp2i_EXPORTS*/

#ifndef hblocks_EXPORTS
HDFPUBLIC int32 HLPcloseAID(accrec_t * access_rec);
HDFPUBLIC int32 HLPstread(accrec_t * access_rec);
HDFPUBLIC int32 HLPstwrite(accrec_t * access_rec);
HDFPUBLIC int32 HLPseek(accrec_t *access_rec, 
        int32     offset, 
        int       origin);
HDFPUBLIC int32 HLPinquire(accrec_t  *access_rec, 
           int32     *pfile_id, 
           uint16    *ptag,
           uint16    *pref, 
           int32     *plength, 
           int32     *poffset, 
           int32     *pposn,
           int16     *paccess, 
           int16     *pspecial);
HDFPUBLIC int32 HLPread(accrec_t *access_rec, 
        int32     length, 
        void *     datap);
HDFPUBLIC int32 HLPwrite(accrec_t   *access_rec, 
         int32       length, 
         const void * datap);
HDFPUBLIC intn HLPendaccess(accrec_t * access_rec);
HDFPUBLIC int32 HLPinfo(accrec_t * access_rec, sp_info_block_t * info_block);

#endif /*hblocks_EXPORTS*/

#ifndef hbuffer_EXPORTS
HDFPUBLIC int32 HBPstread(accrec_t * rec);
HDFPUBLIC int32 HBPstwrite(accrec_t * rec);
HDFPUBLIC int32 HBPseek(accrec_t * access_rec, int32 offset, int origin);
HDFPUBLIC int32 HBPread(accrec_t * access_rec, int32 length, void * data);
HDFPUBLIC int32 HBPwrite(accrec_t * access_rec, int32 length, const void * data);
HDFPUBLIC int32 HBPinquire(accrec_t * access_rec, int32 *pfile_id, uint16 *ptag,
           uint16 *pref, int32 *plength, int32 *poffset,
           int32 *pposn, int16 *paccess, int16 *pspecial);
HDFPUBLIC intn HBPendaccess(accrec_t * access_rec);
HDFPUBLIC int32 HBPcloseAID(accrec_t * access_rec);
HDFPUBLIC int32 HBPinfo(accrec_t * access_rec, sp_info_block_t * info_block);
#endif /*hbuffer_EXPORTS*/

#ifndef hcomp_EXPORTS
HDFPUBLIC int32
HCPquery_encode_header(comp_model_t model_type, model_info * m_info,
         comp_coder_t coder_type, comp_info * c_info);
HDFPUBLIC intn
HCPencode_header(uint8 *p, comp_model_t model_type, model_info * m_info,
         comp_coder_t coder_type, comp_info * c_info);
HDFPUBLIC intn
HCPdecode_header(uint8 *p, comp_model_t *model_type, model_info * m_info,
         comp_coder_t *coder_type, comp_info * c_info);
HDFPUBLIC int32
HCcreate(int32 file_id, uint16 tag, uint16 ref, comp_model_t model_type,
         model_info * m_info, comp_coder_t coder_type,
         comp_info * c_info);
HDFPUBLIC intn
HCPgetcompress(int32 file_id,
              uint16 data_tag, uint16 data_ref,
              comp_coder_t* comp_type,  /* OUT: compression type */
              comp_info* c_info);        /* OUT: retrieved compression info */
HDFPUBLIC intn
HCPgetcompinfo(int32 file_id,
              uint16 data_tag, uint16 data_ref,
              comp_coder_t* comp_type,  /* OUT: compression type */
              comp_info* c_info);        /* OUT: retrieved compression info */
HDFPUBLIC int32
HCPstread(accrec_t * access_rec);
HDFPUBLIC int32
HCPstwrite(accrec_t * access_rec);
HDFPUBLIC int32
HCPseek(accrec_t * access_rec, int32 offset, intn origin);
HDFPUBLIC int32
HCPread(accrec_t * access_rec, int32 length, void * data);
HDFPUBLIC int32
HCPwrite(accrec_t * access_rec, int32 length, const void * data);
HDFPUBLIC int32
HCPinquire(accrec_t * access_rec, int32 *pfile_id, uint16 *ptag,
 uint16 *pref, int32 *plength, int32 *poffset, int32 *pposn, int16 *paccess,
           int16 *pspecial);
HDFPUBLIC intn
HCPendaccess(accrec_t * access_rec);
HDFPUBLIC int32
HCPcloseAID(accrec_t * access_rec);
HDFPUBLIC int32
HCPinfo(accrec_t * access_rec, sp_info_block_t * info_block);
HDFPUBLIC intn
HCget_config_info( comp_coder_t coder_type,  /* IN: compression type */
		uint32* compression_config_info);
HDFPUBLIC intn
HCPgetcomptype(int32 file_id,
              uint16 data_tag, uint16 data_ref, /* IN: tag/ref of element */
              comp_coder_t* comp_type);  /* OUT: compression type */
HDFPUBLIC intn
HCPgetdatasize(int32 file_id,
              uint16 data_tag, uint16 data_ref, /* IN: tag/ref of element */
              int32* comp_size,	/* OUT  - size of compressed data */
              int32* orig_size);	/* OUT  - size of non-compressed data */

#endif /*hcomp_EXPORTS*/

#ifndef hcompri_EXPORTS
/* forward declaration of the functions provided in this module */
HDFPUBLIC int32 HRPconvert(int32 fid, uint16 tag, uint16 ref, int32 xdim, int32 ydim,int16 scheme, comp_info *cinfo, uintn pixel_size);
HDFPUBLIC int32 HRPstread(accrec_t * rec);
HDFPUBLIC int32 HRPstwrite(accrec_t * rec);
HDFPUBLIC int32 HRPseek(accrec_t * access_rec, int32 offset, int origin);
HDFPUBLIC int32 HRPread(accrec_t * access_rec, int32 length, void * data);
HDFPUBLIC int32 HRPwrite(accrec_t * access_rec, int32 length, const void * data);
HDFPUBLIC int32 HRPinquire(accrec_t * access_rec, int32 *pfile_id, uint16 *ptag,
	             uint16 *pref, int32 *plength, int32 *poffset,
	             int32 *pposn, int16 *paccess, int16 *pspecial);
HDFPUBLIC intn HRPendaccess(accrec_t * access_rec);
HDFPUBLIC int32 HRPcloseAID(accrec_t * access_rec);
HDFPUBLIC int32 HRPinfo(accrec_t * access_rec, sp_info_block_t * info_block);
#endif /*hcompri_EXPORTS*/

#ifndef hfiledd_EXPORTS
HDFPUBLIC intn tagcompare(VOIDP k1, VOIDP k2, intn cmparg);
HDFPUBLIC VOID tagdestroynode(VOIDP n);
#endif /*hfiledd_EXPORTS*/

#ifndef mfgr_EXPORTS
HDFPUBLIC intn GRIil_convert(const void * inbuf,gr_interlace_t inil, void * outbuf, gr_interlace_t outil,int32 dims[2],int32 ncomp,int32 nt);
HDFPUBLIC VOID GRIgrdestroynode(void * n);
HDFPUBLIC VOID GRIattrdestroynode(void * n);
HDFPUBLIC VOID GRIridestroynode(void * n);
#endif /*mfgr_EXPORTS*/

#ifndef tbbt_EXPORTS
HDFPUBLIC TBBT_NODE  *tbbtfirst(TBBT_NODE * root);
HDFPUBLIC TBBT_NODE  *tbbtlast(TBBT_NODE * root);
HDFPUBLIC TBBT_NODE  *tbbtnext(TBBT_NODE * node);
HDFPUBLIC TBBT_NODE  *tbbtprev(TBBT_NODE * node);
HDFPUBLIC TBBT_NODE  *tbbtfind(TBBT_NODE * root, VOIDP key,
     intn (*compar)(VOIDP, VOIDP, intn), intn arg, TBBT_NODE ** pp);
HDFPUBLIC TBBT_NODE  *tbbtdfind(TBBT_TREE * tree, VOIDP key, TBBT_NODE ** pp);
HDFPUBLIC TBBT_NODE  *tbbtless(TBBT_NODE * root, VOIDP key,
     intn (*compar)(VOIDP, VOIDP, intn), intn arg, TBBT_NODE ** pp);
HDFPUBLIC TBBT_NODE  *tbbtdless(TBBT_TREE * tree, VOIDP key, TBBT_NODE ** pp);
HDFPUBLIC TBBT_NODE  *tbbtindx(TBBT_NODE * root, int32 indx);
HDFPUBLIC TBBT_NODE  *tbbtdins(TBBT_TREE * tree, VOIDP item, VOIDP key);
HDFPUBLIC VOIDP tbbtrem(TBBT_NODE ** root, TBBT_NODE * node, VOIDP *kp);
HDFPUBLIC TBBT_TREE  *tbbtdmake(intn (*cmp)(VOIDP /* k1 */, VOIDP /* k2 */, intn /* arg */), intn arg, uintn fast_compare);
HDFPUBLIC VOID tbbtfree(TBBT_NODE ** root, VOID(*fd)(VOIDP item), VOID(*fk)(VOIDP key));
HDFPUBLIC VOID tbbtprint(TBBT_NODE * node);
HDFPUBLIC VOID tbbtdump(TBBT_TREE * tree, intn method);
HDFPUBLIC TBBT_TREE  *tbbtdfree(TBBT_TREE * tree, VOID(*fd)(VOIDP /* item */), VOID(*fk)(VOIDP /* key */));
HDFPUBLIC long tbbtcount(TBBT_TREE * tree);
HDFPUBLIC intn tbbt_shutdown(void);
#endif /*tbbt_EXPORTS*/

#ifndef vconv_EXPORTS
HDFPUBLIC int16 map_from_old_types(intn type);
#endif /*vconv_EXPORTS*/

#ifndef vgp_EXPORTS
HDFPUBLIC vginstance_t *VIget_vginstance_node(void);
HDFPUBLIC void VIrelease_vginstance_node(vginstance_t *vg /* IN: vgroup instance to release */);
HDFPUBLIC vfile_t *Get_vfile(HFILEID f /* IN: file handle */);
HDFPUBLIC VOID vfdestroynode(VOIDP n /* IN: vfile_t record to free */);
HDFPUBLIC vginstance_t *vginst(HFILEID f,   /* IN: file handle */
       uint16 vgid  /* IN: vgroup id */);
HDFPUBLIC intn vpackvg(VGROUP * vg, /* IN: */
        uint8 buf[], /* IN/OUT: */
        int32 *size  /* IN/OUT: */);
HDFPUBLIC VGROUP *VPgetinfo(HFILEID f,  /* IN: file handle */
          uint16 ref  /* IN: ref of vgroup */);
HDFPUBLIC int32 vinsertpair(VGROUP * vg, /* IN: vgroup struct */
            uint16 tag,  /* IN: tag to insert */
            uint16 ref   /* IN: ref to insert */);
HDFPUBLIC VGROUP *VIget_vgroup_node(void);
HDFPUBLIC intn vpackvg(VGROUP * vg, /* IN: */
        uint8 buf[], /* IN/OUT: */
        int32 *size  /* IN/OUT: */);
HDFPUBLIC void VIrelease_vgroup_node(VGROUP *vg);
HDFPUBLIC int32 vinsertpair(VGROUP * vg, /* IN: vgroup struct */
            uint16 tag,  /* IN: tag to insert */
            uint16 ref   /* IN: ref to insert */);
#endif /*vgp_EXPORTS*/

#ifndef vio_EXPORTS
HDFPUBLIC vsinstance_t *VSIget_vsinstance_node(void);
HDFPUBLIC void VSIrelease_vsinstance_node(vsinstance_t *vs /* IN: vinstance node to release */);
HDFPUBLIC vsinstance_t *vsinst(HFILEID f,  /* IN: File handle */
       uint16 vsid /* IN: vdata id i.e. ref */);
HDFPUBLIC intn vpackvs(VDATA * vs,  /* IN/OUT: */
        uint8 buf[], /* IN: */
        int32 *size  /* OUT: */);
HDFPUBLIC VDATA *VSPgetinfo(HFILEID f, /* IN: file handle */
           uint16 ref /* IN: ref of the Vdata */);
HDFPUBLIC DYN_VWRITELIST *vswritelist(int32 vkey /* IN: vdata key */);
HDFPUBLIC VDATA* VSIget_vdata_node(void);
HDFPUBLIC intn vpackvs(VDATA * vs,  /* IN/OUT: */
        uint8 buf[], /* IN: */
        int32 *size  /* OUT: */);
HDFPUBLIC void VSIrelease_vdata_node(VDATA *vs /* IN: vdata to release */);
#endif /*vio_EXPORTS*/


#ifndef vparse_EXPORTS
HDFPUBLIC intn VPparse_shutdown(void);
#endif /*vparse_EXPORTS*/

#ifndef vg_EXPORTS
HDFPUBLIC intn VSIgetvdatas(int32 id,		 /* IN: file id or vgroup id */
	    const char *vsclass, /* IN: a specific class or NULL for user-created vdatas */
	    const uintn start_vd,/* IN: vdata number to start retrieving */
            const uintn n_vds,	 /* IN: number of user-created vds to return */
            uint16 *refarray	 /* IN/OUT: ref array to fill */);
#endif /*vg_EXPORTS*/

#ifndef atom_EXPORTS
HDFPUBLIC intn HAinit_group(group_t grp,
    intn hash_size);
HDFPUBLIC intn HAdestroy_group(group_t grp);
HDFPUBLIC atom_t HAregister_atom(group_t grp, VOIDP object);
HDFPUBLIC VOIDP HAPatom_object(atom_t atm);
HDFPUBLIC group_t HAatom_group(atom_t atm);
HDFPUBLIC VOIDP HAremove_atom(atom_t atm);
HDFPUBLIC VOIDP HAsearch_atom(group_t grp,
    HAsearch_func_t func,
    const void * key);
HDFPUBLIC intn HAshutdown(void);
#endif /* atom_EXPORTS*/

#ifndef cszip_EXPORTS
HDFPUBLICDATA funclist_t cszip_funcs;   /* functions to perform szip encoding */
#endif

/* not in master file hchunk.c */
#ifndef hchunks_EXPORTS
HDFPUBLICDATA funclist_t chunked_funcs;  /* functions to perform chunking */
#endif

#ifndef mstdio_EXPORTS
/*
   ** from mstdio.c
 */

    HDFPUBLIC int32 HCPmstdio_stread
                (accrec_t * rec);

    HDFPUBLIC int32 HCPmstdio_stwrite
                (accrec_t * rec);

    HDFPUBLIC int32 HCPmstdio_seek
                (accrec_t * access_rec, int32 offset, int origin);

    HDFPUBLIC int32 HCPmstdio_inquire
                (accrec_t * access_rec, int32 *pfile_id, uint16 *ptag, uint16 *pref,
               int32 *plength, int32 *poffset, int32 *pposn, int16 *paccess,
                 int16 *pspecial);

    HDFPUBLIC int32 HCPmstdio_read
                (accrec_t * access_rec, int32 length, void * data);

    HDFPUBLIC int32 HCPmstdio_write
                (accrec_t * access_rec, int32 length, const void * data);

    HDFPUBLIC intn HCPmstdio_endaccess
                (accrec_t * access_rec);

#endif /*mstdio_EXPORTS*/

#ifndef dfconvrt_EXPORTS

HDFPUBLIC DF  *DFopen
                (char *name, int acc_mode, int ndds);

HDFPUBLIC int  DFclose
                (DF * dfile);

HDFPUBLIC int  DFdescriptors
                (DF * dfile, DFdesc ptr[], int begin, int num);

HDFPUBLIC int  DFnumber
                (DF * dfile, uint16 tag);

HDFPUBLIC int  DFsetfind
                (DF * dfile, uint16 tag, uint16 ref);

HDFPUBLIC int  DFfind
                (DF * dfile, DFdesc * ptr);

HDFPUBLIC int  DFaccess
                (DF * dfile, uint16 tag, uint16 ref, char *acc_mode);

HDFPUBLIC int  DFstart
                (DF * dfile, uint16 tag, uint16 ref, char *acc_mode);

HDFPUBLIC int32 DFread
                (DF * dfile, char *ptr, int32 len);

HDFPUBLIC int32 DFseek
                (DF * dfile, int32 offset);

HDFPUBLIC int32 DFwrite
                (DF * dfile, char *ptr, int32 len);

HDFPUBLIC int  DFupdate
                (DF * dfile);

HDFPUBLIC int  DFstat
                (DF * dfile, DFdata * dfinfo);

HDFPUBLIC int32 DFgetelement
                (DF * dfile, uint16 tag, uint16 ref, char *ptr);

HDFPUBLIC int32 DFputelement
                (DF * dfile, uint16 tag, uint16 ref, char *ptr, int32 len);

HDFPUBLIC int  DFdup
                (DF * dfile, uint16 itag, uint16 iref, uint16 otag, uint16 oref);

HDFPUBLIC int  DFdel
                (DF * dfile, uint16 tag, uint16 ref);

HDFPUBLIC uint16 DFnewref
                (DF * dfile);

HDFPUBLIC int  DFishdf
                (char *filename);

HDFPUBLIC int  DFerrno
                (void);

HDFPUBLIC int  DFImemcopy
                (char *from, char *to, int length);

#endif /*dfconvrt_EXPORTS*/

#ifndef dfconv_EXPORTS
HDFPUBLIC int  DFconvert
                (uint8 *source, uint8 *dest, int ntype, int sourcetype, int desttype, int32 size);

HDFPUBLIC int32 DFKqueryNT(void);
HDFPUBLIC int DFKsetcustom(int (*DFKcustin)(VOIDP, VOIDP, uint32, uint32, uint32),
			   int (*DFKcustout)(VOIDP, VOIDP, uint32, uint32, uint32));
HDFPUBLIC int DFconvert(uint8 *source, uint8 *dest, int ntype, int sourcetype, 
                     int desttype, int32 size);
#endif /*dfconv_EXPORTS*/

#if defined c_plusplus || defined __cplusplus
}
#endif                          /* c_plusplus || __cplusplus */

#endif                          /* H_SHARED_H */

