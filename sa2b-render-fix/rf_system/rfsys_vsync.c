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
#include <samt/arch.h>              /* arch                                                     */

/****** Game ************************************************************************************/
#include <samt/sonic/display.h>     /* display ratio                                            */

/****** Dx9ctrl *********************************************************************************/
#include <dx9ctrl/dx9ctrl.h>        /* dx9ctrl                                                  */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_util.h>                /* replacefloat                                             */

/****** Config **********************************************************************************/
#include <cnf.h>                    /* config get                                               */

/****** RF Utility ******************************************************************************/
#include <rfu_float.h>              /* replaceflaot                                             */

/****** Std *************************************************************************************/
#include <math.h>                   /* fmax                                                     */

/****** OS **************************************************************************************/
#include <windows.h>

/****** Self ************************************************************************************/
#include <rf_system/rfsys_internal.h> /* parent & siblings                                      */

/********************************/
/*  Constants                   */
/********************************/
/****** Basic Constants *************************************************************************/
#define SLEEP_GRACE_MS              (0.8)             /* sleep call grace time                  */
#define MS_PER_SEC                  (1000.0)          /* milliseconds per second                */
#define TARGET_MS(wait)             (MS_PER_SEC/(60.0/(f64)(wait))) /* target performance       */
#define CLOCK_INC(freq)             ((freq)/60)

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
/****** Windows Vars ****************************************************************************/
static HANDLE HdlTimer;             /* windows timer handle                                     */

/****** User Settings ***************************************************************************/
static bool UseFrameController;     /* enable/disable vsync/frameskip calculations              */

/****** Target Vsync Mode ***********************************************************************/
static i32 WaitVsyncCount;          /* target vsync wait count                                  */
static i32 MinWaitVsync;            /* minimum wait vsync count                                 */

/****** Clock ***********************************************************************************/
static i64 FrameClockStart;         /* start of frame                                           */
static i64 FrameClock;              /* rigidly incremented clock                    (for vsync) */

/****** Frame Time ******************************************************************************/
static f64 FrameTime;               /* total last frametime in milliseconds                     */

/****** Debug ***********************************************************************************/
static i32 DbgSkipVsync;            /* debug skip vsync                                         */
static bool DbgFrameInfo;           /* debug frametime info                                     */
static f64  DbgFrameDelta;          /* last delta time in milliseconds                          */
static i32  DbgFrameSkip;           /* debug frame skip value                                   */

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
GetFrameTimeNow(i64 last_clock, i64 freq)
{
    return ((f64)(osHighResolutionClock() - last_clock) / (f64)freq) * MS_PER_SEC;
}

static f64
GetVsyncWaitValue(void)
{
    return (f64)WaitVsyncCount;
}

static void
SleepUntil(i64 tgtclock)
{
    // if the time has already passed, do nothing
    if ( tgtclock <= GetClock() )
    {
        return;
    }

    const i64 freq = osHighResolutionFrequency();

    for ( ; ; )
    {
        const f64 ms_sleep = GetMilliseconds(tgtclock - GetClock(), freq) - SLEEP_GRACE_MS;

        // if the time to sleep is non-positive, stop
        if ( ms_sleep <= 0.0 )
        {
            break;
        }

        // sleep most of the time first to release CPU cycles
        const LARGE_INTEGER timer = { .QuadPart = (i64)floor( (ms_sleep) / 0.9 ) };

        SetWaitableTimerEx(  HdlTimer, &timer, 0, NULL, NULL, NULL, 0 );
        WaitForSingleObject( HdlTimer, INFINITE );
    }

    // spin for the remaining time
    while ( tgtclock > GetClock() )
    {
        mtArchYield();
    }
}

/****** Extern **********************************************************************************/
void
RF_SysResetFrameClock(void)
{
    FrameClock = 0;
}

