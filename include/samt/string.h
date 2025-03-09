/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/string.h'
*
*   Description:
*     String and path utility functions for ASCII/UTF-8 and UTF-16 (wchar_t).
*
*   Notes:
*     - All UTF-8 params are ASCII code-page safe, but do not support any extended
*       ASCII code pages.
*
*     - String parameter/variable names often use prefixes, here's a rundown:
*       - 'pc' refers to ASCII string pointers
*       - 'pu' refers to UTF-8 string pointers (or ASCII as mentioned)
*       - 'pw' refers to UTF-16 string pointers
*
*   Disambiguations:
*     - Size            : size of something in bytes                 (s32[5] == 20)
*     - Length          : length of something in 'units'             (s32[5] ==  5)
*     - Code point      : a variably sized, actionable character     ('漢字' ==  2) ('nj' == 2)
*     - Code unit       : a fixed sized chunk of a whole code point  ('漢字' ==  8) ('nj' == 2)
*/
#ifndef H_SAMT_STRING
#define H_SAMT_STRING

EXTERN_START

/************************/
/*  Constants           */
/************************/
/****** Size/Count Definitions ******************************************************/
#define STR_NOMAX           (0xFFFFFFFF) /* no maximum, auto-determine sz/nb        */
#define STR_NOINDEX         (0xFFFFFFFF) /* no string index                         */
#define STR_AUTOLEN         (0x00000000) /* auto-calculate length for append        */

/****** String Escape Flags *********************************************************/
#define STR_ESC_NOFLAG          (0)     /* no additional flags                      */

#define STR_ESC_ESCAPE          (1<<0)  /* \ -> \\  OR  \\ -> \                     */
#define STR_ESC_DBLQUOTE        (1<<1)  /* " -> \"  OR  \" -> "                     */
#define STR_ESC_SGLQUOTE        (1<<2)  /* ' -> \'  OR  \' -> '                     */

#define STR_ESC_ALL             (STR_ESC_ESCAPE|STR_ESC_DBLQUOTE|STR_ESC_SGLQUOTE)

/************************/
/*  Prototypes          */
/************************/
/************************************************************************************/
/*
*   UTF-8/ASCII Funcs
*/
/****** String Query ****************************************************************/
/*
*   Description:
*     Compare if two strings exactly match.
*
*   Parameters:
*     - puStr1      : string 1
*     - puStr2      : string 2
*     - lenMax      : maximum length of both strings, in code units
*
*   Returns:
*     'true' if both strings exactly match, or match until 'lenMax' is reached; or
*   'false' if not.
*/
bool    mtStrMatch( const utf8* puStr1, const utf8* puStr2, size_t lenMax );
/*
*   Description:
*     Search for an instance of a string inside another.
*
*   Parameters:
*     - puStr       : string to search through
*     - puKey       : string to search for
*     - lenMax      : maximum length of 'puStr', in code units
*
*   Returns:
*     An index to the first instance of the key inside the search string; or
*   'STR_NOINDEX' if no instance was found.
*/
size_t  mtStrSearch( const utf8* puStr, const utf8* puKey, size_t lenMax );
/*
*   Description:
*     Get the size of a string in bytes, including the terminator.
*
*   Notes:
*     - Example strings and their return values:
*       - "str"   -> '4'
*       - "漢字"   -> '8'
* 
*   Parameters:
*     - puStr       : string to get the size of
*     - lenMax      : maximum length of the string, in code units
*
*   Returns:
*     The size of the string in bytes; or size up to 'lenMax' if it's reached.
*/
size_t  mtStrSize( const utf8* puStr, size_t lenMax );
/*
*   Description:
*     Get the length of a string in code units, including the terminator.
*
*   Notes:
*     - Example strings and their return values:
*       - "str"   -> '4'
*       - "漢字"   -> '8'
* 
*   Parameters:
*     - puStr       : string to get the size of
*     - lenMax      : maximum length of the string, in code units
*
*   Returns:
*     The length of the string in code units; or 'lenMax' if it's reached.
*/
size_t  mtStrLength( const utf8* puStr, size_t lenMax );
/*
*   Description:
*     Get the length of a string in usable code points, including the terminator.
*   
*   Notes:
*     - Example strings and their return values:
*       - "str"   -> '4'
*       - "漢字"   -> '3'
*     - No checks are made for if 'lenMax' lies in the middle of a multi-byte code
*       point. This may cause a code point to be counted but incomplete.
*
*   Parameters:
*     - puStr       : string to get the length of
*     - lenMax      : maximum length of the string, in code units
*
*   Returns:
*     The number of individual code points in the string; or the number of code
*   points before 'lenMax'.
*/
size_t  mtStrCodeLength( const utf8* puStr, size_t lenMax );

