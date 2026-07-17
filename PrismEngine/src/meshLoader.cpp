#include <unordered_map>
#include <iostream>
#include <tiny_obj_loader.h>
#include "meshLoader.h"
#include "logger.h"
#include "pathes.h"
#include "tangentCalculator.h"
#include "resourcesPath.h"

prism::PGC::MeshData prism::PGC::L2::MeshLoader::loadObj(assets::MeshPath assetSpec, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {
    assetSpec.path = prism::basePath / prism::modelsDir / assetSpec.path;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    const std::string pathStr = assetSpec.path.generic_string();
    const std::string baseDir = assetSpec.path.parent_path().string();

    bool ok = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, pathStr.c_str(), baseDir.c_str(), true);
    if (!ok) logger::error(err.empty() ? "Failed to parse OBJ" : err);
    if (!warn.empty()) logger::warning("[OBJ] Warning: " + warn);

    prism::PGC::MeshData meshData;
    meshData.assetSpec = assetSpec;

    meshData.indexCount = meshData.vertexCount = 0;
    meshData.indexOffset = indices.size();
    meshData.vertexOffset = vertices.size();

    glm::mat4 transformMat = calculateMatrix(assetSpec.transform);
    glm::mat3 normalMat = glm::mat3(glm::transpose(glm::inverse(transformMat)));

    std::unordered_map<Vertex, uint32_t, VertexHasher> uniqueVertices;

    for (const auto& shape : shapes) {
        if (shape.name != assetSpec.linkName && assetSpec.linkName != "[all]") continue;

        for (const auto& index : shape.mesh.indices) {
            Vertex vertex{};

            vertex.pos = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };

            if (index.texcoord_index >= 0) {
                vertex.texCoord = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
                };
            }
            else {
                vertex.texCoord = { 0.f, 0.f };
            }

            if (!attrib.colors.empty()) {
                vertex.color = { attrib.colors[3 * index.vertex_index + 0],
                                 attrib.colors[3 * index.vertex_index + 1],
                                 attrib.colors[3 * index.vertex_index + 2] };
            }
            else {
                vertex.color = { 1.f, 1.f, 1.f };
            }

            if (index.normal_index >= 0 && !attrib.normals.empty()) {
                vertex.normal = { attrib.normals[3 * index.normal_index + 0],
                                  attrib.normals[3 * index.normal_index + 1],
                                  attrib.normals[3 * index.normal_index + 2] };
            }
            else {
                vertex.normal = { 0.0f, 1.0f, 0.0f };
            }

            transformVertex(vertex, transformMat, normalMat);

            if (uniqueVertices.count(vertex) == 0) {
                uniqueVertices[vertex] = meshData.vertexCount;
                vertices.push_back(vertex);
                meshData.vertexCount++;
            }

            indices.push_back(uniqueVertices[vertex]);
            meshData.indexCount++;
        }
    }

    prism::PGC::L3::TangentCalculator::generateTangents(&vertices[meshData.vertexOffset], meshData.vertexCount, &indices[meshData.indexOffset], meshData.indexCount);

    return meshData;
}

