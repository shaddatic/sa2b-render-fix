#include <sa2b/core.h>
#include <sa2b/memutil.h>
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

/** Self **/
#include <rf_renderstate.h>

typedef struct
{
    float gap0;
    int field_4;
    float field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    void* D3DVertexDeclaration;
    int field_20;
    uint32_t StrideSize;
    int field_28;
    int field_2C;
    int field_30;
}
VertexDeclarationInfo;

/** Constants **/
#define CNK_FST_IL                  (NJD_FST_IL >>NJD_FST_SHIFT)
#define CNK_FST_IS                  (NJD_FST_IS >>NJD_FST_SHIFT)
#define CNK_FST_IA                  (NJD_FST_IA >>NJD_FST_SHIFT)
#define CNK_FST_UA                  (NJD_FST_UA >>NJD_FST_SHIFT)
#define CNK_FST_DB                  (NJD_FST_DB >>NJD_FST_SHIFT)
#define CNK_FST_FL                  (NJD_FST_FL >>NJD_FST_SHIFT)
#define CNK_FST_ENV                 (NJD_FST_ENV>>NJD_FST_SHIFT)
#define CNK_FST_NAT                 (NJD_FST_NAT>>NJD_FST_SHIFT)

#define ParseStripFlags             FuncPtr(void, __cdecl, (uint8_t), 0x0042CA20)
#define SetOpaqueDraw               FuncPtr(void, __cdecl, (void)   , 0x0042C030)
#define SetAlphaTestDraw            FuncPtr(void, __cdecl, (void)   , 0x0042C0A0)
#define SetTransparentDraw          FuncPtr(void, __cdecl, (void)   , 0x0042C170)

#define ForceUseAlpha               DataRef(bool, 0x01A55832)
#define ForceDstInverseOtherColor   DataRef(bool, 0x01A55833)
#define pTexSurface                 DataRef(int*, 0x01A55840)

#define VertexDeclInfo              DataRef(VertexDeclarationInfo*, 0x0174F7E8)

static void
CopyLastVertex(void)
{
    const int stride = VertexDeclInfo->StrideSize;
    const int vtxbuf = _gx_vtx_buf_base_;
    const int lastvtx = _gx_vtx_buf_offset_ - stride;

    memcpy((char*)vtxbuf + _gx_vtx_buf_offset_, (char*)vtxbuf + lastvtx, stride);
    ++_gx_nb_vtx_;
    _gx_vtx_buf_offset_ += stride;
}

static void
SetCull(int16_t vtxCount)
{
    bool ccw = false;

    if (vtxCount < 0)
    {
        vtxCount = -vtxCount;
        ccw = true;
    }

    const int stride = VertexDeclInfo->StrideSize;

    if (!_gx_nb_vtx_)
    {
        _gx_vtx_buf_offset_cpy_ = 0;
        _gx_prim_type_ = 0x98;
        _gx_vtx_buf_start_ = _gx_vtx_buf_offset_;
        _gx_cull_ = ccw;
        _gx_nb_vtx_ += vtxCount;

        if (ccw)
        {
            _gx_vtx_buf_offset_cpy_ = _gx_vtx_buf_offset_;
            ++_gx_nb_vtx_;
            _gx_vtx_buf_offset_ += stride;
        }

        return;
    }

    if (((_gx_nb_vtx_ - 2) & 0x80000001) == 0)
    {
        if (ccw)
        {
            CopyLastVertex();
            CopyLastVertex();
            _gx_vtx_buf_offset_cpy_ = _gx_vtx_buf_offset_;
            _gx_cull_ = ccw;
            _gx_vtx_buf_offset_ += stride;
            _gx_nb_vtx_ += vtxCount + 1;
            return;
        }
    }
    else
    {
        if (!ccw)
        {
            CopyLastVertex();
            CopyLastVertex();
            _gx_vtx_buf_offset_cpy_ = _gx_vtx_buf_offset_;
            _gx_cull_ = ccw;
            _gx_vtx_buf_offset_ += stride;
            _gx_nb_vtx_ += vtxCount + 1;
            return;
        }
    }

    CopyLastVertex();

    _gx_vtx_buf_offset_cpy_ = _gx_vtx_buf_offset_;
    _gx_cull_ = ccw;
    _gx_vtx_buf_offset_ += stride;
    _gx_nb_vtx_ += vtxCount + 1;
}