/****** String Copy *****************************************************************/
/*
*   Description:
*     Duplicate a string.
*
*   Notes:
*     - No checks are made for if 'lenMax' lies in the middle of a multi-byte code
*       point. This may cause a code point to be incomplete.
*
*   Parameters:
*     - puStr       : string to duplicate
*     - lenMax      : maximum length of the string
*
*   Returns:
*     A duplicate of the given string, allocated by 'mtMemAlloc'.
*/
utf8*   mtStrDupe( const utf8* puStr, size_t lenMax );
/*
*   Description:
*     Copy a string.
*
*   Notes:
*     - A terminator is inserted into the last unit if 'lenMax' is reached.
*     - No checks are made for if 'lenMax' lies in the middle of a multi-byte code
*       point. This may cause a code point to be incomplete.
*
*   Parameters:
*     - puDst       : string buffer to copy to
*     - puSrc       : string to copy
*     - lenMax      : maximum length of both strings
*
*   Returns:
*     The length of the copied string in code units, up to 'lenMax'.
*/
size_t  mtStrCopy( utf8* puDst, const utf8* puSrc, size_t lenMax );

/****** String Append ***************************************************************/
/*
*   Description:
*     Append a set string onto the end of a buffer string.
*
*   Notes:
*     - 'lenMax' specifically refers to 'puDst' and the total length of the string
*       buffer. 'puApp' *must* be null terminated.
*     - No checks are made for if 'lenMax' lies in the middle of a multi-byte code
*       point. This may cause a code point to be incomplete.
*
*   Examples:
*     - mtStrAppend( pu_buf, STR_AUTOLEN, "append me", ARYLEN(pu_buf) ); // single append
*     - {
*         size_t len; // multi-append using return value (faster)
*
*         len = mtStrAppend( pu_buf, STR_AUTOLEN, "app1", sz_buf );
*         len = mtStrAppend( pu_buf, len        , "app2", sz_buf );
*         len = mtStrAppend( pu_buf, len        , "app3", sz_buf );
*         ...
*       }
*
*   Parameters:
*     - puDst       : string buffer to append to
*     - lenDst      : current length of 'puDst'             [optional: STR_AUTOLEN]
*     - puApp       : string to append
*     - lenMax      : maximum length of 'puDst', in code units
*
*   Returns:
*     New length of 'puDst' after append.
*/
size_t  mtStrAppend( utf8* puDst, size_t lenDst, const utf8* puApp, size_t lenMax );

/****** String Case *****************************************************************/
/*
*   Description:
*     Cast a string to upper case, with an optional source string.
*
*   Notes:
*     - If 'puOptSrc' isn't given, the destination string will also act as the
*       source string.
*
*   Parameters:
*     - puDst       : destination string buffer
*     - puOptSrc    : source string                             [optional: nullptr]
*     - lenMax      : maximum length of 'puDst' and 'puOptSrc'
*
*   Returns:
*     The length of the destination string in code units, up to 'lenMax'.
*/
size_t  mtStrToUpper( utf8* puDst, const utf8* puOptSrc, size_t lenMax );
/*
*   Description:
*     Cast a string to lower case, with an optional source string.
*
*   Notes:
*     - If 'puOptSrc' isn't given, the destination string will also act as the
*       source string.
*
*   Parameters:
*     - puDst       : destination string buffer
*     - puOptSrc    : source string                             [optional: nullptr]
*     - lenMax      : maximum length of 'puDst' and 'puOptSrc'
*
*   Returns:
*     The length of the destination string in code units, up to 'lenMax'.
*/
size_t  mtStrToLower( utf8* puDst, const utf8* puOptSrc, size_t lenMax );

