#include <sa2b/core.h>
#include <sa2b/memory.h>
#include <sa2b/memutil.h>
#include <sa2b/funchook.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Utility **/
#include <sa2b/util/devutil.h>

/** Source **/
#include <sa2b/src/task.h>
#include <sa2b/src/debug.h>

/** Chao **/
#define SAMT_INCLUDE_FUNC_PTRS
#include <sa2b/src/chao/chao.h>
#include <sa2b/src/chao/al_egg.h>
#include <sa2b/src/chao/al_world.h>
#include <sa2b/src/chao/alo_growtree.h>
#include <sa2b/src/chao/alo_chaosdrive.h>
#include <sa2b/src/chao/alo_obake_head.h>
#include <sa2b/src/chao/alo_seed.h>
#include <sa2b/src/chao/alo_fruit.h>
#include <sa2b/src/chao/al_minimal.h>
#undef  SAMT_INCLUDE_FUNC_PTRS
#include <sa2b/src/chao/al_chao_info.h>
#include <sa2b/src/chao/al_stage.h>
#include <sa2b/src/chao/al_global.h>
#include <sa2b/src/chao/al_misc.h>

/** AL Toys **/
#define SAMT_INCLUDE_FUNC_PTRS
#include <sa2b/src/chao/al_toy/alo_ball.h>
#include <sa2b/src/chao/al_toy/alo_box.h>
#include <sa2b/src/chao/al_toy/alo_horse.h>
#include <sa2b/src/chao/al_toy/alo_radicase.h>
#include <sa2b/src/chao/al_toy/alo_tv.h>
#undef  SAMT_INCLUDE_FUNC_PTRS

/** Render Fix **/
#include <rf_draw.h>
#include <rf_file.h>
#include <rf_util.h>

#define SHAPE_FLG_SHADOW    (0b0000'0000'0000'1000)

#define CHAO_FLG_DRAW       (0b0000'0010'0000'0000)
#define CHAO_FLG_INRANGE    (0b0001'0000'0000'0000)

NJS_CNK_MODEL* model_al_shadow;

void
AL_ShadowDraw(void)
{
    njCnkModDrawModel(model_al_shadow);
}

