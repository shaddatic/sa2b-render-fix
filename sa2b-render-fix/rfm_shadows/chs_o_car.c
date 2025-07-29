#include <samt/core.h>
#include <samt/writemem.h>
#include <samt/funchook.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Source **/
#include <samt/sonic/task.h>
#include <samt/sonic/debug.h>
#include <samt/sonic/c_colli.h>
#include <samt/sonic/score.h>
#include <samt/sonic/njctrl.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_file.h>
#include <rf_draw.h>
#include <rf_util.h>
#include <rf_renderstate.h>

#define GlobalBuffer        DATA_ARY(int, 0x01DEFE20, [1])

#define ModTurnVertex       FUNC_PTR(void, __cdecl, (f32, f32, Angle3*), 0x005B44E0)

#define object_car_mod      DATA_ARY(NJS_CNK_OBJECT, 0x00B4D254, [1])

static bool
IsCarFlipped(Angle3* pAng)
{
    size_t nb = 0;

    const Sangle x = pAng->x;

    if (x > 0x4000 || x < -0x4000)
        ++nb;

    const Sangle z = pAng->z;

    if (z > 0x4000 || z < -0x4000)
        ++nb;

    return (nb % 2);
}

static void
DrawCarShadow(float sizeX, float sizeZ, Angle3* pAng)
{
    ModTurnVertex(sizeX, sizeZ, pAng);

    NJS_CNK_MODEL* car_model = object_car_mod->model;

    const float r = sqrtf((sizeX * sizeX) + (sizeZ * sizeZ));

    NJS_CNK_MODEL model = {
        .vlist  = (Sint32*)GlobalBuffer,
        .plist  = car_model->plist,
        .center = car_model->center,
        .r      = (r * 2) + car_model->r
    };

    if ( IsCarFlipped(pAng) )
    {
        OnControl3D(NJD_CONTROL_3D_MIRROR_MODEL);
    }

    njCnkModDrawModel(&model);

    OffControl3D(NJD_CONTROL_3D_MIRROR_MODEL);
}

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

#define DisableCars     DATA_REF(b32, 0x1AEDC40)

static bool
PosInRange(NJS_POINT3* pPos, f32 maxRange, f32* pAnsDist)
{
    NJS_POINT3 p3;
    njCalcPoint(NULL, pPos, &p3);

    *pAnsDist = -p3.z;
    
    return -maxRange <= -p3.z;
}

#define stru_10D9810    DATA_ARY(CAR_INFO, 0x010D9810, [30])

static void
ObjectCECarDisplayerMod(task* tp)
{
    if (DisableCars)
        return;

    taskwk*   const twp   = tp->twp;
    CAR_INFO* const carip = &stru_10D9810[(int)(twp->scl.y + 0.1f) % 30];

    if (twp->btimer < 10 || (twp->btimer < 20 && (GameTimer & 0x1)))
        return;

    if (twp->smode < 0 || !carip)
        return;

    const float range = carip->pObject->model->r + 30.0f;

    float distance;
  
    if (!PosInRange(&twp->pos, range, &distance) || distance > 700.0f)
        return;

    njPushMatrixEx();

    anywk* const carwp = TO_ANYWK(tp->mwp);

    const float trans_y = twp->pos.y + carwp[5].work.f[1] + 1.0f + carwp[6].work.f[2];

    njTranslate(NULL, twp->pos.x, trans_y, twp->pos.z);

    Angle3 ang = {
        .x = twp->ang.x + carwp[4].work.ul[1],
        .y = twp->ang.y + carwp[4].work.ul[2],
        .z = twp->ang.z + carwp[4].work.ul[3],
    };

    DrawCarShadow(carip->a5[0], carip->a5[2], &ang);

    njPopMatrixEx();
}

#define ObjectCECar         FUNC_PTR(void, __cdecl, (task*), 0x005DE4E0)

static mt_hookinfo ObjectCECarHookInfo[1];
void
ObjectCECarHook(task* tp)
{
    FuncHookCall( ObjectCECarHookInfo, ObjectCECar(tp) );

    /** If successfully loaded **/
    if (tp->mwp)
        tp->disp_shad = ObjectCECarDisplayerMod;
}

static void
ObjectCECarCrashDisplayerMod(task* tp)
{
    taskwk*   const twp   = tp->twp;
    CAR_INFO* const carip = (CAR_INFO*)tp->awp;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    DrawCarShadow(carip->a5[0], carip->a5[2], &twp->ang);

    njPopMatrixEx();
}

#define stru_1195F80    DATA_ARY(CAR_INFO, 0x01195F80, [15])

static void
ObjectMSCarDisplayerMod(task* tp)
{
    if (DisableCars)
        return;

    taskwk* const twp = tp->twp;
    CAR_INFO* const carip = &stru_1195F80[(int)(twp->scl.y + 0.1f) % 15];

    if (twp->btimer < 10 || (twp->btimer < 20 && (GameTimer & 0x1)))
        return;

    if (twp->smode < 0 || !carip)
        return;

    const float range = carip->pObject->model->r + 30.0f;

    float distance;

    if (!PosInRange(&twp->pos, range, &distance) || distance > 700.0f)
        return;

    njPushMatrixEx();

    anywk* const carwp = TO_ANYWK(tp->mwp);

    const float trans_y = twp->pos.y + carwp[2].work.f[3] + 1.0f + carwp[4].work.f[0];

    njTranslate(NULL, twp->pos.x, trans_y, twp->pos.z);

    Angle3 ang = {
        .x = twp->ang.x + carwp[1].work.ul[3],
        .y = twp->ang.y + carwp[2].work.ul[0],
        .z = twp->ang.z + carwp[2].work.ul[1],
    };

    DrawCarShadow(carip->a5[0], carip->a5[2], &ang);

    njPopMatrixEx();
}

#define ObjectMSCar2        FUNC_PTR(void, __cdecl, (task*), 0x005B4850)

static mt_hookinfo ObjectMSCar2HookInfo[1];
void
ObjectMSCar2Hook(task* tp)
{
    FuncHookCall( ObjectMSCar2HookInfo, ObjectMSCar2(tp) );

    /** If successfully loaded **/
    if (tp->mwp)
        tp->disp_shad = ObjectMSCarDisplayerMod;
}

static void
ObjectMSCarCrashDisplayerMod(task* tp)
{
    taskwk* const twp = tp->twp;
    CAR_INFO* const carip = (CAR_INFO*)tp->awp;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    DrawCarShadow(carip->a5[0], carip->a5[2], &twp->ang);

    njPopMatrixEx();
}

void
CHS_CarInit(void)
{
    /** City Escape **/
    FuncHook(ObjectCECarHookInfo, ObjectCECar, ObjectCECarHook);

    WriteJump(0x005E2930, ObjectCECarCrashDisplayerMod);
    KillCall(0x005E150F); // SetStencilInfo

    /** Mission Street **/
    FuncHook(ObjectMSCar2HookInfo, ObjectMSCar2, ObjectMSCar2Hook);

    WriteJump(0x005B75C0, ObjectMSCarCrashDisplayerMod);
    KillCall(0x005B6148); // SetStencilInfo

    /** Leftover DC Code **/
    KillCall(0x005B588A);
    KillCall(0x005B5944);
    KillCall(0x005B7422);
    KillCall(0x005B74DA);
}
