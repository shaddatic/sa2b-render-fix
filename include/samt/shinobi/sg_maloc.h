/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/shinobi/sg_malloc.h'
*
*   Description:
*       System memory functions.
*/

#ifndef _SG_MALOC_H_
#define _SG_MALOC_H_

/************************/
/*  Includes            */
/************************/
/** System **/
#include <samt/shinobi/sg_xpt.h>

/************************/
/*  Structures          */
/************************/
/** Internal function pointers **/
typedef struct
{
    Void* (*malloc )(Uint32 nbytes, char*, Int);
    Void  (*free   )(Void* ap, char*, Int);
    Void* (*calloc )(Uint32 nobj, Uint32 size);
    Void* (*realloc)(Void* ap, Uint32 nbytes);
}
SYS_MALLOC_IF;

/************************/
/*  Functions           */
/************************/
EXTERN_START
Void*   syMalloc(Uint32 nbytes);

Void*   syRealloc(Void* op, Uint32 nbytes);

Void*   syCalloc(Uint32 nobj, Uint32 size);

Void    syFree(Void* ap);

/** Allows you to replace malloc Internal Functions. 
    Returns old functions **/
SYS_MALLOC_IF* syMallocChangeIF(SYS_MALLOC_IF* mallocIF);

EXTERN_END

#endif /* _SG_MALOC_H_ */
