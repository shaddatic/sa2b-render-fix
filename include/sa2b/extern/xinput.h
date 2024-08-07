/*
*   Sonic Adventure Mod Tools (SA2B) - '/extern/xinput.h'
*
*   Contains functions and pointers to the game's xinput imports.
*
*   Contributors:
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_EXTERN_XINPUT
#define H_EXTERN_XINPUT

EXTERN_START

/************************/
/*  Constants           */
/************************/
/****** Capabilities ****************************************************************/
#define XI_CAPABILITY_FEEDBACK      (0x01)  /* supports feedback other than rumble  */
#define XI_CAPABILITY_WIRELESS      (0x02)  /* device is in wireless mode           */
#define XI_CAPABILITY_VOICE         (0x04)  /* supports voice input                 */
#define XI_CAPABILITY_MODULE        (0x08)  /* supports plug-in modules             */
#define XI_CAPABILITY_NONAV         (0x10)  /* lacks Back, Start, and D-Pad         */

/****** Flags ***********************************************************************/
#define XI_FLAG_GAMEPAD             (0x00)  /* capability flag, gamepad             */

/****** Buttons *********************************************************************/
#define XI_GAMEPAD_DPAD_UP          (0x0001)
#define XI_GAMEPAD_DPAD_DOWN        (0x0002)
#define XI_GAMEPAD_DPAD_LEFT        (0x0004)
#define XI_GAMEPAD_DPAD_RIGHT       (0x0008)
#define XI_GAMEPAD_START            (0x0010)
#define XI_GAMEPAD_BACK             (0x0020)
#define XI_GAMEPAD_LS               (0x0040)
#define XI_GAMEPAD_RS               (0x0080)
#define XI_GAMEPAD_LB               (0x0100)
#define XI_GAMEPAD_RB               (0x0200)
#define XI_GAMEPAD_A                (0x1000)
#define XI_GAMEPAD_B                (0x2000)
#define XI_GAMEPAD_X                (0x4000)
#define XI_GAMEPAD_Y                (0x8000)

/************************/
/*  Structures          */
/************************/
typedef struct xinput_gamepad
{
    uint16_t                button; /* button flags                                 */
    uint8_t                     LT; /* left trigger                         (0~255) */
    uint8_t                     RT; /* right trigger                        (0~255) */
    int16_t                    LSX; /* left stick, x axis            (-32768~32767) */
    int16_t                    LSY; /* left stick, y axis            (-32768~32767) */
    int16_t                    RSX; /* right stick, x axis           (-32768~32767) */
    int16_t                    RSY; /* right stick, y axis           (-32768~32767) */
}
xinput_gamepad;

typedef struct xinput_state
{
    uint32_t              nbPacket; /* packet number                                */
    xinput_gamepad         Gamepad; /* gamepad structure                            */
}
xinput_state;

typedef struct xinput_vibration
{
    uint16_t                  spdL; /* left force feedback motor speed              */
    uint16_t                  spdR; /* right force feedback motor speed             */
}
xinput_vibration;

typedef struct xinput_capabilities
{
    uint8_t                   type; /* xinput type                                  */
    uint8_t                  stype; /* xinput sub type                              */
    uint16_t                  flag; /* xinput flag                                  */
    xinput_gamepad         Gamepad; /* gamepad structure                            */
    xinput_vibration     Vibration; /* vibration structure                          */
}
xinput_capabilities;

/************************/
/*  Functions           */
/************************/
uint32_t  ___XInputGetCapabilities(uint32_t idxUser, uint32_t flag, xinput_capabilities* pCapabilities);

uint32_t  ___XInputGetState(uint32_t idxUser, xinput_state* pState);
uint32_t  ___XInputSetState(uint32_t idxUser, xinput_vibration* pVibration);

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptr **/
#define ___XInputGetCapabilities_p   FUNC_PTR(uint32_t, __stdcall, (uint32_t, uint32_t, xinput_capabilities*), 0x007C0CCE)
#define ___XInputGetState_p          FUNC_PTR(uint32_t, __stdcall, (uint32_t, xinput_state*)                 , 0x007C0CD4)
#define ___XInputSetState_p          FUNC_PTR(uint32_t, __stdcall, (uint32_t, xinput_vibration*)             , 0x007C0CDA)

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_EXTERN_XINPUT*/
