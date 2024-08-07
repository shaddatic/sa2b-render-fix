/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/task/taskwk.h'
*
*   Description:
*       Definitions and macros for the TASKWK struct type.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_TASK_TASKWK_H_
#define _SA2B_TASK_TASKWK_H_

/************************/
/*  Includes            */
/************************/
/** Ninja **/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct colliwk  COLLIWK;

/************************/
/*  Structures          */
/************************/
#define TO_TASKWK(_p)       ((TASKWK*)(_p))

#define TASKWK()        \
struct {                \
    int8_t mode;        \
    int8_t smode;       \
    int8_t id;          \
    int8_t btimer;      \
    int16_t flag;       \
    int16_t wtimer;     \
    Angle3 ang;         \
    NJS_POINT3 pos;     \
    NJS_VECTOR scl;     \
    COLLIWK* cwp;       \
}

typedef struct taskwk
{
    TASKWK();
}
TASKWK;

#endif/*_SA2B_TASK_TASKWK_H_*/
