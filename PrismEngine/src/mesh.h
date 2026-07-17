#pragma once
#include <cstdint>
#include "assetSpec.h"


namespace prism {
	namespace PGC {
		using SubMesh = uint32_t;

		struct MeshData {
			assets::AssetSpec assetSpec;

			uint32_t vertexOffset = 0;
			uint32_t indexOffset = 0;
			uint32_t vertexCount = 0;
			uint32_t indexCount = 0;
		};
	}
}