static void
ChaoDisplayerMod(TASK* tp)
{
    CHAOWK*         const cwp = GET_CHAOWK(tp);
    ALW_ENTRY_WORK* const ewp = GET_ALW_ENTRY_WORK(tp);

    if (!AL_IsOnScreen3(tp, 5.2f, 4.5f, 2.9f) || (cwp->ChaoFlag & CHAO_FLG_DRAW) == 0)
        return;

    const float cam_dist = ewp ? ewp->CamDist : 300.f;

    if (AL_GetStageNumber() == CHAO_STG_RACE)
    {
        njPushMatrixEx();

        njTranslateEx(&cwp->Shape.HeadPos);
        njRotateY(NULL, cwp->ang.y);
        njScale(NULL, 1.6f, 0.7f, 1.5f);

        AL_ShadowDraw();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&cwp->Shape.BodyPos);
        njRotateY(NULL, cwp->ang.y);
        njScale(NULL, 1.4f, 0.7f, 1.4f);

        AL_ShadowDraw();

        njPopMatrixEx();

        return;
    }

    if (ChaoGlobal.CamDistShadowCutLev4 <= cam_dist)
        return;

    njPushMatrixEx(); // Head

    njTranslateEx(&cwp->Shape.HeadPos);
    njRotateY(NULL, cwp->ang.y);
    njScale(NULL, 1.6f, 0.7f, 1.5f);

    AL_ShadowDraw();

    njPopMatrixEx();

    if (ChaoGlobal.CamDistShadowCutLev2 <= cam_dist)
        return;

    njPushMatrixEx(); // Left Hand

    if (cwp->Shape.Flag & SHAPE_FLG_SHADOW)
        cwp->Shape.LeftHandPos.y = cwp->pos.y + 0.01f;

    njTranslateEx(&cwp->Shape.LeftHandPos);
    njRotateY(NULL, cwp->ang.y);
    njScale(NULL, 0.65f, 0.60f, 0.65f);

    AL_ShadowDraw();

    njPopMatrixEx();
    njPushMatrixEx(); // Right Hand

    if (cwp->Shape.Flag & SHAPE_FLG_SHADOW)
        cwp->Shape.RightHandPos.y = cwp->pos.y + 0.01f;

    njTranslateEx(&cwp->Shape.RightHandPos);
    njRotateY(NULL, cwp->ang.y);
    njScale(NULL, 0.65f, 0.60f, 0.65f);

    AL_ShadowDraw();

    njPopMatrixEx();

    if (ChaoGlobal.CamDistShadowCutLev1 <= cam_dist)
        return;

    njPushMatrixEx(); // Body

    njTranslateEx(&cwp->Shape.BodyPos);
    njRotateY(NULL, cwp->ang.y);
    njScale(NULL, 1.4f, 0.7f, 1.4f);

    AL_ShadowDraw();

    njPopMatrixEx();

    /** If not ghost body **/
    if (!cwp->pParamGC->body.ObakeBody)
    {
        njPushMatrixEx(); // Left Foot

        njTranslateEx(&cwp->Shape.LeftFootPos);
        njRotateY(NULL, cwp->ang.y);
        njScale(NULL, 0.6f, 0.6f, 0.9f);

        AL_ShadowDraw();

        njPopMatrixEx();
        njPushMatrixEx(); // Right Foot

        njTranslateEx(&cwp->Shape.RightFootPos);
        njRotateY(NULL, cwp->ang.y);
        njScale(NULL, 0.6f, 0.6f, 0.9f);

        AL_ShadowDraw();

        njPopMatrixEx();
    }

    njPushMatrixEx(); // Honbu/Icon

    if (cwp->Shape.Flag & SHAPE_FLG_SHADOW)
    {
        njTranslate(NULL,
            cwp->Icon.Lower.Pos.x,
            cwp->pos.y + 0.001f,
            cwp->Icon.Lower.Pos.z
        );
    }
    else
        njTranslateEx(&cwp->Icon.Lower.Pos);


    njRotateY(NULL, cwp->ang.y);
    njScale(NULL, 0.5f, 0.7f, 0.5f);

    AL_ShadowDraw();

    njPopMatrixEx();
}

static hook_info* HookInfoCreateChaoExtra;
static TASK*
CreateChaoExtraHook(CHAO_PARAM_GC* pParamGC, bool32_t IsParamCopy, AL_SHAPE_ELEMENT* pElement, NJS_POINT3* pPos, Angle angy)
{
    TASK* tp;

    FuncHookCall(HookInfoCreateChaoExtra, tp = CreateChaoExtra(pParamGC, IsParamCopy, pElement, pPos, angy));

    if (!tp)
        return NULL;

    if (!tp->disp_shad)
        tp->disp_shad = ChaoDisplayerMod;

    return tp;
}

static const Angle LeafRotList[11] = { 0x2000, 0x3800, 0x5000, 0x4B00 };
static const float LeafAdjList[11] = { 7.7f, 7.3f, 7.8f, 7.1f };
static const float LeafSclList[11] = { 3.0f, 3.0f, 4.0f, 4.0f };

