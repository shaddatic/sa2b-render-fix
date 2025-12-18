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
/*  Export Data                 */
/********************************/
/****** Config API ******************************************************************************/
EXTERN
const RFAPI_CONFIG rfapi_config =
{
    .version = RFAPI_CONFIG_VER,

    .ConfigGetInt    = CNF_DirectGetInt,
    .ConfigGetBool   = CNF_DirectGetBool,
    .ConfigGetFloat  = CNF_DirectGetFloat,
    .ConfigGetString = CNF_DirectGetString,
};
