#pragma once
#include "dataHandle.h"
#include "dataPool.h"
#include "mesh.h"

namespace prism {
	namespace scene {
		struct MeshTag {};
		using MeshComponent = DataHandle < prism::PGC::SubMesh, MeshTag > ;
		using MeshDataPool = prism::scene::DataPool<prism::scene::MeshComponent>;
	}
}