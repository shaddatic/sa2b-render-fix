/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/util/devutil.h'
*
*   Description:
*     SAMT utility header containing useful development environment tools.
*/
#ifndef H_UTIL_DEVUTIL
#define H_UTIL_DEVUTIL

EXTERN_START

/********************************/
/*  Macro                       */
/********************************/
/****** Note Macros *****************************************************************************/
/*
*   Description:
*     Make a simple traceable comment/note.
*
*   Examples:
*     - ___NOTE("When our tools are better in a later version, this should be changed");
*/
#define ___NOTE(note)
/*
*   Description:
*     Make a traceable 'todo' comment/note.
*
*   Examples:
*     - ___TODO("This isn't quite working how I intended, return to this before release");
*/
#define ___TODO(note)
/*
*   Description:
*     Make an urgent traceable comment/note that halts compilation when not in debug mode.
* 
*   Examples:
*     - ___VITAL("Do NOT leave this as-is! Even in a dev build this is bad!");
*/
#ifndef NDEBUG
#   define ___VITAL(note)
#else
#   define ___VITAL(note)   static_assert(false, note)
#endif/*NDEBUG*/

EXTERN_END

#endif/*H_UTIL_DEVUTIL*/
