/********************************/
/*  Includes                    */
/********************************/
/****** Core Toolkit ****************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/init.h>              /* export dll                                               */
#include <samt/writeop.h>           /* writenop/jump                                            */
#include <samt/writemem.h>          /* writedata                                                */
#include <samt/os.h>                /* highresclock                                             */
#include <samt/modloader.h>         /* debugprint                                               */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_config.h>              /* config                                                   */
#include <rf_util.h>                /* replacefloat                                             */
#include <rf_config.h>              /* config get                                               */

/****** RF Utility ******************************************************************************/
#include <rfu_float.h>              /* replaceflaot                                             */

/****** Std *************************************************************************************/
#include <math.h>                   /* fmax                                                     */

/****** Self ************************************************************************************/
#include <rf_module/rfm_global/rfg_internal.h> /* parent & siblings                             */

/********************************/
/*  Constants                   */
/********************************/
/****** Basic Constants *************************************************************************/
#define SLEEP_GRACE_MS              (1)               /* sleep call grace time                  */
#define MS_PER_SEC                  (1000.0)          /* milliseconds per second                */
#define TARGET_MS                   (MS_PER_SEC/60.0) /* target performance                     */

/********************************/
/*  Game Defs                   */
/********************************/
/****** Task Exec *******************************************************************************/
#define TaskExecLoop1               DATA_REF(s32, 0x01DEB50C)
#define TaskExecLoop2               DATA_REF(s32, 0x01DEB514)
#define TaskExecCount               DATA_REF(s32, 0x01DEB510)
#define ExecLoopDebug1              DATA_REF(s32, 0x025EFF60)
#define ExecLoopDebug2              DATA_REF(s32, 0x025EFF60)

/********************************/
/*  Data                        */
/********************************/
/****** Target Vsync Mode ***********************************************************************/
static s32 WaitVsyncCount;          /* target vsync wait count                                  */

/****** Clock ***********************************************************************************/
static s64 ClockStart;              /* total frame clock start                      (for vsync) */
static s64 FrameStart;              /* frametime clock start                   (for debug info) */

/****** Frame Time ******************************************************************************/
static f64 FrameTime;               /* last frametime in milliseconds                           */
static f64 FrameTimeTotal;          /* total last frametime in milliseconds                     */

/****** Settings ********************************************************************************/
static bool DebugFrameInfo;         /* debug frametime info                                     */

/********************************/
/*  Source                      */
/********************************/
/****** Static **********************************************************************************/
static s64
GetClock(void)
{
    return osHighResolutionClock();
}

static f64
GetMilliseconds(s64 clock, s64 freq)
{
    return ( (f64)clock / (f64)freq ) * MS_PER_SEC;
}

static f64
GetFrameTime(s64 last_clock, s64 freq)
{
    return ((f64)(osHighResolutionClock() - last_clock) / (f64)freq) * MS_PER_SEC;
}

static s32
GetVsyncFrameskip(void)
{
    const s32 wait_vsync = WaitVsyncCount;

    return ( wait_vsync >= 0 ) ? wait_vsync - 1 : -wait_vsync;
}

/****** Extern **********************************************************************************/
void
RF_FrameSkipSceneStart(void)
{
    static s32 LastFrameskip = 0;

    // get the start of the frame clock for debug frametime info
    FrameStart = GetClock();

    // frameskip
    {
        s32 frameskip = 1 + (s32)floor(FrameTime / TARGET_MS);

        // if this is a sudden lag spike that's lasted longer than a quater of a second (in
        // gametime), then reuse the previous frameskip value
        if ( frameskip >= (LastFrameskip + 15) )
        {
            frameskip = LastFrameskip;
        }

        LastFrameskip = frameskip;

        // include vsync frameskips
        frameskip += GetVsyncFrameskip();

        // set frameskip
        TaskExecLoop1 = frameskip;
        TaskExecLoop2 = frameskip;
    }
}

