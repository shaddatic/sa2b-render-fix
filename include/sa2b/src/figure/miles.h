/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/figure/miles.h'
*
*   ~~ Under Construction ~~
*   Contains functions, structs, and data for Miles 'Tails' Prower
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_FIGURE_MILES_H_
#define _SA2B_FIGURE_MILES_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

#include <sa2b/src/player.h>

/************************/
/*  Structures          */
/************************/
typedef struct mileswk
{
    PLAYERWK pwk;
    char field_1BC[364];
    void* texData;
    float pSomeFloat;
    char field_38A[120];
    PLAYER_OBJECT* pObject0;
    PLAYER_OBJECT* pObject1;
    NJS_TEXLIST* TextureList;
    CHAR_OBJECT* ModelList;
    PLAYER_MOTION* MotionList;
    SHADOWWK shadow;
}
MILESWK;

/************************/
/*  Data                */
/************************/
#define pMilesWork              DataRef(MILESWK*, 0x01A521EC)

#define mtx_MilesInv            DataRef(NJS_MATRIX, 0x01A521BC)
#define mtx_MilesTails          DataRef(NJS_MATRIX, 0x01A5215C)
#define mtx_MilesShaderTails    DataRef(NJS_MATRIX, 0x01A5218C)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    MilesMotionCallBack(NJS_CNK_OBJECT* cnkobj);
void    MilesShadowMotionCallBack(NJS_CNK_OBJECT* cnkobj);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define MilesMotionCallBack_p           FuncPtr(void, __cdecl, (NJS_CNK_OBJECT*), 0x00750320)
#define MilesShadowMotionCallBack_p     FuncPtr(void, __cdecl, (NJS_CNK_OBJECT*), 0x0074FEF0)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_FIGURE_MILES_H_  */
