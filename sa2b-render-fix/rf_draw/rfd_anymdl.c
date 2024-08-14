/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>      /* core                                                 */
#include <sa2b/writeop.h>   /* WriteJump                                            */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h> /* ninja                                              */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */

/****** Self ************************************************************************/
#include <rf_draw/rfd_internal.h> /* parent & siblings                              */

/************************/
/*  Source              */
/************************/
/****** Extern **********************************************************************/
int
rjAnyDrawModel(void* model)
{
    /** The "plist" is unused for  Ginja models in SA2B, so will always be NULL.
        In turn, there's no reason for Chunk models to not have poly data. So, a
        simple check like this should suffice in most cases, and our use case is
        small **/

    NJS_CNK_MODEL* p_cnkm = model;

    if (!p_cnkm->plist)
    {
        gjDrawModel(model);
    }
    else
    {
        njCnkDrawModel(model);
    }

    return 0;
}

void
rjAnyDrawObject(void* object)
{
    njCnkTransformObject(object, rjAnyDrawModel);
}
