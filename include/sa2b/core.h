/*
*   Sonic Adventure Mod Tools (SA2B) - '/core.h'
*
*   Description:
*       Contains the essential Library, Defines, Typedefs,
*   Macros, and Functions.
*       Should always be included first.
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SAMT_CORE_H_
#define _SAMT_CORE_H_

#ifndef SAMT_NO_AUTOLIB
#   pragma comment(lib, "sa2b-mod-toolkit.lib")
#endif

#ifndef SAMT_NO_CORE_ERROR
#   if !defined(_MSC_VER)
#       error "SAMT is designed for the MSVC compiler"
#   endif

#   if !defined(_M_IX86)
#       error "Mod is being built for a non-x86 platform, please change your platform target to x86"
#   endif

#   if !defined(_MSVC_TRADITIONAL) || (_MSVC_TRADITIONAL == 1)
#       error "SAMT is designed for a standard conforming preprocessor, please enable it in your project's settings"
#   endif

#   if defined(_MSVC_LANG) && (_MSVC_LANG < 202002L)
#       error "SAMT is designed for the latest C++ version (C++20), please change the project's C++ standard target"
#   endif

#   if defined(__STDC_VERSION__) && (__STDC_VERSION__ < 201710L)
#       error "SAMT is designed for the latest C version (C17), please change the project's C standard target"
#   endif
#endif/*SAMT_NO_COREERR*/

/************************/
/*  Includes            */
/************************/
#include <stddef.h>                     /*  NULL, size_t, etc        */
#include <stdbool.h>                    /*  bool (until C23)         */

/************************/
/*  Extern Macros       */
/************************/
#ifdef  __cplusplus
#   define EXTERN          extern "C"
#   define EXTERN_START    EXTERN {
#   define EXTERN_END      }
#else
#   define EXTERN          extern
#   define EXTERN_START
#   define EXTERN_END
#endif/*__cplusplus*/

/************************/
/*  Core Functions      */
/************************/
EXTERN_START
/** Retrieves the path of this mod **/
const char* GetModPath(void);

EXTERN_END

/************************/
/*  Core Macros         */
/************************/
#ifndef arylen
#   define arylen(ary)     (sizeof(ary)/sizeof(*ary))
#endif

#ifndef bitsin
#   define bitsin(type)    (sizeof(type)*8)
#endif

/************************/
/*  Global Typedefs     */
/************************/
/*
*   Verbose types
*/
/** Integer types **/
#include <stdint.h>                     /*  stdint types            */

/** Real number types **/
typedef float               float32_t;  /*  4 byte real number      */
typedef double              float64_t;  /*  8 byte real number      */

/** Boolean **/
typedef int32_t             bool32_t;   /*  4 byte boolean          */

/*
*   Short-hand types
*/
/** Integer types **/
typedef unsigned __int8     u8;         /*  unsigned 1 byte integer */
typedef signed   __int8     s8;         /*  signed 1 byte integer   */
typedef unsigned __int16    u16;        /*  unsigned 2 byte integer */
typedef signed   __int16    s16;        /*  signed 2 byte integer   */
typedef unsigned __int32    u32;        /*  unsigned 4 byte integer */
typedef signed   __int32    s32;        /*  signed 4 byte integer   */
typedef unsigned __int64    u64;        /*  unsigned 8 byte integer */
typedef signed   __int64    s64;        /*  signed 8 byte integer   */

/** Real number types **/
typedef float               f32;        /*  4 byte real number      */
typedef double              f64;        /*  8 byte real number      */

/** Boolean **/
typedef int32_t             b32;        /*  4 byte boolean          */

/*
*   Other types
*/
/** Character types **/
typedef char                ansi;       /*  ANSI character (none)   */
typedef char                utf8;       /*  UTF-8 character (u8)    */

/** Byte **/
typedef uint8_t             byte;       /*  Basic byte type         */

/************************/
/*  Data Map Macros     */
/************************/
/** Data **/
#define DataRef(type, addr)                 (*(type *   )addr)
#define DataAry(type, addr, nb)             (*(type(*)nb)addr)

/** Functions **/
#define FuncPtr(type, meth, args, addr)     ((type(meth*const)args)addr)

#endif/*_SAMT_CORE_H_*/
