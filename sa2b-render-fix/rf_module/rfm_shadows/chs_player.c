#include <samt/core.h>
#include <samt/memory.h>
#include <samt/funchook.h>
#include <samt/writemem.h>
#include <samt/writeop.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Source **/
#include <samt/sonic/task.h>
#include <samt/sonic/player.h>
#include <samt/sonic/c_colli.h>
#include <samt/sonic/njctrl.h>
#include <samt/sonic/debug.h>

/** Figure **/
#define SAMT_INCL_FUNCPTRS
#include <samt/sonic/figure/sonic.h>
#include <samt/sonic/figure/shadow.h>
#include <samt/sonic/figure/miles.h>
#include <samt/sonic/figure/eggman.h>
#include <samt/sonic/figure/knuckles.h>
#include <samt/sonic/figure/rouge.h>
#include <samt/sonic/figure/ewalker.h>
#include <samt/sonic/figure/twalker.h>
#undef  SAMT_INCL_FUNCPTRS

/** Render Fix **/
#include <rf_core.h>
#include <rf_samdl.h>
#include <rf_ninja.h>

/****** Config **********************************************************************/
#include <cnf.h>                /* config get                                       */

/** Self (?) **/

/** Constant **/
#define SonicDisplayer      FUNC_PTR(void, __cdecl, (task*), 0x00720090)

static NJS_CNK_OBJECT* object_sonic_head_mod;
static NJS_CNK_OBJECT* object_amy_head_mod;

static NJS_CNK_OBJECT* object_terios_head_mod;
static NJS_CNK_OBJECT* object_metalsonic_head_mod;

static NJS_CNK_OBJECT* object_miles_head_mod;

static NJS_CNK_OBJECT* object_eggman_head_mod;

static NJS_CNK_OBJECT* object_knuckles_head_mod;
static NJS_CNK_OBJECT* object_rouge_head_mod;
static NJS_CNK_OBJECT* object_tikal_head_mod;
static NJS_CNK_OBJECT* object_chaos_head_mod;

static NJS_CNK_OBJECT* object_twalker_body_mod;
static NJS_CNK_OBJECT* object_twalker_foot_mod;
static NJS_CNK_OBJECT* object_cwalker_body_mod;
static NJS_CNK_OBJECT* object_cwalker_foot_mod;
static NJS_CNK_OBJECT* object_ewalker_body_mod;
static NJS_CNK_OBJECT* object_ewalker_foot_mod;
static NJS_CNK_OBJECT* object_dwalker_body_mod;
static NJS_CNK_OBJECT* object_dwalker_foot_mod;

static bool MilesTailModifiers; /* Draw Tails' tail modifiers                           */
static bool TornadoFootFix;     /* Fix Tornado's foot modifiers drawing below the floor */

#define flt_1DEB070         DATA_REF(f32   , 0x01DEB070)
#define MultiIntroPno       DATA_REF(int8_t, 0x0174B009)

#define BALL_OBJ_NUM_SONIC      (6)
#define BALL_OBJ_NUM_SHADOW     (71)
#define BALL_OBJ_NUM_AMY        (401)

static void
SonicDrawMod(taskwk* twp, playerwk* pwp, int motion)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    if (pwp->mj.plactptr[motion].objnum == BALL_OBJ_NUM_SONIC)
    {
        njTranslate(NULL, twp->pos.x, twp->pos.y + 0.3f, twp->pos.z);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 5.0f, 1.0f, 5.0f);

        DrawBasicShadow();
    }
    else
    {
        NJS_CNK_OBJECT* mod_head = CHAR_OBJECTS[7].pObject;

        if (mod_head == nullptr)
            mod_head = object_sonic_head_mod;

        njTranslateEx(&pwp->user0_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(mod_head);

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->righthand_pos);
        njTranslate(NULL, 0.0f, -1.0f, 0.0f);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 1.0f, 1.0f, 0.7f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->lefthand_pos);
        njTranslate(NULL, 0.0f, -1.0f, 0.0f);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 1.0f, 1.0f, 0.7f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->rightfoot_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 2.6f, 1.0f, 1.0f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->leftfoot_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 2.6f, 1.0f, 1.0f);
        DrawBasicShadow();
    }

    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}

static void
TeriosDrawMod(taskwk* twp, playerwk* pwp, int motion)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    if (pwp->mj.plactptr[motion].objnum == BALL_OBJ_NUM_SHADOW)
    {
        njTranslate(NULL, twp->pos.x, twp->pos.y + 0.3f, twp->pos.z);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 5.0f, 1.0f, 5.0f);
        DrawBasicShadow();
    }
    else
    {
        NJS_CNK_OBJECT* mod_head = CHAR_OBJECTS[72].pObject;

        if (mod_head == nullptr)
            mod_head = object_terios_head_mod;

        njTranslateEx(&pwp->user0_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(mod_head);

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->righthand_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 1.0f, 1.0f, 0.7f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->lefthand_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 1.0f, 1.0f, 0.7f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->rightfoot_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 2.6f, 1.0f, 1.0f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->leftfoot_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 2.6f, 1.0f, 1.0f);
        DrawBasicShadow();
    }

    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}

