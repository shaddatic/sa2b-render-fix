/*
*   Sonic Adventure Mod Tools (SA2B) - '/soc/input.h'
*
*   Description:
*       SoC's Input classes.
*
*   Contributors:
*     - SEGA of China
*     - kellnc
*     - MainMemory
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SOC_INPUT
#define H_SOC_INPUT



/************************/
/*  External Header     */
/************************/
#ifdef  __cplusplus
/****** Magic ***********************************************************************/
#include <sa2b/magic/input.h>

#endif/*__cplusplus*/

/************************/
/*  Constants           */
/************************/
/****** SoC Peripheral **************************************************************/
#define SOCBTN_DPAD_LEFT    (0x0000000000001)
#define SOCBTN_DPAD_RIGHT   (0x0000000000002)
#define SOCBTN_DPAD_DOWN    (0x0000000000004)
#define SOCBTN_DPAD_UP      (0x0000000000008)
#define SOCBTN_R            (0x0000000000020)
#define SOCBTN_L            (0x0000000000040)
#define SOCBTN_A            (0x0000000000100)
#define SOCBTN_B            (0x0000000000200)
#define SOCBTN_X            (0x0000000000400)
#define SOCBTN_Y            (0x0000000000800)
#define SOCBTN_START        (0x0000000001000)

/************************/
/*  Structures          */
/************************/
#ifdef  __cplusplus
struct SOCController
{
    enum ControllerButton : int32_t
    {
        BTN_START,
        BTN_UP,
        BTN_DOWN,
        BTN_LEFT,
        BTN_RIGHT,
        BTN_A,
        BTN_B,
        BTN_X,
        BTN_Y,
        BTN_LS,
        BTN_RS,
        AXIS_LX,
        AXIS_LY,
        AXIS_RX,
        AXIS_RY,
        AXIS_LR,
    };

    struct vftbl
    {
        void(__thiscall* Destructor)(SOCController* this_, char);
        void(__thiscall* Update    )(SOCController* this_);
        bool(__thiscall* IsPress   )(SOCController* this_, SOCController::ControllerButton);
        bool(__thiscall* IsDown    )(SOCController* this_, SOCController::ControllerButton);
        f64 (__thiscall* GetValue  )(SOCController* this_, SOCController::ControllerButton);
        bool(__thiscall* VibStart  )(SOCController* this_, int, int);
        bool(__thiscall* VibStop   )(SOCController* this_);
        bool(__thiscall* Vib       )(SOCController* this_, int, int, long double);
        bool(__thiscall* IsValid   )(SOCController* this_);
    }*vft;

    int field_4;
    Magic::INPUT::Input* m_pInput;
    int m_ControllerIndex;
    int field_10;
    int field_14;
    double m_VibStartTime;
    int field_20;
    int field_24;
    int m_VibStrength;
    int field_2C;
    int field_30;
};

struct SOCInput
{
    int player;

    int m_ActiveIndex;

    SOCController*       m_pController[8];
    Magic::INPUT::Input* m_pInput;

    int unk_0;
    int unk_1;
    int unk_2;

    SOCController::ControllerButton m_AdvanceKey;
};

#else

typedef struct SOCController    SOCController;
typedef struct SOCInput         SOCInput;

#endif/*__cplusplus*/

EXTERN_START

typedef struct 
{
    uint32_t capabilities;  /* capability flags                                     */
    uint32_t button;        /* button flags                                         */
    int32_t  x1;            /* left stick, X axis                      (-127<->127) */
    int32_t  y1;            /* left stick, Y axis                      (-127<->127) */
    int32_t  x2;            /* right stick, X axis                     (-127<->127) */
    int32_t  y2;            /* right stick, Y axis                     (-127<->127) */
    int32_t  l;             /* left trigger                               (0<->255) */
    int32_t  r;             /* right trigger                              (0<->255) */
}
SOC_PERIPHERAL;

/************************/
/*  Data                */
/************************/
/****** SoC Peripheral **************************************************************/
#define SocPeripheral               DATA_ARY(SOC_PERIPHERAL, 0x01A52C48, [4])
#define SocPeripheralLast           DATA_ARY(SOC_PERIPHERAL, 0x01A529E8, [4])

/************************/
/*  Functions           */
/************************/
/****** SoC Input *******************************************************************/
SOCInput* SOC_GetInput( void );

/****** SoC Controller **************************************************************/
SOCController*  SOC_GetController( SOCInput* pInput, int pno );

/****** SoC Peripheral **************************************************************/
int         SOC_UpdatePeripheral( void );

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/****** Function Pointer ************************************************************/
#define SOC_GetInput_p              FUNC_PTR(SOCInput*     , __cdecl  , (void)          , 0x00402170)
#define SOC_GetController_p         FUNC_PTR(SOCController*, __stdcall, (SOCInput*, int), 0x004256A0)
#define SOC_UpdatePeripheral_p      FUNC_PTR(int           , __cdecl  , (void)          , 0x00425700)

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SOC_INPUT*/
