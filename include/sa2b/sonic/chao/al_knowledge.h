/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_knowledge.h'
*
*   ~~ Under Construction ~~
*
*   Description:
*       
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_KNOWLEDGE_H_
#define _SA2B_CHAO_KNOWLEDGE_H_

/************************/
/*  Functions           */
/************************/
EXTERN_START
int32_t AL_KW_GetPlayerCharacterNum( void );

void    AL_KW_MeetPlayer( task* tp );

void    AL_KW_AddPlayerLike( task* pChaoTask, int32_t add );

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define AL_KW_GetPlayerCharacterNum_p        FUNC_PTR(int32_t, __cdecl, (void), 0x0053E0C0)

/** User-function ptrs **/
#   define AL_KW_MeetPlayer_p                   ((void*)0x0053E280)
#   define AL_KW_AddPlayerLike_p                ((void*)0x0053E120)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_KNOWLEDGE_H_*/
