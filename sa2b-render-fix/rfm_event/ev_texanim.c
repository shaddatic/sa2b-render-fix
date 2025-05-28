/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */

/****** Self ************************************************************************/
#include <rfm_event/ev_internal.h> /* parent & siblings                             */

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static int
EV_TexAnimSet(EVENT_TEXANIM_CHUNKDATA* pCnkData, int texid, int searchid)
{
    int ret_nb = 0;

    EVENT_TEXANIM_CHUNKDATA* p_cnkdata = pCnkData;

    for ( ; p_cnkdata->pObject; ++p_cnkdata )
    {
        const int count = p_cnkdata->count;

        EVENT_TEXANIM_TINYDATA** pp_tinydata = p_cnkdata->ppTinyData;

        for ( int i = 0; i < count; ++i )
        {
            if ( pp_tinydata[i]->texid == searchid )
            {
                Sint16* p_texid = pp_tinydata[i]->pTiny;

                *p_texid = (*p_texid & ~NJD_TID_MASK) | (texid & NJD_TID_MASK);

                ++ret_nb;
            }
        }
    }

    return ret_nb;
}

/****** Extern **********************************************************************/
void
EV_TexAnimExec(void)
{
    const EVENT_TEXANIM* p_texanim = EventData.pTexAnims;

    if ( !p_texanim || !p_texanim->pChunkData )
    {
        return;
    }

    const int frame = (int) EventFrame;

    const int nb_texid = p_texanim->nbTexId;

    const EVENT_TEXANIM_TEXIDS* p_texids = p_texanim->pTexIds;

    for ( int i = 0; i < nb_texid; ++i )
    {
        const int startid = p_texids[i].startid;
        const int countid = p_texids[i].countid;

        EV_TexAnimSet( p_texanim->pChunkData, startid + (frame % countid), startid );
    }
}
