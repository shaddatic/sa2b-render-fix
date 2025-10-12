#include <samt/core.h>
#include <samt/config.h>
#include <samt/writeop.h>
#include <samt/writemem.h>
#include <samt/funchook.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Source **/
#include <samt/sonic/task.h>
#include <samt/sonic/display.h>
#include <samt/sonic/njctrl.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>
#include <rf_ninja.h>

/** Variables **/
static bool MenuFadeFixEnabled;

/****/
static const int SOCDisplaySprite_p = 0x0041DC80;
static void
SOCDisplaySprite(void* a1, float PosX, float PosY, float Width, float Height, float pri, float a7, float a8, float U, float V, uint32_t color)
{
    __asm
    {
        push[color]
        push[V]
        push[U]
        push[a8]
        push[a7]
        push[pri]
        push[Height]
        push[Width]
        push[PosY]
        push[PosX]
        mov eax, [a1]

        call SOCDisplaySprite_p

        add esp, 40
    }
}

typedef union
{
    uint32_t col;

    struct {
        uint8_t a, r, g, b;
    };
}
uARGB;

static void __cdecl
SOCDrawSpriteWithConstMat(void* a1, float PosX, float PosY, float Width, float Height, float pri, float a7, float a8, float U, float V, uARGB color)
{
    color.a = (uint8_t)((f32)color.a * _nj_constant_material_.a);
    color.r = (uint8_t)((f32)color.r * _nj_constant_material_.r);
    color.g = (uint8_t)((f32)color.g * _nj_constant_material_.g);
    color.b = (uint8_t)((f32)color.b * _nj_constant_material_.b);

    SOCDisplaySprite(a1, PosX, PosY, Width, Height, pri, a7, a8, U, V, color.col);
}

__declspec(naked)
static void
__SOCDrawSpriteWithConstMat(void)
{
    __asm
    {
        push[esp + 28h]
        push[esp + 28h]
        push[esp + 28h]
        push[esp + 28h]
        push[esp + 28h]
        push[esp + 28h]
        push[esp + 28h]
        push[esp + 28h]
        push[esp + 28h]
        push[esp + 28h]
        push eax

        call SOCDrawSpriteWithConstMat

        pop eax
        add esp, 40

        retn
    }
}

static void __cdecl
SOCDrawSpriteOnlyConstMat(void* a1, float PosX, float PosY, float Width, float Height, float pri, float a7, float a8, float U, float V, uARGB color)
{
    color.a = (uint8_t)(255.0f * _nj_constant_material_.a);
    color.r = (uint8_t)(255.0f * _nj_constant_material_.r);
    color.g = (uint8_t)(255.0f * _nj_constant_material_.g);
    color.b = (uint8_t)(255.0f * _nj_constant_material_.b);

    SOCDisplaySprite(a1, PosX, PosY, Width, Height, pri, a7, a8, U, V, color.col);
}

__declspec(naked)
static void
__SOCDrawSpriteOnlyConstMat(void)
{
    __asm
    {
        push[esp + 28h]
        push[esp + 28h]
        push[esp + 28h]
        push[esp + 28h]
        push[esp + 28h]
        push[esp + 28h]
        push[esp + 28h]
        push[esp + 28h]
        push[esp + 28h]
        push[esp + 28h]
        push eax

        call SOCDrawSpriteOnlyConstMat

        pop eax
        add esp, 40

        retn
    }
}

#define DisplayStageMap                 FUNC_PTR(void, __cdecl, (float, float), 0x00675DF0)

static mt_hookinfo HookInfoDisplayStageMap[1];
static void
DisplayStageMapHook(float scroll, float fade)
{
    _nj_constant_material_.a = 1.0f;
    _nj_constant_material_.r = fade;
    _nj_constant_material_.g = fade;
    _nj_constant_material_.b = fade;

    FuncHookCall( HookInfoDisplayStageMap, DisplayStageMap(scroll, fade)) ;

    ResetConstantMaterial();
}

#define flt_1A3D660                     DATA_REF(float, 0x1A3D660)

#define SetConstMatAndBackupConstAttr   FUNC_PTR(void, __cdecl, (float), 0x00433D00)
#define RestoreConstMatAndConstAttr     FUNC_PTR(void, __cdecl, (void) , 0x00433D40)

#define screenEffectDisp                FUNC_PTR(void, __cdecl, (task*), 0x00667E40)

