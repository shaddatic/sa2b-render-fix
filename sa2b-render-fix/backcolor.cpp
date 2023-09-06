#include <sa2b/core.h>
#include <sa2b/memtools.h>

#include <sa2b/ninja/ninja.h>

#include <sa2b/src/display.h>

Uint32 _nj_back_color_0_;
Uint32 _nj_back_color_1_;
Uint32 _nj_back_color_2_;

DataRef(NJS_COLOR, FadeColor, 0x0171CDA0);

void
njDrawBackColor2()
{
    if (FadeColor.argb.a == 0xFF)
        return;

    NJS_COLOR   colors[4];
    NJS_POINT2  points[4];

    float screenratio = (GetDisplayRatio() - 1.0f) * 320.0f;

    colors[0].color = _nj_back_color_1_;
    colors[1].color = _nj_back_color_0_;
    colors[2].color = _nj_back_color_2_;
    colors[3].color = _nj_back_color_0_;

    points[0].x = 0.0f - screenratio;
    points[0].y = 0.0f;

    points[1].x = 0.0f - screenratio;
    points[1].y = 480.0f;

    points[2].x = 640.0f + screenratio;
    points[2].y = 0.0f;

    points[3].x = 640.0f + screenratio;
    points[3].y = 480.0f;

    NJS_POINT2COL poly = { points, colors, 0, 4 };

    njDrawPolygon2D(&poly, 4, 16000000.0f, NJD_FILL);
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
__njSetBackColor2()
{
    __asm
    {
        push [esp+8]
        push [esp+8]
        push eax
        call njSetBackColor2
        pop eax
        add esp, 8
        retn
    }
}

void __cdecl
SetBackColor(uint32 b, uint32 g, uint32 r)
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
        retn
    }
}

#pragma warning( pop )

void
FixNinjaBackColor()
{
    WriteNoOP(0x00433F58, 0x00433F74);
    WriteCall(0x00433F58, njDrawBackColor2);

    WriteJump(0x00426540, __njSetBackColor2);
    WriteJump(0x00426620, __SetBackColor);

    //WriteNoOP(0x00426540, 0x00426547); // Set color to 0
    //WriteNoOP(0x0042654A, 0x00426550);
    //WriteNoOP(0x0046FF50, 0x0046FF8F);
    //WriteNoOP(0x0046FF97, 0x0046FF9D);
    //WriteNoOP(0x0046FD87, 0x0046FDC2);

    KillCall(0x0043AE09); // Pause
    KillCall(0x0043B2C4); // Unpause
}