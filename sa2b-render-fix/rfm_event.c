#include <sa2b/core.h>
#include <sa2b/memory.h>
#include <sa2b/config.h>
#include <sa2b/memutil.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/src/task.h>
#include <sa2b/src/njctrl.h>
#include <sa2b/src/display.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>
#include <rf_eventinfo.h>

/** Self **/
#include <rfm_event.h>
#include <rfm_event/ev_internal.h>

const int EventAnimateTexture_p = 0x006021A0;
void
EventAnimateTexture(EventTexAnimSub1* a1, int a2, int a3)
{
    __asm
    {
        push[a3]
        mov edi, [a2]
        mov edx, [a1]
        call EventAnimateTexture_p
        add esp, 4
    }
}

const int EndiswapEventTexAnim1_p = 0x005FE8A0;
void
EndiswapEventTexAnim1(EventTexAnimSub1* a1)
{
    __asm
    {
        mov eax, [a1]
        call EndiswapEventTexAnim1_p
    }
}

const int EndiswapEventTexAnim0_p = 0x005FE670;
void
EndiswapEventTexAnim0(EventTexAnimSub0* a1)
{
    __asm
    {
        mov eax, [a1]
        call EndiswapEventTexAnim0_p
    }
}

static void
EndiswapEventTexAnim(EventTexAnim* p)
{
    SwapEndianness(&p->count);

    SwapEndianness(&p->somethingelse);

    if (p->somethingelse)
        *(int32_t*)&p->somethingelse -= 2132869184; // idky I'm doing this

    SwapEndianness(&p->something);

    if (p->something)
        *(int32_t*)&p->something -= 2132869184;

    for (EventTexAnimSub1* ptexanim = p->somethingelse; ptexanim->entries; ++ptexanim)
    {
        if (p->somethingelse)
            EndiswapEventTexAnim1(ptexanim);
    }

    for (int i = 0; i < p->count; ++i)
    {
        if (p->something)
            EndiswapEventTexAnim0(&p->something[i]);
    }
}

__declspec(naked)
static void
__EndiswapEventTexAnim()
{
    __asm
    {
        push ebx
        call EndiswapEventTexAnim
        pop ebx
        retn
    }
}

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

static void
Draw43Bars()
{
    const float disp_ratio = GetDisplayRatio();

    if (EventEnforce43 == EV_43MD_ALWAYS && disp_ratio > 1.0f)
    {
        NJS_COLOR   colors[4];
        NJS_POINT2  points[4];

        const float screenratio = (disp_ratio - 1.0f) * (320.0f) + 1.0f;

        colors[0].color = 0xFF000000;
        colors[1].color = 0xFF000000;
        colors[2].color = 0xFF000000;
        colors[3].color = 0xFF000000;

        points[0].x = 0.0f - screenratio;
        points[0].y = 0.0f;

        points[1].x = 0.0f - screenratio;
        points[1].y = 481.0f;

        points[2].x = 0.0f;
        points[2].y = 0.0f;

        points[3].x = 0.0f;
        points[3].y = 481.0f;

        NJS_POINT2COL poly = {
            .p = points,
            .col = colors,
            .tex = NULL,
            .num = 4
        };

        njDrawPolygon2D(&poly, 4, 1.0f, NJD_FILL);

        points[0].x = 640.0f;
        points[1].x = 640.0f;
        points[2].x = 640.0f + screenratio;
        points[3].x = 640.0f + screenratio;

        njDrawPolygon2D(&poly, 4, 1.0f, NJD_FILL);
    }
}

static void
EventDisplayerDelayHook(TASK* tp)
{
    if (DisableCutscene || CutsceneMode == 7 || CutsceneMode == 8 || CutsceneMode == 2 || 0.0f == EventFrame)
        return;

    njSetBackColor(0, 0, 0);
    EventCameraInit();

    njSetTexture(EventData.texlist);

    njCnkSetMotionCallback(NULL);

    for (int i = 1; i < NB_EVENT_LAYER; ++i)
    {
        EventDrawObjects(EVENT_BASE_SCENE, i, false);
        EventDrawObjects(EventScene   , i, false);
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
}

static void
EventDisplayerHook(TASK* tp)
{
    if (DisableCutscene || CutsceneMode == 7 || CutsceneMode == 8 || CutsceneMode == 2 || 0.0f == EventFrame)
        return;

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

    EventDrawObjects(EVENT_BASE_SCENE, 0, false);
    EventDrawObjects(EventScene   , 0, false);

    if (EventEquipmentEnable)
    {
        OnControl3D(NJD_CONTROL_3D_TRANS_MODIFIER | NJD_CONTROL_3D_SHADOW);
        EventDrawEquipment();
        OffControl3D(NJD_CONTROL_3D_TRANS_MODIFIER | NJD_CONTROL_3D_SHADOW);
    }
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
    if (RF_ConfigGetInt(CNF_EVENT_TEXANIM))
    {
        WriteCall(0x005FEFF7, __EndiswapEventTexAnim);
    }

    if (RF_ConfigGetInt(CNF_EVENT_DISPREPLCE))
    {
        WriteJump(0x005FABF0, EventDisplayerHook);
        WriteJump(0x005FAD20, EventDisplayerDelayHook);
    }

    EventEquipmentEnable = RF_ConfigGetInt(CNF_EVENT_DRAWEQUIP);

    if (RF_ConfigGetInt(CNF_EVENT_DRAWMOD))
    {
        EV_ModifierInit();
    }

    EventEnforce43 = (RF_ConfigGetInt(CNF_EVENT_43MD) == 1) ? EV_43MD_ALWAYS : EV_43MD_NEVER;

    //WriteJump(0x005FA4D0, EventEntrySetLight);
    //WriteData(0x005FA404, 4, uint8_t);
}
