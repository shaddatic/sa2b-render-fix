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
#include <samt/sonic/c_colli.h>     /* core collision                                           */
#include <samt/sonic/score.h>       /* score and time                                           */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_ninja.h>               /* render fix ninja                                         */
#include <rf_njcnk.h>               /* ninja chunk draw                                         */
#include <rf_util.h>                /* switch displayer                                         */

/****** Self ************************************************************************************/
#include <rf_shadow/chs_internal.h> /* parent & siblings                                        */

/********************************/
/*  Structures                  */
/********************************/
/****** Car Info ********************************************************************************/
typedef struct 
{
    const char* name;
    f32         LODSwitch;
    NJS_TEXLIST* pTexlist;
    GJS_OBJECT* pObject;
    NJS_TEXLIST* pTexlistLOD;
    GJS_OBJECT* pObjectLOD;
    int a1;
    CCL_INFO* collip;
    int nbColli;
    float a5[8];
    int flags;
    GJS_OBJECT* obj2;
    int a7;
}
CAR_INFO;

/********************************/
/*  Game Refs                   */
/********************************/
/****** Model Reform ****************************************************************************/
#define ReformModifier              FUNC_PTR(void, __cdecl, (f32, f32, Angle3*), 0x005B44E0)

/****** Car Flag ********************************************************************************/
#define DisableCars                 DATA_REF(b32, 0x1AEDC40)

/****** Item Funcs ******************************************************************************/
#define ObjectCECar                 FUNC_PTR(void, __cdecl, (task*), 0x005DE4E0)
#define ObjectMSCar2                FUNC_PTR(void, __cdecl, (task*), 0x005B4850)

/****** Car Info ********************************************************************************/
#define stru_10D9810                DATA_ARY(CAR_INFO, 0x010D9810, [30])
#define stru_1195F80                DATA_ARY(CAR_INFO, 0x01195F80, [15])

/********************************/
/*  Source                      */
/********************************/
/****** Angle Turnover **************************************************************************/
static bool
IsCarFlipped(Angle3* pAng)
{
    size_t nb = 0;

    const Sangle x = pAng->x;

    if ( x > NJM_DEG_ANG(90.f) || x < NJM_DEG_ANG(-90.f) )
    {
        ++nb;
    }

    const Sangle z = pAng->z;

    if ( z > NJM_DEG_ANG(90.f) || z < NJM_DEG_ANG(-90.f) )
    {
        ++nb;
    }

    return (nb % 2);
}

/****** Shadow Modifier *************************************************************************/
static void
DrawCarShadow(f32 sizeX, f32 sizeZ, Angle3* pAng)
{
    ReformModifier(sizeX, sizeZ, pAng);

    NJS_CNK_MODEL* car_model = object_modmod_box->model;

    const f32 r = sqrtf((sizeX * sizeX) + (sizeZ * sizeZ));

    NJS_CNK_MODEL model = {
        .vlist  = (Sint32*)GlobalBuffer,
        .plist  = car_model->plist,
        .center = car_model->center,
        .r      = (r * 2) + car_model->r
    };

    OnControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);

    if ( IsCarFlipped(pAng) )
    {
        OnControl3D(NJD_CONTROL_3D_MIRROR_MODEL);
    }

    njCnkModDrawModel(&model);

    OffControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER|NJD_CONTROL_3D_MIRROR_MODEL);
}

static bool
PosInRange(NJS_POINT3* pPos, f32 maxRange, f32* pAnsDist)
{
    NJS_POINT3 p3;
    njCalcPoint(NULL, pPos, &p3);

    *pAnsDist = -p3.z;
    
    return -maxRange <= -p3.z;
}

