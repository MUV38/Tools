#pragma once

#include <vector>
#include <string>

//! @brief マテリアル
class Material
{
public:
	using MeshIndexList = std::vector<uint32_t>;

public:
	Material();
	~Material();

	//! @brief メッシュのインデックスリスト追加
	void addMeshIndex(uint32_t index);

	//! @brief 名前
	const char* getName() const;
	void setName(const char* name);

	//! @brief メッシュのインデックス数
	uint32_t getNUmMeshIndex() const;

	//! @brief メッシュのインデックスリスト
	const MeshIndexList& getMeshIndexList() const;

private:
	std::string mName;
	MeshIndexList mMeshIndexList;
};