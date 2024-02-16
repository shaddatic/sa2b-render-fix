/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_behavior/albhv_life.h'
*
*   Contains functions related to the Chao life behaviors, and Mayu task functions.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_ALBVH_LIFE_H_
#define _SA2B_CHAO_ALBVH_LIFE_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/src/chao/al_behavior.h>

/************************/
/*  Functions           */
/************************/
EXTERN_START
int32_t  ALBHV_Mayu(TASK* tp);
int32_t  ALBHV_Dead(TASK* tp);

/*
*   Mayu Functions
*/
void    CreateMayu(TASK* tp, char kind);

void    MayuDisplayer(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define ALBHV_Mayu_p        BhvFuncPtr(0x00568D30)
#define ALBHV_Dead_p        BhvFuncPtr(0x00568F60)

#define MayuDisplayer_p     FuncPtr(void, __cdecl, (TASK*), 0x568A70)

/** User-Function ptrs **/
EXTERN const void* const CreateMayu_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_ALBVH_LIFE_H_ */
