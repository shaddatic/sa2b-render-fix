#include <sa2b/core.h>
#include <sa2b/writemem.h>
#include <sa2b/writeop.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/sonic/task.h>
#include <sa2b/sonic/debug.h>

/** Render Fix **/
#include <rf_draw.h>

static void
ObjectMessengerDisplayerMod(task* tp)
{
    taskwk* const twp = tp->twp;

    NJS_POINT3 point;

    njCalcPoint(NULL, &twp->pos, &point);

    if (-point.z >= -100.f)
    {
        const float y_thing = njSin(tp->awp[2].work.sl[1]) * 2.3f;

        njPushMatrixEx();

        njTranslate(NULL, twp->pos.x, twp->pos.y + y_thing + 0.1f, twp->pos.z);
        njScale(NULL, 3.0f, 1.0f, 3.0f);

        DrawBasicShadow();
        njPopMatrixEx();
    }
}

void
CHS_MessengerInit(void)
{
    WriteJump(0x006C0CE0, ObjectMessengerDisplayerMod);

    KillCall(0x006C0815); // Kill SetStencilInfo
}
