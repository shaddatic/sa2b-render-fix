/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njtexture.h'
*
*   Contains flags, macros, and functions for Ninja textures
*
*   Contributors:
*     - SEGA,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _NJTEXTURE_H_
#define _NJTEXTURE_H_

/*--------------------------------------*/
/*      Texture Define                  */
/*--------------------------------------*/
/* Texture Size */
#define NJD_TEXSIZE_1                   1
#define NJD_TEXSIZE_2                   2
#define NJD_TEXSIZE_4                   4
#define NJD_TEXSIZE_8                   8
#define NJD_TEXSIZE_16                  16
#define NJD_TEXSIZE_32                  32
#define NJD_TEXSIZE_64                  64
#define NJD_TEXSIZE_128                 128
#define NJD_TEXSIZE_256                 256
#define NJD_TEXSIZE_512                 512
#define NJD_TEXSIZE_1024                1024

/* Texture Attr */
/*
|31 -  21|20 - 17|16          |15 - 0|
 texattr reserved texcontinue  pvmentryId
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


/*
    texaddr
    |31 - 26|25   -     0|
      bank    globalIndex
*/
#define NJD_TEXBANK_SHIFT           (26)
#define NJD_TEXBANK_MASK            (0xFC000000)
#define NJD_TEXPALGLOBAL_MASK       (0x03FFFFFF)

/* Texture Color Format */
#define NJD_TEXFMT_ARGB_1555            (0x00)
#define NJD_TEXFMT_RGB_565              (0x01)
#define NJD_TEXFMT_ARGB_4444            (0x02)
#define NJD_TEXFMT_YUV_422              (0x03)
#define NJD_TEXFMT_BUMP                 (0x04)
#define NJD_TEXFMT_RGB_555              (0x05)
#define NJD_TEXFMT_ARGB_8888            (0x06)
#define NJD_TEXFMT_YUV_420              (0x06)
#define NJD_TEXFMT_COLOR_MASK           (0xFF)

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

#define NJD_TEXMEM_FREESIZE             (0x00000000)
#define NJD_TEXMEM_MAXBLOCK             (0x00000001)
#define NJD_TEXMEM_MAXSIZE              (0x00000002)

#define NJD_TEXERR_OTHER                (1)
#define NJD_TEXERR_FILEOPEN             (2)
#define NJD_TEXERR_EXTND                (3)
#define NJD_TEXERR_HEADER               (4)
#define NJD_TEXERR_FILELOAD             (5)
#define NJD_TEXERR_SURFACE              (6)
#define NJD_TEXERR_MAINMEMORY           (7)
#define NJD_TEXERR_TEXMEMLOAD           (8)
#define NJD_TEXERR_GLOBALINDEX          (9)

#define NJD_START_GLOBALINEX            (0xFFFFFFEF)
#define NJD_GLOBAXINDEX_FIRST_VAL       (0xFFFFFFFF)
#define NJD_BANK_FIRST_VAL              (0xFFFFFFFF)

#define NJD_GD_SECT_SIZE        2048

/* Palette Color bpp */
#define NJD_TEXPALETTE_16BPP    16
#define NJD_TEXPALETTE_32BPP    32

/* Bit Depth */
#define NJD_BITDEPTH_16     1
#define NJD_BITDEPTH_24     2
#define NJD_BITDEPTH_32     3

/* SurfaceType */
#define NJD_SURFACETYPE_FRAMEBUFFER     1
#define NJD_SURFACETYPE_TEXTURE         2
#define NJD_SURFACETYPE_SMALLVQ_TEXTURE 3

/* Pixelformat */
#define NJD_PIXELFORMAT_ARGB1555        (0x00000000)
#define NJD_PIXELFORMAT_RGB565          (0x08000000)
#define NJD_PIXELFORMAT_ARGB4444        (0x10000000)
#define NJD_PIXELFORMAT_YUV422          (0x18000000)
#define NJD_PIXELFORMAT_BUMP            (0x20000000)
#define NJD_PIXELFORMAT_PALETTIZED_4BPP (0x28000000)
#define NJD_PIXELFORMAT_PALETTIZED_8BPP (0x30000000)

/* Surfaceflag */
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

/*
 *  TEXTURE MACRO
 */
#define NJM_BANKGLOBALINDEX(bank,globalIndex)   (((bank) << NJD_TEXBANK_SHIFT)|((globalIndex)&NJD_TEXPALGLOBAL_MASK))

