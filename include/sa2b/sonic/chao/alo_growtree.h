/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/alo_growtree.h'
*
*   Description:
*       Contains enums, structs, data, and functions related to Chao World trees.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_GROWTREE_H_
#define _SA2B_CHAO_GROWTREE_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/ninja.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task             TASK;
typedef struct colliwk          COLLIWK;
typedef struct tree_save_info   TREE_SAVE_INFO;

/************************/
/*  Enums               */
/************************/
typedef enum
{
    TREE_NONE,
    TREE_MORIMORI,
    TREE_PAKUPAKU,
    TREE_HERO,
    TREE_DARK,
    TREE_MARU,
    TREE_SANKAKU,
    TREE_SIKAKU,
    TREE_LOCAL,
    TREE_END,
}
eTREE_KIND;

typedef enum
{
    TREE_ST_PLANT,
    TREE_ST_SEED,
    TREE_ST_SAPLING,
    TREE_ST_ADULT,
    TREE_ST_DEAD,
    TREE_ST_LOCAL,
}
eTREE_STATE;

enum
{
    MD_PLANT,
    MD_SEED,
    MD_SEED_TO_SAPLING,
    MD_SEED_TO_SAPLING2,
    MD_SAPLING,
    MD_SAPLING_GROW,
    MD_SAPLING_GROW2,
    MD_ADULT,
    MD_DEAD,
    MD_DEAD2,
    MD_FADEOUT,
};

/************************/
/*  Structures          */
/************************/
typedef struct
{
    f32       growth;
    f32       AimGrowth;
    int32_t SwingCounter;
    NJS_POINT3 pos;
    int32_t angx;
    int32_t angy;
}
FRUIT_INFO;

#define GET_TREE_WORK(_tp)      ((TREE_WORK*)_tp->twp)

typedef struct // TASKWK
{
    int8_t mode;
    int8_t smode;
    int8_t id;
    int8_t btimer;
    int16_t flag;
    int16_t wtimer;
    Angle3 ang;
    NJS_POINT3 pos;
    NJS_POINT3 scl;
    COLLIWK* cwp;

    uint8_t type;
    uint8_t state;
    f32     growth;
    int32_t life;
    int32_t water;
    uint8_t pos_num;
    FRUIT_INFO fruit[3];
    f32     scale;
    f32     scaleSpd;
    int32_t ThirstyFlag;
    int32_t WaterFlag;
    int32_t LeafRotAng;
    f32     LeafWidth;
    int32_t LeafDispNum;
    Angle FruitRotAng;
    f32     FruitWidth;
    int32_t FruitDisplayNum;
    int32_t SwingFlag;
    int32_t SwingCountFlag;
    f32     SwingDist;
    Angle RollAngle;
    Angle TouchAngle;
    int32_t ChaoSwingPhase;
    int32_t RollPhase;
    int32_t garden;
    TREE_SAVE_INFO* pMySaveInfo;
    NJS_TEXLIST* texlist;
    NJS_CNK_OBJECT* pLocalObject;
    NJS_CNK_OBJECT* pShadowObject;
    NJS_CNK_OBJECT* pCopyObject;
}
TREE_WORK;

/************************/
/*  Data                */
/************************/
#define TreeSetPos              DATA_ARY(NJS_VECTOR, 0x01366B30, [3][10])
#define LeafPhaseList           DATA_ARY(Angle     , 0x012E8AEC, [11])
#define FruitPhaseList          DATA_ARY(Angle     , 0x013291B4, [4])

/************************/
/*  Functions           */
/************************/
EXTERN_START
TASK*   ALO_GrowTreeCreate(NJS_POINT3* pPos, TREE_SAVE_INFO* pInfo);

/** Task functions **/
void    ALO_GrowTreeExecutor(   TASK* tp );
void    ALO_GrowTreeDisplayer(  TASK* tp );
void    ALO_GrowTreeDestructor( TASK* tp );

/** Internal functions **/
void    CalcFruitPos(NJS_POINT3* pPos, TREE_WORK* pTree, int32_t FruitNum);
void    CalcFruitPosSub(NJS_POINT3* pPos, TREE_WORK* pTree, NJS_CNK_OBJECT* pObject, int32_t FruitNum);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define ALO_GrowTreeCreate_p         FUNC_PTR(TASK*, __cdecl, (NJS_POINT3*, TREE_SAVE_INFO*)                     , 0x00548210)
#   define ALO_GrowTreeExecutor_p       FUNC_PTR(void , __cdecl, (TASK*)                                            , 0x00546810)
#   define ALO_GrowTreeDisplayer_p      FUNC_PTR(void , __cdecl, (TASK*)                                            , 0x00547E70)
#   define ALO_GrowTreeDestructor_p     FUNC_PTR(void , __cdecl, (TASK*)                                            , 0x005481E0)
#   define CalcFruitPos_p               FUNC_PTR(void , __cdecl, (NJS_POINT3*, TREE_WORK*, int32_t)                 , 0x00546670)
#   define CalcFruitPosSub_p            FUNC_PTR(void , __cdecl, (NJS_POINT3*, TREE_WORK*, NJS_CNK_OBJECT*, int32_t), 0x00546530)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_GROWTREE_H_*/
