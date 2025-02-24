/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>      /* core                                                 */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h> /* ninja                                              */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */
#include <rf_mod.h>         /* modifier core                                        */

/****** Self ************************************************************************/
#include <rf_draw/rfd_cnkmod/rfdmod_internal.h> /* parent & siblings                */

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
rjCnkModVolumeP3(const Sint16* const pPList, const CNK_VERTEX_BUFFER* const njvtxbuf)
{
    const CNK_VOLUME_HEAD* p_vohead = (CNK_VOLUME_HEAD*) pPList;

    const int nb_poly = p_vohead->nbpoly;
    const int ufo     = p_vohead->ufo;

    MOD_TRI* const p_modbuf = RFMOD_GetBuffer(nb_poly);

    if (!p_modbuf)
        return;

    const CNK_VOLUME_P3* p_volume = (CNK_VOLUME_P3*) p_vohead->d;

    const CNK_VO_P3* p_vo = p_volume->d;

    if ( RFMOD_GetInvertMode() )
    {
        for (s32 i = 0; i < nb_poly; ++i)
        {
            p_modbuf[i].vtx[2] = njvtxbuf[p_vo->i0].pos;
            p_modbuf[i].vtx[1] = njvtxbuf[p_vo->i1].pos;
            p_modbuf[i].vtx[0] = njvtxbuf[p_vo->i2].pos;

            p_vo = CNK_NEXT_POLY(p_vo, ufo);
        }
    }
    else
    {
        for (s32 i = 0; i < nb_poly; ++i)
        {
            p_modbuf[i].vtx[0] = njvtxbuf[p_vo->i0].pos;
            p_modbuf[i].vtx[1] = njvtxbuf[p_vo->i1].pos;
            p_modbuf[i].vtx[2] = njvtxbuf[p_vo->i2].pos;

            p_vo = CNK_NEXT_POLY(p_vo, ufo);
        }
    }
}

static void
rjCnkModStrip(const Sint16* plist, const CNK_VERTEX_BUFFER* const njvtxbuf)
{
    const CNK_STRIP_HEAD* p_sthead = (CNK_STRIP_HEAD*) plist;

    const bool invmod = RFMOD_GetInvertMode();

    const int nb_strip = p_sthead->nbstrip;
    const int ufo      = p_sthead->ufo;

    const CNK_STRIP* restrict p_strip = (CNK_STRIP*) p_sthead->d;

    for (int ix_strip = 0; ix_strip < nb_strip; ++ix_strip)
    {
        // get inverted strip state
        bool invst = !(p_strip->len < 0);

        // get strip length
        const int len = ABS(p_strip->len);

        // get polygon count
        const int nb_poly = (len - 2);

        /** get and set buffer **/
        MOD_TRI* restrict p_buf_base = RFMOD_GetBuffer(nb_poly);

        if (!p_buf_base)
            return;

        // get strip array
        const CNK_ST* restrict p_st = p_strip->d;

        for (int i = 0; i < nb_poly; ++i)
        {
            NJS_POINT3* restrict p_buf = p_buf_base->vtx;

            /** buffer increment value for destripping algorithm **/
            int buf_inc;

            DESTRIP_START(p_buf, buf_inc, invst);

            const CNK_ST* restrict p_st_2 = p_st;

            for (int j = 0; j < 3; ++j)
            {
                const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[ p_st_2->i ];

                *p_buf = p_vtx->pos;

                p_buf += buf_inc;

                // user offset only applies per polygon, so we skip the first two
                p_st_2 = (i+j >= 2) ? CNK_NEXT_POLY(p_st_2, ufo) : CNK_NEXT_POLY(p_st_2, 0);
            }

            p_buf_base++;

            invst = !invst;

            // user offset only applies per polygon, so we skip the first two
            p_st = (i >= 2) ? CNK_NEXT_POLY(p_st, ufo) : CNK_NEXT_POLY(p_st, 0);
        }

        p_strip = CNK_NEXT_STRIP(p_strip, len, ufo);
    }
}

