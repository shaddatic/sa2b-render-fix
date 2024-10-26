/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njchunk/njcnk_bits.h'
*
*   Description:
*     Definitions for the Ninja Chunk 'bits' data offset
*
*   Contributors:
*     - SEGA
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_NJ_CHUNK_BITS
#define H_NJ_CHUNK_BITS

#ifndef H_NJ_CHUNK
#   error "Ninja Chunk sub-header included without first including 'njchunk.h'"
#else

/*------------*/
/* Chunk Bits */
/*------------*/
/* <Format>=[bits(8)|ChunkHead(8)](16 bits chunk) */
/* BA  : Blend Alpha                      */
/*       13-11 = SRC Alpha Instruction(3) */
/*       10- 8 = DST Alpha Instruction(3) */
/* DA  : Mipmap 'D' adjust                */
/*       11- 8 = Mipmap 'D' adjust(4)     */
/* EXP : Specular Exponent                */
/*       12- 8 = Exponent(5) range:0-16   */
/* CP  : Cache Polygon List               */
/*       15- 8 = Cache Number range:0-255 */
/* DP  : Draw Polygon List                */
/*       15- 8 = Cache Number range:0-255 */
#define NJD_CB_BA   (NJD_BITSOFF+0)
#define NJD_CB_DA   (NJD_BITSOFF+1)
#define NJD_CB_EXP  (NJD_BITSOFF+2)
#define NJD_CB_CP   (NJD_BITSOFF+3)
#define NJD_CB_DP   (NJD_BITSOFF+4)

/*------------*/
/* Chunk Bits */
/*------------*/

/** Flags Blending SRC **/

/* ZER : Zero                                            */
/* ONE : One                                             */
/* OC  : `Other' Color                                   */
/* IOC : Inverse `Other' Color                           */
/* SA  : Src Alpha                                       */
/* ISA : Inverse SRC Alpha                               */
/* DA  : DST Alpha                                       */
/* IDA : Inverse DST Alpha                               */

/* Flag Blending Src */

#define NJD_FBS_SHIFT     11
#define NJD_FBS_ZER      (0<<NJD_FBS_SHIFT)
#define NJD_FBS_ONE      (1<<NJD_FBS_SHIFT)
#define NJD_FBS_OC       (2<<NJD_FBS_SHIFT)
#define NJD_FBS_IOC      (3<<NJD_FBS_SHIFT)
#define NJD_FBS_SA       (4<<NJD_FBS_SHIFT)
#define NJD_FBS_ISA      (5<<NJD_FBS_SHIFT)
#define NJD_FBS_DA       (6<<NJD_FBS_SHIFT)
#define NJD_FBS_IDA      (7<<NJD_FBS_SHIFT)

#define NJD_FBS_MASK     (0x7<<NJD_FBS_SHIFT)

/* Src Select */
#define NJD_FBS_SEL      (BIT_15)

/* Flag Blending Dst */

#define NJD_FBD_SHIFT     8
#define NJD_FBD_ZER      (0<<NJD_FBD_SHIFT)
#define NJD_FBD_ONE      (1<<NJD_FBD_SHIFT)
#define NJD_FBD_OC       (2<<NJD_FBD_SHIFT)
#define NJD_FBD_IOC      (3<<NJD_FBD_SHIFT)
#define NJD_FBD_SA       (4<<NJD_FBD_SHIFT)
#define NJD_FBD_ISA      (5<<NJD_FBD_SHIFT)
#define NJD_FBD_DA       (6<<NJD_FBD_SHIFT)
#define NJD_FBD_IDA      (7<<NJD_FBD_SHIFT)

#define NJD_FBD_MASK     (0x7<<NJD_FBD_SHIFT)

/* Dst Select */
#define NJD_FBD_SEL      (BIT_14)

/** Flag 'D' Adjust **/

#define NJD_FDA_SHIFT     8
#define NJD_FDA_025      (1<<NJD_FDA_SHIFT)      /* 0.25 */
#define NJD_FDA_050      (2<<NJD_FDA_SHIFT)      /* 0.50 */
#define NJD_FDA_075      (3<<NJD_FDA_SHIFT)      /* 0.75 */
#define NJD_FDA_100      (4<<NJD_FDA_SHIFT)      /* 1.00 */
#define NJD_FDA_125      (5<<NJD_FDA_SHIFT)      /* 1.25 */
#define NJD_FDA_150      (6<<NJD_FDA_SHIFT)      /* 1.50 */
#define NJD_FDA_175      (7<<NJD_FDA_SHIFT)      /* 1.75 */
#define NJD_FDA_200      (8<<NJD_FDA_SHIFT)      /* 2.00 */
#define NJD_FDA_225      (9<<NJD_FDA_SHIFT)      /* 2.25 */
#define NJD_FDA_250      (10<<NJD_FDA_SHIFT)     /* 2.25 */
#define NJD_FDA_275      (11<<NJD_FDA_SHIFT)     /* 2.25 */
#define NJD_FDA_300      (12<<NJD_FDA_SHIFT)     /* 3.00 */
#define NJD_FDA_325      (13<<NJD_FDA_SHIFT)     /* 3.25 */
#define NJD_FDA_350      (14<<NJD_FDA_SHIFT)     /* 3.50 */
#define NJD_FDA_375      (15<<NJD_FDA_SHIFT)     /* 3.75 */

#define NJD_FDA_MASK     (0xf<<NJD_FDA_SHIFT)

/** Flag EXPonent range : 0-16 **/

#define NJD_FEXP_SHIFT    8
#define NJD_FEXP_00      (0<<NJD_FEXP_SHIFT)     /*  0.0 */
#define NJD_FEXP_01      (1<<NJD_FEXP_SHIFT)     /*  1.0 */
#define NJD_FEXP_02      (2<<NJD_FEXP_SHIFT)     /*  2.0 */
#define NJD_FEXP_03      (3<<NJD_FEXP_SHIFT)     /*  3.0 */
#define NJD_FEXP_04      (4<<NJD_FEXP_SHIFT)     /*  4.0 */
#define NJD_FEXP_05      (5<<NJD_FEXP_SHIFT)     /*  5.0 */
#define NJD_FEXP_06      (6<<NJD_FEXP_SHIFT)     /*  6.0 */
#define NJD_FEXP_07      (7<<NJD_FEXP_SHIFT)     /*  7.0 */
#define NJD_FEXP_08      (8<<NJD_FEXP_SHIFT)     /*  8.0 */
#define NJD_FEXP_09      (9<<NJD_FEXP_SHIFT)     /*  9.0 */
#define NJD_FEXP_10      (10<<NJD_FEXP_SHIFT)    /* 10.0 */
#define NJD_FEXP_11      (11<<NJD_FEXP_SHIFT)    /* 11.0 */
#define NJD_FEXP_12      (12<<NJD_FEXP_SHIFT)    /* 12.0 */
#define NJD_FEXP_13      (13<<NJD_FEXP_SHIFT)    /* 13.0 */
#define NJD_FEXP_14      (14<<NJD_FEXP_SHIFT)    /* 14.0 */
#define NJD_FEXP_15      (15<<NJD_FEXP_SHIFT)    /* 15.0 */
#define NJD_FEXP_16      (16<<NJD_FEXP_SHIFT)    /* 16.0 */

#define NJD_FEXP_MASK    (0x1f<<NJD_FEXP_SHIFT)

#endif/*H_NJ_CHUNK*/

#endif/*H_NJ_CHUNK_BITS*/
