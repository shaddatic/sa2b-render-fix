/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>          /* core                                             */
#include <sa2b/writeop.h>       /* Writejump                                        */
#include <sa2b/writemem.h>      /* writedata                                        */
#include <sa2b/funchook.h>      /* funchook                                         */

/****** GX **************************************************************************/
#include <sa2b/gx/gx.h>         /* gx                                               */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h> /* ninja                                              */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_config.h>          /* config core                                      */
#include <rf_eventinfo.h>       /* event info                                       */
#include <rf_mod.h>             /* modifier                                         */

/****** Self ************************************************************************/
#include <rf_renderstate.h>               /* self                                   */
#include <rf_renderstate/rfrs_internal.h> /* children                               */

/************************/
/*  Game Functions      */
/************************/
/****** Trans Mode ******************************************************************/
#define SetOpaqueDraw               FUNC_PTR(void, __cdecl, (void)   , 0x0042C030)
#define SetAlphaTestDraw            FUNC_PTR(void, __cdecl, (void)   , 0x0042C0A0)
#define SetTransparentDraw          FUNC_PTR(void, __cdecl, (void)   , 0x0042C170)

/************************/
/*  Source Data         */
/************************/
/****** Default States **************************************************************/
static RFRS_CULLMD      CullModeDefault;
static RFRS_TRANSMD     TransModeDefault;
static RFRS_CMPMD       AlphaFuncDefault    = RFRS_CMPMD_NEQ;
static uint32_t         AlphaRefDefault     = 0;
static RFRS_CNKDRAWMD   CnkDrawModeDefault;
static RFRS_CNKFUNCMD   CnkFuncModeDefault  = RFRS_CNKFUNCMD_SIMPLE;
static RFRS_CNKPASSMD   CnkPassModeDefault;

/****** Override States *************************************************************/
static RFRS_CULLMD      CullModeOverride;
static RFRS_TRANSMD     TransModeOverride;
static RFRS_CMPMD       AlphaFuncOverride   = RFRS_CMPMD_NEQ;
static uint32_t         AlphaRefOverride    = 0;
static RFRS_MODMD       CnkModModeOverride;
static RFRS_CNKDRAWMD   CnkDrawModeOverride;
static RFRS_CNKFUNCMD   CnkFuncModeOverride = RFRS_CNKFUNCMD_SIMPLE;
static RFRS_CNKPASSMD   CnkPassModeOverride;

/************************/
/*  Source              */
/************************/
/****** Trans Mode ******************************************************************/
static void
SetOpaqueDrawNew(void)
{
    switch (TransModeOverride) {
    case RFRS_TRANSMD_AUTO:
    case RFRS_TRANSMD_OPAQUE:
    case RFRS_TRANSMD_AUTO_ATEST:
    case RFRS_TRANSMD_AUTO_TRANS:
        SetTransModeOpaque();
        break;

    case RFRS_TRANSMD_ALPHATEST:
        SetTransModeAlphaTest(AlphaFuncOverride, AlphaRefOverride);
        break;

    case RFRS_TRANSMD_TRANSPARENT:
        SetTransModeTransparent();
        break;
    }
}

static void
SetAlphaTestDrawNew(void)
{
    switch (TransModeOverride) {
    case RFRS_TRANSMD_OPAQUE:
        SetTransModeOpaque();
        break;

    case RFRS_TRANSMD_AUTO:
    case RFRS_TRANSMD_ALPHATEST:
    case RFRS_TRANSMD_AUTO_ATEST:
        SetTransModeAlphaTest(AlphaFuncOverride, AlphaRefOverride);
        break;

    case RFRS_TRANSMD_TRANSPARENT:
    case RFRS_TRANSMD_AUTO_TRANS:
        SetTransModeTransparent();
        break;
    }
}

static void
SetTransparentDrawNew(void)
{
    switch (TransModeOverride) {
    case RFRS_TRANSMD_OPAQUE:
        SetTransModeOpaque();
        break;

    case RFRS_TRANSMD_ALPHATEST:
    case RFRS_TRANSMD_AUTO_ATEST:
        SetTransModeAlphaTest(AlphaFuncOverride, AlphaRefOverride);
        break;

    case RFRS_TRANSMD_AUTO:
    case RFRS_TRANSMD_TRANSPARENT:
    case RFRS_TRANSMD_AUTO_TRANS:
        SetTransModeTransparent();
        break;
    }
}

