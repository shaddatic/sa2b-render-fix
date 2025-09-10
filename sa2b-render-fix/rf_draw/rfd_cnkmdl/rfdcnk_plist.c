/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>      /* core                                                 */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h> /* ninja                                              */

/****** GX **************************************************************************/
#include <samt/gx/gx.h>     /* GX                                                   */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */
#include <rf_renderstate.h> /* render state                                         */
#include <rf_util.h>        /* utility                                              */
#include <rf_gx.h>          /* gx                                                   */

/****** Self ************************************************************************/
#include <rf_draw/rfd_cnkmdl/rfdcnk_internal.h>              /* parent & siblings   */
#include <rf_draw/rfd_cnkmdl/rfdcnk_plist/rfdcpl_internal.h> /* self                */

/************************/
/*  Constants           */
/************************/
/****** Cnk Strip Attributes *********************************************************/
#define CNKST_HAS_OPAQUE         (0x01) /* has opaque strips                         */
#define CNKST_HAS_TRANS          (0x02) /* has transparent strips                    */
#define CNKST_HAS_TRANSDB        (0x04) /* has transparent strips that are db        */

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static bool
GetStripDrawState(CNK_CTX* restrict pCtx)
{
    const s32 flag = pCtx->flag;

    const Sint16 fst = pCtx->fst;

    /** if current draw mode doesn't match the transparent state of this strip, skip it **/
    const bool fst_ua = (fst & (NJD_FST_UA|NJD_FST_NAT));

    if ( (bool)(flag & CTXF_DRAW_TRANS) != fst_ua )
    {
        return false;
    }

    /** if back face culling is supported, normal faces aren't being drawn, and
        this strip isn't double sided: hide the inverse faces **/

    if ( flag & CTXF_CTL_BACKFACECULL && !(flag & CTXF_DRAW_NORMAL) && !(fst & NJD_FST_DB) )
    {
        return false;
    }

    return true;
}

