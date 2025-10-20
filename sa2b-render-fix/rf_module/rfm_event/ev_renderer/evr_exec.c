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
#include <rf_module/rfm_event/ev_internal.h> /* parent & siblings                   */

/************************/
/*  Data                */
/************************/
/****** Debug: Draw Pass ************************************************************/
s32 DebugDrawPass;

/************************/
/*  Source              */
/************************/
/****** Extern **********************************************************************/
void
EV_SceneExec(void)
{
    EventSceneNum = 1;

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

            if ( new_sub - 1.0f >= ev_frame )
            {
                break;
            }

            ev_frame_sub = new_sub;
        }

        EventSceneNum = ix_scene;
    }

    const f32 new_frame = ev_frame - ev_frame_sub;

    EventSceneFrame = MAX(new_frame, 0.f);

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

bool
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
