#include <sa2b/core.h>
#include <sa2b/memory.h>
#include <sa2b/funchook.h>
#include <sa2b/memutil.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Util **/
#include <sa2b/util/devutil.h>

/** Source **/
#include <sa2b/src/task.h>
#include <sa2b/src/player.h>
#include <sa2b/src/c_colli.h>
#include <sa2b/src/njctrl.h>
#include <sa2b/src/debug.h>

/** Figure **/
#define SAMT_INCLUDE_FUNC_PTRS
#include <sa2b/src/figure/sonic.h>
#include <sa2b/src/figure/shadow.h>
#include <sa2b/src/figure/miles.h>
#include <sa2b/src/figure/eggman.h>
#include <sa2b/src/figure/knuckles.h>
#include <sa2b/src/figure/rouge.h>
#include <sa2b/src/figure/ewalker.h>
#include <sa2b/src/figure/twalker.h>
#undef  SAMT_INCLUDE_FUNC_PTRS

/** Render Fix **/
#include <rf_file.h>
#include <rf_draw.h>

/** Self (?) **/

/** Constant **/
#define SonicDisplayer      FuncPtr(void, __cdecl, (TASK*), 0x00720090)

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

const void* const HideSomeCharModels_p = (void*)0x0046F0D0;
static void
HideSomeCharModels(int pno)
{
    __asm
    {
        mov eax, [pno]
        call HideSomeCharModels_p
    }
}

const void* const DrawAndUnhideCharModels_p = (void*)0x0046F1E0;
static void
DrawAndUnhideCharModels(int pno)
{
    __asm
    {
        mov eax, [pno]
        call DrawAndUnhideCharModels_p
    }
}

#define flt_1DEB070         DataRef(float32_t, 0x01DEB070)
#define MultiIntroPno       DataRef(int8_t   , 0x0174B009)

#define BALL_OBJ_NUM        (6)

static void
SonicDrawMod(TASKWK* twp, PLAYERWK* pwp, int motion)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    if (pwp->mj.plactptr[motion].objnum == BALL_OBJ_NUM)
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

        njCnkModDrawObject(pwp->ch_num_multi != ADV2_PLNO_AMY ?
            object_sonic_head_mod :
            object_amy_head_mod);

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
TeriosDrawMod(TASKWK* twp, PLAYERWK* pwp, int motion)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    if (pwp->mj.plactptr[motion].objnum == BALL_OBJ_NUM)
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

        njCnkModDrawObject(pwp->ch_num_multi != ADV2_PLNO_METAL_SONIC ?
            object_terios_head_mod :
            object_metalsonic_head_mod);

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

#define BALL_FLAG   (0x100)

#define AmyMotionCallBack_p             FuncPtr(void, __cdecl, (NJS_CNK_OBJECT*), 0x0071F040)
#define MetalSonicMotionCallBack_p      FuncPtr(void, __cdecl, (NJS_CNK_OBJECT*), 0x0071FBE0)

