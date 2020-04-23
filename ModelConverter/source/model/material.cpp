#include "model/material.h"

Material::Material()
	: mName("")
	, mMeshIndexList()
{
}

Material::~Material()
{
}

// メッシュのインデックスリスト追加
void Material::addMeshIndex(uint32_t index)
{
	mMeshIndexList.push_back(index);
}

// 名前
const char* Material::getName() const
{
	return mName.c_str();
}
void Material::setName(const char* name)
{
	mName = name;
}

// メッシュのインデックス数
uint32_t Material::getNUmMeshIndex() const
{
	return static_cast<uint32_t>(mMeshIndexList.size());
}

// メッシュのインデックスリスト取得
const Material::MeshIndexList& Material::getMeshIndexList() const
{
	return mMeshIndexList;
}
