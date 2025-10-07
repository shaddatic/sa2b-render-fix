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
#include <rf_ninja.h>
#include <rf_util.h>

static void
ObjectIronBall2DisplayerMod(task* tp)
{
    taskwk* const twp = tp->twp;

    njPushMatrixEx();

    njTranslate(NULL, twp->pos.x, twp->pos.y + 0.1f, twp->pos.z);
    njRotateY(NULL, twp->ang.y);

    njPushMatrixEx();

    njScale(NULL, 5.0f, 1.0f, 5.0f);
    DrawBasicShadow();

    njPopMatrixEx();
    njPushMatrixEx();

    const float trans_x = (twp->scl.x + 1) * 20.0f;

    njTranslate(NULL, trans_x, 0.0f, 0.0f);
    njScale(NULL, 10.0f, 1.0f, 10.0f);
    DrawBasicShadow();

    njPopMatrixEx();
    njPushMatrixEx();

    njTranslate(NULL, -trans_x, 0.0f, 0.0f);
    njScale(NULL, 10.0f, 1.0f, 10.0f);
    DrawBasicShadow();

    njPopMatrixEx();

    njPopMatrixEx();
}

void
CHS_IronBall2Init(void)
{
    WriteNOP(0x006D3C7C, 0x006D3C82);
    SwitchDisplayer(0x006D3C82, DISP_SHAD);
    WriteJump(0x006D4340, ObjectIronBall2DisplayerMod);
}
