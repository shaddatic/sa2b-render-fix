#include <samt/core.h>
#include <samt/writemem.h>
#include <samt/writeop.h>
#include <samt/funchook.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Source **/
#include <samt/sonic/task.h>
#include <samt/sonic/debug.h>

/** Render Fix **/
#include <rf_file.h>
#include <rf_draw.h>
#include <rf_util.h>

static void
ObjectUdreelDisplayerMod(task* tp)
{
    taskwk* const twp = tp->twp;

    njPushMatrixEx();

    njTranslate(NULL, twp->pos.x, twp->pos.y + tp->mwp[1].work.f, twp->pos.z);
    njScale(NULL, 3.6f, 1.0f, 3.6f);

    DrawBasicShadow();

    njPopMatrixEx();
}

static void
ObjectGolemUdreelDisplayerMod(task* tp)
{
    taskwk* const twp = tp->twp;

    njPushMatrixEx();

    njTranslate(NULL, twp->pos.x, twp->pos.y + tp->mwp[1].work.f, twp->pos.z);
    njScale(NULL, 4.0f, 1.0f, 4.0f);

    DrawBasicShadow();

    njPopMatrixEx();
}

#define ObjectGolemUdreel       FUNC_PTR(void, __cdecl, (task*), 0x004BB5D0)

static hook_info HookInfoGolemUdreel[1];

static void
ObjectGolemUdreelHook(task* tp)
{
    HookInfoUnhook(HookInfoGolemUdreel);
    ObjectGolemUdreel(tp);
    HookInfoRehook(HookInfoGolemUdreel);

    if (tp->disp)
        tp->disp_shad = ObjectGolemUdreelDisplayerMod;
}

void
CHS_UdreelInit(void)
{
    WriteJump(0x006E6320, ObjectUdreelDisplayerMod);
    SwitchDisplayer(0x006E56A2, DISP_SHAD);

    FuncHook(HookInfoGolemUdreel, ObjectGolemUdreel, ObjectGolemUdreelHook);
    KillCall(0x004BC47C);
    KillCall(0x004BC6FE);
}
