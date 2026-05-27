#include "meshStorage.h"
#include "meshLoader.h"
#include "mesh.h"
#include "bufferWrapper.h"
#include <sstream>

using BaseStorage = prism::PGC::L1::Storage<prism::scene::MeshComponent::DataType, prism::PGC::MeshData, prism::PGC::L2::MeshLoader, prism::PGC::L1::MeshStorage>;

void prism::PGC::L1::MeshStorage::createImpl()
{
    BaseStorage::createImpl();
}

prism::scene::MeshComponent::DataType prism::PGC::L1::MeshStorage::loadImpl(MeshData meshData)
{
    meshData.info.vertexOffset += static_cast<uint32_t>(allVertices.size());
    meshData.info.indexOffset += static_cast<uint32_t>(allIndices.size());

    allVertices.insert(allVertices.end(), meshData.vertices.begin(), meshData.vertices.end());
    allIndices.insert(allIndices.end(), meshData.indices.begin(), meshData.indices.end());

    pathToId.emplace(getPathForId(meshData.path, meshData.name, meshData.transform), meshData.info);

    uint32_t index = getNextAvailableIndex();
    meshData.info.id = index;

    if (index >= data.size()) {
        data.push_back(meshData);
    }
    else {
        data[index] = meshData;
    }

    return meshData.info;
}

void clenupBuffers(prism::PGC::utils::Context* context) {
    if (context->vertexBuffer != VK_NULL_HANDLE) {
        vkDestroyBuffer(context->device, context->vertexBuffer, nullptr);
        context->vertexBuffer = VK_NULL_HANDLE;
    }

    if (context->vertexBufferMemory != VK_NULL_HANDLE) {
        vkFreeMemory(context->device, context->vertexBufferMemory, nullptr);
        context->vertexBufferMemory = VK_NULL_HANDLE;
    }

    if (context->indexBuffer != VK_NULL_HANDLE) {
        vkDestroyBuffer(context->device, context->indexBuffer, nullptr);
        context->indexBuffer = VK_NULL_HANDLE;
    }
    if (context->indexBufferMemory != VK_NULL_HANDLE) {
        vkFreeMemory(context->device, context->indexBufferMemory, nullptr);
        context->indexBufferMemory = VK_NULL_HANDLE;
    }
}

void prism::PGC::L1::MeshStorage::updateImpl()
{
    clenupBuffers(this->context);

    if (!allVertices.empty()) {
        PGC::L3::BufferWrapper::createVertexBuffer(context, allVertices);
    }
    if (!allIndices.empty()) {
        PGC::L3::BufferWrapper::createIndexBuffer(context, allIndices);
    }
}

uint32_t prism::PGC::L1::MeshStorage::getId(prism::scene::MeshComponent::DataType dataId)
{
    return dataId.id;
}

void prism::PGC::L1::MeshStorage::clearImpl()
{
    clenupBuffers(this->context);

    allVertices.clear();
    allIndices.clear();
}

std::filesystem::path prism::PGC::L1::MeshStorage::getPathForId(std::filesystem::path path, std::string meshName, prism::PGC::MeshData::Transform transform)
{
    std::ostringstream oss;
    oss << path.string() << "@" << meshName << "@"
        << transform.position.x << "," << transform.position.y << "," << transform.position.z << "@"
        << transform.rotation.x << "," << transform.rotation.y << "," << transform.rotation.z << "," << transform.rotation.w << "@"
        << transform.scale.x << "," << transform.scale.y << "," << transform.scale.z;
    return std::filesystem::path(oss.str());
}
