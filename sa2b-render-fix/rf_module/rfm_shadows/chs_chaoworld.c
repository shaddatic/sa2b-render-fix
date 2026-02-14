/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/memory.h>            /* alloc                                                    */
#include <samt/writemem.h>          /* write memory                                             */
#include <samt/funchook.h>          /* function hook                                            */
#include <samt/writeop.h>           /* write operation                                          */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Game ************************************************************************************/
#include <samt/sonic/task.h>        /* task                                                     */

/****** Chao ************************************************************************************/
#define SAMT_INCL_FUNCPTRS
#include <samt/sonic/chao/chao.h>           /* chao                                             */
#include <samt/sonic/chao/al_egg.h>         /* chao egg                                         */
#include <samt/sonic/chao/al_world.h>       /* world manager                                    */
#include <samt/sonic/chao/alo_growtree.h>   /* trees                                            */
#include <samt/sonic/chao/alo_chaosdrive.h> /* chaos drives                                     */
#include <samt/sonic/chao/alo_obake_head.h> /* hat/masks                                        */
#include <samt/sonic/chao/alo_seed.h>       /* seeds                                            */
#include <samt/sonic/chao/alo_fruit.h>      /* fruit                                            */
#include <samt/sonic/chao/al_minimal.h>     /* minimals                                         */
#undef  SAMT_INCL_FUNCPTRS
#include <samt/sonic/chao/al_chao_info.h>   /* chao info                                        */
#include <samt/sonic/chao/al_stage.h>       /* stage info                                       */
#include <samt/sonic/chao/al_global.h>      /* global vars                                      */
#include <samt/sonic/chao/al_misc.h>        /* chao ball                                        */

/****** Chao Toys *******************************************************************************/
#define SAMT_INCL_FUNCPTRS
#include <samt/sonic/chao/al_toy/alo_ball.h>     /* chao ball                                   */
#include <samt/sonic/chao/al_toy/alo_box.h>      /* jack box                                    */
#include <samt/sonic/chao/al_toy/alo_horse.h>    /* rocking horse                               */
#include <samt/sonic/chao/al_toy/alo_radicase.h> /* radio                                       */
#include <samt/sonic/chao/al_toy/alo_tv.h>       /* television                                  */
#undef  SAMT_INCL_FUNCPTRS

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_ninja.h>               /* rf ninja                                                 */
#include <rf_samdl.h>               /* get samdl                                                */
#include <rf_util.h>                /* utils                                                    */

/****** RF Util *********************************************************************************/
#include <rfu_draw.h>               /* al shadow draw                                           */

/****** Config **********************************************************************************/
#include <cnf.h>                    /* config get                                               */

/********************************/
/*  Constants                   */
/********************************/
/****** Chao Shape Flags ************************************************************************/
#define SHAPE_FLG_SHADOW    (0b0000'0000'0000'1000)

/****** Chao Flags ******************************************************************************/
#define CHAO_FLG_DRAW       (0b0000'0010'0000'0000)
#define CHAO_FLG_INRANGE    (0b0001'0000'0000'0000)

/********************************/
/*  Static Variables            */
/********************************/
/****** Chao Shape Flags ************************************************************************/
static const Angle LeafRotList[11] = { 0x2000, 0x3800, 0x5000, 0x4B00 };
static const float LeafAdjList[11] = { 7.7f, 7.3f, 7.8f, 7.1f };
static const float LeafSclList[11] = { 3.0f, 3.0f, 4.0f, 4.0f };

