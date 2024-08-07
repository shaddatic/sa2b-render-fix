/*
*   Sonic Adventure Mod Tools (SA2B) - '/magic/input.h'
*
*   Description:
*       Magic's INPUT namespace.
*
*   Contributors:
*     - Magic Developers
*     - kellnc
*     - MainMemory
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _MAGIC_INPUT_H_
#define _MAGIC_INPUT_H_

#ifdef  __cplusplus

/************************/
/*  Abstract Types      */
/************************/
typedef struct IDirectInput8A*          LPDIRECTINPUT8A;
typedef struct IDirectInputDeviceA*     LPDIRECTINPUTDEVICEA;

/************************/
/*  Abstract Types      */
/************************/
#ifndef _XINPUT_H_

typedef int32_t     XINPUT_GAMEPAD[3];
typedef int32_t     XINPUT_STATE[4];
typedef int32_t     XINPUT_VIBRATION[1];

#endif/*_XINPUT_H_*/

/************************/
/*  Input               */
/************************/
namespace Magic::INPUT
{
    enum KEYBTN_CODE : uint32_t // Basically stripped DIK enum
    {
        KEYBTN_NULL = 0xFFFFFFFF,
        KEYBTN_ESCAPE = 0x0,
        KEYBTN_1 = 0x1,
        KEYBTN_2 = 0x2,
        KEYBTN_3 = 0x3,
        KEYBTN_4 = 0x4,
        KEYBTN_5 = 0x5,
        KEYBTN_6 = 0x6,
        KEYBTN_7 = 0x7,
        KEYBTN_8 = 0x8,
        KEYBTN_9 = 0x9,
        KEYBTN_0 = 0xA,
        KEYBTN_MINUS = 0xB,
        KEYBTN_EQUALS = 0xC,
        KEYBTN_BACK = 0xD,
        KEYBTN_TAB = 0xE,
        KEYBTN_Q = 0xF,
        KEYBTN_W = 0x10,
        KEYBTN_E = 0x11,
        KEYBTN_R = 0x12,
        KEYBTN_T = 0x13,
        KEYBTN_Y = 0x14,
        KEYBTN_U = 0x15,
        KEYBTN_I = 0x16,
        KEYBTN_O = 0x17,
        KEYBTN_P = 0x18,
        KEYBTN_LBRACKET = 0x19,
        KEYBTN_RBRACKET = 0x1A,
        KEYBTN_RETURN = 0x1B,
        KEYBTN_LCONTROL = 0x1C,
        KEYBTN_A = 0x1D,
        KEYBTN_S = 0x1E,
        KEYBTN_D = 0x1F,
        KEYBTN_F = 0x20,
        KEYBTN_G = 0x21,
        KEYBTN_H = 0x22,
        KEYBTN_J = 0x23,
        KEYBTN_K = 0x24,
        KEYBTN_L = 0x25,
        KEYBTN_SEMICOLON = 0x26,
        KEYBTN_APOSTROPHE = 0x27,
        KEYBTN_GRAVE = 0x28,
        KEYBTN_LSHIFT = 0x29,
        KEYBTN_BACKSLASH = 0x2A,
        KEYBTN_Z = 0x2B,
        KEYBTN_X = 0x2C,
        KEYBTN_C = 0x2D,
        KEYBTN_V = 0x2E,
        KEYBTN_B = 0x2F,
        KEYBTN_N = 0x30,
        KEYBTN_M = 0x31,
        KEYBTN_COMMA = 0x32,
        KEYBTN_PERIOD = 0x33,
        KEYBTN_SLASH = 0x34,
        KEYBTN_RSHIFT = 0x35,
        KEYBTN_MULTIPLY = 0x36,
        KEYBTN_LMENU = 0x37,
        KEYBTN_SPACE = 0x38,
        KEYBTN_CAPITAL = 0x39,
        KEYBTN_F1 = 0x3A,
        KEYBTN_F2 = 0x3B,
        KEYBTN_F3 = 0x3C,
        KEYBTN_F4 = 0x3D,
        KEYBTN_F5 = 0x3E,
        KEYBTN_F6 = 0x3F,
        KEYBTN_F7 = 0x40,
        KEYBTN_F8 = 0x41,
        KEYBTN_F9 = 0x42,
        KEYBTN_F10 = 0x43,
        KEYBTN_NUMLOCK = 0x44,
        KEYBTN_SCROLL = 0x45,
        KEYBTN_NUMPAD7 = 0x46,
        KEYBTN_NUMPAD8 = 0x47,
        KEYBTN_NUMPAD9 = 0x48,
        KEYBTN_SUBTRACT = 0x49,
        KEYBTN_NUMPAD4 = 0x4A,
        KEYBTN_NUMPAD5 = 0x4B,
        KEYBTN_NUMPAD6 = 0x4C,
        KEYBTN_ADD = 0x4D,
        KEYBTN_NUMPAD1 = 0x4E,
        KEYBTN_NUMPAD2 = 0x4F,
        KEYBTN_NUMPAD3 = 0x50,
        KEYBTN_NUMPAD0 = 0x51,
        KEYBTN_DECIMAL = 0x52,
        KEYBTN_OEM_102 = 0x53,
        KEYBTN_F11 = 0x54,
        KEYBTN_F12 = 0x55,
        KEYBTN_F13 = 0x56,
        KEYBTN_F14 = 0x57,
        KEYBTN_F15 = 0x58,
        KEYBTN_KANA = 0x59,
        KEYBTN_ABNT_C1 = 0x5A,
        KEYBTN_CONVERT = 0x5B,
        KEYBTN_NOCONVERT = 0x5C,
        KEYBTN_YEN = 0x5D,
        KEYBTN_ABNT_C2 = 0x5E,
        KEYBTN_NUMPADEQUALS = 0x5F,
        KEYBTN_PREVTRACK = 0x60,
        KEYBTN_AT = 0x61,
        KEYBTN_COLON = 0x62,
        KEYBTN_UNDERLINE = 0x63,
        KEYBTN_KANJI = 0x64,
        KEYBTN_STOP = 0x65,
        KEYBTN_AX = 0x66,
        KEYBTN_UNLABELED = 0x67,
        KEYBTN_NEXTTRACK = 0x68,
        KEYBTN_NUMPADENTER = 0x69,
        KEYBTN_RCONTROL = 0x6A,
        KEYBTN_MUTE = 0x6B,
        KEYBTN_CALCULATOR = 0x6C,
        KEYBTN_PLAYPAUSE = 0x6D,
        KEYBTN_MEDIASTOP = 0x6E,
        KEYBTN_VOLUMEDOWN = 0x6F,
        KEYBTN_VOLUMEUP = 0x70,
        KEYBTN_WEBHOME = 0x71,
        KEYBTN_NUMPADCOMMA = 0x72,
        KEYBTN_DIVIDE = 0x73,
        KEYBTN_SYSRQ = 0x74,
        KEYBTN_RMENU = 0x75,
        KEYBTN_PAUSE = 0x76,
        KEYBTN_HOME = 0x77,
        KEYBTN_UP = 0x78,
        KEYBTN_PRIOR = 0x79,
        KEYBTN_LEFT = 0x7A,
        KEYBTN_RIGHT = 0x7B,
        KEYBTN_END = 0x7C,
        KEYBTN_DOWN = 0x7D,
        KEYBTN_NEXT = 0x7E,
        KEYBTN_INSERT = 0x7F,
        KEYBTN_DELETE = 0x80,
        KEYBTN_LWIN = 0x81,
        KEYBTN_RWIN = 0x82,
        KEYBTN_APPS = 0x83,
        KEYBTN_POWER = 0x84,
        KEYBTN_SLEEP = 0x85,
        KEYBTN_WAKE = 0x86,
        KEYBTN_WEBSEARCH = 0x87,
        KEYBTN_WEBFAVORITES = 0x88,
        KEYBTN_WEBREFRESH = 0x89,
        KEYBTN_WEBSTOP = 0x8A,
        KEYBTN_WEBFORWARD = 0x8B,
        KEYBTN_WEBBACK = 0x8C,
        KEYBTN_MYCOMPUTER = 0x8D,
        KEYBTN_MAIL = 0x8E,
        KEYBTN_MEDIASELECT = 0x8F,
        KEYBTN_MAX = 0x90,
    };

