#include <sa2b/core.h>
#include <sa2b/writeop.h>
#include <sa2b/funchook.h>

/** GX **/
#include <sa2b/gx/gx.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>
#include <rf_eventinfo.h>
#include <rf_magic.h>
#include <rf_mod.h>

/** Self **/
#include <rf_renderstate.h>
#include <rf_renderstate/rfrs_internal.h>

/** Constants **/
#define CNK_FST_IL                  (NJD_FST_IL >>NJD_FST_SHIFT)
#define CNK_FST_IS                  (NJD_FST_IS >>NJD_FST_SHIFT)
#define CNK_FST_IA                  (NJD_FST_IA >>NJD_FST_SHIFT)
#define CNK_FST_UA                  (NJD_FST_UA >>NJD_FST_SHIFT)
#define CNK_FST_DB                  (NJD_FST_DB >>NJD_FST_SHIFT)
#define CNK_FST_FL                  (NJD_FST_FL >>NJD_FST_SHIFT)
#define CNK_FST_ENV                 (NJD_FST_ENV>>NJD_FST_SHIFT)
#define CNK_FST_NAT                 (NJD_FST_NAT>>NJD_FST_SHIFT)

#define ParseStripFlags             FUNC_PTR(void, __cdecl, (uint8_t), 0x0042CA20)
#define SetOpaqueDraw               FUNC_PTR(void, __cdecl, (void)   , 0x0042C030)
#define SetAlphaTestDraw            FUNC_PTR(void, __cdecl, (void)   , 0x0042C0A0)
#define SetTransparentDraw          FUNC_PTR(void, __cdecl, (void)   , 0x0042C170)

#define ForceUseAlpha               DATA_REF(bool, 0x01A55832)
#define ForceDstInverseOtherColor   DATA_REF(bool, 0x01A55833)
#define pTexSurface                 DATA_REF(int*, 0x01A55840)

static RFRS_CULLMD    CullModeDefault;
static RFRS_TRANSMD   TransModeDefault;
static RFRS_CMPMD     AlphaFuncDefault    = RFRS_CMPMD_GTR;
static uint32_t       AlphaRefDefault     = 64;
static RFRS_CNKDRAWMD CnkDrawModeDefault;

static RFRS_CULLMD    CullModeOverride;
static RFRS_TRANSMD   TransModeOverride;
static RFRS_CMPMD     AlphaFuncOverride   = RFRS_CMPMD_GTR;
static uint32_t       AlphaRefOverride    = 64;
static RFRS_CNKDRAWMD CnkDrawModeOverride;

static bool CullEventPatch;

static void
ParseStripFlagsHook(uint8_t flag)
{
    const bool fst_ua = (flag & (CNK_FST_NAT | CNK_FST_UA));

    switch (CnkDrawModeOverride) {
    case RFRS_CNKDRAWMD_ALL:
        break;

    case RFRS_CNKDRAWMD_OPAQUE:
        if (fst_ua)
        {
            SetChunkStripHideMode(true);
            return;
        }
        break;

    case RFRS_CNKDRAWMD_TRANSPARENT:
        if (!fst_ua)
        {
            SetChunkStripHideMode(true);
            return;
        }
        break;
    }

    const bool fst_db = (flag & CNK_FST_DB);

    /** Event patch, temporary **/
    if (CullEventPatch)
    {
        switch (CutsceneMode) {
        case 0: case 4: case 7:
            break;

        default:
            goto CULL_OFF;
        }
    }

    /** Set culling mode **/
    switch (CullModeOverride) {
    case RFRS_CULLMD_AUTO:
        GX_SetCullMode(fst_db ? GXD_CULLMODE_NONE : GXD_CULLMODE_CW);
        break;

    CULL_OFF:
    case RFRS_CULLMD_NONE:
        GX_SetCullMode(GXD_CULLMODE_NONE);
        break;

    case RFRS_CULLMD_NORMAL:
        GX_SetCullMode(GXD_CULLMODE_CW);
        break;

    case RFRS_CULLMD_INVERSE:

        /** if this strip isn't double sided,
            hide it's inverse face **/
        if (!fst_db)
        {
            SetChunkStripHideMode(true);
            return;
        }

        GX_SetCullMode(GXD_CULLMODE_CCW);
        break;
    }

    /** Allow strip drawing **/
    SetChunkStripHideMode(false);

    const bool use_alpha = ForceUseAlpha | fst_ua;

    GX_SetBlendMode(
        (_nj_cnk_blend_mode_ >> NJD_FBS_SHIFT) & 0x7,
        ForceDstInverseOtherColor ? 3 : (_nj_cnk_blend_mode_ >> NJD_FBD_SHIFT) & 0x7,
        use_alpha
    );

    switch (TransModeOverride) {
    case RFRS_TRANSMD_AUTO:
        if (use_alpha)
        {
            if ((flag & CNK_FST_NAT) ||
                (_nj_cnk_blend_mode_ & NJD_FBS_MASK) == NJD_FBS_ONE ||
                (_nj_cnk_blend_mode_ & NJD_FBD_MASK) == NJD_FBD_ONE ||
                !pTexSurface ||
                *pTexSurface != 14)
            {
                SetTransparentDraw();
            }
            else
                SetAlphaTestDraw();
        }
        else
            SetOpaqueDraw();
        break;

    case RFRS_TRANSMD_OPAQUE:
        SetOpaqueDraw();
        break;

    case RFRS_TRANSMD_ALPHATEST:
        SetAlphaTestDraw();
        break;

    case RFRS_TRANSMD_TRANSPARENT:
        SetTransparentDraw();
        break;
    }
}

