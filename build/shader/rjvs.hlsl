/********************************/
/*  Constant Registers          */
/********************************/
/****** Floats **********************************************************************************/
float4 c_DeviceInfo         : register(c104); /* adj w_res, adj h_res, ???, 4:3 stretch         */
float  c_NumTexGen          : register(c155); /* tex generation count                           */
float4 c_PolyAttr           : register(c200); /* normals, texture, color, offset color          */
float4 c_ScreenInfo         : register(c201); /* 1/w_res, 1/h_res, X, X                         */

/****** Matrix **********************************************************************************/
float4x4 c_MtxProjection    : register(c8);   /* projection matrix                              */
float4x4 c_MtxWorldView     : register(c0);   /* view matrix                                    */
float4x4 c_MtxWorldViewIT   : register(c12);  /* inverse transpose view matrix                  */
float4x4 c_MtxTexGen[10]    : register(c160); /* texture gen matrix(s)                          */

/********************************/
/*  Structures                  */
/********************************/
/****** Vertex Input ****************************************************************************/
struct VS_IN
{
    float3 pos              : POSITION0;    /* vertex position                                  */
    float2 uv               : TEXCOORD0;    /* texture coordinate                               */
    float4 col              : COLOR0;       /* color                                            */
    float4 off              : COLOR1;       /* offset color/specular                            */
};

/****** Vertex Output ***************************************************************************/
struct VS_OUT
{
    float4 pos              : POSITION;     /* vertex screen postion                            */
    float  w                : TEXCOORD0;    /* vertex w component                               */

    float2 uv               : TEXCOORD1;    /* texture coordinate                               */
    float4 col              : COLOR0;       /* color                                            */
    float4 off              : COLOR1;       /* offset color/specular                            */
    
#ifdef VTX_SHTEX
    float4 stexuvs          : TEXCOORD6;    /* shadow tex uvs (xy + zw)                         */
    float  stexnum          : TEXCOORD7;    /* shadow tex count                                 */
#endif
};

/********************************/
/*  Vertex Shader               */
/********************************/
/****** Main ************************************************************************************/
VS_OUT main(VS_IN inpt)
{
    const bool vnrm = c_PolyAttr.x > 0.f;
    const bool vtex = c_PolyAttr.y > 0.f;
    const bool vcol = c_PolyAttr.z > 0.f;
    const bool voff = c_PolyAttr.w > 0.f;

    VS_OUT outp;

#ifdef VTX_3D
    outp.pos = mul( float4(inpt.pos, 1.f), c_MtxProjection );
#else
    outp.pos.x =  inpt.pos.x * c_DeviceInfo.w;
    outp.pos.y = -inpt.pos.y;
    outp.pos.z =  inpt.pos.z;
    outp.pos.w =  1.f;
#endif

    outp.w = outp.pos.w;
    
    outp.uv  = vtex ? inpt.uv  : float2(0.f, 0.f);
    outp.col = vcol ? inpt.col : float4(1.f, 1.f, 1.f, 1.f);
    outp.off = voff ? inpt.off : float4(0.f, 0.f, 0.f, 0.f);

#ifdef VTX_SHTEX
    const float4 vtx_pos = float4( mul(float4(inpt.pos, 1.f), c_MtxWorldView).xyz, 1.f );
    
    const float3 stx_p1 = mul( vtx_pos, c_MtxTexGen[1] ).xyz;
    outp.stexuvs.xy     = stx_p1.xy / stx_p1.z;

    const float3 stx_p2 = mul( vtx_pos, c_MtxTexGen[2] ).xyz;
    outp.stexuvs.zw     = stx_p2.xy / stx_p2.z;
    
    outp.stexnum = c_NumTexGen;
#endif

    // DirectX 9 pixel offset issue
    outp.pos.x -= ( c_ScreenInfo.x * outp.pos.w );
    outp.pos.y += ( c_ScreenInfo.y * outp.pos.w );

    return outp;
}
