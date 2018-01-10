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

/* $Id$ */

#ifndef HDFI_H
#define HDFI_H

#ifdef GOT_MACHINE
#undef GOT_MACHINE
#endif


/*--------------------------------------------------------------------------*/
/*                              MT/NT constants                             */
/*  Four MT nibbles represent double, float, int, uchar (from most          */
/*      significant to least significant).                                  */
/*  Each "column" in the "table" below is essentially independant of the    */
/*      other "columns", for example the CONVEXNATIVE entry means that the  */
/*      floating point formats are in Convex native format but the integers */
/*      are big-endian and standard sizes                                   */
/*  If you add another value to this "table", you need to add another       */
/*      DFNTF_xxx entry in hntdefs.h                                        */
/*  The values for each nibble are:                                         */
/*      1 - Big Endian                                                      */
/*          (i.e. Big-Endian, 32-bit architecture w/IEEE Floats)            */
/*      2 - VAX                                                             */
/*          (i.e. Middle-Endian, 32-bit architecture w/VAX Floats)          */
/*      3 - Cray                                                            */
/*          (i.e. Big-Endian, all 64-bit architecture w/Cray Floats)        */
/*      4 - Little Endian                                                   */
/*          (i.e. Little-Endian, 32-bit architecture w/IEEE Floats)         */
/*      5 - Convex                                                          */
/*          (i.e. Big-Endian, 32-bit architecture w/Convex Native Floats)   */
/*      6 - Fujitsu VP                                                      */
/*          (i.e. Big-Endian, 32-bit architecture w/Fujitsu Native Floats)  */
/*      7 - Cray MPP                                                        */
/*          (i.e. Big-Endian, 32-bit architecture w/IEEE Floats, but no 16-bit type)            */
/*      8 - Cray IEEE                                                       */
/*          (i.e. Big-Endian, all 64-bit architecture w/IEEE Floats)        */
/*--------------------------------------------------------------------------*/
#define     DFMT_SUN            0x1111 
#define     DFMT_SUN_INTEL      0x4441
#define     DFMT_ALLIANT        0x1111
#define     DFMT_IRIX           0x1111
#define     DFMT_APOLLO         0x1111
#define     DFMT_IBM6000        0x1111
#define     DFMT_HP9000         0x1111
#define     DFMT_CONVEXNATIVE   0x5511
#define     DFMT_CONVEX         0x1111
#define     DFMT_UNICOS         0x3331
#define     DFMT_UNICOSIEEE     0x1831
#define     DFMT_CTSS           0x3331
#define     DFMT_VAX            0x2221
#define     DFMT_MIPSEL         0x4441
#define     DFMT_PC             0x4441
#define     DFMT_APPLE          0x1111
#define     DFMT_APPLE_INTEL    0x4441
#define     DFMT_MAC            0x1111
#define     DFMT_SUN386         0x4441
#define     DFMT_NEXT           0x1111
#define     DFMT_MOTOROLA       0x1111
#define     DFMT_ALPHA          0x4441
#define     DFMT_VP             0x6611
#define     DFMT_I860           0x4441
#define     DFMT_IA64           0x4441
#define     DFMT_LINUX64        0x4441
#define     DFMT_CYGWIN         0x4441
#define     DFMT_POWERPC64      0x1111

/* I/O library constants */
#define UNIXUNBUFIO 1
#define UNIXBUFIO   2
#define MACIO       3

#include "h4config.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>          /* for character macros */
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_MEMORY_H
#include <memory.h>
#endif
#ifdef HAVE_CONIO_H
#include <conio.h>          /* for debugging getch() calls */
#endif
#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#endif
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>      /* for unbuffered file I/O */
#endif
#ifdef HAVE_SYS_FILE_H
#include <sys/file.h>               /* for unbuffered i/o stuff */
#endif
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#ifdef HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif
#ifdef _MSC_VER
#include <windows.h>        /* include the windows headers */
#include <winnt.h>
#include <io.h>
#endif

#include "H4api_adpt.h"