static void
AmyDrawMod(taskwk* twp, playerwk* pwp, int motion)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    if (pwp->mj.plactptr[motion].objnum == BALL_OBJ_NUM_AMY)
    {
        njTranslate(NULL, twp->pos.x, twp->pos.y + 0.3f, twp->pos.z);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 5.0f, 1.0f, 5.0f);

        DrawBasicShadow();
    }
    else
    {
        njTranslateEx(&pwp->user0_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(object_amy_head_mod);

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->righthand_pos);
        njTranslate(NULL, 0.0f, -1.0f, 0.0f);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 1.0f, 1.0f, 0.7f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->lefthand_pos);
        njTranslate(NULL, 0.0f, -1.0f, 0.0f);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 1.0f, 1.0f, 0.7f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->rightfoot_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 2.6f, 1.0f, 1.0f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->leftfoot_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 2.6f, 1.0f, 1.0f);
        DrawBasicShadow();
    }

    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}

static void
MetalSonicDrawMod(taskwk* twp, playerwk* pwp, int motion)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    njTranslateEx(&pwp->user0_pos);
    njRotateY(NULL, 0x8000 - twp->ang.y);
    njCnkModDrawObject(object_metalsonic_head_mod);

    njPopMatrixEx();
    njPushMatrixEx();

    njTranslateEx(&pwp->righthand_pos);
    njRotateY(NULL, 0x8000 - twp->ang.y);
    njScale(NULL, 1.0f, 1.0f, 0.7f);
    DrawBasicShadow();

    njPopMatrixEx();
    njPushMatrixEx();

    njTranslateEx(&pwp->lefthand_pos);
    njRotateY(NULL, 0x8000 - twp->ang.y);
    njScale(NULL, 1.0f, 1.0f, 0.7f);
    DrawBasicShadow();

    njPopMatrixEx();
    njPushMatrixEx();

    njTranslateEx(&pwp->rightfoot_pos);
    njRotateY(NULL, 0x8000 - twp->ang.y);
    njScale(NULL, 2.6f, 1.0f, 1.0f);
    DrawBasicShadow();

    njPopMatrixEx();
    njPushMatrixEx();

    njTranslateEx(&pwp->leftfoot_pos);
    njRotateY(NULL, 0x8000 - twp->ang.y);
    njScale(NULL, 2.6f, 1.0f, 1.0f);
    DrawBasicShadow();

    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}

#define BALL_FLAG   (0x100)

#define AmyMotionCallBack_p             FUNC_PTR(void, __cdecl, (NJS_CNK_OBJECT*), 0x0071F040)
#define MetalSonicMotionCallBack_p      FUNC_PTR(void, __cdecl, (NJS_CNK_OBJECT*), 0x0071FBE0)

