/*
*   Sonic Adventure Mod Tools (SA2B) - '/string.h'
*
*   Description:
*       Manipulating, copying, duplicating, & converting strings of ASCII, UTF-8, &
*   UTF-16 code-pages.
*       All 'utf8' params are ASCII code-page safe.
*
*   Contributors:
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SAMT_STRING
#define H_SAMT_STRING

EXTERN_START

/************************/
/*  Constants           */
/************************/
/****** Size/Count Definitions ******************************************************/
#define STR_NOMAX          (0xFFFFFFFF) /* no maximum, auto-determine sz/nb         */

/************************/
/*  UTF-8/ASCII Funcs   */
/************************/
/****** String Query ****************************************************************/
/*
*   Description:
*     Calculate if two strings exactly match
*
*   Parameters:
*     - str1    : string 1
*     - str2    : string 2
*     - maxSize : maximum size, in bytes, of 'str1' & 'str2'
*
*   Returns:
*     If 'str1' & 'str2' exactly match, or match until 'maxSize'
*/
bool    StringMatch( const utf8* str1, const utf8* str2, size_t maxSize );
/*
*   Description:
*     Search for an instance of 'key' inside 'str'
*
*   Parameters:
*     - str     : string to search
*     - key     : string to search for, not including NULL terminator
*     - maxSize : maximum size, in bytes, of 'str'
*
*   Returns:
*     An index to the first instance of 'key' inside 'str'
*/
size_t  StringSearch( const utf8* str, const utf8* key, size_t maxSize );
/*
*   Description:
*     Calculate the size of a string in bytes, including the NULL terminator
*
*   Parameters:
*     - str     : string to calculate size of
*     - maxSize : maximum size, in bytes, of 'str'
*
*   Returns:
*     The size of the string in bytes, or 'maxSize' if NULL was not found
*/
size_t  StringSize( const utf8* str, size_t maxSize );
/*
*   Description:
*     Calculate the length of a string in characters. No checks are made for if
*   'maxSize' lies in the middle of a multi-byte character
*
*   Parameters:
*     - str     : string to calculate length of
*     - maxSize : maximum size, in bytes, of 'str'
*
*   Returns:
*     The length of the string in characters until 'maxSize' is reached
*/
size_t  StringLength( const utf8* str, size_t maxSize );

/****** String Copy *****************************************************************/
/*
*   Description:
*     Create a duplicate of a string
*
*   Parameters:
*     - str     : string to duplicate
*     - maxSize : maximum size, in bytes, of 'str'
*
*   Returns:
*     A duplicate of 'str' up to 'maxSize' allocated by 'malloc()'
*/
utf8*   StringDupe( const utf8* str, size_t maxSize );
/*
*   Description:
*     Copy 'strSrc' into 'strDst'
*
*   Parameters:
*     - strDst  : string buffer to copy to
*     - strSrc  : string to copy
*     - maxSize : maximum size, in bytes, of 'strDst' & 'strSrc'
*
*   Returns:
*     'strDst' argument
*/
utf8*   StringCopy( utf8* strDst, const utf8* strSrc, size_t maxSize );

