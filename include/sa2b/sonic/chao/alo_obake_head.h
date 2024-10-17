/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/alo_obake_head.h'
*
*   Description:
*       Contains enums and functions related to Chao masks.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_OBAKEHEAD_H_
#define _SA2B_CHAO_OBAKEHEAD_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/ninja.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task             task;
typedef struct item_save_info   ITEM_SAVE_INFO;

/************************/
/*  Enums               */
/************************/
typedef enum
{
    OBAKE_HEAD_PARTS_NONE = 0x0,
    OBAKE_HEAD_PARTS_PUMPKIN = 0x1,
    OBAKE_HEAD_PARTS_SKULL = 0x2,
    OBAKE_HEAD_PARTS_APPLE = 0x3,
    OBAKE_HEAD_PARTS_BUCKET = 0x4,
    OBAKE_HEAD_PARTS_CAN = 0x5,
    OBAKE_HEAD_PARTS_CDBOX = 0x6,
    OBAKE_HEAD_PARTS_FLOWERPOT = 0x7,
    OBAKE_HEAD_PARTS_PAPERBAG = 0x8,
    OBAKE_HEAD_PARTS_STEWPAN = 0x9,
    OBAKE_HEAD_PARTS_STUMP = 0xA,
    OBAKE_HEAD_PARTS_WMELON = 0xB,
    OBAKE_HEAD_PARTS_WOOL_A = 0xC,
    OBAKE_HEAD_PARTS_WOOL_B = 0xD,
    OBAKE_HEAD_PARTS_WOOL_C = 0xE,
    OBAKE_HEAD_PARTS_TEETHINGRING = 0xF,
    OBAKE_HEAD_PARTS_EGG = 0x10,
    OBAKE_HEAD_PARTS_EGG_Yellow = 0x11,
    OBAKE_HEAD_PARTS_EGG_White = 0x12,
    OBAKE_HEAD_PARTS_EGG_Brown = 0x13,
    OBAKE_HEAD_PARTS_EGG_SkyBlue = 0x14,
    OBAKE_HEAD_PARTS_EGG_Pink = 0x15,
    OBAKE_HEAD_PARTS_EGG_Blue = 0x16,
    OBAKE_HEAD_PARTS_EGG_Gray = 0x17,
    OBAKE_HEAD_PARTS_EGG_Green = 0x18,
    OBAKE_HEAD_PARTS_EGG_Red = 0x19,
    OBAKE_HEAD_PARTS_EGG_AppleGreen = 0x1A,
    OBAKE_HEAD_PARTS_EGG_Purple = 0x1B,
    OBAKE_HEAD_PARTS_EGG_Orange = 0x1C,
    OBAKE_HEAD_PARTS_EGG_Black = 0x1D,
    OBAKE_HEAD_PARTS_EGG_BlendYellow = 0x1E,
    OBAKE_HEAD_PARTS_EGG_BlendWhite = 0x1F,
    OBAKE_HEAD_PARTS_EGG_BlendBrown = 0x20,
    OBAKE_HEAD_PARTS_EGG_BlendSkyBlue = 0x21,
    OBAKE_HEAD_PARTS_EGG_BlendPink = 0x22,
    OBAKE_HEAD_PARTS_EGG_BlendBlue = 0x23,
    OBAKE_HEAD_PARTS_EGG_BlendGray = 0x24,
    OBAKE_HEAD_PARTS_EGG_BlendGreen = 0x25,
    OBAKE_HEAD_PARTS_EGG_BlendRed = 0x26,
    OBAKE_HEAD_PARTS_EGG_BlendAppleGreen = 0x27,
    OBAKE_HEAD_PARTS_EGG_BlendPurple = 0x28,
    OBAKE_HEAD_PARTS_EGG_BlendOrange = 0x29,
    OBAKE_HEAD_PARTS_EGG_BlendBlack = 0x2A,
    OBAKE_HEAD_PARTS_EGG_ShinyNormal = 0x2B,
    OBAKE_HEAD_PARTS_EGG_ShinyYellow = 0x2C,
    OBAKE_HEAD_PARTS_EGG_ShinyWhite = 0x2D,
    OBAKE_HEAD_PARTS_EGG_ShinyBrown = 0x2E,
    OBAKE_HEAD_PARTS_EGG_ShinySkyBlue = 0x2F,
    OBAKE_HEAD_PARTS_EGG_ShinyPink = 0x30,
    OBAKE_HEAD_PARTS_EGG_ShinyBlue = 0x31,
    OBAKE_HEAD_PARTS_EGG_ShinyGray = 0x32,
    OBAKE_HEAD_PARTS_EGG_ShinyGreen = 0x33,
    OBAKE_HEAD_PARTS_EGG_ShinyRed = 0x34,
    OBAKE_HEAD_PARTS_EGG_ShinyAppleGreen = 0x35,
    OBAKE_HEAD_PARTS_EGG_ShinyPurple = 0x36,
    OBAKE_HEAD_PARTS_EGG_ShinyOrange = 0x37,
    OBAKE_HEAD_PARTS_EGG_ShinyBlack = 0x38,
    OBAKE_HEAD_PARTS_EGG_ShinyBlendYellow = 0x39,
    OBAKE_HEAD_PARTS_EGG_ShinyBlendWhite = 0x3A,
    OBAKE_HEAD_PARTS_EGG_ShinyBlendBrown = 0x3B,
    OBAKE_HEAD_PARTS_EGG_ShinyBlendSkyBlue = 0x3C,
    OBAKE_HEAD_PARTS_EGG_ShinyBlendPink = 0x3D,
    OBAKE_HEAD_PARTS_EGG_ShinyBlendBlue = 0x3E,
    OBAKE_HEAD_PARTS_EGG_ShinyBlendGray = 0x3F,
    OBAKE_HEAD_PARTS_EGG_ShinyBlendGreen = 0x40,
    OBAKE_HEAD_PARTS_EGG_ShinyBlendRed = 0x41,
    OBAKE_HEAD_PARTS_EGG_ShinyBlendAppleGreen = 0x42,
    OBAKE_HEAD_PARTS_EGG_ShinyBlendPurple = 0x43,
    OBAKE_HEAD_PARTS_EGG_ShinyBlendOrange = 0x44,
    OBAKE_HEAD_PARTS_EGG_ShinyBlendBlack = 0x45,
    OBAKE_HEAD_PARTS_EGG_Gold = 0x46,
    OBAKE_HEAD_PARTS_EGG_Silver = 0x47,
    OBAKE_HEAD_PARTS_EGG_Ruby = 0x48,
    OBAKE_HEAD_PARTS_EGG_Sapphire = 0x49,
    OBAKE_HEAD_PARTS_EGG_Emerald = 0x4A,
    OBAKE_HEAD_PARTS_EGG_Amethyst = 0x4B,
    OBAKE_HEAD_PARTS_EGG_Aquamarine = 0x4C,
    OBAKE_HEAD_PARTS_EGG_Garnet = 0x4D,
    OBAKE_HEAD_PARTS_EGG_Onyx = 0x4E,
    OBAKE_HEAD_PARTS_EGG_Peridot = 0x4F,
    OBAKE_HEAD_PARTS_EGG_Topaz = 0x50,
    OBAKE_HEAD_PARTS_EGG_Pearl = 0x51,
    OBAKE_HEAD_PARTS_EGG_Env0 = 0x52,
    OBAKE_HEAD_PARTS_EGG_Env1 = 0x53,
    OBAKE_HEAD_PARTS_EGG_Env2 = 0x54,
    OBAKE_HEAD_PARTS_END = 0x55,
}
eHEAD_PARTS;

/************************/
/*  Functions           */
/************************/
EXTERN_START
task*   ALO_ObakeHeadCreate(eHEAD_PARTS kind, NJS_POINT3* pPos, Angle AngY, NJS_VECTOR* pVelo, ITEM_SAVE_INFO* pSaveInfo);

/** Task functions **/
void    ALO_ObakeHeadExecutor(task* tp);
void    ALO_ObakeHeadDisplayer(task* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define ALO_ObakeHeadCreate_p            FUNC_PTR(task*, __cdecl, (eHEAD_PARTS kind, NJS_POINT3* pPos, Angle AngY, NJS_VECTOR* pVelo, ITEM_SAVE_INFO* pSaveInfo), 0x0054A540)
#   define ALO_ObakeHeadExecutor_p          FUNC_PTR(void , __cdecl, (task*)                                                                                       , 0x0054A050)
#   define ALO_ObakeHeadDisplayer_p         FUNC_PTR(void , __cdecl, (task*)                                                                                       , 0x0054A0F0)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_OBAKEHEAD_H_*/
