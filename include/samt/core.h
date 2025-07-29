/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/core.h'
*
*   Description:
*     Core header for SAMT, defining everything universally relied upon in the
*   library. It is recommended to always include it first, either directly or
*   through a core header made for your project.
*/
#ifndef H_SAMT_CORE
#define H_SAMT_CORE

/************************/
/*  Core Init           */
/************************/
/****** Core Library ****************************************************************/
#ifndef SAMT_NO_AUTOLIB
#   pragma comment(lib, "samt.lib")
#endif

/****** Core Errors *****************************************************************/
#ifndef SAMT_NO_COREERR
#   if !defined(_MSC_VER)
#       error "SAMT is designed for the MSVC compiler"
#   endif

#   if !defined(_M_IX86)
#       error "Mod is being built for a non-x86 platform, please change your platform target to x86"
#   endif

#   if !defined(__clang__)

#       if defined(_MSVC_TRADITIONAL) && (_MSVC_TRADITIONAL != 0)
#           error "SAMT is designed for the standard conforming MSVC preprocessor, please enable either in your project's settings"
#       endif
#       if defined(_MSVC_LANG) && (_MSVC_LANG < 202002L)
#           error "SAMT is designed for C++20 or later, please change the project's C++ standard target"
#       endif
#       if defined(__STDC_VERSION__) && (__STDC_VERSION__ < 201710L)
#           error "SAMT for MSVC is designed for C17 or later, please change the project's C standard target"
#       endif

#   else/*__clang__*/

#       if defined(__cplusplus) && (__cplusplus < 202002L)
#           error "SAMT is designed for C++20 or later, please change the project's C++ standard target"
#       endif
#       if defined(__STDC_VERSION__) && (__STDC_VERSION__ < 202311L)
#           error "SAMT for Clang is designed for C23 or later, please change the project's C standard target"
#       endif

#   endif/*__clang__*/
#endif/*SAMT_DONT_COREERR*/

/****** C++ Debug Fix ***************************************************************************/
#ifndef SAMT_NO_DEBUGFIX
#   undef _DEBUG                    /* undefine MSVC specific debug flag                        */
#endif

/****** Core Warning Disable ********************************************************************/
#ifndef SAMT_NO_WARNDISABLE
#   pragma warning(disable:4200)    /* allow variable length arrays in structs                  */
#endif

/********************************/
/*  Core Definitions            */
/********************************/
/************************************************************************************************/
/*
*   Game Definitions
*/
/****** Game Number *****************************************************************************/
#define SAMT_GAME_SA2B          (0) /* sonic adventure 2 for PC, 2012                           */
#define SAMT_GAME_SADX          (1) /* sonic adventure DX for PC, 2004                          */

/****** Current Game ****************************************************************************/
#define SAMT_CURR_GAME          SAMT_GAME_SA2B

/************************************************************************************************/
/*
*   Standard Keywords
*/
/****** Boolean *********************************************************************************/
#define TRUE                    (1) /* true                                                     */
#define FALSE                   (0) /* false                                                    */

/****** Switch **********************************************************************************/
#define ON                      (1) /* on                                                       */
#define OFF                     (0) /* off                                                      */

#ifndef __cplusplus
/****** C ***************************************************************************************/
#define EXTERN                  extern      /* extern                                           */
#define STATIC                  static      /* static                                           */
#define RESTRICT                restrict    /* restrict                                         */
#define CONST                   const       /* const                                            */
#define CONSTEXPR               const       /* constexpr                                        */
#define TYPEOF                __typeof__    /* typeof                                           */

#define EXTERN_START                        /* extern block start                               */
#define EXTERN_END                          /* extern block end                                 */

#else
/****** C++ *************************************************************************************/
#define EXTERN                  extern "C"  /* extern                                           */
#define STATIC                  static      /* static                                           */
#define RESTRICT                __restrict  /* restrict                                         */
#define CONST                   const       /* const                                            */
#define CONSTEXPR               constexpr   /* constexpr                                        */
#define TYPEOF                  decltype    /* typeof                                           */

#define EXTERN_START            EXTERN {    /* extern block start                               */
#define EXTERN_END              }           /* extern block end                                 */

#endif/*__cplusplus*/

/********************************/
/*  Includes                    */
/********************************/
/****** Standard Library ************************************************************************/
#include <stddef.h>                 /* NULL, size_t, etc                                        */
#include <stdbool.h>                /* bool                                         (until C23) */
#include <stdint.h>                 /* verbose stdint types                                     */
#include <assert.h>                 /* asserts for C                                (until C23) */

EXTERN_START

/********************************/
/*  Types                       */
/********************************/
/************************************************************************************************/
/*
*   Short-Hand Types
*/
/****** Integer types ***************************************************************************/
typedef uint8_t             u8;     /* unsigned 1 byte integer                                  */
typedef int8_t              s8;     /* signed 1 byte integer                                    */
typedef uint16_t            u16;    /* unsigned 2 byte integer                                  */
typedef int16_t             s16;    /* signed 2 byte integer                                    */
typedef uint32_t            u32;    /* unsigned 4 byte integer                                  */
typedef int32_t             s32;    /* signed 4 byte integer                                    */
typedef uint64_t            u64;    /* unsigned 8 byte integer                                  */
typedef int64_t             s64;    /* signed 8 byte integer                                    */

/****** Real number types ***********************************************************************/
typedef float               f32;    /* 4 byte real number                                       */
typedef double              f64;    /* 8 byte real number                                       */

/****** Boolean *********************************************************************************/
typedef int32_t             b32;    /* 4 byte boolean                                           */

