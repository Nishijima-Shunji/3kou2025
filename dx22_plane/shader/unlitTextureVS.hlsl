#include "common.hlsl"

PS_IN vs_main(in VS_IN input)
{
    PS_IN output;
	
	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);

    output.pos = mul(input.pos, wvp);

	//uv座標を移動させる
	float4 uv;
	uv.xy = input.tex;			//行列掛け算のためfloat4型に映移す
	uv.z = 0.0f;
	uv.w = 1.0f;
	uv =mul(uv, matrixTex);	//UV座標と移動行列を掛け算にセット
	output.tex = uv.xy;			//掛け算の結果を送信用変数にセット
    //output.tex = input.tex;
    output.col = input.col;
	
    return output;
}

