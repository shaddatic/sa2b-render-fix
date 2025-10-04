#include <samt/core.h>
#include <samt/writemem.h>
#include <samt/funchook.h>
#include <samt/writeop.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Core Matrix **/
#include <samt/c_mtx/c_mtx.h>

/** Source **/
#include <samt/sonic/display.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_shader.h>

static void
FixNinjaDrawSomething(float* pri, NJS_MATRIX* m, NJS_VECTOR* ps, NJS_VECTOR* pd)
{
    C_MTXMultVec(m, ps, pd, false);

    if (*pri == 0.0f)
        return;

    const float adj_mul = (*pri / njScalor(pd));

    pd->x += (-pd->x * adj_mul);
    pd->y += (-pd->y * adj_mul);
    pd->z += (-pd->z * adj_mul);

    *pri = 0;
}

__declspec(naked)
static void
___C_MTXMultVec(void)
{
    __asm
    {
        push edx
        push ecx
        push eax

        mov eax, esp
        add eax, 128

        push eax

        call FixNinjaDrawSomething

        add esp, 4

        pop eax
        pop ecx
        pop edx

        retn
    }
}

static void
SendScreenRatioToShader(float resW, float resH)
{
    ___NOTE("This is far more general now than just 3D sprites, and should be moved at a later date.");

    const float adj_w = resW / 640.0f;
    const float adj_h = resH / 480.0f;

    const float res_w = DisplayResolutionX * adj_w;
    const float res_h = DisplayResolutionY * adj_h;

    // x and y components are the inverse viewport resolution (Render Fix register)
    const float inv_x = 1.f / res_w;
    const float inv_y = 1.f / res_h;

    // z is idk, and w is the aspect ratio difference from 4:3
    const float asp_w = (res_w) / resW;
    const float asp_h = (res_h * adj_h) / resH / asp_w;

    RF_ShaderSetConstant(SHC_VTX_DEVICEINFO, res_w, res_h, asp_w / adj_h, asp_h / adj_w);
    RF_ShaderSetConstant(SHC_VTX_SCRNINFO  , inv_x, inv_y, 0.f, 0.f);
}

#define GX_SetViewport      FUNC_PTR(void, __cdecl, (float, float, float, float, float, float), 0x00420210)

static mt_hookinfo GX_SetViewportHookInfo[1];
static void
GX_SetViewportHook(float X, float Y, float W, float H, float MinZ, float MaxZ)
{
    FuncHookCall( GX_SetViewportHookInfo, GX_SetViewport(X, Y, W, H, MinZ, MaxZ) );

    SendScreenRatioToShader(_nj_screen_.w, _nj_screen_.h);
}

static const int HintTextDisplayer_p = 0x006B5350;
static void
HintTextDisplayer(void* p)
{
    __asm
    {
        mov eax, [p]
        call HintTextDisplayer_p
    }
}

static mt_hookinfo HintTextDisplayerHookInfo[1];
static void
HintTextDisplayerHook(void* p)
{
    /** Temporarily tell the shader the un-fixed aspect ratio
        so the hint text displays correctly **/
    SendScreenRatioToShader(640.0f, 480.0f);

    FuncHookCall( HintTextDisplayerHookInfo, HintTextDisplayer(p) );

    /** Once drawn, update the shader to the correct aspect
        ratio again **/
    SendScreenRatioToShader(_nj_screen_.w, _nj_screen_.h);
}

__declspec(naked)
static void
__HintTextDisplayerHook(void)
{
    __asm
    {
        push eax
        call HintTextDisplayerHook
        pop eax
        retn
    }
}

void
RFG_3DSpriteInit(void)
{
    /** Fix floating lights **/
    WriteCall(0x004911F9, ___C_MTXMultVec);

    /** Fix njDrawSprite3D forcing sprites
        in front of the camera **/
    //WriteNOP(0x0077D835, 0x0077D83A); // Kill `if (z < -1.0f) z = -1.0f;`

    /** Fix Multi-screen desync and squish **/
    FuncHook(GX_SetViewportHookInfo, GX_SetViewport, GX_SetViewportHook);

    /** Fix lens flairs "un-squishing" themselves,
        which causes stretching with the above fix **/
    WriteNOP(0x006C79EE, 0x006C79F8);

    /** Fix hint text in 2P **/
    FuncHook(HintTextDisplayerHookInfo, HintTextDisplayer_p, __HintTextDisplayerHook);

    /** Fix ectoplasm effects "un-squishing" themselves,
        which causes stretching with the above fix **/
    WriteNOP(0x0075A911, 0x0075A924);
}
