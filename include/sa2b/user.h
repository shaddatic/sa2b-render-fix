/*
*   Sonic Adventure Mod Tools (SA2B) - '/user.h'
*
*   Contains functions for interacting with the user
*
*   Contributors:
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SAMT_USER_H_
#define _SAMT_USER_H_

/************************/
/*  Defines             */
/************************/
/** Input Settings **/
#define INPT_OK                     (0x00)
#define INPT_OK_CANCEL              (0x01)
#define INPT_ABORT_RETRY_IGNORE     (0x02)
#define INPT_YES_NO_CANCEL          (0x03)
#define INPT_YES_NO                 (0x04)
#define INPT_RETRY_CANCEL           (0x05)
#define INPT_CANCEL_TRY_CONT        (0x05)

/** Icon Settings **/
#define ICON_ERROR                  (0x10)
#define ICON_QUESTION               (0x20)
#define ICON_WARNING                (0x30)
#define ICON_INFO                   (0x40)
#define ICON_USER                   (0x80)

/** Returned User Selections **/
#define USER_OK                     (0x01)
#define USER_CANCEL                 (0x02)
#define USER_ABORT                  (0x03)
#define USER_RETRY                  (0x04)
#define USER_IGNORE                 (0x05)
#define USER_YES                    (0x06)
#define USER_NO                     (0x07)
#define USER_CLOSE                  (0x08)
#define USER_HELP                   (0x09)
#define USER_TRYAGAIN               (0x0A)
#define USER_CONTINUE               (0x0B)

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Pop-up a message box for the user **/
int     UserMessageBox(const utf8* header, const utf8* body, uint32_t input, uint32_t icon);

/** Pop-up common, basic message boxes for the user **/
int     UserWarningMessageBox(const utf8* header, const utf8* body);
int     UserErrorMessageBox(const utf8* header, const utf8* body);

EXTERN_END

#endif /* _SAMT_USER_H_ */
