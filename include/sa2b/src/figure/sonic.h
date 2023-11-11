/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/figure/sonic.h'
*
*   ~~ Under Construction ~~
*   Contains functions, structs, and data for Sonic
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_FIGURE_SONIC_H_
#define _SA2B_FIGURE_SONIC_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

#include <sa2b/src/player.h>

/************************/
/*  Structures          */
/************************/
typedef struct sonicwk
{
    PLAYERWK pwk;
    char field_1BC[428];
    __int16 SpindashCounter;
    int field_36A;
    int field_36E;
    int field_372;
    __int16 field_376;
    NJS_VECTOR Position_;
    sint8 gap384[2];
    int field_386;
    int field_38A;
    __int16 field_38E;
    float* field_390;
    NJS_TEXLIST* TextureList;
    CHAR_OBJECT* ModelList;
    PLAYER_MOTION* MotionList;
}
SONICWK;

/************************/
/*  Data                */
/************************/
#define pSonicWork          DataRef(SONICWK*  , 0x01A51A9C)

#define mtx_SonicHandL      DataRef(NJS_MATRIX, 0x01A51A3C)
#define mtx_SonicHandR      DataRef(NJS_MATRIX, 0x01A51AA0)
#define mtx_SonicFootL      DataRef(NJS_MATRIX, 0x01A51A6C)
#define mtx_SonicFootR      DataRef(NJS_MATRIX, 0x01A519D0)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    SonicMotionCallBack(NJS_CNK_OBJECT* cnkobj);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define SonicMotionCallBack_p   FuncPtr(void, __cdecl, (NJS_CNK_OBJECT*), 0x0071EAA0)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_FIGURE_SONIC_H_ */
