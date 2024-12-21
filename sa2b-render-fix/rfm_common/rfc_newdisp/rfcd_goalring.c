/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>          /* core                                             */
#include <sa2b/writeop.h>       /* writejump                                        */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h>   /* ninja                                            */

/****** Game ************************************************************************/
#include <sa2b/sonic/task.h>    /* task                                             */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_njcnk.h>           /* emulated njcnk draw functions                    */
#include <rf_renderstate.h>     /* render state                                     */
#include <rf_mdlutil.h>         /* change strip flag                                */

/****** Self ************************************************************************/
#include <rfm_common/rfc_newdisp/rfcd_internal.h> /* parent & siblings              */

/************************/
/*  Game Functions      */
/************************/
/****** Texture Shadow **************************************************************/
#define DisplayRingShadow           FUNC_PTR(void, __cdecl, (void), 0x006BD500)

/************************/
/*  Game Data           */
/************************/
/****** Fog ********************************************************************/
#define DisableObjectFog            DATA_REF(s32, 0x01AEFE64)

/****** Goalring ********************************************************************/
#define texlist_goalring            DATA_ARY(NJS_TEXLIST, 0x00B4DA90, [1])
#define texlist_goalring_text       DATA_ARY(NJS_TEXLIST, 0x00B4DA98, [1])
#define texlist_goalring_restart    DATA_ARY(NJS_TEXLIST, 0x00B4DAA0, [1])

#define object_goalring             DATA_ARY(NJS_CNK_OBJECT, 0x00B4EAE4, [1])
#define object_goalring_text        DATA_ARY(NJS_CNK_OBJECT, 0x00B4EC84, [1])
#define object_goalring_restart     DATA_ARY(NJS_CNK_OBJECT, 0x00B4EE24, [1])

/****** Lost Chao *******************************************************************/
#define texlist_lostchao            DATA_ARY(NJS_TEXLIST, 0x00B4DAD8, [1])
#define texlist_lostchao_found      DATA_ARY(NJS_TEXLIST, 0x00B5266C, [1])

#define object_lostchao             DATA_ARY(NJS_CNK_OBJECT, 0x00B507D4, [1])
#define object_lostchao_found       DATA_ARY(NJS_CNK_OBJECT, 0x00B5266C, [1])

#define motion_lostchao             DATA_ARY(NJS_MOTION, 0x00B4D83C, [1])
#define motion_lostchao_found       DATA_ARY(NJS_MOTION, 0x00B4EE5C, [1])

#define LostChaoShadowScale         DATA_REF(NJS_VECTOR, 0x00B53320)
#define GoalRingShadowScale         DATA_REF(NJS_VECTOR, 0x00B526A4)

#define LostChaoWorkP               DATA_REF(NJS_MATRIX*, 0x01AEFD94)

/************************/
/*  Source              */
/************************/
/****** Inline **********************************************************************/
static inline void
ObjectGoalringDisp_LostChao(const task* tp)
{
    const taskwk* twp = tp->twp;

    /** draw ground shadow **/

    njPushMatrixEx();

    njTranslate(NULL, twp->pos.x, twp->scl.z + 0.3f, twp->pos.z);

    njRotateY(NULL, twp->ang.y);

    njTranslate(NULL, 0.f, 0.f, 0.8f);

    njScaleV(NULL, &LostChaoShadowScale);

    DisplayRingShadow();

    njPopMatrixEx();

    /** draw lost chao **/

    njPushMatrixEx();

    njTranslateV(NULL, &twp->pos);

    njRotateY(NULL, twp->ang.y);

    if (DisableObjectFog)
        njFogDisable();

    NJS_MATRIX* p_mtx = (void*)tp->mwp;

    LostChaoWorkP = p_mtx;

    njCnkSetMotionCallback((void*)0x006C6C00);

    if (twp->smode == 0)
    {
        njSetTexture(texlist_lostchao);

        njCnkEasyDrawMotion(object_lostchao, motion_lostchao, twp->scl.y);
    }
    else
    {
        njSetTexture(texlist_lostchao_found);

        njCnkEasyDrawMotion(object_lostchao_found, motion_lostchao_found, twp->scl.y);
    }

    njCnkSetMotionCallback(NULL);

    /** genuinely no clue **/

    njPushMatrixEx();

    njInvertMatrix(NULL);

    njMultiMatrix(NULL, p_mtx);

    njGetMatrix(p_mtx);

    njPopMatrixEx();

    /** finish up **/

    tp->mwp->ang_spd.z = 1;

    LostChaoWorkP = nullptr;

    if (DisableObjectFog)
        njFogEnable();

    njPopMatrixEx();
}

static inline void
ObjectGoalringDisp_Goalring(const task* tp)
{
    const taskwk* twp = tp->twp;

    if (DisableObjectFog)
        njFogDisable();

    /** draw ground shadow **/

    if ( !tp->disp_shad )
    {
        njPushMatrixEx();

        njTranslate(NULL, twp->pos.x, twp->scl.z + 0.8f, twp->pos.z);

        njRotateY(NULL, twp->ang.y);

        njScaleV(NULL, &GoalRingShadowScale);

        DisplayRingShadow();

        njPopMatrixEx();
    }

    njPushMatrixEx();

    njTranslateV(NULL, &twp->pos);

    njRotateY(NULL, twp->ang.y);

    if (twp->smode)
    {
        f32 scl = 1.f - ((f32)twp->wtimer / 60.f);

        if (scl < 0.f)
            scl = 0.f;

        njScale(NULL, scl, 1.f, scl);
    }

    /** inverse text faces **/

    RFRS_SetCullMode(RFRS_CULLMD_INVERSE);

    if (twp->btimer == 1)
    {
        njSetTexture(texlist_goalring_text);

        njCnkSimpleDrawModel(object_goalring_text->model);
    }
    else if (twp->btimer == 2)
    {
        njSetTexture(texlist_goalring_restart);

        njCnkSimpleDrawModel(object_goalring_restart->model);
    }

    RFRS_SetCullMode(RFRS_CULLMD_END);

    /** goal ring **/

    njSetTexture(texlist_goalring);

    njCnkDirectDrawModel(object_goalring->model);

    /** normal text faces **/

    RFRS_SetCullMode(RFRS_CULLMD_NORMAL);

    if (twp->btimer == 1)
    {
        njSetTexture(texlist_goalring_text);

        njCnkSimpleDrawModel(object_goalring_text->model);
    }
    else if (twp->btimer == 2)
    {
        njSetTexture(texlist_goalring_restart);

        njCnkSimpleDrawModel(object_goalring_restart->model);
    }

    RFRS_SetCullMode(RFRS_CULLMD_END);

    njPopMatrixEx();

    if (DisableObjectFog)
        njFogEnable();
}

/****** Static **********************************************************************/
static void
CNK_ObjectGoalringDisp(const task* tp)
{
    const taskwk* twp = tp->twp;

    if (twp->ang.x % 3 == 1)
    {
        ObjectGoalringDisp_LostChao(tp);
    }
    else
    {
        ObjectGoalringDisp_Goalring(tp);
    }
}

/****** Init ************************************************************************/
void
RFCD_GoalringInit(void)
{
    WriteRetn(0x006C6CD0);                         // kill regular disp
    WriteJump(0x006C6F10, CNK_ObjectGoalringDisp); // replace disp_sort

    WriteNOP(0x006C651E, 0x006C6525); // stop setting 'tp->disp'

    CnkModelMaterialFlagOn(0x00B4EACC, 1, NJD_FST_UA); // add UA flag to ring
}
