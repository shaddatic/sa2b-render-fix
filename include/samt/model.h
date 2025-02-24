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
//#include <samt/shinobi/sg_xpt.h>

/****** Ninja ***********************************************************************/
#include <samt/ninja/njbasic.h>
#include <samt/ninja/njchunk.h>
#include <samt/ninja/gjmodel.h>

EXTERN_START

/************************/
/*  Prototypes          */
/************************/
/************************************************************************************/
/*
*   Basic Model
*/
/****** Object **********************************************************************/
size_t  mtBscNodeCount( const NJS_OBJECT* pObject );

NJS_OBJECT* mtBscGetNode( const NJS_OBJECT* pObject, size_t ixNode );

/************************************************************************************/
/*
*   Chunk Model
*/
/****** Object **********************************************************************/
size_t  mtCnkNodeCount( const NJS_CNK_OBJECT* pObject );

NJS_CNK_OBJECT* mtCnkGetNode( const NJS_CNK_OBJECT* pObject, size_t ixNode );

/****** Model ***********************************************************************/
size_t  mtCnkVListSize( const Sint32* pVList );
size_t  mtCnkPListSize( const Sint16* pPList );

/************************************************************************************/
/*
*   Ginja Model
*/
/****** Object **********************************************************************/
size_t  mtGjsNodeCount( const GJS_OBJECT* pObject );

GJS_OBJECT* mtGjsGetNode( const GJS_OBJECT* pObject, size_t ixNode );

/****** Model ***********************************************************************/
size_t  mtGjsVertinfoLength( const GJS_VERTINFO* pVertinfo );
size_t  mtGjsVertinfoSize(  const GJS_VERTINFO* pVertinfo );

EXTERN_END

#endif/*H_SAMT_MODEL*/
