#include "model/mesh.h"

Mesh::Mesh()
    : mVertices()
    , mIndices()
    , mMaterialIndex(0)
{
}

Mesh::~Mesh()
{

}

// 頂点数
uint32_t Mesh::getNumVertex() const
{
    return static_cast<uint32_t>(mVertices.size());
}

// 頂点
const std::vector<Mesh::Vertex>& Mesh::getVertices() const
{
    return mVertices;
}
void Mesh::setVertices(const std::vector<Vertex>& vertices)
{
    mVertices = vertices;
}

// インデックス数
uint32_t Mesh::getNumIndex() const
{
    return static_cast<uint32_t>(mIndices.size());
}

// インデックス
const std::vector<Mesh::Index>& Mesh::getIndices() const
{
    return mIndices;
}
void Mesh::setIndices(const std::vector<Index>& indices)
{
    mIndices = indices;
}

// マテリアルインデックス
uint32_t Mesh::getMaterialIndex() const
{
	return mMaterialIndex;
}
void Mesh::setMaterialIndex(uint32_t index)
{
    mMaterialIndex = index;
}
