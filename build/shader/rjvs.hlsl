/********************************/
/*  Constant Registers          */
/********************************/
/****** Floats **********************************************************************************/
float4x4 g_WorldMatrix              : register(c0);
float4x4 g_ProjMatrix               : register(c8);
float4x4 g_WorldViewITMatrix        : register(c12);
float4   g_DeviceInfo               : register(c104);
float    g_NumTexGens               : register(c155);
float4x4 g_TexMatrix[10]            : register(c160);

/********************************/
/*  Structures                  */
/********************************/
/****** Vertex Input ***************************************************************************/
struct VS_IN
{
    float3 position         : POSITION0;

#ifdef VTX_TEX
    float2 uv               : TEXCOORD0;
#endif
#ifdef VTX_COL
    float4 color            : COLOR0;
#endif
#ifdef VTX_OFF
    float4 specular         : COLOR1;
#endif
};

/****** Vertex Output ***************************************************************************/
struct VS_OUT
{
    float4 position         : SV_POSITION;
   
    float w                 : TEXCOORD0;

    float2 uv               : TEXCOORD1;    
    float4 color            : COLOR0;
    float4 specular         : COLOR1;
    
#ifdef VTX_SHTEX
    float2 stexuv1          : TEXCOORD2;
    float2 stexuv2          : TEXCOORD3;
    float2 stexuv3          : TEXCOORD4;
    float2 stexuv4          : TEXCOORD5;
    float2 stexuv5          : TEXCOORD6;
    float  stexnum          : TEXCOORD7;
#endif
};

/********************************/
/*  Vertex Shader               */
/********************************/
/****** Main ************************************************************************************/
VS_OUT main(VS_IN inp)
{
    VS_OUT outp;

#ifdef VTX_3D
    outp.position = mul( float4(inp.position, 1.0f), g_ProjMatrix );
#else
    outp.position.x =  inp.position.x * g_DeviceInfo.w;
    outp.position.y = -inp.position.y;
    outp.position.z = 1.f - inp.position.z;
    outp.position.w = 1.f;
#endif

    outp.w = outp.position.z;
    
#ifdef VTX_TEX
    outp.uv       = inp.uv;
#else
    outp.uv       = float2(0.f, 0.f);
#endif

#ifdef VTX_COL
    outp.color    = inp.color;
#else
    outp.color    = float4(1.f, 1.f, 1.f, 1.f);
#endif

#ifdef VTX_OFF
    outp.specular = inp.specular;
#else
    outp.specular = float4(0.f, 0.f, 0.f, 0.f);
#endif

#ifdef VTX_SHTEX
    const float3 vtx_pos = mul( float4(inp.position, 1.f), g_WorldMatrix );
    
    {
        const float3 stx_pos = mul( float4(vtx_pos, 1), g_TexMatrix[1] ).xyz;
        
        outp.stexuv1.xy = stx_pos.xy / stx_pos.z;
    }
    {
        const float3 stx_pos = mul( float4(vtx_pos, 1), g_TexMatrix[2] ).xyz;
        
        outp.stexuv2.xy = stx_pos.xy / stx_pos.z;
    }
    {
        const float3 stx_pos = mul( float4(vtx_pos, 1), g_TexMatrix[3] ).xyz;
        
        outp.stexuv3.xy = stx_pos.xy / stx_pos.z;
    }
    {
        const float3 stx_pos = mul( float4(vtx_pos, 1), g_TexMatrix[4] ).xyz;
        
        outp.stexuv4.xy = stx_pos.xy / stx_pos.z;
    }
    {
        const float3 stx_pos = mul( float4(vtx_pos, 1), g_TexMatrix[5] ).xyz;
        
        outp.stexuv5.xy = stx_pos.xy / stx_pos.z;
    }
    
    outp.stexnum = g_NumTexGens;
#endif

    // DirectX 9 pixel offset issue
    outp.position.xy += g_DeviceInfo.xy * outp.position.w;

    return outp;
}
