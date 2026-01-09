/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/model.h>             /* write call                                               */

/****** Util ************************************************************************************/
#include <samt/util/ptrlist.h>      /* ptrlist                                                  */
#include <samt/util/endian.h>       /* swap endian                                              */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_fixhistory.h>          /* fix history                                              */

/****** Self ************************************************************************************/
#include <rf_module/rfm_event/ev_renderer/evr_internal.h> /* parent & siblings                  */

/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
static bool
MtypeIsShape(NJ_MTYPE mtype)
{
    return ( mtype == NJ_MTYPE_VERT_4 || mtype == NJ_MTYPE_NORM_5 );
}

static void
FixShapeData(NJS_MKEY_P* mkey, usize nb, const mt_ptrlist* mtwk, RF_FIXHIST* fxwk)
{
    for ( usize i = 0; i < nb; ++i )
    {
        NJS_POINT3* p = mkey[i].key;

        const isize ix_ptr = mtPtrListFind( mtwk, p );

        if ( ix_ptr < 0 || RF_FixHistAdd(fxwk, p) )
        {
            continue;
        }

        const void* p_next = mtwk->ptrs[ix_ptr+1];

        for ( ; (pint)p < (pint)p_next; ++p )
        {
            EndianSwap32( &p->x );
            EndianSwap32( &p->y );
            EndianSwap32( &p->z );
        }
    }
}

static void
FixShape(NJS_MOTION* pShape, usize nbNode, RF_FIXHIST* fxwk)
{
    void** pp;
    usize* pnb;

    const isize nb_elem = mtMotGetMdata(pShape, (void**)&pp, &pnb);

    if ( nb_elem <= 0 )
    {
        return;
    }

    u8 mtypes[16];
    mtMotGetMtypes(pShape, mtypes);

    mt_ptrlist* mtwk = mtMotGetPointers(pShape, nbNode, false);

    for ( usize ix_node = 0; ix_node < nbNode; ++ix_node )
    {
        for ( isize ix_elem = 0; ix_elem < nb_elem; ++ix_elem )
        {
            if ( *pp && MtypeIsShape(mtypes[ix_elem]) )
            {
                FixShapeData(*pp, *pnb, mtwk, fxwk);
            }

            pp++;
            pnb++;
        }

        pp  += nb_elem; // skip over 'nb' list
        pnb += nb_elem; // skip over 'p' list
    }

    mtPtrListFree(mtwk);

}

void
EVR_FixShapes(void)
{
    const int nb_scene = EventData.nbScene+1;

    RF_DbgExtraInfo("Fixing shape data...");

    RF_FIXHIST* fxwk = RF_FixHistCreate();

    for ( int ix_scene = 0; ix_scene < nb_scene; ++ix_scene )
    {
        const EVENT_SCENE* const p_scene = &SceneData[ix_scene];

        const int nb_entry = p_scene->nbEntry;

        for (int ix_entry = 0; ix_entry < nb_entry; ++ix_entry)
        {
            EVENT_ENTRY* const p_entry = &p_scene->pEntries[ix_entry];

            if ( p_entry->pShape )
            {
                FixShape(p_entry->pShape, mtCnkNodeCount(p_entry->pObject), fxwk);
            }
        }

        EVENT_BIG* p_big = p_scene->pBig;

        if ( p_big && p_big->nbMotion )
        {
            const isize nb_mot  = p_big->nbMotion;
            const usize nb_node = mtCnkNodeCount(p_big->pObject);

            EVENT_BIG_MOTION* p_mot = p_big->pMotions;

            for ( isize i = 0; i < nb_mot; ++i )
            {
                if ( p_mot[i].pShape )
                {
                    FixShape(p_mot[i].pShape, nb_node, fxwk);
                }
            }
        }
    }

    RF_FixHistFree(fxwk);
}
