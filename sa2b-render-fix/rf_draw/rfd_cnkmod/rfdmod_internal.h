/*
*   SA2 Render Fix - '/rf_draw/rfd_cnkmod/rfdmod_internal.h'
*
*   Description:
*     Internal header for CnkModDraw module.
*
*   Contributors:
*     - Shaddatic
*/
#ifndef H_RF_DRAW_CNKMOD_INTERNAL
#define H_RF_DRAW_CNKMOD_INTERNAL

/************************/
/*  External Includes   */
/************************/
/****** Utility *********************************************************************/
#include <samt/util/cnkmdl.h>

/****** Self ************************************************************************/
#include <rf_draw/rfd_internal.h> /* grand parent                                   */
#include <rf_draw/rfd_cnk.h>      /* parent util                                    */

EXTERN_START

/************************/
/*  Prototypes          */
/************************/
/****** Modifier Model **************************************************************/
/*
*   Description:
*     Parse Chunk VList parameters as a modifier model.
*
*   Parameters:
*     - pVList   : pointer to a chunk vlist
*     - njvtxbuf : vertex buffer to push to
*
*   Returns:
*     '0' on success, or '1' if VList type is unparsable
*/
int32_t rjCnkModVList( const Sint32* pVList, RJS_VERTEX_BUF* njvtxbuf );
/*
*   Description:
*     Parse Chunk PList parameters as a modifier model.
*
*   Parameters:
*     - pPList   : pointer to a chunk plist
*     - njvtxbuf : vertex buffer to read from
*/
void    rjCnkModPList( const Sint16* pPList, const RJS_VERTEX_BUF* njvtxbuf );

EXTERN_END

#endif/*H_RF_DRAW_CNKMOD_INTERNAL*/
