/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/task/motionwk.h'
*
*   Description:
*       Definitions and macros for the MOTIONWK struct type.
*/
#ifndef _SA2B_TASK_MOTIONWK_H_
#define _SA2B_TASK_MOTIONWK_H_

/************************/
/*  Includes            */
/************************/
/** Ninja **/
#include <samt/ninja/njcommon.h>

/************************/
/*  Structures          */
/************************/
#define TO_MOTIONWK(_p)     ((motionwk*)(_p))

#define MOTIONWK            \
struct {                    \
    union {                 \
        int8_t    b[4];     \
        int16_t   w[2];     \
        int32_t   l;        \
        f32       f;        \
        void* ptr;          \
    } work;                 \
    NJS_POINT3 spd;         \
    NJS_POINT3 acc;         \
    Angle3     ang_aim;     \
    Angle3     ang_spd;     \
    f32        force;       \
    f32        accel;       \
    f32        frict;       \
}

typedef struct motionwk
{
    MOTIONWK;
}
motionwk;

#endif/*_SA2B_TASK_MOTIONWK_H_*/
