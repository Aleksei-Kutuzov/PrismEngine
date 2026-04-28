#pragma once
#include "DataHandle.h"
#include "dataPool.h"

namespace prism {
	namespace scene {
		struct MeshTag {};
		using MeshComponent = DataHandle<uint32_t, MeshTag>;
		using MeshDataPool = prism::scene::DataPool<prism::scene::MeshComponent>;
	}
}