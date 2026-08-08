/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/chao/al_gba_manager.h'
*
*   Description:
*     Chao World GBA Manager.
*/
#ifndef H_SA2B_CHAO_GBAMANAGER
#define H_SA2B_CHAO_GBAMANAGER

EXTERN_START

/********************************/
/*  Includes                    */
/********************************/
#include <samt/sonic/chao/al_chao_info.h>
#include <samt/sonic/chao/al_world.h>

/********************************/
/*  Abstract Types              */
/********************************/
typedef struct task                 task;

/********************************/
/*  Constants                   */
/********************************/
typedef enum
{
    MD_GBAMAN_SLEEP,
    MD_GBAMAN_ACTIVE,
    MD_GBAMAN_ERROR,
}
GBAManMode;

typedef enum
{
    MD_PORT_CHECK,
    MD_PORT_LOAD,
    MD_PORT_ODEKAKE,
    MD_PORT_ODEKAKE_JOYBOOT,
    MD_PORT_TORIDASU,
    MD_PORT_FILE_SAVE,
}
GBAPortMode;

typedef enum
{
    GBA_PORT_KIND_NONE,
    GBA_PORT_KIND_NOTCHAO,
    GBA_PORT_KIND_WAITRES,
    GBA_PORT_KIND_CHAO,
}
GBAPortKind;

typedef enum
{
    eGbaCheck_NotGba,
    eGbaCheck_NotChao,
    eGbaCheck_WaitRes,
    eGbaCheck_Ready,
    eGbaCheck__end,
}
EGbaCheck;

typedef enum
{
    eGbaStatus_Busy,
    eGbaStatus_Succ,
    eGbaStatus_Fail,
    eGbaStatus__end,
}
EGbaStatus;

/********************************/
/*  Structures                  */
/********************************/
typedef struct 
{
    EGbaCheck       check;
    i32             NotGbaTimer;
    u16             kind;
    GBAPortMode     mode;
    i32             IsROM;
    i32             KinderFlag;
    i32             ToridasuFlag[NB_CATEGORY];
    i32             ExistFlag[NB_CATEGORY];
    CHAO_PARAM_GC* pToridasuChaoParam;
    i32             ToridasuEggColor;
    i32             ToridasuRing;
    u8              ToridasuFruit[8];
    CHAO_SAVE_INFO  data;
    CHAO_SAVE_INFO  dataEgg;
}
GBA_PORT_INFO;

typedef struct 
{
    GBAManMode      mode;
    i32             debugDisp;
    i32             IsBusy;
    task*           tp;
    i32             IsOdekake;
    CHAO_PARAM_GC*  pChaoParam;
    GBA_PORT_INFO   PortInfo[4];
}
GBA_MANAGER_WORK;

#define pGBAManager         DATA_REF(GBA_MANAGER_WORK*, 0x01A5CB54)

void    AL_GBAManagerSetOdekakeChaoParam( CHAO_PARAM_GC *pParam );

b32     AL_GBAManagerIsOdekake( void );

b32     AL_GBAManagerIsToridasu( void );

EXTERN_END

#endif/*H_SA2B_CHAO_GBAMANAGER*/
