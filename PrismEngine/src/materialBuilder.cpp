#include "materialBuilder.h"
#include "linker.h"
#include "textureStorage.h"
#include "renderer.h"

prism::render::MaterialBuilder& prism::render::MaterialBuilder::size(uint16_t size)
{
    materialsData.resize(size);
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::forMesh(prism::scene::MeshComponent mesh)
{
    uint16_t matSize = 0;
    scene.getDataFromPool<prism::scene::MeshComponent>(mesh, matSize);
    return size(matSize);
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::copyAll(prism::scene::MaterialComponent material)
{
    uint16_t matSize = 0;
    auto* renderer = prism::linker.find<prism::scene::Scene, prism::render::Renderer>(&scene);
    prism::scene::MaterialComponent::DataType* mats = const_cast<prism::scene::MaterialComponent::DataType*>(scene.getDataFromPool<prism::scene::MaterialComponent>(material, matSize));
    for (size_t i = 0; i < matSize; i++)
    {
        materialsData[i].albedo = storage.get(mats[i].albedo).path;
        materialsData[i].normal = storage.get(mats[i].normal).path;
        materialsData[i].metallic = storage.get(mats[i].metallic).path;
        materialsData[i].roughness = storage.get(mats[i].roughness).path;
        materialsData[i].ambient = storage.get(mats[i].ambient).path;
        materialsData[i].emission = storage.get(mats[i].emission).path;

        materialsData[i].metalicScalar = mats[i].metalicScalar;
        materialsData[i].roughnessScalar = mats[i].roughnessScalar;
        materialsData[i].emissionScalar = mats[i].emissionScalar;
    }
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::copy(prism::scene::MaterialComponent material, uint16_t subMaterialId)
{
    uint16_t matSize = 0;
    auto* renderer = prism::linker.find<prism::scene::Scene, prism::render::Renderer>(&scene);
    prism::scene::MaterialComponent::DataType* mats = const_cast<prism::scene::MaterialComponent::DataType*>(scene.getDataFromPool<prism::scene::MaterialComponent>(material, matSize));

    materialsData[subMaterialId].albedo = storage.get(mats[subMaterialId].albedo).path;
    materialsData[subMaterialId].normal = storage.get(mats[subMaterialId].normal).path;
    materialsData[subMaterialId].metallic = storage.get(mats[subMaterialId].metallic).path;
    materialsData[subMaterialId].roughness = storage.get(mats[subMaterialId].roughness).path;
    materialsData[subMaterialId].ambient = storage.get(mats[subMaterialId].ambient).path;
    materialsData[subMaterialId].emission = storage.get(mats[subMaterialId].emission).path;

    materialsData[subMaterialId].metalicScalar = mats[subMaterialId].metalicScalar;
    materialsData[subMaterialId].roughnessScalar = mats[subMaterialId].roughnessScalar;
    materialsData[subMaterialId].emissionScalar = mats[subMaterialId].emissionScalar;

    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::albedo(uint16_t subMaterialId, std::filesystem::path filename)
{
    materialsData[subMaterialId].albedo = filename;
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::normal(uint16_t subMaterialId, std::filesystem::path filename)
{
    materialsData[subMaterialId].normal = filename;
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::mrao(uint16_t subMaterialId, std::filesystem::path filename)
{
    materialsData[subMaterialId].metallic = filename;
    materialsData[subMaterialId].roughness = filename;
    materialsData[subMaterialId].ambient = filename;
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::metalic(uint16_t subMaterialId, std::filesystem::path filename)
{
    materialsData[subMaterialId].metallic = filename;
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::metalic(uint16_t subMaterialId, float metalic)
{
    materialsData[subMaterialId].metalicScalar = metalic;
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::metalic(float metalic)
{
    globalMetalicScalar = metalic;
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::roughness(uint16_t subMaterialId, std::filesystem::path filename)
{
    materialsData[subMaterialId].roughness = filename;
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::roughness(uint16_t subMaterialId, float roughness)
{
    materialsData[subMaterialId].roughnessScalar = roughness;
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::roughness(float roughness)
{
    globalRoughnessScalar = roughness;
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::ambientOcclusion(uint16_t subMaterialId, std::filesystem::path filename)
{
    materialsData[subMaterialId].ambient = filename;
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::emission(uint16_t subMaterialId, std::filesystem::path filename)
{
    materialsData[subMaterialId].emission = filename;
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::emission(uint16_t subMaterialId, float emission)
{
    materialsData[subMaterialId].emissionScalar = emission;
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::emission(float emission)
{
    globalEmissionScalar = emission;
    return *this;
}

prism::scene::MaterialComponent prism::render::MaterialBuilder::complete()
{
    prism::scene::MaterialComponent material;
    uint16_t itemsSize = materialsData.size();
    std::vector<prism::scene::MaterialComponent::DataType> items;
    items.resize(itemsSize);
    for (uint16_t i = 0; i < itemsSize; ++i) {

        items[i].albedo = materialsData[i].albedo.has_value() ? storage.load(materialsData[i].albedo.value(), prism::PGC::TextureType::ALBEDO) : INVALID_TEXTURE_ID;
        items[i].normal = materialsData[i].normal.has_value() ? storage.load(materialsData[i].normal.value(), prism::PGC::TextureType::NORMAL) : INVALID_TEXTURE_ID;
        items[i].metallic = materialsData[i].metallic.has_value() ? storage.load(materialsData[i].metallic.value(), prism::PGC::TextureType::MRAO) : INVALID_TEXTURE_ID;
        items[i].roughness = materialsData[i].roughness.has_value() ? storage.load(materialsData[i].roughness.value(), prism::PGC::TextureType::MRAO) : INVALID_TEXTURE_ID;
        items[i].ambient = materialsData[i].ambient.has_value() ? storage.load(materialsData[i].ambient.value(), prism::PGC::TextureType::MRAO) : INVALID_TEXTURE_ID;
        items[i].emission = materialsData[i].emission.has_value() ? storage.load(materialsData[i].emission.value(), prism::PGC::TextureType::EMISSION) : INVALID_TEXTURE_ID;

        items[i].metalicScalar = materialsData[i].metalicScalar * globalMetalicScalar;
        items[i].roughnessScalar = materialsData[i].roughnessScalar * globalRoughnessScalar;
        items[i].emissionScalar = materialsData[i].emissionScalar * globalEmissionScalar;
    }

    storage.update();

    return scene.addDataToPool<prism::scene::MaterialComponent>(items.data(), itemsSize);
}

