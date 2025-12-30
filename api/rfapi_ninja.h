/*
*   SA2 Render Fix - '/rfapi_ninja.h'
*
*   Description:
*     The 'Ninja' API module is for global Ninja API attributes.
* 
*   Notes:
*     - Use 'RJD' defines where possible, as they may differ from your own 'NJD' defines.
*     - Anything that notes a default value should be reset to that value when you're done.
*       - This can be done for all Ninja context parameters with 'Get/SetSystemAttr'.
* 
*   Version History:
*     - v1.5.0.0        : Version 0, initial release
* 
*   Availability:
*     - Before Init     : No
*     - At Init         : Yes
*     - After Init      : Yes
*/
#ifndef H_RFAPI_NINJA
#define H_RFAPI_NINJA

/********************************/
/*  Constants                   */
/********************************/
/****** API Module Version **********************************************************************/
#define RFAPI_NINJA_VER                         (0) /* ninja api version                        */

/****** Color Target ****************************************************************************/
#define RJD_COLOR_SRC                           (0) /* new rasterized pixel color               */
#define RJD_COLOR_DST                           (1) /* render target pixel color                */

/****** Color Blending Mode *********************************************************************/
#define RJD_COLOR_BLENDING_BOTHINVALPHA         ( 0) /* src = SA, dst = ISA; tgt param ignored  */
#define RJD_COLOR_BLENDING_BOTHSRCALPHA         ( 1) /* src = ISA, dst = SA; tgt param ignored  */

#define RJD_COLOR_BLENDING_DSTALPHA             ( 2) /* tgt * destination alpha                 */
#define RJD_COLOR_BLENDING_DSTCOLOR             ( 3) /* tgt * destination color            [sc] */
#define RJD_COLOR_BLENDING_INVDSTALPHA          ( 4) /* tgt * inverse destination alpha         */
#define RJD_COLOR_BLENDING_INVDSTCOLOR          ( 5) /* tgt * inverse destination color   [isc] */
#define RJD_COLOR_BLENDING_INVSRCALPHA          ( 6) /* tgt * inverse source alpha              */
#define RJD_COLOR_BLENDING_INVSRCCOLOR          ( 7) /* tgt * inverse source color              */
#define RJD_COLOR_BLENDING_SRCALPHA             ( 8) /* tgt * source alpha                      */
#define RJD_COLOR_BLENDING_SRCCOLOR             ( 9) /* tgt * source color                      */
#define RJD_COLOR_BLENDING_ONE                  (10) /* tgt * 1                                 */
#define RJD_COLOR_BLENDING_ZERO                 (11) /* tgt * 0                                 */

/****** Polygon Culling *************************************************************************/
#define RJD_POLYGONCULL_OFF                     (0x00000000) /* no culling                      */
#define RJD_POLYGONCULL_SMALL                   (0x08000000) /* cull small polygons             */
#define RJD_POLYGONCULL_ACW                     (0x10000000) /* cull anti-clockwise polygons    */
#define RJD_POLYGONCULL_CW                      (0x18000000) /* cull clockwise polygons         */

/****** Texture Shading Mode ********************************************************************/
/*
*   t = texture
*   c = color
*   o = offset color
*
*   pixel_color | pixel_alpha
*/
#define RJD_TEXSHADING_DECAL                    (0x00000000) /*  RGBt + RGBo                         | At       */
#define RJD_TEXSHADING_MODULATE                 (0x00000040) /* (RGBc * RGBt) + RGBo                 | Ac       */
#define RJD_TEXSHADING_DECALALPHA               (0x00000080) /* (RGBt * At) + (RGBc * (1-At)) + RGBo | Ac       */
#define RJD_TEXSHADING_MODULATEALPHA            (0x000000C0) /* (RGBc * RGBt) + RGBo                 | Ac * At  */

/****** Texture Filtering ***********************************************************************/
#define RJD_TEXTUREFILTER_POINTSAMPLE           (0x00000000) /* point filtering (no filter)     */
#define RJD_TEXTUREFILTER_BILINEAR              (0x00002000) /* bilinear filtering              */
#define RJD_TEXTUREFILTER_TRILINEAR_A           (0x00004000) /* trilinear filtering A (+Z)      */
#define RJD_TEXTUREFILTER_TRILINEAR_B           (0x00006000) /* trilinear filtering B (+1-Z)    */

/****** Texture Clamping ************************************************************************/
#define RJD_TEXTURECLAMP_OFF                    (0x00000000) /* no texture clamp                */
#define RJD_TEXTURECLAMP_V                      (0x00008000) /* texture clamp V                 */
#define RJD_TEXTURECLAMP_U                      (0x00010000) /* texture clamp U                 */
#define RJD_TEXTURECLAMP_UV                     (0x00018000) /* texture clamp both              */