/****** String Escape ***************************************************************/
/*
*   Description:
*     Get the length of a string after inserting escape characters.
*
*   Parameters:
*     - puStr       : string to get the length
*     - lenMax      : maximum length of 'puStr', in code units
*     - flag        : additional escape sequence flags
*
*   Returns:
*     Length of string after inserting escape characters.
*/
size_t  mtStrEscapeLength( const utf8* puStr, const size_t lenMax, s32 flag );
/*
*   Description:
*     Get the length of a string after resolving escape characters.
*
*   Parameters:
*     - puStr       : string to get the length
*     - lenMax      : maximum length of 'puStr', in code units
*     - flag        : additional escape sequence flags
*
*   Returns:
*     Length of string after resolving escape characters.
*/
size_t  mtStrUnescapeLength( const utf8* puStr, const size_t lenMax, s32 flag );
/*
*   Description:
*     Insert literal escape sequences into a string.
*
*   Notes:
*     - '\a' -> { '\\', 'a' }
*     - '\b' -> { '\\', 'b' }
*     - '\t' -> { '\\', 't' }
*     - '\n' -> { '\\', 'n' }
*     - '\v' -> { '\\', 'v' }
*     - '\f' -> { '\\', 'f' }
*     - '\r' -> { '\\', 'r' }
*     - '\"' -> { '\\', '\"' } // optional
*     - '\'' -> { '\\', '\'' } // optional
*     - '\\' -> { '\\', '\\' } // optional
*
*   Parameters:
*     - puDst       : destination buffer
*     - puSrc       : source string
*     - lenMax      : maximum length of 'puDst', in code units
*     - flag        : additional escape sequence flags
*
*   Returns:
*     Length of 'puDst' after inserting escape sequences.
*/
size_t  mtStrEscape( utf8* puDst, const utf8* puSrc, const size_t lenMax, s32 flag );
/*
*   Description:
*     Resolve literal escape sequences from a string.
*
*   Notes:
*     - { '\\', 'a' }  -> '\a' 
*     - { '\\', 'b' }  -> '\b' 
*     - { '\\', 't' }  -> '\t' 
*     - { '\\', 'n' }  -> '\n' 
*     - { '\\', 'v' }  -> '\v' 
*     - { '\\', 'f' }  -> '\f' 
*     - { '\\', 'r' }  -> '\r' 
*     - { '\\', '\"' } -> '\"'  // optional
*     - { '\\', '\'' } -> '\''  // optional
*     - { '\\', '\\' } -> '\\'  // optional
*
*   Parameters:
*     - puDst       : destination buffer
*     - puSrc       : source string
*     - lenMax      : maximum length of 'puDst', in code units
*     - flag        : additional escape sequence flags
*
*   Returns:
*     Length of 'puDst' after resolving escape sequences.
*/
size_t  mtStrUnescape( utf8* puDst, const utf8* puSrc, const size_t lenMax, s32 flag );

/************************************************************************************/
/*
*   UTF-16 Funcs
*/
/****** String Query ****************************************************************/
/*
*   Description:
*     Compare if two strings exactly match.
*
*   Parameters:
*     - pwStr1      : string 1
*     - pwStr2      : string 2
*     - lenMax      : maximum length of both strings, in code units
*
*   Returns:
*     'true' if both strings exactly match, or match until 'lenMax' is reached; or
*   'false' if not.
*/
bool    mtStrMatchW( const wchar_t* pwStr1, const wchar_t* pwStr2, size_t lenMax );
/*
*   Description:
*     Search for an instance of a string inside another.
*
*   Parameters:
*     - pwStr       : string to search through
*     - pwKey       : string to search for
*     - lenMax      : maximum length of 'pwStr', in code units
*
*   Returns:
*     An index to the first instance of the key inside the search string; or
*   'STR_NOINDEX' if no instance was found.
*/
size_t  mtStrSearchW( const wchar_t* pwStr, const wchar_t* pwKey, size_t lenMax );
/*
*   Description:
*     Get the size of a string in bytes, including the terminator.
*
*   Notes:
*     - Example strings and their return values:
*       - L"str"   -> '8'
*       - L"漢字"   -> '6'
* 
*   Parameters:
*     - pwStr       : string to get the size of
*     - lenMax      : maximum length of the string, in code units
*
*   Returns:
*     The size of the string in bytes; or size up to 'lenMax' if it's reached.
*/
size_t  mtStrSizeW( const wchar_t* pwStr, size_t lenMax );
/*
*   Description:
*     Get the length of a string in code units, including the terminator.
*
*   Notes:
*     - Example strings and their return values:
*       - "str"   -> '4'
*       - "漢字"   -> '3'
* 
*   Parameters:
*     - puStr       : string to get the size of
*     - lenMax      : maximum length of the string, in code units
*
*   Returns:
*     The length of the string in code units; or 'lenMax' if it's reached.
*/
size_t  mtStrLengthW( const wchar_t* pwStr, size_t lenMax );
/*
*   Description:
*     Get the length of a string in usable code points, including the terminator.
*
*   Notes:
*     - Example strings and their return values:
*       - L"str"   -> '4'
*       - L"漢字"   -> '3'
*
*   Parameters:
*     - pwStr       : string to get the length of
*     - lenMax      : maximum size, in bytes, of 'str'
*
*   Returns:
*     The number of individual code points in the string; or the number of code
*   points before 'lenMax'.
*/
size_t  mtStrCodeLengthW( const wchar_t* pwStr, size_t lenMax );

