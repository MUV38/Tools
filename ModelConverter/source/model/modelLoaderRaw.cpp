#include "model/modelLoaderRaw.h"

#include <vector>
#include <fstream>

#include "core/core.h"
#include "assimp/assimp.h"
#include "picojson/picojson.h"

using namespace std::experimental;

ModelLoaderRaw::ModelLoaderRaw()
    : mIsLoaded(false)
{
}

ModelLoaderRaw::~ModelLoaderRaw()
{
}

// ロード
bool ModelLoaderRaw::load(const wchar_t* filePath)
{
    Assimp::Importer importer;

    std::string filePathStr = util::ToString(filePath);

    const aiScene* scene = importer.ReadFile(
        filePathStr.c_str(),
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType |
        aiProcess_ConvertToLeftHanded
    );

    if (scene)
    {
        // マテリアル
        for (size_t i = 0; i < scene->mNumMaterials; ++i)
        {
            auto material = processMaterial(scene->mMaterials[i], scene);
            mMaterials.push_back(material);
        }

        // ノード
        processNode(scene->mRootNode, scene);

        // マテリアルリスト構築
        associateMeshWithMaterial();

        mIsLoaded = true;
    }
    else
    {
        OutputDebugStringA(importer.GetErrorString());
        return false;
    }

    return true;
}

// ロード済みか
bool ModelLoaderRaw::isLoaded() const
{
    return mIsLoaded;
}

// エクスポート(json)
bool ModelLoaderRaw::exportToJson(const wchar_t* outputPath)
{
    filesystem::path path = outputPath;
    
    // フォーマットチェック
    if (!path.has_extension() || path.extension() != ".json")
    {
        return false;
    }

    // jsonデータ構築
    picojson::value jsonValue;
    {
        // mesh
        picojson::array meshArray;
        for (auto& mesh : mMeshes)
        {
            picojson::array vertexArray;
            for (auto& vertex : mesh->getVertices())
            {
                picojson::array positionArray;
                positionArray.push_back(picojson::value(static_cast<double>(vertex.position.x)));
                positionArray.push_back(picojson::value(static_cast<double>(vertex.position.y)));
                positionArray.push_back(picojson::value(static_cast<double>(vertex.position.z)));

                picojson::array normalArray;
                normalArray.push_back(picojson::value(static_cast<double>(vertex.normal.x)));
                normalArray.push_back(picojson::value(static_cast<double>(vertex.normal.y)));
                normalArray.push_back(picojson::value(static_cast<double>(vertex.normal.z)));

                picojson::array tangentArray;
                tangentArray.push_back(picojson::value(static_cast<double>(vertex.tangent.x)));
                tangentArray.push_back(picojson::value(static_cast<double>(vertex.tangent.y)));
                tangentArray.push_back(picojson::value(static_cast<double>(vertex.tangent.z)));

                picojson::array binormalArray;
                binormalArray.push_back(picojson::value(static_cast<double>(vertex.binormal.x)));
                binormalArray.push_back(picojson::value(static_cast<double>(vertex.binormal.y)));
                binormalArray.push_back(picojson::value(static_cast<double>(vertex.binormal.z)));

                picojson::array uvArray;
                uvArray.push_back(picojson::value(static_cast<double>(vertex.uv.x)));
                uvArray.push_back(picojson::value(static_cast<double>(vertex.uv.y)));

                picojson::object vertexObj;
                vertexObj["Position"] = picojson::value(positionArray);
                vertexObj["Normal"] = picojson::value(normalArray);
                vertexObj["Tangent"] = picojson::value(tangentArray);
                vertexObj["Binormal"] = picojson::value(binormalArray);
                vertexObj["UV"] = picojson::value(uvArray);

                vertexArray.push_back(picojson::value(vertexObj));
            }

            picojson::array indexArray;
            for (auto& index : mesh->getIndices())
            {
                indexArray.push_back(picojson::value(static_cast<double>(index)));
            }

            picojson::object meshObj;
            meshObj["Name"] = picojson::value(mesh->getName().c_str());
            meshObj["NumVertex"] = picojson::value(static_cast<double>(mesh->getNumVertex()));
            meshObj["NumIndex"] = picojson::value(static_cast<double>(mesh->getNumIndex()));
            meshObj["MaterialIndex"] = picojson::value(static_cast<double>(mesh->getMaterialIndex()));
            meshObj["Vertex"] = picojson::value(vertexArray);
            meshObj["Index"] = picojson::value(indexArray);

            meshArray.push_back(picojson::value(meshObj));
        }

        // material
        picojson::array materialArray;
        for (auto& material : mMaterials)
        {
            picojson::array meshIndexArray;
            for (auto meshIndex : material->getMeshIndexList())
            {
                meshIndexArray.push_back(picojson::value(static_cast<double>(meshIndex)));
            }

            picojson::object materialObj;
            materialObj["Name"] = picojson::value(material->getName());
            materialObj["NumMeshIndex"] = picojson::value(static_cast<double>(material->getNUmMeshIndex()));
            materialObj["MeshIndex"] = picojson::value(meshIndexArray);

            materialArray.push_back(picojson::value(materialObj));
        }

        picojson::object modelObj;
        modelObj["NumMesh"] = picojson::value(static_cast<double>(mMeshes.size()));
        modelObj["NumMaterial"] = picojson::value(static_cast<double>(mMaterials.size()));
        modelObj["Mesh"] = picojson::value(meshArray);
        modelObj["Material"] = picojson::value(materialArray);
    
        jsonValue = picojson::value(modelObj);
    }

    // ファイル出力
    std::ofstream ofs(outputPath);
    if (!ofs)
    {
        return false;
    }
    ofs << jsonValue.serialize(true);

    return true;
}

