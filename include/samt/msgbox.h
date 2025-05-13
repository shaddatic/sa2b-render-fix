/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/msgbox.h'
*
*   Description:
*     Constants and functions for creating basic, user-interactable, pop-up message boxes.
*/
#ifndef H_SAMT_MSGBOX
#define H_SAMT_MSGBOX

EXTERN_START

/************************/
/*  Enums               */
/************************/
/****** Input Option ****************************************************************/
typedef enum mt_msgbox_input
{
    MSGBOX_INPUT_OK         = 0,    /* ok                                           */
    MSGBOX_INPUT_OKCANCEL,          /* ok, cancel                                   */
    MSGBOX_INPUT_ABORTRETRYIGNORE,  /* abort, retry, ignore                         */
    MSGBOX_INPUT_YESNOCANCEL,       /* yes, no, cancel                              */
    MSGBOX_INPUT_YESNO,             /* yes, no                                      */
    MSGBOX_INPUT_RETRYCANCEL,       /* retry, cancel                                */
    MSGBOX_INPUT_CANCELTRYCONT,     /* cancel, try again, continue                  */
}
mt_msgbox_input;

/****** Icon ************************************************************************/
typedef enum mt_msgbox_icon
{
    MSGBOX_ICON_ERROR       = 0,    /* red circle with 'x'                          */
    MSGBOX_ICON_QUESTION,           /* blue circle with '?'                         */
    MSGBOX_ICON_WARNING,            /* yellow triangle with '!'                     */
    MSGBOX_ICON_INFO,               /* blue circle with 'i'                         */
}
mt_msgbox_icon;

/****** Return Value ****************************************************************/
typedef enum mt_msgbox_retn
{
    MSGBOX_RETN_OK          = 0,    /* user pressed 'ok'                            */
    MSGBOX_RETN_CANCEL,             /* user pressed 'cancel'                        */
    MSGBOX_RETN_ABORT,              /* user pressed 'abort'                         */
    MSGBOX_RETN_RETRY,              /* user pressed 'retry'                         */
    MSGBOX_RETN_IGNORE,             /* user pressed 'ignore'                        */
    MSGBOX_RETN_YES,                /* user pressed 'yes'                           */
    MSGBOX_RETN_NO,                 /* user pressed 'no'                            */
    MSGBOX_RETN_CLOSE,              /* user pressed 'close'                         */
    MSGBOX_RETN_HELP,               /* user pressed 'help'                          */
    MSGBOX_RETN_TRYAGAIN,           /* user pressed 'try again'                     */
    MSGBOX_RETN_CONTINUE,           /* user pressed 'continue'                      */
}
mt_msgbox_retn;

/************************/
/*  Prototypes          */
/************************/
/****** Core Function ***************************************************************/
/*
*   Description:
*     Create a message box with a custom title, text, user options, and set icon.
*
*   Notes: 
*     - Calling this will pause the game until the user selects an option.
* 
*   Parameters:
*     - puTitle     : title text
*     - puBody      : message text
*     - input       : user input options
*     - icon        : image icon for the message box
*/
mt_msgbox_retn mtMsgBox( const c8* puTitle, const c8* puBody, mt_msgbox_input input, mt_msgbox_icon icon );

/****** Common Uses *****************************************************************/
/*
*   Description:
*     Create a warning message box with a custom title and text.
*
*   Notes: 
*     - Calling this will pause the game until the user selects an option.
*     - Uses yellow '!' icon with 'Ok' option.
* 
*   Parameters:
*     - puTitle     : title text
*     - puBody      : message text
*/
mt_msgbox_retn mtMsgWarning( const c8* puTitle, const c8* puBody );
/*
*   Description:
*     Create an error message box with a custom title and text.
*
*   Notes: 
*     - Calling this will pause the game until the user selects an option.
*     - Uses red 'X' icon with 'Ok' option.
* 
*   Parameters:
*     - puTitle     : title text
*     - puBody      : message text
*/
mt_msgbox_retn mtMsgError( const c8* puTitle, const c8* puBody );
/*
*   Description:
*     Create a query message box with a custom title and text.
*
*   Notes: 
*     - Calling this will pause the game until the user selects an option.
*     - Uses blue '?' icon with 'Yes' and 'No' options.
* 
*   Parameters:
*     - puTitle     : title text
*     - puBody      : message text
*/
mt_msgbox_retn mtMsgQuery( const c8* puTitle, const c8* puBody );

EXTERN_END

#endif/*H_SAMT_MSGBOX*/
