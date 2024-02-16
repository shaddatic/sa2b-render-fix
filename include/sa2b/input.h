/*
*   Sonic Adventure Mod Tools (SA2B) - '/input.h'
*
*   Contains functions and defines for recieving DirectX gamepad input,
*   keyboard input, and mouse input.
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SAMT_INPUT_H_
#define _SAMT_INPUT_H_

/************************/
/*  Gamepad Defs        */
/************************/
/** User def **/
#define USER_1          (0)
#define USER_2          (1)
#define USER_3          (2)
#define USER_4          (3)

/** Buttons **/
#define GAMEPAD_UP      (0x0001)
#define GAMEPAD_DOWN    (0x0002)
#define GAMEPAD_LEFT    (0x0004)
#define GAMEPAD_RIGHT   (0x0008)
#define GAMEPAD_START   (0x0010)
#define GAMEPAD_SELECT  (0x0020)
#define GAMEPAD_LS      (0x0040)
#define GAMEPAD_RS      (0x0080)
#define GAMEPAD_ZL      (0x0100) /* LB, L1 */
#define GAMEPAD_ZR      (0x0200) /* RB, R1 */
#define GAMEPAD_A       (0x1000)
#define GAMEPAD_B       (0x2000)
#define GAMEPAD_X       (0x4000)
#define GAMEPAD_Y       (0x8000)

/** Button & analog **/
#define GAMEPAD_L       (0x0400) /* LT, L2 */
#define GAMEPAD_R       (0x0800) /* RT, R2 */

/** Analog only **/
#define GAMEPAD_LX      (0x1000)
#define GAMEPAD_LY      (0x1800)
#define GAMEPAD_RX      (0x2000)
#define GAMEPAD_RY      (0x2800)

/** Misc **/
#define GAMEPAD_PAUSE   GAMEPAD_START
#define GAMEPAD_Z       GAMEPAD_ZR

/** Min/Max values **/
#define GAMEPAD_TRIGG_MIN   (0)
#define GAMEPAD_TRIGG_MAX   (255)

#define GAMEPAD_STICK_MIN   (-32'768)
#define GAMEPAD_STICK_MAX   ( 32'767)

/************************/
/*  Keyboard Defs       */
/************************/
/** Main keys **/
#define KEY_BACK            (0x08)
#define KEY_TAB             (0x09)
#define KEY_CLEAR           (0x0C)
#define KEY_RETURN          (0x0D)
#define KEY_PAUSE           (0x13)
#define KEY_ESCAPE          (0x1B)
#define KEY_SPACE           (0x20)
#define KEY_PAGE_UP         (0x21)
#define KEY_PAGE_DOWN       (0x22)
#define KEY_END             (0x23)
#define KEY_HOME            (0x24)
#define KEY_ARROW_LEFT      (0x25)
#define KEY_ARROW_UP        (0x26)
#define KEY_ARROW_RIGHT     (0x27)
#define KEY_ARROW_DOWN      (0x28)
#define KEY_PRINTSCREEN     (0x2C)
#define KEY_INSERT          (0x2D)
#define KEY_DELETE          (0x2E)
#define KEY_HELP            (0x2F)
#define KEY_SEMICOLON       (0xBA)
#define KEY_EQUALS          (0xBB)
#define KEY_COMMA           (0xBC)
#define KEY_SUBTRACT        (0xBD)
#define KEY_PERIOD          (0xBE)
#define KEY_FORWARDSLASH    (0xBF)
#define KEY_TILDE           (0xC0)
#define KEY_SQUAREBRACKET_L (0xDB)
#define KEY_BACKSLASH       (0xDC)
#define KEY_SQUAREBRACKET_R (0xDD)
#define KEY_QUOTE           (0xDE)
/** Numbers '0' through '9' **/
/** Letters 'A' through 'Z' **/

/** Super/Windows keys **/
#define KEY_SUPER_L         (0x5B)
#define KEY_SUPER_R         (0x5C)

/** Numpad keys (may require numlock) **/
#define KEY_NUM_0           (0x60)
#define KEY_NUM_1           (0x61)
#define KEY_NUM_2           (0x62)
#define KEY_NUM_3           (0x63)
#define KEY_NUM_4           (0x64)
#define KEY_NUM_5           (0x65)
#define KEY_NUM_6           (0x66)  
#define KEY_NUM_7           (0x67)
#define KEY_NUM_8           (0x68)
#define KEY_NUM_9           (0x69)
#define KEY_NUM_MULTIPLY    (0x6A)
#define KEY_NUM_PLUS        (0x6B)
#define KEY_NUM_SEPARATOR   (0x6C)
#define KEY_NUM_SUBTRACT    (0x6D)
#define KEY_NUM_DECIMAL     (0x6E)
#define KEY_NUM_DIVIDE      (0x6F)

