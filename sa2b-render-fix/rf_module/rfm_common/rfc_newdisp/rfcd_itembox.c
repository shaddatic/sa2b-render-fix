/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/writeop.h>           /* writejump                                                */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Game ************************************************************************************/
#include <samt/sonic/task.h>        /* task                                                     */
#include <samt/sonic/njctrl.h>      /* task                                                     */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_ninja.h>               /* cnkdraw                                                  */
#include <rf_njcnk.h>               /* easysimpledirect                                         */
#include <rf_renderstate.h>         /* setcullmode                                              */
#include <rf_util.h>                /* switchdisplayer                                          */
#include <rf_mdlutil.h>             /* changediffuse                                            */

/****** RF Utility ******************************************************************************/
#include <rfu_float.h>              /* replacefloat                                             */

/****** Self ************************************************************************************/
#include <rf_module/rfm_common/rfc_newdisp/rfcd_internal.h> /* parent & siblings                */

/********************************/
/*  Structures                  */
/********************************/
/****** Itemboxwk *******************************************************************************/
typedef struct 
{
    int texid;
    void(__cdecl* exec)(task* tp, int pno);
}
ITEMBOX_INFO;

/********************************/
/*  Game Defs                   */
/********************************/
/****** Texlists ********************************************************************************/
#define texlist_itembox             DATA_ARY(NJS_TEXLIST  , 0x00B493F8, [1])
#define texlist_itemboxair          DATA_ARY(NJS_TEXLIST  , 0x00B48784, [1])
#define texlist_itemboxballoon      DATA_ARY(NJS_TEXLIST  , 0x00B19008, [1])

/****** Objects *********************************************************************************/
#define object_itembox              DATA_ARY(NJS_CNK_OBJECT, 0x00B4A19C, [1])
#define object_itemboxair           DATA_ARY(NJS_CNK_OBJECT, 0x00B49304, [1])
#define object_itemboxballoon       DATA_ARY(NJS_CNK_OBJECT, 0x00B198A4, [1])

/****** Itembox Info ****************************************************************************/
#define ItemBoxInfoList             DATA_ARY(ITEMBOX_INFO, 0x00B4D120, [11])
#define ItemBoxAirInfoList          DATA_ARY(ITEMBOX_INFO, 0x00B493A0, [11])

/****** Disable Fog *****************************************************************************/
#define DisableObjectFog            DATA_REF(b32         , 0x01AEFE64)

/********************************/
/*  Source                      */
/********************************/
/****** Task ************************************************************************************/
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

static void
ObjectItemBoxBalloonDisplayer_RF(task* tp)
{
    ___NOTE("When back-face culling is removed, this hack should be removed too");

    RFRS_SetCullMode(RFRS_CULLMD_AUTO); // fix for people who still have back-face culling off.

    const taskwk* twp = tp->twp;

    njSetTexture(texlist_itemboxballoon);

    if (twp->mode == 4 || DisableObjectFog)
    {
        njFogDisable();
    }

    f32 alpha_mat = 1.f - ( (twp->scl.z - 1.f) * 0.5f );

    alpha_mat = CLAMP(alpha_mat, 0.f, 1.f);

    SaveControl3D();
    SaveConstantAttr();

    OffControl3D(NJD_CONTROL_3D_CONSTANT_TEXTURE_MATERIAL|NJD_CONTROL_3D_OFFSET_MATERIAL);
    OnControl3D(NJD_CONTROL_3D_CNK_CONSTANT_ATTR|NJD_CONTROL_3D_CONSTANT_MATERIAL);

    njSetConstantAttr(NJD_FST_MASK, NJD_FST_UA);

    SetConstantMaterial(alpha_mat * 0.7f, 1.f, 1.f, 1.f);

    njPushMatrixEx();
    {
        const s16 wtimer = twp->wtimer;

        const f32 posy = ( njSin( (wtimer + 800) << 8) * 4.f ) + twp->pos.y;

        njTranslate(NULL, twp->pos.x, posy, twp->pos.z);

        njRotateY(NULL, twp->ang.y);

        const Angle angx = NJM_DEG_ANG( njSin(640 * wtimer) * 3.5f );

        njRotateX(NULL, angx);

        const f32 sclx = ( njCos(2304 * wtimer) * 0.01f ) + twp->scl.z;
        const f32 scly = ( njSin(wtimer << 11)  * 0.01f ) + twp->scl.z;
        const f32 sclz = ( njCos(2128 * wtimer) * 0.01f ) + twp->scl.z;

        njScale(NULL, sclx, scly, sclz);

        njCnkSimpleDrawModel(object_itemboxballoon->model);
    }
    njPopMatrixEx();

    ResetConstantMaterial();

    LoadConstantAttr();
    LoadControl3D();

    if (twp->mode == 4 || DisableObjectFog)
    {
        njFogEnable();
    }

    RFRS_SetCullMode(RFRS_CULLMD_END);
}

/****** Init ************************************************************************************/
void
RFCD_ItemBoxInit(void)
{
    /** Item Box, Ground **/

    WriteJump(0x006C8280, ObjectItemBoxDisp_RF);
    WriteJump(0x006C83B0, ObjectItemBoxDispSort_RF);
    WriteJump(0x006C8810, ObjectItemBoxGotDisp_RF);

    /** Item Box, Ground 2B **/

    WriteJump(0x006C8520, ObjectItemBoxDisp_RF);
    WriteJump(0x006C86A0, ObjectItemBoxDispSort_RF);
    WriteJump(0x006C88C0, ObjectItemBoxGotDisp_RF);

    /** Item Box, Air **/

    WriteJump(0x006C9500, ObjectItemBoxAirDispSort_RF);
    WriteRetn(0x006C93C0); // ItemBoxAirDisplayer
    WriteNOP(0x006C917C, 0x006C9183); // tp->disp = func

    /** Item Box, Balloon **/

    WriteJump(0x006DB630, ObjectItemBoxBalloonDisplayer_RF);
    WriteRetn(0x06DB3B0); // tp->disp
    WriteNOP(0x006DB07A, 0x006DB07D); // tp->disp = func
    WriteNOP(0x006DB098, 0x006DB09B); // tp->disp = func

    /** Item Box, Balloon (cart) **/

    ___NOTE("We'll replace this too eventually, but for now just edit the vanilla disp");

    SwitchDisplayer(0x00624E43, DISP_SORT);

    WriteNOP( 0x00625199, 0x0062519B);

    RFU_ReplaceFloat(0x006251EE, 85.0); // alpha value

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
