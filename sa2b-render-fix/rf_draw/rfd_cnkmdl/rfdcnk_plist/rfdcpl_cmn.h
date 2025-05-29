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
/*  Prototypes          */
/************************/
/****** Begin Strip *****************************************************************/
/*
*   Description:
*     Setup shaders and render context for a textureless Chunk strip.
*
*   Parameters:
*     - pCtx        : current chunk context
*/
void    rjCnkStartVertexNonTex( CNK_CTX* pCtx );
/*
*   Description:
*     Setup shaders and render context for a textured Chunk strip.
*
*   Parameters:
*     - pCtx        : current chunk context
*/
void    rjCnkStartVertexTex( CNK_CTX* pCtx );

void
rjCnkStartVertexTexSpec(CNK_CTX* pCtx);

/*
*   Description:
*     Setup render context for specular draw.
*
*   Parameters:
*     - pCtx        : current chunk context
*/
void    rjCnkStartVertexSpec( CNK_CTX* pCtx );

/****** End/Draw Vertex *************************************************************/
/*
*   Description:
*     Draw buffered polygons.
*/
void    rjCnkEndVertex( void );

EXTERN_END

#endif/*H_RF_DRAW_CNKMDL_PLIST_COMMON*/
