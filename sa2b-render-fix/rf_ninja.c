/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>      /* core                                                 */
#include <sa2b/memutil.h>   /* WriteData, WriteJump, WritePointer                   */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h>   /* ninja                                            */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_mod.h>             /* RFMOD_SetAlpha                                   */

/****** Self ************************************************************************/
#include <rf_ninja.h>           /* self                                             */

/************************/
/*  Source              */
/************************/
void
rjSetCheapShadowMode(int32_t mode)
{
    if (mode < 0)
    {
        RFMOD_SetAlpha(0.0f);
        return;
    }
    else if (mode > 255)
        mode = 255;

    RFMOD_SetAlphaI(255 - mode);
}
