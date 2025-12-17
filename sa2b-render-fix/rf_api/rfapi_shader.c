/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */

/****** Self ************************************************************************************/
#include <rf_api/rfapi_internal.h>  /* parent & siblings                                        */
#include <rf_shader.h>              /* shader                                                   */

/********************************/
/*  Constants                   */
/********************************/
/****** API Module Version **********************************************************************/
#define SHDR_API_VER                (1) /* shader api version                                   */

/********************************/
/*  Export Data                 */
/********************************/
/****** Shader API ******************************************************************************/
EXTERN
const RFAPI_SHADER rfapi_shader =
{
    .version = SHDR_API_VER,

    .LoadVShader = RF_DirectLoadVShader,
    .LoadPShader = RF_DirectLoadPShader,

    .SetGameVShader = RF_SetGameVShader,
    .SetGamePShader = RF_SetGamePShader,

    // version 1

    .GetGameVShader = RF_GetGameVShader,
    .GetGamePShader = RF_GetGamePShader,

    .CompileVShader = RF_DirectCompileVShader,
    .CompilePShader = RF_DirectCompilePShader,
};
