/*
*	Sonic Adventure Mod Tools - User Tools Header
*/

#ifndef _SAMT_USER_H_
#define _SAMT_USER_H_

/* Input Settings */
#define INPT_OK					(0x00)
#define INPT_OK_CANCEL			(0x01)
#define INPT_ABORT_RETRY_IGNORE (0x02)
#define INPT_YES_NO_CANCEL		(0x03)
#define INPT_YES_NO				(0x04)
#define INPT_RETRY_CANCEL		(0x05)
#define INPT_CANCEL_TRY_CONT	(0x05)

/* Icon Settings */
#define ICON_ERROR				(0x10)
#define ICON_QUESTION			(0x20)
#define ICON_WARNING			(0x30)
#define ICON_INFO				(0x40)
#define ICON_USER				(0x80)

/* User Selections */
#define USER_OK					(0x01)
#define USER_CANCEL				(0x02)
#define USER_ABORT				(0x03)
#define USER_RETRY				(0x04)
#define USER_IGNORE				(0x05)
#define USER_YES				(0x06)
#define USER_NO					(0x07)
#define USER_CLOSE				(0x08)
#define USER_HELP				(0x09)
#define USER_TRYAGAIN			(0x0A)
#define USER_CONTINUE			(0x0B)

/* Functions */
int		UserMessageBox(const char* header, const char* body, uint input, uint icon);

int		UserMessageBoxW(const wchar_t* header, const wchar_t* body, uint input, uint icon);

/* Quick Functions */
int		UserWarningMessageBox(const char* header, const char* body);
int		UserErrorMessageBox(const char* header, const char* body);

#endif /* _SAMT_USER_H_ */