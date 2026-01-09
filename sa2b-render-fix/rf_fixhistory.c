/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/memory.h>            /* write call                                               */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */

/****** Self ************************************************************************************/
#include <rf_fixhistory.h>          /* self                                                     */

/********************************/
/*  Source                      */
/********************************/
/****** Fix History *****************************************************************************/
RF_FIXHIST*
RF_FixHistCreate(void)
{
    RF_FIXHIST* p_history = mtAlloc(RF_FIXHIST, 1);

    p_history->pp  = mtCalloc(void*, 128);
    p_history->num = 128;

    return p_history;
}

void
RF_FixHistFree(RF_FIXHIST* pfh)
{
    mtFree(pfh->pp);
    mtFree(pfh);
}

bool
RF_FixHistAdd(RF_FIXHIST* pfh, const void* p)
{
    const int   num = pfh->num;
    const void** pp = pfh->pp;

    for ( int i = 0; i < num; ++i, ++pp )
    {
        if ( *pp == nullptr )
        {
            *pp = p;
            return false;
        }

        if ( p == *pp )
        {
            return true;
        }
    }

    /** If we got here without returning, the list has been maxed out. Realloc more
        room and clear new space. **/

    mtRecalloc(&pfh->pp, void*, num, num * 2);

    pfh->num = num * 2;

    return RF_FixHistAdd(pfh, p); // try again
}
