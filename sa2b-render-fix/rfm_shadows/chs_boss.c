#include <sa2b/core.h>
#include <sa2b/writemem.h>
#include <sa2b/funchook.h>
#include <sa2b/writeop.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/sonic/task.h>
#include <sa2b/sonic/move.h>
#include <sa2b/sonic/motion.h>
#include <sa2b/sonic/njctrl.h>
#include <sa2b/sonic/debug.h>

/** Render Fix **/
#include <rf_file.h>
#include <rf_draw.h>
#include <rf_util.h>

#define GET_BOSSWK(_tp)     ((BOSSWK*)_tp->awp)

typedef struct bosswk
{
    char gap0[8];
    MOVE_WORK* move_work;
    MOTION_CTRL* pMtnCtrl;
    void* pOtherWork;
    char gap2[14];
}
BOSSWK;

#define BossBogyGlassCheapShadow    FUNC_PTR(void, __cdecl, (int), 0x00613F20)

static NJS_CNK_OBJECT* object_b_bigbogy_mod;

#define motion_b_bigbogy_mod        DATA_ARY(NJS_MOTION, 0x010131E4, [1])

static void
BossBogyDisplayerMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;
    BOSSWK* const bwp = GET_BOSSWK(tp);
    MOVE_WORK* const mwp = GET_MOVE_WORK(tp);

    ANYWK* const unk = (ANYWK*)bwp->pOtherWork;

    if (unk->work.ub[1] == 2)
    {
        njPushMatrixEx();

        njTranslateEx(&twp->pos);
        njRotateY(NULL, twp->ang.z);
        njRotateX(NULL, twp->ang.x);
        njScale(NULL, twp->scl.x, twp->scl.x, twp->scl.x);

        njCnkModDrawMotion(object_b_bigbogy_mod, motion_b_bigbogy_mod, mwp->BoundFriction);

        njPopMatrixEx();
    }

    BossBogyGlassCheapShadow(unk->work.ul[3]);
}

static NJS_CNK_OBJECT* object_b_grobo_body_mod;
static NJS_CNK_OBJECT* object_b_grobo_foot_mod;

#define BossBigFootBodyPos          DATA_REF(NJS_POINT3, 0x01A27E84)
#define BossBigFootLeftFootPos      DATA_REF(NJS_POINT3, 0x01A27F44)
#define BossBigFootRightFootPos     DATA_REF(NJS_POINT3, 0x01A27EFC)

static void
BossBigFootDrawMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;

    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    njTranslateEx(&BossBigFootBodyPos);
    njRotateY(NULL, twp->ang.y + 0x4000);
    njCnkModDrawObject(object_b_grobo_body_mod);

    njPopMatrixEx();
    njPushMatrixEx();

    njTranslateEx(&BossBigFootLeftFootPos);
    njRotateY(NULL, twp->ang.y + 0x4000);
    njCnkModDrawObject(object_b_grobo_foot_mod);

    njPopMatrixEx();
    njPushMatrixEx();

    njTranslateEx(&BossBigFootRightFootPos);
    njRotateY(NULL, twp->ang.y + 0xC000);
    njCnkModDrawObject(object_b_grobo_foot_mod);

    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}

#define BossBigFootInvMatrix        DATA_REF(NJS_MATRIX, 0x01A27E90)
#define BossBigFootInvTransMatrix   DATA_REF(NJS_MATRIX, 0x01A27E54)

static void
BossBigFootDisplayerMod(TASK* tp)
{
    TASKWK*    const twp = tp->twp;
    MOVE_WORK* const mwp = GET_MOVE_WORK(tp);
    BOSSWK*    const bwp = GET_BOSSWK(tp);

    MOTION_CTRL* mtn_ctrl = bwp->pMtnCtrl;

    njGetMatrix(&BossBigFootInvMatrix);
    njInvertMatrix(&BossBigFootInvMatrix);

    njCnkSetMotionCallback((void*)0x005D0330);

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);

    if (twp->flag & 0x01)
    {
        njTranslate(NULL, 0.0f, 35.0f, 0.0f);
        njRotateZ(NULL, twp->ang.z);
        njRotateX(NULL, twp->ang.x);
    }
    else
    {
        njTranslate(NULL, 0.0f, njSin(mwp->Phase.y) * 0.9f + 35.0f, 0.0f);
        njRotateZ(NULL, twp->ang.z - (Angle)(njSin(mwp->Phase.z) * 1.5f * -182.0444488525391f));
        njRotateX(NULL, twp->ang.x - (Angle)(njSin(mwp->Phase.x) * 0.8f * -182.0444488525391f));
    }

    njTranslate(NULL, 0.0f, -35.0f, 0.0f);

    njGetMatrix(&BossBigFootInvTransMatrix);
    njInvertMatrix(&BossBigFootInvTransMatrix);

    njRotateY(NULL, 0x4000);

    AnimateMotion((void*)0x01116FC8, mtn_ctrl);

    njPopMatrixEx();

    njCnkSetMotionCallback(NULL);

    BossBigFootDrawMod(tp);
}

