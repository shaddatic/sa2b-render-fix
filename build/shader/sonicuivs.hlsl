struct VS_IN
{
	float3 position : POSITION;
	float4 color    : COLOR0;
	float2 tex      : TEXCOORD0;
};

struct PS_IN
{
	float4 position    : POSITION;
	float4 color       : COLOR;
	float2 uv          : TEXCOORD;
};

float4 g_DeviceInfo : register(c104);

PS_IN main(VS_IN input)
{
	PS_IN output;
	
	float2 pos = input.position.xy / input.position.z - 0.5;
	float2 res = float2(320, 240);
	pos = (pos /  res) - 1; 

	output.position.x = pos.x * g_DeviceInfo.w;
	output.position.y = -pos.y;
	output.position.z = -1.f / input.position.z;
	output.position.w = 1.f; 
	output.color = input.color;
	output.uv = input.tex;
	return output;
}