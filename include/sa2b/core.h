/*
*   Sonic Adventure Mod Tools (SA2B) - '/core.h'
*
*   Description:
*     Core header for the Sonic Adventure Mod Toolkit. Anything nearly universally
*   relied upon is defined or included in this header. It is recommended to always
*   include it first, either directly or through a core header made for your project
*
*   Contributors:
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SAMT_CORE
#define H_SAMT_CORE

/************************/
/*  Core Init           */
/************************/
/****** Core Library ****************************************************************/
#ifndef SAMT_NO_AUTOLIB
#   pragma comment(lib, "sa2b-mod-toolkit.lib")
#endif

/****** Core Errors *****************************************************************/
#ifndef SAMT_NO_COREERR
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
#endif/*SAMT_DONT_COREERR*/

/************************/
/*  Includes            */
/************************/
/****** Standard Library ************************************************************/
#include <stddef.h>                     /*  NULL, size_t, etc                       */
#include <stdbool.h>                    /*  bool (until C23)                        */

/************************/
/*  Core Definitions    */
/************************/
/****** C/C++ Extern Macros *********************************************************/
#ifdef  __cplusplus
#   define EXTERN          extern "C"
#   define EXTERN_START    EXTERN {
#   define EXTERN_END      }
#else
#   define EXTERN          extern
#   define EXTERN_START
#   define EXTERN_END
#endif/*__cplusplus*/

EXTERN_START

/****** Verbose Types ***************************************************************/
/** Integer types **/
#include <stdint.h>                     /* stdint types                             */

/****** Short-Hand Types ************************************************************/
/** Integer types **/
typedef unsigned __int8     u8;         /* unsigned 1 byte integer                  */
typedef signed   __int8     s8;         /* signed 1 byte integer                    */
typedef unsigned __int16    u16;        /* unsigned 2 byte integer                  */
typedef signed   __int16    s16;        /* signed 2 byte integer                    */
typedef unsigned __int32    u32;        /* unsigned 4 byte integer                  */
typedef signed   __int32    s32;        /* signed 4 byte integer                    */
typedef unsigned __int64    u64;        /* unsigned 8 byte integer                  */
typedef signed   __int64    s64;        /* signed 8 byte integer                    */

/** Real number types **/
typedef float               f32;        /* 4 byte real number                       */
typedef double              f64;        /* 8 byte real number                       */

/** Boolean **/
typedef int32_t             b32;        /* 4 byte boolean                           */

/****** Other Types *****************************************************************/
/** Character types **/                                                             
typedef char                ascii;      /* ASCII character (none)                   */
typedef char                utf8;       /* UTF-8 character (u8)                     */

/** Byte **/
typedef uint8_t             byte;       /* basic byte type                          */

/************************/
/*  Core Functions      */
/************************/
/*
*   Retrieves the string path sent into 'SAMT_Init(path, ...)'
*/
const char* GetModPath(void);

/************************/
/*  Core Macros         */
/************************/
/****** Core ************************************************************************/
/*
*   Description:
*     Gets the number of elements in a defined array variable.
*
*   Parameters:
*     - ary     : array variable
*/
#define ARYLEN(ary)             (sizeof(ary)/sizeof(0[ary]))
/*
*   Description:
*     Gets the total number of elements in a defined array type. This macro is
*   temporary until C23.
*
*   Parameters:
*     - ary     : array type
*/
#ifndef ARYLEN_T
#   define ARYLEN_T(ary)       (sizeof(ary)/sizeof(0[(ary){0}]))
#endif/*ARYLEN_T*/
/*
*   Description:
*     Gets the number of bits in a defined type or variable.
*
*   Parameters:
*     - type    : type/variable
*/
#define BITSIN(type)            (sizeof(type)*8)

/****** Function *********************************************************************/
/*
*   Description:
*     Clamps a value within the set range.
*
*   Parameters:
*     - val     : value to clamp
*     - min     : minimum value
*     - max     : maximum value
*/
#ifndef CLAMP
#   define CLAMP(val, min, max)             (((val)<(min))?(min):((max)<(val))?(max):(val))
#endif/*CLAMP*/
/*
*   Description:
*     Gets the maximum of two values.
*
*   Parameters:
*     - val#    : values to find the maximum of
*/
#ifndef MAX
#   define MAX(val1, val2)                  ((val1)>(val2)?(val1):(val2))
#endif/*MAX*/
/*
*   Description:
*     Gets the minimum of two values.
*
*   Parameters:
*     - val#    : values to find the minimum of
*/
#ifndef MIN
#   define MIN(val1, val2)                  ((val1)>(val2)?(val2):(val1))
#endif/*MIN*/
/*
*   Description:
*     Gets the absolute value of the input value. In other words, the non-negative
*   form of the value.
*
*   Parameters:
*     - val     : value to find the absolute value of
*/
#ifndef ABS
#   define ABS(val)                         ((val)>=0?(val):-(val))
#endif/*ABS*/
/*
*   Description:
*     Get the highest absolute value of two values
*
*   Parameters:
*     - val#    : values to find the absolute maximum of
*/
#ifndef MAX_ABS
#   define MAX_ABS(val1, val2)              ((ABS(val1))>(ABS(val2))?(val1):(val2))
#endif/*MAX_ABS*/
/*
*   Description:
*     Get the lowest absolute value of two values
*
*   Parameters:
*     - val#    : values to find the absolute minimum of
*/
#ifndef MIN_ABS
#   define MIN_ABS(val1, val2)              ((ABS(val1))>(ABS(val2))?(val2):(val1))
#endif/*MIN_ABS*/

/****** Address Mapping *************************************************************/
/*
*   Description:
*     Define a data reference at an arbitrary address.
*
*   Example:
*     #define SomeData    DATA_REF(int*, 0x12345678)
*
*   Parameters:
*     - type    : Type of the data, can be a pointer type
*     - addr    : Constant address of the data
*/
#define DATA_REF(type, addr)                (*(type*const)(addr))
/*
*   Description:
*     Define a data array reference at an arbitrary address.
*
*   Example:
*     #define SomeArray   DATA_ARY(double, 0x12345678, [23][2])
*
*   Parameters:
*     - type    : Type of the data the array contains
*     - addr    : Constant address of the start of the array
*     - nb      : Number of elements in the array, can be multi-dimensional
*/
#define DATA_ARY(type, addr, nb)            (*(type(*const)nb)(addr))
/*
*   Description:
*     Define a function pointer at an arbitrary address.
*
*   Example:
*     #define SomeFunc    FUNC_PTR(void*, __cdecl, (int), 0x12345678)
*
*   Parameters:
*     - type    : Return type of the function
*     - meth    : Calling method of the function; __cdecl is default
*     - args    : Arguments to the function
*     - addr    : Address of the start of the function
*/
#define FUNC_PTR(type, meth, args, addr)    ((type(meth*const)args)(addr))

EXTERN_END

#endif/*H_SAMT_CORE*/
