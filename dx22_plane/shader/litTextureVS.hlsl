#include "common.hlsl"

PS_IN vs_main(in VS_IN input)
{
    PS_IN output;

	//positoin=============================
	// ���[���h�A�r���[�A�v���W�F�N�V�����s����|�����킹�č��W�ϊ����s��
	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);
    output.pos = mul(input.pos, wvp);
	
	//color=============================
	//�@���x�N�g���̕ϊ��Ɛ��K�����s��
	//���͂��ꂽ�@�������[���h��Ԃɕϊ����A���K������
	float4 normal = float4(input.nrm.xyz, 0.0);
	float4 worldNormal = mul(normal, World);//�@�������[���h��Ԃɕϊ�
	worldNormal = normalize(worldNormal);	//�@���x�N�g���𐳋K��

	//���������Ɩ@���x�N�g���̓��ς��v�Z���Ċg�U�������߂�
	float d = -dot(Light.Direction.xyz, worldNormal.xyz);

	d = saturate(d); //d�̒l��0�`1�ɃN�����v


    output.col.xyz = input.col.xyz * d * Light.Diffuse.xyz; // �g�U���̉e������Z
    output.col.xyz += input.col.xyz * Light.Ambient.xyz; // �A���r�G���g�������Z
	output.col.xyz += Material.Emission.xyz;	//Emission�����Z
    output.col.a = input.col.a * Material.Diffuse.a; // �A���t�@�l�͂��̂܂܎g�p
	
	//texture=============================
	// �e�N�X�`�����W�͂��̂܂܎g�p
    output.tex = input.tex;
	
    return output;
}
