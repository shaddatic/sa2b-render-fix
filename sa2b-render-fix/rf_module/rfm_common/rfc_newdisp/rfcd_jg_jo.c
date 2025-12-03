/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* writejump                                        */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** Game ************************************************************************/
#include <samt/sonic/task.h>    /* task                                             */
#include <samt/sonic/njctrl.h>  /* nj control                                       */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_ninja.h>           /* rf ninja                                         */
#include <rf_njcnk.h>           /* emulated njcnk draw functions                    */
#include <rf_mdlutil.h>         /* change strip flag                                */
#include <rf_samdl.h>           /* load model                                       */

/****** Self ************************************************************************/
#include <rf_module/rfm_common/rfc_newdisp/rfcd_internal.h> /* parent & siblings    */

/************************/
/*  Game Data           */
/************************/
/****** Jungle Object Tree Textures *************************************************/
#define JungleObjectTexlists    DATA_ARY(NJS_TEXLIST*, 0x01072D54, [4])

/************************/
/*  Extern Data         */
/************************/
/****** Jungle Object Tree Textures *************************************************/
EXTERN NJS_TEXLIST texlist_jo_tree[];

/************************/
/*  Data                */
/************************/
/****** Jungle Object List **********************************************************/
static NJS_CNK_MODEL* JungleObjects[4];

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
CNK_JungleObjectDisp(const task* tp)
{
    const taskwk* twp = tp->twp;

    OnControl3D(NJD_CONTROL_3D_TRANS_MODIFIER|NJD_CONTROL_3D_SHADOW);

    njPushMatrixEx();

    njSetTexture( JungleObjectTexlists[twp->btimer] );

    njTranslateEx(&twp->pos);
    njRotateEx(&twp->ang.x, FALSE);

    njTranslate(NULL, 0.f, 0.5f, 0.f);

    njCnkDirectDrawModel( JungleObjects[twp->btimer] );

    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_TRANS_MODIFIER|NJD_CONTROL_3D_SHADOW);
}

static void
CNK_JungleObjectDisp_NoShadow(const task* tp)
{
    const taskwk* twp = tp->twp;

    njPushMatrixEx();

    njSetTexture( JungleObjectTexlists[twp->btimer] );

    njTranslateEx(&twp->pos);
    njRotateEx(&twp->ang.x, FALSE);

    njTranslate(NULL, 0.f, 0.5f, 0.f);

    njCnkDirectDrawModel( JungleObjects[twp->btimer] );

    njPopMatrixEx();
}

/****** Init ************************************************************************/
void
RFCD_JungleObjectInit(void)
{
    JungleObjectTexlists[2] = texlist_jo_tree;

    JungleObjects[0] = RF_GetCnkModel("stage/03_jungle/jo_wrock.sa2mdl");
    JungleObjects[1] = RF_GetCnkModel("stage/03_jungle/jo_grock.sa2mdl");
    JungleObjects[2] = RF_GetCnkModel("stage/03_jungle/jo_tree.sa2mdl");
    
    WriteJump(0x005EF7F0, CNK_JungleObjectDisp);
    WriteJump(0x005EF8F0, CNK_JungleObjectDisp_NoShadow);
}
