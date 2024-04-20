#include <sa2b/core.h>
#include <sa2b/memutil.h>
#include <sa2b/funchook.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/src/task.h>
#include <sa2b/src/debug.h>
#include <sa2b/src/c_colli.h>
#include <sa2b/src/score.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_file.h>
#include <rf_draw.h>
#include <rf_util.h>

#define GlobalBuffer        DataAry(int, 0x01DEFE20, [1])

#define ModTurnVertex       FuncPtr(void, __cdecl, (float32_t, float32_t, Angle3*), 0x005B44E0)

#define object_car_mod      DataAry(NJS_CNK_OBJECT, 0x00B4D254, [1])

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

    njCnkModDrawModel(&model);
}

typedef struct 
{
    const char* name;
    float32_t   LODSwitch;
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

#define DisableCars     DataRef(bool32_t, 0x1AEDC40)

static bool
PosInRange(NJS_POINT3* pPos, float32_t maxRange, float32_t* pAnsDist)
{
    NJS_POINT3 p3;
    njCalcPoint(NULL, pPos, &p3);

    *pAnsDist = -p3.z;
    
    return -maxRange <= -p3.z;
}

#define stru_10D9810    DataAry(CAR_INFO, 0x010D9810, [30])

static void
ObjectCECarDisplayerMod(TASK* tp)
{
    if (DisableCars)
        return;

    TASKWK*   const twp   = tp->twp;
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

    ANYWK* const carwp = TO_ANYWK(tp->mwp);

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

#define ObjectCECar         FuncPtr(void, __cdecl, (TASK*), 0x005DE4E0)

static hook_info* ObjectCECarHookInfo;
void
ObjectCECarHook(TASK* tp)
{
    FuncHookCall( ObjectCECarHookInfo, ObjectCECar(tp) );

    /** If successfully loaded **/
    if (tp->mwp)
        tp->disp_shad = ObjectCECarDisplayerMod;
}

static void
ObjectCECarCrashDisplayerMod(TASK* tp)
{
    TASKWK*   const twp   = tp->twp;
    CAR_INFO* const carip = (CAR_INFO*)tp->awp;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    DrawCarShadow(carip->a5[0], carip->a5[2], &twp->ang);

    njPopMatrixEx();
}

#define stru_1195F80    DataAry(CAR_INFO, 0x01195F80, [15])

static void
ObjectMSCarDisplayerMod(TASK* tp)
{
    if (DisableCars)
        return;

    TASKWK* const twp = tp->twp;
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

    ANYWK* const carwp = TO_ANYWK(tp->mwp);

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

#define ObjectMSCar2        FuncPtr(void, __cdecl, (TASK*), 0x005B4850)

static hook_info* ObjectMSCar2HookInfo;
void
ObjectMSCar2Hook(TASK* tp)
{
    FuncHookCall( ObjectMSCar2HookInfo, ObjectMSCar2(tp) );

    /** If successfully loaded **/
    if (tp->mwp)
        tp->disp_shad = ObjectMSCarDisplayerMod;
}

static void
ObjectMSCarCrashDisplayerMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;
    CAR_INFO* const carip = (CAR_INFO*)tp->awp;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    DrawCarShadow(carip->a5[0], carip->a5[2], &twp->ang);

    njPopMatrixEx();
}

void
CHS_CarInit()
{
    /** City Escape **/
    ObjectCECarHookInfo = FuncHook(ObjectCECar, ObjectCECarHook);

    WriteJump(0x005E2930, ObjectCECarCrashDisplayerMod);
    KillCall(0x005E150F); // SetStencilInfo

    /** Mission Street **/
    ObjectMSCar2HookInfo = FuncHook(ObjectMSCar2, ObjectMSCar2Hook);

    WriteJump(0x005B75C0, ObjectMSCarCrashDisplayerMod);
    KillCall(0x005B6148); // SetStencilInfo

    /** Leftover DC Code **/
    KillCall(0x005B588A);
    KillCall(0x005B5944);
    KillCall(0x005B7422);
    KillCall(0x005B74DA);
}
