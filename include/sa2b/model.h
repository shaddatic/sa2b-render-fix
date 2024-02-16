/*
*   Sonic Adventure Mod Tools (SA2B) - '/model.h'
*
*   Contains functions for loading Model and LandTable files
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SAMT_MODEL_H_
#define _SAMT_MODEL_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/ninja.h>

#include <sa2b/util/anyobj.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct _OBJ_LANDTABLE   OBJ_LANDTABLE;

/************************/
/*  Enums               */
/************************/
typedef enum
{
    MDL_FMT_NONE,   /* error            */
    MDL_FMT_BASIC,  /* basic format     */
    MDL_FMT_CHUNK,  /* chunk format     */
    MDL_FMT_GINJA,  /* ginja format     */
}
mdl_format;

/************************/
/*  Functions           */
/************************/
EXTERN_START
/*
*   These functions are for loading the community made binary model formats.
*
*   'Basic' refers to ".sa1___ " files
*   'Chunk' refers to ".sa2___ " files
*   'Ginja' refers to ".sa2b___" files
*/
/************************/
/*  Files               */
/************************/
/** Objects **/
NJS_OBJECT*     MDL_BasicLoadObjectFile( const utf8* fpath );
NJS_CNK_OBJECT* MDL_ChunkLoadObjectFile( const utf8* fpath );
GJS_OBJECT*     MDL_GinjaLoadObjectFile( const utf8* fpath );

/** Land Tables **/
OBJ_LANDTABLE*  MDL_ChunkLoadLandTableFile( const utf8* fpath );
OBJ_LANDTABLE*  MDL_GinjaLoadLandTableFile( const utf8* fpath );

/** Any format **/
ANY_OBJECT*     MDL_LoadObjectFile(    const utf8* fpath, mdl_format* pOptRetFmt );
OBJ_LANDTABLE*  MDL_LoadLandTableFile( const utf8* fpath, mdl_format* pOptRetFmt );

/************************/
/*  Copy                */
/************************/
/** Basic **/
NJS_MODEL*      MDL_BasicCopyModel(  const NJS_MODEL*  pModel  );
NJS_OBJECT*     MDL_BasicCopyObject( const NJS_OBJECT* pObject );

/** Chunk **/
Sint32*         MDL_ChunkCopyVList(  const Sint32*         pVList  );
Sint16*         MDL_ChunkCopyPList(  const Sint16*         pPList  );
NJS_CNK_MODEL*  MDL_ChunkCopyModel(  const NJS_CNK_MODEL*  pModel  );
NJS_CNK_OBJECT* MDL_ChunkCopyObject( const NJS_CNK_OBJECT* pObject );

/** Ginja **/
GJS_MODEL*      MDL_GinjaCopyModel(  const GJS_MODEL*  pModel  );
GJS_OBJECT*     MDL_GinjaCopyObject( const GJS_OBJECT* pObject );

/************************/
/*  Free                */
/************************/
/** Basic **/
void    MDL_BasicFreeModel(  NJS_MODEL*  pModel  );
void    MDL_BasicFreeObject( NJS_OBJECT* pObject );

/** Chunk **/
void    MDL_ChunkFreeVList(  Sint32*         pVList  );
void    MDL_ChunkFreePList(  Sint16*         pPList  );
void    MDL_ChunkFreeModel(  NJS_CNK_MODEL*  pModel  );
void    MDL_ChunkFreeObject( NJS_CNK_OBJECT* pObject );

/** Ginja **/
void    MDL_GinjaFreeModel(  GJS_MODEL*  pModel  );
void    MDL_GinjaFreeObject( GJS_OBJECT* pObject );

/** Land Tables **/
void    MDL_ChunkFreeLandTable( OBJ_LANDTABLE* pLand );
void    MDL_GinjaFreeLandTable( OBJ_LANDTABLE* pLand );

/************************/
/*  Additional Util     */
/************************/
/** Count the number of objects in an object tree **/
size_t  MDL_CountObject( const ANY_OBJECT* pObject );

/** Get size of Chunk Vertex and Poly lists (in bytes) **/
size_t  MDL_ChunkGetVListSize( const Sint32* pVList );
size_t  MDL_ChunkGetPListSize( const Sint16* pPList );

EXTERN_END

#endif /* _SAMT_MODEL_H_ */
