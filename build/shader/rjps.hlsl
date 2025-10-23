/********************************/
/*  Constant Registers          */
/********************************/
/****** Floats **********************************************************************************/
float4 c_FogParam           : register(c50);  /* mode, near, far, X                             */
float4 c_FogColor           : register(c51);  /* r, g, b, a                                     */
float4 c_ColShadow          : register(c200); /* shadow color + shadow tex                      */
float4 c_TexParam           : register(c201); /* texshading, texalpha, X, X                     */

/********************************/
/*  Texture Samplers            */
/********************************/
/****** Sampler2D *******************************************************************************/
sampler2D s_DiffuseTex      : register(s0);  /* diffuse texture                                 */
sampler2D s_PaletteTex      : register(s1);  /* palette color texture                           */
sampler2D s_ShadowTex3      : register(s3);  /* shadow texture                                  */
sampler2D s_ShadowTex4      : register(s4);  /* shadow texture                                  */
sampler2D s_ShadowTex0      : register(s5);  /* shadow texture                                  */
sampler2D s_ShadowTex1      : register(s6);  /* shadow texture                                  */
sampler2D s_ShadowTex2      : register(s7);  /* shadow texture                                  */

/********************************/
/*  Constants                   */
/********************************/
/****** Tex Shading *****************************************************************************/
#define TEXSHADING_DECAL            (0) /* RGBt + RGBo                          | At            */
#define TEXSHADING_MODULATE         (1) /* (RGBc * RGBt) + RGBo                 | Ac            */
#define TEXSHADING_DECALALPHA       (2) /* (RGBt * At) + (RGBc * (1-At)) + RGBo | Ac            */
#define TEXSHADING_MODULATEALPHA    (3) /* (RGBc * RGBt) + RGBo                 | Ac * At       */

/********************************/
/*  Structures                  */
/********************************/
/****** Pixel Input *****************************************************************************/
struct PS_IN
{
    float4 pos              : VPOS;         /* vertex screen postion                            */
    float  w                : TEXCOORD0;    /* vertex w component                               */

    float2 uv               : TEXCOORD1;    /* texture coordinate                               */
    float4 col              : COLOR0;       /* color                                            */
    float4 off              : COLOR1;       /* offset color/specular                            */
    
#ifdef PXL_SHTEX
    float2 stexuv1          : TEXCOORD2;    /* shadow tex uvs                                   */
    float2 stexuv2          : TEXCOORD3;    /* shadow tex uvs                                   */
    float2 stexuv3          : TEXCOORD4;    /* shadow tex uvs                                   */
    float2 stexuv4          : TEXCOORD5;    /* shadow tex uvs                                   */
    float2 stexuv5          : TEXCOORD6;    /* shadow tex uvs                                   */
    float  stexnum          : TEXCOORD7;    /* shadow tex count                                 */
#endif
};

/****** Pixel Output ****************************************************************************/
struct PS_OUT
{
    half4 col               : COLOR;        /* final pixel color                                */
};

/********************************/
/*  Shader Functions            */
/********************************/
/****** Get Texture *****************************************************************************/
#if (PXL_TEX == 2)    // palette

half4
GetTexture(const float2 uv)
{
    const half   plt_index = (half)tex2D( s_DiffuseTex, uv ).w * totalPaletteIndices + paletteOffset;
    const float2 plt_uv    = float2(plt_index / indexDiv, 0);

    return tex2D(s_PaletteTex, plt_uv);
}

#elif (PXL_TEX == 1)  // diffuse

half4
GetTexture(const float2 uv)
{
    return tex2D(s_DiffuseTex, uv);
}

#endif

/****** Fog *************************************************************************************/
#if (PXL_FOG == 1)

float
GetFogIntensity(const float w)
{
    const float fogDensity = 8;
    
    const float fog_mode = c_FogParam.x;
    const float fog_near = c_FogParam.y;
    const float fog_far  = c_FogParam.z;

    float fog = (w - fog_near) / (fog_far - fog_near);
    
    float exp2fog = exp2(-fogDensity * fog * fog);
    float expfog  = exp2(-fogDensity * fog);

    if ( fog_mode > 4.5 )
    {
        fog = saturate( 1.0f - exp2fog );
    }
    else if ( fog_mode > 2.5 )
    {
        fog = saturate( 1.0f - expfog );
    }

    return saturate(fog);
}

#endif



/****** Shadow Tex ******************************************************************************/
#if (PXL_SHTEX == 1)

bool
HasTex(float texGenCount, int check)
{
    return (texGenCount - (check + 0.2f)) > 0;
}

float
GetShadow(sampler2D tex, float2 uv, float texGenCount, int check)
{
    half v = tex2D(tex, uv).x;
    return HasTex(texGenCount, check) ? (1.0f - v) : 1;
}

half
GetShadowTexIntensity(const PS_IN inpt)
{
    half shadow = 1;

    shadow *= GetShadow(s_ShadowTex0, inpt.stexuv1, inpt.stexnum, 1);
    shadow *= GetShadow(s_ShadowTex1, inpt.stexuv2, inpt.stexnum, 2);
    shadow *= GetShadow(s_ShadowTex2, inpt.stexuv3, inpt.stexnum, 3);
    shadow *= GetShadow(s_ShadowTex3, inpt.stexuv4, inpt.stexnum, 4);
    shadow *= GetShadow(s_ShadowTex4, inpt.stexuv5, inpt.stexnum, 5);

    return (shadow > 0.5f) ? 1.f : (1.f - c_ColShadow.a);
}

#endif

/********************************/
/*  Pixel Shader                */
/********************************/
/****** Main ************************************************************************************/
PS_OUT
main(const PS_IN inpt)
{
    const float texshading = c_TexParam.x; // texture shading mode
    const float texalpha   = c_TexParam.y; // ignore texture alpha
    
    PS_OUT outp;

    /****** Get Color ***********************************************************************/
    
#ifdef PXL_TEX

    half4 tex = GetTexture( inpt.uv );

    tex.a = saturate( tex.a + texalpha ); // ignore texture alpha

	if ( texshading <= TEXSHADING_DECAL )
	{
        outp.col.rgb = tex.rgb + inpt.off.rgb;
        outp.col.a   = tex.a;
    }
    else if ( texshading <= TEXSHADING_MODULATE )
    {
        outp.col.rgb = (inpt.col.rgb * tex.rgb) + inpt.off.rgb;
        outp.col.a   = inpt.col.a;
    }
    else if ( texshading <= TEXSHADING_DECALALPHA )
    {
        outp.col.rgb = (tex.rgb * (tex.a)) + (inpt.col.rgb * (1.f - tex.a)) + inpt.off.rgb;
        outp.col.a   = inpt.col.a;
    }
    else // ( texshading <= TEXSHADING_MODULATEALPHA )
    {
        outp.col.rgb = (tex.rgb * inpt.col.rgb) + inpt.off.rgb;
        outp.col.a   = inpt.col.a * tex.a;
    }

#else // NONTEX
    
    outp.col.rgb = inpt.col.rgb + inpt.off.rgb;
    outp.col.a   = inpt.col.a;
    
#endif

    outp.col = saturate( outp.col ); // clamp color

    /****** Shadow Tex **********************************************************************/

#ifdef PXL_SHTEX

    outp.col.rgb *= GetShadowTexIntensity(inpt);
    
#endif

    /****** Fog *****************************************************************************/

#ifdef PXL_FOG

    const float fog_inten = GetFogIntensity( inpt.w );

    outp.col.rgb = lerp( outp.col.rgb, c_FogColor.rgb, fog_inten );
    
#endif

    /****** End *****************************************************************************/

    return outp;
}
