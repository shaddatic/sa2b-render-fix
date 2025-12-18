/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_font.h>                /* rf font                                                  */

/****** Self ************************************************************************************/
#include <rf_api/rfapi_internal.h>  /* parent & siblings                                        */

/********************************/
/*  Export Data                 */
/********************************/
/****** Font API ********************************************************************************/
EXTERN
const RFAPI_FONT rfapi_font =
{
    .version = RFAPI_FONT_VER,

    .LoadFontFile   = RF_FontLoadFile,
    .HalfSpaceWidth = RF_FontHalfSpace,

    .SetWidthList = RF_FontSetLeft,

    .SetFont = RF_FontReplace,
    .GetFont = RF_FontGet,

    .SetChaoFont = RF_FontChaoReplace,
    .GetChaoFont = RF_FontChaoGet,
};
