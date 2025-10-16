#include <samt/core.h>
#include <samt/memory.h>
#include <samt/writeop.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** SOC **/
#include <samt/soc/shader.h>

/** Source **/
#include <samt/sonic/task.h>
#include <samt/sonic/camera.h>
#include <samt/sonic/debug.h>
#include <samt/sonic/score.h>
#include <samt/sonic/game.h>
#include <samt/sonic/player.h>
#include <samt/sonic/light.h>
#include <samt/sonic/njctrl.h>
#include <samt/sonic/display.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>
#include <rf_mod.h>
#include <rf_feature.h>
#include <rf_ninja.h>
#include <rf_system.h>

#define byte_0174AFFD           DATA_REF(int8_t  , 0x0174AFFD)
#define SomeCountMax            DATA_REF(size_t  , 0x01A5A3D0)

#define sub_00493A90            FUNC_PTR(void, __cdecl, (void), 0x493A90)
#define njExecuteFade           FUNC_PTR(void, __cdecl, (void), 0x004785A0)
#define DisplayGameHUD          FUNC_PTR(void, __cdecl, (void), 0x0044E9C0)

#define pExecute                DATA_REF(task_exec, 0x01A5A274)

#define SortDispSortList        FUNC_PTR(void, __cdecl, (task*, float), 0x00492F60)

static void
TaskDisplayDisplayer(task* btpl)
{
    if (!btpl)
        return;

    task* const base_tp = btpl;

    task* tp = btpl;

    do
    {
        task* const nexttp = tp->next;

        pExecute = tp->disp;

        if (tp->disp)
            tp->disp(tp);

        pExecute = NULL;

        TaskDisplayDisplayer(tp->ctp);

        tp = nexttp;
    }
    while (tp != base_tp);
}

const void* const TaskDisplayDispSortedList_p = (void*)0x00470D20;
static void
TaskDisplayDispSort(task* btpl)
{
    if (!btpl)
        return;

    __asm
    {
        mov eax, [btpl]
        call TaskDisplayDispSortedList_p
    }
}

static void
TaskDisplayDispSort_NoSort(task* btpl)
{
    if (!btpl)
        return;

    task* const base_tp = btpl;

    task* tp = btpl;

    do
    {
        task* const nexttp = tp->next;

        pExecute = tp->disp_sort;

        if (tp->disp_sort)
            tp->disp_sort(tp);

        pExecute = NULL;

        TaskDisplayDispSort_NoSort(tp->ctp);

        tp = nexttp;
    }
    while (tp != base_tp);
}

static void
TaskDisplayDispSort_Buffer(task* btpl)
{
    if (!btpl)
        return;

    task* const base_tp = btpl;

    task* tp = btpl;

    do
    {
        task* const nexttp = tp->next;

        if (tp->disp_sort && tp->twp)
            SortDispSortList(tp, -1.0);

        tp = nexttp;
    }
    while (tp != base_tp);
}

static void
TaskDisplayDispDelayed(task* btpl)
{
    if (!btpl)
        return;

    task* const base_tp = btpl;

    task* tp = btpl;

    do
    {
        task* const nexttp = tp->next;

        pExecute = tp->disp_dely;

        if (tp->disp_dely)
            tp->disp_dely(tp);
            
        pExecute = NULL;

        TaskDisplayDispDelayed(tp->ctp);

        tp = nexttp;
    }
    while (tp != base_tp);
}

static void
TaskDisplayDispLate(task* btpl)
{
    if (!btpl)
        return;

    task* const base_tp = btpl;

    task* tp = btpl;

    do
    {
        task* const nexttp = tp->next;

        pExecute = tp->disp_late;

        if (tp->disp_late)
            tp->disp_late(tp);

        pExecute = NULL;

        TaskDisplayDispLate(tp->ctp);

        tp = nexttp;
    }
    while (tp != base_tp);
}

