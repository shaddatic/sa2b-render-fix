#include <sa2b/core.h>
#include <sa2b/memory.h>
#include <sa2b/funchook.h>
#include <sa2b/writeop.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/sonic/task.h>
#include <sa2b/sonic/camera.h>
#include <sa2b/sonic/debug.h>
#include <sa2b/sonic/score.h>
#include <sa2b/sonic/game.h>
#include <sa2b/sonic/player.h>
#include <sa2b/sonic/light.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>
#include <rf_mod.h>
#include <rf_feature.h>

#define byte_0174AFFD           DATA_REF(int8_t  , 0x0174AFFD)
#define SomeCountMax            DATA_REF(size_t  , 0x01A5A3D0)

#define sub_00493A90            FUNC_PTR(void, __cdecl, (void), 0x493A90)
#define njExecuteFade           FUNC_PTR(void, __cdecl, (void), 0x004785A0)
#define DisplayGameHUD          FUNC_PTR(void, __cdecl, (void), 0x0044E9C0)

#define pExecute                DATA_REF(task_exec, 0x01A5A274)

#define SortDispSortList        FUNC_PTR(void, __cdecl, (TASK*, float), 0x00492F60)

static void
TaskDisplayDisplayer(TASK* btpl)
{
    if (!btpl)
        return;

    TASK* const base_tp = btpl;

    TASK* tp = btpl;

    do
    {
        TASK* const nexttp = tp->next;

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
TaskDisplayDispSort(TASK* btpl)
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
TaskDisplayDispSort_NoSort(TASK* btpl)
{
    if (!btpl)
        return;

    TASK* const base_tp = btpl;

    TASK* tp = btpl;

    do
    {
        TASK* const nexttp = tp->next;

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
TaskDisplayDispSort_Buffer(TASK* btpl)
{
    if (!btpl)
        return;

    TASK* const base_tp = btpl;

    TASK* tp = btpl;

    do
    {
        TASK* const nexttp = tp->next;

        if (tp->disp_sort && tp->twp)
            SortDispSortList(tp, -1.0);

        tp = nexttp;
    }
    while (tp != base_tp);
}

static void
TaskDisplayDispDelayed(TASK* btpl)
{
    if (!btpl)
        return;

    TASK* const base_tp = btpl;

    TASK* tp = btpl;

    do
    {
        TASK* const nexttp = tp->next;

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
TaskDisplayDispLate(TASK* btpl)
{
    if (!btpl)
        return;

    TASK* const base_tp = btpl;

    TASK* tp = btpl;

    do
    {
        TASK* const nexttp = tp->next;

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
TaskDisplayDispLast(TASK* btpl)
{
    if (!btpl)
        return;

    TASK* const base_tp = btpl;

    TASK* tp = btpl;

    do
    {
        TASK* const nexttp = tp->next;

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
ClearModBuffer(void)
{
    RFMOD_ClearBuffer(); 
}

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

static hook_info* TaskDisplayShadowsHookInfo;

static void
TaskDisplayShadowsHook(void)
{
    RFMOD_ClearBuffer(); 
    RFMOD_SetInvViewMatrix();

    FuncHookCall( TaskDisplayShadowsHookInfo, TaskDisplayShadows() );
}

static void
TaskDisplayAll(void)
{
    bool no_draw;

    if (byte_0174AFFD == 1)
    {
        no_draw = cameraNumber == 0;
    }
    else if (byte_0174AFFD == 2)
    {
        no_draw = cameraNumber == 1;
    }
    else
    {
        no_draw = byte_0174AFFD == 3;
    }

    /** Draw Displayer **/
    {
        gjSetRenderMode(GJD_DRAW_SOLID | GJD_DRAW_TRANS);
        TaskDisplayDisplayer(btp[0]);

        RFMOD_CalcBuffer();     // Calculate buffer for new frame

        SetLighting(DefaultPlayerLight); // Reset lighting

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

    /** Draw game HUD **/
    if (ulGlobalMode == MD_ACTION && !MultiIntroPno && playerpwp[0])
    {
        if (IsSplitscreen)
        {
            SetBaseScreenInfo();
            DisplayGameHUD();
            RestoreScreenInfo();
        }
        else
            DisplayGameHUD();
    }
    
    /** Draw fade **/
    njExecuteFade();

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
}

void
RFG_TaskDisplayInit(void)
{
    WriteJump(0x00470010, TaskDisplayAll);

    TaskDisplayShadowsHookInfo = FuncHook(TaskDisplayShadows, TaskDisplayShadowsHook);

    /** Draw HUD **/
    KillCall(0x0043D134);
    KillCall(0x0043D26F);
    KillCall(0x0043D290);
    KillCall(0x0043D4D5);
    KillCall(0x0043D4F8);
    
    /** Draw shadows **/
//  KillCall(0x0047050E);
//  KillCall(0x004708A3);

    if (RF_ConfigGetInt(CNF_SHADOW_CHSMD) <= CNFE_SHADOW_CHSMD_PERFORMANCE)
    {
        /** Disable all the early draws to reduce draw calls **/
        ModShadowDrawList[MOD_DRAW_DISP_BASE_EARLY] = false;
        ModShadowDrawList[MOD_DRAW_DISP_SORT_EARLY] = false;
        ModShadowDrawList[MOD_DRAW_DISP_DELY_EARLY] = false;
        ModShadowDrawList[MOD_DRAW_DISP_DELY]       = false; /* "Dely" draw list is rarely used for shadow
                                                                effected stuff, so disable it entirely */
    }

    if (RF_ConfigGetInt(CNF_DEBUG_MODIFIER))
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
