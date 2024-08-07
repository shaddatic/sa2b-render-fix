/*
*   Sonic Adventure Mod Tools (SA2B) - '/memory.h'
*
*   Description:
*       Contains memory allocation, setter, copy, & move
*   functions; alongside useful allocation macros.
*
*   Contributors:
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SAMT_MEMORY_H_
#define _SAMT_MEMORY_H_

/************************/
/*  Memory Allocate     */
/************************/
EXTERN_START
void*   MemAlloc(  size_t nbByte );
void*   MemCalloc( size_t nb, size_t nbByte );

/************************/
/*  Memory Deallocate   */
/************************/
void    MemFree( void* p );

/************************/
/*  Dynamic Allocate    */
/************************/
void*   MemReAlloc(  void* p, size_t nbByte );
void*   MemReCalloc( void* p, size_t nbBytePre, size_t nbByteNew ); /* Calls ReAlloc then zeros out new space */

/************************/
/*  Memory Set          */
/************************/
void*   MemSet(   void* pDst, u8  val, size_t nb );
void*   MemSet16( void* pDst, u16 val, size_t nb );
void*   MemSet32( void* pDst, u32 val, size_t nb );
void*   MemSet64( void* pDst, u64 val, size_t nb );

/************************/
/*  Memory Copy         */
/************************/
void*   MemCopy(   void* pDst, const void* pSrc, size_t nb );
void*   MemCopy16( void* pDst, const void* pSrc, size_t nb );
void*   MemCopy32( void* pDst, const void* pSrc, size_t nb );
void*   MemCopy64( void* pDst, const void* pSrc, size_t nb );

/************************/
/*  Memory Move         */
/************************/
void*   MemMove(   void* pDst, const void* pSrc, size_t nb );
void*   MemMove16( void* pDst, const void* pSrc, size_t nb );
void*   MemMove32( void* pDst, const void* pSrc, size_t nb );
void*   MemCopy64( void* pDst, const void* pSrc, size_t nb );

EXTERN_END

/************************/
/*  Macros              */
/************************/
/** Macro MemAlloc() and MemCalloc() **/
#define mAlloc(type, nb)                    (type*)MemAlloc((nb) * sizeof(type))
#define mCalloc(type, nb)                   (type*)MemCalloc((nb), sizeof(type))

/** Macro MemReAlloc() **/
#define mReAlloc(type, p, nb)               (type*)MemReAlloc((p), sizeof(type)*(nb))

/** Macro MemReCalloc() **/
#define mReCalloc(type, p, nb_pre, nb_new)  (type*)MemReCalloc((p), sizeof(type)*(nb_pre), sizeof(type)*(nb_new))

#endif /* _SAMT_MEMORY_H_ */
