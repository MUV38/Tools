#include "model/material.h"

Material::Material()
	: mName("")
	, mMeshIndexList()
{
}

Material::~Material()
{
}

// ���b�V���̃C���f�b�N�X���X�g�ǉ�
void Material::addMeshIndex(uint32_t index)
{
	mMeshIndexList.push_back(index);
}

// ���O
const char* Material::getName() const
{
	return mName.c_str();
}
void Material::setName(const char* name)
{
	mName = name;
}

// ���b�V���̃C���f�b�N�X��
uint32_t Material::getNUmMeshIndex() const
{
	return static_cast<uint32_t>(mMeshIndexList.size());
}

// ���b�V���̃C���f�b�N�X���X�g�擾
const Material::MeshIndexList& Material::getMeshIndexList() const
{
	return mMeshIndexList;
}
