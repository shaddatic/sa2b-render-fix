/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njchunk.h'
*
*   Description:
*     Defines Ninja Chunk vertex data chunk types
*
*   Contributors:
*     - SEGA
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_NJ_CHUNK_VERTEX
#define H_NJ_CHUNK_VERTEX

#define NJD_VERTOFF           ( 32) /* chunk vertex offset          (variable size) */

/************************************************/
/*                                              */
/*    Chunk Table                               */
/*                                              */
/************************************************/
/*
*   Notes:
*     - The usage of '<' and '>' defines a data chunk
*     - The usage of '[' and ']' defines 16 or 32 bit chunk (plist or vlist)
*     - The usage of '(' and ')' defines data size in bits
*     - All notations assume little-endian
*     - Any omitted bits are null from the left
*
*   Definitions:
*     - CNK_OFFSET < [name_of_data(size_in_bits)] > size(size_of_chunk)
*/

/************************/
/*  Chunk Vertex        */
/************************/
/****** Chunk Vertex Header *********************************************************/
/*
*   Description:
*     Chunk vertex information
*
*   Header Format:
*     u8  [cnkhead    ] : chunk offset type
*     u8  [headbits   ] : headbits for offset type
*     u16 [size       ] : size of data chunk
*     u16 [indexoffset] : offset into vertex buffer
*     u16 [nbindeces  ] : number of vertex entries
* 
*   Offset Types:
*     - SH  : SH4 optimized
*     - VN  : vertex normals
*     - VNX : 32bit vertex normals                [(null(2)|x(10)|y(10)|z(10))] (32)
*     - D8  : ARGB8888 vertex diffuse
*     - S5  : RGB565 vertex diffuse and RGB565 specular 
*     - S4  : RGB444 vertex diffuse and RGB565 specular
*     - IN  : 32bit intensity                        [diffuse(16)|specular(16)] (32)
*     - NF  : ninja flag for vertex weights
*     - UF  : user flag
*/

/****** Chunk Vertex Types **********************************************************/
/*
*   Description:
*     Chunk vertex optimized for SH4
* 
*   Format:
*     f32 [x  ]  : x position
*     f32 [y  ]  : y position
*     f32 [z  ]  : z position
*     f32 [1.f]  : boundary control 
*/
#define NJD_CV_SH     (NJD_VERTOFF+0)
/*
*   Description:
*     Chunk vertex and normal optimized for SH4
* 
*   Format:
*     f32 [x  ]  : x position
*     f32 [y  ]  : y position
*     f32 [z  ]  : z position
*     f32 [1.f]  : boundary control
*     f32 [vx ]  : x normal
*     f32 [vy ]  : y normal
*     f32 [vz ]  : z normal
*     f32 [0.f]  : boundary control
*/
#define NJD_CV_VN_SH  (NJD_VERTOFF+1)
/*
*   Description:
*     Chunk vertex
* 
*   Format:
*     f32 [x] : x position
*     f32 [y] : y position
*     f32 [z] : z position
*/
#define NJD_CV        (NJD_VERTOFF+2)
/*
*   Description:
*     Chunk vertex and diffuse ARGB
* 
*   Format:
*     f32 [x   ] : x position
*     f32 [y   ] : y position
*     f32 [z   ] : z position
*     u32 [diff] : diffuse in D8888
*/
#define NJD_CV_D8     (NJD_VERTOFF+3)
/*
*   Description:
*     Chunk vertex and user flags
* 
*   Format:
*     f32 [x     ] : x position
*     f32 [y     ] : y position
*     f32 [z     ] : z position
*     u32 [usrflg] : user flags
*/
#define NJD_CV_UF     (NJD_VERTOFF+4)
/*
*   Description:
*     Chunk vertex and ninja flags
*
*   Headbits:
*     Weight status: Start, Middle, End (0~3)
* 
*   Format:
*     f32 [x        ] : x position
*     f32 [y        ] : y position
*     f32 [z        ] : z position
*     u16 [vtxoffset] : ninja flag, vertex buffer offset
*     u16 [vtxweight] : ninja flag, vertex weight 0~255 (0.f~1.f)
*/
#define NJD_CV_NF     (NJD_VERTOFF+5)
/*
*   Description:
*     Chunk vertex, diffuse RGB, and specular
*
*   Format:
*     f32 [x]    : x position
*     f32 [y]    : y position
*     f32 [z]    : z position
*     u16 [diff] : diffuse in D565
*     u16 [spec] : specular in S565
*/
#define NJD_CV_S5     (NJD_VERTOFF+6)
/*
*   Description:
*     Chunk vertex, diffuse ARGB, and specular
*
*   Format:
*     f32 [x]    : x position
*     f32 [y]    : y position
*     f32 [z]    : z position
*     u16 [diff] : diffuse in D4444
*     u16 [spec] : specular in S565
*/
#define NJD_CV_S4     (NJD_VERTOFF+7)
/*
*   Description:
*     Chunk vertex and intensity
*
*   Format:
*     f32 [x]    : x position
*     f32 [y]    : y position
*     f32 [z]    : z position
*     s16 [diff] : diffuse intensity 0~32767 (0.f~1.f)
*     s16 [spec] : specular intensity 0~32767 (0.f~1.f)
*/
#define NJD_CV_IN     (NJD_VERTOFF+8)
/*
*   Description:
*     Chunk vertex and normal
* 
*   Format:
*     f32 [x]  : x position
*     f32 [y]  : y position
*     f32 [z]  : z position
*     f32 [vx] : x normal
*     f32 [vy] : y normal
*     f32 [vz] : z normal
*/
#define NJD_CV_VN     (NJD_VERTOFF+9)
/*
*   Description:
*     Chunk vertex, normal, and diffuse ARGB
* 
*   Format:
*     f32 [x]    : x position
*     f32 [y]    : y position
*     f32 [z]    : z position
*     f32 [vx]   : x normal
*     f32 [vy]   : y normal
*     f32 [vz]   : z normal
*     u32 [diff] : diffuse in D8888
*/
#define NJD_CV_VN_D8  (NJD_VERTOFF+10)

#endif/*H_NJ_CHUNK_VERTEX*/
