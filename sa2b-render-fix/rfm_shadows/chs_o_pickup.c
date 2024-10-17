#include <sa2b/core.h>
#include <sa2b/writemem.h>
#include <sa2b/writeop.h>
#include <sa2b/funchook.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/sonic/task.h>
#include <sa2b/sonic/debug.h>

/** Render Fix **/
#include <rf_draw.h>

static void
ObjectPickUpDisplayerMod(task* tp)
{
    taskwk* const twp = tp->twp;

    if (twp->flag & 0x8000)
        return;

    njPushMatrixEx();

    njTranslate(NULL, twp->pos.x, twp->pos.y + 0.1f, twp->pos.z);
    njScale(NULL, 3.0f, 1.0f, 3.0f);

    DrawBasicShadow();

    njPopMatrixEx();
}

#define ObjectPickUpDisplayer   FUNC_PTR(void, __cdecl, (task*), 0x006BC7A0)

static void
ObjectPickUpInitDisplayers(task* tp)
{
    tp->disp = ObjectPickUpDisplayer;
    tp->disp_shad = ObjectPickUpDisplayerMod;
}

__declspec(naked)
static void
__ObjectPickUpInitDisplayers(task* tp)
{
    __asm
    {
        push esi
        call ObjectPickUpInitDisplayers
        pop esi
        retn
    }
}

void
CHS_PickUpInit(void)
{
    WriteNOP( 0x006BC9E7, 0x006BC9EE); // NOP mov dword ptr
    WriteCall(0x006BC9E7, __ObjectPickUpInitDisplayers);
}
