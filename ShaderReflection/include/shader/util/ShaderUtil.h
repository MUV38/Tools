#pragma once

#include <string>

#include <wrl.h>
#include <d3d12.h>
#include <d3d12shader.h>

#include "dxc/MyDxcApi.h"

namespace shader {
namespace util {

//! @brief シェーダーコンパイル
HRESULT compileShaderFromFile(Microsoft::WRL::ComPtr<IDxcBlob>& blob, const wchar_t* filePath);

//! @brief ターゲットプロファイル(e.g. ps_6_0)をファイル名から取得
const wchar_t* getTargetProfileByFilename(const wchar_t* filename);

//! @brief シェーダーリフレクション取得
HRESULT getShaderReflection(Microsoft::WRL::ComPtr<ID3D12ShaderReflection>& shaderRfl, const Microsoft::WRL::ComPtr<IDxcBlob>& shaderBlob);

} // namespace util
} // namespace shader