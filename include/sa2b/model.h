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
/*  Abstract Types      */
/************************/
typedef struct obj        NJS_OBJECT;
typedef struct cnkobj    NJS_CNK_OBJECT;
typedef struct gjsobj    GJS_OBJECT;

typedef struct _OBJ_LANDTABLE OBJ_LANDTABLE;

EXTERN_START

/************************/
/*  Functions           */
/************************/
NJS_OBJECT*     LoadBasicObject(const utf8* fn);
NJS_CNK_OBJECT* LoadChunkObject(const utf8* fn);
GJS_OBJECT*     LoadGinjaObject(const utf8* fn);

OBJ_LANDTABLE*  LoadChunkLandTable(const utf8* fn);
OBJ_LANDTABLE*  LoadGinjaLandTable(const utf8* fn);

/** Quick Open **/
NJS_OBJECT*     LoadBasicObject2(const utf8* path, const utf8* name);
NJS_CNK_OBJECT* LoadChunkObject2(const utf8* path, const utf8* name);
GJS_OBJECT*     LoadGinjaObject2(const utf8* path, const utf8* name);

OBJ_LANDTABLE*  LoadChunkLandTable2(const utf8* path, const utf8* name);
OBJ_LANDTABLE*  LoadGinjaLandTable2(const utf8* path, const utf8* name);

EXTERN_END

#endif /* _SAMT_MODEL_H_ */
