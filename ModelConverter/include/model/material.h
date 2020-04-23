#pragma once

#include <vector>
#include <string>

//! @brief �}�e���A��
class Material
{
public:
	using MeshIndexList = std::vector<uint32_t>;

public:
	Material();
	~Material();

	//! @brief ���b�V���̃C���f�b�N�X���X�g�ǉ�
	void addMeshIndex(uint32_t index);

	//! @brief ���O
	const char* getName() const;
	void setName(const char* name);

	//! @brief ���b�V���̃C���f�b�N�X��
	uint32_t getNUmMeshIndex() const;

	//! @brief ���b�V���̃C���f�b�N�X���X�g
	const MeshIndexList& getMeshIndexList() const;

private:
	std::string mName;
	MeshIndexList mMeshIndexList;
};