#include "shader/util/ShaderUtil.h"

#include <iostream>
#include <fstream>

#include "core/core.h"

namespace shader {
namespace util {

//! @brief シェーダーコンパイル
HRESULT compileShaderFromFile(Microsoft::WRL::ComPtr<IDxcBlob>& blob, const wchar_t* filePath)
{
	using namespace std::experimental;

	filesystem::path path(filePath);

	auto filename = path.filename();
	filename.replace_extension("");

	const wchar_t* profile = shader::util::getTargetProfileByFilename(filename.c_str());

	std::ifstream infile(path);
	if (!infile)
	{
		return E_FAIL;
	}

	std::vector <char> srcData;
	srcData.resize(uint32_t(infile.seekg(0, infile.end).tellg()));
	infile.seekg(0, infile.beg).read(srcData.data(), srcData.size());

	// DXCによるコンパイル
	Microsoft::WRL::ComPtr<IDxcLibrary> library;
	Microsoft::WRL::ComPtr<IDxcCompiler> compiler;
	Microsoft::WRL::ComPtr<IDxcBlobEncoding> source;
	Microsoft::WRL::ComPtr<IDxcOperationResult> dxcResult;
	Microsoft::WRL::ComPtr<IDxcIncludeHandler> includeHandler;

	DxcCreateInstance(CLSID_DxcLibrary, IID_PPV_ARGS(&library));
	library->CreateBlobWithEncodingFromPinned(srcData.data(), UINT(srcData.size()), CP_ACP, &source);
	DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&compiler));

	Microsoft::WRL::ComPtr<IDxcBlob> includeSource;
	library->CreateIncludeHandler(includeHandler.GetAddressOf());
	includeHandler->LoadSource(path.c_str(), includeSource.GetAddressOf());

	LPCWSTR compilerFlags[] = {
		DXC_ARG_OPTIMIZATION_LEVEL2,
		//#if _DEBUG
		//		L"/Zi", L"/O0",
		//#else 
		//		L"/O2" // リリースでは最適化
		//#endif
	};
	compiler->Compile(
		source.Get(),
		path.c_str(),
		L"main",
		profile,
		compilerFlags,
		_countof(compilerFlags),
		nullptr,
		0,
		includeHandler.Get(),
		&dxcResult
	);

	HRESULT hr;
	dxcResult->GetStatus(&hr);
	if (SUCCEEDED(hr))
	{
		dxcResult->GetResult(blob.GetAddressOf());

		return hr;
	}
	else
	{
		Microsoft::WRL::ComPtr<IDxcBlobEncoding> errorBlob;
		dxcResult->GetErrorBuffer(errorBlob.GetAddressOf());
		std::cout << (static_cast<const char*>(errorBlob->GetBufferPointer())) << std::endl;
	}

	return E_FAIL;
}
	// ターゲットプロファイル(e.g. ps_6_0)をファイル名から取得
const wchar_t* getTargetProfileByFilename(const wchar_t* filename)
{
	std::wstring filenameStr(filename);
	if (filenameStr.find(L"_vs") != std::wstring::npos)
	{
		return L"vs_6_0";
	}
	else if (filenameStr.find(L"_ps") != std::wstring::npos)
	{
		return L"ps_6_0";
	}
	else if (filenameStr.find(L"_cs") != std::wstring::npos)
	{
		return L"cs_6_0";
	}
	else if (filenameStr.find(L"_gs") != std::wstring::npos)
	{
		return L"gs_6_0";
	}
	else if (filenameStr.find(L"_ds") != std::wstring::npos)
	{
		return L"ds_6_0";
	}
	else if (filenameStr.find(L"_hs") != std::wstring::npos)
	{
		return L"hs_6_0";
	}

	return L"";
}

// シェーダーリフレクション取得
HRESULT getShaderReflection(Microsoft::WRL::ComPtr<ID3D12ShaderReflection>& shaderRfl, const Microsoft::WRL::ComPtr<IDxcBlob>& shaderBlob)
{
	if (!shaderBlob.Get())
	{
		return E_FAIL;
	}

	HRESULT hr;
	Microsoft::WRL::ComPtr<IDxcContainerReflection> pReflection;
	UINT32 shaderIdx;

	hr = DxcCreateInstance(CLSID_DxcContainerReflection, IID_PPV_ARGS(&pReflection));
	if (FAILED(hr))
	{
		return hr;
	}

	hr = pReflection->Load(shaderBlob.Get());
	if (FAILED(hr))
	{
		return hr;
	}

	hr = pReflection->FindFirstPartKind(hlsl::DFCC_DXIL, &shaderIdx);
	if (FAILED(hr))
	{
		return hr;
	}

	hr = pReflection->GetPartReflection(shaderIdx, IID_PPV_ARGS(&shaderRfl));

	return hr;
}

} // namespace util
} // namespace shader