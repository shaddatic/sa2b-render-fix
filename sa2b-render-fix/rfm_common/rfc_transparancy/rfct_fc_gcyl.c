/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>      /* core                                                 */
#include <sa2b/writemem.h>  /* WriteData, WritePointer                              */
#include <sa2b/writeop.h>   /* WriteJump, WriteRetn                                 */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h> /* ninja                                              */

/****** Game ************************************************************************/
#include <sa2b/sonic/task.h>   /* TASK, TASKWK, MOTIONWK, ...                       */
#include <sa2b/sonic/score.h>  /* GetGameTime                                       */
#include <sa2b/sonic/njctrl.h> /* OnControl3D, OffControl3D                         */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */
#include <rf_util.h>        /* ReplaceFloat, SwitchDisplayer                        */
#include <rf_mdlutil.h>     /* MaterialFlagOn                                       */
#include <rf_renderstate.h> /* RFRS_CullMode                                        */

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

    ___NOTE("This should be improved."
        "The glass should be a seperate model, & only that is drawn twice");
    /** Main body (first/inverse pass) **/
    {
        OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

        RFRS_SetCullMode(RFRS_CULLMD_INVERSE);
        njCnkDrawModel_Broken(object_gcyl->model);
        RFRS_SetCullMode(RFRS_CULLMD_END);

        OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
    }

    /** Animated green arrows **/
    {
        CnkModelChangeTexID(object_gcyl_tanim->model, 0, ((game_timer >> 1) & 7) + 7);
        njCnkDrawModel_Broken(object_gcyl_tanim->model);
    }

    /** Inner half ring **/
    {
        njPushMatrixEx();
        njRotateY(NULL, game_timer << 9);
        njCnkDrawModel_Broken(object_gcyl_inner->model);
        njPopMatrixEx();
    }

    /** Main body (second/normal pass) **/
    {
        OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

        RFRS_SetCullMode(RFRS_CULLMD_NORMAL);
        njCnkDrawModel_Broken(object_gcyl->model);
        RFRS_SetCullMode(RFRS_CULLMD_END);

        OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
    }

    njPopMatrixEx();
}

void
RFCT_FinalChaseGravityCylinderInit(void)
{
    WriteRetn(0x004E9C50);
    WriteJump(0x004E9DB0, GravityCylinderDisplayerSorted);

    CnkModelMaterialFlagOn(object_gcyl->model, 4, NJD_FST_DB);  // Transparant glass
    CnkModelMaterialFlagOn(object_gcyl->model, 4, NJD_FST_NAT);
}
