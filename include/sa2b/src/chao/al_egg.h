/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_egg.h'
*
*   Description:
*       Contains functions, data, and enums related to Chao
*   eggs.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_EGG_H_
#define _SA2B_CHAO_EGG_H_

/************************/
/*  Includes            */
/************************/
/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Colli Info **/
#include <sa2b/src/c_colli/ccl_info.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task             TASK;
typedef struct al_gene          AL_GENE;
typedef struct chao_param_gc    CHAO_PARAM_GC;

/************************/
/*  Enums               */
/************************/
enum EggColor
{
    EggColor_Normal = 0x0,
    EggColor_Yellow = 0x1,
    EggColor_White = 0x2,
    EggColor_Brown = 0x3,
    EggColor_SkyBlue = 0x4,
    EggColor_Pink = 0x5,
    EggColor_Blue = 0x6,
    EggColor_Gray = 0x7,
    EggColor_Green = 0x8,
    EggColor_Red = 0x9,
    EggColor_AppleGreen = 0xA,
    EggColor_Purple = 0xB,
    EggColor_Orange = 0xC,
    EggColor_Black = 0xD,
    EggColor_BlendYellow = 0xE,
    EggColor_BlendWhite = 0xF,
    EggColor_BlendBrown = 0x10,
    EggColor_BlendSkyBlue = 0x11,
    EggColor_BlendPink = 0x12,
    EggColor_BlendBlue = 0x13,
    EggColor_BlendGray = 0x14,
    EggColor_BlendGreen = 0x15,
    EggColor_BlendRed = 0x16,
    EggColor_BlendAppleGreen = 0x17,
    EggColor_BlendPurple = 0x18,
    EggColor_BlendOrange = 0x19,
    EggColor_BlendBlack = 0x1A,
    EggColor_ShinyNormal = 0x1B,
    EggColor_ShinyYellow = 0x1C,
    EggColor_ShinyWhite = 0x1D,
    EggColor_ShinyBrown = 0x1E,
    EggColor_ShinySkyBlue = 0x1F,
    EggColor_ShinyPink = 0x20,
    EggColor_ShinyBlue = 0x21,
    EggColor_ShinyGray = 0x22,
    EggColor_ShinyGreen = 0x23,
    EggColor_ShinyRed = 0x24,
    EggColor_ShinyAppleGreen = 0x25,
    EggColor_ShinyPurple = 0x26,
    EggColor_ShinyOrange = 0x27,
    EggColor_ShinyBlack = 0x28,
    EggColor_ShinyBlendYellow = 0x29,
    EggColor_ShinyBlendWhite = 0x2A,
    EggColor_ShinyBlendBrown = 0x2B,
    EggColor_ShinyBlendSkyBlue = 0x2C,
    EggColor_ShinyBlendPink = 0x2D,
    EggColor_ShinyBlendBlue = 0x2E,
    EggColor_ShinyBlendGray = 0x2F,
    EggColor_ShinyBlendGreen = 0x30,
    EggColor_ShinyBlendRed = 0x31,
    EggColor_ShinyBlendAppleGreen = 0x32,
    EggColor_ShinyBlendPurple = 0x33,
    EggColor_ShinyBlendOrange = 0x34,
    EggColor_ShinyBlendBlack = 0x35,
    EggColor_Gold = 0x36,
    EggColor_Silver = 0x37,
    EggColor_Ruby = 0x38,
    EggColor_Sapphire = 0x39,
    EggColor_Emerald = 0x3A,
    EggColor_Amethyst = 0x3B,
    EggColor_Aquamarine = 0x3C,
    EggColor_Garnet = 0x3D,
    EggColor_Onyx = 0x3E,
    EggColor_Peridot = 0x3F,
    EggColor_Topaz = 0x40,
    EggColor_Pearl = 0x41,
    EggColor_Env0 = 0x42, // Metal 1
    EggColor_Env1 = 0x43, // Metal 2
    EggColor_Env2 = 0x44, // Glass
    EggColor_Env3 = 0x45, // Moon
    EggColor_Env4 = 0x46, // Rare
    nbEggColor = 0x47,
};

/************************/
/*  Structures          */
/************************/
#define GET_EGG_WORK(tp)    ((EGG_WORK*)tp->awp)

typedef struct // ANYWK
{
    int32_t type;
    int32_t SwingFlag;
    int32_t nbSwing;
    int32_t HeldAng;
    float32_t frame;
    int32_t BornTimer;
    float32_t ScaleAll;
    float32_t BuyoScale;
    float32_t BuyoVelo;
    int32_t NoColliTimer;
    int32_t Color;
}
EGG_WORK;

/************************/
/*  Data                */
/************************/
/** Objects **/
#define object_alm_egg_egg              DataAry(NJS_CNK_OBJECT, 0x0125CC64, [1])
#define object_alm_egg_eggtop           DataAry(NJS_CNK_OBJECT, 0x0125CC2C, [1]) /* Child of ^ */
#define object_alm_egg_eggbottom        DataAry(NJS_CNK_OBJECT, 0x0125C68C, [1]) /* Sibling of ^ */

/** Model is used in the Black Market **/
#define object_alo_dummyegg_dummyegg    DataAry(NJS_CNK_OBJECT, 0x0125D334, [1])
#define model_alo_dummyegg_dummyegg     DataAry(NJS_CNK_MODEL , 0x0125D31C, [1])

/** Motions **/
#define motion_alm_egg_pon              DataAry(NJS_MOTION    , 0x0125C6C4, [1])
#define motion_alm_egg_kyoro            DataAry(NJS_MOTION    , 0x0125CC9C, [1])
#define motion_alo_dummyegg             DataAry(NJS_MOTION    , 0x0125C11C, [1])

/** Collision info **/
#define colli_info_egg                  DataAry(CCL_INFO      , 0x008A5840, [3])

/************************/
/*  Functions           */
/************************/
EXTERN_START
TASK*   CreateEgg(AL_GENE* pGene, CHAO_PARAM_GC* pParamGC, int32_t IsParamCopy, const NJS_POINT3* pPos, int32_t type);

/** Task functions **/
void    AL_EggExecutor(TASK* tp);
void    AL_EggDisplayer(TASK* tp);
void    AL_EggDestructor(TASK* tp); /* Same function as many other ALO objects */

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define CreateEgg_p             FuncPtr(TASK*, __cdecl, (AL_GENE*, CHAO_PARAM_GC*, int32_t, const NJS_POINT3*, int32_t), 0x0057B9C0)
#define AL_EggExecutor_p        FuncPtr(void , __cdecl, (TASK*)                                                      , 0x0057B520)
#define AL_EggDisplayer_p       FuncPtr(void , __cdecl, (TASK*)                                                      , 0x0057B640)
#define AL_EggDestructor_p      FuncPtr(void , __cdecl, (TASK*)                                                      , 0x0057B9B0)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_EGG_H_ */
