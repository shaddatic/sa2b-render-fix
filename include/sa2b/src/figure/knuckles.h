/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/figure/knuckles.h'
*
*   ~~ Under Construction ~~
*   Contains functions, structs, and data for Knuckles
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_FIGURE_KNUCKLES_H_
#define _SA2B_FIGURE_KNUCKLES_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

#include <sa2b/src/player.h>

/************************/
/*  Structures          */
/************************/
#define GET_KNUCKLESWK(_tp)     ((KNUCKLESWK*)tp->awp)

typedef struct knuckleswk
{
    PLAYERWK pw;

    char field_308[78];
    signed __int16 someAng0;
    signed __int16 someAng1;
    __int16 chaos0_texid;
    int someAnimationIndex;
    char field_3B0[4];
    float someFlt;
    Angle someHeadAng;
    char field_3C0[36];
    PLAYER_OBJECT* pObjectData0;
    PLAYER_OBJECT* pObjectData1;
    PLAYER_OBJECT* pObjectData2;
    NJS_TEXLIST* TextureList;
    NJS_TEXLIST* EffectTextureList;
    PL_OBJECT* ModelList;
    PL_MOTION* MotionList;
    NJS_MOTION_LINK pMotionLink;
    char field_410[16];
}
KNUCKLESWK;

/************************/
/*  Data                */
/************************/
#define KnucklesWorkPointer     DataRef(KNUCKLESWK*, 0x01A51C88)

#define mtx_KnucklesBase        DataRef(NJS_MATRIX , 0x01A51BEC)
#define mtx_KnucklesHead        DataRef(NJS_MATRIX , 0x01A51CBC)
#define mtx_KnucklesBody        DataRef(NJS_MATRIX , 0x01A51B3C)
#define mtx_KnucklesHandL       DataRef(NJS_MATRIX , 0x01A51C58)
#define mtx_KnucklesHandR       DataRef(NJS_MATRIX , 0x01A51C8C)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    KnucklesMotionCallBack(NJS_CNK_OBJECT* cnkobj);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define KnucklesMotionCallBack_p    FuncPtr(void, __cdecl, (NJS_CNK_OBJECT*), 0x0072EAA0)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_FIGURE_KNUCKLES_H_ */