/************************************************************************************************/
/*
*   Character Types
*/
/****** ASCII ***********************************************************************************/
typedef char                c7;     /* ASCII-7                                                  */

/****** Unicode *********************************************************************************/
typedef char                c8;     /* UTF-8 code unit or ASCII                                 */
typedef wchar_t             c16;    /* UTF-16 code unit                                         */
typedef uint32_t            c32;    /* UTF-32 code point                                        */

/************************************************************************************************/
/*
*   Other Types
*/
/****** Byte ************************************************************************************/
typedef uint8_t             byte;   /* basic byte type                                          */

/****** Pointer *********************************************************************************/
typedef uintptr_t           pint;   /* pointer integer value                                    */
typedef intptr_t            poff;   /* pointer offset value                                     */

/****** Size ************************************************************************************/
typedef int32_t             size;   /* size integer                                             */
typedef uint32_t            usize;  /* unsigned size integer                                    */

/********************************/
/*  Core Functions              */
/********************************/
/****** Mod Path ********************************************************************************/
/*
*   Description:
*     Get the local path to this mod, as passed into 'mtSystemInit'.
*
*   Returns:
*     Normalized local path to your mod folder.
*/
const c8* mtGetModPath( void );
/*
*   Description:
*     Get the mod position index of this mod, as passed into 'mtSystemInit'.
*
*   Returns:
*     Current mod position index; or '-1' if the mod loader isn't a supported version.
*/
size    mtGetModIndex( void );

/********************************/
/*  Core Macros                 */
/********************************/
/****** Core ************************************************************************************/
/*
*   Description:
*     Gets the number of elements in a defined array variable.
*
*   Parameters:
*     - ary     : array variable
*/
#define ARYLEN(ary)         (sizeof(ary)/sizeof(0[ary]))
/*
*   Description:
*     Gets the number of bits in a defined type or variable.
*
*   Parameters:
*     - type    : type/variable
*/
#define BITSIN(type)        (sizeof(type)*8)

/****** Function ********************************************************************************/
/*
*   Description:
*     Clamps a value within the set range.
*
*   Parameters:
*     - val     : value to clamp
*     - min     : minimum value
*     - max     : maximum value
*/
#define CLAMP(val, min, max)             (((val)<(min))?(min):((max)<(val))?(max):(val))
/*
*   Description:
*     Gets the maximum of two values.
*
*   Parameters:
*     - val#    : values to find the maximum of
*/
#define MAX(val1, val2)                  ((val1)>(val2)?(val1):(val2))
/*
*   Description:
*     Gets the minimum of two values.
*
*   Parameters:
*     - val#    : values to find the minimum of
*/
#define MIN(val1, val2)                  ((val1)>(val2)?(val2):(val1))
/*
*   Description:
*     Gets the absolute value of the input value. In other words, the non-negative
*   form of the value.
*
*   Parameters:
*     - val     : value to find the absolute value of
*/
#define ABS(val)                         ((val)>=0?(val):-(val))
/*
*   Description:
*     Get the highest absolute value of two values
*
*   Parameters:
*     - val#    : values to find the absolute maximum of
*/
#define MAX_ABS(val1, val2)              ((ABS(val1))>(ABS(val2))?(val1):(val2))
/*
*   Description:
*     Get the lowest absolute value of two values
*
*   Parameters:
*     - val#    : values to find the absolute minimum of
*/
#define MIN_ABS(val1, val2)              ((ABS(val1))>(ABS(val2))?(val2):(val1))

/****** Data Address Mapping ********************************************************************/
/*
*   Description:
*     Define a data reference at an arbitrary address.
*
*   Examples:
*     - #define SomeData    DATA_REF(int*, 0x12345678)
*
*   Parameters:
*     - type    : type of the data, can be a pointer type
*     - addr    : constant address of the data
*/
#define DATA_REF(type, addr)                (*(type*const)(addr))
/*
*   Description:
*     Define a data array reference at an arbitrary address.
*
*   Examples:
*     - #define SomeArray   DATA_ARY(double, 0x12345678, [23][2])
*
*   Parameters:
*     - type    : type of the data the array contains
*     - addr    : constant address of the start of the array
*     - nb      : number of elements in the array, can be multi-dimensional
*/
#define DATA_ARY(type, addr, nb)            (*(type(*const)nb)(addr))

/****** Function Address Mapping ****************************************************************/
/*
*   Description:
*     Define a function pointer at an arbitrary address.
*
*   Notes:
*     - If the calling method isn't defined, it will use the default of your project
*
*   Examples:
*     - #define SomeFunc    FUNC_PTR(void*, __cdecl, (int), 0x12345678)
*     - #define SomeFunc    FUNC_PTR(void*,        , (int), 0x12345678)
*
*   Parameters:
*     - type        : return type of the function
*     - meth        : calling method of the function                      (optional)
*     - args        : arguments to the function
*     - addr        : constant address of the start of the function
*/
#define FUNC_PTR(type, meth, args, addr)    ((type(meth*const)args)(addr))
/*
*   Description:
*     Define a function pointer reference at an arbitrary address.
*
*   Notes:
*     - If the calling method isn't defined, it will use the default of your project
*
*   Examples:
*     - #define SomeFuncPtr   FUNC_REF(void*, __cdecl, (int), 0x12345678)
*     - #define SomeFuncPtr   FUNC_REF(void*,        , (int), 0x12345678)
*
*   Parameters:
*     - type        : return type of the function
*     - meth        : calling method of the function                      (optional)
*     - args        : arguments to the function
*     - addr        : constant address of the pointer reference
*/
#define FUNC_REF(type, meth, args, addr)    (*(type(meth**const)args)(addr))

EXTERN_END

#endif/*H_SAMT_CORE*/
