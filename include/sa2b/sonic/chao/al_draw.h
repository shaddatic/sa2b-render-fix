/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_draw.h'
*
*   Description:
*       Contains functions and data related to Chao drawing.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
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
typedef struct task         task;
typedef struct al_object    AL_OBJECT;

/************************/
/*  Data                */
/************************/
/** Refers to Chao tree nodes - called 'tree_count' in symbols **/
#define tree_count_draw         DATA_REF(int16_t     , 0x01A259D8)

/** Pointer to Chao shadow task **/
#define ShadowTexTp             DATA_REF(task*      , 0x01A5D144)

#define texlist_al_mm_kage      DATA_ARY(NJS_TEXLIST, 0x01349ED4, [1])

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Chao Draw **/
void    AL_Draw(task* tp);
void    AL_DrawSub(task* tp, AL_OBJECT* pObject);

/*
*   Chao Shadow Engine 
*/
void    AL_CreateShadowTex(void);
void    AL_EntryShadowTex(NJS_POINT3* pos, float scl);

/** Task functions **/
void    AL_ExecShadowTex(task* tp);
void    AL_DisplayShadowTex(task* tp);
void    AL_DestructShadowTex(task* tp);

/** Internal functions **/
void    AL_AllocateShadowTex(void);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define AL_Draw_p                    FUNC_PTR(void, __cdecl, (task*)            , 0x00540B60)
#   define AL_DrawSub_p                 FUNC_PTR(void, __cdecl, (task*, AL_OBJECT*), 0x0053FCF0)
#   define AL_CreateShadowTex_p         FUNC_PTR(void, __cdecl, (void)             , 0x00540F70)
#   define AL_ExecShadowTex_p           FUNC_PTR(void, __cdecl, (task*)            , 0x005412E0)
#   define AL_DisplayShadowTex_p        FUNC_PTR(void, __cdecl, (task*)            , 0x00541370)
#   define AL_DestructShadowTex_p       FUNC_PTR(void, __cdecl, (task*)            , 0x00541250)
#   define AL_AllocateShadowTex_p       FUNC_PTR(void, __cdecl, (void)             , 0x00541020)

/** User-Function ptrs **/
#   define AL_EntryShadowTex_p          ((void*)0x00540FD0);

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_DRAW_H_*/
