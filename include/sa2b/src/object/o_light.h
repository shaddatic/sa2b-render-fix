/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/object/o_light.h'
*
*   Contains functions for the Light Switch object
* 
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#pragma once

/************************/
/*  Structures          */
/************************/
typedef struct // ANYWK
{
	
}
LIGHTSW_WORK;

/************************/
/*  Task Functions      */
/************************/
TaskFuncPtr(ObjectLightSW, 0x006C9910);

TaskFuncPtr(ObjectLightSWExecutor, 0x006C9C90);