static void __cdecl
SonicDisplayerShadowHook(task* tp)
{
    taskwk* const twp = tp->twp;
    SONICWK* const swp = GET_SONICWK(tp);

    njGetMatrix(&mtx_SonicBase);
    njInvertMatrix(&mtx_SonicBase);

    SonicWorkPointer = swp;

    switch (swp->pw.ch_num_multi) {
    case PLNO_SONIC:
        njCnkSetMotionCallback(SonicMotionCallBack_p);
        break;

    case PLNO_SHADOW:
        njCnkSetMotionCallback(ShadowMotionCallBack_p);
        break;

    case PLNO_AMY:
        njCnkSetMotionCallback(AmyMotionCallBack_p);
        break;

    case PLNO_METAL_SONIC:
        njCnkSetMotionCallback(MetalSonicMotionCallBack_p);
        break;
    }

    njPushMatrixEx();

    int mtnnum = swp->pw.mj.mtnnum;

    if (twp->mode == 51)
    {
        NJS_POINT3 point_in = {
            .x = 0.0f,
            .y = -swp->pw.p.height * 0.5f,
            .z = 0.0f
        };

        NJS_POINT3 point_out;

        CCL_INFO* p_cinfo = twp->cwp->info;

        njPushMatrix(&_nj_unit_matrix_);

        njRotateZ(NULL, twp->ang.z);
        njRotateX(NULL, twp->ang.x);
        njRotateY(NULL, -twp->ang.y);

        njCalcVector(NULL, &point_in, &point_out);

        njPopMatrixEx();

        point_out.x += p_cinfo->center.x;
        point_out.y += p_cinfo->center.y;
        point_out.z += p_cinfo->center.z;

        njTranslateEx(&point_out);
    }
    else
        njTranslateEx(&twp->pos);

    if (MultiIntroPno != swp->pw.pl_num + 1)
    {
        njRotateZ(NULL, twp->ang.z);
        njRotateX(NULL, twp->ang.x);
        njRotateY(NULL, 0x8000 - twp->ang.y);

        if (mtnnum == 11 && twp->flag & 3)
        {
            /** I have no idea **/
            njTranslate(NULL, 0.0f, -1.0f, 0.0f);
            njTranslate(NULL, 0.0f, 5.0f, 0.0f);
            njRotateZ(NULL, 0x2000);
            njTranslate(NULL, 0.0f, -5.0f, 0.0f);
            njScale(NULL, 0.7f, 1.1f, 0.8f);
        }
    }
    else
        njRotateY(NULL, 0x8000 - twp->ang.y);

    njScaleEx(&twp->scl);

    if (twp->mode == 54 && swp->pw.motion_list)
    {
        njCnkAnimateMotion(CHAR_OBJECTS[swp->pw.mj.plactptr->objnum].pObject, *swp->pw.motion_list, flt_1DEB070);
    }
    else
    {
        NJS_CNK_OBJECT* p_object = CHAR_OBJECTS[swp->pw.mj.plactptr[mtnnum].objnum].pObject;
        NJS_MOTION* p_motion;

        if (swp->pw.mj.mtnmode == 2)
        {
            p_motion = swp->pw.mj.plmtnptr;
        }
        else
        {
            if ((twp->flag & BALL_FLAG) && swp->pw.ch_num_multi != PLNO_METAL_SONIC && (swp->flag & 0x11))
            {
                mtnnum = 30;
                p_object = CHAR_OBJECTS[swp->pw.mj.plactptr[mtnnum].objnum].pObject;
            }

            p_motion = CHAR_MOTIONS[swp->pw.mj.plactptr[swp->pw.mj.plactptr[mtnnum].actnum].actnum].pMotion;
        }

        njCnkAnimateMotion(p_object, p_motion, swp->pw.mj.nframe);
    }

    njCnkSetMotionCallback(NULL);

    njPopMatrixEx();

    switch (swp->pw.ch_num_multi) {
    case PLNO_SONIC:
        SonicDrawMod(twp, &swp->pw, mtnnum);
        break;

    case PLNO_SHADOW:
        TeriosDrawMod(twp, &swp->pw, mtnnum);
        break;

    case PLNO_AMY:
        AmyDrawMod(twp, &swp->pw, mtnnum);
        break;

    case PLNO_METAL_SONIC:
        MetalSonicDrawMod(twp, &swp->pw, mtnnum);
        break;
    }
}

static void
MilesDisplayMod(taskwk* twp, playerwk* pwp, int motion)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    const int objnum = pwp->mj.plactptr[motion].objnum;

    if (objnum == 208)
    {
        NJS_CNK_OBJECT* mod_head = CHAR_OBJECTS[214].pObject;

        if (mod_head == nullptr)
            mod_head = object_miles_head_mod;

        njTranslateEx(&pwp->user0_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(mod_head);

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->righthand_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 1.0f, 1.0f, 0.7f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->lefthand_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 1.0f, 1.0f, 0.7f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->rightfoot_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 2.6f, 1.0f, 1.0f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->leftfoot_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 2.6f, 1.0f, 1.0f);
        DrawBasicShadow();

        /** Miles Tails **/
        if (MilesTailModifiers)
        {
            njPopMatrixEx();
            njPushMatrixEx();

            MILESWK* const mileswp = (MILESWK*)pwp;

            njTranslateV(NULL, &pwp->tails_pos);

            Angle ang_adj  =  0x1200;
            Angle ang_spin = -mileswp->TailsAngX;
            f32   scl_x    =  3.2f;
            f32   add_y    = -2.5f;

            const Angle ang_main = njArcTan2(pwp->tails_vec.z, pwp->tails_vec.x);

            switch (motion)
            {
                case 8: case 9:
                {
                    ang_adj = 0x4000;
                    scl_x = njAbs( njSin(ang_spin + NJM_DEG_ANG(90.f)) ) * 3.2f;
                    ang_spin = 0;
                    break;
                }
                case 90:
                {
                    add_y = 1.5f;
                //  [[fallthrough]];
                }
                case 91: case 93:
                {
                    ang_adj = 0x4000;
                    break;
                }
            }

            njPushMatrixEx();

            njRotateY(NULL, ((0x8000 + ang_adj) - ang_main) + ang_spin);
            njTranslate(NULL, scl_x, add_y, 0.0f);
            njScale(NULL, scl_x, 1.0f, 1.0f);
            DrawBasicShadow();

            njPopMatrixEx();
            njPushMatrixEx();

            njRotateY(NULL, ((0x8000 - ang_adj) - ang_main) + ang_spin);
            njTranslate(NULL, scl_x, add_y, 0.0f);
            njScale(NULL, scl_x, 1.0f, 1.0f);
            DrawBasicShadow();

            njPopMatrixEx();
        }
    }
    else if (objnum == 6)
    {
        njTranslate(NULL, twp->pos.x, twp->pos.y + 0.3f, twp->pos.z);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 5.0f, 1.0f, 5.0f);
        DrawBasicShadow();
    }

    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}

