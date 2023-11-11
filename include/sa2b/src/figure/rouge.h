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
#ifndef _SA2B_FIGURE_ROUGE_H_
#define _SA2B_FIGURE_ROUGE_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/src/figure/knuckles.h>

/************************/
/*  Data                */
/************************/
#define mtx_RougeBootL      DataRef(NJS_MATRIX, 0x01A51BBC)
#define mtx_RougeBootR      DataRef(NJS_MATRIX, 0x01A51C1C)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    RougeMotionCallBack(NJS_CNK_OBJECT* cnkobj);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define RougeMotionCallBack_p       FuncPtr(void, __cdecl, (NJS_CNK_OBJECT*), 0x007304D0)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_FIGURE_ROUGE_H_ */
