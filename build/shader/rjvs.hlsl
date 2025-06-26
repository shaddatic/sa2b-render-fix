float4x4 g_ProjMatrix           : register(c8);
float4x4 g_WorldViewITMatrix    : register(c12);
float4   g_DeviceInfo           : register(c104);

#ifdef EFF_STX
    float4x4 g_WorldMatrix      : register(c0);
    float4x4 g_TexMatrix[10]    : register(c160);
#endif

struct VS_IN
{
    float3 position         : POSITION0;

#ifdef VTX_T
    float2 uv               : TEXCOORD0;
#endif
#ifdef VTX_C
    float4 color            : COLOR0;
#endif
#ifdef VTX_S
    float4 specular         : COLOR1;
#endif
};

struct VS_OUT
{
    float4 ScreenPosition      : SV_POSITION;
    float4 PositionInfo        : TEXCOORD0;

    float2 uv                  : TEXCOORD1;
    float4 color               : COLOR0;
    float4 specular            : COLOR1;

#ifdef EFF_STX
    float4 Shadow12            : TEXCOORD2;
    float4 Shadow34            : TEXCOORD3;
    float3 Shadow5             : TEXCOORD4;
#endif
};

VS_OUT main(VS_IN input)
{
    VS_OUT output;

#ifdef VTX_3D
    output.ScreenPosition = mul( float4(input.position, 1.0f), g_ProjMatrix );
    
    output.PositionInfo.xyz = input.position;
    output.PositionInfo.w   = output.ScreenPosition.z;
#else
    output.ScreenPosition.x = ((input.position.x / +320.f) - 1.f) *  g_DeviceInfo.w;
    output.ScreenPosition.y = ((input.position.y / -240.f) + 1.f);
    output.ScreenPosition.z = 1.f - input.position.z;
    output.ScreenPosition.w = 1.f;
    
    output.PositionInfo.xyz = output.ScreenPosition.xyz;
    output.PositionInfo.w   = output.ScreenPosition.z;
#endif
    
#ifdef VTX_T
    output.uv       = input.uv;
#else
    output.uv       = float2(0.f, 0.f);
#endif

#ifdef VTX_C
    output.color    = input.color;
#else
    output.color    = float4(1.f, 1.f, 1.f, 1.f);
#endif

#ifdef VTX_S
    output.specular = input.specular;
#else
    output.specular = float4(0.f, 0.f, 0.f, 0.f);
#endif

#ifdef EFF_S
    const float3 pos = mul(float4(input.position, 1.f), g_WorldMatrix);

    {
        const float3 shadow1 = mul( float4(pos, 1), g_TexMatrix[1] ).xyz;
        output.Shadow12.xy = shadow1.xy / shadow1.z;
    }
    {
        const float3 shadow2 = mul( float4(pos, 1), g_TexMatrix[2] ).xyz;
        output.Shadow12.zw = shadow2.xy / shadow2.z;
    }
    {
        const float3 shadow3 = mul( float4(pos, 1), g_TexMatrix[3] ).xyz;
        output.Shadow34.xy = shadow3.xy / shadow3.z;
    }
    {
        const float3 shadow4 = mul( float4(pos, 1), g_TexMatrix[4] ).xyz;
        output.Shadow34.zw = shadow4.xy / shadow4.z;
    }
    {
        const float3 shadow5 = mul( float4(pos, 1), g_TexMatrix[5] ).xyz;
        output.Shadow5.xy = shadow5.xy / shadow5.z;
    }
#endif

    return output;
}
