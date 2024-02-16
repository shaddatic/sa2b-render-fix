/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_draw.h'
*
*   Contains functions and data related to Chao drawing.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_DRAW_H_
#define _SA2B_CHAO_DRAW_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task         TASK;
typedef struct al_object    AL_OBJECT;

/************************/
/*  Data                */
/************************/
/** Refers to Chao tree nodes - called 'tree_count' in symbols **/
#define tree_count_draw         DataRef(int16_t     , 0x01A259D8)

/** Pointer to Chao shadow task **/
#define ShadowTexTp             DataRef(TASK*      , 0x01A5D144)

#define texlist_al_mm_kage      DataAry(NJS_TEXLIST, 0x01349ED4, [1])

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Chao Draw **/
void    AL_Draw(TASK* tp);
void    AL_DrawSub(TASK* tp, AL_OBJECT* pObject);

/*
*   Chao Shadow Engine 
*/
void    AL_CreateShadowTex(void);
void    AL_EntryShadowTex(NJS_POINT3* pos, float scl);

/** Task functions **/
void    AL_ExecShadowTex(TASK* tp);
void    AL_DisplayShadowTex(TASK* tp);
void    AL_DestructShadowTex(TASK* tp);

/** Internal functions **/
void    AL_AllocateShadowTex(void);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define AL_Draw_p                   FuncPtr(void, __cdecl, (TASK*)            , 0x00540B60)
#define AL_DrawSub_p                FuncPtr(void, __cdecl, (TASK*, AL_OBJECT*), 0x0053FCF0)
#define AL_CreateShadowTex_p        FuncPtr(void, __cdecl, (void)             , 0x00540F70)
#define AL_ExecShadowTex_p          FuncPtr(void, __cdecl, (TASK*)            , 0x005412E0)
#define AL_DisplayShadowTex_p       FuncPtr(void, __cdecl, (TASK*)            , 0x00541370)
#define AL_DestructShadowTex_p      FuncPtr(void, __cdecl, (TASK*)            , 0x00541250)
#define AL_AllocateShadowTex_p      FuncPtr(void, __cdecl, (void)             , 0x00541020)

/** User-Function ptrs **/
EXTERN const void* const AL_EntryShadowTex_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_DRAW_H_ */
