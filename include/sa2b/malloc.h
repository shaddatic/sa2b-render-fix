/*
*   Sonic Adventure Mod Tools (SA2B) - '/malloc.h'
*
*   Contains memory allocation and manipulation functions. Along with useful
*   macros.
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SAMT_MALLOC_H_
#define _SAMT_MALLOC_H_

/************************/
/*  Functions           */
/************************/
EXTERN_START
void*   MemAlloc(size_t bytes);
void*   MemCalloc(size_t count, size_t bytes);
void    MemFree(void* p);

void*   MemSet(void* p, int val, size_t size);
void*   MemCopy(void* pDest, const void* pCopy, size_t bytes);
void*   MemMove(void* pDest, const void* pCopy, size_t bytes);

void*   MemReAlloc(void* p, size_t bytes);

/** Calls ReAlloc then zeros out new space **/
void*   MemReCalloc(void* p, size_t bytesOld, size_t bytesNew);

EXTERN_END

/************************/
/*  Macros              */
/************************/
#define mAlloc(type, nb)                    (type*)MemAlloc((nb) * sizeof(type))
#define mCalloc(type, nb)                   (type*)MemCalloc((nb), sizeof(type))

#define mReAlloc(type, p, nb)               (type*)MemReAlloc((p), sizeof(type)*(nb))

#define mReCalloc(type, p, nbold, nbnew)    (type*)MemReCalloc((p), sizeof(type)*(nbold), sizeof(type)*(nbnew))

#endif /* _SAMT_MALLOC_H_ */
