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
/*  Macro                       */
/********************************/
/****** Square **********************************************************************************/
#define SQR(x)                      ((x)*(x))

/********************************/
/*  Structures                  */
/********************************/
/****** Cart Work *******************************************************************************/
typedef struct
{
    char gap0[8];
    Angle3 ang;
    NJS_POINT3 pos;
    char gap2[20];
    NJS_CNK_OBJECT* pObject;
    NJS_CNK_OBJECT* pFarObject;
    NJS_TEXLIST*    pTexlist;
    int headlights;
    b32 is_player;
    int character;
    int player_num;
    void* ptr1;
    char gap4[20];
    Angle angSlide;
    char gap5[132];
    Angle3 ang3;
    Angle3 ang2;
    char gap6[412];
    void* texp;
    int address_u;
    int address_v;
    int tes5;
    int min_filter;
    int mag_filter;
    int bank;
    __int32 stencil_data[1];
    void* stencil_tex;
    char gap7[28];
}
CARTWK;

#define GET_CARTWK(_tp)     ((CARTWK*)_tp->mwp)

/********************************/
/*  Game Refs                   */
/********************************/
/****** Cart ************************************************************************************/
#define PlayerCartSelected          DATA_ARY(i8, 0x0174B021, [2])

/****** Course **********************************************************************************/
#define courseDisplayDisplayer      FUNC_PTR(void, __cdecl, (task*), 0x00623E10)

/********************************/
/*  Source                      */
/********************************/
/****** Displayers ******************************************************************************/
void
cartShadow(task* tp)
{
    CARTWK* const cwp = GET_CARTWK(tp);

    camposwk* const camwk = camera_pos[camera_num];

    NJS_POINT3 rel_pos = {
        .x = cwp->pos.x - camwk->pos.x,
        .y = cwp->pos.y - camwk->pos.y,
        .z = cwp->pos.z - camwk->pos.z,
    };

    const float fchk = (rel_pos.x * rel_pos.x) + (rel_pos.y * rel_pos.y) + (rel_pos.z * rel_pos.z);

    if (fchk > SQR(5000.f))
    {
        return;
    }

    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    bool alt;

    const NJS_POINT3* p_pos;

    if ( cwp->is_player )
    {
        const int chnum = PlayerCartSelected[cwp->player_num];

        alt = (chnum < 0);

        p_pos = &cwp->pos;
    }
    else
    {
        alt = false;

        p_pos = &tp->twp->pos;
    }

    njPushMatrixEx();
    {
        njTranslate(NULL, p_pos->x, p_pos->y + 0.01f - 2.0f, p_pos->z);

        njRotateZ(NULL, cwp->ang.z);
        njRotateX(NULL, cwp->ang.x);
        njRotateY(NULL, cwp->ang.y + cwp->angSlide - NJM_DEG_ANG(180.f));

        njRotateZ(NULL, cwp->ang2.z + cwp->ang3.z);
        njRotateX(NULL, cwp->ang2.x + cwp->ang3.x);
        njRotateY(NULL, cwp->ang2.y + cwp->ang3.y);

        NJS_CNK_OBJECT* const p_obj = CartObjectList[cwp->character][alt];

        switch ( cwp->character )
        {
            case CART_CAR_TAILS_SPECIAL:
            {
                njRotateY( NULL, NJM_DEG_ANG(90.f) );

//          [[fallthrough]];
            }
            case CART_CAR_ROUGE_SPECIAL:
            case CART_CAR_SONIC:
            case CART_CAR_KNUCKLES:
            case CART_CAR_TAILS:
            case CART_CAR_EGGMAN:
            case CART_CAR_SHADOW:
            case CART_CAR_ROUGE:
            {
                njCnkModDrawObject( p_obj );
                break;
            }
            default:
            {
                njScale( NULL, 5.0f, 1.0f, 5.0f );

                njCnkModDrawObject( object_shadow );
                break;
            }
        }
    }
    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}

/****** Hooks *****************************************************************************/
static mt_hookinfo HookInfoCourseDisplayDisplayer[1];
static void
courseDisplayDisplayerHook(task* tp)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    mtHookInfoCall( HookInfoCourseDisplayDisplayer, courseDisplayDisplayer(tp) );

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}

/****** Init ******************************************************************************/
void
CHS_CartInit(void)
{
    WriteJump(0x0061CB80, cartShadow);
    WriteCall(0x0061C60F, CreateNoStencilTexture);

    mtHookFunc(HookInfoCourseDisplayDisplayer, courseDisplayDisplayer, courseDisplayDisplayerHook);
}
