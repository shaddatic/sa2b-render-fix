/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* writejump                                        */
#include <samt/funchook.h>      /* funchook                                         */

/****** Utility *********************************************************************/
#include <samt/util/cnkmdl.h>   /* chunk model                                      */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** Game ************************************************************************/
#include <samt/sonic/task.h>    /* task                                             */
#include <samt/sonic/njctrl.h>  /* ninja control                                    */
#include <samt/sonic/display.h> /* screen display                                   */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_eventinfo.h>       /* event data                                       */
#include <rf_renderstate.h>     /* render state                                     */
#include <rf_njcnk.h>           /* emulated njcnk draw functions                    */
#include <rf_ninja.h>           /* mod draw                                         */
#include <rf_util.h>            /* switch displayer                                 */

/****** Self ************************************************************************/
#include <rf_module/rfm_event/ev_renderer/evr_internal.h> /* parent & siblings      */

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
EV_SetWaitVsyncCount(void)
{
    switch ( EventVsyncMode )
    {
        case EV_VSYNCMD_30:
        {
            rjSetWaitVsyncCount( 2 );
            break;
        }
        case EV_VSYNCMD_EVENT:
        {
            const int wait_vsync = MAX( 1, EventEffData.sound[0].WaitVsyncCount );

            RF_DbgExtraInfo("Setting Event vsync to '%i'...", wait_vsync);

            rjSetWaitVsyncCount( wait_vsync );
            break;
        }
        case EV_VSYNCMD_60:
        {
            rjSetWaitVsyncCount( 1 );
            break;
        }
    }
}

static void
EV_ResetWaitVsyncCountTimecard(void)
{
    CutsceneMode = EVENTMD_TIMECARD;

    rjSetWaitVsyncCount( 1 );
}

static void
EV_ResetWaitVsyncCount7(void)
{
    CutsceneMode = EVENTMD_UNK_7;

    rjSetWaitVsyncCount( 1 );
}

/****** Init ************************************************************************/
void
EVR_VsyncInit(void)
{
    WriteNOP( 0x00602B5C, 0x00602B72);
    WriteCall(0x00602B5C, EV_SetWaitVsyncCount);

    WriteNOP( 0x005FB385, 0x005FB38F);
    WriteCall(0x005FB385, EV_ResetWaitVsyncCountTimecard);

    WriteNOP( 0x005FB775, 0x005FB77F);
    WriteCall(0x005FB775, EV_ResetWaitVsyncCount7);

    WriteJump(0x005F8EE0, EV_SetWaitVsyncCount);
}
