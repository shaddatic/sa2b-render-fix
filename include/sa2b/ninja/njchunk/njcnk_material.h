/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njchunk/njcnk_material.h'
*
*   Description:
*     Definitions for the Ninja Chunk 'material' data offset
*
*   Contributors:
*     - SEGA
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_NJ_CHUNK_MATERIAL
#define H_NJ_CHUNK_MATERIAL

#ifndef H_NJ_CHUNK
#   error "Ninja Chunk sub-header included without first including 'njchunk.h'"
#else

/*----------------*/
/* Chunk Material */
/*----------------*/
/* <Format>=[ChunkHead][Size][Data]                        */
/*       13-11 = SRC Alpha Instruction(3)                  */
/*       10- 8 = DST Alpha Instruction(3)                  */
/* D  : Diffuse (ARGB)                            bit 0    */
/* A  : Ambient (RGB)                             bit 1    */
/* S  : Specular(ERGB) E:exponent(5) range:0-16   bit 2    */
#define NJD_CM_D    (NJD_MATOFF+1)  /* [CHead][4(Size)][ARGB]              */
#define NJD_CM_A    (NJD_MATOFF+2)  /* [CHead][4(Size)][NRGB] N: NOOP(255) */
#define NJD_CM_DA   (NJD_MATOFF+3)  /* [CHead][8(Size)][ARGB][NRGB]        */
#define NJD_CM_S    (NJD_MATOFF+4)  /* [CHead][4(Size)][ERGB] E: Exponent  */
#define NJD_CM_DS   (NJD_MATOFF+5)  /* [CHead][8(Size)][ARGB][ERGB]        */
#define NJD_CM_AS   (NJD_MATOFF+6)  /* [CHead][8(Size)][NRGB][ERGB]        */
#define NJD_CM_DAS  (NJD_MATOFF+7)  /* [CHead][12(Size)][ARGB][NRGB][ERGB] */

/* Bump */
#define NJD_CM_BU   (NJD_MATOFF+8)  /* [CHead][12(Size)][dx(16)][dy(16)][dz(16)]
[ux(16)][uy(16)][uz(16)]            */

/* 2para modifier */
#define NJD_CM_D2   (NJD_MATOFF+9)  /* [CHead][4(Size)][ARGB]              */
#define NJD_CM_A2   (NJD_MATOFF+10) /* [CHead][4(Size)][NRGB] N: NOOP(255) */
#define NJD_CM_DA2  (NJD_MATOFF+11) /* [CHead][8(Size)][ARGB][NRGB]        */
#define NJD_CM_S2   (NJD_MATOFF+12) /* [CHead][4(Size)][ERGB] E: Exponent  */
#define NJD_CM_DS2  (NJD_MATOFF+13) /* [CHead][8(Size)][ARGB][ERGB]        */
#define NJD_CM_AS2  (NJD_MATOFF+14) /* [CHead][8(Size)][NRGB][ERGB]        */
#define NJD_CM_DAS2 (NJD_MATOFF+15) /* [CHead][12(Size)][ARGB][NRGB][ERGB] */

#endif/*H_NJ_CHUNK*/

#endif/*H_NJ_CHUNK_MATERIAL*/
