/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */

/****** Self ************************************************************************************/
#include <rf_api/rfapi_internal.h>  /* parent & siblings                                        */
#include <rf_ninja.h>               /* rf ninja                                                 */

/********************************/
/*  Prototypes                  */
/********************************/
/****** Non-Functional **************************************************************************/
static void
NonFunctional(void)
{
    ;
}

/********************************/
/*  Extern Variables            */
/********************************/
/****** API Structure ***************************************************************************/
EXTERN
const RFAPI_LIGHT rfapi_light =
{
    .version = RFD_APIVER_LIGHT,

    .SetLightSwitch = rjSetLightSwitch,

    .SetLightColor = rjSetLightColor,
    .SetAmbient    = rjSetAmbient,

    .SetLightIntensity = rjSetLightIntensity,

    .SetLightVector = rjSetLightVector,
    .SetLightPoint  = rjSetLightPoint,
    .SetLightSpot   = (void*) NonFunctional,

    .SetLightRange = rjSetLightRange,
    .SetLightAngle = (void*) NonFunctional,

    .SetLightMatrix = rjSetLightMatrix,
};
