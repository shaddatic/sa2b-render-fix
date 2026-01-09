/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/msgbox.h>            /* msgbox                                                   */
#include <samt/string.h>            /* strformat                                                */
#include <samt/memory.h>            /* memory                                                   */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core/self                                                */

/****** Config **********************************************************************************/
#include <cnf.h>                    /* config get                                               */

/****** Std *************************************************************************************/
#include <stdio.h>                  /* std i/o                                                  */
#include <stdarg.h>                 /* varg                                                     */

/********************************/
/*  Data                        */
/********************************/
/****** Format Buffer ***************************************************************************/
static c8*   MsgBuffer;
static isize MsgBufferLen;

/****** Settings ********************************************************************************/
static bool DbgExtraInfo;
static bool MsgWarnSuppress;

/********************************/
/*  Source                      */
/********************************/
/****** Msg Buffer ******************************************************************************/
static void
MsgSetFormatLen(isize szfmt)
{
    if ( MsgBuffer )
    {
        mtFree(MsgBuffer);
    }

    const isize sz = szfmt + (32 - (szfmt % 32));

    MsgBuffer    = mtAlloc(c8, sz);
    MsgBufferLen = sz;
}

static const c8*
MsgGetFormatStr(const c8* fmt, va_list varg)
{
    if ( mtStrSearch(fmt, "%", STR_NOMAX) == STR_NOINDEX )
    {
        return fmt; // if no format codes, don't format
    }

    c8* pu_buf;

    for ( ; ; )
    {
        const isize sz_buf = MsgBufferLen;
        pu_buf             = MsgBuffer;

        const isize out = vsnprintf(pu_buf, sz_buf, fmt, varg);

        if ( out < 0 )
        {
            return "Error formatting message";
        }

        const isize sz_need = (out+1);

        if ( sz_need <= sz_buf )
        {
            break; // done!
        }

        // buffer too small; expand, try again
        MsgSetFormatLen( sz_need );
    }

    return pu_buf;
}

/****** Message Box *****************************************************************************/
static mt_msgbox_retn
RF_MsgBox(const c8* puTitle, const c8* puBody, mt_msgbox_input input, mt_msgbox_icon icon)
{
    c8 buf[64];

    mtStrFormat(buf, ARYLEN(buf), "Render Fix : %s", puTitle);

    return mtMsgBox(buf, puBody, input, icon);
}

/****** Msg Buffer ******************************************************************************/
static inline mt_msgbox_retn
MsgBoxFmt(const c8* puTitle, const c8* puFmt, va_list vaFmt, mt_msgbox_input input, mt_msgbox_icon icon)
{
    return RF_MsgBox(puTitle, MsgGetFormatStr(puFmt, vaFmt), input, icon);
}

/****** Msg Common ******************************************************************************/
void
RF_MsgInfo(const c8* puTitle, const c8* puBodyF, ...)
{
    va_list varg;
    va_start(varg, puBodyF);

    MsgBoxFmt(puTitle, puBodyF, varg, MSGBOX_INPUT_OK, MSGBOX_ICON_INFO);

    va_end(varg);
}

bool
RF_MsgQuery(const c8* puTitle, const c8* puBodyF, ...)
{
    va_list varg;
    va_start(varg, puBodyF);

    const mt_msgbox_retn retn = MsgBoxFmt(puTitle, puBodyF, varg, MSGBOX_INPUT_YESNO, MSGBOX_ICON_QUESTION);

    va_end(varg);

    return (retn == MSGBOX_RETN_YES);
}

void
RF_MsgWarn(const c8* puTitle, const c8* puBodyF, ...)
{
    if ( MsgWarnSuppress )
    {
        return;
    }

    va_list varg;
    va_start(varg, puBodyF);

    MsgBoxFmt(puTitle, puBodyF, varg, MSGBOX_INPUT_OK, MSGBOX_ICON_WARNING);

    va_end(varg);
}

void
RF_MsgError(const c8* puTitle, const c8* puBodyF, ...)
{
    va_list varg;
    va_start(varg, puBodyF);

    MsgBoxFmt(puTitle, puBodyF, varg, MSGBOX_INPUT_OK, MSGBOX_ICON_ERROR);

    va_end(varg);
}

/****** Init ************************************************************************************/
bool
RF_DbgUseExtraInfo(void)
{
    return DbgExtraInfo;
}

/****** Init ************************************************************************************/
void
RF_MsgInit(void)
{
    DbgExtraInfo    = CNF_GetInt(CNF_DEBUG_EXTRAINFO);
    MsgWarnSuppress = CNF_GetInt(CNF_DEBUG_DISABLE_ALERT);
}
