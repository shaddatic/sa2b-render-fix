/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_palette.h'
*
*   Description:
*       Contains functions related to the Chao palette system.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_PALETTE_H_
#define _SA2B_CHAO_PALETTE_H_

/************************/
/*  Abstract Types      */
/************************/
typedef struct task     task;

/************************/
/*  Functions           */
/************************/
EXTERN_START
void  AL_PaletteInit(task* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#define AL_PaletteInit_p        FUNC_PTR(void, __cdecl, (task*), 0x00534DE0)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_PALETTE_H_*/
