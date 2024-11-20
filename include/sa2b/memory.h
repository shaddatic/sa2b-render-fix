/*
*   Sonic Adventure Mod Tools (SA2B) - '/memory.h'
*
*   Description:
*     Memory management and manipulation header with useful macros for type safety
*   and automatic size deducing.
*
*   Contributors:
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SAMT_MEMORY
#define H_SAMT_MEMORY

#ifdef __cplusplus
#   pragma push_macro("restrict")
#   define restrict     __restrict
#endif/*__cplusplus*/

EXTERN_START

/************************/
/*  Prototypes          */
/************************/
/************************************************************************************/
/*
*   Memory Allocation
*/

/****** Malloc/Calloc ***************************************************************/
/*
*   Description:
*     Dynamically allocate a region of memory from the heap.
*
*   Notes:
*     - In ordinary operation, this will *never* return 'nullptr'. if it does, the
*     | system is fatally out of memory and will crash regardless.
*     - The memory returned may not be clear and could contain garbage data.
*
*   Parameters:
*     - sz          : size of allocation, in bytes
*
*   Returns:
*     Pointer to newly allocated memory.
*/
void*   MemAlloc( size_t sz );
/*
*   Description:
*     Dynamically allocate a region of zeroed memory from the heap using a chunk
*   size and count value.
*
*   Notes:
*     - In ordinary operation, this will *never* return 'nullptr'. if it does, the
*     | system is fatally out of memory and will crash regardless.
*     - This function is faster than using 'memset', as it specifically asks the OS
*     | for already zeroed memory.
*
*   Examples:
*     - MemCalloc(8, sizeof(int)); // memory sized for 8 integers
* 
*   Parameters:
*     - nb          : number of memory chunks to allocate for
*     - sz          : size of memory chunk, in bytes
*
*   Returns:
*     Pointer to newly allocated memory.
*/
void*   MemCalloc( size_t nb, size_t sz );

/****** Free ***********************************************************************/
/*
*   Description:
*     Free a dynamically allocated memory region.
*
*   Notes:
*     - Memory chunk must be allocated by 'malloc()' or 'calloc()', and must not
*     | have been released be 'free()'.
*
*   Parameters:
*     - p           : pointer to memory chunk
*/
void    MemFree( void* p );

/****** Realloc ********************************************************************/
/*
*   Description:
*     Re-allocate a region of memory to a different size, keeping the contents of
*   the old region.
*
*   Notes:
*     - Unlike 'realloc', operates by writing new pointer directly to 'pp'. This is
*     | to ensure invalid pointers are overwritten and cannot be addressed.
*     |-- In the event of failure, 'pp' will be left unchanged.
*
*   Examples:
*     - MemRealloc(&p, sizeof(*p) * 2); // double memory region size
* 
*   Parameters:
*     - pp          : memory region to reallocate and return pointer for new region
*     - sz          : new size to reallocate to, in bytes
*/
void    MemRealloc( void** pp, size_t sz );
/*
*   Description:
*     Re-allocate a region of memory to a different size, keeping the contents of
*   the old region and zero'ing the new chunk of memory if applicable.
*
*   Notes:
*     - Unlike 'realloc', operates by writing new pointer directly to 'pp'. This is
*     | to ensure invalid pointers are overwritten and cannot be addressed.
*     |-- In the event of failure, 'pp' will be left unchanged.
*
*   Examples:
*     - MemRecalloc(&p, sizeof(*p), sizeof(*p) * 2); // double memory region size
* 
*   Parameters:
*     - pp          : memory region to reallocate and return pointer for new region
*     - szPre       : previous size of region, in bytes
*     - szNew       : new size to reallocate to, in bytes
*/
void    MemRecalloc( void** pp, size_t szPre, size_t szNew );

/************************************************************************************/
/*
*   Memory Set/Copy/Move
*/