static void
TaskDisplayDispLast(task* btpl)
{
    if (!btpl)
        return;

    task* const base_tp = btpl;

    task* tp = btpl;

    do
    {
        task* const nexttp = tp->next;

        pExecute = tp->disp_last;

        if (tp->disp_last)
            tp->disp_last(tp);

        pExecute = NULL;

        TaskDisplayDispLast(tp->ctp);

        tp = nexttp;
    }
    while (tp != base_tp);
}

enum
{
    MOD_DRAW_DISP_BASE_EARLY,   /* "EARLY" is drawn after LEV_1 so the player and LT get first dibs; fixes small sorting issues */
    MOD_DRAW_DISP_BASE,         /* Whereas this is drawn after the entire disp layer is drawn                                   */
    MOD_DRAW_DISP_SORT_EARLY,
    MOD_DRAW_DISP_SORT,
    MOD_DRAW_DISP_DELY_EARLY,
    MOD_DRAW_DISP_DELY,
    NB_MOD_DRAW,
};

static bool ModShadowDrawList[NB_MOD_DRAW] = { true, true, true, true, true, true };

static void
DrawModBuffer(int index)
{
    if (ModShadowDrawList[index])
        RFMOD_DrawBuffer();
}

#define TaskDisplayShadows  FUNC_PTR(void, __cdecl, (void), 0x0046FBC0)

#define SetBaseScreenInfo   FUNC_PTR(void, __cdecl, (void), 0x00458B90)
#define BackupScreenInfo    FUNC_PTR(void, __cdecl, (void), 0x00458EA0)
#define RestoreScreenInfo   FUNC_PTR(void, __cdecl, (void), 0x00458EE0)

#define MultiIntroPno       DATA_REF(int8_t, 0x0174B009)
#define IsSplitscreen       DATA_REF(bool  , 0x0174AFE0)

#define ShadowMapCount      DATA_REF(s16, 0x01A5A3EC)

static void
TaskDisplayDispShad(task* btpl)
{
    if (!btpl)
        return;

    task* const base_tp = btpl;

    task* tp = btpl;

    do
    {
        task* const nexttp = tp->next;

        pExecute = tp->disp_shad;

        if (tp->disp_shad)
            tp->disp_shad(tp);

        pExecute = NULL;

        TaskDisplayDispShad(tp->ctp);

        tp = nexttp;
    }
    while (tp != base_tp);
}

static bool ForceShadowMaps;

void
RFG_ForceShadowMaps(void)
{
    ForceShadowMaps = true;
}

static void
TaskDisplayShadAllTasks(void)
{
    /** Clear mod buffer for new frame **/
    RFMOD_ClearBuffer();

    if (ForceShadowMaps || ShadowMapCount) // Delayed by 1 frame
    {
        /** Draw the modifiers and shadow maps.
            Can screw with screen and lighting,
            so backup & restore too (slow) **/
        BackupScreenInfo();
        TaskDisplayShadows();
        RestoreScreenInfo();

        SetLight(DefaultPlayerLight); // Reset lighting
    }
    else
    {
        /** No shadow maps to draw,
            just draw the modifiers (fast) **/
        TaskDisplayDispShad(btp[0]);
        TaskDisplayDispShad(btp[1]);
        TaskDisplayDispShad(btp[2]);
        TaskDisplayDispShad(btp[3]);
        TaskDisplayDispShad(btp[4]);
        TaskDisplayDispShad(btp[5]);
    }
}

#define GX_SetViewport          FUNC_PTR(void, __cdecl, (float, float, float, float, float, float), 0x00420210)
#define GX_SetScreenRect        FUNC_PTR(void, __cdecl, (float, float, float, float)              , 0x00420390)

static void
SetBaseScreenKeepRect(void)
{
    const NJS_SCREEN scrn =
    {
        .dist = _nj_screen_.dist,
        .cx   = 320.f,
        .cy   = 240.f,
        .w    = 640.f,
        .h    = 480.f,
    };

    njSetScreen(&scrn);

    const f32 a1 = scrn.cx - (scrn.w * 0.5f);
    const f32 a2 = scrn.cy - (scrn.h * 0.5f);
    
    GX_SetViewport(a1, a2, scrn.w, scrn.h, 0.f, 1.f);
//  GX_SetScreenRect(a1, a2, scrn.w, scrn.h);

    gjSetPerspective((scrn.w/scrn.h), 1.f, 100000.f);
}

