#ifndef COMMON_HLSLI
#define COMMON_HLSLI

#include "Global.hlsli"
#include "Scene.hlsli"
#include "Model.hlsli"

// ユーザー定義のテクスチャ
#define USER_TEXTURE_DEFINE(NO, NAME) Texture2D UserTex_##NAME : register(t##NO); SamplerState UserSamp_##NAME : register(s##NO);
#define USER_TEXTURE_SAMPLE(NAME, UV) UserTex_##NAME.Sample(UserSamp_##NAME, UV)

#endif // COMMON_HLSLI