/****** Memset **********************************************************************/
/*
*   Description:
*     Set a region of memory to a set value.
*
*   Notes:
*     - 'MemSet32(p, 0, 4)' and 'MemSet(p, 0, 16)' are functionally the same,
*     | although the former may give the compilier additional information for
*     | optimizations.
*
*   Examples:
*     - MemSet(  ary, 0, sizeof(ary));
*     - MemSet32(ary, 0, ARYLEN(ary)); // assume 'ary' is 's32[]'
*
*   Parameters:
*     - pd          : set destination
*     - val         : value to set
*     - nb          : size of memory area in 1, 2, 4, or 8 byte chunks
*/
void    MemSet(   void* pd, u8  val, size_t nb );
void    MemSet16( void* pd, u16 val, size_t nb );
void    MemSet32( void* pd, u32 val, size_t nb );
void    MemSet64( void* pd, u64 val, size_t nb );

/****** Memcpy **********************************************************************/
/*
*   Description:
*     Copy a chunk of memory from one region to another.
*
*   Notes:
*     - Overlap of the memory regions will lead to undefined behavior.
*
*   Parameters:
*     - pd          : copy destination
*     - ps          : copy source
*     - nb          : size of copy in 1, 2, 4, or 8 byte chunks
*/
void    MemCopy(   void* restrict pd, const void* restrict ps, size_t nb );
void    MemCopy16( void* restrict pd, const void* restrict ps, size_t nb );
void    MemCopy32( void* restrict pd, const void* restrict ps, size_t nb );
void    MemCopy64( void* restrict pd, const void* restrict ps, size_t nb );

/****** Memmove *********************************************************************/
/*
*   Description:
*     Copy a chunk of memory from one region to another with explicit support for
*   the two regions to overlap.
*
*   Notes:
*     - Slower than 'MemCopy'.
*
*   Parameters:
*     - pd          : copy destination
*     - ps          : copy source
*     - nb          : size of copy in 1, 2, 4, or 8 byte chunks
*/
void    MemMove(   void* pd, const void* ps, size_t nb );
void    MemMove16( void* pd, const void* ps, size_t nb );
void    MemMove32( void* pd, const void* ps, size_t nb );
void    MemMove64( void* pd, const void* ps, size_t nb );

/****** Memdupe *********************************************************************/
/*
*   Description:
*     Duplicate a chunk of memory.
*
*   Notes:
*     - Memory must be freed with 'MemFree'/'free'.
*
*   Parameters:
*     - ps          : duplicate source
*     - nb          : size of duplication, in bytes
*/
void*   MemDupe( const void* ps, size_t nb );

/************************************************************************************/
/*
*   Memory Compare
*/

/****** Memcmp *********************************************************************/
/*
*   Description:
*     Compare two chunks of memory.
*
*   Notes:
*     - This function will return on the first byte that doesn't match.
*
*   Parameters:
*     - p1          : memory chunk one
*     - p2          : memory chunk two
*     - nb          : size of memory chunk to compare, in bytes
*
*   Returns:
*     'true' if the memory chunks exactly match, 'false' if they don't.
*/
bool    MemMatch( const void* p1, const void* p2, size_t nb );

/************************************************************************************/
/*
*   Deprecated Memory Functions
*/

/****** Realloc ********************************************************************/
/*
*   Description:
*     Re-allocate a region of memory to a different size, keeping the contents of
*   the old region.
*
*   Notes:
*     - Ensure to discard 'p' after use, as the old pointer is likely garbage.
*
*   Parameters:
*     - p           : memory region to reallocate
*     - sz          : new size to reallocate to, in bytes
*
*   Returns:
*     Pointer to new, resized memory region; or 'nullptr' on failure.
*/
void*   MemReAlloc( void* p, size_t sz );
/*
*   Description:
*     Re-allocate a region of memory to a different size, keeping the contents of
*   the old region and zero'ing the new chunk of memory if applicable.
*
*   Notes:
*     - Ensure to discard 'p' after use, as the old pointer is likely garbage.
*     - New memory chunk will only be zeroed when the new region size is larger than
*     | the old size.
*
*   Parameters:
*     - p           : memory region to reallocate
*     - szPre       : previous size of region, in bytes
*     - szNew       : new size to reallocate to, in bytes
*
*   Returns:
*     Pointer to new, resized memory region; or 'nullptr' on failure.
*/
void*   MemReCalloc( void* p, size_t szPre, size_t szNew );

