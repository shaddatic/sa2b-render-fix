#include <samt/core.h>
#include <samt/writemem.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Source **/
#include <samt/sonic/task.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_util.h>
#include <rf_mdlutil.h>

#define texlist_pr_siren        DATA_ARY(NJS_TEXLIST   , 0x01043D40, [1])
#define object_pr_siren         DATA_ARY(NJS_CNK_OBJECT, 0x0104467C, [1])

static void
ObjectPRSirenDisplayer(task* tp)
{
    taskwk* const twp = tp->twp;

    njSetTexture(texlist_pr_siren);

    njPushMatrixEx();
    njFogDisable();

    njTranslateEx(&twp->pos);
    njRotateZ(NULL, twp->ang.z);
    njRotateY(NULL, twp->ang.y);
    njRotateX(NULL, twp->ang.x);

    njPushMatrixEx();

    njRotateY(NULL, twp->wtimer);
    njCnkCacheDrawModel(object_pr_siren->child->model);

    njPopMatrixEx();

    njCnkCacheDrawModel(object_pr_siren->model);

    njFogEnable();
    njPopMatrixEx();
}

#define texlist_rn_siren        DATA_ARY(NJS_TEXLIST   , 0x00BF5948, [1])
#define object_rn_siren         DATA_ARY(NJS_CNK_OBJECT, 0x00BF627C, [1])

static void
ObjectRNSirenDisplayer(task* tp)
{
    taskwk* const twp = tp->twp;

    njSetTexture(texlist_rn_siren);

    njPushMatrixEx();
    njFogDisable();

    njTranslateEx(&twp->pos);
    njRotateZ(NULL, twp->ang.z);
    njRotateY(NULL, twp->ang.y);
    njRotateX(NULL, twp->ang.x);

    njPushMatrixEx();

    njRotateY(NULL, twp->wtimer);
    njCnkCacheDrawModel(object_rn_siren->child->model);

    njPopMatrixEx();

    njCnkCacheDrawModel(object_rn_siren->model);

    njFogEnable();
    njPopMatrixEx();
}

void
RFCD_PrisonSirenInit(void)
{
    /** Prison Lane **/
    CnkObjectMaterialFlagOn(object_pr_siren, NJD_FST_IL);
    CnkObjectBlendingDst(object_pr_siren, NJD_FBD_ONE);

    WriteJump(0x00606820, ObjectPRSirenDisplayer);

    SwitchDisplayer(0x0060679E, DISP_SORT);

    /** Iron Gate **/
    CnkObjectMaterialFlagOn(object_rn_siren, NJD_FST_IL);
    CnkObjectBlendingDst(object_rn_siren, NJD_FBD_ONE);

    WriteJump(0x0069E100, ObjectRNSirenDisplayer);

    SwitchDisplayer(0x0069E04E, DISP_SORT);
}
