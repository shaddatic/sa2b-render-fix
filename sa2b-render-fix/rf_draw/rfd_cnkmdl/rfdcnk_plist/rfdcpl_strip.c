/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>      /* core                                                 */
#include <sa2b/memory.h>    /* MemCopy                                              */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h> /* ninja                                              */

/****** GX **************************************************************************/
#include <sa2b/gx/gx.h>     /* GX                                                   */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */
#include <rf_renderstate.h> /* render state                                         */
#include <rf_util.h>        /* utility                                              */
#include <rf_magic.h>       /* magic                                                */

/****** Self ************************************************************************/
#include <rf_draw/rfd_cnkmdl/rfdcnk_plist/rfdcpl_internal.h> /* parent & siblings   */

/************************/
/*  Game References     */
/************************/
/****** Shadow Map Stuff ************************************************************/
#define ShadowMapDrawCount      DATA_REF(u8, 0x01934758)

/************************/
/*  Structures          */
/************************/
/****** GX Buffer *******************************************************************/
typedef struct
{
    NJS_POINT3 pos;
}
GXBUF_POS;

typedef struct
{
    NJS_POINT3 pos;
    NJS_VECTOR norm;
}
GXBUF_POSNORM;

typedef struct
{
    NJS_POINT3 pos;
    Uint32     col;
}
GXBUF_POSCOL;

typedef struct
{
    NJS_POINT3 pos;
    NJS_VECTOR norm;
    Uint32     col;
}
GXBUF_POSNORMCOL;

typedef struct
{
    NJS_POINT3 pos;
    Uint32     col;
    f32        u, v;
}
GXBUF_POSCOLUV;

typedef struct
{
    NJS_POINT3 pos;
    NJS_VECTOR norm;
    f32        u, v;
}
GXBUF_POSNORMUV;

typedef struct
{
    NJS_POINT3 pos;
    NJS_VECTOR norm;
    Uint32     col;
    f32        u, v;
}
GXBUF_POSNORMCOLUV;

/************************/
/*  Source              */
/************************/
/****** Start Triangle Strip ********************************************************/
inline void
CopyLastVertex(const int szStride)
{
    const int vtxbuf  = _gx_vtx_buf_base_;
    const int lastvtx = _gx_vtx_buf_offset_ - szStride;

    MemCopy((char*)vtxbuf + _gx_vtx_buf_offset_, (char*)vtxbuf + lastvtx, szStride);

    _gx_vtx_buf_offset_ += szStride;
}

inline void
CopyCopyVertex(const int stride)
{
    /** If the copy pointer isn't null,  **/
    if ( _gx_vtx_buf_offset_cpy_ )
    {
        const uintptr_t ptr = (_gx_vtx_buf_base_ + _gx_vtx_buf_offset_cpy_);

        MemCopy((void*)ptr , (void*)(ptr + stride), stride);
    }
}

