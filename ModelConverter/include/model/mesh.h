#pragma once

#include <vector>

#include <DirectXMath.h>

/// ���b�V��
class Mesh
{
public:
    //! @brief ���_
    struct Vertex
    {
        DirectX::XMFLOAT3 position;
        DirectX::XMFLOAT3 normal;
        DirectX::XMFLOAT3 tangent;
        DirectX::XMFLOAT3 binormal;
        DirectX::XMFLOAT2 uv;
    };

    //! @brief �C���f�b�N�X
    using Index = uint32_t;

public:
    Mesh();
    ~Mesh();

    //! @brief ���_��
    uint32_t getNumVertex() const;

    //! @brief ���_
    const std::vector<Vertex>& getVertices() const;
    void setVertices(const std::vector<Vertex>& vertices);

    //! @brief �C���f�b�N�X��
    uint32_t getNumIndex() const;

    //! @brief �C���f�b�N�X
    const std::vector<Index>& getIndices() const;
    void setIndices(const std::vector<Index>& indices);

    //! @brief �}�e���A���C���f�b�N�X
    uint32_t getMaterialIndex() const;
    void setMaterialIndex(uint32_t index);

private:
    std::vector<Vertex> mVertices;
    std::vector<Index> mIndices;
    uint32_t mMaterialIndex;
};