/* typedef void VOID fails on some compilers */
#define VOID void
typedef void              *VOIDP;
typedef char              *_fcd;
typedef char              char8;
typedef unsigned char     uchar8;
typedef char              int8;
typedef unsigned char     uint8;
typedef short int         int16;
typedef unsigned short int uint16;
typedef int               int32;
typedef unsigned int      uint32;
typedef int               intn;
typedef unsigned int      uintn;
typedef float             float32;
typedef double            float64;
typedef uintptr_t	  hdf_pint_t;   /* an integer the same size as a pointer */

/* Determine the memory manager we are going to use. Valid values are: */
/*  MEM_ANSI, MEM_NAME, MEM_NOBS.  See the JPEG docs for details on */
/*  what each does */
#define JMEMSYS         MEM_ANSI

#ifdef __GNUC__
#define INCLUDES_ARE_ANSI
#define DUMBCC 	/* because it is.  for later use in macros */
#define FNAME_POST_UNDERSCORE
#endif

/* atexit() should always be available, even windows */
#define HDatexit(f)             (atexit(f))

/*-------------------------------------------------------------------------
 * Define options for each platform
 *-------------------------------------------------------------------------*/

/*
 * Meaning of each defined macros (not completed yet)
 *
 * BIG_LONGS--Define when long is not "equal" to int32.  True in cases
 *      where (int32 *) is not compatible with (long *).  Should
 *      be renamed as LONGNEINT32.
 */

#if (defined(SUN) || defined(sun) || defined(__sun__) || defined(__SUNPRO_C)) & !defined(__i386)
#ifdef __STDC__
#define ANSISUN
#else /* __STDC__ */
#define KNRSUN
#endif /* __STDC__ */
#endif /* SUN || sun */

#if defined(ANSISUN)
#if !defined(SUN)
#define SUN
#endif

#ifdef GOT_MACHINE
If you get an error on this line more than one machine type has been defined.
Please check your Makefile.
#endif
#define GOT_MACHINE

#if (defined __sun) && (defined __amd64 || defined __i386) /* SunOS on Intel; 32 and 64-bit modes */
#define DF_MT   DFMT_SUN_INTEL 
#else
#define DF_MT   DFMT_SUN
#endif /* __sun */
#define FNAME_POST_UNDERSCORE
#define _fcdtocp(desc) (desc)
#define FILELIB UNIXBUFIO

#endif /* ANSISUN */

#if defined(KNRSUN)

#if !defined(SUN)
#define SUN
#endif 

#ifdef GOT_MACHINE
If you get an error on this line more than one machine type has been defined.
Please check your Makefile.
#endif
#define GOT_MACHINE

#define BSD
#define DF_MT             DFMT_SUN
#define _fcdtocp(desc) (desc)
#define FILELIB UNIXBUFIO

#endif /* KNRSUN */

#if defined(IBM6000) || defined(_AIX)

#ifndef IBM6000
#define IBM6000
#endif

#ifdef GOT_MACHINE
If you get an error on this line more than one machine type has been defined.
Please check your Makefile.
#endif
#define GOT_MACHINE

#define BSD

#define DF_MT             DFMT_IBM6000
#define _fcdtocp(desc) (desc)
#define FILELIB UNIXBUFIO

#endif /* IBM6000 */

#if defined(HP9000) || (!defined(__convexc__) && (defined(hpux) || defined(__hpux)))

#ifndef HP9000
#define HP9000
#endif

#ifdef GOT_MACHINE
If you get an error on this line more than one machine type has been defined.
Please check your Makefile.
#endif
#define GOT_MACHINE

#define BSD
#define DF_MT             DFMT_HP9000
#define _fcdtocp(desc) (desc)
#define FILELIB UNIXBUFIO
#endif /* HP9000 */

#if defined(IRIX) || defined(IRIS4) || defined(sgi) || defined(__sgi__) || defined(__sgi)

#ifndef IRIX
#define IRIX
#endif

#if (_MIPS_SZLONG == 64)
/* IRIX 64 bits objects.  It is nearly the same as the conventional
 * 32 bits objects.  Let them share IRIX definitions for now.
 */
#define IRIX64
#endif

#ifdef GOT_MACHINE
If you get an error on this line more than one machine type has been defined.
Please check your Makefile.
#endif
#define GOT_MACHINE 1

/*
 * BSD was originally defined with no value.  But some newer SGI system
 * header files (e.g., resolv.h) assume it has a value and evaluate it
 * in expressions, thus causing compiling errors.  This has been reported
 * to SGI as bug #781568.  SGI could not provide a list of the semantics
 * of BSD values and suggested a work around of setting BSD to 1.
 */
