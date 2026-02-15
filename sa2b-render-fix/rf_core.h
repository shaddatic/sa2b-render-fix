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
*     Function name.
*/
#define RFD_FUNCNAME                "["__FUNCTION__"]"
/*
*   Description:
*     Function name and line macro, eg. "RF_DebugOut (ln 50)"
*/
#define RFD_FUNCINFO                "["__FUNCTION__"](ln " __LINE__ ")"

/********************************/
/*  Prototypes                  */
/********************************/
/****** Msg Common ******************************************************************************/
/*
*   Description:
*     Post an informational/warning/error message box with a header title and formatted body.
*
*   Parameters:
*     - puHeader    : message header
*     - puBodyF     : message body with format tokens
*     - ...         : format parameters
*/
void    RF_MsgInfo(  const c8* puHeader, const c8* puBodyF, ... );
void    RF_MsgWarn(  const c8* puHeader, const c8* puBodyF, ... );
void    RF_MsgError( const c8* puHeader, const c8* puBodyF, ... );
/*
*   Description:
*     Post a question message box with header title and formatted body.
*
*   Parameters:
*     - puHeader    : message header
*     - puBodyF     : message body with format tokens
*     - ...         : format parameters
*
*   Returns:
*     'true' if the user selects 'YES'; or 'false' if `NO`.
*/
bool    RF_MsgQuery( const c8* puTitle, const c8* puBodyF, ... );

/****** Dbg Common ******************************************************************************/
/*
*   Description:
*     If Render Fix should print extra information to the console.
*/
bool    RF_DbgUseExtraInfo( void );

/********************************/
/*  Function Macros             */
/********************************/
/****** Debug Out *******************************************************************************/
#define RF_DbgInfo(...)             ___OutputDebugString("RF INFO: "  __VA_ARGS__)
#define RF_DbgWarn(...)             ___OutputDebugString("RF WARN: "  __VA_ARGS__)
#define RF_DbgError(...)            ___OutputDebugString("RF ERROR: " __VA_ARGS__)
/*
*   Description:
*     Print extra operational info.
*/
#define RF_DbgExtra(...)        if ( RF_DbgUseExtraInfo() ) RF_DbgInfo(__VA_ARGS__)

EXTERN_END

#endif/*H_RF_CORE*/
