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

/*-----------------------------------------------------------------------------
 * File:    atom.h
 * Purpose: header file for atom API
 * Dependencies: 
 * Invokes:
 * Contents:
 * Structure definitions: 
 * Constant definitions: 
 *---------------------------------------------------------------------------*/

/* avoid re-inclusion */
#ifndef __ATOM_H
#define __ATOM_H

#include "H4api_adpt.h"

/* Atom Features control */
/* Define the following macro for fast hash calculations (but limited hash sizes) */
#define HASH_SIZE_POWER_2

/* Define the following macro for atom caching over all the atoms */
#define ATOMS_ARE_CACHED

/* Define the following macro for "inline" atom lookups from the cache */
#ifdef ATOMS_ARE_CACHED     /* required for this to work */
#define ATOMS_CACHE_INLINE
#endif /* ATOMS_ARE_CACHED */

#ifdef ATOMS_CACHE_INLINE
/* Do swap using XOR operator. Ugly but fast... -QAK */
#define HAIswap_cache(i,j) \
                atom_id_cache[i]^=atom_id_cache[j], \
                atom_obj_cache[i]=(void *)((hdf_pint_t)atom_obj_cache[j]^(hdf_pint_t)atom_obj_cache[i]), \
                atom_id_cache[j]^=atom_id_cache[i], \
                atom_obj_cache[j]=(void *)((hdf_pint_t)atom_obj_cache[i]^(hdf_pint_t)atom_obj_cache[j]), \
                atom_id_cache[i]^=atom_id_cache[j], \
                atom_obj_cache[i]=(void *)((hdf_pint_t)atom_obj_cache[i]^(hdf_pint_t)atom_obj_cache[j])

/* Note! This is hardwired to the atom cache value being 4 */
#define HAatom_object(atm) \
    (atom_id_cache[0]==atm ? atom_obj_cache[0] : \
      atom_id_cache[1]==atm ? (HAIswap_cache(0,1),atom_obj_cache[0]) : \
       atom_id_cache[2]==atm ? (HAIswap_cache(1,2),atom_obj_cache[1]) : \
        atom_id_cache[3]==atm ? (HAIswap_cache(2,3),atom_obj_cache[2]) : \
         HAPatom_object(atm))
#endif /* ATOMS_CACHE_INLINE */

#include "hdf.h"

/* Group values allowed */
typedef enum {BADGROUP=(-1),    /* Invalid Group */
DDGROUP=0,                  /* Group ID for DD objects */
AIDGROUP=1,                 /* Group ID for access ID objects */
FIDGROUP=2,                 /* Group ID for file ID objects */
VGIDGROUP=3,                /* Group ID for Vgroup ID objects */
VSIDGROUP=4,                /* Group ID for Vdata ID objects */
GRIDGROUP=5,                /* Group ID for GR ID objects */
RIIDGROUP=6,                /* Group ID for RI ID objects */
BITIDGROUP=7,               /* Group ID for Bitfile ID objects */
ANIDGROUP=8,                /* Group ID for Annotation ID objects */
MAXGROUP                    /* Highest group in group_t (Invalid as true group) */
} group_t;

/* Type of atoms to return to users */
typedef int32 atom_t;

/* Type of the function to compare objects & keys */
typedef intn (*HAsearch_func_t)(const void * obj, const void * key);

#if defined ATOM_MASTER || defined ATOM_TESTER || defined atom_EXPORTS

/* # of bits to use for Group ID in each atom (change if MAXGROUP>16) */
#define GROUP_BITS  4
#define GROUP_MASK  0x0F

/* # of bits to use for the Atom index in each atom (change if MAXGROUP>16) */
#define ATOM_BITS   28
#define ATOM_MASK   0x0FFFFFFF

#ifdef ATOMS_ARE_CACHED
/* # of previous atoms cached, change inline caching macros (HAatom_object & HAIswap_cache) if this changes */
#define ATOM_CACHE_SIZE 4
#endif /* ATOMS_ARE_CACHED */

/* Map an atom to a Group number */
#define ATOM_TO_GROUP(a)    ((group_t)((((atom_t)(a))>>((sizeof(atom_t)*8)-GROUP_BITS))&GROUP_MASK))

#ifdef HASH_SIZE_POWER_2
/* Map an atom to a hash location (assumes s is a power of 2 and smaller than the ATOM_MASK constant) */
#define ATOM_TO_LOC(a,s)    ((atom_t)(a)&((s)-1))
#else /* HASH_SIZE_POWER_2 */
/* Map an atom to a hash location */
#define ATOM_TO_LOC(a,s)    (((atom_t)(a)&ATOM_MASK)%(s))
#endif /* HASH_SIZE_POWER_2 */

/* Combine a Group number and an atom index into an atom */
#define MAKE_ATOM(g,i)      ((((atom_t)(g)&GROUP_MASK)<<((sizeof(atom_t)*8)-GROUP_BITS))|((atom_t)(i)&ATOM_MASK))

/* Atom information structure used */
typedef struct atom_info_struct_tag {
    atom_t id;              /* atom ID for this info */
    VOIDP *obj_ptr;         /* pointer associated with the atom */
    struct atom_info_struct_tag *next;   /* link to next atom (in case of hash-clash) */
  }atom_info_t;

/* Atom group structure used */
typedef struct atom_group_struct_tag {
    uintn count;            /* # of times this group has been initialized */
    intn hash_size;         /* size of the hash table to store the atoms in */
    uintn atoms;            /* current number of atoms held */
    uintn nextid;           /* atom ID to use for the next atom */
    atom_info_t **atom_list;/* pointer to an array of ptrs to atoms */
  }atom_group_t;

#endif /*defined ATOM_MASTER | defined ATOM_TESTER*/

#ifndef atom_EXPORTS
#ifndef ATOM_MASTER 
HDFLIBDATA atom_t atom_id_cache[];
HDFLIBDATA VOIDP atom_obj_cache[];
#endif /* ATOM_MASTER */
#endif /* atom_EXPORTS */


#endif /*__ATOM_H*/


