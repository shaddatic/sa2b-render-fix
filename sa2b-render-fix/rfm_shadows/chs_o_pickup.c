#include <sa2b/core.h>
#include <sa2b/memutil.h>
#include <sa2b/funchook.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/src/task.h>
#include <sa2b/src/debug.h>

/** Render Fix **/
#include <rf_draw.h>

static void
ObjectPickUpDisplayerMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;

    if (twp->flag & 0x8000)
        return;

    njPushMatrixEx();

    njTranslate(NULL, twp->pos.x, twp->pos.y + 0.1f, twp->pos.z);
    njScale(NULL, 3.0f, 1.0f, 3.0f);

    DrawBasicShadow();

    njPopMatrixEx();
}

#define ObjectPickUpDisplayer   FuncPtr(void, __cdecl, (TASK*), 0x006BC7A0)

static void
ObjectPickUpInitDisplayers(TASK* tp)
{
    tp->disp = ObjectPickUpDisplayer;
    tp->disp_shad = ObjectPickUpDisplayerMod;
}

__declspec(naked)
static void
__ObjectPickUpInitDisplayers(TASK* tp)
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
CHS_PickUpInit()
{
    WriteNoOP(0x006BC9E7, 0x006BC9EE); // NOP mov dword ptr
    WriteCall(0x006BC9E7, __ObjectPickUpInitDisplayers);
}