static void
StartTriStrip(int16_t nbVtx)
{
    int  nb_vertex;
    bool str_inv;

    /** If the vertex count is negative, that means the incomming strip is inverted
        and needs to be flipped back. So, invert the count and set the inverted flag **/
    if ( nbVtx < 0 )
    {
        nb_vertex = -nbVtx;
        str_inv   =  true;
    }
    else
    {
        nb_vertex = nbVtx;
        str_inv   = false;
    }

    const int stride = VertexDeclInfo->StrideSize;
    const int nb_buf = _gx_nb_vtx_;

    /** If no verteces are currently in the buffer, then the buffer is empty. So,
        setup buffer attributes for drawing a triangle strip **/
    if ( !nb_buf )
    {
        _gx_prim_type_     = GXD_PRIM_TRISTRIP;
        _gx_vtx_buf_start_ = _gx_vtx_buf_offset_;
        _gx_cull_          = str_inv;

        /** If the first strip is inverted, then save the position of the buffer so
            the next vertex can be copied into it; creating a degen triangle **/
        if (str_inv)
        {
            _gx_vtx_buf_offset_cpy_ = _gx_vtx_buf_offset_;
            _gx_vtx_buf_offset_    += stride;
            _gx_nb_vtx_             = nb_vertex + 1; // +1 for copy
        }
        else
        {
            _gx_vtx_buf_offset_cpy_ = 0;
            _gx_nb_vtx_             = nb_vertex;
        }

        return;
    }

    /** If the number of verteces in the buffer is odd & the current strip isn't
        itself inverted, copy an additional vertex onto the buffer **/
    if ( (bool)(nb_buf & 0x01) != str_inv )
    {
        CopyLastVertex(stride);
        ++nb_vertex;
    }

    CopyLastVertex(stride);
    ++nb_vertex;

    /** Set the copy pointer for degen creation and update buffer variables **/
    _gx_vtx_buf_offset_cpy_ = _gx_vtx_buf_offset_;
    _gx_cull_               = str_inv;
    _gx_vtx_buf_offset_    += stride;
    _gx_nb_vtx_             = nb_buf + nb_vertex + 1; // +1 for copy
}

static void
StartTriList(int16_t nbVtx)
{
    int  nb_vertex;
    bool str_inv;

    /** If the vertex count is negative, that means the incomming strip is inverted
    and needs to be flipped back. So, invert the count and set the inverted flag **/
    if ( nbVtx < 0 )
    {
        nb_vertex = (-nbVtx - 2) * 3;
        str_inv   =  true;
    }
    else
    {
        nb_vertex = (nbVtx - 2) * 3;
        str_inv   = false;
    }

    const int stride = VertexDeclInfo->StrideSize;
    const int nb_buf = _gx_nb_vtx_;

    /** If no verteces are currently in the buffer, then the buffer is empty. So,
        setup buffer attributes for drawing a triangle strip **/
    if ( !nb_buf )
    {
        _gx_prim_type_          = GXD_PRIM_TRIANGLE;
        _gx_vtx_buf_start_      = _gx_vtx_buf_offset_;
        _gx_cull_               = str_inv;
        _gx_vtx_buf_offset_cpy_ = 0;
        _gx_nb_vtx_             = nb_vertex;

        return;
    }

    /** Update buffer variables **/
    _gx_cull_            = str_inv;
    _gx_nb_vtx_          = nb_buf + nb_vertex;
}

/****** Vertex Buffer ***************************************************************/
inline void*
GetVertexBuffer(void)
{
    return (void*)(_gx_vtx_buf_base_ + _gx_vtx_buf_offset_);
}

/****** Copy Vertex Attr ************************************************************/
inline void
CopyPos(NJS_POINT3* const pd, const NJS_POINT3* const ps)
{
    *pd = *ps;
}

inline void
CopyNorm(NJS_VECTOR* const nd, const NJS_VECTOR* const ns, const bool bInv)
{
    if ( !bInv )
    {
        nd->x = ns->x;
        nd->y = ns->y;
        nd->z = ns->z;
    }
    else // inverted
    {
        nd->x = -ns->x;
        nd->y = -ns->y;
        nd->z = -ns->z;
    }
}

inline void
CopyCol(Uint32* const cd, const Uint32* const cs)
{
    *cd = *cs;
}

inline void
CopyUV(Float* const uvd, const Sint16* const uvs, const f32 fmul)
{
    uvd[0] = (f32)(uvs[0]) * fmul;
}

inline void
CalcFlatNormal(const NJS_POINT3* const p0, const NJS_POINT3* const p1, const NJS_POINT3* const p2, NJS_VECTOR* const nd)
{
    NJS_VECTOR v1, v2;

    v1.x = p1->x - p0->x;
    v1.y = p1->y - p0->y;
    v1.z = p1->z - p0->z;

    v2.x = p2->x - p0->x;
    v2.y = p2->y - p0->y;
    v2.z = p2->z - p0->z;

    njOuterProduct2(&v1, &v2, nd);
    njUnitVector(nd);
}