    enum JOYBTN_CODE : uint32_t
    {
        JOYBTN_NULL = 0xFFFFFFFF,
        JOYBTN_SINGLE_BEGIN = 0x0,
        JOYBTN_0 = 0x0,
        JOYBTN_A = 0x0,
        JOYBTN_CROSS = 0x0,
        JOYBTN_1 = 0x1,
        JOYBTN_B = 0x1,
        JOYBTN_CIRCLE = 0x1,
        JOYBTN_2 = 0x2,
        JOYBTN_X = 0x2,
        JOYBTN_SQUARE = 0x2,
        JOYBTN_3 = 0x3,
        JOYBTN_Y = 0x3,
        JOYBTN_TRIANGLE = 0x3,
        JOYBTN_4 = 0x4,
        JOYBTN_LSHOULDER1 = 0x4,
        JOYBTN_L1 = 0x4,
        JOYBTN_5 = 0x5,
        JOYBTN_RSHOULDER1 = 0x5,
        JOYBTN_R1 = 0x5,
        JOYBTN_6 = 0x6,
        JOYBTN_BACK = 0x6,
        JOYBTN_7 = 0x7,
        JOYBTN_START = 0x7,
        JOYBTN_8 = 0x8,
        JOYBTN_LTHUMB_PUSH = 0x8,
        JOYBTN_L3 = 0x8,
        JOYBTN_9 = 0x9,
        JOYBTN_RTHUMB_PUSH = 0x9,
        JOYBTN_R3 = 0x9,
        JOYBTN_10 = 0xA,
        JOYBTN_SELECT = 0xA,
        JOYBTN_11 = 0xB,
        JOYBTN_BIGBUTTON = 0xB,
        JOYBTN_12 = 0xC,
        JOYBTN_13 = 0xD,
        JOYBTN_14 = 0xE,
        JOYBTN_15 = 0xF,
        JOYBTN_16 = 0x10,
        JOYBTN_17 = 0x11,
        JOYBTN_18 = 0x12,
        JOYBTN_19 = 0x13,
        JOYBTN_20 = 0x14,
        JOYBTN_21 = 0x15,
        JOYBTN_22 = 0x16,
        JOYBTN_23 = 0x17,
        JOYBTN_24 = 0x18,
        JOYBTN_25 = 0x19,
        JOYBTN_26 = 0x1A,
        JOYBTN_27 = 0x1B,
        JOYBTN_28 = 0x1C,
        JOYBTN_29 = 0x1D,
        JOYBTN_30 = 0x1E,
        JOYBTN_31 = 0x1F,
        JOYBTN_UP = 0x20,
        JOYBTN_DOWN = 0x21,
        JOYBTN_LEFT = 0x22,
        JOYBTN_RIGHT = 0x23,
        JOYBTN_SINGLE_END = 0x24,
        JOYBTN_INTERZONE_BEGIN = 0x24,
        JOYBTN_LTRIGGER = 0x24,
        JOYBTN_L2 = 0x24,
        JOYBTN_RTRIGGER = 0x25,
        JOYBTN_R2 = 0x25,
        JOYBTN_LTHUMBX = 0x26,
        JOYBTN_LTHUMBY = 0x27,
        JOYBTN_RTHUMBX = 0x28,
        JOYBTN_RTHUMBY = 0x29,
        JOYBTN_SENSOR_X = 0x2A,
        JOYBTN_SENSOR_Y = 0x2B,
        JOYBTN_SENSOR_Z = 0x2C,
        JOYBTN_SENSOR_G = 0x2D,
        JOYBTN_INTERZONE_END = 0x2E,
        JOYBTN_POS_BEGIN = 0x2E,
        JOYBTN_LTHUMB_STICK = 0x2E,
        JOYBTN_RTHUMB_STICK = 0x2F,
        JOYBTN_POS_END = 0x30,
        JOYBTN_MAX = 0x30,
    };

