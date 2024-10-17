/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_material.h'
*
*   Description:
*       Chao body materials, colors, and textures.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_MATERIAL_H_
#define _SA2B_CHAO_MATERIAL_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/ninja.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task         task;
typedef struct al_model     AL_MODEL;
typedef struct al_object    AL_OBJECT;

/************************/
/*  Data                */
/************************/
#define ChaoColorList       DATA_ARY(int32_t, 0x01298448, [16])
#define EggColorList        DATA_ARY(int32_t, 0x01298414, [13])

/************************/
/*  Functions           */
/************************/
EXTERN_START
int32_t AL_MatSetChaoColor( task* tp, int16_t ColorNum );

void    AL_MatChangeModelTexture(  AL_MODEL*  pModel,  uint16_t TexID );
void    AL_MatChangeObjectTexture( AL_OBJECT* pObject, uint16_t TexID );

/** Create and free copies of objects (no official names yet) **/
NJS_CNK_OBJECT* AL_CopyObject( NJS_CNK_OBJECT* pObject );
void            AL_FreeObject( NJS_CNK_OBJECT* pObject );

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define AL_CopyObject_p                  FUNC_PTR(NJS_CNK_OBJECT*, __cdecl, (NJS_CNK_OBJECT*), 0x0055EBD0)
#   define AL_FreeObject_p                  FUNC_PTR(void           , __cdecl, (NJS_CNK_OBJECT*), 0x0055EDF0)

/** User-Function ptrs **/
#   define AL_MatSetChaoColor_p             ((void*)0x0055EA00)
#   define AL_MatChangeModelTexture_p       ((void*)0x0055EA00)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_MATERIAL_H_*/
