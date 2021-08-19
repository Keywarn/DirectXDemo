struct VS_INPUT {
	float4 pos : POSITION;
	float4 colour : COLOUR;
};

struct VS_OUTPUT {
	float4 pos: SV_POSITION;
	float4 colour: COLOUR;
};

cbuffer ConstantBuffer : register(b0) {
	float4x4 wvpMat;
}


VS_OUTPUT main( VS_INPUT input)
{
	VS_OUTPUT output;
	output.pos = mul(input.pos, wvpMat);
	output.colour = input.colour;
	return output;
}