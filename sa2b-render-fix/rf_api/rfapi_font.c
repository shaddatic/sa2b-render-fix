#include <samt/core.h>

/** Render Fix **/
#include <rf_core.h>

/** Self **/
#include <rf_api/rfapi_internal.h>
#include <rf_font.h>

/** Constants **/
#define FONT_API_VER    (0)

EXTERN
const RFAPI_FONT rfapi_font =
{
    .version = FONT_API_VER,

    .LoadFontFile   = RF_FontLoadFile,
    .HalfSpaceWidth = RF_FontHalfSpace,

    .SetWidthList = RF_FontSetLeft,

    .SetFont = RF_FontReplace,
    .GetFont = RF_FontGet,

    .SetChaoFont = RF_FontChaoReplace,
    .GetChaoFont = RF_FontChaoGet,
};