/****** Ctx Check *******************************************************************/
inline bool
CtxDrawNrmFaces(const CNK_CTX* const pCtx)
{
    return (pCtx->flag & CTXFLG_CULL_NORMAL);
}

inline bool
CtxDrawInvFaces(const CNK_CTX* const pCtx)
{
    return (pCtx->flag & CTXFLG_CULL_INVERSE && pCtx->fst & NJD_FST_DB);
}

/****** Push Strip ******************************************************************/
inline void
PushStripUV_PosNorm(const CNK_STRIP_UV* const pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* const njvtxbuf, const bool bInv)
{
    const CNK_STRIP_UV* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        StartTriStrip( bInv ? -p_str->len : p_str->len );

        GXBUF_POSNORM* p_buf = GetVertexBuffer();

        const int nb_vtx = ABS(p_str->len);

        for (int vidx = 0; vidx < nb_vtx; ++vidx)
        {
            const int idx = p_str->d[vidx].i;

            const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[idx];

            CopyPos (&p_buf->pos , &p_vtx->pos       );
            CopyNorm(&p_buf->norm, &p_vtx->norm, bInv);

            ++p_buf;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * nb_vtx;

        CopyCopyVertex(sizeof(*p_buf));

        p_str = NEXT_STRIP(p_str, nb_vtx, ufo);
    }
}

inline void
PushStripUV_PosNorm_FL(const CNK_STRIP_UV* const pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* const njvtxbuf, const bool bInv)
{
    const CNK_STRIP_UV* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        StartTriList( bInv ? -p_str->len : p_str->len );

        GXBUF_POSNORM* p_buf = GetVertexBuffer();

        const int nb_vtx = ABS(p_str->len);

        const int nb_tri = (nb_vtx - 2);

        bool inv_strip = bInv ? !(p_str->len < 0) : (p_str->len < 0);

        for (int tidx = 0; tidx < nb_tri; ++tidx)
        {
            const NJS_POINT3* p_vtxpos[3];

            /** vertex index and vertex increment for de-strip-ing the triangle **/
            int vidx, vinc;

            VIDX_START(vidx, vinc, inv_strip);

            for (int k = 0; k < 3; ++k)
            {
                const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[ p_str->d[tidx+vidx].i ];

                p_vtxpos[k] = &p_vtx->pos;

                CopyPos(&p_buf->pos, &p_vtx->pos);

                vidx += vinc;

                p_buf++;
            }

            /** Calculate flat normal for triangle and apply it to the triangle **/
            NJS_VECTOR norm;
            CalcFlatNormal(p_vtxpos[0], p_vtxpos[1], p_vtxpos[2], &norm);

            p_buf[-3].norm = norm;
            p_buf[-2].norm = norm;
            p_buf[-1].norm = norm;

            /** Swap strip inverse mode for next tri **/
            inv_strip = !inv_strip;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * (nb_tri * 3);

        p_str = NEXT_STRIP(p_str, nb_vtx, ufo);
    }
}

inline void
PushStripUV_PosNormUV(const CNK_STRIP_UV* const pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* const njvtxbuf, const f32 uvMul, const bool bInv)
{
    const CNK_STRIP_UV* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        StartTriStrip( bInv ? -p_str->len : p_str->len );

        GXBUF_POSNORMUV* p_buf = GetVertexBuffer();

        const int nb_vtx = ABS(p_str->len);

        for (int vidx = 0; vidx < nb_vtx; ++vidx)
        {
            const int idx = p_str->d[vidx].i;

            const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[idx];

            CopyPos (&p_buf->pos , &p_vtx->pos         );
            CopyNorm(&p_buf->norm, &p_vtx->norm  , bInv);

            CopyUV(&p_buf->u, &p_str->d[vidx].u, uvMul);
            CopyUV(&p_buf->v, &p_str->d[vidx].v, uvMul);

            ++p_buf;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * nb_vtx;

        CopyCopyVertex(sizeof(*p_buf));

        p_str = NEXT_STRIP(p_str, nb_vtx, ufo);
    }
}

