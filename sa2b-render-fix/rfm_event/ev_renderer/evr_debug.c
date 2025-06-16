/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/modloader.h>     /* modloader                                        */
#include <samt/string.h>        /* strcopy                                          */

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
#include <rfm_event/ev_renderer/evr_internal.h> /* parent & siblings                */

/************************/
/*  Macros              */
/************************/
/****** Fast Square *****************************************************************/
#define SQR(x)              ((x) * (x))

/****** Get Input *******************************************************************/
#define GET_TRIGG(lr)       ((f32)(lr) * (1.f/255.f))
#define GET_ANLOG(xy)       ((f32)(xy) * (1.f/128.f)) // input controls uses 128 for both axes

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
GetAngleXYFromVec(const NJS_VECTOR* pVec, Angle* pAnsX, Angle* pAnsY)
{
    *pAnsY = njArcTan2(  pVec->x, pVec->z );
    *pAnsX = njArcTan2( -pVec->y, njSqrt( SQR(pVec->x) + SQR(pVec->z) ) );
}

/****** Debug Exec ******************************************************************/
void
EV_DebugCameraExec(task* tp)
{
    taskwk* restrict twp = tp->twp;

    const PDS_PERIPHERAL* restrict p_peri = per[0];

    if ( !(twp->flag & DBG_FLAG_CAMERAINIT) )
    {
        twp->pos.x = EventCamera.px;
        twp->pos.y = EventCamera.py;
        twp->pos.z = EventCamera.pz;

        GetAngleXYFromVec( (const NJS_VECTOR*)&EventCamera.vx, &twp->ang.x, &twp->ang.y );

        twp->flag |= DBG_FLAG_CAMERAINIT;
    }

    twp->ang.z = EventCamera.roll;

    twp->wtimer = (s16) EventCamera.ang;

    // ang
    {
        // change rotation rate depending on how 'zoomed' the camera is
        const f32 ang_spd = ((f32)twp->wtimer * ( 1.f / (f32)NJM_DEG_ANG(90.f) )) * 5.f;

        twp->ang.y -= (Angle)((f32)p_peri->x2 * ang_spd);

        const Angle ang_x = twp->ang.x + (Angle)((f32)p_peri->y2 * ang_spd);

        twp->ang.x  = CLAMP(ang_x, -NJM_DEG_ANG(90.f) + 0x10, +NJM_DEG_ANG(90.f) - 0x10);
    }

    // roll
    {
        const Angle roll_zl = (p_peri->on & BTN_RIGHT) ? 0x80 : 0x00;
        const Angle roll_zr = (p_peri->on & BTN_LEFT)  ? 0x80 : 0x00;

        twp->ang.z += (roll_zr - roll_zl);
    }

    // fov
    {
        // slow down change rate depending on how close the fov is to the extremes
        const f32 mul = 1.05f - njAbs( (f32)(twp->wtimer - NJM_DEG_ANG(90.f)) / (f32)NJM_DEG_ANG(90.f) );

        const Angle add = (Angle)((f32)0x80 * mul);

        const Angle dgt_u = (p_peri->on & BTN_UP  ) ? add : 0x00;
        const Angle dgt_d = (p_peri->on & BTN_DOWN) ? add : 0x00;

        const Angle new_fov = twp->wtimer + (Angle)(dgt_d - dgt_u);

        twp->wtimer = CLAMP(new_fov, 0x10, NJM_DEG_ANG(180.f) - 1);
    }

    // pos

    f32 x_adj = -GET_ANLOG(p_peri->x1);
    f32 y_adj = 0.f;
    f32 z_adj = 0.f;

    if ( (p_peri->on & (BTN_L|BTN_R)) == (BTN_L|BTN_R) )
    {
        y_adj = -GET_ANLOG(p_peri->y1);
    }
    else
    {
        z_adj = -GET_ANLOG(p_peri->y1);
    }

    if ( twp->flag & DBG_FLAG_CAMERAFAST )
    {
        x_adj *= 10.f;
        y_adj *= 10.f;
        z_adj *= 10.f;
    }

    // calc

    njPushMatrix( &_nj_unit_matrix_ );
    {
        njTranslateV(NULL, &twp->pos);

        njRotateY(NULL, twp->ang.y);
        njRotateX(NULL, twp->ang.x);

        njCalcPoint(NULL, &(NJS_POINT3){ x_adj, y_adj, z_adj }, &twp->pos);

        njCalcVector(NULL, &(NJS_VECTOR){ 0, 0, 1 }, (NJS_VECTOR*)&EventCamera.vx);
    }
    njPopMatrixEx();

    // set

    EventCamera.px = twp->pos.x;
    EventCamera.py = twp->pos.y;
    EventCamera.pz = twp->pos.z;

    EventCamera.roll = twp->ang.z;

    EventCamera.ang = twp->wtimer;
}