static void __cdecl
SonicDisplayerShadowHook(TASK* tp)
{
    TASKWK*  const twp = tp->twp;
    SONICWK* const swp = GET_SONICWK(tp);

    njGetMatrix(&mtx_SonicBase);
    njInvertMatrix(&mtx_SonicBase);

    SonicWorkPointer = swp;

    switch (swp->pw.ch_num_multi) {
    case ADV2_PLNO_SONIC:
        njCnkSetMotionCallback(SonicMotionCallBack_p);
        break;

    case ADV2_PLNO_SHADOW:
        njCnkSetMotionCallback(ShadowMotionCallBack_p);
        break;

    case ADV2_PLNO_AMY:
        njCnkSetMotionCallback(AmyMotionCallBack_p);
        break;

    case ADV2_PLNO_METAL_SONIC:
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
        HideSomeCharModels(swp->pw.pl_num);
        njCnkAnimateMotion(CHAR_OBJECTS[swp->pw.mj.plactptr->objnum].pObject, *swp->pw.motion_list, flt_1DEB070);
        DrawAndUnhideCharModels(swp->pw.pl_num);
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
            if ((twp->flag & BALL_FLAG) && swp->pw.ch_num_multi != ADV2_PLNO_METAL_SONIC && (swp->field_35C[4] & 0x11))
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

    if (!swp->pw.ch_num)
        SonicDrawMod(twp, &swp->pw, mtnnum);
    else
        TeriosDrawMod(twp, &swp->pw, mtnnum);
}

static void
MilesDisplayMod(TASKWK* twp, PLAYERWK* pwp, int motion)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    const int objnum = pwp->mj.plactptr[motion].objnum;

    if (objnum == 208)
    {
        njTranslateEx(&pwp->user0_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(object_miles_head_mod);

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

        ___NOTE("Make this optional");
        /** Miles Tails **/
        if (true)
        {
            njPopMatrixEx();
            njPushMatrixEx();

            MILESWK* const mileswp = (MILESWK*)pwp;

            njTranslateEx(&pwp->tails_pos);

            Angle angadj =  0x1200;
            Angle angspn = -mileswp->TailsAngX;
            float scl_x  =  3.2f;
            float add_y  = -2.5f;

            switch (motion) {
            case 8: case 9:
                angadj = 0x4000;
                scl_x = fabsf(sinf((float)angspn * (1.0f / 16384.0f))) * 3.2f;
                angspn = 0;
                break;

            case 90: 
                add_y = 1.5f;

            case 91: case 93:
                angadj = 0x4000;
                break;
            }

            njPushMatrixEx();

            njRotateY(NULL, ((0x8000 + angadj) - twp->ang.y) + angspn);
            njTranslate(NULL, scl_x, add_y, 0.0f);
            njScale(NULL, scl_x, 1.0f, 1.0f);
            DrawBasicShadow();

            njPopMatrixEx();
            njPushMatrixEx();

            njRotateY(NULL, ((0x8000 - angadj) - twp->ang.y) + angspn);
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
MilesDisplayerShadowHook(TASK* tp)
{
    TASKWK*  const     twp = tp->twp;
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
        HideSomeCharModels(mileswp->pw.pl_num);
        njCnkAnimateMotion(CHAR_OBJECTS[mileswp->pw.mj.plactptr->objnum].pObject, *mileswp->pw.motion_list, flt_1DEB070);
        DrawAndUnhideCharModels(mileswp->pw.pl_num);
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
EggmanDisplayMod(TASKWK* twp, PLAYERWK* pwp, int mtnnum)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    const int objnum = pwp->mj.plactptr[mtnnum].objnum;

    if (objnum == 230)
    {
        njTranslateEx(&pwp->user0_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(object_eggman_head_mod);

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
EggmanDisplayerShadowHook(TASK* tp)
{
    TASKWK*   const      twp = tp->twp;
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
        HideSomeCharModels(eggmanwp->pw.pl_num);
        njCnkAnimateMotion(CHAR_OBJECTS[eggmanwp->pw.mj.plactptr->objnum].pObject, *eggmanwp->pw.motion_list, flt_1DEB070);
        DrawAndUnhideCharModels(eggmanwp->pw.pl_num);
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
KnucklesDisplayMod(TASKWK* twp, PLAYERWK* pwp, int motion)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    const int objnum = pwp->mj.plactptr[motion].objnum;

    if (objnum == 142)
    {
        njTranslateEx(&pwp->user0_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(object_knuckles_head_mod);

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

#define PlayerNumCheck      DataRef(bool, 0x0174B009)

#define KnucklesDisplayer   FuncPtr(void, __cdecl, (TASK*), 0x0072EF20)


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
RougeDisplayMod(TASKWK* twp, PLAYERWK* pwp, int mtnnum)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    const int objnum = pwp->mj.plactptr[mtnnum].objnum;

    if (objnum == 171)
    {
        njTranslateEx(&pwp->user0_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(object_rouge_head_mod);

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
TikalDisplayMod(TASKWK* twp, PLAYERWK* pwp, int mtnnum)
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
ChaosDisplayMod(TASKWK* twp, PLAYERWK* pwp, int mtnnum)
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
KnucklesDisplayerShadowHook(TASK* tp)
{
    TASKWK* const  twp = tp->twp;
    KNUCKLESWK* const knwp = GET_KNUCKLESWK(tp);

    njGetMatrix(&mtx_KnucklesBase);
    njInvertMatrix(&mtx_KnucklesBase);

    KnucklesWorkPointer = knwp;

    switch (knwp->pw.ch_num_multi) {
    case ADV2_PLNO_KNUCKLES:
        njCnkSetMotionCallback(KnucklesMotionCallBack_p);
        break;

    case ADV2_PLNO_ROUGE:
        njCnkSetMotionCallback(RougeMotionCallBack_p);
        break;

    case ADV2_PLNO_TIKAL:
        njCnkSetMotionCallback((void*)0x0072F690);
        break;

    case ADV2_PLNO_CHAOS:
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
            MOTIONWK* mwp = tp->mwp;

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
        HideSomeCharModels(knwp->pw.pl_num);
        njCnkAnimateMotion(CHAR_OBJECTS[knwp->pw.mj.plactptr->objnum].pObject, *knwp->pw.motion_list, flt_1DEB070);
        DrawAndUnhideCharModels(knwp->pw.pl_num);
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
    case ADV2_PLNO_KNUCKLES:
        KnucklesDisplayMod(twp, &knwp->pw, mtnnum);
        break;

    case ADV2_PLNO_ROUGE:
        RougeDisplayMod(twp, &knwp->pw, mtnnum);
        break;

    case ADV2_PLNO_TIKAL:
        TikalDisplayMod(twp, &knwp->pw, mtnnum);
        break;

    case ADV2_PLNO_CHAOS:
        ChaosDisplayMod(twp, &knwp->pw, mtnnum);
        break;
    }
}

static void
TornadoWalkerDisplayMod(TASKWK* twp, PLAYERWK* pwp, int mtnnum)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    const int objnum = pwp->mj.plactptr[mtnnum].objnum;

    if (objnum == 293)
    {
        njTranslateEx(&pwp->user0_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(object_twalker_body_mod);

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->rightfoot_pos);

        if (true)
            njTranslate(NULL, 0.0f, 0.4f, 0.0f);

        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(object_twalker_foot_mod);

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->leftfoot_pos);

        if (true)
            njTranslate(NULL, 0.0f, 0.4f, 0.0f);

        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(object_twalker_foot_mod);
    }

    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}


static void
EggWalkerDisplayMod(TASKWK* twp, PLAYERWK* pwp, int mtnnum)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    const int objnum = pwp->mj.plactptr[mtnnum].objnum;

    if (objnum == 248)
    {
        njTranslateEx(&pwp->user0_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(object_ewalker_body_mod);

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->rightfoot_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(object_ewalker_foot_mod);

        njPopMatrixEx();
        njPushMatrixEx();

        njTranslateEx(&pwp->leftfoot_pos);
        njRotateY(NULL, 0x8000 - twp->ang.y);
        njCnkModDrawObject(object_ewalker_foot_mod);
    }

    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}

static void
ChaoWalkerDisplayMod(TASKWK* twp, PLAYERWK* pwp, int mtnnum)
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
DarkChaoWalkerDisplayMod(TASKWK* twp, PLAYERWK* pwp, int mtnnum)
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
EggWalkerDisplayerShadowHook(TASK* tp)
{
    TASKWK*   const twp = tp->twp;
    WALKERWK* const wwp = GET_WALKERWK(tp);

    njGetMatrix(&mtx_EWalkerBase);
    njInvertMatrix(&mtx_EWalkerBase);

    EggWalkerWorkPointer = wwp;

    switch (wwp->pw.ch_num_multi) {
    case ADV2_PLNO_TORNADO:
        njCnkSetMotionCallback(TornadoWalkerMotionCallBack_p);
        break;

    case ADV2_PLNO_EGGWALKER:
        njCnkSetMotionCallback(EggWalkerMotionCallBack_p);
        break;

    case ADV2_PLNO_CHAO_WALKER:
        njCnkSetMotionCallback(ChaoWalkerMotionCallBack_p);
        break;

    case ADV2_PLNO_DARK_CHAO_WALKER:
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
        HideSomeCharModels(wwp->pw.pl_num);
        njCnkAnimateMotion(CHAR_OBJECTS[wwp->pw.mj.plactptr->objnum].pObject, *wwp->pw.motion_list, flt_1DEB070);
        DrawAndUnhideCharModels(wwp->pw.pl_num);
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
    case ADV2_PLNO_TORNADO:
        TornadoWalkerDisplayMod(twp, &wwp->pw, mtnnum);
        break;

    case ADV2_PLNO_EGGWALKER:
        EggWalkerDisplayMod(twp, &wwp->pw, mtnnum);
        break;

    case ADV2_PLNO_CHAO_WALKER:
        ChaoWalkerDisplayMod(twp, &wwp->pw, mtnnum);
        break;

    case ADV2_PLNO_DARK_CHAO_WALKER:
        DarkChaoWalkerDisplayMod(twp, &wwp->pw, mtnnum);
        break;
    }
}

void* __cdecl
CreateNoStencilTexture()
{
    return NULL;
}

void
CHS_PlayerInit()
{
    /** Sonic/Shadow/Amy/Metal **/
    object_sonic_head_mod      = RF_ChunkLoadObjectFile("sonic_head_mod");
    object_amy_head_mod        = RF_ChunkLoadObjectFile("amy_head_mod");
    object_terios_head_mod     = RF_ChunkLoadObjectFile("terios_head_mod");
    object_metalsonic_head_mod = RF_ChunkLoadObjectFile("metalsonic_head_mod");

    WriteJump(0x0071E520, SonicDisplayerShadowHook);

    /** Miles **/
    object_miles_head_mod = RF_ChunkLoadObjectFile("miles_head_mod");

    WriteRetn(0x00750C40);
    WriteJump(0x0074FF20, MilesDisplayerShadowHook);

    /** Eggman **/
    object_eggman_head_mod = RF_ChunkLoadObjectFile("eggman_head_mod");

    WriteRetn(0x0073F1A0);
    WriteJump(0x0073E8B0, EggmanDisplayerShadowHook);

    /** Knuckles/Rouge/Tikal/Chaos **/
    object_knuckles_head_mod = RF_ChunkLoadObjectFile("knuckles_head_mod");
    object_rouge_head_mod    = RF_ChunkLoadObjectFile("rouge_head_mod");
    object_tikal_head_mod    = RF_ChunkLoadObjectFile("tikal_head_mod");
    object_chaos_head_mod    = RF_ChunkLoadObjectFile("chaos_head_mod");

    WriteRetn(0x00730100);
    WriteJump(0x0072DCE0, KnucklesDisplayerShadowHook);
    WriteRetn(0x007311E0);
    WriteJump(0x0072E390, KnucklesDisplayerShadowHook);

    /** Mech Walkers **/
    object_twalker_body_mod = RF_ChunkLoadObjectFile("twalker_body_mod");
    object_twalker_foot_mod = RF_ChunkLoadObjectFile("twalker_foot_mod");
    object_ewalker_body_mod = RF_ChunkLoadObjectFile("ewalker_body_mod");
    object_ewalker_foot_mod = RF_ChunkLoadObjectFile("ewalker_foot_mod");
    object_cwalker_body_mod = RF_ChunkLoadObjectFile("cwalker_body_mod");
    object_cwalker_foot_mod = RF_ChunkLoadObjectFile("cwalker_foot_mod");
    object_dwalker_body_mod = RF_ChunkLoadObjectFile("dwalker_body_mod");
    object_dwalker_foot_mod = RF_ChunkLoadObjectFile("dwalker_foot_mod");

    WriteRetn(0x00748AF0);
    WriteRetn(0x00745310);
    WriteJump(0x00745910, EggWalkerDisplayerShadowHook);

    /** PInitialize **/
    WriteCall(0x00459D53, CreateNoStencilTexture);
}
