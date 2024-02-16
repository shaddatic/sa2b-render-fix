#include <sa2b/core.h>
#include <sa2b/memutil.h>
#include <sa2b/funchook.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/src/display.h>

/** Render Fix **/
#include <rf_core.h>

static Uint32 _nj_back_color_0_;
static Uint32 _nj_back_color_1_;
static Uint32 _nj_back_color_2_;

#define FadeColor   DataRef(NJS_COLOR, 0x0171CDA0)

void __cdecl
njDrawBackColor2()
{
    if (FadeColor.argb.a == 0xFF)
        return;

    NJS_COLOR   colors[4];
    NJS_POINT2  points[4];

    float screenratio = (GetDisplayRatio() - 1.0f) * 320.0f;

    points[0].x = 0.0f - screenratio;
    points[0].y = 0.0f;

    points[1].x = 0.0f - screenratio;
    points[1].y = 480.0f;

    points[2].x = 640.0f + screenratio;
    points[2].y = 0.0f;

    points[3].x = 640.0f + screenratio;
    points[3].y = 480.0f;

    colors[0].color = _nj_back_color_1_;
    colors[1].color = _nj_back_color_0_;
    colors[2].color = _nj_back_color_2_;
    colors[3].color = _nj_back_color_0_;

    NJS_POINT2COL poly = { points, colors, 0, 4 };

    njDrawPolygon2D(&poly, 4, 16000000.0f, NJD_FILL);
}

const void* const RendererClear_p = (void*)0x00867B20;

__declspec(naked)
static void
__RendererClearHook()
{
    /** 1. Re-push stack objects for OG func call
        2. Call original function, which cleans the new stack
        3. Call DrawBackColor to draw on the cleared buffer
        4. return while pushing adding 0x10 to the stack ptr **/

    __asm
    {
        push[esp + 10h]
        push[esp + 10h]
        push[esp + 10h]
        push[esp + 10h]

        call RendererClear_p

        call njDrawBackColor2

        retn 10h
    }
}

void __cdecl
njSetBackColor2(Uint32 col1, Uint32 col2, Uint32 col3)
{
    _nj_back_color_0_ = col1;
    _nj_back_color_1_ = col2;
    _nj_back_color_2_ = col3;

    OutputDebugFormat("Backcolor: %X, %X, %X", col1, col2, col3);
}

__declspec(naked)
static void
__njSetBackColor2()
{
    __asm
    {
        push[esp + 8]
        push[esp + 8]
        push eax
        call njSetBackColor2
        pop eax
        add esp, 8
        retn
    }
}

void __cdecl
SetBackColor(uint32_t b, uint32_t g, uint32_t r)
{
    NJS_COLOR col;

    col.argb.r = r;
    col.argb.g = g;
    col.argb.b = b;

    njSetBackColor2(col.color, col.color, col.color);
}

#pragma warning( push )
#pragma warning( disable : 4409 )
__declspec(naked)
static void
__SetBackColor()
{
    __asm
    {
        push eax
        push ecx
        push edx
        push esi

        movzx esi, dl
        push esi
        movzx esi, al
        push esi
        movzx esi, cl
        push esi

        call SetBackColor

        add esp, 12

        pop esi
        pop edx
        pop ecx
        pop eax
        retn
    }
}
#pragma warning( pop )

#define UnloadRELFile       FuncPtr(void, __cdecl, (), 0x00454CC0)

static hook_info* HookInfoUnloadRELFile;
static void
UnloadRELFileHook()
{
    FuncHookCall( HookInfoUnloadRELFile, UnloadRELFile() );

    njSetBackColor2(0, 0, 0);
}

void
RFG_NinjaBackColorInit()
{
    WritePointer(0x008B6FDC, __RendererClearHook);

    WriteJump(0x00426540, __njSetBackColor2);
    WriteJump(0x00426620, __SetBackColor);

    /** SOC SetBackColor calls **/
    KillCall(0x0043AA73); // King Boom Boo
    KillCall(0x0043AC81); // ^
    KillCall(0x0043BACF); // Wild Canyon
    KillCall(0x0043B4A7); // ^
    KillCall(0x0043AE09); // Pause
    KillCall(0x0043B2C4); // Unpause
    KillCall(0x0043B146); // Unk Menu

    /** Always reset back color on level exit **/
    HookInfoUnloadRELFile = FuncHook(UnloadRELFile, UnloadRELFileHook);
}