/****** Set Render Mode *************************************************************/
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
    case RFRS_TRANSMD_AUTO_ATEST:
    case RFRS_TRANSMD_AUTO_TRANS:
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

    CnkModModeOverride = (mode != RFRS_MODMD_INVERSE) ?
                         RFRS_MODMD_NORMAL : RFRS_MODMD_INVERSE;
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
RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD mode)
{
    switch (mode) {
    case RFRS_CNKFUNCMD_NORMAL:
    case RFRS_CNKFUNCMD_EASY:
    case RFRS_CNKFUNCMD_SIMPLE:
    case RFRS_CNKFUNCMD_EASYMULTI:
    case RFRS_CNKFUNCMD_SIMPLEMULTI:
    case RFRS_CNKFUNCMD_DIRECT:
        CnkFuncModeOverride = mode;
        break;

    case RFRS_CNKFUNCMD_END:
        CnkFuncModeOverride = CnkFuncModeDefault;
        break;
    }
}

void
RFRS_SetCnkPassMode(RFRS_CNKPASSMD mode)
{
    switch (mode) {
    case RFRS_CNKPASSMD_NORMAL:
    case RFRS_CNKPASSMD_INVERSE:
        CnkPassModeOverride = mode;
        break;

    case RFRS_CNKPASSMD_END:
        CnkPassModeOverride = CnkPassModeDefault;
        break;
    }
}

/****** Get Render Mode *************************************************************/
RFRS_CULLMD
RFRS_GetCullMode(void)
{
    return CullModeOverride;
}

RFRS_TRANSMD
RFRS_GetTransMode(void)
{
    return TransModeOverride;
}

RFRS_CMPMD
RFRS_GetAlphaTestFunc(void)
{
    return AlphaFuncOverride;
}

int32_t
RFRS_GetAlphaTestRef(void)
{
    return AlphaRefOverride;
}

RFRS_MODMD
RFRS_GetModifierMode(void)
{
    return CnkModModeOverride;
}

RFRS_CNKDRAWMD
RFRS_GetCnkDrawMode(void)
{
    return CnkDrawModeOverride;
}

RFRS_CNKFUNCMD
RFRS_GetCnkFuncMode(void)
{
    return CnkFuncModeOverride;
}

RFRS_CNKPASSMD
RFRS_GetCnkPassMode(void)
{
    return CnkPassModeOverride;
}

/****** Set Default Render Mode *****************************************************/
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
RFRS_SetDefaultCnkFuncMode(RFRS_CNKFUNCMD mode)
{
    CnkFuncModeDefault = mode;
    CnkFuncModeOverride = mode;
}

void
RFRS_SetDefaultCnkPassMode(RFRS_CNKPASSMD mode)
{
    CnkPassModeDefault = mode;
    CnkPassModeOverride = mode;
}

/****** Init ************************************************************************/
void
RF_RenderStateInit(void)
{
    /** Transparancy draw set **/
    WriteJump(SetOpaqueDraw     , SetOpaqueDrawNew);
    WriteJump(SetAlphaTestDraw  , SetAlphaTestDrawNew);
    WriteJump(SetTransparentDraw, SetTransparentDrawNew);

    /** Fix direct calls to Magic draw set **/
    WriteNOP( 0x005FF290, 0x005FF2E2);
    WriteData(0x005FF290, 0x56, u8); // push esi
    WriteData(0x005FF291, 0x57, u8); // push edi
    WriteCall(0x005FF292, SetTransparentDrawNew);

    WriteNOP( 0x00600569, 0x006005B3);
    WriteData(0x00600569, 0x83, u8);  // add esp, 8
    WriteData(0x0060056A, 0xC4, u8);  // ^^^
    WriteData(0x0060056B, 0x08, u8);  // ^^^
    WriteCall(0x0060056C, SetTransparentDrawNew);
}
