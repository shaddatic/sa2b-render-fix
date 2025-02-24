/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/figure/shadow.h'
*
*   ~~ Under Construction ~~
*   Contains functions, structs, and data for Shadow
*/
#ifndef _SA2B_FIGURE_SHADOW_H_
#define _SA2B_FIGURE_SHADOW_H_

/************************/
/*  Includes            */
/************************/
#include <samt/sonic/figure/sonic.h>

/************************/
/*  Data                */
/************************/
#define mtx_ShadowFootR          DATA_REF(NJS_MATRIX, 0x01A51894)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    ShadowMotionCallBack(NJS_CNK_OBJECT* cnkobj);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define ShadowMotionCallBack_p       FUNC_PTR(void, __cdecl, (NJS_CNK_OBJECT*), 0x0071F5E0)

#endif /* SAMT_INCL_FUNCPTRS */

#endif /* _SA2B_FIGURE_SHADOW_H_ */
