/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_chaosdrive.h'
*
*   ~~~ Under Construction ~~~
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_CHAOSDRIVE_H_
#define _SA2B_CHAO_CHAOSDRIVE_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

#include <sa2b/sonic/task/taskwk.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task             task;
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

typedef struct // taskwk
{
    TASKWK;

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
task*   ALO_ChaosDriveCreate( uint8_t kind, NJS_POINT3* pPos, NJS_VECTOR* pVelo, ITEM_SAVE_INFO* pSaveInfo );

/** Task functions **/
void    ALO_ChaosDriveExecutor(         task* tp );
void    ALO_ChaosDriveDisplayer(        task* tp );
void    ALO_ChaosDriveDestructor(       task* tp );
void    ALO_ChaosDriveDisplayerDelayed( task* tp );

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/** User-Function ptrs **/
#   define ALO_ChaosDriveCreate_p               FUNC_PTR(task*, __cdecl, (uint8_t, NJS_POINT3*, NJS_VECTOR*, ITEM_SAVE_INFO*), 0x00545600)
#   define ALO_ChaosDriveExecutor_p             FUNC_PTR(void , __cdecl, (task*)                                             , 0x005450C0)
#   define ALO_ChaosDriveDisplayer_p            FUNC_PTR(void , __cdecl, (task*)                                             , 0x00545150)
#   define ALO_ChaosDriveDestructor_p           FUNC_PTR(void , __cdecl, (task*)                                             , 0x005455B0)
#   define ALO_ChaosDriveDisplayerDelayed_p     FUNC_PTR(void , __cdecl, (task*)                                             , 0x00545430)

#endif /* SAMT_INCL_FUNCPTRS */

#endif /* _SA2B_CHAO_CHAOSDRIVE_H_ */
