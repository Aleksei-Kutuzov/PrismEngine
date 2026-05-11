#include "renderSystem.h"
#include "cameraComponent.h"
#include "transformComponent.h"
#include "materialComponent.h"
#include "lightsComponent.h"
#include "linker.h"
#include "pipelineComponent.h"

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

        auto renderingObjects = scene->getEntitiesWithAll<TransformComponent, MeshComponent>();
        
        batches.clear();
        
        for (auto object : renderingObjects) {
            TransformComponent* transform = scene->getComponent<TransformComponent>(object);
            MeshComponent* mesh = scene->getComponent<MeshComponent>(object);
            MaterialComponent* material = scene->getComponent<MaterialComponent>(object);
            PipelineComponent* pipeline = scene->getComponent<PipelineComponent>(object);
            
            const MeshComponent::DataType* subMeshes; uint16_t subMeshesCount = 0;
            const MaterialComponent::DataType* subMaterials; uint16_t subMaterialsCount = 0;
            PipelineIndex pipelineIndex = renderer->getDefaultPipeline().pipeline;
            
            if (mesh->isValid()) subMeshes = scene->getDataFromPool(*mesh, subMeshesCount);
            else { logger::info("NO FOUNND SUBMESH " + std::to_string(mesh->id) + "IN DATAPOOL"); continue;/*TODO*/ }
            if (material->isValid()) subMaterials = scene->getDataFromPool(*material, subMaterialsCount);
            else { logger::info("NO FOUNND SUBMATERIAL " + std::to_string(material->id) + "IN DATAPOOL"); continue;/*TODO*/ }
            if (subMaterialsCount < subMeshesCount) logger::info("SUBMATERIALS COUNT(" + std::to_string(subMaterialsCount) + ") < SUBMESHES COUNT(" + std::to_string(subMeshesCount) + ")"); /*TODO*/
            if (pipeline) pipelineIndex = pipeline->pipeline;

            for (uint16_t i = 0; i < subMeshesCount; i++)
            {
                batches.push_back(prism::render::RenderObjectBatch(0, pipelineIndex, *(subMeshes+i),
                    transform, subMaterials+i));
            }
        }

        if (batches.size() == 0) return;

        std::sort(batches.begin(), batches.end());

        prism::render::LightData lightData;
        auto pointsLightEntitys =  scene->getEntitiesWith<PointLightComponent>();
        for (auto pointLightEntity : pointsLightEntitys) {
            PointLightComponent pointsLight = *scene->getComponent<PointLightComponent>(pointLightEntity);
            
            if (TransformComponent* transform = scene->getComponent<TransformComponent>(pointLightEntity)) { pointsLight.pos += transform->pos; }
            lightData.pointLights.push_back(pointsLight);
        }

        auto directionalLightEntitys = scene->getEntitiesWith<DirectionalLightComponents>();
        for (auto directionalLightEntity : directionalLightEntitys) {
            DirectionalLightComponents* dirLight = scene->getComponent<DirectionalLightComponents>(directionalLightEntity);
            lightData.directionalLights.push_back(*dirLight);
        }

        renderer->updateRenderObjects(batches);
        renderer->updateLights(&lightData);
        
        renderer->beginRender();
        renderer->bindDefault();
        renderer->bindObjectsData();

        MeshComponent::DataType oldSubMesh = batches[0].subMesh;
        PipelineIndex oldPipelineIndex = batches[0].pipeline;

        uint32_t instanceCount = 0;
        uint32_t firstIndex = 0;
        for (auto& obj : batches) {

            if (oldSubMesh != obj.subMesh) {
                renderer->drawMesh(oldSubMesh, instanceCount, firstIndex);
                firstIndex += instanceCount;
                instanceCount = 0;
            }

            if (oldPipelineIndex != obj.pipeline) {
                renderer->bindPipeline(obj.pipeline);
            }

            instanceCount++;
            

            oldSubMesh = obj.subMesh;
            oldPipelineIndex = obj.pipeline;
        }

        if (instanceCount > 0) {
            renderer->drawMesh(oldSubMesh, instanceCount, firstIndex);
        }

        renderer->endRender();
        renderer->endFrame();
        batches.clear();
     }
}
