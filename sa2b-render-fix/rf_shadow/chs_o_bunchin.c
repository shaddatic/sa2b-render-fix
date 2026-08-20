#include <samt/core.h>
#include <samt/writemem.h>
#include <samt/writeop.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Source **/
#include <samt/sonic/task.h>
#include <samt/sonic/debug.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_model.h>
#include <rf_ninja.h>
#include <rf_shadow.h>

void
ObjectBunchinShadow(task* tp)
{
    taskwk*   const twp = tp->twp;
    motionwk* const mwp = tp->mwp;

    njPushMatrixEx();

    float scl_y = mwp->work.f * 0.5f;

    if (scl_y > 100.0f)
        scl_y = 100.f;

    float scl_y_add;

    if (twp->ang.z & 0x1000)
    {
        njTranslate(NULL, twp->pos.x, twp->pos.y + scl_y - 102.5f, twp->pos.z);
        njRotateY(NULL, twp->ang.y);

        scl_y_add = 103.0f;
    }
    else
    {
        njTranslate(NULL, twp->pos.x, twp->pos.y + scl_y - 2.5f, twp->pos.z);
        njRotateY(NULL, twp->ang.y);
        
        scl_y_add = 3.0f;
    }

    scl_y += scl_y_add;

    float scl_x = (twp->scl.x + 1.0f) * 1.3333334f;
    float scl_z = (twp->scl.z + 1.0f) * 1.3333334f;

    njScale(NULL, scl_x , scl_y * 0.06666667f, scl_z);

    njCnkModDrawModel(object_modmod_box->model);
    njPopMatrixEx();
}

void
CHS_BunchinInit(void)
{
    WriteJump(0x006DCBE0, ObjectBunchinShadow);

    KillCall(0x006DBC9C); // Kill SetStencilInfo
}
