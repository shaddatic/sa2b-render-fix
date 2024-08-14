/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njchunk.h'
*
*   Contains structs and functions for the Ninja Chunk model
*
*   Contributors:
*     - SEGA,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _NINJA_CHUNK_H_
#define _NINJA_CHUNK_H_

/*======================================*/
/*                                      */
/*      Chunk Table                     */
/*                                      */
/*======================================*/
/* Chunk type offset */
#define NJD_NULLOFF             0 /* null chunk (16 bits size)            */
#define NJD_BITSOFF             1 /* chunk bits offset (16 bits size)     */
#define NJD_TINYOFF             8 /* chunk tiny offset (32 bits size)     */
#define NJD_MATOFF             16 /* chunk material offset (32 bits size) */
#define NJD_VERTOFF            32 /* chunk vertex offset (32 bits size)   */
#define NJD_VOLOFF             56 /* chunk volume offset (32 bits size)   */
#define NJD_STRIPOFF           64 /* chunk strip offset                   */
#define NJD_SHAPEOFF          128 /* chunk shape offset                   */
#define NJD_ENDOFF            255 /* end chunk offset (16 bits size)      */

/*------------*/
/* Chunk Null */
/*------------*/
/* <Format>=[ChunkHead(16)](16 bits chunk) */
#define NJD_CN     (NJD_NULLOFF+0)/* NULL chunk for boundary control      */

/*-----------*/
/* Chunk End */
/*-----------*/
/* <Format>=[ChunkHead(16)](16 bits chunk) */
#define NJD_CE      (NJD_ENDOFF+0)

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

/*-------------*/
/* Chunk Strip */
/*-------------*/
/* UserFlags N=0,1(16bit*1),2(16bit*2),3(16bit*3)                         */
/* <Format1>=[CFlags(8)|CHead(8)][Size(16)][UserOffset(2)|nbStrip(14)]    */
/*           [flag(1)|len(15), index0(16), index1(16),                    */
/*            index2, UserFlag2(*N), ...]                                 */
/* <Format2>=[CFlags(8)|CHead(8)][Size(16)][UserOffset(2)|nbStrip(14)]    */
/*           [flag(1)|len(15),                                            */
/*            index0(16), U0(16), V0(16),                                 */
/*            index1, U1, V1,                                             */
/*            index2, U2, V2, UserFlag2(*N), ... ]                        */
/* <Format3>=[CFlags(8)|CHead(8)][Size(16)][UserOffset(2)|nbStrip(14)]    */
/*           [flag(1)|len(15),                                            */
/*            index0(16), vnx0(16), vny0(16), vnz0(16),                   */
/*            index1, vnx1, vny1, vny1,                                   */
/*            index2, vnx2, vny2, vnz2, UserFlag2(*N),                    */
/*            index3, vnx2, vny2, vnz2, UserFlag3(*N), ... ]              */
/* <Format4>=[CFlags(8)|CHead(8)][Size(16)][UserOffset(2)|nbStrip(14)]    */
/*           [flag(1)|len(15),                                            */
/*            index0(16), U0(16), V0(16), vnx0(16), vny0(16), vnz0(16),   */
/*            index1, U1, V1, vnx1, vny1, vny1,                           */
/*            index2, U2, V2, vnx2, vny2, vnz2, UserFlag2(*N),            */
/*            index3, U3, V3, vnx3, vny3, vnz3, UserFlag3(*N), ... ]      */
/* <Format5>=[CFlags(8)|CHead(8)][Size(16)][UserOffset(2)|nbStrip(14)]    */
/*           [flag(1)|len(15),                                            */
/*            index0(16), AR0(16), GB0(16),                               */
/*            index1, AR1, GB1,                                           */
/*            index2, AR2, GB2, UserFlag2(*N),                            */
/*            index3, AR3, GB3, UserFlag3(*N), ... ]                      */
/* <Format6>=[CFlags(8)|CHead(8)][Size(16)][UserOffset(2)|nbStrip(14)]    */
/*           [flag(1)|len(15),                                            */
/*            index0(16), U0(16), V0(16), AR0(16), GB0(16),               */
/*            index1, U1, V1, AR1, GB1,                                   */
/*            index2, U2, V2, AR2, GB2, UserFlag2(*N), ... ]              */
/*                                                                        */
/* << 2para modifiler >>                                                  */
/* <Format7>=[CFlags(8)|CHead(8)][Size(16)][UserOffset(2)|nbStrip(14)]    */
/*           [flag(1)|len(15),                                            */
/*            index0(16), U0a(16), V0a(16), U0b(16), V0b(16),             */
/*            index1, U1a, V1a, U1b, V1b,                                 */
/*            index2, U2a, V2a, U2b, V2b, UserFlag2(*N), ... ]            */
/*                                                                        */
/* UV  : Uv (0-255)                                                       */
/* UVH : Uv (0-1023)                                                      */
/* VN  : Vertex Normal                                                    */
/* D8  : Strip Color ARGB8888                                             */

