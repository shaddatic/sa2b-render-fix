#include <sa2b/core.h>
#include <sa2b/writemem.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/sonic/task.h>
#include <sa2b/sonic/set.h>
#include <sa2b/sonic/c_colli.h>

/** Object **/
#include <sa2b/sonic/object/o_light.h>

static OBJ_CONDITION objcond_treelightsw;

static void
CreateNewLightSW(task* tp, float posX, float posY, float posZ)
{
    NJS_POINT3 point = {
        .x = 0.0f,
        .y = 0.0f,
        .z = 0.0f
    };

    task* ctp = CreateChildTask(TELE_TWK, ObjectLightSW, tp);

    njPushMatrixEx();

    njTranslate(NULL, posX, posY, posZ);

    njCalcPointEx(&point, &point);

    ctp->twp->pos.x = point.x;
    ctp->twp->pos.y = point.y + 24.0f;
    ctp->twp->pos.z = point.z;

    ctp->twp->scl.x = 24.0f;
    ctp->twp->scl.y = 32.0f;
    ctp->twp->scl.z = 24.0f;

    ctp->twp->smode = 1;

    ctp->ocp = &objcond_treelightsw;

    njPopMatrixEx();
}

void
ObjectTreeShadows(task* tp)
{
    if (CheckRangeOut(tp))
        return;

    tp->exec = ObjectGenericExec;

    taskwk* twp = tp->twp;

    njPushMatrix(&_nj_unit_matrix_);

    njTranslateEx(&twp->pos);
    njRotateY(0, twp->ang.y);

    CreateNewLightSW(tp, 70.0f, -165.0f, 240.0f);
    CreateNewLightSW(tp, 70.0f, 0.0f, 0.0f);
    CreateNewLightSW(tp, 70.0f, 165.0f, -240.0f);
    CreateNewLightSW(tp, -70.0f, -165.0f, 240.0f);
    CreateNewLightSW(tp, -70.0f, 0.0f, 0.0f);
    CreateNewLightSW(tp, -70.0f, 165.0f, -240.0f);

    njPopMatrixEx();
}
