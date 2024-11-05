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

/****** Self ************************************************************************/
#include <rf_draw/rfd_cnkmdl/rfdcnk_internal.h>              /* parent & siblings   */
#include <rf_draw/rfd_cnkmdl/rfdcnk_plist/rfdcpl_internal.h> /* self                */

/************************/
/*  Source Constants    */
/************************/
/****** Cnk Offsets *****************************************************************/
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

    /** if this strip isn't double sided, hide its inverse face **/
    const bool fst_db = (fst & NJD_FST_DB);

    if ( (ctxflg & CTXFLG_MASK_CULL) == CTXFLG_CULL_INVERSE && !fst_db )
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
                        rjCnkStripUV(pCtx, plist, njvtxbuf, false);
                        break;
                    }
                    case STSW( NJD_CS_UVH ):
                    {
                        rjCnkStripUV(pCtx, plist, njvtxbuf, true);
                        break;
                    }
                    case STSW( NJD_CS_VN ):
                    {
                        rjCnkStripVN(pCtx, plist, njvtxbuf);
                        break;
                    }
                    case STSW( NJD_CS_UVN_VN ):
                    {
                        rjCnkStripUVVN(pCtx, plist, njvtxbuf, false);
                        break;
                    }
                    case STSW( NJD_CS_UVH_VN ):
                    {
                        rjCnkStripUVVN(pCtx, plist, njvtxbuf, true);
                        break;
                    }
                    case STSW( NJD_CS_D8 ):
                    {
                        rjCnkStripD8(pCtx, plist, njvtxbuf);
                        break;
                    }
                    case STSW( NJD_CS_UVN_D8 ):
                    {
                        rjCnkStripUVD8(pCtx, plist, njvtxbuf, false);
                        break;
                    }
                    case STSW( NJD_CS_UVH_D8 ):
                    {
                        rjCnkStripUVD8(pCtx, plist, njvtxbuf, true);
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
        OutputFormat("Type error pre-pass %i", type);
        break;
    }
}

static void
DrawOpaqueStrip(CNK_CTX* pCtx, const Sint16* plist, const void* njvtxbuf)
{
//  pCtx->flag &= ~CTXFLG_DRAW_TRANS;  // implied
//  pCtx->flag &= ~CTXFLG_CULL_MASK;   // ^

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
DrawTransStrip(CNK_CTX* pCtx, const Sint16* plist, const void* njvtxbuf, const s32 flag)
{
    pCtx->flag |=  CTXFLG_DRAW_TRANS;
    pCtx->flag &= ~CTXFLG_MASK_CULL;

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
rjCnkPList(const Sint16* const pPList, const CNK_VERTEX_BUFFER* const njvtxbuf)
{
    CNK_CTX ctx = {0};

    /** Set culling mode **/
    GX_SetCullMode(GXD_CULLMODE_CW);

    u32 flag = 0;
    ExecCnkPlist(pPList, &flag);

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

    /** Unset culling mode **/
    GX_SetCullMode(GXD_CULLMODE_NONE);
}
