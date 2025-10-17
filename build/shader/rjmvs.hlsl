float4x4 g_ProjMatrix : register(c8);

struct VS_INPUT
{
	float3 pos : POSITION;
};

struct VS_OUTPUT
{
	float4 pos : POSITION;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output = { mul(float4(input.pos, 1.0f), g_ProjMatrix) };

	return output;
}
