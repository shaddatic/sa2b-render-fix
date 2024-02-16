/*
*   SA2 Render Fix - '/rf_usermsg.h'
*
*   Description:
*       Header for alerting the end-user with a pop-up message
*   box of various events. It should be noted that posting a
*   message will freeze the game until it is closed, so this
*   disruption should be taken into account.
*       If the alert is of limited interest to the end-user, a
*   regular debug print to the console may be a better
*   alternative.
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_USERMSG_H_
#define _RF_USERMSG_H_

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Post alert **/
void    RF_Alert(const utf8* head, const utf8* body);

/** Post fatal error alert **/
void    RF_FatalError(const utf8* head, const utf8* body);

/** Post mod conflict alert **/
void    RF_ModConflict(const utf8* mod, const utf8* body);

#define RF_ModConflictEx(_mod, _rf_feature)     RF_ModConflict(_mod, \
                                                    "The '" _mod "' mod is obsolete and is incompatible with Render Fix's '" _rf_feature "' feature!\n\n" \
                                                    "Please disable either the '" _mod "' mod, or the '" _rf_feature "' setting!")

/** Query the user with a yes/no message box.
    A return of 'true' means the user selected 'yes' **/
bool    RF_Query(const utf8* head, const utf8* body);

EXTERN_END

#endif/*_RF_USERMSG_H_*/
