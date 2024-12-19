/*
*   SA2 Render Fix - '/rf_draw/rfd_cnkmdl/rfdcnk_plist/rfdcpl_internal.h'
*
*   Description:
*     Common header for Chunk draw plist.
*
*   Contributors:
*     - Shaddatic
*/
#ifndef H_RF_DRAW_CNKMDL_PLIST_COMMON
#define H_RF_DRAW_CNKMDL_PLIST_COMMON

EXTERN_START

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
/*  Inline Funcs        */
/************************/
/****** Vertex Buffer ***************************************************************/
/*
*   Description:
*     Get current vertex buffer head position pointer.
*/
static inline void*
GetVertexBuffer(void)
{
    return (void*)(_gx_vtx_buf_base_ + _gx_vtx_buf_offset_);
}
/*
*   Description:
*     Copy the previous vertex to the current head position of the vertex buffer.
*
*   Parameters:
*     szStride      : vertex stride size in bytes
*/
static inline void
CopyLastVertex(const int szStride)
{
    const int vtxbuf  = _gx_vtx_buf_base_;
    const int lastvtx = _gx_vtx_buf_offset_ - szStride;

    MemCopy((char*)vtxbuf + _gx_vtx_buf_offset_, (char*)vtxbuf + lastvtx, szStride);

    _gx_vtx_buf_offset_ += szStride;
}
/*
*   Description:
*     Copy the stored copy vertex pointer to the vertex in front of the copy
*   pointer. This is used for creating degen triangles in strips.
*
*   Parameters:
*     szStride      : vertex stride size in bytes
*/
static inline void
CopyCopyVertex(const int stride)
{
    /** If the copy pointer isn't null,  **/
    if ( _gx_vtx_buf_offset_cpy_ )
    {
        const uintptr_t ptr = (_gx_vtx_buf_base_ + _gx_vtx_buf_offset_cpy_);

        MemCopy((void*)ptr , (void*)(ptr + stride), stride);
    }
}

/****** Copy Vertex Attr ************************************************************/
/*
*   Description:
*     Copy a point3.
*
*   Parameters:
*     pd            : point3 destination
*     ps            : point3 source
*/
static inline void
CopyPos(NJS_POINT3* const pd, const NJS_POINT3* const ps)
{
    *pd = *ps;
}
/*
*   Description:
*     Copy a normal vector.
*
*   Parameters:
*     nd            : normal destination
*     ns            : normal source
*/
static inline void
CopyNorm(NJS_VECTOR* const nd, const NJS_VECTOR* const ns)
{
    nd->x = ns->x;
    nd->y = ns->y;
    nd->z = ns->z;
}
/*
*   Description:
*     Copy and invert normal vector.
*
*   Parameters:
*     nd            : normal destination
*     ns            : normal source
*/
static inline void
CopyNormInverse(NJS_VECTOR* const nd, const NJS_VECTOR* const ns)
{
    nd->x = -ns->x;
    nd->y = -ns->y;
    nd->z = -ns->z;
}
/*
*   Description:
*     Copy a 32bit color.
*
*   Parameters:
*     cd            : color destination
*     cs            : color source
*/
static inline void
CopyCol(Uint32* const cd, const Uint32* const cs)
{
    *cd = *cs;
}
/*
*   Description:
*     Copy a Chunk UV (0~256/1024) to a float UV (0~1).
*
*   Parameters:
*     uvd           : uv destination
*     uvs           : uv source
*     fmul          : multiplication value to convert Chunk UV to float UV
*/
static inline void
CopyUV(Float* const uvd, const Sint16* const uvs, const f32 fmul)
{
    uvd[0] = (f32)(uvs[0]) * fmul;
    uvd[1] = (f32)(uvs[1]) * fmul;
}
/*
*   Description:
*     Calculate the flat normal of a triangle using its verteces.
*
*   Parameters:
*     p0, p1, p2    : triangle verteces
*     nd            : normal destination
*/
static inline void
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

/************************/
/*  Prototypes          */
/************************/
/****** Start Triange Strip *********************************************************/
/*
*   Description:
*     Setup vertex buffer for triangle strips.
*
*   Parameters:
*     nbVtx         : number of Chunk strip verteces being processed.
*/
void    CnkStartTriStrip( int16_t nbVtx );
/*
*   Description:
*     Setup vertex buffer for inverted triangle strips.
*
*   Parameters:
*     nbVtx         : number of Chunk strip verteces being processed.
*/
void    CnkStartTriStripInverse( int16_t nbVtx );

/****** Start Triange List **********************************************************/
/*
*   Description:
*     Setup vertex buffer for triangle lists.
*
*   Parameters:
*     nbVtx         : number of Chunk strip verteces being processed.
*/
void    CnkStartTriList( int16_t nbVtx );
/*
*   Description:
*     Setup vertex buffer for inverted triangle lists.
*
*   Parameters:
*     nbVtx         : number of Chunk strip verteces being processed.
*/
void    CnkStartTriListInverse( int16_t nbVtx );

/****** Begin Strip *****************************************************************/
/*
*   Description:
*     Setup shaders and render context for a textureless Chunk strip.
*
*   Parameters:
*     - pCtx        : current chunk context
*/
void    CnkSetupNoTexStrip( CNK_CTX* pCtx );
/*
*   Description:
*     Setup shaders and render context for a textured Chunk strip.
*
*   Parameters:
*     - pCtx        : current chunk context
*/
void    CnkSetupTexStrip( CNK_CTX* pCtx );
/*
*   Description:
*     Setup shaders and render context for an environment mapped Chunk strip.
*
*   Parameters:
*     - pCtx        : current chunk context
*/
void    CnkSetupEnvStrip( CNK_CTX* pCtx );

EXTERN_END

#endif/*H_RF_DRAW_CNKMDL_PLIST_COMMON*/
