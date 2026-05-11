#pragma once
#include "scene.h"
#include "meshComponent.h"
#include "materialComponent.h"
#include "textureStorage.h"
#include <string>
#include <optional>

namespace prism {
	namespace render {
		struct MaterialBuilder {
			struct MaterialData {
				std::optional<std::filesystem::path> albedo;
				std::optional<std::filesystem::path> normal;
				std::optional<std::filesystem::path> metallic;
				std::optional<std::filesystem::path> roughness;
				std::optional<std::filesystem::path> ambient;
				std::optional<std::filesystem::path> emission;

				float metalicScalar = 0.0f;
				float roughnessScalar = 0.5f;
				float emissionScalar = 0.0f;
			};

			std::vector<MaterialData> materialsData;
			float globalMetalicScalar = 1.0f;
			float globalRoughnessScalar = 1.0f;
			float globalEmissionScalar = 1.0f;

			prism::scene::Scene& scene;
			prism::PGC::L1::TextureStorage& storage;

			MaterialBuilder(prism::scene::Scene& scene, prism::PGC::L1::TextureStorage& storage) : scene(scene), storage(storage) {};
			
			MaterialBuilder& size(uint16_t size);
			MaterialBuilder& forMesh(prism::scene::MeshComponent mesh);

			MaterialBuilder& copyAll(prism::scene::MaterialComponent material);
			MaterialBuilder& copy(prism::scene::MaterialComponent material, uint16_t subMaterialId);

			MaterialBuilder& albedo(uint16_t subMaterialId, std::filesystem::path filename);
			
			MaterialBuilder& normal(uint16_t subMaterialId, std::filesystem::path filename);
			
			MaterialBuilder& mrao(uint16_t subMaterialId, std::filesystem::path filename);
			
			MaterialBuilder& metalic(uint16_t subMaterialId, std::filesystem::path filename);
			MaterialBuilder& metalic(uint16_t subMaterialId, float metalic);
			MaterialBuilder& metalic(float metalic);

			MaterialBuilder& roughness(uint16_t subMaterialId, std::filesystem::path filename);
			MaterialBuilder& roughness(uint16_t subMaterialId, float roughness);
			MaterialBuilder& roughness(float roughness);

			MaterialBuilder& ambientOcclusion(uint16_t subMaterialId, std::filesystem::path filename);

			MaterialBuilder& emission(uint16_t subMaterialId, std::filesystem::path filename);
			MaterialBuilder& emission(uint16_t subMaterialId, float emission);
			MaterialBuilder& emission(float emission);
			
			prism::scene::MaterialComponent complete();
		};
	}
}