/** Function keys **/
#define KEY_F1              (0x70)
#define KEY_F2              (0x71)
#define KEY_F3              (0x72)
#define KEY_F4              (0x73)
#define KEY_F5              (0x74)
#define KEY_F6              (0x75)
#define KEY_F7              (0x76)
#define KEY_F8              (0x77)
#define KEY_F9              (0x78)
#define KEY_F10             (0x79)
#define KEY_F11             (0x7A)
#define KEY_F12             (0x7B)
#define KEY_F13             (0x7C)
#define KEY_F14             (0x7D)
#define KEY_F15             (0x7E)
#define KEY_F16             (0x7F)
#define KEY_F17             (0x80)
#define KEY_F18             (0x81)
#define KEY_F19             (0x82)
#define KEY_F20             (0x83)
#define KEY_F21             (0x84)
#define KEY_F22             (0x85)
#define KEY_F23             (0x86)
#define KEY_F24             (0x87)

/** 'Lock' keys **/
#define KEY_CAPSLOCK        (0x14)
#define KEY_NUMLOCK         (0x90)
#define KEY_SCROLLLOCK      (0x91)

/** Modifier keys **/
#define KEY_SHIFT_L         (0xA0)
#define KEY_SHIFT_R         (0xA1)
#define KEY_CONTROL_L       (0xA2)
#define KEY_CONTROL_R       (0xA3)
#define KEY_ALT_L           (0xA4)
#define KEY_ALT_R           (0xA5)
/** L or R **/
#define KEY_SHIFT           (0x10)
#define KEY_CONTROL         (0x11)

/** Other **/
#define KEY_CTRLBREAK       (0x03) /* Ctrl+Pause/Break */

/** Mouse 'keys' **/
#define MOUSE_LCLICK        (0x01)
#define MOUSE_RCLICK        (0x02)
#define MOUSE_MIDDLE        (0x04)
#define MOUSE_SIDE_1        (0x05)
#define MOUSE_SIDE_2        (0x06)

/** No key **/
#define KEY_NONE            (0xFF)

/************************/
/*  Structures          */
/************************/
/** Mouse return struct **/
typedef struct
{
    int16_t x, y;
}
mouse_pos, mouse_vec;

/************************/
/*  Update Function     */
/************************/
EXTERN_START
/** Updates all input types, call inside 'OnInput()' **/
void    InputUpdate(void);

/************************/
/*  Gamepad Functions   */
/************************/
/** Whether the given gamepad is enabled & active **/
bool    InputGamepadActive(int user);

/** Enable/Disable gamepads. Gamepads 1 & 2 are automatically 
    enabled/disabled at startup depending on user settings &
    gamepad on-state, matching vanilla game behavior **/
void    InputGamepadEnable(int user);
void    InputGamepadDisable(int user);

/** Returns most recent button press **/
uint16_t  InputGamepadPoll(int user);

/* 
*   Held      : Always active
*   Press     : Only active for 1 tick
*
*   Both support combining buttons with OR
*/
bool    InputGamepadHeld(int user, uint16_t input);
bool    InputGamepadPress(int user, uint16_t input);

/** Returns analog value of given analog input **/
int     InputGamepadAnalog(int user, uint16_t input);

/** 'ticks' refers to the number of update calls **/
void    InputGamepadFeedback(int user, uint16_t ticks, uint16_t lr);
void    InputGamepadFeedbackLR(int user, uint16_t ticks, uint16_t l, uint16_t r);

/************************/
/*  Keyboard Functions  */
/************************/
/** Returns if a new key was pressed **/
bool    InputKeyboardEvent(void);

/** Returns most recent key press **/
uint8_t   InputKeyboardPoll(void);

/*
*   Held      : Always active
*   Press     : Only active for 1 tick
*
*   Uses KEY defines and MS-VK defines
*/
bool    InputKeyboardHeld(uint8_t key);
bool    InputKeyboardPress(uint8_t key);

/** Returns state of toggle keys **/
bool    InputKeyboardCapsLocked(void);
bool    InputKeyboardNumLocked(void);
bool    InputKeyboardScrollLocked(void);

/************************/
/*  Mouse Functions     */
/************************/
/** Whether the mouse is currently captured **/
bool    InputMouseCaptured(void);

/** Capture and free mouse. The mouse will be hidden when captured 
    and locked to the center of the game window. The mouse must be
    captured to read mouse movement **/
void    InputMouseCapture(void);
void    InputMouseFree(void);

/** Returns mouse position on the game window in pixels, starting 
    in the top-left. Returns 0, 0 if mouse is currently captured **/
mouse_pos   InputMouseCoords(void);
/** Returns mouse movement this frame in pixels **/
mouse_vec   InputMouseMovement(void);

EXTERN_END

#endif /* _SAMT_INPUT_H_ */
