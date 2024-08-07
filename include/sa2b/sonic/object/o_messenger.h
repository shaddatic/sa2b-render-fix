/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/object/o_messenger.h'
*
*   Contains functions for Omochao.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_OBJECT_MSGER_H_
#define _SA2B_OBJECT_MSGER_H_

/************************/
/*  Abstract Types      */
/************************/
typedef struct task     TASK;

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Load Omochao dialog file **/
int32_t  LoadMessengerFile(const char* f);
int32_t  FreeMessengerFile(void);

/** Task functions **/
void    ObjectMessengerCreate(TASK* tp);
void    ObjectMessengerExec(TASK* tp);
void    ObjectMessengerDestructor(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/** Function ptr **/
#   define ObjectMessengerCreate_p          FUNC_PTR(void, __cdecl, (TASK*), 0x6C0780)
#   define ObjectMessengerExec_p            FUNC_PTR(void, __cdecl, (TASK*), 0x006BE2E0)
#   define ObjectMessengerDestructor_p      FUNC_PTR(void, __cdecl, (TASK*), 0x006C0970)
#   define FreeMessengerFile_p              FUNC_PTR(int32_t, __cdecl, (), 0x006BD5D0)

/** User-Function ptr **/
#   define LoadMessengerFile_p              ((void*)0x006BD650);

#endif /* SAMT_INCL_FUNCPTRS */

#endif /* _SA2B_OBJ_MSGER_H_ */
