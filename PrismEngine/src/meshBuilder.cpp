#include "meshBuilder.h"
#include <glm.hpp>
#include <gtc/quaternion.hpp>
#include <gtc/matrix_transform.hpp>

prism::render::MeshBuilder& prism::render::MeshBuilder::size(uint16_t size) {
	meshParams.resize(size);
	return *this;
}

prism::render::MeshBuilder& prism::render::MeshBuilder::copyAll(prism::scene::MeshComponent mesh)
{
	uint16_t copyMeshSize = 0;
	const prism::scene::MeshComponent::DataType* subMeshes = scene.getDataFromPool<prism::scene::MeshComponent>(mesh, copyMeshSize);

	for (size_t i = 0; i < copyMeshSize; i++) {
		meshParams[i].path = storage.get(subMeshes[i]).path;
		meshParams[i].transform = storage.get(subMeshes[i]).transform;
	}

	return *this;
}

prism::render::MeshBuilder& prism::render::MeshBuilder::copy(prism::scene::MeshComponent mesh, uint16_t subMeshId)
{
	uint16_t copyMeshSize = 0;
	const prism::scene::MeshComponent::DataType* subMeshes = scene.getDataFromPool<prism::scene::MeshComponent>(mesh, copyMeshSize);
	
	meshParams[subMeshId].path = storage.get(subMeshes[subMeshId]).path;

	return *this;
}

prism::render::MeshBuilder& prism::render::MeshBuilder::addSubMesh(std::filesystem::path filename, uint16_t subMeshId)
{
	return addSubMesh(filename, "[all]", subMeshId);
}

prism::render::MeshBuilder& prism::render::MeshBuilder::addSubMesh(std::filesystem::path filename, std::string sourceMeshName, uint16_t subMeshId)
{
	meshParams[subMeshId].path = filename;
	meshParams[subMeshId].sourceMeshName = sourceMeshName;
	return *this;
}


prism::render::MeshBuilder& prism::render::MeshBuilder::position(uint16_t subMeshId, glm::vec3 position)
{
	meshParams[subMeshId].transform.position = position;
	return *this;
}

prism::render::MeshBuilder& prism::render::MeshBuilder::rotation(uint16_t subMeshId, glm::vec3 rotation)
{
	meshParams[subMeshId].transform.rotation = glm::quat(glm::radians(rotation));
	return *this;
}

prism::render::MeshBuilder& prism::render::MeshBuilder::rotation(uint16_t subMeshId, glm::quat rotation)
{
	meshParams[subMeshId].transform.rotation = rotation;
	return *this;
}

prism::render::MeshBuilder& prism::render::MeshBuilder::scale(uint16_t subMeshId, glm::vec3 scale)
{
	meshParams[subMeshId].transform.scale = scale;
	return *this;
}

prism::render::MeshBuilder& prism::render::MeshBuilder::positionBy(uint16_t subMeshId, glm::vec3 positionBy)
{
	meshParams[subMeshId].transform.position += positionBy;
	return *this;
}

prism::render::MeshBuilder& prism::render::MeshBuilder::rotationBy(uint16_t subMeshId, glm::vec3 rotationBy)
{
	glm::quat delta = glm::quat(glm::radians(rotationBy));

	meshParams[subMeshId].transform.rotation *= delta;
	return *this;
}

prism::render::MeshBuilder& prism::render::MeshBuilder::rotationBy(uint16_t subMeshId, glm::quat rotationBy)
{
	meshParams[subMeshId].transform.rotation *= rotationBy;
	return *this;
}

prism::render::MeshBuilder& prism::render::MeshBuilder::scaleBy(uint16_t subMeshId, glm::vec3 scaleBy)
{
	meshParams[subMeshId].transform.scale *= scaleBy;
	return *this;
}

prism::scene::MeshComponent prism::render::MeshBuilder::complete()
{
	prism::scene::MeshComponent mesh;
	uint16_t itemsSize = meshParams.size();
	std::vector<prism::scene::MeshComponent::DataType> items;
	items.resize(itemsSize);

	for (uint16_t i = 0; i < itemsSize; ++i) {
		if (!meshParams[i].path.has_value()) continue;
		items[i] = storage.load(meshParams[i].path.value(), meshParams[i].sourceMeshName, meshParams[i].transform);
	}

	storage.update();

	return scene.addDataToPool<prism::scene::MeshComponent>(items.data(), itemsSize);
}
