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
#ifndef _ALLOC_H_
#define _ALLOC_H_

#ifndef NO_STDLIB
#include <stdlib.h>
#else
extern char *malloc();
extern char *realloc();
#ifndef NULL
#define NULL  0
#endif /* !NULL */
#endif /* !NO_STDLIB */


#define Alloc(theNum, theType) \
	(theType *)HDmalloc(sizeof(theType) * (theNum))

#ifndef NO_STDLIB
#define Free(ptr)		HDfree((VOIDP)ptr)
#else
/* old style free */
#define Free(ptr)		(void)HDfree((char *)ptr)
#endif /* !NO_STDLIB */


#define ARRAYLEN(arr) (sizeof(arr)/sizeof(arr[0]))

#endif /* !_ALLOC_H_ */