#define NJD_CS          (NJD_STRIPOFF+0)  /* <Format1>   */
#define NJD_CS_UVN      (NJD_STRIPOFF+1)  /* <Format2>   */
#define NJD_CS_UVH      (NJD_STRIPOFF+2)  /* <Format2>   */

#define NJD_CS_VN       (NJD_STRIPOFF+3)  /* <Format3>   */
#define NJD_CS_UVN_VN   (NJD_STRIPOFF+4)  /* <Format4>   */
#define NJD_CS_UVH_VN   (NJD_STRIPOFF+5)  /* <Format4>   */

#define NJD_CS_D8       (NJD_STRIPOFF+6)  /* <Format5>   */
#define NJD_CS_UVN_D8   (NJD_STRIPOFF+7)  /* <Format6>   */
#define NJD_CS_UVH_D8   (NJD_STRIPOFF+8)  /* <Format6>   */

/* 2para modifier */
#define NJD_CS_2        (NJD_STRIPOFF+9)  /* <Format1>   */
#define NJD_CS_UVN2     (NJD_STRIPOFF+10) /* <Format7>   */
#define NJD_CS_UVH2     (NJD_STRIPOFF+11) /* <Format7>   */

/*======================================*/
/*                                      */
/*      Chunk Flags                     */
/*                                      */
/*======================================*/
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

/*--------------------*/
/* Chunk Multi Lights */
/*--------------------*/

#define    NJD_CNK_EASY_MULTILIGHT_1            1
#define    NJD_CNK_EASY_MULTILIGHT_2            2
#define    NJD_CNK_EASY_MULTILIGHT_3            3
#define    NJD_CNK_EASY_MULTILIGHT_4            4
#define    NJD_CNK_EASY_MULTILIGHT_5            5
#define    NJD_CNK_EASY_MULTILIGHT_6            6

#define    NJD_CNK_EASY_MULTILIGHT_ALL          0

#define    NJD_CNK_SIMPLE_MULTILIGHT_1          1
#define    NJD_CNK_SIMPLE_MULTILIGHT_2          2
#define    NJD_CNK_SIMPLE_MULTILIGHT_3          3
#define    NJD_CNK_SIMPLE_MULTILIGHT_4          4
#define    NJD_CNK_SIMPLE_MULTILIGHT_5          5
#define    NJD_CNK_SIMPLE_MULTILIGHT_6          6

#define    NJD_CNK_SIMPLE_MULTILIGHT_ALL        0


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

/*-------------*/
/* Chunk Strip */
/*-------------*/
/** Flag STrip **/
/* <Format>=[ChunkFlags(8)|ChunkHead(8)](16 bits size)   */
/* IL  : Ignore light                                    */
/* IS  : Ignore specular                                 */
/* IA  : Ignore ambient                                  */
/* UA  : Use alpha                                       */
/* DB  : Double side                                     */
/* FL  : Flat shading                                    */
/* ENV : Environment                                     */
/* NAT : No Alpha Test                                   */
#define NJD_FST_SHIFT      8
#define NJD_FST_IL        (0x01<<NJD_FST_SHIFT)
#define NJD_FST_IS        (0x02<<NJD_FST_SHIFT)
#define NJD_FST_IA        (0x04<<NJD_FST_SHIFT)
#define NJD_FST_UA        (0x08<<NJD_FST_SHIFT)
#define NJD_FST_DB        (0x10<<NJD_FST_SHIFT)
#define NJD_FST_FL        (0x20<<NJD_FST_SHIFT)
#define NJD_FST_ENV       (0x40<<NJD_FST_SHIFT)
#define NJD_FST_NAT       (0x80<<NJD_FST_SHIFT)
#define NJD_FST_MASK      (0xFF<<NJD_FST_SHIFT)