// ノード探索
void ModelLoaderRaw::processNode(aiNode* node, const aiScene* scene)
{
    for (size_t i = 0; i < node->mNumMeshes; i++)
    {
        auto mesh = processMesh(scene->mMeshes[node->mMeshes[i]], scene);
        mMeshes.push_back(mesh);
    }

    for (size_t i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

// メッシュ探索
ModelLoaderRaw::MeshPtr ModelLoaderRaw::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Mesh::Vertex> vertices;
    std::vector<Mesh::Index> indices;
    
    for (size_t i = 0; i < mesh->mNumVertices; i++)
    {
        Mesh::Vertex vertex;
        
        vertex.position.x = mesh->mVertices[i].x;
        vertex.position.y = mesh->mVertices[i].y;
        vertex.position.z = mesh->mVertices[i].z;

        if (mesh->mTextureCoords[0])
        {
            vertex.uv.x = static_cast<float>(mesh->mTextureCoords[0][i].x);
            vertex.uv.y = static_cast<float>(mesh->mTextureCoords[0][i].y);
        }

        vertex.normal.x = mesh->mNormals[i].x;
        vertex.normal.y = mesh->mNormals[i].y;
        vertex.normal.z = mesh->mNormals[i].z;

        vertex.tangent.x = mesh->mTangents[i].x;
        vertex.tangent.y = mesh->mTangents[i].y;
        vertex.tangent.z = mesh->mTangents[i].z;

        vertex.binormal.x = mesh->mBitangents[i].x;
        vertex.binormal.y = mesh->mBitangents[i].y;
        vertex.binormal.z = mesh->mBitangents[i].z;

        vertices.push_back(vertex);
    }

    for (size_t i = 0; i < mesh->mNumFaces; i++)
    {
        const auto& face = mesh->mFaces[i];
        for (size_t j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }
    
    const char* name = mesh->mName.C_Str();
    uint32_t materialIndex = mesh->mMaterialIndex;

    MeshPtr outMesh(new Mesh());
    outMesh->setName(name);
    outMesh->setVertices(vertices);
    outMesh->setIndices(indices);
    outMesh->setMaterialIndex(materialIndex);

    return outMesh;
}

// マテリアル探索
ModelLoaderRaw::MaterialPtr ModelLoaderRaw::processMaterial(aiMaterial* material, const aiScene* scene)
{
    MaterialPtr outMaterials(new Material());
    outMaterials->setName(material->GetName().C_Str());

    return outMaterials;
}

// マテリアルリスト構築
void ModelLoaderRaw::associateMeshWithMaterial()
{
    if (mMeshes.size() <= 0 || mMaterials.size() <= 0)
    {
        ASSERT(false);
        return;
    }

    for (size_t i=0 ; i<mMeshes.size() ; ++i)
    {
        const auto& mesh = mMeshes[i];
        const auto materialIndex = mesh->getMaterialIndex();

        mMaterials[materialIndex]->addMeshIndex(static_cast<uint32_t>(i));
    }
}
