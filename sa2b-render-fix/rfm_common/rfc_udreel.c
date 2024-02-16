#include <sa2b/core.h>
#include <sa2b/memutil.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/src/task.h>
#include <sa2b/src/njctrl.h>
#include <sa2b/src/score.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_file.h>

#define DisableObjectFog        DataRef(bool32_t, 0x01AEFE64)
#define texlist_udreel          DataAry(NJS_TEXLIST, 0x00B129F8, [1])

static NJS_CNK_OBJECT* object_o_udreel;

static void
ObjectUDReelCnkDisplayer(TASK* tp)
{
    TASKWK* const twp = tp->twp;
    ANYWK* const rwp = TO_ANYWK(tp->mwp);

    njSetTexture(texlist_udreel);

    /** Top **/
    NJS_CNK_OBJECT* obj = object_o_udreel;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);

    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njCnkDrawModel(obj->model);

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    /** Wire **/
    obj = object_o_udreel->child;

    NJS_CNK_MODEL* wire_mdl = obj->model;

    const float oldr = wire_mdl->r;

    wire_mdl->r = 0.0f;

    njScale(NULL, 1.0f, rwp[4].work.f[1], 1.0f);

    njCnkDrawModel(wire_mdl);

    wire_mdl->r = oldr;

    njPopMatrixEx();

    /** Handle **/
    obj = obj->child;

    njTranslate(NULL, 0.0f, rwp[4].work.f[0], 0.0f);

    if (DisableObjectFog)
        njFogDisable();

    SaveConstantMaterial();
    OnControl3D(NJD_CONTROL_3D_CONSTANT_MATERIAL);

    if (GetGameTime() % 46 >= 23 && (twp->mode & 0x1) == 0)
        SetConstantMaterial(1.0f, 1.0f, 1.0f, 1.0f);
    else
        SetConstantMaterial(1.0f, 0.7f, 0.7f, 0.7f);

    njCnkDrawModel(obj->model);

    OffControl3D(NJD_CONTROL_3D_CONSTANT_MATERIAL);
    LoadConstantMaterial();

    if (DisableObjectFog)
        njFogEnable();

    njPopMatrixEx();
}

#define texlist_udreel_golem    DataAry(NJS_TEXLIST, 0x166CFF0, [1])

static void
ObjectUDReelGolemCnkDisplayer(TASK* tp)
{
    TASKWK* const twp = tp->twp;
    ANYWK* const rwp = TO_ANYWK(tp->mwp);

    njSetTexture(texlist_udreel_golem);

    /** Top **/
    NJS_CNK_OBJECT* obj = object_o_udreel;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);

    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njCnkDrawModel(obj->model);

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    /** Wire **/
    obj = object_o_udreel->child;

    NJS_CNK_MODEL* wire_mdl = obj->model;

    const float oldr = wire_mdl->r;

    wire_mdl->r = 0.0f;

    njScale(NULL, 1.0f, rwp[4].work.f[1], 1.0f);

    njCnkDrawModel(wire_mdl);

    wire_mdl->r = oldr;

    njPopMatrixEx();

    /** Handle **/
    obj = obj->child;

    njTranslate(NULL, 0.0f, rwp[4].work.f[0], 0.0f);

    if (DisableObjectFog)
        njFogDisable();

    OnControl3D(NJD_CONTROL_3D_CONSTANT_MATERIAL);

    if (GetGameTime() % 46 >= 23 && (twp->mode & 0x1) == 0)
        SetConstantMaterial(1.0f, 1.0f, 1.0f, 1.0f);
    else
        SetConstantMaterial(1.0f, 0.7f, 0.7f, 0.7f);

    njCnkDrawModel(obj->model);
    ResetConstantMaterial();

    OffControl3D(NJD_CONTROL_3D_CONSTANT_MATERIAL);

    if (DisableObjectFog)
        njFogEnable();

    njPopMatrixEx();
}

void
RFC_UDReelInit(void)
{
    WriteJump(0x006E6170, ObjectUDReelCnkDisplayer);
    WriteJump(0x004BC210, ObjectUDReelGolemCnkDisplayer); // Golem

    object_o_udreel = RF_ChunkLoadObjectFile("o_udreel");
}
