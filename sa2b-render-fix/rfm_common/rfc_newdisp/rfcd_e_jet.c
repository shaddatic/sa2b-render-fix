/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/writeop.h>           /* writejump                                                */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Game ************************************************************************************/
#include <samt/sonic/task.h>        /* task                                                     */
#include <samt/sonic/njctrl.h>      /* setconstantmat                                           */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */

/****** RF Utility ******************************************************************************/
#include <rfu_float.h>              /* replacefloat                                             */

/****** Self ************************************************************************************/
#include <rfm_common/rfc_newdisp/rfcd_internal.h> /* parent & siblings                          */

/********************************/
/*  Game Defs                   */
/********************************/
/****** Texlists ********************************************************************************/
#define texlist_e_jet1              DATA_ARY(NJS_TEXLIST, 0x0145F5D4, [1])

/****** Function Ptrs ***************************************************************************/
#define EnemyJetDisplayer           FUNC_PTR(void, __cdecl, (task*), 0x00511230)

/********************************/
/*  Data                        */
/********************************/
/****** Texanims ********************************************************************************/
static NJS_TEXANIM texanim =
{
    .sx     = 32,
    .sy     = 32,
    .cx     = 16,
    .cy     = 16,
    .u1     = 0,
    .v1     = 0,
    .u2     = 256,
    .v2     = 256,
    .texid  = 0,
    .attr   = 0,
};

/********************************/
/*  Source                      */
/********************************/
/****** Task ************************************************************************************/
static void
EnemyJetDisplayer_(task* tp)
{
    task* const ptp = tp->ptp;

    if (!ptp || ptp->ctp == tp || tp->last->disp != EnemyJetDisplayer)
    {
        njColorBlendingMode(NJD_COLOR_SRC, NJD_COLOR_BLENDING_SRCALPHA);
        njColorBlendingMode(NJD_COLOR_DST, NJD_COLOR_BLENDING_ONE);

        njSetTexture(texlist_e_jet1);
        njFogDisable();
    }

    taskwk* const twp = tp->twp;

    NJS_SPRITE sprite = {
        .p     = twp->pos,
        .sx    = twp->scl.z,
        .sy    = twp->scl.z,
        .ang   = 0,
        .tlist = texlist_e_jet1,
        .tanim = &texanim,
    };

    const float col = twp->scl.x;

    SetConstantMaterial(col, col, col, col);

    njDrawSprite3D(&sprite, 0, NJD_SPRITE_COLOR | NJD_SPRITE_SCALE | NJD_SPRITE_ALPHA);

    ResetConstantMaterial();

    if (!ptp || ptp->ctp == tp->next || tp->next->disp != EnemyJetDisplayer)
    {
        njColorBlendingMode(0, NJD_COLOR_BLENDING_BOTHSRCALPHA);

        njFogEnable();
    }
}

/****** Init ************************************************************************************/
void
RFCD_EnemyJetInit(void)
{
    WriteJump(EnemyJetDisplayer, EnemyJetDisplayer_);

    /** Fix Shouko jet displaying inside its model **/
    RFU_ReplaceFloat(0x004F9B37, 7.2); // sub velocity
}
