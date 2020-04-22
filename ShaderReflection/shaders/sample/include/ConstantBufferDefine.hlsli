#ifndef CONSTANT_BUFFER_DEFINE_HLSLI
#define CONSTANT_BUFFER_DEFINE_HLSLI

// コンスタントバッファのスロット定義
#define CB_SLOT_GLOBAL b0
#define CB_SLOT_SCENE b1
#define CB_SLOT_MODEL_STATIC b2
#define CB_SLOT_MODEL_DYNAMIC b3

// グローバルなコンスタントバッファ
#define CB_GLOBAL_BEGIN cbuffer CBGlobal : register(CB_SLOT_GLOBAL) {
#define CB_GLOBAL_END };

// シーンのコンスタントバッファ
#define CB_SCENE_BEGIN cbuffer CBScene : register(CB_SLOT_SCENE) {
#define CB_SCENE_END };

// モデルのスタティックなコンスタントバッファ
#define CB_MODEL_STATIC_BEGIN cbuffer CBModelStatic : register(CB_SLOT_MODEL_STATIC) {
#define CB_MODEL_STATIC_END };

// モデルのダイナミックなコンスタントバッファ(ユーザー側で定義)
#define CB_MODEL_DYNAMIC_BEGIN cbuffer CBModelDynamic : register(CB_SLOT_MODEL_DYNAMIC) {
#define CB_MODEL_DYNAMIC_END };

#endif // CONSTANT_BUFFER_DEFINE_HLSLI