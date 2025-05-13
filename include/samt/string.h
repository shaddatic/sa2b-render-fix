/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/string.h'
*
*   Description:
*     String - and by extension, path - utility functions for UTF-8, 16, and 32.
*
*   Notes:
*     - All UTF-8 params are ASCII code-page safe, referred to as ASCII-7 or 'a7' in SAMT - but
*       do not explicitly support any extended ASCII code pages.
*     - String parameter/variable names often use prefixes, here's a rundown:
*       - 'pc' refers to regular ASCII (a7)
*       - 'pu' refers to unicode string pointers (c8, c16, c32)
        - 'ln' refers to length in code units
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

/********************************/
/*  Constants                   */
/********************************/
/****** Arguments *******************************************************************************/
#define STR_NOMAX               (0xFFFFFFFF) /* no maximum, rely on null terminator             */
#define STR_AUTOLEN             (0xFFFFFFFF) /* auto-calculate length for append                */

/****** Return Values ***************************************************************************/
#define STR_NOINDEX             (0xFFFFFFFF) /* no string index                                 */

/****** Escape Flags ****************************************************************************/
#define STR_ESC_ESCAPE          (1<<0)  /* \ -> \\  OR  \\ -> \                                 */
#define STR_ESC_DBLQUOTE        (1<<1)  /* " -> \"  OR  \" -> "                                 */
#define STR_ESC_SGLQUOTE        (1<<2)  /* ' -> \'  OR  \' -> '                                 */

#define STR_ESC_NOFLAG          (0)
#define STR_ESC_ALL             (STR_ESC_ESCAPE|STR_ESC_DBLQUOTE|STR_ESC_SGLQUOTE)

/********************************/
/*  Prototypes                  */
/********************************/
/************************************************************************************************/
/*
*   ASCII / UTF-8 / UTF-16
*/
/****** String Query ****************************************************************************/
/*
*   Description:
*     Compare if two strings exactly match.
*
*   Parameters:
*     - puStr1      : string 1
*     - puStr2      : string 2
*     - lnMax       : maximum length of both strings                           [opt: STR_NOMAX]
*
*   Returns:
*     'true' if both strings exactly match, or match until 'lnMax' is reached; or 'false' if
*   not.
*/
bool    mtStrMatch(   const c8*  puStr1, const c8*  puStr2, size_t lnMax );
bool    mtStrMatch16( const c16* puStr1, const c16* puStr2, size_t lnMax );
/*
*   Description:
*     Search for an instance of a string inside another.
*
*   Parameters:
*     - puStr       : string to search through
*     - puKey       : null-terminated string to search for
*     - lnMax       : maximum length of 'puStr'                                [opt: STR_NOMAX]
*
*   Returns:
*     An index to the first instance of the key string inside the search string; or
*   'STR_NOINDEX' if no instance was found.
*/
size_t  mtStrSearch(   const c8*  puStr, const c8*  puKey, size_t lnMax );
size_t  mtStrSearch16( const c16* puStr, const c16* puKey, size_t lnMax );
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
*     - lnMax       : maximum length of the string                             [opt: STR_NOMAX]
*
*   Returns:
*     The size of the string in bytes; or size up to 'lnMax' if it's reached.
*/
size_t  mtStrSize(   const c8*  puStr, size_t lnMax );
size_t  mtStrSize16( const c16* puStr, size_t lnMax );
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
*     - lnMax       : maximum length of the string                             [opt: STR_NOMAX]
*
*   Returns:
*     The length of the string in code units; or 'lnMax' if it's reached.
*/
size_t  mtStrLength(   const c8*  puStr, size_t lnMax );
size_t  mtStrLength16( const c16* puStr, size_t lnMax );
/*
*   Description:
*     Get the number of whole code points in a string, including the terminator.
*   
*   Notes:
*     - Example strings and their return values:
*       - "str"   -> '4'
*       - "漢字"   -> '3'
*     - Code points cut off by 'lnMax' being reached will not be counted.
*
*   Parameters:
*     - puStr       : string to get the number of code points of
*     - lnMax       : maximum length of the string                             [opt: STR_NOMAX]
*
*   Returns:
*     The number of code points in the string; or number up to 'lnMax' if it's
*   reached.
*/
size_t  mtStrCodeCount(   const c8*  puStr, size_t lnMax );
size_t  mtStrCodeCount16( const c16* puStr, size_t lnMax );