static void
ALO_GrowTreeDisplayerMod(TASK* tp)
{
    TREE_WORK* const twp = GET_TREE_WORK(tp);

    if (twp->state == TREE_ST_LOCAL)
    {
        if (twp->pShadowObject)
            return;

        NJS_POINT3 trans;

        njPushMatrix(&_nj_unit_matrix_);

        njTranslateEx(&twp->pos);
        njRotateY(NULL, twp->TouchAngle);
        njRotateX(NULL, twp->RollAngle);
        njRotateY(NULL, -twp->TouchAngle);
        njRotateY(NULL, twp->ang.y);
        njTranslate(NULL, 0.0f, 20.0f, 0.0f);

        njGetTranslation(NULL, &trans);

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&trans);
        njRotateY(NULL, twp->ang.y);

        for (int i = 0; i < 4; ++i)
        {
            njRotateY(NULL, LeafRotList[i]);

            njPushMatrixEx();

            const float leaf_width = (twp->LeafWidth * 0.15f);
            const float scl_z = njSin(LeafPhaseList[i] + twp->LeafRotAng) * leaf_width + LeafAdjList[i];

            njScale(NULL, LeafSclList[i], 2.0f, scl_z);
            njTranslate(NULL, 0.0f, 0.0f, 0.85f);

            AL_ShadowDraw();

            njPopMatrixEx();
        }

        njPopMatrixEx();
    }
    else if (twp->mode > MD_ADULT)
    {
        NJS_POINT3 trans;

        njPushMatrix(&_nj_unit_matrix_);

        njTranslateEx(&twp->pos);
        njRotateY(NULL, twp->TouchAngle);
        njRotateX(NULL, twp->RollAngle);
        njRotateY(NULL, -twp->TouchAngle);
        njRotateY(NULL, twp->ang.y);
        njTranslate(NULL, 0.0f, 20.0f, 0.0f);

        njGetTranslation(NULL, &trans);

        njPopMatrixEx();
        njPushMatrixEx();

        /** I'm aware that this won't work, 
            this is how it is **/
        njScale(NULL, 3.0f, 2.0f, 3.0f);
        njTranslate(NULL, 0.0f, 0.0f, 0.85f);

        AL_ShadowDraw();

        njPopMatrixEx();
    }
}

static hook_info* HookInfoALO_GrowTreeCreate;
static TASK*
ALO_GrowTreeCreateHook(NJS_POINT3* pPos, TREE_SAVE_INFO* pInfo)
{
    TASK* tp;

    FuncHookCall( HookInfoALO_GrowTreeCreate, tp = ALO_GrowTreeCreate(pPos, pInfo) );

    if (!tp)
        return NULL;

    tp->disp_shad = ALO_GrowTreeDisplayerMod;

    return tp;
}

static void
ALO_RaceTreeDisplayerMod(TASK* tp)
{
    TREE_WORK* const twp = GET_TREE_WORK(tp);

    ___NOTE("Consider maybe making this a feature?");
    if (false)
    {
        njPushMatrixEx();

        njTranslateEx(&twp->pos);
        njRotateY(NULL, twp->ang.y);
        njTranslate(NULL, 0.0f, 0.5f, 0.0f);
        njScale(NULL, 1.8f, 1.0f, 1.8f);

        AL_ShadowDraw();

        njPopMatrixEx();
        return;
    }

    NJS_POINT3 trans;

    njPushMatrix(&_nj_unit_matrix_);

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->TouchAngle);
    njRotateX(NULL, twp->RollAngle);
    njRotateY(NULL, -twp->TouchAngle);
    njRotateY(NULL, twp->ang.y);
    njTranslate(NULL, 0.0f, 20.0f, 0.0f);

    njGetTranslation(NULL, &trans);

    njPopMatrixEx();
    njPushMatrixEx();

    njTranslateEx(&trans);
    njRotateY(NULL, twp->ang.y);

    for (int i = 0; i < 4; ++i)
    {
        njRotateY(NULL, LeafRotList[i]);

        njPushMatrixEx();

        const float leaf_width = (twp->LeafWidth * 0.15f);
        const float scl_z = njSin(LeafPhaseList[i] + twp->LeafRotAng) * leaf_width + LeafAdjList[i];

        njScale(NULL, LeafSclList[i], 2.0f, scl_z);
        njTranslate(NULL, 0.0f, 0.0f, 0.85f);

        AL_ShadowDraw();

        njPopMatrixEx();
    }

    njPopMatrixEx();
}

