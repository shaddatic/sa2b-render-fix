/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/task/forcewk.h'
*
*   Description:
*       Definitions and macros for the FORCEWK struct type.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
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
typedef struct task         task;
typedef struct taskwk       taskwk;
typedef struct forcewk      forcewk;

/************************/
/*  Structures          */
/************************/
#define TO_FORCEWK(_p)      ((forcewk*)(_p))

typedef struct forcewk
{
    void(__cdecl* call_back)(task*, taskwk*, forcewk*);
    Angle3        ang_spd;
    NJS_POINT3    pos_spd;
}
forcewk;

#endif/*_SA2B_TASK_FORCEWK_H_*/
