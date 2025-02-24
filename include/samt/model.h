/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/model.h'
*
*   Description:
*     Utility functions for the Ninja model types.
*/
#ifndef H_SAMT_MODEL
#define H_SAMT_MODEL

/************************/
/*  External Includes   */
/************************/
/****** System **********************************************************************/
#include <samt/shinobi/sg_xpt.h> /* core types                                      */

/****** Ninja ***********************************************************************/
#include <samt/ninja/njbasic.h> /* basic model format                               */
#include <samt/ninja/njchunk.h> /* chunk model format                               */
#include <samt/ninja/gjmodel.h> /* ginja model format                               */

EXTERN_START

/************************/
/*  Prototypes          */
/************************/
/************************************************************************************/
/*
*   Basic Model
*/
/****** Object **********************************************************************/
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
*     Pointer to object node at given index; or 'nullptr' if the index is larger
*   than the object tree.
*/
NJS_OBJECT* mtBscGetNode( const NJS_OBJECT* pObject, size_t ixNode );

/************************************************************************************/
/*
*   Chunk Model
*/
/****** Object **********************************************************************/
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
*     Pointer to object node at given index; or 'nullptr' if the index is larger
*   than the object tree.
*/
NJS_CNK_OBJECT* mtCnkGetNode( const NJS_CNK_OBJECT* pObject, size_t ixNode );

/****** Model ***********************************************************************/
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

/************************************************************************************/
/*
*   Ginja Model
*/
/****** Object **********************************************************************/
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
*     Pointer to object node at given index; or 'nullptr' if the index is larger
*   than the object tree.
*/
GJS_OBJECT* mtGjsGetNode( const GJS_OBJECT* pObject, size_t ixNode );

/****** Model ***********************************************************************/
/*
*   Description:
*     Get the total number of entries in a Ginja vertex info list.
*
*   Parameters:
*     - pVertinfo   : ginja vertex info
*
*   Returns:
*     The length of the Ginja vertinfo, including the termination entry.
*/
size_t  mtGjsVertinfoLength( const GJS_VERTINFO* pVertinfo );
/*
*   Description:
*     Get the total size of a Ginja vertex info list.
*
*   Parameters:
*     - pVertinfo   : ginja vertex info
*
*   Returns:
*     The size of the Ginja vertinfo, in bytes.
*/
size_t  mtGjsVertinfoSize( const GJS_VERTINFO* pVertinfo );

EXTERN_END

#endif/*H_SAMT_MODEL*/