#define BossHotShotBodyPos          DATA_REF(NJS_POINT3, 0x01A27D34)
#define BossHotShotLeftFootPos      DATA_REF(NJS_POINT3, 0x01A27E00)
#define BossHotShotRightFootPos     DATA_REF(NJS_POINT3, 0x01A27DB8)

static void
BossHotShotDrawMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;

    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    njTranslateEx(&BossHotShotBodyPos);
    njRotateY(NULL, twp->ang.y + 0x4000);
    njCnkModDrawObject(object_b_grobo_body_mod);

    njPopMatrixEx();
    njPushMatrixEx();

    njTranslateEx(&BossHotShotLeftFootPos);
    njRotateY(NULL, twp->ang.y + 0x4000);
    njCnkModDrawObject(object_b_grobo_foot_mod);

    njPopMatrixEx();
    njPushMatrixEx();

    njTranslateEx(&BossHotShotRightFootPos);
    njRotateY(NULL, twp->ang.y + 0xC000);
    njCnkModDrawObject(object_b_grobo_foot_mod);

    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}

#define BossHotShotInvMatrix        DATA_REF(NJS_MATRIX, 0x01A27D40)
#define BossHotShotInvTransMatrix   DATA_REF(NJS_MATRIX, 0x01A27D04)

static void
BossHotShotDisplayerMod(TASK* tp)
{
    TASKWK*    const twp = tp->twp;
    MOVE_WORK* const mwp = GET_MOVE_WORK(tp);
    BOSSWK*    const bwp = GET_BOSSWK(tp);

    MOTION_CTRL* mtn_ctrl = bwp->pMtnCtrl;

    njGetMatrix(&BossHotShotInvMatrix);
    njInvertMatrix(&BossHotShotInvMatrix);

    njCnkSetMotionCallback((void*)0x005CB840);

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);

    if (twp->flag & 0x01)
    {
        njTranslate(NULL, 0.0f, 35.0f, 0.0f);
        njRotateZ(NULL, twp->ang.z);
        njRotateX(NULL, twp->ang.x);
    }
    else
    {
        njTranslate(NULL, 0.0f, njSin(mwp->Phase.y) * 0.9f + 35.0f, 0.0f);
        njRotateZ(NULL, twp->ang.z - (Angle)(njSin(mwp->Phase.z) * 1.5f * -182.0444488525391f));
        njRotateX(NULL, twp->ang.x - (Angle)(njSin(mwp->Phase.x) * 0.8f * -182.0444488525391f));
    }

    njTranslate(NULL, 0.0f, -35.0f, 0.0f);

    njGetMatrix(&BossHotShotInvTransMatrix);
    njInvertMatrix(&BossHotShotInvTransMatrix);

    njRotateY(NULL, 0x4000);

    AnimateMotion((void*)0x011320F8, mtn_ctrl);

    njPopMatrixEx();

    njCnkSetMotionCallback(NULL);

    BossHotShotDrawMod(tp);
}

static NJS_CNK_OBJECT* object_b_fdog_mod;

#define BossFlyingDogBodyPos    DATA_REF(NJS_POINT3, 0x01A27FBC)

static void
BossFlyingDogDrawMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;

    njPushMatrixEx();

    njTranslateEx(&BossFlyingDogBodyPos);
    njRotateY(NULL, twp->ang.y + 0x4000);

    njCnkModDrawObject(object_b_fdog_mod);

    njPopMatrixEx();
}

#define BossFlyingDogInvMatrix        DATA_REF(NJS_MATRIX, 0x01A27FC8)
#define BossFlyingDogInvTransMatrix   DATA_REF(NJS_MATRIX, 0x01A27F8C)

