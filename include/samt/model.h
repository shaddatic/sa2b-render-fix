/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/model.h'
*
*   Description:
*     Utility functions for the Ninja model types.
*/
#ifndef H_SAMT_MODEL
#define H_SAMT_MODEL

/********************************/
/*  Includes                    */
/********************************/
/****** System **********************************************************************************/
#include <samt/shinobi/sg_xpt.h>    /* core types                                      */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/njbasic.h>     /* basic model format                              */
#include <samt/ninja/njchunk.h>     /* chunk model format                              */
#include <samt/ninja/gjmodel.h>     /* ginja model format                              */
#include <samt/ninja/njmotion.h>    /* ninja motion                                    */

EXTERN_START

/************************/
/*  Opaque Types        */
/************************/
/****** Pointer List ****************************************************************************/
typedef struct mt_ptrlist   mt_ptrlist; /* ptrlist                                  */

/************************/
/*  Prototypes          */
/************************/
/************************************************************************************************/
/*
*   Basic Model
*/
/****** Object **********************************************************************************/
/*
*   Description:
*     Get the node count of a Basic object tree.
*
*   Parameters:
*     - pObject     : object head
*
*   Returns:
*     Object node count of given object.
*/
size_t  mtBscNodeCount( const NJS_OBJECT* pObject );
/*
*   Description:
*     Get an object node via index in a Basic object tree.
*
*   Parameters:
*     - pObject     : object head
*
*   Returns:
*     Pointer to object node at given index; or 'nullptr' if the index is larger than the
*   object tree.
*/
NJS_OBJECT* mtBscGetNode( const NJS_OBJECT* pObject, size_t ixNode );

/************************************************************************************************/
/*
*   Chunk Model
*/
/****** Object **********************************************************************************/
/*
*   Description:
*     Get the node count of a Chunk object tree.
*
*   Parameters:
*     - pObject     : object head
*
*   Returns:
*     Object node count of given object.
*/
size_t  mtCnkNodeCount( const NJS_CNK_OBJECT* pObject );
/*
*   Description:
*     Get an object node via index in a Chunk object tree.
*
*   Parameters:
*     - pObject     : object head
*
*   Returns:
*     Pointer to object node at given index; or 'nullptr' if the index is larger than the
*   object tree.
*/
NJS_CNK_OBJECT* mtCnkGetNode( const NJS_CNK_OBJECT* pObject, size_t ixNode );

/****** Model ***********************************************************************************/
/*
*   Description:
*     Get the total size of a Chunk vertex list.
*
*   Parameters:
*     - pVList      : chunk vertex list
*
*   Returns:
*     Size of the vlist, in bytes.
*/
size_t  mtCnkVListSize( const Sint32* pVList );
/*
*   Description:
*     Get the total size of a Chunk polygon list.
*
*   Parameters:
*     - pPList      : chunk polygon list
*
*   Returns:
*     Size of the plist, in bytes.
*/
size_t  mtCnkPListSize( const Sint16* pPList );

/************************************************************************************************/
/*
*   Ginja Model
*/
/****** Object **********************************************************************************/
/*
*   Description:
*     Get the node count of a Ginja object tree.
*
*   Parameters:
*     - pObject     : object head
*
*   Returns:
*     Object node count of given object.
*/
size_t  mtGjsNodeCount( const GJS_OBJECT* pObject );
/*
*   Description:
*     Get an object node via index in a Ginja object tree.
*
*   Parameters:
*     - pObject     : object head
*
*   Returns:
*     Pointer to object node at given index; or 'nullptr' if the index is larger than the
*   object tree.
*/
GJS_OBJECT* mtGjsGetNode( const GJS_OBJECT* pObject, size_t ixNode );

/****** Model ***********************************************************************************/
/*
*   Description:
*     Get the total number of entries in a Ginja vertex array list.
*
*   Parameters:
*     - pArrays     : ginja vertex array list
*
*   Returns:
*     The length of a Ginja vertex array list, including the termination entry.
*/
size_t  mtGjsArrayLength( const GJS_ARRAY* pArrays );
/*
*   Description:
*     Get the total size of a Ginja vertex array list.
*
*   Parameters:
*     - pArrays     : ginja vertex array list
*
*   Returns:
*     The size of a Ginja vertex array list, in bytes.
*/
size_t  mtGjsArraySize( const GJS_ARRAY* pArrays );
/*
*   Description:
*     Get the total number of entries in a Ginja vertex array list.
*
*   Parameters:
*     - pArrays     : ginja vertex array list
*
*   Returns:
*     The length of a Ginja vertex array list, including the termination entry.
*/
size_t  mtGjsVlistLength( const GJS_VLIST* pVlist );
/*
*   Description:
*     Get the total size of a Ginja vertex array list.
*
*   Parameters:
*     - pArrays     : ginja vertex array list
*
*   Returns:
*     The size of a Ginja vertex array list, in bytes.
*/
size_t  mtGjsVlistSize( const GJS_VLIST* pVlist );

/************************************************************************************************/
/*
*   Ninja Motion
*/
/****** Mtype ***********************************************************************************/
/*
*   Description:
*     Get motion key types contained in a motion structure.
*
*   Notes:
*     - Output array will use 'NJ_MTYPE' values.
*
*   Parameters:
*     - pMotion     : motion structure
*     - pOutMtypes  : output motion key type array
*
*   Returns:
*     Number of motion key types.
*/
isize   mtMotGetMtypes( const NJS_MOTION* pMotion, u8 pOutMtypes[16] );
/*
*   Description:
*     Get the size of a motion key type, with Ninja2 flag.
*
*   Parameters:
*     - mtype       : motion key type
*     - nj2         : ninja2 motion key types, over 'VERT' and 'NORM'
*
*   Returns:
*     Size of motion key type.
*/
isize   mtMotGetMtypeSize( NJ_MTYPE mtype, bool nj2 );

/****** Mdata ***********************************************************************************/
/*
*   Description:
*     Get the variable mdata pointers from a motion structure. In other words, this function
*   does:
*   {
*     *ppOutMkey = &pMotion->mdata->p[0];
*     *ppOutMnb  = &pMotion->mdata->nb[0];
*   }
*
*   Parameters:
*     - pMotion     : motion structure
*     - ppOutMkey   : output pointer for start of mkey pointers
*     - ppOutMnb    : output pointer for start of mkey numbers
*
*   Returns:
*     Number of motion key types; or '-1' on failure.
*/
isize   mtMotGetMdata( const NJS_MOTION* pMotion, const void** ppOutMkey, const Uint32** ppOutMnb );

/****** Ptrs ************************************************************************************/
/*
*   Description:
*     Get a list of all pointers in a motion in ascending order. This can be used to determine
*   the size of shape motion data, which is not stored in the motion itself.
*
*   Notes:
*     - Remember to free the pointer list after use.
*
*   Parameters:
*     - pMotion     : motion structure
*     - nbNode      : number of motion nodes
*     - nj2         : ninja2 motion key types, over 'VERT' and 'NORM'
*/
mt_ptrlist* mtMotGetPointers( const NJS_MOTION* pMotion, usize nbNode, bool nj2 );

EXTERN_END

#endif/*H_SAMT_MODEL*/
