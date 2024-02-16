#include <sa2b/core.h>
#include <sa2b/memory.h>
#include <sa2b/memutil.h>
#include <sa2b/funchook.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/src/task.h>
#include <sa2b/src/camera.h>
#include <sa2b/src/debug.h>
#include <sa2b/src/score.h>
#include <sa2b/src/game.h>
#include <sa2b/src/player.h>
#include <sa2b/src/light.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_mod.h>
#include <rf_feature.h>

#define GJD_DRAW_SOLID          (0x01)
#define GJD_DRAW_TRANS          (0x02)

#define _gj_render_mode_        DataRef(uint32_t, 0x025EFEE0)
#define byte_0174AFFD           DataRef(int8_t  , 0x0174AFFD)
#define SomeCountMax            DataRef(size_t  , 0x01A5A3D0)

#define sub_00493A90            FuncPtr(void, __cdecl, (), 0x493A90)
#define njExecuteFade           FuncPtr(void, __cdecl, (), 0x004785A0)
#define DisplayGameHUD          FuncPtr(void, __cdecl, (), 0x0044E9C0)

#define pExecute                DataRef(task_exec, 0x01A5A274)

#define SortDispSortList        FuncPtr(void, __cdecl, (TASK *, float), 0x00492F60)

void
gjSetRenderMode(Sint32 mode)
{
    _gj_render_mode_ = mode;
}

static void
TaskDisplayDisplayer(TASK* btpl)
{
    if (!btpl)
        return;

    TASK* const base_tp = btpl;

    TASK* tp = btpl;

    do
    {
        pExecute = tp->disp;

        if (tp->disp)
            tp->disp(tp);

        pExecute = NULL;

        TaskDisplayDisplayer(tp->ctp);
    }
    while (tp = tp->next, tp != base_tp);
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
        pExecute = tp->disp_sort;

        if (tp->disp_sort)
            tp->disp_sort(tp);

        pExecute = NULL;

        TaskDisplayDispSort_NoSort(tp->ctp);

    }
    while (tp = tp->next, tp != base_tp);
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
        if (tp->disp_sort && tp->twp)
            SortDispSortList(tp, -1.0);
    }
    while (tp = tp->next, tp != base_tp);
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
        pExecute = tp->disp_dely;

        if (tp->disp_dely)
            tp->disp_dely(tp);
            
        pExecute = NULL;

        TaskDisplayDispDelayed(tp->ctp);

    }
    while (tp = tp->next, tp != base_tp);
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
        pExecute = tp->disp_late;

        if (tp->disp_late)
            tp->disp_late(tp);

        pExecute = NULL;

        TaskDisplayDispLate(tp->ctp);

    }
    while (tp = tp->next, tp != base_tp);
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
        pExecute = tp->disp_last;

        if (tp->disp_last)
            tp->disp_last(tp);

        pExecute = NULL;

        TaskDisplayDispLast(tp->ctp);

    }
    while (tp = tp->next, tp != base_tp);
}

#define TaskDisplayShadows  FuncPtr(void, __cdecl, (), 0x0046FBC0)

#define SetBaseScreenInfo   FuncPtr(void, __cdecl, (), 0x00458B90)
#define BackupScreenInfo    FuncPtr(void, __cdecl, (), 0x00458EA0)
#define RestoreScreenInfo   FuncPtr(void, __cdecl, (), 0x00458EE0)

#define MultiIntroPno       DataRef(int8_t, 0x0174B009)
#define IsSplitscreen       DataRef(bool  , 0x0174AFE0)

static void
TaskDisplayAll()
{
    const bool chs_performance = RF_CheapShadowPerformance();

    bool no_draw;

    if (byte_0174AFFD == 1)
    {
        no_draw = cameraControlWorkIndex == 0;
    }
    else if (byte_0174AFFD == 2)
    {
        no_draw = cameraControlWorkIndex == 1;
    }
    else
    {
        no_draw = byte_0174AFFD == 3;
    }

    /** Draw Displayer **/
    gjSetRenderMode(GJD_DRAW_SOLID | GJD_DRAW_TRANS);
    TaskDisplayDisplayer(btp[0]);

    RFMOD_ClearBuffer();

    BackupScreenInfo();
    TaskDisplayShadows();
    RestoreScreenInfo();

    SetLighting(DefaultPlayerLight); // Reset lighting

    gjSetRenderMode(GJD_DRAW_SOLID);
    TaskDisplayDisplayer(btp[1]);

    if (!chs_performance)
        RFMOD_DrawBuffer();

    gjSetRenderMode(GJD_DRAW_SOLID | GJD_DRAW_TRANS);

    if (!no_draw)
    {
        TaskDisplayDisplayer(btp[2]);
        TaskDisplayDisplayer(btp[3]);
        TaskDisplayDisplayer(btp[4]);
        TaskDisplayDisplayer(btp[5]);

        RFMOD_DrawBuffer();
    }

    /** Draw Sorted displayer **/
    gjSetRenderMode(GJD_DRAW_TRANS);
    
    TaskDisplayDispSort(btp[0]);
    TaskDisplayDispSort_NoSort(btp[1]);

    if (!chs_performance)
        RFMOD_DrawBuffer();

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

        RFMOD_DrawBuffer();
    }
    else
    {
        if (!no_draw)
        {
            TaskDisplayDispSort(btp[2]);
            TaskDisplayDispSort(btp[3]);
            TaskDisplayDispSort(btp[4]);
            TaskDisplayDispSort(btp[5]);
            RFMOD_DrawBuffer();
        }
    }

    /** Draw Delayed displayer **/
    TaskDisplayDispDelayed(btp[0]);
    TaskDisplayDispDelayed(btp[1]);

    if (!chs_performance)
        RFMOD_DrawBuffer();

    if (!no_draw)
    {
        TaskDisplayDispDelayed(btp[2]);
        TaskDisplayDispDelayed(btp[3]);
        TaskDisplayDispDelayed(btp[4]);
        TaskDisplayDispDelayed(btp[5]);

        if (!chs_performance)
            RFMOD_DrawBuffer();
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

__declspec(naked)
static void
__TaskDisplayAll()
{
    __asm
    {
        push [esp+0]
        call TaskDisplayAll
        add esp, 4
        retn
    }
}

void
RFG_TaskDisplayInit()
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

    /** Avoid crash that only 
        happens in debug mode **/
#ifndef NDEBUG
    KillCall(0x0068B3B9);
#endif
}
