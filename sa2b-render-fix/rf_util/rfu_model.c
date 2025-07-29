/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Utility *********************************************************************************/
#include <samt/util/cnkmdl.h>       /* cnkstruct                                                */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */

/****** Self ************************************************************************************/
#include <rfu_model.h>              /* self                                                     */

/********************************/
/*  Source                      */
/********************************/
/************************************************************************************************/
/*
*   Strip Flags
*/
/****** Plist Direct ****************************************************************************/
void
RFU_CnkSetStripFlag(Sint16* pPlist, s32 ixStrip, u16 flagOn, u16 flagOff)
{
    Sint16* plist = pPlist;

    const Uint8 flagon  =  (Uint8) ( flagOn  >> NJD_FST_SHIFT );
    const Uint8 flagoff = ~(Uint8) ( flagOff >> NJD_FST_SHIFT );

    for ( ; ; )
    {
        const int type = CNK_GET_OFFTYPE(plist);

        if ( type == NJD_NULLOFF )
        {
            // next
            plist += CNK_NULLOFF_SIZE;
            continue;
        }

        if ( type < CNK_BITSOFF_MAX )
        {
            // next
            plist += CNK_BITSOFF_SIZE;
            continue;
        }

        if ( type < CNK_TINYOFF_MAX )
        {
            // next
            plist += CNK_TINYOFF_SIZE;
            continue;
        }

        if ( type < CNK_MATOFF_MAX )
        {
            const CNK_MATERIAL_HEAD* restrict p_cnkmat = (CNK_MATERIAL_HEAD*) plist;

            // next
            plist += CNK_MATOFF_SIZE_ADD + p_cnkmat->size;
            continue;
        }

        if ( type < CNK_VOLOFF_MAX )
        {
            CNK_VOLUME_HEAD* restrict p_cnkvol = (CNK_VOLUME_HEAD*) plist;

            // next
            plist += CNK_VOLOFF_SIZE_ADD + p_cnkvol->size;
            continue;
        }

        if ( type < CNK_STRIPOFF_MAX )
        {
            CNK_STRIP_HEAD* restrict p_cnkst = (CNK_STRIP_HEAD*) plist;

            if ( ixStrip == RFD_INDEX_ALL )
            {
                p_cnkst->flag &= flagoff;
                p_cnkst->flag |= flagon;
            }
            else if ( ixStrip-- == 0 )
            {
                p_cnkst->flag &= flagoff;
                p_cnkst->flag |= flagon;
                return;
            }

            // next
            plist += CNK_STRIPOFF_SIZE_ADD + p_cnkst->size;
            continue;
        }

        // end
        break;
    }
}

/****** Model ***********************************************************************************/
void
RFU_CnkModelSetStripFlag(NJS_CNK_MODEL* pModel, s32 ixStrip, u16 flagOn, u16 flagOff)
{
    if ( !pModel->plist )
    {
        return;
    }

    RFU_CnkSetStripFlag(pModel->plist, ixStrip, flagOn, flagOff);
}

/****** Object **********************************************************************************/
void
RFU_CnkObjectSetStripFlag(NJS_CNK_OBJECT* pObject, u16 flagOn, u16 flagOff)
{
    NJS_CNK_OBJECT* p_object = pObject;

    do
    {
        if ( p_object->model )
        {
            RFU_CnkModelSetStripFlag( p_object->model, RFD_INDEX_ALL, flagOn, flagOff );
        }

        if ( p_object->child )
        {
            RFU_CnkObjectSetStripFlag( p_object->child, flagOn, flagOff );
        }

        p_object = p_object->sibling;
    }
    while ( p_object );
}
