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
#include <rf_core.h>                /* core                                                     */
#include <rf_model.h>
#include <rf_ninja.h>
#include <rf_njcnk.h>               /* ninja chunk draw                                         */
#include <rf_shadow.h>

void
ObjectFireBallShadow(task* tp)
{
    taskwk* const twp = tp->twp;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);

    njCnkModDrawObject(object_md_meteo_mod);

    njPopMatrixEx();
}

#define ObjectMDFireBall    FUNC_PTR(void, __cdecl, (task*), 0x005C1280)

static mt_hookinfo HookInfoObjectMDFireBall[1];
static void
ObjectMDFireBallHook(task* tp)
{
    mtHookInfoCall(HookInfoObjectMDFireBall, ObjectMDFireBall(tp));

    tp->disp_shad = ObjectFireBallShadow;
}

void
ObjectMeteoBigShadow(task* tp)
{
    taskwk* const twp = tp->twp;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njCnkModDrawObject(object_md_meteo_mod);

    njPopMatrixEx();
}

void
CHS_MeteoBigInit(void)
{
    mtHookFunc(HookInfoObjectMDFireBall, ObjectMDFireBall, ObjectMDFireBallHook);

    WriteJump(0x005C5120, ObjectMeteoBigShadow);
    KillCall(0x005C4E04); // Kill SetStencilInfo
}
