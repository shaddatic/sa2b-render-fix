/*
*   SA2 Render Fix - '/rf_api.h'
*
*   Description:
*     Render Fix API.
*/
#ifndef H_RF_API
#define H_RF_API

EXTERN_START

/********************************/
/*  Enums                       */
/********************************/
/****** API Functions ***************************************************************************/
typedef enum rfapifunc
{
    RF_APIFUNC_INIT,                /* RFAPI_Init                                               */
    RF_APIFUNC_EARLY,               /* RFAPI_Early                                              */
    RF_APIFUNC_LATE,                /* RFAPI_Late                                               */

    RF_APIFUNC_OLD_INIT,            /* RF_Init                                                  */
    RF_APIFUNC_OLD_EARLY,           /* RF_InitEarly                                             */

    RF_NB_APIFUNC,                  /* enum count                                               */
}
RF_APIFUNC;

/********************************/
/*  Prototypes                  */
/********************************/
/****** User-Exported Functions *****************************************************************/
/*
*   Description:
*     Call a specific API user-exported function list.
*/
void    RFAPI_CallFuncs( RF_APIFUNC apifn );

EXTERN_END

#endif/*H_RF_API*/
