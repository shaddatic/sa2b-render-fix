/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>      /* core                                                 */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h> /* ninja                                              */

/****** GX **************************************************************************/
#include <sa2b/gx/gx.h>     /* GX                                                   */

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
GetStripDrawState(CNK_CTX* const pCtx)
{
    const s32 ctxflg = pCtx->flag;

    const Sint16 fst = pCtx->fst;

    /** if current draw mode doesn't match the transparent state of this strip, skip it **/
    const bool fst_ua = (fst & (NJD_FST_UA|NJD_FST_NAT));

    if ( (bool)(ctxflg & CTXFLG_DRAW_TRANS) != fst_ua )
        return false;

    /** if this strip isn't double sided and normal faces aren't being drawn, hide its inverse face **/
    const bool fst_db = (fst & NJD_FST_DB);

    if ( !(ctxflg & CTXFLG_CULL_NORMAL) && !fst_db )
        return false;

    return true;
}

static void
rjCnkPlistSub(CNK_CTX* pCtx, const Sint16* pPList, const void* njvtxbuf)
{
    const Sint16* plist = pPList;
;
    pTexSurface = nullptr;

    for ( ; ; )
    {
        const int type = ((u8*)plist)[0];

        if (type == NJD_ENDOFF)
        {
            /** NJD_ENDOFF **/
            break;
        }

        if (type == NJD_NULLOFF)
        {
            /** NJD_NULLOFF **/

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type < NJD_BITSOFF_MAX)
        {
            /** NJD_BITSOFF **/
            switch (type) {
            case NJD_CB_BA: // CnkBits Blend Alpha

                rjCnkSetBlend(pCtx, plist);
                break;

            case NJD_CB_DA: // CnkBits mipmap 'D' Adjust
                break;

            case NJD_CB_EXP: // CnkBits specular EXPonent
                break;

            case NJD_CB_CP: // CnkBits Cache Polygons
                /** caching is handled in the pre-pass **/
                return;

            case NJD_CB_DP: // CnkBits Draw Polygons

                s32 cache_idx = ((u8*)plist)[1];

                rjCnkPlistSub(pCtx, _nj_cnk_polygon_cache_tbl_[cache_idx], njvtxbuf);
                break;
            }

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type < NJD_TINYOFF_MAX)
        {
            /** NJD_TINYOFF **/
            rjCnkSetTexture(pCtx, plist);

            /** Next offset **/
            plist += 2;
            continue;
        }

        if (type < NJD_MATOFF_MAX)
        {
            /** NJD_MATOFF **/
            rjCnkSetMaterial(pCtx, plist);

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        if (type < NJD_STRIPOFF_MAX)
        {
            /** NJD_STRIPOFF **/
            rjCnkSetStrip(pCtx, plist);

            /** Based on context and strip flags, determine if this strip should be
                drawn. For example, we're drawing only inverse faces but this strip
                isn't double sided. If it shouldn't be drawn, just skip it. **/
            if ( GetStripDrawState(pCtx) )
            {
                switch ( STSW( type ) )
                {
                    case STSW( NJD_CS ):
                    {
                        rjCnkStrip(pCtx, plist, njvtxbuf);
                        break;
                    }
                    case STSW( NJD_CS_UVN ):
                    {
                        rjCnkStripUV(pCtx, plist, njvtxbuf, IS_UVN);
                        break;
                    }
                    case STSW( NJD_CS_UVH ):
                    {
                        rjCnkStripUV(pCtx, plist, njvtxbuf, IS_UVH);
                        break;
                    }
                    case STSW( NJD_CS_VN ):
                    {
                        rjCnkStripVN(pCtx, plist, njvtxbuf);
                        break;
                    }
                    case STSW( NJD_CS_UVN_VN ):
                    {
                        rjCnkStripUVVN(pCtx, plist, njvtxbuf, IS_UVN);
                        break;
                    }
                    case STSW( NJD_CS_UVH_VN ):
                    {
                        rjCnkStripUVVN(pCtx, plist, njvtxbuf, IS_UVH);
                        break;
                    }
                    case STSW( NJD_CS_D8 ):
                    {
                        rjCnkStripD8(pCtx, plist, njvtxbuf);
                        break;
                    }
                    case STSW( NJD_CS_UVN_D8 ):
                    {
                        rjCnkStripUVD8(pCtx, plist, njvtxbuf, IS_UVN);
                        break;
                    }
                    case STSW( NJD_CS_UVH_D8 ):
                    {
                        rjCnkStripUVD8(pCtx, plist, njvtxbuf, IS_UVH);
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
ExecCnkPlist(const Sint16* pPList, u32* pFlag)
{
    const Sint16* plist = pPList;
    int type;

    for ( ; ; )
    {
        type = ((u8*)plist)[0];

        if (type == NJD_ENDOFF)
        {
            /** NJD_ENDOFF **/
            break;
        }

        if (type == NJD_NULLOFF)
        {
            /** NJD_NULLOFF **/

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type < NJD_BITSOFF_MAX)
        {
            /** NJD_BITSOFF **/
            switch (type) {
                s32 cache_idx;

            case NJD_CB_BA: // CnkBits Blend Alpha
                break;

            case NJD_CB_DA: // CnkBits mipmap 'D' Adjust
                break;

            case NJD_CB_EXP: // CnkBits specular EXPonent
                break;

            case NJD_CB_CP: // CnkBits Cache Polygons

                cache_idx = ((u8*)plist)[1];

                _nj_cnk_polygon_cache_tbl_[cache_idx] = &(plist)[1]; // cache next offset

                ++_nj_cnk_polygon_cache_num_;
                return;

            case NJD_CB_DP: // CnkBits Draw Polygons

                cache_idx = ((u8*)plist)[1];

                ExecCnkPlist(_nj_cnk_polygon_cache_tbl_[cache_idx], pFlag);

                --_nj_cnk_polygon_cache_num_;
                break;
            }

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type < NJD_TINYOFF_MAX)
        {
            /** NJD_TINYOFF **/

            /** Next offset **/
            plist += 2;
            continue;
        }

        if (type < NJD_MATOFF_MAX)
        {
            /** NJD_MATOFF **/

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        if (type < NJD_STRIPOFF_MAX)
        {
            /** NJD_STRIPOFF **/
            const Sint16 fst = GetCnkStripFlags(plist);

            if ( fst & (NJD_FST_UA|NJD_FST_NAT) )
            {
                *pFlag |= CNKST_HAS_TRANS;

                if ( fst & (NJD_FST_DB) )
                    *pFlag |= CNKST_HAS_TRANSDB;
            }
            else
                *pFlag |= CNKST_HAS_OPAQUE;

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
            pCtx->flag |= CTXFLG_CULL_NORMAL;
            rjCnkPlistSub(pCtx, plist, njvtxbuf);
            break;
        }
        case RFRS_CULLMD_INVERSE:
        {
            pCtx->flag |= CTXFLG_CULL_INVERSE;
            rjCnkPlistSub(pCtx, plist, njvtxbuf);
            break;
        }
        case RFRS_CULLMD_AUTO:
        case RFRS_CULLMD_NONE:
        {
            pCtx->flag |= (CTXFLG_CULL_NORMAL|CTXFLG_CULL_INVERSE);
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

    pCtx->flag |=  CTXFLG_DRAW_TRANS;
    pCtx->flag &= ~CTXFLG_MASK_CULL;

    /** Draw normal and inverse mesh faces depending on culling mode, pass mode,
        and the existence of double sided strips. If there are no double sided
        strips the back-face never needs to be drawn, so we can entirely skip it. **/
    switch ( RFRS_GetCullMode() )
    {
        case RFRS_CULLMD_NORMAL:
        {
            pCtx->flag |= CTXFLG_CULL_NORMAL;
            rjCnkPlistSub(pCtx, plist, njvtxbuf);
            break;
        }
        case RFRS_CULLMD_INVERSE:
        {
            if ( flag & CNKST_HAS_TRANSDB )
            {
                pCtx->flag |= CTXFLG_CULL_INVERSE;
                rjCnkPlistSub(pCtx, plist, njvtxbuf);
            }
            break;
        }
        case RFRS_CULLMD_AUTO:
        case RFRS_CULLMD_NONE:
        {
            if ( flag & CNKST_HAS_TRANSDB )
            {
                if ( RFRS_GetCnkPassMode() == RFRS_CNKPASSMD_NORMAL )
                {
                    pCtx->flag |= CTXFLG_CULL_INVERSE;
                    rjCnkPlistSub(pCtx, plist, njvtxbuf);
                    pCtx->flag &= ~CTXFLG_CULL_INVERSE;

                    pCtx->flag |= CTXFLG_CULL_NORMAL;
                    rjCnkPlistSub(pCtx, plist, njvtxbuf);
                }
                else // draw inverse order
                {
                    pCtx->flag |= CTXFLG_CULL_NORMAL;
                    rjCnkPlistSub(pCtx, plist, njvtxbuf);
                    pCtx->flag &= ~CTXFLG_CULL_NORMAL;

                    pCtx->flag |= CTXFLG_CULL_INVERSE;
                    rjCnkPlistSub(pCtx, plist, njvtxbuf);
                }
            }
            else
            {
                pCtx->flag |= CTXFLG_CULL_NORMAL;
                rjCnkPlistSub(pCtx, plist, njvtxbuf);
            }
            break;
        }
    }
}

/****** Extern **********************************************************************/
void
rjCnkPList(const Sint16* restrict pPList, const CNK_VERTEX_BUFFER* restrict njvtxbuf)
{
    EXTERN NJS_ARGB rj_ambi_color;

    /** Setup the Chunk context. This is used to track the current draw context of
        the model and it's strips. If the diffuse color is changed, it's applied to
        this context first.
        The 'flag' struct member starts with the function emulation mode, so we
        initiate it to the current function mode value. **/

    CNK_CTX ctx = { .flag = RFRS_GetCnkFuncMode() };

    /** First pass of the Chunk 'plist' data. This executes plist data, such as
        cache and draw 'bits' data, and gets strip attributes (opaque, alpha,
        double sided flags) and puts them into 'flag'. **/
    u32 flag = 0;
    ExecCnkPlist(pPList, &flag);

    /** Depending on the current transparancy mode and the attributes of the
        'plist', draw the opaque and/or transparent strips.

        In future, perhaps all this can be optimized to just one pass, where each
        strip is stored into another buffer and drawn in one go, rather than having
        to loop through the plist multiple times. This isn't that slow though, so
        it's fine for now. **/
    switch ( RFRS_GetCnkDrawMode() )
    {
        case RFRS_CNKDRAWMD_ALL:
        {
            if (flag & CNKST_HAS_OPAQUE)
                DrawOpaqueStrip(&ctx, pPList, njvtxbuf);

            if (flag & CNKST_HAS_TRANS)
                DrawTransStrip(&ctx, pPList, njvtxbuf, flag);

            break;
        }
        case RFRS_CNKDRAWMD_OPAQUE:
        {
            if (flag & CNKST_HAS_OPAQUE)
                DrawOpaqueStrip(&ctx, pPList, njvtxbuf);

            break;
        }
        case RFRS_CNKDRAWMD_TRANSPARENT:
        {
            if (flag & CNKST_HAS_TRANS)
                DrawTransStrip(&ctx, pPList, njvtxbuf, flag);

            break;
        }
    }

    /** End chunk draw **/

    // reset ambient color
    RX_SetChanAmbColor_Direct(rj_ambi_color.r, rj_ambi_color.g, rj_ambi_color.b);

    // unset culling mode
    GX_SetCullMode(GXD_CULLMODE_NONE);
}
