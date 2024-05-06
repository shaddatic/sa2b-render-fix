float4 g_ColorOut : register(c0);

struct VS_OUTPUT
{
	float4 pos : POSITION;
};

float4 main(VS_OUTPUT input) : COLOR
{
	return g_ColorOut;
}
