using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Text.Json;
using System.Text.Json.Serialization;
using System.Collections.ObjectModel;

namespace ModelEditor.Model3d
{
    public class VertexData
    {
        [JsonPropertyName("Position")]
        public ObservableCollection<double> Position { get; set; }
        [JsonPropertyName("Normal")]
        public ObservableCollection<double> Normal { get; set; }
        [JsonPropertyName("Tangent")]
        public ObservableCollection<double> Tangent { get; set; }
        [JsonPropertyName("Binormal")]
        public ObservableCollection<double> Binormal { get; set; }
        [JsonPropertyName("UV")]
        public ObservableCollection<double> UV { get; set; }

        public VertexData()
        {
            Position = new ObservableCollection<double>();
            Normal = new ObservableCollection<double>();
            Tangent = new ObservableCollection<double>();
            Binormal = new ObservableCollection<double>();
            UV = new ObservableCollection<double>();
        }

        public bool ParseJsonElement(JsonElement element)
        {
            // position
            JsonElement posElem;
            if (element.TryGetProperty("Position", out posElem))
            {
                ObservableCollection<double> vec = new ObservableCollection<double>();
                ParseVectorElement(ref vec, posElem, 3);
                Position = vec;
            }
            // normal
            JsonElement normalElem;
            if (element.TryGetProperty("Normal", out normalElem))
            {
                ObservableCollection<double> vec = new ObservableCollection<double>();
                ParseVectorElement(ref vec, normalElem, 3);
                Normal = vec;
            }
            // tangent
            JsonElement tangentElem;
            if (element.TryGetProperty("Tangent", out tangentElem))
            {
                ObservableCollection<double> vec = new ObservableCollection<double>();
                ParseVectorElement(ref vec, tangentElem, 3);
                Tangent = vec;
            }
            // binormal
            JsonElement binormalElem;
            if (element.TryGetProperty("Binormal", out binormalElem))
            {
                ObservableCollection<double> vec = new ObservableCollection<double>();
                ParseVectorElement(ref vec, binormalElem, 3);
                Binormal = vec;
            }
            // uv
            JsonElement uvElem;
            if (element.TryGetProperty("UV", out uvElem))
            {
                ObservableCollection<double> vec = new ObservableCollection<double>();
                ParseVectorElement(ref vec, uvElem, 2);
                UV = vec;
            }

            return true;
        }

        private bool ParseVectorElement(ref ObservableCollection<double> vector, JsonElement element, int elementCount)
        {
            if (element.ValueKind == JsonValueKind.Array && element.GetArrayLength() == elementCount)
            {
                for (int i = 0; i < elementCount; ++i)
                {
                    if (element[i].ValueKind == JsonValueKind.Number)
                    {
                        vector.Add(element[i].GetDouble());
                    }
                }
            }

            return true;
        }
    }

    public class MeshData
    {
        [JsonPropertyName("Name")]
        public string Name { get; set; }
        [JsonPropertyName("NumVertex")]
        public uint NumVertex { get; set; }
        [JsonPropertyName("NumIndex")]
        public uint NumIndex { get; set; }
        [JsonPropertyName("MaterialIndex")]
        public uint MaterialIndex { get; set; }
        [JsonPropertyName("Vertex")]
        public ObservableCollection<VertexData> Vertices { get; set; }
        [JsonPropertyName("Index")]
        public ObservableCollection<uint> Indices { get; set; }

        public MeshData()
        {
            Vertices = new ObservableCollection<VertexData>();
            Indices = new ObservableCollection<uint>();
        }

