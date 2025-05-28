/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* writejump                                        */
#include <samt/funchook.h>      /* funchook                                         */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** Game ************************************************************************/
#include <samt/sonic/task.h>    /* task                                             */
#include <samt/sonic/njctrl.h>  /* ninja control                                    */
#include <samt/sonic/display.h> /* screen display                                   */
#include <samt/sonic/input.h>   /* player input                                     */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_eventinfo.h>       /* event data                                       */
#include <rf_renderstate.h>     /* render state                                     */
#include <rf_njcnk.h>           /* emulated njcnk draw functions                    */

/****** Std *************************************************************************/
#include <stdio.h>              /* snprintf                                         */

/****** Self ************************************************************************/
#include <rfm_event/ev_internal.h> /* parent & siblings                             */

/************************/
/*  Game Defs           */
/************************/
/****** Flag ************************************************************************/
#define DisableCutsceneRendering                DATA_REF(int, 0x01AEDE28)

/****** Clip ************************************************************************/
#define NearClip                                DATA_REF(f32, 0x025EFF44)

/************************/
/*  Data                */
/************************/
/****** Debug: Draw Pass ************************************************************/
s32 DebugDrawPass;

___TODO("Replace this with the actual function call when it's ready");

EXTERN s32 AspectRatioMode;

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
EV_SceneExec(void)
{
    const f32 ev_frame = EventFrame;

    f32 ev_frame_sub = 0.f;

    int ix_scene = 1;

    if ( ev_frame > 0.f ) // calculate scene index and frame
    {
        EVENT_SCENE* p_scene = &SceneData[1];

        const int nb_scene = EventData.nbScene;

        for ( ; ix_scene < nb_scene; ++ix_scene, ++p_scene )
        {
            const f32 new_sub = (f32)p_scene->nbFrame + ev_frame_sub;

            if ( new_sub - 1.0f >= EventFrame )
            {
                break;
            }

            ev_frame_sub = new_sub;
        }

        EventSceneNum = ix_scene;
    }

    const f32 new_frame = ev_frame - ev_frame_sub;

    if ( new_frame < 0.f )
    {
        EventSceneFrame = 0.f;
    }
    else
    {
        EventSceneFrame = new_frame;
    }

    /** Execute Big **/

    int ix_big_scene;

    if ( EvBigLastScene == ix_scene ) // ie, we've not switched scenes
    {
        ix_big_scene = EventBigScene;
    }
    else // new scene, reset
    {
        ix_big_scene = 0;

        EventBigFrame = 0.f;
        EvBigActive = 0;
        EventBigScene = 0;
    }

    EvBigLastScene = ix_scene;

    if ( EvBigActive )
    {
        EventBigFrame += ( EventFrame - EventLastFrame );

        EVENT_BIG* p_big = SceneData[ix_scene].pBig;

        const f32 nb_mframe = (f32) p_big->motions[ix_big_scene].motion->nbFrame;

        if ( EventBigFrame >= nb_mframe )
        {
            EventBigFrame = 0.f;
            EvBigActive = 0;
            EventBigScene = ix_big_scene + 1;

            if ( p_big->nbScene <= EventBigScene )
            {
                EventBigScene = (p_big->Unknown != 0) - 1;
            }
        }
    }
}

static bool
UseLagEmu(void)
{
    if ( EventNum == 2 && EventSceneNum == 15 && SceneData->nbFrame == 2193 )
    {
        return true;
    }

    return false;
}

bool
EV_AllowsWideAspect(void)
{
    return EventNum == 350;
}

static f32
GetEventFrameStep(void)
{
    const int vsync = EventEffData.sound[0].VsyncWaitCount;

    return (vsync == 0) ? 0.5f : 0.5f * (f32)vsync;
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
    if ( DisableCutsceneRendering || DisableCutscene || CutsceneMode == 7 || CutsceneMode == 8 || CutsceneMode == EVENTMD_TIMECARD )
    {
        return;
    }

    if ( EventNum == 350 )
    {
        NearClip = 3.f; // set the near plane to 3 during Dreamcast intro, increasing Z accuracy
    }

    taskwk* restrict twp = tp->twp;

    // 4:3 bars
    {
        if ( EV_Get43Mode() == EV_43MD_ALWAYS && !EV_AllowsWideAspect() && GetDisplayRatio() > 1.f )
        {
            AspectRatioMode = 1;
        }
    }

    // update last frame, may be changed inside of 'DebugExec'
    EventLastFrame = EventFrame;

    EV_DebugExec(tp);

    ___TODO("This should actually do something");

    if ( true ) // frameskip
    {
        twp->scl.x += UseLagEmu() ? ( EventSpeed * 0.5f ) : ( EventSpeed );

        const f32 fstep = GetEventFrameStep();

        if ( ABS(twp->scl.x) >= fstep )
        {
            const f32 add_frame = ( twp->scl.x - fmodf(twp->scl.x, fstep) );

            EventFrame += add_frame;
            twp->scl.x -= add_frame;
        }
    }
    else
    {
        EventFrame += UseLagEmu() ? ( EventSpeed * 0.5f ) : ( EventSpeed );
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

/****** Extern **********************************************************************/
void
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
