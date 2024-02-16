/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/object/o_messenger.h'
*
*   Contains functions for Omochao.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
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
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptr **/
#define ObjectMessengerCreate_p         FuncPtr(void, __cdecl, (TASK*), 0x6C0780)
#define ObjectMessengerExec_p           FuncPtr(void, __cdecl, (TASK*), 0x006BE2E0)
#define ObjectMessengerDestructor_p     FuncPtr(void, __cdecl, (TASK*), 0x006C0970)
#define FreeMessengerFile_p             FuncPtr(int32_t, __cdecl, (), 0x006BD5D0)

/** User-Function ptr **/
EXTERN const void* const LoadMessengerFile_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_OBJ_MSGER_H_ */
