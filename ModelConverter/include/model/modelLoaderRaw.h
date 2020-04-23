#pragma once

#include <memory>
#include "Mesh.h"
#include "Material.h"

struct aiScene;
struct aiNode;
struct aiMesh;
struct aiMaterial;

//! @brief ���f�����[�_�[(���f�[�^���� e.g. fbx)
class ModelLoaderRaw
{
public:
    ModelLoaderRaw();
    ~ModelLoaderRaw();

    //! @brief ���[�h
    bool load(const wchar_t* filePath);

    //! @brief ���[�h�ς݂�
    bool isLoaded() const;

    //! @brief �G�N�X�|�[�g(json)
    bool exportToJson(const wchar_t* outputPath);

private:
    using MeshPtr = std::shared_ptr<Mesh>;
    using MaterialPtr = std::shared_ptr<Material>;

private:
    //! @brief �m�[�h�T��
    void processNode(aiNode* node, const aiScene* scene);
    //! @brief ���b�V���T��
    MeshPtr processMesh(aiMesh* mesh, const aiScene* scene);
    //! @brief �}�e���A���T��
    MaterialPtr processMaterial(aiMaterial* material, const aiScene* scene);

    //! @brief �}�e���A�����X�g�\�z
    void associateMeshWithMaterial();

private:
    bool mIsLoaded;
    std::vector<MeshPtr> mMeshes;
    std::vector<MaterialPtr> mMaterials;
};