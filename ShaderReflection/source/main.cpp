#include <wrl.h>
#include <d3d12.h>
#include <d3d12shader.h>

#include "dxc/MyDxcApi.h"

#include <picojson/picojson.h>

#include <iostream>
#include <fstream>
#include <vector>

#include "core/core.h"
#include "shader/reflection/ShaderReflectionContainer.h"
#include "shader/util/ShaderUtil.h"

using namespace std::experimental;

int main(int argc, char* argv[])
{
	if (argc < 3) 
	{ 
		std::cout << "The number of command line arguments is not enough." << std::endl;
		std::cout << "arg1 : search directory, arg2 : output directory." << std::endl;
		return -1;
	}

	const char* searchDir = argv[1];
	const char* outputPath = argv[2];

	// シェーダーリフレクション
	HRESULT hr;
	shader::reflection::ShaderReflectionContainer shRflContainer;
	if (filesystem::exists(searchDir) && filesystem::is_directory(searchDir))
	{
		std::cout << "---Begin ShaderReflection---" << std::endl;
		for (auto& entry : filesystem::recursive_directory_iterator(searchDir)) 
		{
			const auto& path = entry.path();
			if (filesystem::is_regular_file(path) && path.extension() == ".hlsl")
			{
				std::cout << "[ShaderReflection : " << path.filename().string().c_str() << "]" << std::endl;
				Microsoft::WRL::ComPtr<IDxcBlob> blob;
				hr = shader::util::compileShaderFromFile(blob, path.c_str());

				if (SUCCEEDED(hr))
				{
					Microsoft::WRL::ComPtr<ID3D12ShaderReflection> shaderRfl;
					hr = shader::util::getShaderReflection(shaderRfl, blob);

					if (SUCCEEDED(hr))
					{
						shRflContainer.addShaderReflection(path.string().c_str(), shaderRfl.Get());
					}
				}

			}
		}
		std::cout << "---End ShaderReflection---" << std::endl;
	}

	std::cout << std::endl;

	// json出力
	{
		std::ofstream ofs(outputPath);
		if (ofs)
		{
			picojson::value value;
			shRflContainer.serializeToJson(value);
			ofs << value.serialize(true);

			std::cout << "Succeed output json[" << outputPath << "]." << std::endl;
		}
		else
		{
			std::cout << "Failed output json..." << std::endl;
		}
	}

	return 0;
}