/************************/
/*  UTF-16 Funcs        */
/************************/
/****** String Query ****************************************************************/
/*
*   Description:
*     Calculate if two strings exactly match
*
*   Parameters:
*     - str1    : string 1
*     - str2    : string 2
*     - maxSize : maximum size, in 2 byte units, of 'str1' & 'str2'
*
*   Returns:
*     If string 1 & 2 exactly match
*/
bool    StringMatchW( const wchar_t* str1, const wchar_t* str2, size_t maxSize );
/*
*   Description:
*     Search for an instance of 'key' inside 'str'
*
*   Parameters:
*     - str     : string to search
*     - key     : string to search for, not including NULL terminator
*     - maxSize : maximum size, in 2 byte units, of 'str'
*
*   Returns:
*     An index to the first instance of 'key' inside 'str'
*/
size_t  StringSearchW( const wchar_t* str, const wchar_t* key, size_t maxSize );
/*
*   Description:
*     Calculate the size of a string in 2 byte units, including the NULL terminator
*
*   Parameters:
*     - str     : string to calculate size of
*     - maxSize : maximum size, in 2 byte units, of 'str'
*
*   Returns:
*     The size of the string in 2 byte units, or 'maxSize' if NULL was not found
*/
size_t  StringSizeW( const wchar_t* str, size_t maxSize );
/*
*   Description:
*     Calculate the length of a string in characters. No checks are made for if
*   'maxSize' lies in the middle of a multi-byte character
*
*   Parameters:
*     - str     : string to calculate length of
*     - maxSize : maximum size, in 2 byte units, of 'str'
*
*   Returns:
*     The length of the string in characters until 'maxSize' is reached
*/
size_t  StringLengthW( const wchar_t* str, size_t maxSize );

/****** String Copy *****************************************************************/
/*
*   Description:
*     Create a duplicate of a string
*
*   Parameters:
*     - str     : string to duplicate
*     - maxSize : maximum size, in 2 byte units, of 'str'
*
*   Returns:
*     A duplicate of 'str' up to 'maxSize' allocated by 'malloc()'
*/
wchar_t* StringDupeW( const wchar_t* str, size_t maxSize );
/*
*   Description:
*     Copy 'strSrc' into 'strDst'
*
*   Parameters:
*     - strDst  : string buffer to copy to
*     - strSrc  : string to copy
*     - maxSize : maximum size, in 2 byte units, of 'strDst' & 'strSrc'
*
*   Returns:
*     'strDst' argument
*/
wchar_t* StringCopyW( wchar_t* strDst, const wchar_t* strSrc, size_t maxSize );

/************************/
/*  Code-Page Convert   */
/************************/
/****** To UTF-8 ********************************************************************/
/*
*   Description:
*     Create a duplicate of a UTF-16 string in the UTF-8 codepage
*
*   Parameters:
*     - str     : string to duplicate
*
*   Returns:
*     A duplicate of 'str' in UTF-8 allocated by 'malloc()'
*/
utf8*   StringDupeTo8( const wchar_t* str );
/*
*   Description:
*     Copy 'strSrc' into 'strDst'
*
*   Parameters:
*     - strDst  : string buffer to copy to
*     - strSrc  : string to copy
*     - maxSize : maximum size, in bytes, of 'strDst'
*
*   Returns:
*     The size, in bytes, of the new string in 'strDst'
*/
size_t  StringCopyTo8( utf8* strDst, const wchar_t* strSrc, size_t maxSize );

/****** To UTF-16 *******************************************************************/
/*
*   Description:
*     Create a duplicate of a UTF-8 string in the UTF-16 codepage
*
*   Parameters:
*     - str     : string to duplicate
*
*   Returns:
*     A duplicate of 'str' in UTF-16 allocated by 'malloc()'
*/
wchar_t* StringDupeTo16( const utf8* str );
/*
*   Description:
*     Copy 'strSrc' into 'strDst'
*
*   Parameters:
*     - strDst  : string buffer to copy to
*     - strSrc  : string to copy
*     - maxSize : maximum size, in 2 byte units, of 'strDst'
*
*   Returns:
*     The size, in two byte units, of the new string in 'strDst'
*/
size_t   StringCopyTo16( wchar_t* strDst, const utf8* strSrc, size_t maxSize );

/************************/
/*  File Path           */
/************************/
/*
*   Description:
*     Modify a path to point to its parent directory by inserting a '\0' at the last
*   path delimiter ('/' or '\')
*
*   Parameters:
*     - strPath : string path buffer to modify
*     - maxSize : maximum size, in bytes, of 'strPath'
*/
void    StringPathToParent( utf8* strPath, size_t maxSize );

EXTERN_END

#endif/*H_SAMT_STRING*/
