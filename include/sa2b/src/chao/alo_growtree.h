/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/alo_growtree.h'
*
*   Contains enums, structs, data, and functions related to Chao World trees.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
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
    TREE_ST_PLANT = 0x0,
    TREE_ST_SEED = 0x1,
    TREE_ST_SAPLING = 0x2,
    TREE_ST_ADULT = 0x3,
    TREE_ST_DEAD = 0x4,
    TREE_ST_LOCAL = 0x5,
}
eTREE_STATE;

/************************/
/*  Structures          */
/************************/
typedef struct
{
    float32 growth;
    float32 AimGrowth;
    sint32 SwingCounter;
    NJS_POINT3 pos;
    sint32 angx;
    sint32 angy;
}
FRUIT_INFO;

typedef struct // TASKWK
{
    sint8 mode;
    sint8 smode;
    sint8 id;
    sint8 btimer;
    sint16 flag;
    sint16 wtimer;
    Angle3 ang;
    NJS_POINT3 pos;
    NJS_POINT3 scl;
    COLLIWK* cwp;

    uint8 type;
    uint8 state;
    float32 growth;
    sint32 life;
    sint32 water;
    uint8 pos_num;
    FRUIT_INFO fruit[3];
    float32 scale;
    float32 scaleSpd;
    sint32 ThirstyFlag;
    sint32 WaterFlag;
    sint32 LeafRotAng;
    float32 LeafWidth;
    sint32 LeafDispNum;
    Angle FruitRotAng;
    float32 FruitWidth;
    sint32 FruitDisplayNum;
    sint32 SwingFlag;
    sint32 SwingCountFlag;
    float32 SwingDist;
    Angle RollAngle;
    Angle TouchAngle;
    sint32 ChaoSwingPhase;
    sint32 RollPhase;
    sint32 garden;
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
#define TreeSetPos              DataAry(NJS_VECTOR, 0x01366B30, [3][10])
#define LeafPhaseList           DataAry(Angle     , 0x012E8AEC, [11])
#define FruitPhaseList          DataAry(Angle     , 0x013291B4, [4])

/************************/
/*  Functions           */
/************************/
EXTERN_START
TASK*   ALO_GrowTreeCreate(NJS_POINT3* pPos, TREE_SAVE_INFO* info);

/** Task functions **/
void    ALO_GrowTreeExecutor(TASK* tp);
void    ALO_GrowTreeDisplayer(TASK* tp);
void    ALO_GrowTreeDestructor(TASK* tp);

/** Internal functions **/
void    CalcFruitPos(NJS_POINT3* pPos, TREE_WORK* pTree, sint32 FruitNum);
void    CalcFruitPosSub(NJS_POINT3* pPos, TREE_WORK* pTree, NJS_CNK_OBJECT* pObject, sint32 FruitNum);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define ALO_GrowTreeCreate_p        FuncPtr(TASK*, __cdecl, (NJS_POINT3*, TREE_SAVE_INFO*)                    , 0x00548210)
#define ALO_GrowTreeExecutor_p      FuncPtr(void , __cdecl, (TASK*)                                           , 0x00546810)
#define ALO_GrowTreeDisplayer_p     FuncPtr(void , __cdecl, (TASK*)                                           , 0x00547E70)
#define ALO_GrowTreeDestructor_p    FuncPtr(void , __cdecl, (TASK*)                                           , 0x005481E0)
#define CalcFruitPos_p              FuncPtr(void , __cdecl, (NJS_POINT3*, TREE_WORK*, sint32)                 , 0x00546670)
#define CalcFruitPosSub_p           FuncPtr(void , __cdecl, (NJS_POINT3*, TREE_WORK*, NJS_CNK_OBJECT*, sint32), 0x00546530)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_GROWTREE_H_ */
