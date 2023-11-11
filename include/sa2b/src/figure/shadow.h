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
#ifndef _SA2B_FIGURE_SHADOW_H_
#define _SA2B_FIGURE_SHADOW_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/src/figure/sonic.h>

/************************/
/*  Data                */
/************************/
#define mtx_ShadowFootR          DataRef(NJS_MATRIX, 0x01A51894)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    ShadowMotionCallBack(NJS_CNK_OBJECT* cnkobj);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define ShadowMotionCallBack_p      FuncPtr(void, __cdecl, (NJS_CNK_OBJECT*), 0x0071F5E0)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_FIGURE_SHADOW_H_ */
