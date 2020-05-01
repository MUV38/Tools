#pragma once

#include <vector>

#include <DirectXMath.h>
#include <string>

/// メッシュ
class Mesh
{
public:
    //! @brief 頂点
    struct Vertex
    {
        DirectX::XMFLOAT3 position;
        DirectX::XMFLOAT3 normal;
        DirectX::XMFLOAT3 tangent;
        DirectX::XMFLOAT3 binormal;
        DirectX::XMFLOAT2 uv;
    };

    //! @brief インデックス
    using Index = uint32_t;

public:
    Mesh();
    ~Mesh();

    //! @brief 名前
    const std::string& getName() const;
    void setName(const std::string& name);

    //! @brief 頂点数
    uint32_t getNumVertex() const;

    //! @brief 頂点
    const std::vector<Vertex>& getVertices() const;
    void setVertices(const std::vector<Vertex>& vertices);

    //! @brief インデックス数
    uint32_t getNumIndex() const;

    //! @brief インデックス
    const std::vector<Index>& getIndices() const;
    void setIndices(const std::vector<Index>& indices);

    //! @brief マテリアルインデックス
    uint32_t getMaterialIndex() const;
    void setMaterialIndex(uint32_t index);

private:
    std::string mName;
    std::vector<Vertex> mVertices;
    std::vector<Index> mIndices;
    uint32_t mMaterialIndex;
};