/****** String Copy *****************************************************************************/
/*
*   Description:
*     Copy a string into a seperate string buffer.
*
*   Notes:
*     - A terminator is inserted into the last unit if 'lnMax' is reached.
*     - No checks are made for if 'lnMax' lies in the middle of a multi-byte code point. This
*       may cause a code point to be incomplete.
*
*   Parameters:
*     - puDst       : string buffer to copy to
*     - puSrc       : string to copy
*     - lnMax       : maximum length of both string buffers                    [opt: STR_NOMAX]
*
*   Returns:
*     The length of the copied string in 'puDst', up to 'lnMax'.
*/
size_t  mtStrCopy(   c8*  puDst, const c8*  puSrc, size_t lnMax );
size_t  mtStrCopy16( c16* puDst, const c16* puSrc, size_t lnMax );
/*
*   Description:
*     Duplicate a string into a new heap buffer.
*
*   Notes:
*     - No checks are made for if 'lnMax' lies in the middle of a multi-byte code point. This
*       may cause a code point to be incomplete.
*
*   Parameters:
*     - puStr       : string to duplicate
*     - lnMax       : maximum length of the string                             [opt: STR_NOMAX]
*
*   Returns:
*     A duplicate of the given string, allocated by 'mtMemAlloc'.
*/
c8*     mtStrDupe(   const c8*  puStr, size_t lnMax );
c16*    mtStrDupe16( const c16* puStr, size_t lnMax );

/****** String Append ***************************************************************************/
/*
*   Description:
*     Append a string onto the end of another.
*
*   Notes:
*     - If 'lnDst' is '0', this indicates the string buffer is dirty and the function will
*       operate as a regular copy.
*     - No checks are made for if 'lnDstMax' lies in the middle of a multi-unit code point.
*       This may cause a code point to be incomplete.
*
*   Examples:
*     - mtStrAppend( pu_buf, STR_AUTOLEN, "append", STR_NOMAX ); // single append
*     - {
*         size_t len = 0; // zero indicates buffer is 'dirty'
*
*         utf8 pu_buf[32];
*
*         len = mtStrAppend( pu_buf, len, "app1", 32 ); // multi-append with length (faster)
*         len = mtStrAppend( pu_buf, len, "app2", 32 );
*         len = mtStrAppend( pu_buf, len, "app3", 32 );
*       } 
*
*   Parameters:
*     - puDst       : string buffer to append to
*     - lnDst       : current length of 'puDst'                           [opt: STR_AUTOLEN, 0]
*     - puApp       : null-terminated string to append
*     - lnDstMax    : maximum length of 'puDst'                                [opt: STR_NOMAX]
*
*   Returns:
*     New length of 'puDst' string after append.
*/
size_t  mtStrAppend(   c8*  puDst, size_t lnDst, const c8*  puApp, size_t lnDstMax );
size_t  mtStrAppend16( c16* puDst, size_t lnDst, const c16* puApp, size_t lnDstMax );

/****** String Format ***************************************************************************/
/*
*   Description:
*     Get the size of a string after formatting in bytes, including the terminator.
*
*   Parameters:
*     - puFmt       : format string (printf)
*     - ...         : format params
*
*   Returns:
*     Size of formatted string; or '0' on error.
*/
size_t  mtStrFormatSize(   const c8*  puFmt, ... );
size_t  mtStrFormatSize16( const c16* puFmt, ... );
/*
*   Description:
*     Get the length of a string after formatting in code units, including the terminator.
*
*   Parameters:
*     - puFmt       : format string (printf)
*     - ...         : format params
*
*   Returns:
*     Length of formatted string; or '0' on error.
*/
size_t  mtStrFormatLength(   const c8*  puFmt, ... );
size_t  mtStrFormatLength16( const c16* puFmt, ... );
/*
*   Description:
*     Get the length of a string after formatting in code units, including the terminator.
*
*   Parameters:
*     - puDst       : destination buffer for formatted string
*     - lnDstMax    : maximum length of the destination buffer
*     - puFmt       : format string (printf)
*     - ...         : format params
*
*   Returns:
*     Length of new formatted string in the destination buffer; or '0' on error.
*/
size_t  mtStrFormat(   c8*  RESTRICT puDst, size_t lnDstMax, const c8*  RESTRICT puFmt, ... );
size_t  mtStrFormat16( c16* RESTRICT puDst, size_t lnDstMax, const c16* RESTRICT puFmt, ... );

