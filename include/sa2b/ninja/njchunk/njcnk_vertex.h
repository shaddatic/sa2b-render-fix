/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njchunk/njcnk_vertex.h'
*
*   Description:
*     Definitions for the Ninja Chunk 'vertex' data offset
*
*   Contributors:
*     - SEGA
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_NJ_CHUNK_VERTEX
#define H_NJ_CHUNK_VERTEX

#ifndef H_NJ_CHUNK
#   error "Ninja Chunk sub-header included without first including 'njchunk.h'"
#else

/*--------------*/
/* Chunk Vertex */
/*--------------*/
/* <Format>=[headbits(8)|ChunkHead(8)]                                    */
/*          [Size(16)][IndexOffset(16)][nbIndices(16)]                    */
/*     <headbits>(NF only)                                                */
/*        9- 8 = WeightStatus(2) Start, Middle, End                       */
/* VN  : use vertex normal                                                */
/* VNX : 32bits vertex normal  reserved(2)|x(10)|y(10)|z(10)              */
/* SH  : SH4 optimize                                                     */
/* D8  : Diffuse ARGB8888 only                                            */
/* S5  : Diffuse RGB565 and Specular RGB565                               */
/* S4  : Diffuse RGB4444 and Specular RGB565                              */
/* IN  : Diffuse(16)|Specular(16)                                         */
/* NF  : NinjaFlags32 for extention                                       */
/* UF  : UserFlags32                                                      */

/* optimize for SH4 */
#define NJD_CV_SH     (NJD_VERTOFF+0)  /* x,y,z,1.0F, ...                 */
#define NJD_CV_VN_SH  (NJD_VERTOFF+1)  /* x,y,z,1.0F,nx,ny,nz,0.0F,...    */

/* chunk vertex */
#define NJD_CV        (NJD_VERTOFF+2)  /* x,y,z, ...                      */
#define NJD_CV_D8     (NJD_VERTOFF+3)  /* x,y,z,D8888,...                 */  
#define NJD_CV_UF     (NJD_VERTOFF+4)  /* x,y,z,UserFlags32, ...          */
#define NJD_CV_NF     (NJD_VERTOFF+5)  /* x,y,z,NinjaFlags32,...          */
#define NJD_CV_S5     (NJD_VERTOFF+6)  /* x,y,z,D565|S565,...             */
#define NJD_CV_S4     (NJD_VERTOFF+7)  /* x,y,z,D4444|S565,...            */
#define NJD_CV_IN     (NJD_VERTOFF+8)  /* x,y,z,D16|S16,...               */

#define NJD_CV_VN     (NJD_VERTOFF+9)  /* x,y,z,nx,ny,nz, ...             */
#define NJD_CV_VN_D8  (NJD_VERTOFF+10) /* x,y,z,nx,ny,nz,D8888,...        */
#define NJD_CV_VN_UF  (NJD_VERTOFF+11) /* x,y,z,nx,ny,nz,UserFlags32,...  */
#define NJD_CV_VN_NF  (NJD_VERTOFF+12) /* x,y,z,nx,ny,nz,NinjaFlags32,... */
#define NJD_CV_VN_S5  (NJD_VERTOFF+13) /* x,y,z,nx,ny,nz,D565|S565,...    */
#define NJD_CV_VN_S4  (NJD_VERTOFF+14) /* x,y,z,nx,ny,nz,D4444|S565,...   */
#define NJD_CV_VN_IN  (NJD_VERTOFF+15) /* x,y,z,nx,ny,nz,D16|S16,...      */

#define NJD_CV_VNX    (NJD_VERTOFF+16) /* x,y,z,nxyz32, ...               */
#define NJD_CV_VNX_D8 (NJD_VERTOFF+17) /* x,y,z,nxyz32,D8888,...          */
#define NJD_CV_VNX_UF (NJD_VERTOFF+18) /* x,y,z,nxyz32,UserFlags32,...    */

#define NJD_CV_D8_S8  (NJD_VERTOFF+19)  /* x,y,z,D8888,S8888,...        for Ninja2   */  
#define NJD_CV_NF_D8  (NJD_VERTOFF+20)  /* x,y,z,NinjaFlags32,D8888,... for Ninja2   */  

/* chunk shape */
#define NJD_VN        (NJD_SHAPEOFF+0)  /* nx,ny,nz,... for Ninja2 Shape             */  
#define NJD_VN_D8     (NJD_SHAPEOFF+1)  /* nx,ny,nz,D8888,... for Ninja2  Shape      */  
#define NJD_D8        (NJD_SHAPEOFF+2)  /* D8888,... for Ninja2 Shape                */  

/*--------------*/
/* Chunk Vertex */
/*--------------*/
/* Flag Weight status (NF only) */
#define NJD_FW_SHIFT     8
#define NJD_FW_START    (0<<NJD_FW_SHIFT)      /* Start  */
#define NJD_FW_MIDDLE   (1<<NJD_FW_SHIFT)      /* Middle */
#define NJD_FW_END      (2<<NJD_FW_SHIFT)      /* End    */

#define NJD_FW_MASK     (0x2<<NJD_FW_SHIFT)

/* Flag Vertex */
#define NJD_FV_SHIFT     8
#define NJD_FV_CONT     (0x80<<NJD_FV_SHIFT)   /* vertex calculation continue */

/* Flag Compact Shape */
#define NJD_FV_SHAPE    (0x40<<NJD_FV_SHIFT)   /* compact shape flag */

#endif/*H_NJ_CHUNK*/

#endif/*H_NJ_CHUNK_VERTEX*/
