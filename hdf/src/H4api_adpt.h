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

/* $Id: hdfi.h 5435 2010-08-11 17:31:24Z byrn $ */

#ifndef H4API_ADPT_H
#define H4API_ADPT_H

#include "h4config.h"

/**
 * Provide the macros to adapt the HDF public functions to
 * dll entry points.
 * In addition it provides error lines if the configuration is incorrect.
 **/

/* This will only be defined if HDF4 was built with CMake + Visual Studio */
#if defined(_MSC_VER) || defined(__MINGW)

/*
We need to separate out (1) those functions
that are referenced between .obj in this library
from (2) those that are referenced externally
in, say, hdf/util.
We mark case (2) with HDFLIBAPI and HDFLIBDATA.
Case (1) requires further subdivision to avoid
LNK4049 errors in Visual Studio. So, in the file
defining function f(), we need to mark the function's
forward reference prototype with HDFPUBLIC and HDFPUBLICDATA
(which translated to __declspec(dllexport)).
However, in the function that uses f(), we need to
have no marks on the prototype at all.
In order to do this, we need to:
1. Replace hproto.h with hinternal.h when compiling this lib
2. Define HDFPUBLIC in hinternal depending on whether
   we are declaring it or using it.
*/
#ifdef hdf4_EXPORTS /* This is set only when compiling this library */
    /* Use this in .c files for data only: redefined in hinternal.h */
    #define HDFPUBLICDATA
    /* Use this in .c files for functions only: redefined in hinternal.h */
    #define HDFPUBLIC
    /* Use this in .h files for data only*/
    #define HDFLIBDATA __declspec(dllimport)
    /* Use this in .h files for functions only*/
    #define HDFLIBAPI __declspec(dllimport)
  #else /* This case is for using data/functions */
    /* Use this in .h files for data only*/
    #define HDFLIBDATA __declspec(dllimport) extern
    /* Use this in .h files for functions only*/
    #define HDFLIBAPI __declspec(dllimport) extern
  #endif
#else /* ! defined (_MSC_VER) */
  #define HDFPUBLICDATA
  #define HDFPUBLIC
  #define HDFLIBDATA extern
  #define HDFLIBAPI extern
#endif

#endif /* H4API_ADPT_H */
