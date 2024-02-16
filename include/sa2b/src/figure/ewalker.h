/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/figure/ewalker.h'
*
*   ~~ Under Construction ~~
*   Contains functions, structs, and data for the Egg Walker
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_FIGURE_EWALKER_H_
#define _SA2B_FIGURE_EWALKER_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

#include <sa2b/src/player.h>

/************************/
/*  Structures          */
/************************/
#define GET_WALKERWK(_tp)       ((WALKERWK*)tp->awp)

typedef struct walkerwk
{
    PLAYERWK pw;

    char field_35C;
    char field_35D;
    char field_35E;
    char field_35F;
    char field_360;
    char field_361[3];
    __int16 field_364;
    __int16 field_366;
    __int16 field_368;
    __int16 field_36A;
    __int16 field_36C;
    __int16 field_36E;
    char field_370[4];
    float field_374;
    char field_378[8];
    int field_380;
    char field_384[12];
    float field_390;
    float field_394;
    float field_398;
    int field_39C;
    char field_3A0[132];
    int alsosomerotation;
    int field_428;
    int field_42C;
    int CannonRecoil;
    int alsomayberotation;
    float field_438;
    float field_43C;
    float field_440;
    NJS_TEXLIST* CommonTextureList;
    NJS_TEXLIST* TextureList;
    PL_OBJECT* ModelList;
    PL_MOTION* MotionList;
}
WALKERWK;

/************************/
/*  Data                */
/************************/
#define EggWalkerWorkPointer            DataRef(WALKERWK* , 0x01A51F0C)

#define mtx_EWalkerBase                 DataRef(NJS_MATRIX, 0x01A51F70)
#define mtx_EWalkerLaserBlaster         DataRef(NJS_MATRIX, 0x01A51EAC)
#define mtx_EWalkerLargeCannon          DataRef(NJS_MATRIX, 0x01A51D2C)
#define mtx_EWalkerJetEngineL           DataRef(NJS_MATRIX, 0x01A52000)
#define mtx_EWalkerJetEngineR           DataRef(NJS_MATRIX, 0x01A52060)
#define mtx_EWalkerProtectiveArmor      DataRef(NJS_MATRIX, 0x01A520C0)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    EggWalkerMotionCallBack(NJS_CNK_OBJECT* cnkobj);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define EggWalkerMotionCallBack_p       FuncPtr(void, __cdecl, (NJS_CNK_OBJECT*), 0x00744020)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_FIGURE_EWALKER_H_ */
