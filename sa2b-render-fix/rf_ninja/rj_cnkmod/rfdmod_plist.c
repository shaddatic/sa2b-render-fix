/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>      /* core                                                 */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h> /* ninja                                              */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */

/****** Self ************************************************************************/
#include <rf_ninja/rj_cnkmod/rfdmod_internal.h> /* parent & siblings                */

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
rjCnkModVolumeP3(const Sint16* const pPList, const RJS_VERTEX_BUF* const vbuf)
{
    const CNK_VOLUME_HEAD* p_vohead = (CNK_VOLUME_HEAD*) pPList;

    const int nb_poly = p_vohead->nbpoly;
    const int ufo     = p_vohead->ufo;

    const int nb_vtx = rjStartModTriList( nb_poly );

    if ( !nb_vtx )
    {
        return;
    }

    RJS_VERTEX_M* p_vbuf = rjGetModVertexBuffer();

    const CNK_VOLUME_P3* p_volume = (const CNK_VOLUME_P3*) p_vohead->d;

    const CNK_VO_P3* p_vo = p_volume->d;

    if ( _nj_control_3d_flag_ & NJD_CONTROL_3D_MIRROR_MODEL )
    {
        for (s32 i = 0; i < nb_poly; ++i)
        {
            p_vbuf[0].pos = vbuf[p_vo->i2].pos;
            p_vbuf[1].pos = vbuf[p_vo->i1].pos;
            p_vbuf[2].pos = vbuf[p_vo->i0].pos;
            
            p_vbuf += 3;

            p_vo = CNK_NEXT_POLY(p_vo, ufo);
        }
    }
    else // normal draw
    {
        for (s32 i = 0; i < nb_poly; ++i)
        {
            p_vbuf[0].pos = vbuf[p_vo->i0].pos;
            p_vbuf[1].pos = vbuf[p_vo->i1].pos;
            p_vbuf[2].pos = vbuf[p_vo->i2].pos;

            p_vbuf += 3;

            p_vo = CNK_NEXT_POLY(p_vo, ufo);
        }
    }

    rjEndModTriList( nb_vtx );
}

static void
rjCnkModStrip(const CNK_STRIP_HEAD* restrict striph, const RJS_VERTEX_BUF* restrict vbuf)
{
    const int nb_strip = striph->nbstrip;
    const int ufo      = striph->ufo;

    const CNK_STRIP* p_st = (const CNK_STRIP*) striph->d;

    for (int ix_strip = 0; ix_strip < nb_strip; ++ix_strip)
    {
        Bool invst;
        const Sint32 nb_vert = rjStartModTriDestrip( p_st->len, &invst );

        if ( !nb_vert )
        {
            return;
        }

        // get vertex buffer
        RJS_VERTEX_M* p_buf_base = rjGetModVertexBuffer();

        // get strip array
        const CNK_ST* restrict p_st_base = p_st->d;

        for (int ix_poly = 0, ix_vert = 0; ix_vert < nb_vert; ++ix_poly, ix_vert += 3)
        {
            RJS_VERTEX_M* p_buf = p_buf_base;

            const CNK_ST* restrict p_polyvtx = p_st_base;

            int buf_inc;

            DESTRIP_START(p_buf, buf_inc, invst);

            for (int j = 0; j < 3; ++j)
            {
                const RJS_VERTEX_BUF* restrict p_vtx = &vbuf[ p_polyvtx->i ];

                // set position
                p_buf->pos = p_vtx->pos;

                /** End set buffer vertex **/

                p_buf += buf_inc;

                // to next polygon vertex
                p_polyvtx = NEXT_STRIP_POLY(p_polyvtx, ix_poly+j, ufo);
            }

            p_buf_base += 3;

            // swap strip winding mode for next polygon
            invst = !invst;

            // base to next polygon vertex
            p_st_base = NEXT_STRIP_POLY(p_st_base, ix_poly, ufo);
        }

        rjEndModTriDestrip(nb_vert);

        // we're now two strip indexes short
        p_st_base = CNK_NEXT_POLY(p_st_base, ufo);
        p_st_base = CNK_NEXT_POLY(p_st_base, ufo);

        // next strip chunk starts at the end of the current one
        p_st = (void*) p_st_base;
    }
}

static void
rjCnkModStripUV(const CNK_STRIP_HEAD* restrict striph, const RJS_VERTEX_BUF* restrict vbuf)
{
    const int nb_strip = striph->nbstrip;
    const int ufo      = striph->ufo;

    const CNK_STRIP_UV* p_st = (const CNK_STRIP_UV*) striph->d;

    for (int ix_strip = 0; ix_strip < nb_strip; ++ix_strip)
    {
        Bool invst;
        const Sint32 nb_vert = rjStartModTriDestrip( p_st->len, &invst );

        if ( !nb_vert )
        {
            return;
        }

        // get vertex buffer
        RJS_VERTEX_M* p_buf_base = rjGetModVertexBuffer();

        // get strip array
        const CNK_ST_UV* restrict p_st_base = p_st->d;

        for (int ix_poly = 0, ix_vert = 0; ix_vert < nb_vert; ++ix_poly, ix_vert += 3)
        {
            RJS_VERTEX_M* p_buf = p_buf_base;

            const CNK_ST_UV* restrict p_polyvtx = p_st_base;

            int buf_inc;

            DESTRIP_START(p_buf, buf_inc, invst);

            for (int j = 0; j < 3; ++j)
            {
                const RJS_VERTEX_BUF* restrict p_vtx = &vbuf[ p_polyvtx->i ];

                // set position
                p_buf->pos = p_vtx->pos;

                /** End set buffer vertex **/

                p_buf += buf_inc;

                // to next polygon vertex
                p_polyvtx = NEXT_STRIP_POLY(p_polyvtx, ix_poly+j, ufo);
            }

            p_buf_base += 3;

            // swap strip winding mode for next polygon
            invst = !invst;

            // base to next polygon vertex
            p_st_base = NEXT_STRIP_POLY(p_st_base, ix_poly, ufo);
        }

        rjEndModTriDestrip(nb_vert);

        // we're now two strip indexes short
        p_st_base = CNK_NEXT_POLY(p_st_base, ufo);
        p_st_base = CNK_NEXT_POLY(p_st_base, ufo);

        // next strip chunk starts at the end of the current one
        p_st = (void*) p_st_base;
    }
}

/****** Extern **********************************************************************/
void
rjCnkModPList(const Sint16* const pPList, const RJS_VERTEX_BUF* const njvtxbuf)
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

            switch ( VOSW(type) )
            {
                case VOSW( NJD_CO_P3 ):
                {
                    rjCnkModVolumeP3(plist, njvtxbuf);
                    break;
                }
                case VOSW( NJD_CO_P4 ):
                case VOSW( NJD_CO_ST ):
                {
                    break;
                }
            }

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        if (type <= CNK_STRIPOFF_MAX)
        {
            const CNK_STRIP_HEAD* striph = (const CNK_STRIP_HEAD*)plist;

            /** NJD_STRIPOFF **/
            switch ( STSW(type) )
            {
                case STSW( NJD_CS ):
                {
                    rjCnkModStrip(striph, njvtxbuf);
                    break;
                }
                case STSW( NJD_CS_UVN ):
                case STSW( NJD_CS_UVH ):
                {
                    rjCnkModStripUV(striph, njvtxbuf);
                    break;
                }
            }

            /** Next offset **/
            plist += striph->size + 2;
            continue;
        }

        /** An error occured, stop **/
        break;
    }
}