#define BSD 1
#define DF_MT              DFMT_IRIX
#define FNAME_POST_UNDERSCORE
#define _fcdtocp(desc) (desc)
#define FILELIB UNIXBUFIO

#endif /* IRIX */

/* CRAY XT3
 * Note from RedStorm helpdesk,
 * When I compile a C code with the '-v' option, it indicates that the compile
 * is done with the macros __QK_USER__ and __LIBCATAMOUNT__ defined.  In
 * addition, there are other macros like __x86_64__ defined as well, to
 * indicate processor type.  __QK_USER__ might be a good check for Catamount,
 * and __x86_64__ might be good for Opteron node.  You might try something
 * like the following in a header file:
 */
#if ((defined(__QK_USER__)) && (defined(__x86_64__)))
#define __CRAY_XT3__
#endif

#if defined(CONVEX) || defined(CONVEXNATIVE) || defined(__convexc__)

#ifndef CONVEX
#define CONVEX
#endif

#ifdef GOT_MACHINE
If you get an error on this line more than one machine type has been defined.
Please check your Makefile.
#endif
#define GOT_MACHINE

/* For Convex machines with native format floats */
#ifdef CONVEXNATIVE
#define DF_MT             DFMT_CONVEXNATIVE
#else
#define DF_MT             DFMT_CONVEX
#endif
#define _fcdtocp(desc) (desc)
#define FILELIB UNIXBUFIO

#define RIGHT_SHIFT_IS_UNSIGNED
#define INCLUDES_ARE_ANSI
#define HAVE_STDC

#endif /* CONVEX */
 
#if defined (__APPLE__)

#ifdef __LITTLE_ENDIAN__
#define DF_MT DFMT_APPLE_INTEL
#else
#define DF_MT DFMT_APPLE
#endif
#ifdef GOT_MACHINE
If you get an error on this line more than one machine type has been defined.
Please check your Makefile.
#endif
#define GOT_MACHINE 1

#ifdef __i386
#ifndef INTEL86
#define INTEL86   /* we need this Intel define or bad things happen later */
#endif /* INTEL86 */
#endif /* __i386 */

#define _fcdtocp(desc) (desc)
#define FILELIB UNIXBUFIO

#endif /* __APPLE__ */

/* Metrowerks Mac compiler defines some PC stuff so need to exclude this on the Mac */
#if !(defined (__APPLE__))

#if defined _M_ALPHA || defined _M_X64 || defined _M_IA64 || defined _M_IX86 || defined INTEL86 || defined M_I86 || defined M_I386 || defined __i386 || defined UNIX386 || defined i386

#if 0
#define DF_MT             DFMT_PC
#endif

#ifndef INTEL86
#define INTEL86
#endif /* INTEL86 */

#if !defined UNIX386 && (defined unix || defined __unix)
#define UNIX386
#endif /* UNIX386 */

#if defined _M_ALPHA
#define FNAME_PRE_UNDERSCORE
#endif

#ifdef UNIX386
#define FNAME_POST_UNDERSCORE
#endif
#define _fcdtocp(desc) (desc)

#define FILELIB UNIXBUFIO

#endif /* INTEL86 */

#endif /* !(defined(__APPLE__)) */

/*-----------------------------------------------------*/
#if defined(NEXT) || defined(NeXT)

#ifndef NEXT
#define NEXT
#endif

#ifdef GOT_MACHINE
If you get an error on this line more than one machine type has been defined.
Please check your Makefile.
#endif
#define GOT_MACHINE

#define isascii(c)  (isprint(c) || iscntrl(c))
#define DF_MT             DFMT_NEXT
#define FNAME_POST_UNDERSCORE
#define _fcdtocp(desc) (desc)
#define FILELIB UNIXBUFIO

#endif /* NEXT */

/*-----------------------------------------------------*/
#if defined(MOTOROLA) || defined(m88k)

#ifdef GOT_MACHINE
If you get an error on this line more than one machine type has been defined.
Please check your Makefile.
#endif
#define GOT_MACHINE

#define DF_MT             DFMT_MOTOROLA
#define FNAME_POST_UNDERSCORE
#define _fcdtocp(desc) (desc)
#define FILELIB UNIXBUFIO