/********************************/
/*  Source                      */
/********************************/
/****** Chao Shadow *****************************************************************************/
static void
ChaoDisplayerMod(task* tp)
{
    chaowk*               const cwp = GET_CHAOWK(tp);
    const ALW_ENTRY_WORK* const ewp = GET_ALW_ENTRY_WORK(tp);

    if ( (cwp->ChaoFlag & CHAO_FLG_DRAW) == 0 || !AL_IsOnScreen3(tp, 5.2f, 4.5f, 2.9f) )
    {
        return;
    }

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

static mt_hookinfo HookInfoCreateChaoExtra[1];
static task*
CreateChaoExtraHook(CHAO_PARAM_GC* pParamGC, b32 IsParamCopy, AL_SHAPE_ELEMENT* pElement, NJS_POINT3* pPos, Angle angy)
{
    task* tp;

    mtHookInfoCall(HookInfoCreateChaoExtra, tp = CreateChaoExtra(pParamGC, IsParamCopy, pElement, pPos, angy));

    if (!tp)
        return NULL;

    if (!tp->disp_shad)
        tp->disp_shad = ChaoDisplayerMod;

    return tp;
}

/****** Tree Shadow *****************************************************************************/
static void
ALO_GrowTreeDisplayerMod(task* tp)
{
    const TREE_WORK* const twp = GET_TREE_WORK(tp);

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

static mt_hookinfo HookInfoALO_GrowTreeCreate[1];
static task*
ALO_GrowTreeCreateHook(NJS_POINT3* pPos, TREE_SAVE_INFO* pInfo)
{
    task* tp;

    mtHookInfoCall( HookInfoALO_GrowTreeCreate, tp = ALO_GrowTreeCreate(pPos, pInfo) );

    if (!tp)
        return NULL;

    tp->disp_shad = ALO_GrowTreeDisplayerMod;

    return tp;
}

/****** Race Tree Shadow ************************************************************************/
static void
ALO_RaceTreeDisplayerMod(task* tp)
{
    const TREE_WORK* const twp = GET_TREE_WORK(tp);

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

#define ALO_RaceTree        FUNC_PTR(void, __cdecl, (task*), 0x00537E70)

static mt_hookinfo HookInfoALO_RaceTree[1];
static void
ALO_RaceTreeHook(task* tp)
{
    mtHookInfoCall( HookInfoALO_RaceTree, ALO_RaceTree(tp) );

    tp->disp_shad = ALO_RaceTreeDisplayerMod;
}

/****** Chao Egg Shadow ************************************************************************/
static void
AL_EggDisplayerMod(task* tp)
{
    const chaowk*         const cwp   = GET_CHAOWK(tp);
    const EGG_WORK*       const eggwp = GET_EGG_WORK(tp);
    const ALW_ENTRY_WORK* const ewp   = GET_ALW_ENTRY_WORK(tp);

    if ( !ewp ) // not CWE related
    {
        return;
    }

    if ( ChaoGlobal.CamDistShadowCutLev3 <= ewp->CamDist || !AL_IsOnScreen2(tp, 3.5f, 3.0f) )
    {
        return;
    }

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

static mt_hookinfo HookInfoCreateEgg[1];
static task*
CreateEggHook(AL_GENE* pGene, CHAO_PARAM_GC* pParamGC, int32_t IsParamCopy, const NJS_POINT3* pPos, int32_t type)
{
    task* tp;

    mtHookInfoCall( HookInfoCreateEgg, tp = CreateEgg(pGene, pParamGC, IsParamCopy, pPos, type) );

    if (!tp)
        return NULL;

    tp->disp_shad = AL_EggDisplayerMod;

    return tp;
}

/****** Chaos Drive Shadow **********************************************************************/
static void
ALO_ChaosDriveDisplayerMod(task* tp)
{
    const AL_CHAOSDRIVE_WORK* const cdwp = GET_AL_CHAOSDRIVE_WORK(tp);

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

static mt_hookinfo HookInfoALO_ChaosDriveCreate[1];
static task*
ALO_ChaosDriveCreateHook(uint8_t kind, NJS_POINT3* pPos, NJS_VECTOR* pVelo, ITEM_SAVE_INFO* pSaveInfo)
{
    task* tp;

    mtHookInfoCall( HookInfoALO_ChaosDriveCreate, tp = ALO_ChaosDriveCreate(kind, pPos, pVelo, pSaveInfo) );

    if (!tp)
        return NULL;

    tp->disp_shad = ALO_ChaosDriveDisplayerMod;

    return tp;
}

/****** Obake Head Shadow ***********************************************************************/
static void
ALO_ObakeHeadDisplayerMod(task* tp)
{
    const taskwk*         const twp = tp->twp;
    const ALW_ENTRY_WORK* const ewp = GET_ALW_ENTRY_WORK(tp);

    if ( (ChaoGlobal.CamDistShadowCutLev2 <= ewp->CamDist) || !AL_IsOnScreen2(tp, 2.5f, 2.0f) )
    {
        return;
    }

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

static mt_hookinfo HookInfoALO_ObakeHeadCreate[1];
static task*
ALO_ObakeHeadCreateHook(eHEAD_PARTS kind, NJS_POINT3* pPos, Angle AngY, NJS_VECTOR* pVelo, ITEM_SAVE_INFO* pSaveInfo)
{
    task* tp;

    mtHookInfoCall( HookInfoALO_ObakeHeadCreate, tp = ALO_ObakeHeadCreate(kind, pPos, AngY, pVelo, pSaveInfo) );

    if (!tp)
        return NULL;

    tp->disp_shad = ALO_ObakeHeadDisplayerMod;

    return tp;
}

/****** Seed Shadow *****************************************************************************/
static void
ALO_SeedDisplayerMod(task* tp)
{
    const taskwk*         const twp = tp->twp;
    const ALW_ENTRY_WORK* const ewp = GET_ALW_ENTRY_WORK(tp);

    if ( (ChaoGlobal.CamDistShadowCutLev1 <= ewp->CamDist) || !AL_IsOnScreen2(tp, 1.5f, 1.0f) )
    {
        return;
    }

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

static mt_hookinfo HookInfoALO_SeedCreate[1];
static task*
ALO_SeedCreateHook(eHEAD_PARTS kind, NJS_POINT3* pPos, NJS_VECTOR* pVelo, ITEM_SAVE_INFO* pSaveInfo)
{
    task* tp;

    mtHookInfoCall( HookInfoALO_SeedCreate, tp = ALO_SeedCreate(kind, pPos, pVelo, pSaveInfo) );

    if (!tp)
        return NULL;

    tp->disp_shad = ALO_SeedDisplayerMod;

    return tp;
}

/****** Fruit Shadow ****************************************************************************/
static void
ALO_FruitDisplayerMod(task* tp)
{
    const taskwk* const twp = tp->twp;
    const ALW_ENTRY_WORK* const ewp = GET_ALW_ENTRY_WORK(tp);

    if ( (ChaoGlobal.CamDistShadowCutLev2 <= ewp->CamDist) || (twp->ang.z <= 0) || !AL_IsOnScreen2(tp, 2.5f, 2.0f) )
    {
        return;
    }

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

static mt_hookinfo HookInfoALO_FruitCreate[1];
static task*
ALO_FruitCreateHook(eHEAD_PARTS kind, NJS_POINT3* pPos, Angle AngY, NJS_VECTOR* pVelo, ITEM_SAVE_INFO* pSaveInfo)
{
    task* tp;

    mtHookInfoCall( HookInfoALO_FruitCreate, tp = ALO_FruitCreate(kind, pPos, AngY, pVelo, pSaveInfo) );

    if (!tp)
        return NULL;

    tp->disp_shad = ALO_FruitDisplayerMod;

    return tp;
}

/****** Minimal Shadow **************************************************************************/
static void
AL_MinimalDisplayerMod(task* tp)
{
    const MINIMAL_WORK*   const miniwp = GET_MINIMAL_WORK(tp);
    const ALW_ENTRY_WORK* const ewp    = GET_ALW_ENTRY_WORK(tp);

    if ( !ewp ) // CWE moveable toys crash prevention
    {
        return;
    }

    if ( (ChaoGlobal.CamDistShadowCutLev2 <= ewp->CamDist) || !AL_IsOnScreen2(tp, 3.0f, 2.0f) )
    {
        return;
    }

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

static mt_hookinfo HookInfoAL_MinimalCreate[1];
static task*
AL_MinimalCreateHook(eHEAD_PARTS kind, NJS_POINT3* pPos, Angle AngY, NJS_VECTOR* pVelo, ITEM_SAVE_INFO* pSaveInfo)
{
    task* tp;

    mtHookInfoCall( HookInfoAL_MinimalCreate, tp = AL_MinimalCreate(kind, pPos, AngY, pVelo, pSaveInfo) );

    if (!tp)
        return NULL;

    tp->disp_shad = AL_MinimalDisplayerMod;

    return tp;
}

/****** Race Fruit Shadow ***********************************************************************/
static void
ALO_RaceFruitDisplayerMod(task* tp)
{
    const taskwk*         const twp = tp->twp;
    const ALW_ENTRY_WORK* const ewp = GET_ALW_ENTRY_WORK(tp);

    if ( !ewp ) // CWE moveable toys crash prevention
    {
        return;
    }

    if ( (ChaoGlobal.CamDistShadowCutLev2 <= ewp->CamDist) || twp->ang.z <= 0 )
    {
        return;
    }

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

#define ALO_RaceFruit       FUNC_PTR(void, __cdecl, (task*), 0x0055A560)

static mt_hookinfo HookInfoALO_RaceFruit[1];
static void
ALO_RaceFruitHook(task* tp)
{
    mtHookInfoCall( HookInfoALO_RaceFruit, ALO_RaceFruit(tp) );

    tp->disp_shad = ALO_RaceFruitDisplayerMod;
}

/****** Chao Ball Shadow ************************************************************************/
static void
ALO_BallDisplayerMod(task* tp)
{
    const taskwk*         const twp = tp->twp;
    const ALW_ENTRY_WORK* const ewp = GET_ALW_ENTRY_WORK(tp);

    if ( !ewp ) // CWE moveable toys crash prevention
    {
        return;
    }

    if ( (ChaoGlobal.CamDistShadowCutLev2 <= ewp->CamDist) || !AL_IsOnScreen2(tp, 2.0f, 0.0f) )
    {
        return;
    }

    njPushMatrixEx();

    njTranslateEx(&twp->pos);

    if (twp->flag & 0x8000)
        njTranslate(NULL, 0.0f, 0.4f, 0.0f);

    njRotateY(NULL, twp->ang.y);

    const float add_y = AL_IsHitKindWithNum(tp, 1, CI_KIND_AL_SHADOW) ? -1.45f : -1.0f;

    njTranslate(NULL, 0.0f, add_y, 0.0f);
    njScale(NULL, 1.8f, 0.7f, 1.8f);

    AL_ShadowDraw();

    njPopMatrixEx();
}

static mt_hookinfo HookInfoALO_Ball[1];
static void
ALO_BallHook(task* tp)
{
    mtHookInfoCall( HookInfoALO_Ball, ALO_Ball(tp) );

    tp->disp_shad = ALO_BallDisplayerMod;
}

/****** Box Shadow ******************************************************************************/
static void
ALO_BoxDisplayerMod(task* tp)
{
    const taskwk* const twp = tp->twp;

    if ( !AL_IsOnScreen2(tp, 2.5f, 1.0f) )
    {
        return;
    }

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);
    njTranslate(NULL, 0.0f, 0.5f, 0.0f);
    njScale(NULL, 1.5f, 1.0f, 1.5f);

    AL_ShadowDraw();

    njPopMatrixEx();
}

static mt_hookinfo BoxHookInfo[1];
static void
ALO_BoxCreateHook(NJS_POINT3* pPos)
{
    mtHookInfoCall( BoxHookInfo, ALO_BoxCreate(pPos) );

    task* const tp = ALO_BoxTaskPointer;

    if ( tp && !tp->disp_shad )
    {
        tp->disp_shad = ALO_BoxDisplayerMod;
    }
}

/****** Horse Shadow ****************************************************************************/
static void
ALO_HorseDisplayerMod(task* tp)
{
    const taskwk*         const twp = tp->twp;
    const ALW_ENTRY_WORK* const ewp = GET_ALW_ENTRY_WORK(tp);

    if ( !ewp ) // CWE moveable toys crash prevention
    {
        return;
    }

    if ( (ChaoGlobal.CamDistShadowCutLev3 <= ewp->CamDist) || !AL_IsOnScreen3(tp, 3.4f, 3.2f, 0.0f) )
    {
        return;
    }

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);
    njTranslate(NULL, 0.0f, 0.8f, 0.0f);
    njScale(NULL, 0.7f, 0.7f, 1.8f);

    AL_ShadowDraw();

    njPopMatrixEx();
}

static mt_hookinfo HookInfoALO_Horse[1];
static void
ALO_HorseHook(task* tp)
{
    mtHookInfoCall( HookInfoALO_Horse, ALO_Horse(tp) );

    tp->disp_shad = ALO_HorseDisplayerMod;
}

/****** Radicase Shadow *************************************************************************/
static void
ALO_RadicaseDisplayerMod(task* tp)
{
    const taskwk*         const twp = tp->twp;
    const ALW_ENTRY_WORK* const ewp = GET_ALW_ENTRY_WORK(tp);

    if ( !ewp ) // CWE moveable toys crash prevention
    {
        return;
    }

    if ( (ChaoGlobal.CamDistShadowCutLev2 <= ewp->CamDist) || !AL_IsOnScreen2(tp, 3.0f, 1.0f) )
    {
        return;
    }

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

static mt_hookinfo RadicaseHookInfo[1];
static void
ALO_RadicaseCreateHook(NJS_POINT3* pPos)
{
    mtHookInfoCall( RadicaseHookInfo, ALO_RadicaseCreate(pPos) );

    task* const tp = ALO_RadicaseTaskPointer;

    if ( tp && !tp->disp_shad )
    {
        tp->disp_shad = ALO_RadicaseDisplayerMod;
    }
}

/****** TV Shadow *******************************************************************************/
static void
ALO_TVDisplayerMod(task* tp)
{
    const taskwk*         const twp = tp->twp;
    const ALW_ENTRY_WORK* const ewp = GET_ALW_ENTRY_WORK(tp);

    if ( !ewp ) // CWE moveable toys crash prevention
    {
        return;
    }

    if ( (ChaoGlobal.CamDistShadowCutLev2 <= ewp->CamDist) || !AL_IsOnScreen2(tp, 3.0f, 1.0f) )
    {
        return;
    }

    njPushMatrixEx();

    njTranslate(NULL, 0.0f, -1.5f, 0.0f);
    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);
    njTranslate(NULL, 0.0f, 0.5f, 0.0f);
    njScale(NULL, 2.0f, 1.0f, 1.5f);

    AL_ShadowDraw();

    njPopMatrixEx();
}

static mt_hookinfo TVHookInfo[1];
static void
ALO_TVCreateHook(NJS_POINT3* pPos)
{
    mtHookInfoCall( TVHookInfo, ALO_TVCreate(pPos) );

    task* const tp = ALO_TVTaskPointer;

    if ( tp && !tp->disp_shad )
    {
        tp->disp_shad = ALO_TVDisplayerMod;
    }
}

/****** Control *********************************************************************************/
static bool CheapShadowNoChaoWorld;
void
RFCTRL_CheapShadowChaoWorldDisable(void)
{
    CheapShadowNoChaoWorld = true;
}

/****** Init ************************************************************************************/
void
CHS_ChaoWorldInit(void)
{
    if (CheapShadowNoChaoWorld || CNF_GetInt(CNF_COMPAT_NOCHMOD))
    {
        return;
    }

    WriteRetn(0x00540F70);  // Kill AL_CreateShadowTex

    /** Chao **/
    mtHookFunc(HookInfoCreateChaoExtra, CreateChaoExtra_p, CreateChaoExtraHook);
    WriteRetn(0x005405D0); // AL_DrawChaoShadow

    /** Grow Tree **/
    mtHookFunc(HookInfoALO_GrowTreeCreate, ALO_GrowTreeCreate_p, ALO_GrowTreeCreateHook);

    if ( CNF_GetInt(CNF_MISC_RACETREEMOD) )
    {
        mtHookFunc(HookInfoALO_RaceTree, ALO_RaceTree, ALO_RaceTreeHook);
    }

    /** AL Objects **/
    mtHookFunc(HookInfoCreateEgg           , CreateEgg_p           , CreateEggHook);
    mtHookFunc(HookInfoALO_ChaosDriveCreate, ALO_ChaosDriveCreate_p, ALO_ChaosDriveCreateHook);
    mtHookFunc(HookInfoALO_ObakeHeadCreate , ALO_ObakeHeadCreate_p , ALO_ObakeHeadCreateHook);
    mtHookFunc(HookInfoALO_SeedCreate      , ALO_SeedCreate_p      , ALO_SeedCreateHook);
    mtHookFunc(HookInfoALO_FruitCreate     , ALO_FruitCreate_p     , ALO_FruitCreateHook);
    mtHookFunc(HookInfoAL_MinimalCreate    , AL_MinimalCreate_p    , AL_MinimalCreateHook);
    mtHookFunc(HookInfoALO_RaceFruit       , ALO_RaceFruit         , ALO_RaceFruitHook);

    /** Toys **/
    mtHookFunc(HookInfoALO_Ball , ALO_Ball_p          , ALO_BallHook);
    mtHookFunc(HookInfoALO_Horse, ALO_Horse_p         , ALO_HorseHook);
    mtHookFunc(BoxHookInfo      , ALO_BoxCreate_p     , ALO_BoxCreateHook);
    mtHookFunc(RadicaseHookInfo , ALO_RadicaseCreate_p, ALO_RadicaseCreateHook);
    mtHookFunc(TVHookInfo       , ALO_TVCreate_p      , ALO_TVCreateHook);
}
