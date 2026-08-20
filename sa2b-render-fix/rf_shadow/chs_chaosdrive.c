/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/writemem.h>          /* write memory                                             */
#include <samt/writeop.h>           /* write op                                                 */
#include <samt/funchook.h>          /* function hook                                            */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Game ************************************************************************************/
#include <samt/sonic/task.h>        /* task                                                     */
#include <samt/sonic/njctrl.h>      /* ninja control funcs                                      */
#include <samt/sonic/camera.h>
#include <samt/sonic/cart/cartcar.h>

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_ninja.h>               /* render fix ninja                                         */
#include <rf_njcnk.h>               /* ninja chunk draw                                         */
#include <rf_util.h>                /* switch displayer                                         */

/****** RF Util *********************************************************************************/
#include <rfu_draw.h>               /* animate motion                                           */

/****** Self ************************************************************************************/
#include <rf_shadow/chs_internal.h> /* parent & siblings                                        */

/********************************/
/*  Game Refs                   */
/********************************/
/****** Cdr *************************************************************************************/
#define dword_1945E08               DATA_REF(int, 0x1945E08)

/********************************/
/*  Source                      */
/********************************/
/****** Displayers ******************************************************************************/
void
ChaosDriveShadow(task* tp)
{
    taskwk* const twp = tp->twp;

    njPushMatrixEx();

    njTranslateV( NULL, &twp->pos );

    switch ( dword_1945E08 )
    {
        case 0: case 1:
        {
            njRotateZ( NULL, NJM_DEG_ANG(90.f) );
            break;
        }
        case 4: case 5:
        {
            njRotateX( NULL, NJM_DEG_ANG(90.f) );
            break;
        }
    }

    njRotateY( NULL, twp->ang.y );
    njScale(   NULL, twp->scl.z, twp->scl.z, twp->scl.z );
    njScale(   NULL, 1.6f, 0.5f, 2.6f );

    njCnkModDrawModel( object_shadow->model );

    njPopMatrixEx();
}

/****** Hooks ***********************************************************************************/
__declspec(naked)
static void
__ChaosDriveMovHook(void)
{
    __asm
    {
        mov dword ptr[esi+1Ch], 0048F0E0h
        mov dword ptr[esi+2Ch], offset ChaosDriveShadow
        retn
    }
}

/****** Init ************************************************************************************/
void
CHS_ChaosDriveInit(void)
{
    WriteCallToMovDwordPtr(0x0048F87A, __ChaosDriveMovHook);
}
