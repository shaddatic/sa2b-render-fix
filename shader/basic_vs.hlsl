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
	VS_OUTPUT output = { float4(input.pos, 1.0f) };

	return output;
}