#define _njCnkDrawModelSub      FUNC_PTR(void, __cdecl, (NJS_CNK_MODEL*), 0x0042D500)

static hook_info* njCnkDrawModelSubHookInfo;
static void
CnkDrawModelSubUnsetCulling(NJS_CNK_MODEL* model)
{
    FuncHookCall( njCnkDrawModelSubHookInfo, _njCnkDrawModelSub(model) );

    GX_SetCullMode(GXD_CULLMODE_NONE);
}

static void
SetAlphaTestFunc(void)
{
    RF_MagicSetAlphaTestFunc(AlphaFuncOverride);
}

static void
SetAlphaRef(void)
{
    RF_MagicSetAlphaRef(AlphaRefOverride);
}

/** extern **/
void
RFRS_SetCullMode(RFRS_CULLMD mode)
{
    switch (mode) {
    case RFRS_CULLMD_AUTO:
    case RFRS_CULLMD_NONE:
    case RFRS_CULLMD_NORMAL:
    case RFRS_CULLMD_INVERSE:
        CullModeOverride = mode;
        break;

    case RFRS_CULLMD_END:
        CullModeOverride = CullModeDefault;
        break;
    }
}

void
RFRS_SetTransMode(RFRS_TRANSMD mode)
{
    switch (mode) {
    case RFRS_TRANSMD_AUTO:
    case RFRS_TRANSMD_OPAQUE:
    case RFRS_TRANSMD_ALPHATEST:
    case RFRS_TRANSMD_TRANSPARENT:
        TransModeOverride = mode;
        break;

    case RFRS_TRANSMD_END:
        TransModeOverride = TransModeDefault;
        break;
    }
}

void
RFRS_SetAlphaTestFunc(RFRS_CMPMD mode)
{
    switch (mode) {
    case RFRS_CMPMD_NVR:
    case RFRS_CMPMD_LSS:
    case RFRS_CMPMD_EQU:
    case RFRS_CMPMD_LEQ:
    case RFRS_CMPMD_GTR:
    case RFRS_CMPMD_NEQ:
    case RFRS_CMPMD_GEQ:
    case RFRS_CMPMD_ALW:
        AlphaFuncOverride = mode;
        break;

    case RFRS_CMPMD_END:
        AlphaFuncOverride = AlphaFuncDefault;
        break;
    }
}

void
RFRS_SetAlphaTestRef(int32_t value)
{
    if (value <= RFRS_ALPHAREF_END)
    {
        AlphaRefOverride = AlphaRefDefault;
        return;
    }

    AlphaRefOverride = value;
}

void
RFRS_SetModifierMode(RFRS_MODMD mode)
{
    RFMOD_SetInvertMode(mode == RFRS_MODMD_INVERSE);
}

void
RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD mode)
{
    switch (mode) {
    case RFRS_CNKDRAWMD_ALL:
    case RFRS_CNKDRAWMD_OPAQUE:
    case RFRS_CNKDRAWMD_TRANSPARENT:
        CnkDrawModeOverride = mode;
        break;

    case RFRS_CNKDRAWMD_END:
        CnkDrawModeOverride = CnkDrawModeDefault;
        break;
    }
    
}

void
RFRS_SetDefaultCullMode(RFRS_CULLMD mode)
{
    CullModeDefault = mode;
    CullModeOverride = mode;
}

void
RFRS_SetDefaultTransMode(RFRS_TRANSMD mode)
{
    TransModeDefault = mode;
    TransModeOverride = mode;
}

void
RFRS_SetDefaultAlphaTestFunc(RFRS_CMPMD mode)
{
    AlphaFuncDefault = mode;
    AlphaFuncOverride = mode;
}

void
RFRS_SetDefaultAlphaTestRef(int32_t mode)
{
    AlphaRefDefault = mode;
    AlphaRefOverride = mode;
}

void
RFRS_SetDefaultCnkDrawMode(RFRS_CNKDRAWMD mode)
{
    CnkDrawModeDefault = mode;
    CnkDrawModeOverride = mode;
}

void
RF_RenderStateInit(void)
{
    WriteJump(ParseStripFlags, ParseStripFlagsHook);

    RFRS_BackFaceCullingInit();

    njCnkDrawModelSubHookInfo = FuncHook(_njCnkDrawModelSub, CnkDrawModelSubUnsetCulling);

    /** Replace Alpha Test set **/
    WriteNOP( 0x0042C0CE, 0x0042C104);
    WriteCall(0x0042C0CE, SetAlphaTestFunc);
    WriteCall(0x0042C0D3, SetAlphaRef);

    CullEventPatch = RF_ConfigGetInt(CNF_DEBUG_BFC_EVENT) == 1;
}
