/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/figure/miles.h'
*
*   ~~ Under Construction ~~
*   Contains functions, structs, and data for Miles 'Tails' Prower
*/
#ifndef _SA2B_FIGURE_MILES_H_
#define _SA2B_FIGURE_MILES_H_

/************************/
/*  Includes            */
/************************/
#include <samt/ninja/njcommon.h>

#include <samt/sonic/player.h>

/************************/
/*  Structures          */
/************************/
#define GET_MILESWK(_tp)    ((MILESWK*)tp->awp)

typedef struct mileswk
{
    playerwk pw;

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
    shadowwk shadow_tails;
}
MILESWK;

/************************/
/*  Data                */
/************************/
#define MilesWorkPointer        DATA_REF(MILESWK*, 0x01A521EC)

#define mtx_MilesBase           DATA_REF(NJS_MATRIX, 0x01A521BC)
#define mtx_MilesTails          DATA_REF(NJS_MATRIX, 0x01A5215C)
#define mtx_MilesShaderTails    DATA_REF(NJS_MATRIX, 0x01A5218C)

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
#ifdef SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define MilesMotionCallBack_p            FUNC_PTR(void, __cdecl, (NJS_CNK_OBJECT*), 0x00750320)
#   define MilesShadowMotionCallBack_p      FUNC_PTR(void, __cdecl, (NJS_CNK_OBJECT*), 0x0074FEF0)

#endif /* SAMT_INCL_FUNCPTRS */

#endif /* _SA2B_FIGURE_MILES_H_  */
