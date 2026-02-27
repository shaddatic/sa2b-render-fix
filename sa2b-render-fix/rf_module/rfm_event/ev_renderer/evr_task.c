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
#include <samt/sonic/texture.h> /* texfreetexture                                   */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_renderstate.h>     /* render state                                     */
#include <rf_njcnk.h>           /* emulated njcnk draw functions                    */
#include <rf_ninja.h>           /* mod draw                                         */
#include <rf_util.h>            /* switch displayer                                 */
#include <rf_system.h>          /* aspect ratio mode                                */

/****** Self ************************************************************************/
#include <rf_module/rfm_event/ev_renderer/evr_internal.h> /* parent & siblings      */

/************************/
/*  Game Defs           */
/************************/
/****** Flag ************************************************************************/
#define DisableCutsceneRendering                DATA_REF(int, 0x01AEDE28)

/************************/
/*  Source              */
/************************/
/****** Meta ************************************************************************/
static bool
UseLagEmu(void)
{
    // final scene of Sonic meeting Shadow (hero)
    if ( EventNum == 2 && EventSceneNum == 15 && SceneData->nbFrame == 2193 )
    {
        return true;
    }

    // Knuckles stopping the chaos emeralds (spinny master emerald)
    if ( EventNum == 206 && EventSceneNum == 6 && SceneData->nbFrame == 2759 )
    {
        if ( EventSceneFrame > 75.f && EventSceneFrame < 130.f )
        {
            return true;
        }
    }

    return false;
}

static bool
UsePillarBox(void)
{
    if ( GetDisplayRatio() <= 1.f )
    {
        return false;
    }

    return EV_GetPillarbox(EventNum);
}


/****** Task ************************************************************************/
static bool
EventDispRetn(void)
{
    return (DisableCutscene || CutsceneMode == 7 || CutsceneMode == 8 || CutsceneMode == 2 || 0.f == EventFrame);
}

static void
EventDisplayerShadow(task* tp)
{
    if ( EventDispRetn() )
    {
        return;
    }

    /** Setup draw state **/
    njSetCamera( &EventCamera );

    /** Draw modifiers **/
    EventSceneModDraw(EVENT_BASE_SCENE);
    EventSceneModDraw(EventSceneNum);
}

static void
EventDisplayerSort(task* tp)
{
    if ( EventDispRetn() )
    {
        return;
    }

    /** Set constant material via screen sprites **/
    EV_SetConstMat();

    /** Draw **/
    njSetBackColor(0, 0, 0);
    njSetCamera( &EventCamera );

    njSetTexture(EventData.pTexlist);
    EventLightSet();

    njCnkSetMotionCallback(NULL);

    EV_SetDrawPass(EV_DRAWPASS_TRANS);

    for (int i = 1; i <= 8; ++i)
    {
        EventSceneDraw(EVENT_BASE_SCENE, i);
        EventSceneDraw(EventSceneNum   , i);
    }

    EV_SetDrawPass(EV_DRAWPASS_END);
}

static void
EventDisplayerDelayed(task* tp)
{
    if ( EventDispRetn() )
    {
        return;
    }

    /** Set constant material via screen sprites **/
    EV_SetConstMat();

    /** Draw **/
    njSetBackColor(0, 0, 0);
    njSetCamera( &EventCamera );

    njSetTexture(EventData.pTexlist);
    EventLightSet();

    EV_DebugDisp(tp);

    njCnkSetMotionCallback(NULL);

    /** Draw Event Scenes **/

    EventDrawReflections();
    EventDrawSprites();

    EV_SetDrawPass(EV_DRAWPASS_TRANS);

    for (int i = 9; i <= 16; ++i)
    {
        EventSceneDraw(EVENT_BASE_SCENE, i);
        EventSceneDraw(EventSceneNum   , i);
    }

    EV_SetDrawPass(EV_DRAWPASS_END);

    if (EventUseFlare)
    {
        EventDrawFlare(&EventFlarePos);
    }

    if (EventDebugInfo == 1)
    {
        EventDebug();
    }
    else if (EventDebugInfo == 2)
    {
        EventDebugNull();
    }

    EV_DrawScreenEffect();
}

