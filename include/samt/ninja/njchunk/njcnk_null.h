/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/ninja/njchunk/njcnk_null.h'
*
*   Description:
*     Definitions for the Ninja Chunk 'null' data offset
*/
#ifndef H_NJ_CHUNK_NULL
#define H_NJ_CHUNK_NULL

#ifndef H_NJ_CHUNK
#   error "Ninja Chunk sub-header included without first including 'njchunk.h'"
#else

/*------------*/
/* Chunk Null */
/*------------*/
/* <Format>=[ChunkHead(16)](16 bits chunk) */
#define NJD_CN     (NJD_NULLOFF+0)/* NULL chunk for boundary control      */

#endif/*H_NJ_CHUNK*/

#endif/*H_NJ_CHUNK_NULL*/