#define ALO_RaceTree        FuncPtr(void, __cdecl, (TASK*), 0x00537E70)

static hook_info* HookInfoALO_RaceTree;
static void
ALO_RaceTreeHook(TASK* tp)
{
    FuncHookCall( HookInfoALO_RaceTree, ALO_RaceTree(tp) );

    tp->disp_shad = ALO_RaceTreeDisplayerMod;
}

static void
AL_EggDisplayerMod(TASK* tp)
{
    CHAOWK*         const cwp   = GET_CHAOWK(tp);
    EGG_WORK*       const eggwp = GET_EGG_WORK(tp);
    ALW_ENTRY_WORK* const ewp   = GET_ALW_ENTRY_WORK(tp);

    if (!AL_IsOnScreen2(tp, 3.5f, 3.0f))
        return;

    if (!ewp || ChaoGlobal.CamDistShadowCutLev3 <= ewp->CamDist)
        return;

    float scl_h = (       eggwp->BuyoScale) * eggwp->ScaleAll;
    float scl_y = (2.0f - eggwp->BuyoScale) * eggwp->ScaleAll;

    if (AL_GetStageNumber() == CHAO_STG_ODEKAKE)
    {
        scl_h *= 0.68f;
        scl_y *= 0.68f;
    }

    njPushMatrixEx();

    njTranslateEx(&cwp->pos);

    if (cwp->flag & 0x8000)
        njTranslate(NULL, 0.0f, -2.2f, 0.0f);

    njRotateY(NULL, cwp->ang.y);
    njScale(NULL, scl_h, scl_y, scl_h);

    const float add_y = 
        AL_IsHitKindWithNum(tp, 1, CI_KIND_AL_SHADOW) ? 0.01f : 0.5f;

    njTranslate(NULL, 0.0f, add_y, 0.0f);
    njScale(NULL, 1.8f, 0.7f, 1.8f);

    AL_ShadowDraw();

    njPopMatrixEx();
}

static hook_info* HookInfoCreateEgg;
static TASK*
CreateEggHook(AL_GENE* pGene, CHAO_PARAM_GC* pParamGC, int32_t IsParamCopy, const NJS_POINT3* pPos, int32_t type)
{
    TASK* tp;

    FuncHookCall( HookInfoCreateEgg, tp = CreateEgg(pGene, pParamGC, IsParamCopy, pPos, type) );

    if (!tp)
        return NULL;

    tp->disp_shad = AL_EggDisplayerMod;

    return tp;
}

static void
ALO_ChaosDriveDisplayerMod(TASK* tp)
{
    AL_CHAOSDRIVE_WORK* const cdwp = GET_AL_CHAOSDRIVE_WORK(tp);

    njPushMatrixEx();

    if (cdwp->flag & 0x8000)
    {
        njTranslate(NULL, cdwp->pos.x, cdwp->pos.y + 0.7f, cdwp->pos.z);
        njRotateY(NULL, cdwp->ang.y);
        njScale(NULL, 1.1f, 1.1f, 1.1f); // ????
        njScale(NULL, 0.7f, 0.7f, 0.7f);
        AL_ShadowDraw();
    }
    else
    {
        const float scl = cdwp->scl.x;

        njTranslateEx(&cdwp->pos);
        njRotateY(NULL, cdwp->ang.y);
        njScale(NULL, scl * 0.65f, scl * 0.65f, scl * 1.1f);
        AL_ShadowDraw();
    }

    njPopMatrixEx();
}

static hook_info* HookInfoALO_ChaosDriveCreate;
static TASK*
ALO_ChaosDriveCreateHook(uint8_t kind, NJS_POINT3* pPos, NJS_VECTOR* pVelo, ITEM_SAVE_INFO* pSaveInfo)
{
    TASK* tp;

    FuncHookCall( HookInfoALO_ChaosDriveCreate, tp = ALO_ChaosDriveCreate(kind, pPos, pVelo, pSaveInfo) );

    if (!tp)
        return NULL;

    tp->disp_shad = ALO_ChaosDriveDisplayerMod;

    return tp;
}

