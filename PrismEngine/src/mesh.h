#pragma once
#include <cstdint>
#include <filesystem>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <gtc/quaternion.hpp>
#include <gtc/matrix_transform.hpp>

#include "vertex.h"


namespace prism {
	namespace PGC {
		struct SubMesh
		{
			uint32_t vertexOffset = 0;
			uint32_t indexOffset = 0;
			uint32_t vertexCount = 0;
			uint32_t indexCount = 0;

			uint32_t id;

			bool operator==(const SubMesh& other) const {
				return vertexOffset == other.vertexOffset &&
					   indexOffset  == other.indexOffset &&
					   vertexCount  == other.vertexCount &&
					   indexCount   == other.indexCount;
			}

			bool operator!=(const SubMesh& other) const {
				return !(*this == other);
			}

			bool operator<(const SubMesh& other) const {
				if (vertexOffset != other.vertexOffset) return vertexOffset < other.vertexOffset;
				if (indexOffset != other.indexOffset)  return indexOffset < other.indexOffset;
				if (vertexCount != other.vertexCount)  return vertexCount < other.vertexCount;
				return indexCount < other.indexCount;
			}
		};

		struct MeshData {
			struct Transform {
				glm::vec3 position = { 0.f, 0.f , 0.f };
				glm::quat rotation;
				glm::vec3 scale = { 1.f, 1.f, 1.f };
			};
			std::string name;
			std::filesystem::path path;

			std::vector<Vertex> vertices;
			std::vector<uint32_t> indices;

			PGC::SubMesh info;

			Transform transform;
		};
	}
}