/*
*   Sonic Adventure Mod Tools (SA2B) - '/util/devutil.h'
*
*   Description:
*       SAMT utility header containing useful development environment tools
*
*   Contributors:
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _UTIL_DEVUTIL_H_
#define _UTIL_DEVUTIL_H_

/************************/
/*  Macro               */
/************************/
/** To make a trackable comment/note **/
#define ___NOTE(_note)

/** To make a trackable, vital comment/note
    that also stops non-debug compilation **/
#ifndef NDEBUG
#   define ___VITAL(_note)
#else
#   define ___VITAL(_note)  static_assert(false, _note)
#endif/*NDEBUG*/

#endif/*_UTIL_DEVUTIL_H_*/