static void
ALO_ObakeHeadDisplayerMod(TASK* tp)
{
    TASKWK*         const twp = tp->twp;
    ALW_ENTRY_WORK* const ewp = GET_ALW_ENTRY_WORK(tp);

    if (!AL_IsOnScreen2(tp, 2.5f, 2.0f))
        return;

    if (ChaoGlobal.CamDistShadowCutLev2 <= ewp->CamDist)
        return;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);

    if (twp->flag & 0x8000)
        njTranslate(NULL, 0.0f, -0.35f, 0.0f);

    njRotateY(NULL, twp->ang.y);

    const float add_y =
        AL_IsHitKindWithNum(tp, 1, CI_KIND_AL_SHADOW) ? 0.1f : 0.4f;

    njTranslate(NULL, 0.0f, add_y, 0.0f);
    njScale(NULL, 1.5f, 0.7f, 1.5f);

    AL_ShadowDraw();

    njPopMatrixEx();
}

static hook_info* HookInfoALO_ObakeHeadCreate;
static TASK*
ALO_ObakeHeadCreateHook(eHEAD_PARTS kind, NJS_POINT3* pPos, Angle AngY, NJS_VECTOR* pVelo, ITEM_SAVE_INFO* pSaveInfo)
{
    TASK* tp;

    FuncHookCall( HookInfoALO_ObakeHeadCreate, tp = ALO_ObakeHeadCreate(kind, pPos, AngY, pVelo, pSaveInfo) );

    if (!tp)
        return NULL;

    tp->disp_shad = ALO_ObakeHeadDisplayerMod;

    return tp;
}

static void
ALO_SeedDisplayerMod(TASK* tp)
{
    TASKWK*         const twp = tp->twp;
    ALW_ENTRY_WORK* const ewp = GET_ALW_ENTRY_WORK(tp);

    if (!AL_IsOnScreen2(tp, 1.5f, 1.0f))
        return;

    if (ChaoGlobal.CamDistShadowCutLev1 <= ewp->CamDist)
        return;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);

    if (twp->flag & 0x8000)
        njTranslate(NULL, 0.0f, -0.25f, 0.0f);

    njRotateY(NULL, twp->ang.y);
    njScale(NULL, 1.5f, 1.5f, 1.5f);
    njScale(NULL, 0.38f, 0.7f, 0.38f);
    njTranslate(NULL, 0.0f, 0.1f, 0.0f);

    AL_ShadowDraw();

    njPopMatrixEx();
}

static hook_info* HookInfoALO_SeedCreate;
static TASK*
ALO_SeedCreateHook(eHEAD_PARTS kind, NJS_POINT3* pPos, NJS_VECTOR* pVelo, ITEM_SAVE_INFO* pSaveInfo)
{
    TASK* tp;

    FuncHookCall( HookInfoALO_SeedCreate, tp = ALO_SeedCreate(kind, pPos, pVelo, pSaveInfo) );

    if (!tp)
        return NULL;

    tp->disp_shad = ALO_SeedDisplayerMod;

    return tp;
}

static void
ALO_FruitDisplayerMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;
    ALW_ENTRY_WORK* const ewp = GET_ALW_ENTRY_WORK(tp);

    if (!AL_IsOnScreen2(tp, 2.5f, 2.0f))
        return;

    if (ChaoGlobal.CamDistShadowCutLev2 <= ewp->CamDist)
        return;

    if (twp->ang.z <= 0)
        return;

    float scl_sub = (float)twp->ang.z * 0.3f + 0.3f;

    if (twp->ang.x == 9)
        scl_sub *= 0.8f;

    const float scl = scl_sub * 0.8f;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);

    float add_y =
        twp->flag & 0x8000 ? (0.4f) : (scl * 0.55f + 0.8f);

    njTranslate(NULL, 0.0f, add_y, 0.0f);
    njRotateY(NULL, twp->ang.y);

    add_y = AL_IsHitKindWithNum(tp, 1, CI_KIND_AL_SHADOW) ? -1.85f : -1.0f;

    njTranslate(NULL, 0.0f, add_y, 0.0f);

    njScale(NULL, scl, 0.7f, scl);

    AL_ShadowDraw();

    njPopMatrixEx();
}

