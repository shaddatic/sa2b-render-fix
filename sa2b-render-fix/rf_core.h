/*
*   SA2 Render Fix - '/rf_core.h'
*
*   Description:
*     Contains project wide resources. Should always be included & should be first before other
*   Render Fix headers.
*/
#ifndef H_RF_CORE
#define H_RF_CORE

/********************************/
/*  Includes                    */
/********************************/
/****** Utility *********************************************************************************/
#include <samt/util/devutil.h>      /* developer utilities                                      */
#include <samt/util/c_constexpr.h>  /* constexpr                                                */
#include <samt/util/c_nullptr.h>    /* nullptr                                                  */

/****** System **********************************************************************************/
#include <samt/shinobi/sg_xpt.h>    /* shinobi types                                            */

/****** Game ************************************************************************************/
#include <samt/sonic/debug.h>       /* debug out                                                */

EXTERN_START

/********************************/
/*  Constants                   */
/********************************/
/****** Function Info ***************************************************************************/
/*
*   Description:
*     Function name and line macro, eg. "RF_DebugOut (ln 50)"
*/
#define RFD_FUNCINFO                __FUNCTION__ " (ln " __LINE__ ")"

/********************************/
/*  Enums                       */
/********************************/
/****** Message Box *****************************************************************************/
typedef enum
{
    MSGINPUT_OK,                        /* ok                                                   */
    MSGINPUT_OKCANCEL,                  /* ok, cancel                                           */
    MSGINPUT_ABORTRETRYIGNORE,          /* abort, retry, ignore                                 */
    MSGINPUT_YESNOCANCEL,               /* yes, no, cancel                                      */
    MSGINPUT_YESNO,                     /* yes, no                                              */
    MSGINPUT_RETRYCANCEL,               /* retry, cancel                                        */
    MSGINPUT_CANCELTRYCONT,             /* cancel, try again, continue                          */
}
eRF_MSGINPUT;

typedef enum
{
    MSGICON_ERROR,                      /* red circle with 'x'                                  */
    MSGICON_QUESTION,                   /* blue circle with '?'                                 */
    MSGICON_WARNING,                    /* yellow triangle with '!'                             */
    MSGICON_INFO,                       /* blue circle with 'i'                                 */
}
eRF_MSGICON;

/********************************/
/*  Prototypes                  */
/********************************/
/****** Message Box *****************************************************************************/
/*
*   Description:
*     Display a message box with a set header, body, input options, and icon.
*
*   Parameters:
*     - puHeader    : message window title
*     - puBody      : body text
*     - input       : input options
*     - icon        : icon
*
*   Returns:
*     'true' if the user response was positive (OK/YES); or 'false' if it wasn't (NO/ABORT).
*/
bool    RF_MessageOut( const c8* puHeader, const c8* puBody, eRF_MSGINPUT input, eRF_MSGICON icon );

/********************************/
/*  Function Macros             */
/********************************/
/****** Debug Out *******************************************************************************/
#define RF_DbgInfo(s, ...)          ___OutputDebugString("RF INFO: "  s __VA_ARGS__)
#define RF_DbgWarn(s, ...)          ___OutputDebugString("RF WARN: "  s __VA_ARGS__)
#define RF_DbgError(s, ...)         ___OutputDebugString("RF ERROR: " s __VA_ARGS__)

/****** Message Box *****************************************************************************/
#define RF_MsgInfo(h, b)            RF_MessageOut("Render Fix : " h, b, MSGINPUT_OK, MSGICON_INFO)
#define RF_MsgWarn(h, b)            RF_MessageOut("Render Fix : " h, b, MSGINPUT_OK, MSGICON_WARNING)
#define RF_MsgError(h, b)           RF_MessageOut("Render Fix : " h, b, MSGINPUT_OK, MSGICON_ERROR)

EXTERN_END

#endif/*H_RF_CORE*/
