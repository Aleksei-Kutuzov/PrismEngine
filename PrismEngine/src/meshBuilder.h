#pragma once
#include "scene.h"
#define GLM_FORCE_RADIANS
#include "meshStorage.h"
#include <vec3.hpp>
#include <gtc/quaternion.hpp> 
#include <gtx/quaternion.hpp>

namespace prism {
	namespace render {
		struct MeshBuilder {
		public:
			prism::scene::Scene& scene;
			prism::PGC::L1::MeshStorage& storage;

			std::vector<assets::AssetSpec> meshParams;

			MeshBuilder(prism::scene::Scene& scene, prism::PGC::L1::MeshStorage& storage) : scene(scene), storage(storage) {}

			MeshBuilder& size(uint16_t size);

			MeshBuilder& copyAll(prism::scene::MeshComponent mesh);
			MeshBuilder& copy(uint16_t subMeshId, prism::scene::MeshComponent mesh);

			MeshBuilder& model(uint16_t subMeshId, std::filesystem::path filepath);
			MeshBuilder& model(uint16_t subMeshId, std::filesystem::path filepath, std::string sourceMeshName);
			
			MeshBuilder& cube(uint16_t subMeshId);
			MeshBuilder& plane(uint16_t subMeshId);
			MeshBuilder& grid(uint16_t subMeshId, uint16_t subdivsX, uint16_t subdivsZ, uint16_t repeatX, uint16_t repeatZ);
			MeshBuilder& icoSphere(uint16_t subMeshId, uint8_t subdivisiones);
			MeshBuilder& uvSphere(uint16_t subMeshId, uint16_t subdivsVert, uint16_t subdivsHoriz);
			
			MeshBuilder& position(uint16_t subMeshId, glm::vec3 position);
			MeshBuilder& rotation(uint16_t subMeshId, glm::vec3 rotation);
			MeshBuilder& rotation(uint16_t subMeshId, glm::quat rotation);
			MeshBuilder& scale(uint16_t subMeshId, glm::vec3 scale);
			
			MeshBuilder& positionBy(uint16_t subMeshId, glm::vec3 positionBy);
			MeshBuilder& rotationBy(uint16_t subMeshId, glm::vec3 rotationBy);
			MeshBuilder& rotationBy(uint16_t subMeshId, glm::quat rotationBy);
			MeshBuilder& scaleBy(uint16_t subMeshId, glm::vec3 scaleBy);
			
			prism::scene::MeshComponent complete();

		private:
			prism::PGC::MeshTransform& getMeshTransform(uint16_t subMeshId);
		};
	}
}