inline void
PushStripUV_PosNormUV_FL(const CNK_STRIP_UV* const pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* const njvtxbuf, const f32 uvMul, const bool bInv)
{
    const CNK_STRIP_UV* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        StartTriList( bInv ? -p_str->len : p_str->len );

        GXBUF_POSNORMUV* p_buf = GetVertexBuffer();

        const int nb_vtx = ABS(p_str->len);

        const int nb_tri = (nb_vtx - 2);

        bool inv_strip = bInv ? !(p_str->len < 0) : (p_str->len < 0);

        for (int tidx = 0; tidx < nb_tri; ++tidx)
        {
            const NJS_POINT3* p_vtxpos[3];

            /** vertex index and vertex increment for de-strip-ing the triangle **/
            int vidx, vinc;

            VIDX_START(vidx, vinc, inv_strip);

            for (int k = 0; k < 3; ++k)
            {
                const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[ p_str->d[tidx+vidx].i ];

                p_vtxpos[k] = &p_vtx->pos;

                CopyPos(&p_buf->pos, &p_vtx->pos);

                CopyUV( &p_buf->u  , &p_str->d[tidx+vidx].u, uvMul);
                CopyUV( &p_buf->v  , &p_str->d[tidx+vidx].v, uvMul);

                vidx += vinc;

                p_buf++;
            }

            /** Calculate flat normal for triangle and apply it to the triangle **/
            NJS_VECTOR norm;
            CalcFlatNormal(p_vtxpos[0], p_vtxpos[1], p_vtxpos[2], &norm);

            p_buf[-3].norm = norm;
            p_buf[-2].norm = norm;
            p_buf[-1].norm = norm;

            /** Swap strip inverse mode for next tri **/
            inv_strip = !inv_strip;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * (nb_tri * 3);

        p_str = NEXT_STRIP(p_str, nb_vtx, ufo);
    }
}

inline void
PushStripUV_PosColUV(const CNK_STRIP_UV* const pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* const njvtxbuf, const f32 uvMul, const bool bInv)
{
    const CNK_STRIP_UV* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        StartTriStrip( bInv ? -p_str->len : p_str->len );

        GXBUF_POSCOLUV* p_buf = GetVertexBuffer();

        const int nb_vtx = ABS(p_str->len);

        for (int vidx = 0; vidx < nb_vtx; ++vidx)
        {
            const int idx = p_str->d[vidx].i;

            const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[idx];

            CopyPos(&p_buf->pos, &p_vtx->pos  );
            CopyCol(&p_buf->col, &p_vtx->color);

            CopyUV(&p_buf->u, &p_str->d[vidx].u, uvMul);
            CopyUV(&p_buf->v, &p_str->d[vidx].v, uvMul);

            ++p_buf;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * nb_vtx;

        CopyCopyVertex(sizeof(*p_buf));

        p_str = NEXT_STRIP(p_str, nb_vtx, ufo);
    }
}

inline void
PushStrip_PosNorm(const CNK_STRIP* const pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* const njvtxbuf, const bool bInv)
{
    const CNK_STRIP* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        StartTriStrip( bInv ? -p_str->len : p_str->len );

        GXBUF_POSNORM* p_buf = GetVertexBuffer();

        const int nb_vtx = ABS(p_str->len);

        for (int vidx = 0; vidx < nb_vtx; ++vidx)
        {
            const int idx = p_str->d[vidx].i;

            const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[idx];

            CopyPos( &p_buf->pos , &p_vtx->pos       );
            CopyNorm(&p_buf->norm, &p_vtx->norm, bInv);

            ++p_buf;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * nb_vtx;

        CopyCopyVertex(sizeof(*p_buf));

        p_str = NEXT_STRIP(p_str, nb_vtx, ufo);
    }
}

