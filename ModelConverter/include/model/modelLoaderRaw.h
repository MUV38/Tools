#pragma once

#include <memory>
#include "Mesh.h"
#include "Material.h"

struct aiScene;
struct aiNode;
struct aiMesh;
struct aiMaterial;

//! @brief モデルローダー(生データ向け e.g. fbx)
class ModelLoaderRaw
{
public:
    ModelLoaderRaw();
    ~ModelLoaderRaw();

    //! @brief ロード
    bool load(const wchar_t* filePath);

    //! @brief ロード済みか
    bool isLoaded() const;

    //! @brief エクスポート(json)
    bool exportToJson(const wchar_t* outputPath);

private:
    using MeshPtr = std::shared_ptr<Mesh>;
    using MaterialPtr = std::shared_ptr<Material>;

private:
    //! @brief ノード探索
    void processNode(aiNode* node, const aiScene* scene);
    //! @brief メッシュ探索
    MeshPtr processMesh(aiMesh* mesh, const aiScene* scene);
    //! @brief マテリアル探索
    MaterialPtr processMaterial(aiMaterial* material, const aiScene* scene);

    //! @brief マテリアルリスト構築
    void associateMeshWithMaterial();

private:
    bool mIsLoaded;
    std::vector<MeshPtr> mMeshes;
    std::vector<MaterialPtr> mMaterials;
};