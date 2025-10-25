/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* Writejump                                        */
#include <samt/writemem.h>      /* writedata                                        */
#include <samt/funchook.h>      /* funchook                                         */

/****** GX **************************************************************************/
#include <samt/gx/gx.h>         /* gx                                               */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h> /* ninja                                              */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_config.h>          /* config core                                      */

/****** Self ************************************************************************/
#include <rf_renderstate.h>               /* self                                   */

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
static RFRS_TRANSMD         TransModeDefault            = RFRS_TRANSMD_AUTO;
static RFRS_CMPMD           AlphaFuncDefault            = RFRS_CMPMD_NEQ;
static uint32_t             AlphaRefDefault             = 0;
static RFRS_CNKFUNCMD       CnkFuncModeDefault          = RFRS_CNKFUNCMD_SIMPLE;
static RFRS_CNKSPECMD       CnkSpecModeDefault          = RFRS_CNKSPECMD_AUTO;

/****** Override States *************************************************************/
static RFRS_TRANSMD         TransModeOverride           = RFRS_TRANSMD_AUTO;
static RFRS_CMPMD           AlphaFuncOverride           = RFRS_CMPMD_NEQ;
static uint32_t             AlphaRefOverride            = 0;
static RFRS_CNKFUNCMD       CnkFuncModeOverride         = RFRS_CNKFUNCMD_SIMPLE;
static RFRS_CNKSPECMD       CnkSpecModeOverride         = RFRS_CNKSPECMD_AUTO;

/************************/
/*  Source              */
/************************/
/****** Set Render Mode *************************************************************/
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
    case RFRS_TRANSMD_PUNCH:
    case RFRS_TRANSMD_AUTO_PUNCH:
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
RFRS_SetCnkSpecMode(RFRS_CNKSPECMD mode)
{
    switch (mode)
    {
        case RFRS_CNKSPECMD_NONE:
        case RFRS_CNKSPECMD_AUTO:
        case RFRS_CNKSPECMD_NORMAL:
        case RFRS_CNKSPECMD_EASY:
        case RFRS_CNKSPECMD_SIMPLE:
        case RFRS_CNKSPECMD_MULTI:
        {
            CnkSpecModeOverride = mode;
            break;
        }
        case RFRS_CNKSPECMD_END:
        {
            CnkSpecModeOverride = CnkSpecModeDefault;
            break;
        }
    }
}

/****** Get Render Mode *************************************************************/
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

RFRS_CNKFUNCMD
RFRS_GetCnkFuncMode(void)
{
    return CnkFuncModeOverride;
}

RFRS_CNKSPECMD
RFRS_GetCnkSpecMode(void)
{
    return CnkSpecModeOverride;
}

/****** Set Default Render Mode *****************************************************/
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
RFRS_SetDefaultCnkFuncMode(RFRS_CNKFUNCMD mode)
{
    CnkFuncModeDefault = mode;
    CnkFuncModeOverride = mode;
}

void
RFRS_SetDefaultCnkSpecMode(RFRS_CNKSPECMD mode)
{
    CnkSpecModeDefault = mode;
    CnkSpecModeOverride = mode;
}

/****** Init ************************************************************************/
void
RF_RenderStateInit(void)
{
    if ( RF_ConfigGetInt(CNF_COMPAT_OLDATEST) )
    {
        RFRS_SetDefaultAlphaTestFunc(RFRS_CMPMD_GTR);
        RFRS_SetDefaultAlphaTestRef(64);
    }
}