inline void
PushStrip_PosNorm_FL(const CNK_STRIP* const pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* const njvtxbuf, const bool bInv)
{
    const CNK_STRIP* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        StartTriList( bInv ? -p_str->len : p_str->len );

        GXBUF_POSNORM* p_buf = GetVertexBuffer();

        const int nb_strip = ABS(p_str->len);

        const int nb_tri = (nb_strip - 2);

        bool inv_strip = bInv ? !(p_str->len < 0) : (p_str->len < 0);

        for (int tidx = 0; tidx < nb_tri; ++tidx)
        {
            const NJS_POINT3* p_vtxpos[3];

            /** vertex index and vertex increment for de-strip-ing the triangle **/
            int vidx, vinc;

            VIDX_START(vidx, vinc, inv_strip);

            for (int k = 0; k < 3; ++k)
            {
                const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[ p_str->d[tidx+vidx].i ];

                p_vtxpos[k] = &p_vtx->pos;

                CopyPos(&p_buf->pos, &p_vtx->pos);

                vidx += vinc;

                p_buf++;
            }

            /** Calculate flat normal for triangle and apply it to the triangle **/
            NJS_VECTOR norm;
            CalcFlatNormal(p_vtxpos[0], p_vtxpos[1], p_vtxpos[2], &norm);

            p_buf[-3].norm = norm;
            p_buf[-2].norm = norm;
            p_buf[-1].norm = norm;

            /** Swap strip inverse mode for next tri **/
            inv_strip = !inv_strip;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * (nb_tri * 3);

        p_str = NEXT_STRIP(p_str, nb_strip, ufo);
    }
}

inline void
PushStrip_PosCol(const CNK_STRIP* const pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* const njvtxbuf, const bool bInv)
{
    const CNK_STRIP* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        StartTriStrip( bInv ? -p_str->len : p_str->len );

        GXBUF_POSCOL* p_buf = GetVertexBuffer();

        const int nb_strip = ABS(p_str->len);

        for (int j = 0; j < nb_strip; ++j)
        {
            const int idx = p_str->d[j].i;

            const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[idx];

            CopyPos(&p_buf->pos, &p_vtx->pos  );
            CopyCol(&p_buf->col, &p_vtx->color);

            ++p_buf;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * nb_strip;

        CopyCopyVertex(sizeof(*p_buf));

        p_str = NEXT_STRIP(p_str, nb_strip, ufo);
    }
}

/****** Static **********************************************************************/
static void
CnkSetupNoTexStrip(CNK_CTX* const pCtx)
{
    const f32 smf = ShadowMapDrawCount ? (f32)(ShadowMapDrawCount + 1) : 0.f;

    RF_MagicSetShaderConstantFloat(MAGIC_SHADER_VERTEX, 155, smf, 1);
    RF_MagicSetShaderConstantFloat(MAGIC_SHADER_PIXEL ,   0, 4.f, 1);

    /** Cnk Context **/

    /** No texture to draw. So, add notex flag **/
    pCtx->flag |= CTXFLG_STRIP_NOTEX;

    rjCnkContext(pCtx);
}

static void
CnkSetupTexStrip(CNK_CTX* const pCtx)
{
    const f32 smf = ShadowMapDrawCount ? (f32)(ShadowMapDrawCount + 1) : 1.f;

    RF_MagicSetShaderConstantFloat(MAGIC_SHADER_VERTEX, 155, smf, 1);
    RF_MagicSetShaderConstantFloat(MAGIC_SHADER_PIXEL ,   0, 0.f, 1);

    f32* str36 = *(float**)(0x01A557BC);

    str36[378] = 0.f;

    RF_MagicSetShaderConstantMatrix(MAGIC_SHADER_VERTEX, 160, &str36[250]);

    GX_SetTexMtx(&_unit_matrix_44_, GXD_TEXMTX0, GXD_TG_TEXCOORD0);

    /** Cnk Context **/
    pCtx->flag &= ~CTXFLG_STRIP_NOTEX;

    rjCnkContext(pCtx);
}

