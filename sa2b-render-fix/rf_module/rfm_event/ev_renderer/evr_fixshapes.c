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

        if ( !p || RF_FixHistAdd(fxwk, p) )
        {
            continue;
        }

        const isize ix_ptr = mtPtrListFind( mtwk, p );

        if ( ix_ptr < 0 )
        {
            continue;
        }

        const void* p_next;

        if ( ix_ptr+1 >= (isize)mtwk->num )
        {
            if ( (pint)p > (pint)EV_MTNBUF_START && (pint)p < (pint)EV_MTNBUF_END )
            {
                // byteswap entire buffer from here, no other choice
                p_next = EV_MTNBUF_END;
            }
            else // pointer is outside of buffer somehow? nothing can be done
            {
                continue;
            }
        }
        else // not end of the list
        {
            p_next = mtwk->ptrs[ix_ptr+1];
        }

        for ( ; (pint)p < (pint)p_next; ++p )
        {
            EndianSwap32( &p->x );
            EndianSwap32( &p->y );
            EndianSwap32( &p->z );
        }
    }
}

static void
FixShape(NJS_MOTION* pShape, usize nbNode, const mt_ptrlist* mtwk, RF_FIXHIST* fxwk)
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
}

void
EVR_FixShapes(void)
{
    const isize nb_scene = EventData.nbScene+1;

    RF_DbgExtra("Fixing Event shape data...");

    RF_FIXHIST* fxwk = RF_FixHistCreate();
    mt_ptrlist* mtwk = mtPtrListCreate( 8192 );

    for ( isize ix_scene = 0; ix_scene < nb_scene; ++ix_scene )
    {
        const EVENT_SCENE* const p_scene = &SceneData[ix_scene];

        const isize nb_cam = p_scene->nbCameraMotion;

        for ( isize ix_cam = 0; nb_cam < ix_cam; ++ix_cam )
        {
            NJS_MOTION* p_mtn = p_scene->pCameraMotions[ix_cam];

            if ( p_mtn )
            {
                mtMotAddPointers( mtwk, p_mtn, 1, false );
            }
        }

        const isize nb_entry = p_scene->nbEntry;

        for (isize ix_entry = 0; ix_entry < nb_entry; ++ix_entry)
        {
            EVENT_ENTRY* const p_entry = &p_scene->pEntries[ix_entry];

            if ( p_entry->pMotion )
            {
                mtMotAddPointers( mtwk, p_entry->pMotion, mtCnkNodeCount(p_entry->pObject), false );
            }

            if ( p_entry->pShape )
            {
                mtMotAddPointers( mtwk, p_entry->pShape, mtCnkNodeCount(p_entry->pObject), false );
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
                if ( p_mot[i].pMotion )
                {
                    mtMotAddPointers( mtwk, p_mot[i].pMotion, nb_node, false );
                }

                if ( p_mot[i].pShape )
                {
                    mtMotAddPointers( mtwk, p_mot[i].pShape, nb_node, false );
                }
            }
        }
    }

    // sort pointers for next step
    mtPtrListSort( mtwk );

    for ( isize ix_scene = 0; ix_scene < nb_scene; ++ix_scene )
    {
        const EVENT_SCENE* const p_scene = &SceneData[ix_scene];

        const isize nb_entry = p_scene->nbEntry;

        for (isize ix_entry = 0; ix_entry < nb_entry; ++ix_entry)
        {
            EVENT_ENTRY* const p_entry = &p_scene->pEntries[ix_entry];

            if ( p_entry->pShape )
            {
                FixShape( p_entry->pShape, mtCnkNodeCount(p_entry->pObject), mtwk, fxwk );
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
                    FixShape( p_mot[i].pShape, nb_node, mtwk, fxwk );
                }
            }
        }
    }

    mtPtrListFree(mtwk);
    RF_FixHistFree(fxwk);

    RF_DbgExtra("Event shape data fixed to little endian!");
}
