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
#include <rf_draw.h>            /* mod draw                                         */
#include <rf_util.h>            /* switch displayer                                 */

/****** Self ************************************************************************/
#include <rfm_event/ev_renderer/evr_internal.h> /* parent & siblings                */

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/

___TODO("Add and use actual header for this");
void rjSetWaitVsyncCount( Sint32 count );

static void
EV_SetWaitVsyncCount(void)
{
    if ( false ) // 30fps mode
    {
        rjSetWaitVsyncCount( 2 );
        return;
    }

    if ( true )
    {
        const int wait_vsync = EventEffData.sound[0].WaitVsyncCount;

        rjSetWaitVsyncCount( MAX( 1, wait_vsync ) );
    }
    else
    {
        rjSetWaitVsyncCount( 1 );
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
