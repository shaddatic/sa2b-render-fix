/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_world.h'
*
*   Contains enums, structs, data, and functions related to Chao World's texture loading engine.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_WORLD_H_
#define _SA2B_CHAO_WORLD_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task     TASK;

/************************/
/*  Enums               */
/************************/
enum
{
    ALW_CATEGORY_CHAO,
    ALW_CATEGORY_EGG,
    ALW_CATEGORY_MINIMAL,
    ALW_CATEGORY_FRUIT,
    ALW_CATEGORY_TREE,
    ALW_CATEGORY_GROWTREE,
    ALW_CATEGORY_TOY,
    ALW_CATEGORY_SEED,
    ALW_CATEGORY_SOUND,
    ALW_CATEGORY_MASK,
    ALW_CATEGORY_SPECIAL,
    NB_CATEGORY,
};

enum
{
    ALW_KIND_NONE = 0x0,
    ALW_KIND_CDR = 0x1,
    ALW_KIND_TV = 0x2,
    ALW_KIND_RADICASE = 0x3,
    ALW_KIND_BALL = 0x4,
    ALW_KIND_PIANO = 0x5,
    ALW_KIND_ORGAN = 0x6,
    ALW_KIND_HORSE = 0x7,
    ALW_KIND_BOX = 0x8,
};

/************************/
/*  Structures          */
/************************/
typedef struct
{
    sint16 mood;
    sint16 belly;
    sint16 addexp[8];
}
GROW_PARAM;

#define GET_ALW_ENTRY_WORK(tp) ((ALW_ENTRY_WORK*)tp->fwp)

typedef struct al_entry_work
{
    uint16 category;
    uint16 num;
    uint16 kind;
    uint16 flag;
    void* pSaveInfo;
    sint32 CommuID;
    NJS_POINT3 pos;
    Angle3 ang;
    float32 radius;
    float32 offset;
    float32 CamDist;
    sint16 command;
    sint16 command_value;
    sint16 state;
    TASK* tp;
    struct al_entry_work* pCommu;
    struct al_entry_work* pLockOn;
}
ALW_ENTRY_WORK;

/************************/
/*  Data                */
/************************/
#define ChaoWorldLoadFlag       DataRef(bool32        , 0x01A5AF0C)

#define WorldMasterTask         DataRef(TASK*         , 0x01A0F94C)

#define WorldEntryList          DataAry(ALW_ENTRY_WORK, 0x01DC0FC0, [11][64])
#define nbWorldEntry            DataAry(sint32        , 0x01DC0F80, [11])
#define nbMaxEntry              DataAry(sint32        , 0x008AB838, [11])

#define FruitGrowParam          DataAry(GROW_PARAM    , 0x008A6448, [24])
#define MinimalGrowParam        DataAry(GROW_PARAM    , 0x008A6240, [26])

#define Clock                   DataRef(sint32        , 0x01DBED74)
#define gBusy_0                 DataRef(sint32        , 0x019F6440)
#define gLoaded_0               DataRef(sint32        , 0x019F6444)
#define gCommuID                DataRef(uint16        , 0x01A5B5EC)

/************************/
/*  Functions           */
/************************/
EXTERN_START
sint32  AL_ConfirmLoadIsBusy(void);

/** Initialize and reset ALW module params for new stage **/
void    ALW_Create(void);

sint32  ALW_Entry(uint16 category, TASK* tp, uint16 kind);
sint32  ALW_Entry2(uint16 category, TASK* tp, uint16 kind, void* pSaveInfo);

sint32  ALW_GetMaxEntry(uint16 category); /* Toolkit addition */

TASK*   ALW_GetTask(sint32 category, uint16 num);
sint32  ALW_GetCategory(TASK* tp);
uint16  ALW_GetKind(TASK* tp); /* Toolkit addition */

sint32  ALW_AttentionOn(TASK* tp1, TASK* tp2);
sint32  ALW_AttentionOff(TASK* tp);
ALW_ENTRY_WORK* ALW_IsAttention(TASK* tp);
sint32  ALW_IsSheAttentionOtherOne(TASK* pMyTask, TASK* pHerTask);
sint32  ALW_CommunicationOn(TASK* tp1, TASK* tp2);
sint32  ALW_CommunicationOff(TASK* tp);
ALW_ENTRY_WORK* ALW_IsCommunication(TASK* tp);
ALW_ENTRY_WORK* ALW_IsCommunicationEx(TASK* tp, uint16 category);
sint32  ALW_RecieveCommand(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define ALW_Create_p        FuncPtr(void, __cdecl, (void), 0x00530B80)

/** User-Function ptrs **/
EXTERN const void* const ALW_Entry2_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_WORLD_H_ */
