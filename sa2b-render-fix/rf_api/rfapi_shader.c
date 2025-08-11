/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_shader.h>              /* shader                                                   */

/****** Self ************************************************************************************/
#include <rf_api/rfapi_internal.h>  /* parent & siblings                                        */

/********************************/
/*  Constants                   */
/********************************/
/****** API Module Version **********************************************************************/
#define SHDR_API_VER                (0) /* shader api version                                   */

/********************************/
/*  Export Data                 */
/********************************/
/****** Shader API ******************************************************************************/
EXTERN
const RFAPI_SHADER rfapi_shader =
{
    .version = SHDR_API_VER,

    .LoadVtxShader = RF_DirectLoadVtxShader,
    .LoadPxlShader = RF_DirectLoadPxlShader,

    .ReplaceVtxShader = RF_ReplaceVtxShader,
    .ReplacePxlShader = RF_ReplacePxlShader,
};
