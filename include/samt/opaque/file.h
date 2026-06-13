/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/opaque/file.h'
*
*   Description:
*     Opaque definition of the stdio.h 'FILE' type.
*/
#ifndef H_MT_OPAQUE_FILE
#define H_MT_OPAQUE_FILE

EXTERN_START

/********************************/
/*  Opaque Types                */
/********************************/
/****** MSVC stdio ******************************************************************************/
typedef struct _iobuf               FILE; /* msvc std file type                                 */

EXTERN_END

#endif/*H_MT_OPAQUE_FILE*/
