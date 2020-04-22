#pragma once

#include <string>
#include <vector>

#include <wrl.h>

#include <d3d12.h>
#include <d3d12shader.h>

#include <picojson/picojson.h>

#include "dxc/MyDxcApi.h"

namespace shader {
namespace reflection {

//! @brief jsonにシリアライズ可能なオブジェクト
class JsonSerializeable
{
public:
	virtual ~JsonSerializeable() {}

	//! @brief jsonにシリアライズ
	virtual void serializeToJson(picojson::value& value) = 0;
};

//! @brief シェーダーのパラメータごとのデータ
class ShaderParamData : public JsonSerializeable
{
public:
	ShaderParamData();
	explicit ShaderParamData(ID3D12ShaderReflectionVariable* variable);
	virtual ~ShaderParamData();

	//! @brief jsonにシリアライズ
	void serializeToJson(picojson::value& value) override;

public:
	//! @brief パラメータ名
	const std::string& getName() const;
	void setName(const std::string& name);

	//! @brief パラメータタイプ
	const std::string& getType() const;
	void setType(const std::string& type);

private:
	std::string mName; //!< パラメータ名
	std::string mType; //!< パラメータタイプ
};

//! @brief シグネチャごとのデータ
class SignatureData : public JsonSerializeable
{
public:
	//! @brief コンポーネントタイプ名取得
	static const char* getComponentTypeName(D3D_REGISTER_COMPONENT_TYPE type);

public:
	SignatureData();
	explicit SignatureData(const D3D12_SIGNATURE_PARAMETER_DESC& desc);
	virtual ~SignatureData();

	//! @brief jsonにシリアライズ
	void serializeToJson(picojson::value& value) override;

public:
	//! @brief セマンティック名
	const std::string& getSemanticName() const;
	void setSemanticName(const std::string& semanticName);

	//! @brief セマンティックインデックス
	int64_t getSemanticIndex() const;
	void setSemanticIndex(int64_t semanticIndex);

	//! @brief レジスタ番号
	int64_t getRegister() const;
	void setRegister(int64_t registerNo);

	//! @brief コンポーネントタイプ
	const std::string& getComponentType() const;
	void setComponentType(const std::string& componentType);

	//! @brief マスク
	int64_t getMask() const;
	void setMask(int64_t mask);

private:
	std::string mSemanticName;		//!< セマンティック名
	int64_t mSemanticIndex;			//!< セマンティックインデックス
	int64_t mRegister;				//!< レジスタ番号
	std::string mComponentType;		//!< コンポーネントタイプ
	int64_t mMask;					//!< マスク
};

//! @brief テクスチャごとのデータ
class TextureData : public JsonSerializeable
{
public:
	TextureData();
	explicit TextureData(const D3D12_SHADER_INPUT_BIND_DESC& desc);
	virtual ~TextureData();

	//! @brief jsonにシリアライズ
	void serializeToJson(picojson::value& value) override;

public:
	//! @brief テクスチャ名
	const std::string& getName() const;
	void setName(const std::string& name);

	//! @brief スロット番号
	int64_t getSlot() const;
	void setSlot(int64_t slot);

private:
	std::string mName;	//!< テクスチャ名
	int64_t mSlot;		//!< スロット番号
};

//! @brief シェーダーごとのデータ
class ShaderData : public JsonSerializeable
{
public:
	//! @brief シェーダータイプ名取得
	static const char* getTypeName(UINT type);

public:
	ShaderData(const char* filePath, ID3D12ShaderReflection* d3dShaderReflection);
	virtual ~ShaderData();

	//! @brief jsonにシリアライズ
	void serializeToJson(picojson::value& value) override;

	//! @brief ファイルパス
	const std::string& getFilePath() const;
	void setFilePath(const std::string& filePath);

	//! @brief シェーダー名
	const std::string& getName() const;
	void setName(const std::string& name);

	//! @brief シェーダータイプ
	const std::string& getType() const;
	void setType(const std::string& type);

	//! @brief 入力シグネチャ数
	int64_t getNumInputSignature() const;
	void setNumInputSignature(int64_t num);

	//! @brief 入力シグネチャ
	std::vector<SignatureData>& getInputSignatures();

	//! @brief 出力シグネチャ数
	int64_t getNumOutputSignature() const;
	void setNumOutputSignature(int64_t num);

	//! @brief 出力シグネチャ
	std::vector<SignatureData>& getOutputSignatures();

	//! @brief ユーザーテクスチャ数
	int64_t getNumUserTexture() const;
	void setNumUserTexture(int64_t num);

	//! @brief ユーザーテクスチャ
	std::vector<TextureData>& getUserTextures();

	//! @brief モデルのダイナミックパラメータ数
	int64_t getNumModelDynamicParam() const;
	void setNumModelDynamicParam(int64_t num);

	//! @brief モデルのダイナミックパラメータ
	std::vector<ShaderParamData>& getModelDynamicParams();
	
private:
	std::string mFilePath;								//!< ファイルパス
	std::string mName;									//!< シェーダー名
	std::string mType;									//!< シェーダータイプ
	int64_t mNumInputSignature;							//!< 入力シグネチャ数
	std::vector<SignatureData> mInputSignatures;		//!< 入力シグネチャ
	int64_t mNumOutputSignature;						//!< 出力シグネチャ数
	std::vector<SignatureData> mOutputSignatures;		//!< 出力シグネチャ
	int64_t mNumUserTexture;							//!< ユーザーテクスチャ数
	std::vector<TextureData> mUserTextures;				//!< ユーザーテクスチャ
	int64_t mNumModelDynamicParam;						//!< モデルのダイナミックパラメータ数
	std::vector<ShaderParamData> mModelDynamicParams;	//!< モデルのダイナミックパラメータ
};

//! @brief シェーダリフレクションコンテナ
class ShaderReflectionContainer : public JsonSerializeable
{
public:
	ShaderReflectionContainer();
	virtual ~ShaderReflectionContainer();

	//! @brief シェーダーリフレクション追加
	void addShaderReflection(const char* filePath, ID3D12ShaderReflection* d3dShaderReflection);

	//! @brief jsonにシリアライズ
	void serializeToJson(picojson::value& value) override;

private:
	std::vector<ShaderData> mShaderDatas;
};

} // namespace reflection
} // namespace shader