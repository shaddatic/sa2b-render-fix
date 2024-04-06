#include <sa2b/core.h>
#include <sa2b/memutil.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Core Matrix **/
#include <sa2b/c_mtx/c_mtx.h>

/** Render Fix **/
#include <rf_core.h>

static void
FlipEnv2(GJS_MATRIX* mat0, GJS_MATRIX* mat1, GJS_MATRIX* mat2)
{
    (*mat0)[0] = 0.5f;

    C_MTXConcat(mat0, mat1, mat2);
}

__declspec(naked)
static void
__FlipEnv2()
{
    __asm
    {
        push ecx
        push edx
        push eax
        call FlipEnv2
        pop eax
        pop edx
        pop ecx
        retn
    }
}

static const int njCnkDrawModel_p = 0x0042E660;
__declspec(naked)
static void
__FixCnkDrawModel(void)
{
    __asm
    {
        push eax
        call njCnkDrawModel_p
        pop eax
        retn
    }
}

/** Drawing Ginja models as shadows for some reason breaks env maps.
    So, we just replace said draw functions with Cnk equivelants **/
EXTERN NJS_CNK_MODEL model_bunchin_shadow[];

static void
BunchinShadowDraw(void) // The crushers
{
    njCnkDrawModel(model_bunchin_shadow);
}

EXTERN NJS_CNK_MODEL model_msger_shadow[];

static void
OmochaoShadowDraw(void)
{
    njCnkDrawModel(model_msger_shadow);
}

/** Init **/
void
RFG_EnvMapFlip(void)
{
    WriteCall(0x0042D4B0, __FlipEnv2); // Chunk
    WriteCall(0x0042B6A4, __FlipEnv2); // Ginja
    WriteCall(0x0056DEEB, __FlipEnv2); // chDraw
}

void
RFG_EnvMapFix(void)
{
    WriteJump(0x0042E6C0, __FixCnkDrawModel);

    WriteCall(0x006DCD5D, BunchinShadowDraw);
    WriteCall(0x006C0E6F, OmochaoShadowDraw);
}