#endif /* MOTOROLA */

/*-----------------------------------------------------*/
#if defined DEC_ALPHA || (defined __alpha && defined __unix__)

#ifndef DEC_ALPHA
#define DEC_ALPHA
#endif

#ifdef GOT_MACHINE
If you get an error on this line more than one machine type has been defined.
Please check your Makefile.
#endif
#define GOT_MACHINE

#define DF_MT             DFMT_ALPHA
#define FNAME_POST_UNDERSCORE
#define _fcdtocp(desc) (desc)
#define FILELIB UNIXBUFIO


#endif /* DEC_ALPHA */

/*-----------------------------------------------------*/
#if defined VP | defined __uxpm__

#ifndef VP
#define VP
#endif

#ifdef GOT_MACHINE
If you get an error on this line more than one machine type has been defined.
Please check your Makefile.
#endif
#define GOT_MACHINE 1

#define DF_MT              DFMT_VP
#define FNAME_POST_UNDERSCORE
#define _fcdtocp(desc) (desc)
#define FILELIB UNIXBUFIO


#endif /* VP */

/*-----------------------------------------------------*/
#if defined I860 | defined i860

#ifndef I860
#define I860
#endif

#ifdef GOT_MACHINE
If you get an error on this line more than one machine type has been defined.
Please check your Makefile.
#endif
#define GOT_MACHINE 1

#define DF_MT   DFMT_I860
#define _fcdtocp(desc) (desc)
#define FNAME_POST_UNDERSCORE
#define FILELIB UNIXBUFIO

#endif /* I860 */


/*-----------------------------------------------------*/
/* Power PC 5 64 */
#if defined __powerpc64__

#ifdef GOT_MACHINE
If you get an error on this line more than one machine type has been defined.
Please check your Makefile.
#endif
#define GOT_MACHINE

#define DF_MT             DFMT_POWERPC64
#define _fcdtocp(desc) (desc)
#define FILELIB UNIXBUFIO


/*-----------------------------------------------------*/
#endif /*power PC 5 64 */
/* Linux 64 */
#if defined(__linux__) && defined __x86_64__  && !(defined  SUN)  /* i.e. 64-bit Linux  but not SunOS on Intel */

#ifdef GOT_MACHINE
If you get an error on this line more than one machine type has been defined.
Please check your Makefile.
#endif
#define GOT_MACHINE

#define DF_MT             DFMT_LINUX64
#define FNAME_POST_UNDERSCORE
#define _fcdtocp(desc) (desc)
#define FILELIB UNIXBUFIO


#endif /*Linux 64 */

/*-----------------------------------------------------*/
/* 64-bit Free BSD */

#if defined __FreeBSD__ && defined __x86_64__

#ifdef GOT_MACHINE
If you get an error on this line more than one machine type has been defined.
Please check your Makefile.
#endif
#define GOT_MACHINE

#define DF_MT             DFMT_LINUX64
#define FNAME_POST_UNDERSCORE
#define _fcdtocp(desc) (desc)
#define FILELIB UNIXBUFIO

#endif /*64-bit FreeBSD */

/*-----------------------------------------------------*/

/* IA64 running Linux */
#if defined __ia64 && !(defined(hpux) || defined(__hpux))

#ifdef GOT_MACHINE
If you get an error on this line more than one machine type has been defined.
Please check your Makefile.
#endif
#define GOT_MACHINE

#define DF_MT             DFMT_IA64
#define FNAME_POST_UNDERSCORE
#define _fcdtocp(desc) (desc)
#define FILELIB UNIXBUFIO


#endif /* IA64 */


/* CYGWIN */
#if defined(__CYGWIN__)

#ifdef GOT_MACHINE
If you get an error on this line more than one machine type has been defined.
Please check your Makefile.
#endif
#define GOT_MACHINE

#define DF_MT             DFMT_CYGWIN
#define FNAME_POST_UNDERSCORE
#define _fcdtocp(desc) (desc)
#define FILELIB UNIXBUFIO

#endif /*CYGWIN*/

/* Visual Studio */
#if defined(_MSC_VER)

#ifdef GOT_MACHINE
If you get an error on this line more than one machine type has been defined.
Please check your Makefile.
#endif
#define GOT_MACHINE

