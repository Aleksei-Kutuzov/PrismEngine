#include "meshStorage.h"
#include "meshLoader.h"
#include "bufferWrapper.h"
#include "logger.h"


void prism::PGC::L1::MeshStorage::createImpl()
{
    loader = new prism::PGC::L2::MeshLoader(context, settings);
}

prism::scene::MeshComponent::DataType prism::PGC::L1::MeshStorage::load(prism::assets::AssetSpec assetSpec)
{
    for (size_t i = 0; i < data.size(); i++)
    {
        if (data[i].assetSpec == assetSpec) return i + 1;
    }

    MeshData mesh = std::visit(prism::assets::overloaded{
        [this](assets::MeshPath i) { return loader->loadObj(i, allVertices, allIndices); },
        [this](assets::MeshCube f) { return loader->loadCube(f, allVertices, allIndices); },
        [this](assets::MeshPlane p){ return loader->loadPlane(p, allVertices, allIndices); },
        [this](assets::MeshGrid g) { return loader->loadGrid(g, allVertices, allIndices); },
        [this](assets::MeshIcoSphere p) { return loader->loadIcoSphere(p, allVertices, allIndices); },
        [this](assets::MeshUvSphere u) { return loader->loadUvSphere(u, allVertices, allIndices); },
        [](auto& bad) -> MeshData {throw std::runtime_error("Unexpected mesh asset type"); }
        }, assetSpec);

    auto id = pool.newId();

    if (id > data.size()) data.push_back(std::move(mesh));
    else data[id - 1] = std::move(mesh);

    isActual = false;
    return id;
}

prism::PGC::MeshData& prism::PGC::L1::MeshStorage::getData(prism::scene::MeshComponent::DataType id)
{
    if (id != 0) {
        id--;
        try {
            return data.at(id);
        }
        catch (const std::out_of_range& e) {
            logger::logError(logger::Error::RUNTIME_ERROR, std::string(e.what()));
        }
    }
    throw std::runtime_error("Invalid mesh ID");
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

void prism::PGC::L1::MeshStorage::update()
{
    clenupBuffers(this->context);

    if (!allVertices.empty()) {
        PGC::L3::BufferWrapper::createVertexBuffer(context, allVertices);
    }
    if (!allIndices.empty()) {
        PGC::L3::BufferWrapper::createIndexBuffer(context, allIndices);
    }
}

void prism::PGC::L1::MeshStorage::clear()
{
    clenupBuffers(this->context);

    allVertices.clear();
    allIndices.clear();
}

void prism::PGC::L1::MeshStorage::cleanupImpl() {
    this->clear();

    if (this->loader) {
        delete this->loader;
        this->loader = nullptr;
    }
};