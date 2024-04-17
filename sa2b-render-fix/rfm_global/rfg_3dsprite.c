#include <sa2b/core.h>
#include <sa2b/memutil.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Core Matrix **/
#include <sa2b/c_mtx/c_mtx.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_funchook.h>

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

void RFG3DS_SendResToShader(void);

#define GX_SetViewport      FuncPtr(void, __cdecl, (float, float, float, float, float, float), 0x00420210)

static hook_info* GX_SetViewportHookInfo;

static void
GX_SetViewportHook(float X, float Y, float W, float H, float MinZ, float MaxZ)
{
    FuncHookCall( GX_SetViewportHookInfo, GX_SetViewport(X, Y, W, H, MinZ, MaxZ) );

    RFG3DS_SendResToShader();
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
    RF_FuncHook(GX_SetViewport);
}
