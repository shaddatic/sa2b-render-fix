/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_renderstate.h>         /* render state                                             */

/****** Self ************************************************************************************/
#include <rf_api/rfapi_internal.h>  /* parent & siblings                                        */

/********************************/
/*  Constants                   */
/********************************/
/****** API Module Version **********************************************************************/
#define STATE_API_VER               (4) /* render state api version                             */

/********************************/
/*  Source                      */
/********************************/
/****** Null Funcs ******************************************************************************/
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

    .SetTwoPassLightingMode = RFRS_SetTwoPassLightingMode,
    .GetTwoPassLightingMode = RFRS_GetTwoPassLightingMode,
};
