#include <samt/core.h>
#include <samt/writeop.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Source **/
#include <samt/sonic/task.h>
#include <samt/sonic/njctrl.h>
#include <samt/sonic/score.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_file.h>
#include <rf_njcnk.h>

#define DisableObjectFog        DATA_REF(b32        , 0x01AEFE64)
#define texlist_udreel          DATA_ARY(NJS_TEXLIST, 0x00B129F8, [1])

static NJS_CNK_OBJECT* object_udreel;

static void
ObjectUDReelCnkDisplayer(task* tp)
{
    taskwk* const twp = tp->twp;
    anywk* const rwp = TO_ANYWK(tp->mwp);

    njSetTexture(texlist_udreel);

    /** Top **/
    NJS_CNK_OBJECT* obj = object_udreel;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);

    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njCnkDirectDrawModel(obj->model);

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    /** Wire **/
    obj = object_udreel->child;

    NJS_CNK_MODEL* wire_mdl = obj->model;

    const float oldr = wire_mdl->r;

    wire_mdl->r = 0.0f;

    njScale(NULL, 1.0f, rwp[4].work.f[1], 1.0f);

    njCnkEasyDrawModel(wire_mdl);

    wire_mdl->r = oldr;

    njPopMatrixEx();

    /** Handle **/
    obj = obj->child;

    njTranslate(NULL, 0.0f, rwp[4].work.f[0], 0.0f);

    if (DisableObjectFog)
        njFogDisable();

    if ( GetGameTime() % 46 >= 23 && !(twp->mode & 0x1) )
        njCnkEasyDrawModel(obj->model);
    else
        njCnkDirectDrawModel(obj->model);

    if (DisableObjectFog)
        njFogEnable();

    njPopMatrixEx();
}

#define texlist_udreel_golem    DATA_ARY(NJS_TEXLIST, 0x166CFF0, [1])

static void
ObjectUDReelGolemCnkDisplayer(task* tp)
{
    taskwk* const twp = tp->twp;
    anywk* const rwp = TO_ANYWK(tp->mwp);

    njSetTexture(texlist_udreel_golem);

    /** Top **/
    NJS_CNK_OBJECT* obj = object_udreel;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);

    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njCnkDirectDrawModel(obj->model);

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    /** Wire **/
    obj = object_udreel->child;

    NJS_CNK_MODEL* wire_mdl = obj->model;

    const float oldr = wire_mdl->r;

    wire_mdl->r = 0.0f;

    njScale(NULL, 1.0f, rwp[4].work.f[1], 1.0f);

    njCnkEasyDrawModel(wire_mdl);

    wire_mdl->r = oldr;

    njPopMatrixEx();

    /** Handle **/
    obj = obj->child;

    njTranslate(NULL, 0.0f, rwp[4].work.f[0], 0.0f);

    if (DisableObjectFog)
        njFogDisable();

    if ( GetGameTime() % 46 >= 23 && !(twp->mode & 0x1) )
        njCnkEasyDrawModel(obj->model);
    else
        njCnkDirectDrawModel(obj->model);

    if (DisableObjectFog)
        njFogEnable();

    njPopMatrixEx();
}

void
RFCD_UDReelInit(void)
{
    WriteJump(0x006E6170, ObjectUDReelCnkDisplayer);
    WriteJump(0x004BC210, ObjectUDReelGolemCnkDisplayer); // Golem

    object_udreel = RF_ChunkLoadObjectFile("object/udreel");
}