static void
MilesDisplayerShadowHook(task* tp)
{
    taskwk*  const     twp = tp->twp;
    MILESWK* const mileswp = GET_MILESWK(tp);

    njGetMatrix(&mtx_MilesBase);
    njInvertMatrix(&mtx_MilesBase);

    MilesWorkPointer = mileswp;

    njCnkSetMotionCallback(MilesMotionCallBack_p);

    njPushMatrixEx();

    int mtnnum = mileswp->pw.mj.mtnnum;

    njTranslateEx(&twp->pos);
    njRotateZ(NULL, twp->ang.z);
    njRotateX(NULL, twp->ang.x);
    njRotateY(NULL, 0x8000 - twp->ang.y);

    if (mtnnum == 11 && twp->flag & 0x03)
    {
        njTranslate(NULL, 0.0f, -1.0f, 0.0f);
        njRotateZ(NULL, 0x2000);
        njScale(NULL, 0.7f, 1.1f, 0.8f);
    }

    njScaleEx(&twp->scl);

    if (twp->mode == 54 && mileswp->pw.motion_list)
    {
        njCnkAnimateMotion(CHAR_OBJECTS[mileswp->pw.mj.plactptr->objnum].pObject, *mileswp->pw.motion_list, flt_1DEB070);
    }
    else
    {
        if (mileswp->pw.mj.mtnmode == 2)
        {
            njCnkAnimateMotion(
                CHAR_OBJECTS[mileswp->pw.mj.plactptr[mtnnum].objnum].pObject, 
                mileswp->pw.mj.plmtnptr, 
                mileswp->pw.mj.nframe);
        }
        else
        {
            const int actnum = mileswp->pw.mj.plactptr[mtnnum].actnum;

            njCnkAnimateMotion(
                CHAR_OBJECTS[mileswp->pw.mj.plactptr[mtnnum].objnum].pObject,
                CHAR_MOTIONS[mileswp->pw.mj.plactptr[actnum].actnum].pMotion,
                mileswp->pw.mj.nframe);
        }
    }

    njPopMatrixEx();

    njCnkSetMotionCallback(NULL);

    MilesDisplayMod(twp, &mileswp->pw, mtnnum);
}

static void
EggmanDisplayMod(taskwk* twp, playerwk* pwp, int mtnnum)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    const int objnum = pwp->mj.plactptr[mtnnum].objnum;

    if (objnum == 230)
    {
        NJS_CNK_OBJECT* mod_head = CHAR_OBJECTS[236].pObject;

        if (mod_head == nullptr)
            mod_head = object_eggman_head_mod;

        njTranslateEx(&pwp->user0_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(mod_head);

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->righthand_pos);
        njTranslate(NULL, 0.0f, -2.0f, 0.0f);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 1.6f, 1.0f, 1.1f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->lefthand_pos);
        njTranslate(NULL, 0.0f, -2.0f, 0.0f);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 1.6f, 1.0f, 1.1f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->rightfoot_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 2.2f, 1.0f, 0.7f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->leftfoot_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 2.2f, 1.0f, 0.7f);
        DrawBasicShadow();
    }

    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}

static void
EggmanDisplayerShadowHook(task* tp)
{
    taskwk*   const      twp = tp->twp;
    EGGMANWK* const eggmanwp = GET_EGGMANWK(tp);

    njGetMatrix(&mtx_EggmanBase);
    njInvertMatrix(&mtx_EggmanBase);

    EggmanWorkPointer = eggmanwp;

    njCnkSetMotionCallback(EggmanMotionCallBack_p);

    const int mtnnum = eggmanwp->pw.mj.mtnnum;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateZ(NULL, twp->ang.z);
    njRotateX(NULL, twp->ang.x);
    njRotateY(NULL, 0x8000 - twp->ang.y);
    njScaleEx(&twp->scl);

    if (twp->mode == 54 && eggmanwp->pw.motion_list)
    {
        njCnkAnimateMotion(CHAR_OBJECTS[eggmanwp->pw.mj.plactptr->objnum].pObject, *eggmanwp->pw.motion_list, flt_1DEB070);
    }
    else
    {
        if (eggmanwp->pw.mj.mtnmode == 2)
        {
            njCnkAnimateMotion(
                CHAR_OBJECTS[eggmanwp->pw.mj.plactptr[mtnnum].objnum].pObject, 
                eggmanwp->pw.mj.plmtnptr, 
                eggmanwp->pw.mj.nframe);
        }
        else
        {
            const actnum = eggmanwp->pw.mj.plactptr[mtnnum].actnum;

            njCnkAnimateMotion(
                CHAR_OBJECTS[eggmanwp->pw.mj.plactptr[mtnnum].objnum].pObject,
                CHAR_MOTIONS[eggmanwp->pw.mj.plactptr[actnum].actnum].pMotion,
                eggmanwp->pw.mj.nframe);
        }
    }

    njPopMatrixEx();

    njCnkSetMotionCallback(NULL);

    EggmanDisplayMod(twp, &eggmanwp->pw, mtnnum);
}

