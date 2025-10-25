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
#include <rf_system.h>          /* aspect ratio mode                                */

/****** Self ************************************************************************/
#include <rf_module/rfm_event/ev_renderer/evr_internal.h> /* parent & siblings      */

/************************/
/*  Game Defs           */
/************************/
/****** Flag ************************************************************************/
#define DisableCutsceneRendering                DATA_REF(int, 0x01AEDE28)

/****** Clip ************************************************************************/
#define NearClip                                DATA_REF(f32, 0x025EFF44)

/************************/
/*  Source              */
/************************/
/****** Meta ************************************************************************/
static bool
UseLagEmu(void)
{
    if ( EventNum == 2 && EventSceneNum == 15 && SceneData->nbFrame == 2193 )
    {
        return true;
    }

    return false;
}

static const Sint16 Ev43List[] =
{
     21,  24,
    100, 101, 126,
    205, 206, 211,
    360, 361
};

static bool
UsePillarBox(void)
{
    if ( GetDisplayRatio() <= 1.f )
    {
        return false;
    }

    // always force 4:3 for 211
    if ( EventNum == 211 )
    {
        return true;
    }

    switch ( EventEnforce43 )
    {
        case EV_43MD_ALWAYS:
        {
            return true;
        }
        case EV_43MD_NOINTRO: default:
        {
            return EventNum != 350;
        }
        case EV_43MD_SPECIFIC:
        {
            const int evnum = EventNum;

            for ( int i = 0; i < ARYLEN(Ev43List); ++i )
            {
                if ( evnum == Ev43List[i] ) return true;
            }

            return false;
        }
        case EV_43MD_NEVER:
        {
            return false;
        }
    }

    return false; // unreachable
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

    const int old_rmode = _gj_render_mode_;

    {
        _gj_render_mode_ = GJD_DRAW_TRANS;

        rjCnkSetControl( RJD_CNK_CTRL_MASK_DRAW, RJD_CNK_CTRL_TRANSLUCENT );

        for (int i = 1; i <= 8; ++i)
        {
            EventSceneDraw(EVENT_BASE_SCENE, i);
            EventSceneDraw(EventSceneNum   , i);
        }

        rjCnkSetControl( 0, RJD_CNK_CTRL_MASK_DRAW );

        _gj_render_mode_ = old_rmode;
    }
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

    const int old_rmode = _gj_render_mode_;

    {
        _gj_render_mode_ = GJD_DRAW_TRANS;

        rjCnkSetControl( RJD_CNK_CTRL_MASK_DRAW, RJD_CNK_CTRL_TRANSLUCENT );

        for (int i = 9; i <= 16; ++i)
        {
            EventSceneDraw(EVENT_BASE_SCENE, i);
            EventSceneDraw(EventSceneNum   , i);
        }

        rjCnkSetControl( 0, RJD_CNK_CTRL_MASK_DRAW );

        _gj_render_mode_ = old_rmode;
    }

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

    /** Draw Event Scenes **/
    {
        const int old_rmode = _gj_render_mode_;

        /** Draw all opaque polygons **/

        _gj_render_mode_ = GJD_DRAW_SOLID;

        rjCnkSetControl( RJD_CNK_CTRL_MASK_DRAW, RJD_CNK_CTRL_OPAQUE );

        EventSceneDraw(EVENT_BASE_SCENE, EV_ALL_LAYERS);
        EventSceneDraw(EventSceneNum   , EV_ALL_LAYERS);

        /** Draw opaque equipment strips **/

        if ( EventEquipmentEnable )
        {
            EventEquipmentDraw();
        }

        /** Draw first transparent layer **/

        _gj_render_mode_ = GJD_DRAW_TRANS;

        rjCnkSetControl( RJD_CNK_CTRL_MASK_DRAW, RJD_CNK_CTRL_TRANSLUCENT );

        EventSceneDraw(EVENT_BASE_SCENE, 0);
        EventSceneDraw(EventSceneNum   , 0);

        /** Draw transparent equipment strips **/

        if ( EventEquipmentEnable )
        {
            EventEquipmentDraw();
        }

        rjCnkSetControl( 0, RJD_CNK_CTRL_MASK_DRAW );

        _gj_render_mode_ = old_rmode;
    }
}

static void
EventDestructor(task* tp)
{
    taskwk* restrict twp = tp->twp;

    NearClip = twp->scl.z; // reset the near plane to 1.f
}

static void
EventExecutor(task* tp)
{
    if ( DisableCutsceneRendering || DisableCutscene || CutsceneMode == EVENTMD_UNK_7 || CutsceneMode == EVENTMD_UNK_8 || CutsceneMode == EVENTMD_TIMECARD )
    {
        return;
    }

    if ( EventNum == 350 )
    {
        NearClip = 3.f; // set the near plane to 3 during Dreamcast intro, increasing Z accuracy
    }

    taskwk* restrict twp = tp->twp;

    // 4:3 bars
    if ( UsePillarBox() )
    {
        if ( EventNum != 211 )
        {
            RF_SysSetPillarColor( 0xFF000010, 0xFF000008 );
        }

        RF_SysEasySetPillarAspect( RF_SYS_PBA_43 );
    }

    // update last frame, may be changed inside of 'DebugExec'
    EventLastFrame = EventFrame;

    EV_DebugExec(tp);

    ___TODO("This should check a user setting in future");

    const f32 add_frame = UseLagEmu() ? ( EventSpeed * 0.5f ) : ( EventSpeed );

    if ( true ) // psudo-frameskip
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

    tp->twp->scl.z = NearClip;

    EventExecutor(tp);
}

/****** Extern **********************************************************************/
void
EVR_TaskInit(void)
{
    WriteJump(0x005FAA70, EventInitiator);
}