__declspec(naked)
static void
__SetGXCull(void)
{
    __asm
    {
        push eax
        call SetCull
        add esp, 4
        retn
    }
}

#define _njCnkDrawModelSub      FuncPtr(int, __cdecl, (NJS_CNK_MODEL*), 0x0042D500)

static hook_info* njCnkDrawModelSubHookInfo;
static int
CnkDrawModelSubUnsetCulling(NJS_CNK_MODEL* model)
{
    int result;
    FuncHookCall( njCnkDrawModelSubHookInfo, result = _njCnkDrawModelSub(model) );

    GX_SetCullMode(GXD_CULLMODE_NONE);

    return result;
}

static RFRS_CULLMD  CullModeDefault;
static RFRS_TRANSMD TransModeDefault;
static RFRS_CMPMD   AlphaFuncDefault    = RFRS_CMPMD_GTR;
static uint32_t     AlphaRefDefault     = 64;

static RFRS_CULLMD  CullModeOverride;
static RFRS_TRANSMD TransModeOverride;
static RFRS_CMPMD   AlphaFuncOverride   = RFRS_CMPMD_GTR;
static uint32_t     AlphaRefOverride    = 64;

static bool CullEventPatch;

static void
ParseStripFlagsHook(uint8_t flag)
{
    if (CullEventPatch)
    {
        switch (CutsceneMode) {
        case 0: case 4: case 7:
            break;

        default:
            goto CULL_OFF;
        }
    }

    switch (CullModeOverride) {
    case RFRS_CULLMD_AUTO:
        GX_SetCullMode((flag & CNK_FST_DB) ? GXD_CULLMODE_NONE : GXD_CULLMODE_CW);
        break;

    CULL_OFF:
    case RFRS_CULLMD_NONE:
        GX_SetCullMode(GXD_CULLMODE_NONE);
        break;

    case RFRS_CULLMD_NORMAL:
        GX_SetCullMode(GXD_CULLMODE_CW);
        break;

    case RFRS_CULLMD_INVERSE:
        GX_SetCullMode(GXD_CULLMODE_CCW);
        break;
    };

    const bool use_alpha = ForceUseAlpha ? true : (flag & (CNK_FST_NAT | CNK_FST_UA));

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
RF_RenderStateInit(void)
{
    WriteJump(ParseStripFlags, ParseStripFlagsHook);

    WriteCall(0x0042E22D, __SetGXCull);
    WriteCall(0x0042E388, __SetGXCull);
    WriteCall(0x0042E59D, __SetGXCull);
    WriteCall(0x0042E7B1, __SetGXCull);
    WriteCall(0x0042E9EE, __SetGXCull);
    WriteCall(0x0042F0FB, __SetGXCull);
    WriteCall(0x0042F1ED, __SetGXCull);
    WriteCall(0x0042F2FB, __SetGXCull);
    WriteCall(0x0042F40D, __SetGXCull);
    WriteCall(0x0077F908, __SetGXCull);

    njCnkDrawModelSubHookInfo = FuncHook(_njCnkDrawModelSub, CnkDrawModelSubUnsetCulling);

    /** Replace Alpha Test set **/
    WriteNoOP(0x0042C0CE, 0x0042C104);
    WriteCall(0x0042C0CE, SetAlphaTestFunc);
    WriteCall(0x0042C0D3, SetAlphaRef);

    CullEventPatch = RF_ConfigGetInt(CNF_DEBUG_BFC_EVENT) == 1;
}
