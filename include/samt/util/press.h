/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/util/press.h'
*
*   Description:
*     Dreamcast 'PRS' file utility header.
*/
#ifndef H_SAMT_UTIL_PRESS
#define H_SAMT_UTIL_PRESS

EXTERN_START

/********************************/
/*  Constants                   */
/********************************/
/****** Return **********************************************************************************/
#define PRS_RET_EOSB                (-1) /* end of source buffer/file                           */
#define PRS_RET_EODB                (-2) /* end of destination buffer                           */
#define PRS_RET_FILE                (-3) /* file couldn't be opened                             */
#define PRS_RET_SIZE                (-4) /* file was larger than 4GB                            */

/********************************/
/*  Prototypes                  */
/********************************/
/****** Expand **********************************************************************************/
/*
*   Description:
*     Expand a pressed file into a destination buffer.
*
*   Notes:
*     - If destination buffer isn't given, the function only calculates the expanded size of
*       the pressed data.
*
*   Parameters:
*     - puSrc       : pressed source file path
*     - pDst        : destination buffer                                             [opt:NULL]
*     - szDst       : maximum size of destination buffer
*
*   Returns:
*     Number of bytes written to the destination buffer; or 'PRS_RET' value on failure.
*/
lsize   mtPrsExpand( const c8* puSrc, void* pDst, usize szDst );

/****** Memory Expand ***************************************************************************/
/*
*   Description:
*     Expand a pressed source buffer into a destination buffer.
*
*   Notes:
*     - If destination buffer isn't given, the function only calculates the expanded size of
*       the pressed data.
* 
*   Parameters:
*     - pSrc        : pressed source buffer
*     - szSrc       : maximum size of source buffer
*     - pDst        : destination buffer                                             [opt:NULL]
*     - szDst       : maximum size of destination buffer
*
*   Returns:
*     Number of bytes written to the destination buffer; or 'PRS_RET' value on failure.
*/
lsize   mtPrsExpandMem( const void* RESTRICT pSrc, usize szSrc, void* RESTRICT pDst, usize szDst );

EXTERN_END

#endif/*H_SAMT_UTIL_PRESS*/