/****** String Case *****************************************************************************/
/*
*   Description:
*     Cast a string to upper case, with an optional source string.
*
*   Notes:
*     - If 'puOptSrc' is NULL, the destination string will also act as the source string.
*     - Only affects ASCII characters
*
*   Parameters:
*     - puDst       : destination string buffer
*     - puOptSrc    : source string                                              [opt: nullptr]
*     - lnMax       : maximum length of 'puDst' and 'puOptSrc'                 [opt: STR_NOMAX]
*
*   Returns:
*     The length of the destination string, up to 'lnMax'.
*/
size_t  mtStrToUpper( c8* RESTRICT puDst, const c8* RESTRICT puOptSrc, size_t lnMax );
/*
*   Description:
*     Cast a string to lower case, with an optional source string.
*
*   Notes:
*     - If 'puOptSrc' isn't given, the destination string will also act as the source string.
*     - Only affects ASCII characters
*
*   Parameters:
*     - puDst       : destination string buffer
*     - puOptSrc    : source string                                              [opt: nullptr]
*     - lenMax      : maximum length of 'puDst' and 'puOptSrc'                 [opt: STR_NOMAX]
*
*   Returns:
*     The length of the destination string, up to 'lnMax'.
*/
size_t  mtStrToLower( c8* RESTRICT puDst, const c8* RESTRICT puOptSrc, size_t lenMax );

/****** String Escape ***************************************************************************/
/*
*   Description:
*     Get the length of a string after inserting escape characters.
*
*   Parameters:
*     - puStr       : string to get the escaped length of
*     - lnMax       : maximum length of 'puStr'                                [opt: STR_NOMAX]
*     - flag        : additional escape sequence flags                    [opt: STR_ESC_NOFLAG]
*
*   Returns:
*     Calculated length of string after inserting escape characters.
*/
size_t  mtStrEscapeLength( const c8* puStr, const size_t lnMax, s32 flag );
/*
*   Description:
*     Get the length of a string after resolving escape characters.
*
*   Parameters:
*     - puStr       : string to get the length
*     - lnMax       : maximum length of 'puStr'                                [opt: STR_NOMAX]
*     - flag        : additional escape sequence flags                    [opt: STR_ESC_NOFLAG]
*
*   Returns:
*     Calculated length of string after resolving escape characters.
*/
size_t  mtStrUnescapeLength( const c8* puStr, const size_t lnMax, s32 flag );
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
*     - lnMax       : maximum length of 'puDst'                                [opt: STR_NOMAX]
*     - flag        : additional escape sequence flags                    [opt: STR_ESC_NOFLAG]
*
*   Returns:
*     Length of 'puDst' after inserting escape sequences.
*/
size_t  mtStrEscape( c8* puDst, const c8* puSrc, const size_t lnMax, s32 flag );
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
*     - lnMax       : maximum length of 'puDst'                                [opt: STR_NOMAX]
*     - flag        : additional escape sequence flags                    [opt: STR_ESC_NOFLAG]
*
*   Returns:
*     Length of 'puDst' after resolving escape sequences.
*/
size_t  mtStrUnescape( c8* puDst, const c8* puSrc, const size_t lnMax, s32 flag );

/************************************************************************************************/
/*
*   Conversion (To/As)
*/
/****** Query As ********************************************************************************/
/*
*   Description:
*     Get the size of a string in bytes, including the terminator, after conversion into
*   another string format.
*
*   Parameters:
*     - puStr       : string to get size of
*     - lnMax       : maximum length of the string                             [opt: STR_NOMAX]
*
*   Returns:
*     Size of the string in bytes if it were in another format.
*/
size_t  mtStrSizeAs16( const c8* puStr, size_t lnMax );
size_t  mtStrSizeAs32( const c8* puStr, size_t lnMax );
//
size_t  mtStrSize16As8(  const c16* puStr, size_t lnMax );
size_t  mtStrSize16As32( const c16* puStr, size_t lnMax );
//
size_t  mtStrSize32As8(  const c32* puStr, size_t lnMax );
size_t  mtStrSize32As16( const c32* puStr, size_t lnMax );