static void
rjCnkPlistSub(CNK_CTX* restrict pCtx, const Sint16* pPList, const void* vbuf)
{
    const Sint16* plist = pPList;
;
    pTexSurface = nullptr;

    for ( ; ; )
    {
        const int type = CNK_GET_OFFTYPE(plist);

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
            switch (type)
            {
                case NJD_CB_BA: // CnkBits Blend Alpha
                {
                    rjCnkSetBlend(pCtx, plist);
                    break;
                }
                case NJD_CB_DA: // CnkBits mipmap 'D' Adjust
                {
                    break;
                }
                case NJD_CB_EXP: // CnkBits specular EXPonent
                {
                    rjCnkSetExponent(pCtx, plist);
                    break;
                }
                case NJD_CB_CP: // CnkBits Cache Polygons
                {
                    /** caching is handled in the exec-pass **/
                    return;
                }
                case NJD_CB_DP: // CnkBits Draw Polygons
                {
                    s32 cache_idx = ((u8*)plist)[1];

                    rjCnkPlistSub(pCtx, _nj_cnk_polygon_cache_tbl_[cache_idx], vbuf);
                    break;
                }
            }

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type <= CNK_TINYOFF_MAX)
        {
            /** NJD_TINYOFF **/
            rjCnkSetTexture(pCtx, plist);

            /** Next offset **/
            plist += 2;
            continue;
        }

        if (type <= CNK_MATOFF_MAX)
        {
            /** NJD_MATOFF **/
            rjCnkSetMaterial(pCtx, plist);

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        if (type <= CNK_STRIPOFF_MAX)
        {
            /** NJD_STRIPOFF **/
            rjCnkSetStrip(pCtx, plist);

            /** Based on context and strip flags, determine if this strip should be
                drawn. For example, we're drawing only inverse faces but this strip
                isn't double sided. If it shouldn't be drawn, just skip it. **/
            if ( GetStripDrawState(pCtx) )
            {
                const CNK_STRIP_HEAD* restrict striph = (void*) plist;

                switch ( STSW( type ) )
                {
                    case STSW( NJD_CS ):
                    {
                        rjCnkStrip(pCtx, striph, vbuf);
                        break;
                    }
                    case STSW( NJD_CS_UVN ):
                    {
                        rjCnkStripUV(pCtx, striph, vbuf, IS_UVN);
                        break;
                    }
                    case STSW( NJD_CS_UVH ):
                    {
                        rjCnkStripUV(pCtx, striph, vbuf, IS_UVH);
                        break;
                    }
                    case STSW( NJD_CS_VN ):
                    {
                        rjCnkStripVN(pCtx, striph, vbuf);
                        break;
                    }
                    case STSW( NJD_CS_UVN_VN ):
                    {
                        rjCnkStripUVVN(pCtx, striph, vbuf, IS_UVN);
                        break;
                    }
                    case STSW( NJD_CS_UVH_VN ):
                    {
                        rjCnkStripUVVN(pCtx, striph, vbuf, IS_UVH);
                        break;
                    }
                    case STSW( NJD_CS_D8 ):
                    {
                        rjCnkStripD8(pCtx, striph, vbuf);
                        break;
                    }
                    case STSW( NJD_CS_UVN_D8 ):
                    {
                        rjCnkStripUVD8(pCtx, striph, vbuf, IS_UVN);
                        break;
                    }
                    case STSW( NJD_CS_UVH_D8 ):
                    {
                        rjCnkStripUVD8(pCtx, striph, vbuf, IS_UVH);
                        break;
                    }
                }
            }

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        /** An error occured, stop **/
        break;
    }
}

static void
ExecCnkPlist(const CNK_CTX* restrict pCtx, const Sint16* pPList, u32* pFlag)
{
    const Sint16* plist = pPList;

    for ( ; ; )
    {
        const int type = CNK_GET_OFFTYPE(plist);

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
            const CNK_BITS_HEAD* p_bits = (const void*) plist;

            /** NJD_BITSOFF **/
            switch (type)
            {
                case NJD_CB_CP: // CnkBits Cache Polygons
                {
                    const CNK_BITS_POLYLIST* p_cache = (const CNK_BITS_POLYLIST*)&p_bits->d;

                    const s32 ix_cache = p_cache->list;

                    _nj_cnk_polygon_cache_tbl_[ix_cache] = plist + CNK_BITSOFF_SIZE; // cache next offset

                    _nj_cnk_polygon_cache_num_++;
                    return;
                }
                case NJD_CB_DP: // CnkBits Draw Polygons
                {
                    const CNK_BITS_POLYLIST* p_cache = (const CNK_BITS_POLYLIST*)&p_bits->d;

                    const s32 ix_cache = p_cache->list;

                    ExecCnkPlist(pCtx, _nj_cnk_polygon_cache_tbl_[ix_cache], pFlag);

                    _nj_cnk_polygon_cache_num_--;
                    break;
                }
            }

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

        if (type <= CNK_STRIPOFF_MAX)
        {
            /** NJD_STRIPOFF **/
            Sint16 fst = plist[0];

            if ( _nj_control_3d_flag_ & NJD_CONTROL_3D_CNK_CONSTANT_ATTR )
            {
                fst = (fst & _nj_constant_attr_and_) | _nj_constant_attr_or_;
            }

            switch ( _rj_cnk_depth_queue_ )
            {
                case RJD_CNK_DEPTHQUEUE_OFF:
                case RJD_CNK_DEPTHQUEUE_NEAR:
                {
                    break;
                }
                case RJD_CNK_DEPTHQUEUE_ON:
                {
                    fst |= NJD_FST_UA;
                    break;
                }
            }

            if ( fst & (NJD_FST_UA|NJD_FST_NAT) )
            {
                *pFlag |= CNKST_HAS_TRANS;

                if ( !(pCtx->flag & CTXF_CTL_BACKFACECULL) || fst & (NJD_FST_DB) || RFRS_GetCullMode() == RFRS_CULLMD_NONE )
                {
                    *pFlag |= CNKST_HAS_TRANSDB;
                }
            }
            else
            {
                *pFlag |= CNKST_HAS_OPAQUE;
            }

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        /** An error occured, stop **/
        break;
    }
}

static void
DrawOpaqueStrip(CNK_CTX* pCtx, const Sint16* restrict plist, const void* restrict njvtxbuf)
{
    /** Draw opaque strips.

        Unlike transparent strips, we don't need to worry about the draw order of
        normal and inverse faces. So, we just set both to draw and the 'SubPlist'
        function will correctly handle the rest.

        It's important to note that the 'CULL' context flags only *allow* the
        drawing of faces, the flags don't enforce it. It's up to the strip
        renderer itself if faces should be drawn or not. **/

//  pCtx->flag &= ~CTXFLG_DRAW_TRANS;  // implied
//  pCtx->flag &= ~CTXFLG_CULL_MASK;   // ^

    /** Draw normal and inverse mesh faces depending on culling mode. **/
    switch ( RFRS_GetCullMode() )
    {
        case RFRS_CULLMD_NORMAL:
        {
            pCtx->flag |= CTXF_DRAW_NORMAL;
            rjCnkPlistSub(pCtx, plist, njvtxbuf);
            break;
        }
        case RFRS_CULLMD_INVERSE:
        {
            pCtx->flag |= CTXF_DRAW_INVERSE;
            rjCnkPlistSub(pCtx, plist, njvtxbuf);
            break;
        }
        case RFRS_CULLMD_AUTO:
        case RFRS_CULLMD_NONE:
        {
            pCtx->flag |= (CTXF_DRAW_NORMAL|CTXF_DRAW_INVERSE);
            rjCnkPlistSub(pCtx, plist, njvtxbuf);
            break;
        }
    }
}

static void
DrawTransStrip(CNK_CTX* pCtx, const Sint16* restrict plist, const void* restrict njvtxbuf, s32 flag)
{
    /** Draw transparent strips.

        Unlike opaque strips, transparent strips are drawn back-face first for
        basic transparancy sorting reasons. This is also done as two entire 'plist'
        passes, rather than per strip, which works better as it stops potential
        strip ordering issues. The pass order can be changed by setting the
        'CnkPassMode' to 'inverse'. **/

    pCtx->flag |=  CTXF_DRAW_TRANS;
    pCtx->flag &= ~(CTXF_DRAW_NORMAL|CTXF_DRAW_INVERSE);

    /** Draw normal and inverse mesh faces depending on culling mode, pass mode,
        and the existence of double sided strips. If there are no double sided
        strips the back-face never needs to be drawn, so we can entirely skip it. **/
    switch ( RFRS_GetCullMode() )
    {
        case RFRS_CULLMD_NORMAL:
        {
            pCtx->flag |= CTXF_DRAW_NORMAL;
            rjCnkPlistSub(pCtx, plist, njvtxbuf);
            break;
        }
        case RFRS_CULLMD_INVERSE:
        {
            if ( flag & CNKST_HAS_TRANSDB )
            {
                pCtx->flag |= CTXF_DRAW_INVERSE;
                rjCnkPlistSub(pCtx, plist, njvtxbuf);
            }
            break;
        }
        case RFRS_CULLMD_AUTO:
        case RFRS_CULLMD_NONE:
        {
            if ( flag & CNKST_HAS_TRANSDB )
            {
                if ( !(_nj_control_3d_flag_ & NJD_CONTROL_3D_MIRROR_MODEL) )
                {
                    pCtx->flag |= CTXF_DRAW_INVERSE;
                    rjCnkPlistSub(pCtx, plist, njvtxbuf);
                    pCtx->flag &= ~CTXF_DRAW_INVERSE;

                    pCtx->flag |= CTXF_DRAW_NORMAL;
                    rjCnkPlistSub(pCtx, plist, njvtxbuf);
                }
                else // draw inverse order
                {
                    pCtx->flag |= CTXF_DRAW_NORMAL;
                    rjCnkPlistSub(pCtx, plist, njvtxbuf);
                    pCtx->flag &= ~CTXF_DRAW_NORMAL;

                    pCtx->flag |= CTXF_DRAW_INVERSE;
                    rjCnkPlistSub(pCtx, plist, njvtxbuf);
                }
            }
            else
            {
                pCtx->flag |= CTXF_DRAW_NORMAL;
                rjCnkPlistSub(pCtx, plist, njvtxbuf);
            }
            break;
        }
    }
}

void    rjCnkBeginDraw(void);
void    rjCnkEndDraw(void);

/****** Extern **********************************************************************/
void
rjCnkPList(const Sint16* restrict plist, const CNK_VERTEX_BUFFER* restrict vbuf)
{
    /** Setup the Chunk context. This is used to track the current draw context of
        the model and it's strips. If the diffuse color is changed, it's applied to
        this context first.
        The 'flag' struct member starts with the function emulation mode, so we
        initiate it to the current function mode value. **/

    CNK_CTX ctx;
    rjCnkBeginContext( &ctx );

    /** First pass of the Chunk 'plist' data. This executes plist data, such as
        cache and draw 'bits' data, and gets strip attributes (opaque, alpha,
        double sided flags) and puts them into 'flag'. **/
    u32 flag = 0;
    ExecCnkPlist(&ctx, plist, &flag);

    if ( !flag )
    {
        return;
    }

    /** Depending on the current transparancy mode and the attributes of the
        'plist', draw the opaque and/or transparent strips.

        In future, perhaps all this can be optimized to just one pass, where each
        strip is stored into another buffer and drawn in one go, rather than having
        to loop through the plist multiple times. This isn't that slow though, so
        it's fine for now. **/

    rjCnkBeginDraw();

    switch ( RFRS_GetCnkDrawMode() )
    {
        case RFRS_CNKDRAWMD_ALL:
        {
            if (flag & CNKST_HAS_OPAQUE)
            {
                DrawOpaqueStrip(&ctx, plist, vbuf);
            }

            if (flag & CNKST_HAS_TRANS)
            {
                DrawTransStrip(&ctx, plist, vbuf, flag);
            }

            break;
        }
        case RFRS_CNKDRAWMD_OPAQUE:
        {
            if (flag & CNKST_HAS_OPAQUE)
            {
                DrawOpaqueStrip(&ctx, plist, vbuf);
            }

            break;
        }
        case RFRS_CNKDRAWMD_TRANSPARENT:
        {
            if (flag & CNKST_HAS_TRANS)
            {
                DrawTransStrip(&ctx, plist, vbuf, flag);
            }

            break;
        }
    }

    rjCnkEndDraw();
}