    enum MOUSEBTN_CODE : uint32_t
    {
        MOUSEBTN_LB = 0x0,
        MOUSEBTN_RB = 0x1,
        MOUSEBTN_MB = 0x2,
    };

    struct Keystroke
    {
        KEYBTN_CODE m_KeyCode;
        int m_Flags;
        int unknown3;
    };

    struct IPoint
    {
        float x;
        float y;
    };

    struct Controller
    {
        struct vtbl
        {
            void(__thiscall* Destructor)(Controller* _this);
            bool(__thiscall* IsMouse)(Controller* _this);
            bool(__thiscall* IsKeyboard)(Controller* _this);
            bool(__thiscall* IsJoystick)(Controller* _this);
            bool(__thiscall* IsValid)(Controller* _this);
        }*__vftable;
    };

    struct Joystick /* : Controller */
    {
        struct vtbl
        {
            void(__thiscall* Destructor)(Joystick* _this);
            bool(__thiscall* IsMouse)(Joystick* _this);
            bool(__thiscall* IsKeyboard)(Joystick* _this);
            bool(__thiscall* IsJoystick)(Joystick* _this);
            bool(__thiscall* IsValid)(Joystick* _this);
            void(__thiscall* Initialize)(Joystick* _this);
            void(__thiscall* Finalize)(Joystick* _this);
            void(__thiscall* Update)(Joystick* _this);
            bool(__thiscall* IsPress)(Joystick* _this, JOYBTN_CODE);
            bool(__thiscall* IsRelease)(Joystick* _this, JOYBTN_CODE);
            bool(__thiscall* IsLast)(Joystick* _this, JOYBTN_CODE);
            bool(__thiscall* IsUp)(Joystick* _this, JOYBTN_CODE);
            bool(__thiscall* IsDown)(Joystick* _this, JOYBTN_CODE);
            bool(__thiscall* Unknown13)(Joystick* _this, int, int);
            float(__thiscall* GetValue)(Joystick* _this, JOYBTN_CODE);
            IPoint* (__thiscall* GetPos)(Joystick* _this, IPoint* result, JOYBTN_CODE);
            bool(__thiscall* VibStart)(Joystick* _this, int left, int right);
            bool(__thiscall* VibStop)(Joystick* _this);
            bool(__thiscall* Unknown18)(Joystick* _this, int, int);
            bool(__thiscall* Unknown19)(Joystick* _this);
        }*__vftable;