/*
*   Description:
*     Get the length of a string, including the terminator, after conversion into another
*   string format.
*
*   Parameters:
*     - puStr       : string to get length of
*     - lnMax       : maximum length of the string                             [opt: STR_NOMAX]
*
*   Returns:
*     Length of the string if it were in another format.
*/
size_t  mtStrLengthAs16( const c8* puStr, size_t lnMax );
size_t  mtStrLengthAs32( const c8* puStr, size_t lnMax );
//
size_t  mtStrLength16As8(  const c16* puStr, size_t lnMax );
size_t  mtStrLength16As32( const c16* puStr, size_t lnMax );
//
size_t  mtStrLength32As8(  const c32* puStr, size_t lnMax );
size_t  mtStrLength32As16( const c32* puStr, size_t lnMax );

/****** Copy To *********************************************************************************/
/*
*   Description:
*     Copy a string into a seperate string buffer, while also converting the string format.
*
*   Notes:
*     - A terminator is inserted into the last unit if 'lnMax' is reached.
*     - No checks are made for if either 'lnMax' lies in the middle of a multi-unit code point.
*       This may cause a code point to be incomplete.
*     - Src and Dst can be the same buffer, but only when converting *from* UTF-32.
*
*   Parameters:
*     - puDst       : string buffer to copy to
*     - lnDstMax    : maximum length of the destination buffer                 [opt: STR_NOMAX]
*     - puSrc       : string to copy
*     - lnSrcMax    : maximum length of the source buffer                      [opt: STR_NOMAX]
*
*   Returns:
*     The length of the copied string in 'puDst', up to 'lnDstMax'.
*/
size_t  mtStrCopyTo16( c16* puDst, size_t lnDstMax, const c8* puSrc, size_t lnSrcMax );
size_t  mtStrCopyTo32( c32* puDst, size_t lnDstMax, const c8* puSrc, size_t lnSrcMax );
//
size_t  mtStrCopy16To8(  c8*  puDst, size_t lnDstMax, const c16* puSrc, size_t lnSrcMax );
size_t  mtStrCopy16To32( c32* puDst, size_t lnDstMax, const c16* puSrc, size_t lnSrcMax );
//
size_t  mtStrCopy32To8(  c8*  puDst, size_t lnDstMax, const c32* puSrc, size_t lnSrcMax );
size_t  mtStrCopy32To16( c16* puDst, size_t lnDstMax, const c32* puSrc, size_t lnSrcMax );
/*
*   Description:
*     Duplicate a string into a new heap buffer, while also converting the string format.
*
*   Parameters:
*     - puStr       : string to duplicate
*     - lnMax       : maximum length of the string                             [opt: STR_NOMAX]
*
*   Returns:
*     A duplicate of the given string, allocated by 'mtMemAlloc', in the new format.
*/
c16*    mtStrDupeTo16( const c8* puStr, size_t lnMax );
c32*    mtStrDupeTo32( const c8* puStr, size_t lnMax );
//
c8*     mtStrDupe16To8(  const c16* puStr, size_t lnMax );
c32*    mtStrDupe16To32( const c16* puStr, size_t lnMax );
//
c8*     mtStrDupe32To8(  const c32* puStr, size_t lnMax );
c16*    mtStrDupe32To16( const c32* puStr, size_t lnMax );

/************************************************************************************************/
/*
*   File Paths
*/
/****** String Query ****************************************************************************/
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
bool    mtPathMatch( const c8* puPath1, const c8* puPath2, size_t lenMax );
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
size_t  mtPathSearch( const c8* puPath, const c8* puKey, size_t lenMax );

/****** Path Logcal Resolve *********************************************************************/
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
c8      mtPathResolveLogicalCode( c8 c );
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
void    mtPathResolveLogicalString( c8* puPath, size_t lenMax );

/****** Path To Parent **************************************************************************/
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
size_t  mtPathParent( c8* puDst, const c8* puOptSrc, size_t lenMax );

EXTERN_END

#endif/*H_SAMT_STRING*/