        public bool ParseJsonElement(JsonElement element)
        {
            // Name
            JsonElement nameElem;
            if (element.TryGetProperty("Name", out nameElem))
            {
                if (nameElem.ValueKind == JsonValueKind.String)
                {
                    Name = nameElem.GetString();
                }
            }
            // NumVertex
            JsonElement numVertexElem;
            if (element.TryGetProperty("NumVertex", out numVertexElem))
            {
                if (numVertexElem.ValueKind == JsonValueKind.Number)
                {
                    NumVertex = numVertexElem.GetUInt32();
                }
            }
            // NumIndex
            JsonElement numIndexElem;
            if (element.TryGetProperty("NumIndex", out numIndexElem))
            {
                if (numIndexElem.ValueKind == JsonValueKind.Number)
                {
                    NumIndex = numIndexElem.GetUInt32();
                }
            }
            // MaterialIndex
            JsonElement materialIndexElem;
            if (element.TryGetProperty("MaterialIndex", out materialIndexElem))
            {
                if (materialIndexElem.ValueKind == JsonValueKind.Number)
                {
                    MaterialIndex = materialIndexElem.GetUInt32();
                }
            }
            // Vertex
            JsonElement vertexElem;
            if (element.TryGetProperty("Vertex", out vertexElem))
            {
                if (vertexElem.ValueKind == JsonValueKind.Array)
                {
                    for (int i=0; i<vertexElem.GetArrayLength(); ++i)
                    {
                        var vertex = new VertexData();
                        vertex.ParseJsonElement(vertexElem[i]);
                        Vertices.Add(vertex);
                    }
                }
            }
            // Index
            JsonElement indexElem;
            if (element.TryGetProperty("Index", out indexElem))
            {
                if (indexElem.ValueKind == JsonValueKind.Array)
                {
                    for (int i = 0; i < indexElem.GetArrayLength(); ++i)
                    {
                        if (indexElem[i].ValueKind == JsonValueKind.Number)
                        {
                            Indices.Add(indexElem[i].GetUInt32());
                        }
                    }
                }
            }

            return true;
        }
    }
    public class MaterialData
    {
        [JsonPropertyName("Name")]
        public string Name { get; set; }
        [JsonPropertyName("NumMeshIndex")]
        public uint NumMeshIndex { get; set; }
        [JsonPropertyName("MeshIndex")]
        public ObservableCollection<uint> MeshIndices { get; set; }

        public MaterialData()
        {
            MeshIndices = new ObservableCollection<uint>();
        }

        public bool ParseJsonElement(JsonElement element)
        {
            // Name
            JsonElement nameElem;
            if (element.TryGetProperty("Name", out nameElem))
            {
                if (nameElem.ValueKind == JsonValueKind.String)
                {
                    Name = nameElem.GetString();
                }
            }
            // NumMeshIndex
            JsonElement numMeshIndexElem;
            if (element.TryGetProperty("NumMeshIndex", out numMeshIndexElem))
            {
                if (numMeshIndexElem.ValueKind == JsonValueKind.Number)
                {
                    NumMeshIndex = numMeshIndexElem.GetUInt32();
                }
            }
            // MeshIndex
            JsonElement meshIndexElem;
            if (element.TryGetProperty("MeshIndex", out meshIndexElem))
            {
                if (meshIndexElem.ValueKind == JsonValueKind.Array)
                {
                    for (int i=0; i<meshIndexElem.GetArrayLength(); ++i)
                    {
                        if (meshIndexElem[i].ValueKind == JsonValueKind.Number)
                        {
                            MeshIndices.Add(meshIndexElem[i].GetUInt32());
                        }
                    }
                }
            }

            return true;
        }
    }

    public class Model3dData
    {
        [JsonPropertyName("NumMesh")]
        public uint NumMesh { get; set; }
        [JsonPropertyName("NumMaterial")]
        public uint NumMaterial { get; set; }
        [JsonPropertyName("Mesh")]
        public ObservableCollection<MeshData> Meshes { get; set; }
        [JsonPropertyName("Material")]
        public ObservableCollection<MaterialData> Materials { get; set; }

        public Model3dData()
        {
            Meshes = new ObservableCollection<MeshData>();
            Materials = new ObservableCollection<MaterialData>();
        }

        public bool ParseJsonElement(JsonElement element)
        {
            // NumMesh
            JsonElement numMeshElem;
            if (element.TryGetProperty("NumMesh", out numMeshElem))
            {
                if (numMeshElem.ValueKind == JsonValueKind.Number)
                {
                    NumMesh = numMeshElem.GetUInt32();
                }
            }
            // NumMaterial
            JsonElement numMaterialElem;
            if (element.TryGetProperty("NumMaterial", out numMaterialElem))
            {
                if (numMaterialElem.ValueKind == JsonValueKind.Number)
                {
                    NumMaterial = numMaterialElem.GetUInt32();
                }
            }
            // Mesh
            JsonElement meshElem;
            if (element.TryGetProperty("Mesh", out meshElem))
            {
                if (meshElem.ValueKind == JsonValueKind.Array)
                {
                    for (int i=0; i<meshElem.GetArrayLength(); ++i)
                    {
                        var mesh = new MeshData();
                        mesh.ParseJsonElement(meshElem[i]);
                        Meshes.Add(mesh);
                    }
                }
            }
            // Material
            JsonElement materialElem;
            if (element.TryGetProperty("Material", out materialElem))
            {
                if (materialElem.ValueKind == JsonValueKind.Array)
                {
                    for (int i = 0; i < materialElem.GetArrayLength(); ++i)
                    {
                        var material = new MaterialData();
                        material.ParseJsonElement(materialElem[i]);
                        Materials.Add(material);
                    }
                }
            }

            return true;
        }
    }
}