/************************/
/*  Macros              */
/************************/
/************************************************************************************/
/*
*   Memory Allocation Macros
*/

/****** Malloc/Calloc ***************************************************************/
/*
*   Description:
*     Dynamically allocate a region of memory from the heap with type parameter for
*   size calculations and return type safety.
*
*   Examples:
*     - mAlloc(int, 4); // allocate array of 4 integers
*     - mAlloc(f32, 1); // allocate a single float
*
*   Parameters:
*     - type        : data type or structure of allocation
*     - nb          : number of 'type' to allocate
*
*   Returns:
*     Pointer to newly allocated memory.
*/
#define mAlloc(type, nb)        (type*)MemAlloc((nb) * sizeof(type))
/*
*   Description:
*     Dynamically allocate a region of zeroed memory from the heap using a chunk
*   size and count value with type parameter for size calculations and return type
*   safety.
*
*   Examples:
*     - mCalloc(int, 4); // allocate array of 4 integers
*     - mCalloc(f32, 1); // allocate a single float
* 
*   Parameters:
*     - type        : data type or structure of allocation
*     - nb          : number of 'type' to allocate
*
*   Returns:
*     Pointer to newly allocated memory.
*/
#define mCalloc(type, nb)       (type*)MemCalloc((nb), sizeof(type))

/****** Free ************************************************************************/
/*
*   Description:
*     Free a dynamically allocated memory region.
*
*   Notes:
*     - Same as 'MemFree', only defined for completeness
*
*   Parameters:
*     - p           : pointer to memory chunk
*/
#define mFree(p)                MemFree((p))

/****** Realloc ********************************************************************/
/*
*   Description:
*     Re-allocate a region of memory to a different size, keeping the contents of
*   the old region with type parameter for size calculations.
*
*   Examples:
*     - mRealloc(&p, f32, 8); // reallocate 'p' to the size of 8 floats
* 
*   Parameters:
*     - pp          : memory region to reallocate and return pointer for new region
*     - type        : data type or structure of reallocation
*     - nb          : number of 'type' to reallocate
*/
#define mRealloc(pp, type, nb)      MemRealloc((void**)(pp), (sizeof(type) * (nb)))
/*
*   Description:
*     Re-allocate a region of memory to a different size, keeping the contents of
*   the old region and zero'ing the new chunk of memory if applicable with type
*   parameter for size calculations.
*
*   Examples:
*     - mRecalloc(&p, f32, 4, 8); // reallocate 'p' to the size of 8 floats, from 4
* 
*   Parameters:
*     - pp          : memory region to reallocate and return pointer for new region
*     - type        : data type or structure of reallocation
*     - nbpre       : previous size of region, in number of 'type'
*     - nbnew       : number of 'type' to reallocate
*/
#define mRecalloc(pp, type, nbpre, nbnew)       MemRecalloc((void**)(pp), (sizeof(type)*(nbpre)), (sizeof(type)*(nbnew)))

/************************************************************************************/
/*
*   Memory Copy/Move
*/

/****** Memcpy **********************************************************************/
/*
*   Description:
*     Copy a chunk of memory from one region to another with type parameter for size
*   calculations.
*
*   Examples:
*     - mCopy(pd, ps, s32, 8); // copy 8 integers
*
*   Parameters:
*     - pd          : copy destination
*     - ps          : copy source
*     - type        : data type or structure of memory
*     - nb          : number of 'type' to copy
*/
#define mCopy(pd, ps, type, nb)     MemCopy((pd), (ps), (sizeof(type) * (nb)))

