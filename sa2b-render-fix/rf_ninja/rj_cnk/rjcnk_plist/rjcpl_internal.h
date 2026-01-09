/*
*   SA2 Render Fix - '/rf_draw/rfd_cnkmdl/rfdcnk_plist/rfdcpl_internal.h'
*
*   Description:
*     Internal header for CnkDraw module.
*
*   Contributors:
*     - Shaddatic
*/
#ifndef H_RF_DRAW_CNKMDL_PLIST_INTERNAL
#define H_RF_DRAW_CNKMDL_PLIST_INTERNAL

/************************/
/*  External Headers    */
/************************/
/****** Self ************************************************************************/
#include <rf_ninja/rj_cnk/rjcnk_internal.h> /* grand-parent                         */

EXTERN_START

/************************/
/*  Prototypes          */
/************************/
/****** Strip ***********************************************************************/
/*
*   Description:
*     Parse and draw Chunk strip chunk.
*
*   Parameters:
*     - pCtx        : current chunk draw context
*     - striph      : strip chunk header
*     - vbuf        : current vertex buffer
*/
void    rjCnkStrip( const RJS_CNK_STRIP* restrict strip, const RJS_VERTEX_BUF* restrict vbuf );
/*
*   Description:
*     Parse and draw Chunk UV strip chunk.
*
*   Parameters:
*     - pCtx        : current chunk draw context
*     - striph      : strip chunk header
*     - vbuf        : current vertex buffer
*     - uvh         : use HD UVs
*/
void    rjCnkStripUV( const RJS_CNK_STRIP* restrict strip, const RJS_VERTEX_BUF* restrict vbuf, i32 uvh );
/*
*   Description:
*     Parse and draw Chunk VN strip chunk.
*
*   Parameters:
*     - pCtx        : current chunk draw context
*     - striph      : strip chunk header
*     - vbuf        : current vertex buffer
*/
void    rjCnkStripVN( const RJS_CNK_STRIP* restrict strip, const RJS_VERTEX_BUF* restrict vbuf );
/*
*   Description:
*     Parse and draw Chunk UVVN strip chunk.
*
*   Parameters:
*     - pCtx        : current chunk draw context
*     - striph      : strip chunk header
*     - vbuf        : current vertex buffer
*     - uvh         : use HD UVs
*/
void    rjCnkStripUVVN( const RJS_CNK_STRIP* restrict strip, const RJS_VERTEX_BUF* restrict vbuf, bool uvh );
/*
*   Description:
*     Parse and draw Chunk D8 strip chunk.
*
*   Parameters:
*     - pCtx        : current chunk draw context
*     - striph      : strip chunk header
*     - vbuf        : current vertex buffer
*/
void    rjCnkStripD8( const RJS_CNK_STRIP* restrict strip, const RJS_VERTEX_BUF* restrict vbuf );
/*
*   Description:
*     Parse and draw Chunk UVD8 strip chunk.
*
*   Parameters:
*     - pCtx        : current chunk draw context
*     - striph      : strip chunk header
*     - vbuf        : current vertex buffer
*     - uvh         : use HD UVs
*/
void    rjCnkStripUVD8( const RJS_CNK_STRIP* restrict strip, const RJS_VERTEX_BUF* restrict vbuf, bool uvh );

EXTERN_END

#endif/*H_RF_DRAW_CNKMDL_PLIST_INTERNAL*/
