/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/msgbox.h>            /* msgbox                                                   */
#include <samt/string.h>            /* strformat                                                */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core/self                                                */

/********************************/
/*  Source                      */
/********************************/
/****** Message Box *****************************************************************************/
bool
RF_MessageOut(const c8* puTitle, const c8* puBody, eRF_MSGINPUT input, eRF_MSGICON icon)
{
    const mt_msgbox_retn ret = mtMsgBox(puTitle, puBody, (mt_msgbox_input)input, (mt_msgbox_icon)icon);

    switch ( ret )
    {
        case MSGBOX_RETN_OK:
        case MSGBOX_RETN_RETRY:
        case MSGBOX_RETN_YES:
        case MSGBOX_RETN_HELP:
        case MSGBOX_RETN_TRYAGAIN:
        case MSGBOX_RETN_CONTINUE:
        {
            return true;
        }
        case MSGBOX_RETN_CANCEL: default:
        case MSGBOX_RETN_ABORT:
        case MSGBOX_RETN_NO:
        case MSGBOX_RETN_CLOSE:
        {
            return false;
        }
    }
}