static void
KnucklesDisplayMod(taskwk* twp, playerwk* pwp, int motion)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    const int objnum = pwp->mj.plactptr[motion].objnum;

    if (objnum == 142)
    {
        NJS_CNK_OBJECT* mod_head = CHAR_OBJECTS[148].pObject;

        if (mod_head == nullptr)
            mod_head = object_knuckles_head_mod;

        njTranslateEx(&pwp->user0_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(mod_head);

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->righthand_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 1.4f, 1.0f, 1.1f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->lefthand_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 1.4f, 1.0f, 1.1f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->rightfoot_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 2.6f, 1.0f, 1.2f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->leftfoot_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 2.6f, 1.0f, 1.2f);
        DrawBasicShadow();
    }

    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}

#define PlayerNumCheck      DATA_REF(bool, 0x0174B009)

#define KnucklesDisplayer   FUNC_PTR(void, __cdecl, (task*), 0x0072EF20)


static const void* const sub_446960_p = (void*)0x00446960;
static Sangle
sub_446960(Angle ang1, Angle ang2, Sangle sang)
{
    Angle result;

    __asm
    {
        mov cx , [sang]
        mov edx, [ang2]
        mov eax, [ang1]

        call sub_446960_p

        mov [result], eax
    }

    return (Sangle)result;
}

static void
RougeDisplayMod(taskwk* twp, playerwk* pwp, int mtnnum)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    const int objnum = pwp->mj.plactptr[mtnnum].objnum;

    if (objnum == 171)
    {
        NJS_CNK_OBJECT* mod_head = CHAR_OBJECTS[178].pObject;

        if (mod_head == nullptr)
            mod_head = object_rouge_head_mod;
        
        njTranslateEx(&pwp->user0_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(mod_head);

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->righthand_pos);
        njTranslate(NULL, 0.0f, -2.0f, 0.0f);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 1.2f, 1.0f, 0.7f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->lefthand_pos);
        njTranslate(NULL, 0.0f, -2.0f, 0.0f);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 1.2f, 1.0f, 0.7f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->rightfoot_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 2.0f, 1.0f, 1.0f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->leftfoot_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 2.0f, 1.0f, 1.0f);
        DrawBasicShadow();
    }

    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}

static void
TikalDisplayMod(taskwk* twp, playerwk* pwp, int mtnnum)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    const int objnum = pwp->mj.plactptr[mtnnum].objnum;

    if (objnum == 483)
    {
        njTranslateEx(&pwp->user0_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(object_tikal_head_mod);

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->righthand_pos);
        njTranslate(NULL, 0.0f, -2.0f, 0.0f);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 1.4f, 1.0f, 1.1f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->lefthand_pos);
        njTranslate(NULL, 0.0f, -2.0f, 0.0f);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 1.4f, 1.0f, 1.1f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->rightfoot_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 2.6f, 1.0f, 1.2f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->leftfoot_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 2.6f, 1.0f, 1.2f);
        DrawBasicShadow();
    }

    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}

static void
ChaosDisplayMod(taskwk* twp, playerwk* pwp, int mtnnum)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    const int objnum = pwp->mj.plactptr[mtnnum].objnum;

    if (objnum == 507)
    {
        njTranslateEx(&pwp->user0_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(object_chaos_head_mod);

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->righthand_pos);
        njTranslate(NULL, 0.0f, -2.0f, 0.0f);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 1.4f, 1.0f, 1.1f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->lefthand_pos);
        njTranslate(NULL, 0.0f, -2.0f, 0.0f);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 1.4f, 1.0f, 1.1f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->rightfoot_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 2.6f, 1.0f, 1.2f);
        DrawBasicShadow();

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->leftfoot_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njScale(NULL, 2.6f, 1.0f, 1.2f);
        DrawBasicShadow();
    }

    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}

