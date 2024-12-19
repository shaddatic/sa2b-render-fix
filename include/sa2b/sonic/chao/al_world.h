/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_world.h'
*
*   Description:
*       Contains enums, structs, data, and functions related to
*   Chao World communications & general execution.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
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
typedef struct task     task;

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
    ALW_KIND_NONE,
    ALW_KIND_CDR,
    ALW_KIND_TV,
    ALW_KIND_RADICASE,
    ALW_KIND_BALL,
    ALW_KIND_PIANO,
    ALW_KIND_ORGAN,
    ALW_KIND_HORSE,
    ALW_KIND_BOX,
};

enum
{
    ALW_CMD_ERROR = -1,

    ALW_CMD_NONE,
    ALW_CMD_GO,
    ALW_CMD_EAT,
    ALW_CMD_CHANGE,
    ALW_CMD_FINISH,
    ALW_CMD_PLANTED,
    ALW_CMD_BYE,
};

/************************/
/*  Structures          */
/************************/
typedef struct
{
    s16 mood;
    s16 belly;
    s16 addexp[8];
}
GROW_PARAM;

#define GET_ALW_ENTRY_WORK(tp) ((ALW_ENTRY_WORK*)tp->fwp)

typedef struct al_entry_work
{
    u16             category;
    u16             num;
    u16             kind;
    u16             flag;
    void*           pSaveInfo;
    s32             CommuID;
    NJS_POINT3      pos;
    Angle3          ang;
    f32             radius;
    f32             offset;
    f32             CamDist;
    s16             command;
    s16             command_value;
    s16             state;
    task*           tp;
    struct al_entry_work* pCommu;
    struct al_entry_work* pLockOn;
}
ALW_ENTRY_WORK;

/************************/
/*  Data                */
/************************/
#define ChaoWorldLoadFlag       DATA_REF(b32           , 0x01A5AF0C)

#define WorldMasterTask         DATA_REF(task*         , 0x01A0F94C)

#define WorldEntryList          DATA_ARY(ALW_ENTRY_WORK, 0x01DC0FC0, [11][64])
#define nbWorldEntry            DATA_ARY(int32_t       , 0x01DC0F80, [11])
#define nbMaxEntry              DATA_ARY(int32_t       , 0x008AB838, [11])

#define FruitGrowParam          DATA_ARY(GROW_PARAM    , 0x008A6448, [24])
#define MinimalGrowParam        DATA_ARY(GROW_PARAM    , 0x008A6240, [26])

#define Clock                   DATA_REF(int32_t       , 0x01DBED74)
#define gCommuID                DATA_REF(uint16_t      , 0x01A5B5EC)

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Initialize and reset ALW module params for new stage **/
void     ALW_Create( void );

/** Make new entry **/
int32_t  ALW_Entry(  uint16_t category, task* tp, uint16_t kind                  );
int32_t  ALW_Entry2( uint16_t category, task* tp, uint16_t kind, void* pSaveInfo );

/** Get max entry by 'category' **/
int32_t  ALW_GetMaxEntry( uint16_t category ); /* Toolkit addition */

/** Get Task in 'catergory' by 'num' **/
task*    ALW_GetTask( int32_t category, uint16_t num );

/** Get Task attributes **/
int32_t  ALW_GetCategory( task* tp );
uint16_t ALW_GetKind(     task* tp ); /* Toolkit addition */

/** ALW attention **/
ALW_ENTRY_WORK* ALW_IsAttention(  task* tp             ); /* Returns current attention */
int32_t         ALW_AttentionOn(  task* tp1, task* tp2 ); /* Set attention */
int32_t         ALW_AttentionOff( task* tp             ); /* Attention off */

int32_t         ALW_IsSheAttentionOtherOne( task* pMyTask, task* pHerTask );

/** ALW communication **/
ALW_ENTRY_WORK* ALW_IsCommunication(  task* tp             ); /* Returns current communication */
int32_t         ALW_CommunicationOn(  task* tp1, task* tp2 ); /* Set communication */
int32_t         ALW_CommunicationOff( task* tp             ); /* Communication off */

ALW_ENTRY_WORK* ALW_IsCommunicationEx( task* tp, uint16_t category ); /* Returns current communication by 'category' */

int32_t         ALW_RecieveCommand( task* tp );

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define ALW_Create_p         FUNC_PTR(void, __cdecl, (void), 0x00530B80)

/** User-Function ptrs **/
#   define ALW_Entry2_p         ((void*)00530750)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_WORLD_H_*/