/** UserFlag Offset Mask **/
#define NJD_UFO_SHIFT      14
#define NJD_UFO_0         (0<<NJD_UFO_SHIFT)
#define NJD_UFO_1         (1<<NJD_UFO_SHIFT)
#define NJD_UFO_2         (2<<NJD_UFO_SHIFT)
#define NJD_UFO_3         (3<<NJD_UFO_SHIFT)
#define NJD_UFO_MASK      (0x3<<NJD_UFO_SHIFT) /* 0 - 3 */

#define NJD_EVAL_UNIT_POS       BIT_0   /* ignore translation */
#define NJD_EVAL_UNIT_ANG       BIT_1   /* ignore rotation */
#define NJD_EVAL_UNIT_SCL       BIT_2   /* ignore scaling */
#define NJD_EVAL_HIDE           BIT_3   /* do not draw model */
#define NJD_EVAL_BREAK          BIT_4   /* terminate tracing children */
#define NJD_EVAL_ZXY_ANG        BIT_5 
#define NJD_EVAL_SKIP           BIT_6
#define NJD_EVAL_SHAPE_SKIP     BIT_7
#define NJD_EVAL_CLIP           BIT_8
#define NJD_EVAL_MODIFIER       BIT_9
#define NJD_EVAL_QUATERNION     BIT_10
#define NJD_EVAL_ROTATE_BASE    BIT_11
#define NJD_EVAL_ROTATE_SET     BIT_12
#define NJD_EVAL_ENVELOPE       BIT_13
#define NJD_EVAL_MASK           0x3fff 

/*------------------*/
/*  Structure       */
/*------------------*/
/*
 * NJS_CNK_MODEL
 */
typedef struct {
    Sint32            *vlist;   /* vertex list                  */
    Sint16            *plist;   /* polygon list                 */
    NJS_POINT3        center;   /* model center                 */
    Float                  r;   /* radius                       */
} NJS_CNK_MODEL;

/*
 * NJS_CNK_OBJECT
 */
typedef struct cnkobj {
    Uint32          evalflags;  /* evalation flags              */
    NJS_CNK_MODEL*  model;      /* model data pointer           */
    Float           pos[3];     /* translation                  */
    Angle           ang[3];     /* rotation or im part of quat  */
    Float           scl[3];     /* scaling                      */
    struct cnkobj*  child;      /* child object                 */
    struct cnkobj*  sibling;    /* sibling object               */
    Float           re_quat;    /* re part of quat              */
} NJS_CNK_OBJECT;

typedef struct {
    Float       dmy[16];
} NJS_VERTEX_BUF;           /* TotalSize        : 64        */


void    njInit3D( NJS_VERTEX_BUF* vbuf, Int vn );     // MIA
void    njControl3D( Uint32 flag );
void    njSetConstantAttr( Uint32 and_attr, Uint32 or_attr );
void    njSetConstantMaterial( NJS_ARGB* mat );
void    njSetDepthQueue( Float dnear, Float dfar );   // MIA

/*
    Internals
*/
Bool    njCnkModelClip( NJS_CNK_MODEL* model );
void    njCnkTransformObject( NJS_CNK_OBJECT* object, int(__cdecl* callback)(NJS_CNK_MODEL*) );

/*
    Internal Draw
*/
Sint32  _njCnkDrawModel( NJS_CNK_MODEL* model );

/*
    Draw
*/
Sint32  njCnkDrawModel( NJS_CNK_MODEL* model );
void    njCnkDrawObject( NJS_CNK_OBJECT* object );

void    njCnkDrawModel_Broken( NJS_CNK_MODEL* model );

/*
    Blending mode
*/
void    njSetCnkBlendMode( Uint32 attr );

#endif /* _NINJA_CHUNK_H_ */

/*
 * End Of File
 */
