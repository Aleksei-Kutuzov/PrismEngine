#include "meshBuilder.h"
#include <glm.hpp>
#include <gtc/quaternion.hpp>
#include <gtc/matrix_transform.hpp>
#include "resourcesPath.h"

prism::PGC::MeshTransform& prism::render::MeshBuilder::getMeshTransform(uint16_t subMeshId) {
	if (subMeshId >= meshParams.size()) meshParams.resize(subMeshId + 1);

	if (std::holds_alternative<std::monostate>(meshParams[subMeshId])) meshParams[subMeshId] = assets::MeshPath();

   	return std::visit(prism::assets::overloaded{
	    [](assets::MeshPath& p) -> prism::PGC::MeshTransform& { return p.transform; },
	    [](assets::MeshCube& c) -> prism::PGC::MeshTransform& { return c.transform; },
	    [](assets::MeshPlane& l) -> prism::PGC::MeshTransform& { return l.transform; },
		[](assets::MeshGrid& g) -> prism::PGC::MeshTransform& { return g.transform; },
		[](assets::MeshIcoSphere& i) -> prism::PGC::MeshTransform& { return i.transform; },
		[](assets::MeshUvSphere& u) -> prism::PGC::MeshTransform& { return u.transform; },
		[](auto& bad) -> prism::PGC::MeshTransform& {throw std::runtime_error("Unexpected mesh asset type"); }
	}, meshParams[subMeshId]);
}


prism::render::MeshBuilder& prism::render::MeshBuilder::size(uint16_t size) {
	meshParams.resize(size);
	return *this;
}

prism::render::MeshBuilder& prism::render::MeshBuilder::copyAll(prism::scene::MeshComponent mesh)
{
	uint16_t copyMeshSize = 0;
	const prism::scene::MeshComponent::DataType* subMeshes = scene.getDataFromPool<prism::scene::MeshComponent>(mesh, copyMeshSize);

	meshParams.resize(copyMeshSize);
	for (size_t i = 0; i < copyMeshSize; i++) {
		meshParams[i] = storage.getData(subMeshes[i]).assetSpec;
	}

	return *this;
}

prism::render::MeshBuilder& prism::render::MeshBuilder::copy(uint16_t subMeshId, prism::scene::MeshComponent mesh)
{
	uint16_t copyMeshSize = 0;
	const prism::scene::MeshComponent::DataType* subMeshes = scene.getDataFromPool<prism::scene::MeshComponent>(mesh, copyMeshSize);
	
	if (subMeshId < copyMeshSize) {
		if (subMeshId >= meshParams.size()) meshParams.resize(subMeshId + 1);
		meshParams[subMeshId] = storage.getData(subMeshes[subMeshId]).assetSpec;
	}

	return *this;
}

prism::render::MeshBuilder& prism::render::MeshBuilder::model(uint16_t subMeshId, std::filesystem::path filepath)
{
	return model(subMeshId, filepath, "[all]");
}

prism::render::MeshBuilder& prism::render::MeshBuilder::model(uint16_t subMeshId, std::filesystem::path filepath, std::string sourceMeshName)
{
	meshParams[subMeshId] = assets::MeshPath{ filepath, sourceMeshName, getMeshTransform(subMeshId) };
	return *this;
}

prism::render::MeshBuilder& prism::render::MeshBuilder::cube(uint16_t subMeshId)
{
	meshParams[subMeshId] = assets::MeshCube{ getMeshTransform(subMeshId)};
	return *this;
}

prism::render::MeshBuilder& prism::render::MeshBuilder::plane(uint16_t subMeshId)
{
	meshParams[subMeshId] = assets::MeshPlane{ getMeshTransform(subMeshId) };
	return *this;
}

prism::render::MeshBuilder& prism::render::MeshBuilder::grid(uint16_t subMeshId, uint16_t subdivsX, uint16_t subdivsZ, uint16_t repeatX, uint16_t repeatZ)
{
	meshParams[subMeshId] = assets::MeshGrid{ subdivsX, subdivsZ, repeatX, repeatZ, getMeshTransform(subMeshId) };
	return *this;
}

prism::render::MeshBuilder& prism::render::MeshBuilder::icoSphere(uint16_t subMeshId, uint8_t subdivisiones)
{
	meshParams[subMeshId] = assets::MeshIcoSphere{subdivisiones, getMeshTransform(subMeshId) };
	return *this;
}

prism::render::MeshBuilder& prism::render::MeshBuilder::uvSphere(uint16_t subMeshId, uint16_t subdivsVert, uint16_t subdivsHoriz)
{
	meshParams[subMeshId] = assets::MeshUvSphere{ subdivsVert, subdivsHoriz, getMeshTransform(subMeshId) };
	return *this;
}


prism::render::MeshBuilder& prism::render::MeshBuilder::position(uint16_t subMeshId, glm::vec3 position)
{
	getMeshTransform(subMeshId).position = position;
	return *this;
}

prism::render::MeshBuilder& prism::render::MeshBuilder::rotation(uint16_t subMeshId, glm::vec3 rotation)
{
	getMeshTransform(subMeshId).rotation = glm::quat(glm::radians(rotation));
	return *this;
}

prism::render::MeshBuilder& prism::render::MeshBuilder::rotation(uint16_t subMeshId, glm::quat rotation)
{
	getMeshTransform(subMeshId).rotation = rotation;
	return *this;
}

prism::render::MeshBuilder& prism::render::MeshBuilder::scale(uint16_t subMeshId, glm::vec3 scale)
{
	getMeshTransform(subMeshId).scale = scale;
	return *this;
}

prism::render::MeshBuilder& prism::render::MeshBuilder::positionBy(uint16_t subMeshId, glm::vec3 positionBy)
{
	getMeshTransform(subMeshId).position += positionBy;
	return *this;
}

prism::render::MeshBuilder& prism::render::MeshBuilder::rotationBy(uint16_t subMeshId, glm::vec3 rotationBy)
{
	glm::quat delta = glm::quat(glm::radians(rotationBy));

	getMeshTransform(subMeshId).rotation *= delta;
	return *this;
}

prism::render::MeshBuilder& prism::render::MeshBuilder::rotationBy(uint16_t subMeshId, glm::quat rotationBy)
{
	getMeshTransform(subMeshId).rotation *= rotationBy;
	return *this;
}

prism::render::MeshBuilder& prism::render::MeshBuilder::scaleBy(uint16_t subMeshId, glm::vec3 scaleBy)
{
	getMeshTransform(subMeshId).scale *= scaleBy;
	return *this;
}

prism::scene::MeshComponent prism::render::MeshBuilder::complete()
{
	prism::scene::MeshComponent mesh;
	uint16_t itemsSize = meshParams.size();
	std::vector<prism::scene::MeshComponent::DataType> items;
	items.resize(itemsSize);

	for (uint16_t i = 0; i < itemsSize; ++i) {
		if (std::holds_alternative<std::monostate>(meshParams[i])) continue;
		items[i] = storage.load(meshParams[i]);
	}

	storage.update();

	return scene.addDataToPool<prism::scene::MeshComponent>(items.data(), itemsSize);
}