static hook_info* HookInfoALO_FruitCreate;
static TASK*
ALO_FruitCreateHook(eHEAD_PARTS kind, NJS_POINT3* pPos, Angle AngY, NJS_VECTOR* pVelo, ITEM_SAVE_INFO* pSaveInfo)
{
    TASK* tp;

    FuncHookCall( HookInfoALO_FruitCreate, tp = ALO_FruitCreate(kind, pPos, AngY, pVelo, pSaveInfo) );

    if (!tp)
        return NULL;

    tp->disp_shad = ALO_FruitDisplayerMod;

    return tp;
}

static void
AL_MinimalDisplayerMod(TASK* tp)
{
    MINIMAL_WORK*   const miniwp = GET_MINIMAL_WORK(tp);
    ALW_ENTRY_WORK* const ewp    = GET_ALW_ENTRY_WORK(tp);

    if (!AL_IsOnScreen2(tp, 3.0f, 2.0f))
        return;

    if (ChaoGlobal.CamDistShadowCutLev2 <= ewp->CamDist)
        return;

    njPushMatrixEx();

    njTranslateEx(&miniwp->pos);

    float add_y =
        miniwp->flag & 0x8000 ? -1.0f : -1.2f;

    njTranslate(NULL, 0.0f, add_y, 0.0f);
    njRotateY(NULL, miniwp->ang.y);

    add_y = AL_IsHitKindWithNum(tp, 1, CI_KIND_AL_SHADOW) ? 0.01f : 0.5f;

    njTranslate(NULL, 0.0f, add_y, 0.0f);

    AL_ShadowDraw();

    njPopMatrixEx();
}

static hook_info* HookInfoAL_MinimalCreate;
static TASK*
AL_MinimalCreateHook(eHEAD_PARTS kind, NJS_POINT3* pPos, Angle AngY, NJS_VECTOR* pVelo, ITEM_SAVE_INFO* pSaveInfo)
{
    TASK* tp;

    FuncHookCall( HookInfoAL_MinimalCreate, tp = AL_MinimalCreate(kind, pPos, AngY, pVelo, pSaveInfo) );

    if (!tp)
        return NULL;

    tp->disp_shad = AL_MinimalDisplayerMod;

    return tp;
}

static void
ALO_RaceFruitDisplayerMod(TASK* tp)
{
    TASKWK*         const twp = tp->twp;
    ALW_ENTRY_WORK* const ewp = GET_ALW_ENTRY_WORK(tp);

    if (ChaoGlobal.CamDistShadowCutLev2 <= ewp->CamDist)
        return;

    if (twp->ang.z <= 0)
        return;

    const float scl = (float)twp->ang.z * 0.3f + 0.3f;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njTranslate(NULL, 0.0f, (scl * 0.55f + 0.8f), 0.0f);
    njRotateY(NULL, twp->ang.y);

    const float add_y = 
        AL_IsHitKindWithNum(tp, 1, CI_KIND_AL_SHADOW) ? -1.85f : -1.0f;

    njTranslate(NULL, 0.0f, add_y, 0.0f);
    njScale(NULL, scl, 0.7f, scl);

    AL_ShadowDraw();

    njPopMatrixEx();
}

#define ALO_RaceFruit       FuncPtr(void, __cdecl, (TASK*), 0x0055A560)

