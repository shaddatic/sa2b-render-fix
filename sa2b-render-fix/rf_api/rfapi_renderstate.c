/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */

/****** Self ************************************************************************************/
#include <rf_api/rfapi_internal.h>  /* parent & siblings                                        */
#include <rf_renderstate.h>         /* render state                                             */
#include <rf_ninja.h>               /* render fix ninja                                         */

/********************************/
/*  Constants                   */
/********************************/
/****** API Module Version **********************************************************************/
#define STATE_API_VER               (4) /* render state api version                             */

/********************************/
/*  Source                      */
/********************************/
/************************************************************************************************/
/*
*   Depricated Functions
*/
/****** Cull Mode *******************************************************************************/
void
RFRS_SetCullMode(RFRS_CULLMD mode)
{
    switch (mode)
    {
        case RFRS_CULLMD_END:
        case RFRS_CULLMD_AUTO:
        case RFRS_CULLMD_NONE:
        {
            rjCnkSetControl( ~RJD_CNK_CTRL_MASK_CULL, RJD_CNK_CTRL_MASK_CULL );
            break;
        }
        case RFRS_CULLMD_NORMAL:
        {
            rjCnkSetControl( ~RJD_CNK_CTRL_MASK_CULL, RJD_CNK_CTRL_NORMAL );
            break;
        }
        case RFRS_CULLMD_INVERSE:
        {
            rjCnkSetControl( ~RJD_CNK_CTRL_MASK_CULL, RJD_CNK_CTRL_INVERSE );
            break;
        }
    }
}

static RFRS_CULLMD
RFRS_GetCullMode(void)
{
    const Uint32 cnkctrl = rjCnkGetControl();

    if ( cnkctrl & RJD_CNK_CTRL_NORMAL )
    {
        if ( cnkctrl & RJD_CNK_CTRL_INVERSE )
        {
            return RFRS_CULLMD_AUTO;
        }
        else
        {
            return RFRS_CULLMD_NORMAL;
        }
    }
    else
    {
        return RFRS_CULLMD_INVERSE;
    }
}

/****** Cnk Draw Mode ***************************************************************************/
void
RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD mode)
{
    switch (mode)
    {
        case RFRS_CNKDRAWMD_END:
        case RFRS_CNKDRAWMD_ALL:
        {
            rjCnkSetControl( ~RJD_CNK_CTRL_MASK_DRAW, RJD_CNK_CTRL_MASK_DRAW );
            break;
        }
        case RFRS_CNKDRAWMD_OPAQUE:
        {
            rjCnkSetControl( ~RJD_CNK_CTRL_MASK_DRAW, RJD_CNK_CTRL_OPAQUE );
            break;
        }
        case RFRS_CNKDRAWMD_TRANSPARENT:
        {
            rjCnkSetControl( ~RJD_CNK_CTRL_MASK_DRAW, RJD_CNK_CTRL_TRANSLUCENT );
            break;
        }
    }
}

static RFRS_CNKDRAWMD
RFRS_GetCnkDrawMode(void)
{
    const Uint32 cnkctrl = rjCnkGetControl();

    if ( cnkctrl & RJD_CNK_CTRL_OPAQUE )
    {
        if ( cnkctrl & RJD_CNK_CTRL_TRANSLUCENT )
        {
            return RFRS_CNKDRAWMD_ALL;
        }
        else
        {
            return RFRS_CNKDRAWMD_OPAQUE;
        }
    }
    else
    {
        return RFRS_CNKDRAWMD_TRANSPARENT;
    }
}

/****** Modifier Mode ***************************************************************************/
static void
RFRS_SetModifierMode(RFRS_MODMD mode)
{
    if ( mode == RFRS_MODMD_INVERSE )
    {
        _nj_control_3d_flag_ |= NJD_CONTROL_3D_MIRROR_MODEL;
    }
    else
    {
        _nj_control_3d_flag_ &= ~NJD_CONTROL_3D_MIRROR_MODEL;
    }
}

static RFRS_MODMD
RFRS_GetModifierMode(void)
{
    return (_nj_control_3d_flag_ & NJD_CONTROL_3D_MIRROR_MODEL) ? RFRS_MODMD_INVERSE : RFRS_MODMD_NORMAL;
}

/****** Cnk Pass Mode ***************************************************************************/
static void
RFRS_SetCnkPassMode(RFRS_CNKPASSMD mode)
{
    if ( mode == RFRS_CNKPASSMD_INVERSE )
    {
        _nj_control_3d_flag_ |= NJD_CONTROL_3D_MIRROR_MODEL;
    }
    else
    {
        _nj_control_3d_flag_ &= ~NJD_CONTROL_3D_MIRROR_MODEL;
    }
}

static RFRS_CNKPASSMD
RFRS_GetCnkPassMode(void)
{
    return (_nj_control_3d_flag_ & NJD_CONTROL_3D_MIRROR_MODEL) ? RFRS_CNKPASSMD_INVERSE : RFRS_CNKPASSMD_NORMAL;
}

/************************************************************************************************/
/*
*   Null Functions
*/
/****** Cnk Pass Mode ***************************************************************************/
static void
RFRS_SetSocTexHackMode(RFRS_SOCTEXHACKMD mode)
{
    mode;
}

static RFRS_SOCTEXHACKMD
RFRS_GetSocTexHackMode(void)
{
    return RFRS_SOCTEXHACKMD_DISABLED;
}

/********************************/
/*  Export Data                 */
/********************************/
/****** Render State API ************************************************************************/
EXTERN
const RFAPI_RENDERSTATE rfapi_rstate =
{
    .version = STATE_API_VER,

    .SetCullMode      = RFRS_SetCullMode,
    .SetTransMode     = RFRS_SetTransMode,
    .SetAlphaTestFunc = RFRS_SetAlphaTestFunc,
    .SetAlphaTestRef  = RFRS_SetAlphaTestRef,

    /** Ver 1 **/
    .SetModifierMode  = RFRS_SetModifierMode,
    .SetCnkDrawMode   = RFRS_SetCnkDrawMode,

    /** Ver 2 **/
    .SetCnkFuncMode = RFRS_SetCnkFuncMode,
    .SetCnkPassMode = RFRS_SetCnkPassMode,

    .GetCullMode      = RFRS_GetCullMode,
    .GetTransMode     = RFRS_GetTransMode,
    .GetAlphaTestFunc = RFRS_GetAlphaTestFunc,
    .GetAlphaTestRef  = RFRS_GetAlphaTestRef,
    .GetModifierMode  = RFRS_GetModifierMode,
    .GetCnkDrawMode   = RFRS_GetCnkDrawMode,
    .GetCnkFuncMode   = RFRS_GetCnkFuncMode,
    .GetCnkPassMode   = RFRS_GetCnkPassMode,

    /** Ver 3 **/
    .SetSocTexHackMode = RFRS_SetSocTexHackMode,
    .GetSocTexHackMode = RFRS_GetSocTexHackMode,

    /** Ver 4 **/
    .SetCnkSpecMode = RFRS_SetCnkSpecMode,
    .GetCnkSpecMode = RFRS_GetCnkSpecMode,
};