#define DF_MT             DFMT_PC

#pragma comment( lib, "oldnames" )

#endif /*_MSC_VER*/

#ifndef GOT_MACHINE
No machine type has been defined.  Your Makefile needs to have someing like
-DSUN or -DUNICOS in order for the HDF internal structures to be defined
correctly.
#endif



/*-----------------------------------------------------*/
/*              encode and decode macros               */
/*-----------------------------------------------------*/

#   define INT16ENCODE(p, i) \
{ *(p) = (uint8)(((uintn)(i) >> 8) & 0xff); (p)++; \
        *(p) = (uint8)((uintn)(i) & 0xff); (p)++; }

#   define UINT16ENCODE(p, i) \
{ *(p) = (uint8)(((uintn)(i) >> 8) & 0xff); (p)++; *(p) = (uint8)((i) & 0xff); (p)++; }

#   define INT32ENCODE(p, i) \
{ *(p) = (uint8)(((uint32)(i) >> 24) & 0xff); (p)++; \
        *(p) = (uint8)(((uint32)(i) >> 16) & 0xff); (p)++; \
        *(p) = (uint8)(((uint32)(i) >> 8) & 0xff); (p)++; \
        *(p) = (uint8)((uint32)(i) & 0xff); (p)++; }

#   define UINT32ENCODE(p, i) \
{ *(p) = (uint8)(((i) >> 24) & 0xff); (p)++; \
        *(p) = (uint8)(((i) >> 16) & 0xff); (p)++; \
        *(p) = (uint8)(((i) >> 8) & 0xff); (p)++; \
        *(p) = (uint8)((i) & 0xff); (p)++; }

#   define NBYTEENCODE(d, s, n) \
{   HDmemcpy(d,s,n); p+=n }

/* DECODE converts big endian bytes pointed by p to integer values and store
 * it in i.  For signed values, need to do sign-extension when converting
 * the 1st byte which carries the sign bit.
 * The macros does not require i be of a certain byte sizes.  It just requires
 * i be big enough to hold the intended value range.  E.g. INT16DECODE works
 * correctly even if i is actually a 64bit int like in a Cray.
 */

#   define INT16DECODE(p, i) \
{ (i) = ((*(p) & 0x80) ? ~0xffff : 0x00) | ((int16)(*(p) & 0xff) << 8); (p)++; \
        (i) |= (int16)((*(p) & 0xff)); (p)++; }

#   define UINT16DECODE(p, i) \
{ (i) = (uint16)((*(p) & 0xff) << 8); (p)++; \
        (i) |= (uint16)(*(p) & 0xff); (p)++; }

#   define INT32DECODE(p, i) \
{ (i) = (int32)(((int32)*(p) & 0x80) ? ~0xffffffff : 0x00) | ((int32)(*(p) & 0xff) << 24); (p)++; \
        (i) |= ((int32)(*(p) & 0xff) << 16); (p)++; \
        (i) |= ((int32)(*(p) & 0xff) << 8); (p)++; \
        (i) |= (*(p) & 0xff); (p)++; }

#   define UINT32DECODE(p, i) \
{ (i) = ((uint32)(*(p) & 0xff) << 24); (p)++; \
        (i) |= ((uint32)(*(p) & 0xff) << 16); (p)++; \
        (i) |= ((uint32)(*(p) & 0xff) << 8); (p)++; \
        (i) |= (uint32)(*(p) & 0xff); (p)++; }

/* Note! the NBYTEDECODE macro is backwards from the memcpy() routine, */
/*      in the spirit of the other DECODE macros */
#   define NBYTEDECODE(s, d, n) \
{   HDmemcpy(d,s,n); p+=n }

/*----------------------------------------------------------------
** MACRO FCALLKEYW for any special fortran-C stub keyword
**
** Microsoft C and Fortran need __fortran for Fortran callable C
**  routines.
**
** MACRO FRETVAL for any return value from a fortran-C stub function
**  Replaces the older FCALLKEYW macro.
**---------------------------------------------------------------*/
#ifdef FRETVAL
#undef FRETVAL
#endif

#ifndef FRETVAL /* !MAC */
#   define FCALLKEYW    /*NONE*/
#   define FRETVAL(x)   x
#endif


