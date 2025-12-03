/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* writejump                                        */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** Game ************************************************************************/
#include <samt/sonic/task.h>    /* task                                             */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_ninja.h>           /* rf ninja                                         */
#include <rf_njcnk.h>           /* emulated njcnk draw functions                    */

/****** Self ************************************************************************/
#include <rf_module/rfm_common/rfc_newdisp/rfcd_internal.h> /* parent & siblings    */

/************************/
/*  Game Data           */
/************************/
/****** Spring A/B ******************************************************************/
#define texlist_spring          DATA_ARY(NJS_TEXLIST   , 0x00B533C0, [1])

#define object_springa          DATA_ARY(NJS_CNK_OBJECT, 0x00B53DFC, [1])
#define object_springb          DATA_ARY(NJS_CNK_OBJECT, 0x00B5484C, [1])

/****** 3 Spring ********************************************************************/
#define texlist_3spring         DATA_ARY(NJS_TEXLIST   , 0x00B1DF18, [1])

#define object_3spring          DATA_ARY(NJS_CNK_OBJECT, 0x00B1ECC4, [1])

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
CNK_ObjectSpringADisp(const task* tp)
{
    const taskwk* twp = tp->twp;

    njSetTexture(texlist_spring);

    njPushMatrixEx();

    njTranslateV(NULL, &twp->pos);

    njRotateZ(NULL, twp->ang.z);
    njRotateX(NULL, twp->ang.x);
    njRotateY(NULL, twp->ang.y);

    const s32 wtimer = twp->wtimer;

    if (wtimer)
    {
        const f32 scl = 1.f / (f32)wtimer;

        njScale(NULL, scl, scl, scl);
    }

    NJS_CNK_OBJECT* p_base   = object_springa;
    NJS_CNK_OBJECT* p_spring = p_base->child;
    NJS_CNK_OBJECT* p_face   = p_spring->child;

    /** spring base **/

    njCnkDirectDrawModel(p_base->model);

    const f32 sprf = *((f32*)&tp->mwp);

    /** spring spring **/

    njTranslateV(NULL, (NJS_POINT3*)p_spring->pos);

    njScale(NULL, 0.98f, sprf + 1.f, 0.98f);

    njCnkDirectDrawModel(p_spring->model);

    /** spring face **/

    njTranslateV(NULL, (NJS_POINT3*)p_face->pos);

    njTranslate(NULL, 0.f, sprf * 4.f, 0.f);

    njCnkDirectDrawModel(p_face->model);

    njPopMatrixEx();
}

static void
CNK_ObjectSpringBDisp(const task* tp)
{
    const taskwk* twp = tp->twp;

    njSetTexture(texlist_spring);

    njPushMatrixEx();

    njTranslateV(NULL, &twp->pos);

    njRotateZ(NULL, twp->ang.z);
    njRotateX(NULL, twp->ang.x);
    njRotateY(NULL, twp->ang.y);

    const s32 wtimer = twp->wtimer;

    if (wtimer)
    {
        const f32 scl = 1.f / (f32)wtimer;

        njScale(NULL, scl, scl, scl);
    }

    /** spring base **/

    NJS_CNK_OBJECT* p_base   = object_springb;
    NJS_CNK_OBJECT* p_spring = p_base->child;
    NJS_CNK_OBJECT* p_face   = p_spring->child;

    njCnkDirectDrawModel(p_base->model);

    const f32 sprf = *((f32*)&tp->mwp);

    njPushMatrixEx();

    njTranslateV(NULL, (NJS_POINT3*)p_spring->pos);

    /** spring face **/

    njPushMatrixEx();

    njTranslateV(NULL, (NJS_POINT3*)p_face->pos);

    njTranslate(NULL, 0.f, sprf * 4.f, 0.f);

    njCnkDirectDrawModel(p_face->model);

    njPopMatrixEx();

    /** spring spring **/

    njScale(NULL, 0.98f, sprf + 1.f, 0.98f);

    njCnkDirectDrawModel(p_spring->model);

    njPopMatrix(2);
}

static void
CNK_Object3SpringDisp(const task* tp)
{
    const taskwk*   twp = tp->twp;
    const motionwk* mwp = tp->mwp;

    njSetTexture(texlist_3spring);

    njPushMatrixEx();

    njTranslateV(NULL, &twp->pos);

    njRotateZ(NULL, twp->ang.z);
    njRotateX(NULL, twp->ang.x);
    njRotateY(NULL, twp->ang.y);

    NJS_CNK_OBJECT* p_base = object_3spring;

    njCnkDirectDrawModel(p_base->model);

    const f32 trans = njAbs(mwp->spd.x);

    njTranslate(NULL, 0.f, trans, trans);

    njCnkDirectDrawModel(p_base->child->model);

    njPopMatrixEx();
}

/****** Init ************************************************************************/
void
RFCD_SpringInit(void)
{
    WriteJump(0x006C4AA0, CNK_ObjectSpringADisp);
    WriteJump(0x006C50E0, CNK_ObjectSpringBDisp);
    WriteJump(0x006D94D0, CNK_Object3SpringDisp);
}
