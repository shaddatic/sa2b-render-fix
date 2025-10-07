#include <samt/core.h>
#include <samt/writemem.h>
#include <samt/funchook.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Source **/
#include <samt/sonic/task.h>
#include <samt/sonic/debug.h>

/** Render Fix **/
#include <rf_ninja.h>
#include <rf_util.h>

#define dword_1945E08   DATA_REF(int, 0x1945E08)

static void
ChaosDriveDisplayerMod(task* tp)
{
    taskwk* const twp = tp->twp;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);

    switch (dword_1945E08) {
    case 0:
    case 1:
        njRotateZ(NULL, 0x4000);
        break;

    case 4:
    case 5:
        njRotateX(NULL, 0x4000);
        break;
    }

    njRotateY(NULL, twp->ang.y);
    njScale(NULL, twp->scl.z, twp->scl.z, twp->scl.z);
    njScale(NULL, 1.6f, 0.5f, 2.6f);

    DrawBasicShadow();

    njPopMatrixEx();
}

__declspec(naked)
static void
__ChaosDriveMovHook(void)
{
    __asm
    {
        mov dword ptr[esi+1Ch], 0048F0E0h
        mov dword ptr[esi+2Ch], offset ChaosDriveDisplayerMod
        retn
    }
}

void
CHS_ChaosDriveInit(void)
{
    WriteCallToMovDwordPtr(0x0048F87A, __ChaosDriveMovHook);
}
