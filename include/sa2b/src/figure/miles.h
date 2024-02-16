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
#define GET_MILESWK(_tp)    ((MILESWK*)tp->awp)

typedef struct mileswk
{
    PLAYERWK pw;

    char field_38A[16];
    Angle TailsAngX;
    Angle TailsAngZ;
    Angle3 SomeAng;
    char field_3AC[40];
    PLAYER_OBJECT* pObject0;
    PLAYER_OBJECT* pObject1;
    NJS_TEXLIST* TextureList;
    PL_OBJECT* ModelList;
    PL_MOTION* MotionList;
    SHADOWWK shadow_tails;
}
MILESWK;

/************************/
/*  Data                */
/************************/
#define MilesWorkPointer        DataRef(MILESWK*, 0x01A521EC)

#define mtx_MilesBase           DataRef(NJS_MATRIX, 0x01A521BC)
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
