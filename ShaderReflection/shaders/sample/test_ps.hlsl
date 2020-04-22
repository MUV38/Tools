#include "include/Common.hlsli"

USER_TEXTURE_DEFINE(0, tex0)
USER_TEXTURE_DEFINE(1, tex1)

CB_MODEL_DYNAMIC_BEGIN
	float4 ModelDynamic_UserParam0;
CB_MODEL_DYNAMIC_END

float4 main(float4 pos : SV_POSITION) : SV_TARGET
{
	float2 uv = float2(0.0f, 0.0f);
	
	return USER_TEXTURE_SAMPLE(tex0, uv) * USER_TEXTURE_SAMPLE(tex1, uv) * ModelStatic_UserParam0 * ModelDynamic_UserParam0;
}