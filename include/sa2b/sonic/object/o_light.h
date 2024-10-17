/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/object/o_light.h'
*
*   Contains functions for the Light Switch object.
* 
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_OBJECT_LIGHT_H_
#define _SA2B_OBJECT_LIGHT_H_

/************************/
/*  Abstract Types      */
/************************/
typedef struct task     task;

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Object function **/
void    ObjectLightSW(task* tp);

/** Task functions **/
void    ObjectLightSWExecutor(task* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/** Function ptr **/
#   define ObjectLightSW_p              FUNC_PTR(void, __cdecl, (task* tp), 0x006C9910)
#   define ObjectLightSWExecutor_p      FUNC_PTR(void, __cdecl, (task* tp), 0x006C9C90)

#endif /* SAMT_INCL_FUNCPTRS */

#endif /* _SA2B_OBJECT_LIGHT_H_ */