void
EV_DebugExec(task* tp)
{
    static char s_DebugTextBuffer[64];

    taskwk* restrict twp = tp->twp;

    if ( EventDebugFlag ) // debug controls
    {
        const PDS_PERIPHERAL* restrict p_peri = per[0];

        if ( p_peri->press & BTN_Y )
        {
            twp->flag ^= DBG_FLAG_SPEED;

            mtStrCopy(s_DebugTextBuffer, ( twp->flag & DBG_FLAG_SPEED ) ? "DEBUG SPEED  : ON" : "DEBUG SPEED  : OFF", STR_NOMAX);

            twp->btimer = 255;
        }

        if ( p_peri->press & BTN_X )
        {
            if ( twp->flag & DBG_FLAG_CAMERAFAST )
            {
                twp->flag &= ~(DBG_FLAG_CAMERA|DBG_FLAG_CAMERAINIT|DBG_FLAG_CAMERAFAST);

                mtStrCopy(s_DebugTextBuffer, "DEBUG CAMERA : OFF", STR_NOMAX);
            }
            else if ( twp->flag & DBG_FLAG_CAMERA )
            {
                twp->flag |= DBG_FLAG_CAMERAFAST;

                mtStrCopy(s_DebugTextBuffer, "DEBUG CAMERA : FAST", STR_NOMAX);
            }
            else
            {
                twp->flag |= DBG_FLAG_CAMERA;

                mtStrCopy(s_DebugTextBuffer, "DEBUG CAMERA : ON", STR_NOMAX);
            }

            twp->btimer = 255;
        }

        if ( p_peri->press & BTN_B )
        {
            DebugDrawPass = ++DebugDrawPass % NB_DBG_DRAWPASS;

            switch ( DebugDrawPass )
            {
                case DBG_DRAWPASS_ALL:
                {
                    mtStrCopy(s_DebugTextBuffer, "DEBUG DRAW   : ALL", STR_NOMAX);
                    break;
                }
                case DBG_DRAWPASS_OPAQUE:
                {
                    mtStrCopy(s_DebugTextBuffer, "DEBUG DRAW   : OPAQUE", STR_NOMAX);
                    break;
                }
                case DBG_DRAWPASS_TRANS:
                {
                    mtStrCopy(s_DebugTextBuffer, "DEBUG DRAW   : TRANS", STR_NOMAX);
                    break;
                }
                default: // transparent layers
                {
                    const s32 layer = (DebugDrawPass - DBG_DRAWPASS_LAYER_START);
            
                    mtStrFormat(s_DebugTextBuffer, ARYLEN(s_DebugTextBuffer), "DEBUG DRAW   : TRANS L%02i", layer);
                    break;
                }
            }

            twp->btimer = 255;
        }

        if ( p_peri->press & PDD_DGT_TD )
        {
            twp->flag ^= DBG_FLAG_PRINTINFO;

            mtStrCopy(s_DebugTextBuffer, ( twp->flag & DBG_FLAG_PRINTINFO ) ? "DEBUG INFO   : ON" : "DEBUG INFO   : OFF", STR_NOMAX);

            twp->btimer = 255;
        }

        if ( twp->flag & DBG_FLAG_SPEED )
        {
            const PDS_PERIPHERAL* restrict p_peri = per[0];

            const f32 lr = ( GET_TRIGG(p_peri->r) - GET_TRIGG(p_peri->l) ) * 3.f;

            EventSpeed = EVENT_SPEED_BASE * lr;

            if ( lr )
            {
                mtStrFormat(s_DebugTextBuffer, STR_NOMAX, "DEBUG SPEED  : %+.2f", lr);

                twp->btimer = 255;
            }

            if ( p_peri->press & BTN_ZL ) // last scene
            {
                const f32 sub_frame = ( EventSceneNum == 1 ) ?
                                      ( EventSceneFrame + (f32)EventData.pScenes[EventData.nbScene].nbFrame ) - 2.f :
                                      ( EventSceneFrame + (f32)EventData.pScenes[EventSceneNum - 1].nbFrame ) - 1.f;

                EventFrame    -= sub_frame;
                EventLastFrame = EventFrame + 0.001f; // make sure LastFrame != ThisFrame

                twp->scl.x = 0.f;

                mtStrCopy(s_DebugTextBuffer, "SCENE SELECT : PREV", STR_NOMAX);

                twp->btimer = 255;
            }
            else if ( p_peri->press & BTN_ZR ) // next scene
            {
                const f32 add_frame = ( (f32)EventData.pScenes[EventSceneNum].nbFrame - EventSceneFrame ) + 1.f;

                EventFrame    += add_frame;
                EventLastFrame = EventFrame + 0.001f; // make sure LastFrame != ThisFrame

                twp->scl.x = 0.f;

                mtStrCopy(s_DebugTextBuffer, "SCENE SELECT : NEXT", STR_NOMAX);

                twp->btimer = 255;
            }
        }
        else
        {
            EventSpeed = EVENT_SPEED_BASE;
        }

        if ( twp->btimer )
        {
            ML_SetDebugFontScale( 16.f );
            ML_SetDebugFontColor( (NJS_COLOR){ .argb = { 255, 255, 255, twp->btimer } }.color );

            ML_DisplayDebugString(NJM_LOCATION(1, 1), s_DebugTextBuffer);

            twp->btimer -= 5;
        }
    }
}