/*----------------------------------------------------------------
** MACRO FNAME for any fortran callable routine name.
**
**  This macro prepends, appends, or does not modify a name
**  passed as a macro parameter to it based on the FNAME_PRE_UNDERSCORE,
**  FNAME_POST_UNDERSCORE macros set for a specific system.
**
**---------------------------------------------------------------*/
#if defined(FNAME_PRE_UNDERSCORE) && defined(FNAME_POST_UNDERSCORE)
#   define FNAME(x)     _##x##_
#endif
#if defined(FNAME_PRE_UNDERSCORE) && !defined(FNAME_POST_UNDERSCORE)
#   define FNAME(x)     _##x
#endif
#if !defined(FNAME_PRE_UNDERSCORE) && defined(FNAME_POST_UNDERSCORE)
#   define FNAME(x)     x##_
#endif
#if !defined(FNAME_PRE_UNDERSCORE) && !defined(FNAME_POST_UNDERSCORE)
#   define FNAME(x)     x
#endif

/**************************************************************************
*  Generally useful macro definitions
**************************************************************************/
#ifndef MIN
#define MIN(a,b)    (((a)<(b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b)    (((a)>(b)) ? (a) : (b))
#endif

/**************************************************************************
*  Debugging Allocation functions
**************************************************************************/
#ifdef MALDEBUG
#include "maldebug.h"
#endif

/**************************************************************************
*  Macros to work around ANSI C portability problems.
**************************************************************************/
#ifdef DUMBCC
#define CONSTR(v,s) char *v=s
#else
#define CONSTR(v,s) static const char v[]=s
#endif

/* Old-style memory allocation function aliases -QAK */
#define HDgetspace HDmalloc
#define HDclearspace HDcalloc
#define HDregetspace HDrealloc
#define HDfreespace HDfree

/**************************************************************************
*  Allocation functions defined differently 
**************************************************************************/
#if !defined(MALLOC_CHECK)
#  define HDmalloc(s)      (malloc((size_t)s))
#  define HDcalloc(a,b)    (calloc((size_t)a,(size_t)b))
#  define HDfree(p)        (free((void*)p))
#  define HDrealloc(p,s)   (realloc((void*)p,(size_t)s))
#endif /* !defined MALLOC_CHECK */
/* Macro to free space and clear pointer to NULL */
#define HDfreenclear(p) { if((p)!=NULL) HDfree(p); p=NULL; }

/**************************************************************************
*  String functions defined differently 
**************************************************************************/

#  define HDstrcat(s1,s2)   (strcat((s1),(s2)))
#  define HDstrcmp(s,t)     (strcmp((s),(t)))
#  define HDstrcpy(s,d)     (strcpy((s),(d)))
#  define HDstrlen(s)       (strlen((const char *)(s)))
#  define HDstrncmp(s1,s2,n)    (strncmp((s1),(s2),(n)))
#  define HDstrncpy(s1,s2,n)    (strncpy((s1),(s2),(n)))
#  define HDstrchr(s,c)         (strchr((s),(c)))
#  define HDstrrchr(s,c)        (strrchr((s),(c)))
#  define HDstrtol(s,e,b)       (strtol((s),(e),(b)))


/**************************************************************************
*  Memory functions defined differently
**************************************************************************/

# define HDmemcpy(dst,src,n)   (memcpy((void *)(dst),(const void *)(src),(size_t)(n)))
# define HDmemset(dst,c,n)     (memset((void *)(dst),(intn)(c),(size_t)(n)))
# define HDmemcmp(dst,src,n)   (memcmp((const void *)(dst),(const void *)(src),(size_t)(n)))


/**************************************************************************
*  Misc. functions
**************************************************************************/
#define HDgetenv(s1)            (getenv(s1))
#define HDputenv(s1)            (putenv(s1))
#define HDltoa(v)               (ltoa(v))

#ifdef _MSC_VER
#define HDaccess(path, mode)	(_access(path, mode))
#define F_OK 00
#else
#define HDaccess(path, mode)	(access(path, mode))
#endif

/* Compatibility #define for V3.3, should be taken out by v4.0 - QAK */
/* Commented out only, just in case any legacy code is still using it out there.
   Will be removed in a few maintenance releases.  -BMR, Jun 5, 2016
#define DFSDnumber DFSDndatasets */

#endif /* HDFI_H */

