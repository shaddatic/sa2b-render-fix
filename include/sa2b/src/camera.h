/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/camera.h'
*
*   ~~ Under Construction ~~
*   Contains structs and data related to the camera
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#pragma once

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Defines             */
/************************/
#define CurrentCameraWork cameraControlWorkList[cameraControlWorkIndex] // Called camera_twp in symbols

/************************/
/*  Structures          */
/************************/
typedef struct _camcontwork
{
	NJS_POINT3 campos;
	Angle ang[3];
	NJS_POINT3 relpos; // pos Relative to target
	NJS_POINT3 tgtpos;
	NJS_POINT3 spd;
	float32 tgtdist;
	NJS_POINT3 prevcampos; // pos again
	Angle ang_spd[3];
}
camcontwork;

/************************/
/*  Data                */
/************************/
DataRef(int, cameraControlWorkIndex, 0x01DD92A0);
DataAry(camcontwork*, cameraControlWorkList, 0x01DD92B0, [2]);