static void
BossFlyingDogDispMod(TASK* tp)
{
    TASKWK*    const twp = tp->twp;
    MOVE_WORK* const mwp = GET_MOVE_WORK(tp);
    BOSSWK*    const bwp = GET_BOSSWK(tp);

    MOTION_CTRL* mtn_ctrl = bwp->pMtnCtrl;

    njGetMatrix(&BossFlyingDogInvMatrix);
    njInvertMatrix(&BossFlyingDogInvMatrix);

    njCnkSetMotionCallback((void*)0x005D3D20);

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);

    njTranslate(NULL, 0.0f, njSin(mwp->Phase.y) * 0.5f + 35.0f, 0.0f);
    njRotateZ(NULL, twp->ang.z - (Angle)(njSin(mwp->Phase.z) * 0.75f * -182.0444488525391f));
    njRotateX(NULL, twp->ang.x - (Angle)(njSin(mwp->Phase.x) * 0.4f * -182.0444488525391f));

    njTranslate(NULL, 0.0f, -35.0f, 0.0f);

    njGetMatrix(&BossFlyingDogInvTransMatrix);
    njInvertMatrix(&BossFlyingDogInvTransMatrix);

    njRotateY(NULL, 0x4000);

    AnimateMotion((void*)0x011004E8, mtn_ctrl);

    njPopMatrixEx();

    njCnkSetMotionCallback(NULL);

    BossFlyingDogDrawMod(tp);
}

static NJS_CNK_OBJECT* object_b_grobo_missile_mod;

static void
GRoboMissileDispMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;

    if (twp->mode != 1)
        return;

    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    njTranslate(NULL, twp->pos.x, twp->pos.y - 0.8f, twp->pos.z);
    njRotateY(NULL, twp->ang.y);
    njRotateZ(NULL, twp->ang.z);
    njRotateX(NULL, twp->ang.x);

    njRotateY(NULL, 0x4000);

    njCnkModDrawObject(object_b_grobo_missile_mod);

    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}

__declspec(naked)
static void
__GRoboMissileMovHook(void)
{
    __asm
    {
        mov dword ptr[esi+14h], 005D6AA0h
        mov dword ptr[esi+2Ch], offset GRoboMissileDispMod
        retn
    }
}

static void
BossLastEnergyDispMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;

    if (twp->mode != 3)
        return;

    float pos_y = twp->pos.y - 40.0f;
    float scl;

    /** I'm aware this is logically incorrect,
        this is just how it's written. Idk. **/
    if (pos_y >= 10.2f)
    {
        if (pos_y <= 0.0f)
            scl = 40.0f - -pos_y * twp->scl.x;
        else
            scl = 40.f * twp->scl.x;
    }
    else
    {
        pos_y = 10.2f;
        scl = 40.f * twp->scl.x;
    }

    njPushMatrixEx();

    njTranslate(NULL, twp->pos.x, pos_y, twp->pos.z);
    njScale(NULL, scl, 1.0f, scl);

    DrawBasicShadow();

    njPopMatrixEx();
}

__declspec(naked)
static void
__BossLastEnergyMovHook(void)
{
    __asm
    {
        mov dword ptr[eax+1Ch], 00523070h
        mov dword ptr[eax+2Ch], offset BossLastEnergyDispMod
        retn
    }
}

void* CreateNoStencilTexture(void);

void
CHS_BossInit(void)
{
    /** King Boom Boo **/
    WriteJump(0x006133C0, BossBogyDisplayerMod);
    WriteCall(0x0060B5EE, CreateNoStencilTexture); // Kill GetStencilInfo

    WriteCall(0x00613FD0, DrawBasicShadow); // Sand Timer
    KillCall(0x00612F70);

    object_b_bigbogy_mod = RF_ChunkLoadObjectFile("b_bigbogy_mod");

    /** Big Foot **/
    WriteJump(0x005D0B30, BossBigFootDisplayerMod);
    WriteCall(0x005CC509, CreateNoStencilTexture); // Kill GetStencilInfo

    /** Hot Shot **/
    WriteJump(0x005CC110, BossHotShotDisplayerMod);
    WriteCall(0x005C7329, CreateNoStencilTexture); // Kill GetStencilInfo

    object_b_grobo_body_mod = RF_ChunkLoadObjectFile("b_grobo_body_mod");
    object_b_grobo_foot_mod = RF_ChunkLoadObjectFile("b_grobo_foot_mod");

    /** Flying Dog **/
    WriteJump(0x005D4410, BossFlyingDogDispMod);
    WriteCall(0x005D0F86, CreateNoStencilTexture); // Kill GetStencilInfo

    object_b_fdog_mod = RF_ChunkLoadObjectFile("b_fdog_mod");

    /** Gun Robot Missiles **/
    WriteCallToMovDwordPtr(0x005D6393, __GRoboMissileMovHook);

    object_b_grobo_missile_mod = RF_ChunkLoadObjectFile("b_grobo_missile_mod");

    /** Biolizard Energy Balls **/
    WriteCallToMovDwordPtr(0x00523743, __BossLastEnergyMovHook);
}
