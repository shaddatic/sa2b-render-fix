/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */

/****** Config **********************************************************************************/
#include <cnf.h>                    /* config get                                               */

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

    .ConfigGetInt    = CNF_DirectGetInt,
    .ConfigGetBool   = CNF_DirectGetBool,
    .ConfigGetFloat  = CNF_DirectGetFloat,
    .ConfigGetString = CNF_DirectGetString,
};
