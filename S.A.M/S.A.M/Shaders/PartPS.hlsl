Texture2D PartTex : register(t0);

SamplerState sampAni : register(s0);

struct PS_IN
{
	float4 Pos : SV_POSITION;
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
	float4 Glow : SV_Target4;
};

PS_OUT PS_main(PS_IN input)
{
	PS_OUT output = (PS_OUT)0;

	output.Normal = float4(input.Normal, 1.0f);
	output.DiffAlbedo = (PartTex.Sample(sampAni, input.Tex));
	output.SpecAlbedo = float4(0.0f, 0.0f, 0.0f, 0.0f);
	output.Pos = float4(input.Position, 1.0f);
	output.Glow = PartTex.Sample(sampAni, input.Tex);

	return output;
}