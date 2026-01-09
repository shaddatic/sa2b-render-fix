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

/****** Game ************************************************************************************/
#include <samt/sonic/display.h>     /* display ratio                                            */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_util.h>                /* replacefloat                                             */

/****** Config **********************************************************************************/
#include <cnf.h>                    /* config get                                               */

/****** RF Utility ******************************************************************************/
#include <rfu_float.h>              /* replaceflaot                                             */

/****** Std *************************************************************************************/
#include <math.h>                   /* fmax                                                     */

/****** Self ************************************************************************************/
#include <rf_system/rfsys_internal.h> /* parent & siblings                                      */

/********************************/
/*  Constants                   */
/********************************/
/****** Basic Constants *************************************************************************/
#define SLEEP_GRACE_MS              (0.5)             /* sleep call grace time                  */
#define MS_PER_SEC                  (1000.0)          /* milliseconds per second                */
#define TARGET_MS(wait)             (MS_PER_SEC/(60.0/(f64)(wait))) /* target performance       */

/********************************/
/*  Game Defs                   */
/********************************/
/****** Task Exec *******************************************************************************/
#define TaskExecLoop1               DATA_REF(i32, 0x01DEB50C)
#define TaskExecLoop2               DATA_REF(i32, 0x01DEB514)
#define TaskExecCount               DATA_REF(i32, 0x01DEB510)
#define ExecLoopDebug1              DATA_REF(i32, 0x025EFF60)
#define ExecLoopDebug2              DATA_REF(i32, 0x025EFF60)

/********************************/
/*  Data                        */
/********************************/
/****** User Settings ***************************************************************************/
static bool UseFrameController;     /* enable/disable vsync/frameskip calculations              */
static bool FastVsync;              /* use fast but unnacurate vsync calcs                      */

/****** Target Vsync Mode ***********************************************************************/
static i32 WaitVsyncCount;          /* target vsync wait count                                  */
static i32 SkipVsyncCount;          /* debug skip vsync                                         */
static i32 MinWaitVsync;            /* minimum wait vsync count                                 */

/****** Clock ***********************************************************************************/
static i64 ClockStart;              /* total frame clock start                      (for vsync) */

/****** Frame Time ******************************************************************************/
static f64 FrameTime;               /* last frametime in milliseconds                           */
static f64 FrameTimeTotal;          /* total last frametime in milliseconds                     */

/****** Settings ********************************************************************************/
static bool DebugFrameInfo;         /* debug frametime info                                     */

/********************************/
/*  Source                      */
/********************************/
/****** Static **********************************************************************************/
static i64
GetClock(void)
{
    return osHighResolutionClock();
}

static f64
GetMilliseconds(i64 clock, i64 freq)
{
    return ( (f64)clock / (f64)freq ) * MS_PER_SEC;
}

static f64
GetFrameTime(i64 last_clock, i64 freq)
{
    return ((f64)(osHighResolutionClock() - last_clock) / (f64)freq) * MS_PER_SEC;
}

static f64
GetVsyncWaitValue(void)
{
    return (f64)WaitVsyncCount;
}

/****** Extern **********************************************************************************/
void
RF_SysVsyncSceneStart(void)
{
    static i32 LastFrameskip = 0;

    const i64 freq = osHighResolutionFrequency();

    // vsync
    if ( UseFrameController )
    {
        const f64 vsync_ms = TARGET_MS( GetVsyncWaitValue() );

        const i64 start_clock = GetClock();
        const f64 delta_ms    = GetMilliseconds(start_clock - ClockStart, freq);

        f64 wait_ms = 0.f;

        if ( vsync_ms > delta_ms )
        {
            // if the frame was too fast, wait a bit
            wait_ms = (vsync_ms - delta_ms);
        }
        else
        {
            // if the frame was too slow, wait until the next frame
            wait_ms = TARGET_MS(1) - fmod(delta_ms, TARGET_MS(1));
        }

        if ( wait_ms > 0.f )
        {
            if ( FastVsync )
            {
                u32 sleep_ms = (u32)floor(wait_ms);

                if ( sleep_ms >= 1 )
                {
                    // sleep to release CPU cycles
                    osSleep( sleep_ms );
                }
            }
            else // accurate
            {
                const i32 sleep_ms = (i32)floor(wait_ms - SLEEP_GRACE_MS);

                // sleep most of the time first to release CPU cycles
                if ( sleep_ms > 0 ) osSleep( (u32) sleep_ms );

                // wait for the remaining time
                while ( wait_ms > GetFrameTime(start_clock, freq) );
            }
        }

        const f64 ftotal = (delta_ms + wait_ms);

        // frameskip

        i32 frameskip = (i32) round( ftotal / TARGET_MS(1) );

        // if this is a sudden lag spike that's lasted longer than a quater of a second (in
        // gametime), then reuse the previous frameskip value
        if ( frameskip >= (LastFrameskip + 15) )
        {
            frameskip      = LastFrameskip;
            LastFrameskip += 1;
        }
        else
        {
            LastFrameskip = frameskip;
        }

        // include vsync frameskips
        frameskip += SkipVsyncCount;

        // set frameskip
        TaskExecLoop1 = frameskip;
        TaskExecLoop2 = frameskip;

        // end
        FrameTime      = delta_ms;
        FrameTimeTotal = ftotal;
    }
    else // frame controller is disabled
    {
        const f64 ftotal = GetMilliseconds(GetClock() - ClockStart, freq);

        FrameTime      = ftotal;
        FrameTimeTotal = ftotal;

        // set frameskip
        TaskExecLoop1 = 1;
        TaskExecLoop2 = 1;
    }

    // get the end of this frame clock for vsync calculations
    ClockStart = GetClock();
}

