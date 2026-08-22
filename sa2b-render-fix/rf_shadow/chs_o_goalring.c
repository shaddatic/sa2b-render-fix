/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/writemem.h>          /* write memory                                             */
#include <samt/writeop.h>           /* write op                                                 */
#include <samt/funchook.h>          /* function hook                                            */

/****** Utl *************************************************************************************/
#include <samt/util/asm.h>          /* asm helper                                               */

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
/*  Source                      */
/********************************/
/****** Displayers ******************************************************************************/
void
ObjectGoalRingShadow(task* tp)
{
    taskwk* const twp = tp->twp;

    /** Is not a Chao **/
    if (twp->ang.x % 3 != 1)
    {
        OnControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);

        njPushMatrixEx();
        {
            njTranslateV(NULL, &twp->pos);
            njRotateY(NULL, twp->ang.y);
            njScale(NULL, 30.0f, 5.0f, 10.0f);

            njCnkModDrawModel( object_shadow->model );
        }
        njPopMatrixEx();

        OffControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);
    }
}

/****** Init ************************************************************************************/
void
CHS_GoalRingInit(void)
{
    WriteJump(0x006C7280, ObjectGoalRingShadow);

    /** disp_sort func also handles lost Chao sprites, so
        should be left on. Has no impact on Goal Ring due
        to code returning if disp_shad isn't NULL **/
//  WriteRetn(0x006C6F10);             // Kill disp_sort

    /** Ensure modifier displayer is awlays active **/
    WriteNOP(0x006C653A, 0x006C653E); // Force disp_shad
    WriteNOP(0x006C6543, 0x006C6545); // ^
    WriteNOP(0x006C6546, 0x006C655D); // ^

    KillCall(0x006C6519); // Kill SetStencilInfo
}
