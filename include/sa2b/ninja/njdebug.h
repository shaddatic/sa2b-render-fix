/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njdebug.h'
*
*   Contains macros and functions for debugging with Ninja
*   Many of these functions re-route to Mod Loader functions
*
*   Contributors:
*     - SEGA,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _NJDEBUG_H_
#define _NJDEBUG_H_

#include <sa2b/shinobi/sg_xpt.h>

#define NJM_GET_X(n)        ((Sint16)((n)>>16))
#define NJM_GET_Y(n)        ((Sint16)((n)&0x0000FFFF))
#define NJM_LOCATION(x,y)   ((x)<<16|(y))

/************************/
/*  Debug Font Function */
/************************/
void    njPrintSize(Uint16 size);
void    njPrintColor(Uint32 c);
void    njPrintC(Int loc, const char* s);
void    njPrintD(Int loc, Int val, Int digit);
void    njPrintB(Int loc, Uint32 val, Int digit);
void    njPrintH(Int loc, Uint32 val, Int digit);
void    njPrintF(Int loc, Float val, Int digit);
void    njPrint(Int loc, const char* fmt, ...);

#endif
