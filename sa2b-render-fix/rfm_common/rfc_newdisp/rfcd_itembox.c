#include <sa2b/core.h>
#include <sa2b/writeop.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/sonic/task.h>
#include <sa2b/sonic/njctrl.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_draw.h>
#include <rf_renderstate.h>
#include <rf_enemywk.h>
#include <rf_njcnk.h>

typedef struct 
{
    int texid;
    void(__cdecl* exec)(task* tp, int pno);
}
ITEMBOX_INFO;

#define texlist_itembox         DATA_ARY(NJS_TEXLIST  , 0x00B493F8, [1])

#define object_itembox          DATA_ARY(NJS_CNK_OBJECT, 0x00B4A19C, [1])

#define ItemBoxInfoList         DATA_ARY(ITEMBOX_INFO, 0x00B4D120, [11])
#define DisableObjectFog        DATA_REF(b32         , 0x01AEFE64)

static void
ObjectItemBoxDisp_RF(task* tp)
{
    NJS_CNK_OBJECT* obj_base = object_itembox;
    NJS_CNK_OBJECT* obj_top  = obj_base->child;
//  NJS_CNK_OBJECT* obj_dome = obj_top->sibling;

    const taskwk* twp = tp->twp;

    njSetTexture(texlist_itembox);

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);
    njRotateZ(NULL, twp->ang.z);
    njScale(NULL, twp->scl.z, twp->scl.z, twp->scl.z);

    if (DisableObjectFog)
        njFogDisable();

    njCnkDirectDrawModel(obj_base->model);
    njCnkDirectDrawModel(obj_top->model);

    if (DisableObjectFog)
        njFogEnable();

    njPopMatrixEx();
}

static void
ObjectItemBoxGotDisp_RF(task* tp)
{
    NJS_CNK_OBJECT* obj_base = object_itembox;
//  NJS_CNK_OBJECT* obj_top  = obj_base->child;
//  NJS_CNK_OBJECT* obj_dome = obj_top->sibling;

    const taskwk* twp = tp->twp;

    njSetTexture(texlist_itembox);

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);
    njRotateZ(NULL, twp->ang.z);

    njCnkDirectDrawModel(obj_base->model);

    njPopMatrixEx();
}

static const void* const DrawItemBoxItemTexture_p = (void*)0x006DF030;
static int32_t
DrawItemBoxItemTexture(int texid, NJS_POINT3* pos, Angle angy, float scl)
{
    int32_t result;
    __asm
    {
        push [scl]
        push [angy]
        mov edi, [pos]
        mov ecx, [texid]

        call DrawItemBoxItemTexture_p

        add esp, 8

        mov [result], eax
    }
    return result;
}

static void
ObjectItemBoxDispSort_RF(task* tp)
{
    NJS_CNK_OBJECT* obj_base = object_itembox;
    NJS_CNK_OBJECT* obj_top  = obj_base->child;
    NJS_CNK_OBJECT* obj_dome = obj_top->sibling;

    taskwk* const twp = tp->twp;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);
    njRotateZ(NULL, twp->ang.z);
    njScale(NULL, twp->scl.z, twp->scl.z, twp->scl.z);

    if (DisableObjectFog)
        njFogDisable();

    njSetTexture(texlist_itembox);

    RFRS_SetCullMode(RFRS_CULLMD_INVERSE);
    {
        njCnkDirectDrawModel(obj_dome->model);
    }
    RFRS_SetCullMode(RFRS_CULLMD_END);

    const int texid = ItemBoxInfoList[(int)tp->fwp].texid;

    if (texid != 7)
    {
        NJS_POINT3 p3 = {
            .x = 0.0f,
            .y = 7.5f,
            .z = 0.0f
        };

        DrawItemBoxItemTexture(texid, &p3, (Angle)(twp->scl.y * 182.0444488525391f), 6.0f);
    }

    njSetTexture(texlist_itembox);

    RFRS_SetCullMode(RFRS_CULLMD_NORMAL);
    {
        njCnkDirectDrawModel(obj_dome->model);
    }
    RFRS_SetCullMode(RFRS_CULLMD_END);

    if (DisableObjectFog)
        njFogEnable();

    njPopMatrixEx();
}

#define texlist_itemboxair          DATA_ARY(NJS_TEXLIST  , 0x00B48784, [1])

#define object_itemboxair           DATA_ARY(NJS_CNK_OBJECT, 0x00B49304, [1])

#define ItemBoxAirInfoList          DATA_ARY(ITEMBOX_INFO, 0x00B493A0, [11])

