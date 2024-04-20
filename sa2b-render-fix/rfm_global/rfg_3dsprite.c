#include <sa2b/core.h>
#include <sa2b/memutil.h>
#include <sa2b/funchook.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Core Matrix **/
#include <sa2b/c_mtx/c_mtx.h>

/** Source **/
#include <sa2b/src/display.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_magic.h>

static void
FixNinjaDrawSomething(float* pri, GJS_MATRIX* m, NJS_VECTOR* ps, NJS_VECTOR* pd)
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

#define GX_SetViewport      FuncPtr(void, __cdecl, (float, float, float, float, float, float), 0x00420210)

static hook_info* GX_SetViewportHookInfo;
static void
GX_SetViewportHook(float X, float Y, float W, float H, float MinZ, float MaxZ)
{
    FuncHookCall( GX_SetViewportHookInfo, GX_SetViewport(X, Y, W, H, MinZ, MaxZ) );

    const float adj_w = _nj_screen_.w / 640.0f;
    const float adj_h = _nj_screen_.h / 480.0f;

    const float res_w = DisplayResolutionX * adj_w;
    const float res_h = DisplayResolutionY * adj_h;

    const float asp_w = res_w / _nj_screen_.w;
    const float asp_h = res_h / _nj_screen_.h / asp_w;

    RF_MagicSetShaderConstantVec4(MAGIC_SHADER_VERTEX, 104, res_w, res_h, asp_w / adj_h, asp_h / adj_w);
}

void
RFG_3DSpriteInit(void)
{
    /** Fix floating lights **/
    WriteCall(0x004911F9, ___C_MTXMultVec);

    /** Fix njDrawSprite3D forcing sprites
        in front of the camera **/
    ___NOTE("This patch is hacky, add a return or something");
    WriteNoOP(0x0077D83E, 0x0077D840);

    /** Fix Multi-screen desync and squish **/
    GX_SetViewportHookInfo = FuncHook(GX_SetViewport, GX_SetViewportHook);

    /** Fix lens flairs "un-squishing" themselves,
        which causes stretching with the above fix **/
    WriteNoOP(0x006C79EE, 0x006C79F8);
}