/****** String Copy *****************************************************************/
/*
*   Description:
*     Duplicate a string.
*
*   Notes:
*     - No checks are made for if 'lenMax' lies in the middle of a multi-byte code
*       point. This may cause a code point to be incomplete.
*
*   Parameters:
*     - pwStr       : string to duplicate
*     - lenMax      : maximum length of the string
*
*   Returns:
*     A duplicate of the given string, allocated by 'mtMemAlloc'.
*/
wchar_t* mtStrDupeW( const wchar_t* pwStr, size_t lenMax );
/*
*   Description:
*     Copy a string.
*
*   Notes:
*     - A terminator is inserted into the last unit if 'lenMax' is reached.
*     - No checks are made for if 'lenMax' lies in the middle of a multi-byte code
*       point. This may cause a code point to be incomplete.
*
*   Parameters:
*     - pwDst       : string buffer to copy to
*     - pwSrc       : string to copy
*     - lenMax      : maximum length of both strings
*
*   Returns:
*     The length of the copied string in code units.
*/
size_t  mtStrCopyW( wchar_t* pwDst, const wchar_t* pwSrc, size_t lenMax );

/****** String Append ***************************************************************/
/*
*   Description:
*     Append a set string onto the end of a buffer string.
*
*   Notes:
*     - 'lenMax' specifically refers to 'pwDst' and the total length of the string
*       buffer. 'puApp' *must* be null terminated.
*     - No checks are made for if 'lenMax' lies in the middle of a multi-byte code
*       point. This may cause a code point to be incomplete.
*
*   Examples:
*     - mtStrAppendW( pw_buf, STR_AUTOLEN, L"append me", ARYLEN(pw_buf) ); // single append
*     - {
*         size_t len; // multi-append using return value (faster)
*
*         len = mtStrAppendW( pw_buf, STR_AUTOLEN, L"app1", sz_buf );
*         len = mtStrAppendW( pw_buf, len        , L"app2", sz_buf );
*         len = mtStrAppendW( pw_buf, len        , L"app3", sz_buf );
*         ...
*       }
*
*   Parameters:
*     - pwDst       : string buffer to append to
*     - lenDst      : current length of 'pwDst'             [optional: STR_AUTOLEN]
*     - pwApp       : string to append
*     - lenMax      : maximum length of 'pwDst', in code units
*
*   Returns:
*     New length of 'pwDst' after append.
*/
size_t  mtStrAppendW( wchar_t* pwDst, size_t lenDst, const wchar_t* pwApp, size_t lenMax );

