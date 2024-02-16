/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_palette.h'
*
*   Contains functions related to the Chao palette system.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_PALETTE_H_
#define _SA2B_CHAO_PALETTE_H_

/************************/
/*  Abstract Types      */
/************************/
typedef struct task     TASK;

/************************/
/*  Functions           */
/************************/
EXTERN_START
void  AL_PaletteInit(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define AL_PaletteInit_p        FuncPtr(void, __cdecl, (TASK*), 0x00534DE0)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_PALETTE_H_ */
