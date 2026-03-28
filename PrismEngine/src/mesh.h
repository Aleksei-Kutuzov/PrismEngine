#pragma once
#include <cstdint>

namespace prism {
	using Mesh = std::vector<uint32_t>;

	namespace PGC {
		struct SubMesh
		{
			uint32_t vertexOffset = 0;
			uint32_t indexOffset = 0;
			uint32_t vertexCount = 0;
			uint32_t indexCount = 0;
		};

		using Mesh = std::vector<PGC::SubMesh>;

		struct MeshData {
			std::vector<Vertex> vertices;
			std::vector<uint32_t> indices;

			Mesh infos;
		};
	}
}