static hook_info* HookInfoALO_RaceFruit;
static void
ALO_RaceFruitHook(TASK* tp)
{
    FuncHookCall( HookInfoALO_RaceFruit, ALO_RaceFruit(tp) );

    tp->disp_shad = ALO_RaceFruitDisplayerMod;
}

static void
ALO_BallDisplayerMod(TASK* tp)
{
    TASKWK*         const twp = tp->twp;
    ALW_ENTRY_WORK* const ewp = GET_ALW_ENTRY_WORK(tp);

    if (!AL_IsOnScreen2(tp, 2.0f, 0.0f))
        return;

    if (ChaoGlobal.CamDistShadowCutLev2 <= ewp->CamDist)
        return;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);

    if (twp->flag & 0x8000)
        njTranslate(NULL, 0.0f, 0.4f, 0.0f);

    njRotateY(NULL, twp->ang.y);

    const float add_y = 
        AL_IsHitKindWithNum(tp, 1, CI_KIND_AL_SHADOW) ? -1.45f : -1.0f;

    njTranslate(NULL, 0.0f, add_y, 0.0f);
    njScale(NULL, 1.8f, 0.7f, 1.8f);

    AL_ShadowDraw();

    njPopMatrixEx();
}

static hook_info* HookInfoALO_Ball;
static void
ALO_BallHook(TASK* tp)
{
    FuncHookCall( HookInfoALO_Ball, ALO_Ball(tp) );

    tp->disp_shad = ALO_BallDisplayerMod;
}

static void
ALO_BoxDisplayerMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;

    if (!AL_IsOnScreen2(tp, 2.5f, 1.0f))
        return;

    /** The box doesn't check CamDist **/

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);
    njTranslate(NULL, 0.0f, 0.5f, 0.0f);
    njScale(NULL, 1.5f, 1.0f, 1.5f);

    AL_ShadowDraw();

    njPopMatrixEx();
}

__declspec(naked)
static void
ALO_BoxCreateMovHook()
{
    __asm
    {
        mov dword ptr [ebx+14h], 00580510h // ALO_BoxDisplayer
        mov dword ptr [ebx+2Ch], offset ALO_BoxDisplayerMod
        retn
    }
}

static void
ALO_HorseDisplayerMod(TASK* tp)
{
    TASKWK*         const twp = tp->twp;
    ALW_ENTRY_WORK* const ewp = GET_ALW_ENTRY_WORK(tp);

    if (!ewp)
        return; // Goddamnit CWE! The Horse too??

    if (!AL_IsOnScreen3(tp, 3.4f, 3.2f, 0.0f))
        return;

    if (ChaoGlobal.CamDistShadowCutLev3 <= ewp->CamDist)
        return;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);
    njTranslate(NULL, 0.0f, 0.8f, 0.0f);
    njScale(NULL, 0.7f, 0.7f, 1.8f);

    AL_ShadowDraw();

    njPopMatrixEx();
}

static hook_info* HookInfoALO_Horse;
static void
ALO_HorseHook(TASK* tp)
{
    FuncHookCall( HookInfoALO_Horse, ALO_Horse(tp) );

    tp->disp_shad = ALO_HorseDisplayerMod;
}

static void
ALO_RadicaseDisplayerMod(TASK* tp)
{
    TASKWK*         const twp = tp->twp;
    ALW_ENTRY_WORK* const ewp = GET_ALW_ENTRY_WORK(tp);

    if (!AL_IsOnScreen2(tp, 3.0f, 1.0f))
        return;

    if (ChaoGlobal.CamDistShadowCutLev2 <= ewp->CamDist)
        return;

    njPushMatrixEx();

    const float scl = njSin(twp->ang.x) * 0.05f + 1.0f;

    njTranslate(NULL, 0.0f, -1.5f, 0.0f);
    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);
    njScale(NULL, scl, 2.0f - scl, 1.0f);
    njTranslate(NULL, 0.0f, 0.5f, 0.0f);
    njScale(NULL, 2.0f, 1.0f, 1.5f);

    AL_ShadowDraw();

    njPopMatrixEx();
}

