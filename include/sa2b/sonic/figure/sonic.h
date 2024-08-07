/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/figure/sonic.h'
*
*   ~~ Under Construction ~~
*   Contains functions, structs, and data for Sonic
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_FIGURE_SONIC_H_
#define _SA2B_FIGURE_SONIC_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

#include <sa2b/sonic/player.h>

/************************/
/*  Structures          */
/************************/
#define GET_SONICWK(_tp)    ((SONICWK*)(_tp)->awp)

typedef struct sonicwk
{
    PLAYERWK pw;

    char field_35C[4];
    int16_t flag;
    char field_35C_[4];
    int16_t unks_1;
    __int16 SpindashCounter;
    int field_36A;
    int field_36E;
    int field_372;
    __int16 field_376;
    NJS_VECTOR Position_;
    int field_386;
    int field_38A;
    PLAYER_OBJECT* pObjectData;
    NJS_TEXLIST* TextureList;
    PL_OBJECT* ModelList;
    PL_MOTION* MotionList;
}
SONICWK; // 928

/************************/
/*  Data                */
/************************/
#define SonicWorkPointer    DATA_REF(SONICWK*  , 0x01A51A9C)

#define mtx_SonicBase       DATA_REF(NJS_MATRIX, 0x01A51A00)
#define mtx_SonicHandL      DATA_REF(NJS_MATRIX, 0x01A51A3C)
#define mtx_SonicHandR      DATA_REF(NJS_MATRIX, 0x01A51AA0)
#define mtx_SonicFootL      DATA_REF(NJS_MATRIX, 0x01A51A6C)
#define mtx_SonicFootR      DATA_REF(NJS_MATRIX, 0x01A519D0)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    SonicMotionCallBack(NJS_CNK_OBJECT* cnkobj);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define SonicMotionCallBack_p    FUNC_PTR(void, __cdecl, (NJS_CNK_OBJECT*), 0x0071EAA0)

#endif /* SAMT_INCL_FUNCPTRS */

#endif /* _SA2B_FIGURE_SONIC_H_ */
