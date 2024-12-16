#include "common.hlsl"

PS_IN vs_main(in VS_IN input)
{
    PS_IN output;

    // ワールド、ビュー、プロジェクション行列を掛け合わせて座標変換を行う
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);

    // ================================
    // 波の高さを計算
    // ================================
    float waveFrequency = 0.1;  // 波の周波数（波の密度を調整）
    float waveSpeed = 1.0;      // 波の進行速度
    float waveAmplitude = 1.5;  // 波の振幅（高さを調整）
    float time = Timer; // C++ から渡される 'Timer' に変更float time = Time;         // グローバルタイマー（外部から渡す）

    // 波の式: sin関数を使って波を表現
    float waveHeight = waveAmplitude * sin(input.pos.x * waveFrequency + time * waveSpeed);
    waveHeight += waveAmplitude * cos(input.pos.z * waveFrequency * 0.8 + time * waveSpeed * 1.2); // 複数の波を合成

    // 入力頂点のY座標に波の高さを加算
    input.pos.y += waveHeight;

    // 変換後の頂点座標を設定
    output.pos = mul(input.pos, wvp);

    // ================================
    // 法線の再計算（波の傾きを反映）
    // ================================
    float dx = waveAmplitude * waveFrequency * cos(input.pos.x * waveFrequency + time * waveSpeed);
    float dz = -waveAmplitude * waveFrequency * sin(input.pos.z * waveFrequency * 0.8 + time * waveSpeed * 1.2);
    float3 waveNormal = normalize(float3(-dx, 1.0, -dz));

    // 法線ベクトルをワールド空間に変換して正規化
    float4 normal = float4(waveNormal, 0.0);
    float4 worldNormal = mul(normal, World); // ワールド空間に変換
    worldNormal = normalize(worldNormal);

    // ================================
    // ライティング計算
    // ================================
    // 光源方向と法線ベクトルの内積を計算して拡散光を求める
    float d = -dot(Light.Direction.xyz, worldNormal.xyz);
    d = saturate(d); // 内積を0～1にクランプ

    // 拡散光とアンビエント光を適用
    output.col.xyz = input.col.xyz * d * Light.Diffuse.xyz; // 拡散光
    output.col.xyz += input.col.xyz * Light.Ambient.xyz;    // アンビエント光
    output.col.xyz += Material.Emission.xyz;               // エミッションを加算
    output.col.a = input.col.a * Material.Diffuse.a;        // アルファ値を適用

    // ================================
    // テクスチャ座標はそのまま使用
    // ================================
    output.tex = input.tex;

    return output;
}
