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
	static MeshData load(std::filesystem::path path, std::string meshName, prism::PGC::MeshData::Transform transform);
	static void loadObj(prism::PGC::MeshData& meshData);
private:
	static void transformVertex(prism::PGC::Vertex& vertex, const glm::mat4& transformMat, const glm::mat3& normalMat);
	static glm::mat4 calculateMatrix(prism::PGC::MeshData::Transform transform);
};
END_NAMESPACE_DECLARATION