void
EV_DebugDisp(task* tp)
{
    taskwk* restrict twp = tp->twp;

    if ( twp->flag & DBG_FLAG_PRINTINFO )
    {
        ML_SetDebugFontScale( 16.f );
        ML_SetDebugFontColor( 0xFFFFFFFF );

        char buf[64];

        char* pc_evtype;

        if (EventNum < 100)
        {
            pc_evtype = "HERO";
        }
        else if (EventNum < 200)
        {
            pc_evtype = "DARK";
        }
        else if (EventNum < 300)
        {
            pc_evtype = "LAST";
        }
        else if (EventNum < 400)
        {
            pc_evtype = "INTRO";
        }
        else if (EventNum < 500)
        {
            pc_evtype = "FMV";
        }
        else
        {
            pc_evtype = "OTHER";
        }

        snprintf(buf, ARYLEN(buf), "EVENT        : E%04i (%s)", EventNum, pc_evtype);

        ML_DisplayDebugString(NJM_LOCATION(1, 3), buf);

        snprintf(buf, ARYLEN(buf), "EVENT SCENE  : %02i     /%02i", EventSceneNum, EventData.nbScene);

        ML_DisplayDebugString(NJM_LOCATION(1, 4), buf);

        snprintf(buf, ARYLEN(buf), "EVENT FRAME  : %06.1f /%i", EventFrame, EventData.pScenes[EVENT_BASE_SCENE].nbFrame);

        ML_DisplayDebugString(NJM_LOCATION(1, 5), buf);

        snprintf(buf, ARYLEN(buf), "SCENE FRAME  : %06.1f /%i", EventSceneFrame, EventData.pScenes[EventSceneNum].nbFrame);

        ML_DisplayDebugString(NJM_LOCATION(1, 6), buf);

        // camera

        snprintf(buf, ARYLEN(buf), "CAMERA POS   : %+.2f, %+.2f, %+.2f", EventCamera.px, EventCamera.py, EventCamera.pz);

        ML_DisplayDebugString(NJM_LOCATION(1, 8), buf);

        NJS_VECTOR vec = { EventCamera.vx, EventCamera.vy, EventCamera.vz };

        njUnitVector(&vec);

        snprintf(buf, ARYLEN(buf), "CAMERA VEC   : %+.2f, %+.2f, %+.2f", vec.x, vec.y, vec.z);

        vec.x = ( EventCamera.px + EventCamera.vx );
        vec.y = ( EventCamera.py + EventCamera.vy );
        vec.z = ( EventCamera.pz + EventCamera.vz );

        ML_DisplayDebugString(NJM_LOCATION(1, 9), buf);

        snprintf(buf, ARYLEN(buf), "CAMERA LOOKAT: %+.2f, %+.2f, %+.2f", vec.x, vec.y, vec.z);

        ML_DisplayDebugString(NJM_LOCATION(1, 10), buf);

        snprintf(buf, ARYLEN(buf), "CAMERA ROLL  : %+.2f", NJM_ANG_DEG(EventCamera.roll));

        ML_DisplayDebugString(NJM_LOCATION(1, 11), buf);

        snprintf(buf, ARYLEN(buf), "CAMERA FOV   : %+.2f", NJM_ANG_DEG(EventCamera.ang));

        ML_DisplayDebugString(NJM_LOCATION(1, 12), buf);

        // sprite alpha

        snprintf(buf, ARYLEN(buf), "ALPHA EFFECT : %+.2f", _nj_constant_material_.a);

        ML_DisplayDebugString(NJM_LOCATION(1, 14), buf);
    }
}
