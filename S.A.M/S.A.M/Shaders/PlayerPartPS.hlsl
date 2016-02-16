Texture2D PartTex : register(t0);

SamplerState sampAni : register(s0);

struct PS_IN
{
	float4 Pos : SV_POSITION;
	float4 SourcePos : SOURCEPOS;
	float3 Normal : NORMAL;
	float3 Position : POS;
	float2 Tex : TEXCOORD;
};

struct PS_OUT
{
	float4 Normal : SV_Target0;
	float4 DiffAlbedo : SV_Target1;
	float4 SpecAlbedo : SV_Target2;
	float4 Pos : SV_Target3;
};

PS_OUT PS_main(PS_IN input)
{
	PS_OUT output = (PS_OUT)0;

	float _depth = (input.Position.y + 2) / 4;
	float _distance = distance(input.SourcePos, float4(0, 0, 0, 1));

	output.Normal = float4(float3(0, 1, 0), 1.0f);
	output.DiffAlbedo = ((PartTex.Sample(sampAni, input.Tex) * _depth) * _distance);
	output.SpecAlbedo = float4(0.16f, 0.16f, 0.16f, 1000.0f);
	output.Pos = float4(input.Position, 1.0f);

	return output;
}