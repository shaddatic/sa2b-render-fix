#include <samt/core.h>
#include <samt/msgbox.h>

/** Std **/
#include <stdio.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>

/** Self **/
#include <rf_usermsg.h>

static bool UserMsgAlertSuppress;

void
RF_Alert(const c8* head, const c8* body)
{
    if (UserMsgAlertSuppress)
        return;

    c8 buf[64];

    snprintf(buf, sizeof(buf), "Render Fix Alert : %s", head);

    mtMsgWarning(buf, body);
}

void
RF_FatalError(const c8* head, const c8* body)
{
    c8 buf[64];

    snprintf(buf, sizeof(buf), "Render Fix Error : %s", head);

    mtMsgError(buf, body);
}

bool
RF_Query(const c8* head, const c8* body)
{
    c8 buf[64];

    snprintf(buf, sizeof(buf), "Render Fix Query : %s", head);

    return mtMsgQuery(buf, body) == MSGBOX_RETN_YES;
}

void
RF_UserMessageInit(void)
{
    UserMsgAlertSuppress = RF_ConfigGetInt(CNF_DEBUG_DISABLE_ALERT);
}
