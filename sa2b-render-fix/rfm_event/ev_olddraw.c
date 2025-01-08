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
#include <sa2b/sonic/njctrl.h>  /* ninja control                                    */
#include <sa2b/sonic/display.h> /* screen display                                   */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_eventinfo.h>       /* event data                                       */
#include <rf_renderstate.h>     /* render state                                     */

/****** Self ************************************************************************/
#include <rfm_event/ev_internal.h>          /* parent & siblings                    */
#include <rfm_event/ev_draw/evd_internal.h> /* children                             */

/************************/
/*  Constants           */
/************************/
/****** Event Layers ****************************************************************/
#define NB_EVENT_LAYER      (5)

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
EventDrawReflectionLists(int idxScene)
{
    static const void* const fptr = (void*)0x005F9520;

    __asm
    {
        mov ebx, [idxScene]
        call fptr
    }
}

static void
StartOldEventDraw(void)
{
    SaveControl3D();
    SaveConstantAttr();

    OffControl3D(NJD_CONTROL_3D_CONSTANT_TEXTURE_MATERIAL);

    OnControl3D(NJD_CONTROL_3D_CNK_CONSTANT_ATTR);
    OnConstantAttr(~NJD_FST_MASK, NJD_FST_DB);
}

static void
EndOldEventDraw(void)
{
    LoadConstantAttr();
    LoadControl3D();
}

static void
EventDisplayerDelayHook(task* tp)
{
    if (DisableCutscene || CutsceneMode == 7 || CutsceneMode == 8 || CutsceneMode == 2 || 0.0f == EventFrame)
        return;

    StartOldEventDraw();

    const int old_rmode = _gj_render_mode_;

    _gj_render_mode_ = GJD_DRAW_TRANS;

    RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_TRANSPARENT);

    /** Draw **/
    njSetBackColor(0, 0, 0);
    EventCameraInit();

    njSetTexture(EventData.pTexlist);

    njCnkSetMotionCallback(NULL);

    for (int i = 0; i < NB_EVENT_LAYER; ++i)
    {
        EventDrawObjects(EVENT_BASE_SCENE, i, false);
        EventDrawObjects(EventScene      , i, false);
    }

    if (EventUseFlare)
        EventDrawFlare(&EventFlarePos);

    EventDrawSprites();

    if (EventDebugInfo == 1)
        EventDebug();
    if (EventDebugInfo == 2)
        EventDebugNull();

    EventDrawScreenQuad();

    Draw43Bars();

    /** End **/
    RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_END);

    _gj_render_mode_ = old_rmode;

    EndOldEventDraw();
}

static void
EventResetEquipmentFlags(void)
{
    for (int i = 0; i < ARYLEN(EventEquipmentFlags); ++i)
    {
        EventEquipmentFlags[i] = 0;
    }
}

static void
EventDisplayerHook(task* tp)
{
    if (DisableCutscene || CutsceneMode == 7 || CutsceneMode == 8 || CutsceneMode == 2 || 0.0f == EventFrame)
        return;

    StartOldEventDraw();

    const int old_rmode = _gj_render_mode_;

    _gj_render_mode_ = GJD_DRAW_SOLID;

    RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_OPAQUE);

    /** Draw **/
    njSetBackColor(0, 0, 0);
    EventCameraInit();

    njSetTexture(EventData.pTexlist);
    EventLightInit();
    EventDrawReflectionLists(0);
    EventDrawReflectionLists(EventScene);

    njSetTexture(EventData.pTexlist);

    EventResetEquipmentFlags();

    njCnkSetMotionCallback(NULL);

    for (int i = 0; i < NB_EVENT_LAYER; ++i)
    {
        EventDrawObjects(EVENT_BASE_SCENE, i, false);
        EventDrawObjects(EventScene      , i, false);
    }

    if ( EV_GetEquipmentMode() )
    {
        RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_ALL);

        OnControl3D(NJD_CONTROL_3D_TRANS_MODIFIER | NJD_CONTROL_3D_SHADOW);
        EventDrawEquipment();
        OffControl3D(NJD_CONTROL_3D_TRANS_MODIFIER | NJD_CONTROL_3D_SHADOW);
    }

    /** End **/
    RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_END);

    _gj_render_mode_ = old_rmode;

    EndOldEventDraw();
}

/****** Init ************************************************************************/
void
EV_OldDrawInit(void)
{
    WriteJump(0x005FABF0, EventDisplayerHook);
    WriteJump(0x005FAD20, EventDisplayerDelayHook);
}