__declspec(naked)
static void
ALO_RadicaseCreateMovHook()
{
    __asm
    {
        mov dword ptr[ebx + 18h], 0057CC80h // ALO_RadicaseDestructor
        mov dword ptr[ebx + 2Ch], offset ALO_RadicaseDisplayerMod
        retn
    }
}

static void
ALO_TVDisplayerMod(TASK* tp)
{
    TASKWK*         const twp = tp->twp;
    ALW_ENTRY_WORK* const ewp = GET_ALW_ENTRY_WORK(tp);

    if (!ewp)
        return; // Goddamnit CWE! Why only the TV??

    if (!AL_IsOnScreen2(tp, 3.0f, 1.0f))
        return;

    if (ChaoGlobal.CamDistShadowCutLev2 <= ewp->CamDist)
        return;

    njPushMatrixEx();

    njTranslate(NULL, 0.0f, -1.5f, 0.0f);
    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);
    njTranslate(NULL, 0.0f, 0.5f, 0.0f);
    njScale(NULL, 2.0f, 1.0f, 1.5f);

    AL_ShadowDraw();

    njPopMatrixEx();
}

__declspec(naked)
static void
ALO_TVCreateMovHook()
{
    __asm
    {
        mov dword ptr[ebx + 18h], 0055CB70h // ALO_TVDestructor
        mov dword ptr[ebx + 2Ch], offset ALO_TVDisplayerMod
        retn
    }
}

void
CHS_ChaoWorldInit()
{
    WriteRetn(0x00540F70);  // Kill AL_CreateShadowTex

    /** Chao **/
    HookInfoCreateChaoExtra = FuncHook(CreateChaoExtra_p, CreateChaoExtraHook);
    WriteRetn(0x005405D0); // AL_DrawChaoShadow

    /** Grow Tree **/
    HookInfoALO_GrowTreeCreate = FuncHook(ALO_GrowTreeCreate_p, ALO_GrowTreeCreateHook);
    HookInfoALO_RaceTree       = FuncHook(ALO_RaceTree        , ALO_RaceTreeHook);

    /** AL Objects **/
    HookInfoCreateEgg            = FuncHook(CreateEgg_p           , CreateEggHook);
    HookInfoALO_ChaosDriveCreate = FuncHook(ALO_ChaosDriveCreate_p, ALO_ChaosDriveCreateHook);
    HookInfoALO_ObakeHeadCreate  = FuncHook(ALO_ObakeHeadCreate_p , ALO_ObakeHeadCreateHook);
    HookInfoALO_SeedCreate       = FuncHook(ALO_SeedCreate_p      , ALO_SeedCreateHook);
    HookInfoALO_FruitCreate      = FuncHook(ALO_FruitCreate_p     , ALO_FruitCreateHook);
    HookInfoAL_MinimalCreate     = FuncHook(AL_MinimalCreate_p    , AL_MinimalCreateHook);
    HookInfoALO_RaceFruit        = FuncHook(ALO_RaceFruit         , ALO_RaceFruitHook);

    /** Toys **/
    HookInfoALO_Ball  = FuncHook(ALO_Ball_p , ALO_BallHook);
    HookInfoALO_Horse = FuncHook(ALO_Horse_p, ALO_HorseHook);

    WriteCallToMovDwordPtr(0x0058092A, ALO_BoxCreateMovHook);
    WriteCallToMovDwordPtr(0x0057CD2B, ALO_RadicaseCreateMovHook);
    WriteCallToMovDwordPtr(0x0055CC2E, ALO_TVCreateMovHook);

    /** Object **/
    NJS_CNK_OBJECT* objp = RF_ChunkLoadObjectFile("al_shadow");

    model_al_shadow = objp->model;

    MemFree(objp); // Only the model is used, so we can free this
}
