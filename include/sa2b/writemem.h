/*
*   Sonic Adventure Mod Tools (SA2B) - '/writemem.h'
*
*   Description:
*     Utility functions for modifying otherwise protected memory data, such as
*   executable memory. Extension of 'memory.h'
*
*   Contributors:
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SAMT_WRITEMEM
#define H_SAMT_WRITEMEM

EXTERN_START

/************************/
/*  Functions           */
/************************/
/****** Mem Copy/Move ***************************************************************/
/*
*   Description:
*     Copy 'nb' bytes from 'pSrc' to 'pDst' while ignoring write permissions. Leaves
*   memory page with all permissions (EXEC, READ, & WRITE).
*
*   Parameters:
*     - pDst    : address to copy to
*     - pSrc    : address to copy from
*     - nb      : number of bytes to copy
*/
void    MemCopyProtected( void* pDst, const void* pSrc, size_t nb );
/*
*   Description:
*     Move 'nb' bytes from 'pSrc' to 'pDst' while ignoring write permissions. Leaves
*   memory page with all permissions (EXEC, READ, & WRITE).
*
*   Parameters:
*     - pDst    : address to copy to
*     - pSrc    : address to copy from
*     - nb      : number of bytes to copy
*/
void    MemMoveProtected( void* pDst, const void* pSrc, size_t nb );

/****** Mem Set *********************************************************************/
/*
*   Description:
*     Copy 'nb' repeated bytes of value 'val' to protected memory.
*
*   Parameters:
*     - pDst    : address to mem set
*     - val     : value of the bytes
*     - nb      : number of bytes to set
*/
void    MemSetProtected( void* pDst, u8 val, size_t nb );
/*
*   Description:
*     Copy 'nb' repeated 2-byte units of value 'val' to protected memory.
*
*   Parameters:
*     - pDst    : address to mem set
*     - val     : value of the 8-byte chunks
*     - nb      : number of 2-byte units to set (2*'nb' bytes)
*/
void    MemSetProtected16( void* pDst, u16 val, size_t nb );
/*
*   Description:
*     Copy 'nb' repeated 4-byte units of value 'val' to protected memory.
*
*   Parameters:
*     - pDst    : address to mem set
*     - val     : value of the 8-byte chunks
*     - nb      : number of 4-byte units to set (4*'nb' bytes)
*/
void    MemSetProtected32( void* pDst, u32 val, size_t nb );
/*
*   Description:
*     Copy 'nb' repeated 8-byte units of value 'val' to protected memory.
*
*   Parameters:
*     - pDst    : address to mem set
*     - val     : value of the 8-byte chunks
*     - nb      : number of 8-byte units to set (8*'nb' bytes)
*/
void    MemSetProtected64( void* pDst, u64 val, size_t nb );

#ifdef __cplusplus
/************************/
/*  C++ Functions       */
/************************/
EXTERN_END
/****** Write Data ******************************************************************/
/*
*   Description:
*     Write lvalue 'data' to protected memory
*
*   Templates:
*     - T       : lvalue type
* 
*   Parameters:
*     - pDst    : address to mem write to
*     - data    : lvalue value
*/
template<typename T>
inline void
___WriteDataCpp(uintptr_t pDst, T value)
{
    MemCopyProtected((void*)(pDst), &value, sizeof(T));
}

EXTERN_START
#endif/*__cplusplus*/

/************************/
/*  Function Macros     */
/************************/
/****** Write Memory ****************************************************************/
/*
*   Description:
*     Copy 'nb' bytes from 'src' to 'dst' while ignoring write permissions. Leaves
*   memory page with all permissions (EXEC, READ, & WRITE).
*
*   Parameters:
*     - dst     : address to write to
*     - src     : pointer to copy from
*     - nb      : number of bytes to copy
*/
#define WriteMemory(dst, src, nb)           MemCopyProtected((void*)(dst), (const void*)(src), (size_t)(nb))

/****** Write R-Value ***************************************************************/
/*
*   Description:
*     Write value(s) directly to protected memory, without requiring a buffer.
*     C++ cannot use compound literals in this way, so a seperate definition is
*   required. There is no guarantee the two versions will operate exactly the same
*   if used outside of the intended bounds.
*
*   Parameters:
*     - dst     : address to write to
*     - val     : value(s) to write
*     - type    : type of 'val'
*/
#ifndef __cplusplus
#   define WriteData(dst, val, type)        WriteMemory((dst), &(type){val}, sizeof(type))
#else
#   define WriteData(dst, val, type)        ___WriteDataCpp<type>((uintptr_t)dst, val);
#endif/*__cplusplus*/

/****** Write Ex ********************************************************************/
/*
*   Description:
*     Write a pointer directly to protected memory, without requiring a buffer
*
*   Parameters:
*     - dst     : address to write to
*     - ptr     : pointer value to write
*/
#define WritePointer(dst, ptr)             WriteData((dst), (void*)(ptr), const void*)
/*
*   Description:
*     Copy an entire buffer (struct/array) of known size to protected memory
*
*   Parameters:
*     - dst     : address to write to
*     - bufp    : pointer to buffer of known size
*/
#define WriteBuffer(dst, bufp)              WriteMemory((dst), (bufp), sizeof(*bufp))

EXTERN_END

#endif/*H_SAMT_WRITEMEM*/
