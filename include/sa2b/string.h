/*
*   Sonic Adventure Mod Tools (SA2B) - '/string.h'
*
*   Description:
*       Manipulating, copying, duplicating, & converting
*   strings of ASCII, UTF-8, & UTF-16 code-pages.
*       All 'utf8' params are ASCII code-page safe.
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SAMT_STRING_H_
#define _SAMT_STRING_H_

/************************/
/*  UTF-8/ASCII Funcs   */
/************************/
EXTERN_START
/** String exact match **/
bool    StringMatch( const utf8* pStr1, const utf8* pStr2 );

/** Size of string in bytes **/
size_t  StringSize( const utf8* pStr, size_t maxLen );

/** Length of string in code points, excluding NULL **/
size_t  StringLength( const utf8* pStr, size_t maxLen );

utf8*   StringDupe( const utf8* pSrc );
utf8*   StringCopy(       utf8* pDst, const utf8* pSrc, size_t maxDst );
utf8*   StringAppend(     utf8* pDst, const utf8* pSrc, size_t maxDst );

/************************/
/*  UTF-16 Funcs        */
/************************/
/** String exact match **/
bool    StringMatchW( const wchar_t* pStr1, const wchar_t* pStr2 );

/** Size of string in two byte units **/
size_t  StringSizeW( const wchar_t* pStr, size_t maxLen );

/** Length of string in code points, excluding NULL **/
size_t  StringLengthW( const wchar_t* pStr, size_t maxLen );

wchar_t* StringDupeW( const wchar_t* pStr );
wchar_t* StringCopyW(       wchar_t* pDest, const wchar_t* pStr, size_t lenDest );
wchar_t* StringAppendW(     wchar_t* pDest, const wchar_t* pStr, size_t lenDest );

/************************/
/*  Code-Page Convert   */
/************************/
utf8*   StringDupeTo8(const wchar_t* pStr);
/** Returns the new size of the string in bytes **/
size_t  StringCopyTo8(utf8* pDest, const wchar_t* pStr, size_t lenDest);

wchar_t* StringDupeTo16(const utf8* pStr);
/** Returns the new size of the string in two byte units **/
size_t   StringCopyTo16(wchar_t* pDest, const utf8* pStr, size_t lenDest);

EXTERN_END

#endif /* _SAMT_STRING_H_ */
