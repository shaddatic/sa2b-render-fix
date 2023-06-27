/*
*	Sonic Adventure Mod Toolkit
* 
*	Model.h
*/

#ifndef _SAMT_MODEL_H_
#define _SAMT_MODEL_H_

typedef struct obj		NJS_OBJECT;
typedef struct cnkobj	NJS_CNK_OBJECT;
typedef struct gjsobj	GJS_OBJECT;

typedef struct _OBJ_LANDTABLE OBJ_LANDTABLE;

NJS_OBJECT*		LoadBasicObject(const utf8* fn);
NJS_CNK_OBJECT* LoadChunkObject(const utf8* fn);
GJS_OBJECT*		LoadGinjaObject(const utf8* fn);

OBJ_LANDTABLE*	LoadChunkLandTable(const utf8* fn);
OBJ_LANDTABLE*	LoadGinjaLandTable(const utf8* fn);

#endif /* _SAMT_MODEL_H_ */