void
RF_SysVsyncSceneStart(void)
{
    const i64 clock_vsync_start = GetClock();

    // if the frame controller is disabled
    if ( !UseFrameController )
    {
        // set frameskip
        TaskExecLoop1 = 1;
        TaskExecLoop2 = 1;
        return;
    }

    // start frame clock
    if ( !FrameClock )
    {
        // wait for vblank
        while ( DX9_InVBlank() == FALSE )
        {
            mtArchYield();
        }
        
        // wait for end of vblank
        while ( DX9_InVBlank() == TRUE )
        {
            mtArchYield();
        }

        // now set frame clock
        FrameClock = GetClock();
    }

    // frequency
    const i64 freq = osHighResolutionFrequency();

    // wait for vsync and get frameskip count
    const i32 nb_vsync = WaitVsyncCount;
    i32 fskip = 0;

    // wait for vsync interval
    do 
    {
        SleepUntil(FrameClock);

        // set next frame clock
        FrameClock += CLOCK_INC(freq);

        // inc frameskip
        fskip++;
    }
    while ( (fskip < nb_vsync) || (FrameClock < clock_vsync_start) );

    // set frame time
    FrameTime = (f64)fskip * TARGET_MS(1);

    // frameskip
    if ( fskip > 15 )
    {
        // if that frame took longer than a quater-second, clamp fskip
        fskip = 15;
    }

    // include debug game speed
    fskip += DbgSkipVsync;

    // set frameskip
    TaskExecLoop1 = fskip;
    TaskExecLoop2 = fskip;

    // set debug info
    DbgFrameDelta = GetMilliseconds(clock_vsync_start - FrameClockStart, freq);
    DbgFrameSkip  = fskip;

    // get the start of this frame for vsync calculations
    FrameClockStart = GetClock();
}

void
RF_SysVsyncSceneEnd(void)
{
    static f64 DbgAvgMs;

#if 0
    Sleep(20);
#endif

    // frametime debug
    if ( DbgFrameInfo )
    {
        const i64 freq = osHighResolutionFrequency();

        const f64 vsync_ms = TARGET_MS( GetVsyncWaitValue() );

        const f64 frame_ms = DbgFrameDelta;

        DbgAvgMs = DbgAvgMs + ( (frame_ms - DbgAvgMs) / (64.0 / GetVsyncWaitValue()) );

        mlDebugSetScale( 8 );
        mlDebugSetColor( (frame_ms > vsync_ms) ? 0xFFFF7F7F : 0xFFFFFFFF );

        const i32 x_offset = (i32) roundf(46.f * GetDisplayRatio());

        mlDebugPrintC( NJM_LOCATION(10 +x_offset, 1),   "IMM /      AVG /    TGT" );
        mlDebugPrint(  NJM_LOCATION( 0 +x_offset, 3),   "FPS:%9.02f /%9.02f /%7.02f", MS_PER_SEC / frame_ms, MS_PER_SEC / DbgAvgMs, MS_PER_SEC / vsync_ms );
        mlDebugPrint(  NJM_LOCATION( 0 +x_offset, 4),   "FMS:%9.02f /%9.02f /%7.02f", frame_ms, DbgAvgMs, vsync_ms );
        mlDebugPrint(  NJM_LOCATION(-2 +x_offset, 6), "FSKIP:%9.02f", (f32)DbgFrameSkip );
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
    return FrameTime;
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
        DbgSkipVsync = 0;
        count          = MAX(MinWaitVsync, count);
    }
    else
    {
        DbgSkipVsync = -count;
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
    if ( DbgSkipVsync )
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

    // set wait vsync count
    const int game_speed = CNF_GetInt( CNF_DEBUG_GAMESPEED );

    RF_SysSetWaitVsyncCount( 0 - game_speed );

    // set config
    UseFrameController = CNF_GetInt( CNF_GFX_VSYNC );
    MinWaitVsync       = CNF_GetInt( CNF_GFX_VSYNCWAIT );

    if ( UseFrameController && mlGetUserSettings()->limitfps )
    {
        RF_MsgWarn(
            "Frame Controller",

            "It is recommeneded that you disable the Mod Loader's 'Lock Framerate' patch, as "
            "it will conflict with Render Fix's own frame controller and frameskipping systems.\n\n"

            "It can be found in the Mod Manager at: Game Config > Patches > Limit Framerate."
        );
    }

    // set debug info
    DbgFrameInfo = CNF_GetInt( CNF_DEBUG_FRAMEINFO ) && UseFrameController;

    // get the timer handle
    HdlTimer = CreateWaitableTimerExW(NULL, NULL, CREATE_WAITABLE_TIMER_HIGH_RESOLUTION, TIMER_ALL_ACCESS);
}
