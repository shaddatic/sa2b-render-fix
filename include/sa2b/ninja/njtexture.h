/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njtexture.h'
*
*   Description:
*     Ninja texture header.
*
*   Contributors:
*     - SEGA,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_NJ_TEXTURE
#define H_NJ_TEXTURE

/************************/
/*  External Headers    */
/************************/
/****** System **********************************************************************/
#include <sa2b/shinobi/sg_xpt.h> /* shinobi types                                   */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/njcommon.h> /* ninja common                                    */

EXTERN_START

/************************/
/*  Constants           */
/************************/
/****** Texture Size ****************************************************************/
#define NJD_TEXSIZE_1           (1)
#define NJD_TEXSIZE_2           (2)
#define NJD_TEXSIZE_4           (4)
#define NJD_TEXSIZE_8           (8)
#define NJD_TEXSIZE_16          (16)
#define NJD_TEXSIZE_32          (32)
#define NJD_TEXSIZE_64          (64)
#define NJD_TEXSIZE_128         (128)
#define NJD_TEXSIZE_256         (256)
#define NJD_TEXSIZE_512         (512)
#define NJD_TEXSIZE_1024        (1024)

/****** Texture Attribute ***********************************************************/
/*
*   |31 -  21|20 - 17|    16      |15 - 0|
*    texattr reserved texcontinue  pvmentryId
*/
#define NJD_TEXATTR_TYPE_FILE           0
#define NJD_TEXATTR_TYPE_MEMORY         BIT_30
#define NJD_TEXATTR_TYPE_SURFACE        BIT_27
#define NJD_TEXATTR_TYPE_SYSAREA        BIT_26

#define NJD_TEXATTR_READAREA_MASK       (BIT_31)
#define NJD_TEXATTR_READTYPE_MASK       (BIT_30|BIT_28|BIT_27|BIT_26)

#define NJD_TEXATTR_PALGLOBALINDEX      BIT_24
#define NJD_TEXATTR_GLOBALINDEX         BIT_23

#define NJD_TEXATTR_REGISTRATION        BIT_21
#define NJD_TEXATTR_HEADER              BIT_20
#define NJD_TEXATTR_MASK                0xFFFE0000

#define NJD_TEXATTR_TEXCONTINUE         BIT_16

/****** Palette Bank ****************************************************************/
/*
*   texaddr
*   |31 - 26|25   -     0|
*     bank    globalIndex
*/
#define NJD_TEXBANK_SHIFT           (26)
#define NJD_TEXBANK_MASK            (0xFC000000)
#define NJD_TEXPALGLOBAL_MASK       (0x03FFFFFF)

/****** Texture Color Format ********************************************************/
#define NJD_TEXFMT_ARGB_1555            (0x00)
#define NJD_TEXFMT_RGB_565              (0x01)
#define NJD_TEXFMT_ARGB_4444            (0x02)
#define NJD_TEXFMT_YUV_422              (0x03)
#define NJD_TEXFMT_BUMP                 (0x04)
#define NJD_TEXFMT_RGB_555              (0x05)
#define NJD_TEXFMT_ARGB_8888            (0x06)
#define NJD_TEXFMT_YUV_420              (0x06)
#define NJD_TEXFMT_COLOR_MASK           (0xFF)

/****** Texture Type Format *********************************************************/
#define NJD_TEXFMT_TWIDDLED             (0x0100)
#define NJD_TEXFMT_TWIDDLED_MM          (0x0200)
#define NJD_TEXFMT_VQ                   (0x0300)
#define NJD_TEXFMT_VQ_MM                (0x0400)
#define NJD_TEXFMT_PALETTIZE4           (0x0500)
#define NJD_TEXFMT_PALETTIZE4_MM        (0x0600)
#define NJD_TEXFMT_PALETTIZE8           (0x0700)
#define NJD_TEXFMT_PALETTIZE8_MM        (0x0800)
#define NJD_TEXFMT_RECTANGLE            (0x0900)
#define NJD_TEXFMT_STRIDE               (0x0B00)
#define NJD_TEXFMT_TWIDDLED_RECTANGLE   (0x0D00)
#define NJD_TEXFMT_ABGR                 (0x0E00)
#define NJD_TEXFMT_ABGR_MM              (0x0F00)

#define NJD_TEXFMT_SMALLVQ              (0x1000)
#define NJD_TEXFMT_SMALLVQ_MM           (0x1100)
#define NJD_TEXFMT_TWIDDLED_MM_DMA      (0x1200)

