/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/figure/twalker.h'
*
*   ~~ Under Construction ~~
*   Contains functions, structs, and data for the Tornado
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_FIGURE_TWALKER_H_
#define _SA2B_FIGURE_TWALKER_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/sonic/figure/ewalker.h>

/************************/
/*  Data                */
/************************/
#define mtx_TornadoBazooka      DATA_REF(NJS_MATRIX, 0x01A52030)
#define mtx_TornadoBoosterL     DATA_REF(NJS_MATRIX, 0x01A51EDC)
#define mtx_TornadoBoosterR     DATA_REF(NJS_MATRIX, 0x01A51E4C)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    TornadoWalkerMotionCallBack(NJS_CNK_OBJECT* cnkobj);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define TornadoWalkerMotionCallBack_p     FUNC_PTR(void, __cdecl, (NJS_CNK_OBJECT*), 0x00747940)

#endif /* SAMT_INCL_FUNCPTRS */

#endif /* _SA2B_FIGURE_TWALKER_H_ */
