/********************************/
/*  Includes                    */
/********************************/
/****** Core Toolkit ****************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Render Fix ******************************************************************************/
#include <rf_system.h>              /* system                                                   */

/****** Self ************************************************************************************/
#include <rf_ninja/rj_internal.h>   /* parent & siblings                                        */

/********************************/
/*  Source                      */
/********************************/
/****** Vsync Wait Count ************************************************************************/
void
rjSetWaitVsyncCount(Sint32 count)
{
    RF_SysSetWaitVsyncCount(count);
}

Sint32
rjGetWaitVsyncCount(void)
{
    return RF_SysGetWaitVsyncCount();
}