#define NJD_TEXFMT_TYPE_MASK            (0xFF00)

/****** njCalcTexture ***************************************************************/
#define NJD_TEXMEM_FREESIZE             (0x00000000)
#define NJD_TEXMEM_MAXBLOCK             (0x00000001)
#define NJD_TEXMEM_MAXSIZE              (0x00000002)

/****** Texture Error ***************************************************************/
#define NJD_TEXERR_OTHER                (1)
#define NJD_TEXERR_FILEOPEN             (2)
#define NJD_TEXERR_EXTND                (3)
#define NJD_TEXERR_HEADER               (4)
#define NJD_TEXERR_FILELOAD             (5)
#define NJD_TEXERR_SURFACE              (6)
#define NJD_TEXERR_MAINMEMORY           (7)
#define NJD_TEXERR_TEXMEMLOAD           (8)
#define NJD_TEXERR_GLOBALINDEX          (9)

/****** Initial Values **************************************************************/
#define NJD_GLOBALINDEX_FIRST_VAL       (0xFFFFFFFF)
#define NJD_BANK_FIRST_VAL              (0xFFFFFFFF)

/****** Section Size ****************************************************************/
#define NJD_GD_SECT_SIZE        (2048)

/****** Palette Color ***************************************************************/
#define NJD_TEXPALETTE_16BPP    (16)
#define NJD_TEXPALETTE_32BPP    (32)

/****** Bit Depth *******************************************************************/
#define NJD_BITDEPTH_16         (1)
#define NJD_BITDEPTH_24         (2)
#define NJD_BITDEPTH_32         (3)

/****** Texture Surface Type ********************************************************/
#define NJD_SURFACETYPE_FRAMEBUFFER     (1)
#define NJD_SURFACETYPE_TEXTURE         (2)
#define NJD_SURFACETYPE_SMALLVQ_TEXTURE (3)

/****** Pixel Format ****************************************************************/
#define NJD_PIXELFORMAT_ARGB1555        (0x00000000)
#define NJD_PIXELFORMAT_RGB565          (0x08000000)
#define NJD_PIXELFORMAT_ARGB4444        (0x10000000)
#define NJD_PIXELFORMAT_YUV422          (0x18000000)
#define NJD_PIXELFORMAT_BUMP            (0x20000000)
#define NJD_PIXELFORMAT_PALETTIZED_4BPP (0x28000000)
#define NJD_PIXELFORMAT_PALETTIZED_8BPP (0x30000000)

/****** Surface Flag ****************************************************************/
#define NJD_SURFACEFLAGS_MIPMAPED       (0x80000000)
#define NJD_SURFACEFLAGS_VQ             (0x40000000)
#define NJD_SURFACEFLAGS_NOTWIDDLED     (0x04000000)
#define NJD_SURFACEFLAGS_TWIDDLED       (0x00000000)
#define NJD_SURFACEFLAGS_STRIDE         (0x02000000)
#define NJD_SURFACEFLAGS_PALETTIZED     (0x00008000)

#define NJD_SURFACEFLAGS_VSIZE8         (0x00000000)
#define NJD_SURFACEFLAGS_VSIZE16        (0x00000001)
#define NJD_SURFACEFLAGS_VSIZE32        (0x00000002)
#define NJD_SURFACEFLAGS_VSIZE64        (0x00000003)
#define NJD_SURFACEFLAGS_VSIZE128       (0x00000004)
#define NJD_SURFACEFLAGS_VSIZE256       (0x00000005)
#define NJD_SURFACEFLAGS_VSIZE512       (0x00000006)
#define NJD_SURFACEFLAGS_VSIZE1024      (0x00000007)
#define NJD_SURFACEFLAGS_USIZE8         (0x00000000)
#define NJD_SURFACEFLAGS_USIZE16        (0x00000008)
#define NJD_SURFACEFLAGS_USIZE32        (0x00000010)
#define NJD_SURFACEFLAGS_USIZE64        (0x00000018)
#define NJD_SURFACEFLAGS_USIZE128       (0x00000020)
#define NJD_SURFACEFLAGS_USIZE256       (0x00000028)
#define NJD_SURFACEFLAGS_USIZE512       (0x00000030)
#define NJD_SURFACEFLAGS_USIZE1024      (0x00000038)

