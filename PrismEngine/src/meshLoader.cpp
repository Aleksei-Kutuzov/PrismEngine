#include <unordered_map>
#include <iostream>
#include <tiny_obj_loader.h>
#include "meshLoader.h"
#include "logger.h"
#include "pathes.h"

prism::PGC::MeshData prism::PGC::L2::MeshLoader::load(std::filesystem::path path, std::string meshName, prism::PGC::MeshData::Transform transform)
{
    prism::PGC::MeshData meshData;

    const std::filesystem::path fullPath = prism::basePath / prism::modelsDir / path;
    meshData.path = fullPath;
    meshData.name = meshName;
    meshData.transform = transform;

    std::filesystem::path ext = path.extension();

    if (ext == ".obj") {
        loadObj(meshData);
    }
    // TODO: Добавить поддержку glTF
    // else if (ext == ".gltf" || ext == ".glb") {
    //     return loadGltf(fullPath, meshName, transform);
    // }
    else {
        logger::error("Unsupported mesh format: " + ext.string());
    }

    return meshData;
}

void prism::PGC::L2::MeshLoader::loadObj(prism::PGC::MeshData& meshData)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    const std::string pathStr = meshData.path.generic_string();
    const std::string baseDir = meshData.path.parent_path().string();

    bool ok = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, pathStr.c_str(), baseDir.c_str(), true);
    if (!ok) logger::error(err.empty() ? "Failed to parse OBJ" : err);
    if (!warn.empty()) logger::warning("[OBJ] Warning: " + warn);

    meshData.info.indexCount = meshData.info.vertexCount = 0;
    meshData.info.indexOffset = meshData.info.vertexOffset = 0;

    glm::mat4 transformMat = calculateMatrix(meshData.transform);
    glm::mat3 normalMat = glm::mat3(glm::transpose(glm::inverse(transformMat)));

    for (const auto& shape : shapes) {
        if (shape.name != meshData.name && meshData.name != "[all]") continue;

        std::unordered_map<Vertex, uint32_t, VertexHasher> uniqueVertices;

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
                uniqueVertices[vertex] = static_cast<uint32_t>(meshData.vertices.size());
                meshData.vertices.push_back(vertex);
                meshData.info.vertexCount++;
            }

            meshData.indices.push_back(uniqueVertices[vertex]);
            meshData.info.indexCount++;
        }
    }
}

void prism::PGC::L2::MeshLoader::transformVertex(prism::PGC::Vertex& vertex, const glm::mat4& transformMat, const glm::mat3& normalMat)
{
    glm::vec4 posHomogeneous = transformMat * glm::vec4(vertex.pos, 1.0f);
    vertex.pos = glm::vec3(posHomogeneous) / posHomogeneous.w;
    vertex.normal = glm::normalize(normalMat * vertex.normal);
}

glm::mat4 prism::PGC::L2::MeshLoader::calculateMatrix(prism::PGC::MeshData::Transform transform)
{
    glm::mat4 transformMat = glm::mat4(1.0f);
    transformMat = glm::translate(transformMat, transform.position);
    transformMat = transformMat * glm::mat4_cast(transform.rotation);
    transformMat = glm::scale(transformMat, transform.scale);
    return transformMat;
}
