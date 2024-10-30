/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>          /* core                                             */
#include <sa2b/writeop.h>       /* writejump                                        */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h>   /* ninja                                            */

/****** Game ************************************************************************/
#include <sa2b/sonic/task.h>    /* task                                             */
#include <sa2b/sonic/camera.h>  /* camera                                           */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_eventinfo.h>       /* event data                                       */

/****** Self ************************************************************************/
#include <rfm_event/ev_internal.h>          /* parent & siblings                    */

/************************/
/*  Game Structures     */
/************************/
/****** Camera Motion ***************************************************************/
typedef struct
{
    Float* pos;
    Float* vec;
    Angle* roll;
    Angle* ang;
}
CAM_MTN_OUTPUT;

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
#pragma optimize("", off)
static void
CalcCamMotion(CAM_MTN_OUTPUT* input, const NJS_CAMERA* pCam, const NJS_MOTION* motion, float frame)
{
    static const uintptr_t p = 0x007816B0;

    __asm
    {
        push [frame]
        push [motion]
        mov edi, [pCam]
        mov eax, [input]
        call p
        add esp, 8
    }
}
#pragma optimize("", on)

static void
EventCamMotion(const NJS_CAMERA* pInCam, const NJS_MOTION* motion, float frame)
{
    NJS_CAMERA cam;

    CAM_MTN_OUTPUT out;

    out.pos  = &cam.px;
    out.vec  = &cam.vx;
    out.roll = &cam.roll;
    out.ang  = &cam.ang;

    CalcCamMotion(&out, pInCam, motion, frame);

    cam.roll = -cam.roll;

    EventCamera = cam;

    njSetCamera(&cam);
}

__declspec(naked)
static void
___EventCamMotion(void)
{
    __asm
    {
        push [esp+8]
        push [esp+8]
        push eax
        call EventCamMotion
        add esp, 12
        retn
    }
}

/****** Init ************************************************************************/
void
EV_CameraInit(void)
{
    WriteJump(0x007817F0, ___EventCamMotion);
}
