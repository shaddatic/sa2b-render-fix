#pragma once

#include <sa2b/ninja/ninja.h>

void	DefaultGinjaDiffuseEnable();

void	DisableTintGinjaModel(GJS_MODEL* pModel);
void	DisableTintGinjaObject(GJS_OBJECT* pObject);

void	DisableTintChunkModel(NJS_CNK_MODEL* pModel);
void	DisableTintChunkObject(NJS_CNK_OBJECT* pObject);

void	DisableTintGinjaObjectList(int* pList, int nbList);
void	DisableTintGinjaModelList(int* pList, int nbList);

void	DisableTintChunkObjectList(int* pList, int nbList);
void	DisableTintChunkModelList(int* pList, int nbList);

#define DisableTintGinjaObjectListEx(list)	DisableTintGinjaObjectList(list, arylen(list))
#define DisableTintGinjaModelListEx(list)	DisableTintGinjaModelList(list, arylen(list))

#define DisableTintChunkObjectListEx(list)	DisableTintChunkObjectList(list, arylen(list))
#define DisableTintChunkModelListEx(list)	DisableTintChunkModelList(list, arylen(list))