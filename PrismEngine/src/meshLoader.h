 #pragma once
#include <vector>
#include "layersMacroses.h"
#include "pgcLayersObjsTemplate.h"
#include "utils.h"
#include "vertex.h"
#include "mesh.h"


DECLARE_PGC_LAYER_INSTANCE(L2)
class MeshLoader : public L2_Object<MeshLoader> {
public:
	MeshLoader(PGC::utils::Context* context, PGC::utils::Settings* settings) : L2_Object(context, settings) {};
	prism::PGC::MeshData loadObj(assets::MeshPath assetSpec, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
	prism::PGC::MeshData loadCube(assets::MeshCube assetSpec, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
	prism::PGC::MeshData loadPlane(assets::MeshPlane assetSpec, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
	prism::PGC::MeshData loadGrid(assets::MeshGrid assetSpec, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
	prism::PGC::MeshData loadIcoSphere(assets::MeshIcoSphere assetSpec, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
	prism::PGC::MeshData loadUvSphere(assets::MeshUvSphere assetSpec, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
	
private:
	void transformVertex(prism::PGC::Vertex& vertex, const glm::mat4& transformMat, const glm::mat3& normalMat);
	glm::mat4 calculateMatrix(prism::PGC::MeshTransform transform);
};
END_NAMESPACE_DECLARATION