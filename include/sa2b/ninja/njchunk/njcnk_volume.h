/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njchunk/njcnk_volume.h'
*
*   Description:
*     Definitions for the Ninja Chunk 'volume' data offset
*
*   Contributors:
*     - SEGA
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_NJ_CHUNK_VOLUME
#define H_NJ_CHUNK_VOLUME

#ifndef H_NJ_CHUNK
#   error "Ninja Chunk sub-header included without first including 'njchunk.h'"
#else

/*--------------*/
/* Chunk vOlume */
/*--------------*/
/* UserFlags N=0,1(16bit*1),2(16bit*2),3(16bit*3)                         */
/* <Format P3>=[ChunkHead(16)][Size(16)][UserOffset(2)|nbPolygon(14)]     */
/*            i0, i1, i2, UserflagPoly0(*N),                              */
/*            i3, i4, i5, UserflagPoly1(*N), ...                          */
/* <Format P4>=[ChunkHead(16)][Size(16)][UserOffset(2)|nbPolygon(14)]     */
/*            i0, i1, i2, i3, UserflagPoly0(*N),                          */
/*            i4, i5, i6, i7, UserflagPoly1(*N), ...                      */
/* <Format ST>=[ChunkHead(16)][Size(16)][UserOffset(2)|nbStrip(14)]       */
/*          [flag|len, i0, i1, i2, Userflag2(*N), i3, Userflag3(*N), ...  */
/* P3  : Polygon3     (Modifier Volume)                                   */
/* P4  : Polygon4                                                         */
/* ST  : triangle STrip(Trimesh)                                          */

#define NJD_CO_P3       (NJD_VOLOFF+0)
#define NJD_CO_P4       (NJD_VOLOFF+1)
#define NJD_CO_ST       (NJD_VOLOFF+2)

#endif/*H_NJ_CHUNK*/

#endif/*H_NJ_CHUNK_VOLUME*/
