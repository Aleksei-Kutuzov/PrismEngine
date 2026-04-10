#include "scene.h"

prism::scene::Entity prism::scene::Scene::createEntity()
{
	return entityManager.createEntity();
}

bool prism::scene::Scene::destroyEntity(Entity entityId)
{
	componentManager.removeAllComponents(entityId);
	return entityManager.destroyEntity(entityId);
}

void prism::scene::Scene::enableSystem(SystemId systemId)
{
	systemManager.enableSystem(systemId);
}

void prism::scene::Scene::disableSystem(SystemId systemId)
{
	systemManager.disableSystem(systemId);
}

void prism::scene::Scene::linkRenderer(prism::render::Renderer* renderer)
{
	this->renderer = renderer;
}

prism::render::Renderer* prism::scene::Scene::getRenderer()
{
	if (!renderer) logger::logError(logger::Error::RENDERER_IS_NOT_INSTALLED_FOR_SCENE);
	return renderer;
}

void prism::scene::Scene::addMesh(Entity entity, MeshComponent mesh)
{
	addComponent(entity, mesh);
	renderer->meshRegistry->addRef(mesh.id);
}

void prism::scene::Scene::delMesh(Entity entity)
{
	MeshComponent* mesh = getComponent<MeshComponent>(entity);
	renderer->meshRegistry->remove(mesh->id);
}
