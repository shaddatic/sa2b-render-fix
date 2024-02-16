/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/task/motionwk.h'
*
*   Description:
*       Definitions and macros for the MOTIONWK struct type.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_TASK_MOTIONWK_H_
#define _SA2B_TASK_MOTIONWK_H_

/************************/
/*  Includes            */
/************************/
/** Ninja **/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Structures          */
/************************/
#define TO_MOTIONWK(_p)     ((MOTIONWK*)(_p))

#define MOTIONWK()          \
struct {                    \
    union {                 \
        int8_t    b[4];     \
        int16_t   w[2];     \
        int32_t   l;        \
        float32_t f;        \
        void* ptr;          \
    } work;                 \
    NJS_POINT3 spd;         \
    NJS_POINT3 acc;         \
    Angle3     ang_aim;     \
    Angle3     ang_spd;     \
    float32_t  force;       \
    float32_t  accel;       \
    float32_t  frict;       \
}

typedef struct motionwk
{
    MOTIONWK();
}
MOTIONWK;

#endif/*_SA2B_TASK_MOTIONWK_H_*/
