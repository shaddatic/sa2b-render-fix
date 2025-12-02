/********************************/
/*  Includes                    */
/********************************/
/****** Core Toolkit ****************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/writeop.h>           /* writejump                                                */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Game ************************************************************************************/
#include <samt/sonic/task.h>        /* task                                                     */
#include <samt/sonic/njctrl.h>      /* ninja control                                            */
#include <samt/sonic/score.h>       /* game timer                                               */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_ninja.h>               /* rf ninja                                                 */
#include <rf_njcnk.h>               /* ninja chunk draw                                         */
#include <rf_samdl.h>               /* load model                                               */

/****** Self ************************************************************************************/
#include <rf_module/rfm_common/rfc_newdisp/rfcd_internal.h> /* parent & siblings                */

/********************************/
/*  Game Defs                   */
/********************************/
/****** Textures ********************************************************************************/
#define texlist_tjumpdai_ce          DATA_ARY(NJS_TEXLIST, 0x01092A18, [1])
#define texlist_tjumpdai_rh          DATA_ARY(NJS_TEXLIST, 0x01572DB8, [1])

/********************************/
/*  Data                        */
/********************************/
/****** Objects *********************************************************************************/
static NJS_CNK_OBJECT* object_tjumpdai_ce;
static NJS_CNK_OBJECT* object_tjumpdai_rh;

/****** UV Change Model *************************************************************************/
static NJS_CNK_MODEL* TrickJumpModelUvChange;

/********************************/
/*  Source                      */
/********************************/
/****** Callback ********************************************************************************/
static void
TrickJumpModelCallback(NJS_CNK_MODEL* model)
{
    f32 xoff, yoff;

    if ( TrickJumpModelUvChange == model )
    {
        xoff = -((f32)GameTimer * (38.f/256.f));
        yoff = 0.f;
    }
    else
    {
        xoff = 0.f;
        yoff = 0.f;
    }

    rjCnkSetUvScroll( xoff, yoff );
}

/****** Task ************************************************************************************/
void
ObjectTrickJumpDaiDisp_CE_CNK(task* tp)
{
    const taskwk* restrict twp = tp->twp;

    OnControl3D( NJD_CONTROL_3D_TRANS_MODIFIER|NJD_CONTROL_3D_SHADOW );

    njSetTexture( texlist_tjumpdai_ce );

    njPushMatrixEx();
    {
        njTranslateV( NULL, &twp->pos );
        njRotateXYZ(  NULL, twp->ang.x, twp->ang.y, twp->ang.z );

        njCnkEasyDrawObject( object_tjumpdai_ce );
    }
    njPopMatrixEx();

    OffControl3D( NJD_CONTROL_3D_TRANS_MODIFIER|NJD_CONTROL_3D_SHADOW );
}

void
ObjectTrickJumpDaiDisp_RH_CNK(task* tp)
{
    const taskwk* restrict twp = tp->twp;

    OnControl3D( NJD_CONTROL_3D_TRANS_MODIFIER|NJD_CONTROL_3D_SHADOW );

    njSetTexture( texlist_tjumpdai_rh );

    rjCnkSetModelCallback( TrickJumpModelCallback );

    njPushMatrixEx();
    {
        njTranslateV( NULL, &twp->pos );
        njRotateXYZ(  NULL, twp->ang.x, twp->ang.y, twp->ang.z );

        njCnkEasyDrawObject( object_tjumpdai_rh );
    }
    njPopMatrixEx();

    rjCnkSetModelCallback( nullptr );
    rjCnkSetUvScroll( 0.f, 0.f );

    OffControl3D( NJD_CONTROL_3D_TRANS_MODIFIER|NJD_CONTROL_3D_SHADOW );
}

/****** Init ************************************************************************************/
void
RFCD_TrickJumpDaiInit(void)
{
    WriteJump(0x005EB140, ObjectTrickJumpDaiDisp_CE_CNK);
    WriteJump(0x004E3830, ObjectTrickJumpDaiDisp_RH_CNK);

    object_tjumpdai_ce = RF_GetCnkObject("stage/13_cescape/tjumpdai.sa2mdl");
    object_tjumpdai_rh = RF_GetCnkObject("stage/14_highway/tjumpdai.sa2mdl");

    TrickJumpModelUvChange = object_tjumpdai_rh->child->model;
}