/************************/
/*  Macros              */
/************************/
/****** Bank/Gbix Value *************************************************************/
#define NJM_BANKGLOBALINDEX(bank,globalIndex)   (((bank)<<NJD_TEXBANK_SHIFT)|((globalIndex)&NJD_TEXPALGLOBAL_MASK))

/****** Get Texture Info ************************************************************/
#define NJM_TEXTURE_WIDTH(texlist,n)        (((NJS_TEXMANAGE*)(texlist)->textures[(n)].texaddr)->texsys->texsurface.nWidth)
#define NJM_TEXTURE_HEIGHT(texlist,n)       (((NJS_TEXMANAGE*)(texlist)->textures[(n)].texaddr)->texsys->texsurface.nHeight)
#define NJM_TEXTURE_GLOBALINDEX(texlist,n)  (((NJS_TEXMANAGE*)(texlist)->textures[(n)].texaddr)->texsys->globalIndex)
#define NJM_TEXTURE_SIZE(texlist,n)         (((NJS_TEXMANAGE*)(texlist)->textures[(n)].texaddr)->texsys->texsurface.TextureSize)
#define NJM_TEXTURE_TYPE(texlist,n)        ((((NJS_TEXMANAGE*)(texlist)->textures[(n)].texaddr)->texsys->texsurface.Type) >> 16)
#define NJM_TEXTURE_SURFACEFLAG(texlist,n)  (((NJS_TEXMANAGE*)(texlist)->textures[(n)].texaddr)->texsys->texsurface.fSurfaceFlags)

/************************/
/*  Structures          */
/************************/
/****** Texture Surface *************************************************************/
typedef struct
{
    Uint32 Type;                /* surface type                                     */
    Uint32 BitDepth;            /* bit depth                                        */
    Uint32 PixelFormat;         /* pixel format                                     */
    Uint32 nWidth;              /* width                                (in pixels) */
    Uint32 nHeight;             /* height                               (in pixels) */
    Uint32 TextureSize;         /* total size                            (in bytes) */
    Uint32 fSurfaceFlags;       /* surface flags                                    */
    Uint32* pSurface;           /* pointer to surface data                          */
}
NJS_TEXSURFACE;

/****** Texture System **************************************************************/
typedef struct
{
    Uint32          globalIndex; /* global index value                              */
    NJS_TEXSURFACE  texsurface;  /* texture surface data                            */
    Int             count;       /* reference count                                 */
}
NJS_TEXSYSTEM;

/****** Texture Manage **************************************************************/
typedef struct
{
    Uint32          tspparam;   /* internal tsp param                               */
    Uint32          texparam;   /* internal tex param                               */
    Uint32          bank;       /* palette texture bank number         (-1 == none) */
    NJS_TEXSYSTEM*  texsys;     /* texture system struct pointer                    */
    Int             count;      /* reference count                                  */
    Uint32          texflag;    /* texture flags                           (unused) */
}
NJS_TEXMANAGE;

/****** Texture Palette *************************************************************/
typedef struct
{
    void*           palette;    /* palette pointer                                  */
    Uint16          mode;       /* color mode                                       */
    Sint16          bank;       /* bank                                             */
    Sint16          offset;     /* entry offset                                     */
    Sint16          count;      /* entry count                                      */
}
NJS_TEXPALETTE;

/****** Texture Error Status ********************************************************/
typedef struct
{
    Uint32	n;                  /* texture number (in texlist) where error occured  */
    Uint32	globalIndex;        /* global index of texture where error occured      */
    Sint32	texerr;             /* texture error code                               */
    Sint32	gdstat;             /* gd status code                                   */
    Sint32	gderr;              /* gd error code                                    */
    Sint32	reserved0;          /* reserved                                         */
    Sint32	reserved1;          /* reserved                                         */
    Sint32	reserved2;          /* reserved                                         */
}
NJS_TEXERRSTAT;

/****** PVR Texture Header *******************************************************&&*/
typedef struct
{
    Uint32 nTextureType;        /* pvr texture type                                 */
    Uint16 nWidth;              /* texture width                        (in pixels) */
    Uint16 nHeight;             /* texture height                       (in pixels) */
}
NJS_PVRHEADERDATA;

/************************/
/*  Structures          */
/************************/
/****** Texture Manage **************************************************************/
#define _nj_texmanage           DATA_REF(NJS_TEXMANAGE*, 0x02670590)
#define _nj_texmanagesize       DATA_REF(Int           , 0x0267058C)

