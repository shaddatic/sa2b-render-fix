/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njchunk/njcnk_tiny.h'
*
*   Description:
*     Definitions for the Ninja Chunk 'tiny' data offset
*
*   Contributors:
*     - SEGA
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_NJ_CHUNK_TINY
#define H_NJ_CHUNK_TINY

#ifndef H_NJ_CHUNK
#   error "Ninja Chunk sub-header included without first including 'njchunk.h'"
#else

/*------------*/
/* Chunk Tiny */
/*------------*/
/* <Format>=[headbits(8)|ChunkHead(8)][texbits(3)|TexId(13)] (32 bits chunk) */
/* TID : Set Texture                      */
/*     <headbits>                         */
/*       15-14 = FlipUV(2)                */
/*       13-12 = ClampUV(2)               */
/*       11- 8 = Mipmap 'D' adjust(4)     */
/*     <texbits>                          */
/*       15-14 = Filter Mode(2)           */
/*       13    = Super Sample(1)          */
/*     (TexId Max = 8191)                 */
#define NJD_CT_TID  (NJD_TINYOFF+0)

/* 2para modifier */
#define NJD_CT_TID2 (NJD_TINYOFF+1)

/*------------*/
/* Chunk Tiny */
/*------------*/
/** TexId **/
/* Flag FLip <headbits> */
#define NJD_FFL_U         (BIT_15)
#define NJD_FFL_V         (BIT_14)
/* Flag CLamp <headbits> */
#define NJD_FCL_U         (BIT_13)
#define NJD_FCL_V         (BIT_12)

/* Look at Chunk Bits about 'D' adust */

/* Flag Filter Mode<texbits> */
/* PS   : Point Sampled                   */
/* BF   : Bilinear Filter                 */
/* TF_A : Tri-liner Filter A              */
/* TF_B : Tri-liner Filter B              */
#define NJD_FFM_SHIFT      14
#define NJD_FFM_PS        (0<<NJD_FFM_SHIFT)
#define NJD_FFM_BF        (1<<NJD_FFM_SHIFT)
#define NJD_FFM_TF_A      (2<<NJD_FFM_SHIFT)
#define NJD_FFM_TF_B      (3<<NJD_FFM_SHIFT)

#define NJD_FFM_MASK      (0x3<<NJD_FFM_SHIFT)

/* Flag Super Sample<texbits> */
#define NJD_FSS           (BIT_13)

#define NJD_TID_MASK      (~(NJD_FSS|NJD_FFM_MASK))

#endif/*H_NJ_CHUNK*/

#endif/*H_NJ_CHUNK_TINY*/
