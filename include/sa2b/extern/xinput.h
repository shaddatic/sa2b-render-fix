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
uint32_t  ___XInputGetCapabilities(uint32_t dwUserIndex, uint32_t dwFlags, XINPUT_CAPABILITIES* pCapabilities);

uint32_t  ___XInputGetState(uint32_t dwUserIndex, XINPUT_STATE* pState);
uint32_t  ___XInputSetState(uint32_t dwUserIndex, XINPUT_VIBRATION* pVibration);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptr **/
#define ___XInputGetCapabilities_p   FuncPtr(uint32_t, __stdcall, (uint32_t, uint32_t, XINPUT_CAPABILITIES*), 0x007C0CCE)
#define ___XInputGetState_p          FuncPtr(uint32_t, __stdcall, (uint32_t, XINPUT_STATE*)                 , 0x007C0CD4)
#define ___XInputSetState_p          FuncPtr(uint32_t, __stdcall, (uint32_t, XINPUT_VIBRATION*)             , 0x007C0CDA)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _EXTERN_XINPUT_H_ */