/****** Texture System **************************************************************/
#define _nj_texsys              DATA_REF(NJS_TEXSYSTEM*, 0x025F0278)
#define _nj_texsyssize          DATA_REF(Int           , 0x025EFFE0)

/****** Texture Count ***************************************************************/
#define _nj_tex_count           DATA_REF(Sint32        , 0x025F0260)

/****** Texture Error ***************************************************************/
#define _nj_texerr_             DATA_REF(NJS_TEXERRSTAT, 0x025F0280)

/************************/
/*  Prototypes          */
/************************/
/****** Init ************************************************************************/
/*
*   Description:
*     Init and set Ninja texture manage buffer. Given buffer will be set to
*   '_nj_texmanage' and its 'size' variable.
*
*   Parameters:
*     - pmng        : texture manage buffer
*     - nmng        : texture manage count
*     - psys        : texture system buffer
*     - nsys        : texture system count
*/
void    njInitTexManage( NJS_TEXMANAGE *pmng, Int nmng );
/*
*   Description:
*     Init and set Ninja texture system buffer. Given buffer will be set to
*   '_nj_texsys' and its 'size' variable.
*
*   Parameters:
*     - pmng        : texture manage buffer
*     - nmng        : texture manage count
*     - psys        : texture system buffer
*     - nsys        : texture system count
*/
void    njInitTexSystem( NJS_TEXSYSTEM *psys, Int nsys );

/****** Init Ex *********************************************************************/
/*
*   Description:
*     Init and set both Ninja texture system buffers in one function call. Given
*   buffers will be set to '_nj_texmanage' and '_nj_texsys' and their 'size'
*   variables.
*
*   Notes:
*     - Internally calls 'njInitTexManage/System'
*
*   Parameters:
*     - pmng        : texture manage buffer
*     - nmng        : texture manage count
*     - psys        : texture system buffer
*     - nsys        : texture system count
*/
void    njInitTextureEx( NJS_TEXMANAGE *pmng, Int nmng, NJS_TEXSYSTEM *psys, Int nsys );

/****** Set Texture *****************************************************************/
/*
*   Description:
*     Set current Texlist structure.
*
*   Parameters:
*     - texlist     : texlist pointer
*
*   Returns:
*     Always '1'.
*/
Sint32  njSetTexture( NJS_TEXLIST* texlist );
/*
*   Description:
*     Set the active texture for use with draw functions via texture index in the
*   current texlist.
*
*   Parameters:
*     - n           : texname index into current texlist
*
*   Returns:
*     '1' on success; or '-1' on failure.
*/
Sint32  njSetTextureNum( Uint32 n );
/*
*   Description:
*     Set the active texture for use with draw functions via a global index value.
*   Seaches all loaded textures and picks the first GBIX match.
*
*   Parameters:
*     - globalIndex : global index search value
*
*   Returns:
*     '1' on success; or '-1' on failure.
*/
Sint32  njSetTextureNumG( Uint32 globalIndex );

/****** Get Texture *****************************************************************/
/*
*   Description:
*     Get the current texlist.
*
*   Returns:
*     Current texlist pointer.
*/
NJS_TEXLIST* njGetCurrentTexList( void );

/****** Release Texture *************************************************************/
/*
*   Description:
*     Release all textures inside a texlist.
*
*   Returns:
*     '1' on success; or '-1' if any error (check '_nj_texerr_').
*/
Sint32  njReleaseTexture( NJS_TEXLIST* texlist );
/*
*   Description:
*     Release all loaded textures.
*/
void    njReleaseTextureAll( void );

/****** Palette *********************************************************************/
/*
*   Description:
*     Set palette bank index of texture via texture index into the current texlist.
*
*   Notes:
*     - a bank value of '-1' will disable palette
*
*   Parameters:
*     - n           : texname index into current texlist
*     - bank        : palette bank to set
*/
void    njSetPaletteBankNum( Uint32 n, Uint32 bank );
/*
*   Description:
*     Set palette bank index of texture via global index value. Seaches all loaded
*   textures and picks the first GBIX match.
*
*   Notes:
*     - a bank value of '-1' will disable palette
*
*   Parameters:
*     - globalIndex : global index search value
*     - bank        : palette bank to set
*/
void    njSetPaletteBankNumG( Uint32 globalIndex, Uint32 bank );

EXTERN_END

#endif/*H_NJ_TEXTURE*/
