/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njsystem.h'
*
*   Contains flags, values, and functions for interacting with the Ninja system
*
*   Contributors:
*     - SEGA,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _NJSYSTEM_H_
#define _NJSYSTEM_H_

/*--------------------------------------*/
/*      Render Mode Define              */
/*--------------------------------------*/

#define NJD_POLYGON_NOCULLING               0x00000000
#define NJD_POLYGON_CULLINGSMALL            0x08000000
#define NJD_POLYGON_CULLINGACW              0x10000000
#define NJD_POLYGON_CULLINGCW               0x18000000

#define NJD_SOURCE_COLOR                    0
#define NJD_DESTINATION_COLOR               1
#define NJD_COLOR_BLENDING_BOTHINVALPHA     0
#define NJD_COLOR_BLENDING_BOTHSRCALPHA     1
#define NJD_COLOR_BLENDING_DESTALPHA        2
#define NJD_COLOR_BLENDING_DESTCOLOR        3
#define NJD_COLOR_BLENDING_INVDESTALPHA     4
#define NJD_COLOR_BLENDING_INVDESTCOLOR     5
#define NJD_COLOR_BLENDING_INVSRCALPHA      6
#define NJD_COLOR_BLENDING_INVSRCCOLOR      7
#define NJD_COLOR_BLENDING_SRCALPHA         8
#define NJD_COLOR_BLENDING_SRCCOLOR         9
#define NJD_COLOR_BLENDING_ONE              10
#define NJD_COLOR_BLENDING_ZERO             11

#define NJD_TEX_SHADING_MODE_DECAL          0x00000000
#define NJD_TEX_SHADING_MODE_MODULATE       0x00000040
#define NJD_TEX_SHADING_MODE_DECALALPHA     0x00000080
#define NJD_TEX_SHADING_MODE_MODULATEALPHA  0x000000c0

#define NJD_CLIP_DISABLE                    0
#define NJD_CLIP_RESERVE                    1
#define NJD_CLIP_INSIDE                     2
#define NJD_CLIP_OUTSIDE                    3

#define NJD_TEXTUREFILTER_POINT_SAMPLE      0x00000000
#define NJD_TEXTUREFILTER_BILINEAR          0x00002000
#define NJD_TEXTUREFILTER_TRILINEAR_A       0x00004000
#define NJD_TEXTUREFILTER_TRILINEAR_B       0x00006000

#define NJD_TEXTURECLAMP_NOCLAMP            0x00000000
#define NJD_TEXTURECLAMP_CLAMP_V            0x00008000
#define NJD_TEXTURECLAMP_CLAMP_U            0x00010000
#define NJD_TEXTURECLAMP_CLAMP_UV           0x00018000

#define NJD_TEXTUREFLIP_NOFLIP              0x00000000
#define NJD_TEXTUREFLIP_FLIP_V              0x00020000
#define NJD_TEXTUREFLIP_FLIP_U              0x00040000
#define NJD_TEXTUREFLIP_FLIP_UV             0x00060000

#define NJD_MODIFIER_INSIDE                 0x20000000
#define NJD_MODIFIER_OUTSIDE                0x40000000

enum {
    NJD_SYSTEM_CTX = 0,
    NJD_DEBUG_CTX,
    NJD_NINDOWS_CTX,
    NJD_USER0_CTX,
    NJD_USER1_CTX,
    NJD_USER2_CTX,
    NJD_CONTEXT_MAX
};

typedef struct {
    Float	xad, yad;		/* aspect * dist	*/
    Float   cx, cy;			/* screen center	*/
    Float	ooxad, ooyad;	/* 1.0 / aspect * dist	*/
    Float   dist;			/* screen distance	*/
    Float	ax, ay;			/* aspect			*/
    Float	aspect;			/* aspect ay/ax		*/
    Float   w, h;			/* screen size		*/
} NJS_SCREEN;

typedef struct {
    Float		f_clip;			/* far clip			*/
    Float		n_clip;			/* near clip		*/
    Float		x1, x0, y1, y0;	/* screen clip		*/
    NJS_POINT2	d[2];			/* 2d clip			*/
} NJS_CLIP;

/*--------------------------------------*/
/*      Render Mode Data                */
/*--------------------------------------*/
#define _nj_screen_                         DATA_REF(NJS_SCREEN, 0x02670300)
#define _nj_clip_                           DATA_REF(NJS_CLIP  , 0x02670560)

#define _nj_control_3d_flag_                DATA_REF(Uint32    , 0x025F02D8)

#define _nj_vertex_buf_                     DATA_REF(void*     , 0x025EFE48)
#define _nj_constant_attr_and_              DATA_REF(Uint32    , 0x025F0268)
#define _nj_constant_attr_or_               DATA_REF(Uint32    , 0x025F02D4)
#define _nj_constant_material_              DATA_REF(NJS_ARGB  , 0x025EFFD0) 
#define _nj_cnk_blend_mode_                 DATA_REF(Uint32    , 0x025F0264)

/************************/
/*  System              */
/************************/
void    njSetBackColor(Uint32 col1, Uint32 col2, Uint32 col3);
void    njSetBackTexture(NJS_TEXTUREH_VTX* vtx);
void    njTextureFilterMode(Int mode);
void    njTextureClampMode(Int mode);
void    njTextureFlipMode(Int mode);
void    njMipmapAdjust(Int level);
void    njSuperSampleMode(Int mode);
void    njPolygonCullingSize(Float size);
void    njPolygonCullingMode(Int mode);
void    njColorBlendingMode(Int target, Int mode);
void    njSpecularMode(Int mode);
void    njIgnoreTextureAlphaMode(Int mode);
void    njTextureShadingMode(Int mode);
void    njUserClipping(Int mode, NJS_POINT2* p);
void    njGetSystemAttr(NJS_SYS_ATTR* attr);
void    njSetSystemAttr(NJS_SYS_ATTR* attr);
void    njColorClampMode(Int mode);
void    njSetColorClamp(Uint32 MaxARGB, Uint32 MinARGB);
void    njAdjustDisplay(Sint32 xadjust, Sint32 yadjust);
void    njSetPunchThroughThreshold(Int nThreshold);
void    njSetVirticalFilterMode(Int mode);
void    njSetBorderColor(Uint32 color);
void    njZBufferMode(Int mode);
void    njSetWaitVsyncCount(Int count);
Int     njGetDisplayMode(void);
Sint32  njSetHSyncLine(Int line);
void    njGetHSyncLine(Int* line);
void    njChangeDisplayDitherMode(Int mode);
void    njAccumlationBufferMode(Int SrcSelect, Int DstSelect);
void    njModifierMode(Int mode);
void    njSetYCoefficient(Sint32 nYCoeff0, Sint32 nYCoeff1);
void    njSetYCoefficientEx(Float fFilterRate, Float fBrightness);

/************************/
/*  View                */
/************************/
void    njSetScreenDist(Float dist);
void    njSetPerspective(Angle ang);
void    njSetScreenCenter(Float x, Float y);
void    njSetAspect(Float ax, Float ay);
void    njClip2D(NJS_POINT2* v);
void    njClipZ(Float n, Float f);
int     njCalcScreen(NJS_POINT3* p, Float* sx, Float* sy);

#endif
