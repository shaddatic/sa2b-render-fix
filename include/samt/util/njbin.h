/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/util/njbin.h'
*
*   Description:
*     For opening and reading Ninja binary files (.nj, .njd, .njt, .njm, etc).
*/
#ifndef H_SAMT_UTIL_NJBIN
#define H_SAMT_UTIL_NJBIN

EXTERN_START

/********************************/
/*  Constants                   */
/********************************/
/****** Return Code *****************************************************************************/
#define NJBIN_RET_OK                ( 0) /* no error                                            */
#define NJBIN_RET_END               ( 1) /* no error, but last data chunk                       */
// errors
#define NJBIN_RET_EOF               (-1) /* unexpected end of file/memory buffer                */
#define NJBIN_RET_CHUNK             (-2) /* chunk name not expected, might be custom data       */
#define NJBIN_RET_LOST              (-3) /* binary reader got list, can't continue              */

/********************************/
/*  Opaque Types                */
/********************************/
/****** Ninja Binary ****************************************************************************/
typedef struct mt_njbin             mt_njbin; /* njbin reference                                */

/********************************/
/*  Prototypes                  */
/********************************/
/****** Open/Close ******************************************************************************/
/*
*   Description:
*     Open a new Ninja binary file.
*
*   Parameters:
*     - puFile      : file path string
*
*   Returns:
*     Ninja binary reference; or 'nullptr' on failure.
*/
mt_njbin* mtNinjaBinaryOpen( const c8* puFile );
/*
*   Description:
*     Close a Ninja binary file.
*
*   Returns:
*     Ninja binary return code.
*/
i32     mtNinjaBinaryClose( mt_njbin* pNb );

/****** Seek ************************************************************************************/
/*
*   Description:
*     Skip to the next binary chunk.
*
*   Parameters:
*     - pNb         : ninja binary
*
*   Returns:
*     Ninja binary return code.
*/
i32     mtNinjaBinarySkip( mt_njbin* pNb );
/*
*   Description:
*     Check if the end of the binary file has been reached.
*
*   Parameters:
*     - pNb         : ninja binary
*
*   Returns:
*     Ninja binary return code.
*/
i32     mtNinjaBinaryEnd( const mt_njbin* pNb );
/*
*   Description:
*     Reset a Ninja binary back to its start.
*
*   Parameters:
*     - pNb         : ninja binary
*
*   Returns:
*     Ninja binary return code.
*/
i32     mtNinjaBinaryReset( mt_njbin* pNb );

/****** Read ************************************************************************************/
/*
*   Description:
*     Get current binary chunk info.
*
*   Parameters:
*     - pNb         : ninja binary
*     - pOutName    : chunk name out                                                 [opt:NULL]
*     - pOutSize    : chunk size out                                                 [opt:NULL]
*
*   Returns:
*     Ninja binary return code.
*/
i32     mtNinjaBinaryChunk( mt_njbin* pNb, u32* pOutName, usize* pOutSize );
/*
*   Description:
*     Read the current binary chunk into a given buffer, then advance to the next chunk.
*
*   Parameters:
*     - pNb         : ninja binary
*     - pDst        : chunk destination buffer
*     - pOutName    : chunk name out                                                 [opt:NULL]
*     - pOutSize    : chunk size out                                                 [opt:NULL]
*
*   Returns:
*     Ninja binary return code.
*/
i32     mtNinjaBinaryRead( mt_njbin* pNb, void* pDst, u32* pOutName, usize* pOutSize );
/*
*   Description:
*     Allocate a buffer and read the current binary chunk into it, then advance to the next
*   chunk.
*
*   Parameters:
*     - pNb         : ninja binary
*     - pOutName    : chunk name                                                     [opt:NULL]
*     - pOutSize    : chunk size                                                     [opt:NULL]
*
*   Returns:
*     Allocated buffer with binary data; or 'nullptr' on error.
*/
void*   mtNinjaBinaryAlloc( mt_njbin* pNb, u32* pOutName, usize* pOutSize );

/****** Open Memory *****************************************************************************/
/*
*   Description:
*     Open a binary file that's already loaded in memory.
*
*   Notes:
*     - While a memory size of '0' is accepted, it will prevent mt from catching EOF errors
*       early. Only read what you know the binary file contains, and no more.
*     - Managing the input memory after reading is completed is left up to you, not mt.
*
*   Parameters:
*     - pMem        : binary memory buffer
*     - szMem       : binary size                                                       [opt:0]
*
*   Returns:
*     Ninja binary reference; or 'nullptr' on failure.
*/
mt_njbin* mtNinjaBinaryMem( const void* pMem, usize szMem );

/************************************************************************************************/
/*
*   Additional Utils
*
*   Notes:
*     - These are not required for binary reading, and their functions are already done
*       internally. This are only for more advanced use cases, such as loading a binary file
*       manually to use with the 'Mem' open function.
*/
/****** Utility *********************************************************************************/
/*
*   Description:
*     Endian swap a 4 byte value, to convert raw binary chunk names to/from big endian.
*
*   Parameters:
*     - val         : value
*
*   Returns:
*     Endian swapped input value.
*/
u32     mtNinjaBinarySwap( u32 val );
/*
*   Description:
*     Check if chunk name is from a valid binary chunk.
*
*   Parameters:
*     - name        : binary chunk name, eg. 'NJTL'
*
*   Returns:
*     'true' if it is a valid binary chunk name; or 'false' if not.
*/
bool    mtNinjaBinaryCheck( u32 name );

EXTERN_END

#endif/*H_SAMT_UTIL_NJBIN*/
