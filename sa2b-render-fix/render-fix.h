#pragma once

#include <sa2b/core.h>

#include <sa2b/ninja/ninja.h>

#define arylen(arry)	(sizeof(arry) / sizeof(*arry))

/*
*	Enemy Jet
*/

void	EnemyJetDisplayerFix();

/*
*	Tint Disable
*/

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

/*
*	objpak
*/

enum
{
	TINTMD_KEEP,
	TINTMD_DISABLE
};

int		EditObjPak(bool tintDisable, float32 shadowOpacity);

/*
*	Stage Map
*/

void	StageMapTextBackdropRestore();
void	StageMapStretchFix();

/*
*	GUN Emblem
*/

void	GUNEmblemRestore();

/*
*	Shadows
*/

void	EnemyShadowEnable();

/*
*	Light Mod
*/

void	LightModifierFix();