#include <sa2b/core.h>
#include <sa2b/writemem.h>
#include <sa2b/funchook.h>
#include <sa2b/writeop.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Core Matrix **/
#include <sa2b/c_mtx/c_mtx.h>

/** Source **/
#include <sa2b/sonic/display.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_magic.h>

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
    const float adj_w = resW / 640.0f;
    const float adj_h = resH / 480.0f;

    const float res_w = DisplayResolutionX * adj_w;
    const float res_h = DisplayResolutionY * adj_h;

    const float asp_w = res_w / resW;
    const float asp_h = res_h / resH / asp_w;

    RF_MagicSetShaderConstantVec4(MAGIC_SHADER_VERTEX, 104, res_w, res_h, asp_w / adj_h, asp_h / adj_w);
}

#define GX_SetViewport      FUNC_PTR(void, __cdecl, (float, float, float, float, float, float), 0x00420210)

static hook_info* GX_SetViewportHookInfo;
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

static hook_info* HintTextDisplayerHookInfo;
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
    WriteNOP(0x0077D835, 0x0077D83A); // Kill `if (z < -1.0f) z = -1.0f;`

    /** Fix Multi-screen desync and squish **/
    GX_SetViewportHookInfo = FuncHook(GX_SetViewport, GX_SetViewportHook);

    /** Fix lens flairs "un-squishing" themselves,
        which causes stretching with the above fix **/
    WriteNOP(0x006C79EE, 0x006C79F8);

    /** Fix hint text in 2P **/
    HintTextDisplayerHookInfo = FuncHook(HintTextDisplayer_p, __HintTextDisplayerHook);

    /** Fix ectoplasm effects "un-squishing" themselves,
        which causes stretching with the above fix **/
    WriteNOP(0x0075A911, 0x0075A924);
}