bool
GetCurrCameraCullState(void)
{
    if (byte_0174AFFD == 1)
    {
        return cameraNumber == 0;
    }
    else if (byte_0174AFFD == 2)
    {
        return cameraNumber == 1;
    }
    else
    {
        return byte_0174AFFD == 3;
    }
}

static void
StartPillarBox(void)
{
    RF_SysCtrlDrawPillar( false ); // not final
}

static void
EndPillarBox(void)
{
    RF_SysCtrlDrawPillar( true ); // final pass
    RF_SysCtrlResetPillar();
}

#define FadeColor       DATA_REF(NJS_COLOR      , 0x0171CDA0)
#define FadePoly        DATA_ARY(NJS_POLYGON_VTX, 0x0171CD60, [4])

static void
DrawGameFade(void)
{
    RF_SysDrawScreenFade( FadeColor, FadePoly[0].z );
}

static void
TaskDisplayAll(void)
{
    const bool no_draw = GetCurrCameraCullState();

    /** Some tasks don't reset the constant material. This is normally handled in
        the task 'disp_shad' exec function, but since that doesn't run anymore we
        need to handle it ourselves. This was likely a thing on DC too **/

    ResetConstantMaterial();

    StartPillarBox();

    /** Draw Displayer **/
    {
        gjSetRenderMode(GJD_DRAW_SOLID | GJD_DRAW_TRANS);
        TaskDisplayDisplayer(btp[0]);

        TaskDisplayShadAllTasks();

        gjSetRenderMode(GJD_DRAW_SOLID);
        TaskDisplayDisplayer(btp[1]);

        DrawModBuffer(MOD_DRAW_DISP_BASE_EARLY);

        gjSetRenderMode(GJD_DRAW_SOLID | GJD_DRAW_TRANS);

        if (!no_draw)
        {
            TaskDisplayDisplayer(btp[2]);
            TaskDisplayDisplayer(btp[3]);
            TaskDisplayDisplayer(btp[4]);
            TaskDisplayDisplayer(btp[5]);

            DrawModBuffer(MOD_DRAW_DISP_BASE);
        }
    }

    /** Draw Sorted displayer **/
    {
        gjSetRenderMode(GJD_DRAW_TRANS);

        TaskDisplayDispSort(btp[0]);
        TaskDisplayDispSort_NoSort(btp[1]);

        DrawModBuffer(MOD_DRAW_DISP_SORT_EARLY);

        if (SomeCountMax)
        {
            if (!no_draw)
            {
                TaskDisplayDispSort_Buffer(btp[2]);
                TaskDisplayDispSort_Buffer(btp[3]);
                TaskDisplayDispSort_Buffer(btp[4]);
                TaskDisplayDispSort_Buffer(btp[5]);
            }

            sub_00493A90();

            DrawModBuffer(MOD_DRAW_DISP_SORT);
        }
        else
        {
            if (!no_draw)
            {
                TaskDisplayDispSort(btp[2]);
                TaskDisplayDispSort(btp[3]);
                TaskDisplayDispSort(btp[4]);
                TaskDisplayDispSort(btp[5]);

                DrawModBuffer(MOD_DRAW_DISP_SORT);
            }
        }
    }

    /** Draw Delayed displayer **/
    {
        TaskDisplayDispDelayed(btp[0]);
        TaskDisplayDispDelayed(btp[1]);

        DrawModBuffer(MOD_DRAW_DISP_DELY_EARLY);

        if (!no_draw)
        {
            TaskDisplayDispDelayed(btp[2]);
            TaskDisplayDispDelayed(btp[3]);
            TaskDisplayDispDelayed(btp[4]);
            TaskDisplayDispDelayed(btp[5]);

            DrawModBuffer(MOD_DRAW_DISP_DELY);
        }
    }

    //StartHud();

    /** Draw game HUD **/
    if (ulGlobalMode == MD_ACTION && ssGameMode != MD_GAME_INIT && !MultiIntroPno)
    {
        if (!IsSplitscreen)
        {
            DisplayGameHUD();
        }
        else
        {
            BackupScreenInfo();
            SetBaseScreenKeepRect();
            DisplayGameHUD();
            RestoreScreenInfo();
        }
    }
    
    /** Draw fade **/
    DrawGameFade();

    //EndHud();

    /** Draw Late displayer **/
    TaskDisplayDispLate(btp[0]);
    TaskDisplayDispLate(btp[1]);

    if (!no_draw)
    {
        TaskDisplayDispLate(btp[2]);
        TaskDisplayDispLate(btp[3]);
        TaskDisplayDispLate(btp[4]);
        TaskDisplayDispLate(btp[5]);
    }

    /** Draw Last displayer **/
    TaskDisplayDispLast(btp[0]);
    TaskDisplayDispLast(btp[1]);

    if (!no_draw)
    {
        TaskDisplayDispLast(btp[2]);
        TaskDisplayDispLast(btp[3]);
        TaskDisplayDispLast(btp[4]);
        TaskDisplayDispLast(btp[5]);
    }

    gjSetRenderMode(GJD_DRAW_SOLID | GJD_DRAW_TRANS);

#if 0
    ML_SetDebugFontColor(0xFFFFFFFF);
    ML_SetDebugFontScale(24.f);

    ML_DisplayDebugString(NJM_LOCATION(1 , 15), "GLOBAL MD:");
    ML_DisplayDebugInt(   NJM_LOCATION(12, 15), ulGlobalMode, 2);

    ML_DisplayDebugString(NJM_LOCATION(1 , 16), "GAME MD:");
    ML_DisplayDebugInt(   NJM_LOCATION(12, 16), ssGameMode, 2);
#endif

    EndPillarBox();

    // Mod Loader debug text fix, logic oversight causes it to set the wrong shader on older
    // versions if this isn't done.
    SetShaderType( SHADER_TYPE_UI );
}

