/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/task/forcewk.h'
*
*   Description:
*       Definitions and macros for the FORCEWK struct type.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_TASK_FORCEWK_H_
#define _SA2B_TASK_FORCEWK_H_

/************************/
/*  Includes            */
/************************/
/** Ninja **/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task         TASK;
typedef struct taskwk       TASKWK;
typedef struct forcewk      FORCEWK;

/************************/
/*  Structures          */
/************************/
#define TO_FORCEWK(_p)      ((FORCEWK*)(_p))

typedef struct forcewk
{
    void(__cdecl* call_back)(TASK*, TASKWK*, FORCEWK*);
    Angle3        ang_spd;
    NJS_POINT3    pos_spd;
}
FORCEWK;

#endif/*_SA2B_TASK_FORCEWK_H_*/