/****** Memmove *********************************************************************/
/*
*   Description:
*     Copy a chunk of memory from one region to another with explicit support for
*   the two regions to overlap with type parameter for size calculations.
*
*   Examples:
*     - mMove(pd, ps, s32, 8); // copy 8 integers
*
*   Parameters:
*     - pd          : copy destination
*     - ps          : copy source
*     - type        : data type or structure of memory
*     - nb          : number of 'type' to copy
*/
#define mMove(pd, ps, type, nb)     MemMove((pd), (ps), (sizeof(type) * (nb)))

/****** Memdupe *********************************************************************/
/*
*   Description:
*     Duplicate a chunk of memory with type parameter for size calculations and type
*   safety.
*
*   Examples:
*     - pd = mDupe(ps, s32, 8); // duplicate 8 integers
*
*   Parameters:
*     - ps          : duplicate source
*     - nb          : size of duplication, in bytes
*     - type        : data type or structure of memory
*     - nb          : number of 'type' to duplicate
*/
#define mDupe(ps, type, nb)         (type*)MemDupe((ps), (sizeof(type) * (nb)))

/************************************************************************************/
/*
*   Ex Macros
*/

/****** Realloc ********************************************************************/
/*
*   Description:
*     Re-allocate a region of memory to a different size, keeping the contents of
*   the old region with automatic type deducing.
*
*   Examples:
*     - mReallocEx(&p, 8); // assume 'p' is 'f32*', reallocate 'p' to the size of 8 floats
* 
*   Parameters:
*     - pp          : memory region to reallocate and return pointer for new region
*     - nb          : number of deduced type to reallocate
*/
#define mReallocEx(pp, nb)                  MemRealloc((pp), (sizeof(**(pp))*(nb)))
/*
*   Description:
*     Re-allocate a region of memory to a different size, keeping the contents of
*   the old region and zero'ing the new chunk of memory if applicable with automatic
*   type deducing.
*
*   Examples:
*     - mRecalloc(&p, 4, 8); // assume 'p' is 'f32*', reallocate 'p' to the size of 8 floats, from 4
* 
*   Parameters:
*     - pp          : memory region to reallocate and return pointer for new region
*     - nbpre       : previous size of region, in number of deduced type
*     - nbnew       : number of deduced type to reallocate
*/
#define mRecallocEx(pp, nbpre, nbnew)       MemRecalloc((pp), (sizeof(**(pp))*(nbpre)), (sizeof(type)*(nbnew)))

/************************************************************************************/
/*
*   Deprecated Macros
*/

/****** Realloc ********************************************************************/
/*
*   Description:
*     Re-allocate a region of memory to a different size, keeping the contents of
*   the old region with type parameter for size calculations and type safety.
*
*   Examples:
*     - p = mReAlloc(f32, p, 8); // reallocate 'p' to the size of 8 floats
* 
*   Parameters:
*     - type        : data type or structure of reallocation
*     - pp          : memory region to reallocate
*     - nb          : number of 'type' to reallocate
*/
#define mReAlloc(type, p, nb)               (type*)MemReAlloc((p), sizeof(type)*(nb))
/*
*   Description:
*     Re-allocate a region of memory to a different size, keeping the contents of
*   the old region and zero'ing the new chunk of memory if applicable with type
*   parameter for size calculations and type safety.
*
*   Examples:
*     - p = mReCalloc(f32, p, 4, 8); // reallocate 'p' to the size of 8 floats, from 4
* 
*   Parameters:
*     - type        : data type or structure of reallocation
*     - pp          : memory region to reallocate
*     - nbpre       : previous size of region, in number of 'type'
*     - nbnew       : number of 'type' to reallocate
*/
#define mReCalloc(type, p, nbpre, nbnew)    (type*)MemReCalloc((p), sizeof(type)*(nbpre), sizeof(type)*(nbnew))

EXTERN_END

#ifdef __cplusplus
#   pragma pop_macro("restrict")
#endif/*__cplusplus*/

#endif/*H_SAMT_MEMORY*/
