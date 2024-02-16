/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_material.h'
*
*   Contains structs, data, and functions related to Chao landmarks.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
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
typedef struct task         TASK;
typedef struct al_model     AL_MODEL;
typedef struct al_object    AL_OBJECT;

/************************/
/*  Data                */
/************************/
#define ChaoColorList       DataAry(int32_t, 0x01298448, [16])
#define EggColorList        DataAry(int32_t, 0x01298414, [13])

/************************/
/*  Functions           */
/************************/
EXTERN_START
int32_t  AL_MatSetChaoColor(TASK* tp, int16_t ColorNum);

void    AL_MatChangeModelTexture(AL_MODEL* pModel, uint16_t TexID);
void    AL_MatChangeObjectTexture(AL_OBJECT* pObject, uint16_t TexID);

/** Create and free copies of objects (no official names yet) **/
NJS_CNK_OBJECT* AL_CopyObject(NJS_CNK_OBJECT* pObject);
void            AL_FreeObject(NJS_CNK_OBJECT* pObject);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define AL_CopyObject_p     FuncPtr(NJS_CNK_OBJECT*, __cdecl, (NJS_CNK_OBJECT*), 0x0055EBD0)
#define AL_FreeObject_p     FuncPtr(void           , __cdecl, (NJS_CNK_OBJECT*), 0x0055EDF0)

/** User-Function ptrs **/
EXTERN const void* const AL_MatSetChaoColor_p;
EXTERN const void* const AL_MatChangeModelTexture_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_MATERIAL_H_ */
