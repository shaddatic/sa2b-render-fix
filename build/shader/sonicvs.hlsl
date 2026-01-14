/*
*   sonicvs.hlsl - decompiled and fixed by Exant
*/
/********************************/
/*  Constant Registers          */
/********************************/
/****** Floats **********************************************************************************/
float4x4 g_WorldMatrix          : register(c0);
float4x4 g_ProjMatrix           : register(c8);
float4x4 g_WorldViewITMatrix    : register(c12);
float3 g_LightPos[4]            : register(c20);
float3 g_LightDir[4]            : register(c24);
float4 g_LightColor[4]          : register(c28);
float4 g_LightAttenA[4]         : register(c32);
float3 g_LightAttenK[4]         : register(c36);
float g_MaterialSrcType[4]      : register(c40);
float g_AmbientSrcType[4]       : register(c44);
float g_DiffAttenSelect[4]      : register(c48);
float g_LightFuncEnable[4]      : register(c52);
float m_AttnFunc[4]             : register(c56);
float4 g_MaterialReg[2]         : register(c66);
float4 g_AmbientReg[2]          : register(c68);
float g_LightMask[16]           : register(c70);
float g_TexGenSrc_0             : register(c140);
float g_NumTexGens              : register(c155);
float4x4 g_TexMatrix[10]        : register(c160);
float4	 g_ScreenInfo           : register(c201); // RF

/********************************/
/*  Structures                  */
/********************************/
/****** Vertex Input ****************************************************************************/
struct VS_IN
{
    float3 Position     : POSITION;
    float3 Normal       : NORMAL;
    float2 TexCoord     : TEXCOORD;
    float4 Color        : COLOR;
};

/********************************/
/*  Structures                  */
/********************************/
/****** Vertex Output ***************************************************************************/
struct PS_IN
{
    float4 ScreenPosition       : SV_POSITION;
    float4 PositionInfo         : TEXCOORD;
	float3 Normal				: TEXCOORD1;
	float2 UV					: TEXCOORD2;
	float4 Color0				: TEXCOORD3;
	float4 Shadow12				: TEXCOORD4;
	float4 Shadow34				: TEXCOORD5;
	float3 Shadow5				: TEXCOORD6;
	float3 TexCoord				: TEXCOORD7;
};