/****** Texture Flipping ************************************************************************/
#define RJD_TEXTUREFLIP_OFF                     (0x00000000) /* no texture flip                 */
#define RJD_TEXTUREFLIP_V                       (0x00020000) /* texture flip V                  */
#define RJD_TEXTUREFLIP_U                       (0x00040000) /* texture flip U                  */
#define RJD_TEXTUREFLIP_UV                      (0x00060000) /* texture flip both               */

/****** Modifier Mode ***************************************************************************/
#define RJD_MODIFIER_INSIDE                     (0x20000000) /* shade inside polygons           */
#define RJD_MODIFIER_OUTSIDE                    (0x40000000) /* shade outside polygons          */

/********************************/
/*  API Structures              */
/********************************/
/****** Font API ********************************************************************************/
typedef struct
{
    uint32_t version;               /* structure version                                        */

    /****** Version >= 0 ************************************************************************/

    /**** Context *******************************************/
    /*
    *   Description:
    *     Set the current Ninja context slot.
    *
    *   Parameters:
    *     - n           : context number                                          [NJD_###_CTX]
    */
    void (*SetCurrentContext)( Int n );

    /**** Sys Attribute *************************************/
    /*
    *   Description:
    *     Get the current Ninja context state.
    *
    *   Parameters:
    *     - attr        : system attribute buffer
    */
    void (*GetSystemAttr)( NJS_SYS_ATTR* attr );
    /*
    *   Description:
    *     Set the current Ninja context state.
    *
    *   Parameters:
    *     - attr        : system attribute buffer
    */
    void (*SetSystemAttr)( const NJS_SYS_ATTR* attr );

    /**** Back Texture **************************************/
    /*
    *   Description:
    *     Set the back color (non-tex), which will be used to clear the framebuffer.
    *
    *   Parameters:
    *     - color1      : upper left color                                      [0xAA'RR'GG'BB]
    *     - color2      : upper right color                                     [0xAA'RR'GG'BB]
    *     - color3      : bottom left & right color                             [0xAA'RR'GG'BB]
    */
    void (*SetBackColor)( Uint32 color1, Uint32 color2, Uint32 color3 );
    /*
    *   Description:
    *     Set the back texture, which will be used to clear the framebuffer.
    *
    *   Notes:
    *     - Set the texture first before calling, using 'SetTextureNum' or 'SetTextureG'.
    *     - Vertex position info is ignored.
    *     - The bottom right vertex is generated automatically from the bottom left vertex
    *       (color/offset) and its relationship to the top right vertex (texture coords).
    *
    *   Parameters:
    *     - vtx         : the upper left, upper right, & bottom left vertex params
    */
    void (*SetBackTexture)( const NJS_TEXTUREH_VTX vtx[3] );

    /**** Global Param (Context) ****************************/
    /*
    *   Description:
    *     Set the specular behavior of draw functions.
    *
    *   Notes:
    *     - Sets Ninja context, but RF currently doesn't read it.
    *     - Has no effect on model draw, set by model parameters.
    *     - Default is 'ON', please reset it to this value when you're done.
    *
    *   Parameters:
    *     - mode        : specular mode                                                [ON/OFF]
    */
    void (*SpecularMode)( Int mode );

    /**** ISP Param (Context) *******************************/
    /*
    *   Description:
    *     Set the polygon culling mode of draw functions.
    *
    *   Notes:
    *     - Has no effect on model draw, set by model parameters.
    *     - 'SMALL' is not implemented, same as 'OFF'.
    *     - Default is 'SMALL'.
    *
    *   Parameters:
    *     - mode        : polygon culling mode to set                     [RJD_POLYGONCULL_###]
    */
    void (*PolygonCullingMode)( Int mode );
    /*
    *   Description:
    *     Set Z buffering behavior.
    *
    *   Notes:
    *     - Sets Ninja context, but RF currently doesn't read it.
    *     - Default is 'ON'.
    *
    *   Parameters:
    *     - mode        : z buffer mode                                                [ON/OFF]
    */
    void (*ZBufferMode)( Int mode );
    /*
    *   Description:
    *     Set Z writing behavior.
    *
    *   Notes:
    *     - Sets Ninja context, but RF currently doesn't read it.
    *     - Default is 'ON'.
    *
    *   Parameters:
    *     - mode        : z write mode                                                 [ON/OFF]
    */
    void (*ZWriteMode)( Int mode );

    /**** TSP Param (Context) *******************************/
    /*
    *   Description:
    *     Set the texture shading mode of draw functions.
    * 
    *   Notes:
    *     - Default is 'MODULATEALPHA'.
    *
    *   Parameters:
    *     - mode        : texture flip mode                                [RJD_TEXSHADING_###]
    */
    void (*TextureShadingMode)( Int mode );
    /*
    *   Descrption:
    *     Set the anisotropic filtering behavior of draw functions.
    *
    *   Notes:
    *     - Has no effect on model draw, set by model parameters.
    *     - Default is 'OFF'.
    *
    *   Parameters:
    *     - mode        : super sample mode                                            [ON/OFF]
    */
    void (*SuperSampleMode)( Int mode );
    /*
    *   Description:
    *     Set the mipmap depth adjust level.
    *
    *   Notes:
    *     - Has no effect on model draw, set by model parameters.
    *     - Hardware value is 'level/4' - eg. '1->0.25', '2->0.5', etc
    *     - A level value of '0' is NOT valid.
    *     - Default is '4'.
    *
    *   Parameters:
    *     - level       : mipmap depth adjust                                            [1~15]
    */
    void (*MipmapAdjust)( Int level );
    /*
    *   Description:
    *     Set if texture alpha component should be ignored and treated as opaque.
    *
    *   Notes:
    *     - Default is 'OFF'.
    *
    *   Parameters:
    *     - mode        : ignore texture alpha                                         [ON/OFF]
    */
    void (*IgnoreTextureAlphaMode)( Int mode );
    /*
    *   Description:
    *     Set the texture filter behavior of draw functions.
    *
    *   Notes:
    *     - Has no effect on model draw, set by model parameters.
    *     - Default is 'BILINEAR'.
    *
    *   Parameters:
    *     - mode        : texture filter mode                           [RJD_TEXTUREFILTER_###]
    */
    void (*TextureFilterMode)( Int mode );
    /*
    *   Description:
    *     Set the texture clamping behavior of draw functions.
    *
    *   Notes:
    *     - Has no effect on model draw, set by model parameters.
    *     - Default is 'OFF'.
    *
    *   Parameters:
    *     - mode        : texture clamping mode                          [RJD_TEXTURECLAMP_###]
    */
    void (*TextureClampMode)( Int mode );
    /*
    *   Description:
    *     Set the texture flip behavior of draw functions.
    *
    *   Notes:
    *     - Has no effect if texture clamping is enabled.
    *     - Has no effect on model draw, set by model parameters.
    *     - Default is 'OFF'.
    * 
    *   Parameters:
    *     - mode        : texture flip mode                               [RJD_TEXTUREFLIP_###]
    */
    void (*TextureFlipMode)( Int mode );
    /*
    *   Description:
    *     Set the color clamping mode.
    *
    *   Notes:
    *     - Sets Ninja context, but RF currently doesn't read it.
    *     - Default is 'OFF'.
    *
    *   Parameters:
    *     - mode        : color clamp mode                                             [ON/OFF]
    */
    void (*ColorClampMode)( Int mode );
    /*
    *   Description:
    *     Set the color blending behavior of draw functions.
    *
    *   Notes:
    *     - Has no effect on model draw, set by model parameters.
    *     - Default is 'BOTHINVALPHA'.
    *
    *   Parameters:
    *     - target      : color target                                          [RJD_###_COLOR]
    *     - mode        : blending mode                                [RJD_COLOR_BLENDING_###]
    */
    void (*ColorBlendingMode)( Int target, Int mode );

    /**** Modifier Param (Context) **************************/
    /*
    *   Description:
    *     Set modifier inside/outside behavior.
    *
    *   Notes:
    *     - Sets Ninja context, but RF currently doesn't read it.
    *     - Default is 'INSIDE'.
    *
    *   Parameters:
    *     - mode        : modifier mode                                      [RJD_MODIFIER_###]
    */
    void (*ModifierMode)( Int mode );

    /**** Cheap Shadow **************************************/
    /*
    *   Description:
    *     Set the intensity of modifier shadows, also called cheap shadows. The value is
    *   divided by '256' and multiplied with the pixel color. For example, a value of '0'
    *   would result in a fully black pixel and a value of '256' would result in no change
    *   - or in other words cheap shadows would be disabled.
    *
    *   Notes:
    *     - Only one intensity can be used across a single scene. In other words, all shadows
    *       will use the same value across a single frame.
    *     - The original Ninja version only supported values up to '255'.
    *
    *   Parameters:
    *     - mode        : cheap shadow intensity                                        [0~256]
    */
    void (*SetCheapShadowMode)( Int mode );

    /**** Depth Queue ***************************************/
    /*
    *   Description:
    *     Set the depth queue depth values.
    * 
    *   Notes:
    *     - Depth values are in world units
    *
    *   Examples:
    *     - rjSetDepthQueue( -1800.f, -2000.f ); // default
    *
    *   Paramters:
    *     - near        : near depth value
    *     - far         : far depth value
    */
    void (*SetDepthQueue)( Float near, Float far );
}
RFAPI_NINJA;

#endif/*H_RFAPI_NINJA*/
