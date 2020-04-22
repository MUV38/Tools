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

//! @brief json�ɃV���A���C�Y�\�ȃI�u�W�F�N�g
class JsonSerializeable
{
public:
	virtual ~JsonSerializeable() {}

	//! @brief json�ɃV���A���C�Y
	virtual void serializeToJson(picojson::value& value) = 0;
};

//! @brief �V�F�[�_�[�̃p�����[�^���Ƃ̃f�[�^
class ShaderParamData : public JsonSerializeable
{
public:
	ShaderParamData();
	explicit ShaderParamData(ID3D12ShaderReflectionVariable* variable);
	virtual ~ShaderParamData();

	//! @brief json�ɃV���A���C�Y
	void serializeToJson(picojson::value& value) override;

public:
	//! @brief �p�����[�^��
	const std::string& getName() const;
	void setName(const std::string& name);

	//! @brief �p�����[�^�^�C�v
	const std::string& getType() const;
	void setType(const std::string& type);

private:
	std::string mName; //!< �p�����[�^��
	std::string mType; //!< �p�����[�^�^�C�v
};

//! @brief �V�O�l�`�����Ƃ̃f�[�^
class SignatureData : public JsonSerializeable
{
public:
	//! @brief �R���|�[�l���g�^�C�v���擾
	static const char* getComponentTypeName(D3D_REGISTER_COMPONENT_TYPE type);

public:
	SignatureData();
	explicit SignatureData(const D3D12_SIGNATURE_PARAMETER_DESC& desc);
	virtual ~SignatureData();

	//! @brief json�ɃV���A���C�Y
	void serializeToJson(picojson::value& value) override;

public:
	//! @brief �Z�}���e�B�b�N��
	const std::string& getSemanticName() const;
	void setSemanticName(const std::string& semanticName);

	//! @brief �Z�}���e�B�b�N�C���f�b�N�X
	int64_t getSemanticIndex() const;
	void setSemanticIndex(int64_t semanticIndex);

	//! @brief ���W�X�^�ԍ�
	int64_t getRegister() const;
	void setRegister(int64_t registerNo);

	//! @brief �R���|�[�l���g�^�C�v
	const std::string& getComponentType() const;
	void setComponentType(const std::string& componentType);

	//! @brief �}�X�N
	int64_t getMask() const;
	void setMask(int64_t mask);

private:
	std::string mSemanticName;		//!< �Z�}���e�B�b�N��
	int64_t mSemanticIndex;			//!< �Z�}���e�B�b�N�C���f�b�N�X
	int64_t mRegister;				//!< ���W�X�^�ԍ�
	std::string mComponentType;		//!< �R���|�[�l���g�^�C�v
	int64_t mMask;					//!< �}�X�N
};

//! @brief �e�N�X�`�����Ƃ̃f�[�^
class TextureData : public JsonSerializeable
{
public:
	TextureData();
	explicit TextureData(const D3D12_SHADER_INPUT_BIND_DESC& desc);
	virtual ~TextureData();

	//! @brief json�ɃV���A���C�Y
	void serializeToJson(picojson::value& value) override;

public:
	//! @brief �e�N�X�`����
	const std::string& getName() const;
	void setName(const std::string& name);

	//! @brief �X���b�g�ԍ�
	int64_t getSlot() const;
	void setSlot(int64_t slot);

private:
	std::string mName;	//!< �e�N�X�`����
	int64_t mSlot;		//!< �X���b�g�ԍ�
};

//! @brief �V�F�[�_�[���Ƃ̃f�[�^
class ShaderData : public JsonSerializeable
{
public:
	//! @brief �V�F�[�_�[�^�C�v���擾
	static const char* getTypeName(UINT type);

public:
	ShaderData(const char* filePath, ID3D12ShaderReflection* d3dShaderReflection);
	virtual ~ShaderData();

	//! @brief json�ɃV���A���C�Y
	void serializeToJson(picojson::value& value) override;

	//! @brief �t�@�C���p�X
	const std::string& getFilePath() const;
	void setFilePath(const std::string& filePath);

	//! @brief �V�F�[�_�[��
	const std::string& getName() const;
	void setName(const std::string& name);

	//! @brief �V�F�[�_�[�^�C�v
	const std::string& getType() const;
	void setType(const std::string& type);

	//! @brief ���̓V�O�l�`����
	int64_t getNumInputSignature() const;
	void setNumInputSignature(int64_t num);

	//! @brief ���̓V�O�l�`��
	std::vector<SignatureData>& getInputSignatures();

	//! @brief �o�̓V�O�l�`����
	int64_t getNumOutputSignature() const;
	void setNumOutputSignature(int64_t num);

	//! @brief �o�̓V�O�l�`��
	std::vector<SignatureData>& getOutputSignatures();

	//! @brief ���[�U�[�e�N�X�`����
	int64_t getNumUserTexture() const;
	void setNumUserTexture(int64_t num);

	//! @brief ���[�U�[�e�N�X�`��
	std::vector<TextureData>& getUserTextures();

	//! @brief ���f���̃_�C�i�~�b�N�p�����[�^��
	int64_t getNumModelDynamicParam() const;
	void setNumModelDynamicParam(int64_t num);

	//! @brief ���f���̃_�C�i�~�b�N�p�����[�^
	std::vector<ShaderParamData>& getModelDynamicParams();
	
private:
	std::string mFilePath;								//!< �t�@�C���p�X
	std::string mName;									//!< �V�F�[�_�[��
	std::string mType;									//!< �V�F�[�_�[�^�C�v
	int64_t mNumInputSignature;							//!< ���̓V�O�l�`����
	std::vector<SignatureData> mInputSignatures;		//!< ���̓V�O�l�`��
	int64_t mNumOutputSignature;						//!< �o�̓V�O�l�`����
	std::vector<SignatureData> mOutputSignatures;		//!< �o�̓V�O�l�`��
	int64_t mNumUserTexture;							//!< ���[�U�[�e�N�X�`����
	std::vector<TextureData> mUserTextures;				//!< ���[�U�[�e�N�X�`��
	int64_t mNumModelDynamicParam;						//!< ���f���̃_�C�i�~�b�N�p�����[�^��
	std::vector<ShaderParamData> mModelDynamicParams;	//!< ���f���̃_�C�i�~�b�N�p�����[�^
};

//! @brief �V�F�[�_���t���N�V�����R���e�i
class ShaderReflectionContainer : public JsonSerializeable
{
public:
	ShaderReflectionContainer();
	virtual ~ShaderReflectionContainer();

	//! @brief �V�F�[�_�[���t���N�V�����ǉ�
	void addShaderReflection(const char* filePath, ID3D12ShaderReflection* d3dShaderReflection);

	//! @brief json�ɃV���A���C�Y
	void serializeToJson(picojson::value& value) override;

private:
	std::vector<ShaderData> mShaderDatas;
};

} // namespace reflection
} // namespace shader