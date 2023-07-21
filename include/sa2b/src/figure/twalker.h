/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/figure/twalker.h'
*
*   ~~ Under Construction ~~
*   Contains functions, structs, and data for the Tornado
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
#include <sa2b/src/figure/ewalker.h>

/************************/
/*  Data                */
/************************/
DataRef(NJS_MATRIX, mtx_TornadoBazooka, 0x01A52030);
DataRef(NJS_MATRIX, mtx_TornadoBoosterL, 0x01A51EDC);
DataRef(NJS_MATRIX, mtx_TornadoBoosterR, 0x01A51E4C);

/************************/
/*  Function Pointers   */
/************************/
FuncPtr(void, __cdecl, TornadoMotionCallBack, (NJS_CNK_OBJECT*), 0x00747940);