void
RF_FrameSkipSceneEnd(void)
{
    const s64 freq = osHighResolutionFrequency();

    const f64 vsync_wait_count = ( WaitVsyncCount >= 0 ) ? (f64)WaitVsyncCount : 1.0;

    const f64 vsync_ms = (TARGET_MS * vsync_wait_count);

    // frametime debug
    if ( DebugFrameInfo )
    {
        static f64 s_avg_ms;

        const f64 frame_ms = GetMilliseconds(GetClock() - FrameStart, freq);

        const f64 avg_ms = s_avg_ms + ( (frame_ms - s_avg_ms) / (64.0 / vsync_wait_count) );

        mlDebugSetScale( 8 );
        mlDebugSetColor( (frame_ms > vsync_ms) ? 0xFFFF0000 : 0xFFFFFFFF );

        mlDebugPrintC( NJM_LOCATION(11,1), "IMM /      AVG /    TGT");

        mlDebugPrint(NJM_LOCATION(1,3), "FPS:%9.02f /%9.02f /%7.02f", MS_PER_SEC / frame_ms, MS_PER_SEC / avg_ms, MS_PER_SEC / vsync_ms);
        mlDebugPrint(NJM_LOCATION(1,4), "FMS:%9.02f /%9.02f /%7.02f", frame_ms, avg_ms, vsync_ms);

        s_avg_ms = avg_ms;
    }

    // vsync
    {
        const s64 start_clock = GetClock();

        const f64 delta_ms = GetMilliseconds(start_clock - ClockStart, freq);

        f64 wait_ms = 0.f;

        // if the frame was too fast, wait a bit
        if ( vsync_ms > delta_ms )
        {
            wait_ms = (vsync_ms - delta_ms);
        }
        // if the frame was too slow, wait for next open vsync window
        else if ( vsync_ms < delta_ms )
        {
            wait_ms = TARGET_MS - fmod(delta_ms, TARGET_MS);
        }

        if ( wait_ms != 0.f )
        {
            const u32 sleep_ms = (u32)floor(wait_ms);

            // sleep most of the time first to save CPU time
            if ( sleep_ms > SLEEP_GRACE_MS ) osSleep( sleep_ms - SLEEP_GRACE_MS );

            // wait for the remaining time
            while ( wait_ms > GetFrameTime(start_clock, freq) );
        }

        FrameTime      = delta_ms;
        FrameTimeTotal = delta_ms + wait_ms;
    }

    // get the end of this frame clock for vsync calculations
    ClockStart = GetClock();
}

/****** Extern **********************************************************************************/
___TODO("These will be moved to a seperate module eventually");

static void
SetWaitVsyncCount(Sint32 count)
{
    WaitVsyncCount = count;

    TaskExecLoop1 = ABS(count);
    TaskExecLoop2 = ABS(count);

    TaskExecCount = 0;

    ExecLoopDebug1 = 1;
    ExecLoopDebug2 = 1;
}

void
rjSetWaitVsyncCount(Sint32 count)
{
    // if 0, force reset count back to 1
    if ( count == 0 )
    {
        SetWaitVsyncCount(1);
        return;
    }

    // if the wait count is negative, eg. the game is sped up,
    // don't accept any non-negative values
    if ( WaitVsyncCount < 0 )
    {
        if ( count < 0 )
        {
            SetWaitVsyncCount(count);
        }
        return;
    }

    // otherwise, just set the value as given
    SetWaitVsyncCount(count);
}

s32
rjGetWaitVsyncCount(void)
{
    return WaitVsyncCount;
}

/****** Hook ************************************************************************************/
static void
ResetWaitVsyncCount(void)
{
    rjSetWaitVsyncCount(1);
}

static f64
GetFrameTimeMidi(void)
{
    // Give the game the actual frametime in ms, it will then do 'ft - 0.f' because we set the
    // start time to 0 and continue on as normal with the correct frametime info
    return FrameTimeTotal;
}

