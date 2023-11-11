/*
*   Sonic Adventure Mod Tools (SA2B) - '/extern/xinput.h'
*
*   Contains functions and pointers to the game's xinput imports.
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _EXTERN_XINPUT_H_
#define _EXTERN_XINPUT_H_

/************************/
/*  Abstract Types      */
/************************/
typedef struct _XINPUT_CAPABILITIES XINPUT_CAPABILITIES;
typedef struct _XINPUT_STATE        XINPUT_STATE;
typedef struct _XINPUT_VIBRATION    XINPUT_VIBRATION;

/************************/
/*  Functions           */
/************************/
EXTERN_START
uint32  __XInputGetCapabilities(uint32 dwUserIndex, uint32 dwFlags, XINPUT_CAPABILITIES* pCapabilities);

uint32  __XInputGetState(uint32 dwUserIndex, XINPUT_STATE* pState);
uint32  __XInputSetState(uint32 dwUserIndex, XINPUT_VIBRATION* pVibration);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptr **/
#define __XInputGetCapabilities_p    FuncPtr(uint32, __stdcall, (uint32, uint32, XINPUT_CAPABILITIES*), 0x007C0CCE)
#define __XInputGetState_p           FuncPtr(uint32, __stdcall, (uint32, XINPUT_STATE*)               , 0x007C0CD4)
#define __XInputSetState_p           FuncPtr(uint32, __stdcall, (uint32, XINPUT_VIBRATION*)           , 0x007C0CDA)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _EXTERN_XINPUT_H_ */