static void
EventDisplayer(task* tp)
{
    if ( EventDispRetn() )
    {
        return;
    }

    /** Set constant material via screen sprites **/
    EV_SetConstMat();

    /** Draw **/
    njSetBackColor(0, 0, 0);
    njSetCamera( &EventCamera );

    njSetTexture(EventData.pTexlist);
    EventLightSet();

    EventResetEquipmentFlags();

    njCnkSetMotionCallback(NULL);

    /** Draw all opaque polygons **/

    EV_SetDrawPass(EV_DRAWPASS_OPAQUE);

    EventSceneDraw(EVENT_BASE_SCENE, EV_ALL_LAYERS);
    EventSceneDraw(EventSceneNum   , EV_ALL_LAYERS);

    /** Draw opaque equipment strips **/

    if ( EventEquipmentEnable )
    {
        EventEquipmentDraw();
    }

    /** Draw first transparent layer **/

    EV_SetDrawPass(EV_DRAWPASS_TRANS);

    EventSceneDraw(EVENT_BASE_SCENE, 0);
    EventSceneDraw(EventSceneNum   , 0);

    /** Draw transparent equipment strips **/

    if ( EventEquipmentEnable )
    {
        EventEquipmentDraw();
    }

    EV_SetDrawPass(EV_DRAWPASS_END);
}

static void
EventDestructor(task* tp)
{
    taskwk* restrict twp = tp->twp;

    if ( EvBigTexture )
    {
        texFreeTexlist(EvBigTexture);

        EvBigTexture = nullptr;
    }

    EVR_EndReplaceAttr();
}

static void
EventExecutor(task* tp)
{
    // 4:3 bars
    if ( UsePillarBox() )
    {
        ___NOTE("Make color customizeable for next update");
#if 0
        if ( EventNum < 400 && EventNum != 211 && CutsceneMode != 2 )
        {
            RF_SysSetPillarColor( 0xFF000010, 0xFF000008 );
        }
#endif

        RF_SysEasySetPillarAspect( RF_SYS_PBA_43 );
    }

    // core exec

    if ( DisableCutsceneRendering || DisableCutscene || CutsceneMode == EVENTMD_UNK_7 || CutsceneMode == EVENTMD_UNK_8 || CutsceneMode == EVENTMD_TIMECARD )
    {
        return;
    }

    taskwk* restrict twp = tp->twp;

    // update last frame, may be changed inside of 'DebugExec'
    EventLastFrame = EventFrame;

    EV_DebugExec(tp);

    const f32 add_frame = UseLagEmu() ? ( EventSpeed * 0.5f ) : ( EventSpeed );

    if ( EventVsyncMode != EV_VSYNCMD_60 || EventDebugFlag ) // psudo-frameskip
    {
        twp->scl.x += add_frame;

        if ( ABS(twp->scl.x) >= EVENT_FRAME_STEP )
        {
            const f32 add_step = ( twp->scl.x - fmodf(twp->scl.x, EVENT_FRAME_STEP) );

            EventFrame += add_step;
            twp->scl.x -= add_step;
        }
    }
    else
    {
        EventFrame += add_frame;
    }

    // check if this frame is different than the "current" frame
    if ( EventLastFrame != EventFrame )
    {
        const f32 scene_last_frame = (f32)(SceneData[EVENT_BASE_SCENE].nbFrame - 1);

        if ( twp->flag & DBG_FLAG_SPEED ) // if scrubbing enabled, loop event
        {
            if ( scene_last_frame > EventFrame )
            {
                if ( EventFrame < 1.f )
                {
                    const f32 sub_frame = (EventFrame < 0.f) ? -EventFrame : 0.f;

                    const f32 new_frame = (scene_last_frame - sub_frame);

                    EventFrame     = new_frame;
                    EventLastFrame = new_frame;
                }
            }
            else
            {
                EventFrame = 1.f;
            }
        }
        else // normal play (no looping)
        {
            if ( scene_last_frame > EventFrame )
            {
                if ( EventFrame < 1.f )
                {
                    EventFrame = 1.f;
                }
            }
            else
            {
                CutsceneMode = EVENTMD_END;

                EventFrame   = scene_last_frame;
                twp->scl.x   = 0.f;
            }
        }

        EV_SceneExec();

        EV_BlareExec(EVENT_BASE_SCENE);
        EV_BlareExec(EventSceneNum);

        EV_TexAnimExec();
    }

    EV_CameraExec(tp);
}

static void
EventInitiator(task* tp)
{
    tp->exec      = EventExecutor;
    tp->disp      = EventDisplayer;
    tp->dest      = EventDestructor;
    tp->disp_dely = EventDisplayerDelayed;
    tp->disp_sort = EventDisplayerSort;
    tp->disp_shad = EventDisplayerShadow;

    EventExecutor(tp);
}

/****** Extern **********************************************************************/
void
EVR_TaskInit(void)
{
    WriteJump(0x005FAA70, EventInitiator);
}
