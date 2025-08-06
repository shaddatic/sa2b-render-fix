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
#include <rf_njcnk.h>               /* core                                                     */

/****** Self ************************************************************************************/
#include <rfm_common/rfc_newdisp/rfcd_internal.h> /* parent & siblings                          */

/********************************/
/*  Game Defs                   */
/********************************/
/****** Draw Shape ******************************************************************************/
#define DrawBasicObject_p           FUNC_PTR(void, __fastcall, (const void*, const NJS_POINT3*, const Angle3*, const NJS_VECTOR*, int), 0x00497350)

/****** Texlist ********************************************************************************/
#define texlist_bultex              DATA_ARY(NJS_TEXLIST   , 0x0145F284, [1])
#define object_e_bullet             DATA_ARY(NJS_CNK_OBJECT, 0x0145F43C, [1])

/****** Texture Manager *************************************************************************/
#define EnemyBulletManTexP          DATA_REF(task*, 0x01A5AD9C)

/********************************/
/*  Source                      */
/********************************/
/****** Task ************************************************************************************/
static void
DrawBasicObject(const NJS_POINT3* pPos, const Angle3* pAng, const NJS_VECTOR* pScl, int ixObject)
{
    // the first argument is fake, this is actually a usercall but this was easier
    DrawBasicObject_p(pScl, pPos, pAng, pScl, ixObject);
}

/****** Task ************************************************************************************/
static void
EnemyBulletDisplayer_RF(const task* tp)
{
    const taskwk* restrict twp = tp->twp;

    if ( twp->mode == 1 )
    {
        const NJS_VECTOR scl = { twp->scl.x, twp->scl.x, twp->scl.x };
        const Angle3     ang = { 0 };

        DrawBasicObject(&twp->pos, &ang, &scl, 4);
        return;
    }

    njPushMatrixEx();

    // if ( EnemyDrawAllowDirect != TRUE ) // Dreamcast only
    {
        njSetTexture(texlist_bultex);
    }

    njTranslateV(NULL, &twp->pos);

    njRotateY(NULL, twp->ang.y);
    njRotateX(NULL, twp->ang.x);
    njRotateZ(NULL, twp->ang.z);

    if ( EnemyDrawAllowDirect == TRUE && EnemyBulletManTexP && EnemyBulletManTexP->awp )
    {
        njCnkDirectDrawObject(object_e_bullet);
    }
    else
    {
        njCnkEasyDrawObject(object_e_bullet);
    }

    njPopMatrixEx();
}

/****** Init ************************************************************************************/
void
RFCD_EnemyBulletInit(void)
{
    WriteJump(0x00511820, EnemyBulletDisplayer_RF);
}