static void
CnkSetupEnvStrip(CNK_CTX* const pCtx)
{
    const f32 smf = ShadowMapDrawCount ? (f32)(ShadowMapDrawCount + 1) : 1.f;

    RF_MagicSetShaderConstantFloat(MAGIC_SHADER_VERTEX, 155, smf, 1);
    RF_MagicSetShaderConstantFloat(MAGIC_SHADER_PIXEL ,   0, 0.f, 1);

    f32* str36 = *(float**)(0x01A557BC);

    str36[378] = 0.f;

    RF_MagicSetShaderConstantMatrix(MAGIC_SHADER_VERTEX, 160, &str36[250]);

    GX_SetTexMtx(&_env_matrix_44_, GXD_TEXMTX0, GXD_TG_NRM);

    /** Cnk Context **/
    pCtx->flag &= ~CTXFLG_STRIP_NOTEX;

    rjCnkContext(pCtx);
}

/****** Extern **********************************************************************/
void
rjCnkStrip(CNK_CTX* const pCtx, const Sint16* plist, const CNK_VERTEX_BUFFER* njvtxbuf)
{
    const int count = plist[2];

    const int nb_stcnk = count & ~NJD_UFO_MASK;
    const int ufo      = count >> NJD_UFO_SHIFT;

    CNK_STRIP* const p_str = (void*)&plist[3];

    if (pCtx->fst & NJD_FST_ENV)
    {
        CnkSetupEnvStrip(pCtx);

        VertexDeclInfo = VertexDecl_PosNorm;

        ___NOTE("We should figure out what Dreamcast does in cases where something is env mapped but lacks any vertex normals");

        if (pCtx->fst & NJD_FST_FL)
        {
            if (CtxDrawNrmFaces(pCtx)) PushStrip_PosNorm_FL(p_str, nb_stcnk, ufo, njvtxbuf, false);
            if (CtxDrawInvFaces(pCtx)) PushStrip_PosNorm_FL(p_str, nb_stcnk, ufo, njvtxbuf, true);
        }
        else
        {
            if (CtxDrawNrmFaces(pCtx)) PushStrip_PosNorm(p_str, nb_stcnk, ufo, njvtxbuf, false);
            if (CtxDrawInvFaces(pCtx)) PushStrip_PosNorm(p_str, nb_stcnk, ufo, njvtxbuf, true);
        }
    }
    else // No tex
    {
        CnkSetupNoTexStrip(pCtx);

        if (_nj_cnk_vtx_attrs_ & CNKVTX_HAS_VCOLORS)
        {
            VertexDeclInfo = VertexDecl_PosCol;

            if (CtxDrawNrmFaces(pCtx)) PushStrip_PosCol(p_str, nb_stcnk, ufo, njvtxbuf, false);
            if (CtxDrawInvFaces(pCtx)) PushStrip_PosCol(p_str, nb_stcnk, ufo, njvtxbuf, true);
        }
        else
        {
            VertexDeclInfo = VertexDecl_PosNorm;

            if (pCtx->fst & NJD_FST_FL)
            {
                if (CtxDrawNrmFaces(pCtx)) PushStrip_PosNorm_FL(p_str, nb_stcnk, ufo, njvtxbuf, false);
                if (CtxDrawInvFaces(pCtx)) PushStrip_PosNorm_FL(p_str, nb_stcnk, ufo, njvtxbuf, true);
            }
            else
            {
                if (CtxDrawNrmFaces(pCtx)) PushStrip_PosNorm(p_str, nb_stcnk, ufo, njvtxbuf, false);
                if (CtxDrawInvFaces(pCtx)) PushStrip_PosNorm(p_str, nb_stcnk, ufo, njvtxbuf, true);
            }
        }
    }

    GX_End(); // Draw buffered vertex list
}

