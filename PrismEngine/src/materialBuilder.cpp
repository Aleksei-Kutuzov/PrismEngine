#include "materialBuilder.h"
#include "linker.h"
#include "textureStorage.h"
#include "renderer.h"
#include "resourcesPath.h"

prism::render::MaterialBuilder::MaterialBuilder(prism::scene::Scene& scene, prism::PGC::L1::TextureStorage& storage) : scene(scene), storage(storage) { }

prism::render::MaterialBuilder& prism::render::MaterialBuilder::size(uint16_t size)
{
    materialsData.resize(size);
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::forMesh(prism::scene::MeshComponent& mesh)
{
    uint16_t matSize = 0;
    scene.getDataFromPool<prism::scene::MeshComponent>(mesh, matSize);
    return size(matSize);
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::forMesh(prism::scene::Entity entity)
{
    return forMesh(*scene.getComponent<prism::scene::MeshComponent>(entity));
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::copyAll(prism::scene::MaterialComponent material)
{
    uint16_t matSize = 0;
    auto* renderer = prism::linker.find<prism::scene::Scene, prism::render::Renderer>(&scene);
    prism::scene::MaterialComponent::DataType* mats = const_cast<prism::scene::MaterialComponent::DataType*>(scene.getDataFromPool<prism::scene::MaterialComponent>(material, matSize));
    for (size_t i = 0; i < matSize; i++)
    {
        materialsData[i].albedo = storage.getData(mats[i].albedo).assetSpec;
        materialsData[i].normal = storage.getData(mats[i].normal).assetSpec;
        materialsData[i].metallic = storage.getData(mats[i].metallic).assetSpec;
        materialsData[i].roughness = storage.getData(mats[i].roughness).assetSpec;
        materialsData[i].ambient = storage.getData(mats[i].ambient).assetSpec;
        materialsData[i].emission = storage.getData(mats[i].emission).assetSpec;

        materialsData[i].metallicScalar = mats[i].metallicScalar;
        materialsData[i].roughnessScalar = mats[i].roughnessScalar;
        materialsData[i].emissionScalar = mats[i].emissionScalar;
    }
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::copy(prism::scene::MaterialComponent material, uint16_t subMaterialId)
{
    uint16_t matSize = 0;
    prism::scene::MaterialComponent::DataType* otherMats = const_cast<prism::scene::MaterialComponent::DataType*>(scene.getDataFromPool<prism::scene::MaterialComponent>(material, matSize));

    materialsData[subMaterialId].albedo = storage.getData(otherMats[subMaterialId].albedo).assetSpec;
    materialsData[subMaterialId].normal = storage.getData(otherMats[subMaterialId].normal).assetSpec;
    materialsData[subMaterialId].metallic = storage.getData(otherMats[subMaterialId].metallic).assetSpec;
    materialsData[subMaterialId].roughness = storage.getData(otherMats[subMaterialId].roughness).assetSpec;
    materialsData[subMaterialId].ambient = storage.getData(otherMats[subMaterialId].ambient).assetSpec;
    materialsData[subMaterialId].emission = storage.getData(otherMats[subMaterialId].emission).assetSpec;

    materialsData[subMaterialId].metallicScalar = otherMats[subMaterialId].metallicScalar;
    materialsData[subMaterialId].roughnessScalar = otherMats[subMaterialId].roughnessScalar;
    materialsData[subMaterialId].emissionScalar = otherMats[subMaterialId].emissionScalar;

    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::albedo(uint16_t subMaterialId, std::filesystem::path filename)
{
    materialsData[subMaterialId].albedo = assets::TexturePath{ filename, PGC::TextureType::ALBEDO };
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::albedo(uint16_t subMaterialId, std::array<unsigned char, 4> rgba)
{
    materialsData[subMaterialId].albedo = assets::TextureColor{ rgba, PGC::TextureType::ALBEDO };
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::normal(uint16_t subMaterialId, std::filesystem::path filename)
{
    materialsData[subMaterialId].normal = assets::TexturePath{ filename, PGC::TextureType::NORMAL };
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::normal(uint16_t subMaterialId, std::array<unsigned char, 4> rgba)
{
    materialsData[subMaterialId].normal = assets::TextureColor{ rgba, PGC::TextureType::NORMAL };
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::mrao(uint16_t subMaterialId, std::filesystem::path filename)
{
    materialsData[subMaterialId].metallic = assets::TexturePath{ filename, PGC::TextureType::MRAOH };
    materialsData[subMaterialId].roughness = assets::TexturePath{ filename, PGC::TextureType::MRAOH };
    materialsData[subMaterialId].ambient = assets::TexturePath{ filename, PGC::TextureType::MRAOH };
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::mrao(uint16_t subMaterialId, std::array<unsigned char, 4> rgba)
{
    materialsData[subMaterialId].metallic = assets::TextureColor{ rgba, PGC::TextureType::MRAOH };
    materialsData[subMaterialId].roughness = assets::TextureColor{ rgba, PGC::TextureType::MRAOH };
    materialsData[subMaterialId].ambient = assets::TextureColor{ rgba, PGC::TextureType::MRAOH };
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::mraoh(uint16_t subMaterialId, std::filesystem::path filename)
{
    return mrao(subMaterialId, filename).
           height(subMaterialId, filename);
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::mraoh(uint16_t subMaterialId, std::array<unsigned char, 4> rgba)
{
    return mraoh(subMaterialId, rgba);
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::metallic(uint16_t subMaterialId, std::filesystem::path filename)
{
    materialsData[subMaterialId].metallic = assets::TexturePath{ filename, PGC::TextureType::MRAOH };
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::metallic(uint16_t subMaterialId, float metallic)
{
    materialsData[subMaterialId].metallicScalar = metallic;
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::metallic(float metallic)
{
    globalMetallicScalar = metallic;
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::roughness(uint16_t subMaterialId, std::filesystem::path filename)
{
    materialsData[subMaterialId].roughness = assets::TexturePath{ filename, PGC::TextureType::MRAOH };;
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
    materialsData[subMaterialId].ambient = assets::TexturePath{ filename, PGC::TextureType::MRAOH };;
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::ambientOcclusion(uint16_t subMaterialId, float ambient)
{
    materialsData[subMaterialId].ambientScalar = ambient;
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::ambientOcclusion(float ambient)
{
    globalAmbientScalar = ambient;
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::emission(uint16_t subMaterialId, std::filesystem::path filename)
{
    materialsData[subMaterialId].emission = assets::TexturePath{ filename, PGC::TextureType::EMISSION };;
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::emission(uint16_t subMaterialId, std::array<unsigned char, 4> rgba)
{
    materialsData[subMaterialId].emission = assets::TextureColor{ rgba, PGC::TextureType::EMISSION };;
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

prism::render::MaterialBuilder& prism::render::MaterialBuilder::height(uint16_t subMaterialId, std::filesystem::path filename)
{
    materialsData[subMaterialId].height = assets::TexturePath{ filename, PGC::TextureType::MRAOH };;
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::height(uint16_t subMaterialId, float height)
{
    materialsData[subMaterialId].heightScalar = height;
    return *this;
}

prism::render::MaterialBuilder& prism::render::MaterialBuilder::height(float height)
{
    globalHeightScalar = height;
    return *this;
}

prism::scene::MaterialComponent prism::render::MaterialBuilder::complete()
{
    prism::scene::MaterialComponent material;
    uint16_t itemsSize = materialsData.size();
    std::vector<prism::scene::MaterialComponent::DataType> items;
    items.resize(itemsSize);
    for (uint16_t i = 0; i < itemsSize; ++i) {

        items[i].albedo = storage.load(materialsData[i].albedo.has_value() ? materialsData[i].albedo.value() :          assets::TextureColor{ {255, 255, 255, 255}, prism::PGC::TextureType::ALBEDO });
        items[i].normal = storage.load(materialsData[i].normal.has_value() ? materialsData[i].normal.value() :          assets::TextureColor{ {128, 128, 255, 255}, prism::PGC::TextureType::NORMAL });
        items[i].metallic = storage.load(materialsData[i].metallic.has_value() ? materialsData[i].metallic.value() :    assets::TextureColor{ {0, 0, 0, 128}, prism::PGC::TextureType::MRAOH });
        items[i].roughness = storage.load(materialsData[i].roughness.has_value() ? materialsData[i].roughness.value() : assets::TextureColor{ {0, 0, 0, 128}, prism::PGC::TextureType::MRAOH });
        items[i].ambient = storage.load(materialsData[i].ambient.has_value() ? materialsData[i].ambient.value() :       assets::TextureColor{ {0, 0, 0, 128}, prism::PGC::TextureType::MRAOH });
        items[i].height = storage.load(materialsData[i].height.has_value() ? materialsData[i].height.value() :          assets::TextureColor{ {0, 0, 0, 128}, prism::PGC::TextureType::MRAOH });
        items[i].emission = storage.load(materialsData[i].emission.has_value() ? materialsData[i].emission.value() :    assets::TextureColor{ {0, 0, 0, 225}, prism::PGC::TextureType::EMISSION });

        items[i].metallicScalar = std::clamp(materialsData[i].metallicScalar, 0.0f, 1.0f) * std::clamp(globalMetallicScalar, 0.0f, 1.0f);
        items[i].roughnessScalar = std::clamp(materialsData[i].roughnessScalar, 0.0f, 1.0f) * std::clamp(globalRoughnessScalar, 0.0f, 1.0f);
        items[i].ambientScalar = std::clamp(materialsData[i].ambientScalar, 0.0f, 1.0f) * std::clamp(globalAmbientScalar, 0.0f, 1.0f);
        items[i].emissionScalar = std::clamp(materialsData[i].emissionScalar, 0.0f, 1.0f) * std::clamp(globalEmissionScalar, 0.0f, 1.0f);
        items[i].heightScalar = std::clamp(materialsData[i].heightScalar, 0.0f, 1.0f) * std::clamp(globalHeightScalar, 0.0f, 1.0f);
    }

    storage.update();

    return scene.addDataToPool<prism::scene::MaterialComponent>(items.data(), itemsSize);
}