static void
KnucklesDisplayerShadowHook(task* tp)
{
    taskwk* const  twp = tp->twp;
    KNUCKLESWK* const knwp = GET_KNUCKLESWK(tp);

    njGetMatrix(&mtx_KnucklesBase);
    njInvertMatrix(&mtx_KnucklesBase);

    KnucklesWorkPointer = knwp;

    switch (knwp->pw.ch_num_multi) {
    case PLNO_KNUCKLES:
        njCnkSetMotionCallback(KnucklesMotionCallBack_p);
        break;

    case PLNO_ROUGE:
        njCnkSetMotionCallback(RougeMotionCallBack_p);
        break;

    case PLNO_TICAL:
        njCnkSetMotionCallback((void*)0x0072F690);
        break;

    case PLNO_CHAOS0:
        njCnkSetMotionCallback((void*)0x007315E0);
        break;
    }

    const int mtnnum = knwp->pw.mj.mtnnum;

    njPushMatrixEx();

    if (twp->mode != 18)
    {
        NJS_POINT3 point_in = {
            .x = 0.0f,
            .y = -knwp->pw.p.height * 0.5f,
            .z = 0.0f
        };

        NJS_POINT3 point_out;

        CCL_INFO* p_cinfo = twp->cwp->info;

        njPushMatrix(&_nj_unit_matrix_);

        njRotateZ(NULL, twp->ang.z);
        njRotateX(NULL, twp->ang.x);
        njRotateY(NULL, -twp->ang.y);

        njCalcVector(NULL, &point_in, &point_out);

        njPopMatrixEx();

        point_out.x += p_cinfo->center.x;
        point_out.y += p_cinfo->center.y;
        point_out.z += p_cinfo->center.z;

        njTranslateEx(&point_out);
    }
    else
        njTranslateEx(&twp->pos);

    /** Multiplayer intro **/
    if (MultiIntroPno != knwp->pw.pl_num + 1)
    {
        njRotateZ(NULL, twp->ang.z);
        njRotateX(NULL, twp->ang.x);
        njRotateY(NULL, 0x8000 - twp->ang.y);

        /** Flying **/
        if (mtnnum == 105)
        {
            motionwk* mwp = tp->mwp;

            knwp->someAng0 = sub_446960(-(Sangle)(mwp->ang_aim.x - twp->ang.y), 2048, knwp->someAng0);

            njRotateX(NULL, knwp->someAng0);

        } /** Climb attatch **/
        else if (mtnnum == 106)
        {
            const int actnum = knwp->pw.mj.plactptr[mtnnum].actnum;

            float some_ang = (1.0f - knwp->pw.mj.nframe / CHAR_MOTIONS[knwp->pw.mj.plactptr[actnum].actnum].pMotion->nbFrame) * (float)knwp->someAng0;

            njRotateX(NULL, (Angle)some_ang);
        }
    }
    else
        njRotateY(NULL, 0x8000 - twp->ang.y);

    njScaleEx(&twp->scl);

    if (twp->mode == 54 && knwp->pw.motion_list)
    {
        njCnkAnimateMotion(CHAR_OBJECTS[knwp->pw.mj.plactptr->objnum].pObject, *knwp->pw.motion_list, flt_1DEB070);
    }
    else
    {
        if (knwp->pw.mj.mtnmode == 2)
        {
            njCnkAnimateMotion(
                CHAR_OBJECTS[knwp->pw.mj.plactptr[mtnnum].objnum].pObject,
                knwp->pw.mj.plmtnptr,
                knwp->pw.mj.nframe);
        }
        else
        {
            const int actnum = knwp->pw.mj.plactptr[mtnnum].actnum;

            njCnkAnimateMotion(
                CHAR_OBJECTS[knwp->pw.mj.plactptr[mtnnum].objnum].pObject,
                CHAR_MOTIONS[knwp->pw.mj.plactptr[actnum].actnum].pMotion,
                knwp->pw.mj.nframe);
        }
    }

    njPopMatrixEx();

    njCnkSetMotionCallback(NULL);

    switch (knwp->pw.ch_num_multi) {
    case PLNO_KNUCKLES:
        KnucklesDisplayMod(twp, &knwp->pw, mtnnum);
        break;

    case PLNO_ROUGE:
        RougeDisplayMod(twp, &knwp->pw, mtnnum);
        break;

    case PLNO_TICAL:
        TikalDisplayMod(twp, &knwp->pw, mtnnum);
        break;

    case PLNO_CHAOS0:
        ChaosDisplayMod(twp, &knwp->pw, mtnnum);
        break;
    }
}

static void
TornadoWalkerDisplayMod(taskwk* twp, playerwk* pwp, int mtnnum)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    const int objnum = pwp->mj.plactptr[mtnnum].objnum;

    if (objnum == 293)
    {
        NJS_CNK_OBJECT* mod_body = CHAR_OBJECTS[297].pObject;

        if (mod_body == nullptr)
            mod_body = object_twalker_body_mod;

        njTranslateEx(&pwp->user0_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(mod_body);

        njPopMatrixEx();
        njPushMatrixEx();

        NJS_CNK_OBJECT* mod_foot1 = CHAR_OBJECTS[300].pObject;

        if (mod_foot1 == nullptr)
            mod_foot1 = object_twalker_foot_mod;

        njTranslateEx(&pwp->rightfoot_pos);

        if (TornadoFootFix)
            njTranslate(NULL, 0.0f, 0.4f, 0.0f);

        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(mod_foot1);

        njPopMatrixEx();
        njPushMatrixEx();

        NJS_CNK_OBJECT* mod_foot2 = CHAR_OBJECTS[301].pObject;

        if (mod_foot2 == nullptr)
            mod_foot2 = object_twalker_foot_mod;

        njTranslateEx(&pwp->leftfoot_pos);

        if (TornadoFootFix)
            njTranslate(NULL, 0.0f, 0.4f, 0.0f);

        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(mod_foot2);
    }

    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}