void
rjCnkStripUV(CNK_CTX* const pCtx, const Sint16* plist, const CNK_VERTEX_BUFFER* njvtxbuf, bool uvh)
{
    const int count = plist[2];

    const int nb_stcnk = count & ~NJD_UFO_MASK;
    const int ufo      = count >> NJD_UFO_SHIFT;

    const f32 uv_mul = GET_UV_MUL(uvh);

    CNK_STRIP_UV* const p_str = (void*)&plist[3];

    if (pCtx->fst & NJD_FST_ENV)
    {
        CnkSetupEnvStrip(pCtx);

        VertexDeclInfo = VertexDecl_PosNorm;

        ___NOTE("We should figure out what Dreamcast does in cases where something is env mapped but lacks any vertex normals");

        if (pCtx->fst & NJD_FST_FL)
        {
            if (CtxDrawNrmFaces(pCtx)) PushStripUV_PosNorm_FL(p_str, nb_stcnk, ufo, njvtxbuf, false);
            if (CtxDrawInvFaces(pCtx)) PushStripUV_PosNorm_FL(p_str, nb_stcnk, ufo, njvtxbuf, true);
        }
        else
        {
            if (CtxDrawNrmFaces(pCtx)) PushStripUV_PosNorm(p_str, nb_stcnk, ufo, njvtxbuf, false);
            if (CtxDrawInvFaces(pCtx)) PushStripUV_PosNorm(p_str, nb_stcnk, ufo, njvtxbuf, true);
        }
    }
    else
    {
        CnkSetupTexStrip(pCtx);

        if (_nj_cnk_vtx_attrs_ & CNKVTX_HAS_VCOLORS)
        {
            VertexDeclInfo = VertexDecl_PosColUV;

            if (CtxDrawNrmFaces(pCtx)) PushStripUV_PosColUV(p_str, nb_stcnk, ufo, njvtxbuf, uv_mul, false);
            if (CtxDrawInvFaces(pCtx)) PushStripUV_PosColUV(p_str, nb_stcnk, ufo, njvtxbuf, uv_mul, true);
        }
        else
        {
            VertexDeclInfo = VertexDecl_PosNormUV;

            if (pCtx->fst & NJD_FST_FL)
            {
                if (CtxDrawNrmFaces(pCtx)) PushStripUV_PosNormUV_FL(p_str, nb_stcnk, ufo, njvtxbuf, uv_mul, false);
                if (CtxDrawInvFaces(pCtx)) PushStripUV_PosNormUV_FL(p_str, nb_stcnk, ufo, njvtxbuf, uv_mul, true);
            }
            else
            {
                if (CtxDrawNrmFaces(pCtx)) PushStripUV_PosNormUV(p_str, nb_stcnk, ufo, njvtxbuf, uv_mul, false);
                if (CtxDrawInvFaces(pCtx)) PushStripUV_PosNormUV(p_str, nb_stcnk, ufo, njvtxbuf, uv_mul, true);
            }
        }
    }

    GX_End(); // Draw buffered vertex list
}

void
rjCnkStripVN(CNK_CTX* const pCtx, const Sint16* plist, const CNK_VERTEX_BUFFER* njvtxbuf)
{

}

void
rjCnkStripUVVN(CNK_CTX* const pCtx, const Sint16* plist, const CNK_VERTEX_BUFFER* njvtxbuf, bool uvh)
{

}

void
rjCnkStripD8(CNK_CTX* const pCtx, const Sint16* plist, const CNK_VERTEX_BUFFER* njvtxbuf)
{
    
}

void
rjCnkStripUVD8(CNK_CTX* const pCtx, const Sint16* plist, const CNK_VERTEX_BUFFER* njvtxbuf, bool uvh)
{

}