/************************************************************************************/
/*
*   Code-Page Conversion
*/
/****** To UTF-8 ********************************************************************/
/*
*   Description:
*     Duplicate a UTF-16 string to the UTF-8 codepage.
*
*   Parameters:
*     - pwStr       : UTF-16 string to duplicate
*
*   Returns:
*     A duplicate of the given string in UTF-8, allocated by 'mtMemAlloc'.
*/
utf8*   mtStrDupeToU( const wchar_t* pwStr );
/*
*   Description:
*     Copy a UTF-16 string to the UTF-8 codepage.
*
*   Parameters:
*     - puDst       : UTF-8 string buffer to copy to
*     - pwSrc       : UTF-16 string to copy
*     - maxSize     : maximum length of both strings, in code units
*
*   Returns:
*     The length of the copied string, in code units.
*/
size_t  mtStrCopyToU( utf8* puDst, const wchar_t* pwSrc, size_t lenMax );

/****** To UTF-16 *******************************************************************/
/*
*   Description:
*     Duplicate a UTF-8 string to the UTF-16 codepage.
*
*   Parameters:
*     - puStr       : UTF-8 string to duplicate
*
*   Returns:
*     A duplicate of the given string in UTF-16, allocated by 'mtMemAlloc'.
*/
wchar_t* mtStrDupeToW( const utf8* puStr );
/*
*   Description:
*     Copy a UTF-16 string to the UTF-8 codepage.
*
*   Parameters:
*     - pwDst       : UTF-16 string buffer to copy to
*     - puSrc       : UTF-8 string to copy
*     - maxSize     : maximum length of both strings, in code units
*
*   Returns:
*     The length of the copied string, in code units.
*/
size_t   mtStrCopyToW( wchar_t* pwDst, const utf8* puSrc, size_t lenMax );

/************************************************************************************/
/*
*   File Path Strings
*/
/****** String Query ****************************************************************/
/*
*   Description:
*     Compare if two strings exactly match, taking into account OS path string
*   logic.
*
*   Parameters:
*     - puPath1     : string path 1
*     - puPath2     : string path 2
*     - lenMax      : maximum size of both strings, in code units
*
*   Returns:
*     'true' if both paths exactly match, or match until 'lenMax' is reached; or
*   'false' if not.
*/
bool    mtPathMatch( const utf8* puPath1, const utf8* puPath2, size_t lenMax );
/*
*   Description:
*     Search for an instance of a string inside another, taking into account OS
*   path string logic.
*
*   Parameters:
*     - puPath      : string path to search through
*     - puKey       : string to search for
*     - lenMax      : maximum size of 'puPath', in code units
*
*   Returns:
*     An index to the first instance of 'puKey' inside 'puStr'; or 'STR_NOINDEX' if
*   no instance is found.
*/
size_t  mtPathSearch( const utf8* puPath, const utf8* puKey, size_t lenMax );

/****** Path Logcal Resolve *********************************************************/
/*
*   Description:
*     Resolve a code unit to a logically consistant value for easy comparisons
*   of path strings. This is required as the OS may consider two very different
*   strings as the same path.
*
*   Notes:
*     - Converts code units:
*       - 'a' -> 'A'
*       - 'z' -> 'Z'
*       - '\' -> '/'
*
*   Parameters:
*     - c           : code unit to resolve
*
*   Returns:
*     Code unit that logically matches input code unit.
*/
utf8    mtPathResolveLogicalCode( utf8 c );
/*
*   Description:
*     Resolve a path string to a logically consistant string for easy comparison.
*   This is required as the OS may consider two very different strings as the same
*   path.
*
*   Notes:
*     - Converts code units:
*       - 'a' -> 'A'
*       - 'z' -> 'Z'
*       - '\' -> '/'
*
*   Parameters:
*     - puPath      : path string to resolve
*     - lenMax      : maximum size of 'puPath', in code units
*/
void    mtPathResolveLogicalString( utf8* puPath, size_t lenMax );

/****** Path To Parent **************************************************************/
/*
*   Description:
*     Set a path to its parent directory by inserting a terminator at the last path
*   delimiter ('/' or '\').
*
*   Notes:
*     - If 'puSrc' is 'nullptr', 'puDst' will be read as the source string
*
*   Parameters:
*     - puDst       : parent path string destination
*     - puOptSrc    : current path string                       [optional: nullptr]
*     - lenMax      : maximum size of both string paths, in code units
*
*   Returns:
*     New length of 'puDst'.
*/
size_t  mtPathParent( utf8* puDst, const utf8* puOptSrc, size_t lenMax );

EXTERN_END

#endif/*H_SAMT_STRING*/
