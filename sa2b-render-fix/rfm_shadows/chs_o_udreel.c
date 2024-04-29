#include <sa2b/core.h>
#include <sa2b/memutil.h>
#include <sa2b/funchook.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/src/task.h>
#include <sa2b/src/debug.h>

/** Render Fix **/
#include <rf_file.h>
#include <rf_draw.h>
#include <rf_util.h>

static void
ObjectUdreelDisplayerMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;

    njPushMatrixEx();

    njTranslate(NULL, twp->pos.x, twp->pos.y + tp->mwp[1].work.f, twp->pos.z);
    njScale(NULL, 3.6f, 1.0f, 3.6f);

    DrawBasicShadow();

    njPopMatrixEx();
}

static void
ObjectGolemUdreelDisplayerMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;

    njPushMatrixEx();

    njTranslate(NULL, twp->pos.x, twp->pos.y + tp->mwp[1].work.f, twp->pos.z);
    njScale(NULL, 4.0f, 1.0f, 4.0f);

    DrawBasicShadow();

    njPopMatrixEx();
}

#define ObjectGolemUdreel       FuncPtr(void, __cdecl, (TASK*), 0x004BB5D0)

static hook_info* HookInfoGolemUdreel;

static void
ObjectGolemUdreelHook(TASK* tp)
{
    FuncHookRestore(HookInfoGolemUdreel);
    ObjectGolemUdreel(tp);
    FuncHookRehook(HookInfoGolemUdreel);

    if (tp->disp)
        tp->disp_shad = ObjectGolemUdreelDisplayerMod;
}

void
CHS_UdreelInit(void)
{
    WriteJump(0x006E6320, ObjectUdreelDisplayerMod);
    SwitchDisplayer(0x006E56A2, DISP_SHAD);

    HookInfoGolemUdreel = FuncHook(ObjectGolemUdreel, ObjectGolemUdreelHook);
    KillCall(0x004BC47C);
    KillCall(0x004BC6FE);
}
