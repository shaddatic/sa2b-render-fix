/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_config.h>              /* getconfig                                                */

/****** Self ************************************************************************************/
#include <rf_api/rfapi_internal.h>  /* parent & siblings                                        */

/********************************/
/*  Constants                   */
/********************************/
/****** API Module Version **********************************************************************/
#define CNFG_API_VER                (0) /* config api version                                   */

/********************************/
/*  Export Data                 */
/********************************/
/****** Config API ******************************************************************************/
EXTERN
const RFAPI_CONFIG rfapi_config =
{
    .version = CNFG_API_VER,

    .ConfigGetInt    = RF_ConfigDirectGetInt,
    .ConfigGetBool   = RF_ConfigDirectGetBool,
    .ConfigGetFloat  = RF_ConfigDirectGetFloat,
    .ConfigGetString = RF_ConfigDirectGetString,
};
