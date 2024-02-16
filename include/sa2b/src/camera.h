/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/camera.h'
*
*   ~~ Under Construction ~~
* 
*   Description:
*       Contains structs and data related to the camera.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CAMERA_H_
#define _SA2B_CAMERA_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Defines             */
/************************/
#define cameraCurrentWork           cameraControlWork[cameraControlWorkIndex]

/************************/
/*  Structures          */
/************************/
typedef struct _camcontwork
{
    NJS_POINT3 campos;
    Angle angx;
    Angle angy;
    Angle angz;
    NJS_POINT3 relpos; // pos Relative to target
    NJS_POINT3 tgtpos;
    NJS_POINT3 spd;
    float32_t tgtdist;
    NJS_POINT3 prevcampos; // pos again
    Angle angx_spd;
    Angle angy_spd;
    Angle angz_spd;
}
CAMERA_CONTROL_WORK;

/************************/
/*  Data                */
/************************/
#define cameraControlWorkIndex      DataRef(int32_t             , 0x01DD92A0)
#define cameraControlWork           DataAry(CAMERA_CONTROL_WORK*, 0x01DD92B0, [2])

#endif/*_SA2B_CAMERA_H_*/
