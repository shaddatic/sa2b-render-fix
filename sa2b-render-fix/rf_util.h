/*
*   SA2 Render Fix - '/rf_util.h'
*
*   Description:
*       Common Render Fix utilities.
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_UTIL_H_
#define _RF_UTIL_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/memutil.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct textable     TEX_FILETABLE;

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Swap tex table entries **/
void    RF_SwapTexFileTableIndex( TEX_FILETABLE* pTexTable, int idx1, int idx2 );

EXTERN_END

/************************/
/*  Macro               */
/************************/
/*
*   Display Order Fixes
*/
#define DISP        0x14
#define DISP_DELY   0x1C
#define DISP_SORT   0x20
#define DISP_LATE   0x24
#define DISP_LAST   0x28
#define DISP_SHAD   0x2C

/** Switch a displayer to a different level,
    use this on 'mov dword ptr' operations **/
#define SwitchDisplayer(addr, disp)                     WriteData(addr + 2, disp, uint8_t)

/*
*   Hook 'mov dword ptr'
*/
/** Replace a 'mov dword ptr' with a call to a function **/
#define WriteCallToMovDwordPtr(addr, func)              WriteNoOP((addr), (addr) + 7); WriteCall((addr), (func))

/*
*   Replace float pointer
*/
/** Replace float used in many 'real' instruction **/
#define ReplaceFloat(addr, pflt)                        WritePointer(addr + 2, pflt)

/*
*   Func Macros
*/
#define SwapTexFileTableIndex(_textable, _idx1, _idx2)  RF_SwapTexFileTableIndex((TEX_FILETABLE*)(_textable), (_idx1), (_idx2))

#endif/*_RF_UTIL_H_*/
