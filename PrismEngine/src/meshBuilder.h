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
			prism::scene::Scene& scene;
			prism::PGC::L1::MeshStorage& storage;

			struct MeshParam {
				std::string sourceMeshName;
				std::optional<std::filesystem::path> path;
				prism::PGC::MeshData::Transform transform;
			};

			
			std::vector<MeshParam> meshParams;

			MeshBuilder(prism::scene::Scene& scene, prism::PGC::L1::MeshStorage& storage) : scene(scene), storage(storage) {}

			MeshBuilder& size(uint16_t size);

			MeshBuilder& copyAll(prism::scene::MeshComponent mesh);
			MeshBuilder& copy(prism::scene::MeshComponent mesh, uint16_t subMeshId);

			MeshBuilder& addSubMesh(std::filesystem::path filename, uint16_t subMeshId);
			MeshBuilder& addSubMesh(std::filesystem::path filename, std::string sourceMeshName, uint16_t subMeshId);
			
			MeshBuilder& addCube(uint16_t subMeshId);
			MeshBuilder& addPlane(uint16_t subMeshId);
			MeshBuilder& addIcoSphere(uint16_t subMeshId, uint8_t subdivisiones);
			MeshBuilder& addUvSphere(uint16_t subMeshId, uint8_t subdivsVert, uint8_t subdivsHoriz);
			
			MeshBuilder& position(uint16_t subMeshId, glm::vec3 position);
			MeshBuilder& rotation(uint16_t subMeshId, glm::vec3 rotation);
			MeshBuilder& rotation(uint16_t subMeshId, glm::quat rotation);
			MeshBuilder& scale(uint16_t subMeshId, glm::vec3 scale);
			
			MeshBuilder& positionBy(uint16_t subMeshId, glm::vec3 positionBy);
			MeshBuilder& rotationBy(uint16_t subMeshId, glm::vec3 rotationBy);
			MeshBuilder& rotationBy(uint16_t subMeshId, glm::quat rotationBy);
			MeshBuilder& scaleBy(uint16_t subMeshId, glm::vec3 scaleBy);
			
			prism::scene::MeshComponent complete();
		};
	}
}