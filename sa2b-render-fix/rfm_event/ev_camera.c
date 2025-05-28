/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* writejump                                        */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** Game ************************************************************************/
#include <samt/sonic/task.h>    /* task                                             */
#include <samt/sonic/camera.h>  /* camera                                           */
#include <samt/sonic/input.h>   /* player input                                     */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_eventinfo.h>       /* event data                                       */


/****** Self ************************************************************************/
#include <rfm_event/ev_internal.h>          /* parent & siblings                    */

/****** Camera Data *****************************************************************/
#define EvCamRangeOutPos                DATA_REF(NJS_POINT3, 0x01DB0FF0)
#define EvCameraContWk                  DATA_REF(camcontwk , 0x01A283A0)
#define EventCameraMotionNum            DATA_REF(int       , 0x01DB0EC4)

/************************/
/*  Macros              */
/************************/
/****** Fast Square *****************************************************************/
#define SQR(x)              ((x) * (x))

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
EventCamMotion(const NJS_CAMERA* pInCam, const NJS_MOTION* motion, float frame)
{
    NJS_CAMERA cam = *pInCam;

    NJS_CMOTION_DATA data;

    data.pos  = &cam.px;
    data.vect = &cam.vx;
    data.roll = &cam.roll;
    data.ang  = &cam.ang;

    njGetCameraMotion(pInCam, motion, &data, frame);

    cam.roll = -cam.roll;

    EventCamera = cam;
}

static void
GetInverseAngleXYFromVec(const NJS_VECTOR* pVec, Angle* pAnsX, Angle* pAnsY)
{
    *pAnsY = njArcTan2( -pVec->x, -pVec->z );
    *pAnsX = njArcTan2(  pVec->y, njSqrt( SQR(pVec->x) + SQR(pVec->z) ) );
}

/****** Extern **********************************************************************/
void
EV_CameraExec(task* tp)
{
    const taskwk* twp = tp->twp;

    if ( twp->flag & DBG_FLAG_CAMERA )
    {
        EV_DebugCameraExec(tp);
    }
    else // normal camera exec
    {
        const EVENT_SCENE* p_scene = &SceneData[EventSceneNum];

        if ( EventCameraMotionNum >= p_scene->nbCameraMotion )
        {
            EventCameraMotionNum = 0;
        }

        EventCamMotion( &EventBaseCamera, p_scene->pCameraMotions[EventCameraMotionNum], EventSceneFrame );
    }

    NJS_VECTOR v = { EventCamera.vx, EventCamera.vy, EventCamera.vz };

    njUnitVector(&v);

    EvCamRangeOutPos.x = ( v.x * 500.f ) + EventCamera.px;
    EvCamRangeOutPos.y = ( v.y * 500.f ) + EventCamera.py;
    EvCamRangeOutPos.z = ( v.z * 500.f ) + EventCamera.pz;

    EvCameraContWk.pos.x = EventCamera.px;
    EvCameraContWk.pos.y = EventCamera.py;
    EvCameraContWk.pos.z = EventCamera.pz;

    EvCameraContWk.dir.x = EventCamera.vx;
    EvCameraContWk.dir.y = EventCamera.vy;
    EvCameraContWk.dir.z = EventCamera.vz;

    GetInverseAngleXYFromVec(&EvCameraContWk.dir, &EvCameraContWk.ang.x, &EvCameraContWk.ang.y);
}