/****** Displayers ******************************************************************************/
void
ObjectCarShadow_CE(task* tp)
{
    if (DisableCars)
        return;

    taskwk*   const twp   = tp->twp;
    CAR_INFO* const carip = &stru_10D9810[(int)(twp->scl.y + 0.1f) % 30];

    if (twp->btimer < 10 || (twp->btimer < 20 && (GameTimer & 0x1)))
        return;

    if (twp->smode < 0 || !carip)
        return;

    const f32 range = carip->pObject->model->r + 30.0f;

    f32 distance;

    if (!PosInRange(&twp->pos, range, &distance) || distance > 700.0f)
        return;

    njPushMatrixEx();
    {
        anywk* const carwp = TO_ANYWK(tp->mwp);

        const float trans_y = twp->pos.y + carwp[5].work.f[1] + 1.0f + carwp[6].work.f[2];

        njTranslate(NULL, twp->pos.x, trans_y, twp->pos.z);

        Angle3 ang = {
            .x = twp->ang.x + carwp[4].work.ul[1],
            .y = twp->ang.y + carwp[4].work.ul[2],
            .z = twp->ang.z + carwp[4].work.ul[3],
        };

        DrawCarShadow(carip->a5[0], carip->a5[2], &ang);
    }
    njPopMatrixEx();
}

void
ObjectCarShadow_MS(task* tp)
{
    if (DisableCars)
        return;

    taskwk* const twp = tp->twp;
    CAR_INFO* const carip = &stru_1195F80[(int)(twp->scl.y + 0.1f) % 15];

    if (twp->btimer < 10 || (twp->btimer < 20 && (GameTimer & 0x1)))
        return;

    if (twp->smode < 0 || !carip)
        return;

    const f32 range = carip->pObject->model->r + 30.0f;

    f32 distance;

    if (!PosInRange(&twp->pos, range, &distance) || distance > 700.0f)
        return;

    njPushMatrixEx();
    {
        anywk* const carwp = TO_ANYWK(tp->mwp);

        const float trans_y = twp->pos.y + carwp[2].work.f[3] + 1.0f + carwp[4].work.f[0];

        njTranslate(NULL, twp->pos.x, trans_y, twp->pos.z);

        Angle3 ang = {
            .x = twp->ang.x + carwp[1].work.ul[3],
            .y = twp->ang.y + carwp[2].work.ul[0],
            .z = twp->ang.z + carwp[2].work.ul[1],
        };

        DrawCarShadow(carip->a5[0], carip->a5[2], &ang);
    }
    njPopMatrixEx();
}

void
ObjectCarCrashShadow_CE(task* tp)
{
    taskwk*   const twp   = tp->twp;
    CAR_INFO* const carip = (CAR_INFO*)tp->awp;

    njPushMatrixEx();
    {
        njTranslateV( NULL, &twp->pos );

        DrawCarShadow( carip->a5[0], carip->a5[2], &twp->ang );
    }
    njPopMatrixEx();
}

void
ObjectCarCrashShadow_MS(task* tp)
{
    taskwk* const twp = tp->twp;
    CAR_INFO* const carip = (CAR_INFO*)tp->awp;

    njPushMatrixEx();
    {
        njTranslateV( NULL, &twp->pos );

        DrawCarShadow( carip->a5[0], carip->a5[2], &twp->ang );
    }
    njPopMatrixEx();
}

/****** Hooks ***********************************************************************************/
static mt_hookinfo ObjectCECarHookInfo[1];
void
ObjectCECarHook(task* tp)
{
    mtHookInfoCall( ObjectCECarHookInfo, ObjectCECar(tp) );

    /** If successfully loaded **/
    if (tp->mwp)
        tp->disp_shad = ObjectCarShadow_CE;
}

static mt_hookinfo ObjectMSCar2HookInfo[1];
void
ObjectMSCar2Hook(task* tp)
{
    mtHookInfoCall( ObjectMSCar2HookInfo, ObjectMSCar2(tp) );

    /** If successfully loaded **/
    if (tp->mwp)
        tp->disp_shad = ObjectCarShadow_MS;
}

/****** Init ************************************************************************************/
void
CHS_CarInit(void)
{
    /** City Escape **/
    mtHookFunc(ObjectCECarHookInfo, ObjectCECar, ObjectCECarHook);

    WriteJump(0x005E2930, ObjectCarCrashShadow_CE);
    KillCall(0x005E150F); // SetStencilInfo

    /** Mission Street **/
    mtHookFunc(ObjectMSCar2HookInfo, ObjectMSCar2, ObjectMSCar2Hook);

    WriteJump(0x005B75C0, ObjectCarCrashShadow_MS);
    KillCall(0x005B6148); // SetStencilInfo

    /** Leftover DC Code **/
    KillCall(0x005B588A);
    KillCall(0x005B5944);
    KillCall(0x005B7422);
    KillCall(0x005B74DA);
}