static void
SetMidiPerformanceCounter(void)
{
    // set the sequence start and last tick values to 0, so we can just return the actual
    // frametime value a bit later
    DATA_ARY(u64, 0x01934B08, [1000])[4] = 0;
    DATA_ARY(u64, 0x01934B08, [1000])[5] = 0;
}

/****** Init ************************************************************************************/
void
RFG_FrameSkipInit(void)
{
    WriteNOP(      0x0043CEE7, 0x0043CEED); // stop setting the exec loop count
    WriteShortJump(0x0043CEF3, 0x0043CF16); // skip over the PAL50 code stuff

    WriteNOP(      0x0043CC3C, 0x0043CC42); // ^^
    WriteShortJump(0x0043CC48, 0x0043CC6B);

    /** Inlined 'njSetWaitVsyncCount' Calls **/

    WriteNOP( 0x0043CB51, 0x0043CB5B);
    WriteNOP( 0x0043CB5C, 0x0043CB6B);
    WriteCall(0x0043CB51, ResetWaitVsyncCount);
    
    WriteNOP( 0x0051909E, 0x005190B2);
    WriteCall(0x0051909E, ResetWaitVsyncCount);
    
    WriteNOP( 0x005F71EB, 0x005F71F5);
    WriteNOP( 0x005F71FD, 0x005F7209);
    WriteCall(0x005F71EB, ResetWaitVsyncCount);
    
    WriteNOP( 0x005F8EE5, 0x005F8EF9); // event: end of time card
    WriteCall(0x005F8EE5, ResetWaitVsyncCount);
    
    WriteNOP( 0x005FB986, 0x005FB98B);
    WriteNOP( 0x005FB998, 0x005FB99D);
    WriteNOP( 0x005FB9AB, 0x005FB9B0);
    WriteNOP( 0x005FB9B6, 0x005FB9BB);
    WriteNOP( 0x005FB9C1, 0x005FB9C6);
    WriteCall(0x005FB986, ResetWaitVsyncCount);
    
    WriteNOP( 0x0051909E, 0x005190B8);
    WriteCall(0x0051909E, ResetWaitVsyncCount);
    
    WriteNOP( 0x00602B5C, 0x00602B72); // event: start
    WriteCall(0x00602B5C, ResetWaitVsyncCount);
    
    WriteNOP( 0x005F71EB, 0x005F71F5);
    WriteNOP( 0x005F71FD, 0x005F720F);
    WriteCall(0x005F71EB, ResetWaitVsyncCount);
    
    WriteNOP( 0x00670670, 0x00670689);
    WriteCall(0x00670670, ResetWaitVsyncCount);
    
    WriteNOP( 0x00791EAE, 0x00791EC8);
    WriteCall(0x00791EAE, ResetWaitVsyncCount);
    
    WriteNOP( 0x0079318B, 0x007931A7);
    WriteCall(0x0079318B, ResetWaitVsyncCount);

    /** Fix Sequence audio timing **/

    WriteNOP( 0x00436990, 0x0043699B);
    WriteNOP( 0x00436952, 0x0043699B);
    WriteCall(0x00436961, SetMidiPerformanceCounter);

    WriteNOP( 0x004363DB, 0x004363F1);
    WriteCall(0x004363B3, SetMidiPerformanceCounter);
    KillCall(0x004363B8);

    WriteCall(0x00436427, GetFrameTimeMidi);

    // with our other fixes, their magic number breaks so we need to adjust it to get the
    // sequence data to play at a normal speed again, but this will work for all framerates
    RFU_ReplaceFloat(0x00436448, 8.4);

    /** End **/

    DebugFrameInfo = RF_ConfigGetInt( CNF_DEBUG_FRAMEINFO );

    // set wait vsync count
    const int game_speed = RF_ConfigGetInt( CNF_DEBUG_GAMESPEED );

    rjSetWaitVsyncCount( 0 - game_speed );
}
