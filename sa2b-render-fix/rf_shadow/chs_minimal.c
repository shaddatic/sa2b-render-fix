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

/****** RF Util *********************************************************************************/
#include <rfu_draw.h>               /* animate motion                                           */

/****** Self ************************************************************************************/
#include <rf_shadow/chs_internal.h> /* parent & siblings                                        */

/********************************/
/*  Game Refs                   */
/********************************/
/****** Create Minimal **************************************************************************/
#define ObjectMinimal               FUNC_PTR(void , __cdecl, (task*)                  , 0x0048ADE0)
#define MinimalCreate               FUNC_PTR(task*, __cdecl, (f32, f32, f32, i32, u32), 0x0048AAD0)

/****** Vars ************************************************************************************/
#define dword_1945E08               DATA_REF(i32, 0x1945E08)

/********************************/
/*  Source                      */
/********************************/
/****** Displayers ******************************************************************************/
void
Minimal_Shad(task* tp)
{
    taskwk* const twp = tp->twp;
    anywk*  const awp = tp->awp;

    const u32 mode = awp->work.ul[0];

    if ( mode == 2 || (mode != 0 && awp[1].work.ub[4] & 1) )
    {
        return;
    }

    OnControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();
    {
        if ( mode == 0 )
        {
            const Angle mot_ang = awp->work.sl[3];

            const f32 trns_x = njSin(mot_ang) * twp->scl.x + twp->pos.x;
            const f32 trns_z = njCos(mot_ang) * twp->scl.x + twp->pos.z;

            njTranslate( NULL, trns_x, twp->pos.y, trns_z );
            njRotateY(   NULL, awp->work.ul[3] + NJM_DEG_ANG(90.f) );
        }
        else
        {
            njTranslateV( NULL, &twp->pos );
            njRotateY(    NULL, twp->ang.y );
        }

        njScale( NULL, 1.4f, 1.4f, 1.4f );

        if ( dword_1945E08 != 3 )
        {
            njRotateZ( NULL, NJM_DEG_ANG(180.f) );
        }

        njTranslate( NULL, 0.0f, 2.0f, 0.0f );
        njScale(     NULL, 1.2f, 0.5f, 1.8f );

        njCnkModDrawModel( object_shadow->model );
    }
    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);
}

/****** Hooks ***********************************************************************************/
static mt_hookinfo HookInfoObjectMinimal[1];
static void
ObjectMinimalHook(task* tp)
{
    mtHookInfoCall( HookInfoObjectMinimal, ObjectMinimal(tp) );

    if ( !tp->disp_shad )
    {
        tp->disp_shad = Minimal_Shad;
    }
}

static mt_hookinfo HookInfoMinimalCreate[1];
static task*
MinimalCreateHook(f32 posX, f32 posY, f32 posZ, int num, uint32_t flag)
{
    task* minitp;

    mtHookInfoCall( HookInfoMinimalCreate, minitp = MinimalCreate(posX, posY, posZ, num, flag) );

    if ( minitp && !minitp->disp_shad )
    {
        minitp->disp_shad = Minimal_Shad;
    }

    return minitp;
}

/****** Init ************************************************************************************/
void
CHS_MinimalInit(void)
{
    mtHookFunc(HookInfoObjectMinimal, ObjectMinimal, ObjectMinimalHook);
    mtHookFunc(HookInfoMinimalCreate, MinimalCreate, MinimalCreateHook);
}
