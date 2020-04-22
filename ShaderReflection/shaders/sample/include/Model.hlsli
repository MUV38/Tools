#ifndef MODEL_HLSLI
#define MODEL_HLSLI

#include "ConstantBufferDefine.hlsli"

// モデルのスタティックなコンスタントバッファ
CB_MODEL_STATIC_BEGIN
	float4 ModelStatic_UserParam0;
	float4 ModelStatic_UserParam1;
	float4 ModelStatic_UserParam2;
	float4 ModelStatic_UserParam3;
CB_MODEL_STATIC_END

float4 getModelStaticUserParam0()
{
	return ModelStatic_UserParam0;
}

#endif // MODEL_HLSLI