/********************************/
/*  Vertex Shader               */
/********************************/
/****** Main ************************************************************************************/
PS_IN main(VS_IN input)
{
    PS_IN output;
    
    float4 worldPos = mul(float4(input.Position, 1.0f), g_WorldMatrix);
    output.ScreenPosition = mul(worldPos, g_ProjMatrix);
    
    // DirectX 9 pixel offset issue
    output.ScreenPosition.x -= ( g_ScreenInfo.x * output.ScreenPosition.w );
    output.ScreenPosition.y += ( g_ScreenInfo.y * output.ScreenPosition.w );

    float3 normal = normalize(mul(float4(normalize(input.Normal), 0), g_WorldViewITMatrix).xyz);

    float4 diffuse, ambient;

    diffuse.xyz = g_MaterialSrcType[0].x > 0.5f ? g_MaterialReg[0].xyz : input.Color.xyz;
    diffuse.w   = g_MaterialSrcType[2].x > 0.5f ? g_MaterialReg[0].w   : input.Color.w;
    
    ambient.xyz = g_AmbientSrcType[0].x > 0.5f ? g_AmbientReg[0].xyz : input.Color.xyz;
    ambient.w   = g_AmbientSrcType[2].x > 0.5f ? g_AmbientReg[0].w   : input.Color.w;
    
    float4 finalColor = float4(0,0,0,0);
    
    for (int index = 0; index < 4; ++index)
    {
        float3 diffuseResult = 0;
		float normalDotProd = 0;
		float anotherAttenVar = 0;
        float lightPosDirDotProd = 0;
		float finalAtten = 0;

        if ((g_LightMask[index].x > 0.5 && g_LightFuncEnable[0].x > 0.5) || (g_LightMask[index + 8].x > 0.5 && g_LightFuncEnable[2].x > 0.5))
        {
            float3 lpos = normalize((g_LightPos[index] - worldPos.xyz));
            normalDotProd = max(dot(normal, lpos), 0);
            float3 ldir = normalize(g_LightDir[index].xyz);
			lightPosDirDotProd = saturate(dot(lpos, -ldir));

            // huh?
            float dist = length(g_LightPos[index] - worldPos.xyz);

            float attenK = (dist * dist) * g_LightAttenK[index].z;
			attenK += g_LightAttenK[index].y * dist;
			attenK += g_LightAttenK[index].x;

			if(attenK < 0.01f && attenK > -0.01f) attenK = 1;

			float attenA = (lightPosDirDotProd * lightPosDirDotProd) * g_LightAttenA[index].z;
            attenA += g_LightAttenA[index].y * lightPosDirDotProd;
            attenA += g_LightAttenA[index].x;
			
            finalAtten = saturate(attenA) / attenK;
            diffuseResult = float3(normalDotProd, normalDotProd, normalDotProd);            
            anotherAttenVar = g_LightAttenA[index].w;
        }

        if (g_LightFuncEnable[0].x > 0.5f && g_LightMask[index].x > 0.5f)
        {            
			float3 finalDiffuse = min(diffuseResult.xyz, 1);

			if(g_DiffAttenSelect[0] < 0.3) {
				finalDiffuse = 1;
			}
			else if (g_DiffAttenSelect[0] < 0.7) {
				finalDiffuse = diffuseResult;
			}

            float attnMul;
			if(m_AttnFunc[0].x > 0.7f) {
                attnMul = 1.0f;
            }
            else if(lightPosDirDotProd < anotherAttenVar) {
                attnMul = 0.0;
            }
            else {
                attnMul = finalAtten;
            }

            finalColor.xyz += finalDiffuse * attnMul * g_LightColor[index].xyz;
        }

        if (g_LightFuncEnable[2].x > 0.5f && g_LightMask[index + 8].x > 0.5f)
        {
			float finalAlpha = min(normalDotProd, 1.0f);

			if(g_DiffAttenSelect[2] < 0.3f) {
				finalAlpha = 1.0f;
			}
			else if (g_DiffAttenSelect[2] < 0.7f) {
				finalAlpha = normalDotProd;
			}
			
			float attnMul;
			if(m_AttnFunc[2].x > 0.7f) {
                attnMul = 1.0f;
            }
            else if(lightPosDirDotProd < anotherAttenVar) {
                attnMul = 0.0;
            }
            else {
                attnMul = finalAtten;
            }

            finalColor.w += finalAlpha * attnMul * g_LightColor[index].w;
        }
    }

    float4 r3 = saturate(ambient + finalColor);
    float4 finalFinalColor = float4(1, 1, 1, 1);
    if (g_LightFuncEnable[0] > 0.5f)
    {
        finalFinalColor.xyz = r3.xyz;
    }
    if (g_LightFuncEnable[2] > 0.5f)
    {
        finalFinalColor.w = r3.w;
    }

    output.Color0 = diffuse * finalFinalColor;

    float3 shadow = mul(float4(input.Position,1), g_TexMatrix[1]).xyz;
    output.Shadow12.xy = shadow.xy / shadow.z;
    shadow = mul(float4(input.Position,1), g_TexMatrix[2]).xyz;
    output.Shadow12.zw = shadow.xy / shadow.z;

    shadow = mul(float4(input.Position,1), g_TexMatrix[3]).xyz;
    output.Shadow34.xy = shadow.xy / shadow.z;
    shadow = mul(float4(input.Position,1), g_TexMatrix[4]).xyz;
    output.Shadow34.zw = shadow.xy / shadow.z;

    shadow = mul(float4(input.Position,1), g_TexMatrix[5]).xyz;
    output.Shadow5.xy = shadow.xy / shadow.z;
    
    output.TexCoord = mul(float4(input.TexCoord, 1, 1), g_TexMatrix[0]);
    
    if (g_TexGenSrc_0 < 1) 
    {
        output.TexCoord = mul(float4(input.Position, 1), g_TexMatrix[0]);
    }
    else if (g_TexGenSrc_0 < 2) 
    {
        output.TexCoord = mul(float4(input.Normal, 1), g_TexMatrix[0]);
    }

    output.PositionInfo.xyz = input.Position;
    output.PositionInfo.w = output.ScreenPosition.z;

    output.Normal = input.Normal;
    output.UV = input.TexCoord;

    output.Shadow5.z = g_NumTexGens;

    return output;
}