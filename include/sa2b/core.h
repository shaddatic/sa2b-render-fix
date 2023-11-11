/*
*   Sonic Adventure Mod Tools (SA2B) - '/core.h'
*
*   Contains the essential Library, Defines, Typedefs, Macros, and Functions.
*   Should always be included first.
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SAMT_CORE_H_
#define _SAMT_CORE_H_

#pragma comment(lib, "sa2b-mod-toolkit.lib")

#ifdef _WIN64
static_assert(false, "You cannot use x64 to build a mod for SA2 or SADX");
#endif

/************************/
/*  Includes            */
/************************/
#include <stddef.h>
#include <stdbool.h>

/************************/
/*  Extern              */
/************************/
#ifdef __cplusplus
#define EXTERN          extern "C"
#define EXTERN_START    EXTERN {
#define EXTERN_END      }
#else
#define EXTERN          extern
#define EXTERN_START
#define EXTERN_END
#endif /* __cplusplus */

/************************/
/*  Inline              */
/************************/
#define FORCE_INLINE __forceinline
#define DONOT_INLINE __declspec(noinline)

/************************/
/*  Core Functions      */
/************************/
EXTERN_START
/** Initializes the Toolkit, *always* call this first before anything else **/
void    SAMT_Init(const char* pPath, const void* pHelperFunctions);

/** Retrieves the path of this mod **/
const char* GetModPath(void);

EXTERN_END

/************************/
/*  Core Defines        */
/************************/
#ifndef arylen
#define arylen(ary) (sizeof(ary)/sizeof(*ary))
#endif /* arylen */

/************************/
/*  Global Typedefs     */
/************************/
/** Integer types **/
typedef unsigned __int8     uint8;      /*  unsigned 1 byte integer  */
typedef signed   __int8     sint8;      /*  signed 1 byte integer    */
typedef unsigned __int16    uint16;     /*  unsigned 2 byte integer  */
typedef signed   __int16    sint16;     /*  signed 2 byte integer    */
typedef unsigned __int32    uint32;     /*  unsigned 4 byte integer  */
typedef signed   __int32    sint32;     /*  signed 4 byte integer    */
typedef unsigned __int64    uint64;     /*  unsigned 8 byte integer  */
typedef signed   __int64    sint64;     /*  signed 8 byte integer    */

typedef signed   int        sint;       /*  signed default integer   */
typedef unsigned int        uint;       /*  unsigned default integer */

/** Floating Point types **/
typedef float               float32;    /*  4 byte real number       */
typedef double              float64;    /*  8 byte real number       */

/** Character types **/
typedef char                ansi;       /*  ANSI character (none)    */
typedef char                utf8;       /*  UTF-8 character (u8)     */

/** Byte **/
typedef uint8               byte;       /*  Basic byte type          */

/** Boolean **/
typedef sint32              bool32;     /*  4 byte boolean           */

/************************/
/*  Data Map Macros     */
/************************/
/** Data **/
#define DataRef(type, addr)                 (*(type *   )addr)
#define DataPtr(type, addr)                 ( (type *   )addr)
#define DataAry(type, addr, nb)             (*(type(*)nb)addr)

/** Functions **/
#define FuncPtr(type, meth, args, addr)     ((type(meth*const)args)addr)

#ifdef __cplusplus
#define ThisPtr(type, args, addr)           FuncPtr(type, __thiscall, args, addr)
#else
#define ThisPtr(type, args, addr)           ((void*)addr)
#endif /* __cplusplus */

#endif /* _SAMT_CORE_H_ */