#define NJM_TEXTURE_WIDTH(texlist,n) (((NJS_TEXMANAGE*)(texlist)->textures[(n)].texaddr)->texsys->texsurface.nWidth)
#define NJM_TEXTURE_HEIGHT(texlist,n) (((NJS_TEXMANAGE*)(texlist)->textures[(n)].texaddr)->texsys->texsurface.nHeight)
#define NJM_TEXTURE_GLOBALINDEX(texlist,n) (((NJS_TEXMANAGE*)(texlist)->textures[(n)].texaddr)->texsys->globalIndex)
#define NJM_TEXTURE_SIZE(texlist,n) (((NJS_TEXMANAGE*)(texlist)->textures[(n)].texaddr)->texsys->texsurface.TextureSize)
#define NJM_TEXTURE_TYPE(texlist,n) ((((NJS_TEXMANAGE*)(texlist)->textures[(n)].texaddr)->texsys->texsurface.Type) >> 16)
#define NJM_TEXTURE_SURFACEFLAG(texlist,n) (((NJS_TEXMANAGE*)(texlist)->textures[(n)].texaddr)->texsys->texsurface.fSurfaceFlags)

#define NJM_TEXMEMLIST(texlist, n)  ((NJS_TEXMEMLIST*)((texlist)->textures[(n)].texaddr))

typedef struct {
    Uint32 Type;
    Uint32 BitDepth;
    Uint32 PixelFormat;
    Uint32 nWidth;
    Uint32 nHeight;
    Uint32 TextureSize;
    Uint32 fSurfaceFlags;
    Uint32* pSurface;
}NJS_TEXSURFACE;

typedef struct {
    Uint32          globalIndex;
    NJS_TEXSURFACE  texsurface;
    Int             count;
}NJS_TEXSYSTEM;

typedef struct {
    Uint32          tspparam;
    Uint32          texparam;
    Uint32          bank;
    NJS_TEXSYSTEM*  texsys;
    Int             count;
    Uint32          texflag;
}NJS_TEXMANAGE;

typedef struct {
    void*           palette;    /*  palette pointer             */
    Uint16          mode;       /*  color mode                  */
    Sint16          bank;       /*  bank                        */
    Sint16          offset;     /*  entry offset                */
    Sint16          count;      /*  entry count                 */
}NJS_TEXPALETTE;

typedef struct {
    Uint32  n;
    Uint32  globalIndex;
    Sint32  texerr;
    Sint32  gdstat;
    Sint32  gderr;
    Sint32  reserved0;
    Sint32  reserved1;
    Sint32  reserved2;
}NJS_TEXERRSTAT;

typedef struct {
    Uint32 nTextureType;
    Uint16 nWidth;
    Uint16 nHeight;
}NJS_PVRHEADERDATA;

typedef struct {
    void*              texaddr; /* texture address              */
    NJS_TEXSURFACE  texsurface; /* texture surface              */
} NJS_TEXINFO;

typedef NJS_TEXMANAGE   NJS_TEXMNGDEBUG[100];
typedef NJS_TEXSYSTEM   NJS_TEXSYSDEBUG[100];

/* Set & Get */
Sint32 njSetTexture(NJS_TEXLIST* texlist);
NJS_TEXLIST* njGetCurrentTexList(void);
Sint32 njSetTextureNum(Uint32 n);
Sint32 njSetTextureNumG(Uint32 globalIndex);
void njSetRenderWidth(Uint32 nWidth);
void njSetTextureInfo(NJS_TEXINFO* info, Sint8* pTexture, Sint32 nTextureType, Sint32 nWidth, Sint32 nHeight);
void njSetTextureName(NJS_TEXNAME* texname, void* addr, Uint32 globalIndex, Uint32 attr);
void njSetTextureParamEx(NJS_TEXMANAGE* pmng);
void njSetTextureSurface(NJS_TEXLIST* texlist, Uint32 n, Uint32 bank, void* surface);
void njSetTextureSurfaceNum(Uint32 n, Uint32 bank, void* surface);
void njSetTextureSurfaceNumG(Uint32 globalIndex, Uint32 bank, void* surface);
void njClearTextureSurface(NJS_TEXLIST* texlist, Uint32 n);
void njClearTextureSurfaceNum(Uint32 n);
void njClearTextureSurfaceNumG(Uint32 globalIndex);

/* Release Texture */
Sint32 njReleaseTexture(NJS_TEXLIST* texlist);
Sint32 njReleaseTextureNum(Uint32 n);
Sint32 njReleaseTextureNumG(Uint32 n);
void   njReleaseTextureAll(void);

/* Render Texture */
void njRenderTextureNum(Uint32 n);
void njRenderTextureNumG(Uint32 globalIndex);
void njFrameBufferBmp(char* bmp, char* buffer);

/* Palette */
void njSetPaletteBankNum(Uint32 n, Uint32 bank);
void njSetPaletteBankNumG(Uint32 globalIndex, Uint32 bank);
void njSetPaletteMode(Uint32 mode);
Uint32 njGetPaletteMode(void);
void njSetPaletteData(Sint32 offset, Sint32 count, void* data);
void njGetPaletteData(Sint32 offset, Sint32 count, void* data);
Sint32 njLoadPaletteData(void* data, NJS_TEXPALETTE* pl);

#endif
