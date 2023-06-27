#pragma once

#define CurrentCameraWork cameraControlWorkList[cameraControlWorkIndex] // Called camera_twp in symbols

typedef struct _camcontwork
{
	NJS_POINT3 campos;
	Angle ang[3];
	NJS_POINT3 relpos; // pos Relative to target
	NJS_POINT3 tgtpos;
	NJS_POINT3 spd;
	float tgtdist;
	NJS_POINT3 prevcampos; // pos again
	Angle ang_spd[3];
}
camcontwork;

DataRef(int, cameraControlWorkIndex, 0x01DD92A0);
DataAry(camcontwork*, cameraControlWorkList, 0x01DD92B0, [2]);