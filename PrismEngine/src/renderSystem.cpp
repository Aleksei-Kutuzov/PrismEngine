#include "renderSystem.h"
#include "cameraComponent.h"
#include "transformComponent.h"
#include "materialComponent.h"
#include "lightsComponent.h"
#include "linker.h"

void prism::scene::RenderSystem::start() {
    renderer = prism::linker.find<prism::scene::Scene, prism::render::Renderer>(scene);
}

void prism::scene::RenderSystem::update()
{

    if (renderer->isRenderingActive()) {
        renderer->beginFrame();

        auto cameras = scene->getEntitiesWithAll<TransformComponent, CameraComponent>();
        for (auto camera : cameras) {
            CameraComponent* cameraComponent = scene->getComponent<CameraComponent>(camera);
            if (cameraComponent->isActive) {
                TransformComponent* transformComponent = scene->getComponent<TransformComponent>(camera);
                renderer->updateCamera(transformComponent, cameraComponent);
            }
        }
        auto forRenderingEntites = scene->getEntitiesWithAll<TransformComponent, MeshComponent>();

        MaterialComponent defaultMaterial = { INVALID_TEXTURE_ID };

        std::map<uint32_t, std::vector<std::pair<TransformComponent*, MaterialComponent*>>> meshBatches;
        
        for (auto entity : forRenderingEntites) {
            TransformComponent* transform = scene->getComponent<TransformComponent>(entity);
            MeshComponent* mesh = scene->getComponent<MeshComponent>(entity);
            MaterialComponent* material = scene->getComponent<MaterialComponent>(entity);

            if (!mesh || mesh->id == INVALID_DATA_HANDLE || !transform) continue;
            if (!material) material = &defaultMaterial;

            // Группируем по registry ID для инстансинга
            meshBatches[mesh->id].emplace_back(transform, material);
        }

        std::vector<prism::render::InstanceData> renderData;
        renderData.reserve(forRenderingEntites.size());

        std::map<uint32_t, uint32_t> meshInstanceOffsets;

        for (auto& [meshId, instances] : meshBatches) {
            meshInstanceOffsets[meshId] = static_cast<uint32_t>(renderData.size());
            for (auto& [transform, material] : instances) {
                renderData.push_back({ transform, material });
            }
        }

        prism::render::LightData lightData;
        auto pointsLightEntitys =  scene->getEntitiesWith<PointLightComponent>();
        for (auto pointLightEntity : pointsLightEntitys) {
            PointLightComponent* pointsLight = scene->getComponent<PointLightComponent>(pointLightEntity);
            
            if (auto* transform = scene->getComponent<TransformComponent>(pointLightEntity)) { pointsLight->pos += transform->pos; }
            lightData.pointLights.push_back(*pointsLight);
        }

        auto directionalLightEntitys = scene->getEntitiesWith<DirectionalLightComponents>();
        for (auto directionalLightEntity : directionalLightEntitys) {
            DirectionalLightComponents* dirLight = scene->getComponent<DirectionalLightComponents>(directionalLightEntity);
            lightData.directionalLights.push_back(*dirLight);
        }

        renderer->updateInstances(renderData);
        renderer->updateLights(&lightData);
        
        renderer->beginRender();
        renderer->bindDefault();
        renderer->bindObjectsData();

        for (auto& [meshId, instances] : meshBatches) {
            if (instances.empty()) continue;

            MeshComponent meshHandle{ meshId };

            uint32_t instanceCount = static_cast<uint32_t>(instances.size());
            uint32_t firstInstance = meshInstanceOffsets[meshId];

            renderer->drawMesh(meshHandle, instanceCount, firstInstance);
        }

        renderer->endRender();
        renderer->endFrame();

     }
}
