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

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_ninja.h>               /* render fix ninja                                         */
#include <rf_njcnk.h>               /* ninja chunk draw                                         */
#include <rf_util.h>                /* switch displayer                                         */

/****** Self ************************************************************************************/
#include <rf_shadow/chs_internal.h> /* parent & siblings                                        */

/********************************/
/*  Game Refs                   */
/********************************/
/****** Displayer *******************************************************************************/
#define ObjectPickUpDisplayer       FUNC_PTR(void, __cdecl, (task*), 0x006BC7A0)

/********************************/
/*  Source                      */
/********************************/
/****** Displayers ******************************************************************************/
void
ObjectPickUpShadow(task* tp)
{
    taskwk* const twp = tp->twp;

    if ( twp->flag & 0x8000 )
    {
        return;
    }

    OnControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();
    {
        njTranslate(NULL, twp->pos.x, twp->pos.y + 0.1f, twp->pos.z);
        njScale(NULL, 3.0f, 1.0f, 3.0f);

        njCnkModDrawModel( object_shadow->model );
    }
    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);
}

/****** Hooks ***********************************************************************************/
static void
ObjectPickUpInitDisplayers(task* tp)
{
    tp->disp = ObjectPickUpDisplayer;
    tp->disp_shad = ObjectPickUpShadow;
}

__declspec(naked)
static void
__ObjectPickUpInitDisplayers(task* tp)
{
    __asm
    {
        push esi
        call ObjectPickUpInitDisplayers
        pop esi
        retn
    }
}

/****** Init ************************************************************************************/
void
CHS_PickUpInit(void)
{
    WriteNOP( 0x006BC9E7, 0x006BC9EE); // NOP mov dword ptr
    WriteCall(0x006BC9E7, __ObjectPickUpInitDisplayers);
}
