/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_ctrl.h>                /* rf control                                               */

/****** Self ************************************************************************************/
#include <rf_api/rfapi_internal.h>  /* parent & siblings                                        */

/********************************/
/*  Constants                   */
/********************************/
/****** API Module Version **********************************************************************/
#define CTRL_API_VER                (1) /* control api version                                  */

/********************************/
/*  Export Data                 */
/********************************/
/****** Control API *****************************************************************************/
EXTERN
const RFAPI_CONTROL rfapi_control =
{
    .version = CTRL_API_VER,

    .SetModBufferSize            = RFCTRL_SetModBufferSize,
    .CheapShadowChaoWorldDisable = RFCTRL_CheapShadowChaoWorldDisable,

    /** Ver 1 **/
    .EventApplyModelDiffuse      = RFCTRL_EventApplyModelDiffuse,
};
