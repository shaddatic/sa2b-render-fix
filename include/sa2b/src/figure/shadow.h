/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/figure/shadow.h'
*
*   ~~ Under Construction ~~
*   Contains functions, structs, and data for Shadow
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
#include <sa2b/src/figure/sonic.h>

/************************/
/*  Data                */
/************************/
DataRef(NJS_MATRIX, mtx_ShadowFootR, 0x01A51894);

/************************/
/*  Function Pointers   */
/************************/
FuncPtr(void, __cdecl, ShadowMotionCallBack, (NJS_CNK_OBJECT*), 0x0071F5E0);