        int unknown;
        int m_ControllerIndex;
        char initialized;
        XINPUT_STATE is[2];
        int index_prevpool;
        int index_currentpool;
        XINPUT_VIBRATION vibration;
        char isVibrating;
    };

    struct Keyboard /* : Controller */
    {
        struct vtbl
        {
            void(__thiscall* Destructor)(Keyboard* _this);
            bool(__thiscall* IsMouse)(Keyboard* _this);
            bool(__thiscall* IsKeyboard)(Keyboard* _this);
            bool(__thiscall* IsJoystick)(Keyboard* _this);
            bool(__thiscall* IsValid)(Keyboard* _this);
            void(__thiscall* Initialize)(Keyboard* _this);
            void(__thiscall* Finalize)(Keyboard* _this);
            void(__thiscall* Update)(Keyboard* _this);
            bool(__thiscall* IsPress)(Keyboard* _this, KEYBTN_CODE);
            bool(__thiscall* IsRelease)(Keyboard* _this, KEYBTN_CODE);
            bool(__thiscall* IsLast)(Keyboard* _this, KEYBTN_CODE);
            bool(__thiscall* IsUp)(Keyboard* _this, KEYBTN_CODE);
            bool(__thiscall* IsDown)(Keyboard* _this, KEYBTN_CODE);
            bool(__thiscall* GetKeystroke)(Keyboard* _this, Keystroke*);
        }*__vftable;

