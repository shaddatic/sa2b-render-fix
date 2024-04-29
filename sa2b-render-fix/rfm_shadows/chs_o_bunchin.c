#include <sa2b/core.h>
#include <sa2b/memutil.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/src/task.h>
#include <sa2b/src/debug.h>

/** Render Fix **/
#include <rf_file.h>
#include <rf_draw.h>
#include <rf_enemywk.h>

static NJS_CNK_OBJECT* object_o_bunchin_mod;

static void
ObjectBunchinDisplayerMod(TASK* tp)
{
    TASKWK*  const twp = tp->twp;
    ENEMYWK* const ewp = GET_ENEMYWK(tp);

    njPushMatrixEx();

    float scl_y = ewp->work.f * 0.5f;

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

    njCnkModDrawModel(object_o_bunchin_mod->model);
    njPopMatrixEx();
}

void
CHS_BunchinInit(void)
{
    WriteJump(0x006DCBE0, ObjectBunchinDisplayerMod);

    KillCall(0x006DBC9C); // Kill SetStencilInfo

    object_o_bunchin_mod = RF_ChunkLoadObjectFile("o_bunchin_mod");
}
