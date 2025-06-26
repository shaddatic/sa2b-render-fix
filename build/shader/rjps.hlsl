
#define DITHER_DIV  63.f

float4 g_FogParam : register(c50);
float4 g_FogColor : register(c51);

sampler2D g_DiffuseTex : register(s0);
sampler2D g_PaletteTex : register(s1);

static const float DitherTbl[4][4] = 
{
    { 0.9375f, 0.1875f, 0.75f , 0.0f   },
    { 0.4375f, 0.6875f, 0.25f , 0.5f   },
    { 0.8125f, 0.0625f, 0.875f, 0.125f },
    { 0.3125f, 0.5625f, 0.375f, 0.625f }
};

struct PS_IN
{
    float4 ScreenPosition      : SV_POSITION;
    float4 PositionInfo        : TEXCOORD0;

    float2 uv                  : TEXCOORD1;
    float4 color               : COLOR0;
    float4 specular            : COLOR1;

#if (PXL_ST == 1)
    float4 Shadow12            : TEXCOORD2;
    float4 Shadow34            : TEXCOORD3;
    float3 Shadow5             : TEXCOORD4;
#endif
};

struct PS_OUT
{
    half4 color                : COLOR;
};

#if (PXL_F == 1)

float CalcFog(const PS_IN input)
{
    float fog = (input.PositionInfo.w - g_FogParam.y) / (g_FogParam.z - g_FogParam.y);
    
    float exp2fog = exp2(-8 * fog * fog);
    float expfog = exp2(-8 * fog);

    if(g_FogParam.x > 4.5)
    {
        fog = 1.0f - exp2fog;//(1 - exp2(fog2 * -fogDensity * fog2));
    }
    else if (g_FogParam.x > 2.5)
    {
        fog = 1.0f - expfog;//(1 - exp2(fog2 * -fogDensity));
    }

    return saturate(fog);
}

#endif

PS_OUT main(const PS_IN input)
{
    float4 out_color;

#if (PXL_P == 1)
    const half   plt_index = (half)tex2D(g_DiffuseTex, input.TexCoord).w * totalPaletteIndices + paletteOffset;
    const float2 plt_uv    = float2(plt_index / indexDiv, 0);

    const half4 texd = tex2D(g_PaletteTex, plt_uv);
#elif (PXL_T == 1)
    const half4 texd = tex2D(g_DiffuseTex, input.uv);
#else
    const half4 texd = float4(1.f, 1.f, 1.f, 1.f);
#endif

    out_color = ( input.color * texd );

    // add specular color
    out_color.xyz = saturate( out_color.xyz + input.specular.xyz );

#if (PXL_ST == 1)
    half shadow = 1;

    shadow *= GetShadow(g_ShadowTex0, input.Shadow12.xy, input.Shadow5.z, 1);
    shadow *= GetShadow(g_ShadowTex1, input.Shadow12.zw, input.Shadow5.z, 2);
    shadow *= GetShadow(g_ShadowTex2, input.Shadow34.xy, input.Shadow5.z, 3);
    shadow *= GetShadow(g_ShadowTex3, input.Shadow34.zw, input.Shadow5.z, 4);
    shadow *= GetShadow(g_ShadowTex4, input.Shadow5.xy , input.Shadow5.z, 5);

    out_color.xyz *= (shadow > 0.5f) ? 1.f : 0.3125f;
#endif

    // add fog color
#if (PXL_F == 1)
    const float fogDensity = 8;

    float fog_inten = CalcFog(input);

    out_color.xyz = lerp( out_color.xyz, g_FogColor.xyz, fog_inten );
#endif

#if (PXL_D == 1)
    const float dither = DitherTbl[int(input.ScreenPosition.y % 4.f)][int(input.ScreenPosition.x % 4.f)] / DITHER_DIV;

    // round color
    out_color = floor( (out_color + dither) * DITHER_DIV ) / DITHER_DIV;
#endif

    PS_OUT output;

    output.color = out_color;

    return output;
}
