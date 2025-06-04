/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>      /* core                                                 */
#include <samt/init.h>      /* export dll                                           */
#include <samt/writeop.h>   /* writenop/jump                                        */
#include <samt/os.h>        /* highresclock                                         */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */
#include <rf_config.h>      /* config                                               */

/****** Std *************************************************************************/
#include <math.h>           /* fmax                                                 */

/****** Self ************************************************************************/
#include <rfm_global/rfg_internal.h> /* parent & siblings                           */

/************************/
/*  Constants           */
/************************/
/****** Basic Constants *************************************************************/
#define SLEEP_GRACE_MS      (1)         /* sleep call grace time                    */
#define MS_PER_SEC          (1000.0)    /* milliseconds per second                  */

/************************/
/*  Game Defs           */
/************************/
/****** Task Exec *******************************************************************/
#define TaskExecLoop            DATA_REF(s32, 0x01DEB50C)
#define TaskExecLoop2           DATA_REF(s32, 0x01DEB514)

/************************/
/*  Data                */
/************************/
/****** Target Vsync Mode ***********************************************************/
static s32 WaitVsyncCount;

/****** Clock ***********************************************************************/
static s64 ClockStart;

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static s64
GetClock(void)
{
    return mtOSHighResolutionClock();
}

static f64
GetMilliseconds(s64 clock, s64 freq)
{
    return ( (f64)clock / (f64)freq ) * MS_PER_SEC;
}

static f64
GetFrameTime(s64 last_clock, s64 freq)
{
    return ((f64)(mtOSHighResolutionClock() - last_clock) / (f64)freq) * MS_PER_SEC;
}

/****** Export **********************************************************************/


EXPORT_DLL
void __cdecl
OnRenderSceneStart(void)
{
    if ( ClockStart == 0 )
    {
        ClockStart = GetClock();
        return;
    }

    const s64 freq = mtOSHighResolutionFrequency();

    f64 vsync_wait_count;
    s32 loop_offset;

    if ( WaitVsyncCount >= 0 )
    {
        vsync_wait_count = (f64) WaitVsyncCount;
        loop_offset      = 0;
    }
    else
    {
        vsync_wait_count = 1.0;
        loop_offset      = -WaitVsyncCount;
    }

    const f64 target_ms = (MS_PER_SEC / 60.0);

    const f64 vsync_ms = (target_ms * vsync_wait_count);

    const s64 clock_end = GetClock() - ClockStart;
    const f64 delta_ms = GetMilliseconds(clock_end, freq);

    const s64 start_clock = GetClock();

    const f64 wait_ms = (vsync_ms - delta_ms);

    // vsync
    {
        // if the frame was too fast, wait a bit
        if ( vsync_ms > delta_ms )
        {
            const u32 sleep_ms = (u32)wait_ms;

            // sleep most of the time first to save CPU time
            if ( sleep_ms > SLEEP_GRACE_MS ) mtOSSleep( sleep_ms - SLEEP_GRACE_MS );

            // wait for the remaining time
            while ( wait_ms > GetFrameTime(start_clock, freq) );
        }
    }

    // frameskip
    {
        const f64 frametime = delta_ms + wait_ms;

        const s32 frameskip = (s32)fmax( (frametime / target_ms), 1.f ) + loop_offset;

        TaskExecLoop  = (s32) frameskip;
        TaskExecLoop2 = (s32) frameskip;
    }

    ClockStart = GetClock();
}

/****** Extern **********************************************************************/
___TODO("These will be moved to a seperate module eventually");

void
rjSetWaitVsyncCount(s32 count)
{
    if ( count == 0 )
    {
        WaitVsyncCount = 1;
        return;
    }

    if ( WaitVsyncCount < 0 )
    {
        if ( count < 0 )
        {
            WaitVsyncCount = count;
        }

        return;
    }

    WaitVsyncCount = count;
}

s32
rjGetWaitVsyncCount(void)
{
    return WaitVsyncCount;
}

/****** Init ************************************************************************/
void
RFG_FrameSkipInit(void)
{
    WriteNOP(      0x0043CEE7, 0x0043CEED); // stop setting the exec loop count
    WriteShortJump(0x0043CEF3, 0x0043CF16); // skip over the PAL50 code stuff
    
    rjSetWaitVsyncCount(1);
}
