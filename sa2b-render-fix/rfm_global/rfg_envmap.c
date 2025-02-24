#include <samt/core.h>
#include <samt/writemem.h>
#include <samt/writeop.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Core Matrix **/
#include <samt/c_mtx/c_mtx.h>

/** Render Fix **/
#include <rf_core.h>

static void
FlipEnv2(NJS_MATRIX* mat0, NJS_MATRIX* mat1, NJS_MATRIX* mat2)
{
    mat0->m[0][0] = 0.5f;

    C_MTXConcat(mat0, mat1, mat2);
}

__declspec(naked)
static void
__FlipEnv2(void)
{
    __asm
    {
        push edx
        push ecx
        push eax
        call FlipEnv2
        pop eax
        pop ecx
        pop edx
        retn
    }
}

/** Init **/
void
RFG_EnvMapFlip(void)
{
    WriteCall(0x0042D4B0, __FlipEnv2); // Chunk
    WriteCall(0x0042B6A4, __FlipEnv2); // Ginja
    WriteCall(0x0056DEEB, __FlipEnv2); // chDraw
}
