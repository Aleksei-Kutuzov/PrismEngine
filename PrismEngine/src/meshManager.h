#pragma once
#include <string>
#include "utils.h"
#include "layersMacroses.h"
#include "pgcLayersObjsTemplate.h"
#include "mesh.h"
#include "meshLoader.h"

DECLARE_PGC_LAYER_INSTANCE(L1)
class MeshStorage : public L1_Object<MeshStorage> {
public:
	void createImpl();
	prism::PGC::MeshIds load(std::string texturePath);
	void update();
	void clear();
	void cleanupImpl();
	prism::PGC::SubMesh& getSubMeshInfo(uint32_t id);
private:
	uint32_t getNextAvailableIndex();
	PGC::L2::MeshLoader* meshLoader;
};
END_NAMESPACE_DECLARATION