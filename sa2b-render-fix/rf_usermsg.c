#include <sa2b/core.h>
#include <sa2b/user.h>

/** Std **/
#include <stdio.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>

/** Self **/
#include <rf_usermsg.h>

static bool UserMsgAlertSuppress;

void
RF_Alert(const utf8* head, const utf8* body)
{
    if (UserMsgAlertSuppress)
        return;

    utf8 buf[64];

    snprintf(buf, sizeof(buf), "Render Fix Alert : %s", head);

    UserWarningMessageBox(buf, body);
}

void
RF_FatalError(const utf8* head, const utf8* body)
{
    utf8 buf[64];

    snprintf(buf, sizeof(buf), "Render Fix Error : %s", head);

    UserErrorMessageBox(buf, body);
}

bool
RF_Query(const utf8* head, const utf8* body)
{
    utf8 buf[64];

    snprintf(buf, sizeof(buf), "Render Fix Query : %s", head);

    return UserMessageBox(buf, body, INPT_YES_NO, ICON_QUESTION) == USER_YES;
}

void
RF_UserMessageInit(void)
{
    UserMsgAlertSuppress = RF_ConfigGetInt(CNF_DEBUG_DISABLE_ALERT);
}
