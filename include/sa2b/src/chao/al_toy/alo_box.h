/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_toy/alo_box.h'
*
*   Contains functions and data related to the jack in the box garden object.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_TOY_BOX_H_
#define _SA2B_CHAO_TOY_BOX_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task     TASK;

/************************/
/*  Data                */
/************************/
#define ALO_BoxTaskPointer      DataRef(TASK*, 0x01AED32C)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    ALO_BoxCreate(NJS_POINT3* pPos);

/** Internal task functions **/
void    ALO_BoxExecutor(TASK* tp);
void    ALO_BoxDisplayer(TASK* tp);
void    ALO_BoxDestructor(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define ALO_BoxCreate_p         FuncPtr(void, __cdecl, (NJS_POINT3* pPos), 0x00580890)
#define ALO_BoxExecutor_p       FuncPtr(void, __cdecl, (TASK*)           , 0x005801C0)
#define ALO_BoxDisplayer_p      FuncPtr(void, __cdecl, (TASK*)           , 0x00580510)
#define ALO_BoxDestructor_p     FuncPtr(void, __cdecl, (TASK*)           , 0x00580870)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_TOY_BOX_H_ */