        int unknown1;
        LPDIRECTINPUT8A api;
        int unknown3;
        LPDIRECTINPUTDEVICEA device;
        Keystroke ks[32];
        uint8_t a6[128];
        int ks_index;
        int ks_previndex;
        uint8_t current_keys[256];
        uint8_t last_keys[256];
        int index_prevpool;
        int index_currentpool;
        char initialized;
    };

    struct Mouse /* : Controller */
    {
        struct vtbl
        {
            void(__thiscall* Destructor)(Mouse* _this);
            bool(__thiscall* IsMouse)(Mouse* _this);
            bool(__thiscall* IsKeyboard)(Mouse* _this);
            bool(__thiscall* IsJoystick)(Mouse* _this);
            bool(__thiscall* IsValid)(Mouse* _this);
            void(__thiscall* Initialize)(Mouse* _this);
            void(__thiscall* Finalize)(Mouse* _this);
            void(__thiscall* Update)(Mouse* _this);
            bool(__thiscall* IsPress)(Mouse* _this, MOUSEBTN_CODE);
            bool(__thiscall* IsRelease)(Mouse* _this, MOUSEBTN_CODE);
            bool(__thiscall* IsLast)(Mouse* _this, MOUSEBTN_CODE);
            bool(__thiscall* IsUp)(Mouse* _this, MOUSEBTN_CODE);
            bool(__thiscall* IsDown)(Mouse* _this, MOUSEBTN_CODE);
            int(__thiscall* GetLX)(Mouse* _this);
            int(__thiscall* GetLY)(Mouse* _this);
            int(__thiscall* GetLZ)(Mouse* _this);
            void(__thiscall* GetPos)(Mouse* _this, int* x, int* y);
            IPoint* (__cdecl* GetNormalPos)(Mouse* _this, IPoint* result);

        }*__vftable;
    };

    struct InputImpl
    {
        struct vtbl
        {
            void(__thiscall* Destructor)(InputImpl* _this);
            void(__thiscall* Initialize)(InputImpl* _this);
            void(__thiscall* Finalize)(InputImpl* _this);
            void(__thiscall* Update)(InputImpl* _this);
            Mouse* (__thiscall* GetMouse)(InputImpl* _this, int);
            Keyboard* (__thiscall* GetKeyboard)(InputImpl* _this, int);
            Joystick* (__thiscall* GetJoystick)(InputImpl* _this, int);
            Controller* (__thiscall* GetController)(InputImpl* _this, int);
            void(__thiscall* WndProc)(InputImpl* _this, void*, unsigned int, unsigned int, int);
            int(__thiscall* GetMouseNum)(InputImpl* _this);
            int(__thiscall* GetKeyboardNum)(InputImpl* _this);
            int(__thiscall* GetJoystickNum)(InputImpl* _this);
            void(__thiscall* Unknown)(InputImpl* _this);
        }*__vftable;

        LPDIRECTINPUT8A dinput;
        int unknown2;
        int unknown3;
        int unknown4;
        Keyboard* keyboard;
        int unknown6[6 * 4];
    };

    struct Input
    {
        struct vftbl
        {
            void(__thiscall* Destructor)(Input* _this, char);
            void(__thiscall* Initialize)(Input* _this);
            void(__thiscall* Finalize)(Input* _this);
            void(__thiscall* Update)(Input* _this);
            Mouse* (__thiscall* GetMouse)(Input* _this, int);
            Keyboard* (__thiscall* GetKeyboard)(Input* _this, int);
            Joystick* (__thiscall* GetJoystick)(Input* _this, int);
            Controller* (__thiscall* GetController)(Input* _this, int);
            void(__thiscall* WndProc)(Input* _this, void*, unsigned int, unsigned int, int);
            int(__thiscall* GetMouseNum)(Input* _this);
            int(__thiscall* GetKeyboardNum)(Input* _this);
            int(__thiscall* GetJoystickNum)(Input* _this);
            int(__thiscall* IsInputImpl)(Input* _this);
        }*vft;
        InputImpl* m_pInputImpl;
    };
}

#endif/*__cplusplus*/

#endif/*_MAGIC_INPUT_H_*/
