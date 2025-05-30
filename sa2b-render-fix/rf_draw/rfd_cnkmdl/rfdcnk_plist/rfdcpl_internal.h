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
#include <rf_gx.h>

/****** Self ************************************************************************/
#include <rf_draw/rfd_cnkmdl/rfdcnk_internal.h> /* grand-parent                     */

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
*     - plist       : strip chunk header
*     - njvtxbuf    : current vertex buffer
*/
void    rjCnkStrip( CNK_CTX* restrict pCtx, const Sint16* restrict plist, const CNK_VERTEX_BUFFER* restrict njvtxbuf );
/*
*   Description:
*     Parse and draw Chunk UV strip chunk.
*
*   Parameters:
*     - pCtx        : current chunk draw context
*     - plist       : strip chunk header
*     - njvtxbuf    : current vertex buffer
*     - uvh         : use HD UVs
*/
void    rjCnkStripUV( CNK_CTX* restrict pCtx, const Sint16* restrict plist, const CNK_VERTEX_BUFFER* restrict njvtxbuf, s32 uvh );
/*
*   Description:
*     Parse and draw Chunk VN strip chunk.
*
*   Parameters:
*     - pCtx        : current chunk draw context
*     - plist       : strip chunk header
*     - njvtxbuf    : current vertex buffer
*/
void    rjCnkStripVN( CNK_CTX* restrict pCtx, const Sint16* restrict plist, const CNK_VERTEX_BUFFER* restrict njvtxbuf );
/*
*   Description:
*     Parse and draw Chunk UVVN strip chunk.
*
*   Parameters:
*     - pCtx        : current chunk draw context
*     - plist       : strip chunk header
*     - njvtxbuf    : current vertex buffer
*     - uvh         : use HD UVs
*/
void    rjCnkStripUVVN( CNK_CTX* restrict pCtx, const Sint16* restrict plist, const CNK_VERTEX_BUFFER* restrict njvtxbuf, bool uvh );
/*
*   Description:
*     Parse and draw Chunk D8 strip chunk.
*
*   Parameters:
*     - pCtx        : current chunk draw context
*     - plist       : strip chunk header
*     - njvtxbuf    : current vertex buffer
*/
void    rjCnkStripD8( CNK_CTX* restrict pCtx, const Sint16* restrict plist, const CNK_VERTEX_BUFFER* restrict njvtxbuf );
/*
*   Description:
*     Parse and draw Chunk UVD8 strip chunk.
*
*   Parameters:
*     - pCtx        : current chunk draw context
*     - plist       : strip chunk header
*     - njvtxbuf    : current vertex buffer
*     - uvh         : use HD UVs
*/
void    rjCnkStripUVD8( CNK_CTX* restrict pCtx, const Sint16* restrict plist, const CNK_VERTEX_BUFFER* restrict njvtxbuf, bool uvh );

EXTERN_END

#endif/*H_RF_DRAW_CNKMDL_PLIST_INTERNAL*/