prism::PGC::MeshData prism::PGC::L2::MeshLoader::loadCube(assets::MeshCube assetSpec, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
{
    constexpr std::array<Vertex, 24> cubeVertices = {
        Vertex{{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, { 0.0f,  0.0f,  1.0f}, { 1.0f,  0.0f,  0.0f, 1.0f}},
        Vertex{{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, { 0.0f,  0.0f,  1.0f}, { 1.0f,  0.0f,  0.0f, 1.0f}},
        Vertex{{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, { 0.0f,  0.0f,  1.0f}, { 1.0f,  0.0f,  0.0f, 1.0f}},
        Vertex{{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, { 0.0f,  0.0f,  1.0f}, { 1.0f,  0.0f,  0.0f, 1.0f}},

        Vertex{{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, { 0.0f,  0.0f, -1.0f}, {-1.0f,  0.0f,  0.0f, 1.0f}},
        Vertex{{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, { 0.0f,  0.0f, -1.0f}, {-1.0f,  0.0f,  0.0f, 1.0f}},
        Vertex{{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, { 0.0f,  0.0f, -1.0f}, {-1.0f,  0.0f,  0.0f, 1.0f}},
        Vertex{{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, { 0.0f,  0.0f, -1.0f}, {-1.0f,  0.0f,  0.0f, 1.0f}},

        Vertex{{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, { 1.0f,  0.0f,  0.0f}, { 0.0f,  0.0f, -1.0f, 1.0f}},
        Vertex{{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, { 1.0f,  0.0f,  0.0f}, { 0.0f,  0.0f, -1.0f, 1.0f}},
        Vertex{{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, { 1.0f,  0.0f,  0.0f}, { 0.0f,  0.0f, -1.0f, 1.0f}},
        Vertex{{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, { 1.0f,  0.0f,  0.0f}, { 0.0f,  0.0f, -1.0f, 1.0f}},

        Vertex{{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {-1.0f,  0.0f,  0.0f}, { 0.0f,  0.0f,  1.0f, 1.0f}},
        Vertex{{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {-1.0f,  0.0f,  0.0f}, { 0.0f,  0.0f,  1.0f, 1.0f}},
        Vertex{{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {-1.0f,  0.0f,  0.0f}, { 0.0f,  0.0f,  1.0f, 1.0f}},
        Vertex{{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {-1.0f,  0.0f,  0.0f}, { 0.0f,  0.0f,  1.0f, 1.0f}},

        Vertex{{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, { 0.0f,  1.0f,  0.0f}, { 1.0f,  0.0f,  0.0f, 1.0f}},
        Vertex{{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, { 0.0f,  1.0f,  0.0f}, { 1.0f,  0.0f,  0.0f, 1.0f}},
        Vertex{{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}, { 1.0f,  0.0f,  0.0f, 1.0f}},
        Vertex{{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}, { 1.0f,  0.0f,  0.0f, 1.0f}},

        Vertex{{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, { 0.0f, -1.0f,  0.0f}, { 1.0f,  0.0f,  0.0f, 1.0f}},
        Vertex{{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, { 0.0f, -1.0f,  0.0f}, { 1.0f,  0.0f,  0.0f, 1.0f}},
        Vertex{{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, { 0.0f, -1.0f,  0.0f}, { 1.0f,  0.0f,  0.0f, 1.0f}},
        Vertex{{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, { 0.0f, -1.0f,  0.0f}, { 1.0f,  0.0f,  0.0f, 1.0f}}
    };

    constexpr std::array<uint32_t, 36> cubeIndices = {
        0, 1, 2,  2, 3, 0,
        4, 5, 6,  6, 7, 4,
        8, 9, 10, 10, 11, 8,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        20, 21, 22, 22, 23, 20
    };

    prism::PGC::MeshData meshData;
    meshData.assetSpec = assetSpec;
    meshData.vertexOffset = vertices.size();
    meshData.indexOffset = indices.size();
    meshData.vertexCount = cubeVertices.size();
    meshData.indexCount = cubeIndices.size();

    vertices.insert(vertices.end(), cubeVertices.begin(), cubeVertices.end());
    indices.insert(indices.end(), cubeIndices.begin(), cubeIndices.end());

    glm::mat4 transformMat = calculateMatrix(assetSpec.transform);
    glm::mat3 normalMat = glm::mat3(glm::transpose(glm::inverse(transformMat)));

    for (size_t i = meshData.vertexOffset; i < static_cast<unsigned long long>(meshData.vertexOffset) + meshData.vertexCount; i++) {
        transformVertex(vertices[i], transformMat, normalMat);
    }

    prism::PGC::L3::TangentCalculator::generateTangents(&vertices[meshData.vertexOffset], meshData.vertexCount, &indices[meshData.indexOffset], meshData.indexCount);
    return meshData;
}

prism::PGC::MeshData prism::PGC::L2::MeshLoader::loadPlane(assets::MeshPlane assetSpec, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {
    constexpr std::array<Vertex, 4> planeVertices = {
        Vertex{{-0.5f,  0.0f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, { 0.0f,  1.0f,  0.0f}, { 1.0f,  0.0f,  0.0f, 1.0f}},
        Vertex{{ 0.5f,  0.0f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, { 0.0f,  1.0f,  0.0f}, { 1.0f,  0.0f,  0.0f, 1.0f}},
        Vertex{{ 0.5f,  0.0f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}, { 1.0f,  0.0f,  0.0f, 1.0f}},
        Vertex{{-0.5f,  0.0f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}, { 1.0f,  0.0f,  0.0f, 1.0f}}
    };

    constexpr std::array<uint32_t, 6> planeIndices = {
        0, 1, 2,  2, 3, 0
    };

    prism::PGC::MeshData meshData;
    meshData.assetSpec = assetSpec;
    meshData.vertexOffset = vertices.size();
    meshData.indexOffset = indices.size();
    meshData.vertexCount = planeVertices.size();
    meshData.indexCount = planeIndices.size();

    vertices.insert(vertices.end(), planeVertices.begin(), planeVertices.end());
    indices.insert(indices.end(), planeIndices.begin(), planeIndices.end());

    glm::mat4 transformMat = calculateMatrix(assetSpec.transform);
    glm::mat3 normalMat = glm::mat3(glm::transpose(glm::inverse(transformMat)));

    for (size_t i = meshData.vertexOffset; i < static_cast<unsigned long long>(meshData.vertexOffset) + meshData.vertexCount; i++) {
        transformVertex(vertices[i], transformMat, normalMat);
    }

    prism::PGC::L3::TangentCalculator::generateTangents(&vertices[meshData.vertexOffset], meshData.vertexCount, &indices[meshData.indexOffset], meshData.indexCount);
    return meshData;
}

prism::PGC::MeshData prism::PGC::L2::MeshLoader::loadGrid(assets::MeshGrid assetSpec, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
{
    prism::PGC::MeshData meshData;

    meshData.vertexCount = (assetSpec.subdivisionsX + 1) * (assetSpec.subdivisionsZ + 1);
    std::vector<Vertex> gridVertices;
    gridVertices.resize(meshData.vertexCount);
    for (size_t i = 0; i < meshData.vertexCount; i++)
    {
        size_t x = i % (assetSpec.subdivisionsX + 1);
        size_t z = i / (assetSpec.subdivisionsX + 1);

        float offsetX = (float)assetSpec.subdivisionsX / 2.0f;
        float offsetZ = (float)assetSpec.subdivisionsZ / 2.0f;

        gridVertices[i].pos.x = (float)x - offsetX;
        gridVertices[i].pos.y = 0;
        gridVertices[i].pos.z = (float)z - offsetZ;
        gridVertices[i].color = { 1.0f, 1.0f, 1.0f };
        gridVertices[i].texCoord.x = (float)x / assetSpec.repeatTextureX;
        gridVertices[i].texCoord.y = (float)z / assetSpec.repeatTextureZ;
        gridVertices[i].normal.x = 0.f;
        gridVertices[i].normal.y = 1.f;
        gridVertices[i].normal.z = 0.f;

    }

    meshData.indexCount = assetSpec.subdivisionsX * assetSpec.subdivisionsZ * 6;
    std::vector<uint32_t> gridIndices;
    gridIndices.resize(meshData.indexCount);

    size_t index_offset = 0;
    for (size_t z = 0; z < assetSpec.subdivisionsZ; z++)
    {
        for (size_t x = 0; x < assetSpec.subdivisionsX; x++)
        {
            uint32_t top_left = z * (assetSpec.subdivisionsX + 1) + x;
            uint32_t top_right = top_left + 1;
            uint32_t bottom_left = (z + 1) * (assetSpec.subdivisionsX + 1) + x;
            uint32_t bottom_right = bottom_left + 1;

            gridIndices[index_offset++] = top_left;
            gridIndices[index_offset++] = bottom_left;
            gridIndices[index_offset++] = top_right;

            gridIndices[index_offset++] = top_right;
            gridIndices[index_offset++] = bottom_left;
            gridIndices[index_offset++] = bottom_right;
        }
    }

    meshData.vertexOffset = vertices.size();
    meshData.indexOffset = indices.size();

    vertices.insert(vertices.end(), gridVertices.begin(), gridVertices.end());
    indices.insert(indices.end(), gridIndices.begin(), gridIndices.end());

    glm::mat4 transformMat = calculateMatrix(assetSpec.transform);
    glm::mat3 normalMat = glm::mat3(glm::transpose(glm::inverse(transformMat)));

    for (size_t i = meshData.vertexOffset; i < static_cast<unsigned long long>(meshData.vertexOffset) + meshData.vertexCount; i++) {
        transformVertex(vertices[i], transformMat, normalMat);
    }

    prism::PGC::L3::TangentCalculator::generateTangents(&vertices[meshData.vertexOffset], meshData.vertexCount, &indices[meshData.indexOffset], meshData.indexCount);
    return meshData;
}

prism::PGC::MeshData prism::PGC::L2::MeshLoader::loadIcoSphere(assets::MeshIcoSphere assetSpec, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
{
    prism::PGC::MeshData meshData;
    meshData.assetSpec = assetSpec;

    meshData.vertexOffset = vertices.size();
    meshData.indexOffset = indices.size();

    const float t = (1.0f + std::sqrt(5.0f)) / 2.0f;

    std::vector<glm::vec3> icoPositions = {
        glm::normalize(glm::vec3(-1.0f,  t,  0.0f)),
        glm::normalize(glm::vec3(1.0f,  t,  0.0f)),
        glm::normalize(glm::vec3(-1.0f, -t,  0.0f)),
        glm::normalize(glm::vec3(1.0f, -t,  0.0f)),
        glm::normalize(glm::vec3(0.0f, -1.0f,  t)),
        glm::normalize(glm::vec3(0.0f,  1.0f,  t)),
        glm::normalize(glm::vec3(0.0f, -1.0f, -t)),
        glm::normalize(glm::vec3(0.0f,  1.0f, -t)),
        glm::normalize(glm::vec3(t,  0.0f, -1.0f)),
        glm::normalize(glm::vec3(t,  0.0f,  1.0f)),
        glm::normalize(glm::vec3(-t,  0.0f, -1.0f)),
        glm::normalize(glm::vec3(-t,  0.0f,  1.0f))
    };

    std::vector<std::array<uint32_t, 3>> triangles = {
        {0, 11, 5}, {0, 5, 1}, {0, 1, 7}, {0, 7, 10}, {0, 10, 11},
        {1, 5, 9}, {5, 11, 4}, {11, 10, 2}, {10, 7, 6}, {7, 1, 8},
        {3, 9, 4}, {3, 4, 2}, {3, 2, 6}, {3, 6, 8}, {3, 8, 9},
        {4, 9, 5}, {2, 4, 11}, {6, 2, 10}, {8, 6, 7}, {9, 8, 1}
    };

    std::map<uint64_t, uint32_t> middlePointCache;

    auto getMiddlePoint = [&](uint32_t p1, uint32_t p2) -> uint32_t
        {
            uint64_t key = (std::min(p1, p2) * 100000ULL) + std::max(p1, p2);
            auto it = middlePointCache.find(key);
            if (it != middlePointCache.end()) {
                return it->second;
            }

            glm::vec3 mid = glm::normalize((icoPositions[p1] + icoPositions[p2]) * 0.5f);
            uint32_t newIndex = static_cast<uint32_t>(icoPositions.size());
            icoPositions.push_back(mid);
            middlePointCache[key] = newIndex;
            return newIndex;
        };

  
    for (uint16_t level = 0; level < assetSpec.subdivisions; level++)
    {
        std::vector<std::array<uint32_t, 3>> newTriangles;
        newTriangles.reserve(triangles.size() * 4);

        for (const auto& tri : triangles)
        {
            uint32_t a = tri[0], b = tri[1], c = tri[2];
            uint32_t ab = getMiddlePoint(a, b);
            uint32_t bc = getMiddlePoint(b, c);
            uint32_t ca = getMiddlePoint(c, a);

            newTriangles.push_back({ a, ab, ca });
            newTriangles.push_back({ b, bc, ab });
            newTriangles.push_back({ c, ca, bc });
            newTriangles.push_back({ ab, bc, ca });
        }
        triangles = std::move(newTriangles);
    }

    meshData.vertexCount = static_cast<uint32_t>(icoPositions.size());
    vertices.reserve(vertices.size() + meshData.vertexCount);

    for (const auto& pos : icoPositions)
    {
        Vertex v{};
        v.pos = pos;
        v.normal = pos;

        float u = 0.5f + std::atan2(pos.z, pos.x) / (2.0f * glm::pi<float>());
        float vCoord = 0.5f - std::asin(pos.y) / glm::pi<float>();
        v.texCoord = { u, vCoord };

        v.color = { 1.0f, 1.0f, 1.0f };
        vertices.push_back(v);
    }

    meshData.indexCount = static_cast<uint32_t>(triangles.size() * 3);
    indices.reserve(indices.size() + meshData.indexCount);

    for (const auto& tri : triangles)
    {
        indices.push_back(meshData.vertexOffset + tri[0]);
        indices.push_back(meshData.vertexOffset + tri[1]);
        indices.push_back(meshData.vertexOffset + tri[2]);
    }

    glm::mat4 transformMat = calculateMatrix(assetSpec.transform);
    glm::mat3 normalMat = glm::mat3(glm::transpose(glm::inverse(transformMat)));

    for (size_t i = meshData.vertexOffset; i < meshData.vertexOffset + meshData.vertexCount; i++) transformVertex(vertices[i], transformMat, normalMat);
    

    prism::PGC::L3::TangentCalculator::generateTangents(&vertices[meshData.vertexOffset], meshData.vertexCount, &indices[meshData.indexOffset], meshData.indexCount);

    return meshData;
}

prism::PGC::MeshData prism::PGC::L2::MeshLoader::loadUvSphere(assets::MeshUvSphere assetSpec, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
{
    prism::PGC::MeshData meshData;
    meshData.assetSpec = assetSpec;

    const uint32_t stacks = assetSpec.subdivisionsHoriz;
    const uint32_t slices = assetSpec.subdivisionsVert;

    meshData.vertexCount = (stacks + 1) * (slices + 1);
    meshData.indexCount = stacks * slices * 6;

    meshData.vertexOffset = vertices.size();
    meshData.indexOffset = indices.size();

    vertices.reserve(vertices.size() + meshData.vertexCount);
    indices.reserve(indices.size() + meshData.indexCount);

    const float pi = glm::pi<float>();
    const float twoPi = 2.0f * pi;

    for (uint32_t i = 0; i <= stacks; i++)
    {
        float phi = pi * static_cast<float>(i) / static_cast<float>(stacks);
        float sinPhi = std::sin(phi);
        float cosPhi = std::cos(phi);

        for (uint32_t j = 0; j <= slices; j++)
        {
            float theta = twoPi * static_cast<float>(j) / static_cast<float>(slices);
            float sinTheta = std::sin(theta);
            float cosTheta = std::cos(theta);

            Vertex v{};
            v.pos.x = sinPhi * cosTheta;
            v.pos.y = cosPhi;
            v.pos.z = sinPhi * sinTheta;

            v.normal = v.pos;

            v.texCoord.x = static_cast<float>(j) / static_cast<float>(slices);
            v.texCoord.y = static_cast<float>(i) / static_cast<float>(stacks);

            v.color = { 1.0f, 1.0f, 1.0f };

            vertices.push_back(v);
        }
    }


    for (uint32_t i = 0; i < stacks; i++)
    {
        for (uint32_t j = 0; j < slices; j++)
        {
            uint32_t first = meshData.vertexOffset + i * (slices + 1) + j;
            uint32_t second = first + slices + 1;

            if (i != 0)
            {
                indices.push_back(first);
                indices.push_back(first + 1);
                indices.push_back(second);
            }
            if (i != stacks - 1)
            {
                indices.push_back(first + 1);
                indices.push_back(second + 1);
                indices.push_back(second);
            }
        }
    }

    meshData.indexCount = static_cast<uint32_t>(indices.size() - meshData.indexOffset);

    glm::mat4 transformMat = calculateMatrix(assetSpec.transform);
    glm::mat3 normalMat = glm::mat3(glm::transpose(glm::inverse(transformMat)));

    for (size_t i = meshData.vertexOffset; i < meshData.vertexOffset + meshData.vertexCount; i++) transformVertex(vertices[i], transformMat, normalMat);


    prism::PGC::L3::TangentCalculator::generateTangents(&vertices[meshData.vertexOffset], meshData.vertexCount, &indices[meshData.indexOffset], meshData.indexCount);

    return meshData;
}

void prism::PGC::L2::MeshLoader::transformVertex(prism::PGC::Vertex& vertex, const glm::mat4& transformMat, const glm::mat3& normalMat)
{
    glm::vec4 posHomogeneous = transformMat * glm::vec4(vertex.pos, 1.0f);
    vertex.pos = glm::vec3(posHomogeneous) / posHomogeneous.w;
    vertex.normal = glm::normalize(normalMat * vertex.normal);
}

glm::mat4 prism::PGC::L2::MeshLoader::calculateMatrix(prism::PGC::MeshTransform transform)
{
    glm::mat4 transformMat = glm::mat4(1.0f);
    transformMat = glm::translate(transformMat, transform.position);
    transformMat = transformMat * glm::mat4_cast(transform.rotation);
    transformMat = glm::scale(transformMat, transform.scale);
    return transformMat;
}