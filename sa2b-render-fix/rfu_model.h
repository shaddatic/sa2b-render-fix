/*
*   SA2 Render Fix - '/rfu_model.h'
*
*   Description:
*     Ninja model utility functions.
*/
#ifndef H_RF_UTIL_MODEL
#define H_RF_UTIL_MODEL

EXTERN_START

/********************************/
/*  Constants                   */
/********************************/
/****** All Index *******************************************************************************/
#define RFD_INDEX_ALL               (-1)

/****** Strip Flags *****************************************************************************/
#define RFD_FST_NONE                (0)
#define RFD_FST_ALL                 (NJD_FST_MASK)

/********************************/
/*  Prototypes                  */
/********************************/
/****** Set Strip Flags *************************************************************************/
/*
*   Description:
*     Change strip flags in a Chunk's polygon list.
*
*   Parameters:
*     - pPlist      : chunk polygon list
*     - ixStrip     : strip index in plist
*     - flagOn      : strip flags to enable
*     - flagOff     : strip flags to disable
*/
void    RFU_CnkSetStripFlag( Sint16* pPlist, s32 ixStrip, u16 flagOn, u16 flagOff );
/*
*   Description:
*     Change strip flags in a Chunk model's polygon list.
*
*   Parameters:
*     - pModel      : chunk model
*     - ixStrip     : strip index in plist
*     - flagOn      : strip flags to enable
*     - flagOff     : strip flags to disable
*/
void    RFU_CnkModelSetStripFlag( NJS_CNK_MODEL* pModel, s32 ixStrip, u16 flagOn, u16 flagOff );
/*
*   Description:
*     Change strip flags in a Chunk object tree.
*
*   Parameters:
*     - pObject     : chunk object header
*     - flagOn      : strip flags to enable
*     - flagOff     : strip flags to disable
*/
void    RFU_CnkObjectSetStripFlag( NJS_CNK_OBJECT* pObject, u16 flagOn, u16 flagOff );

EXTERN_END

#endif/*H_RF_UTIL_MODEL*/
