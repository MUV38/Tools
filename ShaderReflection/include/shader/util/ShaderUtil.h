#pragma once

#include <string>

#include <wrl.h>
#include <d3d12.h>
#include <d3d12shader.h>

#include "dxc/MyDxcApi.h"

namespace shader {
namespace util {

//! @brief �V�F�[�_�[�R���p�C��
HRESULT compileShaderFromFile(Microsoft::WRL::ComPtr<IDxcBlob>& blob, const wchar_t* filePath);

//! @brief �^�[�Q�b�g�v���t�@�C��(e.g. ps_6_0)���t�@�C��������擾
const wchar_t* getTargetProfileByFilename(const wchar_t* filename);

//! @brief �V�F�[�_�[���t���N�V�����擾
HRESULT getShaderReflection(Microsoft::WRL::ComPtr<ID3D12ShaderReflection>& shaderRfl, const Microsoft::WRL::ComPtr<IDxcBlob>& shaderBlob);

} // namespace util
} // namespace shader