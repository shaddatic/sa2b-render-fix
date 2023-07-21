/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/figure/rouge.h'
*
*   ~~ Under Construction ~~
*   Contains functions, structs, and data for Rouge
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
#include <sa2b/src/figure/knuckles.h>

/************************/
/*  Data                */
/************************/
DataRef(NJS_MATRIX, mtx_RougeBootL, 0x01A51BBC);
DataRef(NJS_MATRIX, mtx_RougeBootR, 0x01A51C1C);

/************************/
/*  Function Pointers   */
/************************/
FuncPtr(void, __cdecl, RougeMotionCallBack, (NJS_CNK_OBJECT*), 0x007304D0);