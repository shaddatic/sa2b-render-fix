#include <samt/core.h>
#include <samt/writemem.h>
#include <samt/writeop.h>
#include <samt/funchook.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Source **/
#include <samt/sonic/display.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_draw.h>

#define BACKCOLOR_Z_VAL     (1.f/16'000'000.f)

static Uint32 _nj_back_color_0_;
static Uint32 _nj_back_color_1_;
static Uint32 _nj_back_color_2_;

#define FadeColor   DATA_REF(NJS_COLOR, 0x0171CDA0)

void __cdecl
njDrawBackColor2(void)
{
    if (FadeColor.argb.a == 0xFF)
        return;

    NJS_POLYGON_VTX vtx[4];

    vtx[0].z = BACKCOLOR_Z_VAL;
    vtx[1].z = BACKCOLOR_Z_VAL;
    vtx[2].z = BACKCOLOR_Z_VAL;
    vtx[3].z = BACKCOLOR_Z_VAL;

    vtx[0].col = _nj_back_color_1_;
    vtx[1].col = _nj_back_color_0_;
    vtx[2].col = _nj_back_color_2_;
    vtx[3].col = _nj_back_color_0_;

    const f32 scrn_ratio = (GetDisplayRatio() - 1.0f) * 320.0f;

    vtx[0].x = 0.0f - scrn_ratio;
    vtx[0].y = 0.0f;

    vtx[1].x = 0.0f - scrn_ratio;
    vtx[1].y = 480.0f;

    vtx[2].x = 640.0f + scrn_ratio;
    vtx[2].y = 0.0f;

    vtx[3].x = 640.0f + scrn_ratio;
    vtx[3].y = 480.0f;

    rjDrawPolygon(vtx, 4, false);
}

const void* const RendererClear_p = (void*)0x00867B20;

__declspec(naked)
static void
__RendererClearHook(void)
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
}

__declspec(naked)
static void
__njSetBackColor2(void)
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
__SetBackColor(void)
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

#define UnloadRELFile       FUNC_PTR(void, __cdecl, (void), 0x00454CC0)

static mt_hookinfo HookInfoUnloadRELFile[1];
static void
UnloadRELFileHook(void)
{
    FuncHookCall( HookInfoUnloadRELFile, UnloadRELFile() );

    njSetBackColor2(0, 0, 0);
}

void
RFG_NinjaBackColorInit(void)
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
    FuncHook(HookInfoUnloadRELFile, UnloadRELFile, UnloadRELFileHook);
}
