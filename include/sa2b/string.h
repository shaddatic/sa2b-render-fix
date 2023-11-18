/*
*   Sonic Adventure Mod Tools (SA2B) - '/string.h'
*
*   Contains functions for manipulating, copying, duplicating, & converting strings.
*   All 'utf8' params are ANSI code-page safe.
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SAMT_STRING_H_
#define _SAMT_STRING_H_

/************************/
/*  UTF-8/ANSI Funcs    */
/************************/
EXTERN_START
/** String exact match **/
bool    StringMatch(const utf8* pStr1, const utf8* pStr2);
/** Size of string in bytes **/
size_t  StringLength(const utf8* pStr, size_t len);

utf8*   StringDupe(const utf8* pStr);
utf8*   StringCopy(utf8* pDest, const utf8* pStr, size_t lenDest);
utf8*   StringAppend(utf8* pDest, const utf8* pStr, size_t lenDest);

/************************/
/*  UTF-16 Funcs        */
/************************/
/** String exact match **/
bool    StringMatchW(const wchar_t* pStr1, const wchar_t* pStr2);
/** Size of string in two byte chunks **/
size_t  StringLengthW(const wchar_t* pStr, size_t len);

wchar_t* StringDupeW(const wchar_t* pStr);
wchar_t* StringCopyW(wchar_t* pDest, const wchar_t* pStr, size_t lenDest);
wchar_t* StringAppendW(wchar_t* pDest, const wchar_t* pStr, size_t lenDest);

/************************/
/*  Code-Page Convert   */
/************************/
utf8*   StringDupeTo8(const wchar_t* pStr);
/** Returns the new size of the string in bytes **/
size_t  StringCopyTo8(utf8* pDest, const wchar_t* pStr, size_t lenDest);

wchar_t* StringDupeTo16(const utf8* pStr);
/** Returns the new size of the string in two byte chunks **/
size_t   StringCopyTo16(wchar_t* pDest, const utf8* pStr, size_t lenDest);

EXTERN_END

/************************/
/*  Macros              */
/************************/
#define u8(str) (utf8*)u8##str /* (until C++23)    */

#endif /* _SAMT_STRING_H_ */