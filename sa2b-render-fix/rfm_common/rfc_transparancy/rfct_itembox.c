#include <sa2b/core.h>
#include <sa2b/memutil.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/src/task.h>
#include <sa2b/src/njctrl.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_draw.h>
#include <rf_renderstate.h>
#include <rf_enemywk.h>

typedef struct 
{
    int texid;
    void(__cdecl* exec)(TASK* tp, int pno);
}
ITEMBOX_INFO;

#define texlist_itembox         DataAry(NJS_TEXLIST  , 0x00B493F8, [1])
#define model_itembox_bubble    DataAry(NJS_CNK_MODEL, 0x00B497C4, [1])

#define ItemBoxInfoList         DataAry(ITEMBOX_INFO, 0x00B4D120, [11])
#define DisableObjectFog        DataRef(bool32_t    , 0x01AEFE64)

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
ObjectItemBoxDispSort_RF(TASK* tp)
{
    TASKWK* const twp = tp->twp;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);
    njRotateZ(NULL, twp->ang.z);
    njScale(NULL, twp->scl.z, twp->scl.z, twp->scl.z);

    if (DisableObjectFog)
        njFogDisable();

    njSetTexture(texlist_itembox);

    RFRS_SetCullMode(RFRS_CULLMD_INVERSE);
    njCnkDrawModel_Broken(model_itembox_bubble);

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
    njCnkDrawModel_Broken(model_itembox_bubble);

    RFRS_SetCullMode(RFRS_CULLMD_END);

    if (DisableObjectFog)
        njFogEnable();

    njPopMatrixEx();
}



#define texlist_itemboxair          DataAry(NJS_TEXLIST  , 0x00B48784, [1])
#define model_itemboxair_bubble     DataAry(NJS_CNK_MODEL, 0x00B48B44, [1])

#define model_itemboxair_base       DataAry(NJS_CNK_MODEL, 0x00B492EC, [1])
#define model_itemboxair_top        DataAry(NJS_CNK_MODEL, 0x00B48F64, [1])

#define ItemBoxAirInfoList          DataAry(ITEMBOX_INFO, 0x00B493A0, [11])

static void
ObjectItemBoxAirDispSort_RF(TASK* tp)
{
    TASKWK* const twp = tp->twp;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
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

        _nj_constant_attr_and_ = 0xFF;
        _nj_constant_attr_or_  = 0x800;
    }

    njSetTexture(texlist_itemboxair);

    njCnkDrawModel_Broken(model_itemboxair_base);
    njCnkDrawModel_Broken(model_itemboxair_top);

    RFRS_SetCullMode(RFRS_CULLMD_INVERSE);
    njCnkDrawModel_Broken(model_itemboxair_bubble);

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
    njCnkDrawModel_Broken(model_itemboxair_bubble);

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
RFCT_ItemBoxInit(void)
{
    WriteJump(0x006C83B0, ObjectItemBoxDispSort_RF);
    WriteJump(0x006C9500, ObjectItemBoxAirDispSort_RF);
    WriteRetn(0x006C93C0); // ItemBoxAirDisplayer
}
