/*
*   SA2 Render Fix - '/rfu_njbin.h'
*
*   Description:
*     Ninja binary utility functions.
*/
#ifndef H_RF_UTIL_NJBIN
#define H_RF_UTIL_NJBIN

EXTERN_START

/********************************/
/*  Opaque Types                */
/********************************/
/****** Ninja Binary ****************************************************************************/
typedef struct mt_njbin             mt_njbin; /* ninja binary                                   */

/********************************/
/*  Prototypes                  */
/********************************/
/****** Get Binary Chunk ************************************************************************/
/*
*   Description:
*     Find and read a specific chunk from an open Ninja Binary file.
*
*   Parameters:
*     - pNb         : ninja binary
*     - fnCheck     : chunk callback
*       - name      : chunk name input
*       + return    : if this chunk should be read in
*
*   Returns:
*     Memory with read in binary chunk; or 'nullptr' on failure.
*/
void*   RFU_NinjaBinaryRead( mt_njbin* pNb, bool(*fnCheck)(u32 name) );
/*
*   Description:
*     Open and read a specific data chunk from a Ninja binary file.
*
*   Parameters:
*     - fpath       : path to ninja binary
*     - fnNameCheck : chunk select function
*       - name      : chunk name input
*       + return    : if this chunk should be read
*
*   Returns:
*     New buffer with selected binary chunk; or 'nullptr' on failure.
*/
void*   RFU_NinjaBinaryGet( const c8* fpath, bool(*fnNameCheck)(u32 name) );

EXTERN_END

#endif/*H_RF_UTIL_NJBIN*/
