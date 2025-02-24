/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/ninja/njchunk/njcnk_end.h'
*
*   Description:
*     Definitions for the Ninja Chunk 'end' data offset
*/
#ifndef H_NJ_CHUNK_END
#define H_NJ_CHUNK_END

#ifndef H_NJ_CHUNK
#   error "Ninja Chunk sub-header included without first including 'njchunk.h'"
#else

/*-----------*/
/* Chunk End */
/*-----------*/
/* <Format>=[ChunkHead(16)](16 bits chunk) */
#define NJD_CE      (NJD_ENDOFF+0)

#endif/*H_NJ_CHUNK*/

#endif/*H_NJ_CHUNK_END*/