static void
rjCnkModStripUV(const Sint16* plist, const CNK_VERTEX_BUFFER* const njvtxbuf)
{
    const CNK_STRIP_HEAD* pStripHead = (CNK_STRIP_HEAD*) plist;

    const bool invmod = RFMOD_GetInvertMode();

    const int nb_strip = pStripHead->nbstrip;
    const int ufo      = pStripHead->ufo;

    const CNK_STRIP_UV* restrict p_strip = (CNK_STRIP_UV*) pStripHead->d;

    for (int ix_strip = 0; ix_strip < nb_strip; ++ix_strip)
    {
        // get inverted strip state
        bool invst = !(p_strip->len < 0);

        // get strip length
        const int len = ABS(p_strip->len);

        // get polygon count
        const int nb_poly = (len - 2);

        /** get and set buffer **/
        MOD_TRI* restrict p_buf_base = RFMOD_GetBuffer(nb_poly);

        if (!p_buf_base)
            return;

        // get strip array
        const CNK_ST_UV* restrict p_st = p_strip->d;

        for (int i = 0; i < nb_poly; ++i)
        {
            NJS_POINT3* restrict p_buf = p_buf_base->vtx;

            /** buffer fix and increment values for destripping algorithm **/
            int buf_inc;

            DESTRIP_START(p_buf, buf_inc, invst);

            const CNK_ST_UV* restrict p_st_2 = p_st;

            for (int j = 0; j < 3; ++j)
            {
                const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[ p_st_2->i ];

                *p_buf = p_vtx->pos;

                p_buf += buf_inc;

                // user offset only applies per polygon, so we skip the first two
                p_st_2 = (i+j >= 2) ? CNK_NEXT_POLY(p_st_2, ufo) : CNK_NEXT_POLY(p_st_2, 0);
            }

            p_buf_base++;

            invst = !invst;

            // user offset only applies per polygon, so we skip the first two
            p_st = (i >= 2) ? CNK_NEXT_POLY(p_st, ufo) : CNK_NEXT_POLY(p_st, 0);
        }

        p_strip = CNK_NEXT_STRIP(p_strip, len, ufo);
    }
}

/****** Extern **********************************************************************/
void
rjCnkModPList(const Sint16* const pPList, const CNK_VERTEX_BUFFER* const njvtxbuf)
{
    const Sint16* plist = pPList;
    
    for ( ; ; )
    {
        const int type = ((u8*)plist)[0];

        if (type == NJD_CE)
        {
            /** NJD_ENDOFF **/
            break;
        }

        if (type == NJD_CN)
        {
            /** NJD_NULLOFF **/

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type <= CNK_BITSOFF_MAX)
        {
            /** NJD_BITSOFF **/

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type <= CNK_TINYOFF_MAX)
        {
            /** NJD_TINYOFF **/

            /** Next offset **/
            plist += 2;
            continue;
        }

        if (type <= CNK_MATOFF_MAX)
        {
            /** NJD_MATOFF **/

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        if (type <= CNK_VOLOFF_MAX)
        {
            /** NJD_VOLOFF **/

            switch ( VOSW(type) ) {
            case VOSW( NJD_CO_P3 ):

                rjCnkModVolumeP3(plist, njvtxbuf);
                break;

            case VOSW( NJD_CO_P4 ):
            case VOSW( NJD_CO_ST ):
                break;
            }

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        if (type <= CNK_STRIPOFF_MAX)
        {
            /** NJD_STRIPOFF **/
            switch ( STSW(type) ) {
            case STSW( NJD_CS ):

                rjCnkModStrip(plist, njvtxbuf);
                break;

            case STSW( NJD_CS_UVN ):
            case STSW( NJD_CS_UVH ):

                rjCnkModStripUV(plist, njvtxbuf);
                break;
            }

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        /** An error occured, stop **/
        break;
    }
}
