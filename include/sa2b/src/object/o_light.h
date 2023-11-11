/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/object/o_light.h'
*
*   Contains functions for the Light Switch object.
* 
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_OBJECT_LIGHT_H_
#define _SA2B_OBJECT_LIGHT_H_

/************************/
/*  Abstract Types      */
/************************/
typedef struct task     TASK;

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Object function **/
void    ObjectLightSW(TASK* tp);

/** Task functions **/
void    ObjectLightSWExecutor(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptr **/
#define ObjectLightSW_p             FuncPtr(void, __cdecl, (TASK* tp), 0x006C9910)
#define ObjectLightSWExecutor_p     FuncPtr(void, __cdecl, (TASK* tp), 0x006C9C90)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_OBJECT_LIGHT_H_ */
