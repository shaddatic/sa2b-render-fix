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
    NJS_VECTOR nrm;
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
    NJS_VECTOR nrm;
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
    NJS_VECTOR nrm;
    f32        u, v;
}
GXBUF_POSNORMUV;

typedef struct
{
    NJS_POINT3 pos;
    NJS_VECTOR nrm;
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