static mt_hookinfo HookInfoScreenEffectDisp[1];
static void
screenEffectDispHook(task* tp)
{
    if (flt_1A3D660 != 0.0f)
        SetConstMatAndBackupConstAttr(flt_1A3D660);

    FuncHookCall( HookInfoScreenEffectDisp, screenEffectDisp(tp) );

    if (flt_1A3D660 != 0.0f)
        RestoreConstMatAndConstAttr();
}

static void
DrawMapTextBackdrop(void)
{
    NJS_COLOR   colors[4];
    NJS_POINT2  points[4];

    float screenratio = (GetDisplayRatio() - 1.0f) * (320.0f);

    colors[0].color = 0x600000FF;
    colors[1].color = 0x600000FF;
    colors[2].color = 0x600000FF;
    colors[3].color = 0x600000FF;

    points[0].x = 0.0f - screenratio;
    points[0].y = 26.0f;

    points[1].x = 0.0f - screenratio;
    points[1].y = 58.0f;

    points[2].x = 640.0f + screenratio;
    points[2].y = 26.0f;

    points[3].x = 640.0f + screenratio;
    points[3].y = 58.0f;

    NJS_POINT2COL poly = { points, colors, 0, 4 };

    rjDrawPolygon2D(&poly, 4, 0.f, NJD_FILL | NJD_TRANSPARENT);
}

static void
DrawMapPurpleFill(void)
{
    DATA_REF(int, 0x1AEE760) = 3; // part of function we overwrote

    NJS_COLOR   colors[4];
    NJS_POINT2  points[4];

    float screenratio = (GetDisplayRatio() - 1.0f) * 320.0f;

    NJS_COLOR col = { .color = 0xFF210C29 };

    if (MenuFadeFixEnabled)
    {
        col.argb.r = (Uint8)((f32)col.argb.r * _nj_constant_material_.r);
        col.argb.g = (Uint8)((f32)col.argb.g * _nj_constant_material_.g);
        col.argb.b = (Uint8)((f32)col.argb.b * _nj_constant_material_.b);
    }

    colors[0].color = col.color;
    colors[1].color = col.color;
    colors[2].color = col.color;
    colors[3].color = col.color;

    points[0].x = 0.0f - screenratio;
    points[0].y = 0.0f;

    points[1].x = 0.0f - screenratio;
    points[1].y = 480.0f;

    points[2].x = 640.0f + screenratio;
    points[2].y = 0.0f;

    points[3].x = 640.0f + screenratio;
    points[3].y = 480.0f;

    NJS_POINT2COL poly = { points, colors, 0, 4 };

    rjDrawPolygon2D(&poly, 4, -20000.0f, NJD_FILL);
}

void
RFM_MenusInit(void)
{
    if (RF_ConfigGetInt(CNF_MENUS_FADEFIX))
    {
        WriteNOP(0x0066FA08, 0x0066FA0E); // NOP erronious if check

        FuncHook(HookInfoDisplayStageMap , DisplayStageMap , DisplayStageMapHook);  // Set Const Mat
        FuncHook(HookInfoScreenEffectDisp, screenEffectDisp, screenEffectDispHook); // ^

        WriteCall(0x00675EA8, __SOCDrawSpriteWithConstMat); // Stage Map
        WriteCall(0x00675F58, __SOCDrawSpriteWithConstMat); // ^
        WriteCall(0x00676080, __SOCDrawSpriteWithConstMat); // ^
        WriteCall(0x0067619F, __SOCDrawSpriteWithConstMat); // ^

        WriteCall(0x0066FA8F, __SOCDrawSpriteWithConstMat); // Title
        WriteCall(0x0066FB28, __SOCDrawSpriteWithConstMat); // ^

        if (RF_ConfigGetInt(CNF_EXP_DCMENUFADE))
        {
            WriteCall(0x0066F9C7, __SOCDrawSpriteOnlyConstMat); // Title (DC)
        }

        WriteCall(0x0067C21F, __SOCDrawSpriteWithConstMat); // Story Something

        WriteCall(0x00668222, __SOCDrawSpriteWithConstMat); // BTL Custom Backgrounds

        MenuFadeFixEnabled = true;
    }

    if (RF_ConfigGetInt(CNF_MENUS_MAP_TEXTBAR))
    {
        WriteJump(0x00675D50, DrawMapTextBackdrop);
    }

    if (RF_ConfigGetInt(CNF_MENUS_MAP_STRETCH))
    {
        static const float posshift = -108.0f;

        WritePointer(0x006763BB, &posshift);            /* Move icons left  */
        WritePointer(0x00676046, 0x00907420);           /* stop stretch     */

        WriteNOP(0x00676094, 0x0067609E);               // fill blank space
        WriteCall(0x00676094, DrawMapPurpleFill);
    }
}
