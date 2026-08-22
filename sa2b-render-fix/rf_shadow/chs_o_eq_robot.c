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
/*  Game Refs                   */
/********************************/
/****** Task Init *******************************************************************************/
#define ObjectRobotInit             FUNC_PTR(void, __cdecl, (task*), 0x00691720)

/********************************/
/*  Source                      */
/********************************/
/****** Reform **********************************************************************************/
ASM_FUNC
void
ModModifyVList(Angle angz, Angle angx, Sint32* pVList)
{
    // arguments
    ASM_PUSH(      ASM_ESP(3+0) ); // pVList
    ASM_MOVE( ecx, ASM_ESP(2+1) ); // angx
    ASM_MOVE( eax, ASM_ESP(1+1) ); // angz

    // call
    ASM_CALL_R( edx, 0x00693AC0 );

    // end arguments
    ASM_ESP_ADD( 1 );

    // return
    ASM_RET( 0 );
}

/****** Displayers ******************************************************************************/
void
ObjectRobotShadow(task* tp)
{
    taskwk* const twp = tp->twp;
    anywk*  const awp = tp->awp;

    if ( !awp[10].work.ul[3] )
    {
        return;
    }

    OnControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();
    {
        NJS_MATRIX* p_mat = (NJS_MATRIX*)awp[5].work.ul[0];

        if ( !p_mat )
        {
            p_mat = _nj_matrix_;
        }

        njMultiMatrix(NULL, p_mat);

        njRotateZ(NULL, -twp->ang.z);
        njRotateX(NULL, -twp->ang.x);
        njRotateY(NULL, NJM_DEG_ANG(180.f));

        NJS_CNK_MODEL* p_model = object_eq_robot_mod->model;

        const f32 model_r = p_model->r;

        p_model->r *= 1.2f;

        njTranslate(NULL, 0.0f, -14.0f, 0.0f);
        njScale(NULL, 1.0f, 1.2f, 1.0f);

        if (*(uint16_t*)p_model->vlist == 34)
        {
            ModModifyVList(twp->ang.z, twp->ang.x, p_model->vlist);
        }

        njCnkModDrawObject(object_eq_robot_mod);

        p_model->r = model_r;
    }
    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);
}

/****** Hooks ***********************************************************************************/
static void
ObjectRobotInitHook(task* tp)
{
    ObjectRobotInit(tp);
    tp->disp_shad = ObjectRobotShadow;
}

/****** Init ************************************************************************************/
void
CHS_EggQuatersRobotInit(void)
{
    KillCall(0x00691614); // og ObjectRobotModifyVList
    WriteCall(0x00690DB4, ObjectRobotInitHook);
}
