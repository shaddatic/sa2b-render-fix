/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_gba_manager.h'
*
*   Contains structres and enums related to the Chao GBA.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_GBAMANAGER_H_
#define _SA2B_CHAO_GBAMANAGER_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/sonic/chao/al_chao_info.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task     TASK;

/************************/
/*  Enums               */
/************************/
typedef enum
{
    MD_GBAMAN_SLEEP = 0x0,
    MD_GBAMAN_ACTIVE = 0x1,
    MD_GBAMAN_ERROR = 0x2,
}
GBAManMode;

typedef enum
{
    MD_PORT_CHECK = 0x0,
    MD_PORT_LOAD = 0x1,
    MD_PORT_ODEKAKE = 0x2,
    MD_PORT_ODEKAKE_JOYBOOT = 0x3,
    MD_PORT_TORIDASU = 0x4,
    MD_PORT_FILE_SAVE = 0x5,
}
GBAPortMode;

typedef enum
{
    GBA_PORT_KIND_NONE = 0x0,
    GBA_PORT_KIND_NOTCHAO = 0x1,
    GBA_PORT_KIND_WAITRES = 0x2,
    GBA_PORT_KIND_CHAO = 0x3,
}
GBAPortKind;

typedef enum
{
    eGbaCheck_NotGba = 0x0,
    eGbaCheck_NotChao = 0x1,
    eGbaCheck_WaitRes = 0x2,
    eGbaCheck_Ready = 0x3,
    eGbaCheck__end = 0x4,
}
EGbaCheck;

typedef enum
{
    eGbaStatus_Busy = 0x0,
    eGbaStatus_Succ = 0x1,
    eGbaStatus_Fail = 0x2,
    eGbaStatus__end = 0x3,
}
EGbaStatus;

/************************/
/*  Structures          */
/************************/
typedef struct 
{
    EGbaCheck check;
    int32_t NotGbaTimer;
    uint16_t kind;
    GBAPortMode mode;
    int32_t IsROM;
    int32_t KinderFlag;
    int32_t ToridasuFlag[11];
    int32_t ExistFlag[11];
    CHAO_PARAM_GC* pToridasuChaoParam;
    int32_t ToridasuEggColor;
    int32_t ToridasuRing;
    uint8_t ToridasuFruit[8];
    CHAO_SAVE_INFO data;
    CHAO_SAVE_INFO dataEgg;
}
GBA_PORT_INFO;

typedef struct
{
    GBAManMode mode;
    int32_t debugDisp;
    int32_t IsBusy;
    TASK* tp;
    b32 IsOdekake;
    CHAO_PARAM_GC* pChaoParam;
    GBA_PORT_INFO PortInfo[4];
}
GBA_MANAGER_WORK;

#endif/*_SA2B_CHAO_GBAMANAGER_H_*/
