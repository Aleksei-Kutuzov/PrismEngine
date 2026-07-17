#pragma once
#include <string>
#include "pgcResourceStorage.h"
#include "mesh.h"
#include "meshLoader.h"
#include "meshComponent.h"
#include "idPool.h"

DECLARE_PGC_LAYER_INSTANCE(L1)
class MeshStorage : public L1_Object<MeshStorage> {
public:
	void createImpl();
	prism::scene::MeshComponent::DataType load(assets::AssetSpec assetSpec);
	prism::PGC::MeshData& getData(prism::scene::MeshComponent::DataType id);
	void update();
	void clear();
	void cleanupImpl();
private:
	prism::PGC::L2::MeshLoader* loader;
	
	std::vector<prism::PGC::MeshData> data;
	prism::utils::IdPool<uint32_t, 1, 0> pool;
	bool isActual = true;

	std::vector<Vertex> allVertices;
	std::vector<uint32_t> allIndices;


};
END_NAMESPACE_DECLARATION