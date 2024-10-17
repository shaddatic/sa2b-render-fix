#include <sa2b/core.h>
#include <sa2b/memory.h>
#include <sa2b/writemem.h>
#include <sa2b/writeop.h>

/** Util **/
#include <sa2b/util/endian.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/sonic/task.h>
#include <sa2b/sonic/njctrl.h>
#include <sa2b/sonic/display.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>
#include <rf_eventinfo.h>
#include <rf_renderstate.h>

/** Self **/
#include <rfm_event.h>
#include <rfm_event/ev_internal.h>

#define NB_EVENT_LAYER      (5)
#define EVENT_BASE_SCENE    (0)

typedef enum
{
    EV_43MD_NEVER,
    EV_43MD_VANILLA,
    EV_43MD_ALWAYS
}
RFE_EV_43MODE;

static bool          EventEquipmentEnable;
static RFE_EV_43MODE EventEnforce43;

static const void* const EventDrawReflectionLists_p = (void*)0x005F9520;
static void
EventDrawReflectionLists(int idxScene)
{
    __asm
    {
        mov ebx, [idxScene]

        call EventDrawReflectionLists_p
    }
}

/** It completely ignores 'poly' 1 and 3 if I don't do this.
    Genuinely, the optimizer is screwing with it **/
#pragma optimize("", off)
static void
DrawLeft43Bar(NJS_POLYGON_VTX* poly, f32 scrnshft)
{
    const f32 scrnpos = 0.f - scrnshft;

    poly[0].x = scrnpos;
    poly[1].x = scrnpos;
    poly[2].x = 0.f;
    poly[3].x = 0.f;

    njDrawPolygon(poly, 4, false);
}
#pragma optimize("", on)

#pragma optimize("", off)
static void
DrawRight43Bar(NJS_POLYGON_VTX* poly, f32 scrnshft)
{
    const f32 scrnpos = 640.f + scrnshft;

    poly[0].x = scrnpos;
    poly[1].x = scrnpos;
    poly[2].x = 640.f;
    poly[3].x = 640.f;

    njDrawPolygon(poly, 4, false);
}
#pragma optimize("", on)

static void
Draw43Bars(void)
{
    const f32 disp_ratio = GetDisplayRatio();

    if (EventEnforce43 == EV_43MD_ALWAYS && disp_ratio > 1.0f)
    {
        NJS_POLYGON_VTX poly[4];

        /** Init polyvtx **/
        {
            poly[0].y   = 0.0f;
            poly[0].z   = 1.0f;
            poly[0].col = 0xFF000000;
            poly[1].y   = 481.0f;
            poly[1].z   = 1.0f;
            poly[1].col = 0xFF000000;
            poly[2].y   = 0.0f;
            poly[2].z   = 1.0f;
            poly[2].col = 0xFF000000;
            poly[3].y   = 481.0f;
            poly[3].z   = 1.0f;
            poly[3].col = 0xFF000000;
        }

        const f32 scrnshft = (disp_ratio - 1.0f) * (320.0f) + 1.0f;

        DrawLeft43Bar( poly, scrnshft);
        DrawRight43Bar(poly, scrnshft);
    }
}

static void
EventDisplayerDelayHook(task* tp)
{
    if (DisableCutscene || CutsceneMode == 7 || CutsceneMode == 8 || CutsceneMode == 2 || 0.0f == EventFrame)
        return;

    const int old_rmode = _gj_render_mode_;

    _gj_render_mode_ = GJD_DRAW_TRANS;

    RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_TRANSPARENT);

    /** Draw **/
    njSetBackColor(0, 0, 0);
    EventCameraInit();

    njSetTexture(EventData.texlist);

    njCnkSetMotionCallback(NULL);

    for (int i = 0; i < NB_EVENT_LAYER; ++i)
    {
        EventDrawObjects(EVENT_BASE_SCENE, i, false);
        EventDrawObjects(EventScene      , i, false);
    }

    if (EventUseFlare)
        EventDrawFlare(&EventFlarePos);

    EventDrawSprites();

    if (EventOverrideInfo[10] == 1)
        EventDebug();
    if (EventOverrideInfo[10] == 2)
        EventDebugNull();

    EventDrawScreenQuad();

    Draw43Bars();

    /** End **/
    RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_END);

    _gj_render_mode_ = old_rmode;
}

static void
EventDisplayerHook(task* tp)
{
    if (DisableCutscene || CutsceneMode == 7 || CutsceneMode == 8 || CutsceneMode == 2 || 0.0f == EventFrame)
        return;

    const int old_rmode = _gj_render_mode_;

    _gj_render_mode_ = GJD_DRAW_SOLID;

    RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_OPAQUE);

    /** Draw **/
    njSetBackColor(0, 0, 0);
    EventCameraInit();

    njSetTexture(EventData.texlist);
    EventLightInit();
    EventDrawReflectionLists(0);
    EventDrawReflectionLists(EventScene);

    njSetTexture(EventData.texlist);

    for (int i = 0; i < 9; ++i)
        EventOverrideInfo[i] = 0;

    njCnkSetMotionCallback(NULL);

    for (int i = 0; i < NB_EVENT_LAYER; ++i)
    {
        EventDrawObjects(EVENT_BASE_SCENE, i, false);
        EventDrawObjects(EventScene      , i, false);
    }

    if (EventEquipmentEnable)
    {
        RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_ALL);

        OnControl3D(NJD_CONTROL_3D_TRANS_MODIFIER | NJD_CONTROL_3D_SHADOW);
        EventDrawEquipment();
        OffControl3D(NJD_CONTROL_3D_TRANS_MODIFIER | NJD_CONTROL_3D_SHADOW);
    }

    /** End **/
    RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_END);

    _gj_render_mode_ = old_rmode;
}

static void
EventEntrySetLight(Uint32 flag)
{
    gjSetLightSwitch(1, true);
    gjLoadLight(1);

    //gjSetAmbient(0.2f, 0.2f, 0.2f);

    if (flag & 0x4 && false)
    {
        gjSetLightSwitch(2, true);
        gjLoadLight(2);
    }
    else
        gjSetLightSwitch(2, false);

    if (flag & 0x8)
    {
        OutputString("flag 8");
    }

    if (flag & 0x10)
    {
        gjSetLightSwitch(3, true);
        gjLoadLight(3);
        gjSetLightSwitch(4, true);
        gjLoadLight(4);
    }
    else
    {
        gjSetLightSwitch(3, false);
        gjSetLightSwitch(4, false);
    }

    if (flag & 0x20)
    {
        gjSetLightSwitch(4, true);
        gjLoadLight(4);
    }
    else
        gjSetLightSwitch(4, false);
}

void
RFM_EventInit(void)
{
    EV_ByteSwapInit();

    if (RF_ConfigGetInt(CNF_EVENT_DISPREPLCE))
    {
        WriteJump(0x005FABF0, EventDisplayerHook);
        WriteJump(0x005FAD20, EventDisplayerDelayHook);

        EventEquipmentEnable = RF_ConfigGetInt(CNF_EVENT_DRAWEQUIP);
        EventEnforce43       = RF_ConfigGetInt(CNF_EVENT_43MD);
    }

    if (RF_ConfigGetInt(CNF_EVENT_DRAWMOD))
    {
        EV_ModifierInit();
    }
}
