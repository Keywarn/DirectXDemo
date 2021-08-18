struct VS_INPUT {
	float3 pos : POSITION;
	float4 colour : COLOUR;
};

struct VS_OUTPUT {
	float4 pos: SV_POSITION;
	float4 colour: COLOUR;
};

cbuffer ConstantBuffer : register(b0) {
	float4 colourMultiplier;
}

VS_OUTPUT main( VS_INPUT input)
{
	VS_OUTPUT output;
	output.pos = float4(input.pos, 1.0f);
	output.colour = input.colour + colourMultiplier;
	return output;
}