void
RFG_TaskDisplayInit(void)
{
    WriteJump(0x00470010, TaskDisplayAll);

    /** Draw HUD **/
    KillCall(0x0043D134);
    KillCall(0x0043D26F);
    KillCall(0x0043D290);
    KillCall(0x0043D4D5);
    KillCall(0x0043D4F8);
    
    /** Draw shadows **/
    KillCall(0x0047050E);
    KillCall(0x004708A3);

    if ( RFF_CheapShadowPerformance() )
    {
        /** Disable all the early draws to reduce draw calls **/
        ModShadowDrawList[MOD_DRAW_DISP_BASE_EARLY] = false;
        ModShadowDrawList[MOD_DRAW_DISP_SORT_EARLY] = false;
        ModShadowDrawList[MOD_DRAW_DISP_DELY_EARLY] = false;
        ModShadowDrawList[MOD_DRAW_DISP_DELY]       = false; /* "Dely" draw list is rarely used for shadow
                                                                effected stuff, so disable it entirely */
    }

    if ( RF_ConfigGetInt(CNF_DEBUG_MODIFIER) )
    {
        /** Disable all but one draw to stop the modifiers drawing too dark **/
        ModShadowDrawList[MOD_DRAW_DISP_BASE_EARLY] = false;
        ModShadowDrawList[MOD_DRAW_DISP_BASE]       = false;
        ModShadowDrawList[MOD_DRAW_DISP_SORT_EARLY] = false;
        ModShadowDrawList[MOD_DRAW_DISP_DELY_EARLY] = false;
        ModShadowDrawList[MOD_DRAW_DISP_DELY]       = false;
    }

    /** Avoid crash that only 
        happens in debug mode **/
#ifndef NDEBUG
    KillCall(0x0068B3B9);
#endif
}