void
RF_SysVsyncSceneEnd(void)
{
#if 0
    osSleep(33);
#endif

    // frametime debug
    if ( DebugFrameInfo )
    {
        const i64 freq = osHighResolutionFrequency();

        const f64 vsync_ms = TARGET_MS( GetVsyncWaitValue() );

        static f64 s_avg_ms;

        const f64 frame_ms = GetMilliseconds(GetClock() - ClockStart, freq);

        const f64 avg_ms = s_avg_ms + ( (frame_ms - s_avg_ms) / (64.0 / GetVsyncWaitValue()) );

        s_avg_ms = avg_ms;

        const f64 frameskip = round(FrameTimeTotal / TARGET_MS(1));

        mlDebugSetScale( 8 );
        mlDebugSetColor( (frame_ms > vsync_ms) ? 0xFFFF7F7F : 0xFFFFFFFF );

        const i32 x_offset = (i32) roundf(46.f * GetDisplayRatio());

        mlDebugPrintC( NJM_LOCATION( 10+x_offset, 1),   "IMM /      AVG /    TGT" );
        mlDebugPrint(  NJM_LOCATION( 0 +x_offset, 3),   "FPS:%9.02f /%9.02f /%7.02f", MS_PER_SEC / frame_ms, MS_PER_SEC / avg_ms, MS_PER_SEC / vsync_ms );
        mlDebugPrint(  NJM_LOCATION( 0 +x_offset, 4),   "FMS:%9.02f /%9.02f /%7.02f", frame_ms, avg_ms, vsync_ms );
        mlDebugPrint(  NJM_LOCATION(-2 +x_offset, 6), "FSKIP:%9.02f", frameskip );
    }
}

/****** Hook ************************************************************************************/
static void
ResetWaitVsyncCount(void)
{
    RF_SysSetWaitVsyncCount(1);
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

/****** Set Wait Count **************************************************************************/
static void
SetWaitVsyncCount(i32 count)
{
    if ( count > 0 )
    {
        SkipVsyncCount = 0;
        count          = MAX(MinWaitVsync, count);
    }
    else
    {
        SkipVsyncCount = -count;
        count          = MinWaitVsync;
    }

    if ( UseFrameController == 0 )
    {
        count = 1;
    }

    WaitVsyncCount = count;

    TaskExecLoop1 = count;
    TaskExecLoop2 = count;

    TaskExecCount = 0;

    ExecLoopDebug1 = 1;
    ExecLoopDebug2 = 1;
}

void
RF_SysSetWaitVsyncCount(i32 count)
{
    // if 0, force reset count back to 1
    if ( count == 0 )
    {
        SetWaitVsyncCount(1);
        return;
    }

    // if the skip count is non-zero, eg. the game is sped up,
    // don't accept any non-negative values
    if ( SkipVsyncCount )
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

i32
RF_SysGetWaitVsyncCount(void)
{
    return WaitVsyncCount;
}

/****** Init ************************************************************************************/
void
RF_SysVsyncInit(void)
{
    const ml_settings* p_mlset = mlGetUserSettings();

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

    DebugFrameInfo = CNF_GetInt( CNF_DEBUG_FRAMEINFO );

    MinWaitVsync = CNF_GetInt( CNF_GFX_VSYNCWAIT );

    // set wait vsync count
    const int game_speed = CNF_GetInt( CNF_DEBUG_GAMESPEED );

    RF_SysSetWaitVsyncCount( 0 - game_speed );

    const int frame_limit = CNF_GetInt( CNF_GFX_VSYNC );

    switch ( frame_limit )
    {
        case CNFE_GFX_VSYNC_DISABLED:
        {
            break;
        }
        case CNFE_GFX_VSYNC_FAST:
        {
            FastVsync = true;
//          [[fallthrough]];
        }
        case CNFE_GFX_VSYNC_ENABLED:
        {
            UseFrameController = true;
            break;
        }
    }

    if ( frame_limit != CNFE_GFX_VSYNC_DISABLED && p_mlset->limitfps )
    {
        RF_MsgWarn(
            "Frame Controller",

            "It is recommeneded that you disable the Mod Loader's 'Limit Framerate' patch, as "
            "it will conflict with Render Fix's own frame controller and frameskipping systems.\n\n"

            "It can be found in the Mod Manager at: Game Config > Patches > Limit Framerate."
        );
    }

    // start the clock on a reasonable value
    ClockStart = GetClock();
}
