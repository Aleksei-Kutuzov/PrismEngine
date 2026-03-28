#include "meshManager.h"
#include "meshLoader.h"
#include "bufferWrapper.h"

void prism::PGC::L1::MeshManager::createImpl()
{
    meshLoader = new PGC::L2::MeshLoader(context, settings);
}

prism::Mesh prism::PGC::L1::MeshManager::addMesh(std::string texturePath)
{
    prism::PGC::MeshData mesh = meshLoader->load(texturePath);

  //if (vertices.empty() || indices.empty()) {
  //    return INVALID_MESH_ID;
  //}

    prism::Mesh meshIds;
    meshIds.reserve(mesh.infos.size());

    for (auto& info : mesh.infos)
    {
        info.vertexOffset += static_cast<uint32_t>(context->allVertices.size());
        info.indexOffset += static_cast<uint32_t>(context->allIndices.size());

        uint32_t id = getNextAvailableIndex();
        if (id >= context->mesh.size()) {
            context->mesh.push_back(info);
        }
        else {
            context->mesh[id] = info;
        }

        meshIds.push_back(id);
    }

    context->allVertices.insert(context->allVertices.end(), mesh.vertices.begin(), mesh.vertices.end());
    context->allIndices.insert(context->allIndices.end(), mesh.indices.begin(), mesh.indices.end());

    context->meshBuffersDirty = true;
    return meshIds;
}

void prism::PGC::L1::MeshManager::update()
{
    if (!context->meshBuffersDirty) return;

    // Освобождаем старые буферы если они существуют
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
    
    // Создаем новые буферы с актуальными данными
    if (!context->allVertices.empty()) {
        PGC::L3::BufferWrapper::createVertexBuffer(context);
    }
    if (!context->allIndices.empty()) {
        PGC::L3::BufferWrapper::createIndexBuffer(context);
    }

    context->meshBuffersDirty = false;
}

void prism::PGC::L1::MeshManager::clear()
{
    context->mesh.clear();
    context->allVertices.clear();
    context->allIndices.clear();
    context->freeMeshIndices.clear();

    context->meshBuffersDirty = true;
}

void prism::PGC::L1::MeshManager::cleanupImpl()
{
    clear();
    delete meshLoader;
}

prism::PGC::SubMesh& prism::PGC::L1::MeshManager::getSubMeshInfo(uint32_t id)
{
    static prism::PGC::SubMesh emptyInfo = { 0, 0, 0, 0 };

    if (id < context->mesh.size()) {
        return context->mesh[id];
    }

    return emptyInfo;
}

uint32_t prism::PGC::L1::MeshManager::getNextAvailableIndex()
{
    if (!context->freeMeshIndices.empty()) {
        uint32_t index = context->freeMeshIndices.back();
        context->freeMeshIndices.pop_back();
        return index;
    }

    return static_cast<uint32_t>(context->mesh.size());
}