/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_chaosdrive.h'
*
*   ~~~ Under Construction ~~~
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_CHAOSDRIVE_H_
#define _SA2B_CHAO_CHAOSDRIVE_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task             TASK;
typedef struct colliwk          COLLIWK;
typedef struct item_save_info   ITEM_SAVE_INFO;

/************************/
/*  Enums               */
/************************/
typedef enum /* Toolkit addition */
{
    AL_DRIVE_YELLOW = 0x15,
    AL_DRIVE_GREEN = 0x16,
    AL_DRIVE_RED = 0x17,
    AL_DRIVE_PURPLE = 0x18
}
eAL_DRIVES;

/************************/
/*  Structures          */
/************************/
#define GET_AL_CHAOSDRIVE_WORK(_tp) ((AL_CHAOSDRIVE_WORK*)(_tp)->twp)

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

    char kind;
    char gap_31[3];
    int field_34;
    char gap_38[4];
    int field_3C;
    int field_40;
    char gap_44[4];
    int field_48;
    int field_4C;
    int field_50;
}
AL_CHAOSDRIVE_WORK;

/************************/
/*  Functions           */
/************************/
EXTERN_START
TASK*   ALO_ChaosDriveCreate(uint8_t kind, NJS_POINT3* pPos, NJS_VECTOR* pVelo, ITEM_SAVE_INFO* pSaveInfo);

/** Task functions **/
void    ALO_ChaosDriveExecutor(TASK* tp);
void    ALO_ChaosDriveDisplayer(TASK* tp);
void    ALO_ChaosDriveDestructor(TASK* tp);
void    ALO_ChaosDriveDisplayerDelayed(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** User-Function ptrs **/
#define ALO_ChaosDriveCreate_p              FuncPtr(TASK*, __cdecl, (uint8_t kind, NJS_POINT3* pPos, NJS_VECTOR* idkvector, ITEM_SAVE_INFO* a4), 0x00545600)
#define ALO_ChaosDriveExecutor_p            FuncPtr(void, __cdecl, (TASK*), 0x005450C0)
#define ALO_ChaosDriveDisplayer_p           FuncPtr(void, __cdecl, (TASK*), 0x00545150)
#define ALO_ChaosDriveDestructor_p          FuncPtr(void, __cdecl, (TASK*), 0x005455B0)
#define ALO_ChaosDriveDisplayerDelayed_p    FuncPtr(void, __cdecl, (TASK*), 0x00545430)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_CHAOSDRIVE_H_ */
