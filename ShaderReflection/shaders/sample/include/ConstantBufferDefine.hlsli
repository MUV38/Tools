#ifndef CONSTANT_BUFFER_DEFINE_HLSLI
#define CONSTANT_BUFFER_DEFINE_HLSLI

// �R���X�^���g�o�b�t�@�̃X���b�g��`
#define CB_SLOT_GLOBAL b0
#define CB_SLOT_SCENE b1
#define CB_SLOT_MODEL_STATIC b2
#define CB_SLOT_MODEL_DYNAMIC b3

// �O���[�o���ȃR���X�^���g�o�b�t�@
#define CB_GLOBAL_BEGIN cbuffer CBGlobal : register(CB_SLOT_GLOBAL) {
#define CB_GLOBAL_END };

// �V�[���̃R���X�^���g�o�b�t�@
#define CB_SCENE_BEGIN cbuffer CBScene : register(CB_SLOT_SCENE) {
#define CB_SCENE_END };

// ���f���̃X�^�e�B�b�N�ȃR���X�^���g�o�b�t�@
#define CB_MODEL_STATIC_BEGIN cbuffer CBModelStatic : register(CB_SLOT_MODEL_STATIC) {
#define CB_MODEL_STATIC_END };

// ���f���̃_�C�i�~�b�N�ȃR���X�^���g�o�b�t�@(���[�U�[���Œ�`)
#define CB_MODEL_DYNAMIC_BEGIN cbuffer CBModelDynamic : register(CB_SLOT_MODEL_DYNAMIC) {
#define CB_MODEL_DYNAMIC_END };

#endif // CONSTANT_BUFFER_DEFINE_HLSLI