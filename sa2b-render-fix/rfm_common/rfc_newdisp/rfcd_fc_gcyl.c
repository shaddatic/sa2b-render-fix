/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>      /* core                                                 */
#include <samt/writemem.h>  /* WriteData, WritePointer                              */
#include <samt/writeop.h>   /* WriteJump, WriteRetn                                 */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h> /* ninja                                              */

/****** Game ************************************************************************/
#include <samt/sonic/task.h>   /* TASK, TASKWK, MOTIONWK, ...                       */
#include <samt/sonic/score.h>  /* GetGameTime                                       */
#include <samt/sonic/njctrl.h> /* OnControl3D, OffControl3D                         */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */
#include <rf_util.h>        /* ReplaceFloat, SwitchDisplayer                        */
#include <rf_mdlutil.h>     /* MaterialFlagOn                                       */
#include <rf_renderstate.h> /* RFRS_CullMode                                        */
#include <rf_njcnk.h>       /* ninja chunk draw                                     */

/************************/
/*  Constants           */
/************************/
#define texlist_gcyl        DATA_ARY(NJS_TEXLIST   , 0x01528DD4, [1])

#define object_gcyl         DATA_ARY(NJS_CNK_OBJECT, 0x0152AF84, [1])
#define object_gcyl_tanim   DATA_ARY(NJS_CNK_OBJECT, 0x015291AC, [1])
#define object_gcyl_inner   DATA_ARY(NJS_CNK_OBJECT, 0x015298B4, [1])

/************************/
/*  Source              */
/************************/
static void
GravityCylinderDisplayerSorted(task* tp)
{
    taskwk* const twp = tp->twp;

    const int game_timer = GetGameTime();

    njPushMatrixEx();

    njTranslateEx(&twp->pos);

    const Sangle rot_y = -(Sangle)((f64)((s16)twp->ang.x) * 0.1000000014901161);

    njRotateY(NULL, twp->ang.y & 0xFF00);
    njRotateZ(NULL, twp->ang.z);
    njRotateY(NULL, rot_y * game_timer);

    njSetTexture(texlist_gcyl);

    /** Main body (first/opaque pass) **/
    {
        OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

        RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_OPAQUE);
        njCnkSimpleDrawModel(object_gcyl->model);
        RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_END);

        OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
    }

    /** Animated green arrows **/
    {
        CnkModelChangeTexID(object_gcyl_tanim->model, 0, ((game_timer >> 1) & 7) + 7);
        njCnkCacheDrawModel(object_gcyl_tanim->model);
    }

    /** Inner half ring **/
    {
        njPushMatrixEx();
        njRotateY(NULL, game_timer << 9);
        njCnkCacheDrawModel(object_gcyl_inner->model);
        njPopMatrixEx();
    }

    /** Main body (second/transparent pass) **/
    {
        OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

        RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_TRANSPARENT);
        njCnkSimpleDrawModel(object_gcyl->model);
        RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_END);

        OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
    }

    njPopMatrixEx();
}

void
RFCD_FinalChaseGravityCylinderInit(void)
{
    WriteRetn(0x004E9C50);
    WriteJump(0x004E9DB0, GravityCylinderDisplayerSorted);

    CnkModelMaterialFlagOn(object_gcyl->model, 4, NJD_FST_DB);  // Transparant glass
    CnkModelMaterialFlagOn(object_gcyl->model, 4, NJD_FST_NAT);
}
