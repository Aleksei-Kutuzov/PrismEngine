#pragma once
#include <string>
#include "pgcResourceStorage.h"
#include "mesh.h"
#include "meshLoader.h"
#include "meshComponent.h"

DECLARE_PGC_LAYER_INSTANCE(L1)
class MeshStorage : public Storage<prism::scene::MeshComponent::DataType, prism::PGC::MeshData, PGC::L2::MeshLoader, MeshStorage> {
public:
	void createImpl();
	prism::scene::MeshComponent::DataType loadImpl(MeshData meshData);
	void updateImpl();
	uint32_t getId(prism::scene::MeshComponent::DataType dataId);
	void unloadImpl(prism::scene::MeshComponent::DataType id) { throw std::runtime_error("method is not allowed"); };
	void clearImpl();
	std::filesystem::path getPathForId(std::filesystem::path path, std::string meshName, prism::PGC::MeshData::Transform transform);
private:
	std::vector<Vertex> allVertices;
	std::vector<uint32_t> allIndices;
};
END_NAMESPACE_DECLARATION