static void
EggWalkerDisplayMod(taskwk* twp, playerwk* pwp, int mtnnum)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    const int objnum = pwp->mj.plactptr[mtnnum].objnum;

    if (objnum == 248)
    {
        NJS_CNK_OBJECT* mod_body = CHAR_OBJECTS[252].pObject;

        if (mod_body == nullptr)
            mod_body = object_ewalker_body_mod;

        njTranslateEx(&pwp->user0_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(mod_body);

        njPopMatrixEx();
        njPushMatrixEx();

        NJS_CNK_OBJECT* mod_foot = CHAR_OBJECTS[255].pObject;

        if (mod_foot == nullptr)
            mod_foot = object_ewalker_foot_mod;

        njTranslateEx(&pwp->rightfoot_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(mod_foot);

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->leftfoot_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(mod_foot);
    }

    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}

static void
ChaoWalkerDisplayMod(taskwk* twp, playerwk* pwp, int mtnnum)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    const int objnum = pwp->mj.plactptr[mtnnum].objnum;

    if (objnum == 450)
    {
        njTranslateEx(&pwp->user0_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(object_cwalker_body_mod);

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->rightfoot_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(object_cwalker_foot_mod);

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->leftfoot_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(object_cwalker_foot_mod);
    }

    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}

static void
DarkChaoWalkerDisplayMod(taskwk* twp, playerwk* pwp, int mtnnum)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    const int objnum = pwp->mj.plactptr[mtnnum].objnum;

    if (objnum == 473)
    {
        njTranslateEx(&pwp->user0_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(object_dwalker_body_mod);

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->rightfoot_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(object_dwalker_foot_mod);

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->leftfoot_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(object_dwalker_foot_mod);
    }

    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}

#define ChaoWalkerMotionCallBack_p      ((void*)0x00745CC0)
#define DarkChaoWalkerMotionCallBack_p  ((void*)0x00746B00)

static void
EggWalkerDisplayerShadowHook(task* tp)
{
    taskwk*   const twp = tp->twp;
    WALKERWK* const wwp = GET_WALKERWK(tp);

    njGetMatrix(&mtx_EWalkerBase);
    njInvertMatrix(&mtx_EWalkerBase);

    EggWalkerWorkPointer = wwp;

    switch (wwp->pw.ch_num_multi) {
    case PLNO_TAILS_WALKER:
        njCnkSetMotionCallback(TornadoWalkerMotionCallBack_p);
        break;

    case PLNO_EGG_WALKER:
        njCnkSetMotionCallback(EggWalkerMotionCallBack_p);
        break;

    case PLNO_CHAO_WALKER:
        njCnkSetMotionCallback(ChaoWalkerMotionCallBack_p);
        break;

    case PLNO_DARK_WALKER:
        njCnkSetMotionCallback(DarkChaoWalkerMotionCallBack_p);
        break;
    }

    njPushMatrixEx();

    const int mtnnum = wwp->pw.mj.mtnnum;

    if (twp->mode == 51)
    {
        NJS_POINT3 point_in = {
            .x = 0.0f,
            .y = -wwp->pw.p.height * 0.5f,
            .z = 0.0f
        };

        NJS_POINT3 point_out;

        CCL_INFO* p_cinfo = twp->cwp->info;

        njPushMatrix(&_nj_unit_matrix_);

        njRotateZ(NULL, twp->ang.z);
        njRotateX(NULL, twp->ang.x);
        njRotateY(NULL, -twp->ang.y);

        njCalcVector(NULL, &point_in, &point_out);

        njPopMatrixEx();

        point_out.x += p_cinfo->center.x;
        point_out.y += p_cinfo->center.y;
        point_out.z += p_cinfo->center.z;

        njTranslateEx(&point_out);
    }
    else
        njTranslateEx(&twp->pos);

    /** Multiplayer intro **/
    if (MultiIntroPno != wwp->pw.pl_num + 1)
    {
        njRotateZ(NULL, twp->ang.z);
        njRotateX(NULL, twp->ang.x);
    }
    
    njRotateY(NULL, 0x8000 - twp->ang.y);
    
    njScaleEx(&twp->scl);

    if (twp->mode == 54 && wwp->pw.motion_list)
    {
        njCnkAnimateMotion(CHAR_OBJECTS[wwp->pw.mj.plactptr->objnum].pObject, *wwp->pw.motion_list, flt_1DEB070);
    }
    else
    {
        if (wwp->pw.mj.mtnmode == 2)
        {
            njCnkAnimateMotion(
                CHAR_OBJECTS[wwp->pw.mj.plactptr[mtnnum].objnum].pObject,
                wwp->pw.mj.plmtnptr,
                wwp->pw.mj.nframe);
        }
        else
        {
            const int actnum = wwp->pw.mj.plactptr[mtnnum].actnum;

            njCnkAnimateMotion(
                CHAR_OBJECTS[wwp->pw.mj.plactptr[mtnnum].objnum].pObject,
                CHAR_MOTIONS[wwp->pw.mj.plactptr[actnum].actnum].pMotion,
                wwp->pw.mj.nframe);
        }
    }

    njPopMatrixEx();

    njCnkSetMotionCallback(NULL);

    switch (wwp->pw.ch_num_multi) {
    case PLNO_TAILS_WALKER:
        TornadoWalkerDisplayMod(twp, &wwp->pw, mtnnum);
        break;

    case PLNO_EGG_WALKER:
        EggWalkerDisplayMod(twp, &wwp->pw, mtnnum);
        break;

    case PLNO_CHAO_WALKER:
        ChaoWalkerDisplayMod(twp, &wwp->pw, mtnnum);
        break;

    case PLNO_DARK_WALKER:
        DarkChaoWalkerDisplayMod(twp, &wwp->pw, mtnnum);
        break;
    }
}

void* __cdecl
CreateNoStencilTexture(void)
{
    return NULL;
}

void
CHS_PlayerInit(void)
{
    /** Sonic/Shadow/Amy/Metal **/
    object_sonic_head_mod      = RF_GetCnkObject("figure/sonic_head_mod.sa2mdl");
    object_amy_head_mod        = RF_GetCnkObject("figure/amy_head_mod.sa2mdl");
    object_terios_head_mod     = RF_GetCnkObject("figure/terios_head_mod.sa2mdl");
    object_metalsonic_head_mod = RF_GetCnkObject("figure/metalsonic_head_mod.sa2mdl");

    WriteJump(0x0071E520, SonicDisplayerShadowHook);

    /** Miles **/
    object_miles_head_mod = RF_GetCnkObject("figure/miles_head_mod.sa2mdl");

    WriteRetn(0x00750C40);
    WriteJump(0x0074FF20, MilesDisplayerShadowHook);

    MilesTailModifiers = CNF_GetInt(CNF_PLAYER_MILESTAILMOD);

    /** Eggman **/
    object_eggman_head_mod = RF_GetCnkObject("figure/eggman_head_mod.sa2mdl");

    WriteRetn(0x0073F1A0);
    WriteJump(0x0073E8B0, EggmanDisplayerShadowHook);

    /** Knuckles/Rouge/Tikal/Chaos **/
    object_knuckles_head_mod = RF_GetCnkObject("figure/knuckles_head_mod.sa2mdl");
    object_rouge_head_mod    = RF_GetCnkObject("figure/rouge_head_mod.sa2mdl");
    object_tikal_head_mod    = RF_GetCnkObject("figure/tikal_head_mod.sa2mdl");
    object_chaos_head_mod    = RF_GetCnkObject("figure/chaos_head_mod.sa2mdl");

    WriteRetn(0x00730100);
    WriteJump(0x0072DCE0, KnucklesDisplayerShadowHook);
    WriteRetn(0x007311E0);
    WriteJump(0x0072E390, KnucklesDisplayerShadowHook);

    /** Mech Walkers **/
    object_twalker_body_mod = RF_GetCnkObject("figure/twalker_body_mod.sa2mdl");
    object_twalker_foot_mod = RF_GetCnkObject("figure/twalker_foot_mod.sa2mdl");
    object_ewalker_body_mod = RF_GetCnkObject("figure/ewalker_body_mod.sa2mdl");
    object_ewalker_foot_mod = RF_GetCnkObject("figure/ewalker_foot_mod.sa2mdl");
    object_cwalker_body_mod = RF_GetCnkObject("figure/cwalker_body_mod.sa2mdl");
    object_cwalker_foot_mod = RF_GetCnkObject("figure/cwalker_foot_mod.sa2mdl");
    object_dwalker_body_mod = RF_GetCnkObject("figure/dwalker_body_mod.sa2mdl");
    object_dwalker_foot_mod = RF_GetCnkObject("figure/dwalker_foot_mod.sa2mdl");

    WriteRetn(0x00748AF0);
    WriteRetn(0x00745310);
    WriteJump(0x00745910, EggWalkerDisplayerShadowHook);

    TornadoFootFix = CNF_GetInt(CNF_PLAYER_TWALKFOOTMOD);

    /** PInitialize **/
    WriteCall(0x00459D53, CreateNoStencilTexture);
}
