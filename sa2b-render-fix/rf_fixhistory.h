/*
*   SA2 Render Fix - '/rf_feature.h'
*
*   Description:
*     Render Fix feature checks.
*
*   Contributors:
*     - Shaddatic
*/
#ifndef H_RF_FIXHISTORY
#define H_RF_FIXHISTORY

EXTERN_START

/********************************/
/*  Structures                  */
/********************************/
/****** Fix History *****************************************************************************/
typedef struct
{
    const void** pp;                /* pointer list                                             */
    int          num;               /* pointer list size in memory                              */
}
RF_FIXHIST;

/********************************/
/*  Structures                  */
/********************************/
/****** Create/Free *****************************************************************************/
/*
*   Description:
*     Create a new fix history structure.
*/
RF_FIXHIST* RF_FixHistCreate( void );
/*
*   Description:
*     Free a fix history structure.
*
*   Parameters:
*     - pfh         : fix history
*/
void    RF_FixHistFree( RF_FIXHIST* pfh );

/****** Add/Check *******************************************************************************/
/*
*   Description:
*     Add a pointer to a fix history and also check if it already exists in the list.
*
*   Parameters:
*     - pfh         : fix history
*     - p           : pointer to add/check for
*
*   Returns:
*     'true' if the pointer is in the list; or 'false' if it isn't.
*/
bool    RF_FixHistAdd( RF_FIXHIST* pfh, const void* p );

EXTERN_END

#endif/*H_RF_FIXHISTORY*/
