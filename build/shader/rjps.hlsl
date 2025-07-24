/********************************/
/*  Constant Registers          */
/********************************/
/****** Floats **********************************************************************************/
float4     f_FogParam               : register(c50); // mode, near, far
float4     f_FogColor               : register(c51); // r, g, b, a

/********************************/
/*  Texture Samplers            */
/********************************/
/****** Sampler2D *******************************************************************************/
sampler2D  s_DiffuseTex             : register(s0);
sampler2D  s_PaletteTex             : register(s1);
sampler2D  s_ShadowTex3             : register(s3);
sampler2D  s_ShadowTex4             : register(s4);
sampler2D  s_ShadowTex0             : register(s5);
sampler2D  s_ShadowTex1             : register(s6);
sampler2D  s_ShadowTex2             : register(s7);

/********************************/
/*  Structures                  */
/********************************/
/****** Pixel Input *****************************************************************************/
struct PS_IN
{
    float4 position         : SV_POSITION;
   
    float w                 : TEXCOORD0;

    float2 uv               : TEXCOORD1;    
    float4 color            : COLOR0;
    float4 specular         : COLOR1;
    
#ifdef PXL_SHTEX
    float2 stexuv1          : TEXCOORD2;
    float2 stexuv2          : TEXCOORD3;
    float2 stexuv3          : TEXCOORD4;
    float2 stexuv4          : TEXCOORD5;
    float2 stexuv5          : TEXCOORD6;
    float  stexnum          : TEXCOORD7;
#endif
};

/****** Pixel Output ****************************************************************************/
struct PS_OUT
{
    half4 color             : COLOR;
};

/********************************/
/*  Shader Functions            */
/********************************/
/****** Texture *********************************************************************************/
#if (PXL_TEX == 2)    // palette

half4 GetTexture(const float2 uv)
{
    const half   plt_index = (half)tex2D( s_DiffuseTex, uv ).w * totalPaletteIndices + paletteOffset;
    const float2 plt_uv    = float2(plt_index / indexDiv, 0);

    return tex2D(s_PaletteTex, plt_uv);
}

#elif (PXL_TEX == 1)  // diffuse

half4 GetTexture(const float2 uv)
{
    return tex2D(s_DiffuseTex, uv);
}

#endif

/****** Fog *************************************************************************************/
#if (PXL_FOG == 1)

float GetFogIntensity(const float w)
{
    const float fogDensity = 8;
    
    const float fog_mode = f_FogParam.x;
    const float fog_near = f_FogParam.y;
    const float fog_far  = f_FogParam.z;

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

bool HasTex(float texGenCount, int check)
{
    return (texGenCount - (check + 0.2f)) > 0;
}

float GetShadow(sampler2D tex, float2 uv, float texGenCount, int check)
{
    half v = tex2D(tex, uv).x;
    return HasTex(texGenCount, check) ? (1.0f - v) : 1;
}

half GetShadowTexIntensity(const PS_IN inp)
{
    half shadow = 1;

    shadow *= GetShadow(s_ShadowTex0, inp.stexuv1, inp.stexnum, 1);
    shadow *= GetShadow(s_ShadowTex1, inp.stexuv2, inp.stexnum, 2);
    shadow *= GetShadow(s_ShadowTex2, inp.stexuv3, inp.stexnum, 3);
    shadow *= GetShadow(s_ShadowTex3, inp.stexuv4, inp.stexnum, 4);
    shadow *= GetShadow(s_ShadowTex4, inp.stexuv5, inp.stexnum, 5);

    return (shadow > 0.5f) ? 1.f : 0.3125f;
}

#endif

/********************************/
/*  Pixel Shader                */
/********************************/
/****** Main ************************************************************************************/
PS_OUT main(const PS_IN inp)
{
    PS_OUT outp;
    
    // set initial color
#ifdef PXL_TEX
    outp.color = inp.color * GetTexture( inp.uv );
#else
    outp.color = inp.color;
#endif

    // add specular color
    outp.color.rgb = saturate( outp.color.rgb + inp.specular.rgb );

    // battle shadowtex system
#ifdef PXL_SHTEX
    outp.color.rgb *= GetShadowTexIntensity(inp);
#endif

    // apply fog
#ifdef PXL_FOG
    const float fog_inten = GetFogIntensity( inp.w );

    outp.color.rgb = lerp( outp.color.rgb, f_FogColor.rgb, fog_inten );
#endif
    
    // debug color test
#ifdef PXL_TST
    const float c = inp.w / 16383.f;
    
    outp.color = half4( 1.f, c, 0.66f, 1.f );
#endif

    return outp;
}
