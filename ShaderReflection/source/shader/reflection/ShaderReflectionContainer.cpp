#include "shader/reflection/ShaderReflectionContainer.h"

#include "filesystem/FileSystem.h"

namespace shader {
namespace reflection {

//------------------------------------------------------------------------------------
// ShaderParamData
//------------------------------------------------------------------------------------
ShaderParamData::ShaderParamData()
	: mName("")
	, mType("")
{
}

ShaderParamData::ShaderParamData(ID3D12ShaderReflectionVariable* variable)
{
	if (variable)
	{
		D3D12_SHADER_VARIABLE_DESC desc;
		variable->GetDesc(&desc);

		D3D12_SHADER_TYPE_DESC shderTypeDesc;
		variable->GetType()->GetDesc(&shderTypeDesc);

		mName = desc.Name;
		mType = shderTypeDesc.Name;
	}
}

ShaderParamData::~ShaderParamData()
{
}

// jsonにシリアライズ
void ShaderParamData::serializeToJson(picojson::value& value)
{
	picojson::value name(mName);
	picojson::value type(mType);

	picojson::object obj;
	obj["Name"] = name;
	obj["Type"] = type;

	value = picojson::value(obj);
}

// パラメータ名
const std::string& ShaderParamData::getName() const
{
	return mName;
}
void ShaderParamData::setName(const std::string& name)
{
	mName = name;
}

// パラメータタイプ
const std::string& ShaderParamData::getType() const
{
	return mType;
}
void ShaderParamData::setType(const std::string& type)
{
	mType = type;
}

//------------------------------------------------------------------------------------
// SignatureData
//------------------------------------------------------------------------------------
// コンポーネントタイプ名取得
const char* SignatureData::getComponentTypeName(D3D_REGISTER_COMPONENT_TYPE type)
{
	switch (type)
	{
	case D3D_REGISTER_COMPONENT_UNKNOWN:
		return "Unknown";
	case D3D_REGISTER_COMPONENT_UINT32:
		return "Uint32";
	case D3D_REGISTER_COMPONENT_SINT32:
		return "Sint32";
	case D3D_REGISTER_COMPONENT_FLOAT32:
		return "Float32";
	}
	return "";
}

SignatureData::SignatureData()
	: mSemanticName("")
	, mSemanticIndex(0)
	, mRegister(0)
	, mComponentType("")
	, mMask(0)
{
}

SignatureData::SignatureData(const D3D12_SIGNATURE_PARAMETER_DESC& desc)
{
	mSemanticName = desc.SemanticName;
	mSemanticIndex = desc.SemanticIndex;
	mRegister = desc.Register;
	mComponentType = getComponentTypeName(desc.ComponentType);
	mMask = desc.Mask;
}

SignatureData::~SignatureData()
{
}

// jsonにシリアライズ
void SignatureData::serializeToJson(picojson::value& value)
{
	picojson::value semanticName(mSemanticName);
	picojson::value semanticIndex(static_cast<double>(mSemanticIndex));
	picojson::value registerNo(static_cast<double>(mRegister));
	picojson::value componentType(mComponentType);
	picojson::value mask(static_cast<double>(mMask));

	picojson::object obj;
	obj["SemanticName"] = semanticName;
	obj["SemanticIndex"] = semanticIndex;
	obj["Register"] = registerNo;
	obj["ComponentType"] = componentType;
	obj["Mask"] = mask;

	value = picojson::value(obj);
}

// セマンティック名
const std::string& SignatureData::getSemanticName() const
{
	return mSemanticName;
}
void SignatureData::setSemanticName(const std::string& semanticName)
{
	mSemanticName = semanticName;
}

// セマンティックインデックス
int64_t SignatureData::getSemanticIndex() const
{
	return mSemanticIndex;
}
void SignatureData::setSemanticIndex(int64_t semanticIndex)
{
	mSemanticIndex = semanticIndex;
}

// レジスタ番号
int64_t SignatureData::getRegister() const
{
	return mRegister;
}
void SignatureData::setRegister(int64_t registerNo)
{
	mRegister = registerNo;
}

// コンポーネントタイプ
const std::string& SignatureData::getComponentType() const
{
	return mComponentType;
}
void SignatureData::setComponentType(const std::string& componentType)
{
	mComponentType = componentType;
}

// マスク
int64_t SignatureData::getMask() const
{
	return mMask;
}
void SignatureData::setMask(int64_t mask)
{
	mMask = mask;
}

//------------------------------------------------------------------------------------
// TextureData
//------------------------------------------------------------------------------------
TextureData::TextureData()
	: mName("")
	, mSlot(0)
{
}

TextureData::TextureData(const D3D12_SHADER_INPUT_BIND_DESC& desc)
{
	mName = desc.Name;
	mSlot = desc.BindPoint;
}

TextureData::~TextureData()
{
}

// jsonにシリアライズ
void TextureData::serializeToJson(picojson::value& value)
{
	picojson::value name(mName);
	picojson::value slot(static_cast<double>(mSlot));

	picojson::object obj;
	obj["Name"] = name;
	obj["Slot"] = slot;

	value = picojson::value(obj);
}

// テクスチャ名
const std::string& TextureData::getName() const
{
	return mName;
}
void TextureData::setName(const std::string& name)
{
	mName = name;
}

// スロット番号
int64_t TextureData::getSlot() const
{
	return mSlot;
}
void TextureData::setSlot(int64_t slot)
{
	mSlot = slot;
}

//------------------------------------------------------------------------------------
// ShaderData
//------------------------------------------------------------------------------------
// シェーダータイプ名取得
const char* ShaderData::getTypeName(UINT type)
{
	if (type == D3D12_SHVER_PIXEL_SHADER)
	{
		return "ps";
	}
	else if (type == D3D12_SHVER_VERTEX_SHADER)
	{
		return "vs";
	}
	else if (type == D3D12_SHVER_GEOMETRY_SHADER)
	{
		return "gs";
	}
	else if (type == D3D12_SHVER_HULL_SHADER)
	{
		return "hs";
	}
	else if (type == D3D12_SHVER_DOMAIN_SHADER)
	{
		return "ds";
	}
	else if (type == D3D12_SHVER_COMPUTE_SHADER)
	{
		return "cs";
	}

	return "";
}

ShaderData::ShaderData(const char* filePath, ID3D12ShaderReflection* d3dShaderReflection)
	: mName("")
	, mType("")
	, mNumInputSignature(0)
	, mInputSignatures()
	, mNumOutputSignature(0)
	, mOutputSignatures()
	, mNumUserTexture(0)
	, mUserTextures()
	, mNumModelDynamicParam(0)
	, mModelDynamicParams()
{
	using namespace std::experimental;

	if (d3dShaderReflection)
	{
		HRESULT hr;

		D3D12_SHADER_DESC shaderDesc;
		hr = d3dShaderReflection->GetDesc(&shaderDesc);

		if (SUCCEEDED(hr))
		{
			auto path = filesystem::path(filePath);
			auto filename = path.filename();
			filename.replace_extension("");

			mFilePath = path.is_absolute() ? myfilesystem::relative(path).string().c_str() : path.string().c_str();
			mName = filename.string().c_str();
			mType = getTypeName((shaderDesc.Version & 0xFFFF0000) >> 16);

			mNumInputSignature = shaderDesc.InputParameters;
			for (UINT i = 0; i < shaderDesc.InputParameters; ++i)
			{
				D3D12_SIGNATURE_PARAMETER_DESC desc;
				hr = d3dShaderReflection->GetInputParameterDesc(i, &desc);

				if (FAILED(hr))
				{
					continue;
				}

				SignatureData data(desc);
				mInputSignatures.push_back(data);
			}

			mNumOutputSignature = shaderDesc.OutputParameters;
			for (UINT i = 0; i < mNumOutputSignature; ++i)
			{
				D3D12_SIGNATURE_PARAMETER_DESC desc;
				hr = d3dShaderReflection->GetOutputParameterDesc(i, &desc);

				if (FAILED(hr))
				{
					continue;
				}

				SignatureData data(desc);
				mOutputSignatures.push_back(data);
			}

			mNumUserTexture = 0;
			UINT numBoundResource = shaderDesc.BoundResources;
			for (UINT i = 0; i < numBoundResource; ++i)
			{
				D3D12_SHADER_INPUT_BIND_DESC desc;
				hr = d3dShaderReflection->GetResourceBindingDesc(i, &desc);

				if (FAILED(hr))
				{
					continue;
				}

				if (desc.Type != D3D_SIT_TEXTURE)
				{
					continue;
				}

				if (strstr(desc.Name, "UserTex_") != nullptr)
				{
					mNumUserTexture++;

					TextureData data(desc);
					mUserTextures.push_back(data);
				}
			}

			if (auto* constantBuffer = d3dShaderReflection->GetConstantBufferByName("CBModelDynamic"))
			{
				D3D12_SHADER_BUFFER_DESC cbDesc;
				hr = constantBuffer->GetDesc(&cbDesc);

				if (SUCCEEDED(hr)) 
				{
					mNumModelDynamicParam = cbDesc.Variables;
					for (UINT i = 0; i < mNumModelDynamicParam; ++i)
					{
						auto* variable = constantBuffer->GetVariableByIndex(i);

						ShaderParamData data(variable);
						mModelDynamicParams.push_back(data);
					}
				}
			}
		}
	}
}

ShaderData::~ShaderData()
{
}

// jsonにシリアライズ
void ShaderData::serializeToJson(picojson::value& value)
{
	picojson::object obj;
	
	picojson::value filePath(mFilePath);
	picojson::value name(mName);
	picojson::value type(mType);
	obj["FilePath"] = filePath;
	obj["Name"] = name;
	obj["Type"] = type;

	picojson::value numInputSignature(static_cast<double>(mNumInputSignature));
	picojson::array inputSignatureArray;
	for (int64_t i = 0; i < mNumInputSignature; ++i)
	{
		picojson::value value;
		mInputSignatures[i].serializeToJson(value);
		inputSignatureArray.push_back(value);
	}
	obj["NumInputSignature"] = numInputSignature;
	obj["InputSignature"] = picojson::value(inputSignatureArray);

	picojson::value numOutputSignature(static_cast<double>(mNumOutputSignature));
	picojson::array outputSignatureArray;
	for (int64_t i = 0; i < mNumOutputSignature; ++i)
	{
		picojson::value value;
		mOutputSignatures[i].serializeToJson(value);
		outputSignatureArray.push_back(value);
	}
	obj["NumOutputSignature"] = numOutputSignature;
	obj["OutputSignature"] = picojson::value(outputSignatureArray);

	picojson::value numUserTexture(static_cast<double>(mNumUserTexture));
	picojson::array userTextureArray;
	for (int64_t i = 0; i < mNumUserTexture; ++i)
	{
		picojson::value value;
		mUserTextures[i].serializeToJson(value);
		userTextureArray.push_back(value);
	}
	obj["NumUserTexture"] = numUserTexture;
	obj["UserTexture"] = picojson::value(userTextureArray);

	picojson::value numModelDynamicParam(static_cast<double>(mNumModelDynamicParam));
	picojson::array modelDynamicParamArray;
	for (int64_t i = 0; i < mNumModelDynamicParam; ++i)
	{
		picojson::value value;
		mModelDynamicParams[i].serializeToJson(value);
		modelDynamicParamArray.push_back(value);
	}
	obj["NumModelDynamicParam"] = numModelDynamicParam;
	obj["ModelDynamicParam"] = picojson::value(modelDynamicParamArray);

	value = picojson::value(obj);
}

// ファイルパス
const std::string& ShaderData::getFilePath() const
{
	return mFilePath;
}
void ShaderData::setFilePath(const std::string& filePath)
{
	mFilePath = filePath;
}

// シェーダー名
const std::string& ShaderData::getName() const
{
	return mName;
}
void ShaderData::setName(const std::string& name)
{
	mName = name;
}

// シェーダータイプ
const std::string& ShaderData::getType() const
{
	return mType;
}
void ShaderData::setType(const std::string& type)
{
	mType = type;
}

// 入力シグネチャ数
int64_t ShaderData::getNumInputSignature() const
{
	return mNumInputSignature;
}
void ShaderData::setNumInputSignature(int64_t num)
{
	mNumInputSignature = num;
}

// 入力シグネチャ
std::vector<SignatureData>& ShaderData::getInputSignatures()
{
	return mInputSignatures;
}

// 出力シグネチャ数
int64_t ShaderData::getNumOutputSignature() const
{
	return mNumOutputSignature;
}
void ShaderData::setNumOutputSignature(int64_t num)
{
	mNumOutputSignature = num;
}

// 出力シグネチャ
std::vector<SignatureData>& ShaderData::getOutputSignatures()
{
	return mOutputSignatures;
}

// ユーザーテクスチャ数
int64_t ShaderData::getNumUserTexture() const
{
	return mNumUserTexture;
}
void ShaderData::setNumUserTexture(int64_t num)
{
	mNumUserTexture = num;
}

// ユーザーテクスチャ
std::vector<TextureData>& ShaderData::getUserTextures()
{
	return mUserTextures;
}

// モデルのダイナミックパラメータ数
int64_t ShaderData::getNumModelDynamicParam() const
{
	return mNumModelDynamicParam;
}
void ShaderData::setNumModelDynamicParam(int64_t num)
{
	mNumModelDynamicParam = num;
}

// モデルのダイナミックパラメータ
std::vector<ShaderParamData>& ShaderData::getModelDynamicParams()
{
	return mModelDynamicParams;
}

//------------------------------------------------------------------------------------
// ShaderReflectionContainer
//------------------------------------------------------------------------------------
ShaderReflectionContainer::ShaderReflectionContainer()
{
}

ShaderReflectionContainer::~ShaderReflectionContainer()
{
}

void ShaderReflectionContainer::addShaderReflection(const char* filePath, ID3D12ShaderReflection* d3dShaderReflection)
{
	ShaderData data(filePath, d3dShaderReflection);
	mShaderDatas.push_back(data);
}

// jsonにシリアライズ
void ShaderReflectionContainer::serializeToJson(picojson::value& value)
{
	picojson::array shaderArray;
	for (auto& data : mShaderDatas)
	{
		picojson::value dataValue;
		data.serializeToJson(dataValue);

		shaderArray.push_back(dataValue);
	}

	picojson::object obj;
	obj["NumShader"] = picojson::value(static_cast<double>(mShaderDatas.size()));
	obj["Shader"] = picojson::value(shaderArray);

	value = picojson::value(obj);
}

} // namespace reflection
} // namespace shader