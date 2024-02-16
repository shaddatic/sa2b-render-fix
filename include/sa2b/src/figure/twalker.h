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
#ifndef _SA2B_FIGURE_TWALKER_H_
#define _SA2B_FIGURE_TWALKER_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/src/figure/ewalker.h>

/************************/
/*  Data                */
/************************/
#define mtx_TornadoBazooka      DataRef(NJS_MATRIX, 0x01A52030)
#define mtx_TornadoBoosterL     DataRef(NJS_MATRIX, 0x01A51EDC)
#define mtx_TornadoBoosterR     DataRef(NJS_MATRIX, 0x01A51E4C)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    TornadoWalkerMotionCallBack(NJS_CNK_OBJECT* cnkobj);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define TornadoWalkerMotionCallBack_p     FuncPtr(void, __cdecl, (NJS_CNK_OBJECT*), 0x00747940)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_FIGURE_TWALKER_H_ */