static void
ObjectItemBoxAirDispSort_RF(task* tp)
{
    NJS_CNK_OBJECT* obj_base = object_itemboxair;
    NJS_CNK_OBJECT* obj_top  = obj_base->child;
    NJS_CNK_OBJECT* obj_item = obj_top->sibling;
    NJS_CNK_OBJECT* obj_dome = obj_item->sibling;

    taskwk* const twp = tp->twp;

    njPushMatrixEx();

    njTranslateV(NULL, &twp->pos);
    njRotateY(NULL, twp->ang.y);
    njRotateZ(NULL, twp->ang.z);
    njScale(NULL, twp->scl.z, twp->scl.z, twp->scl.z);

    if (twp->mode == 4)
        njFogDisable();

    /** I have to do this weird bool thing or
        else the optimizer breaks this function **/
    const bool scaling = (twp->scl.z > 1.0f);

    if (scaling)
    {
        float flt = 1.0f - (twp->scl.z - 1.0f) * 0.25f;

        if (flt > 1.0f)
            flt = 1.0f;
        else if (flt < 0.0f)
            flt = 0.0f;

        SaveControl3D();
        SaveConstantAttr();

        SetConstantMaterial(flt * 0.7f, 1.0f, 1.0f, 1.0f);

        OffControl3D(NJD_CONTROL_3D_CONSTANT_TEXTURE_MATERIAL | NJD_CONTROL_3D_OFFSET_MATERIAL);
        OnControl3D(NJD_CONTROL_3D_CNK_CONSTANT_ATTR | NJD_CONTROL_3D_CONSTANT_MATERIAL);

        njSetConstantAttr(NJD_FST_MASK, NJD_FST_UA);
    }

    njSetTexture(texlist_itemboxair);

    njCnkDirectDrawModel(obj_base->model);
    njCnkDirectDrawModel(obj_top->model);

    RFRS_SetCullMode(RFRS_CULLMD_INVERSE);
    {
        njCnkDirectDrawModel(obj_dome->model);
    }
    RFRS_SetCullMode(RFRS_CULLMD_END);

    const int texid = ItemBoxAirInfoList[twp->btimer].texid;

    if (texid != 7)
    {
        NJS_POINT3 p3 = {
            .x = 0.0f,
            .y = 14.5f,
            .z = 0.0f
        };

        DrawItemBoxItemTexture(texid, &p3, (Angle)(twp->scl.y * 182.0444488525391f), 9.0f);
    }

    njSetTexture(texlist_itemboxair);

    RFRS_SetCullMode(RFRS_CULLMD_NORMAL);
    {
        njCnkDirectDrawModel(obj_dome->model);
    }
    RFRS_SetCullMode(RFRS_CULLMD_END);

    if (scaling)
    {
        LoadControl3D();
        LoadConstantAttr();
        ResetConstantMaterial();
    }

    if (twp->mode == 4)
        njFogEnable();

    njPopMatrixEx();
}

void
RFCD_ItemBoxInit(void)
{
    /** Item Box, Ground **/

    WriteJump(0x006C8280, ObjectItemBoxDisp_RF);
    WriteJump(0x006C83B0, ObjectItemBoxDispSort_RF);
    WriteJump(0x006C8810, ObjectItemBoxGotDisp_RF);

    /** Item Box, Air **/

    WriteJump(0x006C9500, ObjectItemBoxAirDispSort_RF);
    WriteRetn(0x006C93C0); // ItemBoxAirDisplayer
    WriteNOP(0x006C917C, 0x006C9183); // tp->disp = func

    /** Object Fix **/

    /** These functions use DirectDraw, but they remove all diffuse color from the
      models before compiling. I'm emulating this here. **/

    // itembox
    {
        NJS_CNK_OBJECT* obj_base = object_itembox;
        NJS_CNK_OBJECT* obj_top  = obj_base->child;
        NJS_CNK_OBJECT* obj_dome = obj_top->sibling;

        RF_CnkModelMaterialDiffuse(obj_base->model, -1, 0xFF, 0xFF, 0xFF, 0xFF);
        RF_CnkModelMaterialDiffuse(obj_top->model , -1, 0xFF, 0xFF, 0xFF, 0xFF);
        RF_CnkModelMaterialDiffuse(obj_dome->model, -1, 0xFF, 0xFF, 0xFF, 0xFF);
    }

    // itembox air
    {
        NJS_CNK_OBJECT* obj_base = object_itemboxair;
        NJS_CNK_OBJECT* obj_top  = obj_base->child;
        NJS_CNK_OBJECT* obj_item = obj_top->sibling;
        NJS_CNK_OBJECT* obj_dome = obj_item->sibling;

        RF_CnkModelMaterialDiffuse(obj_base->model, -1, 0xFF, 0xFF, 0xFF, 0xFF);
        RF_CnkModelMaterialDiffuse(obj_top->model , -1, 0xFF, 0xFF, 0xFF, 0xFF);
        RF_CnkModelMaterialDiffuse(obj_dome->model, -1, 0xFF, 0xFF, 0xFF, 0xFF);
    }
    
}
