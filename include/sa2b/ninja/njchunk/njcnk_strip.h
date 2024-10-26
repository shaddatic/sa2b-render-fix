/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njchunk/njcnk_strip.h'
*
*   Description:
*     Definitions for the Ninja Chunk 'strip' data offset
*
*   Contributors:
*     - SEGA
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_NJ_CHUNK_STRIP
#define H_NJ_CHUNK_STRIP

#ifndef H_NJ_CHUNK
#   error "Ninja Chunk sub-header included without first including 'njchunk.h'"
#else

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

#endif/*H_NJ_CHUNK*/

#endif/*H_NJ_CHUNK_STRIP*/
