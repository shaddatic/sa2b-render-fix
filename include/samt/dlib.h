/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/dlib.h'
*
*   Description:
*     For opening, closing, and getting symbols from dynamic libraries
*/
#ifndef H_SAMT_DLIB
#define H_SAMT_DLIB

EXTERN_START

/********************************/
/*  Opaque Types                */
/********************************/
/****** Lib Handle ******************************************************************************/
typedef struct mt_dlib              mt_dlib; /* library handle                                  */

/********************************/
/*  Constants                   */
/********************************/
/****** Open Flag *******************************************************************************/
#define DLIB_NF                     (0x0000'0000) /* no additional load flags                   */
#define DLIB_NOLOAD                 (0x8000'0000) /* don't load library, get open instance      */

/********************************/
/*  Structures                  */
/********************************/
/****** Lib Symbols *****************************************************************************/
typedef struct mt_dlib_sym
{
    const void* ppDst;              /* pointer to write symbol address to                       */
    const c7*   pcSym;              /* name of library symbol                                   */
}
mt_dlib_sym;

/********************************/
/*  Prototypes                  */
/********************************/
/****** Open/Close Library **********************************************************************/
/*
*   Description:
*     Open a dynamic library file with either a direct path or just the file name of the
*   library. if the name is used, the local game path is searched first followed by the system
*   files.
*
*   Notes:
*     - If a path is given, the file extension is required and the 'NOLOAD' flag will not
*       function correctly. Otherwise, the extension is appended automatically. 
*
*   Examples:
*     - mtDlOpen( "lib", DLIB_NF );            // open library 'lib.dll'
*     - mtDlOpen( "lib", DLIB_NOLOAD );        // get already open library 'lib.dll'
*     - mtDlOpen( "./path/lib.dll", DLIB_NF ); // load library at specific path
*
*   Parameters:
*     - puDlib      : path/name of library
*     - flag        : open flags, 'DLIB' or system dependant
*
*   Returns:
*     Library handle; or 'nullptr' if the file doesn't exist/library is not open.
*/
mt_dlib* mtDlOpen( const c8* puDlib, u32 flag );
/*
*   Description:
*     Close a dynamic library.
*
*   Notes:
*     - This will release all static data and functions in the DLL also, so care should be
*       taken to not reference any released memory addresses. Dynamically allocated addresses
*       will remain, but will now be unreleaseable.
*
*   Parameters:
*     - pDlib       : library handle
*/
void    mtDlClose( mt_dlib* pDlib );

/****** Library Symbols *************************************************************************/
/*
*   Description:
*     Get a symbol from an open library.
*
*   Parameters:
*     - pDlib       : library handle
*     - pcSymbol    : symbol name
*
*   Returns:
*     Address of symbol in memory; or 'nullptr' on failure.
*/
void*   mtDlSymbol( const mt_dlib* RESTRICT pDlib, const c7* RESTRICT pcSymbol );
/*
*   Description:
*     Get a list of symbols from an open library.
*
*   Parameters:
*     - pDlib       : library handle
*     - pSymList    : null-terminated symbol list
*
*   Returns:
*     Number of symbols successfully found.
*/
isize   mtDlSymList( const mt_dlib* RESTRICT pDlib, mt_dlib_sym* RESTRICT pSymList );

EXTERN_END

#endif/*H_SAMT_DLIB*/
